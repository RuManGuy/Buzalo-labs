#include <iostream>
#include <vector>
#include <stack>

#include "CustomStack.h"

using namespace std;

/*
* Чтобы изменить реализацию стека нужно передать сюда одно из трёх значений:
* int* - реализация через обычный массив
* list - реализация через односвязный список (описан в CustomStack.h)
* stack<int> - реализация через стек из STL (да, стек реализован с помощью стека)
*/
//using Stack = CustomStack<int*>;
using Stack = CustomStack<list>;
//using Stack = CustomStack<stack<int>>;
using CubeRow = vector<Stack*>;
using Cube = vector<CubeRow>;

/*
    Берём половину элементов из стека "from"
    и запихиваем в стек "to" в обратном порядке

    Было:
    from: 1, 2, 3, 4
    to:   -

    Станет:
    from: 1, 2
    to:   4, 3
*/
void reverseHalf(Stack* from, Stack* to, int depth) {
    for (int i = 0; i < depth / 2; i++) {
        to->push(from->pop());
    }
}

/*
    4 4 0 0
    4 4 0 0
    0 0 0 0
    0 0 0 0

    Разворачивается и становится:

    2 2 0 0
    2 2 0 0
    2 2 0 0
    2 2 0 0
*/
void expandToBottom(Cube cube, int cubeSide, int bottomCount, int depth) {
    int subside = 1 << bottomCount; // 1, 2, 4, 8, 16, ...

    for (int i = 0; i < subside; i++) {
        for (int j = 0; j < subside; j++) {
            reverseHalf(cube[subside - 1 - i][j], cube[subside + i][j], depth);
        }
    }
}

/*
    2 2 0 0
    2 2 0 0
    2 2 0 0
    2 2 0 0

    Разворачивается и становится:

    1 1 1 1
    1 1 1 1
    1 1 1 1
    1 1 1 1
*/
void expandToRight(Cube cube, int cubeSide, int rightCount, int depth) {
    int height = 2 << rightCount; // 2, 4, 8, 16, ...
    int width = 1 << rightCount; // 1, 2, 4, 8, ...

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            reverseHalf(cube[i][width - 1 - j], cube[i][width + j], depth);
        }
    }
}

void printCubeIn2d(Cube cube, int cubeSide) {
    for (int i = 0; i < cubeSide; i++) {
        for (int j = 0; j < cubeSide; j++) {
            cout << cube[i][j]->getTop() << " ";
        }

        cout << endl;
    }
}

int main()
{
    const int k = 3;
    const int cubeSide = 1 << k;
    const int total = cubeSide * cubeSide; // сколько всего клеточек

    // трёхмерный массив
    // x - ширина, y - высота, z - стэк, глубина
    // По x,y находятся "стопки" чисел, изначально она одна в (0, 0)
    // и снаружи вглубь идёт как 1, 2, 3, 4, ..., total

    Cube cube(cubeSide);

    for (int i = 0; i < cubeSide; i++) {
        cube[i] = *new CubeRow(cubeSide);

        // Я пытался создавать стек перед тем как вызывать reverseHalf,
        // передавая реально необходимый размер, но по какой-то причине
        // код переставал работать (грешу на волшебные "оптимизации" Visual Studio)
        // Поэтому в случае реализации через массив приходится тратить много памяти
        for (int j = 0; j < cubeSide; j++) {
            cube[i][j] = new Stack(total);
        }
    }

    // заполняем исходную стопку (0, 0) от 1 до total
    for (int k = 0; k < total; k++) {
        cube[0][0]->push(k + 1);
    }

    // depth - количество слоёв у "стопок"
    int depth = total;
    // сколько раз развернули вниз
    int bottomCount = 0;
    // сколько раз развернули вправо
    int rightCount = 0;

    while (depth != 1) {
        expandToBottom(cube, cubeSide, bottomCount, depth);
        depth /= 2;

        expandToRight(cube, cubeSide, rightCount, depth);
        depth /= 2;

        bottomCount++;
        rightCount++;
    }

    printCubeIn2d(cube, cubeSide);

    return 0;
}
