import argparse


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--out_path", help="Path to file, which will be created", type=str, required=True)
    args = parser.parse_args()

    with open(args.out_path, "w") as writer:
        for i in range(10):
            writer.write(f"{i},{i*10},{i*(-1)}\n")


if __name__ == "__main__":
    main()