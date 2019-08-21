import unittest
import math


def calculate_average_floored(numbers):
    total = sum(numbers)
    return math.floor(total / len(numbers))


class CalculateAverageSpec(unittest.TestCase):
    def test_whenEqualNumbers(self):
        numbers = [1, 1, 1, 1]
        average = calculate_average_floored(numbers)
        self.assertEquals(1, average)

    def test_whenShortRange(self):
        numbers = [1, 2, 3, 4, 5]
        average = calculate_average_floored(numbers)
        self.assertEquals(3, average)

    def test_whenShortRangeAndRound(self):
        numbers = [1, 2, 3, 4, 5, 6]
        average = calculate_average_floored(numbers)
        self.assertEquals(3, average)


if __name__ == '__main__':
    unittest.main()

