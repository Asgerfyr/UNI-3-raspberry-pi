#include <mutex>


class scoped_lock{
    public:
        scoped_lock(std::mutex& mutex):mutex_(&mutex) {mutex.lock();};
        ~scoped_lock(){mutex_->unlock();};

    private:
    std::mutex* mutex_;
};