# Porting Keil MDK to PlatformIO

This document explains how the original Keil project structure maps to the PlatformIO build system.

## General Config

Keil is a mostly GUI-driven project where the user must manually add files and preprocessor symbols to projects. Keil handles the entire toolchain of ARMCC and uses a Scatter file for linking.

PlatformIO uses text-based configuration in `platformio.ini`. It comes with a library dependecy analyzer which can automatically discover source files and compile them - a nice feature until it isn't. The config file can specify which toolchain to use (GNU ARM Embedded toolchain by default), custom linker scripts, and preprocessor symbols. This config can also use configuration interpolation - allowing users to define base configs and then append 'add-on' config paramaters for specific build contexts.

See [`docs/build_system.md`](/docs/build_system.md) for more information on PlatformIO's build process.

## Firmware Stack Overview

This section describes the firmware stack. This stack is sourced from the STM32CubeF7 v2.9.0 package from STMicroelectronics. For a detailed description of the firmware package, see [`lib/cube_f7_2_9_0/readme.md`](/lib/cube_f7_2_9_0/readme.md).

### CMSIS (Cortex Microcontroller Software Interface Standard)

Hardware abstraction for ARM CPU. Provides Cortex-M core definitions, register defintions, system init, and core peripheral access.

PlatformIO brings its own startup assembly file since PIO uses a GNU compiler and not ARM.

### HAL (Hardware Abstraction Layer)

This is provided by ST (the 2.9.0 code). This HAL talks directly to CMSIS and abstracts MCU peripherals like GPIO, UART, SPI.

### BSP (Board Support Package)

Also ST. This provides extra abstraction on top of HAL for other board components (like the LCD, touch screen, audio codec).

### Middleware

These are extra (add-on) software packages like an RTOS or USB stack. This was not included in the port.

## Toolchain Differences

Keil uses ARM's proprietary toolchain which uses ARMCC. PlatformIO uses GNU tooling which includes the arm-non-eabi-gcc compiler, GNU linker, GNU assembler, and the GNU debugger (GDB).

Linker script language is also different. Keil used a "scatter file" whereas PIO uses a GNU-compatible `.ld` linker script.

PlatformIO automatically downloads and uses a GNU-friendly startup assembly file for this project - this is the only unique file in the port.
