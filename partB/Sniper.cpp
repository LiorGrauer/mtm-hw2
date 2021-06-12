#include "./Sniper.h"

namespace mtm{

    bool Sniper::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=SNIPER_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    void Sniper::load(){
        ammo+=SNIPER_AMMO_LOAD;
    }

    bool Sniper::checkAttack(GridPoint src_point, GridPoint dst_point,
                            bool occupied, Team dst_point_team){
        double double_range = getRange();
        if((GridPoint::distance(src_point,dst_point)>getRange()) ||
            (GridPoint::distance(src_point,dst_point)
            <ceil(double_range/SNIPER_MINIMAL_RANGE_DIVIDER))){
            throw OutOfRange();
        }
        if(ammo<SNIPER_AMMO_ATTACK)
        {
            throw OutOfAmmo();
        }
        if((!occupied) || (dst_point_team == getTeam())){
            throw IllegalTarget();
        }
    }

    units_t Sniper::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(dst_point==damage_point){
            ammo-=SNIPER_AMMO_ATTACK;
            return getPower();
        } else {
            return 0;
        }
    }

    Character* Sniper::clone() const{
        return new Sniper(*this);
    }

}