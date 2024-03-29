import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--out_path",
        help="Path to file, which will be created",
        type=str,
        required=True,
    )
    parser.add_argument("inputs", nargs="+")
    args = parser.parse_args()
    with open(args.out_path, "w") as f:
        f.write("Generated by other.py")
        for input in args.inputs:
            f.write(f"{input}\n")


if __name__ == "__main__":
    main()
