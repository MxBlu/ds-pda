# GEMINI.md - DS PDA Project Context

## Project Overview
**DS PDA** is a personal assistant homebrew application for the Nintendo DS. It provides a "PDA OS" interface with widgets for weather, transport, tasks, and budget tracking.

### Core Technologies
- **SDK**: [BlocksDS](https://github.com/blocksds/sdk) - A modern, open-source SDK for Nintendo DS development.
- **Libraries**:
    - `libnds`: Low-level access to DS hardware.
    - `µLibrary` (ulibrary): A 2D-in-3D graphics library used for the main UI.
    - `Maxmod`: Audio library for modules (MOD, S3M) and sound effects.
- **Languages**: C (ARM9).

### Architecture
- **ARM9**: Main application logic, UI rendering via µLibrary, and user interaction.
- **ARM7**: Standard system tasks (audio, wifi) handled by the pre-compiled `arm7_dswifi_maxmod.elf` from the SDK.
- **Assets**:
    - **Graphics**: PNG files in `graphics/` are converted to DS-compatible formats using `grit`.
    - **Audio**: Audio files in `audio/` are processed into a soundbank using `mmutil`.
    - **Data**: Binary files in `data/` are converted to C arrays using `bin2c`.

## Building and Running

### Build Environment
This project requires the BlocksDS SDK. In this environment, `make` can be used directly if `wf-pacman` is present (check with `which wf-pacman`). If `wf-pacman` is not present, use the running Docker container (`skylyrac/blocksds`).

### Build Commands
If `wf-pacman` is present, run these in the project root:
- **Standard Build**: `make`
- **Verbose Build**: `make VERBOSE=1`
- **Clean Build**: `make clean`

Otherwise, use the Docker container:
- **Standard Build**: `docker exec -w /work <container_id> make`
- **Verbose Build**: `docker exec -w /work <container_id> make VERBOSE=1`
- **Clean Build**: `docker exec -w /work <container_id> make clean`

### Running & Testing
To verify changes, run the emulator on the host and capture a screenshot. **Visual validation is mandatory for all UI changes.**

1. **Run Emulator in background**:
   Use the `run_shell_command` tool and explicitly set the `is_background: true` parameter:
     ```json
     {
       "command": "melonDS ds-pda.nds",
       "is_background": true
     }
     ```
2. **Capture Screenshot**: Use the screenshot MCP server tools (`mcp_screenshot_list_windows` and `mcp_screenshot_capture_window`) to identify and capture the `melonDS` window.
3. **Analyze Screenshot**: **You MUST view and describe the captured screenshot.** Compare it against reference images in `references/` or the expected outcome to ensure the UI is rendered correctly and no regressions (e.g., corrupted textures, incorrect layout) are present.
4. **Close Emulator**: Identify the PID and kill it:
   ```bash
   ps aux | grep melonDS
   kill <PID>
   ```
  **CRITICAL**: Do not use pkill, it does not work for melonDS processes.
## Development Conventions

### Adding Assets
- **Graphics**: Place PNG files in `graphics/`. Each PNG should have a corresponding `.grit` file with conversion settings.
- **Audio**: Place `.mod`, `.s3m`, `.xm`, or `.wav` files in `audio/`. They will be automatically included in the Maxmod soundbank.
- **Binary Data**: Place `.bin` files in `data/`.

### Reference Images
- **Location**: `references/`
- **Usage**: When the user mentions "refer to the reference", use the images in this folder (e.g., `top.png`, `bottom-agenda.png`) to understand the intended UI design and layout for the PDA interface.

### Visual Validation
- **Mandatory**: Always perform visual validation of UI changes by capturing and analyzing screenshots using the emulator, as mandated in the [Running & Testing](#running--testing) section.

### Source Code
- **Entry Point**: `source/main.c` is the primary entry point.
- **µLibrary Usage**: The project uses µLibrary's 2D-in-3D rendering. Always ensure VRAM banks are correctly allocated (Bank A for textures) before initializing µLibrary.
- **Screen Layout**:
    - **Top Screen**: Reserved for the PDA graphical interface.
    - **Bottom Screen**: Currently used for a debug console/status output.

### Coding Style
- Follow standard C99/C11 conventions suitable for embedded systems.
- Prefer integer math over floating point where possible to avoid performance overhead on the DS's hardware (which lacks an FPU).
- Use `libnds` types like `u16`, `u32`, `RGB15` for DS-specific operations.
