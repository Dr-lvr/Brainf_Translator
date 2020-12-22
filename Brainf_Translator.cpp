#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

inline std::string optimizeCode(std::string source_code) {

	string result;
	stack<char> resultStack;
	stack<char> optimizerStack;
	string optimizedCode = source_code;

	for (int i = 0; i < (int)optimizedCode.size(); i++) {
		if (optimizerStack.empty()) {
			optimizerStack.push(optimizedCode[i]);
		} else {
			switch (optimizedCode[i]) {
				case ']':
					if (optimizerStack.top() == '[') {
						optimizerStack.pop();
						break;
					} 
					optimizerStack.push(optimizedCode[i]);
					break;
				case '<':
					if (optimizerStack.top() == '>') {
						optimizerStack.pop();
						break;
					}
					optimizerStack.push(optimizedCode[i]);
					break;
				case '>':
					if (optimizerStack.top() == '<') {
						optimizerStack.pop();
						break;
					}
					optimizerStack.push(optimizedCode[i]);
					break;
				case '+':
					if (optimizerStack.top() == '-') {
						optimizerStack.pop();
						break;
					}
					optimizerStack.push(optimizedCode[i]);
					break;
				case '-':
					if (optimizerStack.top() == '+') {
						optimizerStack.pop();
						break;
					}
					optimizerStack.push(optimizedCode[i]);
					break;
				case '.':
				case ',':
				case '[':
					optimizerStack.push(optimizedCode[i]);
					break;
				default:
					break;
			}
		}
	}
	while (!optimizerStack.empty()) {
		resultStack.push(optimizerStack.top());
		optimizerStack.pop();
	}
	while (!resultStack.empty()) {
		result.push_back(resultStack.top());
		resultStack.pop();
	}
	for (auto n : result) {
		cout << n;
	}
	cout << endl;
	return result;
}
inline std::string brainf_to_c(std::string source_cod){

	std::string new_string;
	std::string result;
	std::stack<char> phValidator;


	int indentation = 0;
	new_string = optimizeCode(source_cod);

	//--validate parentesis
	for (int i = 0; i < (int)new_string.size(); i++) {

		if (new_string.at(i) == '[') {
			phValidator.push(new_string.at(i));
		}
		if (new_string.at(i) == ']') {
			if (!phValidator.empty()) {
				phValidator.pop();
			}
			else {
				return "Error!";
			}
		}
	}
	if (!phValidator.empty()) {
		return "Error!";
	}
	int x;
	for (int i = 0; i < (int)new_string.size(); i++) {
		x = 0;
		switch (new_string[i]) {
			case '.': 
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("putchar(*p);\n");
				break;
			case ',':
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("*p = getchar();\n");
				break;
			case '[':
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("if (*p) do {\n");
				indentation++;
				break;
			case ']':
				indentation--;
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("} while (*p);\n");
				break;
			case '<':
				while (new_string[i] == '<') {
					x++;
					i += 1;
				}
				i -= 1;
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("p -= " + to_string(x) + ";\n");
				break;
			case '>':
				while (new_string[i] == '>') {
					x++;
					i += 1;
				}
				i -= 1;
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("p += " + to_string(x) + ";\n");
				break;
			case'+':
				while (new_string[i] == '+') {
					x++;
					i += 1;
				}
				i -= 1;
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("*p += " + to_string(x) + ";\n");
				break;
			case '-':
				while (new_string[i] == '-') {
					x++;
					i += 1;
				}
				i -= 1;
				for (int j = 0; j < indentation; j++) {
					result.append("  ");
				}
				result.append("*p -= " + to_string(x) + ";\n");
				break;
			default:
				break;
		}
	}
	return result;
}
int main() {

	string data = "+<-+.,,+[,.,,.+[-.]-,<>-,>>>>]<,+-+>.<[]>,-.++++-.-,[+<->.]>>>.-<+>,>++[]<-<<-,.,<<-+-+>[<.]-,[]";
	//string data = "[][]";
	string result = brainf_to_c(data);

	cout << result << endl;

	//cout << "--------------------------------------" << endl;

	//string conversion = cToBrainfuck("");

	//cout << conversion << endl;
}