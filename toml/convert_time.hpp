#ifndef TOML11_TIME_CONVERT
#define TOML11_TIME_CONVERT

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif//__STDC_WANT_LIB_EXT1__

#include <time.h>

#ifdef __STDC_LIB_EXT1__
#  define TOML11_HAVE_C11_LOCALTIME_S
#  define TOML11_HAVE_C11_GMTIME_S
#elif (_POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _BSD_SOURCE || _SVID_SOURCE || _POSIX_SOURCE)
#  define TOML11_HAVE_POSIX_LOCALTIME_R
#  define TOML11_HAVE_POSIX_GMTIME_R
#endif

#include <ctime>

namespace toml
{
namespace detail
{

#ifdef TOML11_HAVE_C11_LOCALTIME_S

inline std::tm* localtime(const std::time_t* time_, std::tm* tm_)
{
    return localtime_s(time_, tm_);
}

#elif defined(TOML11_HAVE_POSIX_LOCALTIME_R)

inline std::tm* localtime(const std::time_t* time_, std::tm* tm_)
{
    return localtime_r(time_, tm_);
}

#else // fallback

inline std::tm* localtime(const std::time_t* time_, std::tm* tm_)
{
    std::tm* tmp = std::localtime(time_);
    *tm_ = *tmp;
    return tmp;
}

#endif

#ifdef TOML11_HAVE_C11_GMTIME_S

inline std::tm* gmtime(const std::time_t* time_, std::tm* tm_)
{
    return gmtime_s(time_, tm_);
}

#elif defined(TOML11_HAVE_POSIX_GMTIME_R)

inline std::tm* gmtime(const std::time_t* time_, std::tm* tm_)
{
    return gmtime_r(time_, tm_);
}

#else // fallback

inline std::tm* gmtime(const std::time_t* time_, std::tm* tm_)
{
    std::tm* tmp = std::gmtime(time_);
    *tm_ = *tmp;
    return tmp;
}

#endif

}// detail
}// toml
#endif//TOML11_TIME_CONVERT
