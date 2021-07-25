#include "threads.h"

#define NUM_OF_THREADS 10
  
int main()
{

	call_I_Love_Threads();
 
	std::vector<int> primes1;
	getPrimes(58, 100, primes1);
	printVector(primes1);
	printVector(callGetPrimes(58, 100));

	std::cout << NUM_OF_THREADS << " threads are running " << std::endl;
	callWritePrimesMultipleThreads(0, 10000, "primes_no_sync.txt", NUM_OF_THREADS);
	callWritePrimesMultipleThreads_mtx(0, 10000, "primes_sync.txt", NUM_OF_THREADS);

	callWritePrimesMultipleThreadsEff(0, 10000, "primes2_no_sync.txt", NUM_OF_THREADS);
	callWritePrimesMultipleThreadsEff_mtx(0, 10000, "primes2_sync.txt", NUM_OF_THREADS);

	//callWritePrimesMultipleThreads(0, 1000000, "primes2.txt", NUM_OF_THREADS);
    //================================================================================

	//std::cout << "\nOnly one thread is running " << std::endl;
	//callWritePrimesMultipleThreads(0, 1000, "primes2.txt", 1);
	callWritePrimesMultipleThreads(0, 10000, "primes_1.txt", 1);
	callWritePrimesMultipleThreadsEff(0, 10000, "primes_eff_1.txt", 1);
	//callWritePrimesMultipleThreads(0, 1000000, "primes2.txt", 1);


	//system("pause");
	//getchar();
	return 0;
}