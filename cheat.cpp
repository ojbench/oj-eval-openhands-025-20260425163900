

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <sstream>
#include <random>

// A parser for the custom language
class ProgramParser {
private:
    std::mt19937 rng;
    
    // Generate a random identifier
    std::string generateIdentifier() {
        static const char chars[] = "abcdefghijklmnopqrstuvwxyz";
        std::string result;
        std::uniform_int_distribution<> dist(5, 10);
        int len = dist(rng);
        for (int i = 0; i < len; i++) {
            result += chars[rng() % 26];
        }
        return result;
    }
    
    // Add random whitespace variations
    std::string addWhitespaceVariations(const std::string& code) {
        std::string result = code;
        // Randomly add extra spaces
        std::uniform_int_distribution<> dist(0, 10);
        if (dist(rng) < 3) {
            // Add extra spaces in random places
            std::size_t pos = 0;
            while ((pos = result.find(" ", pos)) != std::string::npos) {
                if (dist(rng) < 2) {
                    result.insert(pos, " ");
                }
                pos += 1;
            }
        }
        return result;
    }
    
    // Rename variables and functions
    std::string renameIdentifiers(const std::string& code) {
        std::string result = code;
        std::map<std::string, std::string> renames;
        
        // Simple regex to find identifiers (this is a simplified approach)
        std::regex identifier_regex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)");
        std::sregex_iterator iter(result.begin(), result.end(), identifier_regex);
        std::sregex_iterator end;
        
        while (iter != end) {
            std::string match = iter->str();
            // Skip keywords and built-in functions
            if (match == "function" || match == "set" || match == "array" || 
                match == "create" || match == "get" || match == "set" || 
                match == "print" || match == "block" || match == "endprogram") {
                ++iter;
                continue;
            }
            
            if (renames.find(match) == renames.end()) {
                renames[match] = generateIdentifier();
            }
            ++iter;
        }
        
        // Replace all occurrences
        for (const auto& pair : renames) {
            std::string pattern = "\\b" + pair.first + "\\b";
            result = std::regex_replace(result, std::regex(pattern), pair.second);
        }
        
        return result;
    }
    
    // Reorder independent statements when possible
    std::string reorderStatements(const std::string& code) {
        // This is a simplified version - in a real implementation, we would
        // need to parse the AST and identify independent statements
        return code;
    }

public:
    ProgramParser() : rng(std::random_device{}()) {}
    
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
        
        // Apply transformations in sequence
        result = renameIdentifiers(result);
        result = addWhitespaceVariations(result);
        
        // Add comments
        result += "\n; Transformed by plagiarism-avoidance tool\n";
        
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

