
#include "lib.h"

using namespace std;

int dict_size;
vector<string> dictionary; // Vector used to allow the use of different dictionaries.

void load_dictionary(const char* filename)
{
    string resourcesdir = "./resources/";
    ifstream file;
    
    ios::iostate filestate;
    file.open(filename);
    
    try {
        file.open((resourcesdir+string(filename)).c_str());
        if ( file.fail() )
            throw file.rdstate();
       
        int position = 0;
        for (std::string line; std::getline(file, line) ; ) {
            dictionary.push_back(line);
        }        
        dict_size = dictionary.size();
    }
    catch (ios::iostate filestate)
    {
        if (filestate == ios::failbit) {
            cout << "failbit" << endl;
        }
            
        if (filestate == ios::badbit) {
            cout << "badbit" << endl;  
        }        
    }   
}

void englishScore(uint8_t* sentence)
{
    string word;
    string sentence_string((char*) sentence); // Allow the use of string::find    
    int score = 0;
    size_t not_found = string::npos ;

    /* Filter some sentences with strange characters to speed up the process */
//    for (char ascii = 33 ; ascii < 47 ; ascii++) {
//        if (sentence_string.find(ascii) != not_found )
//            return;
//    }
    
    int j=0;
    while (j<dictionary.size())
    {
        word = dictionary[j];
        if (sentence_string.find(" " + word + " ") != string::npos)
            score++;

        j++;
    }

    if (score > 2) // si le score est égal à 0 ça sert à rien d'afficher.
    {
        cout << endl;
        cout << "Deciphered text:  " << endl;
        cout << sentence << endl;
        cout << "score: " << score << endl;
    }
}

void singlebyteXORattack(uint8_t* ciphertext, int size )
{
    uint8_t* key_array = new uint8_t[size];
    uint8_t* deciphered;
    assert(dictionary.empty() == false);
            
    // Brut force
    for (int key=0;key<=0xFF;key++)
    {
        memset(key_array, (uint8_t) key, size); // Cast to a byte to prevent an infinite loop. 
        deciphered = myXOR(ciphertext,key_array,size);
        englishScore(deciphered);
    }
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
        englishScore(deciphered);

    }

    // Cas de key = 0xFF
    memset(key_array, 0xFF, size);
    deciphered = myXOR(ciphertext,key_array,size);
    englishScore(deciphered);
}
