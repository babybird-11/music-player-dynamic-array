#include "utilities.h"
#include "splashkit.h"
#include <string>

string read_string(const string &prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(const string &prompt)
{
    string line = read_string(prompt);
    while (!is_integer(line))
    {
        write_line("Invalid input. Please enter a valid integer.");
        line = read_string(prompt);
    }
    return to_integer(line);
}

int read_integer(const string &prompt, int min, int max)
{
    int result = read_integer(prompt);
    while (result < min || result > max)
    {
        write_line("Please enter a number between " + to_string(min) + " and " + to_string(max) + ".");
        result = read_integer(prompt);
    }
    return result;
}


char read_char(const string &prompt)
{
    string line = read_string(prompt);
    while (line.length() == 0)
    {
        write_line("Please enter a character.");
        line = read_string(prompt);
    }
    return line[0];
}

bool read_boolean(const string &prompt)
{
    while (true)
    {
        string input = read_string(prompt);

        if (input == "y" || input == "Y")
        {
            return true;
        }
        else if (input == "n" || input == "N")
        {
            return false;
        }
        else
        {
            write_line("Please enter 'y' for yes or 'n' for no.");
        }
    }
}


