#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class xTaille{};

void XORCombination(char input1[], char input2[], char output[])
/** \brief combinaisonXOR
 *
 * \param tableau char (input1)
 * \param tableau char (input2)
 * \param tableau char (output)
 * \return void
 *
 */
{
    size_t taille1= strlen(input1);
    size_t taille2= strlen(input2);
    size_t taille3= strlen(output);
    if (!(taille1==taille2 && taille2==taille3))
    {
        throw xTaille();
    }
    for (unsigned int i=0; i<taille1; i++)
    {
        output[i]= input1[i] ^ input2[i];
    }
}

int main()
{
    char entree1[37]= "1c0111001f010100061a024b53535009181c";
    char entree2[37]= "686974207468652062756c6c277320657965";
    char resultat[37]= "une chaine de caracteres pour strlen";

    try
    {
        XORCombination(entree1, entree2, resultat);
    }catch (xTaille)
    {
        cout << "les tableaux ne sont pas equivalents" << endl;
    }

    for (unsigned int i=0; i<5; i++)
    {
        cout << resultat[i];
    }
    cout << endl;

    return 0;
}
