#include <iostream>
#include <string>
#include <fstream>

#include "caesar.h"
#include "vigenere.h"
#include "vernam.h"
#include "gronsfeld.h"
#include "rsa.h"

using namespace std;

int main()
{

    string input;
    cout << "enter text or filename: ";
    getline(cin, input);


    bool fileCrypt;
    ifstream my_file;
    my_file.open(&input[0]);


    if (my_file.good())
    {
        cout << "[reading from file]\n";
        fileCrypt = true;

    } else {
        cout << "[reading from string]\n";
        fileCrypt = false;
    }


    do
    {
        cout << "\navailable encryption methods:" << endl;
        cout << "[1] caesar\n"
                "[2] vigenere\n"
                "[3] vernam\n"
                "[4] gronsfeld\n"
                "[5] rsa\n";

        char choice;
        cin >> choice;


        if (choice == '1')
        {
            cout << "[caesar]" << endl;
            caesar(input);
            break;
        }
        else if (choice == '2')
        {
            cout << "[vigenere]" << endl;
            vigenere(input, fileCrypt);
            break;
        }
        else if (choice == '3')
        {
            cout << "[vernam]" << endl;
            vernam(input, fileCrypt);
            break;
        }
        else if (choice == '4')
        {
            cout << "[gronsfeld]" << endl;
            gronsfeld(input, fileCrypt);
            break;
        }
        else if (choice == '5')
        {
            cout << "[rsa]" << endl;
            rsa(input, fileCrypt);
            break;
        } else
            cout << "[error: invalid choice]\n";

    } while (true);
    return 0;
}
