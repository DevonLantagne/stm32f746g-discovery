# Debugging

PlatformIO uses the GNU Debugger (GDB) and can be accessed when running the program in debug mode via the DEBUG CONSOLE terminal.

## Starting the Debugger

![Starting the Debugger](/docs/assets/Debugging.webp)

In VSC's Activity Bar (left side), click the `Run and Debug` icon (bug on play triangle) or use the shortcut `CTRL + SHIFT + D`. At the top of the primary panel you will see a play button next to the words "PIO Debug", clicking that will compile the project in debug mode, upload the code to the board, and start execution until the embedded system reaches your `main()` entrypoint.

Be patient! You may see a small blue line move across the top of the panel near the debug button. This line indicates it is working.

> [!NOTE]
> You will likely see a lot of colored text in the DEBUG CONSOLE. Red and orange text does not necessarily mean the debugger failed.

## Debug Controls

You will notice a small floating panel with common debugger controls to start, pause, single-step, step-into, etc. This is used to control execution. 

![Debugger Step Controls](/docs/assets/DebugStepCommands.png)

The Primary Panel also includes basic debugging information like variables, a watch list of expressions, the call stack, breakpoints, and peripheral and registers (PIO brings in register names and their bitfields). Most of these are only usable when the CPU is halted.

When execution is halted, we can also use our mouse to hover over variables in the editor to get their current values.

> [!NOTE]
> Hovering over commented text will trigger the debugger to look for that symbol (even though it is a comment). You will often see little error messages in the bottom right corner saying it can't find the symbol - that's fine but slighly annoying.

## GNU Debugger Command Line

The GNU Debugger (GDB) exposes a debug console (in the lower Panel) that allows us to execute debug commands and/or probe the device under test. While most of these features are not needed for this application, some features are described below:

### Accessing Memory

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