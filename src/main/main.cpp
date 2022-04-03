#include <list>
#include <string>
#include <iostream>

#include "custom_exceptions.hpp"
#include "arithmetic_expression_parser.hpp"
#include "reverse_polish_notation.hpp"
#include "arithmetic_operation.hpp"

constexpr const char *get_authors() noexcept { return "xyyyt"; }

void start_calculator()
{
    struct arithmetic_operations
    {
        std::string add(std::string_view s, std::string_view s2) const
        {
            return arithm_op::add(s, s2);
        }

        std::string sub(std::string_view s, std::string_view s2) const
        {
            return arithm_op::sub(s, s2);
        }

        std::string mult(std::string_view s, std::string_view s2) const
        {
            return arithm_op::mult(s, s2);
        }

        std::string div(std::string_view s, std::string_view s2) const
        {
            return arithm_op::div(s, s2);
        }

        std::string mod(std::string_view s, std::string_view s2) const
        {
            return arithm_op::mod(s, s2);
        }
    };

    std::cout << "Large integral number calculator made by \""
              << get_authors()
              << "\".\nType \"quit\" if you want to stop program.\n"
              << std::endl;

    constexpr const char *PROMPT = "?>";
    arithmetic_operations operations;
    std::string line;

    while (1)
    {
        std::cout << PROMPT << " " << std::flush;
        std::getline(std::cin, line);

        if (line.empty())
        {
            continue;
        }
        else if (line == "quit")
        {
            break;
        }

        try
        {
            parser::is_arithmetic_expression(line);

            std::list<std::string_view> rpn_expression = rpn::to_rpn(line);
            std::string res = rpn::rpn_evaluate(operations, rpn_expression);

            std::cout << res << std::endl;
        }
        catch (const custom_exceptions::parsing_error&)
        {
            //std::cerr << e.what() << '\n';
            std::cerr << "syntax error" << std::endl;
        }
        catch (const custom_exceptions::arithmetic_error& e)
        {
            std::cerr << "arithmetic error : " << e.what() << std::endl;
        }
    }
}

int main()
{
    try
    {
        start_calculator();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    catch (...)
    {
        std::cerr << "unknown caught exception\n";
        return -1;
    }

    return 0;
}
