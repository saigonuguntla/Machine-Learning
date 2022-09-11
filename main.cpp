//
//  main.cpp
//  MLAsn1
//
//  Created by Saiharshitha Gonuguntla on 9/10/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include<cmath>
using namespace std;

double sum(vector<double>);
double mean(vector<double>);
double median(vector<double>);
double range(vector<double>);
double covar(vector<double>, vector<double>);
void print_stats(vector<double>);
double cor(vector<double>, vector<double>);


int main(int argc, const char* argv[]) {
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);
    
    cout << "Opening file Boston.csv." << endl;
    
    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv." << endl;
        return 1;
    }
    
    cout << "Reading line 1" << endl;
    getline(inFS, line);
    
    cout << "heading:" << line << endl;
    
    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS,rm_in, ',');
        getline(inFS, medv_in, '\n');
                
        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);
        
        numObservations++;
    }
    
    rm.resize(numObservations);
    medv.resize(numObservations);
    
    cout << "new length " << rm.size() << endl;
    
    cout << "Closing file Boston.csv." << endl;
    inFS.close();
    
    cout << "Number of records: " << numObservations << endl;
    
    cout << "\nStats for rm" << endl;
    print_stats(rm);
    
    cout << "\nStats for medv" << endl;
    print_stats(medv);
    
    cout << "\n Covariance = " << covar(rm, medv) << endl;
    
    cout << "\n Correlation = " << cor(rm, medv) << endl;
   
    cout << "\nProgram terminated.";
    
    return 0;
    
}

//function that calculates the sum of values in the vector
double sum(vector<double> vect){
    double sum = 0;
    
    for (int i=0; i < vect.size(); i++)
        sum += vect[i];
    return sum;
}

//function that calculates the mean of values in the vector
double mean(vector<double> vect){
    double sum = 0;
    double mean;
    
    for (int i=0; i < vect.size(); i++)
        sum += vect[i];
    mean = sum/vect.size();
    
    return mean;
}

//function that calculates the median of values in the vector
double median(vector<double> vect){
    int size = vect.size();
    double median;
    
    sort(vect.begin(), vect.end());
    if (size%2==0){
        return(vect[size/2 -1]+vect[size/2])/2;
    }
    else {
        return vect[size/2];
    }

    return median;
}

//function that calculates the range of values in the vector
double range(vector<double> vect){
    double range = 0;
    
    sort(vect.begin(), vect.end());
    range=vect.back()-vect.front();
    
    return range;
}

//function that calculates the covariance of values in the vector
double covar(vector<double> rm, vector<double> medv)
{
    double sum = 0;
    double rm_mean = mean(rm);
    double medv_mean = mean(medv);
    
    for (int i=0; i<rm.size(); i++)
        sum = sum + (rm[i] - rm_mean) * (medv[i] - medv_mean);
    return sum/(rm.size()-1);
}

//function that calculates the correlation of values in the vector
double cor(vector<double> rm, vector<double> medv)
{
    double sum1 = 0;
    double sum2 = 0;
    double var = 0;
    
    double cov = covar(rm,medv);
    double rm_mean = mean(rm);
    double medv_mean = mean(medv);

    for (int i=0; i<rm.size(); i++){
        sum1 = sum1 + pow((rm[i] - rm_mean),2);
    }
    
    for (int i=0; i<medv.size(); i++){
        sum2 = sum2 + pow((medv[i] - medv_mean),2);
    }

    double s3=sum1/(rm.size()-1);
    double s4=sum2/(medv.size()-1);
    
    double s5= sqrt(s3);
    double s6= sqrt(s4);
   
    var = s5*s6;
    return cov/var;
}

void print_stats(vector<double> vect)
{
    cout << "Sum of numeric vector: " << sum(vect) << endl;
    cout << "Mean of numeric vector: " << mean(vect) << endl;
    cout << "Median of numeric vector: " << median(vect) << endl;
    cout << "Range of numeric vector: " << range(vect)<< endl;
    
}

