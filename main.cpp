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
    PeripheralDevice(int id, const string& brand, double price)
        : id(id), brand(brand), price(price) {}

    // Метод для вывода базовой информации
    void displayBasicInfo() const {
        cout << "ID: " << id << ", Brand: " << brand << endl;
    }

    // Метод для вывода полной информации
    virtual void displayInfo() const {
        cout << "ID: " << id << ", Brand: " << brand << ", Price: $" << price;
    }

    // Метод для получения ID
    int getId() const {
        return id;
    }

    virtual ~PeripheralDevice() = default;
};

// Класс наушников
class Headphones : public PeripheralDevice {
    string constructionType;
    string mountingMethod;

public:
    Headphones(int id, const string& brand, double price, const string& constructionType, const string& mountingMethod)
        : PeripheralDevice(id, brand, price), constructionType(constructionType), mountingMethod(mountingMethod) {}

    void displayInfo() const override {
        PeripheralDevice::displayInfo();
        cout << ", Construction Type: " << constructionType
             << ", Mounting Method: " << mountingMethod << endl;
    }
};

// Класс микрофона
class Microphone : public PeripheralDevice {
    string frequencyRange;
    double sensitivity;

public:
    Microphone(int id, const string& brand, double price, const string& frequencyRange, double sensitivity)
        : PeripheralDevice(id, brand, price), frequencyRange(frequencyRange), sensitivity(sensitivity) {}

    void displayInfo() const override {
        PeripheralDevice::displayInfo();
        cout << ", Frequency Range: " << frequencyRange
             << ", Sensitivity: " << sensitivity << " dB" << endl;
    }
};

// Класс клавиатуры
class Keyboard : public PeripheralDevice {
    string switchType;
    string interfaceType;

public:
    Keyboard(int id, const string& brand, double price, const string& switchType, const string& interfaceType)
        : PeripheralDevice(id, brand, price), switchType(switchType), interfaceType(interfaceType) {}

    void displayInfo() const override {
        PeripheralDevice::displayInfo();
        cout << ", Switch Type: " << switchType
             << ", Interface: " << interfaceType << endl;
    }
};

// Фабрика устройств
class DeviceFactory {
public:
    static PeripheralDevice* createDevice(const string& type, int id, const string& brand, double price,
                                          const string& param1, const string& param2, double param3 = 0) {
        if (type == "Headphones") {
            return new Headphones(id, brand, price, param1, param2);
        } else if (type == "Microphone") {
            return new Microphone(id, brand, price, param1, param3);
        } else if (type == "Keyboard") {
            return new Keyboard(id, brand, price, param1, param2);
        }
        return nullptr;
    }
};

int main() {
    vector<PeripheralDevice*> devices;

    // Создание устройств через фабрику
    devices.push_back(DeviceFactory::createDevice("Headphones", 1, "Sony", 99.99, "Over-Ear", "Headband"));
    devices.push_back(DeviceFactory::createDevice("Microphone", 2, "Blue", 149.99, "20Hz-20kHz", "", -42));
    devices.push_back(DeviceFactory::createDevice("Keyboard", 3, "Logitech", 199.99, "Mechanical", "Wireless"));

    // Вывод базовой информации о всех устройствах
    cout << "\nList of devices (basic info):\n";
    for (const auto& device : devices) {
        device->displayBasicInfo();
    }

    // Запрос у пользователя ID для вывода полной информации
    int searchId;
    cout << "\nEnter device ID to get full details: ";
    cin >> searchId;
    bool found = false;

    for (const auto& device : devices) {
        if (device->getId() == searchId) {
            cout << "\nFull details of the selected device:\n";
            device->displayInfo();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Device with ID " << searchId << " not found." << endl;
    }

    // Очистка памяти
    for (auto& device : devices) {
        delete device;
    }

    return 0;
}
