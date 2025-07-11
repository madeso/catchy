#pragma once

#include <limits>

#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_reusable_string_stream.hpp"

namespace catchy
{
    struct ApproxData
    {
        double epsilon;
        double scale;
        double margin;
    };

    // https://groups.google.com/forum/#!topic/catch-forum/03HhdvUzIhg

    template <typename T>
    bool
    approximately_equal(const T& lhs, const T& rhs, const ApproxData& data);


    template <>
    bool
    approximately_equal(
            double const&     lhs,
            double const&     rhs,
            const ApproxData& data);

    template <>
    bool
    approximately_equal(
            float const&      lhs,
            float const&      rhs,
            const ApproxData& data);


    ////////////////////////////////////////////////////////////////////////////////
    // modified Catch Approx

    namespace custom
    {
        template <typename T>
        struct Approx
        {
        public:
            explicit Approx(T value)
                : m_epsilon(std::numeric_limits<float>::epsilon() * 100)
                , m_margin(0.0)
                , m_scale(1.0)
                , m_value(value)
            {}

            friend bool
            operator==(T lhs, Approx<T> const& rhs)
            {
                ApproxData data;
                data.epsilon = rhs.m_epsilon;
                data.scale   = rhs.m_scale;
                data.margin  = rhs.m_margin;
                return approximately_equal(lhs, rhs.m_value, data);
            }

            friend bool
            operator==(Approx<T> const& lhs, T rhs)
            {
                return operator==(rhs, lhs);
            }

            friend bool
            operator!=(T lhs, Approx<T> const& rhs)
            {
                return !operator==(lhs, rhs);
            }

            friend bool
            operator!=(Approx<T> const& lhs, T rhs)
            {
                return !operator==(rhs, lhs);
            }

            Approx&
            epsilon(double newEpsilon)
            {
                m_epsilon = newEpsilon;
                return *this;
            }

            Approx&
            margin(double newMargin)
            {
                m_margin = newMargin;
                return *this;
            }

            Approx&
            scale(double newScale)
            {
                m_scale = newScale;
                return *this;
            }

            std::string
            toString() const
            {
                Catch::ReusableStringStream rss;
                rss << "Approx( " << ::Catch::Detail::stringify(m_value)
                    << " )";
                return rss.str();
            }

        private:
            double m_epsilon;
            double m_margin;
            double m_scale;
            T      m_value;
        };
    }  // namespace custom

    template <typename T>
    std::ostream&
    operator<<(std::ostream& stream, const custom::Approx<T>& v)
    {
        return stream << v.toString();
    }

    ////////////////////////////////////////////////////////////////////////////////


    template <typename T>
    custom::Approx<T>
    approx(T const& t)
    {
        return custom::Approx<T>(t);
    }
}

