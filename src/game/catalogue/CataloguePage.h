#pragma once

struct CataloguePage {
	int id;
	std::string layout;
	std::string headline;
	std::string teaser;
	std::string special;
	std::string text1;
	std::string text2;
	std::string text_details;
	std::string text_teaser;
	bool vip;
	bool loaded;
	int minimum_rank;
};