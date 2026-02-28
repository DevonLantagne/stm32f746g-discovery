# MATLAB Files

This folder contains MATLAB scripts and functions that you can call directly from VS Code with the MATLAB extension. 

To access the MATLAB interpreter:

- Open the **terminal** panel in VS Code via the menu `View > Terminal` or `` CTRL + ` ``.

- On the far right of the TERMINAL panel, click the downward chevron next to the `+` symbol to see a list of terminals we can open. You should see `MATLAB` as an option. Select `MATLAB`.

- You will see a new terminal open and a new status widget on the bottom of VS Code indicating `MATLAB: Establishing Connection` or `MATLAB: Connected`. Once connected, you should see the command prompt `>>`. You now have full access to the MATLAB interpreter for running commands, functions, and generating figures.

> Live Scripts `.mlx` do not work.

## Startup Script

This repository contains the MATLAB startup script `startup.m` which will execute when the MATLAB terminal opens. This startup script will add the `/matlab_new` directory to the path so all related functions and scripts can be called from the root of the repository.