#include "stdafx.h"
#include "Item.h"


Item::Item(int id,int user_id, int item_id, int room_id, int x, int y, int z, std::string extra_data) :
	id(id),
	user_id(user_id),
	item_id(item_id),
	room_id(room_id), 
	x(x), y(y), z(z),
	extra_data(extra_data) {
}


Item::~Item()
{
}
