# Quick Start Guide

This document shows you how to set up VS Code (VSC) to run an example.

## VS Code Setup

There is not much to set up in VS Code aside from importing a profile:

1. Install [VS Code](https://code.visualstudio.com/download).

2. Open the repository in VS Code.
    
    Open VS Code and click `File > Open Folder...`. Select this repository. Ignore any notifications in the bottom right of the screen that appear after opening the repo.

3. Import a preconfigured VS Code profile.

    Open your profile settings with `File > Preferences > Profile (maybe something) > Profiles`. A new tab will open in VS Code called *Profiles*.

    In the top left of the *Profiles* tab, click the down-arrow next to *New Profile* and select *Import Profile...*. Import the profile located at `.vscode/DSP_STM_Discovery.profile`.

    > This will add a profile to VSC which adjusts settings such as theme, keyboard shortcuts, and extensions. We just need the extensions. This will install extensions such as PlatformIO, MATLAB, and 'nice to have' extensions like Markdown.

    For more information on VSC Profiles, visit [their documentation](https://code.visualstudio.com/docs/configure/profiles).

4. Link the repository with the profile. You should see the `DSP STM Discovery` profile in the list of profile. Hover over the profile and click the checkmark to make this the active profile for the current project. You may see several notifications or tabs open after you click this - the extensions are activating.

    > This will also add the project to the "Folders & Workspaces" section of the profile. Now whenever you open this project folder in VSC, this profile will automatically activate.

You have now configured VS Code to use the PlatformIO extension!

## Installing the ST-Link Driver

### Windows

Windows does not know how to communicate with the board via USB. We need to install the ST-Link USB driver. You can visit ST's [ST-Link page](https://www.st.com/en/development-tools/stsw-link009.html) to download and install the driver. You may need an ST account to download the driver.

## Building and Flashing a Project

This project's `platformio.ini` file has configured build environments which tells PIO what file has the main entry point (one of the files in `/examples`). You can change this by clicking the icon in the bottom status bar that has a folder with a circle in the bottom left:

![BuildEnvironmentIcon](/docs/assets/BuildEnvironmentButton.png)

> In the image above, the current environment is "env:stm32f7_loop_intr".

Clicking this icon will open a dropdown menu in VSC where you can select which entry point file to use.

With a build environment selected, you can build the project by clicking the checkmark in in the bottom status bar or `CTRL + ALT + B`. This action runs a task in VSC to build the project.

You can upload (flash) a build by clicking the `->` arrow icon in the bottom status bar or `CTRL + ALT + U`.