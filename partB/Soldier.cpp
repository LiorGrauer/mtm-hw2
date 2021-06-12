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
        if(ammo<1)
        {
            throw OutOfAmmo();
        }
        if(src_point.col != dst_point.col || src_point.row != dst_point.row){
            throw IllegalTarget();
        }
    }

    units_t Soldier::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        double double_power = getPower();
        if(damage_point_team != getTeam()){
            if(dst_point==damage_point){
                return getPower();
            } else {
                return ceil(double_power/2);
            }
        } else {
            return 0;
        }
    }
    
    units_t Soldier::getIncidentalDamageRange(){
        double double_range = getRange();
        return ceil(double_range/3);
    }

    Character* Soldier::clone() const{
        return new Soldier(*this);
    }

}