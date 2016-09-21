
#ifdef __unix__
#elif defined(_WIN32) || defined(WIN32) 
#define OS_Windows
#endif

#include "stdafx.h"
#include "Icarus.h"

using namespace std;

int main(int argc, char* argv[]) {
	try {
		Icarus::boot();
	} catch (std::exception& e) {
		printf("Error occurred: %s", e.what());
	}
	return 0;
}
