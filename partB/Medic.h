#ifndef MEDIC_H
#define MEDIC_H

#include "./Character.h"

namespace mtm{
    /** Medic class consts declaration*/
    const int MEDIC_AMMO_PER_ATTACK = 1;
    const int MEDIC_AMMO_PER_LOAD = 5;
    const int MEDIC_MOVE_DISTANCE = 5;

    /** Medic class declaration*/
    class Medic : public Character {
        public:

            /** Medic C'tor */
            Medic(Team team, units_t health, units_t ammo, units_t range,units_t power) :
                Character(team, health, ammo, range, power) {};

            /** Medic default D'tor */
            ~Medic() = default;

            /**
             * checkMove: check if the medic can execute the move action.
             *
             * @param src_point - current position of the medic on the board.
             * @param dst_point - wanted position of the medic on the board.
             *
             * @return
             *     true if distance between src_point and dst_point is lower or equel to the medic move distance
             *     false if bigger
             * 
             * @throws MoveTooFar - if the distance from src to dst is bigger then the MEDIC_MOVE_DISTANCE.
             */
            bool checkMove(GridPoint src_point, GridPoint dst_point) override;
            
            /** load: medic executes load action. adds ammo according to the medic ammo per load */
            void load() override;

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
             * 
             * @throws OutOfRange    - if dst is not in the medic range of attack.
             * @throws OutOfAmmo     - if the medic does not have the ammo to preform attack. 
             *                         if it is an enemy he needs MEDIC_AMMO_PER_ATTACK and if it is a friend
             *                         then he dosen't need ammo to heal.
             * @throws IllegalTarget - if dst is empty.
             * 
             */
            bool checkAttack(GridPoint src_point, GridPoint dst_point, bool occupied, Team dst_point_team) override;
            
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
            units_t executeAttack(GridPoint dst_point, GridPoint damage_point, Team damage_point_team) override;

            /**
             * clone: return copy of existing medic.
             *
             * @return
             *     character pointer to copy of an existing medic
             */
            Character* clone() const override;

             /**
             * returnCharacterLetter: return the print letter that signals medic
             *
             * @return
             *     big case s if the medic team is powerlifters
             *     lower case s if not
             */
            char returnCharacterLetter() const override;
    };
    
}

#endif