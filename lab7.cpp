#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
using std::cout;
using std::cin;

void vvv(const std::vector<int>& vv) { // вывод массива
    cout << "[";
    for (int i = 0; i < vv.size(); i++) {
        cout << vv[i];
        if (i != vv.size() - 1) {
            cout << " ";
        }
    }
    cout << "]" << std::endl;
}

void findel(const std::vector<int>& vv, int x) { // поиск элементов в массиве
    std::vector<size_t> ind;
    for (size_t i = 0; i < vv.size(); i++){
        if (vv[i] == x) {
            ind.push_back(i);
        }
    }
    cout << "[";
    for (int i = 0; i < ind.size(); i++) {
        cout << ind[i];
        if (i != ind.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << std::endl;
}

void p1() {
    std::vector<int> vv;
    int c;
    
    do {
        cout << "меню:" << std::endl;
        cout << "0. выход" << std::endl;
        cout << "1. просмотр массива" << std::endl;
        cout << "2. добавить элемент в начало" << std::endl;
        cout << "3. добавить элемент в конец" << std::endl;
        cout << "4. очистка всего массива" << std::endl;
        cout << "5. поиск элемента в массиве" << std::endl;
        cout << "6. специальная операция" << std::endl;
        cout << "7. дополнительный 5 вариант" << std::endl;
        cout << "выберите пункт меню: ";
        cin >> c;
        
        switch (c) {
            case 0: {
                cout << "выход из программы :(" << std::endl;
                break;
            }
            case 1: {
                cout << "текущий массив: " << std::endl;
                vvv(vv);
                break;
            }
            case 2: {
                cout << "введите элемент для добавление в начало: ";
                int el; cin >> el;
                cout << "прежний массив: " << std::endl;
                vvv(vv);
                vv.insert(vv.begin(), el);
                cout << "новый массив: " << std::endl;
                vvv(vv);
                break;
            }
            case 3: {
                cout << "введите элемент для добавления в конец: ";
                int el; cin >> el;
                cout << "прежний массив: " << std::endl;
                vvv(vv);
                vv.insert(vv.end(), el);
                cout << "новый массив: " << std::endl;
                vvv(vv);
                break;
            }
            case 4: {
                cout << "массив до: " << std::endl;
                vvv(vv);
                vv.clear();
                cout << "массив после: " << std::endl;
                vvv(vv);
                break;
            }
            case 5: {
                cout << "введите элемент, который хотели бы найти: ";
                int el; cin >> el;
                cout << "индексы элемента " << el << ":";
                findel(vv, el);
                break;
            }
            case 6: {
                cout << "массив до: ";
                vvv(vv);
                
                if (vv.size() % 2 == 0) {
                    if (!vv.empty()) {
                        vv.erase(vv.begin());
                        cout << "удален 1й элемент :(" << std::endl;
                    }
                } else {
                    if (vv.size() > 4) {
                        size_t t = vv.size() - 4;
                        vv.erase(vv.begin(), vv.begin() + t);
                        cout << "удвлено " << t << "элементов с начала :(" << std::endl;
                    } else {
                        cout << "элементы удалить не получится, массив слишком мал" << std::endl;
                    }
                }
                cout << "массив после: ";
                vvv(vv);
                break;
            }
            case 7: {
                cout << "введите положительное число k: ";
                int k; cin >> k;
                if (k <= 0) {
                    cout << "число должно быть положительным дурак :( " << std::endl;
                    break;
                }
                cout << "масив до: ";
                vvv(vv);
                int n = 0; int sum = 0;
                while (sum + (n+1) <= k) {
                    n++;
                    sum += n;
                }
                bool ck = (sum == k);
                if (ck) {
                    if (n > 1) cout << "точно можно разбить: 1+...+" << n << "=" << k << std::endl;
                    std::vector<int> nech;
                    std::vector<int> ch;
                    for (int i = 0; i <= n; i++) {
                        if (i % 2 == 0) {
                            ch.push_back(i);
                        } else {
                            nech.push_back(i);
                        }
                    }
                    vv.insert(vv.begin(), nech.begin(), nech.end());
                    vv.insert(vv.end(), ch.begin(), ch.end());
                    
                    cout << "добавлены числа [";
                    for (size_t i = 0; i < nech.size(); i++) {
                        cout << nech[i];
                        if (i != nech.size() - 1) cout << " ";
                    }
                    cout << "] в начало и [";
                    for (size_t i = 0; i < ch.size(); i++) {
                        cout << ch[i];
                        if (i != ch.size() - 1) cout << " ";
                    }
                    cout << "] в конец" << std::endl;
                
                } else {
                    cout << "нельзя разбить " << k << " на нужную сумму" << std::endl;
                    cout << "продублируем числа на четных позициях в текущем массиве" << std::endl;
                    if (!vv.empty()) {
                        for (int i = (int)vv.size() - 1; i >= 0; i--) {
                            if (i % 2 == 1) {
                                vv.insert(vv.begin() + i, vv[i]);
                            }
                        }
                        cout << "пробублированы элементы на позициях: ";
                        for (size_t i = 0; i < vv.size(); i += 2) {
                            cout << i;
                            if (i+2 < vv.size()) cout << ", ";
                        }
                        cout << std::endl;
                    } else {
                        cout << "массив эмпти, дублировать нечего :(" << std::endl;
                    }
                }
                cout << "массив после: ";
                vvv(vv);
                break;
                /* else {
                   cout << "нельзя разбить точно, будем добавлять на четные позиции" << std::endl;
                   std::vector<int> ttt;
                   for (int i = 1; i <= n; i++) {
                   ttt.push_back(i);
                   }
                   std::vector<int> ch; // чет
                   std::vector<int> nech; // нечет
                   
                   for (size_t i = 0; i < ttt.size(); i++) {
                   if ((i+1) % 2 == 0) {
                   ch.push_back(ttt[i]);
                   } else {
                   nech.push_back(ttt[i]);
                   }
                   }
                   vv.insert(vv.begin(), ch.begin(), ch.end());
                   vv.insert(vv.begin(), nech.begin(),nech.end());
                   
                   cout << "добавлены: нечетные позиции [";
                   for (size_t i = 0; i < nech.size(); i++) {
                   cout << nech[i];
                   if (i != nech.size() - 1) cout << " ";
                   }
                   cout << "] в начало и четные [";
                   for (size_t i = 0; i < ch.size(); i++) {
                   cout << ch[i];
                   if (i != ch.size() - 1) cout << " ";
                   }
                   cout << "] в конец" << std::endl;
                   }
                   cout << "массив после: ";
                   vvv(vv);
                   break;
                   } */
            }
            default:
                cout << "хз что ты выбрал, попробуй еще раз" << std::endl;
                break;
        }
    } while (c != 0);
}

const int s = 10;

void vivod(const std::array<int, s>& mm, const std::string& st = "") {
    if (!st.empty()) {
        cout << st;
    }
    cout << "[";
    for (size_t i = 0; i < mm.size(); i++) {
        cout << mm[i];
        if (i != mm.size()-1) cout << " ";
    }
    cout << "]" << std::endl;
}

std::array<int, s> zz(std::array<int, s> mm, bool as = true) { // передача по значению СУКА СКОЛЬКОЛ МОЖНО КОДА ТО ЮЛЯТЬ
    cout << "адрес массива в ф-ии(по значению): " << &mm << std::endl;
    if (as) {
        std::sort(mm.begin(), mm.end());
    } else {
        std::sort(mm.rbegin(), mm.rend());
    }
    return mm;
}

void ss(std::array<int, s>& mm, bool as = true) { //ссылка
    cout << "адрес массива в ф-ии(по ссылке): " << &mm << std::endl;
    if (as) {
        std::sort(mm.begin(),mm.end());
    } else {
        std::sort(mm.rbegin(),mm.rend());
    }
}

void yk(std::array<int, s>* mm, bool as = true) { //указатель
    cout << "адрес массива в ф-ии(по указателю): " << mm << std::endl;
    if (as) {
        std::sort(mm->begin(),mm->end());
    } else {
        std::sort(mm->rbegin(),mm->rend());
    }
}

void p2() {
    srand((unsigned int)time(nullptr));
    std::array<int, s> mm;
    for (int i = 0; i < s; i++) {
        mm[i] = rand() % 21 - 10;
    }
    cout << "демонтсрация разницы при передаче значений в ф-ю:" << std::endl;
    vivod(mm, "исходный массив: ");
    cout << "адрес массива в p1: " << &mm << std::endl;
    
    std::array<int, s> mass = mm;
    
    cout << "1. передача по значению: " << std::endl;
    cout << "создается копия массива, при этом изменения не затрагивают оригинал" << std::endl;
    
    std::array<int, s> voz = zz(mm,true);
    std::array<int, s> ub = zz(mm,false);
    
    vivod(mm,"оригиналный массив: ");
    vivod(voz, "по возрастанию: ");
    vivod(ub, "по убыванию: ");
    cout << std::endl;
    
    cout << "2. передача по ссылке: " << std::endl;
    cout << "работа с оригинальным массивом, изменения сохраняются" << std::endl;
    std::array<int, s> mas = mm;
    vivod(mas, "массив до сортировки по ссылке: ");
    ss(mas, true);
    vivod(mas, "массив после сортировки по возрастанию: ");
    ss(mas,false);
    vivod(mas, "массив после сортировки по убыванию: ");
    cout << std::endl;
    
    cout << "3. передача по указателю: " << std::endl;
    cout << "работа с оригинальным массивом через указатель" << std::endl;
    
    std::array<int, s> masss = mm;
    vivod(masss,"массив до сортировки по указателю:");
    yk(&masss,true);
    vivod(masss, "массив после сортировки по возрастанию:");
    yk(&masss,false);
    vivod(masss,"массив после сортировки по убыванию");
    cout << std::endl;
    
    cout << "сравнение способов передачи:" << std::endl;
    cout << "1. по значению:" << std::endl;
    cout << "  - создается полная копия массива" << std::endl;
    cout << "  + оригинальный массив защищен от изменений" << std::endl;
    cout << "  - затраты памяти и времени на копирование" << std::endl;
    cout << "  - невозможно вернуть несколько значений" << std::endl;
    cout << "  использование: когда нужно сохранить оригинал неизменным" << std::endl << std::endl;
        
    cout << "2. по ссылке:" << std::endl;
    cout << "  - работа с оригинальным массивом" << std::endl;
    cout << "  + экономия памяти (не создается копия)" << std::endl;
    cout << "  + быстрее выполнение" << std::endl;
    cout <<  "  + можно изменить оригинальный массив" << std::endl;
    cout << "  использование: когда нужно изменить оригинальный массив" << std::endl << std::endl;
        
    cout << "3. по указателю:" << std::endl;
    cout << "  - работа с оригинальным массивом через адрес" << std::endl;
    cout << "  + экономия памяти" << std::endl;
    cout << "  + можно передать nullptr (проверка на валидность)" << std::endl;
    cout << "  - синтаксис сложнее (-> вместо .)" << std::endl;
    cout << "  использование: когда нужна проверка на nullptr или работа с C-style кодом" << std::endl;
}

int main() {
    p1();
    p2();
    return 0;
}
