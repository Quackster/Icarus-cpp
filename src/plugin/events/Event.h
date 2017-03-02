#pragma once
class Event {
public:
	virtual ~Event() = default;
	
	virtual std::string getClassName() = 0;
	virtual std::string getEventName() = 0;

	bool isCancelled() const { return cancelled; }
	void setCancelled(const bool &cancelled) { this->cancelled = cancelled; }

protected:
	bool cancelled = false;
};