/**
 * @file TableConfig
 * @brief
 */
#ifndef TABLECONFIG_HPP
#define TABLECONFIG_HPP

#include <fstream>
#include <sstream>
#include <iostream>

#include "../4_Utilities/ConfigReader.hpp"

/**TableConfig class
 *
 */
class TableConfig {
protected:
	ConfigReader cr;

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

	/**TableConfig function
	 *
	 */
	TableConfig():cr("6_Configuration/TableConfig.txt"){
		loadConfig();
	}

	/**loadConfig function
	 *
	 */
	void loadConfig() {

		tableWidth = cr.getIntValue("tableWidth");
		tableHeight = cr.getIntValue("tableHeight");
		isKeeperActive = cr.getIntValue("isKeeperActive");
		isDefenseActive = cr.getIntValue("isDefenseActive");
		isMidfieldActive = cr.getIntValue("isMidfieldActive");
		isOffenseActive = cr.getIntValue("isOffenseActive");
		playerGapDefense = cr.getIntValue("playerGapDefense");
		playerGapMidfield = cr.getIntValue("playerGapMidfield");
		playerGapOffense = cr.getIntValue("playerGapOffense");
		distGoalToKeeper = cr.getIntValue("distGoalToKeeper");
		distGoalToDefense = cr.getIntValue("distGoalToDefense");
		distGoalToMidfield = cr.getIntValue("distGoalToMidfield");
		distGoalToOffense = cr.getIntValue("distGoalToOffense");
		offsetTopSideKeeper = cr.getIntValue("offsetTopSideKeeper");
		offsetBottomSideKeeper = cr.getIntValue("offsetBottomSideKeeper");
		offsetTopSideDefense = cr.getIntValue("offsetTopSideDefense");
		offsetBottomSideDefense = cr.getIntValue("offsetBottomSideDefense");
		offsetTopSideMidfield = cr.getIntValue("offsetTopSideMidfield");
		offsetBottomSideMidfield = cr.getIntValue("offsetBottomSideMidfield");
		offsetTopSideOffense = cr.getIntValue("offsetTopSideOffense");
		offsetBottomSideOffense = cr.getIntValue("offsetBottomSideOffense");
		shotTriggerRange = cr.getIntValue("shotTriggerRange");

	}

	/**saveConfig function
	 *
	 */
	void saveConfig() {
		cr.setIntValue("tableWidth",tableWidth);
		cr.setIntValue("tableHeight",tableHeight);
		cr.setIntValue("isKeeperActive",isKeeperActive);
		cr.setIntValue("isDefenseActive",isDefenseActive);
		cr.setIntValue("isMidfieldActive",isMidfieldActive);
		cr.setIntValue("isOffenseActive",isOffenseActive);
		cr.setIntValue("playerGapDefense",playerGapDefense);
		cr.setIntValue("playerGapMidfield",playerGapMidfield);
		cr.setIntValue("playerGapOffense",playerGapOffense);
		cr.setIntValue("distGoalToKeeper",distGoalToKeeper);
		cr.setIntValue("distGoalToDefense",distGoalToDefense);
		cr.setIntValue("distGoalToMidfield",distGoalToMidfield);
		cr.setIntValue("distGoalToOffense",distGoalToOffense);
		cr.setIntValue("offsetTopSideKeeper",offsetTopSideKeeper);
		cr.setIntValue("offsetBottomSideKeeper",offsetBottomSideKeeper);
		cr.setIntValue("offsetTopSideDefense",offsetTopSideDefense);
		cr.setIntValue("offsetBottomSideDefense",offsetBottomSideDefense);
		cr.setIntValue("offsetTopSideMidfield",offsetTopSideMidfield);
		cr.setIntValue("offsetBottomSideMidfield",offsetBottomSideMidfield);
		cr.setIntValue("offsetTopSideOffense",offsetTopSideOffense);
		cr.setIntValue("offsetBottomSideOffense",offsetBottomSideOffense);
		cr.setIntValue("shotTriggerRange",shotTriggerRange);
		cr.writeOut();
	}

	/**printConfig function
	 *
	 */
	void printConfig() {

	}
};

#endif //TABLECONFIG_HPP
