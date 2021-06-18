#ifndef SNIPER_H
#define SNIPER_H

#include "./Character.h"

namespace mtm{
    /** Soldier class consts declaration*/
    const int SNIPER_AMMO_PER_ATTACK = 1;
    const int SNIPER_AMMO_PER_LOAD = 2;
    const int SNIPER_MOVE_DISTANCE = 4;
    const int SNIPER_MINIMAL_RANGE_DIVIDER = 2;
    const int SNIPER_HITS_UNTIL_CRITICAL = 3;
    const int SNIPER_CRITICAL_MULTIPLIER = 2;

    /** Soldier class declaration*/
    class Sniper : public Character {
        private:
            int hits_counter;
        public:
            Sniper(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power), hits_counter(0) {};
            ~Sniper() = default;
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;
            void load() override;
            bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) override;
            units_t executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) override;
            Character* clone() const override;
            char returnCharacterLetter() const override;
    };
    
}

#endif