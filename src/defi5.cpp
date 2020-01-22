#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

void XOREncrypting(char input[], char cle[], char output[])
/** \brief cryptageXOR
 *
 * \param tableau char (input1)
 * \param tableau char (clé)
 * \param tableau char (output)
 * \return void
 *
 */
{
    size_t taille= strlen(input);
    size_t taille_cle= strlen(cle);
    for (unsigned int i=0; i<taille; i++)
    {
        output[i]= input[i] ^ cle[i%taille_cle];
    }
}

int main()
{
    char entree[75]= "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char cle[4]= "ICE";
    char resultat[74];

    XOREncrypting(entree, cle, resultat);

    cout << hex; /// on passe en affichage hexa

    for (unsigned int i=0; i<74; i++)
    {
        short nb = (resultat[i] & 0xF0) >> 4;
        short nb2 = resultat[i] & 0x0F;
        cout << nb << nb2;
    }
    cout << endl; ///on purge le flux

    return 0;
}
