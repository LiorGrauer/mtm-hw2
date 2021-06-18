#include "./Sniper.h"

namespace mtm{

    /**
     * checkMove: check if the sniper can execute the move action.
     *
     * @param src_point - current position of the sniper on the board.
     * @param dst_point - wanted position of the sniper on the board.
     *
     * @return
     *     true if distance between src_point and dst_point is lower or equel to the sniper move distance
     *     false if bigger
     */
    bool Sniper::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point)<=SNIPER_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

     /** load: sniper executes load action. adds ammo according to the sniper ammo per load */
    void Sniper::load(){
        ammo += SNIPER_AMMO_PER_LOAD;
    }

    /**
     * checkAttack: check if the sniper can execute the attack action.
     *
     * @param src_point     - current position of the sniper on the board.
     * @param dst_point     - destanation point of the attack.
     * @param occupied      - bool variable that is true if dst_point contains character, false if null.
     * @param dst_point_team- the team of the character in the dst_point,
     *                        if dst_point is null the team opposite to the src_point character team.
     *
     * @return
     *     true if sniper in src_point can attack dst_point 
     *     false if not
     */
    bool Sniper::checkAttack(GridPoint src_point, GridPoint dst_point,
                            bool occupied, Team dst_point_team){
        double double_range = getRange();
        if((GridPoint::distance(src_point,dst_point) > getRange()) ||
            (GridPoint::distance(src_point,dst_point) < ceil(double_range/SNIPER_MINIMAL_RANGE_DIVIDER))){
            throw OutOfRange();
        }
        if(ammo < SNIPER_AMMO_PER_ATTACK)
        {
            throw OutOfAmmo();
        }
        if((!occupied) || (dst_point_team == getTeam())){
            throw IllegalTarget();
        }
        ammo -= SNIPER_AMMO_PER_ATTACK;
        hits_counter++;
        return true;
    }

    /**
     * executeAttack: return the damage the sniper inflicts on the damage point.
     *
     * @param dst_point         - the position the attack is being executed upon
     * @param damage_point      - the position that the damaged character is currently in
     * @param damage_point_team - the team of the character in the damage_point
     *
     * @return
     *     sniper power times 2 each thrid succesfull attack, else sniper power
     */
    units_t Sniper::executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team){
        if(hits_counter % SNIPER_HITS_UNTIL_CRITICAL == 0){
            return SNIPER_CRITICAL_MULTIPLIER*getPower();
        }
        return getPower();
    }

    /**
     * clone: return copy of existing sniper.
     *
     * @return
     *     character pointer to copy of an existing sniper
     */
    Character* Sniper::clone() const{
        return new Sniper(*this);
    }

    /**
     * returnCharacterLetter: return the print letter that signals sniper
     *
     * @return
     *     big case s if the sniper team is powerlifters
     *     lower case s if not
     */
    char Sniper::returnCharacterLetter() const {
        if(getTeam() == POWERLIFTERS){
            return 'N';
        } else {
            return 'n';
        }
    }

}