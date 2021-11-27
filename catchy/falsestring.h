#ifndef CATCHY_FALSE_STRING_H
#define CATCHY_FALSE_STRING_H

#include <string>
#include <ostream>

namespace catchy
{
    // represents a error (false) or empty string (true)
    struct FalseString
    {
        static
        FalseString
        False(const std::string& text);

        static
        FalseString
        True();

        bool
        IsTrue() const;

        operator bool() const;

        static
        FalseString
        Combine(const FalseString& lhs, const FalseString& rhs);
    
        std::string reason;
    };

    std::ostream&
    operator<<(std::ostream& s, const FalseString& f);
}

#endif  // CATCHY_FALSE_STRING_H

