#include <type_traits>

//defaultErrorCode is just so this class can have a default constructor
template<class TValue, class TError, class TMessage, TError defaultErrorCode>
class Errorable {
    static_assert(std::is_default_constructible<TValue>(), "TValue must have a default constructor");
    static_assert(std::is_enum<TError>(), "TError must be an enum or enum class");
    static_assert(std::is_default_constructible<TValue>(), "TMessage must have a default constructor");

    TValue value_;
    TError errorCode_;
    std::string errorMessage_;
    bool hasValue_;

public:
    //if the class has a value
    constexpr bool hasValue() const {
        return hasValue_;
    }

    //returns value if hasValue, else default
    constexpr TValue getValue(TValue default_) const {
        return hasValue_ ? value_ : default_;
    }

    //returns errorCode if !hasValue else default
    constexpr TError getErrorCode(TError default_) const {
        return !hasValue_ ? errorCode_ : default_;
    }

    //returns errorCode if !hasValue else default
    constexpr TMessage getErrorMessage(TMessage default_) const {
        return !hasValue_ ? errorMessage_ : default_;
    }

    constexpr void setValue(TValue value) {
        value_ = value;
        hasValue_ = true;
    }

    constexpr void setError(TError errorCode, TMessage errorMessage = "") {
        errorCode_ = errorCode;
        errorMessage_ = errorMessage;
    }

    constexpr Errorable(TValue value) : value_{value}, hasValue_{true} {}
    constexpr Errorable(TError errorCode, TMessage errorMessage = "") : errorCode_{errorCode}, errorMessage_{errorMessage}, hasValue_{false} {}
    constexpr Errorable() : errorCode_{defaultErrorCode}, errorMessage_{""}, hasValue_{false} {}
};