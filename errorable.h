#include <string>
#include <type_traits>

//defaultErrorCode is just so this class can have a default constructor
template<class TValue, class TError, TError defaultErrorCode>
class Errorable {
    static_assert(std::is_default_constructible<TValue>(), "TValue must have a default constructor");
    static_assert(std::is_enum<TError>(), "TError must be an enum or enum class");

    TValue value_;
    TError errorCode_;
    std::string errorMessage_;
    bool hasValue_;

public:
    //if the class has a value
    bool hasValue() const {
        return hasValue_;
    }

    //returns value if hasValue, else default
    TValue getValue(TValue default_) const {
        return hasValue_ ? value_ : default_;
    }

    //returns errorCode if !hasValue else default
    TError getErrorCode(TError default_) const {
        return !hasValue_ ? errorCode_ : default_;
    }

    //returns errorCode if !hasValue else default
    std::string getErrorMessage(std::string default_) const {
        return !hasValue_ ? errorMessage_ : default_;
    }

    void setValue(TValue value) {
        value_ = value;
        hasValue_ = true;
    }

    void setError(TError errorCode, std::string errorMessage = "") {
        errorCode_ = errorCode;
        errorMessage_ = errorMessage;
    }

    Errorable(TValue value) : value_{value}, hasValue_{true} {}
    Errorable(TError errorCode, std::string errorMessage = "") : errorCode_{errorCode}, errorMessage_{errorMessage}, hasValue_{false} {}
    Errorable() : errorCode_{defaultErrorCode}, errorMessage_{""}, hasValue_{false} {}
};