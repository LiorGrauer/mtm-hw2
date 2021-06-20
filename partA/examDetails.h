#ifndef EXAMDETAILS_H
#define EXAMDETAILS_H

#include <iostream>
#include <fstream>

namespace mtm {
    class ExamDetails {
        private:
            int course_number, month, day, length;
            double hour; 
            std::string link;
            
        public:
            /**
             * ExamDetails: Exam Details constructor
             *
             * @param course_number - course number. Must be type int
             * @param course_number - month. Must be type int
             * @param month - month. Must be type int
             * @param day - day. Must be type int
             * @param hour - hour. Must be type double, only .0 or .5
             * @param length - length. Must be type int
             * @param link - link. Must be type string
             *
             * @return
             *     Exam Details with given data 
             */
            ExamDetails(int course_number, int month, int day, double hour, int length, std::string link = "");

            // default destructor
            ~ExamDetails() = default;

            /**
             * ExamDetails: Exam Details copy constructor
             *
             * @param s - ExamDetails&. existing Exam Details.
             *
             * @return
             *     new copy of the given sorted list
             */
            ExamDetails(const ExamDetails& exam);

            /**
             * operator=: Exam Details placement operator
             *
             * @param exam - ExamDetails&. existing Exam Details
             *
             * @return
             *     inserts the data from the given Exam Details to an existing Exam Details
             *     deletes all the old data and inserts the new from the given Exam Details.
             */
            ExamDetails& operator=(const ExamDetails& exam);

            /**
             * getLink: returns Exam Details zoom link
             *
             * @return 
             *      zoom link
             *
             */
            std::string getLink() const;

            /**
             * setLink: changes Exam Details zoom link
             *
             * @param link - new zoom link
             * 
             */
            void setLink(std::string link);

            /**
             * operator-: Exam Details subtraction operator
             *
             * @param exam - ExamDetails&. Exam Details
             *
             * @return
             *     return the differnce in days between the two exams
             */
            int operator-(const ExamDetails& exam) const;

            /**
             * operator<: Exam Details smaller than operator
             *
             * @param exam - ExamDetails&. Exam Details
             *
             * @return
             *     true/false - return true if the first exam is before the second.
             */
            bool operator<(const ExamDetails& exam) const;

            /**
             * operator<<: Exam Details printing operator
             *
             * @param os - stream to add to. must be ostream type
             *
             * @return
             *     stream after adding the exam details
             */
            friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

            /**
             * makeMatamExam: makes matam Exam Details
             *
             * @return
             *     ExamDetails with the matam exam 
             */
            static ExamDetails makeMatamExam();
            
            // exceptions for ExamDetails
            class InvalidDateException {};
            class InvalidTimeException {};
            class InvalidArgsException {};
    }; 
}

#endif
