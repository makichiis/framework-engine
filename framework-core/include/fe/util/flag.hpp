#ifndef FE_UTIL_FLAG_HPP
#define FE_UTIL_FLAG_HPP

namespace fe {

template <class StateChangeCallback>
struct Flag {
private:
    bool flag_;
    StateChangeCallback cb; 

public:
    Flag(StateChangeCallback p_cb) : cb{ p_cb } {}

    bool operator=(bool other) {
        flag_ = other;
        cb(flag_);

        return flag_;
    }

    operator bool() {
        return flag_;
    }
};

}

#endif 