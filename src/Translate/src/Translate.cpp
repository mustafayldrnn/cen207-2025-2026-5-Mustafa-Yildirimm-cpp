#include "../header/Translate.h"
#include <algorithm>
#include <iostream>
#include <regex>
#include <cctype>

using namespace Coruh::Translate;

Translate::Translate() {
    lineNumber = 0;
    
    // Initialize BASIC to C++ keyword mappings
    basicToCppKeywords["PRINT"] = "std::cout";
    basicToCppKeywords["LET"] = "";
    basicToCppKeywords["IF"] = "if";
    basicToCppKeywords["THEN"] = "";
    basicToCppKeywords["ELSE"] = "else";
    basicToCppKeywords["ENDIF"] = "}";
    basicToCppKeywords["FOR"] = "for";
    basicToCppKeywords["TO"] = "";
    basicToCppKeywords["STEP"] = "";
    basicToCppKeywords["NEXT"] = "}";
    basicToCppKeywords["INPUT"] = "std::cin";
    basicToCppKeywords["GOTO"] = "goto";
    basicToCppKeywords["GOSUB"] = "";
    basicToCppKeywords["RETURN"] = "return";
    basicToCppKeywords["END"] = "return 0";
    basicToCppKeywords["REM"] = "//";
    basicToCppKeywords["DIM"] = "";
    basicToCppKeywords["SUB"] = "void";
    basicToCppKeywords["FUNCTION"] = "";
    basicToCppKeywords["CALL"] = "";
    basicToCppKeywords["WHILE"] = "while";
    basicToCppKeywords["WEND"] = "}";
    basicToCppKeywords["DO"] = "do";
    basicToCppKeywords["LOOP"] = "} while";
    basicToCppKeywords["SELECT"] = "switch";
    basicToCppKeywords["CASE"] = "case";
    basicToCppKeywords["DEFAULT"] = "default";
    basicToCppKeywords["END SELECT"] = "}";
}

std::string Translate::translate(const std::string& basicCode) {
    std::stringstream cppCode;
    std::stringstream input(basicCode);
    std::string line;
    
    // Add C++ headers and main function
    cppCode << "#include <iostream>\n";
    cppCode << "#include <string>\n";
    cppCode << "#include <unordered_map>\n";
    cppCode << "#include <stack>\n\n";
    cppCode << "int main() {\n";
    cppCode << "  std::unordered_map<std::string, double> var;\n";
    cppCode << "  std::stack<int> call;\n";
    cppCode << "  int pc = 10;\n";
    cppCode << "  while(true) {\n";
    cppCode << "    switch(pc) {\n";
    
    lineNumber = 10;
    
    while (std::getline(input, line)) {
        // Remove leading/trailing whitespace safely
        if (!line.empty()) {
            size_t start = line.find_first_not_of(" \t");
            if (start != std::string::npos) {
                line = line.substr(start);
            } else {
                line.clear();
            }
            
            size_t end = line.find_last_not_of(" \t");
            if (end != std::string::npos) {
                line = line.substr(0, end + 1);
            }
        }
        
        if (line.empty()) continue;
        
        std::string cppLine = parseLine(line);
        if (!cppLine.empty()) {
            cppCode << "    case " << lineNumber << ": {\n";
            cppCode << "      " << cppLine << "\n";
            cppCode << "      pc = " << (lineNumber + 10) << "; break;\n";
            cppCode << "    }\n";
        }
        
        // Safe increment to avoid overflow
        if (lineNumber < INT_MAX - 10) {
            lineNumber += 10;
        } else {
            break; // Prevent infinite loop
        }
    }
    
    cppCode << "    default: return 0;\n";
    cppCode << "    }\n";
    cppCode << "  }\n";
    cppCode << "}\n";
    
    return cppCode.str();
}

std::string Translate::parseLine(const std::string& line) {
    std::string upperLine = line;
    std::transform(upperLine.begin(), upperLine.end(), upperLine.begin(), ::toupper);
    
    // Remove line number if present - safe parsing
    std::string content = line;
    size_t spacePos = content.find(' ');
    if (spacePos != std::string::npos && spacePos > 0) {
        std::string potentialNumber = content.substr(0, spacePos);
        if (isNumber(potentialNumber)) {
            content = content.substr(spacePos + 1);
        }
    }
    
    std::string upperContent = content;
    std::transform(upperContent.begin(), upperContent.end(), upperContent.begin(), ::toupper);
    
    // Safe substring operations with bounds checking
    if (upperContent.find("PRINT") == 0 && content.length() >= 5) {
        return parsePrint(content.substr(5));
    } else if (upperContent.find("LET") == 0 && content.length() >= 3) {
        return parseLet(content.substr(3));
    } else if (upperContent.find("IF") == 0 && content.length() >= 2) {
        return parseIf(content.substr(2));
    } else if (upperContent.find("FOR") == 0 && content.length() >= 3) {
        return parseFor(content.substr(3));
    } else if (upperContent.find("NEXT") == 0 && content.length() >= 4) {
        return parseNext(content.substr(4));
    } else if (upperContent.find("INPUT") == 0 && content.length() >= 5) {
        return parseInput(content.substr(5));
    } else if (upperContent.find("GOTO") == 0 && content.length() >= 4) {
        return parseGoto(content.substr(4));
    } else if (upperContent.find("REM") == 0 && content.length() >= 3) {
        return "// " + content.substr(3);
    } else if (upperContent.find("END") == 0) {
        return "return 0";
    }
    
    return "";
}

std::string Translate::parsePrint(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    if (trimmed.empty()) {
        return "std::cout << std::endl;";
    }
    
    // Handle string literals and variables safely
    if (trimmed[0] == '"') {
        size_t endQuote = trimmed.find('"', 1);
        if (endQuote != std::string::npos) {
            std::string str = trimmed.substr(1, endQuote - 1);
            return "std::cout << \"" + str + "\" << std::endl;";
        }
    } else {
        // Variable or expression
        std::string expr = parseExpression(trimmed);
        return "std::cout << " + expr + " << std::endl;";
    }
    
    return "std::cout << std::endl;";
}

std::string Translate::parseLet(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    size_t equalsPos = trimmed.find('=');
    if (equalsPos != std::string::npos && equalsPos > 0) {
        std::string var = trimmed.substr(0, equalsPos);
        std::string expr = trimmed.substr(equalsPos + 1);
        
        // Safe trimming of variable name
        size_t varStart = var.find_first_not_of(" \t");
        size_t varEnd = var.find_last_not_of(" \t");
        if (varStart != std::string::npos && varEnd != std::string::npos) {
            var = var.substr(varStart, varEnd - varStart + 1);
        } else {
            var.clear();
        }
        
        if (!var.empty()) {
            // Add variable to list safely
            if (std::find(variables.begin(), variables.end(), var) == variables.end()) {
                variables.push_back(var);
            }
            
            return "var[\"" + var + "\"] = " + parseExpression(expr) + ";";
        }
    }
    
    return "";
}

std::string Translate::parseIf(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    size_t thenPos = trimmed.find("THEN");
    if (thenPos != std::string::npos) {
        std::string condition = trimmed.substr(0, thenPos);
        std::string action = trimmed.substr(thenPos + 4);
        
        // Safe trimming of condition
        size_t condStart = condition.find_first_not_of(" \t");
        size_t condEnd = condition.find_last_not_of(" \t");
        if (condStart != std::string::npos && condEnd != std::string::npos) {
            condition = condition.substr(condStart, condEnd - condStart + 1);
        } else {
            condition.clear();
        }
        
        // Safe trimming of action
        size_t actStart = action.find_first_not_of(" \t");
        if (actStart != std::string::npos) {
            action = action.substr(actStart);
        } else {
            action.clear();
        }
        
        if (!condition.empty()) {
            std::string cppCondition = parseExpression(condition);
            std::string cppAction = parseLine(action);
            
            return "if (" + cppCondition + ") { " + cppAction + " }";
        }
    }
    
    return "";
}

std::string Translate::parseFor(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    // Simple FOR loop parsing with safe string operations
    std::istringstream iss(trimmed);
    std::string var, to, startVal, endVal;
    
    if (iss >> var >> to >> startVal >> endVal) {
        if (std::find(variables.begin(), variables.end(), var) == variables.end()) {
            variables.push_back(var);
        }
        
        return "for (int " + var + " = " + startVal + "; " + var + " <= " + endVal + "; " + var + "++) {";
    }
    
    return "";
}

std::string Translate::parseNext(const std::string& content) {
    return "}";
}

std::string Translate::parseInput(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    if (!trimmed.empty()) {
        if (std::find(variables.begin(), variables.end(), trimmed) == variables.end()) {
            variables.push_back(trimmed);
        }
        
        return "std::cin >> var[\"" + trimmed + "\"];";
    }
    
    return "";
}

std::string Translate::parseGoto(const std::string& content) {
    std::string trimmed = content;
    
    // Safe trimming
    size_t start = trimmed.find_first_not_of(" \t");
    if (start != std::string::npos) {
        trimmed = trimmed.substr(start);
    } else {
        trimmed.clear();
    }
    
    if (!trimmed.empty()) {
        return "pc = " + trimmed + ";";
    }
    
    return "";
}

std::string Translate::parseExpression(const std::string& expr) {
    std::string result = expr;
    
    // Replace BASIC operators with C++ operators
    std::string upperExpr = expr;
    std::transform(upperExpr.begin(), upperExpr.end(), upperExpr.begin(), ::toupper);
    
    // Safe replacement to avoid overflow issues with bounds checking
    if (upperExpr.find("AND") != std::string::npos) {
        size_t pos = 0;
        while ((pos = result.find("AND", pos)) != std::string::npos) {
            // Check bounds and word boundaries safely
            if ((pos == 0 || !std::isalnum(result[pos-1])) && 
                (pos + 3 < result.length() ? !std::isalnum(result[pos+3]) : true)) {
                // Safe replacement with overflow protection
                if (pos + 3 <= result.length()) {
                    result.replace(pos, 3, "&&");
                    pos += 2;
                } else {
                    break; // Prevent infinite loop
                }
            } else {
                pos += 3;
            }
            
            // Prevent infinite loop
            if (pos >= result.length()) break;
        }
    }
    
    if (upperExpr.find("OR") != std::string::npos) {
        size_t pos = 0;
        while ((pos = result.find("OR", pos)) != std::string::npos) {
            // Check bounds and word boundaries safely
            if ((pos == 0 || !std::isalnum(result[pos-1])) && 
                (pos + 2 < result.length() ? !std::isalnum(result[pos+2]) : true)) {
                // Safe replacement with overflow protection
                if (pos + 2 <= result.length()) {
                    result.replace(pos, 2, "||");
                    pos += 2;
                } else {
                    break; // Prevent infinite loop
                }
            } else {
                pos += 2;
            }
            
            // Prevent infinite loop
            if (pos >= result.length()) break;
        }
    }
    
    if (upperExpr.find("NOT") != std::string::npos) {
        size_t pos = 0;
        while ((pos = result.find("NOT", pos)) != std::string::npos) {
            // Check bounds and word boundaries safely
            if ((pos == 0 || !std::isalnum(result[pos-1])) && 
                (pos + 3 < result.length() ? !std::isalnum(result[pos+3]) : true)) {
                // Safe replacement with overflow protection
                if (pos + 3 <= result.length()) {
                    result.replace(pos, 3, "!");
                    pos += 1;
                } else {
                    break; // Prevent infinite loop
                }
            } else {
                pos += 3;
            }
            
            // Prevent infinite loop
            if (pos >= result.length()) break;
        }
    }
    
    // Handle variable references with safe regex replacement
    try {
        std::regex varRegex("\\b([A-Za-z][A-Za-z0-9]*)\\b");
        result = std::regex_replace(result, varRegex, "var[\"$1\"]");
    } catch (const std::regex_error& e) {
        // Fallback to manual replacement if regex fails
        std::string temp = result;
        result.clear();
        
        // Safe reserve with overflow protection
        size_t reserveSize = (temp.length() < SIZE_MAX / 2) ? temp.length() * 2 : temp.length();
        result.reserve(reserveSize);
        
        for (size_t i = 0; i < temp.length(); ++i) {
            if (std::isalpha(temp[i])) {
                std::string varName;
                size_t start = i;
                
                // Safe variable name extraction with bounds checking
                while (i < temp.length() && std::isalnum(temp[i])) {
                    varName += temp[i];
                    ++i;
                    
                    // Prevent infinite loop
                    if (varName.length() > 1000) break;
                }
                --i; // Adjust for the loop increment
                
                if (!varName.empty()) {
                    result += "var[\"" + varName + "\"]";
                }
            } else {
                result += temp[i];
            }
        }
    }
    
    return result;
}

bool Translate::isNumber(const std::string& str) {
    if (str.empty()) return false;
    
    // Prevent processing extremely long strings
    if (str.length() > 1000) return false;
    
    bool hasDecimal = false;
    bool hasMinus = false;
    
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        
        if (std::isdigit(c)) {
            continue;
        } else if (c == '.') {
            if (hasDecimal) return false; // Multiple decimal points
            hasDecimal = true;
        } else if (c == '-') {
            if (hasMinus || i != 0) return false; // Minus only at start
            hasMinus = true;
        } else {
            return false; // Invalid character
        }
    }
    
    return true;
}

bool Translate::isVariable(const std::string& str) {
    if (str.empty()) return false;
    
    // Prevent processing extremely long strings
    if (str.length() > 1000) return false;
    
    if (!std::isalpha(str[0])) return false;
    
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (!std::isalnum(c)) {
            return false;
        }
    }
    return true;
}

void Translate::addKeywordMapping(const std::string& basicKeyword, 
                                 const std::string& cppEquivalent) {
    basicToCppKeywords[basicKeyword] = cppEquivalent;
}

std::vector<std::string> Translate::getSupportedKeywords() {
    std::vector<std::string> keywords;
    
    // Reserve space to avoid reallocations
    keywords.reserve(basicToCppKeywords.size());
    
    for (const auto& pair : basicToCppKeywords) {
        // Safe string copy with bounds checking
        if (pair.first.length() <= 1000) {
            keywords.push_back(pair.first);
        }
    }
    
    return keywords;
}

bool Translate::validateSyntax(const std::string& basicCode) {
    // Basic syntax validation with overflow protection
    if (basicCode.empty()) return true;
    
    // Prevent processing extremely long code
    if (basicCode.length() > 100000) return false;
    
    std::stringstream input(basicCode);
    std::string line;
    int lineCount = 0;
    
    while (std::getline(input, line) && lineCount < 10000) { // Prevent infinite loop
        lineCount++;
        
        if (line.empty()) continue;
        
        // Prevent processing extremely long lines
        if (line.length() > 1000) return false;
        
        std::string upperLine = line;
        std::transform(upperLine.begin(), upperLine.end(), upperLine.begin(), ::toupper);
        
        // Check for valid BASIC keywords with safe bounds checking
        bool validKeyword = false;
        for (const auto& keyword : basicToCppKeywords) {
            if (keyword.first.length() <= line.length() && 
                upperLine.find(keyword.first) == 0) {
                validKeyword = true;
                break;
            }
        }
        
        if (!validKeyword && !line.empty()) {
            return false;
        }
    }
    
    return true;
}

std::vector<std::string> Translate::getDetectedVariables() {
    return variables;
}

std::vector<std::string> Translate::getDetectedFunctions() {
    return functions;
}