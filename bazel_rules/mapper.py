import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out_path", help="Path to file, which will be created", type=str, required=True)
    parser.add_argument("--input_path", help="Path to input file", type=str, required=True)
    args = parser.parse_args()

    lines = []
    with open(args.input_path) as reader:
        lines = reader.readlines()


    with open(args.out_path, "w") as writer:
        for line in lines:
            writer.write("mapped: " + line)


if __name__ == "__main__":
    main()