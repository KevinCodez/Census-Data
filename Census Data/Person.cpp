//  Person.cpp
//  Census Data
//  Created by Kevin Reynolds on 11/5/20.


#include "Person.hpp"

// Constructors
Person::Person() {
    setGender("N/A");
    setTitle("N/A");
    setFirstName("N/A");
    setMiddleInitial("N/A");
    setLastName("N/A");
    setStreetAddress("N/A");
    setCity("N/A");
    setState("N/A");
    setZipCode("N/A");
    setEmail("N/A");
    setBirthday("N/A");
};

Person::Person(
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
) {
    setGender(gender);
    setTitle(title);
    setFirstName(firstname);
    setMiddleInitial(middleInitial);
    setLastName(lastName);
    setStreetAddress(streetAddress);
    setCity(city);
    setState(state);
    setZipCode(zipCode);
    setEmail(email);
    setBirthday(birthday);
    setAge(birthday);
};

// Destructor
Person::~Person() {
}

// Setters
void Person::setGender(string g) { mGender = g; }
void Person::setTitle(string t) { mTitle = t; }
void Person::setFirstName(string fName) { mFirstName = fName; }
void Person::setMiddleInitial(string initial) { mMiddleInitial = initial; }
void Person::setLastName(string lName) { mLastName = lName; }

void Person::setStreetAddress(string sAddress) {
    
    //Remove quotes from address if needed
    if (sAddress[0] == '"') {
        sAddress.erase(sAddress.begin());
        sAddress.erase(sAddress.end() -1);
    }
    mStreetAddress = sAddress;
}

void Person::setCity(string city) {
    
    //Remove quotes from name if needed
    if (city[0] == '"') {
        city.erase(city.begin());
        city.erase(city.end() -1);
    }
    mCity = city;
}

void Person::setState(string state) { mState = state; }
void Person::setZipCode(string zip) { mZipCode = zip; }
void Person::setEmail(string email) { mEmail = email; }

void Person::setBirthday(string birthday) {
    mBirthday = birthday;
    setAge(birthday);
}

void Person::setAge(string birthday) {
    
    string strDay, strMonth, strYear;
    
    //convert birthday string to individual numbers
    //  eg.  3/3/1999 -> 3  3  1999
    istringstream ss(birthday);
    getline(ss, strMonth, '/');
    getline(ss, strDay, '/');
    getline(ss, strYear, '\n');
    
    // Convert values from string to int
    int bDay = stoi(strDay);
    int bMonth = stoi(strMonth);
    int bYear = stoi(strYear);
    
    // Get Date
    // Grabs local system time
    time_t theTime = time(NULL);
    
    // Sets a tm struct with that time
    tm *currentTime = localtime(&theTime);
    
    // Retrieves the data from struct
    int day = currentTime -> tm_mday;
    int month = currentTime -> tm_mon + 1;
    int year = currentTime -> tm_year + 1900;
    
    mAge = calculateAge(day, month, year, bDay, bMonth, bYear);
}

// Helper Functions
int Person::calculateAge(int cDay, int cMonth, int cYear, int bDay, int bMonth, int bYear) {
    
    int age = cYear - bYear; // Age you should be turning this year
    
    //Determines if you have reached your birthday for this year
    if (cMonth > bMonth) {
        // You've had a birthday this year
        return age;
    } else if (cMonth < bMonth) {
        //You have not had a birthday this year
        // Subtract 1 from age, then return age
        age = age - 1;
        return age;
    } else if (cMonth == bMonth) {
        if (cDay >= bDay) {
            //You had a birthday recently
            return age;
        } else {
            //You havent had a birthday this year
            age = age - 1;
            return age;
        }
    }
    return age;
}


//Getters
string Person::gender() { return mGender; }
string Person::title() { return mTitle; }
string Person::firstName() { return mFirstName; }
string Person::middleInitial() { return mMiddleInitial; }
string Person::lastName() { return mLastName; }
string Person::streetAddress() { return mStreetAddress; }
string Person::city() { return mCity; }
string Person::state() { return mState; }
string Person::zipCode() { return mZipCode; }
string Person::email() { return mEmail; }
string Person::birthday() { return mBirthday; }
int Person::age() { return mAge; }
