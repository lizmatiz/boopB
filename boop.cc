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

        p1Cats = 0; // players start with 0 cats
        p2Cats = 0;

        columnPerson = NEUTRAL; // all of these help check if the player has three in a row
        rowPerson = NEUTRAL;
        diagonalPerson = NEUTRAL;
        diagonalPerson2 = NEUTRAL;
        diagonalPerson3 = NEUTRAL;
        diagonalPerson4 = NEUTRAL;

        cout << "Please enter your moves in a k1a (place a kitten in space 1a) or c1a (place a cat in space 1a) format." << endl;

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

        if(is_game_over() == true){ // if the game is over, return
            return;
        }

        boopThePieces(rowNum, columnNum); // boop all the pieces

        check(); // check for three in a row

        game::make_move(move); // call the game make move
        
    }

    void Boop::check(){
        /**
         * This function loops through the board using a system of nested for loops. There are 6 "sets" of nested for loops":
         * 1. Checks columns
         * 2. Checks rows
         * 3. Checks half of diagonals one way (including the middle)
         * 4. Checks the other half of the diagonals one way
         * 5. Checks half of the diagonals the other way (including the middle)
         * 6. Checks the other half of the diagonals the other way
         * 
         * If the user is successful, it takes and checks a user input to see which pieces to remove
         * 
         * It also checks to see if a player has 8 pieces on a board. If they do, they are asked to remove one, and it turns into a cat in their inventory.
         * 
         */
        int count = 0; // count for column
        int count2 = 0; // count for row
        int count3 = 0; // count for one of the diagonal sections
        int count4 = 0; // count for one of the diagonal sections
        int count5 = 0; // count for one of the diagonal sections
        int count6 = 0; // count for one of the diagonal sections
        int previous = 0; // keeps track of previous (and sometimes current) space state
        string input; // user input
        bool valid = false; // if the input is valid
        bool isColumn = false; // if the column is 3 in a row
        bool isRow = false; // if the row is 3 in a row
        bool isDiagonal = false; // if one of the diagonals is 3 in a row
        bool isDiagonal2 = false; // if one of the diagonals is 3 in a row
        bool isDiagonal3 = false; // if one of the diagonals is 3 in a row
        bool isDiagonal4 = false; // if one of the diagonals is 3 in a row
        int firstNum; // all of these are to transfer the input to the format the 2d array likes
        int secondNum;
        int thirdNum;
        int firstChar;
        int secondChar;
        int thirdChar;
        
        for(int column = 0; column < 6; column++){ // **CHECKS COLUMNS**
            previous = board[0][column].getTaken(); // set previous equal to the first space checked
            if(previous != 0){
                count = 1;
            }
            else{
                count = 0;
            }
            for(int s = 1; s < 6; s++){ // going through the each space of the column
                switch(previous){
                    case 0: 
                        previous = board[s][column].getTaken(); // set previous equal to the current
                        if(board[s][column].getTaken() != 0){ // based on what the current space is, change the count
                            count = 1;
                        }
                        else{
                            count = 0;
                        }
                        break;
                    case 1:
                        previous = board[s][column].getTaken(); // set previous equal to the current
                        switch(previous){ // based on what the current space is, change the count
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
                    previous = board[s][column].getTaken(); // set previous equal to the current
                        switch(previous){ // based on what the current space is, change the count
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
                        previous = board[s][column].getTaken(); // set previous equal to the current
                        switch(previous){ // based on what the current space is, change the count
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
                        previous = board[s][column].getTaken(); // set previous equal to the current
                        switch(previous){ // based on what the current space is, change the count
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
                
                if(count == 3){ // if 3 in a row are found
                    isColumn = true; // bool is true
                    if(previous == 1 || previous == 2){ // this keeps track of if it belongs to a HUMAN or COMPUTER
                        columnPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        columnPerson = COMPUTER;
                    }
                }
                
            } // end of inner for loop
        } // end of outer for loop
        
         // CHECKS ROWS
        for(int row = 0; row < 6; row++){
            previous = board[row][0].getTaken(); // sets previous
            if(previous != 0){ // 
                count2 = 1;
            }
            else{
                count2 = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){ // depending on what the previous space was
                    case 0:
                        previous = board[row][s].getTaken(); // sets previous to current
                        if(board[row][s].getTaken() != 0){ // change the count based on the state
                            count2 = 1;
                        }
                        else{
                            count2 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row][s].getTaken(); // sets previous to current
                        switch(previous){ // based on what the current space is, change the count
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
                    previous = board[row][s].getTaken(); // sets previous to current
                        switch(previous){ // based on what the current space is, change the count
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
                        previous = board[row][s].getTaken(); // sets previous to current
                        switch(previous){ // based on what the current space is, change the count
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
                        previous = board[row][s].getTaken(); // sets previous to current
                        switch(previous){ // based on what the current space is, change the count
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
                if(count2 == 3){ // if there is 3 in a row found
                    isRow = true; // bool is true
                    if(previous == 1 || previous == 2){ // keeps track of if it is a HUMAN's win and a COMPUTER's win
                        rowPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        rowPerson = COMPUTER;
                    }
                }
                

            }// end of inner loop
        } // end of outer loop

        // CHECKS DIAGONALS (the star helps you know what side of the diagonal through the middle it is checking)
        // the diagonal variables...
        int t = 5; // temp is 5
        int row; // variable for a row
        int col; // variable for the column

        // CHECKING DIAGONALS (*\)
        for(int i = 0; i < 6; i++){ // outer loop
            row = i; // change the row
            col = 0; // column is 0
            previous = board[row][col].getTaken(); // set previous
            if(previous != 0){ // change the count based on previous
                count3 = 1;
            }
            else{
                count3 = 0;
            }
            for(int j = 0; j < t; j++){ // innter loop
                
                switch(previous){ // based on what the current space is, change the count
                    case 0:
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        if(board[row + 1][col + 1].getTaken() != 0){ // adjust count
                            count3 = 1;
                        }
                        else{
                            count3 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the state of the space, change count
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
                    previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the state of the space, change count
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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the state of the space, change count
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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the state of the space, change count
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

                if(count3 == 3){ // keeps track of whether or not there is 3 in a row
                    isDiagonal = true;
                    if(previous == 1 || previous == 2){ // keeps track of who the 3 in a row belongs to
                        diagonalPerson = HUMAN;
                    }
                    if(previous == 3 || previous == 4){
                        diagonalPerson = COMPUTER;
                    }
                }
                row++;
                col++;
            } // end of inner loop
            t--;
            previous = 0;
        } // end of outer loop

        // CHECKING DIAGONALS (\*)
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

        // CHECKING THE OTHER WAY DIAGONALLY
        
        // CHECKING DIAGONALS (*/)
        t = 5;
        for(int i = 5; i >= 0; i--){ // loops through rows
            row = i;
            col = 0;
            previous = board[row][col].getTaken(); // sets previous
            if(previous != 0){ // adjust the count based on the state of the space
                count5 = 1;
            }
            else{
                count5 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // based on the actual previous state
                    case 0:
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        if(board[row - 1][col + 1].getTaken() != 0){ // adjust the count based on the state of the space
                            count5 = 1;
                        }
                        else{
                            count5 = 0;
                        }
                        break;
                    
                    case 1:
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the new previous, change count
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
                    previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the new previous, change count
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
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the new previous, change count
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
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // based on the new previous, change count
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

                if(count5 == 3){ // if 3 in a row is found, set the bool and keep track of who it belongs to
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

            } // end of inner loop

            t--;
            previous = 0;

        } // end of outer loop


        // CHECKING DIAGONALS (/*)
        t = 4;
        for(int i = 1; i < 6; i++){ // loops through rows
            row = i;
            col = 5;
            previous = board[row][col].getTaken(); // set previous
            if(previous != 0){ // adjust the count based on previous
                count6 = 1;
            }
            else{
                count6 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // based on actual previous
                    case 0:
                        previous = board[row + 1][col - 1].getTaken(); // set new previous
                        if(board[row - 1][col + 1].getTaken() != 0){
                            count6 = 1;
                        }
                        else{
                            count6 = 0;
                        }
                        break;
                    case 1:
                        previous = board[row + 1][col - 1].getTaken(); // set new previous
                        switch(previous){ // based on the new previous, change count
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
                    previous = board[row + 1][col - 1].getTaken(); // set new previous
                        switch(previous){ // based on the new previous, change count
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
                        previous = board[row + 1][col - 1].getTaken(); // set new previous
                        switch(previous){ // based on the new previous, change count
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
                        previous = board[row + 1][col - 1].getTaken(); // set new previous
                        switch(previous){ // based on the new previous, change count
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

                if(count6 == 3){ // if you find 3 in a row, set the bool and keep track of who it belongs to
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
            } // end of inner loop
            t--;
            previous = 0;
        } // end of outer loop

        if((isColumn == true || isRow == true || isDiagonal == true || isDiagonal2 == true || isDiagonal3 == true || isDiagonal4 == true) && 
        (columnPerson == next_mover() || rowPerson == next_mover() || diagonalPerson == next_mover() || diagonalPerson2 == next_mover() || diagonalPerson3 == next_mover() || 
        diagonalPerson4 == next_mover())){ // checks if any of the for loops "returned" true, and if they actually belong to the player who's turn it is
            display_status(); // displays the board
            do{ // asks for input and checks to see if it is valid
                cout << "Please enter the pieces you would like to remove in order from TOP to BOTTOM or LEFT to RIGHT, ex:" << endl << endl << 
                "1a 1b 1c" << endl << endl << "or" << endl << endl << "1a 2a 3a" << endl << endl << "or" << endl << endl << "1a 2b 3c" << endl << endl;
                getline(cin, input);
                if(input.length() == 8){
                    firstNum = int(input[0] - '1'); // all of this transforms the user input to something accepted by the 2d array
                    firstChar = int(toupper(input[1]) - 'A');
                    secondNum = int(input[3] - '1');
                    secondChar = int(toupper(input[4]) - 'A');
                    thirdNum = int(input[6] - '1');
                    thirdChar = int(toupper(input[7]) - 'A');
                    if(isColumn == true){ // if there are 3 in a row in a column
                        if(firstNum < 6 && secondNum < 6 && thirdNum < 6 && firstChar < 6 && secondChar < 6 && thirdChar < 6){
                            if((firstNum == secondNum && secondNum == thirdNum)){ // checks to make sure it is valid
                                if((firstChar == secondChar - 1) && (secondChar = thirdChar - 1)){
                                    if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                    (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                    (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                    next_mover() == HUMAN) ||

                                    (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                    (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                    (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                    next_mover() == COMPUTER)){
                                        valid = true; // if it is valid, it is true
                                    }
                                }
                            }
                        }
                    }
                    if(isRow == true){ // if there are 3 in a row in a row
                        if((firstChar == secondChar && secondChar == thirdChar)){ // checks to make sure it is valid
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true; // if it is valid, it is true
                                }
                            }
                        } 
                    }
                    if(isDiagonal == true || isDiagonal2 == true){ // if there are 3 in a row in a diagonal (first and second section)
                        if((firstChar == secondChar - 1) && (secondChar = thirdChar - 1)){ // checks to make sure it is valid
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true; // if it is valid, it is true
                                }
                            }
                        } 
                    }
                    if(isDiagonal3 == true || isDiagonal4 == true){ // if there are 3 in a row in a diagonal (third and fourth section)
                        if((firstChar == secondChar + 1) && (secondChar = thirdChar + 1)){ // checks to make sure it is valid
                            if((firstNum == secondNum - 1) && (secondNum = thirdNum - 1)){
                                if((((board[firstChar][firstNum].getTaken() == 1 || board[firstChar][firstNum].getTaken() == 2) &&
                                (board[secondChar][secondNum].getTaken() == 1 || board[secondChar][secondNum].getTaken() == 2) &&
                                (board[thirdChar][thirdNum].getTaken() == 1 || board[thirdChar][thirdNum].getTaken() == 2)) &&
                                next_mover() == HUMAN) ||

                                (((board[firstChar][firstNum].getTaken() == 3 || board[firstChar][firstNum].getTaken() == 4) &&
                                (board[secondChar][secondNum].getTaken() == 3 || board[secondChar][secondNum].getTaken() == 4) &&
                                (board[thirdChar][thirdNum].getTaken() == 3 || board[thirdChar][thirdNum].getTaken() == 4)) &&
                                next_mover() == COMPUTER)){
                                    valid = true; // if it is valid, it is true
                                }
                            }
                        } 
                    }
                }
            }while(valid != true); // do this until the user gives a valid answer
        }

        if(valid == true){ // if valid is true, remove the pieces and increase the player's cats by 3
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

        // this checks to see if the player has 8 kittens / cats on the board
        bool isKitten8 = false;
        if(next_mover() == HUMAN && p1Cats + p1Kittens == 0){ // if they do have all pieces on the board
            display_status();
            do{
                cout << "Please enter a piece you would like to remove in the format 1a" << endl; // ask them for a piece to enter
                getline(cin, input);
                if(input.length() == 2){ // check the length
                        firstNum = int(input[0] - '1'); // all of this transforms the user input to something accepted by the 2d array
                        firstChar = int(toupper(input[1]) - 'A');
                        if(firstNum < 6 && firstChar < 6){ // if it is in the array
                            if(board[firstChar][firstNum].getTaken() == 1){ // if the space is theirs and it is a kitten
                                board[firstChar][firstNum].setTaken(0); // empty the space
                                board[firstChar][firstNum].setSpace("       ", "       ", "       ");
                                p1Cats++; // increment their cats
                                isKitten8 = true; // bool is true
                            }
                        }
                }
            }while(isKitten8 == false);
        }
        
        if(next_mover() == COMPUTER && p2Cats + p2Kittens == 0){ // if they do have all pieces on the board
            display_status();
            do{
                cout << "You have 8 pieces on the board! Please enter a piece you would like to remove in the format 1a." << endl; // ask them for a piece to enter
                getline(cin, input);
                if(input.length() == 2){
                    firstNum = int(input[0] - '1'); // all of this transforms the user input to something accepted by the 2d array
                    firstChar = int(toupper(input[1]) - 'A');
                    if(firstNum < 6 && firstChar < 6){ // if it is in the array
                        if(board[firstChar][firstNum].getTaken() == 3){ // if the space is theirs and it is a kitten
                            board[firstChar][firstNum].setTaken(0); // empty the space
                            board[firstChar][firstNum].setSpace("       ", "       ", "       ");
                            p2Cats++; // increment their cats
                            isKitten8 = true; // bool is true
                        }
                    }
                }
            }while(isKitten8 == false);
        }

    } // end of function

    bool Boop::is_game_over() const{
        /**
         * This function loops through the board using a system of nested for loops. There are 6 "sets" of nested for loops":
         * 1. Checks columns
         * 2. Checks rows
         * 3. Checks half of diagonals one way (including the middle)
         * 4. Checks the other half of the diagonals one way
         * 5. Checks half of the diagonals the other way (including the middle)
         * 6. Checks the other half of the diagonals the other way
         */

        int count = 0; // all of the count
        int count2 = 0;
        int count3 = 0;
        int count4 = 0;
        int count5 = 0;
        int count6 = 0;
        int previous = 0; // keeps track of previous states
        bool isColumn = false; // if there are three cats in a row in a column
        bool isRow = false; // if there are three cats in a row in a row
        bool isDiagonal = false; // if there are three cats in a row in a diagonal
        bool isDiagonal2 = false; // if there are three cats in a row in a diagonal
        bool isDiagonal3 = false; // if there are three cats in a row in a diagonal
        bool isDiagonal4 = false; // if there are three cats in a row in a diagonal
        
        // NOTE: the cases are 2, 4, and default because only cats matter here

        // CHECKS COLUMNS
        for(int column = 0; column < 6; column++){ // loops through columns
            previous = board[0][column].getTaken(); // set previous
            if(previous == 2 || previous == 4){ // based on previous, set count
                count = 1;
            }
            else{
                count = 0;
            }
            for(int s = 1; s < 6; s++){ // inner loop
                switch(previous){ // based on the state of the previous space
                    case 2:
                    previous = board[s][column].getTaken(); // set new previous
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
                        previous = board[s][column].getTaken(); // set new previous
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
                        previous = board[s][column].getTaken(); // set new previous
                        if(board[s][column].getTaken() == 2 || board[s][column].getTaken() == 4){ // if the space is a cat, count = 1
                            count = 1;
                        }
                        else{
                            count = 0;
                        }
                        break;
                }
                
                if(count == 3){ // if it found 3 in a row, isColumn is true
                    isColumn = true;
                }
                
            } // end of inner for loop
        } // end of outer for loop
        
        // CHECKS ROWS
        for(int row = 0; row < 6; row++){ // loops through rows
            previous = board[row][0].getTaken(); // set previous
            if(previous == 2 || previous == 4){
                count2 = 1;
            }
            else{
                count2 = 0;
            }
            for(int s = 1; s < 6; s++){
                switch(previous){ // based on the state of the previous space
                    case 2:
                    previous = board[row][s].getTaken(); // set new previous
                        switch(previous){ // based on previous, change the count

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
                        previous = board[row][s].getTaken(); // set new previous
                        switch(previous){ // based on previous, change the count

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
                        previous = board[row][s].getTaken(); // set new previous
                        if(board[row][s].getTaken() == 2 || board[row][s].getTaken() == 4){ // if the new space is a cat, count = 1
                            count2 = 1;
                        }
                        else{
                            count2 = 0;
                        }
                        break;

                } 
                if(count2 == 3){ // if it found 3 in a row, count2 = true
                    isRow = true;
                }
            }// end of for loop
        }

        // CHECKS DIAGONALS

        // diagonal variables
        int t = 5;
        int row;
        int col;

        // CHECKING DIAGONALS (*\)
        for(int i = 0; i < 6; i++){ // outer loop
            row = i;
            col = 0;
            previous = board[row][col].getTaken(); // set previous
            if(previous == 2 || previous == 4){ // check previous
                count3 = 1;
            }
            else{
                count3 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                
                switch(previous){
                    case 2:
                    previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // set count based on previous
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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        switch(previous){ // set count based on previous

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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        if(board[row + 1][col + 1].getTaken() == 2 || board[row + 1][col + 1].getTaken() == 4){ // adjust count
                            count3 = 1;
                        }
                        else{
                            count3 = 0;
                        }
                        break;

                } 

                if(count3 == 3){ // if 3 in a row are found, true
                    isDiagonal = true;
                }
                row++; // increment
                col++;
            }
            t--; // decrement
            previous = 0; // set previous
        }

        // CHECKING DIAGONALS (\*)
        t = 4;
        for(int i = 1; i < 6; i++){ // outer loop
            row = 0;
            col = i;
            previous = board[row][col].getTaken(); // set previous
            if(previous == 2 || previous == 4){ // set count based on previous
                count4 = 1;
            }
            else{
                count4 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // set count based on previous
                    case 2:
                    previous = board[row + 1][col + 1].getTaken(); // set previous
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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
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
                        previous = board[row + 1][col + 1].getTaken(); // set previous
                        if(board[row + 1][col + 1].getTaken() == 2 || board[row + 1][col + 1].getTaken() == 4){ // if the space is a cat, set count accordingly
                            count4 = 1;
                        }
                        else{
                            count4 = 0;
                        }
                        break;
                } 

                if(count4 == 3){ // if 3 cats were found in a row, set to true
                    isDiagonal2 = true;
                }
                row++; // increment
                col++;
            }
            t--; // decrement
            previous = 0; // set previous
        }


        // CHECKING THE OTHER WAY DIAGONALLY (please kill me lol ik there's a better way to do this)
        
        // CHECKING DIAGONALS (*/)
        t = 5; // set t
        for(int i = 5; i >= 0; i--){ // outer loop
            row = i;
            col = 0;
            previous = board[row][col].getTaken(); // set previous
            if(previous == 2 || previous == 4){ // changed count based on previous
                count5 = 1;
            }
            else{
                count5 = 0;
            }
            for(int j = 0; j < t; j++){
                switch(previous){
                    case 2:
                    previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // change count based on previous
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
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        switch(previous){ // change count based on previous

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
                        previous = board[row - 1][col + 1].getTaken(); // set previous
                        if(board[row - 1][col + 1].getTaken() == 2 || board[row - 1][col + 1].getTaken() == 4){ // if the space has a kitten, set the count accordingly
                            count5 = 1;
                        }
                        else{
                            count5 = 0;
                        }
                        break;
                }

                if(count5 == 3){ // if 3 in a row were found, set to true
                    isDiagonal3 = true;
                }
                row--; // decrement
                col++; // increment
            }
            t--; // decrement
            previous = 0;
        }


        // CHECKING DIAGONALS (/*)
        t = 4;
        for(int i = 1; i < 6; i++){ // outer loop
            row = i;
            col = 5;
            previous = board[row][col].getTaken(); // set previous
            if(previous == 2 || previous == 4){ // based on previous, set count
                count6 = 1;
            }
            else{
                count6 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){
                    case 2:
                    previous = board[row + 1][col - 1].getTaken(); // set previous
                        switch(previous){ // based on previous, set count

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
                        previous = board[row + 1][col - 1].getTaken(); // set previous
                        switch(previous){ // based on previous, set count

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
                        previous = board[row + 1][col - 1].getTaken(); // set previous
                        if(board[row - 1][col + 1].getTaken() == 2 || board[row - 1][col + 1].getTaken() == 4){ // if there is a cat in the space, set count accordingly
                            count6 = 1;
                        }
                        else{
                            count6 = 0;
                        }
                        break;
                }

                if(count6 == 3){ // if 3 cats were found in a row true
                    isDiagonal4 = true;
                }
                row++; // increment
                col--; // decrement
            }
            t--; // decrement
            previous = 0; // set previous back to 0
        }

        if((isRow == true || isColumn == true || isDiagonal == true || isDiagonal2 == true || isDiagonal3 == true || isDiagonal4 == true)){ // if any one of the set loops "returned" true, return true
            return true;
        }
        else{
            return false;
        }
    }

    // 0 for empty, 1 for p1 kitten, 2 for p1 cat, 3 for p2 kitten, 4 for 2 cat
    // This function checks each space around the placed piece to see if you need to boop it.

    void Boop::boopThePieces(int row, int column){
        int state = board[row][column].getTaken();
        if((row - 1 < 6) && (row - 1 >= 0) && (column < 6) && (column >= 0)){ // for the space directly above the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column].getTaken() == 2 || board[row - 1][column].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column < 6) && (column >= 0)){ // if there is space to boop it to
                    if(board[row - 2][column].getTaken() == 0){ // if the space is empty
                        board[row - 2][column].setTaken(board[row - 1][column].getTaken()); // boop the piece over and empty its previous space
                        board[row - 2][column].setSpace(board[row - 1][column].getRow1(), board[row - 1][column].getRow2(), board[row - 1][column].getRow3());
                        board[row - 1][column].setTaken(0);
                        board[row - 1][column].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                if((row + 2 < 6) && (row + 2 >= 0) && (column < 6) && (column >= 0)){ // if there is space to boop it to
                    if(board[row + 2][column].getTaken() == 0){ // if the space is empty
                        board[row + 2][column].setTaken(board[row + 1][column].getTaken()); // boop the piece over and empty its previous space
                        board[row + 2][column].setSpace(board[row + 1][column].getRow1(), board[row + 1][column].getRow2(), board[row + 1][column].getRow3());
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row + 1][column].getTaken() == 2){
                        p1Cats++;
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column].getTaken() == 4){
                        p2Cats++;
                        board[row + 1][column].setTaken(0);
                        board[row + 1][column].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row < 6) && (row >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly to the left of the placed piece
            if(!((state == 1 || state == 3) && ((board[row][column - 1].getTaken() == 2 || board[row][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row < 6) && (row >= 0) && (column - 2 < 6) && (column - 2 >= 0)){ // if there is space to boop it to
                    if(board[row][column - 2].getTaken() == 0){ // if the space is empty
                        board[row][column - 2].setTaken(board[row][column - 1].getTaken()); // boop the piece over and empty its previous space
                        board[row][column - 2].setSpace(board[row][column - 1].getRow1(), board[row][column - 1].getRow2(), board[row][column - 1].getRow3());
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row][column - 1].getTaken() == 2){
                        p1Cats++;
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row][column - 1].getTaken() == 4){
                        p2Cats++;
                        board[row][column - 1].setTaken(0);
                        board[row][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row < 6) && (row >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly to the right of the placed piece
            if(!((state == 1 || state == 3) && ((board[row][column + 1].getTaken() == 2 || board[row][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row < 6) && (row >= 0) && (column + 2 < 6) && (column + 2 >= 0)){ // if there is space to boop it to
                    if(board[row][column + 2].getTaken() == 0){ // if the space is empty
                        board[row][column + 2].setTaken(board[row][column + 1].getTaken()); // boop the piece over and empty its previous space
                        board[row][column + 2].setSpace(board[row][column + 1].getRow1(), board[row][column + 1].getRow2(), board[row][column + 1].getRow3());
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row][column + 1].getTaken() == 2){
                        p1Cats++;
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row][column + 1].getTaken() == 4){
                        p2Cats++;
                        board[row][column + 1].setTaken(0);
                        board[row][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row - 1 < 6) && (row - 1 >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly NE of the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column + 1].getTaken() == 2 || board[row - 1][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column + 2 < 6) && (column + 2 >= 0)){ // if there is space to boop it to
                    if(board[row - 2][column + 2].getTaken() == 0){ // if the space is empty
                        board[row - 2][column + 2].setTaken(board[row - 1][column + 1].getTaken()); // boop the piece over and empty its previous space
                        board[row - 2][column + 2].setSpace(board[row - 1][column + 1].getRow1(), board[row - 1][column + 1].getRow2(), board[row - 1][column + 1].getRow3());
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row - 1][column + 1].getTaken() == 2){
                        p1Cats++;
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row - 1][column + 1].getTaken() == 4){
                        p2Cats++;
                        board[row - 1][column + 1].setTaken(0);
                        board[row - 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row - 1 < 6) && (row - 1 >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly NW of the placed piece
            if(!((state == 1 || state == 3) && ((board[row - 1][column - 1].getTaken() == 2 || board[row - 1][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row - 2 < 6) && (row - 2 >= 0) && (column - 2 < 6) && (column - 2 >= 0)){ // if there is space to boop it to
                    if(board[row - 2][column - 2].getTaken() == 0){ // if the space is empty
                        board[row - 2][column - 2].setTaken(board[row - 1][column - 1].getTaken()); // boop the piece over and empty its previous space
                        board[row - 2][column - 2].setSpace(board[row - 1][column - 1].getRow1(), board[row - 1][column - 1].getRow2(), board[row - 1][column - 1].getRow3());
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row - 1][column - 1].getTaken() == 2){
                        p1Cats++;
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row - 1][column - 1].getTaken() == 4){
                        p2Cats++;
                        board[row - 1][column - 1].setTaken(0);
                        board[row - 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row + 1 < 6) && (row + 1 >= 0) && (column + 1 < 6) && (column + 1 >= 0)){ // for the space directly SE of the placed piece
            if(!((state == 1 || state == 3) && ((board[row + 1][column + 1].getTaken() == 2 || board[row + 1][column + 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row + 2 < 6) && (row + 2 >= 0) && (column + 2 < 6) && (column + 2 >= 0)){ // if there is space to boop it to
                    if(board[row + 2][column + 2].getTaken() == 0){ // if the space is empty
                        board[row + 2][column + 2].setTaken(board[row + 1][column + 1].getTaken()); // boop the piece over and empty its previous space
                        board[row + 2][column + 2].setSpace(board[row + 1][column + 1].getRow1(), board[row + 1][column + 1].getRow2(), board[row + 1][column + 1].getRow3());
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row + 1][column + 1].getTaken() == 2){
                        p1Cats++;
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column + 1].getTaken() == 4){
                        p2Cats++;
                        board[row + 1][column + 1].setTaken(0);
                        board[row + 1][column + 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }

        if((row + 1 < 6) && (row + 1 >= 0) && (column - 1 < 6) && (column - 1 >= 0)){ // for the space directly SW of the placed piece
            if(!((state == 1 || state == 3) && ((board[row + 1][column - 1].getTaken() == 2 || board[row + 1][column - 1].getTaken() == 4)))){ // if the state is not a cat and it the space is not a kitten
                if((row + 2 < 6) && (row + 2 >= 0) && (column - 2 < 6) && (column - 2 >= 0)){ // if there is space to boop it to
                    if(board[row + 2][column - 2].getTaken() == 0){ // if the space is empty
                        board[row + 2][column - 2].setTaken(board[row + 1][column - 1].getTaken()); // boop the piece over and empty its previous space
                        board[row + 2][column - 2].setSpace(board[row + 1][column - 1].getRow1(), board[row + 1][column - 1].getRow2(), board[row + 1][column - 1].getRow3());
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
                else{ // if there is not a space on the board to boop it to, it gets knocked off the board
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
                    else if(board[row + 1][column - 1].getTaken() == 2){
                        p1Cats++;
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                    else if(board[row + 1][column - 1].getTaken() == 4){
                        p2Cats++;
                        board[row + 1][column - 1].setTaken(0);
                        board[row + 1][column - 1].setSpace("       ", "       ", "       ");
                    }
                }
            }
        }
        
    }

     game::who Boop::winning( ) const{

        // This function uses the same code as the is_game_over function, but it keeps track of who's cats are three in a row. At the end, it returns who won based on the bools p1 and p2.

        bool p1 = false; // player 1 win
        bool p2 = false; // player 2 win
        int count = 0;
        int count2 = 0;
        int count3 = 0;
        int count4 = 0;
        int count5 = 0;
        int count6 = 0;
        int previous = 0;
        string input;

        // CHECKS COLUMNS
        for(int column = 0; column < 6; column++){ // outer loop
            previous = board[0][column].getTaken();
            if(previous == 2 || previous == 4){
                count = 1;
            }
            else{
                count = 0;
            }
            for(int s = 1; s < 6; s++){ // inner loop
                switch(previous){ // cases regarding the previous state

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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
                    }
                }
                
            } // end of inner for loop
        } // end of outer for loop
        
        // CHECKS ROWS
        for(int row = 0; row < 6; row++){ // outer loop
            previous = board[row][0].getTaken();
            if(previous == 2 || previous == 4){
                count2 = 1;
            }
            else{
                count2 = 0;
            }
            for(int s = 1; s < 6; s++){ // inner loop
                switch(previous){ // cases regarding the previous state
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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
                    }
                }
                

            }// end of for loop
        }

        // CHECKS DIAGONALS

        // checking diagonals (*\)
        int t = 5;
        int row;
        int col;
        for(int i = 0; i < 6; i++){ // outer loop
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count3 = 1;
            }
            else{
                count3 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                
                switch(previous){ // cases regarding the previous state
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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
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
        for(int i = 1; i < 6; i++){ // outer loop
            row = 0;
            col = i;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count4 = 1;
            }
            else{
                count4 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // cases regarding the previous state
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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
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
        for(int i = 5; i >= 0; i--){ // outer loop
            row = i;
            col = 0;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count5 = 1;
            }
            else{
                count5 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // cases regarding the previous state
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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
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
        for(int i = 1; i < 6; i++){ // outer loop
            row = i;
            col = 5;
            previous = board[row][col].getTaken();
            if(previous == 2 || previous == 4){
                count6 = 1;
            }
            else{
                count6 = 0;
            }
            for(int j = 0; j < t; j++){ // inner loop
                switch(previous){ // cases regarding the previous state

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
                    if(previous == 2){
                        p1 = true;
                    }
                    if(previous == 4){
                        p2 = true;
                    }
                }
                row++;
                col--;
            }
            t--;
            previous = 0;
        }

        // is both player 1 and player 2 have wins, it is a tie
        if(p1 == true && p2 == true){
            return NEUTRAL;
        }
        else if(p1 == true){ // if just player 1 has a win, player 1 wins
            return HUMAN;
        }
        else{ // if just player 2 has a win, player 2 wins
            return COMPUTER;
        }

     }

}