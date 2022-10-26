#pragma once
class Helper
{
private:
	//Variables Clock
	float _time;
	float _time_max;

public:
	Helper();
	~Helper();
	
	//Getter & Setters Clock
	void setTime(float time);
	float getTime();
	
	// Clock Method
	bool isReady();
	
	//Clock Update
	void updateClock();
};
