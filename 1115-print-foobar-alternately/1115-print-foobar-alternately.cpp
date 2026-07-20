class FooBar {
private:
   std::mutex mtx;
   std::condition_variable cv;
 // first run = false , run foo()  set to true
// first run = true , run bar()  set to false
    bool first_run =  false ;
    int n;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock , [this]{ return !(first_run) ;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            // set the bool var 
            first_run = true;
            lock.unlock();
            cv.notify_all();

        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock , [this]{ return (first_run) ;});
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            // reset the bool var 
            first_run = false;
            lock.unlock();
            cv.notify_all();
        }
    }
};