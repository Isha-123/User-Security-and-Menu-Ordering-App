#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Base class for all types of users
class User {
protected:
    string name;
    string password;
    string emailId;
    

public:
    User(string n, string p, string e) : name(n), password(p), emailId(e) {}

    virtual bool validatePassword(string newPassword) = 0; // Pure virtual function for polymorphism

    virtual void displayDetails() {
        cout << "Username: " << name << endl;
        cout << "Password: " << password << endl;
        cout << "Email ID: " << emailId << endl;
        
    }

    virtual ~User() {} // Virtual destructor to ensure proper cleanup
};

// Derived class for registered users
class RegisteredUser : public User {
public:
    RegisteredUser(string n, string p, string e) : User(n, p, e) {}

    bool validatePassword(string newPassword) override {
        // Check if password is numeric and has exactly 4 digits
        for (char c : newPassword) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return newPassword.length() == 4;
    }

    void changePassword(string newPassword) {
        password = newPassword;
    }
};

int main() {
    int choice;
    string name, password, emailId,item;
    User *user = nullptr;

    do {
        cout << "Security System" << endl;
        cout << "______________________" << endl;
        cout << "|    1. Register     |" << endl;
        cout << "|    2. Login        |" << endl;
        cout << "|    3. Change Password   |" << endl;
        cout << "|    4. Menu Card    |" << endl;
        cout << "|    5. Exit         |" << endl;
        cout << "|____________________|" << endl << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Register" << endl;
                cout << "Enter username: ";
                cin >> name;
                cout << "Enter a 4-digit numeric password: ";
                cin >> password;
                cout << "Enter email ID: ";
                cin >> emailId;
                

                user = new RegisteredUser(name, password, emailId);
                cout << "Registration successful." << endl;
                break;
            }
            case 2: {
                if (user == nullptr) {
                    cout << "Please register first." << endl;
                    break;
                }

                string inputPassword;
                cout << "Enter the username: ";
                cin >> name;
                cout << "Enter the password: ";
                cin >> inputPassword;

                RegisteredUser* registeredUser = dynamic_cast<RegisteredUser*>(user);
                if (registeredUser && registeredUser->validatePassword(inputPassword)) {
                    user->displayDetails();
                    cout << "Login Successfully" << endl;
                } else {
                    cout << "Incorrect credentials." << endl;
                }
                break;
            }
            case 3: {
                if (user == nullptr) {
                    cout << "Please register first." << endl;
                    break;
                }

                string newPassword;
                cout << "Enter a new 4-digit numeric password: ";
                cin >> newPassword;

                RegisteredUser* registeredUser = dynamic_cast<RegisteredUser*>(user);
                if (registeredUser) {
                    registeredUser->changePassword(newPassword);
                    cout << "Password changed successfully." << endl;
                } else {
                    cout << "Password must be a 4-digit numeric value." << endl;
                }
                break;
            }
            case 4: {
                if (user == nullptr) {
                    cout << "Please register first." << endl;
                    break;
                }

                cout << "Menu Card" << endl;
                cout << "______________________" << endl;
                cout << "|    1. Tea         |" << endl;
                cout << "|    2. Coffee      |" << endl;
                cout << "|    3. Buttermilk  |" << endl;
                cout << "|    4. Lassi       |" << endl;
                cout << "|____________________|" << endl << endl;
                cout << "Enter the item you want to order: ";
                cin >> item;
                cout << "Your order has been placed and will be served in 10 minutes." << endl;
                break;
            }
            case 5: {
                // Cleanup memory before exiting
                delete user;
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Enter a valid choice" << endl;
        }
    } while (choice != 5);

    return 0;
}
