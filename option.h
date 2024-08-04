#include <type_traits>

template<class T>
class Option {
    static_assert(std::is_default_constructible<T>(), "T must have a default constructor");

    T value;
    bool hasValue;

public:
    constexpr bool has() const {
        return hasValue;
    }

    //returns value if has, else default
    constexpr T get(T default_) const {
        return hasValue ? value : default_;
    }

    constexpr void set(T value_) {
        value = value_;
        hasValue = true;
    }

    constexpr void empty() {
        hasValue = false;
    }

    constexpr Option(T value_) : value{value_}, hasValue{true} {}
    constexpr Option() : hasValue{false} {}
};