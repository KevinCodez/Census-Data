//  main.cpp
//  Census Data
//  Created by Kevin Reynolds on 11/5/20.

#include <iostream>
#include <fstream>
#include <string>
#include "Person.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// Custom pair struct used to pair name, state and age
// with their corresponding occurrences
struct Pair {
    string name;
    int occurrence;
    
    // Constructor
    Pair(string param_name, int param_occurrence) {
        name = param_name;
        occurrence = param_occurrence;
    }
};

// Functions for the std::sort() algorithm to
// operate on values in the above struct
bool isBigger(const Pair& lhs, const Pair& rhs) {
  return lhs.occurrence < rhs.occurrence;
}

bool isBiggerName(const Pair& lhs, const Pair& rhs) {
  return lhs.name < rhs.name;
}

int main() {
    
    //Declare variables;
    string gender,title, firstName, middleInitial, lastName, streetAddress, city, state, zipCode, email, birthday;
    
    const string input_file = "FakeNames.csv";
    const string output_file = "summary.txt";
    
    ifstream iFile; // Create input file stream instance
    iFile.open(input_file); // Create input stream
    
    // Vector to hold all 6000 people objects
    vector<Person> people;
    
    // Keep looping until EOF
    while ( iFile.peek() != EOF ) {
        getline(iFile, gender, ',');
        getline(iFile, gender, ',');
        getline(iFile, title, ',');
        getline(iFile, firstName, ',');
        getline(iFile, middleInitial, ',');
        getline(iFile, lastName, ',');
        getline(iFile, streetAddress, ',');
        getline(iFile, city, ',');
        getline(iFile, state, ',');
        getline(iFile, zipCode, ',');
        getline(iFile, email, ',');
        getline(iFile, birthday, '\n');
        
        // If statement to ignore first line (headers)
        if (gender != "Gender" ) {
            people.push_back(Person(gender, title, firstName, middleInitial, lastName, streetAddress, city, state, zipCode, email, birthday));
        }
    }
    
    iFile.close(); // All records are imported. Close input stream.
    
    // Get gender counts
    int numberOfMales = 0, numberOfFemales = 0;
    for (auto person = people.begin(); person != people.end(); ++person) {
        if (person -> gender() == "male") {
            numberOfMales++;
        } else {
            numberOfFemales++;
        }
    }
    
    // Start to calculate common first names
    vector<Pair> uniqueFirstNames;
    vector<string> firstNames;
    
    //load all names into a vector
    for (auto person = people.begin(); person != people.end(); ++person) {
        firstNames.push_back(person -> firstName());
    }
    
    //Sort vector of all names
    sort(firstNames.begin(), firstNames.end());
    
    //Declare some variables for loop
    string previousName = "";
    int nameOccurance = 1;
    
    // The following loop adds unique Pair structs to the uniqueNames to vector
    for (auto fName = firstNames.begin(); fName != firstNames.end(); ++fName) {
        if (*fName == previousName) {
            // Names occurs Again
            nameOccurance++;
        } else {
            // New Name, add uniqueNames vector
            uniqueFirstNames.push_back(Pair(previousName, nameOccurance));
            nameOccurance = 1;        }
            previousName = *fName;
    }
    
    //Sort the uniqueNames vector by occurance
    sort(uniqueFirstNames.rbegin(), uniqueFirstNames.rend(), isBigger);
    
    
    // Calculate State Totals
    // Load Array of peoples states
    vector<string> states;
    for (auto person = people.begin(); person != people.end(); ++person) {
        states.push_back( person -> state() );
    }
    
    //Sort array of states
    sort(states.begin(), states.end());
    states.push_back("buffer");
    
    //Create array of objects then load array
    string previousState = "";
    int stateOccurance = 1;
    
    vector<Pair> vStatePair;
    for (auto state = states.begin(); state != states.end(); ++state) {
        if (*state == previousState) {
            // Names occurs Again
            stateOccurance++;
        } else {
            // New Name, add uniqueNames vector
            if (previousState != "") {
                vStatePair.push_back(Pair(previousState, stateOccurance));
                stateOccurance = 1;
            }
        }
        previousState = *state;
    }
    
    // Sort states by occurance
    sort(vStatePair.begin(), vStatePair.end(), isBiggerName);
    
    //Create array of ages
    vector<string> ages;
    for (auto person = people.begin(); person != people.end(); ++person) {
        string sAge = to_string( person -> age() );
        ages.push_back(sAge);
    }
    
    //Sort array of states
    sort(ages.begin(), ages.end());
    
    ages.push_back("buffer");
    
    //Create array of objects then load array
    string previousAge = "";
    int ageOccurance = 1;
    
    vector<Pair> vAgePair;
    for (auto age = ages.begin(); age != ages.end(); ++age) {
        if (*age == previousAge) {
            // Names occurs Again
            ageOccurance++;
        } else {
            // New Name, add uniqueNames vector
            if (previousAge != "") {
                vAgePair.push_back(Pair(previousAge, ageOccurance));
                ageOccurance = 1;
            }
        }
        previousAge = *age;
    }
    
    // Sort vAgePair vector
    sort(vAgePair.begin(), vAgePair.end(), isBiggerName);
    
    
    
    //              ***  Output  ***
    
    
    
    ofstream oFile; // Create output file instance
    oFile.open(output_file); // Create output stream
    
    // Display first person in record
    oFile << "File contains " << people.size() << " records" << endl << endl;
    oFile << "First person: " <<
            people.begin() -> firstName() << " " <<
            people.begin() -> middleInitial() << " " <<
            people.begin() -> lastName() << " " <<
            people.begin() -> birthday() << endl;
    
    // Display last person in record
    oFile << "Last person: " <<
            (people.end() - 1) -> firstName() << " " <<
            (people.end() - 1) -> middleInitial() << " " <<
            (people.end() - 1) -> lastName() << " " <<
            (people.end() - 1) -> birthday() << endl << endl;
    
    // Display gender counts
    oFile << "Males: " << numberOfMales << endl;
    oFile << "Famale: " << numberOfFemales << endl << endl;
    
    // Display Number of records
    oFile << uniqueFirstNames.size() << " unique first names found:" << endl;
    
    // Display chart of top 100 name occurances
    for (auto it = uniqueFirstNames.begin(); it != uniqueFirstNames.begin() + 100; ++it) {
        auto i = distance(uniqueFirstNames.begin(), it) + 1;
        
        oFile << setw(12) << right << it -> name << ":" << setw(3) << right << it -> occurrence;
        
        if (i % 4 == 0) {
            oFile << endl;
        }
        
    }
    
    // Display chart of state pairs
    oFile << "\nAmount of people by state: ";
    for (auto it = vStatePair.begin(); it != vStatePair.end(); ++it) {
        
        auto i = distance(vStatePair.begin(), it);
        
        if (i % 7 == 0) {
            oFile << endl;
            oFile << it -> name << ":" << setw(3) << right << it -> occurrence;
        } else {
            oFile << setw(7) << right << it -> name << ":" << setw(3) << right << it -> occurrence;
        }
        
    }
    
    // Display chart of age pairs
    oFile << "\n\nFound " << vAgePair.size() << " unique ages" << endl;
    oFile << "Amount of people by age: " << endl;
    for (auto it = vAgePair.begin(); it != vAgePair.end(); ++it) {
        auto i = distance(vAgePair.begin(), it) + 1;
        oFile << setw(7) << right << it -> name << ":" << setw(3) << right << it -> occurrence;
        if (i % 5 == 0) {
            oFile << endl;
        }

    }
    

    
    return 0;
}
