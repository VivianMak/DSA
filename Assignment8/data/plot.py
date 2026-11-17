import json
from pathlib import Path

import matplotlib.pyplot as plt

# Read the benchmark rows from results.json (same folder as this script)
folder = Path(__file__).parent
rows = json.loads((folder / "results.json").read_text())

# One subplot per K
ks = sorted({row["k"] for row in rows})
fig, axes = plt.subplots(1, len(ks), figsize=(6 * len(ks), 4.5), squeeze=False)

for ax, k in zip(axes[0], ks):
    data = [row for row in rows if row["k"] == k]
    sizes = [row["numPoints"] for row in data]

    ax.plot(sizes, [row["queryTime"] for row in data], marker="o", label="KD tree query")
    ax.plot(sizes, [row["bruteForceTime"] for row in data], marker="o", label="Brute force")
    ax.plot(sizes, [row["buildTime"] for row in data], marker="o", linestyle="--", label="KD tree build")

    # Both axes span orders of magnitude, so use log scales
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_title(f"K = {k}")
    ax.set_xlabel("numPoints")
    ax.set_ylabel("time (ms)")
    # ax.grid(True, which="both", alpha=0.3)
    ax.legend()

fig.tight_layout()
fig.savefig(folder / "plot.png", dpi=150)
print(f"Saved {folder / 'plot.png'}")
