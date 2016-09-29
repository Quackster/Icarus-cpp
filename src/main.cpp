#include "stdafx.h"
#include "Icarus.h"

int main(int argc, char* argv[]) {
	try {
		Icarus::boot();
	} catch (std::exception& e) {
		printf("Error occurred: %s", e.what());
	}
	return 0;
}
