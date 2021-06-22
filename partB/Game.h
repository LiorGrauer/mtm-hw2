#ifndef GAME_H
#define GAME_H

#include "./Auxiliaries.h"
#include "./Exceptions.h"
#include "./Character.h"
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
             *              
             * @return
             *     true if the gridpoint is out of the board
             *     false if it is inside the board
             */
            bool outOfBoard (const GridPoint& coordinates) const;

        public:

            /** Game default C'tor*/
            Game(int height, int width);

            /** Game default D'tor*/
            ~Game() = default;

            /** Game default Copy C'tor*/
            Game(const Game& other);

            /** Game default Assignment C'tor*/
            Game& operator=(const Game& other);

            /**
             * addCharacter: adds existing character to a board.
             *
             * @param coordinates - the coordinates of the checked grid point.
             * @param character   - shared pointer to the existing character.
             * 
             * @throws IllegalCell    - if src or dst is out of board.
             * @throws CellEmpty      - if there is no character in src.
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
             * 
             * @throws IllegalArgument - if health parameter is not a positive number
             *                           or if ammo, range or power are negative numbers
             */
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                                            units_t health, units_t ammo, units_t range, units_t power);
            
            /**
             * move: creates a new character and returns shared pointer to the new character.
             *
             * @param src_coordinates   - the coordinates of the moving character.
             * @param dst_coordinates   - the coordinates of the location the character moves to.
             * 
             * @throws IllegalCell    - if src or dst is out of board.
             * @throws CellEmpty      - if there is no character in src.
             * @throws MoveTooFar     - Character checkMove will throw if the distance from.
             *                          src to dst is bigger then the character move range.
             * @throws CellIsOccupied - if dst all ready contains a character.
             * 
             */
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            
            /**
             * attack: preformes an attack action on the board.
             *
             * @param src_coordinates   - the coordinates of the attacking character.
             * @param dst_coordinates   - the coordinates of the attacked location.
             * 
             * @throws IllegalCell   - if src or dst is out of board.
             * @throws CellEmpty     - if there is no character in src.
             * @throws OutOfRange    - Character checkAttack will throw if dst is not in the character range of attack.
             * @throws OutOfAmmo     - Character checkAttack will throw if the character 
             *                         does not have the ammo to preform attack.
             * @throws IllegalTarget - Character checkAttack will throw if the attack does not meet the character
             *                         conditions to preform the attck.
             * 
             */
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            
            /**
             * reload: creates a new character and returns shared pointer to the new character.
             *
             * @param coordinates   - the coordinates of character type.
             * 
             * 
             * @throws IllegalCell   - if src or dst is out of board.
             * @throws CellEmpty     - if there is no character in src.
             * 
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
             */
            std::ostream& printGameBoard(std::ostream& os, const char* begin, 
                                         const char* end, unsigned int width) const;
            
            /**
             * operator<<: defines the print operator.
             *             uppercase letter for Powerlifters and lower case for Crossfitters
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
             * 
             * @return if winningTeam is nullptr the function does not enter
             *         the winning team to the value of the pointer.
             *         if it's not null then the winning team Enum will be inserted to the pointer value
             */
            bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif