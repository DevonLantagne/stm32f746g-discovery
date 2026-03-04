# Quick Start Guide

This document shows you how to set up VS Code (VSC) to run an example.

> [!IMPORTANT]
> It is assumed that you have cloned or downloaded this repository to your machine.

## VS Code Setup

There is not much to set up in VS Code aside from importing a profile. Profiles are like settings-presets and can be used to quickly configure VS Code for certain jobs (e.g., Python app development, server dev-ops, embedded systems programming).

1. Install [VS Code](https://code.visualstudio.com/download).

2. Open the repository in VS Code.
    
    Open VS Code and click `File > Open Folder...`. Select this repository. Ignore any notifications in the bottom right of the screen that appear after opening the repo.

> [!NOTE]
> When opening this repo in VS Code you might get several notifications in the bottom-right corner - you can ignore these.

3. Import the preconfigured VS Code profile.

    Open your profile settings with `File > Preferences > Profile (maybe something) > Profiles`. A new tab will open in VS Code called *Profiles*.

    In the top left of the *Profiles* tab, click the down-arrow next to *New Profile* and select *Import Profile...*. Import the profile located at `/.vscode/DSP STM Discovery.profile` in this repo.

> [!NOTE]
> This will add a profile to VSC which adjusts settings such as theme, keyboard shortcuts, and extensions. We just need the extensions. This will install extensions such as PlatformIO IDE, MATLAB, Python, and 'nice-to-have' extensions like Markdown. After importing the profile, you can change the color theme, adjust keyboard shortcuts, and extensions if needed.
> 
> For more information on VSC Profiles, visit [their documentation](https://code.visualstudio.com/docs/configure/profiles).

4. Link the repository with the profile. You should see the `DSP STM Discovery` profile in the list of profiles. Hover over the profile and click the checkmark to make this the *active profile* for the current project. You may see several notifications or tabs open after you click this - the extensions are activating.

> [!NOTE]
> This will also add the project to the "Folders & Workspaces" section of the profile. Now whenever you open this project folder in VSC, this profile will automatically activate. This profile can also be used for other embedded projects.

> [!TIP]
> You can see the profile's extensions with the shortcut (`CTRL + SHIFT + X`). You can search to add more extensions or click the gear icon next to an installed extension to uninstall it.

You have now configured VS Code to use the PlatformIO extension!

Get to know VS Code with [this tutorial](/docs/vscode_guide.md).

## Installing the ST-Link Driver

### Windows

Windows does not know how to communicate with the board via USB. We need to install the ST-Link USB driver. You can visit ST's [ST-Link page](https://www.st.com/en/development-tools/stsw-link009.html) to download and install the driver. You may need an ST account to download the driver.

### Linux

[TODO] Should use `udev` and might need rules. Otherwise no driver needed.

## Building and Flashing a Project

This project's `platformio.ini` file has been configured with build environments which tells PIO what file has the main entry point (one of the files in `/examples`). You can change this by clicking the icon in the bottom status bar that has a folder with a circle in the bottom left:

![BuildEnvironmentIcon](/docs/assets/BuildEnvironmentButton.png)

> In the image above, the current environment is "env:stm32f7_loop_intr".

Clicking this icon will open a dropdown menu in VSC where you can select which entry point file to use. You can also type in the search box to narrow the search.

With a build environment selected, you can build the project by clicking the checkmark in in the bottom status bar or `CTRL + ALT + B`. This action runs a task in VSC to build the project.

You can upload (flash) a build by clicking the `->` arrow icon in the bottom status bar or `CTRL + ALT + U`.

## More Information

The VS Code profile you installed includes Markdown tools. You can browse additional documentation in `/docs`. Clicking a `.md` file will open the raw Markdown and open a rendered preview.