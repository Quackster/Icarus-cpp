plugin_details = {
	name = "HotelAlert",
	author = "Quackster"
}

events = {
	"PlayerTryLoginEvent",
	"PlayerLoginEvent"
}

--[[
	Called when the plugin first starts up, so the plugin can load data if needed
	so when the event is called the plugin is ready
	
	param: plugin instance
	return: none
--]]
function onEnable(plugin)
	-- If you want, use print() to show everyone this method being called
	print (string.format(' [Plugin] [Lua] Initialising plugin %s by %s', plugin:getName(), plugin:getAuthor()))
end

--[[
	Try login event called when the user has successfully authenticated, but the user
	may need further checking before having the ability to use the client

	param: PlayerTryLoginEvent instance
	return: PlayerTryLoginEvent so the app can see if anything has been modified
--]]
function onTryLoginEvent(event)

	local ip_address = event:getIpAddress()

	print (string.format(' [ALERT!!!] Login attempt from: %s', ip_address))
	
	-- Only allow local connections (just a test)
	if ip_address != "127.0.0.1" then 
		event:setCancelled(true)
	end

	return event
end


--[[
	Login event called when the user has successfully authenticated and
	hotel packets were sent

	param: PlayerLoginEvent instance
	return: PlayerLoginEvent so the app can see if anything has been modified
--]]
function onLoginEvent(event)

	local username = event:getPlayer():getDetails().username

	event:getPlayer():sendAlert(string.format('Hello %s!\n\nWelcome to Icarus Hotel!', username), '')
	return event
end



