#include "utils.hpp"

namespace utils
{
    std::string ease_number(std::string_view s)
    {
        if (s.empty())
        {
            return "";
        }

        bool negative_nb = false;

        if (s[0] == '-')
        {
            s = s.substr(1);
            negative_nb = true;
        }

        uint32_t n = 0;

        while (n < s.size() && s[n] == '0')
        {
            ++n;
        }

        std::string eased_number;

        if (n == s.size())
        {
            if (s[n - 1] == '0')
            {
                negative_nb = false;
            }

            if (negative_nb)
            {
                eased_number.push_back('-');
            }

            eased_number.push_back(s[n - 1]);
        }
        else
        {
            if (negative_nb)
            {
                eased_number.push_back('-');
            }

            while (n < s.size())
            {
                eased_number.push_back(s[n++]);
            }
        }

        return eased_number;
    }
}
