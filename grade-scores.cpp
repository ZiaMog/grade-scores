#include "grade-scores.h"


vector<PersonRecord> peopleRecords;


bool get_next_word(string inputLine, string &fetchedWord, string &remainingLine)
{
    while (inputLine[0] == ',' || inputLine[0] == ' ') // removing any " " or "," before the fetching word
        inputLine = inputLine.erase(0, 1);

    size_t wordLength = inputLine.find_first_of(", "); // find the first occourness of either " " or "," after the fetching word
    if (wordLength == string::npos)
    { // the input line consists of only one word
        fetchedWord = inputLine;
        remainingLine = "";
        return true;
    }

    fetchedWord = inputLine.substr(0, wordLength);
    remainingLine = inputLine.substr(wordLength + 1);

    // bypass " " or "," (if any exists) to get to the next word
    while (remainingLine[0] == ',' || remainingLine[0] == ' ') // removing any " " or "," before the next fetching word
        remainingLine = remainingLine.erase(0, 1);

    return false;
}


void swap_two_persons(PersonRecord& person1, PersonRecord& person2)
{ // swap the contents of 'a' and 'b'
    PersonRecord tempPerson = PersonRecord(person1.lastName, person1.firstName, person1.personScore);

    person1.set_last_name(person2.get_last_name());
    person1.set_first_name(person2.get_first_name());
    person1.set_score(person2.get_score());

    person2.set_last_name(tempPerson.get_last_name());
    person2.set_first_name(tempPerson.get_first_name());
    person2.set_score(tempPerson.get_score());
}


bool sorting_compare_logic(PersonRecord person1, PersonRecord person2)
{ // return true if the 'person1' should be sorted as smaller than 'person2'
    // first order by 'score' field
    if (person1.get_score() < person2.get_score())
        return true;
    else if (person1.get_score() > person2.get_score())
        return false;
    else // the 'score' filed of both persons are same
    { // next order by 'lastName' field
        int compareResult;
        compareResult = person1.get_last_name().compare(person2.get_last_name());
        if (compareResult > 0)
            return true;
        else if (compareResult < 0)
            return false;
        else // the 'lastName' filed of both persons are same
        { // next order by 'firstName' field
            compareResult = person1.get_first_name().compare(person2.get_first_name());
            if (compareResult > 0)
                return true;
            else
                return false;
        }
    }
}


int find_pivot_index(int firstIndex, int lastIndex)
{ // Find and return the index of pivot element for quick_sort_algo
    int pivotIndex = firstIndex;
    PersonRecord pivotElement = peopleRecords[lastIndex];

    for (int i = firstIndex ; i < lastIndex ; i++)
    {
        if (sorting_compare_logic(peopleRecords[i], pivotElement) == true)
        { // the 'peopleRecords[i]' is smaller than 'pivotElement'
            swap_two_persons(peopleRecords[i], peopleRecords[pivotIndex]);
            pivotIndex++;
        }
    }

    swap_two_persons(peopleRecords[pivotIndex], peopleRecords[lastIndex]);

    return pivotIndex;
}


void quick_sort_algo(int firstIndex, int lastIndex)
{ // the recursive function to sort the input vector using quick sorting algorithm
    if (firstIndex < lastIndex)
    {
        int pivotIndex = find_pivot_index(firstIndex, lastIndex);
        quick_sort_algo(firstIndex, (pivotIndex - 1));
        quick_sort_algo((pivotIndex + 1), lastIndex);
    }
}


int main_grade_scores(string inFilePath)
{
    string outFilePath, curLine;
    ifstream inFileHandler;
    ofstream outFileHandler;
    //vector<PersonRecord> peopleRecords;

    inFileHandler.open(inFilePath.c_str(), ios::in);
    if (inFileHandler.is_open() == false)
    {
        cout << "Error: cannot open input file '" << inFilePath << "' !!!" << endl;
        return -1;
    }

    size_t tmpPos = inFilePath.find(".txt");
    if (tmpPos == string::npos)
    {
        cout << "Error: the input file '" << inFilePath << "' is not from txt extension!" << endl;
        return -1;
    }

    outFilePath = inFilePath.substr(0, tmpPos) + "-graded.txt";
    outFileHandler.open(outFilePath.c_str(), ios::out);
    if (outFileHandler.is_open() == false)
    {
        cout << "Error: cannot open output file '" << outFilePath << "' !!!" << endl;
        return -1;
    }

    peopleRecords.clear();

    while (getline(inFileHandler, curLine))
    { // read the record for each person from the input file
        string lastName, firstName, fetchedWord;
        int personScore;

        // read the 'lastName'
        get_next_word(curLine, lastName, curLine);

        // read the 'firstName'
        get_next_word(curLine, firstName, curLine);

        // read the 'score'
        get_next_word(curLine, fetchedWord, curLine);
        if (!(istringstream(fetchedWord) >> personScore))
            personScore = 0;

        PersonRecord curPerson = PersonRecord(lastName, firstName, personScore);
        peopleRecords.push_back(curPerson);
    }

    // sort the vector of people records using quck sort algorithm
    quick_sort_algo(0, (peopleRecords.size() - 1));

    // write the sorted list into the output file
    for (vector<PersonRecord>::reverse_iterator it = peopleRecords.rbegin(); it < peopleRecords.rend() ; it++)
    {
        ostringstream tmpStreamString;
        tmpStreamString << (it->get_score());
        curLine = it->get_last_name() + ", " + it->get_first_name() + ", " + tmpStreamString.str();
        outFileHandler << curLine << endl;
        cout << curLine << endl;
    }

    peopleRecords.clear();
    inFileHandler.close();
    outFileHandler.close();
    cout << "Finished: created " << (outFilePath.substr(outFilePath.find_last_of("/\\") + 1 )) << endl;

    return 0;
}
