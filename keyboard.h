#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<iostream>

class TModel
{
private:
    std::string Manufacturer;
    std::string Model;
public:
    TModel();
    ~TModel();
    TModel(
            std::string lManufacturer,
            std::string lModel
            );

    void setManufacturer(const std::string lManufacturer);
    std::string getManufacturer() const;

    void setModel(const std::string lModel);
    std::string getModel() const;

    void show();
};

class TKeyboard: public TModel
{
public:
    enum EType{Undef = 0,Membrane, Mechanical, SemiMechanical};
    enum EConstruction{Default = 0, Classic, Ergonomic, Split, Rhombic};
    enum EInterface{Undefined = 0, PS2, USB, Wireless};
private:
    EType Type;
    EConstruction Construction;
    EInterface Interface;
    int KolVo;
    bool DopKl;
    bool Backlighting;
public:
    TKeyboard();
    ~TKeyboard();
    TKeyboard(  TModel lModel,
                EType lType,
                EConstruction lConstruction,
                EInterface lInterface,
                int lKolVo,
                bool lDopKl,
                bool lBacklighting
                );

    void setType (const EType lType);
    void setConstruction (const EConstruction lConstruction);
    void setInterface (const EInterface lInterface);
    void setKolVo (const int lKolVo);
    void setDopKl (const bool lDopKl);
    void setBacklighting (const bool lBacklighting);

    EType getType ();
    EConstruction getConstruction ();
    EInterface getInterface ();
    int getKolVo ();
    bool getDopKl ();
    bool getBacklighting ();

    void show();
};
#endif // KEYBOARD_H
