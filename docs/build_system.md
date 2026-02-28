# PlatformIO Build System Architecture

The entire build system is defined in `platformio.ini` in the root of the repository.

## Default Behavior

By default, PIO will compile everything in the `/src` directory and always include everything in from the `/include` directory.

PIO will then use its library dependency analyzer and compile libraries in the `/lib` directory. Library build parameters are specified in the `library.json` in each library subdirectory (such as `/cube_f7_2_9_0`). Because PIO tries to automatically pull the CubeF7 firmware package online when we want our own, this automatic library detection is disabled for this project.

## Configured Behavior

Each `[section_name]` section in the configuration defines a separate firmware configuration (a build environment) which can extend from another section.

Below is a snippet from `platformio.ini`'s base section. This base section will be reused (and extended by) other sections. The base section starts with its name `[env_base]` and defines board information, how to compile the CubeF7 firmware package, some preprocessor directives, and how to find header files in the firmware package.

```ini
[env_base]
platform = ststm32
board = disco_f746ng
framework = cmsis
; Configure PIO to compile our STM library without using its automation tricks
lib_ldf_mode = off
lib_compat_mode = off
lib_deps = cube_f7_2_9_0
; Declare build flags and specify location of header files
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

However, this configuration alone cannot build a project - there is no defined entrypoint. We define more sections in `platformio.ini` to specify which file contains the program's entrypoint:

```ini
[env:stm32f7_loop_intr]
extends = env_base
build_src_filter = +<../src/> +<../examples/stm32f7_loop_intr.c>
```

In this snippet, we define a build environment name `[env:stm32f7_loop_intr]` that will inherit all configuration from the `[env_base]` section. Then we extend the config by specifying additional files to build using the `build_src_filter` key. This instructs PIO to build everything in the `/src` folder and also compile and include the `/examples/stm32f7_loop_intr.c` file which contains the entrypoint.

An important note, re-defining a key (like `build_flags`) will override the parent key. However, we can use config interpolation to append flags. For example, suppose we wanted to include a DEBUG_FLAG=2 preprocessor macro but also keep everything that was provided in the base config. We can use interpolation `${section.key}`:

```ini
[env:stm32f7_loop_intr]
extends = env_base
build_src_filter = +<../src/> +<../examples/stm32f7_loop_intr.c>
build_flags = 
    ${env_base.build_flags}
    -DDEBUG_FLAG=2
```

This allows for a lot of interesting build contexts for using different files and macros. If there are any files that need to be 'replaced' for an application (like a different `/src/stm32f7_wm8994_init.c`), they can be removed from compilation with the src filter and then a replacement can be provided.

For more information, visit [PlatformIO's configuration documentation](https://docs.platformio.org/en/latest/projectconf/index.html).