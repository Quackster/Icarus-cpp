#include <stdexcept>

#include "stdafx.h"
#include "Icarus.h"

using namespace std;

int main(int argc, char* argv[]) {

	for (int i = 3; i < 10; i++) {
		printf("%i\n", i);
	}

	Icarus::boot();
	return 0;
}
