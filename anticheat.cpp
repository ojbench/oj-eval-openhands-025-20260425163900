


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <sstream>
#include <algorithm>
#include <cctype>

// A plagiarism detection system
class PlagiarismDetector {
private:
    // Remove comments and normalize whitespace
    std::string normalizeCode(const std::string& code) {
        std::string result = code;
        
        // Remove comments (lines starting with ;)
        std::istringstream iss(result);
        std::ostringstream oss;
        std::string line;
        while (std::getline(iss, line)) {
            // Remove leading whitespace
            line.erase(0, line.find_first_not_of(" \t"));
            // Skip comment lines
            if (!line.empty() && line[0] != ';') {
                oss << line << "\n";
            }
        }
        result = oss.str();
        
        // Normalize whitespace
        result = std::regex_replace(result, std::regex("\\s+"), " ");
        
        // Remove spaces around parentheses and other delimiters
        result = std::regex_replace(result, std::regex("\\s*\\(\\s*"), "(");
        result = std::regex_replace(result, std::regex("\\s*\\)\\s*"), ")");
        
        return result;
    }
    
    // Extract tokens from code
    std::vector<std::string> tokenize(const std::string& code) {
        std::vector<std::string> tokens;
        std::regex token_regex(R"(\(|\)|[a-zA-Z_][a-zA-Z0-9_]*|[0-9]+)");
        std::sregex_iterator iter(code.begin(), code.end(), token_regex);
        std::sregex_iterator end;
        
        while (iter != end) {
            tokens.push_back(iter->str());
            ++iter;
        }
        
        return tokens;
    }
    
    // Calculate Jaccard similarity between two token sets
    double jaccardSimilarity(const std::vector<std::string>& tokens1, const std::vector<std::string>& tokens2) {
        std::map<std::string, int> count1, count2;
        
        for (const auto& token : tokens1) {
            count1[token]++;
        }
        for (const auto& token : tokens2) {
            count2[token]++;
        }
        
        int intersection = 0;
        int union_size = 0;
        
        // Count intersection and union
        for (const auto& pair : count1) {
            const std::string& token = pair.first;
            int cnt1 = pair.second;
            int cnt2 = count2[token];
            intersection += std::min(cnt1, cnt2);
            union_size += std::max(cnt1, cnt2);
        }
        
        // Add tokens that are only in tokens2
        for (const auto& pair : count2) {
            const std::string& token = pair.first;
            if (count1.find(token) == count1.end()) {
                union_size += pair.second;
            }
        }
        
        if (union_size == 0) return 0.0;
        return static_cast<double>(intersection) / union_size;
    }
    
    // Calculate structural similarity based on AST patterns
    double structuralSimilarity(const std::string& code1, const std::string& code2) {
        // This is a simplified version - in a real implementation, we would
        // need to parse the AST and compare structural patterns
        return jaccardSimilarity(tokenize(code1), tokenize(code2));
    }

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
        // Normalize both programs
        std::string norm1 = normalizeCode(program1);
        std::string norm2 = normalizeCode(program2);
        
        // Calculate structural similarity
        double structSim = structuralSimilarity(norm1, norm2);
        
        // For now, we'll use the structural similarity as our main measure
        // In a more sophisticated implementation, we would combine multiple
        // similarity measures with weights
        return structSim;
    }
};

int main() {
    PlagiarismDetector detector;
    
    // Read first program
    std::string program1 = detector.scanProgram(std::cin);
    
    // Read second program
    std::string program2 = detector.scanProgram(std::cin);
    
    // Read reference input (we can use this to verify functional equivalence)
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

