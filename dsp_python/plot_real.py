import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path


def plot_real(filename: str):
    """
    Plot float32 samples from a raw binary memory dump.

    Parameters
    ----------
    filename : str
        Path to the binary file containing float32 samples.

    Notes
    -----
    Intended for visualizing raw buffers dumped from embedded memory
    (e.g., via GDB: dump binary memory output.bin <start_addr> <end_addr>)
    """

    filepath = Path(filename)

    if not filepath.exists():
        raise FileNotFoundError(f"Unable to open file: {filename}")

    # Read float32 and promote to float64 (MATLAB-like behavior)
    data = np.fromfile(filepath, dtype=np.float32).astype(np.float64)

    if data.size == 0:
        raise ValueError(f"No data read from file: {filename}")

    plt.figure()
    plt.plot(data)
    plt.title(f"Samples from {filename}")
    plt.xlabel("Sample")
    plt.ylabel("Value")
    plt.grid(True)
    plt.show()