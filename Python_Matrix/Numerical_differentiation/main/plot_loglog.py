from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd

base_dir = Path(__file__).resolve().parent
csv_candidates = [
    base_dir / "integration_results.csv",
    base_dir / "integration_result.csv",
    base_dir / "trapezoidal_results.csv",
]

csv_path = next((p for p in csv_candidates if p.exists()), csv_candidates[0])
df = pd.read_csv(csv_path)

if {"Method", "n", "Error"}.difference(df.columns):
    raise ValueError(f"CSV file '{csv_path.name}' does not contain the expected integration columns.")

methods = df["Method"].dropna().unique()

plt.figure(figsize=(10, 6))

for method in methods:
    subset = df[df["Method"] == method].sort_values("n")
    if subset.empty:
        continue
    plt.loglog(
        subset["n"],
        subset["Error"],
        marker="o",
        linewidth=2,
        label=method,
    )

plt.xlabel("Number of intervals (n)")
plt.ylabel("Absolute error")
plt.title("Integration Error vs Number of Intervals")
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend()
plt.tight_layout()

output_path = base_dir / "integration_error_loglog.png"
plt.savefig(output_path, dpi=200)
plt.show()