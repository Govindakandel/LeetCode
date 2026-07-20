class ZeroEvenOdd {
private:
std::mutex mtx ;
std::condition_variable cv ;
int n;
bool run_zero = false ;
bool run_odd = false  ;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for( int i=0 ; i < n ; i++){
            std::unique_lock<std::mutex> lock(mtx) ;
            //  run when run_zero is false 
            cv.wait(lock , [this]{
                return !(run_zero) ;
            });
            // print zero 
            printNumber(0);
            // set run status 
            run_zero = true;
            lock.unlock();
            cv.notify_all();
        }
        
    }

    void odd(function<void(int)> printNumber) {
            for( int i=1 ; i <= n ; i+=2){
                std::unique_lock<std::mutex> lock(mtx) ;
                //  only run when zero  and even num are printed 
                cv.wait(lock , [this]{
                    return (run_zero && !(run_odd)) ;
                });
                // print odd num 
                printNumber(i);
                // reset zero_run status  and set run_odd status 
                run_zero = false;
                run_odd = true ;
                lock.unlock();
                cv.notify_all();
        }
        
    }

    void even(function<void(int)> printNumber) {
               for( int i=2 ; i <= n ; i+=2){
                std::unique_lock<std::mutex> lock(mtx) ;
                //  only run when zero  and odd num are printed 
                cv.wait(lock , [this]{
                    return (run_zero && run_odd) ;
                });
                // print even num 
                printNumber(i);
                // reset zero_run status 
                run_zero = false;
                // reset the run_odd  status
                run_odd = false ;
                lock.unlock();
                cv.notify_all();
        }
        
    }
};