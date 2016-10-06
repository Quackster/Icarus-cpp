#include "stdafx.h"
#include "boot/Icarus.h"

int main(int argc, char* argv[]) {

    try {
		Icarus::boot();
	} catch (std::exception& e) {
        std::cout << std::endl << " Error occurred: " << e.what() << std::endl;
	}

    while (true);

	return 0;
}
