# Repository Organization

This document provides an overview to the file structure of the repository. While most of the repo is designed to be compatible with PlatformIO, some additional directories are used as utilities.

## Documentation

Documentation readme files are contained in the `/docs` directory. Image and animation assets can be found in the `/docs/assets` directory which are referenced by readme files.

## PlatformIO

These are directories related to PlatformIO and embedded resources.

### Standard Directories

The `/src`, `/include`, and `/lib` directories are all standard PIO directories:

- `/src` Contains shared application logic used across examples. These will always be compiled by PIO unless the configuration says otherwise.
- `/include` Contains project-specific header files.
- `/lib/cube_f7_2_9_0` Contains the STM32CubeF7 2.9.0 firmware package from STMicroelectronics with a few patches already applied. The organization of the firmware package is very precise - please see [`docs/firmware_stack.md`](/docs/firmware_stack.md) for more information.

The `/.pio` directory contains build artifacts and can be removed at any time.

### Extra Directories

- `/examples` Contains example source code files that each contain the `main()` entrypoint. PlatformIO does not compile files in this directory by default. However, by setting a build environment, you instruct PIO to compile one of these example files. 

## MATLAB

This repository also includes some MATLAB utilities related to lab activities. These can be found in `/matlab`.

This repository includes a `startup.m` script in the directory root. When MATLAB's current directory is set to this repository (or a command window prompt is opened to this repo), the startup script will immediately execute. The startup script adds the `/matlab` directory to your path so users don't have to `cd` into the directory.

Using MATLAB requires MATLAB to be installed on your machine and you must have the MATLAB extension in VS Code (which the `DSP STM Discovery` profile includes).

## VS Code

The `/.vscode` directory contains configuration files for VS Code. PlatformIO automatically generates `c_cpp_properties.json` and `launch.json`, so do not change these. These tell PIO what to do when the debugger is started.

The `extensions.json` file contains a list of extensions that are recommended to the user when the workspaced is opened in VS Code. The `settings.json` contains VS Code settings that will apply to only this project (such as keyboard shortcuts or any other UI settings).