# The STM32F746G-Discovery DSP Repository

This repository contains a PlatformIO-based codebase that compiles DSP programs onto a `STM32F746G-Discovery` board. Multiple example files can be found in `/examples`. Build environments are used to select which example file is copmiled. Check out the [example `readme.md` file](/examples/readme.md) for instructions on selecting build environments.

## PlatformIO Toolchain and VS Code IDE

This project uses the PlatformIO toolchain, an extension of VS Code, to build the project and provide some starter files (such as Cortex-M startup assembly). This repository contains CMSIS headers, the Board Support Package (BSP) for the Discovery, and HAL drivers (from ST's version `2.9.0`).

PlatformIO uses the GNU C compiler `gcc` as well as the GNU ARM assembler `gcc-arm-none-eabi`.

Build configuration can be found in `platformio.ini` in the root of the repo. The ST drivers can be found in `/lib/cube_f7_2_9_0`. Wrappers are found in the primary application directory of `/src` and `/include`.

For more information on the toolchain, see [`toolchain_notes.md`](/docs/toolchain_notes.md).

### VS Code

This project is best built and edited in VS Code (VSC) as VSC can be configured with extensions to improve the building and editing experience. Some notable extensions are:

- **PlatformIO**: to build and debug the embedded application.
- **Markdown**: to render these `readme.md` files as pretty text (although this is optional).
- **MATLAB**: to connect VS Code to your existing MATLAB interpreter to run simple programs (see the `/matlab` directory for examples and read its [`readme.md`](/matlab/readme.md)).

To install these extensions, it is recommended to use the provided VSC profile in this repository (located in `/.vscode`). Open VSC's Profile Editor to import this profile. This will bring in all the extensions automatically. Otherwise, if you prefer to use your own extension set, you can manually install extensions.

# Lab Experiments

Lab experiment entry code is stored in `/examples`. Each of these files contains a `main()` entrypoint and thus only one of these files can be compiled at a time (files in the `/src` folder are always compiled).

To change experiments, we must tell PlatformIO to build a specific source file in the `/examples` directory. This is done by selecting a build environment defined in `platformio.ini`.