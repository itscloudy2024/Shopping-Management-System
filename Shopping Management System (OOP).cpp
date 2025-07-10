#include <iostream>
#include <string>
using namespace std;

//Sadeen
template <typename T>
void showInfo(const T& item) {
    item.display();
}

struct Shipmentinfo {
    string shipment_type;
    string address;
};

class Customer {
private:
    string name;
    string email;
    string phone;
    Shipmentinfo shipment;

public:
    Customer() {}
    Customer(string n, string e, string p, Shipmentinfo s) : name(n), email(e), phone(p), shipment(s) {}

    void display() const {
        cout << "---- Customer Information ----" << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Shipment: " << shipment.shipment_type << endl;
        cout << "Address: " << shipment.address << endl;
    }

    friend ostream& operator<<(ostream& os, const Customer& c) {
        os << "Name: " << c.name << "\nEmail: " << c.email << "\nPhone: " << c.phone
           << "\nShipment: " << c.shipment.shipment_type << "\nAddress: " << c.shipment.address;
        return os;
    }
};

class Product {
protected:
    string name;
    double price;
    int quantity;

public:
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}
    virtual void display() const = 0;
    virtual string getType() const = 0;
    double getPrice() const { return price; }
    string getName() const { return name; }
    virtual ~Product() {}

    friend ostream& operator<<(ostream& os, const Product& p) {
        os << p.name << " - $" << p.price << " Qty: " << p.quantity;
        return os;
    }
};

class Lips : public Product {
private:
    string shade;

public:
    Lips(string n, double p, int q, string s) : Product(n, p, q), shade(s) {}

    void display() const override {
        cout << "Lip Product - " << name << " (Shade: " << shade << "), $" << price << " Qty: " << quantity << endl;
    }
    string getType() const override {
        return "Lips";
    }
};

class Face : public Product {
private:
    string brand;

public:
    Face(string n, double p, string b, int q) : Product(n, p, q), brand(b) {}

    Face(string n, double p, int q) : Product(n, p, q), brand("Generic") {}

    void display() const override {
        cout << "Face Product - " << name << " (Brand: " << brand << "), $" << price << " Qty: " << quantity << endl;
    }

    string getType() const override {
        return "Face";
    }
};

class Eyes : public Product {
private:
    string feature;

public:
    Eyes(string n, double p, int q) : Product(n, p, q), feature("Standard") {}

    void display() const override {
        cout << "Eye Product - " << name << ", $" << price << " Qty: " << quantity << endl;
    }

    string getType() const override {
        return "Eyes";
    }
};

//Eman
class Cart {
private:
    Product* items[10];
    int count;

public:
    Cart() : count(0) {}

    void add_item(Product* p) {
        if (count < 10) {
            items[count++] = p;
        }
    }

    double total_cost() const {
        double total = 0;
        for (int i = 0; i < count; i++) {
            total += items[i]->getPrice();
        }
        return total;
    }

    void viewCart() {
        cout << "\n--- Your Cart ---\n";
        for (int i = 0; i < count; i++) {
            items[i]->display();
        }
        cout << "------------------\n";
    }


};

class Order {
private:
    static int ordercount;
    int orderID;
    Customer customer;
    Cart cart;
    string paymentType;

public:
    Order() {
        orderID = ++ordercount;
    }

    void set_details(Customer cust, Cart c, string payment) {
        customer = cust;
        cart = c;
        paymentType = payment;
    }

    void printReceipt() {
        cout << "===== Order Receipt 🛒🎀 =====" << endl;
        cout << "Order ID: " << orderID << endl;
        customer.display();
        cout << "Payment Type: " << paymentType << endl;
        cout << " Total Amount: " << cart.total_cost() << endl;
        cout << "==============================" << endl;
    }

    static void show_total_orders() {
        cout << " Total orders placed: " << ordercount << endl;
    }

};

int Order::ordercount = 0;

//Dania
class ShoppingSystem {
private:
    Product* products[10];
    int productCount;

public:
    ShoppingSystem() {
        productCount = 9;
        products[0] = new Face("Blush", 10.0, 15);
        products[1] = new Face("Foundation", 18.0, 12);
        products[2] = new Face("Bronzer", 10, 13);
        products[3] = new Lips("Lipstick", 10.0, 8, "Red");
        products[4] = new Lips("Lip Gloss", 12.0, 8, "Pink");
        products[5] = new Lips("Lip Liner", 5.0, 13, "Nude");
        products[6] = new Eyes("Mascara", 8.0, 26);
        products[7] = new Eyes("Eyeliner", 4.0, 9);
        products[8] = new Eyes("Eyeshadow Palette", 15.0, 7);
    }

    ~ShoppingSystem() {
        for (int i = 0; i < productCount; i++) delete products[i];
    }

    void displayCategory(int choice) const {
        for (int i = 0; i < productCount; i++) {
            if ((choice == 1 && dynamic_cast<Face*>(products[i])) ||
                (choice == 2 && dynamic_cast<Lips*>(products[i])) ||
                (choice == 3 && dynamic_cast<Eyes*>(products[i]))) {
                cout << i + 1 << ". ";
                products[i]->display();
            }
        }
    }

    Product* getProduct(int index) const {
        if (index >= 0 && index < productCount) return products[index];
        return nullptr;
    }
};

int main() {
    ShoppingSystem shop;
    Cart cart;

    cout << "Welcome to Our Makeup Store!" << endl;
    int choice;
    while (true) {
        cout << "\nSelect a category:\n";
        cout << "1. Face\n2. Lips\n3. Eyes\n4. Checkout\nChoice: ";
        cin >> choice;

        if (choice == 4) break;

        shop.displayCategory(choice);
        cout << "Enter product number to add to cart: ";
        int prodIndex;
        cin >> prodIndex;
        Product* selected = shop.getProduct(prodIndex - 1);
        if (selected) {
            cart.add_item(selected);
            cout << selected->getName() << " added to cart." << endl;
        } else {
            cout << "Invalid product number." << endl;
        }
    }

    cart.viewCart();

    string name, email, phone, shiptype, address;
    cout << "\nEnter your name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone: ";
    cin >> phone;
    cout << "Shipment type (Delivery/Pickup): ";
    cin >> shiptype;
    cout << "Address: ";
    cin >> address;

    Shipmentinfo ship = {shiptype, address};
    Customer customer(name, email, phone, ship);

    cin.ignore();
    string payment;
    cout << "Payment Method (Cash/Card): ";
    getline(cin, payment);

    Order order;
    order.set_details(customer, cart, payment);
    order.printReceipt();
    Order::show_total_orders();

    return 0;
}