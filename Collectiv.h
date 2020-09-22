#pragma once
#include <unordered_map>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include "pugixml.hpp"
#include <deque>
using namespace std;

struct Worker{
    Worker(const string& name_ , const string& surname_ , const string& middlename_,
           const int& salary_ , const string& function_);
    Worker(stringstream & istream_){
        istream_ >> name >> surname >> middlename >> function >> salary;
    }
    Worker() = default;
    string name =  "" , surname = "" , middlename = "" , function = "" , department = "";
    int salary = 0;
};
ostream& operator<<(ostream& ostream, const Worker& worker);
istream& operator>>(istream& ostream, Worker& worker);
bool operator==(const Worker& lhs,const Worker& rhs);
class CompanyHandler{
public:
    CompanyHandler() = default;
    void Print();
    void Add(const Worker& new_worker);
    void Delete(const Worker worker);
    void Save();
    void SaveInXML(const string& path);
    void Back();
    void Load(const char* path);
    void Cancel();
private:
    unordered_map<string , list<Worker>> date_base;
    unordered_map<string , list<Worker>> date_base_buffer;
    deque<string> que_;
    deque<Worker> que_workers;
};