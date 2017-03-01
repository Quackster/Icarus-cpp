#pragma once
class Event {
public:
	virtual ~Event() = default;
	
	bool isCancelled() const { return cancelled; }
	void setCancelled(const bool &cancelled) { this->cancelled = cancelled; }
protected:
	bool cancelled = false;
};