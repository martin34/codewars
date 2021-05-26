def get_int() -> int:
    return 1


def get_string() -> str:
    return "1.0"


# Error will be detected via type checking
def get_string_failing() -> str:
    return 1


def test_pass():
    assert 1 == get_int()


def test_not_equal():
    assert 1 != get_string()
    # val = 1 + get_string() Error not detected via type checking


if __name__ == "__main__":
    import pytest  # type: ignore

    raise SystemExit(pytest.main([__file__]))
