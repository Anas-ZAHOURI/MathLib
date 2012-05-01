#include <stdio.h>
#include <string.h>
#include <gmp.h>
#define MAX(a, b)((a) >= (b) ? (a) : (b))

class GrandNombre
{
    private :
    //Const ??
        char const * nbr1;
        //ba9i la taille khassha dkhol
        int cap,taille;
        char c[];

    public :
    //constructeur

        GrandNombre(){}
        GrandNombre(char const * nbr2)
        {
            nbr1=nbr2;
        }


    //getter and setter
        char const * getNbr()
        {
            return nbr1;
        }

        void setNbr(char const * nbr2)
        {
            nbr1=nbr2;
        }

        int getCap()
        {
            return cap;
        }

        void setCap(int nbr2)
        {
            cap=nbr2;
        }

        int getTaille()
        {
            return taille;
        }

        void setTaille(int nbr2)
        {
            taille=nbr2;
        }



        int cmp(GrandNombre obj)
        {
            int sz1 = (int)strlen(nbr1);
            int sz2 = (int)strlen(obj.getNbr());

            if (sz1 > sz2)
                return 1;
            else if (sz1 < sz2)
                    return -1;
                else
                    return strcmp(nbr1, obj.getNbr());
        }
        void suprZeros(char *s)
{
    int n = (int)strlen(s);
    int i;

    /* On supprime les zéros inutiles */
    for (i = n - 1; i > 0 && s[i] == '0'; i--)
        s[i] = '\0';
}


/* Retourne le chaîne s
 * 1234 -> 4321
 * abcde -> edcba
 */
void reverse(char *s)
{
    int n = (int)strlen(s);
    int i;

    for (i = 0; i < n / 2; ++i)
    {
        int tmp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = tmp;
    }
}

/* Supprime les zéros inutiles et retourne les nombre n */
void transforme(char *s)
{
    suprZeros(s);
    reverse(s);
}

/* -------------------------------------------------------------------------- */

char * addition(GrandNombre obj)
{
    //char c[100];
    /* Nombre de chiffres de a */
    int tailleA = strlen ( nbr1 );
    /* Nombre de chiffres de b */
    int tailleB = strlen ( obj.getNbr() );
    /* Nombre de chiffres mini de c */
    int tailleC =  MAX ( tailleA, tailleB );
    /* Retenue */
    int cr = 0;

    int i;
    for ( i = 0; i <= tailleC || cr; i++ )
    {
        int tmp = cr;

        /* On effectue la somme de la colonne actuelle */
        if ( i < tailleA )
            tmp += nbr1[tailleA - i - 1] - '0';
        if ( i < tailleB )
            tmp += obj.getNbr()[tailleB - i - 1] - '0';

        /* Si la somme dépasse 10, on pose une retenue */
        cr = tmp / 10;

        if ( cr )
        {
            /* Il y a une retenue, on ne conserve que l'unité de tmp */
            tmp %=  10;
        }
        /* On récupère le caractère correspondant à la valeur de tmp */
        c[i] = tmp + '0';
    }

    /* On place le caractère de fin de chaîne */
    c[i] = '\0';

    /* On a rempli c par la gauche, on doit la retourner,et supprimer les
     * zéros inutiles.
     */
    transforme ( c );
    return c;
}

};


int main()
{
    char const * a = "123456012457984546412354565787987846100123456789629";
    char const * b = "9517534286421972213546";
    /*GrandNombre obj1 = new GrandNombre(a);
    GrandNombre obj2 = new GrandNombre(b);*/
    GrandNombre obj1(a,100);
    GrandNombre obj2(b,100);
    /*obj1.setNbr(a);

    obj2.setNbr(b);*/
    printf("%s \n",obj1.addition(obj2));
    return 0;
}
