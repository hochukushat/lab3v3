#include "Menu.h"
#include <fstream>
#include <cstdlib>
using namespace std;

void Menu::UI()
{
    int n=0;
    while(1){
        system("cls");
        cout<<endl;
        cout<<" 1) Open File"<<endl;
        cout<<" 2) Save File"<<endl;
        cout<<" 3) Show"<<endl;
        cout<<" 4) Add New Element"<<endl;
        cout<<" 5) Edit Existing Element"<<endl;
        cout<<" 6) Delete Existing Element"<<endl;
        cout<<" 7) Exit"<<endl;

        cout<<"\n\n Enter Menu Number: ";
        cin>>n;
        switch(n){
        case 1: Menu::ReadFile();  break;
        case 2: Menu::WriteFile(); break;
        case 3: Menu::Display();    break;
        case 4: Menu::Add();       break;
        case 5: Menu::Edit();      break;
        case 6: Menu::Del();    break;
        case 7: exit(0);               break;
        default: cout<<"\n Entered Wrong Menu Number\n "<<endl; break;
        }
        system("pause");
    }
}

void Menu::ReadFile()
{
    if(Opened){
        cerr << "Error: File is Already opened" << endl;
        return;
    }

    fstream in("Keyboard.txt", ios_base::in);

    if(in.is_open())
    {
        ListA = 0;
        LastElem = 0;

        string str;
        while(!in.eof()){
            getline(in, str);

            if(str.empty())continue;

            List *NewL = new List;

            NewData(str,NewL);

            if(!ListA){
                LastElem = NewL;
                ListA = NewL;
                NewL->next = 0;
                NewL->prev = 0;
            }else {
                LastElem->next = NewL;
                NewL->prev = LastElem;
                NewL->next = 0;
                LastElem = NewL;
            }
        }
        in.close();
        setBool(true);
        cout << "File Opened Successfully."<<endl;
    }
}

void Menu::WriteFile()
{
    system("cls");
    if(!Opened){
        cerr << "Error: File is not Opened Yet!" << endl;
        return;
    }

    fstream out("Keyboard.txt", ios_base::out);
    struct List *nt;
    for(nt=ListA; nt!=0; nt=nt->next)
    {
        out << nt->Element.getManufacturer() << ";"
            << nt->Element.getModel() << ";"
            << nt->Element.getType()<< ";"
            << nt->Element.getConstruction() << ";"
            << nt->Element.getInterface() << ";"
            << nt->Element.getKolVo() << ";"
            << nt->Element.getDopKl() << ";"
            << nt->Element.getBacklighting() << ";"
            << endl;
    }
    out.close();
}

void Menu::Display()
{
    system("cls");
    if(!Opened){
        cerr << "Error: File is not Opened Yet!" << endl;
        return;
    }
    struct List *nt;
    int i = 1;

    for(nt=ListA; nt!=0; nt=nt->next){
        cout << "{" << i << "}" << endl;
        nt->Element.show();
        cout << endl;
        i++;
    }
}

void Menu::Add()
{
    system("cls");
    if(!Opened){
        cerr << "Error: File is not Opened Yet!" << endl;
        return;
    }

    List *NewC = new struct List;

    string NewEl;
    int selected;

    cout<<"\n\t\tCreating New Element\n    Please Enter"<<endl;

    cout<<"\tManufacturer: ";
    _flushall();
    cin >> NewEl;
    NewC->Element.setManufacturer(NewEl);

    cout<<"\n\tModel: ";
    _flushall(); cin >> NewEl;
    NewC->Element.setModel(NewEl);
    cout << "\n\tChoose Type (Select \"1-3\"): ";
st1:
    cin >> NewEl;
    if(NewEl == "1" || NewEl == "2" || NewEl == "3" )
    {
        switch (stoi(NewEl))
        {
        case 1: NewC->Element.setType(TKeyboard::Membrane);
            break;
        case 2: NewC->Element.setType(TKeyboard::Mechanical);
            break;
        case 3: NewC->Element.setType(TKeyboard::SemiMechanical);
            break;
        }
    }
    else
    {
        cout << "Please enter \"1 - 3\"!\nTry again!";
        goto st1;
    }

    cout << "\n\tChoose Construction (Select \"1-4\"): ";
st2:
    cin >> NewEl;
    if(NewEl == "1" || NewEl == "2" || NewEl == "3" )
    {
        switch (stoi(NewEl))
        {
        case 1: NewC->Element.setConstruction(TKeyboard::Classic);
            break;
        case 2: NewC->Element.setConstruction(TKeyboard::Ergonomic);
            break;
        case 3: NewC->Element.setConstruction(TKeyboard::Split);
            break;
        case 4: NewC->Element.setConstruction(TKeyboard::Rhombic);
            break;
        }
    }
    else
    {
        cout << "Please enter \"1 - 4\"!\nTry again!";
        goto st2;
    }

    cout << "\n\tChoose Interface (Select \"1-3\"): ";
st3:
    cin >> NewEl;
    if(NewEl == "1" || NewEl == "2" || NewEl == "3" )
    {
        switch (stoi(NewEl))
        {
        case 1: NewC->Element.setInterface(TKeyboard::PS2);
            break;
        case 2: NewC->Element.setInterface(TKeyboard::USB);
            break;
        case 3: NewC->Element.setInterface(TKeyboard::Wireless);
            break;
        }
    }
    else
    {
        cout << "Please enter \"1 - 4\"!\nTry again!";
        goto st3;
    }

    cout << "\n\tAmount of Keys (Please Enter Only Digits!): ";
    cin >> selected;
    NewC->Element.setKolVo(selected);

    cout <<"\n\tAvailability of Additional Keys (Enter \"1\" if Yes, else \"0\"): ";
st4:
    cin >> selected;
    if(selected == 1 || selected == 0)
    {
        NewC->Element.setDopKl(selected);
    }
    else
    {
        cout << "\nPlease Enter \"1\" or \"0\"! Try Again: ";
        goto st4;
    }

    cout << "\n\tAvailability of Backlighting (Enter \"1\" if Yes, else \"0\"): ";
st5:
    cin >> selected;
    if(selected == 1 || selected == 0)
    {
        NewC->Element.setBacklighting(selected);
    }
    else
    {
        cout << "\nPlease Enter \"1\" or \"0\"! Try Again: ";
        goto st5;
    }
    if(!ListA){
        LastElem = NewC;
        ListA = NewC;
        NewC->prev = 0;
        NewC->next = 0;
    }else {
        LastElem->next = NewC;
        NewC->prev = LastElem;
        NewC->next = 0;
    }

}

void Menu::Edit()
{
    system("cls");
    if(!Opened){
        cerr << "Error: File is not Opened Yet!" << endl;
        return;
    }

    int i = 1;
    struct List *nt;
    for(nt=ListA; nt!=0; nt=nt->next)
    {
        cout << "#" << i <<endl;
        nt->Element.TKeyboard::show();
        cout << endl;
        i++;
    }
    string a;
    int selected = 0;
    do
    {
        cout<<"\nSelect Element to Edit (if editing not needed type \"back\"): ";
        cin >> a;
        if(a == "back" || a == "Back" || a == "BACK")
            return;
        else
            selected = stoi(a);
    }while(!selected);
    int j=1;
    for(nt=ListA; j!=selected; nt=nt->next, j++);

    string t;

    cout<<"\n\n\t\tEditing\n    If editing not needed type 'f'"<<endl;
    cout<<"\n\tOld Manufacturer: " << nt->Element.getManufacturer() <<"; Type New: ";
    cin >> t;
    if(t!="F" && t!="f")
        nt->Element.setManufacturer(t);

    cout<<"\n\tOld Model: " << nt->Element.getModel() <<"; Type New: ";
    _flushall(); cin >> t;
    if(t!="F" && t!="f")
        nt->Element.setModel(t);

    cout << "\n\tOld Type: " << nt->Element.getType() << "; \nType New (\"1-3\" metches Membarne, MEchanical, SemiMechanical): ";
st1:
    cin >> t;
    if(t!="F" && t!="f")
    {
        if(stoi(t) == 1 || stoi(t)==2 || stoi(t) == 3)
        {
            switch (stoi(t))
            {
            case 1: nt->Element.setType(TKeyboard::Membrane);
                break;
            case 2: nt->Element.setType(TKeyboard::Mechanical);
                break;
            case 3: nt->Element.setType(TKeyboard::SemiMechanical);
                break;
            }
        }
        else
        {
            cout << "Please Enter only \"1-3\"!\nTry again! ";
            goto st1;
        }
    }

    cout << "\n\tOld Constrution: " << nt->Element.getConstruction() << ";\nType New (\"1-4\" matches Classic, Ergonomic, Split, Rhombic, except for unnecessary [f]): ";
    cin >> t;
st2:
    if(t!="F" && t!="f")
    {
        if(stoi(t) == 1 || stoi(t)==2 || stoi(t) == 3 || stoi(t) == 4)
        {
            switch (stoi(t))
            {
            case 1: nt->Element.setConstruction(TKeyboard::Classic);
                break;
            case 2: nt->Element.setConstruction(TKeyboard::Ergonomic);
                break;
            case 3: nt->Element.setConstruction(TKeyboard::Split);
                break;
            case 4: nt->Element.setConstruction(TKeyboard::Rhombic);
                break;
            }
        }
        else
        {
            cout << "Please Enter only \"1-4\"!\nTry again! ";
            goto st2;
        }
    }
    cout << "\n\tOld Interface: " << nt->Element.getInterface() << "; \nType New (\"1-3\" matches: PS2, USB, Wireless, if unnecessary [f])";
st3:
    //(\"1\" if yes, \"0\" if no)
    cin >> t;
    if(t!="F" && t!="f")
    {
        if(stoi(t) == 1 || stoi(t)==2 || stoi(t) == 3)
        {
            switch (stoi(t))
            {
            case 1: nt->Element.setInterface(TKeyboard::PS2);
                break;
            case 2: nt->Element.setInterface(TKeyboard::USB);
                break;
            case 3: nt->Element.setInterface(TKeyboard::Wireless);
                break;

            }
        }
        else
        {
            cout << "Please Enter only \"1-3\"!\nTry again! ";
            goto st3;
        }
    }

    cout << "\n\tOld Amount of Keys: " << nt->Element.getKolVo() << "; Type new (Only digits!): ";
    cin >> t;
    if(t!="F" && t!="f")
        nt->Element.setKolVo(stoi(t));

    cout << "Old Availability of Additional Keys" << boolalpha << nt->Element.getDopKl() <<"; Type New (\"1\" if yes, \"0\" if no): ";
st4:
    cin >> t;
    if(t!="F" && t!="f")
    {
        if(stoi(t) == 1 || stoi(t)== 0)
        {
            nt->Element.setDopKl(stoi(t));
        }
        else
        {
            cout << "Please Enter only \"1-4\"!\nTry again! ";
            goto st4;
        }
    }

    cout << "Old Availability of Backlighting: " << boolalpha << nt->Element.getBacklighting() << "; \nType New (\"1\" if yes, \"0\" if no): ";
st5:
    cin >> t;
    if(t!="F" && t!="f")
    {
        if(stoi(t) == 1 || stoi(t)== 0)
        {
            nt->Element.setBacklighting(stoi(t));
        }
        else
        {
            cout << "Please Enter only \"1-4\"!\nTry again! ";
            goto st5;
        }
    }
}


void Menu::Del()
{
    system("cls");
    if(!Opened)
    {
        cerr << "Error: File is not opened" << endl;
        return;
    }

    int i = 1, del = 0;
    struct List *nt;
    for(nt=ListA; nt!=0; nt=nt->next)
    {
        cout << "#" << i <<endl;
        nt->Element.TKeyboard::show();
        cout << endl;
        i++;
    }

    string a;
    do
    {
        cout<<"\n\nSelect Element to delete (if deleting not needed type \"back\")\nINPUT ONLY NUMBERS FOR CHOOSING!\n ";
        cin >> a;
        if(a == "BACK" || a == "Back" || a == "back")
            return;
        else
            del = stoi(a);

    }while(!del);
    int j=1;
    for(nt=ListA; j!=del; nt=nt->next, j++);

    if(nt->next)
        nt->next->prev = nt->prev;
    else
        LastElem = nt->prev;

    if(nt->prev)
        nt->prev->next = nt->next;
    else
        ListA = nt->next;

}

void Menu::NewData(string str, Menu::List *New)
{
    const int kol_param = 8;

    string arr[kol_param];
    int index[kol_param+1];
    index[0]=-1;
    int j = 1;
    for(int i=0; i < (int)str.length();i++)
    {
        if(str[i] == ';'){
            index[j]=i;
            j++;
        }
    }
    for(int i=0;i<kol_param;i++)
    {
        arr[i] = str.substr(index[i]+1, index[i+1]-index[i]-1);
    }

    New->Element.setManufacturer(arr[0]);
    New->Element.setModel(arr[1]);
    switch (stoi(arr[2]))
    {
    case 1: New->Element.setType(TKeyboard::Membrane);
        break;
    case 2: New->Element.setType(TKeyboard::Mechanical);
        break;
    case 3: New->Element.setType(TKeyboard::SemiMechanical);
        break;
    }
    switch (stoi(arr[3]))
    {
    case 1: New->Element.setConstruction(TKeyboard::Classic);
        break;
    case 2: New->Element.setConstruction(TKeyboard::Ergonomic);
        break;
    case 3: New->Element.setConstruction(TKeyboard::Split);
        break;
    case 4: New->Element.setConstruction(TKeyboard::Rhombic);
        break;
    }
    switch (stoi(arr[4]))
    {
    case 1: New->Element.setInterface(TKeyboard::PS2);
        break;
    case 2: New->Element.setInterface(TKeyboard::USB);
        break;
    case 3: New->Element.setInterface(TKeyboard::Wireless);
        break;
    }
    New->Element.setKolVo(stoi(arr[5]));
    New->Element.setDopKl(stoi(arr[6]));
    New->Element.setBacklighting(stoi(arr[7]));

}
