#ifndef CHARACTER_H
#define CHARACTER_H

#include "./Auxiliaries.h"
#include "./Exceptions.h"

namespace mtm{
    /** Character class declaration*/
    class Character{
        private:    //does not change during game
            Team team;
            units_t range, power;
        
        protected:  //does change during game
            units_t health, ammo;

        public:
            Character(Team team, units_t health, units_t ammo, units_t range ,units_t power);
            Character& operator=(const Character& character) = delete;
            Character(const Character& character) = default;

            /** D'tor: virtual function that the specific Character type will override*/
            virtual ~Character() = default;

            /**
             * getRange: return character range
             * 
             * @return
             *     character range
             */
            units_t getRange() const;

            /**
             * getPower: return character power
             * 
             * @return
             *     character power
             */
            units_t getPower() const;

            /**
             * getHealth: return character health
             * 
             * @return
             *     character health
             */
            units_t getHealth() const;

            /**
             * getTeam: return character team
             * 
             * @return
             *     character team
             */
            Team getTeam() const;

            /**
             * changeHealth: deductes character range
             * 
             * @param change- int. given number that need to be deducted from the character current health
             *                     (if heal, negetive number)
             */
            void changeHealth(int change);

            /** checkMove: virtual function that the specific Character type will override*/
            virtual bool checkMove(GridPoint src_point, GridPoint dst_point) = 0;

            /** load: virtual function that the specific Character type will override*/
            virtual void load() = 0;

            /** checkAttack: virtual function that the specific Character type will override*/
            virtual bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) = 0;

            /**
             * getIncidentalDamageRange: return character incidental damage range.
             *                           returns default 0 for sniper and medic, 
             *                           for soldier override and return ceil(power/2).
             * 
             * @return
             *     character incidental damage range depends on character class
             */
            virtual units_t getIncidentalDamageRange();

            /** executeAttack: virtual function that the specific Character type will override*/
            virtual units_t executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) = 0;

            /** clone: virtual function that the specific Character type will override*/
            virtual Character* clone() const = 0;

            /** returnCharacterLetter: virtual function that the specific Character type will override*/
            virtual char returnCharacterLetter() const = 0;
    };
    
}
#endif