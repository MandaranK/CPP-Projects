#include "geesespotter_lib.h"


char * createBoard(std::size_t xdim, std::size_t ydim){
    char * board = new char[xdim * ydim];
    for (int i{0}; i < xdim*ydim; i++) {
        board[i] = 0;
    }

    return board;
}
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int i{0}; i < xdim*ydim; i++){
        board[i] ^= hiddenBit();
    }
}
void cleanBoard(char * board){
    delete[] board;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim){

    for (int y{0}; y < ydim; y++) {
        for (int x{0}; x < xdim; x++) {
            unsigned int idx = (xdim * y + x);
            if ((board[idx] & hiddenBit()) == hiddenBit()) {
                if ((board[idx] & markedBit()) == markedBit()) {
                    std::cout << "M";
                } else {
                    std::cout << "*";
                }
            } else {
                std::cout << int(board[idx] & valueMask());
            }
        }
        std::cout << std::endl;
    }

}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    
    int idx = (xdim * yloc + xloc);

    if (board[idx] = board[idx] | hiddenBit()) {
        board[idx] ^= markedBit();
    } else {
        return 2;
    }

    return 0;
}

int index(std::size_t xdim, int x, int y);
int index(std::size_t xdim, int x, int y) {
    return (xdim * y + x);
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    for (int y{0}; y < ydim; y++) {
        for (int x{0}; x < xdim; x++) {
            int idx = index(xdim,x,y);
            if ( board[idx] == 0x9 ) {
                continue;
            } else if ( xdim == 1 && ydim == 1 ) {  // if 1-by-1 grid
                continue;
            } else if ( xdim ==  1 && ydim == 2 ) {  // if 1-by-2 grid
                if ( y == 0 ) {
                    if ( board[index(xdim,0,1)] == 0x9 )
                        board[idx] += 1;
                } else if ( y == 1 ) {
                    if ( board[index(xdim,0,0)] == 0x9 )
                        board[idx] += 1;
                }
            } else if ( xdim ==  2 && ydim == 1 ) {     // if 2-by-1 grid
                if ( x == 0 ) {
                    if ( board[index(xdim,1,0)] == 0x9 )
                        board[idx] += 1;
                } else if ( x == 1 ) {
                    if ( board[index(xdim,0,0)] == 0x9 )
                        board[idx] += 1;
                }
            } else if ( xdim == 1 ) {   // if grid is one unit wide
                if ( y == 0 ) {
                    if ( board[index(xdim,0,1)] == 0x9 )
                        board[idx] += 1;
                } else if ( y == ydim-1 ) {
                    if ( board[index(xdim,0,ydim-2)] == 0x9 )
                        board[idx] += 1;
                } else {
                    if ( board[index(xdim,0,y-1)] == 0x9 )
                        board[idx] += 1;
                    if ( board[index(xdim,0,y+1)] == 0x9 )
                        board[idx] += 1;
                }
            } else if ( xdim == 1 ) {   // if grid is one unit long
                if ( x == 0 ) {
                    if ( board[index(xdim,1,0)] == 0x9 )
                        board[idx] += 1;
                } else if ( x == xdim-1 ) {
                    if ( board[index(xdim,xdim-2,0)] == 0x9 )
                        board[idx] += 1;
                } else {
                    if ( board[index(xdim,x-1,0)] == 0x9 )
                        board[idx] += 1;
                    if ( board[index(xdim,x+1,0)] == 0x9 )
                        board[idx] += 1;
                }
            } else if ( x == 0 && y == 0 ) {     // top-left corner
                if ( board[index(xdim,0,1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,1,1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,1,0)] == 0x9 )
                    board[idx] += 1;
            } else if ( x == xdim-1 && y == 0 ) {   // top-right corner
                if ( board[index(xdim,xdim-1,1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,xdim-2,1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,xdim-2,0)] == 0x9 )
                    board[idx] += 1;
            } else if ( x == 0 && y == ydim-1 ) {   // bottom-left corner
                if ( board[index(xdim,0,ydim-2)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,1,ydim-2)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,1,ydim-1)] == 0x9 )
                    board[idx] += 1;
            } else if ( x == xdim-1 && y == ydim-1 ) {   // bottom-right corner
                if ( board[index(xdim,xdim-1,ydim-2)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,xdim-2,ydim-2)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,xdim-2,ydim-1)] == 0x9 )
                    board[idx] += 1;
            } else if ( y == 0 ) {   // top-side
                if ( board[index(xdim,x-1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y)] == 0x9 )
                    board[idx] += 1;
            } else if ( y == ydim-1 ) {   // bottom-side
                if ( board[index(xdim,x-1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y)] == 0x9 )
                    board[idx] += 1;
            } else if ( x == 0 ) {   // left-side
                if ( board[index(xdim,x,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x,y+1)] == 0x9 )
                    board[idx] += 1;
            } else if ( x == xdim-1 ) {   // right-side
                if ( board[index(xdim,x,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x,y+1)] == 0x9 )
                    board[idx] += 1;
            } else {    // not corner or side
                if ( board[index(xdim,x,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y-1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x+1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y+1)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y)] == 0x9 )
                    board[idx] += 1;
                if ( board[index(xdim,x-1,y-1)] == 0x9 )
                    board[idx] += 1;
            }
        }
    }
    
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int idx = (xdim * yloc + xloc);
    
    if ( (board[idx] & markedBit()) == 0x10 ) {
        return 1;
    } else if ( (board[idx] & hiddenBit()) != 0x20 ) {
        return 2;
    } else if ( ((board[idx] & hiddenBit()) == 0x20) && ((board[idx] & valueMask()) == 0x9) ) {
        board[idx] ^= hiddenBit();
        return 9;
    } else {
        board[idx] ^= hiddenBit();
        
        if ( (board[idx] & valueMask()) == 0x0 ) {
                std::size_t x = xloc;
                std::size_t y = yloc;
                int i{1};

                x -= 1;
                if(x >= 0) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                

                y -= 1;
                if(y >= 0) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                x += 1;
                if(y >= 0) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                x += 1;
                if(y >= 0 && x <= xdim-1) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                y += 1;
                if(x <= xdim-1) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                y += 1;
                if(y <= ydim-1 && x <= xdim-1) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                x -= 1;
                if(y <= ydim-1) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }

                x -= 1;
                if(y <= ydim-1 && x >= 0) {
                    i = (xdim * y + x);
                    if ( (board[i] & hiddenBit()) == 0x20 ) {
                        board[i] ^= hiddenBit();
                    }
                }
        }
    }
    
    return 0;
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    for(int i{0}; i < xdim*ydim; i++) {
        if (((board[i] & hiddenBit()) == hiddenBit()) && (((board[i] & valueMask()) != 9))) {
            return false;
        } else if (((board[i] & hiddenBit()) != hiddenBit()) && (((board[i] & valueMask()) == 9))) {
            return false;
        }
    }
    
    return true;

}

