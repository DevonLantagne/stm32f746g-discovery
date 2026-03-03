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

The Python files in `/dsp_python` are a package which allow it to be easily imported in interactive Python or in scripts.

The easiest method to run Python scripts is to right-click a `.py` file and select *Run Python File in Terminal*.

For functions, it would be best to use command line Python. You can either access the interpreter directly or call python from PowerShell. In either case, first open a new PowerShell terminal in VSC. You will notice VSC step in and automatically activate the `(.venv)` virtual enviornment.

### Interactive Python

The first way to run Python is to use the interactive terminal (Read-Eval-Print Loop: REPL).

You can then run the `python` command in PowerShell which will then access the Python interpreter (>>>).

Now you can import modules from the package and call their functions:

```python
from dsp_python import write_fir_header
write_fir_header.generate_fir_header(arg1,arg2)
```
