#ifndef CHARACTER_H
#define CHARACTER_H

class Character{
    private:

    public:
        virtual checkMove;
        virtual load;
        virtual checkAttack;
        virtual checkIncidentalDamageRange;
        virtual attack;

    protected:
        int health, ammo, range, power;


};

#endif