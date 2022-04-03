#include <list>
#include <utility>
#include <cctype>
#include <cassert>

#include "utils.hpp"
#include "custom_exceptions.hpp"
#include "arithmetic_operation.hpp"

namespace arithm_op
{
    namespace
    {
        std::string to_s(std::string_view s)
        {
            return std::string(s.data(), s.length());
        }

        std::string_view to_sv(const std::string& s) noexcept
        {
            return std::string_view(s);
        }

        std::string to_str(const std::list<char>& l)
        {
            assert(!l.empty());

            std::string s;

            s.reserve(l.size());

            for (auto c : l)
            {
                s.push_back(c);
            }

            return s;
        }

        std::string to_str(const std::list<std::string>& l)
        {
            assert(!l.empty());

            std::string s;

            s.reserve(l.size());

            for (const auto& s2 : l)
            {
                for (auto c : s2)
                {
                    s.push_back(c);
                }
            }

            return s;
        }

        bool less_equal(std::string_view s, std::string_view s2) noexcept
        {
            assert(!s.empty() && !s2.empty());

            size_t s_size = s.size();
            size_t s2_size = s2.size();

            if (s_size == s2_size)
            {
                for (uint32_t n = 0; n < s_size; ++n)
                {
                    if (s[n] < s2[n])
                    {
                        return true;
                    }
                    else if (s[n] > s2[n])
                    {
                        return false;
                    }
                }

                return true;
            }
            else if (s_size < s2_size)
            {
                return true;
            }

            return false;
        }

        bool greater_equal(std::string_view s, std::string_view s2) noexcept
        {
            assert(!s.empty() && !s2.empty());

            size_t s_size = s.size();
            size_t s2_size = s2.size();

            if (s_size == s2_size)
            {
                for (uint32_t n = 0; n < s_size; ++n)
                {
                    if (s[n] > s2[n])
                    {
                        return true;
                    }
                    else if (s[n] < s2[n])
                    {
                        return false;
                    }
                }

                return true;
            }
            else if (s_size > s2_size)
            {
                return true;
            }

            return false;
        }

        std::list<char> _add(std::string_view s, std::string_view s2)
        {
            assert(!s.empty() && !s2.empty());

            std::list<char> add_res;
            int n = s.size() - 1;
            int n2 = s2.size() - 1;
            int carry = 0;

            while (n >= 0 && n2 >= 0)
            {
                int digit = utils::to_digit(s[n--]);
                int digit2 = utils::to_digit(s2[n2--]);
                int digit_sum_res = digit + digit2;

                add_res.emplace_front(
                    utils::to_char((digit_sum_res + carry) % 10));
                carry = (digit_sum_res + carry) / 10;
            }

            while (n >= 0)
            {
                int digit = utils::to_digit(s[n--]);

                add_res.emplace_front(utils::to_char((digit + carry) % 10));
                carry = (digit + carry) / 10;
            }

            while (n2 >= 0)
            {
                int digit = utils::to_digit(s2[n2--]);

                add_res.emplace_front(utils::to_char((digit + carry) % 10));
                carry = (digit + carry) / 10;
            }

            if (carry > 0)
            {
                add_res.emplace_front(utils::to_char(carry));
            }

            return add_res;
        }

        std::list<char> _sub(std::string_view s, std::string_view s2)
        {
            assert(!s.empty() && !s2.empty());

            std::list<char> sub_res;
            int n = s.size() - 1;
            int n2 = s2.size() - 1;
            int carry = 0;

            while (n >= 0 && n2 >= 0)
            {
                int digit = utils::to_digit(s[n--]);
                int digit2 = utils::to_digit(s2[n2--]);
                int digit_sub_res = digit - (digit2 + carry);

                if (digit_sub_res < 0)
                {
                    digit_sub_res = (digit + 10) - (digit2 + carry);
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }

                sub_res.emplace_front(utils::to_char(digit_sub_res));
            }

            while (n >= 0)
            {
                int digit = utils::to_digit(s[n--]);
                int digit_sub_res = digit - carry;

                if (digit_sub_res < 0)
                {
                    digit_sub_res = (digit + 10) - carry;
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }

                sub_res.emplace_front(utils::to_char(digit_sub_res));
            }

            return sub_res;
        }

        std::list<char> _mult(std::string_view s, std::string_view s2)
        {
            assert(!s.empty() && !s2.empty());

            std::list<std::list<char>> mults_ress;
            uint32_t padding = 0;
            int n = s2.size() - 1;

            while (n >= 0)
            {
                std::list<char> mult_res;
                int digit2 = utils::to_digit(s2[n--]);
                int carry = 0;

                for (uint32_t n2 = 0; n2 < padding; ++n2)
                {
                    mult_res.emplace_front('0');
                }

                for (int n2 = s.size() - 1; n2 >= 0; --n2)
                {
                    int digit = utils::to_digit(s[n2]);
                    int digit_mult_res = digit * digit2;

                    mult_res.emplace_front(
                        utils::to_char((digit_mult_res + carry) % 10));
                    carry = (digit_mult_res + carry) / 10;
                }

                if (carry > 0)
                {
                    mult_res.emplace_front(utils::to_char(carry));
                }

                mults_ress.emplace_back(std::move(mult_res));
                ++padding;
            }

            std::list<char> res {'0'};

            for (const auto& mult_res : mults_ress)
            {
                res = _add(to_str(res), to_str(mult_res));
            }

            return res;
        }

        std::pair<std::list<std::string>, std::string> _div(
            std::string_view s, std::string_view s2)
        {
            assert(!s.empty() && !s2.empty());

            auto compute = [](
                std::string_view nb_to_substract, std::string_view divisor)
                -> std::pair<std::string, std::string>
            {
                std::string quotient_part = "0";
                std::string second_nb = to_s(divisor);
                std::string old_second_nb;

                do
                {
                    quotient_part = add(quotient_part, "1");
                    old_second_nb = std::move(second_nb);
                    second_nb = add(old_second_nb, divisor);
                }
                while (less_equal(second_nb, nb_to_substract));

                return {std::move(quotient_part), sub(
                    nb_to_substract, old_second_nb)};
            };
            std::list<std::string> quotient_parts;
            std::string rest;
            uint32_t n = 0;

            while (n < s.size())
            {
                auto nb_to_substract = s.substr(0, n++ + 1);

                if (less_equal(s2, nb_to_substract))
                {
                    auto [quotient_part, sub_res] = compute(
                        nb_to_substract, s2);

                    quotient_parts.emplace_back(std::move(quotient_part));
                    rest = std::move(sub_res);
                    break;
                }
            }

            if (rest.empty())
            {
                return {{"0"}, to_s(s)};
            }

            while (n < s.size())
            {
                rest.push_back(s[n++]);

                if (rest[0] == '0')
                {
                    rest = utils::ease_number(rest);
                }

                if (less_equal(s2, rest))
                {
                    auto [quotient_part, sub_res] = compute(rest, s2);

                    quotient_parts.emplace_back(std::move(quotient_part));
                    rest = std::move(sub_res);
                }
                else
                {
                    quotient_parts.emplace_back("0");
                }
            }

            return {std::move(quotient_parts), std::move(rest)};
        }
    }

    std::string add(std::string_view s, std::string_view s2)
    {
        assert(!s.empty() && !s2.empty());

        std::string eased_s = utils::ease_number(s);
        std::string eased_s2 = utils::ease_number(s2);
        std::list<char> add_res;
        bool should_negative = false;

        if (eased_s[0] == '-' && eased_s2[0] != '-')
        {
            auto eased_s_no_dash = to_sv(eased_s).substr(1);

            if (greater_equal(eased_s_no_dash, eased_s2))
            {
                add_res = _sub(eased_s_no_dash, eased_s2);
                should_negative = true;
            }
            else
            {
                add_res = _sub(eased_s2, eased_s_no_dash);
            }
        }
        else if (eased_s[0] != '-' && eased_s2[0] == '-')
        {
            auto eased_s2_no_dash = to_sv(eased_s2).substr(1);

            if (greater_equal(eased_s, eased_s2_no_dash))
            {
                add_res = _sub(eased_s, eased_s2_no_dash);
            }
            else
            {
                add_res = _sub(eased_s2_no_dash, eased_s);
                should_negative = true;
            }
        }
        else if (eased_s[0] == '-' && eased_s2[0] == '-')
        {
            add_res = _add(
                to_sv(eased_s).substr(1), to_sv(eased_s2).substr(1));
            should_negative = true;
        }
        else
        {
            add_res = _add(eased_s, eased_s2);
        }

        if (should_negative)
        {
            add_res.emplace_front('-');
        }

        return utils::ease_number(to_str(add_res));
    }

    std::string sub(std::string_view s, std::string_view s2)
    {
        assert(!s.empty() && !s2.empty());

        std::string eased_s = utils::ease_number(s);
        std::string eased_s2 = utils::ease_number(s2);
        std::list<char> sub_res;
        bool should_negative = false;

        if (eased_s[0] == '-' && eased_s2[0] != '-')
        {
            sub_res = _add(to_sv(eased_s).substr(1), eased_s2);
            should_negative = true;
        }
        else if (eased_s[0] != '-' && eased_s2[0] == '-')
        {
            sub_res = _add(eased_s, to_sv(eased_s2).substr(1));
        }
        else if (eased_s[0] == '-' && eased_s2[0] == '-')
        {
            auto eased_s_no_dash = to_sv(eased_s).substr(1);
            auto eased_s2_no_dash = to_sv(eased_s2).substr(1);

            if (greater_equal(eased_s_no_dash, eased_s2_no_dash))
            {
                sub_res = _sub(eased_s_no_dash, eased_s2_no_dash);
                should_negative = true;
            }
            else
            {
                sub_res = _sub(eased_s2_no_dash, eased_s_no_dash);
            }
        }
        else
        {
            if (greater_equal(eased_s, eased_s2))
            {
                sub_res = _sub(eased_s, eased_s2);
            }
            else
            {
                sub_res = _sub(eased_s2, eased_s);
                should_negative = true;
            }
        }

        if (should_negative)
        {
            sub_res.emplace_front('-');
        }

        return utils::ease_number(to_str(sub_res));
    }

    std::string mult(std::string_view s, std::string_view s2)
    {
        assert(!s.empty() && !s2.empty());

        std::string eased_s = utils::ease_number(s);
        std::string eased_s2 = utils::ease_number(s2);
        std::list<char> mult_res;
        bool should_negative = false;

        if (eased_s[0] == '-' && eased_s2[0] != '-')
        {
            mult_res = _mult(to_sv(eased_s).substr(1), eased_s2);
            should_negative = true;
        }
        else if (eased_s[0] != '-' && eased_s2[0] == '-')
        {
            mult_res = _mult(eased_s, to_sv(eased_s2).substr(1));
            should_negative = true;
        }
        else if (eased_s[0] == '-' && eased_s2[0] == '-')
        {
            mult_res = _mult(
                to_sv(eased_s).substr(1), to_sv(eased_s2).substr(1));
        }
        else
        {
            mult_res = _mult(eased_s, eased_s2);
        }

        if (should_negative)
        {
            mult_res.emplace_front('-');
        }

        return utils::ease_number(to_str(mult_res));
    }

    std::string div(std::string_view s, std::string_view s2)
    {
        assert(!s.empty() && !s2.empty());

        std::string eased_s = utils::ease_number(s);
        std::string eased_s2 = utils::ease_number(s2);

        if (eased_s2[0] == '0')
        {
            throw custom_exceptions::arithmetic_error(
                "attempted to divide by zero");
        }

        std::list<std::string> quotient_parts;
        bool should_negative = false;

        if (eased_s[0] == '-' && eased_s2[0] != '-')
        {
            quotient_parts = std::move(
                _div(to_sv(eased_s).substr(1), eased_s2).first);
            should_negative = true;
        }
        else if (eased_s[0] != '-' && eased_s2[0] == '-')
        {
            quotient_parts = std::move(
                _div(eased_s, to_sv(eased_s2).substr(1)).first);
            should_negative = true;
        }
        else if (eased_s[0] == '-' && eased_s2[0] == '-')
        {
            quotient_parts = std::move(_div(
                to_sv(eased_s).substr(1), to_sv(eased_s2).substr(1)).first);
        }
        else
        {
            quotient_parts = std::move(_div(eased_s, eased_s2).first);
        }

        if (should_negative)
        {
            quotient_parts.emplace_front("-");
        }

        return utils::ease_number(to_str(quotient_parts));
    }

    std::string mod(std::string_view s, std::string_view s2)
    {
        assert(!s.empty() && !s2.empty());

        std::string eased_s = utils::ease_number(s);
        std::string eased_s2 = utils::ease_number(s2);

        if (eased_s2[0] == '0')
        {
            throw custom_exceptions::arithmetic_error(
                "attempted to modulo by zero");
        }

        auto eased_s2_no_dash = (eased_s2[0] == '-') ?
            to_sv(eased_s2).substr(1) : to_sv(eased_s2);
        std::string rest;
        bool should_negative = false;

        if (eased_s[0] == '-')
        {
            rest = std::move(_div(
                to_sv(eased_s).substr(1), eased_s2_no_dash).second);
            should_negative = true;
        }
        else
        {
            rest = std::move(_div(eased_s, eased_s2_no_dash).second);
        }

        if (should_negative)
        {
            rest.insert(0, "-");
        }

        return utils::ease_number(rest);
    }
}
