#include <iostream>
#include <string>
#include <time.h>

#include <chrono>
#include <thread>

#include "logparsing.h"

using namespace std;

int main()
{
    string f("data.txt");
    string f2("cloud.txt");
	std::chrono::seconds dura(5);
        std::this_thread::sleep_for( dura );
    while(true){
        LogParsing l(f);
        l.write(f2);
        cout << "Updated!!" << endl;
        std::chrono::seconds dura(2);
        std::this_thread::sleep_for( dura );
    }

}
