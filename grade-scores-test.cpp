#include "UnitTest++.h"
#include "grade-scores.h"

namespace
{
    TEST(Get_Last_Name)
    {
        string fetchedWord, remainingLine;
        const bool isLastWord = get_next_word(" BUNDY, TERESSA, 88", fetchedWord, remainingLine);
        CHECK_EQUAL(false, isLastWord);
        CHECK_EQUAL("BUNDY", fetchedWord);
        CHECK_EQUAL("TERESSA, 88", remainingLine);
    }

    TEST(Get_First_Name)
    {
        string fetchedWord, remainingLine;
        const bool isLastWord = get_next_word(" TERESSA , 88", fetchedWord, remainingLine);
        CHECK_EQUAL(false, isLastWord);
        CHECK_EQUAL("TERESSA", fetchedWord);
        CHECK_EQUAL("88", remainingLine);
    }

    TEST(Get_Person_Score)
    {
        string fetchedWord, remainingLine;
        const bool isLastWord = get_next_word(" , 88", fetchedWord, remainingLine);
        CHECK_EQUAL(true, isLastWord);
        CHECK_EQUAL("88", fetchedWord);
        CHECK_EQUAL("", remainingLine);
    }

    TEST(Sort_Bigger_Score)
    {
        PersonRecord person1 = PersonRecord("BUNDY", "TERESSA", 88);
        PersonRecord person2 = PersonRecord("SMITH", "ALLAN", 70);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(false, is_person1_samller);
    }

    TEST(Sort_Smaller_Score)
    {
        PersonRecord person1 = PersonRecord("SMITH", "ALLAN", 70);
        PersonRecord person2 = PersonRecord("BUNDY", "TERESSA", 88);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(true, is_person1_samller);
    }

    TEST(Sort_Same_Score_Bigger_Last_Name)
    {
        PersonRecord person1 = PersonRecord("BUNDY", "TERESSA", 88);
        PersonRecord person2 = PersonRecord("KING", "MADISON", 88);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(false, is_person1_samller);
    }

    TEST(Sort_Same_Score_Smaller_Last_Name)
    {
        PersonRecord person1 = PersonRecord("KING", "MADISON", 88);
        PersonRecord person2 = PersonRecord("BUNDY", "TERESSA", 88);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(true, is_person1_samller);
    }

    TEST(Sort_Same_Score_Same_Last_Name_Smaller_First_Name)
    {
        PersonRecord person1 = PersonRecord("KING", "TERESSA", 88);
        PersonRecord person2 = PersonRecord("KING", "MADISON", 88);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(true, is_person1_samller);
    }

    TEST(Sort_Same_Score_Same_Last_Name_Bigger_First_Name)
    {
        PersonRecord person1 = PersonRecord("KING", "MADISON", 88);
        PersonRecord person2 = PersonRecord("KING", "TERESSA", 88);
        bool is_person1_samller = sorting_compare_logic(person1, person2);
        CHECK_EQUAL(false, is_person1_samller);
    }

    TEST(Swap_Two_Persons)
    {
        PersonRecord person1 = PersonRecord("SMITH", "ALLAN", 70);
        PersonRecord person2 = PersonRecord("BUNDY", "TERESSA", 88);
        swap_two_persons(person1, person2);
        CHECK_EQUAL("BUNDY", person1.get_last_name());
        CHECK_EQUAL("TERESSA", person1.get_first_name());
        CHECK_EQUAL(88, person1.get_score());
        CHECK_EQUAL("SMITH", person2.get_last_name());
        CHECK_EQUAL("ALLAN", person2.get_first_name());
        CHECK_EQUAL(70, person2.get_score());
    }
}
