#include "aes.h"
#include "lib.h"

using namespace std;


generateAESkey(){
  srand (time(NULL));

  byte v = rand() % 256;

  cout <<  v << endl;
}

void challenge_11() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "11. An ECB/CBC detection oracle" << endl;
  cout << "------------------------------------\n" << endl;
}
