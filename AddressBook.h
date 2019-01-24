#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H


#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "User.h"
#include "UsersFile.h"
#include "Recipent.h"
#include "RecipentFile.h"
#include "Menu.h"

using namespace std;

class AddressBook
{

    vector<Recipent> recipents;
    int loggedInUserId;
    FileRecipents recipentFile;
    char id;
    int personalId;
    Users users;
    Menu menu;
    friend class Users;

public:
    AddressBook(int loggedInUserId);
    virtual ~AddressBook();

    void addRecipent();
    void searchByName();
    void searchBySurname();
    void writeAllYourFriends();
    void deleteRecipent();
    void editRecipent();
    int getIdLoggedUser();
    class Users
    {

        vector<User> users;
        int idLoggedUser;
        UsersFile usersFile;
        friend class AddressBook;
        friend class Recipent;


    public:
        Users();
        virtual ~Users();

        void registration();
        void changePassword();
        void singIn();
        void logOut();
        int takeIdLoggedUser();


    private:

        User enterTheDetailsOfTheNewUser();
        int takeIdNewUser();
        string checkThatUserExist(string nick, vector<User> users);
        bool doesUserExist(string nick);

    };





private:
    Recipent addTheDetailsOfTheNewUser();
    int takeIdOfNewFriend();
    char idUserWhichWantsToDeleteFriend();
    char takeIdOfRecipent(int personalId);

};
#endif
