
#include <iostream>
#include <string>
#include <vector>
void checkEmptiness(const std::string& text) {
    if (text.empty()) {
        throw "Error! Your string is empty";
    }
}
void checkIfHasWords(const std::string& text, const std::string& delimeters) {
    if (text.find_first_not_of(delimeters) == std::string::npos) {
        throw "Error! String contains no words, only delimetrs!";
    }
}
std::vector<std::string> SplitText(const std::string& text, const std::string& delimeters) {
    std::vector<std::string> words;
    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(delimeters, beg_index);
    while (beg_index != std::string::npos) {
        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            words.push_back(word);
        }
        //std::cout << word << '\n';
        beg_index = text.find_first_not_of(delimeters, end_index);
        end_index = text.find_first_of(delimeters, end_index + 1);
    }
    return words;
}
bool checkPalindrome(const std::string& word) {
    for (size_t i = 0; i < word.size() / 2; ++i) {
        if (word[i] != word[word.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
void PrintVector(const std::vector<std::string>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}
void FindPalindromes(const std::string& text, const std::string& delimeters) {
    std::vector<std::string> words = SplitText(text, delimeters);
    std::string result;
    for (size_t i = 0; i < words.size(); ++i) {
        const std::string& word = words[i];
        if (checkPalindrome(word)) {
            if (!result.empty()) {
                result += ", ";
            }
            result += word;
        }
    }
    if (result.empty()) {
        throw "No palindromes found.";
    }
    else {
        std::cout << "Palindromes string: " << result << std::endl;
    }
}
void FindLongestPalindromes(const std::string& text, const std::string& delimeters) {
    std::vector<std::string> words = SplitText(text, delimeters);
    std::vector<std::string> longestPalindromes;
    size_t maxLength = 0;
    for (size_t i = 0; i < words.size(); ++i) {
        const std::string& word = words[i];
        if (checkPalindrome(word)) {
            if (word.size() > maxLength) {
                longestPalindromes = { word };
                maxLength = word.size();
            }
            else if (word.size() == maxLength) {
                longestPalindromes.push_back(word);
            }
        }
    }
    if (longestPalindromes.empty()) {
        throw "No palindromes found.";
    }
    else {
        std::cout << "Longest palindrome(s): ";
        for (size_t i = 0; i < longestPalindromes.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << longestPalindromes[i];
        }
        std::cout << std::endl;
    }
}
int main() {
    std::string str, dlm;
    try {
        std::cout << "Enter your delimetrs: ";
        getline(std::cin, dlm);
        checkEmptiness(dlm);
        std::cout << "Enter your string: ";
        getline(std::cin, str);
        checkEmptiness(str);
        checkIfHasWords(str, dlm);
        FindPalindromes(str, dlm);
        FindLongestPalindromes(str, dlm);
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
	return 0;
}

