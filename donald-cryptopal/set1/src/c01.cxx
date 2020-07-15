#include "c01.hxx"

void string_to_hex(const std::string &input, uint8_t* &output, int& lenOutput)
{
    assert((input.size() % 2) == 0);

    lenOutput = input.size()/2;
    output = new uint8_t[lenOutput];

    for (int i = 0; i < lenOutput; i++)
    {
        output[i] = std::strtol(input.substr(2*i, 2).c_str(), NULL, 16);
    }
}


void hex_to_string(const uint8_t* input, const int lenInput, std::string &output)
{
    std::ostringstream ss;

    for (int i = 0; i < lenInput; i++)
    {
        ss <<  std::hex << std::setfill('0') << std::setw(2) << (int)input[i];
    }
    output = ss.str();
    ss.clear();    
}