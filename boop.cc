/**
 * @file boop.cc
 * @author elizabeth hooton
 * @brief 
 * @version 0.1
 * @date 2023-04-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "game.h"
#include "boop.h"
#include "spaces.h"
#include "colors.h"

#include <iostream>
#include <string>

namespace main_savitch_14{

    void Boop::restart( ){
        p1Kittens = 8; // all players start with 8 kittens
        p2Kittens = 8;

        p1Cats = 5; // players start with 0 cats
        p2Cats = 5;

        columnPerson = NEUTRAL;
        rowPerson = NEUTRAL;
        diagonalPerson = NEUTRAL;
        diagonalPerson2 = NEUTRAL;
        diagonalPerson3 = NEUTRAL;
        diagonalPerson4 = NEUTRAL;

        game::restart(); // no moves have been made
    }

    void Boop::display_status() const{
        char letter = 'a';
        std::cout << WHITE << "    1       2       3       4       5       6    " << std::endl; // prints the labels for the columns
        for(int i = 0; i < 6; i++){ // prints the row bars
            std::cout << WHITE << "-------------------------------------------------" << std::endl;
            for(int l = 0; l < 6; l++){ // prints the column bars for row 1 of the space
                std::cout << WHITE << "|";
                if(board[i][l].getTaken() == 1 || board[i][l].getTaken() == 2){ // if it is player one's turn, output in blue
                    std::cout << BLUE << board[i][l].getRow1();
                }
                else{ // if it is player two's turn, output in red
                    std::cout << RED << board[i][l].getRow1();
                }
                if(l == 5){ // if it is the last column, add a closing |
                    std::cout << WHITE << "|";
                }
            }
            std::cout << std::endl;
            for(int l = 0; l < 6; l++){ // prints the column bars for row 2 of the space
                std::cout << WHITE << "|";
                if(board[i][l].getTaken() == 1 || board[i][l].getTaken() == 2){ // if it is player one's turn, output in blue
                    std::cout << BLUE << board[i][l].getRow2();
                }
                else{ // if it is player two's turn, output in red
                    std::cout << RED << board[i][l].getRow2();
                }
                if(l == 5){ // if it is the last column, add a closing |
                        std::cout << WHITE << "|  " << letter++;
                }
            }
            std::cout << std::endl;
            for(int l = 0; l < 6; l++){ // prints the column bars for row 3 of the space
                std::cout << WHITE << "|";
                if(board[i][l].getTaken() == 1 || board[i][l].getTaken() == 2){ // if it is player one's turn, output in blue
                    std::cout << BLUE << board[i][l].getRow3();
                }
                else{ // if it is player two's turn, output in red
                    std::cout << RED << board[i][l].getRow3();
                }
                if(l == 5){ // if it is the last column, add a closing |
                    std::cout << WHITE << "|";
                }
            }
            std::cout << std::endl;
        }
        std::cout << WHITE << "-------------------------------------------------" << std::endl;
    }

    bool Boop::is_legal(const std::string& move) const { // k1a
        char type; // cat or kitten
        int column; // which column
        char row; // which row
        int rowNum; // row as a number
        int columnNum; // row as a column

        cout << move << endl;

        if(move.length() != 3){ // if the length of the move is not 3, it is illegal
            return false;
        }
        if(move[0] == 'K' || move[0] == 'k' || move[0] == 'C' || move[0] == 'c'){ // if the type is cat or kitten, set the type equal to it
            type = move[0];
        }
        else{
            return false; // if it is not a cat or kitten, it is illegal
        }
        if(move[1] == '1' || move[1] == '2' || move[1] == '3' || move[1] == '4' || move[1] == '5' || move[1] == '6'){ // if the column is 1 - 6, set the column
            column = move[1];
        }
        else{ // if it is not 1 - 6, it is illegal
            return false;
        }
        if(move[2] == 'a' || move[2] == 'b' || move[2] == 'c' || move[2] == 'd' || move[2] == 'e' || move[2] == 'f'){ // if the row is a - f, set the row
            row = move[2];
        }
        else{ // if the row is not a - f, it is illegal
            return false;
        }

        columnNum = int(column - '1');
        rowNum = int(toupper(row) - 'A');
        
        if(next_mover() == HUMAN){ // if it is player 1's turn
            if(type == 'K' || type == 'k'){ // if they try to play a kitten when they have none, the move is illegal
                if(p1Kittens == 0){
                    return false;
                }
            }
            if(type == 'C' || type == 'c'){ // if they try to play a cat when they have none, the move is illegal
                if(p1Cats == 0){
                    return false;
                }
            }
        }
        else{ // if it is player 2's turn
            if(type == 'K' || type == 'k'){
                if(p2Kittens == 0){ // if they try to play a kitten when they have none, the move is illegal
                    return false;
                }
            }
            if(type == 'C' || type == 'c'){ // if they try to play a cat when they have none, the move is illegal
                if(p2Cats == 0){
                    return false;
                }
            }
        }
        
        int i = board[rowNum][columnNum].getTaken(); // setting i = to state of the space (if it is taken or not)
        if(i == 0){ // if the space is not taken, the move is legal
            return true;
        }
        else{ // if the space is taken, the move is illegal
            return false;
        }
    }

    void Boop::make_move(const std::string& move){
        char type = move[0]; // set the type = to the type from move
        char column = move[1]; // set the column = to the column from move
        char row = move[2]; // set the row = to the row from move

        int columnNum; // the int for the 2d array
        int rowNum; // the int for the 2d array

        columnNum = int(column - '1');
        rowNum = int(toupper(row) - 'A');

        if(next_mover() == HUMAN){
            if(type == 'C' || type == 'c'){ // if it is a cat, set the space to have a cat
                board[rowNum][columnNum].setSpace(" /\\_/\\ ", "( o.o )", " > ^ < ");
                board[rowNum][columnNum].setTaken(2);
                p1Cats--;
            }
            else{ // if it is a kitten, set the space to have a kitten
                board[rowNum][columnNum].setSpace("       ", " =^..^=", "       ");
                board[rowNum][columnNum].setTaken(1);
                p1Kittens--;
            }
        }

        if(next_mover() == COMPUTER){
            if(type == 'C' || type == 'c'){ // if it is a cat, set the space to have a cat
                board[rowNum][columnNum].setSpace(" /\\_/\\ ", "( o.o )", " > ^ < ");
                board[rowNum][columnNum].setTaken(4);
                p2Cats--;
            }
            else{ // if it is a kitten, set the space to have a kitten
                board[rowNum][columnNum].setSpace("       ", " =^..^=", "       ");
                board[rowNum][columnNum].setTaken(3);
                p2Kittens--;
            }
        }

        //boopThePieces(rowNum, columnNum);

        if(is_game_over() == true){
            cout << "game over" << endl;
            return;
        }

        boopThePieces(rowNum, columnNum);

        check();

        game::make_move(move);


        

    }

    int Boop::evaluate( ) const{
        
    }

    void Boop::check(){
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        int count4 = 0;
        int count5 = 0;
        int count6 = 0;
        int previous = 0;
        string input;
        bool valid = false;
        bool isColumn = false;
        bool isRow = false;
        bool isDiagonal = false;
        bool isDiagonal2 = false;
        bool isDiagonal3 = false;
        bool isDiagonal4 = false;
        
        for(int column = 0; column < 6; column++){ // CHECKS COLUMNS
            previous = board[0][column].getTaken();
            if(previous != 0){
                count = 1;
            }
            else{
                count = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){
                    case 0:
                        previous = board[s][column].getTaken();
                        if(board[s][column].getTaken() != 0){
                            count = 1;
                        }
                        else{
                            count = 0;
                        }
                        break;
                    case 1:
                        previous = board[s][column].getTaken();
                        switch(previous){
                            case 0:
                                count = 0;
                                break;

                            case 1:
                                count++;
                                break;

                            case 2:
                                count++;
                                break;

                            case 3:
                                count = 1;
                                break;

                            case 4:
                                count = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[s][column].getTaken();
                        switch(previous){
                            case 0:
                                count = 0;
                                break;

                            case 1:
                                count++;
                                break;

                            case 2:
                                count++;
                                break;

                            case 3:
                                count = 1;
                                break;

                            case 4:
                                count = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[s][column].getTaken();
                        switch(previous){
                            case 0:
                                count = 0;
                                break;

                            case 1:
                                count = 1;
                                break;

                            case 2:
                                count = 1;
                                break;

                            case 3:
                                count++;
                                break;

                            case 4:
                                count++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[s][column].getTaken();
                        switch(previous){
                            case 0:
                                count = 0;
                                break;

                            case 1:
                                count = 1;
                                break;

                            case 2:
                                count = 1;
                                break;

                            case 3:
                                count++;
                                break;

                            case 4:
                                count++;
                                break;

                        }
                        break;
                }
                
                if(count == 3){
                    isColumn = true;
                    if(previous == 1 || previous == 2){
                        columnPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        columnPerson = COMPUTER;
                    }
                }
                
            } // end of inner for loop
        } // end of outer for loop
        
        for(int row = 0; row < 6; row++){ // CHECKS ROWS
            previous = board[row][0].getTaken();
            if(previous != 0){
                count2 = 1;
            }
            else{
                count2 = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){
                    case 0:
                        previous = board[row][s].getTaken();
                        if(board[row][s].getTaken() != 0){
                            count2 = 1;
                        }
                        else{
                            count2 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row][s].getTaken();
                        switch(previous){
                            case 0:
                                count2 = 0;
                                break;

                            case 1:
                                count2++;
                                break;

                            case 2:
                                count2++;
                                break;

                            case 3:
                                count2 = 1;
                                break;

                            case 4:
                                count2 = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[row][s].getTaken();
                        switch(previous){
                            case 0:
                                count2 = 0;
                                break;

                            case 1:
                                count2++;
                                break;

                            case 2:
                                count2++;
                                break;

                            case 3:
                                count2 = 1;
                                break;

                            case 4:
                                count2 = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[row][s].getTaken();
                        switch(previous){
                            case 0:
                                count2 = 0;
                                break;

                            case 1:
                                count2 = 1;
                                break;

                            case 2:
                                count2 = 1;
                                break;

                            case 3:
                                count2++;
                                break;

                            case 4:
                                count2++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row][s].getTaken();
                        switch(previous){
                            case 0:
                                count2 = 0;
                                break;

                            case 1:
                                count2 = 1;
                                break;

                            case 2:
                                count2 = 1;
                                break;

                            case 3:
                                count2++;
                                break;

                            case 4:
                                count2++;
                                break;

                        }
                        break;

                } 
                if(count2 == 3){
                    isRow = true;
                    if(previous == 1 || previous == 2){
                        rowPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        rowPerson = COMPUTER;
                    }
                }
                

            }// end of for loop
        }

        // CHECKS DIAGONALS

        // checking diagonals (*\)
        int t = 5;
        int row;
        int col;
        for(int i = 0; i < 6; i++){
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous != 0){
                count3 = 1;
            }
            else{
                count3 = 0;
            }
            for(int j = 0; j < t; j++){
                
                switch(previous){
                    case 0:
                        previous = board[row + 1][col + 1].getTaken();
                        if(board[row + 1][col + 1].getTaken() != 0){
                            count3 = 1;
                        }
                        else{
                            count3 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count3 = 0;
                                break;

                            case 1:
                                count3++;
                                break;

                            case 2:
                                count3++;
                                break;

                            case 3:
                                count3 = 1;
                                break;

                            case 4:
                                count3 = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count3 = 0;
                                break;

                            case 1:
                                count3++;
                                break;

                            case 2:
                                count3++;
                                break;

                            case 3:
                                count3 = 1;
                                break;

                            case 4:
                                count3 = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count3 = 0;
                                break;

                            case 1:
                                count3 = 1;
                                break;

                            case 2:
                                count3 = 1;
                                break;

                            case 3:
                                count3++;
                                break;

                            case 4:
                                count3++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count3 = 0;
                                break;

                            case 1:
                                count3 = 1;
                                break;

                            case 2:
                                count3 = 1;
                                break;

                            case 3:
                                count3++;
                                break;

                            case 4:
                                count3++;
                                break;

                        }
                        break;

                } 

                if(count3 == 3){
                    isDiagonal = true;
                    if(previous == 1 || previous == 2){
                        diagonalPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        diagonalPerson = COMPUTER;
                    }
                }
                row++;
                col++;
            }
            t--;
            previous = 0;
        }

        // checking diagonals (\*)
        t = 4;
        for(int i = 1; i < 6; i++){
            row = 0;
            col = i;
            previous = board[row][col].getTaken();
            if(previous != 0){
                count4 = 1;
            }
            else{
                count4 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){
                    case 0:
                        previous = board[row + 1][col + 1].getTaken();
                        if(board[row + 1][col + 1].getTaken() != 0){
                            count4 = 1;
                        }
                        else{
                            count4 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 1:
                                count4++;
                                break;

                            case 2:
                                count4++;
                                break;

                            case 3:
                                count4 = 1;
                                break;

                            case 4:
                                count4 = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 1:
                                count4++;
                                break;

                            case 2:
                                count4++;
                                break;

                            case 3:
                                count4 = 1;
                                break;

                            case 4:
                                count4 = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 1:
                                count4 = 1;
                                break;

                            case 2:
                                count4 = 1;
                                break;

                            case 3:
                                count4++;
                                break;

                            case 4:
                                count4++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 1:
                                count4 = 1;
                                break;

                            case 2:
                                count4 = 1;
                                break;

                            case 3:
                                count4++;
                                break;

                            case 4:
                                count4++;
                                break;

                        }
                        break;

                } 

                if(count4 == 3){
                    isDiagonal2 = true;
                    if(previous == 1 || previous == 2){
                        diagonalPerson2 = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        diagonalPerson2 = COMPUTER;
                    }
                }
                row++;
                col++;
            }
            t--;
            previous = 0;
        }


        // CHECKING THE OTHER WAY DIAGONALLY (please kill me lol ik there's a better way to do this)
        
        // checking diagonals (*/)
        t = 5;
        for(int i = 5; i >= 0; i--){
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous != 0){
                count5 = 1;
            }
            else{
                count5 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){
                    case 0:
                        previous = board[row - 1][col + 1].getTaken();
                        if(board[row - 1][col + 1].getTaken() != 0){
                            count5 = 1;
                        }
                        else{
                            count5 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row - 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count5 = 0;
                                break;

                            case 1:
                                count5++;
                                break;

                            case 2:
                                count5++;
                                break;

                            case 3:
                                count5 = 1;
                                break;

                            case 4:
                                count5 = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[row - 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count5 = 0;
                                break;

                            case 1:
                                count5++;
                                break;

                            case 2:
                                count5++;
                                break;

                            case 3:
                                count5 = 1;
                                break;

                            case 4:
                                count5 = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[row - 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count5 = 0;
                                break;

                            case 1:
                                count5 = 1;
                                break;

                            case 2:
                                count5 = 1;
                                break;

                            case 3:
                                count5++;
                                break;

                            case 4:
                                count5++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row - 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count5 = 0;
                                break;

                            case 1:
                                count5 = 1;
                                break;

                            case 2:
                                count5 = 1;
                                break;

                            case 3:
                                count5++;
                                break;

                            case 4:
                                count5++;
                                break;

                        }
                        break;
                }

                if(count5 == 3){
                    isDiagonal3 = true;
                    if(previous == 1 || previous == 2){
                        diagonalPerson3 = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        diagonalPerson3 = COMPUTER;
                    }
                }
                row--;
                col++;
            }
            t--;
            previous = 0;
        }


        // checking diagonals (/*)
        t = 4;
        for(int i = 1; i < 6; i++){
            row = i;
            col = 5;
            previous = board[row][col].getTaken();
            if(previous != 0){
                count6 = 1;
            }
            else{
                count6 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){
                    case 0:
                        previous = board[row + 1][col - 1].getTaken();
                        if(board[row - 1][col + 1].getTaken() != 0){
                            count6 = 1;
                        }
                        else{
                            count6 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row + 1][col - 1].getTaken();
                        switch(previous){
                            case 0:
                                count6 = 0;
                                break;

                            case 1:
                                count6++;
                                break;

                            case 2:
                                count6++;
                                break;

                            case 3:
                                count6 = 1;
                                break;

                            case 4:
                                count6 = 1;
                                break;

                        }
                        break;

                    case 2:
                    previous = board[row + 1][col - 1].getTaken();
                        switch(previous){
                            case 0:
                                count6 = 0;
                                break;

                            case 1:
                                count6++;
                                break;

                            case 2:
                                count6++;
                                break;

                            case 3:
                                count6 = 1;
                                break;

                            case 4:
                                count6 = 1;
                                break;

                        }
                        break;

                    case 3:
                        previous = board[row + 1][col - 1].getTaken();
                        switch(previous){
                            case 0:
                                count6 = 0;
                                break;

                            case 1:
                                count6 = 1;
                                break;

                            case 2:
                                count6 = 1;
                                break;

                            case 3:
                                count6++;
                                break;

                            case 4:
                                count6++;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row + 1][col - 1].getTaken();
                        switch(previous){
                            case 0:
                                count6 = 0;
                                break;

                            case 1:
                                count6 = 1;
                                break;

                            case 2:
                                count6 = 1;
                                break;

                            case 3:
                                count6++;
                                break;

                            case 4:
                                count6++;
                                break;

                        }
                        break;
                }

                if(count6 == 3){
                    isDiagonal4 = true;
                    if(previous == 1 || previous == 2){
                        diagonalPerson4 = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        diagonalPerson4 = COMPUTER;
                    }
                }
                row++;
                col--;
            }
            t--;
            previous = 0;
        }

        int firstNum;
        int secondNum;
        int thirdNum;
        int firstChar;
        int secondChar;
        int thirdChar;
        if((isColumn == true || isRow == true || isDiagonal == true || isDiagonal2 == true || isDiagonal3 == true || isDiagonal4 == true) && 
        (columnPerson == next_mover() || rowPerson == next_mover() || diagonalPerson == next_mover() || diagonalPerson2 == next_mover() || diagonalPerson3 == next_mover() || 
        diagonalPerson4 == next_mover())){
            display_status();
            do{
                cout << "Please enter the pieces you would like to remove in order from TOP to BOTTOM or LEFT to RIGHT, ex:" << endl << endl << 
                "1a 1b 1c" << endl << endl << "or" << endl << endl << "1a 2a 3a" << endl << endl << "or" << endl << endl << "1a 2b 3c" << endl << endl;
                getline(cin, input);
                if(input.length() == 8){
                    firstNum = int(input[0] - '1');
                    firstChar = int(toupper(input[1]) - 'A');
                    secondNum = int(input[3] - '1');
                    secondChar = int(toupper(input[4]) - 'A');
                    thirdNum = int(input[6] - '1');
                    thirdChar = int(toupper(input[7]) - 'A');
                    if(isColumn == true){
                        if((firstNum == secondNum && secondNum == thirdNum)){
                            if((firstChar == secondChar - 1) && (secondChar = thirdChar - 1)){
                                // need to adjust to check all spaces
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true;
                                }
                            }
                        }
                    }
                    if(isRow == true){
                        if((firstChar == secondChar && secondChar == thirdChar)){
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true;
                                }
                            }
                        } 
                    }
                    if(isDiagonal == true || isDiagonal2 == true){
                        if((firstChar == secondChar - 1) && (secondChar = thirdChar - 1)){
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true;
                                }
                            }
                        } 
                    }
                    if(isDiagonal3 == true || isDiagonal4 == true){
                        if((firstChar == secondChar + 1) && (secondChar = thirdChar + 1)){
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true;
                                }
                            }
                        } 
                    }
                }
            }while(valid != true);
        }

        if(valid == true){
            board[firstChar][firstNum].setTaken(0);
            board[firstChar][firstNum].setSpace("       ", "       ", "       ");
            board[secondChar][secondNum].setTaken(0);
            board[secondChar][secondNum].setSpace("       ", "       ", "       ");
            board[thirdChar][thirdNum].setTaken(0);
            board[thirdChar][thirdNum].setSpace("       ", "       ", "       ");
            if(next_mover() == HUMAN){
                p1Cats += 3;
            }
            else{
                p2Cats += 3;
            }
        }

    } // end of function

    bool Boop::is_game_over() const{
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        int count4 = 0;
        int count5 = 0;
        int count6 = 0;
        int previous = 0;
        string input;
        bool isColumn = false;
        bool isRow = false;
        bool isDiagonal = false;
        bool isDiagonal2 = false;
        bool isDiagonal3 = false;
        bool isDiagonal4 = false;
        bool valid = false;
        
        for(int column = 0; column < 6; column++){ // CHECKS COLUMNS
            previous = board[0][column].getTaken();
            if(previous == 2 || previous == 4){
                count = 1;
            }
            else{
                count = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){

                    case 2:
                    previous = board[s][column].getTaken();
                        switch(previous){

                            case 2:
                                count++;
                                break;

                            case 4:
                                count = 1;
                                break;

                            default:
                                count = 0;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[s][column].getTaken();
                        switch(previous){

                            case 2:
                                count = 1;
                                break;

                            case 4:
                                count++;
                                break;
                            
                            default:
                                count = 0;
                                break;

                        }
                        break;

                    default:
                        previous = board[s][column].getTaken();
                        if(board[s][column].getTaken() == 2 || board[s][column].getTaken() == 4){
                            count = 1;
                        }
                        else{
                            count = 0;
                        }
                        break;
                }
                
                if(count == 3){
                    isColumn = true;
                }
                
            } // end of inner for loop
        } // end of outer for loop
        
        for(int row = 0; row < 6; row++){ // CHECKS ROWS
            previous = board[row][0].getTaken();
            if(previous == 2 || previous == 4){
                count2 = 1;
            }
            else{
                count2 = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){

                    case 2:
                    previous = board[row][s].getTaken();
                        switch(previous){

                            case 2:
                                count2++;
                                break;

                            case 4:
                                count2 = 1;
                                break;

                            default:
                                count2 = 0;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row][s].getTaken();
                        switch(previous){

                            case 2:
                                count2 = 1;
                                break;

                            case 4:
                                count2++;
                                break;

                            default:
                                count2 = 0;
                                break;

                        }
                        break;
                    
                    default:
                        previous = board[row][s].getTaken();
                        if(board[row][s].getTaken() == 2 || board[row][s].getTaken() == 4){
                            count2 = 1;
                        }
                        else{
                            count2 = 0;
                        }
                        break;

                } 
                if(count2 == 3){
                    isRow = true;
                }
                

            }// end of for loop
        }

        // CHECKS DIAGONALS

        // checking diagonals (*\)
        int t = 5;
        int row;
        int col;
        for(int i = 0; i < 6; i++){
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count3 = 1;
            }
            else{
                count3 = 0;
            }
            for(int j = 0; j < t; j++){
                
                switch(previous){

                    case 2:
                    previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 2:
                                count3++;
                                break;

                            case 4:
                                count3 = 1;
                                break;
                            
                            default:
                                count3 = 0;
                                break;

                        }
                        break;

                    case 4:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){

                            case 2:
                                count3 = 1;
                                break;

                            case 4:
                                count3++;
                                break;
                            
                            default:
                                count3 = 0;
                                break;

                        }
                        break;
                    
                    default:
                        previous = board[row + 1][col + 1].getTaken();
                        if(board[row + 1][col + 1].getTaken() == 2 || board[row + 1][col + 1].getTaken() == 4){
                            count3 = 1;
                        }
                        else{
                            count3 = 0;
                        }
                        break;

                } 

                if(count3 == 3){
                    isDiagonal = true;
                }
                row++;
                col++;
            }
            t--;
            previous = 0;
        }

        // checking diagonals (\*)
        t = 4;
        for(int i = 1; i < 6; i++){
            row = 0;
            col = i;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count4 = 1;
            }
            else{
                count4 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){

                    case 2:
                    previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 2:
                                count4++;
                                break;

                            case 4:
                                count4 = 1;
                                break;

                        }
                        break;
                    
                    case 4:
                        previous = board[row + 1][col + 1].getTaken();
                        switch(previous){
                            case 0:
                                count4 = 0;
                                break;

                            case 2:
                                count4 = 1;
                                break;

                            case 4:
                                count4++;
                                break;

                        }
                        break;

                    
                    default:
                        previous = board[row + 1][col + 1].getTaken();
                        if(board[row + 1][col + 1].getTaken() == 2 || board[row + 1][col + 1].getTaken() == 4){
                            count4 = 1;
                        }
                        else{
                            count4 = 0;
                        }
                        break;

                } 

                if(count4 == 3){
                    isDiagonal2 = true;
                }
                row++;
                col++;
            }
            t--;
            previous = 0;
        }


        // CHECKING THE OTHER WAY DIAGONALLY (please kill me lol ik there's a better way to do this)
        
        // checking diagonals (*/)
        t = 5;
        for(int i = 5; i >= 0; i--){
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count5 = 1;
            }
            else{
                count5 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){

                    case 2:
                    previous = board[row - 1][col + 1].getTaken();
                        switch(previous){
                            case 2:
                                count5++;
                                break;

                            case 4:
                                count5 = 1;
                                break;

                            default:
                                count5 = 0;
                                break;


                        }
                        break;
                    
                    case 4:
                        previous = board[row - 1][col + 1].getTaken();
                        switch(previous){

                            case 2:
                                count5 = 1;
                                break;

                            case 4:
                                count5++;
                                break;

                            default:
                                count5 = 0;
                                break;

                        }
                        break;

                    case 0:
                        previous = board[row - 1][col + 1].getTaken();
                        if(board[row - 1][col + 1].getTaken() == 2 || board[row - 1][col + 1].getTaken() == 4){
                            count5 = 1;
                        }
                        else{
                            count5 = 0;
                        }
                        break;
                }

                if(count5 == 3){
                    isDiagonal3 = true;
                }
                row--;
                col++;
            }
            t--;
            previous = 0;
        }


        // checking diagonals (/*)
        t = 4;
        for(int i = 1; i < 6; i++){
            row = i;
            col = 5;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count6 = 1;
            }
            else{
                count6 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){

                    case 2:
                    previous = board[row + 1][col - 1].getTaken();
                        switch(previous){

                            case 2:
                                count6++;
                                break;

                            case 4:
                                count6 = 1;
                                break;
                            
                            default:
                                count6 = 0;
                                break;

                        }
                        break;

                    case 4:
                        previous = board[row + 1][col - 1].getTaken();
                        switch(previous){

                            case 2:
                                count6 = 1;
                                break;

                            case 4:
                                count6++;
                                break;

                            default:
                                count6 = 0;
                                break;

                        }
                        break;

                    
                    default:
                        previous = board[row + 1][col - 1].getTaken();
                        if(board[row - 1][col + 1].getTaken() == 2 || board[row - 1][col + 1].getTaken() == 4){
                            count6 = 1;
                        }
                        else{
                            count6 = 0;
                        }
                        break;
                }

                if(count6 == 3){
                    isDiagonal4 = true;
                }
                row++;
                col--;
            }
            t--;
            previous = 0;
        }

        if((isRow == true || isColumn == true || isDiagonal == true || isDiagonal2 == true || isDiagonal3 == true || isDiagonal4 == true)){
            return true;
        }
    }

    // 0 for empty, 1 for p1 kitten, 2 for p1 cat, 3 for p2 kitten, 4 for 2 cat
    void Boop::boopThePieces(int row, int column){
        int state = board[row][column].getTaken();
        if((row - 1 < 6) && (row - 1 >= 0) && (column < 6) && (column >= 0)){ // for the space directly above the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column].getTaken() == 2 || board[row - 1][column].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column < 6) && (column >= 0)){
                    if(board[row - 2][column].getTaken() == 0){
                        board[row - 2][column].setTaken(board[row - 1][column].getTaken());
                        board[row - 2][column].setSpace(board[row - 1][column].getRow1(), board[row - 1][column].getRow2(), board[row - 1][column].getRow3());
                        board[row - 1][column].setTaken(0);
                        board[row - 1][column].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row - 1][column].getTaken() == 1){
                        p1Kittens++;
                        board[row - 1][column].setTaken(0);
                        board[row - 1][column].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row - 1][column].getTaken() == 3){
                        p2Kittens++;
                        board[row - 1][column].setTaken(0);
                        board[row - 1][column].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }
        
        if((row + 1 < 6) && (row + 1 >= 0) && (column < 6) && (column >= 0)){ // for the space directly below the placed piece
            if(!((state == 1 || state == 3) && ((board[row + 1][column].getTaken() == 2 || board[row + 1][column].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row + 2 < 6) && (row + 2 >= 0) && (column < 6) && (column >= 0)){
                    if(board[row + 2][column].getTaken() == 0){
                        board[row + 2][column].setTaken(board[row + 1][column].getTaken());
                        board[row + 2][column].setSpace(board[row + 1][column].getRow1(), board[row + 1][column].getRow2(), board[row + 1][column].getRow3());
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    cout << "got to the else" << endl;
                    if(board[row + 1][column].getTaken() == 1){
                        p1Kittens++;
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column].getTaken() == 3){
                        p2Kittens++;
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row < 6) && (row >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly to the left of the placed piece
            if(!((state == 1 || state == 3) && ((board[row][column - 1].getTaken() == 2 || board[row][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row < 6) && (row >= 0) && (column - 2 < 6) && (column - 2 >= 0)){
                    if(board[row][column - 2].getTaken() == 0){
                        board[row][column - 2].setTaken(board[row][column - 1].getTaken());
                        board[row][column - 2].setSpace(board[row][column - 1].getRow1(), board[row][column - 1].getRow2(), board[row][column - 1].getRow3());
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row][column - 1].getTaken() == 1){
                        p1Kittens++;
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row][column - 1].getTaken() == 3){
                        p2Kittens++;
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row < 6) && (row >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly to the right of the placed piece
            if(!((state == 1 || state == 3) && ((board[row][column + 1].getTaken() == 2 || board[row][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row < 6) && (row >= 0) && (column + 2 < 6) && (column + 2 >= 0)){
                    if(board[row][column + 2].getTaken() == 0){
                        board[row][column + 2].setTaken(board[row][column + 1].getTaken());
                        board[row][column + 2].setSpace(board[row][column + 1].getRow1(), board[row][column + 1].getRow2(), board[row][column + 1].getRow3());
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row][column + 1].getTaken() == 1){
                        p1Kittens++;
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row][column + 1].getTaken() == 3){
                        p2Kittens++;
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row - 1 < 6) && (row - 1 >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly NE of the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column + 1].getTaken() == 2 || board[row - 1][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column + 2 < 6) && (column + 2 >= 0)){
                    if(board[row - 2][column + 2].getTaken() == 0){
                        board[row - 2][column + 2].setTaken(board[row - 1][column + 1].getTaken());
                        board[row - 2][column + 2].setSpace(board[row - 1][column + 1].getRow1(), board[row - 1][column + 1].getRow2(), board[row - 1][column + 1].getRow3());
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row - 1][column + 1].getTaken() == 1){
                        p1Kittens++;
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row - 1][column + 1].getTaken() == 3){
                        p2Kittens++;
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row - 1 < 6) && (row - 1 >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly NW of the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column - 1].getTaken() == 2 || board[row - 1][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column - 2 < 6) && (column - 2 >= 0)){
                    if(board[row - 2][column - 2].getTaken() == 0){
                        board[row - 2][column - 2].setTaken(board[row - 1][column - 1].getTaken());
                        board[row - 2][column - 2].setSpace(board[row - 1][column - 1].getRow1(), board[row - 1][column - 1].getRow2(), board[row - 1][column - 1].getRow3());
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row - 1][column - 1].getTaken() == 1){
                        p1Kittens++;
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row - 1][column - 1].getTaken() == 3){
                        p2Kittens++;
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row + 1 < 6) && (row + 1 >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly SE of the placed piece
            if(!((state == 1 || state == 3) && ((board[row + 1][column + 1].getTaken() == 2 || board[row + 1][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row + 2 < 6) && (row + 2 >= 0) && (column + 2 < 6) && (column + 2 >= 0)){
                    if(board[row + 2][column + 2].getTaken() == 0){
                        board[row + 2][column + 2].setTaken(board[row + 1][column + 1].getTaken());
                        board[row + 2][column + 2].setSpace(board[row + 1][column + 1].getRow1(), board[row + 1][column + 1].getRow2(), board[row + 1][column + 1].getRow3());
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row + 1][column + 1].getTaken() == 1){
                        p1Kittens++;
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column + 1].getTaken() == 3){
                        p2Kittens++;
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row + 1 < 6) && (row + 1 >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly SW of the placed piece
            if(!((state == 1 || state == 3) && ((board[row + 1][column - 1].getTaken() == 2 || board[row + 1][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row + 2 < 6) && (row + 2 >= 0) && (column - 2 < 6) && (column - 2 >= 0)){
                    if(board[row + 2][column - 2].getTaken() == 0){
                        board[row + 2][column - 2].setTaken(board[row + 1][column - 1].getTaken());
                        board[row + 2][column - 2].setSpace(board[row + 1][column - 1].getRow1(), board[row + 1][column - 1].getRow2(), board[row + 1][column - 1].getRow3());
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{
                    if(board[row + 1][column - 1].getTaken() == 1){
                        p1Kittens++;
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column - 1].getTaken() == 3){
                        p2Kittens++;
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }
        
    }

     game::who Boop::winning( ) const{
        
     }

}