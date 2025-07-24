#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

int main(void)
{
    string input;
    cout << "Enter your input: ";
    cin.ignore();
    getline(cin, input);
    if (input.length() >= 2 && input[0] == '/' && input[1] == '/')
    {
        cout << "This is a single line comment." << endl;
    }
    else if (
             input[0] == '/' &&
             input[1] == '*' &&
             input[input.length() - 2] == '*' &&
             input[input.length() - 1] == '/')
    {
        cout << "This is a multi line comment." << endl;
    }
    else
    {
        cout << "This is not a comment." << endl;
    }

    getch();
}
