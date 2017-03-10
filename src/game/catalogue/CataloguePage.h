/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
struct CataloguePage {
	int id = -1;
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