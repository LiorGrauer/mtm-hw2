#ifndef SNIPER_H
#define SNIPER_H

#include "./Character.h"

namespace mtm{
    /** Soldier class consts declaration*/
    const int SNIPER_AMMO_PER_ATTACK = 1;
    const int SNIPER_AMMO_PER_LOAD = 2;
    const int SNIPER_MOVE_DISTANCE = 4;
    const int SNIPER_MINIMAL_RANGE_DIVIDER = 2;
    const int SNIPER_HITS_UNTIL_CRITICAL = 3;
    const int SNIPER_CRITICAL_MULTIPLIER = 2;

    /** Soldier class declaration*/
    class Sniper : public Character {
        private:
            int hits_counter;
        public:
            Sniper(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power), hits_counter(0) {};
            ~Sniper() = default;

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
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;

            /** load: sniper executes load action. adds ammo according to the sniper ammo per load */
            void load() override;

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
             *     true if sniper in src_point can execute attack on dst_point 
             *     false if not
             */
            bool checkAttack(GridPoint src_point, GridPoint dst_point, bool occupied, Team dst_point_team) override;
            
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
            units_t executeAttack(GridPoint dst_point, GridPoint damage_point, Team damage_point_team) override;

             /**
             * clone: return copy of existing sniper.
             *
             * @return
             *     character pointer to copy of an existing sniper
             */
            Character* clone() const override;

            /**
             * returnCharacterLetter: return the print letter that signals sniper
             *
             * @return
             *     big case s if the sniper team is powerlifters
             *     lower case s if not
             */
            char returnCharacterLetter() const override;
    };
    
}

#endif