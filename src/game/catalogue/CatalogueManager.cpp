/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include <map>

#include "stdafx.h"

#include "boot/Icarus.h"

#include "CatalogueTab.h"
#include "CataloguePage.h"

#include "CatalogueManager.h"

#include "dao/ItemDao.h"
#include "dao/CatalogueDao.h"

/*
	Constructor for catalogue manager
*/
CatalogueManager::CatalogueManager() {
	this->parent_tabs = CatalogueDao::getTabs(-1);
	this->pages = CatalogueDao::getPages();
	this->items = CatalogueDao::getItems();

	for (CatalogueTab *parent_tab : parent_tabs) {
		this->loadCatalogueTabs(parent_tab, parent_tab->id);
	}

	for (auto kvp : this->items) {

		CatalogueItem *item = kvp.second;
		CataloguePage *page = this->getPage(item->page_id);

		if (page != nullptr) {
			page->items.push_back(item);
		}
	}
}

/*
	Assign the Item Definition to each catalogue item

	@return none
*/
void CatalogueManager::assignFurnitureData() {

	for (auto kvp: this->items) {
		CatalogueItem *item = kvp.second;
		item->setDefinition(Icarus::getGame()->getItemManager()->getDefinitionByID(item->item_id));
	}
}

/*
	Recursively loads all catalogue tabs
	
	@param the parent tab
	@param the parent tab id
*/
void CatalogueManager::loadCatalogueTabs(CatalogueTab *tab, int parent_id) {

	std::vector<CatalogueTab*> child = CatalogueDao::getTabs(tab->id);

	if (child.size() > 0) { 

		for (CatalogueTab *parent_tab : child) {
			tab->child_tabs->push_back(parent_tab);
			this->loadCatalogueTabs(parent_tab, parent_tab->id);
		}
	}
}

/*
	Gets all parent tabs with the right rank supplied

	@rank user rank
	@return list of parent tabs
*/
std::vector<CatalogueTab*> CatalogueManager::getParentTabs(int rank) {
	std::vector<CatalogueTab*> tabs;

	for (auto parent_tab : parent_tabs) {
		if (parent_tab->parent_id <= rank) {
			tabs.push_back(parent_tab);
		}
	}

	return tabs;
}


/*
	Gets CataloguePage instance by page id

	@param page id
	@return catalogue page instance, or nullptr if nothing was found
*/
CataloguePage *CatalogueManager::getPage(int page_id) {

	if (pages.count(page_id) > 0) {
		return this->pages.find(page_id)->second;
	}

	return nullptr;
}

/*
	Get CatalogueItem instance by item id

	@param item id
	@return catalogue item instance, or nullptr if nothing was found
*/
CatalogueItem *CatalogueManager::getItem(int item_id) {

	if (items.count(item_id) > 0) {
		return this->items.find(item_id)->second;
	}


	return nullptr;
}

/*
	Deconstructor for catalogue manager
*/
CatalogueManager::~CatalogueManager()
{
}
