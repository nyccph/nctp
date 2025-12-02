#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using std::cout;
using std::cin;

class book {
public:
    std::string author;
    std::string title;
    int volume_number;
    int page_count;
    book* next_volume;
    
    book(const std::string& auth, const std::string& tit, int vol, int pages) : author(auth), title(tit), volume_number(vol), page_count(pages), next_volume(nullptr) {}
};

class bookm {
private:
    std::vector<book*> collect;
    std::vector<book*> readq;
public:
    void viewcollect() { // просмотр сочинений
        cout << "--- собрания сочинений ---" << std::endl;
        if (collect.empty()) {
            cout << "нет собраний сочинений :(" << std::endl;
            return;
        }
        for (book* bookk : collect) {
            cout << "автор: " << bookk->author << std::endl;
            
            book* current = bookk;
            while (current != nullptr && current->author == bookk->author) {
                cout << "- \"" << current->title << "\" - том " << current->volume_number << ", " << current->page_count << " стр." << std::endl;
                current = current->next_volume;
            }
        }
    }
    void crnewcol() { // создание нового собрания книг 
        cout << "--- создание нового собрания ---" << std::endl;
        
        std::string author, title;
        int volume_number, page_count;
        
        cout << "введите фамилию автора: ";
        cin.ignore();
        getline(cin, author);
        
        cout << "введите название произведения: ";
        getline(cin, title);
        
        cout << "введите номер тома: ";
        cin >> volume_number;
        
        cout << "введите количество страниц: ";
        cin >> page_count;
        
        book* newbook = new book(author, title, volume_number, page_count);
        collect.push_back(newbook);
        
        cout << "собрание успешно создано ;)" << std::endl;
    }
    
    void fff() { // поиск самой сложной/легкой книги
        if (collect.empty()) {
            cout << "пусто и грустно, искать негде" << std::endl;
            return;
        }
        
        std::string author;
        int c;
        
        cout << "--- поиск по сложности ---" << std::endl;
        cout << "введите фамилию автора: ";
        cin.ignore();
        getline(cin, author);
        
        cout << "выберите критерий поиска: " << std::endl;
        cout << "1. самая сложная (наибольшее кол-во страниц)" << std::endl;
        cout << "2. самая легкая (наименьшее кол-во страниц)" << std::endl;
        cout << "ваш выбор: ";
        cin >> c;
        
        book* extbook = nullptr;
        
        for (book* authors : collect) {
            book* cur = authors;
            while (cur != nullptr) {
                if (cur->author == author) {
                    if (extbook == nullptr) {
                        extbook = cur;
                    } else {
                        if (c == 1 && cur->page_count > extbook->page_count) {
                            extbook = cur;
                        } else if (c == 2 && cur->page_count < extbook->page_count) {
                            extbook = cur;
                        }
                    }
                }
                cur = cur->next_volume;
            }
        }
        if (extbook == nullptr) {
            cout << "книги автора не найдены :(" << std::endl;
        } else {
            cout << "результат поиска: " << std::endl;
            if (c == 1) {
                cout << "самая сложная книга: " << std::endl;
            } else if (c == 2) {
                cout << "самая лкгкая книга: " << std::endl;
            }
            cout << "автор: " << extbook->author << std::endl;
            cout << "название: " << extbook->title << std::endl;
            cout << "том: " << extbook->volume_number << std::endl;
            cout << "кол-во страниц: " << extbook->page_count << std::endl;
        }
    }
    
    void addbook () { // создание новой книги в существующем собрании
        if (collect.empty()) {
            cout << "нет собраний сочинений :(" << std::endl;
            return;
        }
        
        std::string author, title;
        int page_count, volume_number;
        
        cout << "--- добавление книги в сборник ---" << std::endl;
        cout << "введите фамилию автора: ";
        cin.ignore();
        getline(cin, author);
        
        book* auth = nullptr;
        for (book* bookk : collect) {
            if (bookk->author == author) {
                auth = bookk;
                break;
            }
        }
        
        if (auth == nullptr) {
            cout << "автор " << author << " не найден. сначала надо создать сочинения этого автора ;)" << std::endl;
            return;
        }
        cout << "введите название произведения: ";
        getline(cin, title);
        cout << "введите номер тома: ";
        cin >> volume_number;
        
        book* th = auth;
        while (th != nullptr && th->author == author) {
            if (th->volume_number == volume_number) {
                cout << "error. том с номером " << volume_number << " уже существует у этого автора" << std::endl;
                return;
            }
            th = th->next_volume;
        }
        
        cout << "введите кол-во страниц: ";
        cin >> page_count;
        book* newbook = new book(author,title,volume_number,page_count);
        th = auth;
        book* prev = nullptr;
        while (th != nullptr && th->author == author && th->volume_number < volume_number) {
            prev = th;
            th = th->next_volume;
        }
        
        if (prev == nullptr) {
            newbook->next_volume = auth;
            auto it = find(collect.begin(),collect.end(),auth);
            if (it != collect.end()) {
                *it = newbook;
            }
        } else {
            newbook->next_volume = prev->next_volume;
            prev->next_volume = newbook;
        }
        
        cout << "книга добавлена в сборник ;)" << std::endl;
    }
    void ochered() { // создание очереди чтения
        cout << "--- создание очереди чтения ---" << std::endl;
        
        readq.clear();
        
        if (collect.empty()) {
            cout << "пусто и грустно, нечего добавлять в очередь :(" << std::endl;
            return;
        }
        cout << "доступные книги: " << std::endl;
        int bookc = 1;
        std::vector<book*> allb = getall();
        
        for (book* bookk : allb) {
            cout << bookc << ". " << bookk->author << " - " << bookk->title << ". том " << bookk->volume_number << ", " << bookk->page_count << " стр." << std::endl;
            bookc++;
        }
            cout << "введите номер книги для добавления в очередь (для завершения введите '0'): " << std::endl;
            int choise;
            while (true) {
                cout << "номер книги: ";
                cin >> choise;
                
                if (choise == 0) {
                    break;
                }
                if (choise < 1 || choise > allb.size()) {
                    cout << "книги с таким номером не существует :(" << std::endl;
                }
                
                book* sb = allb[choise-1];
                readq.push_back(sb);
                cout << "книга успешно добавлена в очередь: " << sb->author << " - " << sb->title << std::endl;
            }
        }
    void viewochered() {
        cout << "--- очередь чтения ---" << std::endl;
        if (readq.empty()) {
            cout << "очередб чтения пуста :(" << std::endl;
            return;
        }
        
        for (size_t i = 0; i < readq.size(); i++) {
            book* bookk = readq[i];
            cout << i+1 << ". " << bookk->author << " - " << bookk->title << ". том: " << bookk->volume_number << ", " << bookk->page_count << " стр. " << std::endl;
        }
    }
    void osn () {
        book* king1 = new book("Стивен Кинг","Смиренные сестры Элурии",1,144);
        book* king2 = new book("Стивен Кинг","Стрелок",2,384);
        book* king3 = new book("Стивен Кинг","Извлечение троих",3,480);
        book* king4 = new book("Стивен Кинг","Бесплодные земли",4,672);
        book* king5 = new book("Стивен Кинг","Колдун и кристалл",5,700);
        book* king6 = new book("Стивен Кинг","Ветер сквозь замочную скважину",6,352);
        book* king7 = new book("Стивен Кинг","Волки Кальи",7,800);
        book* king8 = new book("Стивен Кинг","Песнь Сюзанны",8,512);
        book* king9 = new book("Стивен Кинг","Темная башня",9,960);
        
        book* kafka1 = new book("Франц Кафка","Превращение",1,288);
        book* kafka2 = new book("Франц Кафка","Процесс",1,247);
        
        book* orwell1 = new book("Джордж Оруэлл","1984",1,308);
        book* orwell2 = new book("Джордж Оруэлл","Скотный двор",1,95);
        
        king1->next_volume = king2;
        king2->next_volume = king3;
        king3->next_volume = king4;
        king4->next_volume = king5;
        king5->next_volume = king6;
        king6->next_volume = king7;
        king7->next_volume = king8;
        king8->next_volume = king9;
        
        kafka1->next_volume = kafka2;
        
        orwell1->next_volume = orwell2;
        
        collect.push_back(king1);
        collect.push_back(kafka1);
        collect.push_back(orwell1);
        
        cout << "текстовые данные инициализированны: 3 собрания сочинений разных авторов ;)" << std::endl;
        
    }
private:
    std::vector<book*> getall () {
        std::vector<book*> allb;
        for (book* bookk : collect) {
            book* cur = bookk;
            while (cur != nullptr) {
                allb.push_back(cur);
                cur = cur->next_volume;
            }
        }
        return allb;
    }
public:
    ~bookm() {
        for (book* bookk : collect) {
            book* cur = bookk;
            while (cur != nullptr) {
                book* t = cur;
                cur = cur->next_volume;
                delete t;
            }
        }
    }
    void menu() {
        int c;
        do {
            cout << "--- меню ---" << std::endl;
            cout << "0. выход из программы :(" << std::endl;
            cout << "1. просмотр всех собраний" << std::endl;
            cout << "2. создание нового собрания" << std::endl;
            cout << "3. поиск самой сложной/легкой книги автора" << std::endl;
            cout << "4. добавление книги в существующий сборник" << std::endl;
            cout << "5. создать очередь чтения" << std::endl;
            cout << "6. показать очередь чтения" << std::endl;
            cout << "7. инициализировать текстовые данные" << std::endl;
            cout << "выберите пункт меню: ";
            cin >> c;
            
            switch (c) {
                case 0:
                    cout << "выход из программы :(" << std::endl;
                    break;
                case 1:
                    viewcollect();
                    break;
                case 2:
                    crnewcol();
                    break;
                case 3:
                    fff();
                    break;
                case 4:
                    addbook();
                    break;
                case 5:
                    ochered();
                    break;
                case 6:
                    viewochered();
                    break;
                case 7:
                    osn();
                    break;
                default:
                    cout << "неверный выбор..." << std::endl;
                    break;
            }
        } while (c != 0);
    }
        
};

int main() {
    bookm manager;
    manager.menu();
    return 0;
}

