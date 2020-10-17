import pytest
from filter_function import filter_number
import pandas as pd
import numpy


@pytest.mark.parametrize(
    "test_input,expected",
    [
        ("Hello world 1", 1),
        ("Hello world 2", 2),
        ("Hello world 98", 98),
        ("Hello world 98.1", 98),
    ],
)
def test_filter_number(test_input, expected):
    actual = filter_number(test_input)
    assert expected == actual


def test_created_filtered_dataframe():
    data = {
        "Producer": [
            "Honda Civic",
            "Samsung",
            "Toyota Corolla",
            "AEG",
            "Ford Focus",
            "Audi A4",
        ],
        "Type": ["Car", "Multimedia", "Car", "Kitchen", "Car", "Car"],
        "Price": [22000, 330, 25000, 100, 27000, 35000],
    }
    df = pd.DataFrame(data, columns=["Producer", "Type", "Price"])

    data = {
        "Producer": ["Honda Civic", "Toyota Corolla", "Ford Focus", "Audi A4"],
        "Type": ["Car", "Car", "Car", "Car"],
        "Price": [22000, 25000, 27000, 35000],
    }
    expected = pd.DataFrame(data, columns=["Producer", "Type", "Price"])

    df_cars = df[df["Type"] == "Car"]
    # Index is diierent --> compare contend
    assert numpy.array_equal(expected.values, df_cars.values)


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
