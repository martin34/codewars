from pytest_mock import MockerFixture


def foo():
    return "foo"


def test_foo():
    assert "foo" == foo()


def test_bar_foo():
    def bar():
        return "bar"

    foo = bar
    assert "bar" == foo()


def test_lib_func():
    from pytest_examples.lib import lib_func

    assert "lib_func" == lib_func()


def test_stubbed_lib_func():
    def bar():
        return "bar"

    from pytest_examples.lib import lib_func

    lib_func = bar
    assert "bar" == lib_func()


def test_stubbed_lib_func_foo():
    def bar():
        return "bar"

    from pytest_examples.lib import lib_func_foo
    from pytest_examples.lib import lib_func

    lib_func = bar
    assert "lib_func_foo" == lib_func_foo()


def test_stubbed_lib_func_foo_pytest(mocker: MockerFixture) -> None:
    def bar():
        return "bar"

    mocker.patch("pytest_examples.lib.lib_func", bar)

    from pytest_examples.lib import lib_func_foo

    assert "bar_foo" == lib_func_foo()


import pytest


@pytest.fixture
def lib_func_mocked_fixture(mocker: MockerFixture) -> None:
    def stubed_from_fixture():
        return "stubed_from_fixture"

    mocker.patch("pytest_examples.lib.lib_func", stubed_from_fixture)


def test_stubbed_lib_func_with_fixture(lib_func_mocked_fixture) -> None:
    from pytest_examples.lib import lib_func_foo

    assert "stubed_from_fixture_foo" == lib_func_foo()


if __name__ == "__main__":
    import pytest

    raise SystemExit(pytest.main([__file__]))
