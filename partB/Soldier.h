#ifndef SOLDIER_H
#define SOLDIER_H

#include "./Character.h"

namespace mtm{
    /** Soldier class consts declaration*/
    const int SOLDIER_AMMO_PER_ATTACK = 1;
    const int SOLDIER_AMMO_PER_LOAD = 3;
    const int SOLDIER_MOVE_DISTANCE = 3;
    const int SOLDIER_INCIDENTAL_DAMAGE_RANGE_DIVIDER = 3;
    const int SOLDIER_INCIDENTAL_DAMAGE_DIVIDER = 2;

    /** Soldier class declaration */
    class Soldier : public Character {
        public:

            /** Soldier C'tor*/
            Soldier(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power) {};

            /** Soldier default D'tor */
            ~Soldier() = default;

            /**
             * checkMove: check if the soldier can execute the move action.
             *
             * @param src_point - current position of the soldier on the board.
             * @param dst_point - wanted position of the soldier on the board.
             *
             * @return
             *     true if distance between src_point and dst_point is lower or equel to the soldier move distance
             *     false if bigger
             * 
             * @throws MoveTooFar - if the distance from src to dst is bigger then the SOLDIER_MOVE_DISTANCE.
             * 
             */
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;

            /** load: soldier executes load action. adds ammo according to the soldier ammo per load */
            void load() override;

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
             * 
             * @throws OutOfRange    - if dst is not in the soldier range.
             * @throws OutOfAmmo     - if the soldier does not have SOLDIER_AMMO_PER_ATTACK to preform attack. 
             * @throws IllegalTarget - if dst is not in the same col and not in the same row as src.
             * 
             */
            bool checkAttack(GridPoint src_point, GridPoint dst_point, bool occupied, Team dst_point_team) override;\

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
            units_t executeAttack(GridPoint dst_point, GridPoint damage_point, Team damage_point_team) override;


             /**
             * getIncidentalDamageRange: return the soldier incidental damage range.
             *
             * @return
             *     soldier incidental damage range, ceil(range/3)
             */
            units_t getIncidentalDamageRange() override;

            
            /**
             * clone: return copy of existing soldier.
             *
             * @return
             *     character pointer to copy of an existing soldier
             */
            Character* clone() const override;

            /**
             * returnCharacterLetter: return the print letter that signals soldier
             *
             * @return
             *     big case s if the soldier team is powerlifters
             *     lower case s if not
             */
            char returnCharacterLetter() const override;
    };
}

#endif