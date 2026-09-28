import pandas as pd
import matplotlib.pyplot as plt

# Read CSV file
df = pd.read_csv("trapezoidal_results.csv")

# Plot trapezoidal approximation
plt.figure(figsize=(10, 6))

plt.plot(
    df["n"],
    df["Approximation"],
    marker="o",
    linewidth=2,
    label="Trapezoidal Approximation"
)

# Plot exact value
plt.axhline(
    y=df["Exact"].iloc[0],
    linestyle="--",
    linewidth=2,
    label="Exact Value"
)

plt.xlabel("Number of intervals (n)")
plt.ylabel("Integral Value")
plt.title("Trapezoidal Rule: Approximation vs Exact Value")

plt.grid(True, alpha=0.3)
plt.legend()
plt.tight_layout()

plt.show()