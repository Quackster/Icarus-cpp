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
	
	void loadCatalogueTabs();
	std::vector<CatalogueTab> getParentTabs(int rank);
	std::vector<CatalogueTab> getChildTabs(int parent_id, int rank);
	CataloguePage getPage(int page_id);
	std::map<int, CataloguePage> getPages() { return pages; }
private:
	std::vector<CatalogueTab> parent_tabs;
	std::map<int, std::vector<CatalogueTab>> child_tabs;
	std::map<int, CataloguePage> pages;
};

