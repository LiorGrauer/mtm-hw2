#ifndef GAME_H
#define GAME_H

#include "./Auxiliaries.h"
#include "./Exceptions.h"
#include "./Character.h"
//needed?
#include "./Medic.h"
#include "./Soldier.h"
#include "./Sniper.h"
#include <memory>
#include <vector>

namespace mtm {

    /** Game class declaration*/
    class Game {
        private:
            int height;
            int width;
            std::vector<std::vector<std::shared_ptr<Character>>> board;

            /**
             * outOfBoard: check if recived GridPoint is in the board.
             *
             * @param coordinates - the coordinates of the checked grid point.
             *              *
             * @return
             *     true if the gridpoint is out of the board
             *     false if it is inside the board
             */
            bool outOfBoard (const GridPoint& coordinates) const;

        public:
            Game(int height, int width);
            ~Game() = default;
            Game(const Game& other);
            Game& operator=(const Game& other);

            /**
             * addCharacter: adds existing character to a board.
             *
             * @param coordinates - the coordinates of the checked grid point.
             * @param character   - shared pointer to the existing character.
             * 
             */
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

            /**
             * makeCharacter: creates a new character and returns shared pointer to the new character.
             *
             * @param type   - the character type.
             * @param team   - the character team.
             * @param health - the character health.
             * @param ammo   - the character ammo.
             * @param range  - the character range.
             * @param power  - the character power.
             * 
             * @return
             *     shared pointer to the character
             */
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                                            units_t health, units_t ammo, units_t range, units_t power);
            
            /**
             * move: creates a new character and returns shared pointer to the new character.
             *
             * @param src_coordinates   - the coordinates of the moving character.
             * @param dst_coordinates   - the coordinates of the location the character moves to.
             * 
             *  
             */
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            
            /**
             * attack: preformes an attack action on the board.
             *
             * @param src_coordinates   - the coordinates of the attacking character.
             * @param dst_coordinates   - the coordinates of the attacked location.
             * 
             */
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            
            /**
             * reload: creates a new character and returns shared pointer to the new character.
             *
             * @param coordinates   - the coordinates of character type.
             * 
             * @return
             *     shared pointer to the character
             *     false if it is inside the board
             */
            void reload(const GridPoint & coordinates);
            
            /**
             * printGameBoard: prints the board graphicly.
             *
             * @param os    - the ostream.
             * @param begin - pointer to the first char in the board string.
             * @param end   - pointer to the last char in the board string.
             * @param width - the width of the board.
             * 
             * @return
             *     shared pointer to the character
             *     false if it is inside the board
             */
            std::ostream& printGameBoard(std::ostream& os, const char* begin, 
                                         const char* end, unsigned int width) const;
            
            /**
             * operator<<: defines the print operator.
             *
             * @param os     - the ostream, so we can pass it to the printBoardGame function.
             * @param game   - the game that need to be printed.
             * 
             * @return
             *     the board print using the printGameBoard function
             */
            friend std::ostream& operator<<(std::ostream& os, const Game& game);
            
            /**
             * isOver: checks if the game is over.
             * 
             * @return
             *     true if one of the teams won.
             *     false if none of the team won.
             */
            bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif