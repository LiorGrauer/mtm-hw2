#include "./Soldier.h"

namespace mtm{

    /**
     * checkMove: check if the soldier can execute the move action.
     *
     * @param src_point - current position of the soldier on the board.
     * @param dst_point - wanted position of the soldier on the board.
     *
     * @return
     *     true if distance between src_point and dst_point is lower or equel to the soldier move distance
     *     false if bigger
     */
    bool Soldier::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point) <= SOLDIER_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    /** load: soldier executes load action. adds ammo according to the soldier ammo per load */
    void Soldier::load(){
        ammo += SOLDIER_AMMO_PER_LOAD;
    }

    /**
     * checkAttack: check if the soldier can execute the attack action.
     *
     * @param src_point     - current position of the soldier on the board.
     * @param dst_point     - destanation point of the attack.
     * @param occupied      - bool variable that is true if dst_point contains character, false if null.
     * @param dst_point_team- the team of the character in the dst_point,
     *                        if dst_point is null the team opposite to the src_point character team.
     *
     * @return
     *     true if soldier in src_point can execute attack on dst_point 
     *     false if not
     */
    bool Soldier::checkAttack(GridPoint src_point, GridPoint dst_point,
                                bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
        }
        if(ammo < SOLDIER_AMMO_PER_ATTACK)
        {
            throw OutOfAmmo();
        }
        if(src_point.col != dst_point.col && src_point.row != dst_point.row){
            throw IllegalTarget();
        }
        ammo -= SOLDIER_AMMO_PER_ATTACK;
        return true;
    }

    /**
     * executeAttack: return the damage the soldier inflicts on the damage point.
     *
     * @param dst_point         - the position the attack is being executed upon
     * @param damage_point      - the position that the damaged character is currently in
     * @param damage_point_team - the team of the character in the damage_point
     *
     * @return
     *     soldier power if the damage point is the same as the dst_point
     *     if the damage point is not the same as the dst_point then return ceil(power/2)
     */
    units_t Soldier::executeAttack(GridPoint dst_point, GridPoint damage_point, Team damage_point_team){
        double double_power = getPower();
        if(damage_point_team != getTeam()){
            if(dst_point == damage_point){
                return getPower();
            } else {
                return ceil(double_power/SOLDIER_INCIDENTAL_DAMAGE_DIVIDER);
            }
        } else {
            return 0;
        }
    }
    
    /**
     * getIncidentalDamageRange: return the soldier incidental damage range.
     *
     * @return
     *     soldier incidental damage range, ceil(range/3)
     */
    units_t Soldier::getIncidentalDamageRange(){
        double double_range = getRange();
        return ceil(double_range/SOLDIER_INCIDENTAL_DAMAGE_RANGE_DIVIDER);
    }

    /**
     * clone: return copy of existing soldier.
     *
     * @return
     *     character pointer to copy of an existing soldier
     */
    Character* Soldier::clone() const{
        return new Soldier(*this);
    }

    /**
     * returnCharacterLetter: return the print letter that signals soldier
     *
     * @return
     *     big case s if the soldier team is powerlifters
     *     lower case s if not
     */
    char Soldier::returnCharacterLetter() const{
        if(getTeam() == POWERLIFTERS){
            return 'S';
        } else {
            return 's';
        }
    }

}