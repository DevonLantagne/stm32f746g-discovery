# Python Files

This folder contains Python scripts and functions that you call directly from VS Code with the Python extension or via command line.

## Python Installation

Install Python on your host machine.

Visit [Python.org](https://www.python.org/downloads/) to download Python for your system and install it.

**IMPORTANT:** During the installation process you may be asked to "Add python.exe to your path". Ensure that box is checked!

[Instructions]

## Setup

The Python code in this repo needs external packages to function. Instead of polluting your system Python packages, we can create a virtual environment to stash this repo's required packages. This creates a `./venv` folder in the repo that will hold its own mini environment of Python.

In VS Code, right-click the `setup_env.py` script and select *Run Python File in Terminal*. This script will create the venv and install the required packages specified in `requirements.txt`.

> Please ignore any notifications that pop up in the bottom right corner of VS Code. We will have an opportunity to select the venv manually in the next step.

After the venv is created and packages are installed, we need to tell VS Code to use this environment when you run `.py` files. Open the VSC command palette (CTRL + SHIFT + P) and start typing *Python: Select Interpreter*. Press ENTER. You will see a list of enviornments previously used or detected by VS Code. Select the environment whos path starts with a dot `.`. VSC will likely list this as the *recommended* venv.

From now on, every time you open this repo, VSC will activate this virtual environment and use the packages installed in the `/.venv` directory. 

## Running Python Files

The Python files in `/python_dsp` are a package which allow it to be easily imported in interactive Python or in scripts.

The easiest method to run Python scripts is to right-click a `.py` file and select *Run Python File in Terminal*.

For functions, it would be best to use command line Python (REPL). You can either access the interpreter directly or call python from PowerShell. In either case, first open a new PowerShell terminal in VSC. You will notice VSC step in and automatically activate the `(.venv)` virtual enviornment.

### Interactive Python

The first way to run Python is to use the interactive terminal (Read-Eval-Print Loop: REPL). Open a PowerShell terminal and run `python`. You should see the REPL prompt of `>>>`.

Now you can import functions from the module:

```python
from python_dsp import plot_real
plot_real("output.dat")
```

You can exit REPL mode by executing `exit()`.

#### Example

We can generate header files containing FIR coefficients for the DSP hardware using the `write_fir_header` function. It takes the args:

- `b`: b coefficient array
- `filename`: The name of the header file to create and save in the repo root.

There are optional keyword args:

- `array_name`: The name of the array to instantiate in C (default: `h`).
- `macro_name`: The name of the array length macro (default: `N`).
- `line_width`: How many values to print per line (default: `6`).

In REPL:

```python
# Import function from module
from python_dsp import write_fir_header

# Create an FIR coefficient array
b = [0.1, 0.2, 0.3, 0.4, 0.5]

# Call the function to generate a file named "fir_coeffs.h".
# The array will get the default name 'h' and macro length name is 'N'
write_fir_header(b, "fir_coeffs.h")
```

The optional keyword args are useful if you have more than one filter (different variable names and lengths).