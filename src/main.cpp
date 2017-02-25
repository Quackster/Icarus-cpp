/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"
#include "boot/Icarus.h"

int main(int argc, char* argv[]) {

    try {
		Icarus::boot();
    } catch (std::exception& e) {
        cout << endl << " Error occurred: " << e.what() << endl;
    }

    if (argc > 1) {
        if (std::string(argv[1]) == "-hang") {
            while (true);
        }
    }

    return 0;
}
