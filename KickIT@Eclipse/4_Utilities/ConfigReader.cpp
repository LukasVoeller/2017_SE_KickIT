/**
 * @file ConfigReader
 * @brief
 */
#include "../4_Utilities/ConfigReader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

ConfigReader::ConfigReader(const char* filename) {
    this->filename = filename;
    this->readFile();
}

void ConfigReader::readFile() {

    //std::string filename(c);
    std::ifstream configFile(this->filename);
    std::string line;

    if (configFile.is_open()) {

        while (getline(configFile, line)) {
        	//std::cout << line << std::endl;
            std::string type;
            std::string name;
            std::istringstream iss(line);
            iss >> type;
            if(type == "int") {
                int valueInt;
                iss >> name >> valueInt;
                this->values[name] = valueInt;
            } else if(type == "string"){
                std::string valueString;
                iss >> name >> valueString;
                this->strings[name] = valueString;
            } else if(!line.find("#") == 0 && line.length() > 0) {
                throw new UnknownParameterTypeException(type.c_str());
            }
        }

    } else {
        throw new CannotOpenConfigFileException(filename);
    }

}

std::string ConfigReader::getStringValue(const char *name) {
    if(this->strings.find(name) != this->strings.end()) {
        return this->strings[name];
    } else {
        throw new ParameterNotFoundException(name);
    }
}

int ConfigReader::getIntValue(const char *name) {
    if(this->values.find(name) != this->values.end()) {
        return this->values[name];
    } else {
    	std::cout << name << std::endl;
        throw new ParameterNotFoundException(name);
    }
}

void ConfigReader::setStringValue(const char *name, const char *value) {
    std::string n(value);
    this->strings[name] = n;
    this->valueChanged = true;
}

void ConfigReader::setIntValue(const char *name, const int value) {
    this->values[name] = value;
    this->valueChanged = true;
}

void ConfigReader::writeOut() {
    if(this->valueChanged){

        std::ifstream configFile(this->filename);
        std::string line;
        std::vector<std::string> namesToWrite;
        std::vector<std::string> wholeFile;

        if (configFile.is_open()) {

            while (getline(configFile, line)) {
                wholeFile.push_back(line);
                if(!line.find("#") == 0 && line.length() > 0) {
                    std::string type;
                    std::string name;
                    std::string value;
                    std::string comment;

                    std::istringstream iss(line);
                    iss >> type >> name >> value >> comment;
                    if (this->values.find(name) == this->values.end() && this->strings.find(name) == this->strings.end()) {
                        std::cout << name << std::endl;
                        throw new ConfigFileChangedException(filename);
                    } else if (this->values.find(name) != this->values.end()) {
                        std::string numberString = std::to_string(this->values[name]);
                        if (value != numberString) {
                            namesToWrite.push_back(name);
                        }
                    } else if (this->strings.find(name) != this->strings.end()) {
                        if (value != this->strings[name]) {
                            namesToWrite.push_back(name);
                        }
                    }

                }
            }

        } else {
            throw new CannotOpenConfigFileException(filename);
        }
        configFile.close();
        std::ofstream cfWrite(this->filename);

        for (int i = 0 ; i < wholeFile.size(); i++){
            std::string type;
            std::string name;
            std::string value;
            std::string comment;
            std::istringstream iss(wholeFile[i]);
            iss >> type >> name >> value >> comment;

            if(std::find(namesToWrite.begin(), namesToWrite.end(), name) != namesToWrite.end()){
                if(this->strings.find(name) != this->strings.end()) {
                    int fao = wholeFile[i].find(value, 0);
                    wholeFile[i].replace(wholeFile[i].find(value, 0), value.length(), this->strings[name]);
                } else if(this->values.find(name) != this->values.end()) {
                    std::string valueString = std::to_string(this->values[name]);
                    wholeFile[i].replace(wholeFile[i].find(value, 0), value.length(), valueString);
                }
            }

            cfWrite << wholeFile[i] << "\n";
        }

        cfWrite.close();

    }
}
