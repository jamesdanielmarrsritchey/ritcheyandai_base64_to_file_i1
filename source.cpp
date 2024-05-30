#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*
To compile and install the program on Debian, you can follow these steps:

1. Install the g++ compiler if it's not already installed. You can do this by running the following command in your terminal:
   sudo apt-get install g++

2. Navigate to the directory containing the source code file (let's call it base64.cpp) using the cd command.

3. Compile the source code file using the g++ compiler. You can do this by running the following command in your terminal:
   g++ -o base64 base64.cpp

4. Now, you can run the program using the following command:
   ./base64 --source_file "path_to_your_base64_file" --destination_file "path_to_output_file"

Please replace "path_to_your_base64_file" with the path to the Base64-encoded file you want to decode, and "path_to_output_file" with the path where you want to save the decoded output. The program processes and writes each 4-character chunk from the input file as soon as it's read.
*/

const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string base64_decode(const std::string &input) {
    std::string ret;
    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T[base64_chars[i]] = i;

    int val=0, valb=-8;
    for (char c : input) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            ret.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return ret;
}

int main(int argc, char* argv[]) {
    std::string source_file;
    std::string destination_file;
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "--source_file" && i + 1 < argc) {
            source_file = argv[++i];
        } else if(arg == "--destination_file" && i + 1 < argc) {
            destination_file = argv[++i];
        }
    }
    std::ifstream file(source_file);
    if (!file) {
        std::cerr << "Could not open source file.\n";
        return 1;
    }
    std::ofstream outfile(destination_file, std::ios::binary);
    if (!outfile) {
        std::cerr << "Could not open destination file.\n";
        return 1;
    }
    std::string buffer;
    while (std::getline(file, buffer)) {
        std::string output = base64_decode(buffer);
        outfile.write(output.data(), output.size());
    }

    return 0;
}