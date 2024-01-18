#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;

enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType() const { return sensorType; }
	float GetValue() const { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime() const { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////
//DEL3

	  void IncreaseFuelConsumption()
    {
        if (sensorType == SensorType::FuelConsumption)
        {
            value *= 1.75; // Increase by 75%
        }
    }

};







void FillData(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);
int main()
{
	vector<SensorData> sensorData;
	FillData(sensorData);

	//SKRIV DIN KOD HÄR!!!!
/////////////////////////////////////////////////////

//DEL 1!
/*
int altitudeRegistered = count_if(sensorData.begin(), sensorData.end(), [](const SensorData &data) {
    time_t timestamp = data.GetTime();
    struct tm *localTime = localtime(&timestamp);

    return data.GetSensorType() == SensorType::Altitude &&
           localTime->tm_year + 1900 == 2012 &&
           localTime->tm_mon + 1 == 1 && // January
           localTime->tm_mday == 2;
});
	cout << "Altitude data registered on 2012-01-02: " << altitudeRegistered << endl;
*/


	
/*
    int altitudeRegistered = count_if(sensorData.begin(), sensorData.end(), [](const SensorData &data) {
        return data.GetSensorType() == SensorType::Altitude &&
               localtime(&data.GetTime())->tm_year + 1900 == 2012 &&
               localtime(&data.GetTime())->tm_mon + 1 == 1 && // January
               localtime(&data.GetTime())->tm_mday == 2;
    });

    cout << "Altitude data registered on 2012-01-02: " << altitudeRegistered << endl;
*/


/*
//jämför sen med algoritm
    time_t targetDate = CreateTime(2012, 1, 2, 0, 0, 0);

    int altitudeRegistered = 0;

    for (const SensorData &data : sensorData)
    {
        if (data.GetSensorType() == SensorType::Altitude && data.GetTime() >= targetDate && data.GetTime() < targetDate + 24 * 60 * 60)
        {
            altitudeRegistered++;
        }
    }

    cout <<"Altitude data registered on 2012-01-02: " <<altitudeRegistered <<endl;

*/
////////////////////////////////////////////////////////////////////////////////////////////////
//DEL2
bool maxSpeedReached = any_of(sensorData.begin(), sensorData.end(), [](const SensorData &data) {
        return data.GetSensorType() == SensorType::SpeedInKmh && data.GetValue() > 99.9;
    });

if (maxSpeedReached){
        cout << "Maxspeed reached" << endl;
	}
else{
        cout << "Maxspeed not reached" << endl;
    }


////////////////////////////////////////////////////////////////////////////////////////////////////
//DEL3
//75% höjning
for (SensorData &data : sensorData){
    data.IncreaseFuelConsumption();
	}    
//testing
for (const SensorData &data : sensorData){
    cout << "Sensor Type: " << static_cast<int>(data.GetSensorType()) << ", Value: " << data.GetValue() << endl;
    }

}


void FillData(vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}

time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}