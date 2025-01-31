#include <iostream>
#include "Task.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "critical fail " << std::endl;
        return 1;
    }
    std::string filename(argv[1]);
    Task task_obj(filename);


    return 0;
}




