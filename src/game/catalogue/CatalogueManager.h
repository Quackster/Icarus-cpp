#pragma once
#include <map>
#include <vector>

#include "CatalogueTab.h"
#include "CataloguePage.h"

class CatalogueManager
{
public:
    CatalogueManager();
    ~CatalogueManager();
	
	void loadCatalogueTabs(CatalogueTab tab, int parent_id);
	std::vector<CatalogueTab> getParentTabs(int rank);
	CataloguePage getPage(int page_id);
	std::map<int, CataloguePage> getPages() { return pages; }
private:
	std::vector<CatalogueTab> parent_tabs;
	std::map<int, CataloguePage> pages;
};

