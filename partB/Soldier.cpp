#include "./Soldier.h"

namespace mtm{

    /**
     * chessAddTournament: add a new tournament to a chess system.
     *
     * @param chess - chess system to add the tournament to. Must be non-NULL.
     * @param tournament_id - new tournament id. Must be positive, and unique.
     * @param max_games_per_player - maximum number of games a player is allow to play in the specified tournament.
     *                               Must be postivie/
     * @param tournament_location - location in which the tournament take place. Must be non-empty.
     *
     * @return
     *     CHESS_NULL_ARGUMENT - if chess/tournament_location are NULL.
     *     CHESS_INVALID_ID - the tournament ID number is invalid.
     *     CHESS_TOURNAMENT_ALREADY_EXISTS - if a tournament with the given id already exist.
     *     CHESS_INVALID_LOCATION - if the name is empty or doesn't start with a capital letter (A -Z)
     *                      followed by small letters (a -z) and spaces (' ').
     *     CHESS_INVALID_MAX_GAMES - if the maximum number of games allowed is not positive
     *     CHESS_SUCCESS - if tournament was added successfully.
     */
    bool Soldier::checkMove(GridPoint src_point, GridPoint dst_point) {
        if(GridPoint::distance(src_point,dst_point) <= SOLDIER_MOVE_DISTANCE){
            return true;
        } else {
            return false;
        }
    }

    void Soldier::load(){
        ammo += SOLDIER_AMMO_LOAD;
    }

    bool Soldier::checkAttack(GridPoint src_point, GridPoint dst_point,
                                bool occupied, Team dst_point_team){
        if(GridPoint::distance(src_point,dst_point)>getRange()){
            throw OutOfRange();
        }
        if(ammo < SOLDIER_AMMO_ATTACK)
        {
            throw OutOfAmmo();
        }
        if(src_point.col != dst_point.col && src_point.row != dst_point.row){
            throw IllegalTarget();
        }
        ammo -= SOLDIER_AMMO_ATTACK;
        return true;
    }

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
    
    units_t Soldier::getIncidentalDamageRange(){
        double double_range = getRange();
        return ceil(double_range/SOLDIER_INCIDENTAL_DAMAGE_RANGE_DIVIDER);
    }

    Character* Soldier::clone() const{
        return new Soldier(*this);
    }

    char Soldier::returnCharacterLetter() const{
        if(getTeam() == POWERLIFTERS){
            return 'S';
        } else {
            return 's';
        }
    }

}