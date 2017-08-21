#ifndef DATATYPE_MOTORCONFIG_HPP_
#define DATATYPE_MOTORCONFIG_HPP_


#include <fstream>
#include <sstream>
#include <iostream>


class MotorConfig {

	MotorConfig(){
		loadConfig();
	}

	void loadConfig(){
		std::ifstream configFile ("MotorConfig.txt");
		std::string line;
		int valueID = 1;

		if (configFile.is_open()) {
			while (getline(configFile, line)) {
				int value = getNumber(line);

				switch(valueID) {
				case 1: break;
				case 2: break;
				case 3: break;
				case 4: break;
				}
				valueID++;
			}
			configFile.close();
		}else {
			std::cout << "ERROR: Unable to open motor config file" << std::endl;
		}
	}

	void saveConfig() {
		std::ofstream outfile("MotorConfig.txt");

		outfile <<"" <<  "\n"
				<< std::endl;

		outfile.close();
	}

	void printConfig() {
		std::cout << "MOTOR CONFIGURATION\n" << "...:"
				<< std::endl;
	}

private:
	void createEmptyFile() {
		std::ofstream outfile("MotorConfig.txt");

		outfile << "...0\n"
				<< std::endl;
		outfile.close();
	}

	int getNumber(std::string s) {
		std::istringstream iss(s);
		std::string temp;
		int number;
		iss >> temp >> number;
		return number;
	}

};


#endif /* DATATYPE_MOTORCONFIG_HPP_ */
