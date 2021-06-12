#include "./Game.h";

namespace mtm {
    Game::Game(int height, int width) :
    height(height),
    width(width) {
        if (height < 1 || width < 1){
            throw IllegalArgument();
        }
        board.resize(height);
        for (vector<std::shared_ptr<Character>> row : board){
            row.assign(width, nullptr);
        }
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
        if (board.at(coordinates.row).at(coordinates.col) != nullptr){
            throw CellOccupied();
        }
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, 
                                                    units_t health, units_t ammo, units_t range, units_t power){
        if (health < 1 || ammo < 0 || range < 0 || power < 0){
            throw IllegalArgument();
        }
                                                                
    }

    void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){

    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){

    }

    void Game::reload(const GridPoint & coordinates){

    }

    std::ostream& Game::printGameBoard(std::ostream& os, const char* begin, 
                                    const char* end, unsigned int width) const{

    }

    bool Game::isOver(Team* winningTeam=NULL) const{

    }
}