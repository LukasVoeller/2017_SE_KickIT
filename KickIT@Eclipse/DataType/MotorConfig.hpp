#ifndef DATATYPE_MOTORCONFIG_HPP_
#define DATATYPE_MOTORCONFIG_HPP_


#include <fstream>
#include <sstream>
#include <iostream>
#include "../Util/ConfigReader.hpp"


class MotorConfig {
protected:
	ConfigReader cr;

public:
	int homingRequired;
	std::string port;
	int keeperAccelerationTranslational;
	int keeperDecelerationTranslational;
	int keeperSpeedTranslational;
	int keeperSleepAfterReset;
	int keeperSleepAfterHoming;
	int keeperBoundaryInwards;
	int keeperBoundaryOutwards;

	int defenseAccelerationTranslational;
	int defenseAccelerationRotary;
	int defenseDecelerationTranslational;
	int defenseDecelerationRotary;
	int defenseSpeedTranslational;
	int defenseSpeedRotary;
	int defenseSleepAfterReset;
	int defenseSleepAfterHoming;
	int defenseBoundaryInwards;
	int defenseBoundaryOutwards;

	MotorConfig():cr("configuration/MotorConfig.txt"){
		loadConfig();
	}

	void loadConfig(){

		homingRequired = cr.getIntValue("homingRequired");
		std::string port = cr.getStringValue("port");

		keeperAccelerationTranslational = cr.getIntValue("keeperAccelerationTranslational");
		keeperDecelerationTranslational = cr.getIntValue("keeperDecelerationTranslational");
		keeperSpeedTranslational = cr.getIntValue("keeperSpeedTranslational");
		keeperSleepAfterReset = cr.getIntValue("keeperSleepAfterReset");
		keeperSleepAfterHoming = cr.getIntValue("keeperSleepAfterHoming");
		keeperBoundaryInwards = cr.getIntValue("keeperBoundaryInwards");
		keeperBoundaryOutwards = cr.getIntValue("keeperBoundaryOutwards");

		defenseAccelerationTranslational = cr.getIntValue("defenseAccelerationTranslational");
		defenseAccelerationRotary = cr.getIntValue("defenseAccelerationRotary");
		defenseDecelerationTranslational = cr.getIntValue("defenseDecelerationTranslational");
		defenseDecelerationRotary = cr.getIntValue("defenseDecelerationRotary");
		defenseSpeedTranslational = cr.getIntValue("defenseSpeedTranslational");
		defenseSpeedRotary = cr.getIntValue("defenseSpeedRotary");
		defenseSleepAfterReset = cr.getIntValue("defenseSleepAfterReset");
		defenseSleepAfterHoming = cr.getIntValue("defenseSleepAfterHoming");
		defenseBoundaryInwards = cr.getIntValue("defenseBoundaryInwards");
		defenseBoundaryOutwards = cr.getIntValue("defenseBoundaryOutwards");

	}

	void saveConfig() {
		cr.setIntValue("homingRequired", homingRequired);
		cr.setStringValue("port", port.c_str());

		cr.setIntValue("keeperAccelerationTranslational",keeperAccelerationTranslational);
		cr.setIntValue("keeperDecelerationTranslational",keeperDecelerationTranslational);
		cr.setIntValue("keeperSpeedTranslational",keeperSpeedTranslational);
		cr.setIntValue("keeperSleepAfterReset",keeperSleepAfterReset);
		cr.setIntValue("keeperSleepAfterHoming",keeperSleepAfterHoming);

		cr.setIntValue("defenseAccelerationTranslational",defenseAccelerationTranslational);
		cr.setIntValue("defenseAccelerationRotary",defenseAccelerationRotary);
		cr.setIntValue("defenseDecelerationTranslational",defenseDecelerationTranslational);
		cr.setIntValue("defenseDecelerationRotary",defenseDecelerationRotary);
		cr.setIntValue("defenseSpeedTranslational",defenseSpeedTranslational);
		cr.setIntValue("defenseSpeedRotary",defenseSpeedRotary);
		cr.setIntValue("defenseSleepAfterReset",defenseSleepAfterReset);
		cr.setIntValue("defenseSleepAfterHoming",defenseSleepAfterHoming);

		cr.writeOut();
	}

};


#endif
