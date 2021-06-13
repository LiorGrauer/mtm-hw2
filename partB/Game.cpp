#include "./Game.h"

#define BOARD_AT(row,col)       \
                                \
    board.at(row).at(col)       \
                                \

namespace mtm {
    Game::Game(int height, int width) :
    height(height),
    width(width) {
        if (height < 1 || width < 1){
            throw IllegalArgument();
        }
        for (int i=0; i<height; i++){
            vector<std::shared_ptr<Character>> row_vector(width, nullptr);
            board.push_back(row_vector);
        }
    }

    Game::Game(const Game& other):
    height(other.height),
    width(other.width) {
        board = other.board;
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                if (BOARD_AT(i,j) != nullptr){
                    BOARD_AT(i,j) = std::shared_ptr<Character>(other.BOARD_AT(i,j)->clone());
                }
            }
        }
    }

    Game& Game::operator=(const Game& other){
        height = other.height;
        width = other.width;
        board = other.board;
        return *this;
    }

    bool Game::outOfBoard (const GridPoint& coordinates){
        return !(coordinates.col >= 0 && coordinates.row >= 0 &&
                coordinates.col < width && coordinates.row < height);
    }

    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){
        if (outOfBoard(coordinates)){
            throw IllegalCell();
        }
        if (BOARD_AT(coordinates.row,coordinates.col) != nullptr){
            throw CellOccupied();
        }
        BOARD_AT(coordinates.row,coordinates.col) = character;
    }

    std::shared_ptr<Character> Game::makeCharacter
                (CharacterType type, Team team, units_t health,
                 units_t ammo, units_t range, units_t power){
        if (health < 1 || ammo < 0 || range < 0 || power < 0){
            throw IllegalArgument();
        }
        std::shared_ptr<Character> new_character;
        switch (type) {
            case SOLDIER: 
                new_character = std::shared_ptr<Character>(new Soldier(team, health, ammo, range, power)); 
                break;
            case MEDIC: 
                new_character = std::shared_ptr<Character>(new Medic(team, health, ammo, range, power));
                break;
            case SNIPER: 
                new_character = std::shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
                break;
            default: 
                new_character = std::shared_ptr<Character>(nullptr);
        }
        return new_character;                                                  
    }

    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(outOfBoard(src_coordinates) || outOfBoard(dst_coordinates)){
            throw IllegalCell();
        }
        if(BOARD_AT(src_coordinates.row,src_coordinates.col) == nullptr){
            throw CellEmpty();
        }
        if(!(BOARD_AT(src_coordinates.row,src_coordinates.col)
            ->checkMove(src_coordinates,dst_coordinates))){
            throw MoveTooFar();
        }
        if (BOARD_AT(dst_coordinates.row,dst_coordinates.col) != nullptr){
            throw CellOccupied();
        }
        BOARD_AT(dst_coordinates.row,dst_coordinates.col) = 
            BOARD_AT(src_coordinates.row,src_coordinates.col);
        BOARD_AT(src_coordinates.row,src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(outOfBoard(src_coordinates) || outOfBoard(dst_coordinates)){
            throw IllegalCell();
        }
        if(BOARD_AT(src_coordinates.row,src_coordinates.col) == nullptr){
            throw CellEmpty();
        }
        bool occupied = BOARD_AT(dst_coordinates.row,dst_coordinates.col)
                        == nullptr ? false : true;
        if(!(BOARD_AT(src_coordinates.row,src_coordinates.col)->
            checkAttack(src_coordinates, dst_coordinates, occupied, (occupied)
                        ? BOARD_AT(dst_coordinates.row,dst_coordinates.col)->getTeam() : CROSSFITTERS))){
                        //if dst is not occupied the team dosent affect the function
            return;
        }
        int incidential_range = BOARD_AT(src_coordinates.row,src_coordinates.col)->
            getIncidentalDamageRange();
        for(int i=incidential_range; i>=-incidential_range; i--){
            for(int j=incidential_range; j>=-incidential_range; j--){
                if(outOfBoard(GridPoint(dst_coordinates.row+i,dst_coordinates.col+j))){
                    continue;
                }
                occupied = (BOARD_AT(dst_coordinates.row+i,dst_coordinates.col+j) == nullptr) ? false : true;
                if(occupied){
                    BOARD_AT(dst_coordinates.row+i,dst_coordinates.col+j)->
                    changeHealth(BOARD_AT(src_coordinates.row,src_coordinates.col)->
                    executeAttack(GridPoint(dst_coordinates.row,dst_coordinates.col),
                    GridPoint(dst_coordinates.row+i,dst_coordinates.col+j),
                    BOARD_AT(dst_coordinates.row+i,dst_coordinates.col+j)->getTeam()));
                    if(BOARD_AT(dst_coordinates.row+i,dst_coordinates.col+j)->getHealth()<1){
                        BOARD_AT(dst_coordinates.row+i,dst_coordinates.col+j) = nullptr;
                    }
                }
            }
        }
    }

    void Game::reload(const GridPoint & coordinates){
        if(outOfBoard(coordinates)){
            throw IllegalCell();
        }
        if(BOARD_AT(coordinates.row,coordinates.col) == nullptr){
            throw CellEmpty();
        }
        BOARD_AT(coordinates.row,coordinates.col)->load();
    }

    std::ostream& operator<<(std::ostream& os, const Game& game){
        std::string board_string;
        //char* board_string = new char[game.width*game.height];
        for (int i=0; i<game.height; i++){
            for (int j=0; j<game.width; j++){
                std::shared_ptr<Character> character = game.BOARD_AT(i,j);
                if (!character){
                    board_string += ' ';
                }
                else{
                    board_string += character->returnCharacterLetter();
                }
            }
        }
        const char* begin = board_string.c_str();
        const char* end = board_string.c_str()+(game.height*game.width);
        return printGameBoard(os, begin, end, game.width);
    }

    bool Game::isOver(Team* winningTeam) const{
        bool powerlifters = false;
        bool crossfitters = false;
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                if (BOARD_AT(i,j) != nullptr){
                    if (BOARD_AT(i,j)->getTeam() == POWERLIFTERS){
                        powerlifters = true;
                    }
                    else {
                        crossfitters = true;
                    }
                }
            }
        }
        if (powerlifters && !crossfitters){
            if (winningTeam){
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }
        else if (!powerlifters && crossfitters){
            if (winningTeam){
                *winningTeam = CROSSFITTERS;
            }
            return true;
        }
        return false;
    }
}