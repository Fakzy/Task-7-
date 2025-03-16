#include <iostream>
#include <vector>
#include <string>

// Интерфейс наблюдателя
class IObserver {
public:
    virtual void update(const std::string& stockName, double price) = 0;
};

// Конкретный наблюдатель (инвестор)
class Investor : public IObserver {
private:
    std::string name;

public:
    Investor(const std::string& name) : name(name) {}

    void update(const std::string& stockName, double price) override {
        std::cout << name << " received update: " << stockName << " is now $" << price << std::endl;
    }
};

// Класс акции (субъект)
class Stock {
private:
    std::string name;
    double price;
    std::vector<IObserver*> observers;

public:
    Stock(const std::string& name, double price) : name(name), price(price) {}

    void attach(IObserver* observer) {
        observers.push_back(observer);
    }

    void detach(IObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setPrice(double newPrice) {
        price = newPrice;
        notify();
    }

    void notify() {
        for (IObserver* observer : observers) {
            observer->update(name, price);
        }
    }
};

// Клиентский код
int main() {
    // Создаем акцию
    Stock appleStock("AAPL", 150.0);

    // Создаем инвесторов
    Investor investor1("John");
    Investor investor2("Alice");

    // Подписываем инвесторов на акцию
    appleStock.attach(&investor1);
    appleStock.attach(&investor2);

    // Меняем цену акции (инвесторы получат уведомление)
    appleStock.setPrice(155.0);

    // Отписываем одного инвестора
    appleStock.detach(&investor1);

    // Меняем цену снова (только Alice получит уведомление)
    appleStock.setPrice(160.0);

    return 0;
}
