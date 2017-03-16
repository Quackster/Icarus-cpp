#pragma once
#include <map>
#include <vector>

#include "CatalogueTab.h"
#include "CataloguePage.h"
#include "CatalogueItem.h"

class CatalogueManager
{
public:
    CatalogueManager();
    ~CatalogueManager();
	
	void assignFurnitureData();
	void loadCatalogueTabs(CatalogueTab *tab, int parent_id);

	std::vector<CatalogueTab*> getParentTabs(int rank);

	CataloguePage *getPage(int page_id);
	std::vector<CatalogueItem*> getItemsByPage(int page_id) { return this->getPage(page_id)->items; }
	CatalogueItem *getItem(int item_id);

	std::map<int, CataloguePage*> getPages() { return pages; }
	std::map<int, CatalogueItem*> getItems() { return items; }

private:
	std::vector<CatalogueTab*> parent_tabs;
	std::map<int, CatalogueItem*> items;
	std::map<int, CataloguePage*> pages;
};

