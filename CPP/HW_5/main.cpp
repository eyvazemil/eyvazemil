#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;

class CTimeStamp {
public:
    CTimeStamp(int y, int m, int d, int h, int min, double s) : year(y), month(m), day(d), hour(h), minute(min), sec(s) {}
    int Compare(const CTimeStamp & x) const {
        if(this->year > x.year) return 1;
        else if(this->year == x.year) {
            if(this->month > x.month) return 1;
            else if(this->month == x.month) {
                if(this->day > x.day) return 1;
                else if(this->day == x.day) {
                    if(this->hour > x.hour) return 1;
                    else if(this->hour == x.hour) {
                        if(this->minute > x.minute) return 1;
                        else if(this->minute == x.minute) {
                            if(this->sec > x.sec) return 1;
                            else if(this->sec == x.sec) return 0;
                            else return -1;
                        } else return -1;
                    } else return -1;
                } else return -1;
            } else return -1;
        } else return -1;
    }
    friend ostream & operator << (ostream & os, const CTimeStamp & x) {
        os << x.year << "-" << x.month << "-" << x.day << " " << x.hour << ":" << x.minute << ":" << x.sec;
        return os;
    }
private:
    int year, month, day, hour, minute;
    double sec;
};

class CMail {
public:
    CMail(const CTimeStamp & timeStamp, const string & from, const string & to, const string & subject) : time(timeStamp) {
        this->from = from;
        this->subject = subject;
        this->to = to;
    }
    int CompareByTime(const CTimeStamp & x) const;
    int CompareByTime(const CMail & x) const;
    const string & From() const {
        return from;
    }
    const string & To() const {
        return to;
    }
    const string & Subject() const {
        return subject;
    }
    const CTimeStamp & TimeStamp() const {
        return time;
    }
    friend ostream & operator << (ostream & os, const CMail & x) {
        os << x.time << " " << x.from << " -> " << x.to << ", subject: " << x.subject;
        return os;
    }
private:
    CTimeStamp time;
    string from, subject, to;
};
// your code will be compiled in a separate namespace
namespace MysteriousNamespace {
#endif /* __PROGTEST__ */
//----------------------------------------------------------------------------------------

    struct MyCompare {
        bool operator()(const CTimeStamp & lhs, const CTimeStamp & rhs) const {
            if(lhs.Compare(rhs) >= 0) return true;
            return false;
        }
    };

    class CMailLog {
    public:
        CMailLog();
        int ParseLog(istream & in);
        list<CMail> ListMail(const CTimeStamp & from, const CTimeStamp & to) const;
        set<string> ActiveUsers(const CTimeStamp & from, const CTimeStamp & to) const;
    private:
        vector<string> str;
        multimap<string, CMail> map_by_id;
        multimap<CTimeStamp, CMail, MyCompare> map_by_date;
    };

    CMailLog::CMailLog() {
        str.push_back("Jan");
        str.push_back("Feb");
        str.push_back("Mar");
        str.push_back("Apr");
        str.push_back("May");
        str.push_back("Jun");
        str.push_back("Jul");
        str.push_back("Aug");
        str.push_back("Sep");
        str.push_back("Oct");
        str.push_back("Nov");
        str.push_back("Dec");
    }

    int CMailLog::ParseLog(istream & in) {
        map<string, CMail> mp_from;
        map<string, CMail> mp_subject;
        multimap<string, CMail> mp_to;
        string s;
        //in >> s;
        while(!in.eof()) {
            string string_month, string_day, string_year, string_time, string_id, string_from(""), string_subject(""), string_to(""), string_shit("");
            int month, day, year, hour, minute;
            double sec;
            bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
            char c;
            int i;
            in >> s;
            if(in.eof()) break;
            string_month = s;
            for(i = 0; i < (int)str.size(); i++)
                if(string_month == str[i]) break;
            month = i + 1;
            in >> day;
            in >> year;
            in >> s;
            string_time = s;
            istringstream iss(s);
            iss >> hour;
            iss.clear();
            iss >> c;
            iss >> minute;
            iss.clear();
            iss >> c;
            iss >> sec;
            in >> s;
            in >> s;
            string_id = s.substr(0, s.size() - 1);
            in >> s;
            if(in.eof()) break;
            auto ti = find(str.begin(), str.end(), s);
            if(ti != str.end()) continue;
            if(s.size() >= 5 && s.substr(0, 5) == "from=") {
                string_from = s.substr(5, s.size());
                flag1 = true;
            } else if(s.size() >= 8 && s.substr(0, 8) == "subject=") {
                string_subject = s.substr(8, s.size());
                flag2 = true;
            } else if(s.size() >= 3 && s.substr(0, 3) == "to=") {
                string_to = s.substr(3, s.size());
                flag3 = true;
            } else {
                string_shit = s;
                flag4 = true;
            }
            string tmp;
            while(!in.eof()) {
                string t1;
                c = (char)in.get();
                if(c == '\n') break;
                if(flag1) string_from += c;
                if(flag2) string_subject += c;
                if(flag3) string_to += c;
                if(flag4) string_shit += c;
            }
            if(flag1) {
                CTimeStamp t1(year, month, day, hour, minute, sec);
                CMail t2(t1, string_from, string_to, string_subject);
                mp_from.insert(std::pair<string, CMail>(string_id, t2));
            }
            if(flag2) {
                CTimeStamp t1(year, month, day, hour, minute, sec);
                CMail t2(t1, string_from, string_to, string_subject);
                mp_subject.insert(std::pair<string, CMail>(string_id, t2));
            }
            if(flag3) {
                CTimeStamp t1(year, month, day, hour, minute, sec);
                CMail t2(t1, string_from, string_to, string_subject);
                mp_to.insert(std::pair<string, CMail>(string_id, t2));
            }
        }
        for(auto it = mp_to.begin(); it != mp_to.end(); it++) {
            auto it1 = mp_from.find(it->first);
            if(it1 != mp_from.end()) {
                auto it2 = mp_subject.find(it->first);
                if(it2 != mp_subject.end()) {
                    CMail v((it->second).TimeStamp(), (it1->second).From(), (it->second).To(), (it2->second).Subject());
                    map_by_id.insert(std::pair<string, CMail>(it->first, v));
                    map_by_date.insert(std::pair<CTimeStamp, CMail>((it->second).TimeStamp(), v));
                } else {
                    CMail v((it->second).TimeStamp(), (it1->second).From(), (it->second).To(), "");
                    map_by_id.insert(std::pair<string, CMail>(it->first, v));
                    map_by_date.insert(std::pair<CTimeStamp, CMail>((it->second).TimeStamp(), v));
                }
            }
        }
        return (int)map_by_id.size();
    }

    list<CMail> CMailLog::ListMail(const CTimeStamp & from, const CTimeStamp & to) const {
        list<CMail> my_list;
        for(auto it = map_by_date.end(); it != map_by_date.begin(); it--) {
            if(it == map_by_date.end()) continue;
            if((it->first).Compare(from) >= 0 && (it->first).Compare(to) <= 0)
                    my_list.push_back(it->second);
        }
        auto it = map_by_date.begin();
        if((it->first).Compare(from) >= 0 && (it->first).Compare(to) <= 0)
            my_list.push_back(it->second);
        return my_list;
    }

    set<string> CMailLog::ActiveUsers(const CTimeStamp & from, const CTimeStamp & to) const {
        set<string> my_set;
        for(auto it = map_by_date.begin(); it != map_by_date.end(); it++) {
            if((it->first).Compare(from) >= 0 && (it->first).Compare(to) <= 0) {
                my_set.insert((it->second).From());
                my_set.insert((it->second).To());
            }
        }
        return my_set;
    }

//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string printMail(const list<CMail> & all) {
    ostringstream oss;
    for(const auto & mail : all)
        oss << mail << endl;
    return oss . str ();
}
string printUsers(const set<string> & all) {
    ostringstream oss;
    bool first = true;
    for(const auto & name : all) {
        if(!first)
            oss << ", ";
        else
            first = false;
        oss << name;
    }
    return oss . str();
}
int main() {
    MysteriousNamespace::CMailLog m;
    list<CMail> mailList;
    set<string> users;
    istringstream iss;

    iss.clear();
    iss.str(
            "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
            "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
            "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=          N e w progtest homework!       \n"
            "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
            "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
            "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
            "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
            "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
            "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
            "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
            "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n" );

    assert ( m . ParseLog ( iss ) == 8 );
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );

    cout << "size: " << mailList.size() << endl;
    for(auto it = mailList.begin(); it != mailList.end(); it++)
        cout << *it << endl;
    cout << endl;

    /*assert ( printMail ( mailList ) ==
             "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
             "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
             "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
             "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
             "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
             "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
             "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
             "2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n" );*/
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 14, 58, 32 ) );

    cout << "size: " << mailList.size() << endl;
    for(auto it = mailList.begin(); it != mailList.end(); it++)
        cout << *it << endl;
    cout << endl;

    /*assert ( printMail ( mailList ) ==
             "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
             "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
             "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n" );*/
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 30, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 30, 23, 59, 59 ) );

    cout << "size: " << mailList.size() << endl;
    for(auto it = mailList.begin(); it != mailList.end(); it++)
        cout << *it << endl;
    cout << endl;

    //assert ( printMail ( mailList ) == "" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );

    cout << "size: " << users.size() << endl;
    for(auto it = users.begin(); it != users.end(); it++)
        cout << *it << endl;
    cout << endl;

    //assert ( printUsers ( users ) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 13, 59, 59 ) );

    cout << "size: " << users.size() << endl;
    for(auto it = users.begin(); it != users.end(); it++)
        cout << *it << endl;
    cout << endl;

    /*assert ( printUsers ( users ) == "person3@fit.cvut.cz, user76@fit.cvut.cz" );
    return 0;*/
}
#endif /* __PROGTEST__ */