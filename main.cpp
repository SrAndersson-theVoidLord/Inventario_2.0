/********************************************************************
*                         INVENTORY SYSTEM                          *
*                This program is a Inventory System.                *
*                           Version 2.0                             *
*      Lucas Nicolas Greco(grecolucas477@yahoo.com.ar)              *
*                                       *
********************************************************************/

#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;


#include "Headers/Structs.h"
#include "Headers/Funciones.h"










int main()
{
    struct Article_Struct Articles[100], *Pointer_Articles_Struct = &Articles[0];
    Init_Structure_Elements (Pointer_Articles_Struct);

    for(;;)
    {
        switch (Wait_Option ())
        {
            case 1:
                New_Product (Pointer_Articles_Struct);
            break;

            case 2:
                Delete_Product (Pointer_Articles_Struct);
            break;

            case 3:
                Buy_Product (Pointer_Articles_Struct);
            break;

            case 4:
                Sell_Product (Pointer_Articles_Struct);
            break;

            case 5:
                Report_Product (Pointer_Articles_Struct);
            break;

            case 6:
                return EXIT_SUCCESS;
            break;
        }
    }
}

