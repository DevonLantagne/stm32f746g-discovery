# Using Visual Studio Code with PlatformIO

This document provides the basics for using VS Code with this repository. For a full description of the VS Code UI, see [their documentation](https://code.visualstudio.com/docs/getstarted/userinterface).

VS Code (VSC) is a glorified text editor. It uses extensions to inherit IDE-like capabilities for different languages.

VSC can be used to open individual text files but it is best used to open entire folders - these are known as workspaces. You can tell if a folder is also a VSC workspace if the folder has a `/.vscode` directory (which is where VSC will store workspace-specific settings).

## User Interface

Let's identify some of the key UI regions of VSC.

![VS Code UI](/docs/assets/VSC_UI.png)

- A) Activity Bar: The icons on the far left side are used to change the information of the Primary Side Bar (B). This is where you will see Explorer, Search, Source Control, [Debug](/docs/debugging.md), and Extension browser. Some extensions may add their own buttons to the Activity Bar.

- B) Primary Side Bar: Used to display information from each of the Activity Bar options.

- C) Editor: This is where tabbed panels will reside. VSC loves tabs. Source code, terminal instances, settings panels, just about anything is shown as a tab in this view. You can click and drag tabs to form split views so you can see files side by side. You can also 'undock' tabs into their own windows.

- D) Panel: Used for some non-tabbed views like task output and terminals. 

- E) Status Bar: The very bottom of the VS Code window is the status bar. The default status bar is nice but extensions can add their own buttons and text (which is what PlatformIO does). When the PIO extension is active, it will show quick action buttons to build and upload code, open a serial monitor, open the PlatformIO command prompt, and switch build environments.

    ![PlatformIO Status Bar](/docs/assets/BuildEnvironmentButton.png)

## Command Palette

The command palette is a very powerful VSC component and is worth mentioning. The command palette shows a list of commands that VS Code can run.

The command palette can be summoned using `CTRL + Shift + P` or by clicking the Search bar at the top of VS Code and typing `>`. Extensions can also add commands to this palette (such as PlatformIO). You can view a list of PIO commands by typing `platformio` after the `>`.

Some common commands are:

- Reload VS Code: `>Developer: Reload Window`. If you ever need to slap VS Code or an extension in the face, run this to restart everything.

- Browse Themes: `>Preferences: Browse Color Themes in Marketplace`. Shows a list of themes that can be installed for VSC. With the dropdown populated, use your Up/Down arrow keys to preview different themes. This theme will be saved to the active profile.