#include "./Game.h"

namespace mtm {
    Game::Game(int height, int width) :
    height(height),
    width(width) {
        if (height < 1 || width < 1){
            throw IllegalArgument();
        }
        //board.resize(height);
        for (int i=0; i<height; i++){
            vector<std::shared_ptr<Character>> row_vector(width, nullptr);
            board.push_back(row_vector);
        }
        /*for (vector<std::shared_ptr<Character>> row : board){
            row.resize(width, nullptr);
        }*/
    }

    Game::Game(const Game& other){
        Game new_game(other.height, other.width);
        board = other.board;
        //to check if copies successfully or needed to use clone() on every character
    }

    Game& Game::operator=(const Game& other){
        height = other.height;
        width = other.width;
        board = other.board;
        return *this;
    }

    bool Game::outOfBoard (const GridPoint& coordinates){
        return !(coordinates.col >= 0 && coordinates.row >= 0 && coordinates.col < width && coordinates.row < height);
    }

    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){
        if (outOfBoard(coordinates)){
            throw IllegalCell();
        }
        if (board.at(coordinates.row-1).at(coordinates.col-1) != nullptr){
            throw CellOccupied();
        }
        board.at(coordinates.row-1).at(coordinates.col-1) = character;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, 
                                                    units_t health, units_t ammo, units_t range, units_t power){
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
        if(board.at(src_coordinates.row).at(src_coordinates.col) == nullptr){
            throw CellEmpty();
        }
        if(!(board.at(src_coordinates.row).at(src_coordinates.col)
            ->checkMove(src_coordinates,dst_coordinates))){
            throw MoveTooFar();
        }
        if (board.at(dst_coordinates.row).at(dst_coordinates.col) != nullptr){
            throw CellOccupied();
        }
        board.at(dst_coordinates.row).at(dst_coordinates.col) = 
            board.at(src_coordinates.row).at(src_coordinates.col);
        board.at(src_coordinates.row).at(src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
        if(outOfBoard(src_coordinates) || outOfBoard(dst_coordinates)){
            throw IllegalCell();
        }
        if(board.at(src_coordinates.row).at(src_coordinates.col) == nullptr){
            throw CellEmpty();
        }
        bool occupied = board.at(dst_coordinates.row).at(dst_coordinates.col)
                        == nullptr ? false : true;
        if(!(board.at(src_coordinates.row).at(src_coordinates.col)->
            checkAttack(src_coordinates,dst_coordinates,
            occupied, (occupied) ?
            board.at(dst_coordinates.row).at(dst_coordinates.col)->getTeam()
             : CROSSFITTERS))){ //if dst is not occupied the team dosent affect the function
            return;
        }
        int incidential_range = board.at(src_coordinates.row).at(src_coordinates.col)->
            getIncidentalDamageRange();
        for(int i=incidential_range; i>=-incidential_range; i--){
            for(int j=incidential_range; j>=-incidential_range; j--){
                if(outOfBoard(GridPoint(dst_coordinates.row+i,dst_coordinates.col+j))){
                    continue;
                }
                occupied = board.at(dst_coordinates.row).at(dst_coordinates.col)
                        == nullptr ? false : true;
                if(occupied){
                board.at(dst_coordinates.row+i).at(dst_coordinates.col+j)->
                    changeHealth(board.at(src_coordinates.row+i).at(src_coordinates.col+j)->
                    attack(GridPoint(dst_coordinates.row,dst_coordinates.col),
                    GridPoint(dst_coordinates.row+i,dst_coordinates.col+j),
                    board.at(dst_coordinates.row+i).at(dst_coordinates.col+j)->getTeam()));
                    if(board.at(dst_coordinates.row+i).at(dst_coordinates.col+j)->getHealth()<1){
                        board.at(dst_coordinates.row+i).at(dst_coordinates.col+j) = nullptr;
                    }
                }
            }
        }
    }

    void Game::reload(const GridPoint & coordinates){
        if(outOfBoard(coordinates)){
            throw IllegalCell();
        }
        if(board.at(coordinates.row).at(coordinates.col) == nullptr){
            throw CellEmpty();
        }
        board.at(coordinates.row).at(coordinates.col)->load();
    }

    std::ostream& operator<<(std::ostream& os, const Game& game){
        char* board_string[game.width*game.height];
        for (int i=0; i<game.height; i++){
            for (int j=0; j<game.width; j++){
                std::shared_ptr<Character> character = game.board.at(i).at(j);
                if (!character){
                    board_string[i][j] = ' ';
                }
                else{
                    std::string character_type = typeid(*character).name();
                    if (character_type == "Soldier"){
                        if (character->getTeam() == POWERLIFTERS) {
                            board_string[i][j] = 'S';
                        }
                        else {
                            board_string[i][j] = 's';
                        }
                    }
                    else if (character_type == "Medic"){
                        if (character->getTeam() == POWERLIFTERS) {
                            board_string[i][j] = 'M';
                        }
                        else {
                            board_string[i][j] = 'm';
                        }
                    }
                    else if (character_type == "Sniper"){
                        if (character->getTeam() == POWERLIFTERS) {
                            board_string[i][j] = 'S';
                        }
                        else {
                            board_string[i][j] = 's';
                        }
                    }
                }
            }
        }
        const char* begin = *board_string;
        //what should i assign in end?
        const char* end = nullptr;
        return printGameBoard(os, begin, end, game.width);
    }

    bool Game::isOver(Team* winningTeam) const{
        bool powerlifters = false;
        bool crossfitters = false;
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
                if (board.at(i).at(j) != nullptr){
                    if (board.at(i).at(j)->getTeam() == POWERLIFTERS){
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