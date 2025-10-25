#include <iostream>
using std::cout;
using std::cin;

// 1

/* int sumch(int x) { // ф-я для вычисления суммы цифр числа
    x = abs(x);
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
} */

int main() {
    const int n = 5;
    int mass[n];
    cout << "введите 5 чисел массива:" << std::endl;
    for (int i = 0; i < n; i++) cin >> mass[i];
    int sb25 = 0;
    for (int i = 0; i < n; i++) {
        int x = abs(mass[i]); int s = 0;
        while (x > 0) {
            s += x % 10;
            x /= 10;
        }
        if (s > 25) sb25 ++;
    }
    if (sb25 >= 2) {
        for (int i = 0; i < n; i++){
            if (mass[i] > mass[i+1]) std::swap(mass[i],mass[i+1]);
        }
        cout << "успешный успех, массив отсортирован по возрастанию ;)" << std::endl;
    } else {
        cout << "условие о сумме цифр числа, превышающей 25, не выполняется, массив остается в прежнем виде :(" << std::endl;
    }
    for (int i = 0; i < n; i++) cout << mass[i] << " ";
    cout << std::endl;
    
    
    // 2 Найти столбец с минимальным кол-вом положительных чисел и заменить все значения в нем на 100.
    
    const int k = 3, l = 4;
    int matr[k][l];
    cout << "введите элементы матрицы 3х4:" << std::endl;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < l; j++) {
            cin >> matr[i][j];
        }
    }
    cout << "матрица в исходном виде:" << std::endl;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < l; j++) {
            cout << matr[i][j] << " ";
        }
        cout << std::endl;
    }
    int mnpch = k + 1;
    int nst = 0;
    for (int j = 0; j < l; j++) {
        int pch = 0;
        for (int i = 0; i < k; i++) {
            if (matr[i][j] > 0) pch++;
        }
        if (pch < mnpch) {
            mnpch = pch;
            nst = j;
        }
    }
    
    for (int i = 0; i < k; i++) {
        matr[i][nst] = 100;
    }
    cout << "результат замены столбца:" << std::endl;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < l; j++) {
            cout << matr[i][j] << " ";
        }
        cout << std::endl;
    }
    cout << "столбец с минимальным количеством положительных чисел: " << nst + 1 << std::endl;
    return 0;
}
