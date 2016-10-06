#include "stdafx.h"
#include "boot/Icarus.h"

int main(int argc, char* argv[]) {

    printf("%c[%dmHELLO!\n", 0x1B, 32);

    try {
		Icarus::boot();
	} catch (std::exception& e) {
        cout << endl << " Error occurred: " << e.what() << endl;
	}

    while (true);

	return 0;
}
