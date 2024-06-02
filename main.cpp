#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Data {
    string CustomerID;
    string Name;
    int Age;
    int CreditScore;
    double TransactionAmount;
    double LoanAmount;
    int LatePayments;


};

struct SME {
    string BusinessID;
    string BusinessName;
    string Industry;
    double AnnualRevenue;
    int CreditScore;
    int LatePayments;


};

vector<Data> readDataFromCSVFile(string filename) {
    vector<Data> data;
    ifstream file(filename);

    string line, field;
    while (getline(file, line)) {
        Data customer;
        stringstream ss(line);
        getline(ss, customer.CustomerID, ',');
        getline(ss, customer.Name, ',');
        getline(ss, field, ',');
        customer.Age = stoi(field);
        getline(ss, field, ',');
        customer.CreditScore = stoi(field);
        getline(ss, field, ',');
        customer.TransactionAmount = stod(field);
        getline(ss, field, ',');
        customer.LoanAmount = stod(field);
        getline(ss, field, ',');
        customer.LatePayments = stoi(field);

        data.push_back(customer);
    }

    return data;
}

vector<SME> readSMEDataFromCSVFile(string filename) {
    vector<SME> smes;
    ifstream file(filename);

    string line, field;
    while (getline(file, line)) {
        SME sme;
        stringstream ss(line);
        getline(ss, sme.BusinessID, ',');
        getline(ss, sme.BusinessName, ',');
        getline(ss, sme.Industry, ',');
        getline(ss, field, ',');
        sme.AnnualRevenue = stod(field);
        getline(ss, field, ',');
        sme.CreditScore = stoi(field);
        getline(ss, field, ',');
        sme.LatePayments = stoi(field);

        smes.push_back(sme);
    }

    return smes;
}