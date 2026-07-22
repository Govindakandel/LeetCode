
class H2O {
private :
 mutex mtx ;
 condition_variable cv ;
 int count=0; 

public:
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
     unique_lock<mutex> lock(mtx);
     while(count==2){
        cv.wait(lock);
     }
     releaseHydrogen();
     count++;
     cv.notify_all();

    }
    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(mtx);
        while(count < 2) {
            cv.wait(lock);
        }
        releaseOxygen();
        count=0; 
        cv.notify_all();
    }
};