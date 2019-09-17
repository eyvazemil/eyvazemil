#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

class InvalidIndexException
{
};

#endif /* __PROGTEST__ */

// class CString that is like a C++ std::string class
class CString {
public:
    // constructor without parameters
    CString() : size(0) {
        string = new char[1];
        string[0] = '\0';
    }
    // constructor with string parameter
    CString(const char * str) {
        unsigned long len = strlen(str);
        string = new char[len + 1];
        // copies string in parameter in this->string
        strncpy(string, str, len);
        size = len;
    }
    // copy constructor
    CString(const CString & str) {
        char * tmp = new char[str.size + 1];
        strncpy(tmp, str.string, str.size);
        tmp[str.size] = '\0';
        this->string = tmp;
        this->size = str.size;
    }
    // destructor
    ~CString() {
        delete[] string;
    }
    // method substring return a part of the string: from-to inclusively
    CString substring(unsigned long from, unsigned long to) const {
        char * tmp = new char[to - from + 2];
        unsigned long i;
        for(i = from; i <= to; i++)
            tmp[i - from] = string[i];
        tmp[i] = '\0';
        CString a(tmp);
        return a;
    }
    // operator= that takes CString as a parameter
    CString & operator=(const CString & str) {
        char * tmp = new char[str.size + 1];
        strncpy(tmp, str.string, str.size);
        tmp[str.size] = '\0';
        delete[] this->string;
        this->string = tmp;
        this->size = str.size;
        return *this;
    }
    // operator= that takes const string as parameter
    CString & operator=(const char * str) {
        unsigned long len = strlen(str);
        char * tmp = new char[len + 1];
        strncpy(tmp, str, len);
        tmp[len] = '\0';
        delete[] this->string;
        this->string = tmp;
        this->size = len;
        return *this;
    }
    // operator[] returns character at given position
    char operator[](unsigned long id) const {
        return string[id];
    }
    // operator<<
    friend ostream & operator<<(ostream &, const CString &);
    // string getter
    char * get_string() const {
        return this->string;
    }
    // size getter
    unsigned long get_size() const {
        return this->size;
    }
private:
    // C-style string(pointer to character)
    char * string;
    // size of the string
    unsigned long size;
    // constructor without parameters
};

// operator<< for CString class
ostream & operator<<(ostream & os, const CString & rhs) {
    for(unsigned long i = 0; i < rhs.size; i++)
        os << (rhs.string)[i];
    return os;
}

// template class CVector
// stores any amount of any type objects
// works as C++ std::vector
template<class T>
class CVector {
public:
    // constructor without parameters
    CVector() : size(0), mem_size(10) {
        vector = new T[mem_size];
    }
    // destructor
    ~CVector() {
        delete[] vector;
    }
    // push object to the end of this container
    void push_back(const T & rhs) {
        if(size + 2 >= mem_size) {
            T * tmp = new T[mem_size *= 2];
            for(unsigned long i = 0; i < size; i++)
                tmp[i] = vector[i];
            delete[] vector;
            vector = tmp;
        }
        vector[size] = rhs;
        size++;
    }
    // insert object at position pos in this array
    bool insert(unsigned long pos, const T & rhs) {
        if(pos > size) return false;
        if(pos == size) {
            push_back(rhs);
            return true;
        }
        if(size + 2 >= mem_size) {
            T * tmp = new T[mem_size *= 2];
            for(int i = 0; i < size; i++)
                tmp[i] = vector[i];
            delete[] vector;
            vector = tmp;
        }
        T * tmp = new T[mem_size];
        unsigned long counter = 0;
        for(unsigned long i = 0; i < size + 1; i++) {
            if(i == pos) {
                tmp[i] = rhs;
                continue;
            }
            tmp[i] = vector[counter];
            counter++;
        }
        delete[] vector;
        vector = tmp;
        size++;
        return true;
    }
    // erase object from this array at position pos
    bool erase(unsigned long pos) {
        if(size == 0 || pos >= size) return false;
        T * tmp = new T[mem_size];
        unsigned long counter = 0;
        for(int i = 0; i < size; i++) {
            if(i == pos) continue;
            tmp[counter] = vector[i];
            counter++;
        }
        delete[] vector;
        vector = tmp;
        size--;
        return true;
    }
    // erase object that are located in this array: from-to inclusively
    bool erase(unsigned long from, unsigned long to) {
        if(size == 0 || from >= size || to >= size) return false;
        T * tmp = new T[mem_size];
        unsigned long counter = 0;
        for(unsigned long i = 0; i < from; i++) {
            tmp[counter] = vector[i];
            counter++;
        }
        for(unsigned long i = to + 1; i < size; i++) {
            tmp[counter] = vector[i];
            counter++;
        }
        delete[] vector;
        vector = tmp;
        size -= to - from + 1;
        return true;
    }
    // operator= with T object in the parameter
    CVector & operator=(const CVector & rhs) {
        delete[] vector;
        this->mem_size = rhs.mem_size;
        this->size = rhs.size;
        T * tmp = new T[mem_size];
        for(unsigned long i = 0; i < size; i++)
            tmp[i] = rhs[i];
        vector = tmp;
        return *this;
    }
    // operator[] returns object at position id
    T & operator[](unsigned long id) const {
        return vector[id];
    }
    // vector getter
    T * get_vector() const {
        return this->vector;
    }
    // size getter
    unsigned long get_size() const {
        return this->size;
    }
    // mem_size getter
    unsigned long get_mem_size() const {
        return this->mem_size;
    }
private:
    // C-style array of type T
    T * vector;
    // size of the array
    unsigned long size;
    // allocated memory on heap for this array
    unsigned long mem_size;
};

// class Patch that represents one string patch
class Patch {
public:
    // constructor without parameters
    Patch() : from(0), offset(0), ptr(nullptr) {}
    // constructor with parameters
    Patch(unsigned long f, unsigned long oset, const CString & s) : from(f), offset(oset) {
        CString * a = new CString(s);
        shared_ptr<CString> ptr1(a);
        this->ptr = ptr1;
        len = s.get_size();
    }
    // constructor with from, offset, length, and CString parameters
    Patch(unsigned long f, unsigned long oset, unsigned long l, const CString & s) : from(f), offset(oset), len(l) {
        this->ptr = make_shared<CString>(s);
    }
    // constructor with from, offset, length, and shred_ptr parameter
    Patch(unsigned long f, unsigned long oset, unsigned long l, shared_ptr<CString> ptr1) : from(f), offset(oset), len(l) {
        this->ptr = ptr1;
    }
    // destructor
    ~Patch() {}
    // operator=
    Patch & operator=(const Patch & rhs) {
        this->from = rhs.from;
        this->offset = rhs.offset;
        this->ptr = rhs.ptr;
        this->len = rhs.len;
        return *this;
    }
    // from getter
    unsigned long get_from() {
        return this->from;
    }
    // offset getter
    unsigned long get_offset() {
        return this->offset;
    }
    // len getter
    unsigned long get_len() {
        return this->len;
    }
    // ptr getter
    shared_ptr<CString> get_ptr() {
        return this->ptr;
    }
private:
    // position of this patch in original string
    unsigned long from;
    // position of this patch in another patch
    unsigned long offset;
    // length of this patch
    unsigned long len;
    // shared_ptr that points to the CString
    shared_ptr<CString> ptr;
};

// class CPatchStr
// stores original string as separate patches
class CPatchStr {
public:
    // constructor without parameters
    CPatchStr() : length(0) {}
    // constructor with const char parameter
    CPatchStr(const char * str) {
        string_patches.push_back(Patch(0, 0, strlen(str), CString(str)));
        length = strlen(str);
    }
    // copy constructor
    CPatchStr(const CPatchStr & rhs) {
        unsigned long f = 0;
        for(unsigned long i = 0; i < (rhs.string_patches).get_size(); i++) {
            (this->string_patches).push_back(Patch(f, (rhs.string_patches)[i].get_offset(),
                    (rhs.string_patches)[i].get_len(), (rhs.string_patches)[i].get_ptr()));
            f += (rhs.string_patches)[i].get_len();
        }
        length = rhs.length;
    }
    // operator[] that returns Patch in given position
    Patch & operator[](unsigned long id) {
        return (this->string_patches)[id];
    }
    // operator== checks if two strings are equal
    bool operator==(const CPatchStr & rhs) {
        if(this->length != rhs.length) return false;
        for(unsigned long i = 0; i < (this->string_patches).get_size(); i++) {
            if ((this->string_patches)[i].get_ptr() != (rhs.string_patches)[i].get_ptr() ||
                (this->string_patches)[i].get_len() != (rhs.string_patches)[i].get_len() ||
                (this->string_patches)[i].get_offset() != (rhs.string_patches)[i].get_offset() ||
                (this->string_patches)[i].get_from() != (rhs.string_patches)[i].get_from())
                return false;
        }
        return true;
    }
    // destructor
    ~CPatchStr() {}
    // operator= with const char as parameter
    CPatchStr & operator=(const char * str) {
        unsigned long len = strlen(str);
        this->length = len;
        CPatchStr tmp;
        (tmp.string_patches).push_back(Patch(0, 0, len, CString(str)));
        this->string_patches = tmp.string_patches;
        return *this;
    }
    // operator= with CPatchStr as parameter
    CPatchStr & operator=(const CPatchStr & rhs) {
        unsigned long f = 0;
        this->length = rhs.length;
        CPatchStr tmp;
        for(unsigned long i = 0; i < (rhs.string_patches).get_size(); i++) {
            (tmp.string_patches).push_back(Patch(f, (rhs.string_patches)[i].get_offset(),
                    (rhs.string_patches)[i].get_len(), (rhs.string_patches)[i].get_ptr()));
            f += (rhs.string_patches)[i].get_len();
        }
        this->string_patches = tmp.string_patches;
        return *this;
    }
    // to search in log(n) time
    unsigned long binary_search(unsigned long) const;
    // return a substring of the original string
    CPatchStr SubStr(size_t, size_t) const;
    // append into original string
    CPatchStr & Append(const CPatchStr &);
    // insert into original string at given position
    CPatchStr & Insert(size_t, const CPatchStr &);
    // delete from original string
    CPatchStr & Delete(size_t, size_t);
    // convert patches into original string
    char * ToStr() const;
    // string_patches getter
    CVector<Patch> get_string_patches() {
        return this->string_patches;
    }
    // length getter
    unsigned long long get_length() {
        return this->length;
    }
private:
    // vector of patches
    CVector<Patch> string_patches;
    // length of the original string
    unsigned long long length;
};

// binary_search in CPatchStr
unsigned long CPatchStr::binary_search(unsigned long a) const {

    unsigned long low = 0, high = (this->string_patches).get_size() - 1, mid;

    if((this->string_patches)[low].get_from() > a) return 0;
    if((this->string_patches)[high].get_from() + (this->string_patches)[high].get_len() - 1 < a) return high;

    while(low <= high) {
        mid = low + (high - low) / 2;
        if((this->string_patches)[mid].get_from() > a) high = mid - 1;
        else if((this->string_patches)[mid].get_from() + (this->string_patches)[mid].get_len() - 1 < a) low = mid + 1;
        else break;
    }
    return mid;
}

// Append in CPatchStr
CPatchStr & CPatchStr::Append(const CPatchStr & src) {
    unsigned long f = this->length;
    unsigned long till = (src.string_patches).get_size();
    for(unsigned long i = 0; i < till; i++) {
        (this->string_patches).push_back(Patch(f, (src.string_patches)[i].get_offset(),
                (src.string_patches)[i].get_len(), (src.string_patches)[i].get_ptr()));
        f += (src.string_patches)[i].get_len();
    }
    this->length += src.length;
    return *this;
}

// ToStr in CPatchStr
char * CPatchStr::ToStr() const {
    char * str;
    if(this->length == 0) {
        str = new char[1];
        str[0] = '\0';
        return str;
    } else {
        unsigned long counter = 0;
        str = new char[this->length + 1];
        for(unsigned long i = 0; i < (this->string_patches).get_size(); i++) {
            for(unsigned long j = (this->string_patches)[i].get_offset();
            j < (this->string_patches)[i].get_offset() + (this->string_patches)[i].get_len(); j++) {
                str[counter] = ((*((this->string_patches)[i].get_ptr())).get_string())[j];
                counter++;
            }
        }
        str[counter] = '\0';
    }
    return str;
}

// SubStr in CPatchStr
CPatchStr CPatchStr::SubStr(size_t from, size_t len) const {
    if(from + len > this->length) throw InvalidIndexException();
    if(len == 0) return CPatchStr("");
    size_t end = from + len - 1;
    unsigned long f = 0;
    unsigned long i_from = binary_search(from), i_end = binary_search(end), t;
    unsigned long tmp_length_from = (this->string_patches)[i_from].get_from() + (this->string_patches)[i_from].get_len();
    CPatchStr tmp;

    if(i_from == 0) t = 0;
    else t = tmp_length_from - (this->string_patches)[i_from].get_len();

    if(i_from == i_end) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_from].get_offset() + from - t, len,
                (this->string_patches)[i_from].get_ptr()));
        f += len;
    } else if(i_from + 1 == i_end) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_from].get_offset() + from - t,
                tmp_length_from - from, (this->string_patches)[i_from].get_ptr()));
        f += tmp_length_from - from;
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_end].get_offset(),
                end - tmp_length_from + 1, (this->string_patches)[i_end].get_ptr()));
        f += end - tmp_length_from + 1;
    } else {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_from].get_offset() + from - t,
                tmp_length_from - from, (this->string_patches)[i_from].get_ptr()));
        f += tmp_length_from - from;
        for(++i_from; i_from < i_end; i_from++) {
            (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_from].get_offset(),
                    (this->string_patches)[i_from].get_len(), (this->string_patches)[i_from].get_ptr()));
            tmp_length_from += (this->string_patches)[i_from].get_len();
            f += (this->string_patches)[i_from].get_len();
        }
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_end].get_offset(),
                end - tmp_length_from + 1, (this->string_patches)[i_end].get_ptr()));
        f += end - tmp_length_from + 1;
    }
    tmp.length = len;
    return tmp;
}

// Insert in CPatchStr
CPatchStr & CPatchStr::Insert(size_t pos, const CPatchStr & src) {
    if(pos > this->length) throw InvalidIndexException();
    if(pos == this->length) {
        Append(src);
        return *this;
    }
    unsigned long f = 0;
    unsigned long i_pos = binary_search(pos);
    unsigned long tmp_length_before = (this->string_patches)[i_pos].get_from();
    unsigned long tmp_length_pos = tmp_length_before + (this->string_patches)[i_pos].get_len();
    CPatchStr tmp;
    for(unsigned long i = 0; i < i_pos; i++) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i].get_offset(),
                (this->string_patches)[i].get_len(), (this->string_patches)[i].get_ptr()));
        f += (this->string_patches)[i].get_len();
    }
    if(pos > tmp_length_before) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_pos].get_offset(),
                pos - tmp_length_before, (this->string_patches)[i_pos].get_ptr()));
        f += pos - tmp_length_before;
    }
    for(unsigned long i = 0; i < (src.string_patches).get_size(); i++) {
        (tmp.string_patches).push_back(Patch(f, (src.string_patches)[i].get_offset(),
                (src.string_patches)[i].get_len(), (src.string_patches)[i].get_ptr()));
        f += (src.string_patches)[i].get_len();
    }
    (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_pos].get_offset() + pos - tmp_length_before,
            tmp_length_pos - pos, (this->string_patches)[i_pos].get_ptr()));
    f += tmp_length_pos - pos;
    for(++i_pos; i_pos < (this->string_patches).get_size(); i_pos++) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_pos].get_offset(),
                (this->string_patches)[i_pos].get_len(), (this->string_patches)[i_pos].get_ptr()));
        f += (this->string_patches)[i_pos].get_len();
    }
    tmp.length = this->length + src.length;
    *this = tmp;
    return *this;
}

// Delete from CPatchStr
CPatchStr & CPatchStr::Delete(size_t from, size_t len) {
    if(from + len > this->length) throw InvalidIndexException();
    if(len == 0) return *this;
    size_t end = from + len - 1;
    unsigned long f = 0;
    unsigned long i_from = binary_search(from), i_end = binary_search(end);
    unsigned long  tmp_length_from = (this->string_patches)[i_from].get_from() + (this->string_patches)[i_from].get_len();
    unsigned long tmp_length_end = (this->string_patches)[i_end].get_from() + (this->string_patches)[i_end].get_len();
    CPatchStr tmp;
    for(unsigned long i = 0; i < i_from; i++) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i].get_offset(),
                (this->string_patches)[i].get_len(), (this->string_patches)[i].get_ptr()));
        f += (this->string_patches)[i].get_len();
    }
    if(from > tmp_length_from - (this->string_patches)[i_from].get_len()) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_from].get_offset(),
                from - (tmp_length_from - (this->string_patches)[i_from].get_len()), (this->string_patches)[i_from].get_ptr()));
        f += from - (tmp_length_from - (this->string_patches)[i_from].get_len());
    }
    if(end < tmp_length_end - 1) {
        (tmp.string_patches).push_back(Patch(f,
                (this->string_patches)[i_end].get_offset() + end - (tmp_length_end - (this->string_patches)[i_end].get_len()) + 1,
                tmp_length_end - end - 1, (this->string_patches)[i_end].get_ptr()));
        f += tmp_length_end - end - 1;
    }
    for(++i_end; i_end < (this->string_patches).get_size(); i_end++) {
        (tmp.string_patches).push_back(Patch(f, (this->string_patches)[i_end].get_offset(),
                (this->string_patches)[i_end].get_len(), (this->string_patches)[i_end].get_ptr()));
        f += (this->string_patches)[i_end].get_len();
    }
    tmp.length = this->length - len;
    *this = tmp;
    return *this;
}

#ifndef __PROGTEST__
bool stringMatch(char * str, const char * expected) {
    bool res = strcmp(str, expected) == 0;
    delete[] str;
    return res;
}

int main() {
    char tmpStr[100];

    CPatchStr a ( "test" );
    assert ( stringMatch ( a . ToStr (), "test" ) );
    strncpy ( tmpStr, " da", sizeof ( tmpStr ) );
    a . Append ( tmpStr );
    assert ( stringMatch ( a . ToStr (), "test da" ) );
    strncpy ( tmpStr, "ta", sizeof ( tmpStr ) );
    a . Append ( tmpStr );
    assert ( stringMatch ( a . ToStr (), "test data" ) );
    strncpy ( tmpStr, "foo text", sizeof ( tmpStr ) );
    CPatchStr b ( tmpStr );
    assert ( stringMatch ( b . ToStr (), "foo text" ) );
    CPatchStr c ( a );
    assert ( stringMatch ( c . ToStr (), "test data" ) );
    CPatchStr d ( a . SubStr ( 3, 5 ) );
    assert ( stringMatch ( d . ToStr (), "t dat" ) );
    d . Append ( b );
    assert ( stringMatch ( d . ToStr (), "t datfoo text" ) );
    d . Append ( b . SubStr ( 3, 4 ) );
    assert ( stringMatch ( d . ToStr (), "t datfoo text tex" ) );
    c . Append ( d );
    assert ( stringMatch ( c . ToStr (), "test datat datfoo text tex" ) );
    c . Append ( c );
    assert ( stringMatch ( c . ToStr (), "test datat datfoo text textest datat datfoo text tex" ) );
    d . Insert ( 2, c . SubStr ( 6, 9 ) );
    assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
    b = "abcdefgh";
    assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
    assert ( stringMatch ( b . ToStr (), "abcdefgh" ) );
    assert ( stringMatch ( d . ToStr (), "t atat datfdatfoo text tex" ) );
    assert ( stringMatch ( d . SubStr ( 4, 8 ) . ToStr (), "at datfd" ) );
    assert ( stringMatch ( b . SubStr ( 2, 6 ) . ToStr (), "cdefgh" ) );
    try
    {
        b . SubStr ( 2, 7 ) . ToStr ();
        assert ( "Exception not thrown" == NULL );
    }
    catch ( InvalidIndexException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown" == NULL );
    }
    a . Delete ( 3, 5 );
    assert ( stringMatch ( a . ToStr (), "tesa" ) );
    return 0;
}
#endif /* __PROGTEST__ */