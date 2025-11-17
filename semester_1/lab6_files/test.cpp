
#include <iostream>
#include <fstream>
void writeAvgToOutputFile(const std::string& filename, double value) {
    std::ofstream out{ filename };
    if (!(out.is_open())) {
        throw "file cannot be open ";
    }
    out << value;
    out.close();
}
int main() {
    try {
        writeAvgToOutputFile("output.txt", 5677);
        std::cout << "file was create";
    }
    catch (const char* msg) {
        std::cout << msg;
    }
}
