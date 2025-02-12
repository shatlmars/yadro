#include "Task.h"

Task::Task(std::string filename) : critical_fail(false), time_prev(0)
{

    std::ifstream in;
    in.open(filename);
    std::string line;
    while (std::getline(in, line))
    {
        lines.push_back(line);
    }
    in.close();
    count_tables = std::stoi(lines[0]);
    for (int i = 0; i < count_tables; i++) { tables[i + 1]; }
    begin_work = (std::stoi(lines[1].substr(0, lines[1].find(":"))) * 60) + std::stoi(lines[1].substr(3, 2));
    end_work = (std::stoi(lines[1].substr(lines[1].find(" ", 2))) * 60) + std::stoi(lines[1].substr(10, 2));
    cost_by_hour = std::stoi(lines[2]);

    std::cout << timeToStr(begin_work) << std::endl;
    for (int i = 3; i < lines.size(); i++)
    {
        if (!ParseData(lines[i]))
            break;
    }

}
bool Task::ParseData(std::string line)
{
    std::cout << line << std::endl;
    std::string name = getNameClientFromLine(line);
    int id_event = getIdEventFromLine(line);
    int number_table = 0;
    int time = getTimeFromLine(line);
    ;
    if (id_event == 2)
    {
        number_table = getNumberTable(line);
        if (number_table > count_tables)
        {
            critical_fail = true;
            return false;
        }
    }
    else
        number_table = count_tables + 10;
    if (!checkLine(line))
    {
        critical_fail = true;
        return false;
    }

    idEvents(id_event, name, time, number_table);
        time_prev = time;
    return true;
}
int Task::getTimeFromLine(std::string line)
{
    int time = 0;
    time = (std::stoi(line.substr(0, 2)) * 60) + std::stoi(line.substr(3, 2));
    return time;
}

int Task::getIdEventFromLine(std::string line)
{
    size_t poz_id_event = line.find(" ");
    return std::stoi(line.substr(poz_id_event, 3));;
}

std::string Task::getNameClientFromLine(std::string line)
{
    std::string result = "";
    size_t poz_name_client = 0, poz_name_client_end = 0;

    for (size_t i = 0, count = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            count++;
            if (count == 2)
            {
                poz_name_client = i + 1;
                for (size_t j = poz_name_client; j < line.length(); j++)
                {
                    if (line[j] == ' ')
                    {
                        poz_name_client_end = j;
                        break;
                    }
                }
                break;
            }
        }
    }
    result = line.substr(poz_name_client, poz_name_client_end - poz_name_client);
    return result;
}

std::string Task::idEvents(int id, std::string name, int time, int number_table)
{

    std::string result;
    bool check_all_tables_busy = true;
    int debt = 0;
    if (time < begin_work || time > end_work)
    {
        result += std::to_string(time) + errors[1];
        std::cout << timeToStr(time) << errors[1] << std::endl;
        return "";
    }

    switch (id)
    {
    case 1:
        if (persons[name].get_status_in_club())
        {
            std::cout << timeToStr(time) << errors[0] << std::endl;
        }
        else
        {
            persons[name].set_in_club(true);
            persons[name].set_name(name);
        }
        break;
    case 2:
        if (!persons[name].get_status_in_club())
        {
            std::cout << timeToStr(time) << errors[2] << std::endl;
            persons.erase(name);
        }
        else
        {
            if (tables[number_table].getoccupied()) std::cout << timeToStr(time) << errors[3] << std::endl;
            else
            {
                persons[name].set_time_end(time);
                debt = (persons[name].get_allTime()/60) * cost_by_hour;
                if (persons[name].get_allTime() % 60 > 0)
                {
                    debt = ((persons[name].get_allTime()/60) + 1) * cost_by_hour;
                }
                tables[persons[name].get_number_table()].addDebt(debt);
                tables[persons[name].get_number_table()].addTime(persons[name].get_allTime());
                tables[number_table].setOccupied(true);
                persons[name].set_number_table(number_table);
                persons[name].set_start_gaming(time);

            }
        }
        break;
    case 3:
        if (waitList.size() >= count_tables)
        {
            idEvents(4, name, time, number_table);
            persons[name].set_angry(true);
            persons.erase(name);
        }
        else
        {
            for (const auto i : tables)
            {
                if (!tables[i.first].getoccupied())
                {
                    std::cout << timeToStr(time) << errors[4] << std::endl;
                    check_all_tables_busy = false;
                    break;
                }
            }

            if (check_all_tables_busy)
            {
                waitList.push_back(name);
            }
        }
        break;
    case 4:
        if (persons[name].get_status_in_club())
        {

            persons[name].set_time_end(time);
            debt = (persons[name].get_allTime()/60) * cost_by_hour;
            if (persons[name].get_allTime() % 60 > 0)
                debt = ((persons[name].get_allTime() / 60) + 1) * cost_by_hour;
            
            
          
            tables[persons[name].get_number_table()].addDebt(debt);
            tables[persons[name].get_number_table()].addTime(persons[name].get_allTime());
            if (persons[name].get_status_in_club())
            {
                if (waitList.size() != 0)
                 {
                    persons[waitList.front()].set_number_table(persons[name].get_number_table());
                    persons[waitList.front()].set_start_gaming(time);
                    std::cout << timeToStr(time) << " 12 ";
                    std::cout << waitList.front() << " ";
                    std::cout << persons[waitList.front()].get_number_table() << std::endl;
                    waitList.remove(waitList.front());
                }
                persons.erase(name);
            }
        }
        else
        {
            std::cout << timeToStr(time) << " ";
            persons.erase(name);
        }
        break;
    default:
        break;
    }
    return "\n";
}



Task::~Task()
{
    if(!critical_fail)
    {
        int itog_debt = 0;
        for (const auto i : persons)
        {
            persons[i.first].set_time_end(end_work);
            itog_debt = (persons[i.first].get_allTime() / 60) * cost_by_hour;
            if (persons[i.first].get_allTime() % 60 > 0)
                itog_debt = ((persons[i.first].get_allTime() / 60) + 1) * cost_by_hour;

            tables[persons[i.first].get_number_table()].addDebt(itog_debt);
            tables[persons[i.first].get_number_table()].addTime(persons[i.first].get_allTime());
            persons[i.first].set_angry(true);

        }

        persons.clear();
        for (int i = 0; i < count_tables; i++)
        {
            std::cout << i + 1 << " " << tables[i + 1].getDebt() << "\t" << timeToStr(tables[i + 1].getTime()) << std::endl;
        }
    }
    else
    {
        for (const auto pers : persons)
        {
            persons[pers.first].set_fail(true);
        }
    }
}

int Task::getNumberTable(std::string line)
{
    size_t poz = 0;
    for (int i = 0, counter = 0; i < line.length(); i++)
    {
        if (line[i] == ' ')
        {
            counter++;
            if (counter == 3)
            {
                poz = i;
                break;
            }
        }
    }

    int result = std::stoi(line.substr(poz, line.length() - poz));

    return result;
}


std::string Task::timeToStr(int time)
{
    std::string hour;
    std::string mins;

    if ((time / 60) < 10)
    {
        hour = "0" + std::to_string(time / 60);
    }
    else
    {
        hour = std::to_string(time / 60);
    }
    if ((time % 60) < 10)
    {
        mins = "0" + std::to_string(time % 60);
    }
    else
    {
        mins = std::to_string(time % 60);
    }


    std::string result = hour + ":" + mins;
    return result;
}



bool Task::checkLine(std::string line)
{
    std::string name = getNameClientFromLine(line);
    std::string time = timeToStr(getTimeFromLine(line));
    int id = getIdEventFromLine(line);




    int time_int = getTimeFromLine(line);
    std::string time_raw_str = line.substr(0, line.find(" "));
    if (time_raw_str.length() > 5) return false;
    int number_table = 0;
    if (id == 2)
    {
        number_table = getNumberTable(line);
    }
    if (!isValidTimeFormat(time))
    {
        return false;
    }
    if (number_table > count_tables)
        return false;
    if (time_prev > time_int)
    {
        return false;
    }

    return true;
}
