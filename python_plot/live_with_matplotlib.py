import matplotlib.pyplot as plt
import numpy
import math
import time

def main():
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
    plt.ion()

    x = []
    y1 = []
    y2 = []

    start = time.time()

    end = 40.*math.pi
    for pi in numpy.arange(0., end, end/1000.):
        x += [pi]
        y1 += [math.sin(pi)]
        y2 += [math.cos(pi)]
        ax1.clear()
        ax2.clear()
        ax1.plot(x[-25:], y1[-25:])
        ax2.plot(x[-25:], y2[-25:])
        plt.draw()
        plt.pause(0.001)
    end = time.time()
    print(f"Execution time: {end-start}")

    plt.close()

    # plt.pause(10.)


if __name__ == "__main__":
    main()


