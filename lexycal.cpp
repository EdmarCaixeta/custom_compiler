#include <fstream>
#include "scanner.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    std::ifstream file;
    string current_line;
    Scanner *scanner = new Scanner();

    // Open Text File
    file.open(argv[1]);

    // Check File
    if (!file)
    {
        cout << "[ERROR] Can't open file." << endl;
        return 1;
    }

    /* Parse Text */
    for (int i = 0; i < 1; i++)
    {
        getline(file, current_line);
        scanner->feed(current_line.c_str());
    }

    return 0;
}
