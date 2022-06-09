#include <regex>
#include <iostream>

using namespace std;

class Scanner
{
private:
    uint8_t current_state;
    string buffer;
    uint16_t line_length;

public:
    Scanner();
    ~Scanner();
    void feed(string c);
};


