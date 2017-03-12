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


	// 4, -114

	int number = (0 << 24)
		| (0 << 16)
		| (4 << 8)
		| -114;

	cout << MAKEWORD(4, -114) << endl;

	bool close_when_crash = false;   
	
	if (argc > 1) {
        if (std::string(argv[1]) == "-close") {
			close_when_crash = true;
        }
    }

    try {
		Icarus::boot();
    } catch (std::exception& e) {
        cout << endl << " Error occurred: " << e.what() << endl;
    }

	if (!close_when_crash) {
		cout << endl << " Server has crashed, if you want the program to close when it crashes, start it with the command argument: -close" << endl;
		while (true);
	}


    return 0;
}
