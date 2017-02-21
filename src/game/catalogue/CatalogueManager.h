#pragma once
#include <map>
#include <vector>

class CatalogueTab;
class CatalogueManager
{
public:
    CatalogueManager();
    ~CatalogueManager();
	
	void loadCatalogueTabs();
	std::vector<CatalogueTab> getParentTabs(int rank);
	std::vector<CatalogueTab> getChildTabs(int parent_id, int rank);

private:
	std::vector<CatalogueTab> parent_tabs;
	std::map<int, std::vector<CatalogueTab>> child_tabs;
};

