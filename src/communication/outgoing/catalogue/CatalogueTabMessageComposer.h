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
		rank(rank) 
	{ }

    const Response compose() const {
        Response response = this->createResponse();

		response.writeBool(true);
		response.writeInt(0);
		response.writeInt(-1);
		response.writeString("root");
		response.writeString("");
		response.writeInt(0);
		response.writeInt(parent_tabs.size());

		for (CatalogueTab parentTab : parent_tabs) {

			response.writeBool(parentTab.enabled);
			response.writeInt(parentTab.icon_image);
			response.writeInt(parentTab.id);

			std::string lower_parent_caption = parentTab.caption;
			boost::algorithm::to_lower(lower_parent_caption);
			response.writeString(lower_parent_caption);

			response.writeString(parentTab.caption);
			response.writeInt(0); // TODO: flat offers

			std::vector<CatalogueTab> child_tabs = Icarus::getGame()->getCatalogueManager()->getChildTabs(parentTab.id, rank);

			response.writeInt(child_tabs.size());

			for (CatalogueTab child_tab : child_tabs) {

				response.writeBool(child_tab.enabled);
				response.writeInt(child_tab.icon_image);
				response.writeInt(child_tab.id);

				std::string lower_child_caption = child_tab.caption;
				boost::algorithm::to_lower(lower_child_caption);
				response.writeString(lower_child_caption);

				response.writeString(child_tab.caption);
				response.writeInt(0);
				response.writeInt(0);
			}
		}

		response.writeBool(false);
		response.writeString(type);

        return response;
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