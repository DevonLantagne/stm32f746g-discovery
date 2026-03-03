# STM32 Cube F7 v2.9.0 Firmware Package

This directory contains the CMSIS, STM32 HAL drivers, and Board Support Package (BSP).

This library was created by STMicroelectronics and patched so serve the needs of this repository.

Library build configuration is found in `/lib/cube_f7_2_9_0/library.json`. This configuration specifies which components are compiled.

The firmware library references header files via translation (i.e., `#include "../../someheader.h"`) which means the file structure needed to remain the same for the port to PIO. However, PIO needs instructions as to where the `.c` files are located. Therefore, a `library.json` file is used to help PIO find the `.c` files. A listing of the `library.json` file is below:

```json
{
  "name": "cube_f7_2_9_0",
  "version": "2.9.0",
  "frameworks": "*",
  "platforms": "*",
  "build": {
    "flags": [
        "-DUSE_HAL_DRIVER", 
        "-DSTM32F746xx"
    ],
    "srcFilter": [
        "+<Drivers/STM32F7xx_HAL_Driver/Src/*.c>",
        "+<Drivers/BSP/STM32746G-Discovery/*.c>",
        "+<Drivers/BSP/Components/wm8994/*.c>",
        "+<Drivers/BSP/Components/rk043fn48h/*.c>",
        "+<Drivers/BSP/Components/ft5336/*.c>",
        "+<Utilities/Fonts/*.c>"
    ]
  }
}
```

This config provides a name for the library, states the frameworks and platforms the library is allowed to be used with (we set to * for everything), provide library-specific build flags, and state which directories should be compiled with the `srcFilter`.

The `srcFilter` is very important as it is needed to tell PIO which BSP Components to build. There are more components in the `/Drivers/BSP/Components` directory that will need to be included in the `library.json` if you wish to include them in your application. We have omitted most to save on compilation time and space.

## Compiling All Components

The full `library.json` to compile all components is:

```json
{
  "name": "cube_f7_2_9_0",
  "version": "2.9.0",
  "frameworks": "*",
  "platforms": "*",
  "build": {
    "flags": [
        "-DUSE_HAL_DRIVER", 
        "-DSTM32F746xx"
    ],
    "srcFilter": [
        "+<Drivers/STM32F7xx_HAL_Driver/Src/*.c>",
        "+<Drivers/BSP/STM32746G-Discovery/*.c>",
        "+<Drivers/BSP/Components/adv7533/*.c>",
        "+<Drivers/BSP/Components/ampire480272/*.c>",
        "+<Drivers/BSP/Components/exc7200/*.c>",
        "+<Drivers/BSP/Components/ft6x06/*.c>",
        "+<Drivers/BSP/Components/ft5336/*.c>",
        "+<Drivers/BSP/Components/mfxstm32l152/*.c>",
        "+<Drivers/BSP/Components/mx25l512/*.c>",
        "+<Drivers/BSP/Components/n25q128a/*.c>",
        "+<Drivers/BSP/Components/n25q512a/*.c>",
        "+<Drivers/BSP/Components/otm8009a/*.c>",
        "+<Drivers/BSP/Components/ov9655/*.c>",
        "+<Drivers/BSP/Components/rk043fn48h/*.c>",
        "+<Drivers/BSP/Components/s5k5cag/*.c>",
        "+<Drivers/BSP/Components/st7789h2/*.c>",
        "+<Drivers/BSP/Components/stmpe811/*.c>",
        "+<Drivers/BSP/Components/ts3510/*.c>",
        "+<Drivers/BSP/Components/wm8994/*.c>",
        "+<Utilities/Fonts/*.c>"
    ]
  }
}
```