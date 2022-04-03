#ifndef UTILS_HPP_
# define UTILS_HPP_

# include <string_view>
# include <string>

namespace utils
{
    inline constexpr const char *WHITESPACES = " \t";

    constexpr bool is_operator(char c) noexcept
    {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
    }

    constexpr char to_char(int i) noexcept
    {
        return i >= 0 && i <= 9 ? i + 48 : 0;
    }

    constexpr int to_digit(char c) noexcept
    {
        return c >= '0' && c <= '9' ? c - 48 : 0;
    }

    std::string ease_number(std::string_view s);
}

#endif
