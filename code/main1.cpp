#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

class EDevice {
public:
    string name;
    string id;
    int yearOfPurchase;
    string condition;

    EDevice() : name(""), id(""), yearOfPurchase(0), condition("") {}

    EDevice(string n, string i, int y, string c) : name(n), id(i), yearOfPurchase(y), condition(c) {}

    void display() const {
        cout << "Device Name: " << name << "\n"
             << "ID: " << id << "\n"
             << "Year of Purchase: " << yearOfPurchase << "\n"
             << "Condition: " << condition << "\n";
    }
};

class User {
public:
    string username;
    string password;
    vector<EDevice> devices;

    User() : username(""), password("") {}

    User(string u, string p) : username(u), password(p) {}

    void addDevice(const string& name, const string& id, int year, const string& condition) {
        devices.push_back(EDevice(name, id, year, condition));
    }

    void monitorDevices() const {
        cout << "\nMonitoring Devices for " << username << ":\n";
        for (const auto& device : devices) {
            device.display();
            cout << "-------------------------\n";
        }
    }

    void recycleDevice(const string& id) {
        auto it = find_if(devices.begin(), devices.end(), [&](const EDevice& device) {
            return device.id == id;
        });

        if (it != devices.end()) {
            cout << "Recycling Device with ID: " << id << "\n";
            devices.erase(it);
        } else {
            cout << "Device with ID: " << id << " not found.\n";
        }
    }
};

class EWasteMonitoringSystem {
private:
    unordered_map<string, User> users;
    User* loggedInUser = nullptr;

public:
    void signUp(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            users[username] = User(username, password);
            cout << "User " << username << " registered successfully!\n";
        } else {
            cout << "Username already exists. Please choose a different username.\n";
        }
    }

    void logIn(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.password == password) {
            loggedInUser = &it->second;
            cout << "Logged in as " << username << ".\n";
        } else {
            cout << "Invalid username or password.\n";
        }
    }

    void logOut() {
        if (loggedInUser) {
            cout << "Logged out from " << loggedInUser->username << ".\n";
            loggedInUser = nullptr;
        } else {
            cout << "No user is currently logged in.\n";
        }
    }

    string getValidCondition() {
        string condition;
        vector<string> validConditions = {"New", "Good", "Old", "Broken"};
        while (true) {
            cout << "Enter condition (New/Good/Old/Broken): ";
            getline(cin, condition);
            auto it = find(validConditions.begin(), validConditions.end(), condition);
            if (it != validConditions.end()) {
                return condition;
            }
            cout << "Invalid condition. Please try again.\n";
        }
    }

    void addDevice() {
        if (loggedInUser) {
            string name, id, condition;
            int year;

            cout << "Enter device name: ";
            getline(cin, name);

            cout << "Enter device ID: ";
            getline(cin, id);

            cout << "Enter year of purchase: ";
            while (!(cin >> year)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid year: ";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            condition = getValidCondition();

            loggedInUser->addDevice(name, id, year, condition);
            cout << "Device added successfully!\n";
        } else {
            cout << "Please log in first.\n";
        }
    }

    void monitorDevices() const {
        if (loggedInUser) {
            loggedInUser->monitorDevices();
        } else {
            cout << "Please log in first.\n";
        }
    }

    void recycleDevice() {
        if (loggedInUser) {
            string id;
            cout << "Enter the ID of the device to recycle: ";
            getline(cin, id);
            loggedInUser->recycleDevice(id);
        } else {
            cout << "Please log in first.\n";
        }
    }

    void run() {
        while (true) {
            int choice;
            cout << "\n--- E-Waste Monitoring System ---\n";
            cout << "1. Sign Up\n2. Log In\n3. Log Out\n4. Add Device\n5. Monitor Devices\n6. Recycle Device\n7. Exit\n";
            cout << "Enter your choice: ";
            while (!(cin >> choice) || choice < 1 || choice > 7) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter a number between 1 and 7: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: {
                    string username, password;
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    signUp(username, password);
                    break;
                }
                case 2: {
                    string username, password;
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    logIn(username, password);
                    break;
                }
                case 3:
                    logOut();
                    break;
                case 4:
                    addDevice();
                    break;
                case 5:
                    monitorDevices();
                    break;
                case 6:
                    recycleDevice();
                    break;
                case 7:
                    return;
            }
        }
    }
};

int main() {
    EWasteMonitoringSystem system;
    system.run();
    return 0;
}
