#include<mutex>
#include<condition_variable>

class Foo {
private :
       std::mutex  mtx ;
       std::condition_variable cv;
       bool run_third = false;
       bool run_second =false;
public:
    Foo()       {
        
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        unique_lock<mutex> lock(mtx);
        run_second = true;
        lock.unlock();
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock , [this] { return  (run_second); });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        run_third = true;
        lock.unlock();
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock , [this] { return  (run_third); });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        lock.unlock();
    }
};