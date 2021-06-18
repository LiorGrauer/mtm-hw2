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
            Character(Team team, units_t health, units_t ammo, units_t range ,units_t power) :
                team(team), range(range), power(power), health(health), ammo(ammo) {};
            Character& operator=(const Character& character) = delete;
            Character(const Character& character) = default;
            virtual ~Character() = default;
            units_t getRange() const;
            units_t getPower() const;
            units_t getHealth() const;
            Team getTeam() const;
            void changeHealth(int change);
            virtual bool checkMove(GridPoint src_point, GridPoint dst_point) = 0;
            virtual void load() = 0;
            virtual bool checkAttack(GridPoint src_point, GridPoint dst_point,
                                    bool occupied, Team dst_point_team) = 0;
            virtual units_t getIncidentalDamageRange();
            virtual units_t executeAttack(GridPoint dst_point, GridPoint damage_point,
                                    Team damage_point_team) = 0;
            virtual Character* clone() const = 0;
            virtual char returnCharacterLetter() const = 0;
    };
    
}
#endif