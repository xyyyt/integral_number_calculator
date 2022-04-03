#include "utils.hpp"
#include "reverse_polish_notation.hpp"

namespace rpn
{
    std::list<std::string_view> to_rpn(std::string_view line)
    {
        assert(!line.empty());

        std::list<std::string_view> rpn_expression;
        std::stack<std::string_view> operators;
        char previous_char = '\0';
        size_t pos = line.find_first_not_of(utils::WHITESPACES);

        while (1)
        {
            if (isdigit(line[pos])
                || (line[pos] == '-'
                    && isdigit(line[pos + 1])
                    && (utils::is_operator(previous_char)
                        || previous_char == '('
                        || previous_char == '\0')))
            {
                size_t start = pos;

                do
                {
                    previous_char = line[pos++];
                }
                while (pos < line.length() && isdigit(line[pos]));

                rpn_expression.emplace_back(line.substr(start, pos - start));
                pos = line.find_first_not_of(utils::WHITESPACES, pos);

                if (pos == std::string_view::npos)
                {
                    break;
                }
            }
            else if (utils::is_operator(line[pos]))
            {
                auto operator_is_priority = [](char c, char c2) noexcept
                {
                    return (c == '*' || c == '/' || c == '%')
                        && (c2 == '+' || c2 == '-');
                };

                while (!operators.empty()
                       && operators.top()[0] != '('
                       && !operator_is_priority(line[pos], operators.top()[0]))
                {
                    rpn_expression.emplace_back(operators.top());
                    operators.pop();
                }

                operators.emplace(std::string_view(&line[pos], 1));
                previous_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    break;
                }
            }
            else if (line[pos] == '(')
            {
                operators.emplace(std::string_view(&line[pos], 1));
                previous_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    break;
                }
            }
            else if (line[pos] == ')')
            {
                while (!operators.empty() && operators.top()[0] != '(')
                {
                    rpn_expression.emplace_back(operators.top());
                    operators.pop();
                }

                if (!operators.empty() && operators.top()[0] == '(')
                {
                    operators.pop();
                }

                previous_char = line[pos];
                pos = line.find_first_not_of(utils::WHITESPACES, pos + 1);

                if (pos == std::string_view::npos)
                {
                    break;
                }
            }
        }

        while (!operators.empty())
        {
            auto operator_s = operators.top();

            operators.pop();

            if (operator_s[0] != '(')
            {
                rpn_expression.emplace_back(operator_s);
            }
        }

        return rpn_expression;
    }
}
