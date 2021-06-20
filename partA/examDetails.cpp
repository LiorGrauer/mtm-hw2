#include <iostream>
#include <fstream>

#include "examDetails.h"

using std::string;
using std::ostream;

namespace mtm {
    const int MONTH_IN_YEAR = 12;
    const int DAYS_IN_MONTH = 30;
    const int HOURS_IN_DAY = 24;
    const double HALF_HOUR = 0.5;
    const double DOUBLE_MARGIN_OF_ERROR = 1e-6; 
    const int MATAM_COURSE_NUMBER = 234124;
    const int MATAM_EXAM_MONTH = 7;
    const int MATAM_EXAM_DAY = 28;
    const double MATAM_EXAM_HOUR = 13.0;
    const int MATAM_EXAM_LENGTH = 3;
    const std::string MATAM_ZOOM_LINK = "https://tinyurl.com/59hzps6m";

    ExamDetails::ExamDetails(int course_number, int month, int day, double hour, int length, string link):
        course_number(course_number), 
        month(month), 
        day(day), 
        length(length),
        hour(hour), 
        link(link) {
        if (month < 1 || month > MONTH_IN_YEAR){
            throw ExamDetails::InvalidDateException();
        }
        if (day < 1 || day > DAYS_IN_MONTH){
            throw ExamDetails::InvalidDateException();
        }
        double diff = (hour - (int)hour);
        //checks if hour is round hour or half hour
        if ((diff > DOUBLE_MARGIN_OF_ERROR && diff < (HALF_HOUR - DOUBLE_MARGIN_OF_ERROR)) || 
            (diff > (HALF_HOUR + DOUBLE_MARGIN_OF_ERROR) && diff < (1 - DOUBLE_MARGIN_OF_ERROR)) || 
            hour < -DOUBLE_MARGIN_OF_ERROR || (hour - (HOURS_IN_DAY + HALF_HOUR)) > DOUBLE_MARGIN_OF_ERROR){ 
            throw ExamDetails::InvalidTimeException();
        }
        if (length < 1){
            throw ExamDetails::InvalidArgsException();
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
        return DAYS_IN_MONTH*(month - exam.month) + (day - exam.day);  
    }

    bool ExamDetails::operator<(const ExamDetails& exam) const{
        return (month < exam.month) || (month == exam.month && day < exam.day);
    }

    ostream& operator<<(ostream& os, const ExamDetails& exam){
        return (os << "Course Number: " << exam.course_number << std::endl << "Time: " << exam.day << "." << exam.month
                << " at " << (int)exam.hour << ":" << (((exam.hour - (int)exam.hour < DOUBLE_MARGIN_OF_ERROR) || 
                (exam.hour - (int)exam.hour > (1 - DOUBLE_MARGIN_OF_ERROR)))? "00" : "30") << std::endl << "Duration: " 
                << exam.length << ":00" << std::endl << "Zoom Link: " << exam.link << std::endl);
    }

    ExamDetails ExamDetails::makeMatamExam(){
        ExamDetails mtm_exam(MATAM_COURSE_NUMBER, MATAM_EXAM_MONTH, MATAM_EXAM_DAY, MATAM_EXAM_HOUR, MATAM_EXAM_LENGTH, 
                            MATAM_ZOOM_LINK);
        return mtm_exam;
    }
}
