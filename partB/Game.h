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
            bool outOfBoard (const GridPoint& coordinates) const;

        public:
            Game(int height, int width);
            ~Game() = default;
            Game(const Game& other);
            Game& operator=(const Game& other);
            void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
            static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                                                            units_t health, units_t ammo, units_t range, units_t power);
            void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
            void reload(const GridPoint & coordinates);
            std::ostream& printGameBoard(std::ostream& os, const char* begin, 
                                         const char* end, unsigned int width) const;
            friend std::ostream& operator<<(std::ostream& os, const Game& game);
            bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif