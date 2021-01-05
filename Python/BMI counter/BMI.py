# TIE-02100 Johdatus ohjelmointiin
# TIE-02106 Introduction to Programming
# Tampere University
# BMI

from tkinter import *

# If result is not a number
NAN = float("NaN")


class Userinterface:

    def __init__(self):
        self.__mainwindow = Tk()
        self.__mainwindow.title("BMI calculator")

        # Components of mainwindow
        self.__weight_value = Entry(self.__mainwindow)
        self.__height_value = Entry(self.__mainwindow)
        self.__weight_label = Label(self.__mainwindow, text="Add your weight "
                                                            "in kg:")
        self.__height_label = Label(self.__mainwindow, text="Add your height "
                                                            "in cm:")
        self.__result_text = Label(self.__mainwindow, text="")
        self.__explanation_text = Label(self.__mainwindow,
                                        text="")
        self.__calculate_button = Button(self.__mainwindow,
                                         text="Calculate BMI", bg="coral",
                                         command=self.calculate_BMI)
        self.__stop_button = Button(self.__mainwindow, text="Stop",
                                    command=self.stop)

        # Put components on the right places
        self.__weight_label.grid(row=0, column=0)
        self.__height_label.grid(row=0, column=1)
        self.__weight_value.grid(row=1, column=0)
        self.__height_value.grid(row=1, column=1)
        self.__calculate_button.grid(row=2, column=0)
        self.__result_text.grid(row=2, column=1)
        self.__explanation_text.grid(row=3, column=0, columnspan=2, sticky=W)
        self.__stop_button.grid(row=4, column=1, sticky=E)

    def calculate_BMI(self):
        """ Calculates the BMI or give the error message.

        :return: BMI or the error message
        """
        try:
            weight = float(self.__weight_value.get())
            height = (float(self.__height_value.get()) * 0.01)

            if weight < 0 or height < 0:
                self.__explanation_text.configure(
                    text="Error: height and weight must be positive.")
                self.reset_fields()

            else:
                self.__BMI = weight / (height ** 2)
                self.__result_text.configure(text=("{:.2f}".format(self.__BMI)))
                if self.__BMI < 18.50:
                    self.__explanation_text.\
                        configure(text="You are underweight.")
                elif 18.60 < self.__BMI < 25.00:
                    self.__explanation_text.\
                        configure(text="Your weight is normal.")
                else:
                    self.__explanation_text.\
                        configure(text="You are overweight.")

        except ValueError:
            self.__explanation_text.configure(text="Error: height and weight "
                                                   "must be numbers.")
            self.reset_fields()

    def reset_fields(self):
        """ In error situations this method will zeroize the elements
            self.__result_text, self.__height_value, and self.__weight_value.
        """
        self.__height_value.delete(0, END)
        self.__weight_value.delete(0, END)
        self.__result_text.configure(text="")

    def stop(self):
        """ Ends the execution of the program.
        """
        self.__mainwindow.destroy()

    def start(self):
        """ Starts the mainloop.
        """
        self.__mainwindow.mainloop()


def main():
    ui = Userinterface()
    ui.start()


main()
