#ifndef DATATYPE_CAMERACONFIG_HPP_
#define DATATYPE_CAMERACONFIG_HPP_

#include <fstream>
#include <sstream>
#include <iostream>

class CameraConfig {
public:
	int redLow;
	int redHigh;
	int greenLow;
	int greenHigh;
	int blueLow;
	int blueHigh;
	int width;
	int height;
	int packetsize;
	int exposureTime;

	CameraConfig(){
		loadConfig();
	}

	void loadConfig() {
		std::ifstream configFile("CameraConfig.txt");
		std::string line;
		int valueID = 1;

		if (configFile.is_open()) {
			while (getline(configFile, line)) {
				int value = getNumber(line);

				switch(valueID){
				    case 1: redLow = value; break;
				    case 2: redHigh = value; break;
				    case 3: greenLow = value; break;
				    case 4: greenHigh = value; break;
				    case 5: blueLow = value; break;
				    case 6: blueHigh = value; break;
				    case 7: width = value; break;
				    case 8: height = value; break;
				    case 9: packetsize = value; break;
				    case 10: exposureTime = value; break;
				}
				valueID++;
			}

			configFile.close();
		} else {
			std::cout << "ERROR: Unable to open camera config file" << std::endl;
		}
	}

	void saveConfig() {
		std::ofstream outfile("CameraConfig.txt");

		outfile << "RedLow: " << redLow << "\n"
				<< "RedHigh: " << redHigh << "\n"
				<< "GreenLow: " << greenLow << "\n"
				<< "GreenHigh: " << greenHigh << "\n"
				<< "BlueLow: " << blueLow << "\n"
				<< "BlueHigh: " << blueHigh << "\n"
				<< "Width: " << width << "\n"
				<< "Height: " << height << "\n"
				<< "Packetsize: " << packetsize << "\n"
				<< "ExposureTime: " << exposureTime
				<< std::endl;

		outfile.close();
	}

	void printConfig() {
		std::cout << "CAMERA CONFIGURATION\n" << "RedLow: "
				<< redLow << "\n" << "RedHigh: " << redHigh << "\n"
				<< "GreenLow: " << greenLow << "\n" << "GreenHigh: "
				<< greenHigh << "\n" << "BlueLow: " << blueLow << "\n"
				<< "BlueHigh: " << blueHigh << "\n" << "Width: " << width
				<< "\n" << "Height: " << height << "\n" << "Packetsize: "
				<< packetsize << "\n"
				<< "ExposureTime: "  << exposureTime << "\n" << std::endl;
	}

private:
	void createEmptyFile() {
		std::ofstream outfile("CameraConfig.txt");

		outfile << "RedLow: 0\n"
				"RedHigh: 0\n"
				"GreenLow: 0\n"
				"GreenHigh: 0\n"
				"BlueLow: 0\n"
				"BlueHigh: 0\n"
				"Width: 0\n"
				"Height: 0\n"
				"Packetsize: 0\n"
				"ExposureTime: 0\n"
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


#endif //DATATYPE_CAMERACONFIG_HPP_
