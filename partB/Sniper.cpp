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

    }

    units_t Sniper::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){

    }

}