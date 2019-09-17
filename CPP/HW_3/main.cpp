#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException {
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
//#define EXTENDED_SYNTAX

class CRangeList;
class CRangeListIterator;

class CRange {
public:
    // constructor
    CRange(long long l, long long h) : lo(l), hi(h) {
        if(lo > hi) {
            throw InvalidRangeException();
        }
    }
    friend CRangeList operator+(const CRange &, const CRange &);
    friend CRangeList operator-(const CRange &, const CRange &);
    friend ostream & operator<<(ostream & output, const CRange & rhs);
    long long get_lo() const;
    long long get_hi() const;
    void set_lo(long long);
    void set_hi(long long);
private:
    long long lo, hi;
};

class CRangeList {
public:
    // constructor
    CRangeList() = default;
    CRangeList(const initializer_list<pair<long long, long long>> &list) : CRangeList() {
        CRangeList tmp;
        for(auto & element : list)
            tmp += CRange(element.first, element.second);
        this->range_list = tmp.range_list;
    }
    friend vector<CRange> merge(const CRangeList &);
    friend unsigned long long binary_search(const vector<CRange> &, long long);
    CRangeListIterator begin() const;
    CRangeListIterator end() const;
    CRangeList operator+(const CRange &);
    CRangeList operator+(const CRangeList &);
    CRangeList operator-(const CRange &);
    // Includes long long / range
    bool Includes(long long) const;
    bool Includes(const CRange &) const;
    // += range / range list
    CRangeList & operator+=(const CRange &);
    CRangeList & operator+=(const CRangeList &);
    // -= range / range list
    CRangeList & operator-=(const CRange &);
    CRangeList & operator-=(const CRangeList &);
    // = range / range list
    CRangeList & operator=(const CRange &);
    CRangeList & operator=(const CRangeList &);
    // operator ==
    bool operator==(const CRangeList &) const;
    // operator !=
    bool operator!=(const CRangeList &) const;
    // operator <<
    friend ostream & operator<<(ostream &, const CRangeList &);
    void push_range(const CRange &);
    void set(const vector<CRange> &);
    CRange & get(unsigned long long);
private:
    vector<CRange> range_list;
};

class CRangeListIterator {
public:
    CRangeListIterator(const CRangeList & lhs, unsigned long long id) : IterateList(lhs), ID(id) {}
    bool operator!=(const CRangeListIterator & rhs) const {
        return this->ID != rhs.ID;
    }
    const CRangeListIterator & operator++() {
        ID++;
        return *this;
    }
    CRange & operator*();
private:
    CRangeList IterateList;
    unsigned long long ID;
};

CRange & CRangeListIterator::operator*() {
    return IterateList.get(ID);
}

CRange & CRangeList::get(unsigned long long rhs) {
    return this->range_list[rhs];
}

CRangeListIterator CRangeList::begin() const {
    return CRangeListIterator(*this, 0);
}

CRangeListIterator CRangeList::end() const {
    return CRangeListIterator(*this, this->range_list.size());
}

long long CRange::get_lo() const {
    return this->lo;
}

long long CRange::get_hi() const {
    return this->hi;
}

void CRange::set_lo(long long rhs) {
    this->lo = rhs;
}

void CRange::set_hi(long long rhs) {
    this->hi = rhs;
}

void CRangeList::push_range(const CRange & rhs) {
    (this->range_list).push_back(rhs);
}

void CRangeList::set(const vector<CRange> & vec) {
    this->range_list = vec;
}

vector<CRange> merge(const CRangeList & a) {
    vector<CRange> current = a.range_list;
    vector<CRange> result;
    if(current.empty()) return current;
    result.push_back(current[0]);
    for(unsigned long long i = 1; i < current.size(); i++) {
        if(current[i].get_lo() != LLONG_MIN && result[result.size() - 1].get_hi() < current[i].get_lo() - 1)
            result.push_back(current[i]);
        else if(result[result.size() - 1].get_hi() < current[i].get_hi())
            result[result.size() - 1].set_hi(current[i].get_hi());
    }
    return result;
}

unsigned long long binary_search(const vector<CRange> & arr, long long a) {

    unsigned long long low = 0, high = arr.size() - 1, mid;

    if(arr[low].get_lo() > a) return 0;
    if(arr[high].get_lo() < a) return arr.size();

    while(low <= high) {
        mid = low + (high - low) / 2;
        if(arr[mid].get_lo() > a) {
            if(arr[mid - 1].get_lo() < a) return mid;
            else high = mid - 1;
        }
        else if(arr[mid].get_lo() < a) {
            if(arr[mid + 1].get_lo() > a) return mid + 1;
            else low = mid + 1;
        }
        else break;
    }

    return mid;

}

bool CRangeList::Includes(long long rhs) const {
    if(this->range_list.empty()) return false;
    unsigned long long n = binary_search(this->range_list, rhs);
    if(n < (this->range_list).size() && (this->range_list)[n].get_lo() <= rhs && (this->range_list)[n].get_hi() >= rhs) return true;
    if(n > 0 && (this->range_list)[n - 1].get_lo() <= rhs && (this->range_list)[n - 1].get_hi() >= rhs) return true;
    /*for(unsigned long long i = 0; i < this->range_list.size(); i++)
        if((this->range_list)[i].get_lo() <= rhs && (this->range_list)[i].get_hi() >= rhs) return true;*/
    return false;
}

bool CRangeList::Includes(const CRange & rhs) const {
    if(this->range_list.empty()) return false;
    unsigned long long n = binary_search(this->range_list, rhs.get_lo());
    if(n < (this->range_list).size() && (this->range_list)[n].get_lo() <= rhs.get_lo() && (this->range_list)[n].get_hi() >= rhs.get_hi()) return true;
    if(n > 0 && (this->range_list)[n - 1].get_lo() <= rhs.get_lo() && (this->range_list)[n - 1].get_hi() >= rhs.get_hi()) return true;
    /*for(unsigned long long i = 0; i < this->range_list.size(); i++)
        if((this->range_list)[i].get_lo() <= rhs.get_lo() && (this->range_list)[i].get_hi() >= rhs.get_hi()) return true;*/
    return false;
}

CRangeList operator+(const CRange & lhs, const CRange & rhs) {
    CRangeList a;
    if(lhs.lo < rhs.lo) {
        a.push_range(lhs);
        a.push_range(rhs);
    } else {
        a.push_range(rhs);
        a.push_range(lhs);
    }
    a.set(merge(a));
    return a;
}

CRangeList operator-(const CRange & lhs, const CRange & rhs) {
    CRangeList a;
    if(lhs.lo >= rhs.lo && lhs.hi <= rhs.hi) return a;
    else if(lhs.lo > rhs.hi || lhs.hi < rhs.lo)
        a.push_range(CRange(lhs.lo, lhs.hi));
    else if(lhs.lo < rhs.lo && lhs.hi > rhs.hi) {
        if(rhs.lo != LLONG_MIN) a.push_range(CRange(lhs.lo, rhs.lo - 1));
        if(rhs.hi != LLONG_MAX) a.push_range(CRange(rhs.hi + 1, lhs.hi));
    } else if(lhs.lo <= rhs.hi && lhs.hi > rhs.hi) {
        if (rhs.hi != LLONG_MAX) a.push_range(CRange(rhs.hi + 1, lhs.hi));
    } else {
        if(rhs.lo != LLONG_MIN) a.push_range(CRange(lhs.lo, rhs.lo - 1));
    }
    return a;
}

CRangeList CRangeList::operator+(const CRange & rhs) {
    CRangeList a;
    unsigned long long counter = 0;
    for(unsigned long long i = 0; i < (this->range_list).size();) {
        if(counter < 1 && (this->range_list)[i].get_lo() > rhs.get_lo()) {
            (a.range_list).push_back(rhs);
            counter++;
        } else {
            (a.range_list).push_back((this->range_list)[i]);
            i++;
        }
    }
    for(; counter < 1; counter++)
        (a.range_list).push_back(rhs);
    a.range_list = merge(a);
    return a;
}

CRangeList CRangeList::operator+(const CRangeList & rhs) {
    CRangeList a;
    unsigned long long counter = 0;
    for(unsigned long long i = 0; i < (this->range_list).size();) {
        if(counter < rhs.range_list.size() && (this->range_list)[i].get_lo() > (rhs.range_list)[counter].get_lo()) {
            (a.range_list).push_back((rhs.range_list)[counter]);
            counter++;
        } else {
            (a.range_list).push_back((this->range_list)[i]);
            i++;
        }
    }
    for(; counter < rhs.range_list.size(); counter++)
        (a.range_list).push_back((rhs.range_list)[counter]);
    a.range_list = merge(a);
    return a;
}

CRangeList CRangeList::operator-(const CRange & rhs) {
    CRangeList a, b;
    for(unsigned long long i = 0; i < this->range_list.size(); i++) {
        b = this->range_list[i] - rhs;
        if(!(b.range_list).empty()) {
            for(unsigned long long j = 0; j < b.range_list.size(); j++)
                a.range_list.push_back(b.range_list[j]);
        }
    }
    return a;
}

CRangeList & CRangeList::operator=(const CRange & rhs) {
    vector<CRange> vec;
    vec.push_back(CRange(rhs.get_lo(), rhs.get_hi()));
    this->range_list = vec;
    return *this;
}

CRangeList & CRangeList::operator=(const CRangeList & rhs) {
    vector<CRange> vec;
    for(unsigned long long i = 0; i < (rhs.range_list).size(); i++)
        vec.push_back(CRange(((rhs.range_list)[i]).get_lo(), ((rhs.range_list)[i]).get_hi()));
    this->range_list = vec;
    return *this;
}

CRangeList & CRangeList::operator+=(const CRange & rhs) {
    *this = *this + rhs;
    return *this;
}

CRangeList & CRangeList::operator+=(const CRangeList & rhs) {
    *this = *this + rhs;
    return *this;
}

CRangeList & CRangeList::operator-=(const CRange & rhs) {
    *this = *this - rhs;
    return *this;
}

CRangeList & CRangeList::operator-=(const CRangeList & rhs) {
    for(unsigned long long i = 0; i < rhs.range_list.size(); i++)
        *this -= rhs.range_list[i];
    return *this;
}

bool CRangeList::operator==(const CRangeList & rhs) const {
    if((this->range_list).size() != (rhs.range_list).size()) return false;
    for(unsigned long long i = 0; i < (this->range_list).size(); i++) {
        if(((this->range_list)[i]).get_lo() != ((rhs.range_list)[i]).get_lo() || ((this->range_list)[i]).get_hi() != ((rhs.range_list)[i]).get_hi()) return false;
    }
    return true;
}

bool CRangeList::operator!=(const CRangeList & rhs) const {
    if(this->range_list.empty() && rhs.range_list.empty()) return false;
    if((this->range_list).size() != (rhs.range_list).size()) return true;
    for(unsigned long long i = 0; i < (this->range_list).size(); i++) {
        if(((this->range_list)[i]).get_lo() == ((rhs.range_list)[i]).get_lo() && ((this->range_list)[i]).get_hi() == ((rhs.range_list)[i]).get_hi()) return false;
    }
    return true;
}

ostream & operator<<(ostream & output, const CRangeList & rhs) {
    output << "{";
    for(unsigned long long i = 0; i < (rhs.range_list).size(); i++) {
        if((rhs.range_list)[i].get_lo() < (rhs.range_list)[i].get_hi())
            output << "<" << (rhs.range_list)[i].get_lo() << ".." << (rhs.range_list)[i].get_hi() << ">";
        else output << (rhs.range_list)[i].get_lo();
        if(i != (rhs.range_list).size() - 1) output << ",";
    }
    output << "}";
    return output;
}

ostream & operator<<(ostream & output, const CRange & rhs) {
    output << dec;
    if(rhs.lo == rhs.hi)
        output << rhs.lo;
    else output << "<" << rhs.lo << ".." << rhs.hi << ">";
    output << hex;
    return output;
}

//#ifndef __PROGTEST__
string toString(const CRangeList & x) {
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main(void) {
    CRangeList a, b;

    assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
    a = CRange ( 5, 10 );
    a += CRange ( 25, 100 );
    assert ( toString ( a ) == "{<5..10>,<25..100>}" );
    a += CRange ( -5, 0 );
    a += CRange ( 8, 50 );
    assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
    a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
    assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
    a += CRange ( 106, 119 ) + CRange ( 152, 158 );
    assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
    a += CRange ( -3, 170 );
    a += CRange ( -30, 1000 );
    assert ( toString ( a ) == "{<-30..1000>}" );
    b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
    a += b;
    assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( -400, -400 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    try
    {
        a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
        assert ( "Exception not thrown" == NULL );
    }
    catch ( const InvalidRangeException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown" == NULL );
    }
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    b = a;
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 2600, 2700 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 15, 15 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
    assert ( !( a == b ) );
    assert ( a != b );
    assert ( b . Includes ( 15 ) );
    assert ( b . Includes ( 2900 ) );
    assert ( b . Includes ( CRange ( 15, 15 ) ) );
    assert ( b . Includes ( CRange ( -350, -350 ) ) );
    assert ( b . Includes ( CRange ( 100, 200 ) ) );
    assert ( !b . Includes ( CRange ( 800, 900 ) ) );
    assert ( !b . Includes ( CRange ( -1000, -450 ) ) );
    assert ( !b . Includes ( CRange ( 0, 500 ) ) );
    //assert(!b.Includes(CRange(LLONG_MIN, LLONG_MAX)));
    a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
    assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b += a;
    assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b -= a;
    assert ( toString ( b ) == "{}" );
    b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
    assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
    b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
    assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
#ifdef EXTENDED_SYNTAX
  CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
  assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
  ostringstream oss;
  oss << setfill ( '=' ) << hex << left;
  for ( const auto & v : x + CRange ( -100, -100 ) )
      oss << v << endl;
  oss << setw ( 10 ) << 1024;
  assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
    return 0;
}
//#endif /* __PROGTEST__ */