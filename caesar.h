
#include <iostream>
#include <string>
using namespace std;

#ifndef COURSE_FUNCS_H
#define COURSE_FUNCS_H


string caesar_encrypt(string input)
{
    int key;
    cout << "[encryption]" << endl;
    cout << "enter key: " << endl;
    cin >> key;


    for (int i = 0; i < input.length(); ++i)
    {
        if (input[i] != ' ')
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
            {
                input[i] = (input[i] + key - 65) % 26 + 65;
            }
            else if (input[i] >= 'a' && input[i] <= 'z')
                input[i] = (input[i] + key - 97) % 26 + 97;
        }
    }
    return input;
}

string caesar_decrypt(string input)
{
    int key;
    cout << "[decryption]" << endl;
    cout << "enter key: " << endl;
    cin >> key;


    for (int i = 0; i < input.length(); ++i)
    {
        if (input[i] != ' ')
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
                input[i] = (input[i] + (26- key) - 65) % 26 + 65;
            else if (input[i] >= 'a' && input[i] <= 'z')
                input[i] = (input[i] + (26 - key) - 97) % 26 + 97;
        }
    }

    return input;
}


void caesar(string input)
{

    char choice;
    cout << "[E] encryption" << endl;
    cout << "[D] decryption" << endl;
    cin >> choice;

    if (choice == 'E' || choice == 'e')
    {
        input = caesar_encrypt(input);
        cout << "result: \n" << input << endl;
    }
    else if (choice == 'D' || choice == 'd')
    {
        input = caesar_decrypt(input);
        cout << "result: \n" << input << endl;
    } else {

        cout << "error: invalid choice" << endl;
    }
}

#endif
