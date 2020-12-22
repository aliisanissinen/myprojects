# Aliisa Nissinen
# Introduction to Pattern Recognition and Machine Learning
# Week 1, exercise 1


import matplotlib.pyplot as plt
import numpy as np
import sys


# Calculates the a and the b
def my_linfit(x, y):
    avr_x = np.average(x)
    avr_y = np.average(y)
    avr_xx = np.average(x*x)
    avr_xy = np.average(x*y)

    a = (avr_xy-(avr_y*avr_x))/(avr_xx-(avr_x*avr_x))
    b = avr_y-(a*avr_x)
    return a, b


# The program asks the user to give points with a mouse click (left click to
# add a point, right click to stop). After that, it plots the points and
# the fitted linear model.
def main():
    fig = plt.figure()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Press a mouse N times and then stop with the right click. \n '
              'The program will plot the points and the fitted linear model.')
    plt.axis([0, 100, 0, 1000])
    plt.grid(True)
    coords = []

    def onclick(event):
        # If the user clicks the right button of the mouse,
        # collecting the points stops.
        if event.button == 3:
            plt.close()
        else:
            global ix, iy
            ix, iy = event.xdata, event.ydata
            coords.append((ix, iy))

    cid = fig.canvas.mpl_connect('button_press_event', onclick)
    plt.show()

    if len(coords) < 2:
        sys.exit("The program stopped. You should give "
                 "at least 2 points.")

    x_t = np.zeros(len(coords))
    y_t = np.zeros(len(coords))
    for idx, point in enumerate(coords):
        x_t[idx] = point[0]
        y_t[idx] = point[1]

    a, b = my_linfit(x_t, y_t)

    fig = plt.figure()
    plt.xlabel('x')
    plt.ylabel('y')
    plt.axis([0, 100, 0, 1000])
    plt.grid(True)

    plt.plot(x_t, y_t, "ko")

    x = np.arange(0, 1000, 10)
    plt.plot(x, a * x + b)
    print(f"My fit: a={a} and b={b}")
    plt.show()


main()
