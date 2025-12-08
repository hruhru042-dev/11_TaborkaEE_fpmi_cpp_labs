
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
void isEmpty(std::fstream& file) {
	if (file.peek() == std::ifstream::traits_type::eof()) {
		throw "File is empty";
	}
}
void isOpen(std::fstream& file) {
	if (!(file.is_open())) {
		throw "The file cannot be opened!";
	}
}
std::string findTheLengthOfStrictlyIncreasingSubstring(const std::string& line) {
	if (line.empty()) return "";
	int max_length = 1, current_length = 1;
	size_t maxStart = 0, start = 0;
	for (size_t i = 1; i < line.size(); ++i) {
		if (line[i] > line[i - 1]) {
			current_length++;
		}
		else {
			current_length = 1;
			start = i;
		}
		if (current_length > max_length) {
			max_length = current_length;
			maxStart = start;
		}
	}
	return line.substr(maxStart, max_length);
}
void printMaxLengthSubstrings(const std::vector<std::string>& substrings, int globalMax) {
	std::cout << "Substrings of maximum length: " << std::endl;
	int count = 0;
	for (size_t i = 0; i < substrings.size() && count < 10; ++i) {
		if (substrings[i].size() == static_cast<size_t>(globalMax)) {
			std::cout << "[" << i + 1 << "] " << substrings[i] << std::endl;
			count++;
		}
	}
	if (count == 0) {
		std::cout << "No maximum length substrings" << std::endl;
	}
}
std::vector<std::string> readLines(std::fstream& file) {
	std::vector<std::string> lines;
	std::string line;
	while (getline(file, line)) {
		lines.push_back(line);
	}
	return lines;
}
int main() {
	try {
		std::fstream file("input.txt", std::ios::out|std::ios::in);
		isOpen(file);
		isEmpty(file);
		std::vector<std::string> lines = readLines(file);
		file.close();
		std::vector<std::string> substrings;
		size_t globalMax = 0;
		for (size_t i = 0; i < lines.size(); ++i) {
			std::string sub = findTheLengthOfStrictlyIncreasingSubstring(lines[i]);
			substrings.push_back(sub);
			globalMax = std::max(globalMax, sub.size());
		}
		std::cout << "Global maximum length: " << globalMax << std::endl;
		printMaxLengthSubstrings(substrings, globalMax);
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}


