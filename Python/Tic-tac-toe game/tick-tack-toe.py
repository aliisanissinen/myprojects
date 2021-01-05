# TIE-02100 Johdatus ohjelmointiin
# TIE-02106 Introduction to Programming
# Tampere University
# Tick-tack-toe


# Checks the diagonal axes
def winning2(game_board, x, y, mark):
    stop_program2 = 0
    if game_board[0][0] == mark and game_board[1][1] == mark \
            and game_board[2][2] == mark:
        stop_program2 += 1
    if game_board[2][0] == mark and game_board[1][1] == mark and \
            game_board[0][2] == mark:
        stop_program2 += 1
    return stop_program2


# Checks the horizontal and vertical axes
def winning(game_board, x, y, mark):
    stop_program = 0
    i = 0
    if game_board[y] == [mark, mark, mark]:
        stop_program += 1
    if game_board[0][x] == mark and \
            game_board[1][x] == mark \
            and game_board[2][x] == mark:
        stop_program += 1
    return stop_program


def print_board(game_board):
    print(game_board[0][0],game_board[0][1],game_board[0][2], sep="")
    print(game_board[1][0],game_board[1][1],game_board[1][2], sep="")
    print(game_board[2][0],game_board[2][1],game_board[2][2], sep="")


def board():
    game_board = [[".",".","."],[".",".","."],[".",".","."]]
    return game_board


def main():
    game_board = board()
    print_board(game_board)
    turns = 0
    stop_program = 0
    stop_program2 = 0
    while turns < 9:
        if turns % 2 == 0:
            mark = "X"
        else:
            mark = "O"
        coordinates = input("Player " + mark + ", give coordinates: ")
        try:
            x, y = coordinates.split(" ")
            x = int(x)
            y = int(y)
        except ValueError:
            print("Error: enter two integers, separated with spaces.")
            continue
        if not (0 <= x < 3):
            print("Error: coordinates must be between 0 and 2.")
            continue
        if not (0 <= y < 3):
            print("Error: coordinates must be between 0 and 2.")
            continue
        else:
            if game_board[y][x] == "O":
                print("Error: a mark has already been placed on this square.")
            elif game_board[y][x] == "X":
                print("Error: a mark has already been placed on this square.")
            else:
                game_board[y][x] = mark
                turns += 1
                print_board(game_board)
        if turns > 4:
            stop_program = winning(game_board, x, y, mark)
            stop_program2 = winning2(game_board, x, y, mark)
            if stop_program == 1:
                print("The game ended, the winner is {:s}".format(mark))
                break
            if stop_program2 == 1:
                print("The game ended, the winner is {:s}".format(mark))
                break
            if turns == 9:
                print("Draw!")


main()
