import re


def filter_number(text):
    number_filter = re.compile("Hello world ([0-9]*)")
    match = number_filter.search(text)
    if match:
        return int(match.group(1))
    else:
        return None
