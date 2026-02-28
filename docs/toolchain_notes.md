# Toolchain Notes

This file contains notes about the software stack of the STM32F746G Discovery microcontroller and board.

## External Resources

### The STM32F746G Discovery

https://www.st.com/en/evaluation-tools/32f746gdiscovery.html



# Software Stack

## CMSIS

"Cortex Microcontroller Software Interface Standard"

Hardware abstraction for ARM CPU. Provides startup code, system init, and core peripheral access.

PlatformIO brings these files from their repositories. PlatformIO will use the GNU compiler and assembler (Keil uses the ARM assembler). Hence, statup assembly files must be written in GNU assembly. Thankfully, this startup sequence is the same regardless of HAL or BSP versions.

## HAL

"Hardware Abstraction Layer"

This is provided by ST (the 2.9.0 code). This HAL talks directly to CMSIS and abstracts MCU peripherals like GPIO, UART, SPI.

## BSP

"Board Support Package"

Also ST. This provides extra abstraction on top of HAL for other board components (like the LCD, touch screen, audio codec).

## Middleware

These are extra (add-on) software packages like an RTOS or USB stack.

## Application

User code. Note that because we are using several lower layers, those layers may expose weakly-defined functions (function hooks) that we can re-write in our application (such as interrupt handlers in `stm32f7xx_it.c`).

Two wrapper source files, `stm32f7_display.c` and `stm32f7_wm8994_init.c` are used to initialize peripherals via BSP and HAL calls specific to our application.

# Toolchains

## Keil uVision

The Keil IDE brings a proprietary toolchain such as the ARM Compiler (ARMC) and armclang along with its package manager "CMSIS-Pack". These packs are zip files that contains all the CMSIS, HAL, and BSP files (the 2.9.0 directory).

Keil's project manager will record which static packs and dependencies are part of the project. This will cause a great deal of difficulty for the port. The static pack files are called the "Run-Time Environment" and will be copied for this project (RTE files).

Keil also handles the correct startup file (like `startup_stm32f76xx.s`).

> NOTE that ARM assembly is different from GNU assembly!! Use PlatformIO's `.s` files!

## PlatformIO

PIO is platform-agnostic (GCC: arm-none-eabi-gcc for ST devices).

PIO will use `frameworks` to pull in different dependencies (such as CMSIS startup files).

Keil handles several preprocessor symbols (like the board name). We have to do this manually in PIO's `platformio.ini`. We will also need to include everything manually (BSP, CMSIS, etc.).

```ini
build_flags =
  -DARM_MATH_CM7
  -DUSE_HAL_DRIVER
  -DSTM32F746xx
  -Ilib/cube_f7_2_9_0/Drivers/CMSIS/Include
  -Ilib/cube_f7_2_9_0/Drivers/CMSIS/Device/ST/STM32F7xx/Include
  -Ilib/cube_f7_2_9_0/Drivers/STM32F7xx_HAL_Driver/Inc
  -Ilib/cube_f7_2_9_0/Drivers/BSP/STM32746G-Discovery
  -Ilib/cube_f7_2_9_0/Drivers/BSP/Components
  -Ilib/cube_f7_2_9_0/Utilities/Fonts
```

The Keil Pack files will be best served from the `/lib` dir where PIO will scan and build it. To instruct PIO on what to build, we must define a `library.json` file that specifies which directories are compiled (this mainly applies to the `BSP Components`).

PlatformIO has its own dependency analyzer to detect which library source files need to be compiled and linked. However, for this application, we are better off manually setting which libraries to build:

```ini
lib_ldf_mode = off
lib_compat_mode = off
lib_deps = cube_f7_2_9_0
```

See the `platformio.ini` file for full config.

### Debugging

PlatformIO uses the GNU Debugger (GDB) and can be accessed when running the program in debug mode via the DEBUG CONSOLE terminal.

#### Accessing Memory

We can get information about a variable by typing in the DEBUG CONSOLE:

```
print &rbuffer
```

where `rbuffer` is an array variable name. Suppose the print commant returns the address `0x20000678`. We can then dump the variable's contents to a binary file, `output.dat`:

```
dump binary memory output.dat 0x20000678 0x20000678+4*128
```

Or we can resolve the rbuffer address directly:

```
dump binary memory rbuffer_dump.dat &rbuffer &rbuffer+4*128
```
