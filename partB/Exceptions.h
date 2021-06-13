#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace mtm {
    class Exception: public std::exception {
        public:
            virtual const char* what() const noexcept; 
    };

    class IllegalArgument: public Exception {
        public:
            const char* what() const noexcept;
    };

    class IllegalCell: public Exception {
        public:
            const char* what() const noexcept;
    };

    class CellEmpty: public Exception {
        public:
            const char* what() const noexcept;
    };

    class MoveTooFar: public Exception {
        public:
            const char* what() const noexcept;
    };

    class CellOccupied: public Exception {
        public:
            const char* what() const noexcept;
    };

    class OutOfRange: public Exception {
        public:
            const char* what() const noexcept;
    };

    class OutOfAmmo: public Exception {
        public:
            const char* what() const noexcept;
    };

    class IllegalTarget: public Exception {
        public:
            const char* what() const noexcept;
    };
}

#endif