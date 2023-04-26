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

                game* clone( ) const {}
                void compute_moves(std::queue<std::string>& moves) const {}
                int evaluate( ) const {}
                bool is_game_over( ) const;

                void check();

                

            protected:
                Spaces board[SIZE][SIZE]; // [row][column]
                int moves; // number of moves

                int p1Kittens; // player 1's kittens
                int p1Cats; // player 1's cats

                int p2Kittens; // player 2's kittens
                int p2Cats; // player 2's cats
                
    };
    
}
#endif