#pragma once

#include "libh.h"

void readFile2(string fname = "test.txt")
{
    ifstream input;
    size_t pos;
    string line;
        
    input.open(fname);
    if (input.is_open())
    {
        while (getline(input, line))
        {
            cout << "|" << line << endl;
            pos = line.find("hey");
            if (pos != string::npos) // string::npos is returned if string is not found
            {
                cout << "Found!";
                break;
            }
        }
    }

    system("pause");
}