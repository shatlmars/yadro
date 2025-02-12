#include "Tables.h"
#include "Persons.h"
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <regex>
class Task
{
public:
    Task(std::string filename);
    bool ParseData(std::string line);
    int getTimeFromLine(std::string line);
    int getIdEventFromLine(std::string line);
    int getNumberTable(std::string line);
    std::string getNameClientFromLine(std::string line);
    std::string idEvents(int id, std::string name, int time, int number_table);
    std::string timeToStr(int time);
    bool checkLine(std::string line);
    bool isValidTimeFormat(const std::string& time_str) {
        std::regex pattern(R"(^([01]?[0-9]|2[0-3]):([0-5][0-9])$)");
        return std::regex_match(time_str, pattern);
    }
    
    ~Task();
private:
    std::vector<std::string> lines;
    int begin_work;
    int end_work;
    int cost_by_hour;
    std::list<std::string> waitList;
    std::map<std::string, Persons> persons;
    std::unordered_map<int, Tables> tables;
    int count_tables;
    bool critical_fail;
    int time_prev;
    std::string errors[5] = { " 13 YouShallNotPass ", " 13 NotOpenYet ", " 13 ClientUnknown "," 13 PlacesBusy ", " 13 ICanWaitNoLonger " };

};

