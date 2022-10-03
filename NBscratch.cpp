//
// naive_bayes.cpp
//ML-AS2
// created by Atmin Sheth on 9/29/2022
///
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include<cmath>
#include<chrono>
#include <string>
using namespace std;
using namespace std::chrono;

typedef struct class_summary
{
  std::vector<std::vector<float>> Mean_Stdev;
  float class_prob;

} class_summary;
double mean(vector<double> v);
double sum(vector<double> v);
double calc_prob(double value, double mean, double stdev);
class_summary calc_class_summary(vector<vector<float>> dataset, float class_label);
double stDev(vector<double>& data);
double variance(vector<double> data);
double cond_prob(vector<double> dataset, double val, vector<double> dataT, double target, double probTarget);
double quant_prob(double v, double mean, double var);

int main(int argc, const char* argv[])
{
  ifstream inFS;
  string line;
  string string1_in, pclass_in, survived_in, sex_in, age_in;
  const int MAX_LEN = 1500;
  vector<string> string1;
  vector<double> pclass(MAX_LEN);
  vector<double> survived(MAX_LEN);
  vector<double> sex(MAX_LEN);
  vector<double> age(MAX_LEN);

  vector<double> weight(1, 1);
  vector<double> label(MAX_LEN);


  //label = survived -1;


 // labels <- as.integer(train$ESR) - 1

 /* If so, I think the formula is simple o/p = (weights.T)* (X_train) + (bias) . For simplicity ignore the bias term for now. During training apply a sigmoid = 1/(1 + math.exp(x)) function on the o/p and pass it to the loss function. Use this loss value in the weight update function (should have been taught in class) to update your weights.
  */

  /*if(pred>0.5)
   pred=1;
   else
   pred=0;
   cout<<"The class predicted by the model= "<<pred;*/

  cout << "Opening file titanic_project.csv." << endl;

  inFS.open("/Users/saiharshithagonuguntla/Downloads/cs4375/naive_Bayes/naive_Bayes/titanic_project.csv");
  if (!inFS.is_open()) {
    cout << "Could not open file titanic_project.csv." << endl;
    return 1;
  }

  cout << "Reading line 1" << endl;
  getline(inFS, line);

  cout << "heading:" << line << endl;

  int numObservations = 0;
  while (inFS.good()) {
    getline(inFS, string1_in, ',');
    getline(inFS, pclass_in, ',');
    getline(inFS, survived_in, ',');
    getline(inFS, sex_in, ',');
    getline(inFS, age_in, '\n');


    //  string1.at(numObservations) = stof(string1_in);
    pclass.at(numObservations) = stof(pclass_in);
    survived.at(numObservations) = stof(survived_in);
    sex.at(numObservations) = stof(sex_in);
    age.at(numObservations) = stof(age_in);

    numObservations++;
  }

  //string1.resize(numObservations);
  vector<double> test_surv(survived.begin() + 801, survived.end());
  vector<double> test_pc(pclass.begin() + 801, pclass.end());
  vector<double> test_age(age.begin() + 801, age.end());
  vector<double> test_sex(sex.begin() + 801, sex.end());
  pclass.resize(800);
  survived.resize(800);
  sex.resize(800);
  age.resize(800);
  cout << "new length " << survived.size() << endl;
  //cout<< "no. of columns" << survived[0].size();

  cout << "Closing file titanic_project.csv." << endl;
  inFS.close();

  cout << "Number of records: " << numObservations << endl;

  auto start = high_resolution_clock::now();
  double s1 = 0;
  for (double d : survived)
  {
    if (d == 1)
       s1++;
  }
  double prob_Survive = s1 / (survived.size());
  double prob_Nsurvive = 1 - prob_Survive;
  cout << "Call::" << endl << "naiveBayes.default(x=x,y=y,lapace-lapace)" << endl;
  cout << "A-prior probilities: " << endl << "Y" << endl << "0     1" << endl << prob_Nsurvive << "     "
    <<prob_Survive<<endl;
    
//sex
double FS = cond_prob(sex, 0, survived, 1, prob_Survive);
double MS = cond_prob(sex, 1, survived, 1, prob_Survive);
double fNS= cond_prob(sex, 0, survived, 0, prob_Nsurvive);
double mNS = cond_prob(sex, 1, survived, 0, prob_Nsurvive);
    
  //formating
cout << "Female   male" << endl;
cout << "0  " << fNS << "   " << mNS << endl;
cout << "1  " << FS << "    " << MS << endl;

//pclass

double csurvied[3];
double cNotsurv[3];
for (int i = 0; i < 3; i++)
{
  csurvied[i] = cond_prob(pclass, i + 1, survived, 1, prob_Survive);
  cNotsurv[i] = cond_prob(pclass, i + 1, survived, 0, prob_Nsurvive);
}

  //formating
cout << "p class" << endl << "y    1      2      3" << endl;
cout << "1     " ;
for (int i = 0; i < 3; i++)
{
  cout << cond_prob(pclass, i + 1, survived, 1, prob_Survive) << " ";
}
cout << endl << "0   ";
for (int i = 0; i < 3; i++)
{
  cout << cond_prob(pclass, i + 1, survived, 0, prob_Nsurvive) << " ";
}
cout << endl;
//age
vector<double> survA;
vector<double> notSurvA;

for (int i = 0; i < age.size(); i++)
{
  if (survived.at(i) == 1)
    survA.push_back(age.at(i));
  else
    notSurvA.push_back(age.at(i));
}
    
double meanAgeS = mean(survA);
double varAgeS = variance(survA);
double meanAgeNS = mean(notSurvA);
double varAgeNS = variance(notSurvA);
double prob_ageS = quant_prob(survA.size(), meanAgeS, varAgeS);
double prob_ageNS = quant_prob(notSurvA.size(), meanAgeNS, varAgeNS);
 
/*
  //formating
cout << "age " << endl << "y " << "[,1]   [,2]" << endl;
cout << "0  " << meanAgeNS << "  " << stAgeNS << endl;
cout << "1  " << meanAgeS << "  " << stAgeS << endl;
*/
  auto stop = high_resolution_clock::now();

  std::chrono::duration<double> elapsed_sec = stop - start;
  cout << "Time:" << elapsed_sec.count() << endl;
  //do the testing

  cout << "\nProgram terminated.";

  return 0;

}



double sum(vector<double> v)
{
  double s = 0;
  for (double d : v)
    s += d;
  return s;
}

double mean(vector<double> v)
{
  return sum(v) / v.size();
}

double variance(vector<double> data)
{
  double m = mean(data);
  double sqr = 0;
  for (int i = 0; i < data.size(); i++)
  {
    sqr += pow(data.at(i) - m, 2);
  }
  return  sqr /data.size();
  
}
double stDev(vector<double>& data)
{
  return sqrt(variance(data));
}

double quant_prob(double v, double mean, double var)
{
  return (1 / sqrt(2 * 3.14 * var)) * exp(-((pow(v - mean, 2) / (2 * var))));
}

double cond_prob(vector<double> dataset, double val,vector<double> dataT, double target, double probTarget)
{
  double tot = 0;
  double count = 0;
  for (int i = 0; i < dataset.size(); i++)
  {
    if (dataset.at(i) == val)
    {
      tot++;
    //  cout << dataT.at(i) << endl;
      
      if (dataT.at(i) == target)
      {
        count++;
      }

    }
  }
  double p = count/dataset.size();
  return( p/probTarget);
}

