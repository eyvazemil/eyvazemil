#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

string to_lower(const string & str) {
    string s = str;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

class Owner;
class LandLot {
public:
    string city, address, region, owner_string;
    unsigned ID;
    Owner * owner;
    unsigned long long owner_vector;
    LandLot(const string & c, const string & a, const string & r, unsigned int id) : city(c), address(a), region(r), ID(id) {
        owner = nullptr;
    }
};

class Owner {
public:
    Owner() {
        size = 0;
    }
    string owner;
    unsigned long size;
    vector<LandLot *> land;
};

class CLandRegister;

class CIterator
{
public:
    CIterator(vector<LandLot *>, bool);
    bool AtEnd(void) const;
    void Next(void);
    string City(void) const;
    string Addr(void) const;
    string Region(void) const;
    unsigned ID(void) const;
    string Owner(void) const;
private:
    vector<LandLot *> vec;
    unsigned long start;
    unsigned long end;
};

class CLandRegister
{
public:
    ~CLandRegister();
    unsigned long binary_search_city(const string &, const string &) const;
    unsigned long binary_search_region(const string &, unsigned &) const;
    unsigned long binary_search_owner(string) const;
    bool Add(const string & city, const string & addr, const string & region, unsigned int id);
    bool Del(const string & city, const string & addr);
    bool Del(const string & region, unsigned int id);
    bool GetOwner(const string & city, const string & addr, string & owner) const;
    bool GetOwner(const string & region, unsigned int id, string & owner) const;
    bool NewOwner(const string & city, const string & addr, const string & owner);
    bool NewOwner(const string & region, unsigned int id, const string & owner);
    unsigned Count(const string & owner) const;
    CIterator ListByAddr(void) const;
    CIterator ListByOwner(const string & owner) const;
private:
    vector<LandLot *> database_city;
    vector<LandLot *> database_region;
    vector<Owner *> database_owner;
};

CIterator::CIterator(vector<LandLot *> it, bool flag) {
    vec = it;
    if(flag) {
        start = 0;
        end = 0;
    } else {
        start = 0;
        end = it.size();
    }
}

CLandRegister::~CLandRegister() {
    for(unsigned long i = 0; i < database_city.size(); i++)
        delete database_city[i];
    for(unsigned long i = 0; i < database_region.size(); i++)
        delete database_region[i];
    for(unsigned long i = 0; i < database_owner.size(); i++)
        delete database_owner[i];
}

unsigned long CLandRegister::binary_search_city(const string & city, const string & address) const {
    unsigned long low = 0, high = database_city.size() - 1, mid;
    if(database_city[low]->city > city || (database_city[low]->city == city && database_city[low]->address > address)) return 0;
    if(database_city[high]->city < city || (database_city[high]->city == city && database_city[high]->address < address)) return high + 1;

    while(low <= high) {
        mid = low + (high - low) / 2;
        if(database_city[mid]->city > city || (database_city[mid]->city == city && database_city[mid]->address > address)) {
            if(database_city[mid - 1]->city < city || (database_city[mid - 1]->city == city && database_city[mid - 1]->address < address)) return mid;
            else high = mid - 1;
        } else if(database_city[mid]->city < city || (database_city[mid]->city == city && database_city[mid]->address < address)) {
            if(database_city[mid + 1]->city > city || (database_city[mid + 1]->city == city && database_city[mid + 1]->address > address)) return mid + 1;
            else low = mid + 1;
        } else break;
    }
    return mid;
}

unsigned long CLandRegister::binary_search_region(const string & region, unsigned & id) const {
    unsigned long low = 0, high = database_region.size() - 1, mid;
    if(database_region[low]->region > region || (database_region[low]->region == region && database_region[low]->ID > id)) return 0;
    if(database_region[high]->region < region || (database_region[high]->region == region && database_region[high]->ID < id)) return high + 1;

    while(low <= high) {
        mid = low + (high - low) / 2;
        if(database_region[mid]->region > region || (database_region[mid]->region == region && database_region[mid]->ID > id)) {
            if(database_region[mid - 1]->region < region || (database_region[mid - 1]->region == region && database_region[mid - 1]->ID < id)) return mid;
            else high = mid - 1;
        } else if(database_region[mid]->region < region || (database_region[mid]->region == region && database_region[mid]->ID < id)) {
            if(database_region[mid + 1]->region > region || (database_region[mid + 1]->region == region && database_region[mid + 1]->ID > id)) return mid + 1;
            else low = mid + 1;
        } else break;
    }
    return mid;
}

unsigned long CLandRegister::binary_search_owner(string owner) const {
    unsigned long low = 0, high = database_owner.size() - 1, mid;
    if(to_lower(database_owner[low]->owner) > to_lower(owner)) return 0;
    if(to_lower(database_owner[high]->owner) < to_lower(owner)) return high + 1;

    while(low <= high) {
        mid = low + (high - low) / 2;
        string s1 = database_owner[mid]->owner;
        transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

        if(to_lower(database_owner[mid]->owner) > to_lower(owner)) {
            if(to_lower(database_owner[mid - 1]->owner) < to_lower(owner)) return mid;
            else high = mid - 1;
        } else if(to_lower(database_owner[mid]->owner) < to_lower(owner)) {
            if(to_lower(database_owner[mid + 1]->owner) > to_lower(owner)) return mid + 1;
            else low = mid + 1;
        } else break;
    }
    return mid;
}

bool CLandRegister::Add(const string & city, const string & addr, const string & region, unsigned int id) {
    unsigned long n1 = 0, n2 = 0;
    if(!database_city.empty()) {
        n1 = binary_search_city(city, addr);
        if(n1 != database_city.size() && database_city[n1]->city == city && database_city[n1]->address == addr) return false;
        n2 = binary_search_region(region, id);
        if(n2 != database_region.size() && database_region[n2]->region == region && database_region[n2]->ID == id) return false;
    }
    LandLot * c = new LandLot(city, addr, region, id), * r = new LandLot(city, addr, region, id);
    if(database_owner.empty()) {
        Owner * ow = new Owner;
        ow->owner = "";
        database_owner.push_back(ow);
    }
    database_city.insert(database_city.begin() + n1, c);
    database_region.insert(database_region.begin() + n2, r);
    database_owner[0]->land.push_back(database_city[n1]);
    database_owner[0]->size++;
    database_city[n1]->owner_string = "";
    database_city[n1]->owner = database_owner[0];
    database_city[n1]->owner_vector = (database_owner[0]->land).size() - 1;
    return true;
}

bool CLandRegister::Del(const string & city, const string & addr) {
    unsigned long n1, n2;
    n1 = binary_search_city(city, addr);
    if(n1 == database_city.size() || database_city[n1]->city != city || database_city[n1]->address != addr) return false;
    n2 = binary_search_region(database_city[n1]->region, database_city[n1]->ID);
    database_city[n1]->owner->land[database_city[n1]->owner_vector] = nullptr;
    (database_city[n1]->owner->size)--;
    delete database_city[n1];
    delete database_region[n2];
    database_city.erase(database_city.begin() + n1);
    database_region.erase(database_region.begin() + n2);
    return true;
}

bool CLandRegister::Del(const string & region, unsigned int id) {
    unsigned long n1, n2;
    n1 = binary_search_region(region, id);
    if(n1 == database_region.size() || database_region[n1]->region != region || database_region[n1]->ID != id) return false;
    n2 = binary_search_city(database_region[n1]->city, database_region[n1]->address);
    database_city[n2]->owner->land[database_city[n2]->owner_vector] = nullptr;
    (database_city[n2]->owner->size)--;
    delete database_region[n1];
    delete database_city[n2];
    database_region.erase(database_region.begin() + n1);
    database_city.erase(database_city.begin() + n2);
    return true;
}

bool CLandRegister::GetOwner(const string & city, const string & addr, string & owner) const {
    unsigned long n;
    n = binary_search_city(city, addr);
    if(n == database_city.size() || database_city[n]->city != city || database_city[n]->address != addr) return false;
    owner = database_city[n]->owner_string;
    return true;
}

bool CLandRegister::GetOwner(const string & region, unsigned int id, string & owner) const {
    unsigned long n1, n2;
    n1 = binary_search_region(region, id);
    if(n1 == database_region.size() || database_region[n1]->region != region || database_region[n1]->ID != id) return false;
    n2 = binary_search_city(database_region[n1]->city, database_region[n1]->address);
    owner = database_city[n2]->owner_string;
    return true;
}

bool CLandRegister::NewOwner(const string & city, const string & addr, const string & owner) {
    unsigned long n = 0, n1;
    n1 = binary_search_city(city, addr);
    if(n1 == database_city.size() || database_city[n1]->city != city || database_city[n1]->address != addr) return false;
    if(!database_owner.empty()) {
        n = binary_search_owner(owner);
        if(n != database_owner.size() && to_lower(database_owner[n]->owner) == to_lower(owner) && to_lower(database_city[n1]->owner->owner) == to_lower(owner))
            return false; // owner already owns this land
    }
    database_city[n1]->owner->land[database_city[n1]->owner_vector] = nullptr;
    (database_city[n1]->owner->size)--;
    if(n == database_owner.size() || to_lower(database_owner[n]->owner) != to_lower(owner)) {
        Owner * ow = new Owner;
        ow->owner = owner;
        database_owner.insert(database_owner.begin() + n, ow);
    }
    database_owner[n]->land.push_back(database_city[n1]); // each owner will point to land indicated by city vector
    database_owner[n]->size++;
    database_city[n1]->owner_string = owner;
    database_city[n1]->owner = database_owner[n];
    database_city[n1]->owner_vector = (database_owner[n]->land).size() - 1;
    return true;
}

bool CLandRegister::NewOwner(const string & region, unsigned int id, const string & owner) {
    unsigned long n = 0, n1, n2;
    n1 = binary_search_region(region, id);
    if(n1 == database_region.size() || database_region[n1]->region != region || database_region[n1]->ID != id) return false;
    n2 = binary_search_city(database_region[n1]->city, database_region[n1]->address);
    if(!database_owner.empty()) {
        n = binary_search_owner(owner);
        if(n != database_owner.size() && to_lower(database_owner[n]->owner) == to_lower(owner) && to_lower(database_city[n2]->owner->owner) == to_lower(owner))
            return false; // owner already owns this land
    }
    database_city[n2]->owner->land[database_city[n2]->owner_vector] = nullptr;
    (database_city[n2]->owner->size)--;
    if(n == database_owner.size() || to_lower(database_owner[n]->owner) != to_lower(owner)) {
        Owner * ow = new Owner;
        ow->owner = owner;
        database_owner.insert(database_owner.begin() + n, ow);
    }
    database_owner[n]->land.push_back(database_city[n2]); // each owner will point to land indicated by city vector
    database_owner[n]->size++;
    database_city[n2]->owner_string = owner;
    database_city[n2]->owner = database_owner[n];
    database_city[n2]->owner_vector = (database_owner[n]->land).size() - 1;
    return true;
}

unsigned CLandRegister::Count(const string & owner) const {
    unsigned long n;
    if(database_owner.empty()) return 0;
    n = binary_search_owner(owner);
    if(n == database_owner.size() || to_lower(database_owner[n]->owner) != to_lower(owner)) return 0;
    return (unsigned)database_owner[n]->size;
}

CIterator CLandRegister::ListByAddr() const {
    if(database_city.empty()) {
        vector<LandLot *> vec;
        return CIterator(vec, true);
    }
    return CIterator(database_city, false);
}

CIterator CLandRegister::ListByOwner(const string & owner) const {
    unsigned long n = binary_search_owner(owner);
    if(n == database_owner.size() || to_lower(database_owner[n]->owner) != to_lower(owner)) {
        vector<LandLot *> vec;
        return CIterator(vec, true);
    }
    if(database_owner[n]->size == 0)
        return CIterator(database_owner[n]->land, true);
    return CIterator(database_owner[n]->land, false);
}

bool CIterator::AtEnd() const {
    if(start == end) return true;
    return false;
}

void CIterator::Next() {
    if(start != end) start++;
    while(start != end && vec[start] == nullptr) start++;
}

string CIterator::City() const {
    return vec[start]->city;
}

string CIterator::Addr() const {
    return vec[start]->address;
}

string CIterator::Region() const {
    return vec[start]->region;
}

unsigned CIterator::ID() const {
    return vec[start]->ID;
}

string CIterator::Owner() const {
    if(start == end || vec[start]->owner == nullptr) return "";
    return vec[start]->owner_string;
}

#ifndef __PROGTEST__
static void test0()
{
    CLandRegister x;
    string owner;

    assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );//
    assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );//
    assert ( x . Add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );//
    assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );//
    CIterator i0 = x . ListByAddr ();
    //cout << "hello" << endl;
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Liberec"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Librec"
             && i0 . ID () == 4552
             && i0 . Owner () == "" );
    //cout << "hello1" << endl;
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Plzen"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Plzen mesto"
             && i0 . ID () == 78901
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Vokovice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Technicka"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 9873
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Thakurova"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( i0 . AtEnd () );

    assert ( x . Count ( "" ) == 5 );
    //cout << "HEYYA" << endl;
    CIterator i1 = x . ListByOwner ( "" );
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Thakurova"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 12345
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Vokovice"
             && i1 . ID () == 12345
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Technicka"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 9873
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Plzen"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Plzen mesto"
             && i1 . ID () == 78901
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Liberec"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Librec"
             && i1 . ID () == 4552
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( i1 . AtEnd () );

    assert ( x . Count ( "CVUT" ) == 0 );
    //cout << "psdj" << endl;
    CIterator i2 = x . ListByOwner ( "CVUT" );
    //cout << i2.Owner() << endl;
    assert ( i2 . AtEnd () );
    //cout << "HEYYA11" << endl;
    //x.print_database_city();
    assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
    //cout <<"HEYYA@@" << endl;
    //x.print_database_city();
    assert ( x . NewOwner ( "Dejvice", 9873, "CVUT" ) );
    //cout << "split" << endl;
    //x.print_database_city();
    assert ( x . NewOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
    //cout << "HEYYA33" << endl;
    assert ( x . NewOwner ( "Librec", 4552, "Cvut" ) );
    assert ( x . GetOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Prague", "Evropska", owner ) && owner == "" );
    assert ( x . GetOwner ( "Vokovice", 12345, owner ) && owner == "" );
    assert ( x . GetOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
    assert ( x . GetOwner ( "Librec", 4552, owner ) && owner == "Cvut" );
    //x.print_database_owner();
    //x.Del("Prague", "Evropska");
    //x.print_database_owner();
    //cout << "HEYYA33" << endl;
    CIterator i3 = x . ListByAddr ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Liberec"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Librec"
             && i3 . ID () == 4552
             && i3 . Owner () == "Cvut" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Plzen"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Plzen mesto"
             && i3 . ID () == 78901
             && i3 . Owner () == "Anton Hrabis" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Vokovice"
             && i3 . ID () == 12345
             && i3 . Owner () == "" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Technicka"
             && i3 . Region () == "Dejvice"
             && i3 . ID () == 9873
             && i3 . Owner () == "CVUT" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Thakurova"
             && i3 . Region () == "Dejvice"
             && i3 . ID () == 12345
             && i3 . Owner () == "CVUT" );
    i3 . Next ();
    assert ( i3 . AtEnd () );


    //cout << "size_cvut: " << x.Count("cvut") << endl;
    assert ( x . Count ( "cvut" ) == 3 );
    CIterator i4 = x . ListByOwner ( "cVuT" );
    //x.print_database_city();
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Prague"
             && i4 . Addr () == "Thakurova"
             && i4 . Region () == "Dejvice"
             && i4 . ID () == 12345
             && i4 . Owner () == "CVUT" );
    i4 . Next ();
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Prague"
             && i4 . Addr () == "Technicka"
             && i4 . Region () == "Dejvice"
             && i4 . ID () == 9873
             && i4 . Owner () == "CVUT" );
    i4 . Next ();
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Liberec"
             && i4 . Addr () == "Evropska"
             && i4 . Region () == "Librec"
             && i4 . ID () == 4552
             && i4 . Owner () == "Cvut" );
    i4 . Next ();
    assert ( i4 . AtEnd () );

    assert ( x . NewOwner ( "Plzen mesto", 78901, "CVut" ) );
    assert ( x . Count ( "CVUT" ) == 4 );
    CIterator i5 = x . ListByOwner ( "CVUT" );
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Prague"
             && i5 . Addr () == "Thakurova"
             && i5 . Region () == "Dejvice"
             && i5 . ID () == 12345
             && i5 . Owner () == "CVUT" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Prague"
             && i5 . Addr () == "Technicka"
             && i5 . Region () == "Dejvice"
             && i5 . ID () == 9873
             && i5 . Owner () == "CVUT" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Liberec"
             && i5 . Addr () == "Evropska"
             && i5 . Region () == "Librec"
             && i5 . ID () == 4552
             && i5 . Owner () == "Cvut" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Plzen"
             && i5 . Addr () == "Evropska"
             && i5 . Region () == "Plzen mesto"
             && i5 . ID () == 78901
             && i5 . Owner () == "CVut" );
    i5 . Next ();
    assert ( i5 . AtEnd () );

    assert ( x . Del ( "Liberec", "Evropska" ) );
    assert ( x . Del ( "Plzen mesto", 78901 ) );
    assert ( x . Count ( "cvut" ) == 2 );
    CIterator i6 = x . ListByOwner ( "cVuT" );
    assert ( ! i6 . AtEnd ()
             && i6 . City () == "Prague"
             && i6 . Addr () == "Thakurova"
             && i6 . Region () == "Dejvice"
             && i6 . ID () == 12345
             && i6 . Owner () == "CVUT" );
    i6 . Next ();
    assert ( ! i6 . AtEnd ()
             && i6 . City () == "Prague"
             && i6 . Addr () == "Technicka"
             && i6 . Region () == "Dejvice"
             && i6 . ID () == 9873
             && i6 . Owner () == "CVUT" );
    i6 . Next ();
    assert ( i6 . AtEnd () );

    assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
}

static void test1() {
    CLandRegister x;
    string owner;

    assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( ! x . Add ( "Prague", "Technicka", "Hradcany", 7344 ) );
    assert ( ! x . Add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
    assert ( !x . GetOwner ( "Prague", "THAKUROVA", owner ) );
    assert ( !x . GetOwner ( "Hradcany", 7343, owner ) );
    CIterator i0 = x . ListByAddr ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Vokovice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Technicka"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 9873
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Thakurova"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( i0 . AtEnd () );

    assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( ! x . NewOwner ( "Prague", "technicka", "CVUT" ) );
    assert ( ! x . NewOwner ( "prague", "Technicka", "CVUT" ) );
    assert ( ! x . NewOwner ( "dejvice", 9873, "CVUT" ) );
    assert ( ! x . NewOwner ( "Dejvice", 9973, "CVUT" ) );
    assert ( ! x . NewOwner ( "Dejvice", 12345, "CVUT" ) );
    assert ( x . Count ( "CVUT" ) == 1 );
    CIterator i1 = x . ListByOwner ( "CVUT" );
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Thakurova"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 12345
             && i1 . Owner () == "CVUT" );
    i1 . Next ();
    assert ( i1 . AtEnd () );

    assert ( ! x . Del ( "Brno", "Technicka" ) );
    assert ( ! x . Del ( "Karlin", 9873 ) );
    assert ( x . Del ( "Prague", "Technicka" ) );
    assert ( ! x . Del ( "Prague", "Technicka" ) );
    assert ( ! x . Del ( "Dejvice", 9873 ) );
}

int main() {
    test0();
    test1();
    return 0;
}
#endif /* __PROGTEST__ */