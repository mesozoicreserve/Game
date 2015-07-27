#include <String>
#include <deque>
//#include <Appointment.h>


class Schedule
{
private:
    bool active;
    std::string scheduleType;
    deque<Appointment> appList;

public:
    Schedule();
    void createSchedule();
    void checkTask(std::string date,std::string time);
    void setSchedule(std::string appName,std::string date, std::string time);
};

void Schedule::createSchedule(std::string scheduleName)
{
    switch (scheduleName)
    {
    case "FerryArrival":
        scheduleType=1;
        break;
    }

    setDefaultTasks();

}

void Schedule::setDefaultTasks()
{

}
