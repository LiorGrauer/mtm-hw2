#include "./Medic.h"

namespace mtm{

    bool Medic::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=5){
            return true;
        } else {
            return false;
        }
    }

    void Medic::load(){
        ammo+=5;
    }

    bool Medic::checkAttack(GridPoint src_point, GridPoint dst_point,
                            bool occupied, Team dst_point_team){

    }

    units_t Medic::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){

    }
    
}