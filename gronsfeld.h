
#include <iostream>
#include <cstdlib>
#ifndef COURSE_GRONSFELD_H
#define COURSE_GRONSFELD_H
using namespace std;

string gronsfeld_decrypt(string keyword, string inputText, bool fileCrypt)
{
    if (fileCrypt)
    {
        int j = 0, key = 0;
        char ch[1];
        ifstream input("inputFile.txt");
        ofstream output("outputFile.txt");

        char buf;
        while (1)
        {
            buf = input.get();
            j = j % keyword.length();
            if (isalpha(buf))
            {
                ch[0] = keyword[j];
                key = atoi(ch);
                if (islower(buf))
                {
                    buf = ((buf - 97) + (26 - key)) % 26 + 97;
                    output << buf;
                }
                else if (isupper(buf))
                {
                    buf = ((buf - 65) + (26 - key)) % 26 + 65;
                    output << buf;
                }
                j++;
            }
            else if (buf == EOF) {
                break;
            }
            else {
                buf = buf;
                output << buf;
            }
        }

        input.close();
        output.close();
        return "[check output file]";

    } else {

        int j = 0, key = 0;
        char ch[1];
        for (int i = 0; i < inputText.length(); i++)
        {
            j = j % keyword.length();
            if (isalpha(inputText[i]))
            {
                ch[0] = keyword[j];
                key = atoi(ch);
                if (islower(inputText[i]))
                    inputText[i] = (((inputText[i] - 97) + (26 - key)) % 26) + 97;
                else if (isupper(inputText[i]))
                    inputText[i] = (((inputText[i] - 65) +  (26 - key)) % 26) + 65;
                j++;
            } else {
                inputText[i] = inputText[i];
            }
        }
        return inputText;
    }
}


string gronsfeld_encrypt(string keyword, string inputText , bool fileCrypt)
{
    if (fileCrypt)
    {
        int j = 0, key = 0;
        char ch[1];
        ifstream input("inputFile.txt");
        ofstream output("outputFile.txt");

        char buf;
        while (1)
        {
            buf = input.get();
            j = j % keyword.length();
            if (isalpha(buf))
            {
                ch[0] = keyword[j];
                key = atoi(ch);
                if (islower(buf))
                {
                    buf = (((buf - 97) + key) % 26) + 97;
                    output << buf;
                }
                else if (isupper(buf))
                {
                    buf = (((buf - 65) + key) % 26) + 65;
                    output << buf;
                }
                j++;
            }
            else if (buf == EOF) {
                break;
            } else {
                buf = buf;
                output << buf;
            }
        }
        input.close();
        output.close();
        return "[check output file]";
    }
    else {
        int j = 0, key = 0;
        char ch[1];
        for (int i = 0; i < inputText.length(); i++)
        {
            j = j % keyword.length();
            if (isalpha(inputText[i]))
            {
                ch[0] = keyword[j];
                key = atoi(ch);
                if (islower(inputText[i]))
                    inputText[i] = (((inputText[i] - 97) + key ) % 26) + 97;
                else if (isupper(inputText[i]))
                    inputText[i] = (((inputText[i] - 65) + key) % 26) + 65;
                j++;
            } else {
                inputText[i] = inputText[i];
            }
        }
        return inputText;
    }
}


int gronsfeld(string inputText, bool fileCrypt)
{

    string choice;
    string keyword;
    cout << "\ngenerate random key?[Y/N]\n";

    cin >> choice;
    if (choice == "N" || choice == "n" || choice == "No" || choice == "no")
    {
        cout << "\nenter keynumber: ";
        cin >> keyword;

        for (int i = 0; i < keyword.length(); i++)
        {
            if (!isalnum(keyword[i]))
            {
                cout << "\n[error: wrong argument type]\n";
                return 1;
            }
        }

    }
    else if (choice == "Y" || choice == "y" || choice == "Yes" || choice == "yes")
    {
        cout << "[creating key]\n";

        int length = 0;
        cout << "\nenter key length: ";
        cin >> length;

        if (fileCrypt)
        {
            /*
            ifstream len("inputFile.txt");
            char buf;
            while (1)
            {
                buf = len.get();
                if(buf != ' ' && buf != '\n')
                    length++;
                if (buf == EOF)
                    break;
            }
             */
            string charset = "1234567890";
            keyword.resize(length);
            for (int i = 0; i < length; i++)
            {
                keyword[i] = charset[rand() % charset.length()];
            }
            cout << "\nrandomly generated key:\n" << keyword << endl;

        } else {

            string charset = "1234567890";
            keyword.resize(length);
            for (int i = 0; i < length; i++)
            {
                keyword[i] = charset[rand() % charset.length()];
            }
            cout << "\nrandomly generated keyword:\n" << keyword << endl;
        }

    } else {
        cout << "[error: invalid input]";
        return 1;
    }

    while(true)
    {
        cout << "\navailable options:\n";
        cout << "[E] encryption" << endl;
        cout << "[D] decryption" << endl;
        cin >> choice;

        if (choice == "E" || choice == "e")
        {
            cout << "[encryption]\n";
            inputText = gronsfeld_encrypt(keyword, inputText, fileCrypt);
            cout << "\nciphertext: " << inputText << endl;
            break;
        }
        else if (choice == "D" || choice == "d")
        {
            cout << "[decryption]\n";
            inputText = gronsfeld_decrypt(keyword, inputText, fileCrypt);
            cout << "\ndecrypted text: " << inputText << endl;
            break;
        } else
            cout << "[error: invalid choice]\n";
    }
    return 0;
}

#endif
