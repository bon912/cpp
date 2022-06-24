#include <thread>
#include <iostream>


class thread_guard {
private:
    std::thread& t_;
    
public:
    thread_guard(std::thread& t) : t_(t) {}

    ~thread_guard() {
        if (t_.joinable()) {
            t_.join();
        }
    }

    thread_guard(thread_guard const&) = delete;

    thread_guard& operator=(thread_guard const&) = delete;
    
};

class T1 {
private:
    int i_;

public:
    T1(const int i) :i_(i) {
    } 
    
    void operator()() {
        std::cout << "Print from class T1" << std::endl;
    }
};


void print_function() {
    std::cout << "Print from function" << std::endl;

}

int main() {
    T1 t{1};

    std::thread t1(t);    
    std::thread t2(print_function);
    thread_guard tg1{t1};
    thread_guard tg2{t2};

    
    
}
