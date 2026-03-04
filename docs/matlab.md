# MATLAB Files

The MATLAB extension of VS Code allows VSC to access the MALTAB interpreter via a terminal interface or to run scripts using a right-click context menu. 

The extension also brings in color formatting to edit MATLAB scripts.

> [!WARNING]
> Live Scripts `.mlx` are not supported.

## MATLAB in VS Code

Ensure you have the *DSP Profile* installed and running for this repository. The profile includes the **MATLAB** extension. See [`quick_start_guide.md`](/docs/quick_start_guide.md) for setting up the VSC profile with extensions.

## Accessing MATLAB in VS Code

To access the MATLAB interpreter:

- Open the **terminal** panel in VS Code via the menu `View > Terminal` or `` CTRL + ` ``.

- On the far right of the TERMINAL panel, click the downward chevron next to the `+` symbol to see a list of terminals we can open. You should see `MATLAB` as an option. Select `MATLAB`.

- You will see a new terminal open and a new status widget on the bottom of VS Code indicating `MATLAB: Establishing Connection` or `MATLAB: Connected`. Once connected, you should see the command prompt `>>`. You now have full access to the MATLAB interpreter for running commands, functions, and generating figures.


## Startup Script

This repository contains the MATLAB startup script `startup.m` which will execute when the MATLAB terminal opens. This startup script will add the `/matlab` directory to the path so all related functions and scripts can be called from the root of the repository.
