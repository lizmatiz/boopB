/**
 * @file boop.h
 * @author elizabeth hooton
 * @brief 
 * @version 0.1
 * @date 2023-04-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BOOP_H
#define BOOP_H

#include "game.h"
#include "spaces.h"

#include <iostream>

namespace main_savitch_14{

    class Boop:public game{

            public:
                static const int SIZE = 6; // size of board

                /**
                 * @brief displays the board
                 * 
                 */
                void display_status( ) const;

                /**
                 * @brief makes the player's move
                 * 
                 * @param move 
                 */
                void make_move(const std::string& move);

                /**
                 * @brief finds out if a move is legal
                 * 
                 * @param move the move in string form
                 * @return true a move is legal
                 * @return false a move is illegal
                 */
                bool is_legal(const std::string& move) const;

                /**
                 * @brief (re)starts the game
                 * 
                 */
                void restart( );
                
                /**
                 * @brief Checks to see if anyone has three cats in a row
                 * 
                 * @return true 
                 * @return false 
                 */
                bool is_game_over( ) const;

                /**
                 * @brief Checks to see if a player's any three pieces are in a row. If they are, the user is asked which ones they
                 * want to remove. It also checks if a user has all their pieces on the board. If they do, they are asked which one they would
                 * like to remove.
                 * 
                 */
                void check();

                /**
                 * @brief Checks all the spaces directly next to the places piece to see where they should be booped.
                 * 
                 * @param row row of the array
                 * @param column column of the array
                 */
                void boopThePieces(int row, int column);

                /**
                 * @brief Uses almost the same code from is_game_over, but it keeps track of who's cats are 3 in a row.
                 * It returns HUMAN, NEUTRAL, or COMPUTER, depending on who is winning
                 * 
                 * @return game::who 
                 */
                game::who winning( ) const;

                // STUB FUNCTIONS
                game* clone( ) const {return NULL;}
                void compute_moves(std::queue<std::string>& moves) const {}
                int evaluate( ) const{return 0;}

                

            protected:
                Spaces board[SIZE][SIZE]; // [row][column]

                int p1Kittens; // player 1's kittens
                int p1Cats; // player 1's cats

                int p2Kittens; // player 2's kittens
                int p2Cats; // player 2's cats

                who columnPerson; // these are all for the winning function when keeping track of
                who rowPerson; // who's cats are 3 in a row
                who diagonalPerson;
                who diagonalPerson2;
                who diagonalPerson3;
                who diagonalPerson4;
                who complete;
                
    };
    
}
#endif