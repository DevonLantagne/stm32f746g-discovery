# Examples

This directory contains all example files. Each contains the `main()` entrypoint and thus only one can be compiled at a time. The `/examples` directory is not compiled. However, PlatformIO build contexts are defined in `platformio.ini` which can explicitly choose which file in `/examples` is compiled.

## Changing Build Context

With PIO active, toward the bottom of VS Code you will see an icon of a folder wth a filled circle in the bottom left corner. This indicates the current build context. By clicking this, VSC will open a dropdown menu at the top that lists all the build contexts - they are named after their respective source files that will be compiled.

![Build Context Button](/docs/BuildContextButton.png)

In the image above, the current build context is `env:stm32f7_loop_intr` which will include the `stm32f7_loop_intr.c` file during the build. Clicking this icon will open a list of other build contexts.

## Defining Build Context

If you want to create your own build contexts, modify the `platformio.ini` file. The entry of the `env:stm32f7_loop_intr` is shown below:

```ini
[env:stm32f7_loop_intr]
extends = env_base
build_src_filter = +<../src/> +<../examples/stm32f7_loop_intr.c>
```

This will inherit all configuration from the `env_base` section and then apply a `build_src_filter`.