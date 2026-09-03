import pandas as pd
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv("results.csv")

# Get unique functions and methods
functions = df["Function"].unique()
methods = df["Method"].unique()

# One subplot per function, log-log plot of h vs Error, one line per method
fig, axes = plt.subplots(1, len(functions), figsize=(6 * len(functions), 5), squeeze=False)
axes = axes[0]

for ax, func in zip(axes, functions):
    subset = df[df["Function"] == func]
    for method in methods:
        m = subset[subset["Method"] == method].sort_values("h")
        if not m.empty:
            ax.loglog(m["h"], m["Error"], marker="o", label=method)
    ax.set_title(f"{func}")
    ax.set_xlabel("h (log scale)")
    ax.set_ylabel("Error (log scale)")
    ax.grid(True, which="both", ls="--", alpha=0.5)
    ax.legend()

plt.tight_layout()
plt.savefig("loglog_error_vs_h.png", dpi=200)
plt.show()