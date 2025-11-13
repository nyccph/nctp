// помогите sos help
#include <iostream>
#include <vector>
using std::cin;
using std::cout;

void newmatr(int**& matr, int& row, int col, int* zmass, int& c) { // ф-я для удаления строк из матрицы
    
    if (matr == nullptr) {
        cout << "ошибка лол" << std::endl;
        return;
    } if (c == 0){
        cout << "нет 0" << std::endl;
        return;
        }
    for (int i = 0; i < c-1; i++) {
        for (int j = i+1; j < c; j++) {
            if (zmass[i] < zmass[j]) {
                int t = zmass[i];
                zmass[i] = zmass[j];
                zmass[j] = t;
            }
        }
    }
    
    for (int i = 0; i < c; i++) {
        int r = zmass[i];
        if (r < 0 || r >= row) continue;
        free(matr[r]);
        for (int j = r; j < row-1; j++) {
            matr[j] = matr[j+1];
        }
        row--;
    }
    if (row > 0) {
        int** t = (int**)realloc(matr, row * sizeof(int*));
        if (t != nullptr) matr = t;
    } else {
        free(matr);
        matr = nullptr;
    }
}

int* zz(int** matr, int row, int col, int& c) { // ф-я для массива с индексами строк в которых есть 0
    c = 0;
    int* mass = new int[row]();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matr[i][j] == 0) {
                mass[c] = i;
                c++;
                break;
            }
        }
    }
    return mass;
}

void rr(int** matr, int row, int col) { // ф-я для вывода матрицы
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << matr[i][j] << " ";
        }
        cout << std::endl;
    }
}

void p1() {
    int** mm = new int*[2];
    for (int i = 0; i < 2; i++) {
        mm[i] = new int[2];
    }
    do {
        cout << "A = " << std::endl; cin >> mm[0][0];
        if (mm[0][0] < 0) cout << "ты дурак введи положительное число" << std::endl;
    } while (mm[0][0] < 0);
    do {
        cout << "B = " << std::endl; cin >> mm[0][1];
        if (mm[0][0] < 0) cout << "ты дурак введи положительное число" << std::endl;
    } while (mm[0][1] < 0);
    cout << "C = " << std::endl; cin >> mm[1][0];
    cout << "D = " << std::endl; cin >> mm[1][1];
    
    int row = 2 + mm[0][0];
    int col = 2 + mm[0][1];
    
    int** matr = (int**)calloc(row, sizeof(int*));
        for (int i = 0; i < row; ++i) {
            matr[i] = (int*)calloc(col, sizeof(int));
        }
    
    for (int i = 0; i < row-2; i++) { //строки
        for (int j = 0; j < col-2; j++) { //столбцы
            matr[i][j] = i * mm[1][0] + j * mm[1][1];
        }
    }
    matr[row-2][col-2] = mm[0][0]; matr[row-2][col-1] = mm[0][1];
    matr[row-1][col-2] = mm[1][0]; matr[row-1][col-1] = mm[1][1];
    
    cout << "исходная матрица: " << std::endl;
    rr(matr, row, col); cout << std::endl;
    
    
    int c = 0;
    int* zmass = zz(matr, row, col, c);
    
    /* вариант 1 этой хуйни
     
    int** matr2 = (int**)calloc(col,sizeof(int*));
    for (int i = 0; i < col; i ++) {
        matr2[i] = (int*)calloc(row-c, sizeof(int));
    }
    
    for (int i = 0; i < row; i++) {
        bool flag = false;
        for (int j = 0; j < c; j++) {
            if (i == zmass[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            for (int h = 0; h < col; h++) {
                matr2[row2][h] = matr[i][h];
            }
            row2++;
        }
    }
     вариант 2 этой хуйни
     
    for (int i = 0; i < c - 1; i++) { //сортировка zmass по убыванию
        for (int j = 0; j < c - i - 1; j++) {
            if (zmass[j] < zmass[j + 1]) {
                int t = zmass[j];
                zmass[j] = zmass[j + 1];
                zmass[j + 1] = t;
            }
        }
    }
    
    for (int i = 0; i < c; i++) {
        int rowdel = zmass[i];
        delete[] matr[rowdel];
        for (int j = rowdel; j < row2-1; i++) {
            for (int h = 0; h < col; h++) {
                matr[i] = matr[i+1];
            }
        }
        row2--;
    }
    
    
    int** t = new int*[row2];
    for (int i = 0; i < row2; i++) {
        t[i] = matr[i];
    } */
    cout << "новая матрица: " << std::endl;
    newmatr(matr, row, col, zmass, c);
    if (c == row) cout << "все строки матрицы были удалены :(" << std::endl;
    
    if (matr != nullptr) {
        for (int i = 0; i < row; i++) {
            if (matr[i] != nullptr) {
                free(matr[i]);  // освобождаем каждую строку
                matr[i] = nullptr;
            }
        }
        free(matr);
        matr = nullptr;
    }
    
    if (zmass != nullptr) {
        delete [] zmass;
        zmass = nullptr;
    }
    if (matr != nullptr) {
        for (int i = 0; i < row; i++) {
            if (matr[i] != nullptr) {
                free(matr[i]);
                matr[i] = nullptr;
            }
        }
        free(matr);
        matr = nullptr;
    }
}

void p2() {
    int a, b;
    cout << "введите а: " << std::endl; cin >> a;
    cout << "введите b: " << std::endl; cin >> b;
    int* ptrA = new int(a);
    int * ptrB = new int(b);
    *ptrA *= 2;
    cout << "исходное значение a = " << a << ", после учеличения в 2 раза через указатель a = " << *ptrA << std::endl;
    int t = *ptrA;
    *ptrA = *ptrB;
    *ptrB = t;
    
    cout << "после обмена : *ptrA = " << *ptrA << ", *ptrB = " << *ptrB << std::endl;
    a = *ptrA; b = *ptrB;
    cout << "итоговые значения: a = " << a << ", b = " << b << std::endl;
    
    delete ptrA;
    delete ptrB;
}

int main() {
    p1();
    p2();
}
