#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace mtm {
    class Exception: public std::exception {
    };
    
    // IllegalArgument - in case the user sends illegal argument to function
    class IllegalArgument: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // IllegalCell - in case of trying to access cell outside the board
    class IllegalCell: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // CellEmpty - in case of trying to make action from empty cell on the board
    class CellEmpty: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // MoveTooFar - in case of trying to move character outside their move range
    class MoveTooFar: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // CellOccupied - in case of trying to move character to cell which is not empty
    class CellOccupied: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // OutOfRange - in case of trying to attack with character outside their attack range  
    class OutOfRange: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // OutOfAmmo - in case of character left without enough emmo to attack
    class OutOfAmmo: public Exception {
        public:
            const char* what() const noexcept override;
    };

    // IllegalTarget - in case character cant make the attack according to the character abillities
    class IllegalTarget: public Exception {
        public:
            const char* what() const noexcept override;
    };
}

#endif