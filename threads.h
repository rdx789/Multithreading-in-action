#include <string>
#include <fstream>
#include <iostream>
#include <vector>


//void I_Love_Threads();
void call_I_Love_Threads();

//bool checkPrime(int num);//O (n)
//bool checkPrimeEff(int num);//O (sqrt n)
void getPrimes(int begin, int end, std::vector<int>& primes);//Eff
std::vector<int> callGetPrimes(int begin, int end); //added using thread
void printVector(std::vector<int> primes);
//void printVectorToFile(std::vector<int> primes, std::ofstream& file);//added for convinience
//std::vector<int> retGetPrimes(int begin, int end);//added
//void writePrimesToFile(int begin, int end, std::ofstream& file);
void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N);
void callWritePrimesMultipleThreads_mtx(int begin, int end, std::string filePath, int N);
void callWritePrimesMultipleThreadsEff(int begin, int end, std::string filePath, int N);
void callWritePrimesMultipleThreadsEff_mtx(int begin, int end, std::string filePath, int N);