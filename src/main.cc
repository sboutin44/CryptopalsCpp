#include "lib.h"
using namespace std;

void run_challenge(int selection)
{
    switch (selection)
    {
        case 1:
            challenge_1();
            break;
        case 2:
            challenge_2();
            break;
        case 3:
            challenge_3();
            break;
        case 4:
            challenge_4();
            break;
        case 5:
            challenge_5();
            break;
        case 6:
            challenge_6();
            break;
        default:
            std::cerr << "Selection =" << unsigned(selection) << std::endl;
            break;
    }
}

int main(int argc, char* argv[])
{
    int selection = 0;

    if (argc == 1) {
        // Display the list of sets.
        cout << "the cryptopals crypto challenges"          << endl;
        cout << "Enter the number of the challenge you want to run:"    << endl;
        cout << "Set 1 Basics."                             << endl;
        cout << "        1.Convert hex to base64"           << endl;

        cin >> selection;
        run_challenge(selection);
        return 0;
    }

    else
    if(argc == 2) {
        selection = std::stoi(argv[1]);
        run_challenge(selection);
        return 0;
    }

    else {
        std::cerr << "Usage: " << argv[0] << " NAME" << std::endl;
        return 1;
    }
}
