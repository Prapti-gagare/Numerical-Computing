"""
Log-log plot of step size (h) versus absolute error for each integration method.

Usage:
    python plot_h_vs_error.py                      # uses integration_results.csv
    python plot_h_vs_error.py my_results.csv       # use a different file

CSV columns expected: Function, Method, n, h, Approximation, Exact, Error
"""

import sys

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

csv_file = sys.argv[1] if len(sys.argv) > 1 else "integration_results.csv"
df = pd.read_csv(csv_file)

# Use absolute error (a log scale cannot show zero or negative values)
df["AbsError"] = df["Error"].abs()
df = df[(df["h"] > 0) & (df["AbsError"] > 0)]

markers = {"Trapezoidal": "o", "Simpson's 1/3 Rule": "s", "Simpson's 3/8 Rule": "^"}

fig, ax = plt.subplots(figsize=(8, 6))

for method, group in df.groupby("Method"):
    group = group.sort_values("h")
    h = group["h"].to_numpy()
    err = group["AbsError"].to_numpy()

    # Slope of the log-log line = observed order of convergence
    slope, _ = np.polyfit(np.log10(h), np.log10(err), 1)

    ax.loglog(
        h,
        err,
        marker=markers.get(method, "o"),
        linewidth=1.8,
        label=f"{method} (slope ≈ {slope:.2f})",
    )

ax.set_xlabel("Step size  h")
ax.set_ylabel("Absolute error")
ax.set_title("Step size vs. error (log-log)")
ax.grid(True, which="both", linestyle="--", alpha=0.5)
ax.legend()

plt.tight_layout()
plt.savefig("h_vs_error_loglog.png", dpi=200)
plt.show()