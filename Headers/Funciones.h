#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
///Defines:
#define Color_Red 12
#define Color_Def 15
#define Color_Yellow 14
#define Delay_us 0
#define Cursor 16
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

COORD coord = {0,0};
char KEY_PAD;

int Counter_Articles = 0;

void gotoxy(int x,int y);
void Show_Title (void);
int Wait_Option (void);
int New_Product (struct Article_Struct *Pointer_Articles_Struct);
int Delete_Product (struct Article_Struct *Pointer_Articles_Struct);
int Buy_Product (struct Article_Struct *Pointer_Articles_Struct);
int Sell_Product (struct Article_Struct *Pointer_Articles_Struct);
int Report_Product (struct Article_Struct *Pointer_Articles_Struct);
int Get_Elements_Number (struct Article_Struct *Pointer_Articles_Struct);
void Init_Structure_Elements (struct Article_Struct *Pointer_Articles_Struct);


/********************************************************************
*                       Function:  gotoxy                           *
* Input Arguments:                                                  *
*- Integers: Coordenates X and Y in screen.                         *
* Output Arguments:                                                 *
* -----------------                                                 *
* This function move the cursor to an specific coordenates.         *
********************************************************************/
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}



/********************************************************************
*                      Function: Select_Option                      *
*        This function only present de program to the user.         *
********************************************************************/
void Show_Title (void)
{
    int X = 0;
    int Y = 0;

    system("cls");

    char Line1[] = {"  ----------------------------------------------------------------------------   "};
    char Line2[] = {" |                            INVENTORY SYSTEM                                |  "};
    char Line3[] = {" |                                                                            |  "};
    char Line4[] = {" |                         Lucas Nicolas Greco                                |  "};
    char Line5[] = {" |                                                                            |  "};
    char Line6[] = {"  ----------------------------------------------------------------------------   "};


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    gotoxy (X,Y+2);
    for (unsigned int i= 0; i < sizeof(Line1); i++)
    {
        cout << Line1[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+3);
    for (unsigned int i= 0; i < sizeof(Line2); i++)
    {
        cout << Line2[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+4);
    for (unsigned int i= 0; i < sizeof(Line3); i++)
    {
        cout << Line3[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+5);
    for (unsigned int i= 0; i < sizeof(Line4); i++)
    {
        cout << Line4[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+6);
    for (unsigned int i= 0; i < sizeof(Line5); i++)
    {
        cout << Line5[i];
        Sleep(Delay_us);
    }
    gotoxy (X,Y+7);
    for (unsigned int i= 0; i < sizeof(Line6); i++)
    {
        cout << Line6[i];
        Sleep(Delay_us);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
}

/********************************************************************
*                    Function:  Wait_Option                         *
* Input Arguments:                                                  *
* ----------------                                                  *
* Output Arguments:                                                 *
*- Integer value related with a option menu.                        *
* This function wait until the user enter a option.                 *
********************************************************************/
int Wait_Option (void)
{
    int Cursor_Pos = 14;

    system("cls");
    Show_Title ();

    gotoxy(30,10);
    cout << "SELECT A OPTION.";

    gotoxy(5,14);
    cout << "(1) NEW PRODUCT.";

    gotoxy(5,16);
    cout << "(2) DELETE PRODUCT.";

    gotoxy(5,18);
    cout << "(3) BUY PRODUCT.";

    gotoxy(5,20);
    cout << "(4) SALE PRODUCT.";

    gotoxy(5,22);
    cout << "(5) SHOW REPORT.";

    gotoxy(5,24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << "(6) EXIT." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(17,26);
    cout << "Use Key Pad To Select One Or Press ESC To EXIT. " << endl;

    gotoxy(3,Cursor_Pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << (char)Cursor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(64,26);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos >= 16) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos <= 22) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 14: return 1; break;
                        case 16: return 2; break;
                        case 18: return 3; break;
                        case 20: return 4; break;
                        case 22: return 5; break;
                        case 24: return 6; break;
                    }
                }
                break;

                case KEY_ESC: return 6; break;

            }

            for (int i = 0; i<12 ; i+=2)
            {
                gotoxy(3,14+i);
                cout << (char) 0;
            }

            gotoxy(3,Cursor_Pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
            cout << (char)Cursor;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
            gotoxy(64,26);
        }
    }while (KEY_PAD!=27);

    return 6;
}

/********************************************************************
*                     Function:  New_Product                        *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function adds products to the inventory.                     *
********************************************************************/
int New_Product ( struct Article_Struct *Pointer_Articles_Struct )
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    float Cost = 0, Price = 0;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> NEW PRODUCT <<" << endl;
    gotoxy(5,13);
    cout << "Name Product : " << endl;
    gotoxy(5,15);
    cout << "Cost Product : " << endl;
    gotoxy(4,17);
    cout << "Price Product : " << endl;
    gotoxy(6,19);
    cout << "<< SAVE >> " << endl;
    gotoxy(5,21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << " << RETURN MAIN" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(25,25);
    cout << "Use Key Pad To Select One Option." << endl;

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;

                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 20) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        // ENTER NAME
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin.getline (Name,Max_Chars,'\n');
                            for (int i=0; i<Max_Chars ; i++)
                            {
                                Name[i] = toupper(Name[i]);
                                if (Name[i] == 0) break;
                            }
                        break;

                        // ENTER COST
                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Cost;
                        break;

                        // ENTER PRICE
                        case 17:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Price;
                        ; break;

                        // SAVE
                        case 19:
                            if (Cost == 0 || Price == 0 || Name[0] == 0)
                            {
                                gotoxy(23,25);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                cout << "ERROR: YOU MUST ENTER ALL VALUES.  ";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                            }
                            else
                            {
                                int Local_Articles = Get_Elements_Number(Pointer_Articles_Struct);

                                for (int i=0; i<Max_Chars ; i++)
                                {
                                    //Pointer_Articles_Struct[Counter_Articles].Name[i] = Name[i];
                                    Pointer_Articles_Struct[Local_Articles].Name[i] = Name[i];
                                    if (Name[i] == 0) break;
                                }
                                Pointer_Articles_Struct[Local_Articles].Cost = Cost;
                                Pointer_Articles_Struct[Local_Articles].Price = Price;
                                Pointer_Articles_Struct[Local_Articles].Pieces = 0;
                                Pointer_Articles_Struct[Local_Articles].Value *= Cost;

                                if (Counter_Articles == Local_Articles) Counter_Articles++;

                                return 0;
                            }

                        break;

                        //EXIT
                        case 21: return 0 ; break;
                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);

      return 0;
}

/********************************************************************
*                   Function:  Delete_Product                       *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function deletes produts to the inventory.                   *
********************************************************************/
int Delete_Product (struct Article_Struct *Pointer_Articles_Struct)
{
    int Cursor_Pos = 16;
    int Delete_Register = 0;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> DELETE PRODUCT <<" << endl;
    gotoxy(1,11);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,12);
    cout << "|No.|";
    cout << "      NAME     |";
    cout << "     BUY     |";
    cout << "     SALE    |";
    cout << "  AVALIABLE  |";
    cout << "     PRICE    |";
    gotoxy(1,13);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << " << RETURN MAIN";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
    gotoxy(57,9);
    cout << "DELETE Reg. No:" ;

    for (int j = 0 ; j < Counter_Articles ; j++)
    {
        gotoxy(3,14+j);
        cout << j+1;
        gotoxy(10,14+j);
        for (int i = 0 ; i<Max_Chars ; i++)
        {
            cout << Pointer_Articles_Struct[j].Name[i];
            if (Pointer_Articles_Struct[j].Name[i] == 0)
            {
                break;
            }
        }
        cout.precision(2);
        gotoxy(26,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Cost;
        gotoxy(40,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Price;
        gotoxy(55,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Pieces;
        gotoxy(70,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Value;
    }

    gotoxy(Cursor_Pos,9);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_LEFT:
                {
                    if (Cursor_Pos == 74) Cursor_Pos = Cursor_Pos = 16;

                }
                break;

                case KEY_RIGHT:
                {
                    if (Cursor_Pos == 16) Cursor_Pos = Cursor_Pos = 74;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 74:
                            gotoxy(Cursor_Pos-1,9);
                            cout << (char)Cursor;
                            cin >> Delete_Register;
                            if (Delete_Register>Counter_Articles)
                            {
                                gotoxy(23,25);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                cout << "ERROR: REGISTER NUMBER IS INVALID.";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                Cursor_Pos = 16;
                            }
                            else
                            {
                                for (int i=0; i<Max_Chars ; i++)
                                {
                                    Pointer_Articles_Struct[Delete_Register-1].Name[i] = 0;
                                }
                                Pointer_Articles_Struct[Delete_Register-1].Cost = 0;
                                Pointer_Articles_Struct[Delete_Register-1].Price = 0;
                                Pointer_Articles_Struct[Delete_Register-1].Pieces = 0;
                                Pointer_Articles_Struct[Delete_Register-1].Value = 0;
                                gotoxy(19,9);
                                cout << "DONE.";
                                Cursor_Pos = 16;
                            }
                        break;

                        case 16: return 0; break;
                    }
                }
            }
            gotoxy(Cursor_Pos,9);
        }
      }while (KEY_PAD!=27);

      return 0;
}

/********************************************************************
*                    Function:  Buy_Product                         *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function manage the Inventory  Buys.                         *
********************************************************************/
int Buy_Product (struct Article_Struct *Pointer_Articles_Struct)
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    int Quantity_Prod;
    bool Found_Article = false;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> BUY PRODUCT <<";
    gotoxy(5,13);
    cout << "Name Product :";
    gotoxy(4,15);
    cout << "Quantity Prod :";
    gotoxy(7,17);
    cout << "<< SAVE >> ";
    gotoxy(5,19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << " << RETURN MAIN" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;
                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin.getline (Name,Max_Chars,'\n');
                        break;

                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Quantity_Prod;
                        break;

                        case 17:
                            if (Quantity_Prod == 0 || Name[0] == 0)
                            {
                                gotoxy(23,25);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                cout << "ERROR: YOU MUST ENTER ALL VALUES.  ";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                            }
                            else
                            {
                                int j;
                                int i;
                                for (j = 0 ; j < Counter_Articles ; j++)
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)
                                    {
                                        if (Pointer_Articles_Struct[j].Name[i] != toupper(Name[i]) || Pointer_Articles_Struct[j].Name[i] == 0)
                                        {
                                            break;
                                        }
                                    }

                                    if (i == strlen(Name))
                                    {
                                        Found_Article = true;
                                        break;
                                    }
                                }

                                if (Found_Article)
                                {
                                    Pointer_Articles_Struct[j].Pieces += Quantity_Prod;
                                    Pointer_Articles_Struct[j].Value = Pointer_Articles_Struct[j].Cost * Pointer_Articles_Struct[j].Pieces;
                                    return 0;
                                }
                                else
                                {
                                    gotoxy(23,25);
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                    cout << "ERROR: ARTICLE DIDN'T FOUNDED ON INVENTARY.";
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                }
                            }
                        break;

                        case 19: return 0; break;
                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}

/********************************************************************
*                    Function:  Sale_Product                        *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function manage the Inventory Sales.                         *
********************************************************************/
int Sell_Product (struct Article_Struct *Pointer_Articles_Struct)
{
    int Cursor_Pos = 13;
    char Name[Max_Chars];
    int Quantity_Prod;
    bool Found_Article = false;

    system("cls");
    Show_Title ();
    gotoxy(29,9);
    cout << ">> SALE PRODUCT <<" << endl;
    gotoxy(5,13);
    cout << "Name Product :" << endl;
    gotoxy(4,15);
    cout << "Quantity Prod :" << endl;
    gotoxy(5,17);
    cout << "<< SAVE >> ";
    gotoxy(5,19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << " << RETURN MAIN" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    gotoxy(22,Cursor_Pos);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_UP:
                {
                    if (Cursor_Pos > 13) Cursor_Pos = Cursor_Pos - 2;

                }
                break;

                case KEY_DOWN:
                {
                    if (Cursor_Pos < 19) Cursor_Pos = Cursor_Pos + 2;
                }
                break;

                case KEY_ENTER:
                {
                    switch (Cursor_Pos)
                    {
                        case 13:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin.getline (Name,Max_Chars,'\n');
                        break;

                        case 15:
                            gotoxy(20,Cursor_Pos);
                            cout << (char)Cursor << " ";
                            cin >> Quantity_Prod;

                        break;

                        case 17:
                            if (Quantity_Prod == 0 || Name[0] == 0)
                            {
                                gotoxy(23,25);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                cout << "ERROR: YOU MUST ENTER ALL VALUES.  ";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                            }
                            else
                            {
                                int j;
                                int i;
                                for (j = 0 ; j < Counter_Articles ; j++)
                                {
                                    for (i = 0 ; i<Max_Chars ; i++)
                                    {
                                        if (Pointer_Articles_Struct[j].Name[i] != toupper(Name[i]) || Pointer_Articles_Struct[j].Name[i] == 0)
                                        {
                                            break;
                                        }
                                    }

                                    if (i == strlen(Name))
                                    {
                                        Found_Article = true;
                                        break;
                                    }
                                }

                                if (Found_Article)
                                {
                                    if (Quantity_Prod <= Pointer_Articles_Struct[j].Pieces)
                                    {
                                        Pointer_Articles_Struct[j].Pieces -= Quantity_Prod;
                                        Pointer_Articles_Struct[j].Value = Pointer_Articles_Struct[j].Cost * Pointer_Articles_Struct[j].Pieces;
                                        return 0;
                                    }
                                    else
                                    {
                                        gotoxy(23,25);
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                        cout << "ERROR: ARTICLES QUANTITY IS TOO HIGH.";
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                    }
                                }
                                else
                                {
                                    gotoxy(23,25);
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Red);
                                    cout << "ERROR: ARTICLE DIDN'T FOUNDED ON INVENTARY.";
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);
                                }
                            }
                        break;

                        case 19: return 0; break;
                    }
                }
            }
            gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}

/********************************************************************
*                    Function:  Report_Product                      *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function show the Report Products.                           *
********************************************************************/
int Report_Product (struct Article_Struct *Pointer_Articles_Struct)
{
    float Total = 0;

    system("cls");
    Show_Title ();
    gotoxy(27,9);
    cout << ">> REPORT PRODUCTS <<" << endl;
    gotoxy(1,11);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,12);
    cout << "|No.|";
    cout << "      NAME     |";
    cout << "     BUY     |";
    cout << "     SALE    |";
    cout << "  AVALIABLE  |";
    cout << "     PRICE    |";
    gotoxy(1,13);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(1,9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Yellow);
    cout << " << RETURN MAIN" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color_Def);

    int j;
    int i;

    for (j = 0 ; j < Counter_Articles ; j++)
    {
        gotoxy(3,14+j);
        cout << j+1;
        gotoxy(10,14+j);
        for (i = 0 ; i<Max_Chars ; i++)
        {
            cout << Pointer_Articles_Struct[j].Name[i];
            if (Pointer_Articles_Struct[j].Name[i] == 0)
            {
                break;
            }
        }
        cout << setprecision(2);
        gotoxy(26,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Cost;
        gotoxy(40,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Price;
        gotoxy(55,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Pieces;
        gotoxy(70,14+j);
        cout << fixed << Pointer_Articles_Struct[j].Value;
    }

    gotoxy(1, 15+j);
    cout <<"------------------------------------------------------------------------------";
    gotoxy(57, 16+j);
    cout << "TOTAL : ";
    gotoxy(70, 16+j);

    for (int k = 0; k < Counter_Articles ; k++)
    {
        Total +=  Pointer_Articles_Struct[k].Value;
    }
    cout << Total;

    gotoxy(16,9);

    do{
        if (kbhit())
        {
            KEY_PAD = getch();

            switch (KEY_PAD)
            {
                case KEY_ENTER:
                {
                    return 0;
                }
            }
            //gotoxy(22,Cursor_Pos);
        }
      }while (KEY_PAD!=27);
}

/********************************************************************
*                  Function:  Get_Elements_Number                   *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer Number of elements inside of structure.                  *
* This function return the number of structure's elements.          *
********************************************************************/
int Get_Elements_Number (struct Article_Struct *Pointer_Articles_Struct)
{
    int Elements_Number = 0;

    for (int i = 0; i < 100 ; i++)
    {
        if (Pointer_Articles_Struct[i].Name[i] == 0) break;
        Elements_Number++;
    }
    return Elements_Number;
}

/********************************************************************
*                Function:  Init_Structure_Elements                 *
* Input Arguments:                                                  *
*- Pointer to Structure Base.                                       *
* Output Arguments:                                                 *
*- Integer value only for indicate that the function is over.       *
* This function initialize the structure base.                      *
********************************************************************/
void Init_Structure_Elements (struct Article_Struct *Pointer_Articles_Struct)
{
    for (int j = 0 ; j < 100; j++)
    {
        for (int i = 0 ; i<Max_Chars ; i++)
        {
            Pointer_Articles_Struct[j].Name[i] = NULL;
        }
        Pointer_Articles_Struct[j].Pieces = 0;
        Pointer_Articles_Struct[j].Cost = 0;
        Pointer_Articles_Struct[j].Price = 0;
        Pointer_Articles_Struct[j].Value = 0;
    }
}


#endif // FUNCIONES_H_INCLUDED
