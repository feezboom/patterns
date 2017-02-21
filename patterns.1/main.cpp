#include <iostream>
#include <string>

class OneTimeCreatedClass {
public:
	OneTimeCreatedClass() {
		
		static	bool created = false;

		if (created == false) {
			created = true;
			std::cout << "I was born!" << std::endl;
		} else {
			throw "Class can be instantiated only once!";
		}
	}
};


int main() {
	try {
		OneTimeCreatedClass a, b;
	} catch (const char* message) {
		std::cout << std::string("Message caught : ") + message << std::endl;
	}
	return 0;
}


