// помогите sos help
#include <iostream>
#include <vector>
#include <cstdlib>
using std::cin;
using std::cout;

void newmatr(int**& mm, int& row, int col, int* zmass, int& c) { // ф-я для удаления строк из матрицы
    
    if (mm == nullptr) {
        cout << "ошибка лол" << std::endl;
        return;
    } if (c == 0){
        cout << "нет 0" << std::endl;
        return;
        }
    
    for (int i = 0; i < c; i++) {
        int r = zmass[i];
        if (r < 0 || r >= row) continue;
        free(mm[r]);
        for (int j = r; j < row-1; j++) {
            mm[j] = mm[j+1];
        }
        row--;
    }
    if (row > 0) {
        int** t = (int**)realloc(mm, row * sizeof(int*));
        if (t != nullptr) mm = t;
    } else {
        free(mm);
        mm = nullptr;
    }
    if (row == 0) {
        cout << "все строки матрицы были удалены :(" << std::endl;
    }
}

int* zz(int** mm, int row, int col, int& c) { // ф-я для массива с индексами строк в которых есть 0
    c = 0;
    int* mass = new int[row]();
    for (int i = row-1; i >= 0; i--) {
        for (int j = col-1; j >= 0; j--) {
            if (mm[i][j] == 0) {
                mass[c] = i;
                c++;
                break;
            }
        }
    }
    return mass;
}

void rr(int** mm, int row, int col) { // ф-я для вывода матрицы
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mm[i][j] << " ";
        }
        cout << std::endl;
    }
}

void p1() {
    int** mm = (int**)calloc(2, sizeof(int*));
    for (int i = 0; i < 2; i++) {
        mm[i] = (int*)calloc(2, sizeof(int));
    }
    do {
        cout << "A = " << std::endl; cin >> mm[0][0];
        if (mm[0][0] < 0) cout << "ты дурак введи положительное число" << std::endl;
    } while (mm[0][0] < 0);
    do {
        cout << "B = " << std::endl; cin >> mm[0][1];
        if (mm[0][1] < 0) cout << "ты дурак введи положительное число" << std::endl;
    } while (mm[0][1] < 0);
    cout << "C = " << std::endl; cin >> mm[1][0];
    cout << "D = " << std::endl; cin >> mm[1][1];
    
    int row = 2 + mm[0][0];
    int col = 2 + mm[0][1];
    
    int chC = mm[1][0]; int chD = mm[1][1];
    int chA = mm[0][0]; int chB = mm[0][1];
    
    mm = (int**)realloc(mm, row * sizeof(int*));
    for (int i = 2; i < row; i++) {
        mm[i] = (int*)calloc(col, sizeof(int));
    }
    
    for (int i = 0; i < 2; i++) {
        int oldch[2] = {mm[i][0],mm[i][1]};
        
        mm[i] = (int*)realloc(mm[i], col * sizeof(int));
        mm[i][col-2] = oldch[0];
        mm[i][col-1] = oldch[1];
        
        for (int j = 0; j < col-2; j++) {
            mm[i][j] = 0;
        }
    }
    
    for (int i = 0; i < row-2;i++) {
        for (int j = 0; j < col-2; j++) {
            mm[i][j] = i * chC + j * chD;
        }
    }
    mm[row-2][col-2] = chA;
    mm[row-2][col-1] = chB;
    mm[row-1][col-2] = chC;
    mm[row-1][col-1] = chD;
    
    cout << "исходная матрица: " << std::endl;
    rr(mm, row, col); cout << std::endl;
    
    
    int c = 0;
    int* zmass = zz(mm, row, col, c);
    
    cout << "новая матрица: " << std::endl;
    if (row > 0 && mm != nullptr) {
        newmatr(mm, row, col, zmass, c);
        rr(mm, row, col);
    } else {
        cout << "матрица пустая" << std::endl;
    }
    
    if (mm != nullptr) {
        for (int i = 0; i < row; i++) {
            if (mm[i] != nullptr) {
                free(mm[i]);  // освобождаем каждую строку
                mm[i] = nullptr;
            }
        }
        free(mm);
        mm = nullptr;
    }
    
    if (zmass != nullptr) {
        delete [] zmass;
        zmass = nullptr;
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
    return 0;
}
