

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

// A simple parser for the custom language
class ProgramParser {
public:
    // Read a program from input
    std::string scanProgram(std::istream& in) {
        std::string line;
        std::string program;
        while (std::getline(in, line)) {
            // Stop at endprogram
            if (line == "endprogram") {
                break;
            }
            program += line + "\n";
        }
        return program;
    }
    
    // Transform the program to avoid plagiarism detection
    std::string transformProgram(const std::string& program) {
        std::string result = program;
        
        // Simple transformation: add comments and whitespace variations
        // This is a placeholder implementation
        
        // Replace function names with synonyms
        result = std::regex_replace(result, std::regex("\\(function \\("), "(function (renamed_func ");
        
        // Add random comments
        result += "\n; This is a transformed program\n";
        
        return result;
    }
};

int main() {
    ProgramParser parser;
    std::string program = parser.scanProgram(std::cin);
    std::string transformed = parser.transformProgram(program);
    std::cout << transformed;
    return 0;
}

