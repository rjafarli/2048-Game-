#include <iostream>
#include <iomanip>
#include <random>


using namespace std;

// probability of randomly choosing 2 for a cell;
// PROB_2_NUM / PROB_2_DEN

const int
   PROB_2_NUM = 9,
   PROB_2_DEN = 10;
//=========================================================================================
// void displayBoard (int board [4][4], int score)
// clear screen and d

void displayBoard(int board[4][4],int score){

    // clear screen
    cout << "\033[2J\033[H";

    // display score
    cout << "Score: " << score << endl;

    // display board, one row at a time
    for (int row=0;row<4;row++){
        // draw top of box and top row of space
        cout << "+--------+--------+--------+--------+\n"
                "|        |        |        |        |" << endl;

        // draw the row with numbers
        for (int col=0;col<4;col++) {
            cout << "| ";
            if (board[row][col] == 0)
                cout << "       ";
            else
                cout << setw(6) << board[row][col] << ' ';
        }


        // draw end of numbers row and bottom row of space
        cout << "|\n|        |        |        |        |"
        << endl;
    }

    // draw the bottom of game board
    cout << "+--------+--------+--------+--------+" << endl;

}

//================================================================================
// void fillCell(int board[4][4])
// pick random empty cell in board and put 2 or 4 there
//
// Parameter
// board-game board to update

void fillCell (int board [4][4]){
    int
        nEmpty = 0;
    static random_device
      rd;
    static mt19937
      mt (rd());

    // count number of empty cells (nEmpty)
    for (int row=0;row<4;row++)
        for (int col=0;col<4;col++)
            if (board[row][col] == 0)
                nEmpty++;

    // if nEmpty == 0, stop
    if (nEmpty == 0)
        return;

    // pick random number 1 -- nEmpty
    uniform_int_distribution<>
            dis(1,nEmpty);
    int
       pick = dis(mt);

    // scan board, stop when empty cell count == random pick
    int
        count = 0;
    for (int row=0;row<4;row++)
        for (int col = 0; col < 4; col++)
            if (board[row][col] == 0) {
                count++;
                if (count == pick) {
                    // randomly choose 2 or 4, place in that cell
                    uniform_int_distribution<>
                            dis2or4(1,PROB_2_DEN);

                    if (dis2or4(mt) <= PROB_2_NUM)
                        board[row][col] = 2;
                    else
                        board[row][col] = 4;

                    // stop
                    return;

                }
            }


}

bool canSlideLeft(int board[4][4]){

    // for row <- 0 to 3
    for (int row=0;row<4;row++) {

        // for col <- 3 down to 1
        for (int col=3;col>0;col--) {

            // if board [row] [col] == 0, skip
            if (board [row][col] == 0)
                continue;

            // if board [row][col] == board [row] [col-1]
            // we can slide
            if (board[row][col] == board[row][col-1])
                return true;

            // if board [row][col-1] == 0, we can slide
            if (board[row][col-1] == 0)
                return true;

        // end col loop
        }


     // end row loop
    }

 // if we are here, no left slide possible
 return false;
}

bool canSlideRight(int board[4][4]){

    // for row <- 0 to 3
    for (int row=0;row<4;row++) {

        // for col <- 3 down to 1
        for (int col=0;col<3;col++) {

            // if board [row] [col] == 0, skip
            if (board [row][col] == 0)
                continue;

            // if board [row][col] == board [row] [col-1]
            // we can slide
            if (board[row][col] == board[row][col+1])
                return true;

            // if board [row][col-1] == 0, we can slide
            if (board[row][col+1] == 0)
                return true;

            // end col loop
        }


        // end row loop
    }

    // if we are here, no left slide possible
    return false;
}

bool canSlideUp(int board[4][4]){

    // for row <- 0 to 3
    for (int col=0;col<4;col++) {

        // for col <- 3 down to 1
        for (int row=3;row>0;row--) {

            // if board [row] [col] == 0, skip
            if (board [row][col] == 0)
                continue;

            // if board [row][col] == board [row] [col-1]
            // we can slide
            if (board[row][col] == board[row-1][col])
                return true;

            // if board [row][col-1] == 0, we can slide
            if (board[row-1][col] == 0)
                return true;

            // end col loop
        }


        // end row loop
    }

    // if we are here, no left slide possible
    return false;
}

bool canSlideDown(int board[4][4]){

    // for row <- 0 to 3
    for (int col=0;col<4;col++) {

        // for col <- 3 down to 1
        for (int row=0;row<3;row++) {

            // if board [row] [col] == 0, skip
            if (board [row][col] == 0)
                continue;

            // if board [row][col] == board [row] [col-1]
            // we can slide
            if (board[row][col] == board[row+1][col])
                return true;

            // if board [row][col-1] == 0, we can slide
            if (board[row+1][col] == 0)
                return true;

            // end col loop
        }


        // end row loop
    }

    // if we are here, no left slide possible
    return false;
}


void slideLeft (int board [4][4], int & score) {
    int
            hold,
            dest;

    // for row = 0 to 3
    for (int row = 0; row < 4; row++) {

        // hold = -1
        hold = -1;

        // dest = 0
        dest = 0;

        // for col = 0 to 3
        for (int col = 0; col < 4; col++) {

            // if board [row][col] != 0
            if (board[row][col] != 0) {


                // if board [row [col] = hold
                if (board[row][col] == hold) {

                    // double hold
                    hold = 2 * hold;

                    // update score
                    score = score + hold;

                    // place hold in dest position
                    board[row][dest] = hold;

                    // update dest
                    dest++;

                    // clear hold
                    hold = -1;

                    // else if hold != -1
                } else if (hold != -1) {

                    // place hold in dest position
                    board[row][dest] = hold;

                    // update dest
                    dest++;

                    // hold = board [row][col]
                    hold = board[row][col];


                    // else
                } else

                    // hold = board[row] [col]
                    hold = board[row][col];

                // end if not 0
            }

            // end col loop
        }

        // if hold  != -1
        if (hold != -1) {

            // place hold in dest position
            board[row][dest] = hold;

            // update dest
            dest++;
        }

            // while dest < 4
            while (dest < 4) {

                // board [row] [dest] = 0
                board[row][dest] = 0;

                // dest ++ (update dest)
                dest++;
            }

            // end row loop
        }

    }

void slideRight (int board [4][4], int & score) {
    int
            hold,
            dest;

    // for row = 0 to 3
    for (int row = 0; row < 4; row++) {

        // hold = -1
        hold = -1;

        // dest = 0
        dest = 3;

        // for col = 0 to 3
        for (int col = 3; col>=0; col--) {

            // if board [row][col] != 0
            if (board[row][col] != 0) {


                // if board [row [col] = hold
                if (board[row][col] == hold) {

                    // double hold
                    hold = 2 * hold;

                    // update score
                    score = score + hold;

                    // place hold in dest position
                    board[row][dest] = hold;

                    // update dest
                    dest--;

                    // clear hold
                    hold = -1;

                    // else if hold != -1
                } else if (hold != -1) {

                    // place hold in dest position
                    board[row][dest] = hold;

                    // update dest
                    dest--;

                    // hold = board [row][col]
                    hold = board[row][col];


                    // else
                } else

                    // hold = board[row] [col]
                    hold = board[row][col];

                // end if not 0
            }

            // end col loop
        }

        // if hold  != -1
        if (hold != -1) {

            // place hold in dest position
            board[row][dest] = hold;

            // update dest
            dest--;
        }

        // while dest < 4
        while (dest>=0) {

            // board [row] [dest] = 0
            board[row][dest] = 0;

            // dest ++ (update dest)
            dest--;
        }

        // end row loop
    }

}

void slideUp (int board [4][4], int & score) {
    int
            hold,
            dest;

    // for row = 0 to 3
    for (int col = 0; col < 4; col++) {

        // hold = -1
        hold = -1;

        // dest = 0
        dest = 0;

        // for col = 0 to 3
        for (int row = 0; row < 4; row++) {

            // if board [row][col] != 0
            if (board[row][col] != 0) {


                // if board [row [col] = hold
                if (board[row][col] == hold) {

                    // double hold
                    hold = 2 * hold;

                    // update score
                    score = score + hold;

                    // place hold in dest position
                    board[dest][col] = hold;

                    // update dest
                    dest++;

                    // clear hold
                    hold = -1;

                    // else if hold != -1
                } else if (hold != -1) {

                    // place hold in dest position
                    board[dest][col] = hold;

                    // update dest
                    dest++;

                    // hold = board [row][col]
                    hold = board[row][col];


                    // else
                } else

                    // hold = board[row] [col]
                    hold = board[row][col];

                // end if not 0
            }

            // end col loop
        }

        // if hold  != -1
        if (hold != -1) {

            // place hold in dest position
            board[dest][col] = hold;

            // update dest
            dest++;
        }

        // while dest < 4
        while (dest < 4) {

            // board [row] [dest] = 0
            board[dest][col] = 0;

            // dest ++ (update dest)
            dest++;
        }

        // end row loop
    }

}

void slideDown (int board [4][4], int & score) {
    int
            hold,
            dest;

    // for row = 0 to 3
    for (int col = 0; col < 4; col++) {

        // hold = -1
        hold = -1;

        // dest = 0
        dest = 3;

        // for col = 0 to 3
        for (int row = 3; row>=0; row--) {

            // if board [row][col] != 0
            if (board[row][col] != 0) {


                // if board [row [col] = hold
                if (board[row][col] == hold) {

                    // double hold
                    hold = 2 * hold;

                    // update score
                    score = score + hold;

                    // place hold in dest position
                    board[dest][col] = hold;

                    // update dest
                    dest--;

                    // clear hold
                    hold = -1;

                    // else if hold != -1
                } else if (hold != -1) {

                    // place hold in dest position
                    board[dest][col] = hold;

                    // update dest
                    dest--;

                    // hold = board [row][col]
                    hold = board[row][col];


                    // else
                } else

                    // hold = board[row] [col]
                    hold = board[row][col];

                // end if not 0
            }

            // end col loop
        }

        // if hold  != -1
        if (hold != -1) {

            // place hold in dest position
            board[dest][col] = hold;

            // update dest
            dest--;
        }

        // while dest < 4
        while (dest>=0) {

            // board [row] [dest] = 0
            board[dest][col] = 0;

            // dest ++ (update dest)
            dest--;
        }

        // end row loop
    }

}

    int main() {
        int
                board[4][4] = {0},
                score = 0;
        char
                choice;


        // initialize game board
        // a. clear all positions (done)
        // b. choose an empty cell randomly
        // c. randomly put 2 or 4 in that cell
        // d. repeat b and c one time
        fillCell(board);
        fillCell(board);

        bool
                leftOkay,
                rightOkay,
                upOkay,
                downOkay;


        // start do loop
        do {
            // see if the player can slide
            leftOkay = canSlideLeft(board),
            rightOkay = canSlideRight(board),
            upOkay = canSlideUp(board),
            downOkay = canSlideDown(board);

            // if player cannot slide and player cannot undo,
            // game is over
            if (!leftOkay && !rightOkay && ! upOkay && ! downOkay )
                break;

            // display board and score
            displayBoard(board, score);


            // get choice
            cout << "Enter move: ";
            cin >> choice;

            // process choice
            switch (choice) {
                case 'l':
                case 'L':
                    if (leftOkay) {
                        slideLeft(board, score);
			fillCell(board);
		    }
                    break;

                case 'r':
                case 'R':
                    if (rightOkay) {
                        slideRight(board, score);
                        fillCell(board);
                    }
                    break;

                case 'u':
                case 'U':
                    if (upOkay) {
                        slideUp(board, score);
                        fillCell(board);
                    }
                    break;

                case 'd':
                case 'D':
                    if (downOkay) {
                        slideDown(board, score);
                        fillCell(board);
                    }
                    break;


                case 'q':
                case 'Q':
                    break;
                default:
                    cout << "Invalid move" << endl;
            }

            // end do loop
        } while (choice != 'q' && choice != 'Q');

        // display final board and score
        displayBoard(board, score);

        return 0;
    }
