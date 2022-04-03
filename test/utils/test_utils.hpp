#ifndef TEST_UTILS_HPP_
# define TEST_UTILS_HPP_

# define EXPECT_THROW_MSG(statement, exception_type, expected_msg) \
    do                                                             \
    {                                                              \
        try                                                        \
        {                                                          \
            statement;                                             \
            FAIL() << "expected " << #exception_type;              \
        }                                                          \
        catch (const exception_type& e)                            \
        {                                                          \
            EXPECT_STREQ(e.what(), expected_msg);                  \
        }                                                          \
    }                                                              \
    while (0)


#endif
