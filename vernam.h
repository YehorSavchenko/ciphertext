#include <iostream>
#include <cstring>
#include <cstdlib>
#ifndef COURSE_VERNAM_H
#define COURSE_VERNAM_H

using namespace std;

string vernam_decrypt(string keyword, string inputText, bool fileCrypt)
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

        // Переписываем кейворд
        for (int k = 0; k < inputText.length(); ++k)
        {
            if (!isalpha(inputText[k]))
            {
                char buff = keyword[0], temp;
                for (int j = k; j < keyword.length(); ++j)
                {
                    temp = keyword[j];
                    keyword[j] = buff;
                    buff = temp;
                }
            }
        }

        for (int i = 0; i < inputText.length(); i++)
        {
            if (isalpha(inputText[i]))
            {
                if (islower(inputText[i]))
                {
                    inputText[i] = (((inputText[i] - 97) + (26 - (keyword[i] - 65))) % 26) + 97;
                }
                else if (isupper(inputText[i]))
                {
                    inputText[i] = (((inputText[i] - 65) + (26 - (keyword[i] - 65))) % 26) + 65;

                }
            }

        }
        return inputText;
    }
}


string vernam_encrypt(string keyword, string inputText , bool fileCrypt)
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

        // Переписываем кейворд
        for (int k = 0; k < inputText.length(); ++k)
        {
            if (!isalpha(inputText[k]))
            {
                char buff = keyword[0], temp;
                for (int j = k; j < keyword.length(); ++j)
                {
                    temp = keyword[j];
                    keyword[j] = buff;
                    buff = temp;
                }
            }
        }

        for (int i = 0; i < inputText.length(); i++)
        {
            if (isalpha(inputText[i]))
            {
                if (islower(inputText[i]))
                {
                    inputText[i] = (((inputText[i] - 97) + (keyword[i] - 65)) % 26) + 97;
                }
                else if (isupper(inputText[i]))
                {
                    inputText[i] = (((inputText[i] - 65) + (keyword[i] - 65)) % 26) + 65;

                }
            }

        }
        return inputText;
    }
}


int vernam(string inputText, bool fileCrypt)
{

    string choice;
    string keyword;

    while (true)
    {
        cout << "\ngenerate random key?[Y/N]\n";
        cin >> choice;

        if (choice == "N" || choice == "n" || choice == "No" || choice == "no")
        {

            while (true)
            {

                cout << "\nenter keyword: ";
                cin >> keyword;


                bool checkKeyType = true;

                for (int i = 0; i < keyword.length(); i++)
                {
                    if (!(isalpha(keyword[i])))
                    {
                        checkKeyType = false;
                    }
                }

                if (checkKeyType)
                {
                    if (strlen(&inputText[0]) != strlen(&keyword[0]))
                    {
                        cout << "[error: keyword size must be equal to ciphertext size]\n";
                    } else {
                        cout << endl;
                        break;
                    }
                }
                else
                    cout << "[error: wrong keyword type]\n";

            }

            break;

        }
        else if (choice == "Y" || choice == "y" || choice == "Yes" || choice == "yes")
        {
            cout << "[creating keyword]\n";
            int lenght = 0;

            if (fileCrypt)
            {
                ifstream len("inputFile.txt");
                char buf;

                while (1)
                {
                    buf = len.get();
                    if (buf != ' ' && buf != '\n')
                        lenght++;
                    if (buf == EOF)
                        break;
                }

                string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                keyword.resize(lenght);

                for (int i = 0; i < lenght; i++)
                {
                    keyword[i] = charset[rand() % charset.length()];
                }
                cout << "\nrandomly generated keyword:\n" << keyword << endl << endl;

            } else {

                lenght = strlen(&inputText[0]);
                string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                keyword = inputText;

                for (int i = 0; i < lenght; i++)
                {
                    keyword[i] = charset[rand() % charset.length()];
                }
                cout << "\nrandomly generated keyword:\n" << keyword << endl << endl;
            }

            break;

        } else {
            cout << "[error: invalid input]\n";
        }

    }

    while(true)
    {
        cout << "[E] encryption" << endl;
        cout << "[D] decryption" << endl;
        cin >> choice;

        if (choice == "E" || choice == "e")
        {
            cout << "[encryption]\n";
            inputText = vernam_encrypt(keyword, inputText, fileCrypt);
            cout << "\nciphertext:\n" << inputText << endl;
            break;
        }
        else if (choice == "D" || choice == "d")
        {
            cout << "[decryption]\n";
            inputText = vernam_decrypt(keyword, inputText, fileCrypt);
            cout << "\ndecrypted text:\n" << inputText << endl;
            break;
        } else
            cout << "[error: invalid choice]\n";
    }
    return 0;
}

#endif
