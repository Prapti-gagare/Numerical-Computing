class LagrangeInterpolation:

    def __init__(self, offsets=(-2, -1, 0, 1, 2)):
        self.offsets = offsets
        self.name = f"Lagrange ({len(offsets)}-point)"

    def get_name(self):
        return self.name

    def derivative(self, f, x, h):
        nodes = [x + o * h for o in self.offsets]
        values = [f.evaluate(xi) for xi in nodes]

        n = len(nodes)
        result = 0.0

        for i in range(n):
            result += values[i] * self._basis_derivative(nodes, i, x)

        return result

    def _basis_derivative(self, nodes, i, x):
        # L_i'(x) = sum_{j != i} [ 1/(x_i - x_j) * prod_{k != i, k != j} (x - x_k)/(x_i - x_k) ]
        n = len(nodes)
        xi = nodes[i]
        total = 0.0

        for j in range(n):
            if j == i:
                continue

            term = 1.0 / (xi - nodes[j])

            for k in range(n):
                if k == i or k == j:
                    continue
                term *= (x - nodes[k]) / (xi - nodes[k])

            total += term

        return total