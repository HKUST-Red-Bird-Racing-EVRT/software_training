/**
 * @file q4.cpp
 * 
 * @author Planeson (carson.cpk@proton.me) 
 * @brief Homework 1, Question 4: commenting code
 * @version 1.0.0
 * @date 2026-09-28
 *
 * @copyright Copyright (c) 2026 Red Bird Racing
 */

 #include <iostream>
using namespace std;

// ==== Example comment for a function ====

/**
 * 
 * @brief if the boolean is true, it prints the integer
 * 
 * @param param1 the integer to be printed
 * @param param2 whether to print the integer or not
 * 
 */
void exampleFunction(int param1, bool param2)
{
    // this is an example function
    if (param2) {
        cout << "param1 is " << param1 << endl;
    } else {
        cout << "param1 is not printed" << endl;
    }
}

/**
 * HOMEWORK TODO 1: write the comments for the function "secret".
 * 
 * You should describe what the function does, its parameters, and its return value.
 * Use the exampleFunction above as a reference.
 * 
 * as a hint, you can use the @brief, @param, and @return tags to describe the function.
 */

/**
 * Your comment starts here
 */
bool secret(int x, int y, bool z)
{
    if (x > y || z) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    // HOMEWORK TODO 2: give the results of each function call. Replace ANSWER_HERE with the actual result of the function call.

    exampleFunction(5, true);
    // result 1: ANSWER_HERE is printed

    exampleFunction(10, false);
    // result 2: ANSWER_HERE is printed

    bool result = secret(3, 4, false);
    // result 3: result is ANSWER_HERE

    result = secret(5, 2, false);
    // result 4: result is ANSWER_HERE

    result = secret(1, 1, true);
    // result 5: result is ANSWER_HERE

    return 0;
}