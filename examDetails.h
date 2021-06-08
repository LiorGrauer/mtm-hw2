#ifndef EXAMDETAILS_H
#define EXAMDETAILS_H
#include <iostream>
#include <fstream>

namespace mtm {
    class ExamDetails {
        int course_number, month, day, length;
        double hour; 
        std::string link;
        
        public:
            ExamDetails(int course_number, int month, int day, double hour, int length, std::string link = "");
            ~ExamDetails() = default;
            ExamDetails(const ExamDetails& exam);
            ExamDetails& operator=(const ExamDetails& exam);
            std::string getLink() const;
            void setLink(std::string link);
            int operator-(const ExamDetails& exam) const;
            bool operator<(const ExamDetails& exam) const;
            friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);
            static ExamDetails makeMatamExam();

            class InvalidDateException {};
            class InvalidTimeException {};
            class InvalidArgsException {};
    }; 
}

#endif
