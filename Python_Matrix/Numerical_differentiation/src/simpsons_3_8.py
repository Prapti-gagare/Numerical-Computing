from src.base import IntegrationMethod


class Simpson38Rule(IntegrationMethod):
    def __init__(self):
        super().__init__("Simpson's 3/8 Rule")

    def step_size(self, a, b, n):
        return (b - a) / n

    def integrate(self, f, a, b, n):
        if n < 3 or n % 3 != 0:
            raise ValueError("Number of subintervals n must be a multiple of 3 and >= 3")

        h = self.step_size(a, b, n)
        total = f.evaluate(a) + f.evaluate(b)

        for i in range(1, n):
            x = a + i * h
            value = f.evaluate(x)
            if i % 3 == 0:
                total += 2 * value
            else:
                total += 3 * value

        return (3 * h / 8) * total
