#include "Exceptions.h"
#include <string>


namespace mtm {
    const char* IllegalArgument::what() const{
        return "A game related error has occurred: IllegalArgument";
    }

    const char* IllegalCell::what() const{
        return "A game related error has occurred: IllegalCell";
    }

    const char* CellEmpty::what() const{
        return "A game related error has occurred: CellEmpty";
    }

    const char* MoveTooFar::what() const{
        return "A game related error has occurred: MoveTooFar";
    }

    const char* CellOccupied::what() const{
        return "A game related error has occurred: CellOccupied";
    }

    const char* OutOfRange::what() const{
        return "A game related error has occurred: OutOfRange";
    }

    const char* OutOfAmmo::what() const{
        return "A game related error has occurred: OutOfAmmo";
    }

    const char* IllegalTarget::what() const{
        return "A game related error has occurred: IllegalTarget";
    }
}