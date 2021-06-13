#include "./Soldier.h"

namespace mtm{

    bool Soldier::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=SOLDIER_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    void Soldier::load(){
        ammo+=SOLDIER_AMMO_LOAD;
    }

    bool Soldier::checkAttack(GridPoint src_point, GridPoint dst_point,
                                bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
            return false;
        }
        if(ammo<SOLDIER_AMMO_ATTACK)
        {
            throw OutOfAmmo();
            return false;
        }
        if(src_point.col != dst_point.col || src_point.row != dst_point.row){
            throw IllegalTarget();
            return false;
        }
        return true;
    }

    units_t Soldier::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        double double_power = getPower();
        if(damage_point_team != getTeam()){
            if(dst_point==damage_point){
                ammo-=SOLDIER_AMMO_ATTACK;
                return getPower();
            } else {
                return ceil(double_power/SOLDIER_INCIDENTAL_DAMAGE_DIVIDER);
            }
        } else {
            return 0;
        }
    }
    
    units_t Soldier::getIncidentalDamageRange(){
        double double_range = getRange();
        return ceil(double_range/SOLDIER_INCIDENTAL_DAMAGE_RANGE_DIVIDER);
    }

    Character* Soldier::clone() const{
        return new Soldier(*this);
    }

}