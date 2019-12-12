import pytest
from filter_function import filter_number


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


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
