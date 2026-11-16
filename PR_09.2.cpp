//Обчислити значення w.Функції min, max, піднесення до квадрата та
//виведення результату задано макросами.Гілку обчислень обирає препроцесор
//за значенням z(директиви умовної компіляції).
//
//| min((x + y) ^ 2, (x - z) ^ 2), z > 3
//w = |
//| max(xy + yz, (zx + yz) ^ 2), z <= 3

#include <stdio.h>
#include <iostream>
using namespace std;

// Значення z, за яким препроцесор обирає гілку обчислень.
// Можна змінити тут або передати при компіляції: -DZ=2
#ifndef Z
#define Z 5
#endif

#define SQR(a)    ((a)*(a))                    // макрос піднесення до квадрата
#define MIN(a,b)  (((a)<(b))?(a):(b))          // макрос мінімуму з двох чисел
#define MAX(a,b)  (((a)>(b))?(a):(b))          // макрос максимуму з двох чисел

// виведення повідомлення та значення дійсного числа
// символ '#' перетворює аргумент макроса на рядок
#define PRINTR(w) do { puts("rezult :"); \
                       printf(#w"=%f\n",(double)(w)); } while(0)

// Обчислює w(x, y) для z = Z. Гілка обчислень обирається препроцесором.
double calcW(double x, double y)
{
    double z = Z;       // значення z задане макросом
    double w;

#if Z > 3               // якщо z > 3 – компілюється ця гілка
    w = MIN(SQR(x + y), SQR(x - z));
#else                   // якщо z <= 3 – компілюється ця гілка
    w = MAX(x * y + y * z, SQR(z * x + y * z));
#endif                  // завершення блоку умовної компіляції

    return w;
}

#ifndef UNIT_TEST       // під час unit-тесту main не компілюється
int main()
{
    puts("Lab 9.2. Variant 20. Using macros and preprocessing directives");

    double x, y, w;    // змінні для розрахунків
    char ch;           // відповідь, чи продовжувати виконання програми

    do
    {
        printf("z = %d (set by macro Z)\n", Z);

#if Z > 3
        puts("branch: z > 3 :  w = min((x+y)^2, (x-z)^2)");
#else
        puts("branch: z <= 3 : w = max(xy+yz, (zx+yz)^2)");
#endif

        cout << "x = ? "; cin >> x;
        cout << "y = ? "; cin >> y;

        w = calcW(x, y);       // виклик функції обчислення
        PRINTR(w);             // макрос виведення результату

        cout << "Repeat? y/n "; cin >> ch;
    } while (ch == 'y');

    return 0;
}
#endif