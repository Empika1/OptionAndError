#include <type_traits>

template<class T>
class Option {
    static_assert(std::is_default_constructible<T>(), "T must have a default constructor");

    T value;
    bool hasValue;

public:
    bool has() const {
        return hasValue;
    }

    //returns value if has, else default
    T get(T default_) const {
        return hasValue ? value : default_;
    }

    void set(T value_) {
        value = value_;
        hasValue = true;
    }

    void empty() {
        hasValue = false;
    }

    Option(T value_) : value{value_}, hasValue{true} {}
    Option() : hasValue{false} {}
};