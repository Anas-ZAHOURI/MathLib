#include <stdio.h>
#include <string.h>
#include <gmp.h>


#define MAX(a, b)((a) >= (b) ? (a) : (b))

#define SZ_MAX  100

/* -------------------------------------------------------------------------- */
int cmp(char const *a, char const *b)
{
    int sz1 = (int)strlen(a);
    int sz2 = (int)strlen(b);

    if (sz1 > sz2)
        return 1;
    else if (sz1 < sz2)
        return -1;
    else
        return strcmp(a, b);
}

/* Supprime les z�ros inutiles(pas vous !... :D)
 * 0001234 devient 1234
 * 00000   devient 0
 */
void suprZeros(char *s)
{
    int n = (int)strlen(s);
    int i;

    /* On supprime les z�ros inutiles */
    for (i = n - 1; i > 0 && s[i] == '0'; i--)
        s[i] = '\0';
}


/* Retourne le cha�ne s
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

/* Supprime les z�ros inutiles et retourne les nombre n */
void transforme(char *s)
{
    suprZeros(s);
    reverse(s);
}



/* -------------------------------------------------------------------------- */

void addition(char const *a, char const *b, char *c)
{
    /* Nombre de chiffres de a */
    int szA = strlen ( a );
    /* Nombre de chiffres de b */
    int szB = strlen ( b );
    /* Nombre de chiffres mini de c */
    int szC =  MAX ( szA, szB );
    /* Retenue */
    int cr = 0;

    int i;
    for ( i = 0; i <= szC || cr; i++ )
    {
        int tmp = cr;

        /* On effectue la somme de la colonne actuelle */
        if ( i < szA )
            tmp += a[szA - i - 1] - '0';
        if ( i < szB )
            tmp += b[szB - i - 1] - '0';

        /* Si la somme d�passe 10, on pose une retenue */
        cr = tmp / 10;

        if ( cr )
        {
            /* Il y a une retenue, on ne conserve que l'unit� de tmp */
            tmp %=  10;
        }
        /* On r�cup�re le caract�re correspondant � la valeur de tmp */
        c[i] = tmp + '0';
    }

    /* On place le caract�re de fin de cha�ne */
    c[i] = '\0';

    /* On a rempli c par la gauche, on doit la retourner,et supprimer les
     * z�ros inutiles.
     */
    transforme ( c );
}



void multiplication(char const *a, char const *b, char *c)
{
    /* taille de a */
    int szA = strlen( a );
    /* taille de b */
    int szB = strlen ( b );
    /* taille de c */
    int szC = szA + szB;

    int i, j;

    /* On rempli z de z�ro, jusqu'au caract�re de fin de cha�ne */
    memset ( c, 0, ( 1 + szC ) * sizeof *c );

    for ( i = 0; i < szA; i++ )
    {
        /* Retenue */
        int cr = 0;

        for ( j = 0; j < szB || cr; j++ )
        {
            /* On effecue la multiplication de b par le chiffre courant de a */
            int tmp = c[i + j] + cr;

            if ( j < szB )
            {
                tmp += ( a[ szA - i - 1] - '0') *
                       ( b[ szB - j - 1] - '0');
            }

            /* Si le produit est sup�rieur � 10, on pose la retenue */
            cr = tmp / 10;

            if ( cr )
            {
                /* si il y a retenue on ne conserve que l'unit� du produit */
                tmp %= 10;
            }

            c[i + j] = tmp;
        }
    }

    for ( i = 0; i < szC; i++ )
    {
        /* On r�cup�re le caract�re correspondant � la valeur de tmp */
        c[i] += '0';
    }

    /* On a rempli c par la gauche, on doit la retourner,et supprimer les
     * z�ros inutiles.
     */
    transforme ( c );

}



void soustraction(char const *a, char const *b, char *c)
{
    if (cmp(a, b) < 0)
    {
        /* |a| < |b| -> -(b - a) */
        c[0] = '-';
        soustraction(b, a, c + 1);
    }
    else
    {
        /* Nombre de chiffres de a */
        int szA = strlen ( a );
        /* Nombre de chiffres de b */
        int szB = strlen ( b );
        /* Retenue */
        int cr = 0;

        int i;
        for ( i = 0; i < szA; i++ )
        {
            /* On effecute la soustraction de la colonne actuelle */
            int tmp = a[szA - i - 1] - '0' - cr;

            if ( i < szB )
                tmp -= b[szB - i - 1] - '0';

            /* si tmp est n�gatif on pose la retenue */
            cr = tmp < 0;
            if ( cr )
            {
                /* Il y a une retenue on rajoute base � la valeur de tmp*/
                tmp += 10;
            }
            /* On r�cup�re le caract�re correspondant � la valeur de tmp */
            c[i] = tmp + '0';
        }

        /* On place le caract�re de fin de cha�ne */
        c[i] = '\0';

        /* On a rempli c par la gauche, on doit la retourner,et supprimer les
         * z�ros inutiles.
         */
        transforme ( c );
    }
}



void division(char const *a, char const *b, char *c)
{
    /* Reste pr�c�dent */
    char tmp[SZ_MAX];
    /* Reste courant */
    char reste[SZ_MAX] = "";

    int szA = strlen ( a );
    int i, j;

    for ( i = 0; i < szA; i++ )
    {
        for ( j = 0; reste[j] != '\0'; j++ )
            ;
        /* On abaisse le chiffre courant de a */
        reste[j] =  a[i];

        /* On place le caract�re '\0' pour former une cha�ne valide */
        reste[j + 1] = '\0';

        /* On initialise le chiffre courant du quotient � 0 */
        c[szA - i - 1] = 0;

        /* Dans reste contient de fois b ?
         * Le r�sultat va dans le chiffre courant du quotient
         */
        while ( cmp ( reste, b ) >= 0 )
        {
            c[szA - i - 1]++;
            soustraction ( reste, b, tmp);
            strcpy ( reste, tmp );
        }
        /* Si le reste est nul */
        if ( reste[0] == '0' )
        {
            /* On se replace au d�but de la cha�ne */
            reste[0] = '\0';
        }

        /* On r�cup�re le caract�re correspondant � la valeur */
        c[szA - i - 1] +=  '0';
    }

    /* On place le caract�re de fin de cha�ne */
    c[i] = '\0';

    /* On a rempli c par la gauche, on doit la retourner,et supprimer les
     * z�ros inutiles.
     */
    transforme ( c );
}

int main ( void )
{
    char const *a = "123456012457984546412354565787987846100123456789629";
    char const *b = "9517534286421972213546";
    char c[SZ_MAX];

    addition(a, b, c);
    printf("%s + %s = %s\n\n", a, b, c);

    soustraction(a, b, c);
    printf("%s - %s = %s\n\n", a, b, c);

    soustraction(b, a, c);
    printf("%s - %s = %s\n\n", b, a, c);

    multiplication(a, b, c);
    printf("%s * %s = %s\n\n", a, b, c);

    division(a, b, c);
    printf("%s / %s = %s\n\n", a, b, c);

/*
    cmp(a, b);
    printf("%s / %s = %d\n\n", a, b, cmp(a, a));
*/
    return 0;
}
