#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Pizza {
public:
    Pizza(const string& name, const string& description, int diametr, double pprice) : name(name), description(description), diametr(diametr), pprice(pprice), saltn(0), cheesen(0) {}

    virtual double calculatePrice() const {
        double price = pprice;

        switch (diametr) {
        case 25:
            price *= 1;
            break;
        case 30:
            price *= 1.3;
            break;
        case 35:
            price *= 1.5;
            break;
        case 40:
            price *= 1.7;
            break;
        }

        price += saltn * 1;
        price += cheesen * 2.0;

        return price;
    }

    void addSalt(int count) {
        saltn += count;
    }

    void addCheese(int count) {
        cheesen += count;
    }

    virtual void printPizzaDetails() const {
        cout << "Название: " << name << endl << "Описание: " << description
            << endl << "Размер: " << diametr << endl << " Соль: " << saltn << endl << " Сыр: " << cheesen << endl << "Цена: " << calculatePrice() << " рублей " << endl;
    }

protected:
    string name;
    string description;
    int diametr;
    double pprice;
    int saltn;
    int cheesen;
};

class FourCheese : public Pizza {
public:
    FourCheese(int diametr)
        : Pizza("Четыре сыра", "Моцарелла, сыры чеддер и пармезан, фирменный соус", diametr, 450) {}
};

class Meat : public Pizza {
public:
    Meat(int diametr)
        : Pizza("Мясная", "Добавление сливочной курицы с соусом на выбор", diametr, 490) {}
};

class Pepperoni : public Pizza {
public:
    Pepperoni(int diametr)
        : Pizza("Пепперони", "Самая продаваемая пицца - с пепперони и томатами", diametr, 540) {}
};

class HamP : public Pizza {
public:
    HamP(int diametr)
        : Pizza("Ветчина", "Пицца с ветчиной и сыром на выбор", diametr, 520) {}
};

class Mushroom : public Pizza {
public:
    Mushroom(int diametr)
        : Pizza("Грибная", "Грибная пицца с курицей и соусом барбекю", diametr, 580) {}
};

class Order {
public:
    void addPizza(const Pizza& pizza) {
        pizzas.push_back(pizza);
    }

    void printOrder() const {
        cout << "Состав заказа: " << endl;
        double total_price = 0;
        for (const auto& pizza : pizzas) {
            pizza.printPizzaDetails();
            total_price += pizza.calculatePrice();
        }
        cout << "Сумма заказа: " << total_price << " руб. " << endl;
    }

private:
    vector<Pizza> pizzas;

};

int main() {

    setlocale(0, "");

choosep:

    Order order;

    cout << "Здравствуйте! Выберите пиццу (1 - Четыре сыра, 2 - Мясная, 3 - Пепперони, 4 - Ветчина, 5 - Грибная): " << endl;
    int choice;
    cin >> choice;

    int diametr;
    cout << "Введите диаметр пиццы (25, 30, 35, 40): ";
    cin >> diametr;

    Pizza* plPizza = nullptr;

    switch (choice) {
    case 1:
        plPizza = new FourCheese(diametr);
        break;
    case 2:
        plPizza = new Meat(diametr);
        break;
    case 3:
        plPizza = new Pepperoni(diametr);
        break;
    case 4:
        plPizza = new HamP(diametr);
        break;
    case 5:
        plPizza = new Mushroom(diametr);
        break; 
    }

    int salt, cheese;
    cout << "Посолить пиццу? (1 - да, 0 - нет): ";
    cin >> salt;
    if (salt == 1) {
        int salt;
        cout << "Введите порцию соли: ";
        cin >> salt;
        plPizza->addSalt(salt);
    }

    cout << "Добавить сыра? (1 - да, 0 - нет): ";
    cin >> cheese;
    if (cheese == 1) {
        int cheese;
        cout << "Введите количество сыра (в граммах): ";
        cin >> cheese;
        plPizza->addCheese(cheese);
    }

    order.addPizza(*plPizza);
    delete plPizza;

    char addPizz;
    cout << "Нажмите '+', если хотите заказать ещё одну пиццу, и '-', если это весь заказ: ";
    cin >> addPizz;
    if (addPizz == '+') goto choosep;

    order.printOrder();

    return 0;
}