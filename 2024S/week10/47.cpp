#include <iostream>
#include <string>
#include <cctype>

const std::string keyboardKeys = "qwertyuiop[]asdfghjkl;'zxcvbnm,./";

class EncryptedText {
	std::string text;
	std::string mappings;
public:
	EncryptedText() : text(""), mappings("") {};
	EncryptedText(std::string s, std::string m) : text(s), mappings(m) {};
	std::string decrypt() {
		std::string decryptedText = "";
		for (int i = 0; i < text.size(); ++i) 
			decryptedText += (text[i] != ' ') ? getChar(text[i]) : ' ';
		return decryptedText;
	};

	char getChar(char needed) {
		if (std::isalpha(needed)) 
			needed = tolower(needed);

		int i;
		for (i = 0; i < mappings.size() && mappings[i] != needed; ++i);
		return mappings[(i - 2) % mappings.size()];
	}

	void setValue(std::string t) { text = t; }
	std::string getValue() { return text; };
};

int main() {
	EncryptedText cipher("", keyboardKeys);
	std::string temp;

	while (std::getline(std::cin, temp)) {
		cipher.setValue(temp);
		std::cout << cipher.decrypt() << std::endl;
	}

	return 0;
}
