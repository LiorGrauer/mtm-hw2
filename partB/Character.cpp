#include "./Medic.h"

namespace mtm{

    Character::Character(Team team, units_t health, units_t ammo, units_t range ,units_t power) :
                team(team), range(range), power(power), health(health), ammo(ammo) {}

    units_t Character::getRange() const{
        return range;
    }

    units_t Character::getPower() const{
        return power;
    }

    units_t Character::getHealth() const{
        return health;
    }

    Team Character::getTeam() const{
        return team;
    }

    void Character::changeHealth(int change){
        health -= change;
    }

    units_t Character::getIncidentalDamageRange(){
        return 0;
    }
    
}