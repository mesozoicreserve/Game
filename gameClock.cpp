#include "gameClock.h"
#include <string>
gameClock::gameClock()
{
    month=1;
    day=1;
    year=2017;
}

gameClock::gameClock(int imonth,int iday,int iyear, int ihour, int iminute)
{
    month=imonth;
    day=iday;
    year=iyear;
    minute=iminute;
    hour=ihour;
}


void gameClock::cycleMinute()
{
    minute++;
    if (minute > 60)
    {
        minute=0;
        cycleHour();
    }
}

void gameClock::cycleHour()
{
    hour++;
    if (hour > 23)
    {
        hour = 0;
        cycleDay();
    }
}
void gameClock::cycleDay()
{
    day++;
    if (day > 31)
    {
        day=1;
        cycleMonth();
    }
}

void gameClock::cycleMonth()
{
    month++;
    if (month > 12)
    {
        month=1;
        cycleYear();
    }
}

void gameClock::cycleYear()
{
    year++;
}

std::string gameClock::getDate()
{
   char dayBuffer[2];
   itoa(day,dayBuffer,10);

   char monthBuffer[2];
   itoa(month,monthBuffer,10);

   char yearBuffer[5];
   itoa(year,yearBuffer,10);

   std::string monthString = std::string(monthBuffer);
   std::string dayString = std::string(dayBuffer);
   std::string yearString = std::string(yearBuffer);


   std::string dateString = monthString + "/" + dayString + "/" + yearString;

   return dateString;
}

std::string gameClock::getTime()
{
   char minuteBuffer[6];
   itoa(minute,minuteBuffer,10);

   char hourBuffer[3];
   itoa(hour,hourBuffer,10);

   std::string minuteString = std::string(minuteBuffer);
   std::string hourString = std::string(hourBuffer);
   std::string sZero = "0";


   //enforce 0's
   if (minute < 10)
   {
      minuteString = sZero + minuteString;
   }
   if (hour < 10)
   {
       hourString = sZero + hourString;
   }

   std::string timeString = hourString + ":" + minuteString;

   return timeString;
}


