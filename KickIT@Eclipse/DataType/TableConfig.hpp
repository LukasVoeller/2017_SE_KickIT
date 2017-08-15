#ifndef DATATYPE_TABLECONFIG_HPP_
#define DATATYPE_TABLECONFIG_HPP_

#include <fstream>
#include <sstream>
#include <iostream>

class TableConfig {

public:
	float tableHeight;
	float tableWidth;

	bool isKeeperActive;
	bool isDefenseActive;
	bool isMidfieldActive;
	bool isOffenseActive;

	float playerGapDefense;
	float playerGapMidfield;
	float playerGapOffense;

	float distGoalToKeeper;
	float distGoalToDefense;
	float distGoalToMidfield;
	float distGoalToOffense;

	float offsetTopSideKeeper;
	float offsetBottomSideKeeper;
	float offsetTopSideDefense;
	float offsetBottomSideDefense;
	float offsetTopSideMidfield;
	float offsetBottomSideMidfield;
	float offsetTopSideOffense;
	float offsetBottomSideOffense;
	float shotTriggerRange;

	TableConfig(){
		loadConfig();
	}

	void loadConfig() {
		std::ifstream configFile("TableConfig.txt");
		std::string line;
		int valueID = 1;

		if (configFile.is_open()) {
			while (getline(configFile, line)) {
				int value = getNumber(line);

				switch(valueID){
				    case 1: tableHeight = value; break;
				    case 2: tableWidth = value; break;
				    case 3: isKeeperActive = value; break;
				    case 4: isDefenseActive = value; break;
				    case 5: isMidfieldActive = value; break;
				    case 6: isOffenseActive = value; break;
				    case 7: playerGapDefense = value; break;
				    case 8: playerGapMidfield = value; break;
				    case 9: playerGapOffense = value; break;
				    case 10: distGoalToKeeper = value; break;
				    case 11: distGoalToDefense = value; break;
				    case 12: distGoalToMidfield = value; break;
				    case 13: distGoalToOffense = value; break;
				    case 14: offsetTopSideKeeper = value; break;
				    case 15: offsetBottomSideKeeper = value; break;
				    case 16: offsetTopSideDefense = value; break;
				    case 17: offsetBottomSideDefense = value; break;
				    case 18: offsetTopSideMidfield = value; break;
				    case 19: offsetBottomSideMidfield = value; break;
				    case 20: offsetTopSideOffense = value; break;
				    case 21: offsetBottomSideOffense = value; break;
				    case 22: shotTriggerRange = value; break;
				}
				valueID++;
			}

			configFile.close();
		} else {
			std::cout << "ERROR: Unable to open calculator config file" << std::endl;
		}
	}

	void saveConfig() {
		std::ofstream outfile("TableConfig.txt");

		outfile << "tableHeight: " << tableHeight << "\n"
				<< "tableWidth: " << tableWidth << "\n"
				<< "isKeeperActive: " << isKeeperActive << "\n"
				<< "isDefenseActive: " << isDefenseActive << "\n"
				<< "isMidfieldActive: " << isMidfieldActive << "\n"
				<< "isOffenseActive: " << isOffenseActive << "\n"
				<< "playerGapDefense: " << playerGapDefense << "\n"
				<< "playerGapMidfield: " << playerGapMidfield << "\n"
				<< "playerGapOffense: " << playerGapOffense << "\n"
				<< "distGoalToKeeper: " << distGoalToKeeper << "\n"
				<< "distGoalToDefense: " << distGoalToDefense << "\n"
				<< "distGoalToMidfield: " << distGoalToMidfield << "\n"
				<< "distGoalToOffense: " << distGoalToOffense << "\n"
				<< "offsetTopSideKeeper: " << offsetTopSideKeeper << "\n"
				<< "offsetBottomSideKeeper: " << offsetBottomSideKeeper << "\n"
				<< "offsetTopSideDefense: " << offsetTopSideDefense << "\n"
				<< "offsetBottomSideDefense: " << offsetBottomSideDefense << "\n"
				<< "offsetTopSideMidfield: " << offsetTopSideMidfield << "\n"
				<< "offsetBottomSideMidfield: " << offsetBottomSideMidfield << "\n"
				<< "offsetTopSideOffense: " << offsetTopSideOffense << "\n"
				<< "offsetBottomSideOffense: " << offsetBottomSideOffense << "\n"
				<< "shotTriggerRange: " << shotTriggerRange
				<< std::endl;

		outfile.close();
	}

	void printConfig() {

	}

private:
	void createEmptyFile() {
		std::ofstream outfile("TableConfig.txt");

		outfile << "tableHeight: 0\n"
				"tableWidth: 0\n"
				"isKeeperActive: 0\n"
				"isDefenseActive: 0\n"
				"isMidfieldActive: 0\n"
				"isOffenseActive: 0\n"
				"playerGapDefense: 0\n"
				"playerGapMidfield: 0\n"
				"playerGapOffense: 0\n"
				"distGoalToKeeper: 0\n"
				"distGoalToDefense: 0\n"
				"distGoalToMidfield: 0\n"
				"distGoalToOffense: 0\n"
				"offsetTopSideKeeper: 0\n"
				"offsetBottomSideKeeper: 0\n"
				"offsetTopSideDefense: 0\n"
				"offsetBottomSideDefense: 0\n"
				"offsetTopSideMidfield: 0\n"
				"offsetBottomSideMidfield: 0\n"
				"offsetTopSideOffense: 0\n"
				"offsetBottomSideOffense: 0\n"
				"shotTriggerRange: 0"
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

#endif //DATATYPE_TABLECONFIG_HPP_
