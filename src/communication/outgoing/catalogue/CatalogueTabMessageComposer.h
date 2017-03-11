/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>
#include <boost/algorithm/string.hpp>    

#include "communication/outgoing/MessageComposer.h"

class CatalogueTab;
class CatalogueTabMessageComposer : public MessageComposer {

public:
	CatalogueTabMessageComposer(std::string type, std::vector<CatalogueTab> parent_tabs, int parent_id, int rank) : 
		type(type), 
		parent_tabs(parent_tabs), 
		parent_id(parent_id), 
		rank(rank) { }

    const Response compose() const {
        Response response = this->createResponse();

		response.writeBool(true);
		response.writeInt(0);
		response.writeInt(-1);
		response.writeString("root");
		response.writeString("");
		response.writeInt(0);
		response.writeInt(parent_tabs.size());

		for (CatalogueTab parent_tab : parent_tabs) {
			this->appendCatalogueIndexData(parent_tab, response);
			this->recursiveCatalogueIndex(parent_tab, response);
		}

		response.writeBool(false);
		response.writeString(type);

        return response;
    }

	const void appendCatalogueIndexData(CatalogueTab tab, Response &response) const {

		response.writeBool(tab.enabled ? tab.id : -1);
		response.writeInt(tab.icon_image);
		response.writeInt(tab.id);

		std::string lower_child_caption = tab.caption;
		boost::algorithm::to_lower(lower_child_caption);
		response.writeString(lower_child_caption);

		response.writeString(tab.caption);
		response.writeInt(0); // TODO: flat offers
	}

	const void recursiveCatalogueIndex(CatalogueTab tab, Response &response) const {

		std::vector<CatalogueTab> *child_tabs = tab.child_tabs;
		response.writeInt(child_tabs->size());

		for (CatalogueTab child_tab : *child_tabs) {
			this->appendCatalogueIndexData(child_tab, response);
			this->recursiveCatalogueIndex(child_tab, response);
		}
	}

    const int getHeader() const {
        return Outgoing::CatalogueTabMessageComposer;
    }

private:
	std::string type;
	std::vector<CatalogueTab> parent_tabs;
	int parent_id;
	int rank;
};