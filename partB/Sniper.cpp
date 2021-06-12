#include "./Sniper.h"

namespace mtm{

    bool Sniper::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=4){
            return true;
        } else {
            return false;
        }
    }

    void Sniper::load(){
        ammo+=2;
    }

    bool Sniper::checkAttack(GridPoint src_point, GridPoint dst_point,
                            bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
        }
        if(ammo<1)
        {
            throw OutOfAmmo();
        }
        if((!occupied) || (dst_point_team == getTeam())){
            throw IllegalTarget();
        }
        double double_range = getRange();
    }

    units_t Sniper::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(dst_point==damage_point){
            return getPower();
        } else {
            return 0;
        }
    }

    Character* Sniper::clone() const{
        return new Sniper(*this);
    }

}