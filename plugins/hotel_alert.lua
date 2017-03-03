plugin_details = {
	name = "HotelAlert",
	author = "Quackster"
}

events = {
	"PlayerLoginEvent"
}

function onEnable()
	-- If you want, use print() to show everyone this method being called
	print (" [Plugin][Lua] Initialising Testing Plugin 1")
end


function onLoginEvent(event)

	local username = event:getPlayer():getDetails().username

	print (string.format('[ALERT!!!] Login attempt from: %s', username))
	
	if username == "TheTesting123" then
		print (string.format('[ALERT!!!] %s was blocked from logging in', username))
		event:setCancelled(true)
	end
	
	return event
end

