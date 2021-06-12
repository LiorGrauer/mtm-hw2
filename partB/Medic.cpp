#include "./Medic.h"

namespace mtm{

    bool Medic::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=MEDIC_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    void Medic::load(){
        ammo+=MEDIC_AMMO_LOAD;
    }

    bool Medic::checkAttack(GridPoint src_point, GridPoint dst_point,
                            bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
        }
        if((dst_point_team != getTeam()) && (ammo<MEDIC_AMMO_ATTACK))
        {
            throw OutOfAmmo();
        }
        if(!occupied){
            throw IllegalTarget();
        }
    }

    units_t Medic::attack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(dst_point==damage_point){
            if(damage_point_team != getTeam()){
                ammo-=MEDIC_AMMO_ATTACK;
                return getPower();
            } else {
                return -getPower();
            }
        } else {
            return 0;
        }
    }

    Character* Medic::clone() const{
        return new Medic(*this);
    }
    
}