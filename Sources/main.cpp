#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>

bool startsWith(const std::string& s, const std::string& start) {
	return s.substr(0, start.size()) == start;
}

int main(int argc, char** argv) {
	std::ofstream file("zeugs.txt");
	file << "called" << "\n";
	for (int i = 1; i < argc; ++i) {
		file << argv[i] << "\n";
	}
	if (argc < 2) return 0;
	std::string request = argv[1];
	if (startsWith(request, "Username")) printf("\n");
	else if (startsWith(request, "Password")) printf("\n");
}
