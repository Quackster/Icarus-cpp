#pragma once
class Item
{
public:
	Item(int id,
	int user_id,
	int item_id,
	int room_id,
	int x,
	int y,
	int z,
	std::string extra_data);
	~Item();

	int id = -1;
	int user_id = -1;
	int item_id = -1;
	int room_id = -1;
	int x = -1;
	int y = -1;
	int z = -1; 
	std::string extra_data = "";
};

