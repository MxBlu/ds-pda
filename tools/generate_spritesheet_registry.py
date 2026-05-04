#!/usr/bin/env python3

import argparse
import os
import re
import sys


HEADER_GUARD = "SPRITESHEET_REGISTRY_H"


def parse_header(path):
    base = os.path.basename(path)
    # Multi-sheet: spritesheet_12_s1_png.h
    match = re.fullmatch(r"spritesheet_(\d+)_s(\d+)_png\.h", base)
    if match:
        size = int(match.group(1))
        sheet = int(match.group(2))
        symbol = base[:-2]  # remove ".h"
        return size, sheet, symbol
    # Single sheet: spritesheet_12_png.h
    match = re.fullmatch(r"spritesheet_(\d+)_png\.h", base)
    if match:
        size = int(match.group(1))
        symbol = base[:-2]  # remove ".h"
        return size, 0, symbol
    return None


def render(entries):
    out = []
    out.append(f"#ifndef {HEADER_GUARD}")
    out.append(f"#define {HEADER_GUARD}")
    out.append("")

    for _, _, symbol in entries:
        out.append(f"#include \"{symbol}.h\"")

    out.append("")
    out.append("typedef struct spritesheet_registry_entry {")
    out.append("    int size;")
    out.append("    int sheet;")
    out.append("    const unsigned char *data;")
    out.append("    unsigned int data_size;")
    out.append("} spritesheet_registry_entry_t;")
    out.append("")
    out.append("static const spritesheet_registry_entry_t SPRITESHEET_REGISTRY[] = {")

    for size, sheet, symbol in entries:
        out.append(
            f"    {{{size}, {sheet}, {symbol}, sizeof({symbol})}},"
        )

    out.append("};")
    out.append("")
    out.append(
        "static const unsigned int SPRITESHEET_REGISTRY_COUNT = "
        "sizeof(SPRITESHEET_REGISTRY) / sizeof(SPRITESHEET_REGISTRY[0]);"
    )
    out.append("")
    out.append(f"#endif /* {HEADER_GUARD} */")
    out.append("")
    return "\n".join(out)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", required=True)
    parser.add_argument("headers", nargs="+")
    args = parser.parse_args()

    entries = []
    for header in args.headers:
        parsed = parse_header(header)
        if parsed is not None:
            entries.append(parsed)

    if not entries:
        print("No spritesheet headers provided", file=sys.stderr)
        return 1

    entries.sort(key=lambda item: (item[0], item[1]))

    content = render(entries)

    with open(args.output, "w", encoding="ascii") as f:
        f.write(content)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
