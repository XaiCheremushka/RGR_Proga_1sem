#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <string>

using namespace std;



int poiskSim(const char str[]) {
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'ь')
        {
            return i;
        }
    }
}


/* Считает десятки и еденицы */
const char* schet10(unsigned int number)
{
    const char* strNum[] = { "Один", "Два", "Три", "Четыре", "Пять", "Шесть", "Семь", "Восемь", "Девять" };
    //const char* strNumLow[] = { "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
    const char* strDozens[] = { "Двадцать ", "Тридцать ", "Сорок ", "Пятьдесят ", "Шестьдесят ", "Семьдесят ", "Восемьдесят ", "Девяносто " };

    char strVr[30] = "";
    char str10[] = "надцать";

    
    if (number == 0)
        return "";
    else if (number < 10) 
         strcat(strVr, strNum[number-1]);
    else if (number < 20) {
        if (number == 10)
            strcat(strVr, "Десять ");
        else
            for (int i = 0; i < 9; i++) {
                if (number == i + 11 && number == 11) {
                    strcat(strVr, strNum[i]);
                    strcat(strVr, str10);
                    break;
                }
                else if (number == i + 11 && number == 12) {
                    strcat(strVr, "Две");
                    strcat(strVr, str10);
                    break;
                }
               
                else if (number == i + 11) {
                    strncat(strVr, strNum[i], poiskSim(strNum[i]));
                    strcat(strVr, str10);
                    break;
                }
            }
    }
    else {
        for (int doz = 30; doz <= 100; doz += 10) {
            if (number < doz) { //было <30
                if (number == doz - 10) { // было == 20
                    strcat(strVr, strDozens[doz / 10 - 3]); // было двадцать
                    break;
                }
                else
                    for (int i = 0; i < 9; i++) {
                        if (number == i + (doz-10+1)) { // было + 21
                            strcat(strVr, strDozens[doz / 10 - 3]); //было двадцать 
                            //strcat(strVr, strNumLow[i]); можно вернуть, но просто смотрится не красиво
                            strcat(strVr, strNum[i]);
                            break;
                        }
                    }
            }
        }
    }
    return strVr;
}

/* Считает сотни */
const char* schet100(unsigned int number) {
    
    const char* strHundr[] = { "Сто ", "Двести ", "Триста ", "Четыреста ", "Пятьсот ", "Шестьсот ", "Семьсот ", "Восемьсот ", "Девятьсот " };
    char strVr[200] = "";

    for (int hundr = 200; hundr <= 1000; hundr += 100) {
        if (number == 0)
            break;
        else if (number < 100) {
            strcat(strVr, schet10(number));
            break;
        }
        else if (number < hundr) {
            if (number == hundr - 100) {
                strcat(strVr, strHundr[hundr / 100 - 2]);
                break; 
            }
            else if (number == hundr-100 + (number%100)) {
                strcat(strVr, strHundr[hundr / 100 - 2]);
                strcat(strVr, schet10(number % 100));
                break;
            }
        }
    }

    return strVr;
}

/* Считает тысячи */
const char* schet1000(unsigned int number) {

    const char* strFouth[] = { " Тысяча ", " Тысячи ", " Тысяч "};
    const char* strZif[] = { "Одна", "Две", "Три", "Четыре"};
    char strVr[1000] = "";
    int c = (number / 1000) % 10;
    
    if (number == 0)
        return strVr;
    else if (c < 5 && c != 0 && (((number/1000)%100 > 19) || (number / 1000) % 100 < 11)) {
        for (int i = 0; i < 4; i++) {
            if (c == i + 1) {
                strcat(strVr, schet100((number / 10000) * 10));
                strcat(strVr, strZif[i]);
                (c == 1) ? strcat(strVr, strFouth[0]) : strcat(strVr, strFouth[1]);
                strcat(strVr, schet100(number % 1000));
                break;
            }
        }
    }
    else {
        strcat(strVr, schet100(number / 1000));
        strcat(strVr, strFouth[2]);
        strcat(strVr, schet100(number % 1000));
    }
    return strVr;
}


/* Считает миллионы */
const char* schetMln(unsigned int number) {

    const char* strMln[] = { " Миллион ", " Миллиона ", " Миллионов " };
    
    char strVr[1000] = "";
    int c = (number / 1000000) % 10;

    if (c < 5 && c != 0 && (((number / 1000000) % 100 > 19) || (number / 1000000) % 100 < 11)) {
        for (int i = 0; i < 4; i++) {
            if (c == i + 1) {
                strcat(strVr, schet100(number / 1000000));
                //strcat(strVr, strZif[i]);
                (c == 1) ? strcat(strVr, strMln[0]) : strcat(strVr, strMln[1]);
                strcat(strVr, schet1000(number % 1000000));
                break;
            }
        }
    }
    else {
        strcat(strVr, schet100(number / 1000000));
        strcat(strVr, strMln[2]);
        strcat(strVr, schet1000(number % 1000000));
    }
    return strVr;
}


int proverka(char strN[]) {
    //cout << sizeof(strN);
    for (int i = 0; i < 20; i++) {
        if ((int(strN[i]) < 48 || int(strN[i]) > 57) && int(strN[i]) != 0)
            return 0;
        else if (int(strN[i]) == '\0')
            return 1;
    } 
}


int main()
{
    setlocale(0, "RUS");

    int number;
    char strN[20];

    printf("Какое натуральное число вы хотите перевести в письменный вид?\n");
    scanf("%s", &strN);

    while (true) {
        
        if (proverka(strN) == 1) {
            number = atoi(strN);

            if (number == 0) {
                printf("0 - это не натуральное число!");
            }
            else if (number < 100) {
                printf("%s", schet10(number));
                break;
            }
            else if (number < 1000) {
                printf("%s", schet100(number));
                break;
            }
            else if (number < 1000000) {
                printf("%s", schet1000(number));
                break;
            }
            else if (number < 1000000000) {
                printf("%s", schetMln(number));
                break;
            }
            else {
                printf("Вы вышли за пределы подсчета программы) Введите число до 1 миллиарда");
            }
        }
        else
            printf("Некорректный ввод!");
        
        printf("\nВведите НАТУРАЛЬНОЕ ЧИСЛО: \n");
        scanf("%s", &strN);
    }

    _getch();
}

