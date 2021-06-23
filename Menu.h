#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include"keyboard.h"

class Menu
{
    std::string File;
    struct List
    {
        TModel Mod;
        TKeyboard Element;
        List *next;
        List *prev;
    }*ListA;

    bool Opened=0;
    List *LastElem;
public:
    Menu():
        ListA(0),
        LastElem(0)
    {};
    Menu(const std::string nFN):
        File(nFN),
        ListA(0),
        LastElem(0)
    {};
    ~Menu(){};

    void UI();

    void ReadFile();
    void WriteFile();
    void Display();
    void Add();
    void Edit();
    void Del();
    void About();

    void NewData(std::string str, List *New);

    void setBool(bool l)
    {
        Opened = l;
    }
};

#endif // MENU_H
