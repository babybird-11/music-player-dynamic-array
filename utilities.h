#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using std::string;

string read_string(const string& prompt);
int read_integer(const string& prompt);
int read_integer(const string& prompt, int min, int max);
double read_double(const string& prompt);
char read_char(const string& prompt);


bool contains(const string& str, const string& substr);
bool is_empty(const string& text);

bool read_boolean(const string& prompt);

#endif