#include "./Medic.h"

namespace mtm{

    /**
     * checkMove: check if the medic can execute the move action.
     *
     * @param src_point - current position of the medic on the board.
     * @param dst_point - wanted position of the medic on the board.
     *
     * @return
     *     true if distance between src_point and dst_point is lower or equel to the medic move distance
     *     false if bigger
     */
    bool Medic::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point) <= MEDIC_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }
    /** load: medic executes load action. adds ammo according to the medic ammo per load */
    void Medic::load(){
        ammo += MEDIC_AMMO_PER_LOAD;
    }

    /**
     * checkAttack: check if the medic can execute the attack action.
     *
     * @param src_point     - current position of the medic on the board.
     * @param dst_point     - destanation point of the attack.
     * @param occupied      - bool variable that is true if dst_point contains character, false if null.
     * @param dst_point_team- the team of the character in the dst_point,
     *                        if dst_point is null the team opposite to the src_point character team.
     *
     * @return
     *     true if medic in src_point can execute attack on dst_point 
     *     false if not
     */
    bool Medic::checkAttack(GridPoint src_point, GridPoint dst_point, bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point) > getRange()){
            throw OutOfRange();
        }
        if((dst_point_team != getTeam()) && (ammo < MEDIC_AMMO_PER_ATTACK))
        {
            throw OutOfAmmo();
        }
        if(!occupied || src_point == dst_point){
            throw IllegalTarget();
        }
        if(dst_point_team != getTeam()){
            ammo -= MEDIC_AMMO_PER_ATTACK;
        }
        return true;
    }

    /**
     * executeAttack: return the damage the medic inflicts on the damage point.
     *
     * @param dst_point         - the position the attack is being executed upon
     * @param damage_point      - the position that the damaged character is currently in
     * @param damage_point_team - the team of the character in the damage_point
     *
     * @return
     *     medic power attacked character is on the oppsite team
     *     else medic power times -1 
     */
    units_t Medic::executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(damage_point_team != getTeam()){
            return getPower();
        } else {
            return -getPower();
        }
    }

    /**
     * clone: return copy of existing medic.
     *
     * @return
     *     character pointer to copy of an existing medic
     */
    Character* Medic::clone() const{
        return new Medic(*this);
    }

    /**
     * returnCharacterLetter: return the print letter that signals medic
     *
     * @return
     *     big case s if the medic team is powerlifters
     *     lower case s if not
     */
    char Medic::returnCharacterLetter() const{
        if(getTeam() == POWERLIFTERS){
            return 'M';
        } else {
            return 'm';
        }
    }
    
}