#ifndef REVERSE_POLISH_NOTATION_HPP_
# define REVERSE_POLISH_NOTATION_HPP_

# include <list>
# include <stack>
# include <string_view>
# include <string>
# include <utility>
# include <cctype>
# include <cassert>

# include "utils.hpp"

namespace rpn
{
    std::list<std::string_view> to_rpn(std::string_view line);

    template <typename t_arithmetic_operations>
    std::string rpn_evaluate(
        const t_arithmetic_operations& operations,
        const std::list<std::string_view>& rpn_expression)
    {
        assert(!rpn_expression.empty());

        std::stack<std::string> numbers;

        for (const auto& s : rpn_expression)
        {
            if (isdigit(s[0])
                || (s.length() > 1 && s[0] == '-' && isdigit(s[1])))
            {
                numbers.emplace(s);
                continue;
            }

            std::string operand_1;
            std::string operand_2;

            operand_2 = std::move(numbers.top());
            numbers.pop();
            operand_1 = std::move(numbers.top());
            numbers.pop();

            std::string operation_res;

            if (s[0] == '+')
            {
                operation_res = operations.add(
                    operand_1, operand_2);
            }
            else if (s[0] == '-')
            {
                operation_res = operations.sub(
                    operand_1, operand_2);
            }
            else if (s[0] == '*')
            {
                operation_res = operations.mult(
                    operand_1, operand_2);
            }
            else if (s[0] == '/')
            {
                operation_res = operations.div(
                    operand_1, operand_2);
            }
            else
            {
                operation_res = operations.mod(
                    operand_1, operand_2);
            }

            numbers.emplace(std::move(operation_res));
        }

        assert(numbers.size() == 1);

        return utils::ease_number(numbers.top());
    }
}

#endif
