#pragma once
#include <iostream>

class FileUser
{
private:
	std::string _name;
	int _points;
	FileUser* users;
public:
	
	FileUser();
	~FileUser();
	
	//getters
	std::string getName();
	int getPoints();
	
	//setters
	void setName(std::string name);
	void setPoints(int points);
	
	//methods
	FileUser* sortUsers();
	int howManyUsers();
	bool saveUser(std::string name, int points);
	bool loadUser(int pos);
};

