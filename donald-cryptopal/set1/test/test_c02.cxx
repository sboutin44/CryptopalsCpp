#include "c02.hxx"
#include "test_c02.hxx"

bool test_fixed_xor()
{   
    /* Parameters of this test comme from  */
    std::string inputStr0 = "1c0111001f010100061a024b53535009181c";
    std::string inputStr1 = "686974207468652062756c6c277320657965";
    std::string outputStr;

    fixed_xor(inputStr0, inputStr1, outputStr);

    std::string expectedOutputStr = "746865206b696420646f6e277420706c6179";
    
    return (expectedOutputStr == outputStr);
}