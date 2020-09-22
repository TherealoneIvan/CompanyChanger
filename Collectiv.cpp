//
// Created by MacOS on 19.09.2020.
//

#include <fstream>
#include "Collectiv.h"
ostream& operator<<(ostream& ostream, const Worker& worker){
    ostream << "|" << '\n';
    ostream << "|------------- " << worker.name << " " << worker.surname << " " << worker.middlename << " "
    << worker.function << ' ' << worker.salary << '\n';
//    ostream << "|" << '\n';
//    ostream << "---" << worker.surname <<'\n';
//    ostream << "|" << '\n';
//    ostream << "---" << worker.middlename <<'\n';
//    ostream << "|" << '\n';
//    ostream << "---" << worker.function <<'\n';
//    ostream << "|" << '\n';
//    ostream << "---" << worker.salary <<'\n';
//    ostream << "|" << '\n';
//    ostream << "---" << '\n';
    return ostream;
}
istream& operator>>(istream& istream, Worker& worker){
    istream >> worker.name >> worker.surname >> worker.middlename
    >> worker.function >> worker.salary;
    istream.ignore(1);
    getline(istream, worker.department, '\n');
    return istream;
}
bool operator==(const Worker& lhs,const Worker& rhs){
    if (lhs.department == rhs.department && lhs.salary == rhs.salary && lhs.function == rhs.function
        && lhs.name == rhs.name && lhs.surname == rhs.surname && lhs.middlename == rhs.middlename){
        return true;
    }
    return false;
}
Worker::Worker(const string &name_, const string &surname_, const string &middlename_, const int &salary_,
               const string &function_)
        :name(name_)
        ,surname(surname_)
        ,middlename(middlename_)
        ,salary(salary_)
        ,function(function_)
{
}

void CompanyHandler::Load(const char* path) {
    date_base.clear();
    date_base_buffer.clear();
    que_workers.clear();
    que_.clear();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path);
    pugi::xml_node panel = doc.first_child();
    for (auto  i = panel.begin(); i != panel.end(); i++){
//        cout << i->first_attribute().value() << '\n';
        string department_name = i->first_attribute().value();
        for(auto j = i->first_child().begin(); j != i->first_child().end(); j++ ){
            Worker new_worker;
            for ( auto k = j->first_child() ; k ; k = k.next_sibling()){
                string type_of_man = k.name() ;
                if (type_of_man == "name"){
                    new_worker.name = k.child_value();
                }
                if (type_of_man == "surname"){
                    new_worker.surname = k.child_value();
                }
                if (type_of_man == "middleName"){
                    new_worker.middlename = k.child_value();
                }
                if (type_of_man == "function"){
                    new_worker.function = k.child_value();
                }
                if (type_of_man == "salary"){
                    new_worker.salary = atoi(k.child_value());
                }

            }
                new_worker.department = department_name;
                date_base[department_name].push_back(new_worker);
        }
    }
    date_base_buffer = date_base;
}
void CompanyHandler::Print() {
    for (auto depataments : date_base){
        cout << depataments.first  << '\n';
//        cout << "|" << '\n';
        for(auto workers : depataments.second){
            cout << workers;
        }
        cout << endl;
    }
}

void CompanyHandler::Save() {
    date_base = date_base_buffer;
}

void CompanyHandler::Cancel() {
    que_.clear();
}

void CompanyHandler::Back() {
    if (!que_.empty()) {
        string command = que_.front();
        que_.pop_front();
        if (command == "Delete"){
            Worker old_worker_to_add = que_workers.front();
            que_workers.pop_front();
            que_workers.pop_front();
            Add(old_worker_to_add);
        }else if (command == "Add"){
            Worker old_worker_to_add = que_workers.front();
            Delete(old_worker_to_add);
            que_workers.pop_front();
            que_workers.pop_front();
        }
        que_.pop_front();
    }else{
        return;
    }
}

void CompanyHandler::Add(const Worker &new_worker) {
    date_base_buffer[new_worker.department].push_back(new_worker);
    que_workers.push_front(new_worker);
    que_.push_front("Add");
}

void CompanyHandler::Delete(const Worker worker) {
    date_base_buffer.at(worker.department).remove(worker);
    if (date_base_buffer.at(worker.department).empty()){
        date_base_buffer.erase(worker.department);
    }
    que_workers.push_front(worker);
    que_.push_front("Delete");
}

void CompanyHandler::SaveInXML(const string &path) {
    ofstream out_xml(path);
    if (!out_xml){
       cout << "file does not exist!" << endl;
    }
    out_xml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << '\n' << "<departments>" << '\n';
    for (auto depataments : date_base){
        out_xml <<"   <department name=\"" << depataments.first <<"\">" << '\n';
        out_xml << "      <employments>";
        for(auto workers : depataments.second){
            out_xml << "         <employment>" << '\n';
            out_xml << "            <surname>" << workers.surname << "</surname>" << '\n';
            out_xml << "            <name>" << workers.name << "</name>" << '\n';
            out_xml << "            <middleName>" << workers.middlename << "</middleName>" << '\n';
            out_xml << "            <function>" << workers.function << "</function>" << '\n';
            out_xml << "            <salary>" << workers.salary << "</salary>" << '\n';
            out_xml << "         </employment>" << '\n';
        }
        out_xml << "      </employments>" << '\n';
        out_xml << "   </department>" << '\n';
    }
    out_xml << "</departments>" << '\n';
}
