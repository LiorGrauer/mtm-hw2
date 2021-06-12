#include "./Soldier.h"

namespace mtm{

    bool Soldier::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=3){
            return true;
        } else {
            return false;
        }
    }

    void Soldier::load(){
        ammo+=3;
    }

    bool Soldier::checkAttack(GridPoint src_point, GridPoint dst_point,
                                bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
        }
        if(ammo)
        {
            /* code */
        }
        
    }

    units_t Soldier::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){

    }
    
    units_t Soldier::getIncidentalDamageRange(){
        double double_range = getRange();
        return (ceil(double_range/3));
    }

}