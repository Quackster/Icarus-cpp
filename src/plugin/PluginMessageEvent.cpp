#include "stdafx.h"
#include "PluginMessageEvent.h"

PluginMessageEvent::PluginMessageEvent(Player *player, Request request) :
	player(player),
	request(request) {

}


PluginMessageEvent::~PluginMessageEvent()
{
}
