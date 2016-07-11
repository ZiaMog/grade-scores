#ifndef GRADE-SCORES_H_INCLUDED
#define GRADE-SCORES_H_INCLUDED

    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <algorithm>

    using namespace std;

    class PersonRecord
    {
        public:
            PersonRecord(string _ln, string _fn, int _sc)
            {
                lastName = _ln;
                firstName = _fn;
                personScore = _sc;
            };

        public:
            void set_last_name(string _ln) { lastName = _ln; };
            void set_first_name(string _fn) { firstName = _fn; };
            void set_score(int _sc) { personScore = _sc; };
            string get_last_name() { return lastName; };
            string get_first_name() { return firstName; };
            int get_score() { return personScore; };

        public:
            friend bool sorting_compare_logic(PersonRecord person1, PersonRecord person2);
            friend void swap_two_persons(PersonRecord& a, PersonRecord& b);

        private:
            string lastName;
            string firstName;
            int personScore;
    };

    bool get_next_word(string inputLine, string &fetchedWord, string &remainingLine);
    int main_grade_scores(string inFilePath);

#endif // GRADE-SCORES_H_INCLUDED
