#pragma once
class TestingClass
{
public:
	TestingClass();
	~TestingClass();

	std::string getTest() {
		return this->test;
	}

private:
	std::string test = "test";
};

