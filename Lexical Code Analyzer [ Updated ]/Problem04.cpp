#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

int main(void)
{
    string input;
    int isIdentifier = 1;
    cout<<"Enter your input : ";
    getline(cin, input);

    char first = input[0];

    if (!((first >= 'A' && first <= 'Z') ||
            (first >= 'a' && first <= 'z') ||
            first == '_'))
    {
        isIdentifier = 0;
    }
    for (int i = 1; i < input.length(); i++)
    {
        char ch = input[i];


        if (!((ch >= 'A' && ch <= 'Z') ||
                (ch >= 'a' && ch <= 'z') ||
                (ch >= '0' && ch <= '9') ||
                ch == '_'))
        {
            isIdentifier = 0;
            break;
        }
    }
    if (isIdentifier == 1)
    {
        cout << "This is a VALID identifier." << endl;
    }
    else
    {
        cout << "This is NOT a valid identifier." << endl;
    }
    getch();

}
