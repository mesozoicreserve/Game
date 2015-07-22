#include <String>

class gameClock
{
  private:
    int month;
    int day;
    int year;

    int hour;
    int minute;

  public:
    gameClock();
    gameClock(int iMonth, int iDay, int iYear, int iHour, int iMinute);
    void cycleMonth();
    void cycleDay();
    void cycleYear();
    void cycleMinute();
    void cycleHour();

    std::string getDate();
    std::string getTime();

};

