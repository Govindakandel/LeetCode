#include<semaphore>

class H2O {
private :
 binary_semaphore oxygen_counter{0} ; // default to 0 , block upcoming oxy thread 
 counting_semaphore<2> hydrogen_counter{2}; 
 // max count of 2 for hydrogen  allow max 2 hydrogen thread then block unit oxy thread release it 
 int counter = 0; // count no of hydrogen

public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        hydrogen_counter.acquire(); // try to acquire  the space / get block 
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        counter++;
        if(counter==2) {
            oxygen_counter.release(); // allow new oxygen thread to run 

        }
    }

    void oxygen(function<void()> releaseOxygen) {
        oxygen_counter.acquire() ; // try to aquire the space / get block
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        counter=0;
        hydrogen_counter.release(2); // incr the  counter by 2 to allow 2 new hydrogen thread 
    }
};