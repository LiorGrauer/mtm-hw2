#ifndef MEDIC_H
#define MEDIC_H

#include "./Character.h"
#include "./Auxiliaries.h"
#include "./Exceptions.h"

namespace mtm{

    const int MEDIC_AMMO_ATTACK = 1;
    const int MEDIC_AMMO_LOAD = 5;
    const int MEDIC_MOVE_DISTANCE = 5;

    class Medic : public Character {
        public:
            Medic(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power) {}
            ~Medic() {};
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;
            void load() override;
            bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) override;
            units_t attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) override;
            Character* clone() const override;
            char returnCharacterLetter() const override;
    };
    
}

#endif