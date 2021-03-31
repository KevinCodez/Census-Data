//  Person.hpp
//  Census Data
//  Created by Kevin Reynolds on 11/5/20.

#ifndef Person_hpp
#define Person_hpp
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

class Person {
    
private:
    string mGender;
    string mTitle;
    string mFirstName;
    string mMiddleInitial;
    string mLastName;
    string mStreetAddress;
    string mCity;
    string mState;
    string mZipCode;
    string mEmail;
    string mBirthday;
    int mAge;
    
    // Helper Functions
    int calculateAge(int cDay, int cMonth, int cYear, int bDay, int bMonth, int bYear);
    
public:
    // Constructor
    Person();
    Person(
           string gender,
           string title,
           string firstname,
           string middleInitial,
           string lastName,
           string streetAddress,
           string city,
           string state,
           string zipCode,
           string email,
           string birthday
    );
    
    // Destructor
    ~Person();
    
    // Setters
    void setGender(string g);
    void setTitle(string t);
    void setFirstName(string fName);
    void setMiddleInitial(string initial);
    void setLastName(string lName);
    void setStreetAddress(string sAddress);
    void setCity(string city);
    void setState(string state);
    void setZipCode(string zip);
    void setEmail(string email);
    void setBirthday(string birthday);
    void setAge(string birthday);
    
    // Getters
    string gender();
    string title();
    string firstName();
    string middleInitial();
    string lastName();
    string streetAddress();
    string city();
    string state();
    string zipCode();
    string email();
    string birthday();
    int age();
};

#endif /* Person_hpp */
