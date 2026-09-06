from src.base import Interpolation


class NewtonInterpolation(Interpolation):
    def __init__(self, offsets=(-2, -1, 0, 1, 2)):
        super().__init__(f"Newton ({len(offsets)}-point)", offsets)

    def derivative(self, f, x, h):
        nodes, values = self.build_nodes(f, x, h)

        coeffs = self._divided_differences(nodes, values)

        n = len(nodes)
        result = 0.0

        # p(t) = c0 + sum_{k=1}^{n-1} c_k * prod_{i=0}^{k-1} (t - x_i)
        # p'(t) = sum_{k=1}^{n-1} c_k * d/dt[ prod_{i=0}^{k-1} (t - x_i) ]
        for k in range(1, n):
            result += coeffs[k] * self._product_derivative(nodes[:k], x)

        return result

    def _divided_differences(self, nodes, values):
        n = len(nodes)
        coef = list(values)

        for j in range(1, n):
            for i in range(n - 1, j - 1, -1):
                coef[i] = (coef[i] - coef[i - 1]) / (nodes[i] - nodes[i - j])

        return coef  # coef[k] = f[x0, x1, ..., xk]

    def _product_derivative(self, pts, x):
        # d/dx of prod_i (x - pts[i]), via the product rule:
        # sum_i [ prod_{j != i} (x - pts[j]) ]
        total = 0.0

        for i in range(len(pts)):
            term = 1.0
            for j, xj in enumerate(pts):
                if j == i:
                    continue
                term *= (x - xj)
            total += term

        return total
