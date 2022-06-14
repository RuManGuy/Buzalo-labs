#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <optional>
#include <Windows.h>
#include <algorithm>

#include "dict.h"
#include "toLowercase.h"

using namespace std;
using namespace regex_constants;

/*
* "Google Problem"
* 
* Для работы нужен С++ 17
* 
* InnerDict словарь:
* key - слово (целиком, в нижнем регистре)
* value - количество этого слова в тексте
* 
* DoubleDict словарь:
* key - сочетание из 3+ букв
* value - InnerDict
* 
* На этапе подготовки перебираю все слова в тексте
* (словом считается любые не пробельные символы идущие подряд),
* очищаю слово от всего кроме русских и английских букв (простите, французы)
* и перебираю все возможные комбинации от 3 до *длина слова* букв:
* 1) Взял комбинацию, условно, comb от слова combination
* 2) В DoubleDict по ключу comb запихнул InnerDict (если не было)
* 3) В этом InnerDict по ключу combination увеличиваю на 1 значение (если нет ставлю единицу)
* 
* Затем начинается этап обработки запросов от пользователя:
* 1) Пользователь вводит comb
* 2) Из DoubleDict берём значение по ключу comb (это InnerDict)
* 3) Если InnerDict есть, превращаем его в массив пар InnerDict::Pair
* 4) Сортируем массив по убыванию количества слов и выводим до 20 первых слов (их может быть меньше)
*/

using InnerDict = Dict<int>;
using DoubleDict = Dict<InnerDict>;

/*
* text.txt - война и мир на русском, нашёл где-то на отшибах интернета (не знаю, полная ли)
* 3-6 секунд обработки и ест 350 мб ОЗУ
* 
* text_en.txt - война и мир на английском, нашёл в исходниках NVIDIA CUDA
* https://github.com/NVIDIA/cuda-samples/blob/master/Samples/0_Introduction/c%2B%2B11_cuda/warandpeace.txt
* 
* 2-4 секунды обработки и ест 220 мб ОЗУ
* очень странно, т.к. файл больше чем русская версия
*/
const string fileName = "text_en.txt";

const regex notLettersRegex("[^a-zA-Zа-яА-Я]", ECMAScript);

/*
* В DoubleDict ищем InnerDict по ключу subStr
* (если нет, создаём)
* Увеличиваем на 1 значение по ключу fullWord в InnerDict
*/
void incrementWordCount(DoubleDict& d, string subStr, string fullWord) {
    optional<InnerDict> foundDictOpt = d.find(subStr);

    if (foundDictOpt.has_value()) {
        optional<int> curentCountOpt = foundDictOpt->find(fullWord);

        foundDictOpt->insert(fullWord, curentCountOpt.value_or(0) + 1);
    }
    else {
        InnerDict newInnerDict;

        newInnerDict.insert(fullWord, 1);

        d.insert(subStr, newInnerDict);
    }
}

bool comparePairs(InnerDict::Pair p1, InnerDict::Pair p2) {
    return p1.second > p2.second;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DoubleDict d = DoubleDict(11311);

    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        cout << "unable to open file";

        return 0;
    }

    string tempStr;
    string word;
    string subStr;
    size_t strLen;

    // Считываю все слова из файла
    while (file >> tempStr) {
        // Очищаю от не букв и привожу к нижнему регистру
        word = regex_replace(tempStr, notLettersRegex, "");
        word = toLowercase(word);

        strLen = word.length();

        // Слова 2 и меньше длины игнорируем (по условию задачи)
        if (strLen < 3) {
            continue;
        }

        /*
        * Перебираем все возможные комбинации из 3+ букв в слове
        * Пример:
        * Слово - comb:
        * comb
        * com
        * omb
        */
        for (int n = strLen; n >= 3; n--) {
            for (int i = 0; i + n <= strLen; i++) {
                subStr = word.substr(i, n);

                incrementWordCount(d, subStr, word);
            }
        }
    }

    cout << endl << "Gich Vladimir Stanislavovich 020303-AISa-o21" << endl;
    cout << "Prepared" << endl;

    string searchStr;

    while (true) {
        cout << "Enter substring (min 3 letter): " << endl;
        cin >> searchStr;

        if (searchStr.length() < 3) {
            cout << "Must be 3+ letters" << endl;

            continue;
        }

        searchStr = toLowercase(searchStr);

        // Ищу InnerDict в DoubleDict по подстроке
        optional<InnerDict> foundDictOpt = d.find(searchStr);

        if (foundDictOpt.has_value()) {
            InnerDict::List dictList = foundDictOpt->convertToList();

            InnerDict::Pair* arr = new InnerDict::Pair[dictList.size()];

            // Создаю массив
            int k = 0;
            for (auto it = dictList.begin(); it != dictList.end(); it++) {
                arr[k++] = *it;
            }
            
            // Сортирую в порядке возрастания
            for (int i = 1; i < k; ++i)
            {
                for (int j = 0; j < k - i; j++)
                {
                    if (arr[j].second < arr[j + 1].second)
                    {
                        InnerDict::Pair t = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = t;
                    }
                }
            }

            // Выводим до 20 слов
            int countToShow = k > 20 ? 20 : k;
            for (int i = 0; i < countToShow; i++) {
                cout << arr[i].first << ": " << arr[i].second << endl;
            }

            delete[] arr;
        }
    }
}
