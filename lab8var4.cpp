#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using std::cout;
using std::cin;

struct pearl { // структура для жемчуга
    std::string colour;
    bool first;
    
    pearl(const std::string& c = "белый", bool f = false) : colour(c), first(f) {}
};

struct lock { // стр-ра для замка
    std::string metal;
    
    lock(const std::string& m = "сталь") : metal(m) {}
    
    
};

struct jewerly { // стр-ра для украшения
    lock* lockk;
    std::vector<pearl*> pearls;
    bool com;
    std::string name;
    
    jewerly(const std::string& n = "без названия") : lockk(nullptr), com(false), name(n) {}
};

class jewerlymen {
private:
    std::vector<jewerly*> catalog;
    std::vector<lock*> locks;
    std::vector<pearl*> pearls;
public:
    
    void clearall() {
        for (jewerly* jewerlly : catalog) {
            delete jewerlly;
        }
        catalog.clear();
        for (lock* lockk : locks) {
            delete lockk;
        }
        locks.clear();
        for (pearl* pearll : pearls) {
            delete pearll;
        }
        pearls.clear();
        
        cout << "память освобождена" << std::endl;
    }
    
    ~jewerlymen () {
        clearall();
    }
    
    lock* noviyzamok(const std::string& metal = "сталь") {
        lock* newlock = new lock(metal);
        locks.push_back(newlock);
        return newlock;
    }
    
    pearl* novayapearl(const std::string& colour = "белый", bool first = false) {
        pearl* newpearl = new pearl(colour,first);
        pearls.push_back(newpearl);
        return newpearl;
    }
    
    jewerly* novoyejewerly(const std::string& name = "без названия") {
        jewerly* newjewerly = new jewerly(name);
        catalog.push_back(newjewerly);
        return newjewerly;
    }
    
    void zamokvjewerly(jewerly* jewerlly, lock* lockk) {
        if (jewerlly && lockk) {
            jewerlly->lockk = lockk;
            jewerlly->com = !jewerlly->pearls.empty();
        }
    }
    
    void pearlvjewerly(jewerly* jewerlly, pearl* pearll) {
        if (jewerlly && pearll) {
            jewerlly->pearls.push_back(pearll);
            jewerlly->com = (jewerlly->lockk != nullptr);
        }
    }
    
    void prosmotrvsego() {
        if (catalog.empty()) {
            cout << "нечего смотреть :(\n";
            return;
        }
        
        cout << "--- просмотр всех украшений ---" << std::endl;
        for (size_t i = 0; i < catalog.size();i++) {
            cout << "украшение: " << i+1 << ". " << catalog[i]->name << std::endl;
            cout << "статус: " << (catalog[i]->com ? "завершено" : "незавершено") << std::endl;
            if (catalog[i]->lockk) {
                cout << "замок: " << catalog[i]->lockk->metal << std::endl;
            } else {
                cout << "замок отсутствует :(" << std::endl;
            }
            cout << "жемчужены: " << catalog[i]->pearls.size() << "штука" << std::endl;
            for (size_t j = 0; j < catalog[i]->pearls.size();j++) {
                cout << " " << j+1 << ". ";
                if (catalog[i]->pearls[j]->first) {
                    cout << "первый жемчуг: ";
                } else {
                    cout << "не первый жемчуг: ";
                }
                cout << "цвет: " << catalog[i]->pearls[j]->colour << std::endl;
            }
            cout << std::endl;
        }
    }
    
    jewerly* sozdanyejewerly() {
        cout << "--- создание нового украшения ---" << std::endl;
        std::string name;
        
        cout << "введите название украшения: ";
        cin.ignore();
        getline(cin,name);
        
        jewerly* newjewerly = novoyejewerly(name);
        
        cout << "создание замка:" << std::endl;
        cout << "выберите металл\n";
        cout << "1. серебро\n2. золото\n3. сталь\nваш выбор: ";
        int metch; cin >> metch;
        
        std::string metal;
        
        switch (metch) {
            case 1:
                metal = "серебро"; break;
            case 2:
                metal = "золото"; break;
            case 3:
                metal = "сталь"; break;
            default:
                metal = "сталь";
                break;
        }
        lock* lockk = noviyzamok(metal);
        zamokvjewerly(newjewerly, lockk);
        
        int addmore = 1;
        int pearlc = 0;
        bool f = false;
        
        while (addmore == 1) {
            pearlc++;
            
            cout << "жемчужена " << pearlc << ":" << std::endl;
            cout << "выберите цыет:\n";
            cout << "1. белый\n2.черный\n3.розовый\nваш выбор: ";
            int cch; cin >> cch;
            
            std::string colour;
            switch (cch) {
                case 1:
                    colour = "белый"; break;
                case 2:
                    colour = "черный"; break;
                case 3:
                    colour = "розовый"; break;
                default:
                    colour = "белый";
                    break;
            }
           
            pearl* pearll = novayapearl(colour);
            pearlvjewerly(newjewerly, pearll);
            
            cout << "добавить еще жемчужину? (1. да/2. нет): ";
            cin >> addmore;
            
        }
        cout << "украшение " << name << "создано ;)" << std::endl;
        return newjewerly;
    }
    
    void vneshniyvid() {
        cout << "--- вывод украшения по замку ---" << std::endl;
        if (catalog.empty()) {
            cout << "пусто и грустно, нечего выводить :(" << std::endl;
            return;
        }
        
        cout << "выберите тип замка:\n";
        cout << "1. серебро\n2. золото\n3. сталь\nваш выбор: ";
        int ch; cin >> ch;
        
        std::string selmetal;
        switch (ch) {
            case 1:
                selmetal = "серебро";break;
            case 2:
                selmetal = "золото";
                break;
            case 3:
                selmetal = "сталь"; break;
            default:
                selmetal = "";
                break;
        }
        bool found = false;
        
        for (size_t i = 0; i < catalog.size();i++) {
            jewerly* jewerlly = catalog[i];
            
            if (jewerlly->lockk && (selmetal.empty() || jewerlly->lockk->metal == selmetal)) {
                found = true;
                cout << "украшение " << jewerlly->name << ":\n";
                cout << "замок: " << jewerlly->lockk->metal << "\n";
                
                if (jewerlly->pearls.empty()) {
                    cout << "украшение без жемчуга\n";
                } else {
                    for (size_t j = 0; j < jewerlly->pearls.size();j++) {
                        if (jewerlly->pearls[j]->first) {
                            cout << "первый жемчуг " << jewerlly->pearls[j]->colour << " \n";
                        } else {
                            cout << "не первый жемчуг " << jewerlly->pearls[j]->colour << "\n";
                        }
                    }
                }
                cout << "замок " << jewerlly->lockk->metal << std::endl;
                cout << std::endl;
            }
        }
        
        if (!found && !selmetal.empty()) {
            cout << "украшений с замком из " << selmetal << " не найдено" << std::endl;
        }
    }
    void vivodnezjewerly() {
        cout << "--- незавершенные украшения ---" << std::endl;
        bool found = false;
        
        for (size_t i = 0; i < catalog.size();i++) {
            jewerly* jewerlly = catalog[i];
            if (!jewerlly->com) {
                found = true;
                cout << "украшение " << jewerlly->name << "\n";
                if (!jewerlly->lockk) {
                    cout << "причина: нет замка :(" << std::endl;
                } else if (jewerlly->pearls.empty()) {
                    cout << "причина: нет жемчуга :(" << std::endl;
                } else {
                    cout << "причина: помечено как незавершенное" << std::endl;
                }
                
                if (jewerlly->lockk) {
                    cout << "замок: " << jewerlly->lockk->metal << "\n";
                }
                cout << "жемчужин: " << jewerlly->pearls.size() << " штука" << std::endl;
                cout << std::endl;
            }
        }
        if (!found) {
            cout << "нет незавершенных украшений ;)" << std::endl;
        }
    }
    void deletejewerly(int ind) {
        if (ind >= 0 && ind <(int)catalog.size()) {
            jewerly* jewerlly = catalog[ind];
            catalog.erase(catalog.begin()+ind);
            delete jewerlly;
            cout << "украшение удалено" << std::endl;
        } else {
            cout << "неверный индекс" << std::endl;
        }
    }
    size_t kolichestvojewerly() const {
        return catalog.size();
    }
    
    jewerly* jewerlypoindex(size_t ind) {
        if (ind < catalog.size()) {
            return catalog[ind];
        } else {
            return nullptr;
        }
    }
    void initializ() {
        cout << "добавление тестовых украшений" << std::endl;
        
        lock* silverlock = noviyzamok("серебро");
        lock* goldlock = noviyzamok("золото");
        
        pearl* whitepearl = novayapearl("белый",true);
        pearl* blackpearl = novayapearl("черный",false);
        pearl* pinkpearl = novayapearl("розовый",false);
        
        jewerly* j1 = novoyejewerly("ожерелье");
        zamokvjewerly(j1, goldlock);
        pearlvjewerly(j1, whitepearl);
        pearlvjewerly(j1, blackpearl);
        pearlvjewerly(j1, pinkpearl);
        j1->com = true;
        
        jewerly* j2 = novoyejewerly("незаконченные бусы");
        pearl* blackpearl2 = novayapearl("черный",true);
        pearlvjewerly(j2, blackpearl2);
        j2->com = false;
        
        jewerly* j3 = novoyejewerly("у меня закончилась фантазия");
        zamokvjewerly(j3, silverlock);
        j3->com = false;
        
        jewerly* j4 = novoyejewerly("помогите"); // замок тот же что и у j1
        zamokvjewerly(j4, goldlock);
        pearl* pinkpearl2 = novayapearl("розовый",true);
        pearlvjewerly(j4, pinkpearl2);
        j4->com = true;
        
        cout << "создано " << catalog.size() << " тестовых украшений" << std::endl;
        
    }
};

void menu() {
    cout << "--- каталог украшений ---" << std::endl;
    cout << "1. посмотреть все украшения\n";
    cout << "2. создать новое украшение\n";
    cout << "3. вывести внешний вид украшений (по замку)\n";
    cout << "4. вывести незавершенные украшения\n";
    cout << "5. удалить украшение\n";
    cout << "6. очистить все\n";
    cout << "7. добавить тестовые украшения\n";
    cout << "0. выход\n";
    cout << "выберите действие: ";
}

int main() {
    jewerlymen maneger;
    int ch;
    
    do {
        menu();
        cin >> ch;
        
        switch (ch) {
            case 0:
                cout << "выход из программы :(" << std::endl;
                break;
            case 1:
                maneger.prosmotrvsego();
                break;
            case 2:
                maneger.sozdanyejewerly();
                break;
            case 3:
                maneger.vneshniyvid();
                break;
            case 4:
                maneger.vivodnezjewerly();
                break;
            case 5: {
                cout << "введите номер украшения для удаления (1-" << maneger.kolichestvojewerly() << "):";
                int ind;
                cin >> ind;
                maneger.deletejewerly(ind-1);
            }
                break;
            case 6:
                maneger.clearall();
                break;
            case 7:
                maneger.initializ();
                break;
            default:
                cout << "неверный выбор\n";
                break;
        }
    } while (ch != 0);
    
    return 0;
}
