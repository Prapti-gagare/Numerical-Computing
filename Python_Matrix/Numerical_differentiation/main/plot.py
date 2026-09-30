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

if "Method" not in df.columns or "Approximation" not in df.columns:
    raise ValueError(f"CSV file '{csv_path.name}' does not contain the expected integration columns.")

methods = df["Method"].dropna().unique()
exact_value = df["Exact"].iloc[0]

plt.figure(figsize=(10, 6))

for method in methods:
    subset = df[df["Method"] == method].sort_values("n")
    if subset.empty:
        continue
    plt.plot(
        subset["n"],
        subset["Approximation"],
        marker="o",
        linewidth=2,
        label=method,
    )

plt.axhline(
    y=exact_value,
    linestyle="--",
    linewidth=2,
    color="black",
    label="Exact Value",
)

plt.xlabel("Number of intervals (n)")
plt.ylabel("Integral value")
plt.title("Numerical Integration Approximation vs Exact Value")
plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

output_path = base_dir / "integration_plot.png"
plt.savefig(output_path, dpi=200)
plt.show()