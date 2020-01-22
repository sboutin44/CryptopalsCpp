#include <iostream>
#include "englishCheck.h"
using namespace std;

void XORCombination(char input[], char cle[], char output[])
/** \brief combinaison XOR
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



char singleCharXORBreacker(char input[], char output[])
/** \brief craque un cryptage XOR a cle unique
 *
 * \param chaine crypte
 * \param chaine decrypte
 * \return cle
 *
 */
{
    size_t taille= strlen(input);
    int bestScore(0);
    char bestScoreKey;
    for (char test=0x01; test!='\0'; test++) ///brut force attack
    {
        char combinaison[taille];
        char cle[2]= {test, '\0'};
        XORCombination(input, cle , combinaison);
        int score= englishScore(combinaison);
        if (score>=bestScore)
        {
            bestScore=score;
            bestScoreKey=test;
            for (unsigned int i=0; i<taille; i++)
            {
                output[i]=combinaison[i];
            }
        }
    }
    return bestScoreKey;
}


int main()
{
    char cryptedString[35]= {0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78, 0x15, 0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33, 0x3d, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2d, 0x36, 0x3c, 0x78, 0x37, 0x3e, 0x78, 0x3a, 0x39, 0x3b, 0x37, 0x36, 0x00};
    char decryptedString[35];
    /**for (char test=0x01; test!='\0'; test++) ///brut force attack
    {
        char combinaison[35];
        char cle[2]= {test, '\0'};
        XORCombination(cryptedString, cle , combinaison);
        for (unsigned int i=0; i<34; i++)
        {
            cout << combinaison[i];
        }
        cout << "          " << test;
        cout << endl;
    }**/
    char key= singleCharXORBreacker(cryptedString, decryptedString);
    for (int i=0; i<35; i++)
    {
        cout << decryptedString[i];
    }
    cout << endl << "the key was: " << key;
    return 0;
}
