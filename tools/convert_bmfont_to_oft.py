import sys
import struct
import os
import re

if len(sys.argv) < 3:
    print("Usage: python convert_bmfont_to_oft.py <input.fnt> <output.bin>")
    sys.exit(1)

input_fnt = sys.argv[1]
output_bin = sys.argv[2]

if not os.path.exists(input_fnt):
    print(f"Error: {input_fnt} not found.")
    sys.exit(1)

# Parse FNT file
fnt_dir = os.path.dirname(input_fnt)
chars = {}
lineHeight = 13
pages = {}

with open(input_fnt, 'r') as f:
    for line in f:
        line = line.strip()
        if line.startswith("common "):
            m = re.search(r'lineHeight=(\d+)', line)
            if m: lineHeight = int(m.group(1))
        elif line.startswith("page "):
            m_id = re.search(r'id=(\d+)', line)
            m_file = re.search(r'file="([^"]+)"', line)
            if m_id and m_file:
                pages[int(m_id.group(1))] = m_file.group(1)
        elif line.startswith("char "):
            # char id=32 x=99 y=28 width=3 height=13 xoffset=-1 yoffset=0 xadvance=8 page=0
            c = {}
            for kv in re.finditer(r'(\w+)=(-?\d+)', line):
                c[kv.group(1)] = int(kv.group(2))
            if 'id' in c:
                chars[c['id']] = c

if len(pages) == 0:
    print("Error: No pages found in FNT file.")
    sys.exit(1)

page_file = pages[0]
bmp_file = os.path.join(fnt_dir, page_file)

# If it's a PNG, we expect the user/script to have converted it to BMP
if page_file.lower().endswith('.png'):
    bmp_file = os.path.join(fnt_dir, page_file[:-4] + '.bmp')

if not os.path.exists(bmp_file):
    print(f"Error: image file {bmp_file} not found. Please convert FNT PNG to BMP first.")
    sys.exit(1)

# Load BMP
with open(bmp_file, 'rb') as f:
    bmp_data = f.read()

offset = struct.unpack_from('<I', bmp_data, 10)[0]
bmp_w = struct.unpack_from('<i', bmp_data, 18)[0]
bmp_h = struct.unpack_from('<i', bmp_data, 22)[0]
bpp = struct.unpack_from('<H', bmp_data, 28)[0]

is_bottom_up = bmp_h > 0
bmp_h = abs(bmp_h)
row_bytes = ((bmp_w * bpp + 31) // 32) * 4
bytes_per_pixel = bpp // 8

def get_pixel(x, y):
    if x < 0 or x >= bmp_w or y < 0 or y >= bmp_h: return 0
    if is_bottom_up:
        y_bmp = bmp_h - 1 - y
    else:
        y_bmp = y
    idx = offset + y_bmp * row_bytes + x * bytes_per_pixel
    if idx + 2 < len(bmp_data):
        b = bmp_data[idx]
        g = bmp_data[idx+1]
        r = bmp_data[idx+2]
        # if alpha is present, use it, else use RGB luminance
        if bytes_per_pixel == 4:
            a = bmp_data[idx+3]
            if a > 128: return 1
            if r > 128 or g > 128 or b > 128: return 1
        else:
            if r > 128 or g > 128 or b > 128: return 1
    return 0

# Determine OSLFont metrics.
#
# - char_width controls how many source bits are stored per row (lineWidth bytes).
# - width_table (xadvance) controls text cursor advance in uLibrary.
# - added_space lets characters draw wider than their advance (right overhang),
#   which is needed for some Proggy glyphs in the 10px set.
max_xadvance = max(c.get('xadvance', 8) for c in chars.values())
max_extent = max((c.get('xoffset', 0) + c.get('width', 0)) for c in chars.values())

char_width = max(max_xadvance, max_extent)
char_height = lineHeight
line_width = (char_width + 7) // 8
added_space = max(0, max_extent - max_xadvance)

print(
    f"Generating OSLFont: char_width={char_width}, char_height={char_height}, "
    f"line_width={line_width}, added_space={added_space}, chars={len(chars)}"
)

def make_bin():
    header = bytearray(64)
    header[0:12] = b'OSLFont v01\0'
    header[12:16] = bytes([1, 1, 0, 0]) # bitplanes=1, variable=1
    header[16:20] = struct.pack('<I', char_width)
    header[20:24] = struct.pack('<I', char_height)
    header[24:28] = struct.pack('<I', line_width)
    header[28] = added_space & 0xFF

    width_table = bytearray(256)
    
    # Fill width table with default advance.
    for i in range(256):
        width_table[i] = max_xadvance

    # We need ceil(char_width / 8) bytes per row.
    bytes_per_char_row = (char_width + 7) // 8
    
    pixel_data = bytearray()
    
    for char_idx in range(256):
        c = chars.get(char_idx)
        grid = [[0]*char_width for _ in range(char_height)]
        
        if c is not None:
            width_table[char_idx] = c.get('xadvance', max_xadvance)
            
            x_src = c['x']
            y_src = c['y']
            w_src = c['width']
            h_src = c['height']
            x_off = c['xoffset']
            y_off = c['yoffset']
            
            for gy in range(h_src):
                for gx in range(w_src):
                    dst_x = x_off + gx
                    dst_y = y_off + gy
                    if 0 <= dst_x < char_width and 0 <= dst_y < char_height:
                        grid[dst_y][dst_x] = get_pixel(x_src + gx, y_src + gy)

        for row in grid:
            # write row to bytes
            for b_idx in range(bytes_per_char_row):
                byte_val = 0
                for bit in range(8):
                    pixel_x = b_idx * 8 + bit
                    if pixel_x < char_width and row[pixel_x] == 1:
                        byte_val |= (1 << bit) # leftmost is bit 0
                pixel_data.append(byte_val)
                
    return header + width_table + pixel_data

with open(output_bin, 'wb') as f:
    f.write(make_bin())

print(f"Success: Wrote valid OSLFont data to {output_bin}")
