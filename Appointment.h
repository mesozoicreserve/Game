#include <string>

//As it stands we can just use a byte to set a number code for the type
//AppointmentTime - The clock time of the appointment
//appointmentDate - The game date of the appointment
//active - if off the appointment will not fire at the time
//recurring - if on, the appointment will regenerate a date for the action to occur.

/*

  1:Generate Guests at dock. Boat arrives at 9 am every day.

*/
class Appointment
{
private:
    char appID;
    bool active;
    bool recurring;
    std::string appointmentTime;
    std::string appointmentDate;
public:
    Appointment();
    Appointment(char appcode);
    void setApp(char);
    char getAppID();
    void setAppID();
    bool isRecurring();
    bool isActive();
    std::string getAppDate();
    std::string getAppTime();
    void reGenDate();
};

Appointment::Appointment()
{
    setApp(0);
}

void Appointment::setApp(char appCode)
{
    appID = appCode;

    switch(appID)
    {
    // 0 - Default
    case 0:
        active=false;
        recurring=false;
        appointmentDate="";
        appointmentTime="";
        break;
    //1: guests arrive by boat
    case 1:
        active=true;
        recurring=true;
        appointmentDate="Daily";
        appointmentTime="08:10";
        break;
    }
}

Appointment::Appointment(char appcode)
{
    setApp(appcode);
}

bool Appointment::isRecurring()
{
    return recurring;
}
bool Appointment::isActive()
{
    return active;
}
std::string Appointment::getAppDate()
{
    return appointmentDate;
}
std::string Appointment::getAppTime()
{
    return appointmentTime;
}
