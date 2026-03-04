# Python Utilities

This repo includes utility functions to enhance DSP analysis - they can be found in `/python_dsp`. These utilities are maintained as a module so they can be easily imported into scripts or the interactive Python terminal "REPL".

## Python Installation

Install Python on your host machine.

Visit [Python.org](https://www.python.org/downloads/) to download Python for your system and install it.

**IMPORTANT:** During the installation process you may be asked to "Add python.exe to your path". Ensure that box is checked!

## Python in VS Code

Ensure you have the *DSP Profile* installed and running for this repository. The profile includes the **Python** extension. See [`quick_start_guide.md`](/docs/quick_start_guide.md) for setting up the VSC profile with extensions.

## Set Up Python Virtual Environment (venv)

The Python code in this repo needs external packages to function. Instead of polluting your system Python packages, we can create a virtual environment to stash this repo's required packages. This creates a `./venv` folder in this repo that will hold its own mini environment of Python. While the environment is activated in VS Code, any Python commands will use this environment instead of your system Python.

In VS Code, right-click the `setup_env.py` script and select *"Run Python File in Terminal"*. This script will create the venv and install the required packages specified in `requirements.txt`.

> Please ignore any notifications that pop up in the bottom right corner of VS Code. We will have an opportunity to select the venv manually in the next step.

After the venv is created and packages are installed, we need to tell VS Code to use this environment when you run `.py` files. Open the VSC command palette (CTRL + SHIFT + P) and start typing *Python: Select Interpreter*. Press ENTER. You will see a list of enviornments previously used or detected by VS Code. Select the environment whos path starts with a dot `.`. VSC will likely list this as the *recommended* venv.

From now on, every time you open this repo, VSC will activate this virtual environment and use the packages installed in the `/.venv` directory. 

> You can kill the `/.venv` directory and rebuild it by re-running the `setup_env.py` again.

## Immporting Utility Functions

The Python files in `/python_dsp` are a package which allows its functions to be easily imported in interactive Python (REPL) or in scripts.

To include a function (such as `write_fir_header`), you would use the syntax:

```python
from python_dsp import write_fir_header
```

## Running Python Scripts

The easiest method to run Python scripts is to right-click a `.py` file and select *Run Python File in Terminal*. That's it!

Otherwise you can open a PowerShell terminal and call the python executable directly (which will be taken from your venv). Open a PowerShell terminal. Note the current directory is the root of this repo and all Python files are in `/python_dsp`. Also note that you should see the venv active as indicated by a `(.venv)` in your terminal prompt.

```powershell
python ./python_dsp/your_script.py
```

For functions, it would be best to use command line Python (REPL)...

## Running Functions with Interactive Python (REPL)

A good way to interactively work with Python is through the Read-Evel-Print Loop (REPL).

Open a PowerShell terminal and run `python`. You should see the REPL prompt of `>>>`. You now have direct access to the Python environment.

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