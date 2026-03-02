'''
setup_env.py

This script sets up a Python virtual environment in the repository root
and installs the required dependencies from requirements.txt.

This script is OS agnostic and can be reused for other Python projects.
'''

import subprocess
import sys
import os
from pathlib import Path

# Get repository root
REPO_ROOT = Path(__file__).resolve().parent.parent
VENV_PATH = REPO_ROOT / ".venv"
REQUIREMENTS = Path(__file__).resolve().parent / "requirements.txt"


def main():
    print("Creating virtual environment (/.venv)...")

    subprocess.check_call([sys.executable, "-m", "venv", str(VENV_PATH)])

    # Determine the path to the Python executable in the virtual environment
    # which is different for Windows and Unix-based systems.
    if os.name == "nt":
        python_bin = VENV_PATH / "Scripts" / "python.exe"
    else:
        python_bin = VENV_PATH / "bin" / "python"

    print("Upgrading pip...")
    subprocess.check_call([str(python_bin), "-m", "pip", "install", "--upgrade", "pip"])

    print("Installing requirements...")
    subprocess.check_call([str(python_bin), "-m", "pip", "install", "-r", str(REQUIREMENTS)])

    print("\nSetup complete.")
    print("VS Code should have prompted you to select the new virtual environment.")
    print("If not, you can select it manually: Ctrl+Shift+P -> Python: Select Interpreter -> .venv\n")


if __name__ == "__main__":
    main()