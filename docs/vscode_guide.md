# Using Visual Studio Code with PlatformIO

This document provides the basics for using VS Code with this repository. For a full description of the VS Code UI, see [their documentation](https://code.visualstudio.com/docs/getstarted/userinterface).

VS Code (VSC) is a glorified text editor. It uses extensions to inherit IDE-like capabilities for different languages.

VSC can be used to open individual text files but it is best used to open entire folders - these are known as workspaces. You can tell if a folder is also a VSC workspace if the folder has a `/.vscode` directory (which is where VSC will store workspace-specific settings).

## User Interface

Let's identify some of the key UI regions of VSC.

![VS Code UI](/docs/assets/VSC_UI.png)

- A-E) **Activity Bar**: The activity bar selects between different views of the Primary Side Bar (F). The icons on the far left side are used to change the information of the Primary Side Bar (B). This is where you will see Explorer (A), Search, Source Control, [Debugger](/docs/debugging.md) (B), Extension browser (C), and the PlatformIO GUI (D). Some extensions may add their own buttons to the Activity Bar like PIO did.

    - **Explorer**: Shows the repo's files as well as (at the very bottom) an outline view of the current file and a timeline of the file's version control.
    - **Debugger**: This is where we will go to run the debugger. The Primary bar will show variables, watchlist, call stack, registers, and peripherals.
    - **Extensions**: Shows the extension browser to see currently-installed extensions and search/download new ones.
    - **PlatformIO**: Provides a list of PIO actions.

> [!TIP]
> You can easily hide/show the Primary Side Bar (F) by clicking an Activity Bar icon a second time. You can also toggle side panels using the panel icons in the top right of VSC.

- G) **Status Bar**: The very bottom of the VS Code window is the status bar. The default status bar is nice but extensions can add their own buttons and text (which is what PlatformIO and MATLAB does). When the PIO extension is active, it will show quick action buttons to build and upload code, open a serial monitor, open the PlatformIO command prompt, and switch build environments.

- H) **Editor**: This is where tabbed panels will reside. VSC loves tabs. Source code, settings panels, documentation, just about anything is shown as a tab in this view. You can click and drag tabs to form split views so you can see files side by side. You can also 'undock' tabs into their own windows.

> [!TIP]
> Single-clicking a file will open it in the editor, but clicking another file will close this tab and open a new file. Double-clicking a file will keep the tab in the editor.

- I) **Panel**: Yeah, it is just called "Panel". This is used for some non-tabbed views like task output, the GNU debugger console, and terminals. In in the Terminal Panel you will notice a tabbed list of terminals or tasks on the right (J). The image above shows a MATLAB and Python REPL terminal active.

> [!TIP]
> You can create new terminal instances by clicking the `+` icon in the top right of the Panel. Use the drowpdown arrow to select different shells or interpreters.

- K) **Search and Command Palette**: This tool cannot be understated. This "search bar" can be used to search for things, sure, but it is also used for the Command Palette (see below).

## Command Palette

The command palette is a very powerful VSC component. The command palette shows a list of commands that VS Code can run.

The command palette can be summoned using `CTRL + Shift + P` or by clicking the Search bar at the top of VS Code and typing `>`. Extensions can also add commands to this palette (such as PlatformIO or Git). You can view a list of PIO commands by typing `platformio` after the `>`.

> [!TIP]
> Just typing `>` in the search bar will show a list of ALL commands in VSC. Have fun scrolling or start typing for fuzzy search.

Some common commands are:

- Reload VS Code: `>Developer: Reload Window`. If you ever need to slap VS Code or an extension in the face, run this to restart everything.

- Browse Themes: `>Preferences: Browse Color Themes in Marketplace`. Shows a list of themes that can be installed for VSC. With the dropdown populated, use your Up/Down arrow keys to preview different themes. This theme will be saved to the active profile.

## Common Shortcuts (Windows)

### VS Code

- `` CTRL + ` ``: Opens a terminal.

- `CTRL + SHIFT + P`: Open the command palette.

- `CTRL + P`: Open the regular search. This is a good-sized repo and navigating through the Explorer takes a while.

- `CTRL + TAB`: Cycle through open tabs. 

### Editing

- `CTRL + S`: Save current file.

- `CTRL + /`: Comments/uncomments all selected lines.

- `ALT + Up/Down`: Move the current line up or down.

- `ALT + Left Click`: This drops another cursor in the editor. Allows you to write to multiple lines. Click anywhere (without `ALT`) to return to one cursor.

- `ALT + CTRL + Up/Down`: Drops additional cursors above or below the current line.

### PlatformIO

- `CTRL + ALT + B`: Build the current environment.

- `CTRL + ALT + U`: Upload (flash) binary to target device.
