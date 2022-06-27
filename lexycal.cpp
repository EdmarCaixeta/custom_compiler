#include <fstream>
#include "scanner.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream input_file;
    ofstream output_file;
    string current_line;
    Scanner *scanner = new Scanner();

    /* Check flags */
    if (argc > 2)
    {
        if (strcmp(argv[2], "--debug") == 0)
        {
            freopen("debug.lexyc", "w", stdout);
        }
    }

    // Open Text File
    input_file.open(argv[1]);

    // Check File
    if (!input_file)
    {
        cout << "[ERROR] Can't open file." << endl;
        return 1;
    }

    /* Parse Text and Build Linked List of Tokens */
    /* First Part: Lexycal Analysis */
    while (input_file.peek() != EOF)
    {
        getline(input_file, current_line);
        scanner->feed(current_line.c_str());
    }

    /* Parse List of valid Tokens */
    /* Second Part: Syntatic Analysis */

    return 0;
}
