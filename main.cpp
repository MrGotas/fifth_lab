//var 16
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Базовый класс устройства
class PeripheralDevice {
protected:
    int id;
    string brand;
    double price;

public:
    PeripheralDevice(int id, string brand, double price) : id(id), brand(brand), price(price) {}

    virtual void displayInfo() const = 0;

    virtual string getType() const = 0;

    int getId() const {
        return id;
    }

    string getBrand() const {
        return brand;
    }
};

// Класс наушников
class Headphones : public PeripheralDevice {
    string constructionType, mountingMethod;
public:
    Headphones(int id, string brand, double price, string constructionType, string mountingMethod) : PeripheralDevice(id, brand, price), constructionType(constructionType), mountingMethod(mountingMethod) {}

    void displayInfo() const override {
        cout << "ID: " << id << ", Brand: " << brand << ", Price: $" << price << ", Construction: " << constructionType << ", Mounting: " << mountingMethod << endl;
    }

    string getType() const override {
        return "Headphones";
    }
};

// Класс микрофона
class Microphone : public PeripheralDevice {
    string frequencyRange;
    double sensitivity;
public:
    Microphone(int id, string brand, double price, string frequencyRange, double sensitivity) : PeripheralDevice(id, brand, price), frequencyRange(frequencyRange), sensitivity(sensitivity) {}

    void displayInfo() const override {
        cout << "ID: " << id << ", Brand: " << brand << ", Price: $" << price << ", Frequency: " << frequencyRange << ", Sensitivity: " << sensitivity << " dB" << endl;
    }

    string getType() const override {
        return "Microphone";
    }
};

// Класс клавиатуры
class Keyboard : public PeripheralDevice {
    string switchType, interfaceType;
public:
    Keyboard(int id, string brand, double price, string switchType, string interfaceType) : PeripheralDevice(id, brand, price), switchType(switchType), interfaceType(interfaceType) {}

    void displayInfo() const override {
        cout << "ID: " << id << ", Brand: " << brand << ", Price: $" << price << ", Switch: " << switchType << ", Interface: " << interfaceType << endl;
    }

    string getType() const override {
        return "Keyboard";
    }
};

// Фабрика устройств
class DeviceFactory {
public:
    static PeripheralDevice* createDevice(const string& type, int id, string brand, double price, string param1, string param2, double param3 = 0) {
        if (type == "Headphones") return new Headphones(id, brand, price, param1, param2);

        if (type == "Microphone") return new Microphone(id, brand, price, param1, param3);

        if (type == "Keyboard") return new Keyboard(id, brand, price, param1, param2);

        return nullptr;
    }
};

int main() {
    vector<PeripheralDevice*> devices = {
        DeviceFactory::createDevice("Headphones", 1, "Sony", 99.99, "Over-Ear", "Headband"),

        DeviceFactory::createDevice("Microphone", 2, "Blue", 149.99, "20Hz-20kHz", "", -42),

        DeviceFactory::createDevice("Keyboard", 3, "Logitech", 199.99, "Mechanical", "Wireless"),

        DeviceFactory::createDevice("Keyboard", 4, "Ardor", 50.99, "Mechanical", "Wireless")
    };

    // Вывод базовой информации
    for (const auto& device : devices) {
        cout << "ID: " << device->getId() << ", Type: " << device->getType() << ", Brand: " << device->getBrand() << endl;
    }

    int searchId;
    cout << "Enter device ID for full details: ";
    cin >> searchId;

    bool found = false;
    for (const auto& device : devices) {
        if (device->getId() == searchId) {
            device->displayInfo();
            found = true;
            break;
        }
    }

    if (!found) cout << "Device not found." << endl;

    // Очистка памяти
    for (auto& device : devices) delete device;

    return 0;
}