#include <iostream>
#include <fstream>
using std::string;
using std::endl;
using std::ostream;

namespace mtm {
    class ExamDetails {
        int course_number, month, day, length;
        double hour; 
        std::string link;
        
        public:
            ExamDetails(int course_number, int month, int day, double hour, int length, std::string link = "");
            ~ExamDetails();
            ExamDetails(const ExamDetails& exam);
            ExamDetails& operator=(const ExamDetails& exam);
            std::string getLink();
            void setLink(std::string link);
            int operator-(const ExamDetails& exam);
            bool operator<(const ExamDetails& exam);
            friend ostream& operator<<(ostream& os, const ExamDetails& exam);
            ExamDetails makeMatamExam();

            class InvalidDateException {};
            class InvalidTimeException {};
            class InvalidArgsException {};
    };

    ExamDetails::ExamDetails(int course_number, int month, int day, double hour, int length, string link = ""):
        course_number(course_number), 
        month(month), 
        day(day), 
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
        if (hour - (int)hour > 1e-6 || hour - 0.5 - (int)hour > 1e-6){
            throw ExamDetails::InvalidTimeException();
        }
    }

    //**************
    //should i writh this?
    ExamDetails::~ExamDetails(){        
    }

    ExamDetails::ExamDetails(const ExamDetails& exam):
        course_number(exam.course_number), 
        month(exam.month), 
        day(exam.day), 
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
        link = exam.link; 
        return *this;
    }

    string ExamDetails::getLink(){
        return link;
    }

    void ExamDetails::setLink(string link){
        this->link = link;
        //should i use old link destructor??
    }

    int ExamDetails::operator-(const ExamDetails& exam){
        return 30*(month - exam.month) + (day - exam.day);  
    }

    bool ExamDetails::operator<(const ExamDetails& exam){
        return (month < exam.month) || (month == exam.month && day < exam.day);
    }

    ostream& operator<<(ostream& os, const ExamDetails& exam){
        return (os << "Corse number: " << exam.course_number << endl << "Time: " << exam.day << "." << exam.month
                << " at " << (int)exam.hour << ":" << (exam.hour - (int)exam.hour < 1e-6)? "00" : "30" << endl 
                << "Duration: " << exam.length << ":00" << endl << "Zoom Link: " << exam.link);
    }

    ExamDetails ExamDetails::makeMatamExam(){
        ExamDetails mtm_exam(234124, 7, 28, 13.0, 3, "https://tinyurl.com/59hzps6m");
        return mtm_exam;
    }

}