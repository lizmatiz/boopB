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

        check();

        game::make_move(move);

        

    }

    void Boop::check(){
        int count = 0;
        int count2 = 0;
        int previous = 0;
        bool valid = false;
        bool valid2 = false;
        string upgrade;
        int currentRow2;
        int currentColumn2;
        string input;
        string input2;
        bool is3 = false;
        bool is32 = false;
        
        for(int column = 0; column < 6; column++){
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
                    cout << "this" << endl;
                                        }
                
            } // end of inner for loop
        } // end of outer for loop
        
        for(int row = 0; row < 6; row++){
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
                    cout << "this2" << endl;
                    currentColumn2 = s;
                    currentRow2 = row;
                    is32 = true;
                }
                

            }// end of for loop
        }

        if(is32 == true){
            display_status();
            do{
                cout << "Enter the 3 pieces you would like to remove in order from LEFT to RIGHT, ex: "<< endl <<
                "1a 2a 3a" << endl << endl;
                getline(cin, input2);
                if(input2.length() == 8){
                    if(int(input2[0] - '1') == currentColumn2 - 2 && int(toupper(input2[1]) - 'A') == currentRow2 && input2[2] == ' ' &&
                    int(input2[3] - '1') == currentColumn2 - 1 && int(toupper(input2[4]) - 'A') == currentRow2 && input2[5] == ' ' &&
                    int(input2[6] - '1') == currentColumn2 && int(toupper(input2[7]) - 'A') == currentRow2){
                        valid2 = true;
                    }
                }
            }while(valid2 != true);
        }

    } // end of function

}