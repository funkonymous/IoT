#include "logparsing.h"
#include <fstream>
#include <iostream>

//humidity temprature pressure proximity
using namespace std;

vector<size_t> readData(string &l);



void LogParsing::write(string fname){
    float pre, hum, tem, amb, pro;
    float pop;
    pre = hum = tem = amb = pro = 0;
    pop = 0;
    string line;
    ifstream infile(fname);
    char *bin;
    if(infile.is_open()){
	try{
        std::cout << "Reading file : " << fname << std::endl;
        std::string::size_type sz;
        (getline(infile,line));
        line = string(line.begin()+7,line.end());
        //pre = std::stoi(line,0,10);
	sscanf(line.c_str(),"%s\t%f",bin,&pre)
        (getline(infile,line));
        line = string(line.begin()+7,line.end());
        //hum = std::stoi(line,0,10);
        (getline(infile,line));
        line = string(line.begin()+7,line.end());
        //tem = std::stoi(line,0,10);
        (getline(infile,line));
        line = string(line.begin()+7,line.end());
        //amb = std::stoi(line,0,10);
        cout << 1 << endl;
        (getline(infile,line));
        line = string(line.begin()+7,line.end());
        //pro = std::stoi(line,0,10);
        //cout << 1 << endl;
	}catch(const std::exception& ex){;}
    }
    string popf("pop.txt");
    ifstream infile1(popf);
    (getline(infile1,line));
    pop = std::stoi(line,0,10);
    if(pressure<0.5) pressure = pre;
    if(humidity<0.5) humidity = hum;
    if(temprature<0.5) temprature = tem;
    if(ambientLight<0.5) ambientLight = amb;
    if(proximity>10.0){
        if(rand()%2) if(pop>0) pop--;
        else pop++;
    }
    if(proximity<1.0) proximity += 1.1;
    ofstream myfile;
    myfile.open ("cloud.txt");
    ofstream myfile2;
    myfile2.open ("pop.txt");
    myfile << "PRE\t" << (int) pressure << endl;
    myfile << "HUM\t" << (int) humidity << endl;
    myfile << "TEM\t" << (int) temprature << endl;
    myfile << "AMB\t" << (int) ambientLight << endl;
    myfile << "PRO\t" << (int) proximity ;
    myfile2 << pop ;
    myfile.close();

}

LogParsing::LogParsing(string fname)
{
    Fname = fname;
    string line;
    vector<size_t> dataBuffer;
    ifstream infile(fname);
    if(infile.is_open()){
        std::cout << "Reading file : " << fname << std::endl;
        while(getline(infile,line)){
	    try{
            dataBuffer = readData(line);

            dataBuffer.erase(dataBuffer.begin());
            dataBuffer.erase(dataBuffer.begin());

            cout << endl;
            while(dataBuffer.size()){
                dataBuffer = readSensorData(dataBuffer);
            }
            cout << temprature << " " << humidity << " " << pressure << " " << ambientLight
                 << " " << proximity << endl;
            }catch(const std::exception& ex){;}
        }
    }
    else cout << "Could not open file " << fname << "!!" << endl;
    /*
    for(size_t j = 0; j < dataBuffer.size(); ++j){
        cout << dataBuffer[j] << " ";
    }
    cout << endl; //*/
    /*
    dataBuffer.erase(dataBuffer.begin());
    dataBuffer.erase(dataBuffer.begin()); //*/
    /*
    for(size_t j = 0; j < dataBuffer.size(); ++j){
        cout << dataBuffer[j] << " ";
    }
    cout << endl; //*/
    /*
    while(dataBuffer.size()){
        dataBuffer = readSensorData(dataBuffer);
    }
    cout << endl; //*/
    cout << temprature << " " << humidity << " " << pressure << " " << ambientLight
         << " " << proximity << endl;
}

vector<size_t> readData(string &l){
    vector<size_t> dataBuffer;
    cout << l.size() << endl;
    size_t BytesCounter = (int) (l.size()/3) + 1;
    cout << "Bytes Found : " << BytesCounter << endl;
    string Byte;
    int data1;
    for(size_t i = 0; i < BytesCounter - 1; ++i){
        Byte = string(l.begin(),l.begin()+2);
        l = string(l.begin()+3,l.end());
        data1 = std::stoi(Byte, 0, 16);
        //data1 = sscanf(Byte.c_str(),"%h");
        /*
        cout << Byte << " | " << l << " | " << data1 << endl;*/
        dataBuffer.push_back(data1);
    }
    Byte = string(l.begin(),l.begin()+2);
    data1 = std::stoi(Byte, 0, 16);
    dataBuffer.push_back(data1);
    return dataBuffer;
}

vector<size_t> LogParsing::readSensorData(vector<size_t> buff){
    int Case = (int) buff[0];
    cout << "Head : " << Case << " Buffer size : " << buff.size() << endl;
    double val = 0.0;
    switch(Case){
    case 1 :
        if(buff.size()<9){
            buff.clear();
            break;
        }
        for(size_t i = 0; i < 9; ++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 2 :
        if(buff.size()<9){
            buff.clear();
            break;
        }
        for(size_t i = 0; i < 9; ++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 3 :
        if(buff.size()<9){
            buff.clear();
            break;
        }
        for(size_t i = 0; i < 9; ++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 4 : // Pressure
        if(buff.size()<7){
            buff.clear();
            break;
        }
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        val = ((double) (buff[0] + 256*buff[1] + 256*256*buff[2] + 256*256*256*buff[3]))/100.0;
        pressure = val;
        for(size_t i = 0; i<4;++i) buff.erase(buff.begin());
        break;
    case 5 : // Humidity
        if(buff.size()<7){
            buff.clear();
            break;
        }
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        val = ((double) (buff[0] + 256*buff[1] + 256*256*buff[2] + 256*256*256*buff[3]))/100.0;
        humidity = val;
        for(size_t i = 0; i<4;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 6 : // Temprature
        if(buff.size()<7){
            buff.clear();
            break;
        }
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        buff.erase(buff.begin());
        val = ((double) (buff[0] + 256*buff[1] + 256*256*buff[2] + 256*256*256*buff[3]))/100.0;
        temprature = val;
        for(size_t i = 0; i<4;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 7 :
        if(buff.size()<11){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<11;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 8 :
        buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 9 :
        if(buff.size()<7){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<3;++i) buff.erase(buff.begin());
        val = ((double) (buff[0] + 256*buff[1] + 256*256*buff[2] + 256*256*256*buff[3]))/100.0;
        for(size_t i = 0;i<4;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        ambientLight = val;
        break;
    case 10 :
        if(buff.size()<7){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<3;++i) buff.erase(buff.begin());
        val = ((double) (buff[0] + 256*buff[1] + 256*256*buff[2] + 256*256*256*buff[3]))/100.0;
        for(size_t i = 0;i<4;++i) buff.erase(buff.begin());
        proximity = val;
        cout << "case : " << Case << endl;
        break;
    case 11 :
        if(buff.size()<7){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<7;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 12 :
        if(buff.size()<2){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<2;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 13 :
        if(buff.size()<7){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<7;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 14 :
        if(buff.size()<9){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<9;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 15 :
        if(buff.size()<9){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<9;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    case 16 :
        if(buff.size()<11){
            buff.clear();
            break;
        }
        for(size_t i = 0;i<11;++i) buff.erase(buff.begin());
        cout << "case : " << Case << endl;
        break;
    default :
        buff.clear();
        cout << "case excep: " << Case << endl;
        break;
    }
    return buff;
}
