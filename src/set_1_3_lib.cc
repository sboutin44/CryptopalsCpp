/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include "lib.h"
using namespace std;

#include "dictionnary.cc"

void quickEnglishChecker(uint8_t* sentence)
{
    string word;
    string sentence_string((char*) sentence); // pour utiliser la fonction find

    int score = 0;

    // {}
    int j=0;
    while (j< 118)
    {
        word = dictionnary[j];
        if (sentence_string.find(word) != string::npos){
            score++;
        }
        j++;
    }

    if (score > 3) // si le score est égal à 0 ça sert à rien d'afficher.
    {
        cout << endl;
        cout << "Deciphered text:  " << endl;
        cout << sentence << endl;
    }
}

void singlebyteXORattack(uint8_t* ciphertext, int size )
{
    uint8_t* key_array = new uint8_t[size];
    uint8_t* deciphered;

    // Brut force attack
    for (uint8_t key=0;key<=0xFE;key++)
    /*
        Si on va jusqu'au cas où key=0xFF, en incrémentant on va se
        retrouver avec key=0 car key est codé sur 1 octet,
        et on va boucler à l'infini, donc on
        traite le cas 0xFF à part.
     */
    {
        memset(key_array, key, size);
        deciphered = myXOR(ciphertext,key_array,size);
        quickEnglishChecker(deciphered);
    }

    // Cas de key = 0xFF
    memset(key_array, 0xFF, size);
    deciphered = myXOR(ciphertext,key_array,size);
    quickEnglishChecker(deciphered);
}

void singlebyteXORattack2(uint8_t* ciphertext, int size )
{
    uint8_t* key_array = new uint8_t[size];
    uint8_t* deciphered;

    // Brut force attack
    for (uint8_t key=0;key<=0xFE;key++)
    /*
        Si on va jusqu'au cas où key=0xFF, en incrémentant on va se
        retrouver avec key=0 car key est codé sur 1 octet,
        et on va boucler à l'infini, donc on
        traite le cas 0xFF à part.
     */
    {
        memset(key_array, key, size);
        deciphered = myXOR(ciphertext,key_array,size);
        quickEnglishChecker(deciphered);

    }

    // Cas de key = 0xFF
    memset(key_array, 0xFF, size);
    deciphered = myXOR(ciphertext,key_array,size);
    quickEnglishChecker(deciphered);
}
