#pragma once

#include "game/player/Player.h"
#include "communication/streams/Request.h"

class PluginMessageEvent
{
public:
	PluginMessageEvent(Player *player, Request request);
	~PluginMessageEvent();

	Player *player;
	Request request;
};

