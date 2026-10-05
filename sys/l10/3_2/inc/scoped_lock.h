#include <mutex>


class scoped_lock{
    public:
        scoped_lock(){mutex_.lock();};
        ~scoped_lock(){mutex_.unlock();};

    private:
    static inline std::mutex mutex_;
};