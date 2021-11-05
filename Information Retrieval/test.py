import math
import copy

score = {'X':1, 'O':-1, 'tie':0}
board = [[' ',' ',' '],[' ',' ',' '],[' ',' ',' ']]

def printBoard(board):
    print('   |   |')
    print(' '+board[0][0]+' | '+board[0][1]+' | '+board[0][2])
    print('   |   |')
    print('-------------')
    print('   |   |')
    print(' '+board[1][0]+' | '+board[1][1]+' | '+board[1][2])
    print('   |   |')
    print('-------------')
    print('   |   |')
    print(' '+board[2][0]+' | '+board[2][1]+' | '+board[2][2])
    print('   |   |')
    print('')

def isWinner(board, player):
    return ((board[2][0] == player and board[2][1] == player and board[2][2] == player) or
            (board[1][0] == player and board[1][1] == player and board[1][2] == player) or
            (board[0][0] == player and board[0][1] == player and board[0][2] == player) or
            (board[0][0] == player and board[1][0] == player and board[2][0] == player) or
            (board[0][1] == player and board[1][1] == player and board[2][1] == player) or
            (board[0][2] == player and board[1][2] == player and board[2][2] == player) or
            (board[0][0] == player and board[1][1] == player and board[2][2] == player) or
            (board[0][2] == player and board[1][1] == player and board[2][0] == player))

def isBoardFull(board):
    for i in range(0,3):
        for j in range(0,3):
            if(board[i][j] == ' '):
                return False
    return True

def minMax(board, depth, isMaximizing, alpha, beta):

    if isWinner(board, 'X'):
        return 1, None, None
    elif isWinner(board, 'O'):
        return -1, None, None
    else:
        if isBoardFull(board):
            return 0, None, None

    if isMaximizing :
        bestScore = -math.inf, None, None
        # for i in range(0, 3):
            # for j in range(0, 3):
        for i in range(9):
            if(board[i//3][i%3] == ' '):
                newboard = copy.deepcopy(board)
                newboard[i//3][i%3] = 'X'
                score = minMax(newboard, depth+1, False, alpha, beta)[0], (i//3), (i%3)
                bestScore = max(score, bestScore, key=lambda x: x[0])
                alpha = max(alpha, bestScore[0])
                if(alpha >= beta):
                    break
        return bestScore
    else:
        bestScore = math.inf, None, None
        # for i in range(0, 3):
        #     for j in range(0, 3):
        for i in range(9):
            if(board[i//3][i%3] == ' '):
                newboard = copy.deepcopy(board)
                newboard[i//3][i%3] = 'O'
                score = minMax(newboard, depth+1, True, alpha, beta)[0], (i//3), (i%3)
                bestScore = min(score, bestScore, key=lambda x: x[0])
                beta = min(beta, bestScore[0])
                if(alpha >= beta):
                    break
        return bestScore


def bestMove():
    bestScore, i, j = minMax(copy.deepcopy(board), 0, True, -math.inf, math.inf)
    # Best Move is (i,j)
    board[i][j] = 'X'

def playerMove():
    move = list(map(int, input().strip().split()))
    board[move[0]][move[1]] = 'O'

def main():
    printBoard(board)

    while(not(isBoardFull(board))):
        if not isWinner(board, player='X'):
            playerMove()
            printBoard(board)
        else:
            print('X Wins!!!')
            break
        
        if( not(isWinner(board, player='O'))):
            bestMove()
            printBoard(board)
        else:
            print('O Wins!!!')
            break

    if(isBoardFull(board)):
        print('Tie Game!!')

main()