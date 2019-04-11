#ifndef LOGPARSING_H
#define _GLIBCXX_USE_C99 1
#define LOGPARSING_H

#include <vector>
#include <string>

using namespace std;

class LogParsing
{
public:
    LogParsing(string fname);
    void write(string fname);
private:
    vector<size_t> readSensorData(vector<size_t> buff);
    string Fname;
    double pressure;
    double humidity;
    double temprature;
    double ambientLight;
    double proximity;
};

#endif // LOGPARSING_H
