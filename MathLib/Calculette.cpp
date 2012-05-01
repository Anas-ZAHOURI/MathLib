/*************************************************************************
* Project: librairie Mathématique
* Function: Calcul sur des grands nombre entiers
*************************************************************************
* $Author: Anas Zahouri
* $Name: $ anosi22
*************************************************************************
*
* Copyright 2012 by company name
*
************************************************************************/
#include <stdio.h>
#include <string.h>
#include "GrandNombre.cpp"
int main()
{
    char const * a = "123456012457984546412354565787987846100123456789629";
    char const * b = "9517534286421972213546";
    char c[100];
    /*GrandNombre obj1 = new GrandNombre(a);
    GrandNombre obj2 = new GrandNombre(b);*/
    GrandNombre obj1(a);
    GrandNombre obj2(b);
    /*obj1.setNbr(a);

    obj2.setNbr(b);*/
    printf("%d \n",obj1.comparaison(obj1));
    return 0;
}
