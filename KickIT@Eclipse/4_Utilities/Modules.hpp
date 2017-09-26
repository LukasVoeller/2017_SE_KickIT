/**
 * @file Modules.hpp
 * @brief
 */

#ifndef MODULES_HPP
#define MODULES_HPP

#include <vector>
#include <map>
#include <string>
#include <exception>

#include "../4_Utilities/ConfigReader.hpp"

typedef void (*fp)(std::vector<void*>*);

/**FunctionNotFoundException class
 *
 */
class FunctionNotFoundException: public std::exception {
public:
	/**FunctionNotFoundException function
	 *
	 */
	FunctionNotFoundException(const char* name) :
			n(name) {
		std::cout << n << " function not registered!" << std::endl;
	}
protected:
	std::string n;
};

/**FunctionAllreadyRegistered class
 *
 */
class FunctionAllreadyRegistered: public std::exception {
public:
	/**FunctionAllreadyRegistered function
	 *
	 */
	FunctionAllreadyRegistered(const char* name) :
			n(name) {
		std::cout << n << " function allready registered!" << std::endl;
	}
protected:
	std::string n;
};



/**Modules class
 *
 */
class Modules {
protected:
	std::map<std::string, fp> functions;
	ConfigReader cr;
	static Modules* _instance;

	/**Modules constructor
	 *
	 */
	Modules():cr("6_Configuration/Algorithm.txt") {}

	/**Modules function
	 *
	 * @param (const Modules&)
	 */
	Modules(const Modules&);

	/**Modules destructor
	 *
	 */
	~Modules() {}

public:

	/**instance function
	 *
	 * @return _instance;
	 */

	static Modules* instance() {
		if (!_instance) _instance = new Modules();
		return _instance;
	}

	/**registerFunction funktion
	 *
	 * @param (const char* name, fp function)
	 */
	void registerFunction(const char* name, fp function) {
		std::string name_string(name);
		if (functions.insert(std::pair<std::string, fp>(name_string, function)).second == false) {
			throw new FunctionAllreadyRegistered(name);
		}
	}

	/**execute funktion
	 *
	 * @param (const char* algo, vector<void*>* params)
	 *
	 * find out which function is referenced by config-file
	 * look up if that function has been registered
	 */
	void execute(const char* algo, std::vector<void*>* params) {
		//find out which function is referenced by config-file
		std::string functionNameFromConfigFile = cr.getStringValue(algo);
		//look up if that function has been registered
		std::map<std::string, fp>::iterator it = functions.find(functionNameFromConfigFile);
		if (it == functions.end()) {
			throw new FunctionNotFoundException(functionNameFromConfigFile.c_str());
		}
		it->second(params);
	}

};

#endif //MODULES_HPP


