#ifndef SOLDIER_H
#define SOLDIER_H

#include "./Character.h"

namespace mtm{

    const int SOLDIER_AMMO_ATTACK = 1;
    const int SOLDIER_AMMO_LOAD = 3;
    const int SOLDIER_MOVE_DISTANCE = 3;
    const int SOLDIER_INCIDENTAL_DAMAGE_RANGE_DIVIDER = 3;
    const int SOLDIER_INCIDENTAL_DAMAGE_DIVIDER = 2;

    class Soldier : public Character {
        public:
            Soldier(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power) {}
            ~Soldier() {};
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;
            void load() override;
            bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) override;
            units_t getIncidentalDamageRange() override;
            units_t executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) override;
            Character* clone() const override;
            char returnCharacterLetter() const override;
    };
    
}

#endif