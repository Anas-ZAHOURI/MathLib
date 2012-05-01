#include <string.h>
#include <gmp.h>
class GrandNombre
{
    private :
    //Const ??
        char const * nbr1;
        int cap,taille;
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
        int comparaison(GrandNombre obj)
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
};
