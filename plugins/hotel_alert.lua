plugin_details = {
	name = "HotelAlert",
	author = "Quackster"
}

events = {
	"PlayerTryLoginEvent",
	"PlayerLoginEvent"
}

function onEnable(plugin)
	-- If you want, use print() to show everyone this method being called
	print (string.format(' [Plugin] [Lua] Initialising plugin %s by %s', plugin:getName(), plugin:getAuthor()))
end

function onTryLoginEvent(event)

	local ip_address = event:getIpAddress()

	print (string.format(' [ALERT!!!] Login attempt from: %s', ip_address))

	return event
end



function onLoginEvent(event)

	local username = event:getPlayer():getDetails().username

	event:getPlayer():sendAlert(string.format('Hello %s!\n\nWelcome to Icarus Hotel!', username), '')
	return event
end

