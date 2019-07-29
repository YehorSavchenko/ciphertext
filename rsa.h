#include <iostream>
#include <cmath>
#include <limits>
#include <stdint.h>

#ifndef COURSE_RSA_H
#define COURSE_RSA_H
using namespace std;


bool isPrime(long int prime)
{
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for ( i = 2; i <= j; i++)
    {
        if ( prime % i == 0 )
        {
            return false;
        }
    }
    return true;
}

long int greatestCommonDivisor( long int e, long int t )
{
    while ( e > 0 )
    {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int calculateE( long int t )
{
    long int e;

    for ( e = 2; e < t; e++ )
    {
        if (greatestCommonDivisor( e, t ) == 1 )
        {
            return e;
        }
    }

    return -1;
}

long int calculateD( long int e, long int t)
{
    long int d;
    long int k = 1;

    while ( 1 )
    {
        k = k + t;

        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}

string rsa_decrypt(long int d, long int n, char *inputText, bool fileCrypt)
{

    if (fileCrypt)
    {
        /*
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

     */
    } else {

        //59 118 80 80 100

        int wcount = 0;    // Счетчик слов
        char prev = ' ';

        // Считаем количество чисел в инпуте
        // * Можно дописать проверку на "циферность слова" *
        for(int i = 0; i < strlen(inputText); i++)
        {

            if(inputText[i] != ' ' && prev == ' ')
                wcount++;

            prev = inputText[i];
        }


        // Создаем массив указателей на отдельные числа в массиве входного текста
        // Я, надо сказать, горжусь этим кодом, он наверняка весьма костыльный но лаконичный
        // Объяснять его нужно отдельно, но пока давай условимся, что он работает как надо
        // Вроде как работает
        // * В будущем переписать и откомментировать *
        char *crtyptoText[wcount];
        char *p;

        p = &inputText[0];

        for (int j = 0; j < wcount; ++j)
        {
            p = strtok(p, "  ");
            if (p)
            {
                crtyptoText[j] = p;
                p = NULL;
            } else
                break;
        }


        // Дешифровка
        long int key;
        for (int i = 0; i < wcount; ++i)
        {
            key = 1;
            for (int j = 0; j < d; ++j)
            {
                key *= atoi(crtyptoText[i]);
                key %= n;
            }
            inputText[i] = char(key);
        }

        for (int k = 0; k < strlen(inputText); ++k)
        {
            cout << inputText[k] << endl;
        }
    }
}


string rsa_encrypt(long int e, long int n,  string inputText , bool fileCrypt)
{

    if (fileCrypt)
    {
        /*
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
         */
    }
    else {

        long int key;
        for (int i = 0; i < inputText.length(); ++i)
        {
            key = 1;
            for (int j = 0; j < e; ++j)
            {
                key *= inputText[i];
                key %= n;
            }
            inputText[i] = key;
            cout << int(inputText[i]) << " " << inputText[i] << endl;
        }
        return inputText;
    }
}


int rsa(string inputText, bool fileCrypt)
{

    string choice;

    ofstream key_file("keyword.txt");   // Привязываем файл для хранения кючей

    int p, q;   // Два простых числа

    do
    {
        cout << "\nenter a prime number p: ";
        cin >> p;
        if (!isPrime(p))
        {
            cout << "[error: number is not prime]\n";
        }
    } while (!isPrime(p));

    do
    {
        cout << "enter a prime number q: ";
        cin >> q;
        if (!isPrime(q))
        {
            cout << "[error: number is not prime]\n\n";
        }
    } while (!isPrime(q));


    long int n = p * q;     // Вычисляем модуль
    cout << "\nresult of computing p*q: n = " << n;

    long int t = (p - 1)*(q - 1);     // Вычисляем функцию Эйлера
    cout << "\nresult of computing Euler's function: t = " << t << endl;


    long int e;     // Открытый ключ
    long int d;     // Закрытый ключ

    while(true)
    {
        cout << "\ngenerate random keys?[Y/N] ";
        cin >> choice;

        if (choice == "N" || choice == "n" || choice == "No" || choice == "no")
        {

            while (true)
            {
                cout << "\nenter encryption key: ";
                cin >> e;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(INT64_MAX, '\n');
                    cout << "[error: invalid input]\n\n";
                } else {
                    break;
                }
            }

            while (true)
            {
                cout << "enter decryption key: ";
                cin >> d;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(INT64_MAX, '\n');
                    cout << "[error: invalid input]\n";
                } else {
                    break;
                }
            }
            break;
        }
        else if (choice == "Y" || choice == "y" || choice == "Yes" || choice == "yes")
        {

            e = calculateE(t);
            d = calculateD(e, t);
            break;

        }
        else
            cout << "[error: invalid choice]\n";
    }


    cout << "\npublic keys { n = " << n << ", e = " << e << " }";
    cout << "\nprivate keys { n = " << n << ", d = " << d << " }" << endl;

    key_file  << "public keys { n = " << n << ", e = " << e << " }" <<
                 "\nprivate keys { n = " << n << ", d = " << d << " }" << endl;

    while(true)
    {
        cout << "\navailable options:\n";
        cout << "[E] encryption" << endl;
        cout << "[D] decryption" << endl;
        cin >> choice;

        if (choice == "E" || choice == "e")
        {
            cout << "[encryption]\n";
            inputText = rsa_encrypt(e, n, &inputText[0], fileCrypt);
            cout << "\nciphertext: " << inputText << endl;
            break;
        }
        else if (choice == "D" || choice == "d")
        {
            cout << "[decryption]\n";
            inputText = rsa_decrypt(d, n, &inputText[0], fileCrypt);
            cout << "\ndecrypted text: " << inputText << endl;
            break;
        } else
            cout << "[error: invalid choice]\n";
    }
    return 0;
}

#endif
