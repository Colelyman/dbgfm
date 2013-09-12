#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

int main(int argc, char** argv)
{

    if(argc != 2) {
        fprintf(stderr, "Error: a filename must be provided\n");
        fprintf(stderr, "usage: bwtdisk-prepare filename > output\n");
        exit(EXIT_FAILURE);
    }
    
    std::string filename = argv[1];

    std::string line;
    std::ifstream reader(filename.c_str());
    if(!reader.good()) {
        fprintf(stderr, "Error: could not read %s\n", filename.c_str());
        exit(EXIT_FAILURE);
    }

    // Read the fasta file line by line.
    // When we hit a header we output a symbol separating the current record
    // from the last. Non-ACGT symbols in the records cause an error.
    bool first = true;
    while(getline(reader, line)) {
        if(line.empty())
            continue;
        
        if(line[0] == '>') {

            if(!first)
                std::cout << '$';
            first = false;
        } else {
            if(line.find_first_not_of("ACGT") != std::string::npos) {
                fprintf(stderr, "Error: non-ACGT base found.\n");
                exit(EXIT_FAILURE);
            }
               
            std::cout << line;
        }
    }

    // Print a final dollar sign for the last string
    std::cout << '$';
}
