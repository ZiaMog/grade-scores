#include "UnitTest++.h"
#include "grade-scores.h"

int main(int argc, char** argv)
{
    #ifdef DEBUG_BUILD
        return UnitTest::RunAllTests();
    #else
        if (argc < 2)
        {
            cout << "Error: no input file argument is passed !!!" << endl;
            return -1;
        }
        else if (argc > 2)
        {
            cout << "Error: too many input arguments are passed !!!" << endl;
            return -1;
        }
        else // argc = 2
            return main_grade_scores(string(argv[1]));
    #endif
}
