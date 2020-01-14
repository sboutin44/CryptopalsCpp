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
    char entree1[43]= "Burning 'em, if you ain't quick and nimble";
    char entree2[32]= "I go crazy when I hear a cymbal";
    char cle[4]= "ICE";
    char resultat1[43];
    char resultat2[32];

    XOREncrypting(entree1, cle, resultat1);
    XOREncrypting(entree2, cle, resultat2);
    ostringstream oss;

    for (unsigned int i=0; i<43; i++)
    {
        cout << resultat1[i];
    }
    cout << endl; ///on purge le flux
    for (unsigned int i=0; i<23; i++)
    {
        cout << resultat1[i];
    }
    cout << endl;

    return 0;
}
