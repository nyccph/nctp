#include <iostream>
#include <string>
using std::cin;
using std::cout;

class Potion {
    
private:
    
    std::string name;
    std::string opisaniye;
    double price;
    std::string base;
    double volume;
    
public:
    
    Potion() : name("unknown"), opisaniye("no"), price(0.0), base("water"), volume(0.0) {
        
        cout << "зелье по умолчанию ;)" << std::endl;
    }
    
    Potion(const std::string& name, const std::string& opisaniye, double price, const std::string& base, double volume) : name(name), opisaniye(opisaniye), price(price), base(base), volume(volume){
        
        cout << "создано зелье: " << name << std::endl;
    }
    
    Potion(const Potion& copy) : name(copy.name), opisaniye(copy.opisaniye), price(copy.price), base(copy.base), volume(copy.volume) {
        
        cout << "скопировано зелье: " << name << std::endl;
    }
    
    ~Potion() {
        cout << "зелье: " << name << " удалено :(" << std::endl;
    }
    
    std::string gn() const {return name;}
    std::string go() const {return opisaniye;}
    double gp() const {return price;}
    std::string gb() const {return base;}
    double gv() const {return volume;}
    
    void sp(double newprice) {
        if (newprice >= 0) {
            price = newprice;
            cout << "цена зелья " << name << " изменена на " << newprice << std::endl;
        } else {
            cout << "error :(" << std::endl;
        }
    }
    
    void info() const {
        cout << std::endl;
        cout << "--- информация о зелье ---" << std::endl;
        cout << std::endl;
        cout << "название: " << name << std::endl;
        cout << "описание: " << opisaniye << std::endl;
        cout << "цена: " << price << std::endl;
        cout << "база: " << base << std::endl;
        cout << "объем: " << volume << std::endl;
    }
    
    void changebase(const std::string& newbase) {
        if (!newbase.empty()){
            std::string oldbase = base;
            base = newbase;
            cout << "база зелья " << name << " изменена с " << oldbase << " на " << newbase << std::endl;
        } else {
            cout << "error :( " << std::endl;
        }
    }
    
    void ddrink() {
        const double drinksize = 10.0;
        if (volume >= drinksize) {
            volume -= drinksize;
            cout << "выпита фиксированная порция зелья " << name << " (" << drinksize << " мл)" << std::endl;
            cout << "осталось: " << volume << " мл" << std::endl;
        } else if (volume > 0) {
            cout << "все зелье выпито целиком " << std::endl;
            volume = 0.0;
        } else {
            cout << "зелье " << name << " empty!" << std::endl;
        }
    }
    
    double drink(double k) {
        if (k <= 0) {
            cout << "error :(" << std::endl;
            return volume;
        }
        if (k >= volume) {
            cout << "выпито все зелье " << name << " (" << volume << " мл)" << std::endl;
            volume = 0.0;
            return 0.0;
        } else {
            volume = volume - k;
            cout << "вы выпили " << k << " мл " << " зелья " << name << " осталось " << volume << " мл" << std::endl;
            return volume;
        }
    }
};

int main() {
    cout << "--- демонстрация ---" << std::endl;
    cout << std::endl;
    Potion helth ("здоровье","восстанавливает здоровье",100.0,"вода",150.0);
    helth.info();
    helth.sp(105.5);
    helth.changebase("спирт");
    helth.drink(80.0);
    helth.drink(70.0);
    helth.ddrink();
    
    Potion defaultp;
    defaultp.info();
    
    Potion copypotion(helth);
    copypotion.info();
    
    cout << "использование геттеров для copypotion" << std::endl;
    cout << "название: " << copypotion.gn() << std::endl;
    cout << "описание: " << copypotion.go() << std::endl;
    cout << "цена: " << copypotion.gp() << std::endl;
    cout << "база: " << copypotion.gb() << std::endl;
    cout << "объем: " << copypotion.gv() << std::endl;
    cout << std::endl;
    cout << "THE END " << std::endl;
    cout << std::endl;
    return 0;
 }
