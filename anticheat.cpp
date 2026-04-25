


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

// A simple plagiarism detection system
class PlagiarismDetector {
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
    
    // Calculate similarity between two programs
    double calculateSimilarity(const std::string& program1, const std::string& program2) {
        // Simple similarity measure based on string matching
        // This is a placeholder implementation
        
        // For now, return a neutral value
        return 0.5;
    }
};

int main() {
    PlagiarismDetector detector;
    
    // Read first program
    std::string program1 = detector.scanProgram(std::cin);
    
    // Read second program
    std::string program2 = detector.scanProgram(std::cin);
    
    // Read reference input (we don't use it in this basic version)
    std::string referenceInput;
    std::string line;
    while (std::getline(std::cin, line)) {
        referenceInput += line + "\n";
    }
    
    // Calculate similarity
    double similarity = detector.calculateSimilarity(program1, program2);
    
    // Output the similarity score
    std::cout << similarity << std::endl;
    
    return 0;
}


