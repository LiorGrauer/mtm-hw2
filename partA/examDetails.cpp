#include <iostream>
#include <fstream>

#include "examDetails.h"

using std::string;
using std::ostream;

namespace mtm {
    ExamDetails::ExamDetails(int course_number, int month, int day, double hour, int length, string link):
        course_number(course_number), 
        month(month), 
        day(day), 
        length(length),
        hour(hour), 
        link(link) {
        if (course_number < 1){
            throw ExamDetails::InvalidArgsException();
        }
        if (month < 1 || month > 12){
            throw ExamDetails::InvalidDateException();
        }
        if (day < 1 || day > 30){
            throw ExamDetails::InvalidDateException();
        }
        double diff = (hour - (int)hour);
        if ((diff > 1e-6 && diff < (0.5 - 1e-6)) || (diff > (0.5 + 1e-6) && diff < (1 - 1e-6)) || 
            hour < -1e-6 || (hour - 24.5) > 1e-6){
            throw ExamDetails::InvalidTimeException();
        }
    }

    ExamDetails::ExamDetails(const ExamDetails& exam):
        course_number(exam.course_number), 
        month(exam.month), 
        day(exam.day), 
        length(exam.length),
        hour(exam.hour), 
        link(exam.link) {
    }

    ExamDetails& ExamDetails::operator=(const ExamDetails& exam) {
        if (this == &exam) {
            return *this;
        }
        course_number = exam.course_number;
        month = exam.month; 
        day = exam.day;
        hour = exam.hour; 
        length = exam.length;
        link = exam.link; 
        return *this;
    }

    string ExamDetails::getLink() const{
        return link;
    }

    void ExamDetails::setLink(string link){
        this->link = link;
    }

    int ExamDetails::operator-(const ExamDetails& exam) const{
        return 30*(month - exam.month) + (day - exam.day);  
    }

    bool ExamDetails::operator<(const ExamDetails& exam) const{
        return (month < exam.month) || (month == exam.month && day < exam.day);
    }

    ostream& operator<<(ostream& os, const ExamDetails& exam){
        return (os << "Course Number: " << exam.course_number << std::endl << "Time: " << exam.day << "." << exam.month
                << " at " << (int)exam.hour << ":" << 
                (((exam.hour - (int)exam.hour < 1e-6) || (exam.hour - (int)exam.hour > (1 - 1e-6)))? "00" : "30") << 
                std::endl << "Duration: " << exam.length << ":00" << std::endl << "Zoom Link: " << 
                exam.link << std::endl);
    }

    ExamDetails ExamDetails::makeMatamExam(){
        ExamDetails mtm_exam(234124, 7, 28, 13.0, 3, "https://tinyurl.com/59hzps6m");
        return mtm_exam;
    }
}
