#ifndef ARITHMETIC_OPERATION_HPP_
# define ARITHMETIC_OPERATION_HPP_

# include <string_view>
# include <string>

namespace arithm_op
{
    std::string add(std::string_view s, std::string_view s2);
    std::string sub(std::string_view s, std::string_view s2);
    std::string mult(std::string_view s, std::string_view s2);
    std::string div(std::string_view s, std::string_view s2);
    std::string mod(std::string_view s, std::string_view s2);
}

#endif
