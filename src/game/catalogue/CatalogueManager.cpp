/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "CatalogueManager.h"
#include "CatalogueTab.h"

#include "dao/CatalogueDao.h"

/*
    Constructor for catalogue manager
*/
CatalogueManager::CatalogueManager() {
	this->loadCatalogueTabs();
}

/*
	Loads all catalogue tabs and sorts them into parent
	and child tab lists

	@return none
*/
void CatalogueManager::loadCatalogueTabs() {

	this->parent_tabs = CatalogueDao::getTabs(-1);

	for (auto parent_tab : parent_tabs) {
		std::vector<CatalogueTab> child = CatalogueDao::getTabs(parent_tab.id);
		this->child_tabs.insert(std::make_pair(parent_tab.id, child));	
	}
}

/*
	Gets all parent tabs with the right rank supplied

	@rank user rank
	@return list of parent tabs
*/
std::vector<CatalogueTab> CatalogueManager::getParentTabs(int rank) {
	std::vector<CatalogueTab> tabs;

	for (auto parent_tab : parent_tabs) {
		if (parent_tab.parent_id <= rank) {
			tabs.push_back(parent_tab);
		}
	}

	return tabs;
}

/*
	Gets all parent tabs with the right rank and parent tab id supplied

	@rank user rank
	@return list of child tabs
*/
std::vector<CatalogueTab> CatalogueManager::getChildTabs(int parent_id, int rank) {

	std::vector<CatalogueTab> tabs;

	if (child_tabs.count(parent_id) > 0) {
		for (auto child_tab : child_tabs.find(parent_id)->second) {
			if (child_tab.min_rank <= rank) {
				tabs.push_back(child_tab);
			}
		}
	}

	return tabs;
}

/*
    Deconstructor for catalogue manager
*/
CatalogueManager::~CatalogueManager()
{
}
