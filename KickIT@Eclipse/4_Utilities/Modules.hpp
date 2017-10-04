/**
 * @file Modules.hpp
 * @brief
 */

#ifndef MODULES_HPP
#define MODULES_HPP

#include "../4_Utilities/ConfigReader.hpp"
#include <vector>
#include <map>
#include <string>
#include <exception>

typedef void (*fp)(std::vector<void*>*);

/**FunctionNotFoundException class
 *
 */
class FunctionNotFoundException: public std::exception {
public:
	/**FunctionNotFoundException constructor
	 *
	 */
	FunctionNotFoundException(const char* name) :
			n(name) {
		std::cout << n << " function not registered!" << std::endl;
	}

protected:
	std::string n;

};

/**FunctionAllreadyRegisteredException class
 *
 */
class FunctionAllreadyRegisteredException: public std::exception {
public:
	/**FunctionAllreadyRegisteredException constructor
	 *
	 */
	FunctionAllreadyRegisteredException(const char* name) :
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
	 * Throws FunctionAllreadyRegisteredException if the function has been
	 * registered before.
	 *
	 * @param (const char* name, fp function)
	 */
	void registerFunction(const char* name, fp function) {
		std::string name_string(name);
		if (functions.insert(std::pair<std::string, fp>(name_string, function)).second == false) {
			throw new FunctionAllreadyRegisteredException(name);
		}
	}

	/**execute function
	 *
	 *
	 * @param (const char* algo, vector<void*>* params)
	 *
	 * Find out which function is referenced by config-file.
	 * Look up if that function has been registered.
	 *
	 * Throws FunctionNotFoundException if the name has not been registered
	 * or cannot be found in config file.
	 *
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
