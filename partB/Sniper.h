#ifndef SNIPER_H
#define SNIPER_H

#include "./Character.h"
#include "./Auxiliaries.h"
#include "./Exceptions.h"

namespace mtm{

    class Sniper : public Character {
        public:
            Sniper(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power) {}
            virtual ~Sniper() {};
            virtual bool checkMove(GridPoint src_point, GridPoint dst_point) override;
            virtual void load() override;
            virtual bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) override;
            virtual units_t attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) override;
    };
    
}

#endif