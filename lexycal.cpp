#include <iostream>
#include "lexycal.h"
#include <regex>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    FILE *input_file;
    char *current = (char *)malloc(sizeof(char));
    current[0] = 0;
    Scanner *scanner = new Scanner();

    // Open Text File
    input_file = fopen(argv[1], "r");

    // Check File
    if (input_file == NULL)
    {
        cout << "[ERROR] Can't open file." << endl;
        return 1;
    }

    do
    {
        scanner->feed(current);
    } while (fscanf(input_file, "%c", current) != EOF);

    return 0;
}
