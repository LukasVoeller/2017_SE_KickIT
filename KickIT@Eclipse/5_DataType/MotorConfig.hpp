/**
 * @file MotorConfig.hpp
 * @brief
 */

#ifndef MOTORCONFIG_HPP
#define MOTORCONFIG_HPP

#include "../4_Utilities/ConfigReader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

/**MotorConfig class
 *
 */
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

	/**MotorConfig function
	 *
	 */
	MotorConfig():cr("6_Configuration/MotorConfig.txt"){
		loadConfig();
	}

	/**loadConfig function
	 *
	 */
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

	/**saveConfig function
	 *
	 */
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

#endif //MOTORCONFIG_HPP
