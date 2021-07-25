#include "threads.h"
#include <thread>  
#include <time.h>
#include <iomanip> 
#include <chrono> 
#include <mutex>

using std::cout;
using std::endl;
using std::vector;

std::mutex mtx;


void I_Love_Threads()
{
	cout << "I Love Threads" << endl;
}

void call_I_Love_Threads()
{
	std::thread t1(I_Love_Threads);
    t1.join();
}

// O(n)
bool checkPrime(int num)
{
	if (num <= 1)
		return false;

	for (int i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}

// O(sqrt n)
bool checkPrimeEff(int num)
{
	if (num <= 1)
		return false;

	int i = 2;
	while (i*i <= num)
	{
		if (num % i == 0)
			return false;

		i += 1;
	}
	return true;
}

void getPrimes(int begin, int end, vector<int>& primes)
{
	for (int i = begin; i <= end; i++)
	{
		if (checkPrimeEff(i))
		{
			primes.push_back(i);
		}
	}
}

std::vector<int> callGetPrimes(int begin, int end)
{
	std::vector<int> primes;
    
	std::thread t2(getPrimes, begin, end, std::ref(primes));
	t2.join();

	return primes;
} 

void printVector(std::vector<int> primes)
{
	for (vector<int>::const_iterator iter = primes.begin(); iter != primes.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

void printVectorToFile(vector<int> primes, std::ofstream& file)
{
	for (vector<int>::const_iterator iter = primes.begin(); iter != primes.end(); iter++)
	{
		file << *iter << " ";
	}
	file << endl;
}

void printVectorToFile_mtx(vector<int> primes, std::ofstream& file)
{
	mtx.lock();
	for (vector<int>::const_iterator iter = primes.begin(); iter != primes.end(); iter++)
	{
		file << *iter << " ";
	}
	file << endl;
	mtx.unlock();
}

void writePrimesToFile(int begin, int end, std::ofstream& file)
{
	for (int i = begin; i <= end; i++)
	{
		if (checkPrime(i))
			file << i << " ";
	}
	file << endl;
}

void writePrimesToFile_mtx(int begin, int end, std::ofstream& file)
{
	mtx.lock();
	for (int i = begin; i <= end; i++)
	{
		if (checkPrime(i))
			file << i << " ";
	}
	file << endl;
	mtx.unlock();
}

std::vector<int> retGetPrimes(int begin, int end)
{
	std::vector<int> primes;
    
	getPrimes(begin, end, primes);
	
	return primes;
}

uint64_t nanos()
{
    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
    return ns; 
} 

void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N)
{
	uint64_t s_nanos = nanos();
	int nslice = (end-begin)/N; 
	std::vector<std::thread> threads;
	std::vector<int> primes;
	std::ofstream out;
	out.open(filePath);
	
	for (int i = 0; i < N; i++ )
	{
        threads.push_back(std::thread(writePrimesToFile, i*nslice, (i+1)*nslice-1, std::ref(out)));
	}
	for (auto& th : threads) 
	{
        th.join();
    }
	out.close();
	uint64_t e_nanos = nanos();
	uint64_t diff_nanos = e_nanos - s_nanos;
	std::cout << diff_nanos / 1000000 << "   MilliSeconds  " << "Slow version " << N << " threads  " << std::endl;
}

void callWritePrimesMultipleThreads_mtx(int begin, int end, std::string filePath, int N)
{
	uint64_t s_nanos = nanos();
	int nslice = (end-begin)/N; 
	std::vector<std::thread> threads;
	std::vector<int> primes;
	std::ofstream out;
	out.open(filePath);
	
	for (int i = 0; i < N; i++ )
	{
        threads.push_back(std::thread(writePrimesToFile_mtx, i*nslice, (i+1)*nslice-1, std::ref(out)));
	}
	for (auto& th : threads) 
	{
        th.join();
    }
	out.close();
	uint64_t e_nanos = nanos();
	uint64_t diff_nanos = e_nanos - s_nanos;
	std::cout << diff_nanos / 1000000 << "   MilliSeconds  " << "Slow version w/mutex " << N << " threads  "  << std::endl;
}

void callWritePrimesMultipleThreadsEff(int begin, int end, std::string filePath, int N)
{
	uint64_t s_nanos = nanos();
	int nslice = (end-begin)/N; 
	std::vector<std::thread> threads;
	std::vector<int> primes;
	std::ofstream out;
	out.open(filePath);
	
	for (int i = 0; i < N; i++ )
	{
		primes = retGetPrimes((i*nslice), ((i+1)*nslice-1));
        threads.push_back(std::thread(printVectorToFile, primes, std::ref(out)));
	}
	for (auto& th : threads) 
	{
        th.join();
    }
	out.close();
	uint64_t e_nanos = nanos();
	uint64_t diff_nanos = e_nanos - s_nanos;
	std::cout << diff_nanos / 1000000 << "   MilliSeconds  " << "Efficient version " << N << " threads  " << std::endl;
}

void callWritePrimesMultipleThreadsEff_mtx(int begin, int end, std::string filePath, int N)
{
	uint64_t s_nanos = nanos();
	double seconds;
	int nslice = (end-begin)/N; 
	std::vector<std::thread> threads;
	std::vector<int> primes;
	std::ofstream out;
	out.open(filePath);
	
	for (int i = 0; i < N; i++ )
	{
		primes = retGetPrimes((i*nslice), ((i+1)*nslice-1));
        threads.push_back(std::thread(printVectorToFile_mtx, primes, std::ref(out)));
	}
	for (auto& th : threads) 
	{
        th.join();
    }
	out.close();
	uint64_t e_nanos = nanos();
	uint64_t diff_nanos = e_nanos - s_nanos;
	std::cout << diff_nanos / 1000000 << "   MilliSeconds  " << "Efficient version w/mutex " << N << " threads  " << std::endl;
}