// Copyright (c) 2006 Johan Rade

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#   pragma warning(disable : 4702)
#endif

#include <iomanip>
#include <locale>
#include <sstream>
#include <boost/test/auto_unit_test.hpp>
#include "almost_equal.hpp"
#include "S_.hpp"
#include "../../../../boost/math/nonfinite_num_facets.hpp"

namespace {

// the anonymous namespace resolves ambiguities on platforms
// with fpclassify etc functions at global scope

using namespace boost::math;
using boost::math::signbit;
using boost::math::changesign;
using boost::math::isnan;

//------------------------------------------------------------------------------

void basic_test_finite();
void basic_test_inf();
void basic_test_nan();
void basic_test_format();

BOOST_AUTO_TEST_CASE(basic_test)
{
    basic_test_finite();
    basic_test_inf();
    basic_test_nan();
    basic_test_format();
}

//------------------------------------------------------------------------------

template<class CharType, class ValType> void basic_test_finite_impl();

void basic_test_finite()
{
    basic_test_finite_impl<char, float>();
    basic_test_finite_impl<char, double>();
    basic_test_finite_impl<char, long double>();
    basic_test_finite_impl<wchar_t, float>();
    basic_test_finite_impl<wchar_t, double>();
    basic_test_finite_impl<wchar_t, long double>();
}

template<class CharType, class ValType> void basic_test_finite_impl()
{
    std::locale old_locale;
    std::locale tmp_locale(old_locale, new nonfinite_num_put<CharType>);
    std::locale new_locale(tmp_locale, new nonfinite_num_get<CharType>);

    std::basic_stringstream<CharType> ss;
    ss.imbue(new_locale);

    ValType a1 = (ValType)1.2;
    ValType a2 = (ValType)-3.5;
    ValType a3 = std::numeric_limits<ValType>::max();
    ValType a4 = -std::numeric_limits<ValType>::max();
    ss << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4;

    ValType b1, b2, b3, b4;
    ss >> b1 >> b2 >> b3 >> b4;

    BOOST_CHECK(almost_equal(b1, a1));
    BOOST_CHECK(almost_equal(b2, a2));
    BOOST_CHECK(almost_equal(b3, a3));
    BOOST_CHECK(almost_equal(b4, a4));
    BOOST_CHECK(b3 != std::numeric_limits<ValType>::infinity());
    BOOST_CHECK(b4 != -std::numeric_limits<ValType>::infinity());
    BOOST_CHECK(ss.rdstate() == std::ios_base::eofbit);

    ss.clear();
    ss.str(S_(""));

    ss << "++5";
    ValType b5;
    ss >> b5;
    BOOST_CHECK(ss.rdstate() == std::ios_base::failbit);
}

//------------------------------------------------------------------------------

template<class CharType, class ValType> void basic_test_inf_impl();

void basic_test_inf()
{
    basic_test_inf_impl<char, float>();
    basic_test_inf_impl<char, double>();
    basic_test_inf_impl<char, long double>();
    basic_test_inf_impl<wchar_t, float>();
    basic_test_inf_impl<wchar_t, double>();
    basic_test_inf_impl<wchar_t, long double>();
}

template<class CharType, class ValType> void basic_test_inf_impl()
{
    std::locale old_locale;
    std::locale tmp_locale(old_locale, new nonfinite_num_put<CharType>);
    std::locale new_locale(tmp_locale, new nonfinite_num_get<CharType>);

    std::basic_stringstream<CharType> ss;
    ss.imbue(new_locale);

    ValType a1 = std::numeric_limits<ValType>::infinity();
    ValType a2 = -std::numeric_limits<ValType>::infinity();

    ss << a1 << ' ' << a2;

    std::basic_string<CharType> s = S_("inf -inf");
    BOOST_CHECK(ss.str() == s);

    ss << " infinity";          // alternative C99 representation of infinity

    ValType b1, b2, b3;
    ss >> b1;
    ss >> b2;
    ss >> b3;

    BOOST_CHECK(b1 == a1);
    BOOST_CHECK(b2 == a2);
    BOOST_CHECK(b3 == std::numeric_limits<ValType>::infinity());
    BOOST_CHECK(ss.rdstate() == std::ios_base::eofbit);
}

//------------------------------------------------------------------------------

template<class CharType, class ValType> void basic_test_nan_impl();

void basic_test_nan()
{
    basic_test_nan_impl<char, float>();
    basic_test_nan_impl<char, double>();
    basic_test_nan_impl<char, long double>();
    basic_test_nan_impl<wchar_t, float>();
    basic_test_nan_impl<wchar_t, double>();
    basic_test_nan_impl<wchar_t, long double>();
}

template<class CharType, class ValType> void basic_test_nan_impl()
{
    std::locale old_locale;
    std::locale tmp_locale(old_locale, new nonfinite_num_put<CharType>);
    std::locale new_locale(tmp_locale, new nonfinite_num_get<CharType>);

    std::basic_stringstream<CharType> ss;
    ss.imbue(new_locale);

    ValType a1 = std::numeric_limits<ValType>::quiet_NaN();
    ValType a2 = -std::numeric_limits<ValType>::quiet_NaN();
    ValType a3 = std::numeric_limits<ValType>::signaling_NaN();
    ValType a4 = -std::numeric_limits<ValType>::signaling_NaN();
    ss << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4; 

    std::basic_string<CharType> s = S_("nan -nan nan -nan");
    BOOST_CHECK(ss.str() == s);

    // alternative C99 representation of NaN
    ss << " nan(foo)";

    ValType b1, b2, b3, b4, b5;
    ss >> b1 >> b2 >> b3 >> b4 >> b5;

    BOOST_CHECK((isnan)(b1));
    BOOST_CHECK((isnan)(b2));
    BOOST_CHECK((isnan)(b3));
    BOOST_CHECK((isnan)(b4));
    BOOST_CHECK((isnan)(b5));

    BOOST_CHECK(!(signbit)(b1));
    BOOST_CHECK((signbit)(b2));
    BOOST_CHECK(!(signbit)(b3));
    BOOST_CHECK((signbit)(b4));
    BOOST_CHECK(!(signbit)(b5));

    BOOST_CHECK(ss.rdstate() == std::ios_base::eofbit);
}

//------------------------------------------------------------------------------

template<class CharType, class ValType> void basic_test_format_impl();

void basic_test_format()
{
    basic_test_format_impl<char, float>();
    basic_test_format_impl<char, double>();
    basic_test_format_impl<char, long double>();
    basic_test_format_impl<wchar_t, float>();
    basic_test_format_impl<wchar_t, double>();
    basic_test_format_impl<wchar_t, long double>();
}

template<class CharType, class ValType> void basic_test_format_impl()
{
    std::locale old_locale;
    std::locale tmp_locale(old_locale, new nonfinite_num_put<CharType>);
    std::locale new_locale(tmp_locale, new nonfinite_num_get<CharType>);

    std::basic_stringstream<CharType> ss;
    ss.imbue(new_locale);

    ValType a = std::numeric_limits<ValType>::infinity();

    ss << std::setw(6) << a;
    ss << '|';
    ss << std::setw(2) << a;
    ss << '|';
    ss << std::left << std::setw(5) << a;
    ss << '|';
    ss << std::showpos << std::internal << std::setw(7) << a;
    ss << '|';
    ss << std::uppercase << std::right << std::setw(6) << a;

    std::basic_string<CharType> s = S_("   inf|inf|inf  |+   inf|  +INF");
    BOOST_CHECK(ss.str() == s);
}

//------------------------------------------------------------------------------

}   // anonymous namespace
