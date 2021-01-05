# Johdatus ohjelmointiin
# Introduction to programming
# Tampere University
# Made by Aliisa Nissinen
# Design and implementation of the graphical user interface
# Pictures from google advanced search: only freely available and shareable
# Last edited 6.12.2019

# Drinking game, first enter how many players will participate in the game and
# give each player a name. In the game, the player in turn turns the card
# over and run the task assigned to the card. All instructions will appear as
# the game goes on, no prior information is required. Drinking at own risk.


from tkinter import *
import random
import time

CARDS = ["2.1.gif", "2.2.gif", "2.3.gif", "2.4.gif",
         "3.1.gif", "3.2.gif", "3.3.gif", "3.4.gif",
         "4.1.gif", "4.2.gif", "4.3.gif", "4.4.gif",
         "5.1.gif", "5.2.gif", "5.3.gif", "5.4.gif",
         "6.1.gif", "6.2.gif", "6.3.gif", "6.4.gif",
         "7.1.gif", "7.2.gif", "7.3.gif", "7.4.gif",
         "8.1.gif", "8.2.gif", "8.3.gif", "8.4.gif",
         "9.1.gif", "9.2.gif", "9.3.gif", "9.4.gif",
         "10.1.gif", "10.2.gif", "10.3.gif", "10.4.gif",
         "ace.1.gif", "ace.2.gif", "ace.3.gif", "ace.4.gif",
         "jack.1.gif", "jack.2.gif", "jack.3.gif", "jack.4.gif",
         "king.1.gif", "king.2.gif", "king.3.gif", "king.4.gif",
         "queen.1.gif", "queen.2.gif", "queen.3.gif", "queen.4.gif",
         "ready.gif"]


# The game itself
class DrinkingGame:

    def __init__(self):
        self.__window = Tk()
        self.__window.title("DRINKING GAME")
        self.__window.geometry("760x430")

        self.__turn = 0
        self.__cards = 52

        # Creating a list of card deck pictures, 52 cards and one start picture
        self.__cardpics = []
        for i in range(0, 53):
            pic = PhotoImage(file=(CARDS[i]))
            self.__cardpics.append(pic)

        # List, that helps in next_card method
        self.__remove_last_pic = []

        # Label components, first two don't change as the game goes on
        Label(self.__window, text="PLAYERS: ", font=("Arial", 16)). \
            grid(row=0, column=0, sticky=W)
        Label(self.__window, text=(", ".join(PLAYER_NAMES)),
              font=("Arial", 16)).grid(row=0, column=1, sticky=W)

        self.__cardpicLabel = Label(self.__window, image=self.__cardpics[-1])
        self.__infoLabel = Label(self.__window,
                                 text="This is the drinking game. \nAll "
                                      "instructions will appear as the game "
                                      "goes on. \nPress start to start "
                                      "the game.", font=("Arial", 14))

        self.__cardpicLabel.grid(row=2, column=0, rowspan=4, sticky=W)
        self.__infoLabel.grid(row=4, column=1, columnspan=4, rowspan=5,
                              sticky=W)

        # Button components
        self.__nextcardButton = Button(self.__window, text="Next card",
                                       command=self.next_card, state=DISABLED)
        self.__startButton = Button(self.__window, text="Start",
                                    command=self.start_game)
        self.__stopButton = Button(self.__window, text="Stop",
                                   command=self.__window.destroy)

        self.__nextcardButton.grid(row=3, column=1, ipady=10, sticky=W)
        self.__startButton.grid(row=9, column=0, sticky=E + W)
        self.__stopButton.grid(row=10, column=0, sticky=E + W)

    def start(self):
        """
        Starts the class.
        """
        self.__window.mainloop()

    def start_game(self):
        """
        Starts the game after the startButton has been pressed.
        """
        self.__nextcardButton["state"] = NORMAL
        self.__infoLabel["text"] = "Turn over the next card, the card " \
                                   "instructions will appear."
        self.__startButton["state"] = DISABLED

    def next_card(self):
        """
        Turns the next card after the nextcardButton has been pressed. First
        removes the previous card, from picture list and picture name list,
        with the help of self.__remove_last_pic list. At the first round
        removed card is the start picture "ready.gif" card.
        """
        try:
            del self.__cardpics[self.__remove_last_pic[-1]]
            self.__cards -= 1
            del CARDS[self.__remove_last_pic[-1]]
        except IndexError:
            del self.__cardpics[-1]
            del CARDS[-1]

        # If all 52 cards have been played, the game is over.
        if self.__cards == 0:
            self.game_over()

        else:
            card = random.randint(0, (self.__cards - 1))
            self.__cardpicLabel["image"] = self.__cardpics[card]
            self.__remove_last_pic.append(card)
            self.info(card)

    def info(self, card):
        """
        Prints the task that is assigned to the current card.
        :param card: In the function next_card randomly selected current card.
        """
        card_picture = CARDS[card]

        if card_picture[0] == "2":
            self.__infoLabel["text"] = ("{:s}, next player has to take 2 "
                                        "sips!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "3":
            self.__infoLabel["text"] = ("{:s}, next player has to take 3 "
                                        "sips!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "4":
            self.__infoLabel["text"] = ("{:s}, next player has to take 4 "
                                        "sips!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "5":
            self.__infoLabel["text"] = ("{:s}, take 5 sips!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "6":
            self.__infoLabel["text"] = ("{:s}, take 6 sips!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "7":
            self.__infoLabel["text"] = ("{:s}, choose a category.\n Then "
                                        "everyone by turns says something that"
                                        " fits in the chosen category.\n "
                                        "Whoever screws up has to drink the "
                                        "penalty of 4 sips.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "8":
            self.__infoLabel["text"] = ("{:s}, choose another player to be "
                                        "your mate. \nWhenever you drink,"
                                        " your mate must also drink.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0] == "9":
            self.__infoLabel["text"] = ("{:s}, create a new rule for the game."
                                        "\n If the rule is not followed, the "
                                        "person who broke the rule \nhas to "
                                        "drink the penalty of 4 sips.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0:2] == "10":
            self.__infoLabel["text"] = ("{:s}, this is the bathroom card.\n"
                                        " You can trade or sell it to other "
                                        "players or use it yourself.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0:4] == "jack":
            self.__infoLabel["text"] = ("{:s}, you are the Thumb Master.\n "
                                        "Whenever you choose you can put your "
                                        "thumb on the table\n causing all "
                                        "players to race to do the same. \n"
                                        "Last player to do so has to drink "
                                        "the penalty of 4 sips.\n You are the "
                                        "Thumb Master until a new Jack "
                                        "is chosen.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0:5] == "queen":
            self.__infoLabel["text"] = ("{:s}, say something you have never "
                                        "done. \nIf someone has done it, they"
                                        " have to drink the penalty of "
                                        "4 sips!\n If no one has done it, you"
                                        " have to drink the penalty.".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0:4] == "king":
            self.__infoLabel["text"] = ("{:s}, take a shot!".
                                        format(PLAYER_NAMES[self.__turn]))
        elif card_picture[0:3] == "ace":
            self.__infoLabel["text"] = ("{:s}, waterfall time! Everyone "
                                        "drinks!\n You can stop whenever you "
                                        "want, but others have to keep "
                                        "drinking.\n Once you stop, the "
                                        "player next to you can stop and so "
                                        "on. \nThe last player in the ring has"
                                        " to finish last.".
                                        format(PLAYER_NAMES[self.__turn]))
        self.next_player_turn()

    def next_player_turn(self):
        """
        Switch to the next player.
        """
        if self.__turn == (PLAYER_NUMBER - 1):
            self.__turn = 0
        else:
            self.__turn += 1

    def game_over(self):
        """
        The game stops, the cards ran out (52).
        """
        self.__nextcardButton["state"] = DISABLED
        self.__infoLabel["text"] = \
            "The cards ran out. \nGame over.\n You can start a new game by " \
            "opening the program again."


# Collect players information
class Players:

    def __init__(self):
        self.__window = Tk()
        self.__window.title("ENTER THE PLAYERS")
        self.__window.geometry("580x150")

        # Label components
        self.__infoLabel = Label(self.__window, text="Enter how many players "
                                                     "will participate in the "
                                                     "game:",
                                 font=("Arial", 16))
        self.__infoLabel.grid(row=0)

        # Entry components
        self.__entry = Entry(self.__window)
        self.__entry.grid(row=1)

        # Button components, continueButton only appears at the end
        self.__enterButton = Button(self.__window, text="Enter",
                                    command=self.player_number)
        self.__stopButton = Button(self.__window, text="Stop",
                                   command=self.__window.destroy)
        self.__continueButton = Button(self.__window, text="Continue to play",
                                       command=self.start_drinking_game,
                                       bg="green", state=DISABLED)

        self.__enterButton.grid(row=3)
        self.__stopButton.grid(row=4)

    def start(self):
        """
        Starts the class.
        """
        self.__window.mainloop()

    def player_number(self):
        """
        User enter how many players will participate in the game.
        """
        global PLAYER_NUMBER
        try:
            PLAYER_NUMBER = int(self.__entry.get())
            self.__infoLabel["text"] = "Enter player names in order " \
                                       "(separate with commas and spaces):"
            self.__enterButton["command"] = self.player_names
            self.__entry.delete(0, 'end')
        except ValueError:
            self.__infoLabel["text"] = "Error: The number of players must " \
                                       "be an integer.\nEnter how many " \
                                       "players will participate " \
                                       "in the game:"

    def player_names(self):
        """
        User enter all players' names that will participate in the game.
        """
        global PLAYER_NAMES
        PLAYER_NAMES = []
        names = self.__entry.get()
        names = names.split(", ")
        if len(names) == PLAYER_NUMBER:
            for name in names:
                PLAYER_NAMES.append(name)
                self.__continueButton.grid(row=5)
                self.__continueButton["state"] = NORMAL
        else:
            self.__infoLabel["text"] = ("Error: The number of player "
                                        "names must be the same as the "
                                        "amount of players ({:d}). \nEnter "
                                        "player names in order (separate with "
                                        "commas and spaces):"
                                        .format(PLAYER_NUMBER))


    def start_drinking_game(self):
        """
        Starts the DrinkingGame class and destroys this one
        """
        self.__window.destroy()
        ui = DrinkingGame()
        ui.start()


def start_game():
    """
    Initializing the Players class.
    """
    ui = Players()
    ui.start()


def main():
    start_game()


main()
