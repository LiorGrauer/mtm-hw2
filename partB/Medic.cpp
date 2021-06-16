#include "./Medic.h"

namespace mtm{

    bool Medic::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point) <= MEDIC_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    void Medic::load(){
        ammo += MEDIC_AMMO_LOAD;
    }

    bool Medic::checkAttack(GridPoint src_point, GridPoint dst_point, bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point) > getRange()){
            throw OutOfRange();
        }
        if((dst_point_team != getTeam()) && (ammo < MEDIC_AMMO_ATTACK))
        {
            throw OutOfAmmo();
        }
        if(!occupied || src_point == dst_point){
            throw IllegalTarget();
        }
        if(dst_point_team != getTeam()){
            ammo -= MEDIC_AMMO_ATTACK;
        }
        return true;
    }

    units_t Medic::executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(damage_point_team != getTeam()){
            return getPower();
        } else {
            return -getPower();
        }
    }

    Character* Medic::clone() const{
        return new Medic(*this);
    }

    char Medic::returnCharacterLetter() const{
        if(getTeam() == POWERLIFTERS){
            return 'M';
        } else {
            return 'm';
        }
    }
    
}