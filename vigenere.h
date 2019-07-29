#include <iostream>
#include <stdio.h>

#ifndef COURSE_VIGENERE_H
#define COURSE_VIGENERE_H

using namespace std;

string vigenere_decrypt(string keyword, string inputText, bool fileCrypt)
{
    if (fileCrypt)
    {
        int j = 0;
        ifstream input("inputFile.txt");
        ofstream output("outputFile.txt");

        char buf;
        while (1)
        {
            buf = input.get();
            j = j % keyword.length();

            if (isalpha(buf))
            {
                if (islower(buf) && islower(keyword[j])) {
                    buf = ((buf - 97) + (26 - (keyword[j] - 97))) % 26 + 97;
                    output << buf;
                }
                else if (isupper(buf) && islower(keyword[j])) {
                    buf = ((buf - 65) + (26 - (keyword[j] - 97))) % 26 + 65;
                    output << buf;
                }
                else if (islower(buf) && isupper(keyword[j])) {
                    buf = ((buf - 97) + (26 - (keyword[j] - 65))) % 26 + 97;
                    output << buf;
                }
                else if (isupper(buf) && isupper(keyword[j])) {
                    buf = ((buf - 65) + (26 - (keyword[j] - 65))) % 26 + 65;
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
        int j = 0;
        for (int i = 0; i < inputText.length(); i++)
        {
            j = j % keyword.length();
            if (isalpha(inputText[i]))
            {
                if (islower(inputText[i]) && islower(keyword[j]))
                    inputText[i] = ((inputText[i] - 97) + (26 - (keyword[j] - 97))) % 26 + 97;
                else if (isupper(inputText[i]) && islower(keyword[j]))
                    inputText[i] = ((inputText[i] - 65) + (26 - (keyword[j] - 97))) % 26 + 65;
                else if (islower(inputText[i]) && isupper(keyword[j]))
                    inputText[i] = ((inputText[i] - 97) + (26 - (keyword[j] - 65))) % 26 + 97;
                else if (isupper(inputText[i]) && isupper(keyword[j]))
                    inputText[i] = ((inputText[i] - 65) + (26 - (keyword[j] - 65))) % 26 + 65;
                j++;
            } else {
                inputText[i] = inputText[i];
            }
        }
        return inputText;
    }
}


string vigenere_encrypt(string keyword, string inputText , bool fileCrypt)
{
    if (fileCrypt)
    {
        int j = 0;
        ifstream input("inputFile.txt");
        ofstream output("outputFile.txt");

        char buf;
        while (1)
        {
            buf = input.get();
            j = j % keyword.length();
            if (isalpha(buf))
            {
                if (islower(buf) && islower(keyword[j])) {
                    buf = (((buf - 97) + (keyword[j] - 97)) % 26) + 97;
                    output << buf;
                }
                else if (isupper(buf) && islower(keyword[j])) {
                    buf = (((buf - 65) + (keyword[j] - 97)) % 26) + 65;
                    output << buf;
                }
                else if (islower(buf) && isupper(keyword[j])) {
                    buf = (((buf - 97) + (keyword[j] - 65)) % 26) + 97;
                    output << buf;
                }
                else if (isupper(buf) && isupper(keyword[j])) {
                    buf = (((buf - 65) + (keyword[j] - 65)) % 26) + 65;
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
        int j = 0;
        for (int i = 0; i < inputText.length(); i++)
        {
            j = j % keyword.length();
            if (isalpha(inputText[i]))
            {
                if (islower(inputText[i]) && islower(keyword[j]))
                    inputText[i] = (((inputText[i] - 97) + (keyword[j] - 97)) % 26) + 97;
                else if (isupper(inputText[i]) && islower(keyword[j]))
                    inputText[i] = (((inputText[i] - 65) + (keyword[j] - 97)) % 26) + 65;
                else if (islower(inputText[i]) && isupper(keyword[j]))
                    inputText[i] = (((inputText[i] - 97) + (keyword[j] - 65)) % 26) + 97;
                else if (isupper(inputText[i]) && isupper(keyword[j]))
                    inputText[i] = (((inputText[i] - 65) + (keyword[j] - 65)) % 26) + 65;
                j++;
            } else {
                inputText[i] = inputText[i];
            }
        }
        return inputText;
    }
}


int vigenere(string inputText, bool fileCrypt)
{
    string keyword;
    while (true)
    {
        cout << "\nenter keyword: ";

        cin >> keyword;

        bool f = true;

        for (int i = 0; i < keyword.length(); i++)
        {
            if (!isalpha(keyword[i]))
            {
                f = false;
            }
        }

        if (f)
            break;
        else
            cout << "[error: wrong argument type]\n";
    }

    char choice;
    while(true)
    {
        cout << "\navailable options:\n";
        cout << "[E] encryption" << endl;
        cout << "[D] decryption" << endl;
        cin >> choice;

        if (choice == 'E' || choice == 'e')
        {
            cout << "[encryption]\n";
            inputText = vigenere_encrypt(keyword, inputText, fileCrypt);
            cout << "\nciphertext:\n" << inputText << endl;
            break;
        }
        else if (choice == 'D' || choice == 'd')
        {
            cout << "[decryption]\n";
            inputText = vigenere_decrypt(keyword, inputText, fileCrypt);
            cout << "\ndecrypted text:\n" << inputText << endl;
            break;
        } else
            cout << "[error: invalid choice]\n";
    }
    return 0;
}

#endif
