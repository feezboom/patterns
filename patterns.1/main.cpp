#include <iostream>
#include <string>
#include <memory>

class OurClass {
public:
	static std::shared_ptr<OurClass> getInstance() {
		static std::shared_ptr<OurClass> instance = NULL;
		if (instance == NULL) {
			instance = std::shared_ptr<OurClass>(new OurClass());
		}
		return instance;
	}

private:
	OurClass() {};
};

int main() {
	auto instance1 = OurClass::getInstance();
	auto instance2 = OurClass::getInstance();

	std::cout << (instance1 == instance2 ? 
		     	"instances are equal" : "instances are not equal") 
		  << std::endl;

	return 0;
}


