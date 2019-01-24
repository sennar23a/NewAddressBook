#include "Users.h"
#include "AddressBook.h"
#include <fstream>
#include <windows.h>

using namespace std;

AddressBook::AddressBook(int loggedInUserId) {

    this->loggedInUserId = loggedInUserId;
    recipentFile.loadRecipentsFromTextFile(recipents, loggedInUserId);
    int personalId = 0;
    char id = '0';

}
AddressBook::~AddressBook() {

    recipents.clear();
}

int AddressBook::getIdLoggedUser() {

    return loggedInUserId;
}

void AddressBook::addRecipent() {


    Recipent recipent = addTheDetailsOfTheNewUser();
    recipents.push_back(recipent);
    recipentFile.addRecipentToFile(recipent);
}



Recipent AddressBook::addTheDetailsOfTheNewUser () {

    Recipent recipent;

    string name = "";
    string surname = "";
    string phoneNumber = "";
    string email = "";
    string address = "";



    recipent.setIndividualNumberOfEachFriend(takeIdOfNewFriend());
    recipent.setUserId(getIdLoggedUser());


    cout << "Enter friend name: ";
    cin >> name;
    cin.ignore();
    recipent.setName(name);
    cout << "Enter friend surname: ";
    cin >> surname;
    cin.ignore();
    recipent.setSurname(surname);
    cout << "Enter friend phone number: ";
    cin.sync();
    getline(cin,phoneNumber);
    recipent.setPhoneNumber(phoneNumber);
    cout << "Enter friend email: ";
    cin >> email;
    cin.ignore();
    recipent.setEmail(email);
    cout << "Enter friend address: ";
    cin.sync();
    getline(cin, address);
    recipent.setAddress(address);

    return recipent;
}

int AddressBook::takeIdOfNewFriend() {

    int numberOfLastRecipent = 0;
    string line = "";
    int numberZero = 48;


    ifstream file;
    file.open("AddressBook.txt");
    if(!file.good()) {
        cout << "File doesn't exist!" <<endl;
        numberOfLastRecipent = 1;
        return numberOfLastRecipent;
    }
    while(getline(file, line)) {

        numberOfLastRecipent = line[0] - numberZero ;
    }
    return numberOfLastRecipent + 1;
}

void AddressBook::searchByName() {

    system("cls");
    string name;
    int index = 0;
    cout << "Enter friend name: ";
    cin >> name;

    for(vector<Recipent>::iterator i = recipents.begin(); i < recipents.end(); ++i) {
        if(i->name == name) {

            cout << endl;
            cout << "          Recipent id: " << i->individualNumberOfEachFriend << endl;
            cout << "              User id: " << i->userId << endl;
            cout << "        Recipent name: " << i->name << endl;
            cout << "     Recipent surname: " << i->surname << endl;
            cout << "Recipent phone number: " << i->phoneNumber << endl;
            cout << "       Recipent email: " << i->email << endl;
            cout << "     Recipent address: " << i->address << endl;
            cout << endl;
        }
    }
    getch();
}

void AddressBook::searchBySurname() {


    system("cls");
    string surname;
    int index = 0;
    cout << "Enter friend surname: ";
    cin >> surname;

    for(vector<Recipent>::iterator i = recipents.begin(); i < recipents.end(); ++i) {
        if(i->surname == surname) {

            cout << endl;
            cout << "          Recipent id: " << i->individualNumberOfEachFriend << endl;
            cout << "              User id: " << i->userId << endl;
            cout << "        Recipent name: " << i->name << endl;
            cout << "     Recipent surname: " << i->surname << endl;
            cout << "Recipent phone number: " << i->phoneNumber << endl;
            cout << "       Recipent email: " << i->email << endl;
            cout << "     Recipent address: " << i->address << endl;
            cout << endl;
        }
    }
    getch();
}

void AddressBook::writeAllYourFriends() {

    int i = 0;

    system("cls");
    while(i < recipents.size()) {

        cout << endl;
        cout << "          Recipent id: " << recipents[i].individualNumberOfEachFriend << endl;
        cout << "              User id: " << recipents[i].userId << endl;
        cout << "        Recipent name: " << recipents[i].name << endl;
        cout << "     Recipent surname: " << recipents[i].surname << endl;
        cout << "Recipent phone number: " << recipents[i].phoneNumber << endl;
        cout << "       Recipent email: " << recipents[i].email << endl;
        cout << "     Recipent address: " << recipents[i].address << endl;
        cout << endl;
        i++;
    }
    getch();
}

char AddressBook::idUserWhichWantsToDeleteFriend() {

    char userId;
    const int modulo = 10;
    const int numberOfZero = 48;
    userId = (loggedInUserId%modulo) + numberOfZero;

    return userId;
}

void AddressBook::deleteRecipent() {



    char sign;
    char choice;
    int personalId;
    int i = 0;
    string line;

    cout << "Enter your friend id: ";
    cin >> personalId;

    for(vector<Recipent>:: iterator iter = recipents.begin(); iter != recipents.end(); ++iter) {
        if(iter->individualNumberOfEachFriend == personalId) {

            cout << "Do you want to delete this friend ?? <t/n>" << endl;
            cout << "Your decision: ";
            cin >> sign;
            if (sign == 't') {

                iter = recipents.erase(iter);
                char userId = takeIdOfRecipent(personalId);
                recipentFile.overwriteRecentFile(userId);
                break;
            }
        } else if ((iter->individualNumberOfEachFriend != personalId) && (iter == recipents.end() - 1)) {

            cout << "There is no recipent whit this id !!!" << endl;
            Sleep(3000);

        }
    }
    recipents.clear();
}

char AddressBook::takeIdOfRecipent(int personalId) {

    char userId;
    const int modulo = 10;
    const int numberOfZero = 48;
    userId = (personalId%modulo) + numberOfZero;

    return userId;

}


void AddressBook::editRecipent() {

    int personalId;
    char choice;
    cout << "Enter id of person which you are looking for: ";
    cin >> personalId;
    for(vector<Recipent>::iterator i = recipents.begin(); i != recipents.end(); i++) {
        if(i->individualNumberOfEachFriend == personalId) {


            choice = menu.selectOptionFromThirdMenu();

            switch(choice) {

            case '1':
                if(i->individualNumberOfEachFriend == personalId) {

                    string newName;
                    cout << "Enter new name: ";
                    cin >> newName;
                    i->name = newName;
                    cout << endl << "Name has been changed !!";
                    Sleep(1500);
                }
                break;
            case '2':
                if(i->individualNumberOfEachFriend == personalId) {

                    string newSurname;
                    cout << "Enter new surname: ";
                    cin >> newSurname;
                    i->surname = newSurname;
                    cout << endl << "Surname has been changed !!";
                    Sleep(1500);
                }
                break;
            case '3':
                if(i->individualNumberOfEachFriend == personalId) {

                    string newPhoneNumber;
                    cout << "Enter new phone number: ";
                    cin.sync();
                    getline(cin, newPhoneNumber);
                    i->phoneNumber = newPhoneNumber;
                    cout << endl << "Phone number has been changed !!";
                    Sleep(1500);
                }
                break;
            case '4':
                if(i->individualNumberOfEachFriend == personalId) {

                    string newEmail;
                    cout << "Enter new email: ";
                    cin >> newEmail;
                    i->email = newEmail;
                    cout << endl << "Email has been changed !!";
                    Sleep(1500);
                }
                break;
            case '5':
                if(i->individualNumberOfEachFriend == personalId) {

                    string newAddress;
                    cout << "Enter new addres: ";
                    cin.sync();
                    getline(cin,newAddress);
                    i->address = newAddress;
                    cout << endl << "Address has been changed !!";
                    Sleep(1500);
                }
                break;
            case '6': {
                loggedInUserId;
                break;
            }

            }

            char userId = takeIdOfRecipent(personalId);

            string line;
            ifstream file;
            ofstream temporary;
            file.open("AddressBook.txt", ios::out | ios::app);
            temporary.open("TemporaryAddresBook.txt", ios::out | ios::app);
            if(file.good() && temporary.good()) {
                while(getline(file, line)) {
                    if(line[0] == userId) {
                        if(i->individualNumberOfEachFriend == personalId) {

                            temporary << i->individualNumberOfEachFriend << "|";
                            temporary << i->userId << "|";
                            temporary << i->name << "|";
                            temporary << i->surname << "|";
                            temporary << i->phoneNumber << "|";
                            temporary << i->email << "|";
                            temporary << i->address << "|" <<endl;

                        }
                    } else {

                        temporary << line <<endl;
                    }
                }
            }
            file.close();
            temporary.close();
            remove("AddressBook.txt");
            rename("TemporaryAddresBook.txt", "AddressBook.txt");

        } else {
            cout << "There is no recipent with this id !!!" <<endl;
            Sleep(3000);
            break;
        }
    }
    recipents.clear();
}
Users::Users() {

    this->idLoggedUser = 0;
    usersFile.loadUsersFromTextFile(users);
}

Users::~Users() {


    users.clear();

}

void Users::registration() {

    User user = enterTheDetailsOfTheNewUser();
    users.push_back(user);
    usersFile.addUserToFile(user);

}

bool Users::doesUserExist(string nick) {
    vector <User>::iterator itr = users.begin();

    while (itr != users.end()) {
        if (itr->User::getNick() == nick) {
            cout << endl << "That user exist!!" << endl;
            return true;
        } else {
            itr++;
        }
    }

    return false;
}


void Users::singIn() {

    string nick, password;
    int attempt = 3;
    bool doesUserExist = false;

    cout << "Please, enter your username: ";
    cin >> nick;

    for(vector<User>::iterator itr = users.begin(), koniec = users.end(); itr != koniec; ++itr) {
        if(itr->User::getNick() == nick) {

            while(attempt > 0) {
                cout << "Left attempts: " << attempt << " Enter password: ";
                cin >> password;

                if(itr->User::getPassword() == password) {

                    cout << "You logged in !!" << endl;
                    Sleep(1000);
                    this->idLoggedUser = itr->User::getIdOfUser();
                    doesUserExist = true;
                    break;
                }
                attempt--;

                if(attempt == 0) {
                    cout << "Three times you wrote wrong password. Wait 3 seconds and try again !!" << endl;
                    Sleep(3000);
                    this->idLoggedUser = 0;
                    break;
                }
            }
        }
    }
    if(doesUserExist = false) {
        cout << "There is no user with that login !!" << endl;
        Sleep(1500);
    }
}

void Users::changePassword() {

    if(idLoggedUser > 0) {

        string password = "";
        cout << "Enter new password: ";
        cin >> password;

       for(vector<User>::iterator itr = users.begin(), koniec = users.end(); itr != koniec; ++itr) {

            if(itr->User::getIdOfUser() == idLoggedUser) {

                itr->User::setPassword(password);
                cout << "Password has been changed !!" << endl;
                Sleep(1500);
            }
            usersFile.saveAllUsersIntoFile(users);
        }
    } else {

        cout << "Wrond id number. Log in if you want to change password !!" <<endl;
    }
}

User Users::enterTheDetailsOfTheNewUser() {

    User user;
    string nick = "";
    string password = "";

    user.setIdOfUser(takeIdNewUser());

    do {

        cout << endl << "Enter username: ";
        cin >> nick;
        cin.ignore();
        user.setNick(nick);
    } while(doesUserExist(user.getNick()) == true);

    cout << endl << "Password minimum 3 sign !!" << endl << endl;
    do {

        cout << "Enter password: ";
        cin >> password;
        cin.ignore();

    } while(password.length() < 3);

    user.setPassword(password);

    return user;

}

int Users::takeIdNewUser() {

    if(users.size() == 0) {

        return 1;
    } else {

        return users.back().getIdOfUser() + 1;

    }

}

int Users::takeIdLoggedUser() {

    return idLoggedUser;
}

void Users::logOut() {
    this->idLoggedUser = 0;
}










