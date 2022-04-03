#include <cctype>

#include "custom_exceptions.hpp"
#include "utils.hpp"

namespace parser
{
    void is_arithmetic_expression(std::string_view line)
    {
        if (line.empty())
        {
            throw custom_exceptions::parsing_error("empty line");
        }

        size_t pos = line.find_first_not_of(utils::WHITESPACES);

        if (pos == std::string_view::npos)
        {
            throw custom_exceptions::parsing_error(
                "empty arithmetic expression");
        }

        if (line[pos] == ')')
        {
            throw custom_exceptions::parsing_error(
                "arithmetic expression cannot start with closing parenthesis");
        }

        if (utils::is_operator(line[pos])
            && !(line[pos] == '-' && isdigit(line[pos + 1])))
        {
            throw custom_exceptions::parsing_error(
                "arithmetic expression cannot start with operator");
        }

        if (!(isdigit(line[pos])
              || (line[pos] == '-' && isdigit(line[pos + 1]))
              || line[pos] == '('))
        {
            throw custom_exceptions::parsing_error(
                "arithmetic expression cannot start with unknown character");
        }

        char previous_valid_char = '\0';
        uint32_t opening_parenthesis_nb = 0;

        while (1)
        {
            if (isdigit(line[pos])
                || (line[pos] == '-'
                    && isdigit(line[pos + 1])
                    && (utils::is_operator(previous_valid_char)
                        || previous_valid_char == '('
                        || previous_valid_char == '\0')))
            {
                do
                {
                    previous_valid_char = line[pos++];
                }
                while (pos < line.length() && isdigit(line[pos]));

                pos = line.find_first_not_of(utils::WHITESPACES, pos);

                if (pos == std::string_view::npos)
                {
                    break;
                }

                if (utils::is_operator(line[pos]) || line[pos] == ')')
                {
                    continue;
                }

                throw custom_exceptions::parsing_error("error after number");
            }
            else if (utils::is_operator(line[pos]))
            {
                previous_valid_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    throw custom_exceptions::parsing_error(
                        "arithmetic expression cannot end with operator");
                }

                if (line[pos] == '('
                    || isdigit(line[pos])
                    || (line[pos] == '-' && isdigit(line[pos + 1])))
                {
                    continue;
                }

                throw custom_exceptions::parsing_error("error after operator");
            }
            else if (line[pos] == '(')
            {
                ++opening_parenthesis_nb;
                previous_valid_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    throw custom_exceptions::parsing_error(
                        "arithmetic expression cannot end with"
                        " opening parenthesis");
                }

                if (isdigit(line[pos])
                    || (line[pos] == '-' && isdigit(line[pos + 1]))
                    || line[pos] == '(')
                {
                    continue;
                }

                throw custom_exceptions::parsing_error(
                    "error after opening parenthesis");
            }
            else if (line[pos] == ')')
            {
                if (opening_parenthesis_nb == 0)
                {
                    throw custom_exceptions::parsing_error(
                        "missing opening parenthesis");
                }

                --opening_parenthesis_nb;
                previous_valid_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    break;
                }

                if (utils::is_operator(line[pos]) || line[pos] == ')')
                {
                    continue;
                }

                throw custom_exceptions::parsing_error(
                    "error after closing parenthesis");
            }
        }

        if (opening_parenthesis_nb > 0)
        {
            throw custom_exceptions::parsing_error(
                "missing closing parenthesis");
        }
    }
}
