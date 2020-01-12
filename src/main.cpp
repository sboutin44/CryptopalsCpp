#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

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
    size_t taille2= strlen(input2);
    for (unsigned int i=0; i<taille2; i++)
    {
        output[i]= (input1[i] & 0xff) ^ (input2[i] & 0xff);
    }
}

int main()
{
    char entree1[19]= {0x1c, 0x01, 0x11, 0x00, 0x1f, 0x01, 0x01, 0x00, 0x06, 0x1a, 0x02, 0x4b, 0x53, 0x53, 0x50, 0x09, 0x18, 0x1c, *"\0"};
    char entree2[19]= {0x68, 0x69, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x75, 0x6c, 0x6c, 0x27, 0x73, 0x20, 0x65, 0x79, 0x65, *"\0"};
    char resultat[19];

    XORCombination(entree1, entree2, resultat);

    for (unsigned int i=0; i<18; i++)
    {
        cout << resultat[i];
    }
    cout << endl;

    return 0;
}
