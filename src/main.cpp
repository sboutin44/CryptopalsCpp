//============================================================================
// Name        : Matasano.cpp
// Author      : Sebastien Boutin
// Version     :
// Copyright   : free
// Description :
//============================================================================


#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <fstream>

#include "base64.hpp"

using namespace std;

#include "dictionnary.cpp"

void hexDecode(const char* input, uint8_t* out )
{
    //uint8_t* out = new uint8_t[strlen(input)/2];

    std::string myString(input);

    for (int i=0;i<(myString.size())/2;i++) {
        std::string subStr = myString.substr(i*2,2);
        out[i] = strtoul(subStr.c_str(), 0, 16);
    }
//    return out;
}

int occurence(const char* s, char myChar )
{
    int occ = 0;
    char current = s[0];
    int i=0;
    while (current != '\0')
    {
        if (current == myChar)
            occ++;
        current = s[i+1];
        i++;
    }
    return occ;
}

float frequency(const char* s,char c)
{
    if (occurence(s,c) == 0) {
        return 0;
    }
    else {
        return (float) strlen(s) / (float) occurence(s,c) ;
    }
}

float frequencyCheck(const char* s)
{
    string sentence(s); // to use the find function.

    int deltas[8]; // Store deltas of the 8th most frequent letters in english.

    deltas[0] = frequency(s,'e') - 12.02;
    deltas[1] = frequency(s,'t') - 9.10;
    deltas[2] = frequency(s,'a') - 8.12;
    deltas[3] = frequency(s,'o') - 7.68;
    deltas[4] = frequency(s,'i') - 7.31;
    deltas[5] = frequency(s,'n') - 6.95;
    deltas[6] = frequency(s,'s') - 6.28;
    deltas[7] = frequency(s,'r') - 6.02;

    int sum = 0;
    for (int i=0;i<8;i++)
        sum += deltas[i];

    return sum;
}


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
        cout << "Text trouvé:  " << endl;
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

void repeatedKeyXor (
    const char* input,
    const char* key,
    int         inputSize,
    int         keySize,
    const       char* output)
{
    // Expand the key to the size of the input.
    char* expandedKey = new char[inputSize];
    for (int i=0; i<=(inputSize%keySize);i+=keySize)
        strcpy(expandedKey+i,key);

    cout << expandedKey << endl;
}


int main()
{
    cout << "\n============================" << endl;
    cout << "Base64 encoding:" << endl;
    test_base64();

    cout << "\n============================" << endl;
    cout << "Fixed XOR" << endl;
    uint8_t a[] = {0x1c,0x01,0x11,0x00,0x1f,0x01,0x01,0x00,0x06,0x1a,0x02,0x4b,0x53,0x53,0x50,0x09,0x18,0x1c};
    uint8_t b[] = {0x68,0x69,0x74,0x20,0x74,0x68,0x65,0x20,0x62,0x75,0x6c,0x6c,0x27,0x73,0x20,0x65,0x79,0x65};

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    uint8_t* c = myXOR( a, b, sizeof(a));
    cout << "c: " << c << endl;

    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 3" << endl;
    cout << "Detect single-character XOR" << endl;

    uint8_t toDecrypt[] = {0x1b,0x37,0x37,0x33,0x31,0x36,0x3f,0x78,0x15,0x1b,0x7f,0x2b,0x78,0x34,0x31,0x33,0x3d,0x78,0x39,0x78,0x28,0x37,0x2d,0x36,0x3c,0x78,0x37,0x3e,0x78,0x3a,0x39,0x3b,0x37,0x36};

    cout << "toDecrypt: " << toDecrypt << endl;
    uint8_t* key_array = new uint8_t[sizeof(toDecrypt)];

    // Brut force attack
    for (uint8_t key=0;key<=0xFE;key++)
    /*
        Si on va jusqu'au cas où key=0xFF, en incrémentant on va se
        retrouver avec key=0 car key est codé sur 1 octet,
        et on va boucler à l'infini, donc on
        traite le cas 0xFF à part.
     */
    {
        memset(key_array, key, sizeof(toDecrypt));
        c = myXOR(toDecrypt,key_array,sizeof(toDecrypt));
        quickEnglishChecker(c);
    }

    // Cas de key = 0xFF
    memset(key_array, 0xFF, sizeof(toDecrypt));
    c = myXOR(toDecrypt,key_array,sizeof(toDecrypt));
    quickEnglishChecker(c);

    //
    singlebyteXORattack(toDecrypt, sizeof(toDecrypt) );

    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 4" << endl;

    string resourcesdir = "resources/";
    string filename = "ciphertext_set1_chall4.txt";

    ifstream fileToDecrypt;
    fileToDecrypt.open((resourcesdir+filename).c_str());

    if ( (fileToDecrypt.rdstate() & std::ifstream::failbit ) != 0 ) {
        std::cerr << "Error opening " << filename << "\n";
        return 1;
    }

    uint8_t* hexline = new uint8_t[60];
    for (std::string line; std::getline(fileToDecrypt, line) ; )
    {
        hexDecode(line.c_str(),hexline);
        singlebyteXORattack(hexline,60);
    }

    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 5" << endl;
    cout << "Implement repeating-key XOR" << endl;

    const char a = "Burning 'em, if you ain't quick and nimble";
    const char b = "I go crazy when I hear a cymbal";
    const char* key = "ICE";


    return 0;
}
