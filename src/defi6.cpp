#include <iostream>
#include <cstring>
#include "englishCheck.h"
using namespace std;

class xSize{}; ///classe d'exeption


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

int findEditDistance(char input1[], char input2[])
{
    size_t taille1= strlen(input1);
    size_t taille2= strlen(input2);
    int editDistance(0);
    if (taille1!=taille2)
    {
        throw xSize();
    }
    for (unsigned int i=0; i<taille1; i++)
    {
        for (int j=7; j>-1; j--)
        {
            editDistance+= ((input1[i]>> j) & 0x01)^((input2[i]>> j) & 0x01);
        }
    }
    return editDistance;
}

int main()
{
    size_t KEYSIZE(0);

}
