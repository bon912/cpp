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
    
    void operator()(const int value) {
        std::cout << "Print from class T1 value: " << value << std::endl;
    }
};

void print_function(const int value) {
    std::cout << "Print from function value: " << value << std::endl;

}

int main() {
    T1 t{1};

    t(1);
    
    std::thread t1(t, 11);
    std::thread t2(print_function, 22);
    thread_guard tg1{t1};
    thread_guard tg2{t2};       
}
