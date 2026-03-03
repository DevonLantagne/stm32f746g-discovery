# The STM32F746G-Discovery DSP Repository

This repository contains a PlatformIO-based codebase that compiles DSP programs onto a [STM32F746G-Discovery](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html) board for DSP education. Multiple example files can be found in `/examples`. Build environments are used to select which example file is compiled. Both MATLAB and Python utilities are also provided to supplement lab activities.

## Quick Start

See [`docs/quick_start_guide.md`](/docs/quick_start_guide.md) on how to set up VS Code to build and run an example on your hardware.

## Documentation

### Repository Documentation

Further documentation an be found in `/docs`:

- [Porting from Keil uVision to PlatformIO: `keil_to_pio.md`](/docs/keil_to_pio.md)
- [Using VS Code: `vscode_guide.md`](/docs/vscode_guide.md)
- [Understanding the repository structure: `repo_structure.md`](/docs/repo_structure.md)
- [PlatformIO Build System: `build_system.md`](/docs/build_system.md)
- [Using the VS Code Debugger with GDB: `debugging.md`](/docs/debugging.md)

### External Documentation

- [STM32F746G-Discovery ST Product Page](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html)
- [PlatformIO Documentation](https://docs.platformio.org/en/stable/home/index.html)
- [VS Code Documentation](https://code.visualstudio.com/Docs)

## Key Directories

For a full description of the entire repository file structure, see [`docs/repo_structure.md`](/docs/repo_structure.md).

### `/examples`

The `/examples` directory contains source files that contain the program's `main()` entrypoint as well as application-specific hooks such as the data-sampled ISR or DMA processing. This is where you will spend most of your time.

Only one of these files can be included in a build at one time since they all contain `main()`. You tell PIO which one to build by selecting the corresponding build environment in the bottom status bar. Build environments are defined in the `platformio.ini` file. See [`docs/build_system.md`](/docs/build_system.md) for more information.

### `/src` and `/include`

This is the shared logic used by all examples. This includes the audio codec and display configuration as well as interrupt hooks.

### `/matlab`

This directory contains MATLAB utility scripts and functions that are referenced in lab activities. Requires MATLAB to be installed on the host.

### `/dsp_python`

Contains Python utility scripts and functions as alternatives to the MATLAB utilities. Requires Python to be installed on the host. 

Be sure to run the `setup_env.py` script to create a virtual environment for Python packages. When running the `setup_env.py`, ignore any notifications about virtual environments.

### `/lib`

This contains the ST firmware package (CMSIS, HAL, and BSP) which is the foundation of all examples.
