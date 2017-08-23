#ifndef DATATYPE_TABLECONFIG_HPP_
#define DATATYPE_TABLECONFIG_HPP_

#include <fstream>
#include <sstream>
#include <iostream>
#include "../Util/ConfigReader.hpp"

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

	TableConfig():cr("configuration/TableConfig.txt"){
		loadConfig();
	}

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

	void printConfig() {

	}
};

#endif //DATATYPE_TABLECONFIG_HPP_
