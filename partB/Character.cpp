#include "./Medic.h"

namespace mtm{

    /**
     * getRange: return character range
     * 
     * @return
     *     character range
     */
    units_t Character::getRange() const{
        return range;
    };

    /**
     * getPower: return character power
     * 
     * @return
     *     character power
     */
    units_t Character::getPower() const{
        return power;
    };

    /**
     * getHealth: return character health
     * 
     * @return
     *     character health
     */
    units_t Character::getHealth() const{
        return health;
    };

    /**
     * getTeam: return character team
     * 
     * @return
     *     character team
     */
    Team Character::getTeam() const{
        return team;
    };

    /**
     * changeHealth: deductes character range
     * 
     * @param change- int. given number that need to be deducted from the character current health
     *                     (if heal, negetive number)
     */
    void Character::changeHealth(int change){
        health -= change;
    };

    /**
     * getIncidentalDamageRange: return character incidental damage range.
     *                           return 0 for sniper and medic, for soldier return ceil(power/2).
     * 
     * @return
     *     character incidental damage range depends on character class
     */
    units_t Character::getIncidentalDamageRange(){
        return 0;
    };
    
}