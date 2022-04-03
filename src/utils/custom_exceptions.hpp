#ifndef CUSTOM_EXCEPTIONS_HPP_
# define CUSTOM_EXCEPTIONS_HPP_

# include <stdexcept>

namespace custom_exceptions
{
    class parsing_error : public std::logic_error
    {
    public :
        using std::logic_error::logic_error;
        using std::logic_error::what;
    };

    class arithmetic_error : public std::runtime_error
    {
    public :
        using std::runtime_error::runtime_error;
        using std::runtime_error::what;
    };
}

#endif
