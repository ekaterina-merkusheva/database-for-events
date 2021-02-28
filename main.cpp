#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <iomanip>
#include <iterator>
#include <map>
#include <sstream>
using namespace std;

class Date{
public:
    Date(){}
    Date(int new_year,int new_month,int new_day){
        year=new_year;
        if (new_month<1||new_month>12){
            throw invalid_argument("Month value is invalid: " +to_string(new_month));
        }
        month=new_month;
        if (new_day<1||new_day>31){
            throw invalid_argument("Day value is invalid: "+to_string(new_day));
        }
        day=new_day;
    }
    int GetYear() const{
        return year;
    };
    int GetMonth() const{
        return month;
    };
    int GetDay() const{
        return day;
    };
private:
    int day;
    int month;
    int year;
};

bool operator<(const Date& lhs, const Date& rhs){
    vector <int> v1{lhs.GetYear(),lhs.GetMonth(),lhs.GetDay()};
    vector <int> v2{rhs.GetYear(),rhs.GetMonth(),rhs.GetDay()};
        return v1<v2;
}
ostream& operator<<(ostream& stream,const Date& date){
    stream<<setw(4)<<setfill('0')<<date.GetYear()
    <<"-"<<setw(2)<<setfill('0')<<date.GetMonth()
    <<"-"<<setw(2)<<setfill('0')<<date.GetDay();
return stream;
}

class DateBase {
public:
    void AddEvent(const Date& date, const string& event) {
        DataBase[date].insert(event);

    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (DataBase.count(date)>0&&DataBase[date].count(event)>0) {
            DataBase[date].erase(event);
            return true;
        }
            return false;
    }

    int DeleteDate(const Date &date) {
        int k=DataBase[date].size();
        DataBase.erase(date);
        return k;
    }

    set <string> Find(const Date &date) {
        if (DataBase.count(date)>0){
            return DataBase.at(date);
    } else {
            return {};
        }
    }

    void Print() const {
        for (const auto& i:DataBase){
            for (const auto& item: i.second){
            cout<<i.first<<" "<<item<<endl;
            }
        }
    }
private:
    map <Date,set <string>> DataBase;
};

Date ParseDate(const string& s) {
    stringstream stream(s);
    int y;
    stream>>y;
    if (stream.peek()!='-'){
        throw logic_error("Wrong date format: "+s);
    }
    stream.ignore(1);
    if (stream.eof()){
        throw logic_error("Wrong date format: "+s);
    }
    int m;
    stream >> m;
    if (stream.peek()!='-'){
        throw logic_error("Wrong date format: "+s);
    }
    stream.ignore(1);
    int d;
    int c = stream.peek();
    if (c==EOF) {
        string er = "Wrong date format: " + s;
        throw runtime_error(er);
    }
    stream>>d;
    if (!stream.eof()){
        throw logic_error("Wrong date format: "+s);
    }
    Date date{y,m,d};

    return date;

}
int main() {
    DateBase db;
    string str;
    try{
    while (getline(cin, str)) {
            stringstream ss(str);
            string command;
            ss >> command;
            if (command == "Add") {
                string date_str;
                ss >> date_str;
                const Date date = ParseDate(date_str);
                string event;
                ss >> event;
                db.AddEvent(date, event);
            } else if (command == "Del") {
                string date_str;
                ss >> date_str;
                const Date date = ParseDate(date_str);
                string event;
                if (!ss.eof()) {
                    ss >> event;
                }
                if (event.empty()) {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (command == "Find") {
                string date_str;
                ss >> date_str;
                const Date date = ParseDate(date_str);
                for (const string &event: db.Find(date)) {
                    cout << event << endl;
                }
            } else if (command == "Print") {
                db.Print();
            } else if (command != "") {
                throw logic_error("Unknown command: " + command);
            }
        }
    }catch (const exception &i) {
        cout << i.what();
    }

    return 0;
}

