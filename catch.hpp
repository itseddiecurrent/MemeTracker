/*
 *  Catch v2.13.3
 *  Generated: 2020-10-31 18:20:31.045274
 *  ----------------------------------------------------------
 *  This file has been merged from multiple headers. Please don't edit it directly
 *  Copyright (c) 2020 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
#define TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
// start catch.hpp


#define CATCH_VERSION_MAJOR 2
#define CATCH_VERSION_MINOR 13
#define CATCH_VERSION_PATCH 3

#ifdef __clang__
#    pragma clang system_header
#elif defined __GNUC__
#    pragma GCC system_header
#endif

// start catch_suppress_warnings.h

#ifdef __clang__
#   ifdef __ICC // icpc defines the __clang__ macro
#       pragma warning(push)
#       pragma warning(disable: 161 1682)
#   else // __ICC
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wpadded"
#       pragma clang diagnostic ignored "-Wswitch-enum"
#       pragma clang diagnostic ignored "-Wcovered-switch-default"
#    endif
#elif defined __GNUC__
     // Because REQUIREs trigger GCC's -Wparentheses, and because still
     // supported version of g++ have only buggy support for _Pragmas,
     // Wparentheses have to be suppressed globally.
#    pragma GCC diagnostic ignored "-Wparentheses" // See #674 for details

#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wunused-variable"
#    pragma GCC diagnostic ignored "-Wpadded"
#endif
// end catch_suppress_warnings.h
#if defined(CATCH_CONFIG_MAIN) || defined(CATCH_CONFIG_RUNNER)
#  define CATCH_IMPL
#  define CATCH_CONFIG_ALL_PARTS
#endif

// In the impl file, we want to have access to all parts of the headers
// Can also be used to sanely support PCHs
#if defined(CATCH_CONFIG_ALL_PARTS)
#  define CATCH_CONFIG_EXTERNAL_INTERFACES
#  if defined(CATCH_CONFIG_DISABLE_MATCHERS)
#    undef CATCH_CONFIG_DISABLE_MATCHERS
#  endif
#  if !defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#    define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#  endif
#endif

#if !defined(CATCH_CONFIG_IMPL_ONLY)
// start catch_platform.h

#ifdef __APPLE__
# include &lt;TargetConditionals.h&gt;
# if TARGET_OS_OSX == 1
#  define CATCH_PLATFORM_MAC
# elif TARGET_OS_IPHONE == 1
#  define CATCH_PLATFORM_IPHONE
# endif

#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define CATCH_PLATFORM_LINUX

#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__)
#  define CATCH_PLATFORM_WINDOWS
#endif

// end catch_platform.h

#ifdef CATCH_IMPL
#  ifndef CLARA_CONFIG_MAIN
#    define CLARA_CONFIG_MAIN_NOT_DEFINED
#    define CLARA_CONFIG_MAIN
#  endif
#endif

// start catch_user_interfaces.h

namespace Catch {
    unsigned int rngSeed();
}

// end catch_user_interfaces.h
// start catch_tag_alias_autoregistrar.h

// start catch_common.h

// start catch_compiler_capabilities.h

// Detect a number of compiler features - by compiler
// The following features are defined:
//
// CATCH_CONFIG_COUNTER : is the __COUNTER__ macro supported?
// CATCH_CONFIG_WINDOWS_SEH : is Windows SEH supported?
// CATCH_CONFIG_POSIX_SIGNALS : are POSIX signals supported?
// CATCH_CONFIG_DISABLE_EXCEPTIONS : Are exceptions enabled?
// ****************
// Note to maintainers: if new toggles are added please document them
// in configuration.md, too
// ****************

// In general each macro has a _NO_&lt;feature name&gt; form
// (e.g. CATCH_CONFIG_NO_POSIX_SIGNALS) which disables the feature.
// Many features, at point of detection, define an _INTERNAL_ macro, so they
// can be combined, en-mass, with the _NO_ forms later.

#ifdef __cplusplus

#  if (__cplusplus &gt;= 201402L) || (defined(_MSVC_LANG) &amp;&amp; _MSVC_LANG &gt;= 201402L)
#    define CATCH_CPP14_OR_GREATER
#  endif

#  if (__cplusplus &gt;= 201703L) || (defined(_MSVC_LANG) &amp;&amp; _MSVC_LANG &gt;= 201703L)
#    define CATCH_CPP17_OR_GREATER
#  endif

#endif

// We have to avoid both ICC and Clang, because they try to mask themselves
// as gcc, and we want only GCC in this block
#if defined(__GNUC__) &amp;&amp; !defined(__clang__) &amp;&amp; !defined(__ICC) &amp;&amp; !defined(__CUDACC__)
#    define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION _Pragma( "GCC diagnostic push" )
#    define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  _Pragma( "GCC diagnostic pop" )

#    define CATCH_INTERNAL_IGNORE_BUT_WARN(...) (void)__builtin_constant_p(__VA_ARGS__)

#endif

#if defined(__clang__)

#    define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION _Pragma( "clang diagnostic push" )
#    define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  _Pragma( "clang diagnostic pop" )

// As of this writing, IBM XL's implementation of __builtin_constant_p has a bug
// which results in calls to destructors being emitted for each temporary,
// without a matching initialization. In practice, this can result in something
// like `std::string::~string` being called on an uninitialized value.
//
// For example, this code will likely segfault under IBM XL:
// ```
// REQUIRE(std::string("12") + "34" == "1234")
// ```
//
// Therefore, `CATCH_INTERNAL_IGNORE_BUT_WARN` is not implemented.
#  if !defined(__ibmxl__) &amp;&amp; !defined(__CUDACC__)
#    define CATCH_INTERNAL_IGNORE_BUT_WARN(...) (void)__builtin_constant_p(__VA_ARGS__) /* NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg) */
#  endif

#    define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wexit-time-destructors\"" ) \
         _Pragma( "clang diagnostic ignored \"-Wglobal-constructors\"")

#    define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wparentheses\"" )

#    define CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wunused-variable\"" )

#    define CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"" )

#    define CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
         _Pragma( "clang diagnostic ignored \"-Wunused-template\"" )

#endif // __clang__

////////////////////////////////////////////////////////////////////////////////
// Assume that non-Windows platforms support posix signals by default
#if !defined(CATCH_PLATFORM_WINDOWS)
    #define CATCH_INTERNAL_CONFIG_POSIX_SIGNALS
#endif

////////////////////////////////////////////////////////////////////////////////
// We know some environments not to support full POSIX signals
#if defined(__CYGWIN__) || defined(__QNX__) || defined(__EMSCRIPTEN__) || defined(__DJGPP__)
    #define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#endif

#ifdef __OS400__
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#       define CATCH_CONFIG_COLOUR_NONE
#endif

////////////////////////////////////////////////////////////////////////////////
// Android somehow still does not support std::to_string
#if defined(__ANDROID__)
#    define CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING
#    define CATCH_INTERNAL_CONFIG_ANDROID_LOGWRITE
#endif

////////////////////////////////////////////////////////////////////////////////
// Not all Windows environments support SEH properly
#if defined(__MINGW32__)
#    define CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH
#endif

////////////////////////////////////////////////////////////////////////////////
// PS4
#if defined(__ORBIS__)
#    define CATCH_INTERNAL_CONFIG_NO_NEW_CAPTURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Cygwin
#ifdef __CYGWIN__

// Required for some versions of Cygwin to declare gettimeofday
// see: http://stackoverflow.com/questions/36901803/gettimeofday-not-declared-in-this-scope-cygwin
#   define _BSD_SOURCE
// some versions of cygwin (most) do not support std::to_string. Use the libstd check.
// https://gcc.gnu.org/onlinedocs/gcc-4.8.2/libstdc++/api/a01053_source.html line 2812-2813
# if !((__cplusplus &gt;= 201103L) &amp;&amp; defined(_GLIBCXX_USE_C99) \
           &amp;&amp; !defined(_GLIBCXX_HAVE_BROKEN_VSWPRINTF))

#    define CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING

# endif
#endif // __CYGWIN__

////////////////////////////////////////////////////////////////////////////////
// Visual C++
#if defined(_MSC_VER)

#  define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION __pragma( warning(push) )
#  define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION  __pragma( warning(pop) )

// Universal Windows platform does not support SEH
// Or console colours (or console at all...)
#  if defined(WINAPI_FAMILY) &amp;&amp; (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#    define CATCH_CONFIG_COLOUR_NONE
#  else
#    define CATCH_INTERNAL_CONFIG_WINDOWS_SEH
#  endif

// MSVC traditional preprocessor needs some workaround for __VA_ARGS__
// _MSVC_TRADITIONAL == 0 means new conformant preprocessor
// _MSVC_TRADITIONAL == 1 means old traditional non-conformant preprocessor
#  if !defined(__clang__) // Handle Clang masquerading for msvc
#    if !defined(_MSVC_TRADITIONAL) || (defined(_MSVC_TRADITIONAL) &amp;&amp; _MSVC_TRADITIONAL)
#      define CATCH_INTERNAL_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#    endif // MSVC_TRADITIONAL
#  endif // __clang__

#endif // _MSC_VER

#if defined(_REENTRANT) || defined(_MSC_VER)
// Enable async processing, as -pthread is specified or no additional linking is required
# define CATCH_INTERNAL_CONFIG_USE_ASYNC
#endif // _MSC_VER

////////////////////////////////////////////////////////////////////////////////
// Check if we are compiled with -fno-exceptions or equivalent
#if defined(__EXCEPTIONS) || defined(__cpp_exceptions) || defined(_CPPUNWIND)
#  define CATCH_INTERNAL_CONFIG_EXCEPTIONS_ENABLED
#endif

////////////////////////////////////////////////////////////////////////////////
// DJGPP
#ifdef __DJGPP__
#  define CATCH_INTERNAL_CONFIG_NO_WCHAR
#endif // __DJGPP__

////////////////////////////////////////////////////////////////////////////////
// Embarcadero C++Build
#if defined(__BORLANDC__)
    #define CATCH_INTERNAL_CONFIG_POLYFILL_ISNAN
#endif

////////////////////////////////////////////////////////////////////////////////

// Use of __COUNTER__ is suppressed during code analysis in
// CLion/AppCode 2017.2.x and former, because __COUNTER__ is not properly
// handled by it.
// Otherwise all supported compilers support COUNTER macro,
// but user still might want to turn it off
#if ( !defined(__JETBRAINS_IDE__) || __JETBRAINS_IDE__ &gt;= 20170300L )
    #define CATCH_INTERNAL_CONFIG_COUNTER
#endif

////////////////////////////////////////////////////////////////////////////////

// RTX is a special version of Windows that is real time.
// This means that it is detected as Windows, but does not provide
// the same set of capabilities as real Windows does.
#if defined(UNDER_RTSS) || defined(RTX64_BUILD)
    #define CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH
    #define CATCH_INTERNAL_CONFIG_NO_ASYNC
    #define CATCH_CONFIG_COLOUR_NONE
#endif

#if !defined(_GLIBCXX_USE_C99_MATH_TR1)
#define CATCH_INTERNAL_CONFIG_GLOBAL_NEXTAFTER
#endif

// Various stdlib support checks that require __has_include
#if defined(__has_include)
  // Check if string_view is available and usable
  #if __has_include(&lt;string_view&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)
  #    define CATCH_INTERNAL_CONFIG_CPP17_STRING_VIEW
  #endif

  // Check if optional is available and usable
  #  if __has_include(&lt;optional&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)
  #    define CATCH_INTERNAL_CONFIG_CPP17_OPTIONAL
  #  endif // __has_include(&lt;optional&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)

  // Check if byte is available and usable
  #  if __has_include(&lt;cstddef&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)
  #    include &lt;cstddef&gt;
  #    if __cpp_lib_byte &gt; 0
  #      define CATCH_INTERNAL_CONFIG_CPP17_BYTE
  #    endif
  #  endif // __has_include(&lt;cstddef&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)

  // Check if variant is available and usable
  #  if __has_include(&lt;variant&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)
  #    if defined(__clang__) &amp;&amp; (__clang_major__ &lt; 8)
         // work around clang bug with libstdc++ https://bugs.llvm.org/show_bug.cgi?id=31852
         // fix should be in clang 8, workaround in libstdc++ 8.2
  #      include &lt;ciso646&gt;
  #      if defined(__GLIBCXX__) &amp;&amp; defined(_GLIBCXX_RELEASE) &amp;&amp; (_GLIBCXX_RELEASE &lt; 9)
  #        define CATCH_CONFIG_NO_CPP17_VARIANT
  #      else
  #        define CATCH_INTERNAL_CONFIG_CPP17_VARIANT
  #      endif // defined(__GLIBCXX__) &amp;&amp; defined(_GLIBCXX_RELEASE) &amp;&amp; (_GLIBCXX_RELEASE &lt; 9)
  #    else
  #      define CATCH_INTERNAL_CONFIG_CPP17_VARIANT
  #    endif // defined(__clang__) &amp;&amp; (__clang_major__ &lt; 8)
  #  endif // __has_include(&lt;variant&gt;) &amp;&amp; defined(CATCH_CPP17_OR_GREATER)
#endif // defined(__has_include)

#if defined(CATCH_INTERNAL_CONFIG_COUNTER) &amp;&amp; !defined(CATCH_CONFIG_NO_COUNTER) &amp;&amp; !defined(CATCH_CONFIG_COUNTER)
#   define CATCH_CONFIG_COUNTER
#endif
#if defined(CATCH_INTERNAL_CONFIG_WINDOWS_SEH) &amp;&amp; !defined(CATCH_CONFIG_NO_WINDOWS_SEH) &amp;&amp; !defined(CATCH_CONFIG_WINDOWS_SEH) &amp;&amp; !defined(CATCH_INTERNAL_CONFIG_NO_WINDOWS_SEH)
#   define CATCH_CONFIG_WINDOWS_SEH
#endif
// This is set by default, because we assume that unix compilers are posix-signal-compatible by default.
#if defined(CATCH_INTERNAL_CONFIG_POSIX_SIGNALS) &amp;&amp; !defined(CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS) &amp;&amp; !defined(CATCH_CONFIG_NO_POSIX_SIGNALS) &amp;&amp; !defined(CATCH_CONFIG_POSIX_SIGNALS)
#   define CATCH_CONFIG_POSIX_SIGNALS
#endif
// This is set by default, because we assume that compilers with no wchar_t support are just rare exceptions.
#if !defined(CATCH_INTERNAL_CONFIG_NO_WCHAR) &amp;&amp; !defined(CATCH_CONFIG_NO_WCHAR) &amp;&amp; !defined(CATCH_CONFIG_WCHAR)
#   define CATCH_CONFIG_WCHAR
#endif

#if !defined(CATCH_INTERNAL_CONFIG_NO_CPP11_TO_STRING) &amp;&amp; !defined(CATCH_CONFIG_NO_CPP11_TO_STRING) &amp;&amp; !defined(CATCH_CONFIG_CPP11_TO_STRING)
#    define CATCH_CONFIG_CPP11_TO_STRING
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_OPTIONAL) &amp;&amp; !defined(CATCH_CONFIG_NO_CPP17_OPTIONAL) &amp;&amp; !defined(CATCH_CONFIG_CPP17_OPTIONAL)
#  define CATCH_CONFIG_CPP17_OPTIONAL
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_STRING_VIEW) &amp;&amp; !defined(CATCH_CONFIG_NO_CPP17_STRING_VIEW) &amp;&amp; !defined(CATCH_CONFIG_CPP17_STRING_VIEW)
#  define CATCH_CONFIG_CPP17_STRING_VIEW
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_VARIANT) &amp;&amp; !defined(CATCH_CONFIG_NO_CPP17_VARIANT) &amp;&amp; !defined(CATCH_CONFIG_CPP17_VARIANT)
#  define CATCH_CONFIG_CPP17_VARIANT
#endif

#if defined(CATCH_INTERNAL_CONFIG_CPP17_BYTE) &amp;&amp; !defined(CATCH_CONFIG_NO_CPP17_BYTE) &amp;&amp; !defined(CATCH_CONFIG_CPP17_BYTE)
#  define CATCH_CONFIG_CPP17_BYTE
#endif

#if defined(CATCH_CONFIG_EXPERIMENTAL_REDIRECT)
#  define CATCH_INTERNAL_CONFIG_NEW_CAPTURE
#endif

#if defined(CATCH_INTERNAL_CONFIG_NEW_CAPTURE) &amp;&amp; !defined(CATCH_INTERNAL_CONFIG_NO_NEW_CAPTURE) &amp;&amp; !defined(CATCH_CONFIG_NO_NEW_CAPTURE) &amp;&amp; !defined(CATCH_CONFIG_NEW_CAPTURE)
#  define CATCH_CONFIG_NEW_CAPTURE
#endif

#if !defined(CATCH_INTERNAL_CONFIG_EXCEPTIONS_ENABLED) &amp;&amp; !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
#  define CATCH_CONFIG_DISABLE_EXCEPTIONS
#endif

#if defined(CATCH_INTERNAL_CONFIG_POLYFILL_ISNAN) &amp;&amp; !defined(CATCH_CONFIG_NO_POLYFILL_ISNAN) &amp;&amp; !defined(CATCH_CONFIG_POLYFILL_ISNAN)
#  define CATCH_CONFIG_POLYFILL_ISNAN
#endif

#if defined(CATCH_INTERNAL_CONFIG_USE_ASYNC)  &amp;&amp; !defined(CATCH_INTERNAL_CONFIG_NO_ASYNC) &amp;&amp; !defined(CATCH_CONFIG_NO_USE_ASYNC) &amp;&amp; !defined(CATCH_CONFIG_USE_ASYNC)
#  define CATCH_CONFIG_USE_ASYNC
#endif

#if defined(CATCH_INTERNAL_CONFIG_ANDROID_LOGWRITE) &amp;&amp; !defined(CATCH_CONFIG_NO_ANDROID_LOGWRITE) &amp;&amp; !defined(CATCH_CONFIG_ANDROID_LOGWRITE)
#  define CATCH_CONFIG_ANDROID_LOGWRITE
#endif

#if defined(CATCH_INTERNAL_CONFIG_GLOBAL_NEXTAFTER) &amp;&amp; !defined(CATCH_CONFIG_NO_GLOBAL_NEXTAFTER) &amp;&amp; !defined(CATCH_CONFIG_GLOBAL_NEXTAFTER)
#  define CATCH_CONFIG_GLOBAL_NEXTAFTER
#endif

// Even if we do not think the compiler has that warning, we still have
// to provide a macro that can be used by the code.
#if !defined(CATCH_INTERNAL_START_WARNINGS_SUPPRESSION)
#   define CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
#endif
#if !defined(CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION)
#   define CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS
#endif

// The goal of this macro is to avoid evaluation of the arguments, but
// still have the compiler warn on problems inside...
#if !defined(CATCH_INTERNAL_IGNORE_BUT_WARN)
#   define CATCH_INTERNAL_IGNORE_BUT_WARN(...)
#endif

#if defined(__APPLE__) &amp;&amp; defined(__apple_build_version__) &amp;&amp; (__clang_major__ &lt; 10)
#   undef CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#elif defined(__clang__) &amp;&amp; (__clang_major__ &lt; 5)
#   undef CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#endif

#if !defined(CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS
#endif

#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
#define CATCH_TRY if ((true))
#define CATCH_CATCH_ALL if ((false))
#define CATCH_CATCH_ANON(type) if ((false))
#else
#define CATCH_TRY try
#define CATCH_CATCH_ALL catch (...)
#define CATCH_CATCH_ANON(type) catch (type)
#endif

#if defined(CATCH_INTERNAL_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR) &amp;&amp; !defined(CATCH_CONFIG_NO_TRADITIONAL_MSVC_PREPROCESSOR) &amp;&amp; !defined(CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR)
#define CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#endif

// end catch_compiler_capabilities.h
#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#ifdef CATCH_CONFIG_COUNTER
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __COUNTER__ )
#else
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __LINE__ )
#endif

#include &lt;iosfwd&gt;
#include &lt;string&gt;
#include &lt;cstdint&gt;

// We need a dummy global operator&lt;&lt; so we can bring it into Catch namespace later
struct Catch_global_namespace_dummy {};
std::ostream&amp; operator&lt;&lt;(std::ostream&amp;, Catch_global_namespace_dummy);

namespace Catch {

    struct CaseSensitive { enum Choice {
        Yes,
        No
    }; };

    class NonCopyable {
        NonCopyable( NonCopyable const&amp; )              = delete;
        NonCopyable( NonCopyable &amp;&amp; )                  = delete;
        NonCopyable&amp; operator = ( NonCopyable const&amp; ) = delete;
        NonCopyable&amp; operator = ( NonCopyable &amp;&amp; )     = delete;

    protected:
        NonCopyable();
        virtual ~NonCopyable();
    };

    struct SourceLineInfo {

        SourceLineInfo() = delete;
        SourceLineInfo( char const* _file, std::size_t _line ) noexcept
        :   file( _file ),
            line( _line )
        {}

        SourceLineInfo( SourceLineInfo const&amp; other )            = default;
        SourceLineInfo&amp; operator = ( SourceLineInfo const&amp; )     = default;
        SourceLineInfo( SourceLineInfo&amp;&amp; )              noexcept = default;
        SourceLineInfo&amp; operator = ( SourceLineInfo&amp;&amp; ) noexcept = default;

        bool empty() const noexcept { return file[0] == '\0'; }
        bool operator == ( SourceLineInfo const&amp; other ) const noexcept;
        bool operator &lt; ( SourceLineInfo const&amp; other ) const noexcept;

        char const* file;
        std::size_t line;
    };

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, SourceLineInfo const&amp; info );

    // Bring in operator&lt;&lt; from global namespace into Catch namespace
    // This is necessary because the overload of operator&lt;&lt; above makes
    // lookup stop at namespace Catch
    using ::operator&lt;&lt;;

    // Use this in variadic streaming macros to allow
    //    &gt;&gt; +StreamEndStop
    // as well as
    //    &gt;&gt; stuff +StreamEndStop
    struct StreamEndStop {
        std::string operator+() const;
    };
    template&lt;typename T&gt;
    T const&amp; operator + ( T const&amp; value, StreamEndStop ) {
        return value;
    }
}

#define CATCH_INTERNAL_LINEINFO \
    ::Catch::SourceLineInfo( __FILE__, static_cast&lt;std::size_t&gt;( __LINE__ ) )

// end catch_common.h
namespace Catch {

    struct RegistrarForTagAliases {
        RegistrarForTagAliases( char const* alias, char const* tag, SourceLineInfo const&amp; lineInfo );
    };

} // end namespace Catch

#define CATCH_REGISTER_TAG_ALIAS( alias, spec ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
    namespace{ Catch::RegistrarForTagAliases INTERNAL_CATCH_UNIQUE_NAME( AutoRegisterTagAlias )( alias, spec, CATCH_INTERNAL_LINEINFO ); } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

// end catch_tag_alias_autoregistrar.h
// start catch_test_registry.h

// start catch_interfaces_testcase.h

#include &lt;vector&gt;

namespace Catch {

    class TestSpec;

    struct ITestInvoker {
        virtual void invoke () const = 0;
        virtual ~ITestInvoker();
    };

    class TestCase;
    struct IConfig;

    struct ITestCaseRegistry {
        virtual ~ITestCaseRegistry();
        virtual std::vector&lt;TestCase&gt; const&amp; getAllTests() const = 0;
        virtual std::vector&lt;TestCase&gt; const&amp; getAllTestsSorted( IConfig const&amp; config ) const = 0;
    };

    bool isThrowSafe( TestCase const&amp; testCase, IConfig const&amp; config );
    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config );

}

// end catch_interfaces_testcase.h
// start catch_stringref.h

#include &lt;cstddef&gt;
#include &lt;string&gt;
#include &lt;iosfwd&gt;
#include &lt;cassert&gt;

namespace Catch {

    /// A non-owning string class (similar to the forthcoming std::string_view)
    /// Note that, because a StringRef may be a substring of another string,
    /// it may not be null terminated.
    class StringRef {
    public:
        using size_type = std::size_t;
        using const_iterator = const char*;

    private:
        static constexpr char const* const s_empty = "";

        char const* m_start = s_empty;
        size_type m_size = 0;

    public: // construction
        constexpr StringRef() noexcept = default;

        StringRef( char const* rawChars ) noexcept;

        constexpr StringRef( char const* rawChars, size_type size ) noexcept
        :   m_start( rawChars ),
            m_size( size )
        {}

        StringRef( std::string const&amp; stdString ) noexcept
        :   m_start( stdString.c_str() ),
            m_size( stdString.size() )
        {}

        explicit operator std::string() const {
            return std::string(m_start, m_size);
        }

    public: // operators
        auto operator == ( StringRef const&amp; other ) const noexcept -&gt; bool;
        auto operator != (StringRef const&amp; other) const noexcept -&gt; bool {
            return !(*this == other);
        }

        auto operator[] ( size_type index ) const noexcept -&gt; char {
            assert(index &lt; m_size);
            return m_start[index];
        }

    public: // named queries
        constexpr auto empty() const noexcept -&gt; bool {
            return m_size == 0;
        }
        constexpr auto size() const noexcept -&gt; size_type {
            return m_size;
        }

        // Returns the current start pointer. If the StringRef is not
        // null-terminated, throws std::domain_exception
        auto c_str() const -&gt; char const*;

    public: // substrings and searches
        // Returns a substring of [start, start + length).
        // If start + length &gt; size(), then the substring is [start, size()).
        // If start &gt; size(), then the substring is empty.
        auto substr( size_type start, size_type length ) const noexcept -&gt; StringRef;

        // Returns the current start pointer. May not be null-terminated.
        auto data() const noexcept -&gt; char const*;

        constexpr auto isNullTerminated() const noexcept -&gt; bool {
            return m_start[m_size] == '\0';
        }

    public: // iterators
        constexpr const_iterator begin() const { return m_start; }
        constexpr const_iterator end() const { return m_start + m_size; }
    };

    auto operator += ( std::string&amp; lhs, StringRef const&amp; sr ) -&gt; std::string&amp;;
    auto operator &lt;&lt; ( std::ostream&amp; os, StringRef const&amp; sr ) -&gt; std::ostream&amp;;

    constexpr auto operator "" _sr( char const* rawChars, std::size_t size ) noexcept -&gt; StringRef {
        return StringRef( rawChars, size );
    }
} // namespace Catch

constexpr auto operator "" _catch_sr( char const* rawChars, std::size_t size ) noexcept -&gt; Catch::StringRef {
    return Catch::StringRef( rawChars, size );
}

// end catch_stringref.h
// start catch_preprocessor.hpp


#define CATCH_RECURSION_LEVEL0(...) __VA_ARGS__
#define CATCH_RECURSION_LEVEL1(...) CATCH_RECURSION_LEVEL0(CATCH_RECURSION_LEVEL0(CATCH_RECURSION_LEVEL0(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL2(...) CATCH_RECURSION_LEVEL1(CATCH_RECURSION_LEVEL1(CATCH_RECURSION_LEVEL1(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL3(...) CATCH_RECURSION_LEVEL2(CATCH_RECURSION_LEVEL2(CATCH_RECURSION_LEVEL2(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL4(...) CATCH_RECURSION_LEVEL3(CATCH_RECURSION_LEVEL3(CATCH_RECURSION_LEVEL3(__VA_ARGS__)))
#define CATCH_RECURSION_LEVEL5(...) CATCH_RECURSION_LEVEL4(CATCH_RECURSION_LEVEL4(CATCH_RECURSION_LEVEL4(__VA_ARGS__)))

#ifdef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_EXPAND_VARGS(...) __VA_ARGS__
// MSVC needs more evaluations
#define CATCH_RECURSION_LEVEL6(...) CATCH_RECURSION_LEVEL5(CATCH_RECURSION_LEVEL5(CATCH_RECURSION_LEVEL5(__VA_ARGS__)))
#define CATCH_RECURSE(...)  CATCH_RECURSION_LEVEL6(CATCH_RECURSION_LEVEL6(__VA_ARGS__))
#else
#define CATCH_RECURSE(...)  CATCH_RECURSION_LEVEL5(__VA_ARGS__)
#endif

#define CATCH_REC_END(...)
#define CATCH_REC_OUT

#define CATCH_EMPTY()
#define CATCH_DEFER(id) id CATCH_EMPTY()

#define CATCH_REC_GET_END2() 0, CATCH_REC_END
#define CATCH_REC_GET_END1(...) CATCH_REC_GET_END2
#define CATCH_REC_GET_END(...) CATCH_REC_GET_END1
#define CATCH_REC_NEXT0(test, next, ...) next CATCH_REC_OUT
#define CATCH_REC_NEXT1(test, next) CATCH_DEFER ( CATCH_REC_NEXT0 ) ( test, next, 0)
#define CATCH_REC_NEXT(test, next)  CATCH_REC_NEXT1(CATCH_REC_GET_END test, next)

#define CATCH_REC_LIST0(f, x, peek, ...) , f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1) ) ( f, peek, __VA_ARGS__ )
#define CATCH_REC_LIST1(f, x, peek, ...) , f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST0) ) ( f, peek, __VA_ARGS__ )
#define CATCH_REC_LIST2(f, x, peek, ...)   f(x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1) ) ( f, peek, __VA_ARGS__ )

#define CATCH_REC_LIST0_UD(f, userdata, x, peek, ...) , f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ )
#define CATCH_REC_LIST1_UD(f, userdata, x, peek, ...) , f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST0_UD) ) ( f, userdata, peek, __VA_ARGS__ )
#define CATCH_REC_LIST2_UD(f, userdata, x, peek, ...)   f(userdata, x) CATCH_DEFER ( CATCH_REC_NEXT(peek, CATCH_REC_LIST1_UD) ) ( f, userdata, peek, __VA_ARGS__ )

// Applies the function macro `f` to each of the remaining parameters, inserts commas between the results,
// and passes userdata as the first parameter to each invocation,
// e.g. CATCH_REC_LIST_UD(f, x, a, b, c) evaluates to f(x, a), f(x, b), f(x, c)
#define CATCH_REC_LIST_UD(f, userdata, ...) CATCH_RECURSE(CATCH_REC_LIST2_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define CATCH_REC_LIST(f, ...) CATCH_RECURSE(CATCH_REC_LIST2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define INTERNAL_CATCH_EXPAND1(param) INTERNAL_CATCH_EXPAND2(param)
#define INTERNAL_CATCH_EXPAND2(...) INTERNAL_CATCH_NO## __VA_ARGS__
#define INTERNAL_CATCH_DEF(...) INTERNAL_CATCH_DEF __VA_ARGS__
#define INTERNAL_CATCH_NOINTERNAL_CATCH_DEF
#define INTERNAL_CATCH_STRINGIZE(...) INTERNAL_CATCH_STRINGIZE2(__VA_ARGS__)
#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_STRINGIZE2(...) #__VA_ARGS__
#define INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS(param) INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_REMOVE_PARENS(param))
#else
// MSVC is adding extra space and needs another indirection to expand INTERNAL_CATCH_NOINTERNAL_CATCH_DEF
#define INTERNAL_CATCH_STRINGIZE2(...) INTERNAL_CATCH_STRINGIZE3(__VA_ARGS__)
#define INTERNAL_CATCH_STRINGIZE3(...) #__VA_ARGS__
#define INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS(param) (INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_REMOVE_PARENS(param)) + 1)
#endif

#define INTERNAL_CATCH_MAKE_NAMESPACE2(...) ns_##__VA_ARGS__
#define INTERNAL_CATCH_MAKE_NAMESPACE(name) INTERNAL_CATCH_MAKE_NAMESPACE2(name)

#define INTERNAL_CATCH_REMOVE_PARENS(...) INTERNAL_CATCH_EXPAND1(INTERNAL_CATCH_DEF __VA_ARGS__)

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_MAKE_TYPE_LIST2(...) decltype(get_wrapper&lt;INTERNAL_CATCH_REMOVE_PARENS_GEN(__VA_ARGS__)&gt;())
#define INTERNAL_CATCH_MAKE_TYPE_LIST(...) INTERNAL_CATCH_MAKE_TYPE_LIST2(INTERNAL_CATCH_REMOVE_PARENS(__VA_ARGS__))
#else
#define INTERNAL_CATCH_MAKE_TYPE_LIST2(...) INTERNAL_CATCH_EXPAND_VARGS(decltype(get_wrapper&lt;INTERNAL_CATCH_REMOVE_PARENS_GEN(__VA_ARGS__)&gt;()))
#define INTERNAL_CATCH_MAKE_TYPE_LIST(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_MAKE_TYPE_LIST2(INTERNAL_CATCH_REMOVE_PARENS(__VA_ARGS__)))
#endif

#define INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(...)\
    CATCH_REC_LIST(INTERNAL_CATCH_MAKE_TYPE_LIST,__VA_ARGS__)

#define INTERNAL_CATCH_REMOVE_PARENS_1_ARG(_0) INTERNAL_CATCH_REMOVE_PARENS(_0)
#define INTERNAL_CATCH_REMOVE_PARENS_2_ARG(_0, _1) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_1_ARG(_1)
#define INTERNAL_CATCH_REMOVE_PARENS_3_ARG(_0, _1, _2) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_2_ARG(_1, _2)
#define INTERNAL_CATCH_REMOVE_PARENS_4_ARG(_0, _1, _2, _3) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_3_ARG(_1, _2, _3)
#define INTERNAL_CATCH_REMOVE_PARENS_5_ARG(_0, _1, _2, _3, _4) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_4_ARG(_1, _2, _3, _4)
#define INTERNAL_CATCH_REMOVE_PARENS_6_ARG(_0, _1, _2, _3, _4, _5) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_5_ARG(_1, _2, _3, _4, _5)
#define INTERNAL_CATCH_REMOVE_PARENS_7_ARG(_0, _1, _2, _3, _4, _5, _6) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_6_ARG(_1, _2, _3, _4, _5, _6)
#define INTERNAL_CATCH_REMOVE_PARENS_8_ARG(_0, _1, _2, _3, _4, _5, _6, _7) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_7_ARG(_1, _2, _3, _4, _5, _6, _7)
#define INTERNAL_CATCH_REMOVE_PARENS_9_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_8_ARG(_1, _2, _3, _4, _5, _6, _7, _8)
#define INTERNAL_CATCH_REMOVE_PARENS_10_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_9_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9)
#define INTERNAL_CATCH_REMOVE_PARENS_11_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) INTERNAL_CATCH_REMOVE_PARENS(_0), INTERNAL_CATCH_REMOVE_PARENS_10_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

#define INTERNAL_CATCH_VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define INTERNAL_CATCH_TYPE_GEN\
    template&lt;typename...&gt; struct TypeList {};\
    template&lt;typename...Ts&gt;\
    constexpr auto get_wrapper() noexcept -&gt; TypeList&lt;Ts...&gt; { return {}; }\
    template&lt;template&lt;typename...&gt; class...&gt; struct TemplateTypeList{};\
    template&lt;template&lt;typename...&gt; class...Cs&gt;\
    constexpr auto get_wrapper() noexcept -&gt; TemplateTypeList&lt;Cs...&gt; { return {}; }\
    template&lt;typename...&gt;\
    struct append;\
    template&lt;typename...&gt;\
    struct rewrap;\
    template&lt;template&lt;typename...&gt; class, typename...&gt;\
    struct create;\
    template&lt;template&lt;typename...&gt; class, typename&gt;\
    struct convert;\
    \
    template&lt;typename T&gt; \
    struct append&lt;T&gt; { using type = T; };\
    template&lt; template&lt;typename...&gt; class L1, typename...E1, template&lt;typename...&gt; class L2, typename...E2, typename...Rest&gt;\
    struct append&lt;L1&lt;E1...&gt;, L2&lt;E2...&gt;, Rest...&gt; { using type = typename append&lt;L1&lt;E1...,E2...&gt;, Rest...&gt;::type; };\
    template&lt; template&lt;typename...&gt; class L1, typename...E1, typename...Rest&gt;\
    struct append&lt;L1&lt;E1...&gt;, TypeList&lt;mpl_::na&gt;, Rest...&gt; { using type = L1&lt;E1...&gt;; };\
    \
    template&lt; template&lt;typename...&gt; class Container, template&lt;typename...&gt; class List, typename...elems&gt;\
    struct rewrap&lt;TemplateTypeList&lt;Container&gt;, List&lt;elems...&gt;&gt; { using type = TypeList&lt;Container&lt;elems...&gt;&gt;; };\
    template&lt; template&lt;typename...&gt; class Container, template&lt;typename...&gt; class List, class...Elems, typename...Elements&gt;\
    struct rewrap&lt;TemplateTypeList&lt;Container&gt;, List&lt;Elems...&gt;, Elements...&gt; { using type = typename append&lt;TypeList&lt;Container&lt;Elems...&gt;&gt;, typename rewrap&lt;TemplateTypeList&lt;Container&gt;, Elements...&gt;::type&gt;::type; };\
    \
    template&lt;template &lt;typename...&gt; class Final, template&lt; typename...&gt; class...Containers, typename...Types&gt;\
    struct create&lt;Final, TemplateTypeList&lt;Containers...&gt;, TypeList&lt;Types...&gt;&gt; { using type = typename append&lt;Final&lt;&gt;, typename rewrap&lt;TemplateTypeList&lt;Containers&gt;, Types...&gt;::type...&gt;::type; };\
    template&lt;template &lt;typename...&gt; class Final, template &lt;typename...&gt; class List, typename...Ts&gt;\
    struct convert&lt;Final, List&lt;Ts...&gt;&gt; { using type = typename append&lt;Final&lt;&gt;,TypeList&lt;Ts&gt;...&gt;::type; };

#define INTERNAL_CATCH_NTTP_1(signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; struct Nttp{};\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    constexpr auto get_wrapper() noexcept -&gt; Nttp&lt;__VA_ARGS__&gt; { return {}; } \
    template&lt;template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class...&gt; struct NttpTemplateTypeList{};\
    template&lt;template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class...Cs&gt;\
    constexpr auto get_wrapper() noexcept -&gt; NttpTemplateTypeList&lt;Cs...&gt; { return {}; } \
    \
    template&lt; template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class Container, template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class List, INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    struct rewrap&lt;NttpTemplateTypeList&lt;Container&gt;, List&lt;__VA_ARGS__&gt;&gt; { using type = TypeList&lt;Container&lt;__VA_ARGS__&gt;&gt;; };\
    template&lt; template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class Container, template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class List, INTERNAL_CATCH_REMOVE_PARENS(signature), typename...Elements&gt;\
    struct rewrap&lt;NttpTemplateTypeList&lt;Container&gt;, List&lt;__VA_ARGS__&gt;, Elements...&gt; { using type = typename append&lt;TypeList&lt;Container&lt;__VA_ARGS__&gt;&gt;, typename rewrap&lt;NttpTemplateTypeList&lt;Container&gt;, Elements...&gt;::type&gt;::type; };\
    template&lt;template &lt;typename...&gt; class Final, template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; class...Containers, typename...Types&gt;\
    struct create&lt;Final, NttpTemplateTypeList&lt;Containers...&gt;, TypeList&lt;Types...&gt;&gt; { using type = typename append&lt;Final&lt;&gt;, typename rewrap&lt;NttpTemplateTypeList&lt;Containers&gt;, Types...&gt;::type...&gt;::type; };

#define INTERNAL_CATCH_DECLARE_SIG_TEST0(TestName)
#define INTERNAL_CATCH_DECLARE_SIG_TEST1(TestName, signature)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    static void TestName()
#define INTERNAL_CATCH_DECLARE_SIG_TEST_X(TestName, signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    static void TestName()

#define INTERNAL_CATCH_DEFINE_SIG_TEST0(TestName)
#define INTERNAL_CATCH_DEFINE_SIG_TEST1(TestName, signature)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    static void TestName()
#define INTERNAL_CATCH_DEFINE_SIG_TEST_X(TestName, signature,...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    static void TestName()

#define INTERNAL_CATCH_NTTP_REGISTER0(TestFunc, signature)\
    template&lt;typename Type&gt;\
    void reg_test(TypeList&lt;Type&gt;, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&amp;TestFunc&lt;Type&gt;), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER(TestFunc, signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    void reg_test(Nttp&lt;__VA_ARGS__&gt;, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&amp;TestFunc&lt;__VA_ARGS__&gt;), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER_METHOD0(TestName, signature, ...)\
    template&lt;typename Type&gt;\
    void reg_test(TypeList&lt;Type&gt;, Catch::StringRef className, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&amp;TestName&lt;Type&gt;::test), CATCH_INTERNAL_LINEINFO, className, nameAndTags);\
    }

#define INTERNAL_CATCH_NTTP_REGISTER_METHOD(TestName, signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt;\
    void reg_test(Nttp&lt;__VA_ARGS__&gt;, Catch::StringRef className, Catch::NameAndTags nameAndTags)\
    {\
        Catch::AutoReg( Catch::makeTestInvoker(&amp;TestName&lt;__VA_ARGS__&gt;::test), CATCH_INTERNAL_LINEINFO, className, nameAndTags);\
    }

#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0(TestName, ClassName)
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1(TestName, ClassName, signature)\
    template&lt;typename TestType&gt; \
    struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName)&lt;TestType&gt; { \
        void test();\
    }

#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X(TestName, ClassName, signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; \
    struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName)&lt;__VA_ARGS__&gt; { \
        void test();\
    }

#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0(TestName)
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1(TestName, signature)\
    template&lt;typename TestType&gt; \
    void INTERNAL_CATCH_MAKE_NAMESPACE(TestName)::TestName&lt;TestType&gt;::test()
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X(TestName, signature, ...)\
    template&lt;INTERNAL_CATCH_REMOVE_PARENS(signature)&gt; \
    void INTERNAL_CATCH_MAKE_NAMESPACE(TestName)::TestName&lt;__VA_ARGS__&gt;::test()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define INTERNAL_CATCH_NTTP_0
#define INTERNAL_CATCH_NTTP_GEN(...) INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1(__VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_1( __VA_ARGS__),INTERNAL_CATCH_NTTP_1( __VA_ARGS__), INTERNAL_CATCH_NTTP_0)
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0)(TestName, ClassName, __VA_ARGS__)
#define INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD0, INTERNAL_CATCH_NTTP_REGISTER_METHOD0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_NTTP_REG_GEN(TestFunc, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER0, INTERNAL_CATCH_NTTP_REGISTER0)(TestFunc, __VA_ARGS__)
#define INTERNAL_CATCH_DEFINE_SIG_TEST(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST1, INTERNAL_CATCH_DEFINE_SIG_TEST0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_DECLARE_SIG_TEST(TestName, ...) INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST1, INTERNAL_CATCH_DECLARE_SIG_TEST0)(TestName, __VA_ARGS__)
#define INTERNAL_CATCH_REMOVE_PARENS_GEN(...) INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_REMOVE_PARENS_11_ARG,INTERNAL_CATCH_REMOVE_PARENS_10_ARG,INTERNAL_CATCH_REMOVE_PARENS_9_ARG,INTERNAL_CATCH_REMOVE_PARENS_8_ARG,INTERNAL_CATCH_REMOVE_PARENS_7_ARG,INTERNAL_CATCH_REMOVE_PARENS_6_ARG,INTERNAL_CATCH_REMOVE_PARENS_5_ARG,INTERNAL_CATCH_REMOVE_PARENS_4_ARG,INTERNAL_CATCH_REMOVE_PARENS_3_ARG,INTERNAL_CATCH_REMOVE_PARENS_2_ARG,INTERNAL_CATCH_REMOVE_PARENS_1_ARG)(__VA_ARGS__)
#else
#define INTERNAL_CATCH_NTTP_0(signature)
#define INTERNAL_CATCH_NTTP_GEN(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_1,INTERNAL_CATCH_NTTP_1, INTERNAL_CATCH_NTTP_0)( __VA_ARGS__))
#define INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD1, INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X,INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD_X, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD1, INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD0)(TestName, ClassName, __VA_ARGS__))
#define INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD, INTERNAL_CATCH_NTTP_REGISTER_METHOD0, INTERNAL_CATCH_NTTP_REGISTER_METHOD0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_NTTP_REG_GEN(TestFunc, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER, INTERNAL_CATCH_NTTP_REGISTER0, INTERNAL_CATCH_NTTP_REGISTER0)(TestFunc, __VA_ARGS__))
#define INTERNAL_CATCH_DEFINE_SIG_TEST(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DEFINE_SIG_TEST1, INTERNAL_CATCH_DEFINE_SIG_TEST0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_DECLARE_SIG_TEST(TestName, ...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL( "dummy", __VA_ARGS__, INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DEFINE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X,INTERNAL_CATCH_DECLARE_SIG_TEST_X, INTERNAL_CATCH_DECLARE_SIG_TEST1, INTERNAL_CATCH_DECLARE_SIG_TEST0)(TestName, __VA_ARGS__))
#define INTERNAL_CATCH_REMOVE_PARENS_GEN(...) INTERNAL_CATCH_EXPAND_VARGS(INTERNAL_CATCH_VA_NARGS_IMPL(__VA_ARGS__, INTERNAL_CATCH_REMOVE_PARENS_11_ARG,INTERNAL_CATCH_REMOVE_PARENS_10_ARG,INTERNAL_CATCH_REMOVE_PARENS_9_ARG,INTERNAL_CATCH_REMOVE_PARENS_8_ARG,INTERNAL_CATCH_REMOVE_PARENS_7_ARG,INTERNAL_CATCH_REMOVE_PARENS_6_ARG,INTERNAL_CATCH_REMOVE_PARENS_5_ARG,INTERNAL_CATCH_REMOVE_PARENS_4_ARG,INTERNAL_CATCH_REMOVE_PARENS_3_ARG,INTERNAL_CATCH_REMOVE_PARENS_2_ARG,INTERNAL_CATCH_REMOVE_PARENS_1_ARG)(__VA_ARGS__))
#endif

// end catch_preprocessor.hpp
// start catch_meta.hpp


#include &lt;type_traits&gt;

namespace Catch {
    template&lt;typename T&gt;
    struct always_false : std::false_type {};

    template &lt;typename&gt; struct true_given : std::true_type {};
    struct is_callable_tester {
        template &lt;typename Fun, typename... Args&gt;
        true_given&lt;decltype(std::declval&lt;Fun&gt;()(std::declval&lt;Args&gt;()...))&gt; static test(int);
        template &lt;typename...&gt;
        std::false_type static test(...);
    };

    template &lt;typename T&gt;
    struct is_callable;

    template &lt;typename Fun, typename... Args&gt;
    struct is_callable&lt;Fun(Args...)&gt; : decltype(is_callable_tester::test&lt;Fun, Args...&gt;(0)) {};

#if defined(__cpp_lib_is_invocable) &amp;&amp; __cpp_lib_is_invocable &gt;= 201703
    // std::result_of is deprecated in C++17 and removed in C++20. Hence, it is
    // replaced with std::invoke_result here.
    template &lt;typename Func, typename... U&gt;
    using FunctionReturnType = std::remove_reference_t&lt;std::remove_cv_t&lt;std::invoke_result_t&lt;Func, U...&gt;&gt;&gt;;
#else
    // Keep ::type here because we still support C++11
    template &lt;typename Func, typename... U&gt;
    using FunctionReturnType = typename std::remove_reference&lt;typename std::remove_cv&lt;typename std::result_of&lt;Func(U...)&gt;::type&gt;::type&gt;::type;
#endif

} // namespace Catch

namespace mpl_{
    struct na;
}

// end catch_meta.hpp
namespace Catch {

template&lt;typename C&gt;
class TestInvokerAsMethod : public ITestInvoker {
    void (C::*m_testAsMethod)();
public:
    TestInvokerAsMethod( void (C::*testAsMethod)() ) noexcept : m_testAsMethod( testAsMethod ) {}

    void invoke() const override {
        C obj;
        (obj.*m_testAsMethod)();
    }
};

auto makeTestInvoker( void(*testAsFunction)() ) noexcept -&gt; ITestInvoker*;

template&lt;typename C&gt;
auto makeTestInvoker( void (C::*testAsMethod)() ) noexcept -&gt; ITestInvoker* {
    return new(std::nothrow) TestInvokerAsMethod&lt;C&gt;( testAsMethod );
}

struct NameAndTags {
    NameAndTags( StringRef const&amp; name_ = StringRef(), StringRef const&amp; tags_ = StringRef() ) noexcept;
    StringRef name;
    StringRef tags;
};

struct AutoReg : NonCopyable {
    AutoReg( ITestInvoker* invoker, SourceLineInfo const&amp; lineInfo, StringRef const&amp; classOrMethod, NameAndTags const&amp; nameAndTags ) noexcept;
    ~AutoReg();
};

} // end namespace Catch

#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TESTCASE_NO_REGISTRATION( TestName, ... ) \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION( TestName, ClassName, ... ) \
        namespace{                        \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName) { \
                void test();              \
            };                            \
        }                                 \
        void TestName::test()
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( TestName, TestFunc, Name, Tags, Signature, ... )  \
        INTERNAL_CATCH_DEFINE_SIG_TEST(TestFunc, INTERNAL_CATCH_REMOVE_PARENS(Signature))
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( TestNameClass, TestName, ClassName, Name, Tags, Signature, ... )    \
        namespace{                                                                                  \
            namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName) {                                      \
            INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
        }                                                                                           \
        }                                                                                           \
        INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(Name, Tags, ...) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(Name, Tags, ...) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(Name, Tags, Signature, ...) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(Name, Tags, Signature, ...) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION( ClassName, Name, Tags,... ) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION( ClassName, Name, Tags,... ) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ ) )
    #endif

    #ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION( ClassName, Name, Tags, Signature, ... ) \
            INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ )
    #else
        #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION( ClassName, Name, Tags, Signature, ... ) \
            INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ ) )
    #endif
#endif

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TESTCASE2( TestName, ... ) \
        static void TestName(); \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &amp;TestName ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE( ... ) \
        INTERNAL_CATCH_TESTCASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_METHOD_AS_TEST_CASE( QualifiedMethod, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &amp;QualifiedMethod ), CATCH_INTERNAL_LINEINFO, "&amp;" #QualifiedMethod, Catch::NameAndTags{ __VA_ARGS__ } ); } /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEST_CASE_METHOD2( TestName, ClassName, ... )\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        namespace{ \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName) { \
                void test(); \
            }; \
            Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar ) ( Catch::makeTestInvoker( &amp;TestName::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        } \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        void TestName::test()
    #define INTERNAL_CATCH_TEST_CASE_METHOD( ClassName, ... ) \
        INTERNAL_CATCH_TEST_CASE_METHOD2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), ClassName, __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_REGISTER_TESTCASE( Function, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( Function ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ __VA_ARGS__ } ); /* NOLINT */ \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_2(TestName, TestFunc, Name, Tags, Signature, ... )\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        INTERNAL_CATCH_DECLARE_SIG_TEST(TestFunc, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){\
            INTERNAL_CATCH_TYPE_GEN\
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            INTERNAL_CATCH_NTTP_REG_GEN(TestFunc,INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template&lt;typename...Types&gt; \
            struct TestName{\
                TestName(){\
                    int index = 0;                                    \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, __VA_ARGS__)};\
                    using expander = int[];\
                    (void)expander{(reg_test(Types{}, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index]), Tags } ), index++)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
            TestName&lt;INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(__VA_ARGS__)&gt;();\
            return 0;\
        }();\
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        INTERNAL_CATCH_DEFINE_SIG_TEST(TestFunc,INTERNAL_CATCH_REMOVE_PARENS(Signature))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE(Name, Tags, ...) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE(Name, Tags, ...) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename TestType, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG(Name, Tags, Signature, ...) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG(Name, Tags, Signature, ...) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(TestName, TestFuncName, Name, Tags, Signature, TmplTypes, TypesList) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION                      \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS                      \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS                \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS              \
        template&lt;typename TestType&gt; static void TestFuncName();       \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName) {                                     \
            INTERNAL_CATCH_TYPE_GEN                                                  \
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))         \
            template&lt;typename... Types&gt;                               \
            struct TestName {                                         \
                void reg_tests() {                                          \
                    int index = 0;                                    \
                    using expander = int[];                           \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TmplTypes))};\
                    constexpr char const* types_list[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TypesList))};\
                    constexpr auto num_types = sizeof(types_list) / sizeof(types_list[0]);\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &amp;TestFuncName&lt;Types&gt; ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index / num_types]) + "&lt;" + std::string(types_list[index % num_types]) + "&gt;", Tags } ), index++)... };/* NOLINT */\
                }                                                     \
            };                                                        \
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){ \
                using TestInit = typename create&lt;TestName, decltype(get_wrapper&lt;INTERNAL_CATCH_REMOVE_PARENS(TmplTypes)&gt;()), TypeList&lt;INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(INTERNAL_CATCH_REMOVE_PARENS(TypesList))&gt;&gt;::type; \
                TestInit t;                                           \
                t.reg_tests();                                        \
                return 0;                                             \
            }();                                                      \
        }                                                             \
        }                                                             \
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION                       \
        template&lt;typename TestType&gt;                                   \
        static void TestFuncName()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE(Name, Tags, ...)\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename T,__VA_ARGS__)
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE(Name, Tags, ...)\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, typename T, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG(Name, Tags, Signature, ...)\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__)
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG(Name, Tags, Signature, ...)\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_2(TestName, TestFunc, Name, Tags, TmplList)\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template&lt;typename TestType&gt; static void TestFunc();       \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){\
        INTERNAL_CATCH_TYPE_GEN\
        template&lt;typename... Types&gt;                               \
        struct TestName {                                         \
            void reg_tests() {                                          \
                int index = 0;                                    \
                using expander = int[];                           \
                (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &amp;TestFunc&lt;Types&gt; ), CATCH_INTERNAL_LINEINFO, Catch::StringRef(), Catch::NameAndTags{ Name " - " + std::string(INTERNAL_CATCH_STRINGIZE(TmplList)) + " - " + std::to_string(index), Tags } ), index++)... };/* NOLINT */\
            }                                                     \
        };\
        static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){ \
                using TestInit = typename convert&lt;TestName, TmplList&gt;::type; \
                TestInit t;                                           \
                t.reg_tests();                                        \
                return 0;                                             \
            }();                                                      \
        }}\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION                       \
        template&lt;typename TestType&gt;                                   \
        static void TestFunc()

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE(Name, Tags, TmplList) \
        INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), Name, Tags, TmplList )

    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( TestNameClass, TestName, ClassName, Name, Tags, Signature, ... ) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){ \
            INTERNAL_CATCH_TYPE_GEN\
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            INTERNAL_CATCH_DECLARE_SIG_TEST_METHOD(TestName, ClassName, INTERNAL_CATCH_REMOVE_PARENS(Signature));\
            INTERNAL_CATCH_NTTP_REG_METHOD_GEN(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template&lt;typename...Types&gt; \
            struct TestNameClass{\
                TestNameClass(){\
                    int index = 0;                                    \
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, __VA_ARGS__)};\
                    using expander = int[];\
                    (void)expander{(reg_test(Types{}, #ClassName, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index]), Tags } ), index++)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                TestNameClass&lt;INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(__VA_ARGS__)&gt;();\
                return 0;\
        }();\
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        INTERNAL_CATCH_DEFINE_SIG_TEST_METHOD(TestName, INTERNAL_CATCH_REMOVE_PARENS(Signature))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( ClassName, Name, Tags,... ) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( ClassName, Name, Tags,... ) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, typename T, __VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... ) \
        INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... ) \
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____C_L_A_S_S____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ) , ClassName, Name, Tags, Signature, __VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2(TestNameClass, TestName, ClassName, Name, Tags, Signature, TmplTypes, TypesList)\
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_ZERO_VARIADIC_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template&lt;typename TestType&gt; \
            struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName &lt;TestType&gt;) { \
                void test();\
            };\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestNameClass) {\
            INTERNAL_CATCH_TYPE_GEN                  \
            INTERNAL_CATCH_NTTP_GEN(INTERNAL_CATCH_REMOVE_PARENS(Signature))\
            template&lt;typename...Types&gt;\
            struct TestNameClass{\
                void reg_tests(){\
                    int index = 0;\
                    using expander = int[];\
                    constexpr char const* tmpl_types[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TmplTypes))};\
                    constexpr char const* types_list[] = {CATCH_REC_LIST(INTERNAL_CATCH_STRINGIZE_WITHOUT_PARENS, INTERNAL_CATCH_REMOVE_PARENS(TypesList))};\
                    constexpr auto num_types = sizeof(types_list) / sizeof(types_list[0]);\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &amp;TestName&lt;Types&gt;::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ Name " - " + std::string(tmpl_types[index / num_types]) + "&lt;" + std::string(types_list[index % num_types]) + "&gt;", Tags } ), index++)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                using TestInit = typename create&lt;TestNameClass, decltype(get_wrapper&lt;INTERNAL_CATCH_REMOVE_PARENS(TmplTypes)&gt;()), TypeList&lt;INTERNAL_CATCH_MAKE_TYPE_LISTS_FROM_TYPES(INTERNAL_CATCH_REMOVE_PARENS(TypesList))&gt;&gt;::type;\
                TestInit t;\
                t.reg_tests();\
                return 0;\
            }(); \
        }\
        }\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        template&lt;typename TestType&gt; \
        void TestName&lt;TestType&gt;::test()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( ClassName, Name, Tags, ... )\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, typename T, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( ClassName, Name, Tags, ... )\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, typename T,__VA_ARGS__ ) )
#endif

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... )\
        INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, Signature, __VA_ARGS__ )
#else
    #define INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( ClassName, Name, Tags, Signature, ... )\
        INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, Signature,__VA_ARGS__ ) )
#endif

    #define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD_2( TestNameClass, TestName, ClassName, Name, Tags, TmplList) \
        CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
        CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
        CATCH_INTERNAL_SUPPRESS_UNUSED_TEMPLATE_WARNINGS \
        template&lt;typename TestType&gt; \
        struct TestName : INTERNAL_CATCH_REMOVE_PARENS(ClassName &lt;TestType&gt;) { \
            void test();\
        };\
        namespace {\
        namespace INTERNAL_CATCH_MAKE_NAMESPACE(TestName){ \
            INTERNAL_CATCH_TYPE_GEN\
            template&lt;typename...Types&gt;\
            struct TestNameClass{\
                void reg_tests(){\
                    int index = 0;\
                    using expander = int[];\
                    (void)expander{(Catch::AutoReg( Catch::makeTestInvoker( &amp;TestName&lt;Types&gt;::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ Name " - " + std::string(INTERNAL_CATCH_STRINGIZE(TmplList)) + " - " + std::to_string(index), Tags } ), index++)... };/* NOLINT */ \
                }\
            };\
            static int INTERNAL_CATCH_UNIQUE_NAME( globalRegistrar ) = [](){\
                using TestInit = typename convert&lt;TestNameClass, TmplList&gt;::type;\
                TestInit t;\
                t.reg_tests();\
                return 0;\
            }(); \
        }}\
        CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        template&lt;typename TestType&gt; \
        void TestName&lt;TestType&gt;::test()

#define INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD(ClassName, Name, Tags, TmplList) \
        INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD_2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____ ), INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_M_P_L_A_T_E____T_E_S_T____F_U_N_C____ ), ClassName, Name, Tags, TmplList )

// end catch_test_registry.h
// start catch_capture.hpp

// start catch_assertionhandler.h

// start catch_assertioninfo.h

// start catch_result_type.h

namespace Catch {

    // ResultWas::OfType enum
    struct ResultWas { enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,

        FailureBit = 0x10,

        ExpressionFailed = FailureBit | 1,
        ExplicitFailure = FailureBit | 2,

        Exception = 0x100 | FailureBit,

        ThrewException = Exception | 1,
        DidntThrowException = Exception | 2,

        FatalErrorCondition = 0x200 | FailureBit

    }; };

    bool isOk( ResultWas::OfType resultType );
    bool isJustInfo( int flags );

    // ResultDisposition::Flags enum
    struct ResultDisposition { enum Flags {
        Normal = 0x01,

        ContinueOnFailure = 0x02,   // Failures fail test, but execution continues
        FalseTest = 0x04,           // Prefix expression with !
        SuppressFail = 0x08         // Failures are reported but do not fail the test
    }; };

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs );

    bool shouldContinueOnFailure( int flags );
    inline bool isFalseTest( int flags ) { return ( flags &amp; ResultDisposition::FalseTest ) != 0; }
    bool shouldSuppressFailure( int flags );

} // end namespace Catch

// end catch_result_type.h
namespace Catch {

    struct AssertionInfo
    {
        StringRef macroName;
        SourceLineInfo lineInfo;
        StringRef capturedExpression;
        ResultDisposition::Flags resultDisposition;

        // We want to delete this constructor but a compiler bug in 4.8 means
        // the struct is then treated as non-aggregate
        //AssertionInfo() = delete;
    };

} // end namespace Catch

// end catch_assertioninfo.h
// start catch_decomposer.h

// start catch_tostring.h

#include &lt;vector&gt;
#include &lt;cstddef&gt;
#include &lt;type_traits&gt;
#include &lt;string&gt;
// start catch_stream.h

#include &lt;iosfwd&gt;
#include &lt;cstddef&gt;
#include &lt;ostream&gt;

namespace Catch {

    std::ostream&amp; cout();
    std::ostream&amp; cerr();
    std::ostream&amp; clog();

    class StringRef;

    struct IStream {
        virtual ~IStream();
        virtual std::ostream&amp; stream() const = 0;
    };

    auto makeStream( StringRef const &amp;filename ) -&gt; IStream const*;

    class ReusableStringStream : NonCopyable {
        std::size_t m_index;
        std::ostream* m_oss;
    public:
        ReusableStringStream();
        ~ReusableStringStream();

        auto str() const -&gt; std::string;

        template&lt;typename T&gt;
        auto operator &lt;&lt; ( T const&amp; value ) -&gt; ReusableStringStream&amp; {
            *m_oss &lt;&lt; value;
            return *this;
        }
        auto get() -&gt; std::ostream&amp; { return *m_oss; }
    };
}

// end catch_stream.h
// start catch_interfaces_enum_values_registry.h

#include &lt;vector&gt;

namespace Catch {

    namespace Detail {
        struct EnumInfo {
            StringRef m_name;
            std::vector&lt;std::pair&lt;int, StringRef&gt;&gt; m_values;

            ~EnumInfo();

            StringRef lookup( int value ) const;
        };
    } // namespace Detail

    struct IMutableEnumValuesRegistry {
        virtual ~IMutableEnumValuesRegistry();

        virtual Detail::EnumInfo const&amp; registerEnum( StringRef enumName, StringRef allEnums, std::vector&lt;int&gt; const&amp; values ) = 0;

        template&lt;typename E&gt;
        Detail::EnumInfo const&amp; registerEnum( StringRef enumName, StringRef allEnums, std::initializer_list&lt;E&gt; values ) {
            static_assert(sizeof(int) &gt;= sizeof(E), "Cannot serialize enum to int");
            std::vector&lt;int&gt; intValues;
            intValues.reserve( values.size() );
            for( auto enumValue : values )
                intValues.push_back( static_cast&lt;int&gt;( enumValue ) );
            return registerEnum( enumName, allEnums, intValues );
        }
    };

} // Catch

// end catch_interfaces_enum_values_registry.h

#ifdef CATCH_CONFIG_CPP17_STRING_VIEW
#include &lt;string_view&gt;
#endif

#ifdef __OBJC__
// start catch_objc_arc.hpp

#import &lt;Foundation/Foundation.h&gt;

#ifdef __has_feature
#define CATCH_ARC_ENABLED __has_feature(objc_arc)
#else
#define CATCH_ARC_ENABLED 0
#endif

void arcSafeRelease( NSObject* obj );
id performOptionalSelector( id obj, SEL sel );

#if !CATCH_ARC_ENABLED
inline void arcSafeRelease( NSObject* obj ) {
    [obj release];
}
inline id performOptionalSelector( id obj, SEL sel ) {
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED
#define CATCH_ARC_STRONG
#else
inline void arcSafeRelease( NSObject* ){}
inline id performOptionalSelector( id obj, SEL sel ) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#endif
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED __unsafe_unretained
#define CATCH_ARC_STRONG __strong
#endif

// end catch_objc_arc.hpp
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4180) // We attempt to stream a function (address) by const&amp;, which MSVC complains about but is harmless
#endif

namespace Catch {
    namespace Detail {

        extern const std::string unprintableString;

        std::string rawMemoryToString( const void *object, std::size_t size );

        template&lt;typename T&gt;
        std::string rawMemoryToString( const T&amp; object ) {
          return rawMemoryToString( &amp;object, sizeof(object) );
        }

        template&lt;typename T&gt;
        class IsStreamInsertable {
            template&lt;typename Stream, typename U&gt;
            static auto test(int)
                -&gt; decltype(std::declval&lt;Stream&amp;&gt;() &lt;&lt; std::declval&lt;U&gt;(), std::true_type());

            template&lt;typename, typename&gt;
            static auto test(...)-&gt;std::false_type;

        public:
            static const bool value = decltype(test&lt;std::ostream, const T&amp;&gt;(0))::value;
        };

        template&lt;typename E&gt;
        std::string convertUnknownEnumToString( E e );

        template&lt;typename T&gt;
        typename std::enable_if&lt;
            !std::is_enum&lt;T&gt;::value &amp;&amp; !std::is_base_of&lt;std::exception, T&gt;::value,
        std::string&gt;::type convertUnstreamable( T const&amp; ) {
            return Detail::unprintableString;
        }
        template&lt;typename T&gt;
        typename std::enable_if&lt;
            !std::is_enum&lt;T&gt;::value &amp;&amp; std::is_base_of&lt;std::exception, T&gt;::value,
         std::string&gt;::type convertUnstreamable(T const&amp; ex) {
            return ex.what();
        }

        template&lt;typename T&gt;
        typename std::enable_if&lt;
            std::is_enum&lt;T&gt;::value
        , std::string&gt;::type convertUnstreamable( T const&amp; value ) {
            return convertUnknownEnumToString( value );
        }

#if defined(_MANAGED)
        //! Convert a CLR string to a utf8 std::string
        template&lt;typename T&gt;
        std::string clrReferenceToString( T^ ref ) {
            if (ref == nullptr)
                return std::string("null");
            auto bytes = System::Text::Encoding::UTF8-&gt;GetBytes(ref-&gt;ToString());
            cli::pin_ptr&lt;System::Byte&gt; p = &amp;bytes[0];
            return std::string(reinterpret_cast&lt;char const *&gt;(p), bytes-&gt;Length);
        }
#endif

    } // namespace Detail

    // If we decide for C++14, change these to enable_if_ts
    template &lt;typename T, typename = void&gt;
    struct StringMaker {
        template &lt;typename Fake = T&gt;
        static
        typename std::enable_if&lt;::Catch::Detail::IsStreamInsertable&lt;Fake&gt;::value, std::string&gt;::type
            convert(const Fake&amp; value) {
                ReusableStringStream rss;
                // NB: call using the function-like syntax to avoid ambiguity with
                // user-defined templated operator&lt;&lt; under clang.
                rss.operator&lt;&lt;(value);
                return rss.str();
        }

        template &lt;typename Fake = T&gt;
        static
        typename std::enable_if&lt;!::Catch::Detail::IsStreamInsertable&lt;Fake&gt;::value, std::string&gt;::type
            convert( const Fake&amp; value ) {
#if !defined(CATCH_CONFIG_FALLBACK_STRINGIFIER)
            return Detail::convertUnstreamable(value);
#else
            return CATCH_CONFIG_FALLBACK_STRINGIFIER(value);
#endif
        }
    };

    namespace Detail {

        // This function dispatches all stringification requests inside of Catch.
        // Should be preferably called fully qualified, like ::Catch::Detail::stringify
        template &lt;typename T&gt;
        std::string stringify(const T&amp; e) {
            return ::Catch::StringMaker&lt;typename std::remove_cv&lt;typename std::remove_reference&lt;T&gt;::type&gt;::type&gt;::convert(e);
        }

        template&lt;typename E&gt;
        std::string convertUnknownEnumToString( E e ) {
            return ::Catch::Detail::stringify(static_cast&lt;typename std::underlying_type&lt;E&gt;::type&gt;(e));
        }

#if defined(_MANAGED)
        template &lt;typename T&gt;
        std::string stringify( T^ e ) {
            return ::Catch::StringMaker&lt;T^&gt;::convert(e);
        }
#endif

    } // namespace Detail

    // Some predefined specializations

    template&lt;&gt;
    struct StringMaker&lt;std::string&gt; {
        static std::string convert(const std::string&amp; str);
    };

#ifdef CATCH_CONFIG_CPP17_STRING_VIEW
    template&lt;&gt;
    struct StringMaker&lt;std::string_view&gt; {
        static std::string convert(std::string_view str);
    };
#endif

    template&lt;&gt;
    struct StringMaker&lt;char const *&gt; {
        static std::string convert(char const * str);
    };
    template&lt;&gt;
    struct StringMaker&lt;char *&gt; {
        static std::string convert(char * str);
    };

#ifdef CATCH_CONFIG_WCHAR
    template&lt;&gt;
    struct StringMaker&lt;std::wstring&gt; {
        static std::string convert(const std::wstring&amp; wstr);
    };

# ifdef CATCH_CONFIG_CPP17_STRING_VIEW
    template&lt;&gt;
    struct StringMaker&lt;std::wstring_view&gt; {
        static std::string convert(std::wstring_view str);
    };
# endif

    template&lt;&gt;
    struct StringMaker&lt;wchar_t const *&gt; {
        static std::string convert(wchar_t const * str);
    };
    template&lt;&gt;
    struct StringMaker&lt;wchar_t *&gt; {
        static std::string convert(wchar_t * str);
    };
#endif

    // TBD: Should we use `strnlen` to ensure that we don't go out of the buffer,
    //      while keeping string semantics?
    template&lt;int SZ&gt;
    struct StringMaker&lt;char[SZ]&gt; {
        static std::string convert(char const* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template&lt;int SZ&gt;
    struct StringMaker&lt;signed char[SZ]&gt; {
        static std::string convert(signed char const* str) {
            return ::Catch::Detail::stringify(std::string{ reinterpret_cast&lt;char const *&gt;(str) });
        }
    };
    template&lt;int SZ&gt;
    struct StringMaker&lt;unsigned char[SZ]&gt; {
        static std::string convert(unsigned char const* str) {
            return ::Catch::Detail::stringify(std::string{ reinterpret_cast&lt;char const *&gt;(str) });
        }
    };

#if defined(CATCH_CONFIG_CPP17_BYTE)
    template&lt;&gt;
    struct StringMaker&lt;std::byte&gt; {
        static std::string convert(std::byte value);
    };
#endif // defined(CATCH_CONFIG_CPP17_BYTE)
    template&lt;&gt;
    struct StringMaker&lt;int&gt; {
        static std::string convert(int value);
    };
    template&lt;&gt;
    struct StringMaker&lt;long&gt; {
        static std::string convert(long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;long long&gt; {
        static std::string convert(long long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned int&gt; {
        static std::string convert(unsigned int value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned long&gt; {
        static std::string convert(unsigned long value);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned long long&gt; {
        static std::string convert(unsigned long long value);
    };

    template&lt;&gt;
    struct StringMaker&lt;bool&gt; {
        static std::string convert(bool b);
    };

    template&lt;&gt;
    struct StringMaker&lt;char&gt; {
        static std::string convert(char c);
    };
    template&lt;&gt;
    struct StringMaker&lt;signed char&gt; {
        static std::string convert(signed char c);
    };
    template&lt;&gt;
    struct StringMaker&lt;unsigned char&gt; {
        static std::string convert(unsigned char c);
    };

    template&lt;&gt;
    struct StringMaker&lt;std::nullptr_t&gt; {
        static std::string convert(std::nullptr_t);
    };

    template&lt;&gt;
    struct StringMaker&lt;float&gt; {
        static std::string convert(float value);
        static int precision;
    };

    template&lt;&gt;
    struct StringMaker&lt;double&gt; {
        static std::string convert(double value);
        static int precision;
    };

    template &lt;typename T&gt;
    struct StringMaker&lt;T*&gt; {
        template &lt;typename U&gt;
        static std::string convert(U* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    template &lt;typename R, typename C&gt;
    struct StringMaker&lt;R C::*&gt; {
        static std::string convert(R C::* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

#if defined(_MANAGED)
    template &lt;typename T&gt;
    struct StringMaker&lt;T^&gt; {
        static std::string convert( T^ ref ) {
            return ::Catch::Detail::clrReferenceToString(ref);
        }
    };
#endif

    namespace Detail {
        template&lt;typename InputIterator, typename Sentinel = InputIterator&gt;
        std::string rangeToString(InputIterator first, Sentinel last) {
            ReusableStringStream rss;
            rss &lt;&lt; "{ ";
            if (first != last) {
                rss &lt;&lt; ::Catch::Detail::stringify(*first);
                for (++first; first != last; ++first)
                    rss &lt;&lt; ", " &lt;&lt; ::Catch::Detail::stringify(*first);
            }
            rss &lt;&lt; " }";
            return rss.str();
        }
    }

#ifdef __OBJC__
    template&lt;&gt;
    struct StringMaker&lt;NSString*&gt; {
        static std::string convert(NSString * nsstring) {
            if (!nsstring)
                return "nil";
            return std::string("@") + [nsstring UTF8String];
        }
    };
    template&lt;&gt;
    struct StringMaker&lt;NSObject*&gt; {
        static std::string convert(NSObject* nsObject) {
            return ::Catch::Detail::stringify([nsObject description]);
        }

    };
    namespace Detail {
        inline std::string stringify( NSString* nsstring ) {
            return StringMaker&lt;NSString*&gt;::convert( nsstring );
        }

    } // namespace Detail
#endif // __OBJC__

} // namespace Catch

//////////////////////////////////////////////////////
// Separate std-lib types stringification, so it can be selectively enabled
// This means that we do not bring in

#if defined(CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS)
#  define CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#  define CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER
#endif

// Separate std::pair specialization
#if defined(CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER)
#include &lt;utility&gt;
namespace Catch {
    template&lt;typename T1, typename T2&gt;
    struct StringMaker&lt;std::pair&lt;T1, T2&gt; &gt; {
        static std::string convert(const std::pair&lt;T1, T2&gt;&amp; pair) {
            ReusableStringStream rss;
            rss &lt;&lt; "{ "
                &lt;&lt; ::Catch::Detail::stringify(pair.first)
                &lt;&lt; ", "
                &lt;&lt; ::Catch::Detail::stringify(pair.second)
                &lt;&lt; " }";
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER

#if defined(CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER) &amp;&amp; defined(CATCH_CONFIG_CPP17_OPTIONAL)
#include &lt;optional&gt;
namespace Catch {
    template&lt;typename T&gt;
    struct StringMaker&lt;std::optional&lt;T&gt; &gt; {
        static std::string convert(const std::optional&lt;T&gt;&amp; optional) {
            ReusableStringStream rss;
            if (optional.has_value()) {
                rss &lt;&lt; ::Catch::Detail::stringify(*optional);
            } else {
                rss &lt;&lt; "{ }";
            }
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_OPTIONAL_STRINGMAKER

// Separate std::tuple specialization
#if defined(CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER)
#include &lt;tuple&gt;
namespace Catch {
    namespace Detail {
        template&lt;
            typename Tuple,
            std::size_t N = 0,
            bool = (N &lt; std::tuple_size&lt;Tuple&gt;::value)
            &gt;
            struct TupleElementPrinter {
            static void print(const Tuple&amp; tuple, std::ostream&amp; os) {
                os &lt;&lt; (N ? ", " : " ")
                    &lt;&lt; ::Catch::Detail::stringify(std::get&lt;N&gt;(tuple));
                TupleElementPrinter&lt;Tuple, N + 1&gt;::print(tuple, os);
            }
        };

        template&lt;
            typename Tuple,
            std::size_t N
        &gt;
            struct TupleElementPrinter&lt;Tuple, N, false&gt; {
            static void print(const Tuple&amp;, std::ostream&amp;) {}
        };

    }

    template&lt;typename ...Types&gt;
    struct StringMaker&lt;std::tuple&lt;Types...&gt;&gt; {
        static std::string convert(const std::tuple&lt;Types...&gt;&amp; tuple) {
            ReusableStringStream rss;
            rss &lt;&lt; '{';
            Detail::TupleElementPrinter&lt;std::tuple&lt;Types...&gt;&gt;::print(tuple, rss.get());
            rss &lt;&lt; " }";
            return rss.str();
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER

#if defined(CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER) &amp;&amp; defined(CATCH_CONFIG_CPP17_VARIANT)
#include &lt;variant&gt;
namespace Catch {
    template&lt;&gt;
    struct StringMaker&lt;std::monostate&gt; {
        static std::string convert(const std::monostate&amp;) {
            return "{ }";
        }
    };

    template&lt;typename... Elements&gt;
    struct StringMaker&lt;std::variant&lt;Elements...&gt;&gt; {
        static std::string convert(const std::variant&lt;Elements...&gt;&amp; variant) {
            if (variant.valueless_by_exception()) {
                return "{valueless variant}";
            } else {
                return std::visit(
                    [](const auto&amp; value) {
                        return ::Catch::Detail::stringify(value);
                    },
                    variant
                );
            }
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_VARIANT_STRINGMAKER

namespace Catch {
    // Import begin/ end from std here
    using std::begin;
    using std::end;

    namespace detail {
        template &lt;typename...&gt;
        struct void_type {
            using type = void;
        };

        template &lt;typename T, typename = void&gt;
        struct is_range_impl : std::false_type {
        };

        template &lt;typename T&gt;
        struct is_range_impl&lt;T, typename void_type&lt;decltype(begin(std::declval&lt;T&gt;()))&gt;::type&gt; : std::true_type {
        };
    } // namespace detail

    template &lt;typename T&gt;
    struct is_range : detail::is_range_impl&lt;T&gt; {
    };

#if defined(_MANAGED) // Managed types are never ranges
    template &lt;typename T&gt;
    struct is_range&lt;T^&gt; {
        static const bool value = false;
    };
#endif

    template&lt;typename Range&gt;
    std::string rangeToString( Range const&amp; range ) {
        return ::Catch::Detail::rangeToString( begin( range ), end( range ) );
    }

    // Handle vector&lt;bool&gt; specially
    template&lt;typename Allocator&gt;
    std::string rangeToString( std::vector&lt;bool, Allocator&gt; const&amp; v ) {
        ReusableStringStream rss;
        rss &lt;&lt; "{ ";
        bool first = true;
        for( bool b : v ) {
            if( first )
                first = false;
            else
                rss &lt;&lt; ", ";
            rss &lt;&lt; ::Catch::Detail::stringify( b );
        }
        rss &lt;&lt; " }";
        return rss.str();
    }

    template&lt;typename R&gt;
    struct StringMaker&lt;R, typename std::enable_if&lt;is_range&lt;R&gt;::value &amp;&amp; !::Catch::Detail::IsStreamInsertable&lt;R&gt;::value&gt;::type&gt; {
        static std::string convert( R const&amp; range ) {
            return rangeToString( range );
        }
    };

    template &lt;typename T, int SZ&gt;
    struct StringMaker&lt;T[SZ]&gt; {
        static std::string convert(T const(&amp;arr)[SZ]) {
            return rangeToString(arr);
        }
    };

} // namespace Catch

// Separate std::chrono::duration specialization
#if defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#include &lt;ctime&gt;
#include &lt;ratio&gt;
#include &lt;chrono&gt;

namespace Catch {

template &lt;class Ratio&gt;
struct ratio_string {
    static std::string symbol();
};

template &lt;class Ratio&gt;
std::string ratio_string&lt;Ratio&gt;::symbol() {
    Catch::ReusableStringStream rss;
    rss &lt;&lt; '[' &lt;&lt; Ratio::num &lt;&lt; '/'
        &lt;&lt; Ratio::den &lt;&lt; ']';
    return rss.str();
}
template &lt;&gt;
struct ratio_string&lt;std::atto&gt; {
    static std::string symbol();
};
template &lt;&gt;
struct ratio_string&lt;std::femto&gt; {
    static std::string symbol();
};
template &lt;&gt;
struct ratio_string&lt;std::pico&gt; {
    static std::string symbol();
};
template &lt;&gt;
struct ratio_string&lt;std::nano&gt; {
    static std::string symbol();
};
template &lt;&gt;
struct ratio_string&lt;std::micro&gt; {
    static std::string symbol();
};
template &lt;&gt;
struct ratio_string&lt;std::milli&gt; {
    static std::string symbol();
};

    ////////////
    // std::chrono::duration specializations
    template&lt;typename Value, typename Ratio&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, Ratio&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, Ratio&gt; const&amp; duration) {
            ReusableStringStream rss;
            rss &lt;&lt; duration.count() &lt;&lt; ' ' &lt;&lt; ratio_string&lt;Ratio&gt;::symbol() &lt;&lt; 's';
            return rss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;1&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;1&gt;&gt; const&amp; duration) {
            ReusableStringStream rss;
            rss &lt;&lt; duration.count() &lt;&lt; " s";
            return rss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;60&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;60&gt;&gt; const&amp; duration) {
            ReusableStringStream rss;
            rss &lt;&lt; duration.count() &lt;&lt; " m";
            return rss.str();
        }
    };
    template&lt;typename Value&gt;
    struct StringMaker&lt;std::chrono::duration&lt;Value, std::ratio&lt;3600&gt;&gt;&gt; {
        static std::string convert(std::chrono::duration&lt;Value, std::ratio&lt;3600&gt;&gt; const&amp; duration) {
            ReusableStringStream rss;
            rss &lt;&lt; duration.count() &lt;&lt; " h";
            return rss.str();
        }
    };

    ////////////
    // std::chrono::time_point specialization
    // Generic time_point cannot be specialized, only std::chrono::time_point&lt;system_clock&gt;
    template&lt;typename Clock, typename Duration&gt;
    struct StringMaker&lt;std::chrono::time_point&lt;Clock, Duration&gt;&gt; {
        static std::string convert(std::chrono::time_point&lt;Clock, Duration&gt; const&amp; time_point) {
            return ::Catch::Detail::stringify(time_point.time_since_epoch()) + " since epoch";
        }
    };
    // std::chrono::time_point&lt;system_clock&gt; specialization
    template&lt;typename Duration&gt;
    struct StringMaker&lt;std::chrono::time_point&lt;std::chrono::system_clock, Duration&gt;&gt; {
        static std::string convert(std::chrono::time_point&lt;std::chrono::system_clock, Duration&gt; const&amp; time_point) {
            auto converted = std::chrono::system_clock::to_time_t(time_point);

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&amp;timeInfo, &amp;converted);
#else
            std::tm* timeInfo = std::gmtime(&amp;converted);
#endif

            auto const timeStampSize = sizeof("2017-01-16T17:06:45Z");
            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &amp;timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }
    };
}
#endif // CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER

#define INTERNAL_CATCH_REGISTER_ENUM( enumName, ... ) \
namespace Catch { \
    template&lt;&gt; struct StringMaker&lt;enumName&gt; { \
        static std::string convert( enumName value ) { \
            static const auto&amp; enumInfo = ::Catch::getMutableRegistryHub().getMutableEnumValuesRegistry().registerEnum( #enumName, #__VA_ARGS__, { __VA_ARGS__ } ); \
            return static_cast&lt;std::string&gt;(enumInfo.lookup( static_cast&lt;int&gt;( value ) )); \
        } \
    }; \
}

#define CATCH_REGISTER_ENUM( enumName, ... ) INTERNAL_CATCH_REGISTER_ENUM( enumName, __VA_ARGS__ )

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_tostring.h
#include &lt;iosfwd&gt;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4389) // '==' : signed/unsigned mismatch
#pragma warning(disable:4018) // more "signed/unsigned mismatch"
#pragma warning(disable:4312) // Converting int to T* using reinterpret_cast (issue on x64 platform)
#pragma warning(disable:4180) // qualifier applied to function type has no meaning
#pragma warning(disable:4800) // Forcing result to true or false
#endif

namespace Catch {

    struct ITransientExpression {
        auto isBinaryExpression() const -&gt; bool { return m_isBinaryExpression; }
        auto getResult() const -&gt; bool { return m_result; }
        virtual void streamReconstructedExpression( std::ostream &amp;os ) const = 0;

        ITransientExpression( bool isBinaryExpression, bool result )
        :   m_isBinaryExpression( isBinaryExpression ),
            m_result( result )
        {}

        // We don't actually need a virtual destructor, but many static analysers
        // complain if it's not here :-(
        virtual ~ITransientExpression();

        bool m_isBinaryExpression;
        bool m_result;

    };

    void formatReconstructedExpression( std::ostream &amp;os, std::string const&amp; lhs, StringRef op, std::string const&amp; rhs );

    template&lt;typename LhsT, typename RhsT&gt;
    class BinaryExpr  : public ITransientExpression {
        LhsT m_lhs;
        StringRef m_op;
        RhsT m_rhs;

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            formatReconstructedExpression
                    ( os, Catch::Detail::stringify( m_lhs ), m_op, Catch::Detail::stringify( m_rhs ) );
        }

    public:
        BinaryExpr( bool comparisonResult, LhsT lhs, StringRef op, RhsT rhs )
        :   ITransientExpression{ true, comparisonResult },
            m_lhs( lhs ),
            m_op( op ),
            m_rhs( rhs )
        {}

        template&lt;typename T&gt;
        auto operator &amp;&amp; ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator || ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator == ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator != ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator &gt; ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator &lt; ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator &gt;= ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename T&gt;
        auto operator &lt;= ( T ) const -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;T&gt;::value,
            "chained comparisons are not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }
    };

    template&lt;typename LhsT&gt;
    class UnaryExpr : public ITransientExpression {
        LhsT m_lhs;

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            os &lt;&lt; Catch::Detail::stringify( m_lhs );
        }

    public:
        explicit UnaryExpr( LhsT lhs )
        :   ITransientExpression{ false, static_cast&lt;bool&gt;(lhs) },
            m_lhs( lhs )
        {}
    };

    // Specialised comparison functions to handle equality comparisons between ints and pointers (NULL deduces as an int)
    template&lt;typename LhsT, typename RhsT&gt;
    auto compareEqual( LhsT const&amp; lhs, RhsT const&amp; rhs ) -&gt; bool { return static_cast&lt;bool&gt;(lhs == rhs); }
    template&lt;typename T&gt;
    auto compareEqual( T* const&amp; lhs, int rhs ) -&gt; bool { return lhs == reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareEqual( T* const&amp; lhs, long rhs ) -&gt; bool { return lhs == reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareEqual( int lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) == rhs; }
    template&lt;typename T&gt;
    auto compareEqual( long lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) == rhs; }

    template&lt;typename LhsT, typename RhsT&gt;
    auto compareNotEqual( LhsT const&amp; lhs, RhsT&amp;&amp; rhs ) -&gt; bool { return static_cast&lt;bool&gt;(lhs != rhs); }
    template&lt;typename T&gt;
    auto compareNotEqual( T* const&amp; lhs, int rhs ) -&gt; bool { return lhs != reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareNotEqual( T* const&amp; lhs, long rhs ) -&gt; bool { return lhs != reinterpret_cast&lt;void const*&gt;( rhs ); }
    template&lt;typename T&gt;
    auto compareNotEqual( int lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) != rhs; }
    template&lt;typename T&gt;
    auto compareNotEqual( long lhs, T* const&amp; rhs ) -&gt; bool { return reinterpret_cast&lt;void const*&gt;( lhs ) != rhs; }

    template&lt;typename LhsT&gt;
    class ExprLhs {
        LhsT m_lhs;
    public:
        explicit ExprLhs( LhsT lhs ) : m_lhs( lhs ) {}

        template&lt;typename RhsT&gt;
        auto operator == ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { compareEqual( m_lhs, rhs ), m_lhs, "==", rhs };
        }
        auto operator == ( bool rhs ) -&gt; BinaryExpr&lt;LhsT, bool&gt; const {
            return { m_lhs == rhs, m_lhs, "==", rhs };
        }

        template&lt;typename RhsT&gt;
        auto operator != ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { compareNotEqual( m_lhs, rhs ), m_lhs, "!=", rhs };
        }
        auto operator != ( bool rhs ) -&gt; BinaryExpr&lt;LhsT, bool&gt; const {
            return { m_lhs != rhs, m_lhs, "!=", rhs };
        }

        template&lt;typename RhsT&gt;
        auto operator &gt; ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs &gt; rhs), m_lhs, "&gt;", rhs };
        }
        template&lt;typename RhsT&gt;
        auto operator &lt; ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs &lt; rhs), m_lhs, "&lt;", rhs };
        }
        template&lt;typename RhsT&gt;
        auto operator &gt;= ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs &gt;= rhs), m_lhs, "&gt;=", rhs };
        }
        template&lt;typename RhsT&gt;
        auto operator &lt;= ( RhsT const&amp; rhs ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs &lt;= rhs), m_lhs, "&lt;=", rhs };
        }
        template &lt;typename RhsT&gt;
        auto operator | (RhsT const&amp; rhs) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs | rhs), m_lhs, "|", rhs };
        }
        template &lt;typename RhsT&gt;
        auto operator &amp; (RhsT const&amp; rhs) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs &amp; rhs), m_lhs, "&amp;", rhs };
        }
        template &lt;typename RhsT&gt;
        auto operator ^ (RhsT const&amp; rhs) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            return { static_cast&lt;bool&gt;(m_lhs ^ rhs), m_lhs, "^", rhs };
        }

        template&lt;typename RhsT&gt;
        auto operator &amp;&amp; ( RhsT const&amp; ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;RhsT&gt;::value,
            "operator&amp;&amp; is not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        template&lt;typename RhsT&gt;
        auto operator || ( RhsT const&amp; ) -&gt; BinaryExpr&lt;LhsT, RhsT const&amp;&gt; const {
            static_assert(always_false&lt;RhsT&gt;::value,
            "operator|| is not supported inside assertions, "
            "wrap the expression inside parentheses, or decompose it");
        }

        auto makeUnaryExpr() const -&gt; UnaryExpr&lt;LhsT&gt; {
            return UnaryExpr&lt;LhsT&gt;{ m_lhs };
        }
    };

    void handleExpression( ITransientExpression const&amp; expr );

    template&lt;typename T&gt;
    void handleExpression( ExprLhs&lt;T&gt; const&amp; expr ) {
        handleExpression( expr.makeUnaryExpr() );
    }

    struct Decomposer {
        template&lt;typename T&gt;
        auto operator &lt;= ( T const&amp; lhs ) -&gt; ExprLhs&lt;T const&amp;&gt; {
            return ExprLhs&lt;T const&amp;&gt;{ lhs };
        }

        auto operator &lt;=( bool value ) -&gt; ExprLhs&lt;bool&gt; {
            return ExprLhs&lt;bool&gt;{ value };
        }
    };

} // end namespace Catch

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_decomposer.h
// start catch_interfaces_capture.h

#include &lt;string&gt;
#include &lt;chrono&gt;

namespace Catch {

    class AssertionResult;
    struct AssertionInfo;
    struct SectionInfo;
    struct SectionEndInfo;
    struct MessageInfo;
    struct MessageBuilder;
    struct Counts;
    struct AssertionReaction;
    struct SourceLineInfo;

    struct ITransientExpression;
    struct IGeneratorTracker;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    struct BenchmarkInfo;
    template &lt;typename Duration = std::chrono::duration&lt;double, std::nano&gt;&gt;
    struct BenchmarkStats;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    struct IResultCapture {

        virtual ~IResultCapture();

        virtual bool sectionStarted(    SectionInfo const&amp; sectionInfo,
                                        Counts&amp; assertions ) = 0;
        virtual void sectionEnded( SectionEndInfo const&amp; endInfo ) = 0;
        virtual void sectionEndedEarly( SectionEndInfo const&amp; endInfo ) = 0;

        virtual auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const&amp; lineInfo ) -&gt; IGeneratorTracker&amp; = 0;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        virtual void benchmarkPreparing( std::string const&amp; name ) = 0;
        virtual void benchmarkStarting( BenchmarkInfo const&amp; info ) = 0;
        virtual void benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; stats ) = 0;
        virtual void benchmarkFailed( std::string const&amp; error ) = 0;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        virtual void pushScopedMessage( MessageInfo const&amp; message ) = 0;
        virtual void popScopedMessage( MessageInfo const&amp; message ) = 0;

        virtual void emplaceUnscopedMessage( MessageBuilder const&amp; builder ) = 0;

        virtual void handleFatalErrorCondition( StringRef message ) = 0;

        virtual void handleExpr
                (   AssertionInfo const&amp; info,
                    ITransientExpression const&amp; expr,
                    AssertionReaction&amp; reaction ) = 0;
        virtual void handleMessage
                (   AssertionInfo const&amp; info,
                    ResultWas::OfType resultType,
                    StringRef const&amp; message,
                    AssertionReaction&amp; reaction ) = 0;
        virtual void handleUnexpectedExceptionNotThrown
                (   AssertionInfo const&amp; info,
                    AssertionReaction&amp; reaction ) = 0;
        virtual void handleUnexpectedInflightException
                (   AssertionInfo const&amp; info,
                    std::string const&amp; message,
                    AssertionReaction&amp; reaction ) = 0;
        virtual void handleIncomplete
                (   AssertionInfo const&amp; info ) = 0;
        virtual void handleNonExpr
                (   AssertionInfo const &amp;info,
                    ResultWas::OfType resultType,
                    AssertionReaction &amp;reaction ) = 0;

        virtual bool lastAssertionPassed() = 0;
        virtual void assertionPassed() = 0;

        // Deprecated, do not use:
        virtual std::string getCurrentTestName() const = 0;
        virtual const AssertionResult* getLastResult() const = 0;
        virtual void exceptionEarlyReported() = 0;
    };

    IResultCapture&amp; getResultCapture();
}

// end catch_interfaces_capture.h
namespace Catch {

    struct TestFailureException{};
    struct AssertionResultData;
    struct IResultCapture;
    class RunContext;

    class LazyExpression {
        friend class AssertionHandler;
        friend struct AssertionStats;
        friend class RunContext;

        ITransientExpression const* m_transientExpression = nullptr;
        bool m_isNegated;
    public:
        LazyExpression( bool isNegated );
        LazyExpression( LazyExpression const&amp; other );
        LazyExpression&amp; operator = ( LazyExpression const&amp; ) = delete;

        explicit operator bool() const;

        friend auto operator &lt;&lt; ( std::ostream&amp; os, LazyExpression const&amp; lazyExpr ) -&gt; std::ostream&amp;;
    };

    struct AssertionReaction {
        bool shouldDebugBreak = false;
        bool shouldThrow = false;
    };

    class AssertionHandler {
        AssertionInfo m_assertionInfo;
        AssertionReaction m_reaction;
        bool m_completed = false;
        IResultCapture&amp; m_resultCapture;

    public:
        AssertionHandler
            (   StringRef const&amp; macroName,
                SourceLineInfo const&amp; lineInfo,
                StringRef capturedExpression,
                ResultDisposition::Flags resultDisposition );
        ~AssertionHandler() {
            if ( !m_completed ) {
                m_resultCapture.handleIncomplete( m_assertionInfo );
            }
        }

        template&lt;typename T&gt;
        void handleExpr( ExprLhs&lt;T&gt; const&amp; expr ) {
            handleExpr( expr.makeUnaryExpr() );
        }
        void handleExpr( ITransientExpression const&amp; expr );

        void handleMessage(ResultWas::OfType resultType, StringRef const&amp; message);

        void handleExceptionThrownAsExpected();
        void handleUnexpectedExceptionNotThrown();
        void handleExceptionNotThrownAsExpected();
        void handleThrowingCallSkipped();
        void handleUnexpectedInflightException();

        void complete();
        void setCompleted();

        // query
        auto allowThrows() const -&gt; bool;
    };

    void handleExceptionMatchExpr( AssertionHandler&amp; handler, std::string const&amp; str, StringRef const&amp; matcherString );

} // namespace Catch

// end catch_assertionhandler.h
// start catch_message.h

#include &lt;string&gt;
#include &lt;vector&gt;

namespace Catch {

    struct MessageInfo {
        MessageInfo(    StringRef const&amp; _macroName,
                        SourceLineInfo const&amp; _lineInfo,
                        ResultWas::OfType _type );

        StringRef macroName;
        std::string message;
        SourceLineInfo lineInfo;
        ResultWas::OfType type;
        unsigned int sequence;

        bool operator == ( MessageInfo const&amp; other ) const;
        bool operator &lt; ( MessageInfo const&amp; other ) const;
    private:
        static unsigned int globalCount;
    };

    struct MessageStream {

        template&lt;typename T&gt;
        MessageStream&amp; operator &lt;&lt; ( T const&amp; value ) {
            m_stream &lt;&lt; value;
            return *this;
        }

        ReusableStringStream m_stream;
    };

    struct MessageBuilder : MessageStream {
        MessageBuilder( StringRef const&amp; macroName,
                        SourceLineInfo const&amp; lineInfo,
                        ResultWas::OfType type );

        template&lt;typename T&gt;
        MessageBuilder&amp; operator &lt;&lt; ( T const&amp; value ) {
            m_stream &lt;&lt; value;
            return *this;
        }

        MessageInfo m_info;
    };

    class ScopedMessage {
    public:
        explicit ScopedMessage( MessageBuilder const&amp; builder );
        ScopedMessage( ScopedMessage&amp; duplicate ) = delete;
        ScopedMessage( ScopedMessage&amp;&amp; old );
        ~ScopedMessage();

        MessageInfo m_info;
        bool m_moved;
    };

    class Capturer {
        std::vector&lt;MessageInfo&gt; m_messages;
        IResultCapture&amp; m_resultCapture = getResultCapture();
        size_t m_captured = 0;
    public:
        Capturer( StringRef macroName, SourceLineInfo const&amp; lineInfo, ResultWas::OfType resultType, StringRef names );
        ~Capturer();

        void captureValue( size_t index, std::string const&amp; value );

        template&lt;typename T&gt;
        void captureValues( size_t index, T const&amp; value ) {
            captureValue( index, Catch::Detail::stringify( value ) );
        }

        template&lt;typename T, typename... Ts&gt;
        void captureValues( size_t index, T const&amp; value, Ts const&amp;... values ) {
            captureValue( index, Catch::Detail::stringify(value) );
            captureValues( index+1, values... );
        }
    };

} // end namespace Catch

// end catch_message.h
#if !defined(CATCH_CONFIG_DISABLE)

#if !defined(CATCH_CONFIG_DISABLE_STRINGIFICATION)
  #define CATCH_INTERNAL_STRINGIFY(...) #__VA_ARGS__
#else
  #define CATCH_INTERNAL_STRINGIFY(...) "Disabled by CATCH_CONFIG_DISABLE_STRINGIFICATION"
#endif

#if defined(CATCH_CONFIG_FAST_COMPILE) || defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)

///////////////////////////////////////////////////////////////////////////////
// Another way to speed-up compilation is to omit local try-catch for REQUIRE*
// macros.
#define INTERNAL_CATCH_TRY
#define INTERNAL_CATCH_CATCH( capturer )

#else // CATCH_CONFIG_FAST_COMPILE

#define INTERNAL_CATCH_TRY try
#define INTERNAL_CATCH_CATCH( handler ) catch(...) { handler.handleUnexpectedInflightException(); }

#endif

#define INTERNAL_CATCH_REACT( handler ) handler.complete();

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( macroName, resultDisposition, ... ) \
    do { \
        CATCH_INTERNAL_IGNORE_BUT_WARN(__VA_ARGS__); \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        INTERNAL_CATCH_TRY { \
            CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
            CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            catchAssertionHandler.handleExpr( Catch::Decomposer() &lt;= __VA_ARGS__ ); \
            CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( (void)0, (false) &amp;&amp; static_cast&lt;bool&gt;( !!(__VA_ARGS__) ) )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_IF( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ELSE( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( !Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition ); \
        try { \
            static_cast&lt;void&gt;(__VA_ARGS__); \
            catchAssertionHandler.handleExceptionNotThrownAsExpected(); \
        } \
        catch( ... ) { \
            catchAssertionHandler.handleUnexpectedInflightException(); \
        } \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( macroName, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__), resultDisposition); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( macroName, exceptionType, resultDisposition, expr ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(expr) ", " CATCH_INTERNAL_STRINGIFY(exceptionType), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(expr); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( exceptionType const&amp; ) { \
                catchAssertionHandler.handleExceptionThrownAsExpected(); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleUnexpectedInflightException(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( macroName, messageType, resultDisposition, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::StringRef(), resultDisposition ); \
        catchAssertionHandler.handleMessage( messageType, ( Catch::MessageStream() &lt;&lt; __VA_ARGS__ + ::Catch::StreamEndStop() ).m_stream.str() ); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_CAPTURE( varName, macroName, ... ) \
    auto varName = Catch::Capturer( macroName, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info, #__VA_ARGS__ ); \
    varName.captureValues( 0, __VA_ARGS__ )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_INFO( macroName, log ) \
    Catch::ScopedMessage INTERNAL_CATCH_UNIQUE_NAME( scopedMessage )( Catch::MessageBuilder( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) &lt;&lt; log );

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_UNSCOPED_INFO( macroName, log ) \
    Catch::getResultCapture().emplaceUnscopedMessage( Catch::MessageBuilder( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) &lt;&lt; log )

///////////////////////////////////////////////////////////////////////////////
// Although this is matcher-based, it can be used with just a string
#define INTERNAL_CATCH_THROWS_STR_MATCHES( macroName, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( ... ) { \
                Catch::handleExceptionMatchExpr( catchAssertionHandler, matcher, #matcher##_catch_sr ); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

#endif // CATCH_CONFIG_DISABLE

// end catch_capture.hpp
// start catch_section.h

// start catch_section_info.h

// start catch_totals.h

#include &lt;cstddef&gt;

namespace Catch {

    struct Counts {
        Counts operator - ( Counts const&amp; other ) const;
        Counts&amp; operator += ( Counts const&amp; other );

        std::size_t total() const;
        bool allPassed() const;
        bool allOk() const;

        std::size_t passed = 0;
        std::size_t failed = 0;
        std::size_t failedButOk = 0;
    };

    struct Totals {

        Totals operator - ( Totals const&amp; other ) const;
        Totals&amp; operator += ( Totals const&amp; other );

        Totals delta( Totals const&amp; prevTotals ) const;

        int error = 0;
        Counts assertions;
        Counts testCases;
    };
}

// end catch_totals.h
#include &lt;string&gt;

namespace Catch {

    struct SectionInfo {
        SectionInfo
            (   SourceLineInfo const&amp; _lineInfo,
                std::string const&amp; _name );

        // Deprecated
        SectionInfo
            (   SourceLineInfo const&amp; _lineInfo,
                std::string const&amp; _name,
                std::string const&amp; ) : SectionInfo( _lineInfo, _name ) {}

        std::string name;
        std::string description; // !Deprecated: this will always be empty
        SourceLineInfo lineInfo;
    };

    struct SectionEndInfo {
        SectionInfo sectionInfo;
        Counts prevAssertions;
        double durationInSeconds;
    };

} // end namespace Catch

// end catch_section_info.h
// start catch_timer.h

#include &lt;cstdint&gt;

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -&gt; uint64_t;
    auto getEstimatedClockResolution() -&gt; uint64_t;

    class Timer {
        uint64_t m_nanoseconds = 0;
    public:
        void start();
        auto getElapsedNanoseconds() const -&gt; uint64_t;
        auto getElapsedMicroseconds() const -&gt; uint64_t;
        auto getElapsedMilliseconds() const -&gt; unsigned int;
        auto getElapsedSeconds() const -&gt; double;
    };

} // namespace Catch

// end catch_timer.h
#include &lt;string&gt;

namespace Catch {

    class Section : NonCopyable {
    public:
        Section( SectionInfo const&amp; info );
        ~Section();

        // This indicates whether the section should be executed or not
        explicit operator bool() const;

    private:
        SectionInfo m_info;

        std::string m_name;
        Counts m_assertions;
        bool m_sectionIncluded;
        Timer m_timer;
    };

} // end namespace Catch

#define INTERNAL_CATCH_SECTION( ... ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
    if( Catch::Section const&amp; INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, __VA_ARGS__ ) ) \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

#define INTERNAL_CATCH_DYNAMIC_SECTION( ... ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_UNUSED_WARNINGS \
    if( Catch::Section const&amp; INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, (Catch::ReusableStringStream() &lt;&lt; __VA_ARGS__).str() ) ) \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

// end catch_section.h
// start catch_interfaces_exception.h

// start catch_interfaces_registry_hub.h

#include &lt;string&gt;
#include &lt;memory&gt;

namespace Catch {

    class TestCase;
    struct ITestCaseRegistry;
    struct IExceptionTranslatorRegistry;
    struct IExceptionTranslator;
    struct IReporterRegistry;
    struct IReporterFactory;
    struct ITagAliasRegistry;
    struct IMutableEnumValuesRegistry;

    class StartupExceptionRegistry;

    using IReporterFactoryPtr = std::shared_ptr&lt;IReporterFactory&gt;;

    struct IRegistryHub {
        virtual ~IRegistryHub();

        virtual IReporterRegistry const&amp; getReporterRegistry() const = 0;
        virtual ITestCaseRegistry const&amp; getTestCaseRegistry() const = 0;
        virtual ITagAliasRegistry const&amp; getTagAliasRegistry() const = 0;
        virtual IExceptionTranslatorRegistry const&amp; getExceptionTranslatorRegistry() const = 0;

        virtual StartupExceptionRegistry const&amp; getStartupExceptionRegistry() const = 0;
    };

    struct IMutableRegistryHub {
        virtual ~IMutableRegistryHub();
        virtual void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) = 0;
        virtual void registerListener( IReporterFactoryPtr const&amp; factory ) = 0;
        virtual void registerTest( TestCase const&amp; testInfo ) = 0;
        virtual void registerTranslator( const IExceptionTranslator* translator ) = 0;
        virtual void registerTagAlias( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) = 0;
        virtual void registerStartupException() noexcept = 0;
        virtual IMutableEnumValuesRegistry&amp; getMutableEnumValuesRegistry() = 0;
    };

    IRegistryHub const&amp; getRegistryHub();
    IMutableRegistryHub&amp; getMutableRegistryHub();
    void cleanUp();
    std::string translateActiveException();

}

// end catch_interfaces_registry_hub.h
#if defined(CATCH_CONFIG_DISABLE)
    #define INTERNAL_CATCH_TRANSLATE_EXCEPTION_NO_REG( translatorName, signature) \
        static std::string translatorName( signature )
#endif

#include &lt;exception&gt;
#include &lt;string&gt;
#include &lt;vector&gt;

namespace Catch {
    using exceptionTranslateFunction = std::string(*)();

    struct IExceptionTranslator;
    using ExceptionTranslators = std::vector&lt;std::unique_ptr&lt;IExceptionTranslator const&gt;&gt;;

    struct IExceptionTranslator {
        virtual ~IExceptionTranslator();
        virtual std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const = 0;
    };

    struct IExceptionTranslatorRegistry {
        virtual ~IExceptionTranslatorRegistry();

        virtual std::string translateActiveException() const = 0;
    };

    class ExceptionTranslatorRegistrar {
        template&lt;typename T&gt;
        class ExceptionTranslator : public IExceptionTranslator {
        public:

            ExceptionTranslator( std::string(*translateFunction)( T&amp; ) )
            : m_translateFunction( translateFunction )
            {}

            std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const override {
#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
                return "";
#else
                try {
                    if( it == itEnd )
                        std::rethrow_exception(std::current_exception());
                    else
                        return (*it)-&gt;translate( it+1, itEnd );
                }
                catch( T&amp; ex ) {
                    return m_translateFunction( ex );
                }
#endif
            }

        protected:
            std::string(*m_translateFunction)( T&amp; );
        };

    public:
        template&lt;typename T&gt;
        ExceptionTranslatorRegistrar( std::string(*translateFunction)( T&amp; ) ) {
            getMutableRegistryHub().registerTranslator
                ( new ExceptionTranslator&lt;T&gt;( translateFunction ) );
        }
    };
}

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TRANSLATE_EXCEPTION2( translatorName, signature ) \
    static std::string translatorName( signature ); \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS \
    namespace{ Catch::ExceptionTranslatorRegistrar INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionRegistrar )( &amp;translatorName ); } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION \
    static std::string translatorName( signature )

#define INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION2( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// end catch_interfaces_exception.h
// start catch_approx.h

#include &lt;type_traits&gt;

namespace Catch {
namespace Detail {

    class Approx {
    private:
        bool equalityComparisonImpl(double other) const;
        // Validates the new margin (margin &gt;= 0)
        // out-of-line to avoid including stdexcept in the header
        void setMargin(double margin);
        // Validates the new epsilon (0 &lt; epsilon &lt; 1)
        // out-of-line to avoid including stdexcept in the header
        void setEpsilon(double epsilon);

    public:
        explicit Approx ( double value );

        static Approx custom();

        Approx operator-() const;

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx operator()( T const&amp; value ) {
            Approx approx( static_cast&lt;double&gt;(value) );
            approx.m_epsilon = m_epsilon;
            approx.m_margin = m_margin;
            approx.m_scale = m_scale;
            return approx;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        explicit Approx( T const&amp; value ): Approx(static_cast&lt;double&gt;(value))
        {}

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator == ( const T&amp; lhs, Approx const&amp; rhs ) {
            auto lhs_v = static_cast&lt;double&gt;(lhs);
            return rhs.equalityComparisonImpl(lhs_v);
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator == ( Approx const&amp; lhs, const T&amp; rhs ) {
            return operator==( rhs, lhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator != ( T const&amp; lhs, Approx const&amp; rhs ) {
            return !operator==( lhs, rhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator != ( Approx const&amp; lhs, T const&amp; rhs ) {
            return !operator==( rhs, lhs );
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &lt;= ( T const&amp; lhs, Approx const&amp; rhs ) {
            return static_cast&lt;double&gt;(lhs) &lt; rhs.m_value || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &lt;= ( Approx const&amp; lhs, T const&amp; rhs ) {
            return lhs.m_value &lt; static_cast&lt;double&gt;(rhs) || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &gt;= ( T const&amp; lhs, Approx const&amp; rhs ) {
            return static_cast&lt;double&gt;(lhs) &gt; rhs.m_value || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        friend bool operator &gt;= ( Approx const&amp; lhs, T const&amp; rhs ) {
            return lhs.m_value &gt; static_cast&lt;double&gt;(rhs) || lhs == rhs;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; epsilon( T const&amp; newEpsilon ) {
            double epsilonAsDouble = static_cast&lt;double&gt;(newEpsilon);
            setEpsilon(epsilonAsDouble);
            return *this;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; margin( T const&amp; newMargin ) {
            double marginAsDouble = static_cast&lt;double&gt;(newMargin);
            setMargin(marginAsDouble);
            return *this;
        }

        template &lt;typename T, typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
        Approx&amp; scale( T const&amp; newScale ) {
            m_scale = static_cast&lt;double&gt;(newScale);
            return *this;
        }

        std::string toString() const;

    private:
        double m_epsilon;
        double m_margin;
        double m_scale;
        double m_value;
    };
} // end namespace Detail

namespace literals {
    Detail::Approx operator "" _a(long double val);
    Detail::Approx operator "" _a(unsigned long long val);
} // end namespace literals

template&lt;&gt;
struct StringMaker&lt;Catch::Detail::Approx&gt; {
    static std::string convert(Catch::Detail::Approx const&amp; value);
};

} // end namespace Catch

// end catch_approx.h
// start catch_string_manip.h

#include &lt;string&gt;
#include &lt;iosfwd&gt;
#include &lt;vector&gt;

namespace Catch {

    bool startsWith( std::string const&amp; s, std::string const&amp; prefix );
    bool startsWith( std::string const&amp; s, char prefix );
    bool endsWith( std::string const&amp; s, std::string const&amp; suffix );
    bool endsWith( std::string const&amp; s, char suffix );
    bool contains( std::string const&amp; s, std::string const&amp; infix );
    void toLowerInPlace( std::string&amp; s );
    std::string toLower( std::string const&amp; s );
    //! Returns a new string without whitespace at the start/end
    std::string trim( std::string const&amp; str );
    //! Returns a substring of the original ref without whitespace. Beware lifetimes!
    StringRef trim(StringRef ref);

    // !!! Be aware, returns refs into original string - make sure original string outlives them
    std::vector&lt;StringRef&gt; splitStringRef( StringRef str, char delimiter );
    bool replaceInPlace( std::string&amp; str, std::string const&amp; replaceThis, std::string const&amp; withThis );

    struct pluralise {
        pluralise( std::size_t count, std::string const&amp; label );

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, pluralise const&amp; pluraliser );

        std::size_t m_count;
        std::string m_label;
    };
}

// end catch_string_manip.h
#ifndef CATCH_CONFIG_DISABLE_MATCHERS
// start catch_capture_matchers.h

// start catch_matchers.h

#include &lt;string&gt;
#include &lt;vector&gt;

namespace Catch {
namespace Matchers {
    namespace Impl {

        template&lt;typename ArgT&gt; struct MatchAllOf;
        template&lt;typename ArgT&gt; struct MatchAnyOf;
        template&lt;typename ArgT&gt; struct MatchNotOf;

        class MatcherUntypedBase {
        public:
            MatcherUntypedBase() = default;
            MatcherUntypedBase ( MatcherUntypedBase const&amp; ) = default;
            MatcherUntypedBase&amp; operator = ( MatcherUntypedBase const&amp; ) = delete;
            std::string toString() const;

        protected:
            virtual ~MatcherUntypedBase();
            virtual std::string describe() const = 0;
            mutable std::string m_cachedToString;
        };

#ifdef __clang__
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

        template&lt;typename ObjectT&gt;
        struct MatcherMethod {
            virtual bool match( ObjectT const&amp; arg ) const = 0;
        };

#if defined(__OBJC__)
        // Hack to fix Catch GH issue #1661. Could use id for generic Object support.
        // use of const for Object pointers is very uncommon and under ARC it causes some kind of signature mismatch that breaks compilation
        template&lt;&gt;
        struct MatcherMethod&lt;NSString*&gt; {
            virtual bool match( NSString* arg ) const = 0;
        };
#endif

#ifdef __clang__
#    pragma clang diagnostic pop
#endif

        template&lt;typename T&gt;
        struct MatcherBase : MatcherUntypedBase, MatcherMethod&lt;T&gt; {

            MatchAllOf&lt;T&gt; operator &amp;&amp; ( MatcherBase const&amp; other ) const;
            MatchAnyOf&lt;T&gt; operator || ( MatcherBase const&amp; other ) const;
            MatchNotOf&lt;T&gt; operator ! () const;
        };

        template&lt;typename ArgT&gt;
        struct MatchAllOf : MatcherBase&lt;ArgT&gt; {
            bool match( ArgT const&amp; arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (!matcher-&gt;match(arg))
                        return false;
                }
                return true;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " and ";
                    description += matcher-&gt;toString();
                }
                description += " )";
                return description;
            }

            MatchAllOf&lt;ArgT&gt; operator &amp;&amp; ( MatcherBase&lt;ArgT&gt; const&amp; other ) {
                auto copy(*this);
                copy.m_matchers.push_back( &amp;other );
                return copy;
            }

            std::vector&lt;MatcherBase&lt;ArgT&gt; const*&gt; m_matchers;
        };
        template&lt;typename ArgT&gt;
        struct MatchAnyOf : MatcherBase&lt;ArgT&gt; {

            bool match( ArgT const&amp; arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (matcher-&gt;match(arg))
                        return true;
                }
                return false;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " or ";
                    description += matcher-&gt;toString();
                }
                description += " )";
                return description;
            }

            MatchAnyOf&lt;ArgT&gt; operator || ( MatcherBase&lt;ArgT&gt; const&amp; other ) {
                auto copy(*this);
                copy.m_matchers.push_back( &amp;other );
                return copy;
            }

            std::vector&lt;MatcherBase&lt;ArgT&gt; const*&gt; m_matchers;
        };

        template&lt;typename ArgT&gt;
        struct MatchNotOf : MatcherBase&lt;ArgT&gt; {

            MatchNotOf( MatcherBase&lt;ArgT&gt; const&amp; underlyingMatcher ) : m_underlyingMatcher( underlyingMatcher ) {}

            bool match( ArgT const&amp; arg ) const override {
                return !m_underlyingMatcher.match( arg );
            }

            std::string describe() const override {
                return "not " + m_underlyingMatcher.toString();
            }
            MatcherBase&lt;ArgT&gt; const&amp; m_underlyingMatcher;
        };

        template&lt;typename T&gt;
        MatchAllOf&lt;T&gt; MatcherBase&lt;T&gt;::operator &amp;&amp; ( MatcherBase const&amp; other ) const {
            return MatchAllOf&lt;T&gt;() &amp;&amp; *this &amp;&amp; other;
        }
        template&lt;typename T&gt;
        MatchAnyOf&lt;T&gt; MatcherBase&lt;T&gt;::operator || ( MatcherBase const&amp; other ) const {
            return MatchAnyOf&lt;T&gt;() || *this || other;
        }
        template&lt;typename T&gt;
        MatchNotOf&lt;T&gt; MatcherBase&lt;T&gt;::operator ! () const {
            return MatchNotOf&lt;T&gt;( *this );
        }

    } // namespace Impl

} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch

// end catch_matchers.h
// start catch_matchers_exception.hpp

namespace Catch {
namespace Matchers {
namespace Exception {

class ExceptionMessageMatcher : public MatcherBase&lt;std::exception&gt; {
    std::string m_message;
public:

    ExceptionMessageMatcher(std::string const&amp; message):
        m_message(message)
    {}

    bool match(std::exception const&amp; ex) const override;

    std::string describe() const override;
};

} // namespace Exception

Exception::ExceptionMessageMatcher Message(std::string const&amp; message);

} // namespace Matchers
} // namespace Catch

// end catch_matchers_exception.hpp
// start catch_matchers_floating.h

namespace Catch {
namespace Matchers {

    namespace Floating {

        enum class FloatingPointKind : uint8_t;

        struct WithinAbsMatcher : MatcherBase&lt;double&gt; {
            WithinAbsMatcher(double target, double margin);
            bool match(double const&amp; matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            double m_margin;
        };

        struct WithinUlpsMatcher : MatcherBase&lt;double&gt; {
            WithinUlpsMatcher(double target, uint64_t ulps, FloatingPointKind baseType);
            bool match(double const&amp; matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            uint64_t m_ulps;
            FloatingPointKind m_type;
        };

        // Given IEEE-754 format for floats and doubles, we can assume
        // that float -&gt; double promotion is lossless. Given this, we can
        // assume that if we do the standard relative comparison of
        // |lhs - rhs| &lt;= epsilon * max(fabs(lhs), fabs(rhs)), then we get
        // the same result if we do this for floats, as if we do this for
        // doubles that were promoted from floats.
        struct WithinRelMatcher : MatcherBase&lt;double&gt; {
            WithinRelMatcher(double target, double epsilon);
            bool match(double const&amp; matchee) const override;
            std::string describe() const override;
        private:
            double m_target;
            double m_epsilon;
        };

    } // namespace Floating

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred
    Floating::WithinUlpsMatcher WithinULP(double target, uint64_t maxUlpDiff);
    Floating::WithinUlpsMatcher WithinULP(float target, uint64_t maxUlpDiff);
    Floating::WithinAbsMatcher WithinAbs(double target, double margin);
    Floating::WithinRelMatcher WithinRel(double target, double eps);
    // defaults epsilon to 100*numeric_limits&lt;double&gt;::epsilon()
    Floating::WithinRelMatcher WithinRel(double target);
    Floating::WithinRelMatcher WithinRel(float target, float eps);
    // defaults epsilon to 100*numeric_limits&lt;float&gt;::epsilon()
    Floating::WithinRelMatcher WithinRel(float target);

} // namespace Matchers
} // namespace Catch

// end catch_matchers_floating.h
// start catch_matchers_generic.hpp

#include &lt;functional&gt;
#include &lt;string&gt;

namespace Catch {
namespace Matchers {
namespace Generic {

namespace Detail {
    std::string finalizeDescription(const std::string&amp; desc);
}

template &lt;typename T&gt;
class PredicateMatcher : public MatcherBase&lt;T&gt; {
    std::function&lt;bool(T const&amp;)&gt; m_predicate;
    std::string m_description;
public:

    PredicateMatcher(std::function&lt;bool(T const&amp;)&gt; const&amp; elem, std::string const&amp; descr)
        :m_predicate(std::move(elem)),
        m_description(Detail::finalizeDescription(descr))
    {}

    bool match( T const&amp; item ) const override {
        return m_predicate(item);
    }

    std::string describe() const override {
        return m_description;
    }
};

} // namespace Generic

    // The following functions create the actual matcher objects.
    // The user has to explicitly specify type to the function, because
    // inferring std::function&lt;bool(T const&amp;)&gt; is hard (but possible) and
    // requires a lot of TMP.
    template&lt;typename T&gt;
    Generic::PredicateMatcher&lt;T&gt; Predicate(std::function&lt;bool(T const&amp;)&gt; const&amp; predicate, std::string const&amp; description = "") {
        return Generic::PredicateMatcher&lt;T&gt;(predicate, description);
    }

} // namespace Matchers
} // namespace Catch

// end catch_matchers_generic.hpp
// start catch_matchers_string.h

#include &lt;string&gt;

namespace Catch {
namespace Matchers {

    namespace StdString {

        struct CasedString
        {
            CasedString( std::string const&amp; str, CaseSensitive::Choice caseSensitivity );
            std::string adjustString( std::string const&amp; str ) const;
            std::string caseSensitivitySuffix() const;

            CaseSensitive::Choice m_caseSensitivity;
            std::string m_str;
        };

        struct StringMatcherBase : MatcherBase&lt;std::string&gt; {
            StringMatcherBase( std::string const&amp; operation, CasedString const&amp; comparator );
            std::string describe() const override;

            CasedString m_comparator;
            std::string m_operation;
        };

        struct EqualsMatcher : StringMatcherBase {
            EqualsMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct ContainsMatcher : StringMatcherBase {
            ContainsMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct StartsWithMatcher : StringMatcherBase {
            StartsWithMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };
        struct EndsWithMatcher : StringMatcherBase {
            EndsWithMatcher( CasedString const&amp; comparator );
            bool match( std::string const&amp; source ) const override;
        };

        struct RegexMatcher : MatcherBase&lt;std::string&gt; {
            RegexMatcher( std::string regex, CaseSensitive::Choice caseSensitivity );
            bool match( std::string const&amp; matchee ) const override;
            std::string describe() const override;

        private:
            std::string m_regex;
            CaseSensitive::Choice m_caseSensitivity;
        };

    } // namespace StdString

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    StdString::EqualsMatcher Equals( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::ContainsMatcher Contains( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::EndsWithMatcher EndsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::StartsWithMatcher StartsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::RegexMatcher Matches( std::string const&amp; regex, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );

} // namespace Matchers
} // namespace Catch

// end catch_matchers_string.h
// start catch_matchers_vector.h

#include &lt;algorithm&gt;

namespace Catch {
namespace Matchers {

    namespace Vector {
        template&lt;typename T, typename Alloc&gt;
        struct ContainsElementMatcher : MatcherBase&lt;std::vector&lt;T, Alloc&gt;&gt; {

            ContainsElementMatcher(T const &amp;comparator) : m_comparator( comparator) {}

            bool match(std::vector&lt;T, Alloc&gt; const &amp;v) const override {
                for (auto const&amp; el : v) {
                    if (el == m_comparator) {
                        return true;
                    }
                }
                return false;
            }

            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            T const&amp; m_comparator;
        };

        template&lt;typename T, typename AllocComp, typename AllocMatch&gt;
        struct ContainsMatcher : MatcherBase&lt;std::vector&lt;T, AllocMatch&gt;&gt; {

            ContainsMatcher(std::vector&lt;T, AllocComp&gt; const &amp;comparator) : m_comparator( comparator ) {}

            bool match(std::vector&lt;T, AllocMatch&gt; const &amp;v) const override {
                // !TBD: see note in EqualsMatcher
                if (m_comparator.size() &gt; v.size())
                    return false;
                for (auto const&amp; comparator : m_comparator) {
                    auto present = false;
                    for (const auto&amp; el : v) {
                        if (el == comparator) {
                            present = true;
                            break;
                        }
                    }
                    if (!present) {
                        return false;
                    }
                }
                return true;
            }
            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            std::vector&lt;T, AllocComp&gt; const&amp; m_comparator;
        };

        template&lt;typename T, typename AllocComp, typename AllocMatch&gt;
        struct EqualsMatcher : MatcherBase&lt;std::vector&lt;T, AllocMatch&gt;&gt; {

            EqualsMatcher(std::vector&lt;T, AllocComp&gt; const &amp;comparator) : m_comparator( comparator ) {}

            bool match(std::vector&lt;T, AllocMatch&gt; const &amp;v) const override {
                // !TBD: This currently works if all elements can be compared using !=
                // - a more general approach would be via a compare template that defaults
                // to using !=. but could be specialised for, e.g. std::vector&lt;T, Alloc&gt; etc
                // - then just call that directly
                if (m_comparator.size() != v.size())
                    return false;
                for (std::size_t i = 0; i &lt; v.size(); ++i)
                    if (m_comparator[i] != v[i])
                        return false;
                return true;
            }
            std::string describe() const override {
                return "Equals: " + ::Catch::Detail::stringify( m_comparator );
            }
            std::vector&lt;T, AllocComp&gt; const&amp; m_comparator;
        };

        template&lt;typename T, typename AllocComp, typename AllocMatch&gt;
        struct ApproxMatcher : MatcherBase&lt;std::vector&lt;T, AllocMatch&gt;&gt; {

            ApproxMatcher(std::vector&lt;T, AllocComp&gt; const&amp; comparator) : m_comparator( comparator ) {}

            bool match(std::vector&lt;T, AllocMatch&gt; const &amp;v) const override {
                if (m_comparator.size() != v.size())
                    return false;
                for (std::size_t i = 0; i &lt; v.size(); ++i)
                    if (m_comparator[i] != approx(v[i]))
                        return false;
                return true;
            }
            std::string describe() const override {
                return "is approx: " + ::Catch::Detail::stringify( m_comparator );
            }
            template &lt;typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
            ApproxMatcher&amp; epsilon( T const&amp; newEpsilon ) {
                approx.epsilon(newEpsilon);
                return *this;
            }
            template &lt;typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
            ApproxMatcher&amp; margin( T const&amp; newMargin ) {
                approx.margin(newMargin);
                return *this;
            }
            template &lt;typename = typename std::enable_if&lt;std::is_constructible&lt;double, T&gt;::value&gt;::type&gt;
            ApproxMatcher&amp; scale( T const&amp; newScale ) {
                approx.scale(newScale);
                return *this;
            }

            std::vector&lt;T, AllocComp&gt; const&amp; m_comparator;
            mutable Catch::Detail::Approx approx = Catch::Detail::Approx::custom();
        };

        template&lt;typename T, typename AllocComp, typename AllocMatch&gt;
        struct UnorderedEqualsMatcher : MatcherBase&lt;std::vector&lt;T, AllocMatch&gt;&gt; {
            UnorderedEqualsMatcher(std::vector&lt;T, AllocComp&gt; const&amp; target) : m_target(target) {}
            bool match(std::vector&lt;T, AllocMatch&gt; const&amp; vec) const override {
                if (m_target.size() != vec.size()) {
                    return false;
                }
                return std::is_permutation(m_target.begin(), m_target.end(), vec.begin());
            }

            std::string describe() const override {
                return "UnorderedEquals: " + ::Catch::Detail::stringify(m_target);
            }
        private:
            std::vector&lt;T, AllocComp&gt; const&amp; m_target;
        };

    } // namespace Vector

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    template&lt;typename T, typename AllocComp = std::allocator&lt;T&gt;, typename AllocMatch = AllocComp&gt;
    Vector::ContainsMatcher&lt;T, AllocComp, AllocMatch&gt; Contains( std::vector&lt;T, AllocComp&gt; const&amp; comparator ) {
        return Vector::ContainsMatcher&lt;T, AllocComp, AllocMatch&gt;( comparator );
    }

    template&lt;typename T, typename Alloc = std::allocator&lt;T&gt;&gt;
    Vector::ContainsElementMatcher&lt;T, Alloc&gt; VectorContains( T const&amp; comparator ) {
        return Vector::ContainsElementMatcher&lt;T, Alloc&gt;( comparator );
    }

    template&lt;typename T, typename AllocComp = std::allocator&lt;T&gt;, typename AllocMatch = AllocComp&gt;
    Vector::EqualsMatcher&lt;T, AllocComp, AllocMatch&gt; Equals( std::vector&lt;T, AllocComp&gt; const&amp; comparator ) {
        return Vector::EqualsMatcher&lt;T, AllocComp, AllocMatch&gt;( comparator );
    }

    template&lt;typename T, typename AllocComp = std::allocator&lt;T&gt;, typename AllocMatch = AllocComp&gt;
    Vector::ApproxMatcher&lt;T, AllocComp, AllocMatch&gt; Approx( std::vector&lt;T, AllocComp&gt; const&amp; comparator ) {
        return Vector::ApproxMatcher&lt;T, AllocComp, AllocMatch&gt;( comparator );
    }

    template&lt;typename T, typename AllocComp = std::allocator&lt;T&gt;, typename AllocMatch = AllocComp&gt;
    Vector::UnorderedEqualsMatcher&lt;T, AllocComp, AllocMatch&gt; UnorderedEquals(std::vector&lt;T, AllocComp&gt; const&amp; target) {
        return Vector::UnorderedEqualsMatcher&lt;T, AllocComp, AllocMatch&gt;( target );
    }

} // namespace Matchers
} // namespace Catch

// end catch_matchers_vector.h
namespace Catch {

    template&lt;typename ArgT, typename MatcherT&gt;
    class MatchExpr : public ITransientExpression {
        ArgT const&amp; m_arg;
        MatcherT m_matcher;
        StringRef m_matcherString;
    public:
        MatchExpr( ArgT const&amp; arg, MatcherT const&amp; matcher, StringRef const&amp; matcherString )
        :   ITransientExpression{ true, matcher.match( arg ) },
            m_arg( arg ),
            m_matcher( matcher ),
            m_matcherString( matcherString )
        {}

        void streamReconstructedExpression( std::ostream &amp;os ) const override {
            auto matcherAsString = m_matcher.toString();
            os &lt;&lt; Catch::Detail::stringify( m_arg ) &lt;&lt; ' ';
            if( matcherAsString == Detail::unprintableString )
                os &lt;&lt; m_matcherString;
            else
                os &lt;&lt; matcherAsString;
        }
    };

    using StringMatcher = Matchers::Impl::MatcherBase&lt;std::string&gt;;

    void handleExceptionMatchExpr( AssertionHandler&amp; handler, StringMatcher const&amp; matcher, StringRef const&amp; matcherString  );

    template&lt;typename ArgT, typename MatcherT&gt;
    auto makeMatchExpr( ArgT const&amp; arg, MatcherT const&amp; matcher, StringRef const&amp; matcherString  ) -&gt; MatchExpr&lt;ArgT, MatcherT&gt; {
        return MatchExpr&lt;ArgT, MatcherT&gt;( arg, matcher, matcherString );
    }

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CHECK_THAT( macroName, matcher, resultDisposition, arg ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(arg) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        INTERNAL_CATCH_TRY { \
            catchAssertionHandler.handleExpr( Catch::makeMatchExpr( arg, matcher, #matcher##_catch_sr ) ); \
        } INTERNAL_CATCH_CATCH( catchAssertionHandler ) \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_MATCHES( macroName, exceptionType, resultDisposition, matcher, ... ) \
    do { \
        Catch::AssertionHandler catchAssertionHandler( macroName##_catch_sr, CATCH_INTERNAL_LINEINFO, CATCH_INTERNAL_STRINGIFY(__VA_ARGS__) ", " CATCH_INTERNAL_STRINGIFY(exceptionType) ", " CATCH_INTERNAL_STRINGIFY(matcher), resultDisposition ); \
        if( catchAssertionHandler.allowThrows() ) \
            try { \
                static_cast&lt;void&gt;(__VA_ARGS__ ); \
                catchAssertionHandler.handleUnexpectedExceptionNotThrown(); \
            } \
            catch( exceptionType const&amp; ex ) { \
                catchAssertionHandler.handleExpr( Catch::makeMatchExpr( ex, matcher, #matcher##_catch_sr ) ); \
            } \
            catch( ... ) { \
                catchAssertionHandler.handleUnexpectedInflightException(); \
            } \
        else \
            catchAssertionHandler.handleThrowingCallSkipped(); \
        INTERNAL_CATCH_REACT( catchAssertionHandler ) \
    } while( false )

// end catch_capture_matchers.h
#endif
// start catch_generators.hpp

// start catch_interfaces_generatortracker.h


#include &lt;memory&gt;

namespace Catch {

    namespace Generators {
        class GeneratorUntypedBase {
        public:
            GeneratorUntypedBase() = default;
            virtual ~GeneratorUntypedBase();
            // Attempts to move the generator to the next element
             //
             // Returns true iff the move succeeded (and a valid element
             // can be retrieved).
            virtual bool next() = 0;
        };
        using GeneratorBasePtr = std::unique_ptr&lt;GeneratorUntypedBase&gt;;

    } // namespace Generators

    struct IGeneratorTracker {
        virtual ~IGeneratorTracker();
        virtual auto hasGenerator() const -&gt; bool = 0;
        virtual auto getGenerator() const -&gt; Generators::GeneratorBasePtr const&amp; = 0;
        virtual void setGenerator( Generators::GeneratorBasePtr&amp;&amp; generator ) = 0;
    };

} // namespace Catch

// end catch_interfaces_generatortracker.h
// start catch_enforce.h

#include &lt;exception&gt;

namespace Catch {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
    template &lt;typename Ex&gt;
    [[noreturn]]
    void throw_exception(Ex const&amp; e) {
        throw e;
    }
#else // ^^ Exceptions are enabled //  Exceptions are disabled vv
    [[noreturn]]
    void throw_exception(std::exception const&amp; e);
#endif

    [[noreturn]]
    void throw_logic_error(std::string const&amp; msg);
    [[noreturn]]
    void throw_domain_error(std::string const&amp; msg);
    [[noreturn]]
    void throw_runtime_error(std::string const&amp; msg);

} // namespace Catch;

#define CATCH_MAKE_MSG(...) \
    (Catch::ReusableStringStream() &lt;&lt; __VA_ARGS__).str()

#define CATCH_INTERNAL_ERROR(...) \
    Catch::throw_logic_error(CATCH_MAKE_MSG( CATCH_INTERNAL_LINEINFO &lt;&lt; ": Internal Catch2 error: " &lt;&lt; __VA_ARGS__))

#define CATCH_ERROR(...) \
    Catch::throw_domain_error(CATCH_MAKE_MSG( __VA_ARGS__ ))

#define CATCH_RUNTIME_ERROR(...) \
    Catch::throw_runtime_error(CATCH_MAKE_MSG( __VA_ARGS__ ))

#define CATCH_ENFORCE( condition, ... ) \
    do{ if( !(condition) ) CATCH_ERROR( __VA_ARGS__ ); } while(false)

// end catch_enforce.h
#include &lt;memory&gt;
#include &lt;vector&gt;
#include &lt;cassert&gt;

#include &lt;utility&gt;
#include &lt;exception&gt;

namespace Catch {

class GeneratorException : public std::exception {
    const char* const m_msg = "";

public:
    GeneratorException(const char* msg):
        m_msg(msg)
    {}

    const char* what() const noexcept override final;
};

namespace Generators {

    // !TBD move this into its own location?
    namespace pf{
        template&lt;typename T, typename... Args&gt;
        std::unique_ptr&lt;T&gt; make_unique( Args&amp;&amp;... args ) {
            return std::unique_ptr&lt;T&gt;(new T(std::forward&lt;Args&gt;(args)...));
        }
    }

    template&lt;typename T&gt;
    struct IGenerator : GeneratorUntypedBase {
        virtual ~IGenerator() = default;

        // Returns the current element of the generator
        //
        // \Precondition The generator is either freshly constructed,
        // or the last call to `next()` returned true
        virtual T const&amp; get() const = 0;
        using type = T;
    };

    template&lt;typename T&gt;
    class SingleValueGenerator final : public IGenerator&lt;T&gt; {
        T m_value;
    public:
        SingleValueGenerator(T&amp;&amp; value) : m_value(std::move(value)) {}

        T const&amp; get() const override {
            return m_value;
        }
        bool next() override {
            return false;
        }
    };

    template&lt;typename T&gt;
    class FixedValuesGenerator final : public IGenerator&lt;T&gt; {
        static_assert(!std::is_same&lt;T, bool&gt;::value,
            "FixedValuesGenerator does not support bools because of std::vector&lt;bool&gt;"
            "specialization, use SingleValue Generator instead.");
        std::vector&lt;T&gt; m_values;
        size_t m_idx = 0;
    public:
        FixedValuesGenerator( std::initializer_list&lt;T&gt; values ) : m_values( values ) {}

        T const&amp; get() const override {
            return m_values[m_idx];
        }
        bool next() override {
            ++m_idx;
            return m_idx &lt; m_values.size();
        }
    };

    template &lt;typename T&gt;
    class GeneratorWrapper final {
        std::unique_ptr&lt;IGenerator&lt;T&gt;&gt; m_generator;
    public:
        GeneratorWrapper(std::unique_ptr&lt;IGenerator&lt;T&gt;&gt; generator):
            m_generator(std::move(generator))
        {}
        T const&amp; get() const {
            return m_generator-&gt;get();
        }
        bool next() {
            return m_generator-&gt;next();
        }
    };

    template &lt;typename T&gt;
    GeneratorWrapper&lt;T&gt; value(T&amp;&amp; value) {
        return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;SingleValueGenerator&lt;T&gt;&gt;(std::forward&lt;T&gt;(value)));
    }
    template &lt;typename T&gt;
    GeneratorWrapper&lt;T&gt; values(std::initializer_list&lt;T&gt; values) {
        return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;FixedValuesGenerator&lt;T&gt;&gt;(values));
    }

    template&lt;typename T&gt;
    class Generators : public IGenerator&lt;T&gt; {
        std::vector&lt;GeneratorWrapper&lt;T&gt;&gt; m_generators;
        size_t m_current = 0;

        void populate(GeneratorWrapper&lt;T&gt;&amp;&amp; generator) {
            m_generators.emplace_back(std::move(generator));
        }
        void populate(T&amp;&amp; val) {
            m_generators.emplace_back(value(std::forward&lt;T&gt;(val)));
        }
        template&lt;typename U&gt;
        void populate(U&amp;&amp; val) {
            populate(T(std::forward&lt;U&gt;(val)));
        }
        template&lt;typename U, typename... Gs&gt;
        void populate(U&amp;&amp; valueOrGenerator, Gs &amp;&amp;... moreGenerators) {
            populate(std::forward&lt;U&gt;(valueOrGenerator));
            populate(std::forward&lt;Gs&gt;(moreGenerators)...);
        }

    public:
        template &lt;typename... Gs&gt;
        Generators(Gs &amp;&amp;... moreGenerators) {
            m_generators.reserve(sizeof...(Gs));
            populate(std::forward&lt;Gs&gt;(moreGenerators)...);
        }

        T const&amp; get() const override {
            return m_generators[m_current].get();
        }

        bool next() override {
            if (m_current &gt;= m_generators.size()) {
                return false;
            }
            const bool current_status = m_generators[m_current].next();
            if (!current_status) {
                ++m_current;
            }
            return m_current &lt; m_generators.size();
        }
    };

    template&lt;typename... Ts&gt;
    GeneratorWrapper&lt;std::tuple&lt;Ts...&gt;&gt; table( std::initializer_list&lt;std::tuple&lt;typename std::decay&lt;Ts&gt;::type...&gt;&gt; tuples ) {
        return values&lt;std::tuple&lt;Ts...&gt;&gt;( tuples );
    }

    // Tag type to signal that a generator sequence should convert arguments to a specific type
    template &lt;typename T&gt;
    struct as {};

    template&lt;typename T, typename... Gs&gt;
    auto makeGenerators( GeneratorWrapper&lt;T&gt;&amp;&amp; generator, Gs &amp;&amp;... moreGenerators ) -&gt; Generators&lt;T&gt; {
        return Generators&lt;T&gt;(std::move(generator), std::forward&lt;Gs&gt;(moreGenerators)...);
    }
    template&lt;typename T&gt;
    auto makeGenerators( GeneratorWrapper&lt;T&gt;&amp;&amp; generator ) -&gt; Generators&lt;T&gt; {
        return Generators&lt;T&gt;(std::move(generator));
    }
    template&lt;typename T, typename... Gs&gt;
    auto makeGenerators( T&amp;&amp; val, Gs &amp;&amp;... moreGenerators ) -&gt; Generators&lt;T&gt; {
        return makeGenerators( value( std::forward&lt;T&gt;( val ) ), std::forward&lt;Gs&gt;( moreGenerators )... );
    }
    template&lt;typename T, typename U, typename... Gs&gt;
    auto makeGenerators( as&lt;T&gt;, U&amp;&amp; val, Gs &amp;&amp;... moreGenerators ) -&gt; Generators&lt;T&gt; {
        return makeGenerators( value( T( std::forward&lt;U&gt;( val ) ) ), std::forward&lt;Gs&gt;( moreGenerators )... );
    }

    auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const&amp; lineInfo ) -&gt; IGeneratorTracker&amp;;

    template&lt;typename L&gt;
    // Note: The type after -&gt; is weird, because VS2015 cannot parse
    //       the expression used in the typedef inside, when it is in
    //       return type. Yeah.
    auto generate( StringRef generatorName, SourceLineInfo const&amp; lineInfo, L const&amp; generatorExpression ) -&gt; decltype(std::declval&lt;decltype(generatorExpression())&gt;().get()) {
        using UnderlyingType = typename decltype(generatorExpression())::type;

        IGeneratorTracker&amp; tracker = acquireGeneratorTracker( generatorName, lineInfo );
        if (!tracker.hasGenerator()) {
            tracker.setGenerator(pf::make_unique&lt;Generators&lt;UnderlyingType&gt;&gt;(generatorExpression()));
        }

        auto const&amp; generator = static_cast&lt;IGenerator&lt;UnderlyingType&gt; const&amp;&gt;( *tracker.getGenerator() );
        return generator.get();
    }

} // namespace Generators
} // namespace Catch

#define GENERATE( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [ ]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)
#define GENERATE_COPY( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [=]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)
#define GENERATE_REF( ... ) \
    Catch::Generators::generate( INTERNAL_CATCH_STRINGIZE(INTERNAL_CATCH_UNIQUE_NAME(generator)), \
                                 CATCH_INTERNAL_LINEINFO, \
                                 [&amp;]{ using namespace Catch::Generators; return makeGenerators( __VA_ARGS__ ); } ) //NOLINT(google-build-using-namespace)

// end catch_generators.hpp
// start catch_generators_generic.hpp

namespace Catch {
namespace Generators {

    template &lt;typename T&gt;
    class TakeGenerator : public IGenerator&lt;T&gt; {
        GeneratorWrapper&lt;T&gt; m_generator;
        size_t m_returned = 0;
        size_t m_target;
    public:
        TakeGenerator(size_t target, GeneratorWrapper&lt;T&gt;&amp;&amp; generator):
            m_generator(std::move(generator)),
            m_target(target)
        {
            assert(target != 0 &amp;&amp; "Empty generators are not allowed");
        }
        T const&amp; get() const override {
            return m_generator.get();
        }
        bool next() override {
            ++m_returned;
            if (m_returned &gt;= m_target) {
                return false;
            }

            const auto success = m_generator.next();
            // If the underlying generator does not contain enough values
            // then we cut short as well
            if (!success) {
                m_returned = m_target;
            }
            return success;
        }
    };

    template &lt;typename T&gt;
    GeneratorWrapper&lt;T&gt; take(size_t target, GeneratorWrapper&lt;T&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;TakeGenerator&lt;T&gt;&gt;(target, std::move(generator)));
    }

    template &lt;typename T, typename Predicate&gt;
    class FilterGenerator : public IGenerator&lt;T&gt; {
        GeneratorWrapper&lt;T&gt; m_generator;
        Predicate m_predicate;
    public:
        template &lt;typename P = Predicate&gt;
        FilterGenerator(P&amp;&amp; pred, GeneratorWrapper&lt;T&gt;&amp;&amp; generator):
            m_generator(std::move(generator)),
            m_predicate(std::forward&lt;P&gt;(pred))
        {
            if (!m_predicate(m_generator.get())) {
                // It might happen that there are no values that pass the
                // filter. In that case we throw an exception.
                auto has_initial_value = next();
                if (!has_initial_value) {
                    Catch::throw_exception(GeneratorException("No valid value found in filtered generator"));
                }
            }
        }

        T const&amp; get() const override {
            return m_generator.get();
        }

        bool next() override {
            bool success = m_generator.next();
            if (!success) {
                return false;
            }
            while (!m_predicate(m_generator.get()) &amp;&amp; (success = m_generator.next()) == true);
            return success;
        }
    };

    template &lt;typename T, typename Predicate&gt;
    GeneratorWrapper&lt;T&gt; filter(Predicate&amp;&amp; pred, GeneratorWrapper&lt;T&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;T&gt;(std::unique_ptr&lt;IGenerator&lt;T&gt;&gt;(pf::make_unique&lt;FilterGenerator&lt;T, Predicate&gt;&gt;(std::forward&lt;Predicate&gt;(pred), std::move(generator))));
    }

    template &lt;typename T&gt;
    class RepeatGenerator : public IGenerator&lt;T&gt; {
        static_assert(!std::is_same&lt;T, bool&gt;::value,
            "RepeatGenerator currently does not support bools"
            "because of std::vector&lt;bool&gt; specialization");
        GeneratorWrapper&lt;T&gt; m_generator;
        mutable std::vector&lt;T&gt; m_returned;
        size_t m_target_repeats;
        size_t m_current_repeat = 0;
        size_t m_repeat_index = 0;
    public:
        RepeatGenerator(size_t repeats, GeneratorWrapper&lt;T&gt;&amp;&amp; generator):
            m_generator(std::move(generator)),
            m_target_repeats(repeats)
        {
            assert(m_target_repeats &gt; 0 &amp;&amp; "Repeat generator must repeat at least once");
        }

        T const&amp; get() const override {
            if (m_current_repeat == 0) {
                m_returned.push_back(m_generator.get());
                return m_returned.back();
            }
            return m_returned[m_repeat_index];
        }

        bool next() override {
            // There are 2 basic cases:
            // 1) We are still reading the generator
            // 2) We are reading our own cache

            // In the first case, we need to poke the underlying generator.
            // If it happily moves, we are left in that state, otherwise it is time to start reading from our cache
            if (m_current_repeat == 0) {
                const auto success = m_generator.next();
                if (!success) {
                    ++m_current_repeat;
                }
                return m_current_repeat &lt; m_target_repeats;
            }

            // In the second case, we need to move indices forward and check that we haven't run up against the end
            ++m_repeat_index;
            if (m_repeat_index == m_returned.size()) {
                m_repeat_index = 0;
                ++m_current_repeat;
            }
            return m_current_repeat &lt; m_target_repeats;
        }
    };

    template &lt;typename T&gt;
    GeneratorWrapper&lt;T&gt; repeat(size_t repeats, GeneratorWrapper&lt;T&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;RepeatGenerator&lt;T&gt;&gt;(repeats, std::move(generator)));
    }

    template &lt;typename T, typename U, typename Func&gt;
    class MapGenerator : public IGenerator&lt;T&gt; {
        // TBD: provide static assert for mapping function, for friendly error message
        GeneratorWrapper&lt;U&gt; m_generator;
        Func m_function;
        // To avoid returning dangling reference, we have to save the values
        T m_cache;
    public:
        template &lt;typename F2 = Func&gt;
        MapGenerator(F2&amp;&amp; function, GeneratorWrapper&lt;U&gt;&amp;&amp; generator) :
            m_generator(std::move(generator)),
            m_function(std::forward&lt;F2&gt;(function)),
            m_cache(m_function(m_generator.get()))
        {}

        T const&amp; get() const override {
            return m_cache;
        }
        bool next() override {
            const auto success = m_generator.next();
            if (success) {
                m_cache = m_function(m_generator.get());
            }
            return success;
        }
    };

    template &lt;typename Func, typename U, typename T = FunctionReturnType&lt;Func, U&gt;&gt;
    GeneratorWrapper&lt;T&gt; map(Func&amp;&amp; function, GeneratorWrapper&lt;U&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;T&gt;(
            pf::make_unique&lt;MapGenerator&lt;T, U, Func&gt;&gt;(std::forward&lt;Func&gt;(function), std::move(generator))
        );
    }

    template &lt;typename T, typename U, typename Func&gt;
    GeneratorWrapper&lt;T&gt; map(Func&amp;&amp; function, GeneratorWrapper&lt;U&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;T&gt;(
            pf::make_unique&lt;MapGenerator&lt;T, U, Func&gt;&gt;(std::forward&lt;Func&gt;(function), std::move(generator))
        );
    }

    template &lt;typename T&gt;
    class ChunkGenerator final : public IGenerator&lt;std::vector&lt;T&gt;&gt; {
        std::vector&lt;T&gt; m_chunk;
        size_t m_chunk_size;
        GeneratorWrapper&lt;T&gt; m_generator;
        bool m_used_up = false;
    public:
        ChunkGenerator(size_t size, GeneratorWrapper&lt;T&gt; generator) :
            m_chunk_size(size), m_generator(std::move(generator))
        {
            m_chunk.reserve(m_chunk_size);
            if (m_chunk_size != 0) {
                m_chunk.push_back(m_generator.get());
                for (size_t i = 1; i &lt; m_chunk_size; ++i) {
                    if (!m_generator.next()) {
                        Catch::throw_exception(GeneratorException("Not enough values to initialize the first chunk"));
                    }
                    m_chunk.push_back(m_generator.get());
                }
            }
        }
        std::vector&lt;T&gt; const&amp; get() const override {
            return m_chunk;
        }
        bool next() override {
            m_chunk.clear();
            for (size_t idx = 0; idx &lt; m_chunk_size; ++idx) {
                if (!m_generator.next()) {
                    return false;
                }
                m_chunk.push_back(m_generator.get());
            }
            return true;
        }
    };

    template &lt;typename T&gt;
    GeneratorWrapper&lt;std::vector&lt;T&gt;&gt; chunk(size_t size, GeneratorWrapper&lt;T&gt;&amp;&amp; generator) {
        return GeneratorWrapper&lt;std::vector&lt;T&gt;&gt;(
            pf::make_unique&lt;ChunkGenerator&lt;T&gt;&gt;(size, std::move(generator))
        );
    }

} // namespace Generators
} // namespace Catch

// end catch_generators_generic.hpp
// start catch_generators_specific.hpp

// start catch_context.h

#include &lt;memory&gt;

namespace Catch {

    struct IResultCapture;
    struct IRunner;
    struct IConfig;
    struct IMutableContext;

    using IConfigPtr = std::shared_ptr&lt;IConfig const&gt;;

    struct IContext
    {
        virtual ~IContext();

        virtual IResultCapture* getResultCapture() = 0;
        virtual IRunner* getRunner() = 0;
        virtual IConfigPtr const&amp; getConfig() const = 0;
    };

    struct IMutableContext : IContext
    {
        virtual ~IMutableContext();
        virtual void setResultCapture( IResultCapture* resultCapture ) = 0;
        virtual void setRunner( IRunner* runner ) = 0;
        virtual void setConfig( IConfigPtr const&amp; config ) = 0;

    private:
        static IMutableContext *currentContext;
        friend IMutableContext&amp; getCurrentMutableContext();
        friend void cleanUpContext();
        static void createContext();
    };

    inline IMutableContext&amp; getCurrentMutableContext()
    {
        if( !IMutableContext::currentContext )
            IMutableContext::createContext();
        // NOLINTNEXTLINE(clang-analyzer-core.uninitialized.UndefReturn)
        return *IMutableContext::currentContext;
    }

    inline IContext&amp; getCurrentContext()
    {
        return getCurrentMutableContext();
    }

    void cleanUpContext();

    class SimplePcg32;
    SimplePcg32&amp; rng();
}

// end catch_context.h
// start catch_interfaces_config.h

// start catch_option.hpp

namespace Catch {

    // An optional type
    template&lt;typename T&gt;
    class Option {
    public:
        Option() : nullableValue( nullptr ) {}
        Option( T const&amp; _value )
        : nullableValue( new( storage ) T( _value ) )
        {}
        Option( Option const&amp; _other )
        : nullableValue( _other ? new( storage ) T( *_other ) : nullptr )
        {}

        ~Option() {
            reset();
        }

        Option&amp; operator= ( Option const&amp; _other ) {
            if( &amp;_other != this ) {
                reset();
                if( _other )
                    nullableValue = new( storage ) T( *_other );
            }
            return *this;
        }
        Option&amp; operator = ( T const&amp; _value ) {
            reset();
            nullableValue = new( storage ) T( _value );
            return *this;
        }

        void reset() {
            if( nullableValue )
                nullableValue-&gt;~T();
            nullableValue = nullptr;
        }

        T&amp; operator*() { return *nullableValue; }
        T const&amp; operator*() const { return *nullableValue; }
        T* operator-&gt;() { return nullableValue; }
        const T* operator-&gt;() const { return nullableValue; }

        T valueOr( T const&amp; defaultValue ) const {
            return nullableValue ? *nullableValue : defaultValue;
        }

        bool some() const { return nullableValue != nullptr; }
        bool none() const { return nullableValue == nullptr; }

        bool operator !() const { return nullableValue == nullptr; }
        explicit operator bool() const {
            return some();
        }

    private:
        T *nullableValue;
        alignas(alignof(T)) char storage[sizeof(T)];
    };

} // end namespace Catch

// end catch_option.hpp
#include &lt;chrono&gt;
#include &lt;iosfwd&gt;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    enum class Verbosity {
        Quiet = 0,
        Normal,
        High
    };

    struct WarnAbout { enum What {
        Nothing = 0x00,
        NoAssertions = 0x01,
        NoTests = 0x02
    }; };

    struct ShowDurations { enum OrNot {
        DefaultForReporter,
        Always,
        Never
    }; };
    struct RunTests { enum InWhatOrder {
        InDeclarationOrder,
        InLexicographicalOrder,
        InRandomOrder
    }; };
    struct UseColour { enum YesOrNo {
        Auto,
        Yes,
        No
    }; };
    struct WaitForKeypress { enum When {
        Never,
        BeforeStart = 1,
        BeforeExit = 2,
        BeforeStartAndExit = BeforeStart | BeforeExit
    }; };

    class TestSpec;

    struct IConfig : NonCopyable {

        virtual ~IConfig();

        virtual bool allowThrows() const = 0;
        virtual std::ostream&amp; stream() const = 0;
        virtual std::string name() const = 0;
        virtual bool includeSuccessfulResults() const = 0;
        virtual bool shouldDebugBreak() const = 0;
        virtual bool warnAboutMissingAssertions() const = 0;
        virtual bool warnAboutNoTests() const = 0;
        virtual int abortAfter() const = 0;
        virtual bool showInvisibles() const = 0;
        virtual ShowDurations::OrNot showDurations() const = 0;
        virtual double minDuration() const = 0;
        virtual TestSpec const&amp; testSpec() const = 0;
        virtual bool hasTestFilters() const = 0;
        virtual std::vector&lt;std::string&gt; const&amp; getTestsOrTags() const = 0;
        virtual RunTests::InWhatOrder runOrder() const = 0;
        virtual unsigned int rngSeed() const = 0;
        virtual UseColour::YesOrNo useColour() const = 0;
        virtual std::vector&lt;std::string&gt; const&amp; getSectionsToRun() const = 0;
        virtual Verbosity verbosity() const = 0;

        virtual bool benchmarkNoAnalysis() const = 0;
        virtual int benchmarkSamples() const = 0;
        virtual double benchmarkConfidenceInterval() const = 0;
        virtual unsigned int benchmarkResamples() const = 0;
        virtual std::chrono::milliseconds benchmarkWarmupTime() const = 0;
    };

    using IConfigPtr = std::shared_ptr&lt;IConfig const&gt;;
}

// end catch_interfaces_config.h
// start catch_random_number_generator.h

#include &lt;cstdint&gt;

namespace Catch {

    // This is a simple implementation of C++11 Uniform Random Number
    // Generator. It does not provide all operators, because Catch2
    // does not use it, but it should behave as expected inside stdlib's
    // distributions.
    // The implementation is based on the PCG family (http://pcg-random.org)
    class SimplePcg32 {
        using state_type = std::uint64_t;
    public:
        using result_type = std::uint32_t;
        static constexpr result_type (min)() {
            return 0;
        }
        static constexpr result_type (max)() {
            return static_cast&lt;result_type&gt;(-1);
        }

        // Provide some default initial state for the default constructor
        SimplePcg32():SimplePcg32(0xed743cc4U) {}

        explicit SimplePcg32(result_type seed_);

        void seed(result_type seed_);
        void discard(uint64_t skip);

        result_type operator()();

    private:
        friend bool operator==(SimplePcg32 const&amp; lhs, SimplePcg32 const&amp; rhs);
        friend bool operator!=(SimplePcg32 const&amp; lhs, SimplePcg32 const&amp; rhs);

        // In theory we also need operator&lt;&lt; and operator&gt;&gt;
        // In practice we do not use them, so we will skip them for now

        std::uint64_t m_state;
        // This part of the state determines which "stream" of the numbers
        // is chosen -- we take it as a constant for Catch2, so we only
        // need to deal with seeding the main state.
        // Picked by reading 8 bytes from `/dev/random` :-)
        static const std::uint64_t s_inc = (0x13ed0cc53f939476ULL &lt;&lt; 1ULL) | 1ULL;
    };

} // end namespace Catch

// end catch_random_number_generator.h
#include &lt;random&gt;

namespace Catch {
namespace Generators {

template &lt;typename Float&gt;
class RandomFloatingGenerator final : public IGenerator&lt;Float&gt; {
    Catch::SimplePcg32&amp; m_rng;
    std::uniform_real_distribution&lt;Float&gt; m_dist;
    Float m_current_number;
public:

    RandomFloatingGenerator(Float a, Float b):
        m_rng(rng()),
        m_dist(a, b) {
        static_cast&lt;void&gt;(next());
    }

    Float const&amp; get() const override {
        return m_current_number;
    }
    bool next() override {
        m_current_number = m_dist(m_rng);
        return true;
    }
};

template &lt;typename Integer&gt;
class RandomIntegerGenerator final : public IGenerator&lt;Integer&gt; {
    Catch::SimplePcg32&amp; m_rng;
    std::uniform_int_distribution&lt;Integer&gt; m_dist;
    Integer m_current_number;
public:

    RandomIntegerGenerator(Integer a, Integer b):
        m_rng(rng()),
        m_dist(a, b) {
        static_cast&lt;void&gt;(next());
    }

    Integer const&amp; get() const override {
        return m_current_number;
    }
    bool next() override {
        m_current_number = m_dist(m_rng);
        return true;
    }
};

// TODO: Ideally this would be also constrained against the various char types,
//       but I don't expect users to run into that in practice.
template &lt;typename T&gt;
typename std::enable_if&lt;std::is_integral&lt;T&gt;::value &amp;&amp; !std::is_same&lt;T, bool&gt;::value,
GeneratorWrapper&lt;T&gt;&gt;::type
random(T a, T b) {
    return GeneratorWrapper&lt;T&gt;(
        pf::make_unique&lt;RandomIntegerGenerator&lt;T&gt;&gt;(a, b)
    );
}

template &lt;typename T&gt;
typename std::enable_if&lt;std::is_floating_point&lt;T&gt;::value,
GeneratorWrapper&lt;T&gt;&gt;::type
random(T a, T b) {
    return GeneratorWrapper&lt;T&gt;(
        pf::make_unique&lt;RandomFloatingGenerator&lt;T&gt;&gt;(a, b)
    );
}

template &lt;typename T&gt;
class RangeGenerator final : public IGenerator&lt;T&gt; {
    T m_current;
    T m_end;
    T m_step;
    bool m_positive;

public:
    RangeGenerator(T const&amp; start, T const&amp; end, T const&amp; step):
        m_current(start),
        m_end(end),
        m_step(step),
        m_positive(m_step &gt; T(0))
    {
        assert(m_current != m_end &amp;&amp; "Range start and end cannot be equal");
        assert(m_step != T(0) &amp;&amp; "Step size cannot be zero");
        assert(((m_positive &amp;&amp; m_current &lt;= m_end) || (!m_positive &amp;&amp; m_current &gt;= m_end)) &amp;&amp; "Step moves away from end");
    }

    RangeGenerator(T const&amp; start, T const&amp; end):
        RangeGenerator(start, end, (start &lt; end) ? T(1) : T(-1))
    {}

    T const&amp; get() const override {
        return m_current;
    }

    bool next() override {
        m_current += m_step;
        return (m_positive) ? (m_current &lt; m_end) : (m_current &gt; m_end);
    }
};

template &lt;typename T&gt;
GeneratorWrapper&lt;T&gt; range(T const&amp; start, T const&amp; end, T const&amp; step) {
    static_assert(std::is_arithmetic&lt;T&gt;::value &amp;&amp; !std::is_same&lt;T, bool&gt;::value, "Type must be numeric");
    return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;RangeGenerator&lt;T&gt;&gt;(start, end, step));
}

template &lt;typename T&gt;
GeneratorWrapper&lt;T&gt; range(T const&amp; start, T const&amp; end) {
    static_assert(std::is_integral&lt;T&gt;::value &amp;&amp; !std::is_same&lt;T, bool&gt;::value, "Type must be an integer");
    return GeneratorWrapper&lt;T&gt;(pf::make_unique&lt;RangeGenerator&lt;T&gt;&gt;(start, end));
}

template &lt;typename T&gt;
class IteratorGenerator final : public IGenerator&lt;T&gt; {
    static_assert(!std::is_same&lt;T, bool&gt;::value,
        "IteratorGenerator currently does not support bools"
        "because of std::vector&lt;bool&gt; specialization");

    std::vector&lt;T&gt; m_elems;
    size_t m_current = 0;
public:
    template &lt;typename InputIterator, typename InputSentinel&gt;
    IteratorGenerator(InputIterator first, InputSentinel last):m_elems(first, last) {
        if (m_elems.empty()) {
            Catch::throw_exception(GeneratorException("IteratorGenerator received no valid values"));
        }
    }

    T const&amp; get() const override {
        return m_elems[m_current];
    }

    bool next() override {
        ++m_current;
        return m_current != m_elems.size();
    }
};

template &lt;typename InputIterator,
          typename InputSentinel,
          typename ResultType = typename std::iterator_traits&lt;InputIterator&gt;::value_type&gt;
GeneratorWrapper&lt;ResultType&gt; from_range(InputIterator from, InputSentinel to) {
    return GeneratorWrapper&lt;ResultType&gt;(pf::make_unique&lt;IteratorGenerator&lt;ResultType&gt;&gt;(from, to));
}

template &lt;typename Container,
          typename ResultType = typename Container::value_type&gt;
GeneratorWrapper&lt;ResultType&gt; from_range(Container const&amp; cnt) {
    return GeneratorWrapper&lt;ResultType&gt;(pf::make_unique&lt;IteratorGenerator&lt;ResultType&gt;&gt;(cnt.begin(), cnt.end()));
}

} // namespace Generators
} // namespace Catch

// end catch_generators_specific.hpp

// These files are included here so the single_include script doesn't put them
// in the conditionally compiled sections
// start catch_test_case_info.h

#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace Catch {

    struct ITestInvoker;

    struct TestCaseInfo {
        enum SpecialProperties{
            None = 0,
            IsHidden = 1 &lt;&lt; 1,
            ShouldFail = 1 &lt;&lt; 2,
            MayFail = 1 &lt;&lt; 3,
            Throws = 1 &lt;&lt; 4,
            NonPortable = 1 &lt;&lt; 5,
            Benchmark = 1 &lt;&lt; 6
        };

        TestCaseInfo(   std::string const&amp; _name,
                        std::string const&amp; _className,
                        std::string const&amp; _description,
                        std::vector&lt;std::string&gt; const&amp; _tags,
                        SourceLineInfo const&amp; _lineInfo );

        friend void setTags( TestCaseInfo&amp; testCaseInfo, std::vector&lt;std::string&gt; tags );

        bool isHidden() const;
        bool throws() const;
        bool okToFail() const;
        bool expectedToFail() const;

        std::string tagsAsString() const;

        std::string name;
        std::string className;
        std::string description;
        std::vector&lt;std::string&gt; tags;
        std::vector&lt;std::string&gt; lcaseTags;
        SourceLineInfo lineInfo;
        SpecialProperties properties;
    };

    class TestCase : public TestCaseInfo {
    public:

        TestCase( ITestInvoker* testCase, TestCaseInfo&amp;&amp; info );

        TestCase withName( std::string const&amp; _newName ) const;

        void invoke() const;

        TestCaseInfo const&amp; getTestCaseInfo() const;

        bool operator == ( TestCase const&amp; other ) const;
        bool operator &lt; ( TestCase const&amp; other ) const;

    private:
        std::shared_ptr&lt;ITestInvoker&gt; test;
    };

    TestCase makeTestCase(  ITestInvoker* testCase,
                            std::string const&amp; className,
                            NameAndTags const&amp; nameAndTags,
                            SourceLineInfo const&amp; lineInfo );
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_case_info.h
// start catch_interfaces_runner.h

namespace Catch {

    struct IRunner {
        virtual ~IRunner();
        virtual bool aborting() const = 0;
    };
}

// end catch_interfaces_runner.h

#ifdef __OBJC__
// start catch_objc.hpp

#import &lt;objc/runtime.h&gt;

#include &lt;string&gt;

// NB. Any general catch headers included here must be included
// in catch.hpp first to make sure they are included by the single
// header for non obj-usage

///////////////////////////////////////////////////////////////////////////////
// This protocol is really only here for (self) documenting purposes, since
// all its methods are optional.
@protocol OcFixture

@optional

-(void) setUp;
-(void) tearDown;

@end

namespace Catch {

    class OcMethod : public ITestInvoker {

    public:
        OcMethod( Class cls, SEL sel ) : m_cls( cls ), m_sel( sel ) {}

        virtual void invoke() const {
            id obj = [[m_cls alloc] init];

            performOptionalSelector( obj, @selector(setUp)  );
            performOptionalSelector( obj, m_sel );
            performOptionalSelector( obj, @selector(tearDown)  );

            arcSafeRelease( obj );
        }
    private:
        virtual ~OcMethod() {}

        Class m_cls;
        SEL m_sel;
    };

    namespace Detail{

        inline std::string getAnnotation(   Class cls,
                                            std::string const&amp; annotationName,
                                            std::string const&amp; testCaseName ) {
            NSString* selStr = [[NSString alloc] initWithFormat:@"Catch_%s_%s", annotationName.c_str(), testCaseName.c_str()];
            SEL sel = NSSelectorFromString( selStr );
            arcSafeRelease( selStr );
            id value = performOptionalSelector( cls, sel );
            if( value )
                return [(NSString*)value UTF8String];
            return "";
        }
    }

    inline std::size_t registerTestMethods() {
        std::size_t noTestMethods = 0;
        int noClasses = objc_getClassList( nullptr, 0 );

        Class* classes = (CATCH_UNSAFE_UNRETAINED Class *)malloc( sizeof(Class) * noClasses);
        objc_getClassList( classes, noClasses );

        for( int c = 0; c &lt; noClasses; c++ ) {
            Class cls = classes[c];
            {
                u_int count;
                Method* methods = class_copyMethodList( cls, &amp;count );
                for( u_int m = 0; m &lt; count ; m++ ) {
                    SEL selector = method_getName(methods[m]);
                    std::string methodName = sel_getName(selector);
                    if( startsWith( methodName, "Catch_TestCase_" ) ) {
                        std::string testCaseName = methodName.substr( 15 );
                        std::string name = Detail::getAnnotation( cls, "Name", testCaseName );
                        std::string desc = Detail::getAnnotation( cls, "Description", testCaseName );
                        const char* className = class_getName( cls );

                        getMutableRegistryHub().registerTest( makeTestCase( new OcMethod( cls, selector ), className, NameAndTags( name.c_str(), desc.c_str() ), SourceLineInfo("",0) ) );
                        noTestMethods++;
                    }
                }
                free(methods);
            }
        }
        return noTestMethods;
    }

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

    namespace Matchers {
        namespace Impl {
        namespace NSStringMatchers {

            struct StringHolder : MatcherBase&lt;NSString*&gt;{
                StringHolder( NSString* substr ) : m_substr( [substr copy] ){}
                StringHolder( StringHolder const&amp; other ) : m_substr( [other.m_substr copy] ){}
                StringHolder() {
                    arcSafeRelease( m_substr );
                }

                bool match( NSString* str ) const override {
                    return false;
                }

                NSString* CATCH_ARC_STRONG m_substr;
            };

            struct Equals : StringHolder {
                Equals( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str isEqualToString:m_substr];
                }

                std::string describe() const override {
                    return "equals string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct Contains : StringHolder {
                Contains( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location != NSNotFound;
                }

                std::string describe() const override {
                    return "contains string: " + Catch::Detail::stringify( m_substr );
                }
            };

            struct StartsWith : StringHolder {
                StartsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location == 0;
                }

                std::string describe() const override {
                    return "starts with: " + Catch::Detail::stringify( m_substr );
                }
            };
            struct EndsWith : StringHolder {
                EndsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &amp;&amp;
                            [str rangeOfString:m_substr].location == [str length] - [m_substr length];
                }

                std::string describe() const override {
                    return "ends with: " + Catch::Detail::stringify( m_substr );
                }
            };

        } // namespace NSStringMatchers
        } // namespace Impl

        inline Impl::NSStringMatchers::Equals
            Equals( NSString* substr ){ return Impl::NSStringMatchers::Equals( substr ); }

        inline Impl::NSStringMatchers::Contains
            Contains( NSString* substr ){ return Impl::NSStringMatchers::Contains( substr ); }

        inline Impl::NSStringMatchers::StartsWith
            StartsWith( NSString* substr ){ return Impl::NSStringMatchers::StartsWith( substr ); }

        inline Impl::NSStringMatchers::EndsWith
            EndsWith( NSString* substr ){ return Impl::NSStringMatchers::EndsWith( substr ); }

    } // namespace Matchers

    using namespace Matchers;

#endif // CATCH_CONFIG_DISABLE_MATCHERS

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define OC_MAKE_UNIQUE_NAME( root, uniqueSuffix ) root##uniqueSuffix
#define OC_TEST_CASE2( name, desc, uniqueSuffix ) \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Name_test_, uniqueSuffix ) \
{ \
return @ name; \
} \
+(NSString*) OC_MAKE_UNIQUE_NAME( Catch_Description_test_, uniqueSuffix ) \
{ \
return @ desc; \
} \
-(void) OC_MAKE_UNIQUE_NAME( Catch_TestCase_test_, uniqueSuffix )

#define OC_TEST_CASE( name, desc ) OC_TEST_CASE2( name, desc, __LINE__ )

// end catch_objc.hpp
#endif

// Benchmarking needs the externally-facing parts of reporters to work
#if defined(CATCH_CONFIG_EXTERNAL_INTERFACES) || defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
// start catch_external_interfaces.h

// start catch_reporter_bases.hpp

// start catch_interfaces_reporter.h

// start catch_config.hpp

// start catch_test_spec_parser.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_test_spec.h

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_wildcard_pattern.h

namespace Catch
{
    class WildcardPattern {
        enum WildcardPosition {
            NoWildcard = 0,
            WildcardAtStart = 1,
            WildcardAtEnd = 2,
            WildcardAtBothEnds = WildcardAtStart | WildcardAtEnd
        };

    public:

        WildcardPattern( std::string const&amp; pattern, CaseSensitive::Choice caseSensitivity );
        virtual ~WildcardPattern() = default;
        virtual bool matches( std::string const&amp; str ) const;

    private:
        std::string normaliseString( std::string const&amp; str ) const;
        CaseSensitive::Choice m_caseSensitivity;
        WildcardPosition m_wildcard = NoWildcard;
        std::string m_pattern;
    };
}

// end catch_wildcard_pattern.h
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    struct IConfig;

    class TestSpec {
        class Pattern {
        public:
            explicit Pattern( std::string const&amp; name );
            virtual ~Pattern();
            virtual bool matches( TestCaseInfo const&amp; testCase ) const = 0;
            std::string const&amp; name() const;
        private:
            std::string const m_name;
        };
        using PatternPtr = std::shared_ptr&lt;Pattern&gt;;

        class NamePattern : public Pattern {
        public:
            explicit NamePattern( std::string const&amp; name, std::string const&amp; filterString );
            bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            WildcardPattern m_wildcardPattern;
        };

        class TagPattern : public Pattern {
        public:
            explicit TagPattern( std::string const&amp; tag, std::string const&amp; filterString );
            bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            std::string m_tag;
        };

        class ExcludedPattern : public Pattern {
        public:
            explicit ExcludedPattern( PatternPtr const&amp; underlyingPattern );
            bool matches( TestCaseInfo const&amp; testCase ) const override;
        private:
            PatternPtr m_underlyingPattern;
        };

        struct Filter {
            std::vector&lt;PatternPtr&gt; m_patterns;

            bool matches( TestCaseInfo const&amp; testCase ) const;
            std::string name() const;
        };

    public:
        struct FilterMatch {
            std::string name;
            std::vector&lt;TestCase const*&gt; tests;
        };
        using Matches = std::vector&lt;FilterMatch&gt;;
        using vectorStrings = std::vector&lt;std::string&gt;;

        bool hasFilters() const;
        bool matches( TestCaseInfo const&amp; testCase ) const;
        Matches matchesByFilter( std::vector&lt;TestCase&gt; const&amp; testCases, IConfig const&amp; config ) const;
        const vectorStrings &amp; getInvalidArgs() const;

    private:
        std::vector&lt;Filter&gt; m_filters;
        std::vector&lt;std::string&gt; m_invalidArgs;
        friend class TestSpecParser;
    };
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec.h
// start catch_interfaces_tag_alias_registry.h

#include &lt;string&gt;

namespace Catch {

    struct TagAlias;

    struct ITagAliasRegistry {
        virtual ~ITagAliasRegistry();
        // Nullptr if not present
        virtual TagAlias const* find( std::string const&amp; alias ) const = 0;
        virtual std::string expandAliases( std::string const&amp; unexpandedTestSpec ) const = 0;

        static ITagAliasRegistry const&amp; get();
    };

} // end namespace Catch

// end catch_interfaces_tag_alias_registry.h
namespace Catch {

    class TestSpecParser {
        enum Mode{ None, Name, QuotedName, Tag, EscapedName };
        Mode m_mode = None;
        Mode lastMode = None;
        bool m_exclusion = false;
        std::size_t m_pos = 0;
        std::size_t m_realPatternPos = 0;
        std::string m_arg;
        std::string m_substring;
        std::string m_patternName;
        std::vector&lt;std::size_t&gt; m_escapeChars;
        TestSpec::Filter m_currentFilter;
        TestSpec m_testSpec;
        ITagAliasRegistry const* m_tagAliases = nullptr;

    public:
        TestSpecParser( ITagAliasRegistry const&amp; tagAliases );

        TestSpecParser&amp; parse( std::string const&amp; arg );
        TestSpec testSpec();

    private:
        bool visitChar( char c );
        void startNewMode( Mode mode );
        bool processNoneChar( char c );
        void processNameChar( char c );
        bool processOtherChar( char c );
        void endMode();
        void escape();
        bool isControlChar( char c ) const;
        void saveLastMode();
        void revertBackToLastMode();
        void addFilter();
        bool separate();

        // Handles common preprocessing of the pattern for name/tag patterns
        std::string preprocessPattern();
        // Adds the current pattern as a test name
        void addNamePattern();
        // Adds the current pattern as a tag
        void addTagPattern();

        inline void addCharToPattern(char c) {
            m_substring += c;
            m_patternName += c;
            m_realPatternPos++;
        }

    };
    TestSpec parseTestSpec( std::string const&amp; arg );

} // namespace Catch

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec_parser.h
// Libstdc++ doesn't like incomplete classes for unique_ptr

#include &lt;memory&gt;
#include &lt;vector&gt;
#include &lt;string&gt;

#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#define CATCH_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch {

    struct IStream;

    struct ConfigData {
        bool listTests = false;
        bool listTags = false;
        bool listReporters = false;
        bool listTestNamesOnly = false;

        bool showSuccessfulTests = false;
        bool shouldDebugBreak = false;
        bool noThrow = false;
        bool showHelp = false;
        bool showInvisibles = false;
        bool filenamesAsTags = false;
        bool libIdentify = false;

        int abortAfter = -1;
        unsigned int rngSeed = 0;

        bool benchmarkNoAnalysis = false;
        unsigned int benchmarkSamples = 100;
        double benchmarkConfidenceInterval = 0.95;
        unsigned int benchmarkResamples = 100000;
        std::chrono::milliseconds::rep benchmarkWarmupTime = 100;

        Verbosity verbosity = Verbosity::Normal;
        WarnAbout::What warnings = WarnAbout::Nothing;
        ShowDurations::OrNot showDurations = ShowDurations::DefaultForReporter;
        double minDuration = -1;
        RunTests::InWhatOrder runOrder = RunTests::InDeclarationOrder;
        UseColour::YesOrNo useColour = UseColour::Auto;
        WaitForKeypress::When waitForKeypress = WaitForKeypress::Never;

        std::string outputFilename;
        std::string name;
        std::string processName;
#ifndef CATCH_CONFIG_DEFAULT_REPORTER
#define CATCH_CONFIG_DEFAULT_REPORTER "console"
#endif
        std::string reporterName = CATCH_CONFIG_DEFAULT_REPORTER;
#undef CATCH_CONFIG_DEFAULT_REPORTER

        std::vector&lt;std::string&gt; testsOrTags;
        std::vector&lt;std::string&gt; sectionsToRun;
    };

    class Config : public IConfig {
    public:

        Config() = default;
        Config( ConfigData const&amp; data );
        virtual ~Config() = default;

        std::string const&amp; getFilename() const;

        bool listTests() const;
        bool listTestNamesOnly() const;
        bool listTags() const;
        bool listReporters() const;

        std::string getProcessName() const;
        std::string const&amp; getReporterName() const;

        std::vector&lt;std::string&gt; const&amp; getTestsOrTags() const override;
        std::vector&lt;std::string&gt; const&amp; getSectionsToRun() const override;

        TestSpec const&amp; testSpec() const override;
        bool hasTestFilters() const override;

        bool showHelp() const;

        // IConfig interface
        bool allowThrows() const override;
        std::ostream&amp; stream() const override;
        std::string name() const override;
        bool includeSuccessfulResults() const override;
        bool warnAboutMissingAssertions() const override;
        bool warnAboutNoTests() const override;
        ShowDurations::OrNot showDurations() const override;
        double minDuration() const override;
        RunTests::InWhatOrder runOrder() const override;
        unsigned int rngSeed() const override;
        UseColour::YesOrNo useColour() const override;
        bool shouldDebugBreak() const override;
        int abortAfter() const override;
        bool showInvisibles() const override;
        Verbosity verbosity() const override;
        bool benchmarkNoAnalysis() const override;
        int benchmarkSamples() const override;
        double benchmarkConfidenceInterval() const override;
        unsigned int benchmarkResamples() const override;
        std::chrono::milliseconds benchmarkWarmupTime() const override;

    private:

        IStream const* openStream();
        ConfigData m_data;

        std::unique_ptr&lt;IStream const&gt; m_stream;
        TestSpec m_testSpec;
        bool m_hasTestFilters = false;
    };

} // end namespace Catch

// end catch_config.hpp
// start catch_assertionresult.h

#include &lt;string&gt;

namespace Catch {

    struct AssertionResultData
    {
        AssertionResultData() = delete;

        AssertionResultData( ResultWas::OfType _resultType, LazyExpression const&amp; _lazyExpression );

        std::string message;
        mutable std::string reconstructedExpression;
        LazyExpression lazyExpression;
        ResultWas::OfType resultType;

        std::string reconstructExpression() const;
    };

    class AssertionResult {
    public:
        AssertionResult() = delete;
        AssertionResult( AssertionInfo const&amp; info, AssertionResultData const&amp; data );

        bool isOk() const;
        bool succeeded() const;
        ResultWas::OfType getResultType() const;
        bool hasExpression() const;
        bool hasMessage() const;
        std::string getExpression() const;
        std::string getExpressionInMacro() const;
        bool hasExpandedExpression() const;
        std::string getExpandedExpression() const;
        std::string getMessage() const;
        SourceLineInfo getSourceInfo() const;
        StringRef getTestMacroName() const;

    //protected:
        AssertionInfo m_info;
        AssertionResultData m_resultData;
    };

} // end namespace Catch

// end catch_assertionresult.h
#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
// start catch_estimate.hpp

 // Statistics estimates


namespace Catch {
    namespace Benchmark {
        template &lt;typename Duration&gt;
        struct Estimate {
            Duration point;
            Duration lower_bound;
            Duration upper_bound;
            double confidence_interval;

            template &lt;typename Duration2&gt;
            operator Estimate&lt;Duration2&gt;() const {
                return { point, lower_bound, upper_bound, confidence_interval };
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_estimate.hpp
// start catch_outlier_classification.hpp

// Outlier information

namespace Catch {
    namespace Benchmark {
        struct OutlierClassification {
            int samples_seen = 0;
            int low_severe = 0;     // more than 3 times IQR below Q1
            int low_mild = 0;       // 1.5 to 3 times IQR below Q1
            int high_mild = 0;      // 1.5 to 3 times IQR above Q3
            int high_severe = 0;    // more than 3 times IQR above Q3

            int total() const {
                return low_severe + low_mild + high_mild + high_severe;
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_outlier_classification.hpp
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

#include &lt;string&gt;
#include &lt;iosfwd&gt;
#include &lt;map&gt;
#include &lt;set&gt;
#include &lt;memory&gt;
#include &lt;algorithm&gt;

namespace Catch {

    struct ReporterConfig {
        explicit ReporterConfig( IConfigPtr const&amp; _fullConfig );

        ReporterConfig( IConfigPtr const&amp; _fullConfig, std::ostream&amp; _stream );

        std::ostream&amp; stream() const;
        IConfigPtr fullConfig() const;

    private:
        std::ostream* m_stream;
        IConfigPtr m_fullConfig;
    };

    struct ReporterPreferences {
        bool shouldRedirectStdOut = false;
        bool shouldReportAllAssertions = false;
    };

    template&lt;typename T&gt;
    struct LazyStat : Option&lt;T&gt; {
        LazyStat&amp; operator=( T const&amp; _value ) {
            Option&lt;T&gt;::operator=( _value );
            used = false;
            return *this;
        }
        void reset() {
            Option&lt;T&gt;::reset();
            used = false;
        }
        bool used = false;
    };

    struct TestRunInfo {
        TestRunInfo( std::string const&amp; _name );
        std::string name;
    };
    struct GroupInfo {
        GroupInfo(  std::string const&amp; _name,
                    std::size_t _groupIndex,
                    std::size_t _groupsCount );

        std::string name;
        std::size_t groupIndex;
        std::size_t groupsCounts;
    };

    struct AssertionStats {
        AssertionStats( AssertionResult const&amp; _assertionResult,
                        std::vector&lt;MessageInfo&gt; const&amp; _infoMessages,
                        Totals const&amp; _totals );

        AssertionStats( AssertionStats const&amp; )              = default;
        AssertionStats( AssertionStats &amp;&amp; )                  = default;
        AssertionStats&amp; operator = ( AssertionStats const&amp; ) = delete;
        AssertionStats&amp; operator = ( AssertionStats &amp;&amp; )     = delete;
        virtual ~AssertionStats();

        AssertionResult assertionResult;
        std::vector&lt;MessageInfo&gt; infoMessages;
        Totals totals;
    };

    struct SectionStats {
        SectionStats(   SectionInfo const&amp; _sectionInfo,
                        Counts const&amp; _assertions,
                        double _durationInSeconds,
                        bool _missingAssertions );
        SectionStats( SectionStats const&amp; )              = default;
        SectionStats( SectionStats &amp;&amp; )                  = default;
        SectionStats&amp; operator = ( SectionStats const&amp; ) = default;
        SectionStats&amp; operator = ( SectionStats &amp;&amp; )     = default;
        virtual ~SectionStats();

        SectionInfo sectionInfo;
        Counts assertions;
        double durationInSeconds;
        bool missingAssertions;
    };

    struct TestCaseStats {
        TestCaseStats(  TestCaseInfo const&amp; _testInfo,
                        Totals const&amp; _totals,
                        std::string const&amp; _stdOut,
                        std::string const&amp; _stdErr,
                        bool _aborting );

        TestCaseStats( TestCaseStats const&amp; )              = default;
        TestCaseStats( TestCaseStats &amp;&amp; )                  = default;
        TestCaseStats&amp; operator = ( TestCaseStats const&amp; ) = default;
        TestCaseStats&amp; operator = ( TestCaseStats &amp;&amp; )     = default;
        virtual ~TestCaseStats();

        TestCaseInfo testInfo;
        Totals totals;
        std::string stdOut;
        std::string stdErr;
        bool aborting;
    };

    struct TestGroupStats {
        TestGroupStats( GroupInfo const&amp; _groupInfo,
                        Totals const&amp; _totals,
                        bool _aborting );
        TestGroupStats( GroupInfo const&amp; _groupInfo );

        TestGroupStats( TestGroupStats const&amp; )              = default;
        TestGroupStats( TestGroupStats &amp;&amp; )                  = default;
        TestGroupStats&amp; operator = ( TestGroupStats const&amp; ) = default;
        TestGroupStats&amp; operator = ( TestGroupStats &amp;&amp; )     = default;
        virtual ~TestGroupStats();

        GroupInfo groupInfo;
        Totals totals;
        bool aborting;
    };

    struct TestRunStats {
        TestRunStats(   TestRunInfo const&amp; _runInfo,
                        Totals const&amp; _totals,
                        bool _aborting );

        TestRunStats( TestRunStats const&amp; )              = default;
        TestRunStats( TestRunStats &amp;&amp; )                  = default;
        TestRunStats&amp; operator = ( TestRunStats const&amp; ) = default;
        TestRunStats&amp; operator = ( TestRunStats &amp;&amp; )     = default;
        virtual ~TestRunStats();

        TestRunInfo runInfo;
        Totals totals;
        bool aborting;
    };

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    struct BenchmarkInfo {
        std::string name;
        double estimatedDuration;
        int iterations;
        int samples;
        unsigned int resamples;
        double clockResolution;
        double clockCost;
    };

    template &lt;class Duration&gt;
    struct BenchmarkStats {
        BenchmarkInfo info;

        std::vector&lt;Duration&gt; samples;
        Benchmark::Estimate&lt;Duration&gt; mean;
        Benchmark::Estimate&lt;Duration&gt; standardDeviation;
        Benchmark::OutlierClassification outliers;
        double outlierVariance;

        template &lt;typename Duration2&gt;
        operator BenchmarkStats&lt;Duration2&gt;() const {
            std::vector&lt;Duration2&gt; samples2;
            samples2.reserve(samples.size());
            std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](Duration d) { return Duration2(d); });
            return {
                info,
                std::move(samples2),
                mean,
                standardDeviation,
                outliers,
                outlierVariance,
            };
        }
    };
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    struct IStreamingReporter {
        virtual ~IStreamingReporter() = default;

        // Implementing class must also provide the following static methods:
        // static std::string getDescription();
        // static std::set&lt;Verbosity&gt; getSupportedVerbosities()

        virtual ReporterPreferences getPreferences() const = 0;

        virtual void noMatchingTestCases( std::string const&amp; spec ) = 0;

        virtual void reportInvalidArguments(std::string const&amp;) {}

        virtual void testRunStarting( TestRunInfo const&amp; testRunInfo ) = 0;
        virtual void testGroupStarting( GroupInfo const&amp; groupInfo ) = 0;

        virtual void testCaseStarting( TestCaseInfo const&amp; testInfo ) = 0;
        virtual void sectionStarting( SectionInfo const&amp; sectionInfo ) = 0;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        virtual void benchmarkPreparing( std::string const&amp; ) {}
        virtual void benchmarkStarting( BenchmarkInfo const&amp; ) {}
        virtual void benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; ) {}
        virtual void benchmarkFailed( std::string const&amp; ) {}
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        virtual void assertionStarting( AssertionInfo const&amp; assertionInfo ) = 0;

        // The return value indicates if the messages buffer should be cleared:
        virtual bool assertionEnded( AssertionStats const&amp; assertionStats ) = 0;

        virtual void sectionEnded( SectionStats const&amp; sectionStats ) = 0;
        virtual void testCaseEnded( TestCaseStats const&amp; testCaseStats ) = 0;
        virtual void testGroupEnded( TestGroupStats const&amp; testGroupStats ) = 0;
        virtual void testRunEnded( TestRunStats const&amp; testRunStats ) = 0;

        virtual void skipTest( TestCaseInfo const&amp; testInfo ) = 0;

        // Default empty implementation provided
        virtual void fatalErrorEncountered( StringRef name );

        virtual bool isMulti() const;
    };
    using IStreamingReporterPtr = std::unique_ptr&lt;IStreamingReporter&gt;;

    struct IReporterFactory {
        virtual ~IReporterFactory();
        virtual IStreamingReporterPtr create( ReporterConfig const&amp; config ) const = 0;
        virtual std::string getDescription() const = 0;
    };
    using IReporterFactoryPtr = std::shared_ptr&lt;IReporterFactory&gt;;

    struct IReporterRegistry {
        using FactoryMap = std::map&lt;std::string, IReporterFactoryPtr&gt;;
        using Listeners = std::vector&lt;IReporterFactoryPtr&gt;;

        virtual ~IReporterRegistry();
        virtual IStreamingReporterPtr create( std::string const&amp; name, IConfigPtr const&amp; config ) const = 0;
        virtual FactoryMap const&amp; getFactories() const = 0;
        virtual Listeners const&amp; getListeners() const = 0;
    };

} // end namespace Catch

// end catch_interfaces_reporter.h
#include &lt;algorithm&gt;
#include &lt;cstring&gt;
#include &lt;cfloat&gt;
#include &lt;cstdio&gt;
#include &lt;cassert&gt;
#include &lt;memory&gt;
#include &lt;ostream&gt;

namespace Catch {
    void prepareExpandedExpression(AssertionResult&amp; result);

    // Returns double formatted as %.3f (format expected on output)
    std::string getFormattedDuration( double duration );

    //! Should the reporter show
    bool shouldShowDuration( IConfig const&amp; config, double duration );

    std::string serializeFilters( std::vector&lt;std::string&gt; const&amp; container );

    template&lt;typename DerivedT&gt;
    struct StreamingReporterBase : IStreamingReporter {

        StreamingReporterBase( ReporterConfig const&amp; _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            if( !DerivedT::getSupportedVerbosities().count( m_config-&gt;verbosity() ) )
                CATCH_ERROR( "Verbosity level not supported by this reporter" );
        }

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set&lt;Verbosity&gt; getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        ~StreamingReporterBase() override = default;

        void noMatchingTestCases(std::string const&amp;) override {}

        void reportInvalidArguments(std::string const&amp;) override {}

        void testRunStarting(TestRunInfo const&amp; _testRunInfo) override {
            currentTestRunInfo = _testRunInfo;
        }

        void testGroupStarting(GroupInfo const&amp; _groupInfo) override {
            currentGroupInfo = _groupInfo;
        }

        void testCaseStarting(TestCaseInfo const&amp; _testInfo) override  {
            currentTestCaseInfo = _testInfo;
        }
        void sectionStarting(SectionInfo const&amp; _sectionInfo) override {
            m_sectionStack.push_back(_sectionInfo);
        }

        void sectionEnded(SectionStats const&amp; /* _sectionStats */) override {
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const&amp; /* _testCaseStats */) override {
            currentTestCaseInfo.reset();
        }
        void testGroupEnded(TestGroupStats const&amp; /* _testGroupStats */) override {
            currentGroupInfo.reset();
        }
        void testRunEnded(TestRunStats const&amp; /* _testRunStats */) override {
            currentTestCaseInfo.reset();
            currentGroupInfo.reset();
            currentTestRunInfo.reset();
        }

        void skipTest(TestCaseInfo const&amp;) override {
            // Don't do anything with this by default.
            // It can optionally be overridden in the derived class.
        }

        IConfigPtr m_config;
        std::ostream&amp; stream;

        LazyStat&lt;TestRunInfo&gt; currentTestRunInfo;
        LazyStat&lt;GroupInfo&gt; currentGroupInfo;
        LazyStat&lt;TestCaseInfo&gt; currentTestCaseInfo;

        std::vector&lt;SectionInfo&gt; m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template&lt;typename DerivedT&gt;
    struct CumulativeReporterBase : IStreamingReporter {
        template&lt;typename T, typename ChildNodeT&gt;
        struct Node {
            explicit Node( T const&amp; _value ) : value( _value ) {}
            virtual ~Node() {}

            using ChildNodes = std::vector&lt;std::shared_ptr&lt;ChildNodeT&gt;&gt;;
            T value;
            ChildNodes children;
        };
        struct SectionNode {
            explicit SectionNode(SectionStats const&amp; _stats) : stats(_stats) {}
            virtual ~SectionNode() = default;

            bool operator == (SectionNode const&amp; other) const {
                return stats.sectionInfo.lineInfo == other.stats.sectionInfo.lineInfo;
            }
            bool operator == (std::shared_ptr&lt;SectionNode&gt; const&amp; other) const {
                return operator==(*other);
            }

            SectionStats stats;
            using ChildSections = std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt;;
            using Assertions = std::vector&lt;AssertionStats&gt;;
            ChildSections childSections;
            Assertions assertions;
            std::string stdOut;
            std::string stdErr;
        };

        struct BySectionInfo {
            BySectionInfo( SectionInfo const&amp; other ) : m_other( other ) {}
            BySectionInfo( BySectionInfo const&amp; other ) : m_other( other.m_other ) {}
            bool operator() (std::shared_ptr&lt;SectionNode&gt; const&amp; node) const {
                return ((node-&gt;stats.sectionInfo.name == m_other.name) &amp;&amp;
                        (node-&gt;stats.sectionInfo.lineInfo == m_other.lineInfo));
            }
            void operator=(BySectionInfo const&amp;) = delete;

        private:
            SectionInfo const&amp; m_other;
        };

        using TestCaseNode = Node&lt;TestCaseStats, SectionNode&gt;;
        using TestGroupNode = Node&lt;TestGroupStats, TestCaseNode&gt;;
        using TestRunNode = Node&lt;TestRunStats, TestGroupNode&gt;;

        CumulativeReporterBase( ReporterConfig const&amp; _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            if( !DerivedT::getSupportedVerbosities().count( m_config-&gt;verbosity() ) )
                CATCH_ERROR( "Verbosity level not supported by this reporter" );
        }
        ~CumulativeReporterBase() override = default;

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set&lt;Verbosity&gt; getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        void testRunStarting( TestRunInfo const&amp; ) override {}
        void testGroupStarting( GroupInfo const&amp; ) override {}

        void testCaseStarting( TestCaseInfo const&amp; ) override {}

        void sectionStarting( SectionInfo const&amp; sectionInfo ) override {
            SectionStats incompleteStats( sectionInfo, Counts(), 0, false );
            std::shared_ptr&lt;SectionNode&gt; node;
            if( m_sectionStack.empty() ) {
                if( !m_rootSection )
                    m_rootSection = std::make_shared&lt;SectionNode&gt;( incompleteStats );
                node = m_rootSection;
            }
            else {
                SectionNode&amp; parentNode = *m_sectionStack.back();
                auto it =
                    std::find_if(   parentNode.childSections.begin(),
                                    parentNode.childSections.end(),
                                    BySectionInfo( sectionInfo ) );
                if( it == parentNode.childSections.end() ) {
                    node = std::make_shared&lt;SectionNode&gt;( incompleteStats );
                    parentNode.childSections.push_back( node );
                }
                else
                    node = *it;
            }
            m_sectionStack.push_back( node );
            m_deepestSection = std::move(node);
        }

        void assertionStarting(AssertionInfo const&amp;) override {}

        bool assertionEnded(AssertionStats const&amp; assertionStats) override {
            assert(!m_sectionStack.empty());
            // AssertionResult holds a pointer to a temporary DecomposedExpression,
            // which getExpandedExpression() calls to build the expression string.
            // Our section stack copy of the assertionResult will likely outlive the
            // temporary, so it must be expanded or discarded now to avoid calling
            // a destroyed object later.
            prepareExpandedExpression(const_cast&lt;AssertionResult&amp;&gt;( assertionStats.assertionResult ) );
            SectionNode&amp; sectionNode = *m_sectionStack.back();
            sectionNode.assertions.push_back(assertionStats);
            return true;
        }
        void sectionEnded(SectionStats const&amp; sectionStats) override {
            assert(!m_sectionStack.empty());
            SectionNode&amp; node = *m_sectionStack.back();
            node.stats = sectionStats;
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const&amp; testCaseStats) override {
            auto node = std::make_shared&lt;TestCaseNode&gt;(testCaseStats);
            assert(m_sectionStack.size() == 0);
            node-&gt;children.push_back(m_rootSection);
            m_testCases.push_back(node);
            m_rootSection.reset();

            assert(m_deepestSection);
            m_deepestSection-&gt;stdOut = testCaseStats.stdOut;
            m_deepestSection-&gt;stdErr = testCaseStats.stdErr;
        }
        void testGroupEnded(TestGroupStats const&amp; testGroupStats) override {
            auto node = std::make_shared&lt;TestGroupNode&gt;(testGroupStats);
            node-&gt;children.swap(m_testCases);
            m_testGroups.push_back(node);
        }
        void testRunEnded(TestRunStats const&amp; testRunStats) override {
            auto node = std::make_shared&lt;TestRunNode&gt;(testRunStats);
            node-&gt;children.swap(m_testGroups);
            m_testRuns.push_back(node);
            testRunEndedCumulative();
        }
        virtual void testRunEndedCumulative() = 0;

        void skipTest(TestCaseInfo const&amp;) override {}

        IConfigPtr m_config;
        std::ostream&amp; stream;
        std::vector&lt;AssertionStats&gt; m_assertions;
        std::vector&lt;std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt;&gt; m_sections;
        std::vector&lt;std::shared_ptr&lt;TestCaseNode&gt;&gt; m_testCases;
        std::vector&lt;std::shared_ptr&lt;TestGroupNode&gt;&gt; m_testGroups;

        std::vector&lt;std::shared_ptr&lt;TestRunNode&gt;&gt; m_testRuns;

        std::shared_ptr&lt;SectionNode&gt; m_rootSection;
        std::shared_ptr&lt;SectionNode&gt; m_deepestSection;
        std::vector&lt;std::shared_ptr&lt;SectionNode&gt;&gt; m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template&lt;char C&gt;
    char const* getLineOfChars() {
        static char line[CATCH_CONFIG_CONSOLE_WIDTH] = {0};
        if( !*line ) {
            std::memset( line, C, CATCH_CONFIG_CONSOLE_WIDTH-1 );
            line[CATCH_CONFIG_CONSOLE_WIDTH-1] = 0;
        }
        return line;
    }

    struct TestEventListenerBase : StreamingReporterBase&lt;TestEventListenerBase&gt; {
        TestEventListenerBase( ReporterConfig const&amp; _config );

        static std::set&lt;Verbosity&gt; getSupportedVerbosities();

        void assertionStarting(AssertionInfo const&amp;) override;
        bool assertionEnded(AssertionStats const&amp;) override;
    };

} // end namespace Catch

// end catch_reporter_bases.hpp
// start catch_console_colour.h

namespace Catch {

    struct Colour {
        enum Code {
            None = 0,

            White,
            Red,
            Green,
            Blue,
            Cyan,
            Yellow,
            Grey,

            Bright = 0x10,

            BrightRed = Bright | Red,
            BrightGreen = Bright | Green,
            LightGrey = Bright | Grey,
            BrightWhite = Bright | White,
            BrightYellow = Bright | Yellow,

            // By intention
            FileName = LightGrey,
            Warning = BrightYellow,
            ResultError = BrightRed,
            ResultSuccess = BrightGreen,
            ResultExpectedFailure = Warning,

            Error = BrightRed,
            Success = Green,

            OriginalExpression = Cyan,
            ReconstructedExpression = BrightYellow,

            SecondaryText = LightGrey,
            Headers = White
        };

        // Use constructed object for RAII guard
        Colour( Code _colourCode );
        Colour( Colour&amp;&amp; other ) noexcept;
        Colour&amp; operator=( Colour&amp;&amp; other ) noexcept;
        ~Colour();

        // Use static method for one-shot changes
        static void use( Code _colourCode );

    private:
        bool m_moved = false;
    };

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Colour const&amp; );

} // end namespace Catch

// end catch_console_colour.h
// start catch_reporter_registrars.hpp


namespace Catch {

    template&lt;typename T&gt;
    class ReporterRegistrar {

        class ReporterFactory : public IReporterFactory {

            IStreamingReporterPtr create( ReporterConfig const&amp; config ) const override {
                return std::unique_ptr&lt;T&gt;( new T( config ) );
            }

            std::string getDescription() const override {
                return T::getDescription();
            }
        };

    public:

        explicit ReporterRegistrar( std::string const&amp; name ) {
            getMutableRegistryHub().registerReporter( name, std::make_shared&lt;ReporterFactory&gt;() );
        }
    };

    template&lt;typename T&gt;
    class ListenerRegistrar {

        class ListenerFactory : public IReporterFactory {

            IStreamingReporterPtr create( ReporterConfig const&amp; config ) const override {
                return std::unique_ptr&lt;T&gt;( new T( config ) );
            }
            std::string getDescription() const override {
                return std::string();
            }
        };

    public:

        ListenerRegistrar() {
            getMutableRegistryHub().registerListener( std::make_shared&lt;ListenerFactory&gt;() );
        }
    };
}

#if !defined(CATCH_CONFIG_DISABLE)

#define CATCH_REGISTER_REPORTER( name, reporterType ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION         \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS          \
    namespace{ Catch::ReporterRegistrar&lt;reporterType&gt; catch_internal_RegistrarFor##reporterType( name ); } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

#define CATCH_REGISTER_LISTENER( listenerType ) \
    CATCH_INTERNAL_START_WARNINGS_SUPPRESSION   \
    CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS    \
    namespace{ Catch::ListenerRegistrar&lt;listenerType&gt; catch_internal_RegistrarFor##listenerType; } \
    CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
#else // CATCH_CONFIG_DISABLE

#define CATCH_REGISTER_REPORTER(name, reporterType)
#define CATCH_REGISTER_LISTENER(listenerType)

#endif // CATCH_CONFIG_DISABLE

// end catch_reporter_registrars.hpp
// Allow users to base their work off existing reporters
// start catch_reporter_compact.h

namespace Catch {

    struct CompactReporter : StreamingReporterBase&lt;CompactReporter&gt; {

        using StreamingReporterBase::StreamingReporterBase;

        ~CompactReporter() override;

        static std::string getDescription();

        void noMatchingTestCases(std::string const&amp; spec) override;

        void assertionStarting(AssertionInfo const&amp;) override;

        bool assertionEnded(AssertionStats const&amp; _assertionStats) override;

        void sectionEnded(SectionStats const&amp; _sectionStats) override;

        void testRunEnded(TestRunStats const&amp; _testRunStats) override;

    };

} // end namespace Catch

// end catch_reporter_compact.h
// start catch_reporter_console.h

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // Not all labels are EXPLICITLY handled in switch
                              // Note that 4062 (not all labels are handled
                              // and default is missing) is enabled
#endif

namespace Catch {
    // Fwd decls
    struct SummaryColumn;
    class TablePrinter;

    struct ConsoleReporter : StreamingReporterBase&lt;ConsoleReporter&gt; {
        std::unique_ptr&lt;TablePrinter&gt; m_tablePrinter;

        ConsoleReporter(ReporterConfig const&amp; config);
        ~ConsoleReporter() override;
        static std::string getDescription();

        void noMatchingTestCases(std::string const&amp; spec) override;

        void reportInvalidArguments(std::string const&amp;arg) override;

        void assertionStarting(AssertionInfo const&amp;) override;

        bool assertionEnded(AssertionStats const&amp; _assertionStats) override;

        void sectionStarting(SectionInfo const&amp; _sectionInfo) override;
        void sectionEnded(SectionStats const&amp; _sectionStats) override;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        void benchmarkPreparing(std::string const&amp; name) override;
        void benchmarkStarting(BenchmarkInfo const&amp; info) override;
        void benchmarkEnded(BenchmarkStats&lt;&gt; const&amp; stats) override;
        void benchmarkFailed(std::string const&amp; error) override;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        void testCaseEnded(TestCaseStats const&amp; _testCaseStats) override;
        void testGroupEnded(TestGroupStats const&amp; _testGroupStats) override;
        void testRunEnded(TestRunStats const&amp; _testRunStats) override;
        void testRunStarting(TestRunInfo const&amp; _testRunInfo) override;
    private:

        void lazyPrint();

        void lazyPrintWithoutClosingBenchmarkTable();
        void lazyPrintRunInfo();
        void lazyPrintGroupInfo();
        void printTestCaseAndSectionHeader();

        void printClosedHeader(std::string const&amp; _name);
        void printOpenHeader(std::string const&amp; _name);

        // if string has a : in first line will set indent to follow it on
        // subsequent lines
        void printHeaderString(std::string const&amp; _string, std::size_t indent = 0);

        void printTotals(Totals const&amp; totals);
        void printSummaryRow(std::string const&amp; label, std::vector&lt;SummaryColumn&gt; const&amp; cols, std::size_t row);

        void printTotalsDivider(Totals const&amp; totals);
        void printSummaryDivider();
        void printTestFilters();

    private:
        bool m_headerPrinted = false;
    };

} // end namespace Catch

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

// end catch_reporter_console.h
// start catch_reporter_junit.h

// start catch_xmlwriter.h

#include &lt;vector&gt;

namespace Catch {
    enum class XmlFormatting {
        None = 0x00,
        Indent = 0x01,
        Newline = 0x02,
    };

    XmlFormatting operator | (XmlFormatting lhs, XmlFormatting rhs);
    XmlFormatting operator &amp; (XmlFormatting lhs, XmlFormatting rhs);

    class XmlEncode {
    public:
        enum ForWhat { ForTextNodes, ForAttributes };

        XmlEncode( std::string const&amp; str, ForWhat forWhat = ForTextNodes );

        void encodeTo( std::ostream&amp; os ) const;

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, XmlEncode const&amp; xmlEncode );

    private:
        std::string m_str;
        ForWhat m_forWhat;
    };

    class XmlWriter {
    public:

        class ScopedElement {
        public:
            ScopedElement( XmlWriter* writer, XmlFormatting fmt );

            ScopedElement( ScopedElement&amp;&amp; other ) noexcept;
            ScopedElement&amp; operator=( ScopedElement&amp;&amp; other ) noexcept;

            ~ScopedElement();

            ScopedElement&amp; writeText( std::string const&amp; text, XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent );

            template&lt;typename T&gt;
            ScopedElement&amp; writeAttribute( std::string const&amp; name, T const&amp; attribute ) {
                m_writer-&gt;writeAttribute( name, attribute );
                return *this;
            }

        private:
            mutable XmlWriter* m_writer = nullptr;
            XmlFormatting m_fmt;
        };

        XmlWriter( std::ostream&amp; os = Catch::cout() );
        ~XmlWriter();

        XmlWriter( XmlWriter const&amp; ) = delete;
        XmlWriter&amp; operator=( XmlWriter const&amp; ) = delete;

        XmlWriter&amp; startElement( std::string const&amp; name, XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent);

        ScopedElement scopedElement( std::string const&amp; name, XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent);

        XmlWriter&amp; endElement(XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent);

        XmlWriter&amp; writeAttribute( std::string const&amp; name, std::string const&amp; attribute );

        XmlWriter&amp; writeAttribute( std::string const&amp; name, bool attribute );

        template&lt;typename T&gt;
        XmlWriter&amp; writeAttribute( std::string const&amp; name, T const&amp; attribute ) {
            ReusableStringStream rss;
            rss &lt;&lt; attribute;
            return writeAttribute( name, rss.str() );
        }

        XmlWriter&amp; writeText( std::string const&amp; text, XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent);

        XmlWriter&amp; writeComment(std::string const&amp; text, XmlFormatting fmt = XmlFormatting::Newline | XmlFormatting::Indent);

        void writeStylesheetRef( std::string const&amp; url );

        XmlWriter&amp; writeBlankLine();

        void ensureTagClosed();

    private:

        void applyFormatting(XmlFormatting fmt);

        void writeDeclaration();

        void newlineIfNecessary();

        bool m_tagIsOpen = false;
        bool m_needsNewline = false;
        std::vector&lt;std::string&gt; m_tags;
        std::string m_indent;
        std::ostream&amp; m_os;
    };

}

// end catch_xmlwriter.h
namespace Catch {

    class JunitReporter : public CumulativeReporterBase&lt;JunitReporter&gt; {
    public:
        JunitReporter(ReporterConfig const&amp; _config);

        ~JunitReporter() override;

        static std::string getDescription();

        void noMatchingTestCases(std::string const&amp; /*spec*/) override;

        void testRunStarting(TestRunInfo const&amp; runInfo) override;

        void testGroupStarting(GroupInfo const&amp; groupInfo) override;

        void testCaseStarting(TestCaseInfo const&amp; testCaseInfo) override;
        bool assertionEnded(AssertionStats const&amp; assertionStats) override;

        void testCaseEnded(TestCaseStats const&amp; testCaseStats) override;

        void testGroupEnded(TestGroupStats const&amp; testGroupStats) override;

        void testRunEndedCumulative() override;

        void writeGroup(TestGroupNode const&amp; groupNode, double suiteTime);

        void writeTestCase(TestCaseNode const&amp; testCaseNode);

        void writeSection(std::string const&amp; className,
                          std::string const&amp; rootName,
                          SectionNode const&amp; sectionNode);

        void writeAssertions(SectionNode const&amp; sectionNode);
        void writeAssertion(AssertionStats const&amp; stats);

        XmlWriter xml;
        Timer suiteTimer;
        std::string stdOutForSuite;
        std::string stdErrForSuite;
        unsigned int unexpectedExceptions = 0;
        bool m_okToFail = false;
    };

} // end namespace Catch

// end catch_reporter_junit.h
// start catch_reporter_xml.h

namespace Catch {
    class XmlReporter : public StreamingReporterBase&lt;XmlReporter&gt; {
    public:
        XmlReporter(ReporterConfig const&amp; _config);

        ~XmlReporter() override;

        static std::string getDescription();

        virtual std::string getStylesheetRef() const;

        void writeSourceInfo(SourceLineInfo const&amp; sourceInfo);

    public: // StreamingReporterBase

        void noMatchingTestCases(std::string const&amp; s) override;

        void testRunStarting(TestRunInfo const&amp; testInfo) override;

        void testGroupStarting(GroupInfo const&amp; groupInfo) override;

        void testCaseStarting(TestCaseInfo const&amp; testInfo) override;

        void sectionStarting(SectionInfo const&amp; sectionInfo) override;

        void assertionStarting(AssertionInfo const&amp;) override;

        bool assertionEnded(AssertionStats const&amp; assertionStats) override;

        void sectionEnded(SectionStats const&amp; sectionStats) override;

        void testCaseEnded(TestCaseStats const&amp; testCaseStats) override;

        void testGroupEnded(TestGroupStats const&amp; testGroupStats) override;

        void testRunEnded(TestRunStats const&amp; testRunStats) override;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        void benchmarkPreparing(std::string const&amp; name) override;
        void benchmarkStarting(BenchmarkInfo const&amp;) override;
        void benchmarkEnded(BenchmarkStats&lt;&gt; const&amp;) override;
        void benchmarkFailed(std::string const&amp;) override;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    private:
        Timer m_testCaseTimer;
        XmlWriter m_xml;
        int m_sectionDepth = 0;
    };

} // end namespace Catch

// end catch_reporter_xml.h

// end catch_external_interfaces.h
#endif

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
// start catch_benchmarking_all.hpp

// A proxy header that includes all of the benchmarking headers to allow
// concise include of the benchmarking features. You should prefer the
// individual includes in standard use.

// start catch_benchmark.hpp

 // Benchmark

// start catch_chronometer.hpp

// User-facing chronometer


// start catch_clock.hpp

// Clocks


#include &lt;chrono&gt;
#include &lt;ratio&gt;

namespace Catch {
    namespace Benchmark {
        template &lt;typename Clock&gt;
        using ClockDuration = typename Clock::duration;
        template &lt;typename Clock&gt;
        using FloatDuration = std::chrono::duration&lt;double, typename Clock::period&gt;;

        template &lt;typename Clock&gt;
        using TimePoint = typename Clock::time_point;

        using default_clock = std::chrono::steady_clock;

        template &lt;typename Clock&gt;
        struct now {
            TimePoint&lt;Clock&gt; operator()() const {
                return Clock::now();
            }
        };

        using fp_seconds = std::chrono::duration&lt;double, std::ratio&lt;1&gt;&gt;;
    } // namespace Benchmark
} // namespace Catch

// end catch_clock.hpp
// start catch_optimizer.hpp

 // Hinting the optimizer


#if defined(_MSC_VER)
#   include &lt;atomic&gt; // atomic_thread_fence
#endif

namespace Catch {
    namespace Benchmark {
#if defined(__GNUC__) || defined(__clang__)
        template &lt;typename T&gt;
        inline void keep_memory(T* p) {
            asm volatile("" : : "g"(p) : "memory");
        }
        inline void keep_memory() {
            asm volatile("" : : : "memory");
        }

        namespace Detail {
            inline void optimizer_barrier() { keep_memory(); }
        } // namespace Detail
#elif defined(_MSC_VER)

#pragma optimize("", off)
        template &lt;typename T&gt;
        inline void keep_memory(T* p) {
            // thanks @milleniumbug
            *reinterpret_cast&lt;char volatile*&gt;(p) = *reinterpret_cast&lt;char const volatile*&gt;(p);
        }
        // TODO equivalent keep_memory()
#pragma optimize("", on)

        namespace Detail {
            inline void optimizer_barrier() {
                std::atomic_thread_fence(std::memory_order_seq_cst);
            }
        } // namespace Detail

#endif

        template &lt;typename T&gt;
        inline void deoptimize_value(T&amp;&amp; x) {
            keep_memory(&amp;x);
        }

        template &lt;typename Fn, typename... Args&gt;
        inline auto invoke_deoptimized(Fn&amp;&amp; fn, Args&amp;&amp;... args) -&gt; typename std::enable_if&lt;!std::is_same&lt;void, decltype(fn(args...))&gt;::value&gt;::type {
            deoptimize_value(std::forward&lt;Fn&gt;(fn) (std::forward&lt;Args...&gt;(args...)));
        }

        template &lt;typename Fn, typename... Args&gt;
        inline auto invoke_deoptimized(Fn&amp;&amp; fn, Args&amp;&amp;... args) -&gt; typename std::enable_if&lt;std::is_same&lt;void, decltype(fn(args...))&gt;::value&gt;::type {
            std::forward&lt;Fn&gt;(fn) (std::forward&lt;Args...&gt;(args...));
        }
    } // namespace Benchmark
} // namespace Catch

// end catch_optimizer.hpp
// start catch_complete_invoke.hpp

// Invoke with a special case for void


#include &lt;type_traits&gt;
#include &lt;utility&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename T&gt;
            struct CompleteType { using type = T; };
            template &lt;&gt;
            struct CompleteType&lt;void&gt; { struct type {}; };

            template &lt;typename T&gt;
            using CompleteType_t = typename CompleteType&lt;T&gt;::type;

            template &lt;typename Result&gt;
            struct CompleteInvoker {
                template &lt;typename Fun, typename... Args&gt;
                static Result invoke(Fun&amp;&amp; fun, Args&amp;&amp;... args) {
                    return std::forward&lt;Fun&gt;(fun)(std::forward&lt;Args&gt;(args)...);
                }
            };
            template &lt;&gt;
            struct CompleteInvoker&lt;void&gt; {
                template &lt;typename Fun, typename... Args&gt;
                static CompleteType_t&lt;void&gt; invoke(Fun&amp;&amp; fun, Args&amp;&amp;... args) {
                    std::forward&lt;Fun&gt;(fun)(std::forward&lt;Args&gt;(args)...);
                    return {};
                }
            };

            // invoke and not return void :(
            template &lt;typename Fun, typename... Args&gt;
            CompleteType_t&lt;FunctionReturnType&lt;Fun, Args...&gt;&gt; complete_invoke(Fun&amp;&amp; fun, Args&amp;&amp;... args) {
                return CompleteInvoker&lt;FunctionReturnType&lt;Fun, Args...&gt;&gt;::invoke(std::forward&lt;Fun&gt;(fun), std::forward&lt;Args&gt;(args)...);
            }

            const std::string benchmarkErrorMsg = "a benchmark failed to run successfully";
        } // namespace Detail

        template &lt;typename Fun&gt;
        Detail::CompleteType_t&lt;FunctionReturnType&lt;Fun&gt;&gt; user_code(Fun&amp;&amp; fun) {
            CATCH_TRY{
                return Detail::complete_invoke(std::forward&lt;Fun&gt;(fun));
            } CATCH_CATCH_ALL{
                getResultCapture().benchmarkFailed(translateActiveException());
                CATCH_RUNTIME_ERROR(Detail::benchmarkErrorMsg);
            }
        }
    } // namespace Benchmark
} // namespace Catch

// end catch_complete_invoke.hpp
namespace Catch {
    namespace Benchmark {
        namespace Detail {
            struct ChronometerConcept {
                virtual void start() = 0;
                virtual void finish() = 0;
                virtual ~ChronometerConcept() = default;
            };
            template &lt;typename Clock&gt;
            struct ChronometerModel final : public ChronometerConcept {
                void start() override { started = Clock::now(); }
                void finish() override { finished = Clock::now(); }

                ClockDuration&lt;Clock&gt; elapsed() const { return finished - started; }

                TimePoint&lt;Clock&gt; started;
                TimePoint&lt;Clock&gt; finished;
            };
        } // namespace Detail

        struct Chronometer {
        public:
            template &lt;typename Fun&gt;
            void measure(Fun&amp;&amp; fun) { measure(std::forward&lt;Fun&gt;(fun), is_callable&lt;Fun(int)&gt;()); }

            int runs() const { return k; }

            Chronometer(Detail::ChronometerConcept&amp; meter, int k)
                : impl(&amp;meter)
                , k(k) {}

        private:
            template &lt;typename Fun&gt;
            void measure(Fun&amp;&amp; fun, std::false_type) {
                measure([&amp;fun](int) { return fun(); }, std::true_type());
            }

            template &lt;typename Fun&gt;
            void measure(Fun&amp;&amp; fun, std::true_type) {
                Detail::optimizer_barrier();
                impl-&gt;start();
                for (int i = 0; i &lt; k; ++i) invoke_deoptimized(fun, i);
                impl-&gt;finish();
                Detail::optimizer_barrier();
            }

            Detail::ChronometerConcept* impl;
            int k;
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_chronometer.hpp
// start catch_environment.hpp

// Environment information


namespace Catch {
    namespace Benchmark {
        template &lt;typename Duration&gt;
        struct EnvironmentEstimate {
            Duration mean;
            OutlierClassification outliers;

            template &lt;typename Duration2&gt;
            operator EnvironmentEstimate&lt;Duration2&gt;() const {
                return { mean, outliers };
            }
        };
        template &lt;typename Clock&gt;
        struct Environment {
            using clock_type = Clock;
            EnvironmentEstimate&lt;FloatDuration&lt;Clock&gt;&gt; clock_resolution;
            EnvironmentEstimate&lt;FloatDuration&lt;Clock&gt;&gt; clock_cost;
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_environment.hpp
// start catch_execution_plan.hpp

 // Execution plan


// start catch_benchmark_function.hpp

 // Dumb std::function implementation for consistent call overhead


#include &lt;cassert&gt;
#include &lt;type_traits&gt;
#include &lt;utility&gt;
#include &lt;memory&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename T&gt;
            using Decay = typename std::decay&lt;T&gt;::type;
            template &lt;typename T, typename U&gt;
            struct is_related
                : std::is_same&lt;Decay&lt;T&gt;, Decay&lt;U&gt;&gt; {};

            /// We need to reinvent std::function because every piece of code that might add overhead
            /// in a measurement context needs to have consistent performance characteristics so that we
            /// can account for it in the measurement.
            /// Implementations of std::function with optimizations that aren't always applicable, like
            /// small buffer optimizations, are not uncommon.
            /// This is effectively an implementation of std::function without any such optimizations;
            /// it may be slow, but it is consistently slow.
            struct BenchmarkFunction {
            private:
                struct callable {
                    virtual void call(Chronometer meter) const = 0;
                    virtual callable* clone() const = 0;
                    virtual ~callable() = default;
                };
                template &lt;typename Fun&gt;
                struct model : public callable {
                    model(Fun&amp;&amp; fun) : fun(std::move(fun)) {}
                    model(Fun const&amp; fun) : fun(fun) {}

                    model&lt;Fun&gt;* clone() const override { return new model&lt;Fun&gt;(*this); }

                    void call(Chronometer meter) const override {
                        call(meter, is_callable&lt;Fun(Chronometer)&gt;());
                    }
                    void call(Chronometer meter, std::true_type) const {
                        fun(meter);
                    }
                    void call(Chronometer meter, std::false_type) const {
                        meter.measure(fun);
                    }

                    Fun fun;
                };

                struct do_nothing { void operator()() const {} };

                template &lt;typename T&gt;
                BenchmarkFunction(model&lt;T&gt;* c) : f(c) {}

            public:
                BenchmarkFunction()
                    : f(new model&lt;do_nothing&gt;{ {} }) {}

                template &lt;typename Fun,
                    typename std::enable_if&lt;!is_related&lt;Fun, BenchmarkFunction&gt;::value, int&gt;::type = 0&gt;
                    BenchmarkFunction(Fun&amp;&amp; fun)
                    : f(new model&lt;typename std::decay&lt;Fun&gt;::type&gt;(std::forward&lt;Fun&gt;(fun))) {}

                BenchmarkFunction(BenchmarkFunction&amp;&amp; that)
                    : f(std::move(that.f)) {}

                BenchmarkFunction(BenchmarkFunction const&amp; that)
                    : f(that.f-&gt;clone()) {}

                BenchmarkFunction&amp; operator=(BenchmarkFunction&amp;&amp; that) {
                    f = std::move(that.f);
                    return *this;
                }

                BenchmarkFunction&amp; operator=(BenchmarkFunction const&amp; that) {
                    f.reset(that.f-&gt;clone());
                    return *this;
                }

                void operator()(Chronometer meter) const { f-&gt;call(meter); }

            private:
                std::unique_ptr&lt;callable&gt; f;
            };
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_benchmark_function.hpp
// start catch_repeat.hpp

// repeat algorithm


#include &lt;type_traits&gt;
#include &lt;utility&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename Fun&gt;
            struct repeater {
                void operator()(int k) const {
                    for (int i = 0; i &lt; k; ++i) {
                        fun();
                    }
                }
                Fun fun;
            };
            template &lt;typename Fun&gt;
            repeater&lt;typename std::decay&lt;Fun&gt;::type&gt; repeat(Fun&amp;&amp; fun) {
                return { std::forward&lt;Fun&gt;(fun) };
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_repeat.hpp
// start catch_run_for_at_least.hpp

// Run a function for a minimum amount of time


// start catch_measure.hpp

// Measure


// start catch_timing.hpp

// Timing


#include &lt;tuple&gt;
#include &lt;type_traits&gt;

namespace Catch {
    namespace Benchmark {
        template &lt;typename Duration, typename Result&gt;
        struct Timing {
            Duration elapsed;
            Result result;
            int iterations;
        };
        template &lt;typename Clock, typename Func, typename... Args&gt;
        using TimingOf = Timing&lt;ClockDuration&lt;Clock&gt;, Detail::CompleteType_t&lt;FunctionReturnType&lt;Func, Args...&gt;&gt;&gt;;
    } // namespace Benchmark
} // namespace Catch

// end catch_timing.hpp
#include &lt;utility&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename Clock, typename Fun, typename... Args&gt;
            TimingOf&lt;Clock, Fun, Args...&gt; measure(Fun&amp;&amp; fun, Args&amp;&amp;... args) {
                auto start = Clock::now();
                auto&amp;&amp; r = Detail::complete_invoke(fun, std::forward&lt;Args&gt;(args)...);
                auto end = Clock::now();
                auto delta = end - start;
                return { delta, std::forward&lt;decltype(r)&gt;(r), 1 };
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_measure.hpp
#include &lt;utility&gt;
#include &lt;type_traits&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename Clock, typename Fun&gt;
            TimingOf&lt;Clock, Fun, int&gt; measure_one(Fun&amp;&amp; fun, int iters, std::false_type) {
                return Detail::measure&lt;Clock&gt;(fun, iters);
            }
            template &lt;typename Clock, typename Fun&gt;
            TimingOf&lt;Clock, Fun, Chronometer&gt; measure_one(Fun&amp;&amp; fun, int iters, std::true_type) {
                Detail::ChronometerModel&lt;Clock&gt; meter;
                auto&amp;&amp; result = Detail::complete_invoke(fun, Chronometer(meter, iters));

                return { meter.elapsed(), std::move(result), iters };
            }

            template &lt;typename Clock, typename Fun&gt;
            using run_for_at_least_argument_t = typename std::conditional&lt;is_callable&lt;Fun(Chronometer)&gt;::value, Chronometer, int&gt;::type;

            struct optimized_away_error : std::exception {
                const char* what() const noexcept override {
                    return "could not measure benchmark, maybe it was optimized away";
                }
            };

            template &lt;typename Clock, typename Fun&gt;
            TimingOf&lt;Clock, Fun, run_for_at_least_argument_t&lt;Clock, Fun&gt;&gt; run_for_at_least(ClockDuration&lt;Clock&gt; how_long, int seed, Fun&amp;&amp; fun) {
                auto iters = seed;
                while (iters &lt; (1 &lt;&lt; 30)) {
                    auto&amp;&amp; Timing = measure_one&lt;Clock&gt;(fun, iters, is_callable&lt;Fun(Chronometer)&gt;());

                    if (Timing.elapsed &gt;= how_long) {
                        return { Timing.elapsed, std::move(Timing.result), iters };
                    }
                    iters *= 2;
                }
                throw optimized_away_error{};
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_run_for_at_least.hpp
#include &lt;algorithm&gt;

namespace Catch {
    namespace Benchmark {
        template &lt;typename Duration&gt;
        struct ExecutionPlan {
            int iterations_per_sample;
            Duration estimated_duration;
            Detail::BenchmarkFunction benchmark;
            Duration warmup_time;
            int warmup_iterations;

            template &lt;typename Duration2&gt;
            operator ExecutionPlan&lt;Duration2&gt;() const {
                return { iterations_per_sample, estimated_duration, benchmark, warmup_time, warmup_iterations };
            }

            template &lt;typename Clock&gt;
            std::vector&lt;FloatDuration&lt;Clock&gt;&gt; run(const IConfig &amp;cfg, Environment&lt;FloatDuration&lt;Clock&gt;&gt; env) const {
                // warmup a bit
                Detail::run_for_at_least&lt;Clock&gt;(std::chrono::duration_cast&lt;ClockDuration&lt;Clock&gt;&gt;(warmup_time), warmup_iterations, Detail::repeat(now&lt;Clock&gt;{}));

                std::vector&lt;FloatDuration&lt;Clock&gt;&gt; times;
                times.reserve(cfg.benchmarkSamples());
                std::generate_n(std::back_inserter(times), cfg.benchmarkSamples(), [this, env] {
                    Detail::ChronometerModel&lt;Clock&gt; model;
                    this-&gt;benchmark(Chronometer(model, iterations_per_sample));
                    auto sample_time = model.elapsed() - env.clock_cost.mean;
                    if (sample_time &lt; FloatDuration&lt;Clock&gt;::zero()) sample_time = FloatDuration&lt;Clock&gt;::zero();
                    return sample_time / iterations_per_sample;
                });
                return times;
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_execution_plan.hpp
// start catch_estimate_clock.hpp

 // Environment measurement


// start catch_stats.hpp

// Statistical analysis tools


#include &lt;algorithm&gt;
#include &lt;functional&gt;
#include &lt;vector&gt;
#include &lt;iterator&gt;
#include &lt;numeric&gt;
#include &lt;tuple&gt;
#include &lt;cmath&gt;
#include &lt;utility&gt;
#include &lt;cstddef&gt;
#include &lt;random&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            using sample = std::vector&lt;double&gt;;

            double weighted_average_quantile(int k, int q, std::vector&lt;double&gt;::iterator first, std::vector&lt;double&gt;::iterator last);

            template &lt;typename Iterator&gt;
            OutlierClassification classify_outliers(Iterator first, Iterator last) {
                std::vector&lt;double&gt; copy(first, last);

                auto q1 = weighted_average_quantile(1, 4, copy.begin(), copy.end());
                auto q3 = weighted_average_quantile(3, 4, copy.begin(), copy.end());
                auto iqr = q3 - q1;
                auto los = q1 - (iqr * 3.);
                auto lom = q1 - (iqr * 1.5);
                auto him = q3 + (iqr * 1.5);
                auto his = q3 + (iqr * 3.);

                OutlierClassification o;
                for (; first != last; ++first) {
                    auto&amp;&amp; t = *first;
                    if (t &lt; los) ++o.low_severe;
                    else if (t &lt; lom) ++o.low_mild;
                    else if (t &gt; his) ++o.high_severe;
                    else if (t &gt; him) ++o.high_mild;
                    ++o.samples_seen;
                }
                return o;
            }

            template &lt;typename Iterator&gt;
            double mean(Iterator first, Iterator last) {
                auto count = last - first;
                double sum = std::accumulate(first, last, 0.);
                return sum / count;
            }

            template &lt;typename URng, typename Iterator, typename Estimator&gt;
            sample resample(URng&amp; rng, int resamples, Iterator first, Iterator last, Estimator&amp; estimator) {
                auto n = last - first;
                std::uniform_int_distribution&lt;decltype(n)&gt; dist(0, n - 1);

                sample out;
                out.reserve(resamples);
                std::generate_n(std::back_inserter(out), resamples, [n, first, &amp;estimator, &amp;dist, &amp;rng] {
                    std::vector&lt;double&gt; resampled;
                    resampled.reserve(n);
                    std::generate_n(std::back_inserter(resampled), n, [first, &amp;dist, &amp;rng] { return first[dist(rng)]; });
                    return estimator(resampled.begin(), resampled.end());
                });
                std::sort(out.begin(), out.end());
                return out;
            }

            template &lt;typename Estimator, typename Iterator&gt;
            sample jackknife(Estimator&amp;&amp; estimator, Iterator first, Iterator last) {
                auto n = last - first;
                auto second = std::next(first);
                sample results;
                results.reserve(n);

                for (auto it = first; it != last; ++it) {
                    std::iter_swap(it, first);
                    results.push_back(estimator(second, last));
                }

                return results;
            }

            inline double normal_cdf(double x) {
                return std::erfc(-x / std::sqrt(2.0)) / 2.0;
            }

            double erfc_inv(double x);

            double normal_quantile(double p);

            template &lt;typename Iterator, typename Estimator&gt;
            Estimate&lt;double&gt; bootstrap(double confidence_level, Iterator first, Iterator last, sample const&amp; resample, Estimator&amp;&amp; estimator) {
                auto n_samples = last - first;

                double point = estimator(first, last);
                // Degenerate case with a single sample
                if (n_samples == 1) return { point, point, point, confidence_level };

                sample jack = jackknife(estimator, first, last);
                double jack_mean = mean(jack.begin(), jack.end());
                double sum_squares, sum_cubes;
                std::tie(sum_squares, sum_cubes) = std::accumulate(jack.begin(), jack.end(), std::make_pair(0., 0.), [jack_mean](std::pair&lt;double, double&gt; sqcb, double x) -&gt; std::pair&lt;double, double&gt; {
                    auto d = jack_mean - x;
                    auto d2 = d * d;
                    auto d3 = d2 * d;
                    return { sqcb.first + d2, sqcb.second + d3 };
                });

                double accel = sum_cubes / (6 * std::pow(sum_squares, 1.5));
                int n = static_cast&lt;int&gt;(resample.size());
                double prob_n = std::count_if(resample.begin(), resample.end(), [point](double x) { return x &lt; point; }) / (double)n;
                // degenerate case with uniform samples
                if (prob_n == 0) return { point, point, point, confidence_level };

                double bias = normal_quantile(prob_n);
                double z1 = normal_quantile((1. - confidence_level) / 2.);

                auto cumn = [n](double x) -&gt; int {
                    return std::lround(normal_cdf(x) * n); };
                auto a = [bias, accel](double b) { return bias + b / (1. - accel * b); };
                double b1 = bias + z1;
                double b2 = bias - z1;
                double a1 = a(b1);
                double a2 = a(b2);
                auto lo = std::max(cumn(a1), 0);
                auto hi = std::min(cumn(a2), n - 1);

                return { point, resample[lo], resample[hi], confidence_level };
            }

            double outlier_variance(Estimate&lt;double&gt; mean, Estimate&lt;double&gt; stddev, int n);

            struct bootstrap_analysis {
                Estimate&lt;double&gt; mean;
                Estimate&lt;double&gt; standard_deviation;
                double outlier_variance;
            };

            bootstrap_analysis analyse_samples(double confidence_level, int n_resamples, std::vector&lt;double&gt;::iterator first, std::vector&lt;double&gt;::iterator last);
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_stats.hpp
#include &lt;algorithm&gt;
#include &lt;iterator&gt;
#include &lt;tuple&gt;
#include &lt;vector&gt;
#include &lt;cmath&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename Clock&gt;
            std::vector&lt;double&gt; resolution(int k) {
                std::vector&lt;TimePoint&lt;Clock&gt;&gt; times;
                times.reserve(k + 1);
                std::generate_n(std::back_inserter(times), k + 1, now&lt;Clock&gt;{});

                std::vector&lt;double&gt; deltas;
                deltas.reserve(k);
                std::transform(std::next(times.begin()), times.end(), times.begin(),
                    std::back_inserter(deltas),
                    [](TimePoint&lt;Clock&gt; a, TimePoint&lt;Clock&gt; b) { return static_cast&lt;double&gt;((a - b).count()); });

                return deltas;
            }

            const auto warmup_iterations = 10000;
            const auto warmup_time = std::chrono::milliseconds(100);
            const auto minimum_ticks = 1000;
            const auto warmup_seed = 10000;
            const auto clock_resolution_estimation_time = std::chrono::milliseconds(500);
            const auto clock_cost_estimation_time_limit = std::chrono::seconds(1);
            const auto clock_cost_estimation_tick_limit = 100000;
            const auto clock_cost_estimation_time = std::chrono::milliseconds(10);
            const auto clock_cost_estimation_iterations = 10000;

            template &lt;typename Clock&gt;
            int warmup() {
                return run_for_at_least&lt;Clock&gt;(std::chrono::duration_cast&lt;ClockDuration&lt;Clock&gt;&gt;(warmup_time), warmup_seed, &amp;resolution&lt;Clock&gt;)
                    .iterations;
            }
            template &lt;typename Clock&gt;
            EnvironmentEstimate&lt;FloatDuration&lt;Clock&gt;&gt; estimate_clock_resolution(int iterations) {
                auto r = run_for_at_least&lt;Clock&gt;(std::chrono::duration_cast&lt;ClockDuration&lt;Clock&gt;&gt;(clock_resolution_estimation_time), iterations, &amp;resolution&lt;Clock&gt;)
                    .result;
                return {
                    FloatDuration&lt;Clock&gt;(mean(r.begin(), r.end())),
                    classify_outliers(r.begin(), r.end()),
                };
            }
            template &lt;typename Clock&gt;
            EnvironmentEstimate&lt;FloatDuration&lt;Clock&gt;&gt; estimate_clock_cost(FloatDuration&lt;Clock&gt; resolution) {
                auto time_limit = std::min(resolution * clock_cost_estimation_tick_limit, FloatDuration&lt;Clock&gt;(clock_cost_estimation_time_limit));
                auto time_clock = [](int k) {
                    return Detail::measure&lt;Clock&gt;([k] {
                        for (int i = 0; i &lt; k; ++i) {
                            volatile auto ignored = Clock::now();
                            (void)ignored;
                        }
                    }).elapsed;
                };
                time_clock(1);
                int iters = clock_cost_estimation_iterations;
                auto&amp;&amp; r = run_for_at_least&lt;Clock&gt;(std::chrono::duration_cast&lt;ClockDuration&lt;Clock&gt;&gt;(clock_cost_estimation_time), iters, time_clock);
                std::vector&lt;double&gt; times;
                int nsamples = static_cast&lt;int&gt;(std::ceil(time_limit / r.elapsed));
                times.reserve(nsamples);
                std::generate_n(std::back_inserter(times), nsamples, [time_clock, &amp;r] {
                    return static_cast&lt;double&gt;((time_clock(r.iterations) / r.iterations).count());
                });
                return {
                    FloatDuration&lt;Clock&gt;(mean(times.begin(), times.end())),
                    classify_outliers(times.begin(), times.end()),
                };
            }

            template &lt;typename Clock&gt;
            Environment&lt;FloatDuration&lt;Clock&gt;&gt; measure_environment() {
                static Environment&lt;FloatDuration&lt;Clock&gt;&gt;* env = nullptr;
                if (env) {
                    return *env;
                }

                auto iters = Detail::warmup&lt;Clock&gt;();
                auto resolution = Detail::estimate_clock_resolution&lt;Clock&gt;(iters);
                auto cost = Detail::estimate_clock_cost&lt;Clock&gt;(resolution.mean);

                env = new Environment&lt;FloatDuration&lt;Clock&gt;&gt;{ resolution, cost };
                return *env;
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_estimate_clock.hpp
// start catch_analyse.hpp

 // Run and analyse one benchmark


// start catch_sample_analysis.hpp

// Benchmark results


#include &lt;algorithm&gt;
#include &lt;vector&gt;
#include &lt;string&gt;
#include &lt;iterator&gt;

namespace Catch {
    namespace Benchmark {
        template &lt;typename Duration&gt;
        struct SampleAnalysis {
            std::vector&lt;Duration&gt; samples;
            Estimate&lt;Duration&gt; mean;
            Estimate&lt;Duration&gt; standard_deviation;
            OutlierClassification outliers;
            double outlier_variance;

            template &lt;typename Duration2&gt;
            operator SampleAnalysis&lt;Duration2&gt;() const {
                std::vector&lt;Duration2&gt; samples2;
                samples2.reserve(samples.size());
                std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](Duration d) { return Duration2(d); });
                return {
                    std::move(samples2),
                    mean,
                    standard_deviation,
                    outliers,
                    outlier_variance,
                };
            }
        };
    } // namespace Benchmark
} // namespace Catch

// end catch_sample_analysis.hpp
#include &lt;algorithm&gt;
#include &lt;iterator&gt;
#include &lt;vector&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename Duration, typename Iterator&gt;
            SampleAnalysis&lt;Duration&gt; analyse(const IConfig &amp;cfg, Environment&lt;Duration&gt;, Iterator first, Iterator last) {
                if (!cfg.benchmarkNoAnalysis()) {
                    std::vector&lt;double&gt; samples;
                    samples.reserve(last - first);
                    std::transform(first, last, std::back_inserter(samples), [](Duration d) { return d.count(); });

                    auto analysis = Catch::Benchmark::Detail::analyse_samples(cfg.benchmarkConfidenceInterval(), cfg.benchmarkResamples(), samples.begin(), samples.end());
                    auto outliers = Catch::Benchmark::Detail::classify_outliers(samples.begin(), samples.end());

                    auto wrap_estimate = [](Estimate&lt;double&gt; e) {
                        return Estimate&lt;Duration&gt; {
                            Duration(e.point),
                                Duration(e.lower_bound),
                                Duration(e.upper_bound),
                                e.confidence_interval,
                        };
                    };
                    std::vector&lt;Duration&gt; samples2;
                    samples2.reserve(samples.size());
                    std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](double d) { return Duration(d); });
                    return {
                        std::move(samples2),
                        wrap_estimate(analysis.mean),
                        wrap_estimate(analysis.standard_deviation),
                        outliers,
                        analysis.outlier_variance,
                    };
                } else {
                    std::vector&lt;Duration&gt; samples;
                    samples.reserve(last - first);

                    Duration mean = Duration(0);
                    int i = 0;
                    for (auto it = first; it &lt; last; ++it, ++i) {
                        samples.push_back(Duration(*it));
                        mean += Duration(*it);
                    }
                    mean /= i;

                    return {
                        std::move(samples),
                        Estimate&lt;Duration&gt;{mean, mean, mean, 0.0},
                        Estimate&lt;Duration&gt;{Duration(0), Duration(0), Duration(0), 0.0},
                        OutlierClassification{},
                        0.0
                    };
                }
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

// end catch_analyse.hpp
#include &lt;algorithm&gt;
#include &lt;functional&gt;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;cmath&gt;

namespace Catch {
    namespace Benchmark {
        struct Benchmark {
            Benchmark(std::string &amp;&amp;name)
                : name(std::move(name)) {}

            template &lt;class FUN&gt;
            Benchmark(std::string &amp;&amp;name, FUN &amp;&amp;func)
                : fun(std::move(func)), name(std::move(name)) {}

            template &lt;typename Clock&gt;
            ExecutionPlan&lt;FloatDuration&lt;Clock&gt;&gt; prepare(const IConfig &amp;cfg, Environment&lt;FloatDuration&lt;Clock&gt;&gt; env) const {
                auto min_time = env.clock_resolution.mean * Detail::minimum_ticks;
                auto run_time = std::max(min_time, std::chrono::duration_cast&lt;decltype(min_time)&gt;(cfg.benchmarkWarmupTime()));
                auto&amp;&amp; test = Detail::run_for_at_least&lt;Clock&gt;(std::chrono::duration_cast&lt;ClockDuration&lt;Clock&gt;&gt;(run_time), 1, fun);
                int new_iters = static_cast&lt;int&gt;(std::ceil(min_time * test.iterations / test.elapsed));
                return { new_iters, test.elapsed / test.iterations * new_iters * cfg.benchmarkSamples(), fun, std::chrono::duration_cast&lt;FloatDuration&lt;Clock&gt;&gt;(cfg.benchmarkWarmupTime()), Detail::warmup_iterations };
            }

            template &lt;typename Clock = default_clock&gt;
            void run() {
                IConfigPtr cfg = getCurrentContext().getConfig();

                auto env = Detail::measure_environment&lt;Clock&gt;();

                getResultCapture().benchmarkPreparing(name);
                CATCH_TRY{
                    auto plan = user_code([&amp;] {
                        return prepare&lt;Clock&gt;(*cfg, env);
                    });

                    BenchmarkInfo info {
                        name,
                        plan.estimated_duration.count(),
                        plan.iterations_per_sample,
                        cfg-&gt;benchmarkSamples(),
                        cfg-&gt;benchmarkResamples(),
                        env.clock_resolution.mean.count(),
                        env.clock_cost.mean.count()
                    };

                    getResultCapture().benchmarkStarting(info);

                    auto samples = user_code([&amp;] {
                        return plan.template run&lt;Clock&gt;(*cfg, env);
                    });

                    auto analysis = Detail::analyse(*cfg, env, samples.begin(), samples.end());
                    BenchmarkStats&lt;FloatDuration&lt;Clock&gt;&gt; stats{ info, analysis.samples, analysis.mean, analysis.standard_deviation, analysis.outliers, analysis.outlier_variance };
                    getResultCapture().benchmarkEnded(stats);

                } CATCH_CATCH_ALL{
                    if (translateActiveException() != Detail::benchmarkErrorMsg) // benchmark errors have been reported, otherwise rethrow.
                        std::rethrow_exception(std::current_exception());
                }
            }

            // sets lambda to be used in fun *and* executes benchmark!
            template &lt;typename Fun,
                typename std::enable_if&lt;!Detail::is_related&lt;Fun, Benchmark&gt;::value, int&gt;::type = 0&gt;
                Benchmark &amp; operator=(Fun func) {
                fun = Detail::BenchmarkFunction(func);
                run();
                return *this;
            }

            explicit operator bool() {
                return true;
            }

        private:
            Detail::BenchmarkFunction fun;
            std::string name;
        };
    }
} // namespace Catch

#define INTERNAL_CATCH_GET_1_ARG(arg1, arg2, ...) arg1
#define INTERNAL_CATCH_GET_2_ARG(arg1, arg2, ...) arg2

#define INTERNAL_CATCH_BENCHMARK(BenchmarkName, name, benchmarkIndex)\
    if( Catch::Benchmark::Benchmark BenchmarkName{name} ) \
        BenchmarkName = [&amp;](int benchmarkIndex)

#define INTERNAL_CATCH_BENCHMARK_ADVANCED(BenchmarkName, name)\
    if( Catch::Benchmark::Benchmark BenchmarkName{name} ) \
        BenchmarkName = [&amp;]

// end catch_benchmark.hpp
// start catch_constructor.hpp

// Constructor and destructor helpers


#include &lt;type_traits&gt;

namespace Catch {
    namespace Benchmark {
        namespace Detail {
            template &lt;typename T, bool Destruct&gt;
            struct ObjectStorage
            {
                using TStorage = typename std::aligned_storage&lt;sizeof(T), std::alignment_of&lt;T&gt;::value&gt;::type;

                ObjectStorage() : data() {}

                ObjectStorage(const ObjectStorage&amp; other)
                {
                    new(&amp;data) T(other.stored_object());
                }

                ObjectStorage(ObjectStorage&amp;&amp; other)
                {
                    new(&amp;data) T(std::move(other.stored_object()));
                }

                ~ObjectStorage() { destruct_on_exit&lt;T&gt;(); }

                template &lt;typename... Args&gt;
                void construct(Args&amp;&amp;... args)
                {
                    new (&amp;data) T(std::forward&lt;Args&gt;(args)...);
                }

                template &lt;bool AllowManualDestruction = !Destruct&gt;
                typename std::enable_if&lt;AllowManualDestruction&gt;::type destruct()
                {
                    stored_object().~T();
                }

            private:
                // If this is a constructor benchmark, destruct the underlying object
                template &lt;typename U&gt;
                void destruct_on_exit(typename std::enable_if&lt;Destruct, U&gt;::type* = 0) { destruct&lt;true&gt;(); }
                // Otherwise, don't
                template &lt;typename U&gt;
                void destruct_on_exit(typename std::enable_if&lt;!Destruct, U&gt;::type* = 0) { }

                T&amp; stored_object() {
                    return *static_cast&lt;T*&gt;(static_cast&lt;void*&gt;(&amp;data));
                }

                T const&amp; stored_object() const {
                    return *static_cast&lt;T*&gt;(static_cast&lt;void*&gt;(&amp;data));
                }

                TStorage data;
            };
        }

        template &lt;typename T&gt;
        using storage_for = Detail::ObjectStorage&lt;T, true&gt;;

        template &lt;typename T&gt;
        using destructable_object = Detail::ObjectStorage&lt;T, false&gt;;
    }
}

// end catch_constructor.hpp
// end catch_benchmarking_all.hpp
#endif

#endif // ! CATCH_CONFIG_IMPL_ONLY

#ifdef CATCH_IMPL
// start catch_impl.hpp

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// Keep these here for external reporters
// start catch_test_case_tracker.h

#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {
namespace TestCaseTracking {

    struct NameAndLocation {
        std::string name;
        SourceLineInfo location;

        NameAndLocation( std::string const&amp; _name, SourceLineInfo const&amp; _location );
        friend bool operator==(NameAndLocation const&amp; lhs, NameAndLocation const&amp; rhs) {
            return lhs.name == rhs.name
                &amp;&amp; lhs.location == rhs.location;
        }
    };

    class ITracker;

    using ITrackerPtr = std::shared_ptr&lt;ITracker&gt;;

    class  ITracker {
        NameAndLocation m_nameAndLocation;

    public:
        ITracker(NameAndLocation const&amp; nameAndLoc) :
            m_nameAndLocation(nameAndLoc)
        {}

        // static queries
        NameAndLocation const&amp; nameAndLocation() const {
            return m_nameAndLocation;
        }

        virtual ~ITracker();

        // dynamic queries
        virtual bool isComplete() const = 0; // Successfully completed or failed
        virtual bool isSuccessfullyCompleted() const = 0;
        virtual bool isOpen() const = 0; // Started but not complete
        virtual bool hasChildren() const = 0;
        virtual bool hasStarted() const = 0;

        virtual ITracker&amp; parent() = 0;

        // actions
        virtual void close() = 0; // Successfully complete
        virtual void fail() = 0;
        virtual void markAsNeedingAnotherRun() = 0;

        virtual void addChild( ITrackerPtr const&amp; child ) = 0;
        virtual ITrackerPtr findChild( NameAndLocation const&amp; nameAndLocation ) = 0;
        virtual void openChild() = 0;

        // Debug/ checking
        virtual bool isSectionTracker() const = 0;
        virtual bool isGeneratorTracker() const = 0;
    };

    class TrackerContext {

        enum RunState {
            NotStarted,
            Executing,
            CompletedCycle
        };

        ITrackerPtr m_rootTracker;
        ITracker* m_currentTracker = nullptr;
        RunState m_runState = NotStarted;

    public:

        ITracker&amp; startRun();
        void endRun();

        void startCycle();
        void completeCycle();

        bool completedCycle() const;
        ITracker&amp; currentTracker();
        void setCurrentTracker( ITracker* tracker );
    };

    class TrackerBase : public ITracker {
    protected:
        enum CycleState {
            NotStarted,
            Executing,
            ExecutingChildren,
            NeedsAnotherRun,
            CompletedSuccessfully,
            Failed
        };

        using Children = std::vector&lt;ITrackerPtr&gt;;
        TrackerContext&amp; m_ctx;
        ITracker* m_parent;
        Children m_children;
        CycleState m_runState = NotStarted;

    public:
        TrackerBase( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent );

        bool isComplete() const override;
        bool isSuccessfullyCompleted() const override;
        bool isOpen() const override;
        bool hasChildren() const override;
        bool hasStarted() const override {
            return m_runState != NotStarted;
        }

        void addChild( ITrackerPtr const&amp; child ) override;

        ITrackerPtr findChild( NameAndLocation const&amp; nameAndLocation ) override;
        ITracker&amp; parent() override;

        void openChild() override;

        bool isSectionTracker() const override;
        bool isGeneratorTracker() const override;

        void open();

        void close() override;
        void fail() override;
        void markAsNeedingAnotherRun() override;

    private:
        void moveToParent();
        void moveToThis();
    };

    class SectionTracker : public TrackerBase {
        std::vector&lt;std::string&gt; m_filters;
        std::string m_trimmed_name;
    public:
        SectionTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent );

        bool isSectionTracker() const override;

        bool isComplete() const override;

        static SectionTracker&amp; acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation );

        void tryOpen();

        void addInitialFilters( std::vector&lt;std::string&gt; const&amp; filters );
        void addNextFilters( std::vector&lt;std::string&gt; const&amp; filters );
        //! Returns filters active in this tracker
        std::vector&lt;std::string&gt; const&amp; getFilters() const;
        //! Returns whitespace-trimmed name of the tracked section
        std::string const&amp; trimmedName() const;
    };

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;

} // namespace Catch

// end catch_test_case_tracker.h

// start catch_leak_detector.h

namespace Catch {

    struct LeakDetector {
        LeakDetector();
        ~LeakDetector();
    };

}
// end catch_leak_detector.h
// Cpp files will be included in the single-header file here
// start catch_stats.cpp

// Statistical analysis tools

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)

#include &lt;cassert&gt;
#include &lt;random&gt;

#if defined(CATCH_CONFIG_USE_ASYNC)
#include &lt;future&gt;
#endif

namespace {
    double erf_inv(double x) {
        // Code accompanying the article "Approximating the erfinv function" in GPU Computing Gems, Volume 2
        double w, p;

        w = -log((1.0 - x) * (1.0 + x));

        if (w &lt; 6.250000) {
            w = w - 3.125000;
            p = -3.6444120640178196996e-21;
            p = -1.685059138182016589e-19 + p * w;
            p = 1.2858480715256400167e-18 + p * w;
            p = 1.115787767802518096e-17 + p * w;
            p = -1.333171662854620906e-16 + p * w;
            p = 2.0972767875968561637e-17 + p * w;
            p = 6.6376381343583238325e-15 + p * w;
            p = -4.0545662729752068639e-14 + p * w;
            p = -8.1519341976054721522e-14 + p * w;
            p = 2.6335093153082322977e-12 + p * w;
            p = -1.2975133253453532498e-11 + p * w;
            p = -5.4154120542946279317e-11 + p * w;
            p = 1.051212273321532285e-09 + p * w;
            p = -4.1126339803469836976e-09 + p * w;
            p = -2.9070369957882005086e-08 + p * w;
            p = 4.2347877827932403518e-07 + p * w;
            p = -1.3654692000834678645e-06 + p * w;
            p = -1.3882523362786468719e-05 + p * w;
            p = 0.0001867342080340571352 + p * w;
            p = -0.00074070253416626697512 + p * w;
            p = -0.0060336708714301490533 + p * w;
            p = 0.24015818242558961693 + p * w;
            p = 1.6536545626831027356 + p * w;
        } else if (w &lt; 16.000000) {
            w = sqrt(w) - 3.250000;
            p = 2.2137376921775787049e-09;
            p = 9.0756561938885390979e-08 + p * w;
            p = -2.7517406297064545428e-07 + p * w;
            p = 1.8239629214389227755e-08 + p * w;
            p = 1.5027403968909827627e-06 + p * w;
            p = -4.013867526981545969e-06 + p * w;
            p = 2.9234449089955446044e-06 + p * w;
            p = 1.2475304481671778723e-05 + p * w;
            p = -4.7318229009055733981e-05 + p * w;
            p = 6.8284851459573175448e-05 + p * w;
            p = 2.4031110387097893999e-05 + p * w;
            p = -0.0003550375203628474796 + p * w;
            p = 0.00095328937973738049703 + p * w;
            p = -0.0016882755560235047313 + p * w;
            p = 0.0024914420961078508066 + p * w;
            p = -0.0037512085075692412107 + p * w;
            p = 0.005370914553590063617 + p * w;
            p = 1.0052589676941592334 + p * w;
            p = 3.0838856104922207635 + p * w;
        } else {
            w = sqrt(w) - 5.000000;
            p = -2.7109920616438573243e-11;
            p = -2.5556418169965252055e-10 + p * w;
            p = 1.5076572693500548083e-09 + p * w;
            p = -3.7894654401267369937e-09 + p * w;
            p = 7.6157012080783393804e-09 + p * w;
            p = -1.4960026627149240478e-08 + p * w;
            p = 2.9147953450901080826e-08 + p * w;
            p = -6.7711997758452339498e-08 + p * w;
            p = 2.2900482228026654717e-07 + p * w;
            p = -9.9298272942317002539e-07 + p * w;
            p = 4.5260625972231537039e-06 + p * w;
            p = -1.9681778105531670567e-05 + p * w;
            p = 7.5995277030017761139e-05 + p * w;
            p = -0.00021503011930044477347 + p * w;
            p = -0.00013871931833623122026 + p * w;
            p = 1.0103004648645343977 + p * w;
            p = 4.8499064014085844221 + p * w;
        }
        return p * x;
    }

    double standard_deviation(std::vector&lt;double&gt;::iterator first, std::vector&lt;double&gt;::iterator last) {
        auto m = Catch::Benchmark::Detail::mean(first, last);
        double variance = std::accumulate(first, last, 0., [m](double a, double b) {
            double diff = b - m;
            return a + diff * diff;
            }) / (last - first);
            return std::sqrt(variance);
    }

}

namespace Catch {
    namespace Benchmark {
        namespace Detail {

            double weighted_average_quantile(int k, int q, std::vector&lt;double&gt;::iterator first, std::vector&lt;double&gt;::iterator last) {
                auto count = last - first;
                double idx = (count - 1) * k / static_cast&lt;double&gt;(q);
                int j = static_cast&lt;int&gt;(idx);
                double g = idx - j;
                std::nth_element(first, first + j, last);
                auto xj = first[j];
                if (g == 0) return xj;

                auto xj1 = *std::min_element(first + (j + 1), last);
                return xj + g * (xj1 - xj);
            }

            double erfc_inv(double x) {
                return erf_inv(1.0 - x);
            }

            double normal_quantile(double p) {
                static const double ROOT_TWO = std::sqrt(2.0);

                double result = 0.0;
                assert(p &gt;= 0 &amp;&amp; p &lt;= 1);
                if (p &lt; 0 || p &gt; 1) {
                    return result;
                }

                result = -erfc_inv(2.0 * p);
                // result *= normal distribution standard deviation (1.0) * sqrt(2)
                result *= /*sd * */ ROOT_TWO;
                // result += normal disttribution mean (0)
                return result;
            }

            double outlier_variance(Estimate&lt;double&gt; mean, Estimate&lt;double&gt; stddev, int n) {
                double sb = stddev.point;
                double mn = mean.point / n;
                double mg_min = mn / 2.;
                double sg = std::min(mg_min / 4., sb / std::sqrt(n));
                double sg2 = sg * sg;
                double sb2 = sb * sb;

                auto c_max = [n, mn, sb2, sg2](double x) -&gt; double {
                    double k = mn - x;
                    double d = k * k;
                    double nd = n * d;
                    double k0 = -n * nd;
                    double k1 = sb2 - n * sg2 + nd;
                    double det = k1 * k1 - 4 * sg2 * k0;
                    return (int)(-2. * k0 / (k1 + std::sqrt(det)));
                };

                auto var_out = [n, sb2, sg2](double c) {
                    double nc = n - c;
                    return (nc / n) * (sb2 - nc * sg2);
                };

                return std::min(var_out(1), var_out(std::min(c_max(0.), c_max(mg_min)))) / sb2;
            }

            bootstrap_analysis analyse_samples(double confidence_level, int n_resamples, std::vector&lt;double&gt;::iterator first, std::vector&lt;double&gt;::iterator last) {
                CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
                CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
                static std::random_device entropy;
                CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION

                auto n = static_cast&lt;int&gt;(last - first); // seriously, one can't use integral types without hell in C++

                auto mean = &amp;Detail::mean&lt;std::vector&lt;double&gt;::iterator&gt;;
                auto stddev = &amp;standard_deviation;

#if defined(CATCH_CONFIG_USE_ASYNC)
                auto Estimate = [=](double(*f)(std::vector&lt;double&gt;::iterator, std::vector&lt;double&gt;::iterator)) {
                    auto seed = entropy();
                    return std::async(std::launch::async, [=] {
                        std::mt19937 rng(seed);
                        auto resampled = resample(rng, n_resamples, first, last, f);
                        return bootstrap(confidence_level, first, last, resampled, f);
                    });
                };

                auto mean_future = Estimate(mean);
                auto stddev_future = Estimate(stddev);

                auto mean_estimate = mean_future.get();
                auto stddev_estimate = stddev_future.get();
#else
                auto Estimate = [=](double(*f)(std::vector&lt;double&gt;::iterator, std::vector&lt;double&gt;::iterator)) {
                    auto seed = entropy();
                    std::mt19937 rng(seed);
                    auto resampled = resample(rng, n_resamples, first, last, f);
                    return bootstrap(confidence_level, first, last, resampled, f);
                };

                auto mean_estimate = Estimate(mean);
                auto stddev_estimate = Estimate(stddev);
#endif // CATCH_USE_ASYNC

                double outlier_variance = Detail::outlier_variance(mean_estimate, stddev_estimate, n);

                return { mean_estimate, stddev_estimate, outlier_variance };
            }
        } // namespace Detail
    } // namespace Benchmark
} // namespace Catch

#endif // CATCH_CONFIG_ENABLE_BENCHMARKING
// end catch_stats.cpp
// start catch_approx.cpp

#include &lt;cmath&gt;
#include &lt;limits&gt;

namespace {

// Performs equivalent check of std::fabs(lhs - rhs) &lt;= margin
// But without the subtraction to allow for INFINITY in comparison
bool marginComparison(double lhs, double rhs, double margin) {
    return (lhs + margin &gt;= rhs) &amp;&amp; (rhs + margin &gt;= lhs);
}

}

namespace Catch {
namespace Detail {

    Approx::Approx ( double value )
    :   m_epsilon( std::numeric_limits&lt;float&gt;::epsilon()*100 ),
        m_margin( 0.0 ),
        m_scale( 0.0 ),
        m_value( value )
    {}

    Approx Approx::custom() {
        return Approx( 0 );
    }

    Approx Approx::operator-() const {
        auto temp(*this);
        temp.m_value = -temp.m_value;
        return temp;
    }

    std::string Approx::toString() const {
        ReusableStringStream rss;
        rss &lt;&lt; "Approx( " &lt;&lt; ::Catch::Detail::stringify( m_value ) &lt;&lt; " )";
        return rss.str();
    }

    bool Approx::equalityComparisonImpl(const double other) const {
        // First try with fixed margin, then compute margin based on epsilon, scale and Approx's value
        // Thanks to Richard Harris for his help refining the scaled margin value
        return marginComparison(m_value, other, m_margin)
            || marginComparison(m_value, other, m_epsilon * (m_scale + std::fabs(std::isinf(m_value)? 0 : m_value)));
    }

    void Approx::setMargin(double newMargin) {
        CATCH_ENFORCE(newMargin &gt;= 0,
            "Invalid Approx::margin: " &lt;&lt; newMargin &lt;&lt; '.'
            &lt;&lt; " Approx::Margin has to be non-negative.");
        m_margin = newMargin;
    }

    void Approx::setEpsilon(double newEpsilon) {
        CATCH_ENFORCE(newEpsilon &gt;= 0 &amp;&amp; newEpsilon &lt;= 1.0,
            "Invalid Approx::epsilon: " &lt;&lt; newEpsilon &lt;&lt; '.'
            &lt;&lt; " Approx::epsilon has to be in [0, 1]");
        m_epsilon = newEpsilon;
    }

} // end namespace Detail

namespace literals {
    Detail::Approx operator "" _a(long double val) {
        return Detail::Approx(val);
    }
    Detail::Approx operator "" _a(unsigned long long val) {
        return Detail::Approx(val);
    }
} // end namespace literals

std::string StringMaker&lt;Catch::Detail::Approx&gt;::convert(Catch::Detail::Approx const&amp; value) {
    return value.toString();
}

} // end namespace Catch
// end catch_approx.cpp
// start catch_assertionhandler.cpp

// start catch_debugger.h

namespace Catch {
    bool isDebuggerActive();
}

#ifdef CATCH_PLATFORM_MAC

    #if defined(__i386__) || defined(__x86_64__)
        #define CATCH_TRAP() __asm__("int $3\n" : : ) /* NOLINT */
    #elif defined(__aarch64__)
        #define CATCH_TRAP()  __asm__(".inst 0xd4200000")
    #endif

#elif defined(CATCH_PLATFORM_IPHONE)

    // use inline assembler
    #if defined(__i386__) || defined(__x86_64__)
        #define CATCH_TRAP()  __asm__("int $3")
    #elif defined(__aarch64__)
        #define CATCH_TRAP()  __asm__(".inst 0xd4200000")
    #elif defined(__arm__) &amp;&amp; !defined(__thumb__)
        #define CATCH_TRAP()  __asm__(".inst 0xe7f001f0")
    #elif defined(__arm__) &amp;&amp;  defined(__thumb__)
        #define CATCH_TRAP()  __asm__(".inst 0xde01")
    #endif

#elif defined(CATCH_PLATFORM_LINUX)
    // If we can use inline assembler, do it because this allows us to break
    // directly at the location of the failing check instead of breaking inside
    // raise() called from it, i.e. one stack frame below.
    #if defined(__GNUC__) &amp;&amp; (defined(__i386) || defined(__x86_64))
        #define CATCH_TRAP() asm volatile ("int $3") /* NOLINT */
    #else // Fall back to the generic way.
        #include &lt;signal.h&gt;

        #define CATCH_TRAP() raise(SIGTRAP)
    #endif
#elif defined(_MSC_VER)
    #define CATCH_TRAP() __debugbreak()
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) void __stdcall DebugBreak();
    #define CATCH_TRAP() DebugBreak()
#endif

#ifndef CATCH_BREAK_INTO_DEBUGGER
    #ifdef CATCH_TRAP
        #define CATCH_BREAK_INTO_DEBUGGER() []{ if( Catch::isDebuggerActive() ) { CATCH_TRAP(); } }()
    #else
        #define CATCH_BREAK_INTO_DEBUGGER() []{}()
    #endif
#endif

// end catch_debugger.h
// start catch_run_context.h

// start catch_fatal_condition.h

// start catch_windows_h_proxy.h


#if defined(CATCH_PLATFORM_WINDOWS)

#if !defined(NOMINMAX) &amp;&amp; !defined(CATCH_CONFIG_NO_NOMINMAX)
#  define CATCH_DEFINED_NOMINMAX
#  define NOMINMAX
#endif
#if !defined(WIN32_LEAN_AND_MEAN) &amp;&amp; !defined(CATCH_CONFIG_NO_WIN32_LEAN_AND_MEAN)
#  define CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif

#ifdef __AFXDLL
#include &lt;AfxWin.h&gt;
#else
#include &lt;windows.h&gt;
#endif

#ifdef CATCH_DEFINED_NOMINMAX
#  undef NOMINMAX
#endif
#ifdef CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#  undef WIN32_LEAN_AND_MEAN
#endif

#endif // defined(CATCH_PLATFORM_WINDOWS)

// end catch_windows_h_proxy.h
#if defined( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {

    struct FatalConditionHandler {

        static LONG CALLBACK handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo);
        FatalConditionHandler();
        static void reset();
        ~FatalConditionHandler();

    private:
        static bool isSet;
        static ULONG guaranteeSize;
        static PVOID exceptionHandlerHandle;
    };

} // namespace Catch

#elif defined ( CATCH_CONFIG_POSIX_SIGNALS )

#include &lt;signal.h&gt;

namespace Catch {

    struct FatalConditionHandler {

        static bool isSet;
        static struct sigaction oldSigActions[];
        static stack_t oldSigStack;
        static char altStackMem[];

        static void handleSignal( int sig );

        FatalConditionHandler();
        ~FatalConditionHandler();
        static void reset();
    };

} // namespace Catch

#else

namespace Catch {
    struct FatalConditionHandler {
        void reset();
    };
}

#endif

// end catch_fatal_condition.h
#include &lt;string&gt;

namespace Catch {

    struct IMutableContext;

    ///////////////////////////////////////////////////////////////////////////

    class RunContext : public IResultCapture, public IRunner {

    public:
        RunContext( RunContext const&amp; ) = delete;
        RunContext&amp; operator =( RunContext const&amp; ) = delete;

        explicit RunContext( IConfigPtr const&amp; _config, IStreamingReporterPtr&amp;&amp; reporter );

        ~RunContext() override;

        void testGroupStarting( std::string const&amp; testSpec, std::size_t groupIndex, std::size_t groupsCount );
        void testGroupEnded( std::string const&amp; testSpec, Totals const&amp; totals, std::size_t groupIndex, std::size_t groupsCount );

        Totals runTest(TestCase const&amp; testCase);

        IConfigPtr config() const;
        IStreamingReporter&amp; reporter() const;

    public: // IResultCapture

        // Assertion handlers
        void handleExpr
                (   AssertionInfo const&amp; info,
                    ITransientExpression const&amp; expr,
                    AssertionReaction&amp; reaction ) override;
        void handleMessage
                (   AssertionInfo const&amp; info,
                    ResultWas::OfType resultType,
                    StringRef const&amp; message,
                    AssertionReaction&amp; reaction ) override;
        void handleUnexpectedExceptionNotThrown
                (   AssertionInfo const&amp; info,
                    AssertionReaction&amp; reaction ) override;
        void handleUnexpectedInflightException
                (   AssertionInfo const&amp; info,
                    std::string const&amp; message,
                    AssertionReaction&amp; reaction ) override;
        void handleIncomplete
                (   AssertionInfo const&amp; info ) override;
        void handleNonExpr
                (   AssertionInfo const &amp;info,
                    ResultWas::OfType resultType,
                    AssertionReaction &amp;reaction ) override;

        bool sectionStarted( SectionInfo const&amp; sectionInfo, Counts&amp; assertions ) override;

        void sectionEnded( SectionEndInfo const&amp; endInfo ) override;
        void sectionEndedEarly( SectionEndInfo const&amp; endInfo ) override;

        auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const&amp; lineInfo ) -&gt; IGeneratorTracker&amp; override;

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        void benchmarkPreparing( std::string const&amp; name ) override;
        void benchmarkStarting( BenchmarkInfo const&amp; info ) override;
        void benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; stats ) override;
        void benchmarkFailed( std::string const&amp; error ) override;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        void pushScopedMessage( MessageInfo const&amp; message ) override;
        void popScopedMessage( MessageInfo const&amp; message ) override;

        void emplaceUnscopedMessage( MessageBuilder const&amp; builder ) override;

        std::string getCurrentTestName() const override;

        const AssertionResult* getLastResult() const override;

        void exceptionEarlyReported() override;

        void handleFatalErrorCondition( StringRef message ) override;

        bool lastAssertionPassed() override;

        void assertionPassed() override;

    public:
        // !TBD We need to do this another way!
        bool aborting() const final;

    private:

        void runCurrentTest( std::string&amp; redirectedCout, std::string&amp; redirectedCerr );
        void invokeActiveTestCase();

        void resetAssertionInfo();
        bool testForMissingAssertions( Counts&amp; assertions );

        void assertionEnded( AssertionResult const&amp; result );
        void reportExpr
                (   AssertionInfo const &amp;info,
                    ResultWas::OfType resultType,
                    ITransientExpression const *expr,
                    bool negated );

        void populateReaction( AssertionReaction&amp; reaction );

    private:

        void handleUnfinishedSections();

        TestRunInfo m_runInfo;
        IMutableContext&amp; m_context;
        TestCase const* m_activeTestCase = nullptr;
        ITracker* m_testCaseTracker = nullptr;
        Option&lt;AssertionResult&gt; m_lastResult;

        IConfigPtr m_config;
        Totals m_totals;
        IStreamingReporterPtr m_reporter;
        std::vector&lt;MessageInfo&gt; m_messages;
        std::vector&lt;ScopedMessage&gt; m_messageScopes; /* Keeps owners of so-called unscoped messages. */
        AssertionInfo m_lastAssertionInfo;
        std::vector&lt;SectionEndInfo&gt; m_unfinishedSections;
        std::vector&lt;ITracker*&gt; m_activeSections;
        TrackerContext m_trackerContext;
        bool m_lastAssertionPassed = false;
        bool m_shouldReportUnexpected = true;
        bool m_includeSuccessfulResults;
    };

    void seedRng(IConfig const&amp; config);
    unsigned int rngSeed();
} // end namespace Catch

// end catch_run_context.h
namespace Catch {

    namespace {
        auto operator &lt;&lt;( std::ostream&amp; os, ITransientExpression const&amp; expr ) -&gt; std::ostream&amp; {
            expr.streamReconstructedExpression( os );
            return os;
        }
    }

    LazyExpression::LazyExpression( bool isNegated )
    :   m_isNegated( isNegated )
    {}

    LazyExpression::LazyExpression( LazyExpression const&amp; other ) : m_isNegated( other.m_isNegated ) {}

    LazyExpression::operator bool() const {
        return m_transientExpression != nullptr;
    }

    auto operator &lt;&lt; ( std::ostream&amp; os, LazyExpression const&amp; lazyExpr ) -&gt; std::ostream&amp; {
        if( lazyExpr.m_isNegated )
            os &lt;&lt; "!";

        if( lazyExpr ) {
            if( lazyExpr.m_isNegated &amp;&amp; lazyExpr.m_transientExpression-&gt;isBinaryExpression() )
                os &lt;&lt; "(" &lt;&lt; *lazyExpr.m_transientExpression &lt;&lt; ")";
            else
                os &lt;&lt; *lazyExpr.m_transientExpression;
        }
        else {
            os &lt;&lt; "{** error - unchecked empty expression requested **}";
        }
        return os;
    }

    AssertionHandler::AssertionHandler
        (   StringRef const&amp; macroName,
            SourceLineInfo const&amp; lineInfo,
            StringRef capturedExpression,
            ResultDisposition::Flags resultDisposition )
    :   m_assertionInfo{ macroName, lineInfo, capturedExpression, resultDisposition },
        m_resultCapture( getResultCapture() )
    {}

    void AssertionHandler::handleExpr( ITransientExpression const&amp; expr ) {
        m_resultCapture.handleExpr( m_assertionInfo, expr, m_reaction );
    }
    void AssertionHandler::handleMessage(ResultWas::OfType resultType, StringRef const&amp; message) {
        m_resultCapture.handleMessage( m_assertionInfo, resultType, message, m_reaction );
    }

    auto AssertionHandler::allowThrows() const -&gt; bool {
        return getCurrentContext().getConfig()-&gt;allowThrows();
    }

    void AssertionHandler::complete() {
        setCompleted();
        if( m_reaction.shouldDebugBreak ) {

            // If you find your debugger stopping you here then go one level up on the
            // call-stack for the code that caused it (typically a failed assertion)

            // (To go back to the test and change execution, jump over the throw, next)
            CATCH_BREAK_INTO_DEBUGGER();
        }
        if (m_reaction.shouldThrow) {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
            throw Catch::TestFailureException();
#else
            CATCH_ERROR( "Test failure requires aborting test!" );
#endif
        }
    }
    void AssertionHandler::setCompleted() {
        m_completed = true;
    }

    void AssertionHandler::handleUnexpectedInflightException() {
        m_resultCapture.handleUnexpectedInflightException( m_assertionInfo, Catch::translateActiveException(), m_reaction );
    }

    void AssertionHandler::handleExceptionThrownAsExpected() {
        m_resultCapture.handleNonExpr(m_assertionInfo, ResultWas::Ok, m_reaction);
    }
    void AssertionHandler::handleExceptionNotThrownAsExpected() {
        m_resultCapture.handleNonExpr(m_assertionInfo, ResultWas::Ok, m_reaction);
    }

    void AssertionHandler::handleUnexpectedExceptionNotThrown() {
        m_resultCapture.handleUnexpectedExceptionNotThrown( m_assertionInfo, m_reaction );
    }

    void AssertionHandler::handleThrowingCallSkipped() {
        m_resultCapture.handleNonExpr(m_assertionInfo, ResultWas::Ok, m_reaction);
    }

    // This is the overload that takes a string and infers the Equals matcher from it
    // The more general overload, that takes any string matcher, is in catch_capture_matchers.cpp
    void handleExceptionMatchExpr( AssertionHandler&amp; handler, std::string const&amp; str, StringRef const&amp; matcherString  ) {
        handleExceptionMatchExpr( handler, Matchers::Equals( str ), matcherString );
    }

} // namespace Catch
// end catch_assertionhandler.cpp
// start catch_assertionresult.cpp

namespace Catch {
    AssertionResultData::AssertionResultData(ResultWas::OfType _resultType, LazyExpression const &amp; _lazyExpression):
        lazyExpression(_lazyExpression),
        resultType(_resultType) {}

    std::string AssertionResultData::reconstructExpression() const {

        if( reconstructedExpression.empty() ) {
            if( lazyExpression ) {
                ReusableStringStream rss;
                rss &lt;&lt; lazyExpression;
                reconstructedExpression = rss.str();
            }
        }
        return reconstructedExpression;
    }

    AssertionResult::AssertionResult( AssertionInfo const&amp; info, AssertionResultData const&amp; data )
    :   m_info( info ),
        m_resultData( data )
    {}

    // Result was a success
    bool AssertionResult::succeeded() const {
        return Catch::isOk( m_resultData.resultType );
    }

    // Result was a success, or failure is suppressed
    bool AssertionResult::isOk() const {
        return Catch::isOk( m_resultData.resultType ) || shouldSuppressFailure( m_info.resultDisposition );
    }

    ResultWas::OfType AssertionResult::getResultType() const {
        return m_resultData.resultType;
    }

    bool AssertionResult::hasExpression() const {
        return !m_info.capturedExpression.empty();
    }

    bool AssertionResult::hasMessage() const {
        return !m_resultData.message.empty();
    }

    std::string AssertionResult::getExpression() const {
        // Possibly overallocating by 3 characters should be basically free
        std::string expr; expr.reserve(m_info.capturedExpression.size() + 3);
        if (isFalseTest(m_info.resultDisposition)) {
            expr += "!(";
        }
        expr += m_info.capturedExpression;
        if (isFalseTest(m_info.resultDisposition)) {
            expr += ')';
        }
        return expr;
    }

    std::string AssertionResult::getExpressionInMacro() const {
        std::string expr;
        if( m_info.macroName.empty() )
            expr = static_cast&lt;std::string&gt;(m_info.capturedExpression);
        else {
            expr.reserve( m_info.macroName.size() + m_info.capturedExpression.size() + 4 );
            expr += m_info.macroName;
            expr += "( ";
            expr += m_info.capturedExpression;
            expr += " )";
        }
        return expr;
    }

    bool AssertionResult::hasExpandedExpression() const {
        return hasExpression() &amp;&amp; getExpandedExpression() != getExpression();
    }

    std::string AssertionResult::getExpandedExpression() const {
        std::string expr = m_resultData.reconstructExpression();
        return expr.empty()
                ? getExpression()
                : expr;
    }

    std::string AssertionResult::getMessage() const {
        return m_resultData.message;
    }
    SourceLineInfo AssertionResult::getSourceInfo() const {
        return m_info.lineInfo;
    }

    StringRef AssertionResult::getTestMacroName() const {
        return m_info.macroName;
    }

} // end namespace Catch
// end catch_assertionresult.cpp
// start catch_capture_matchers.cpp

namespace Catch {

    using StringMatcher = Matchers::Impl::MatcherBase&lt;std::string&gt;;

    // This is the general overload that takes a any string matcher
    // There is another overload, in catch_assertionhandler.h/.cpp, that only takes a string and infers
    // the Equals matcher (so the header does not mention matchers)
    void handleExceptionMatchExpr( AssertionHandler&amp; handler, StringMatcher const&amp; matcher, StringRef const&amp; matcherString  ) {
        std::string exceptionMessage = Catch::translateActiveException();
        MatchExpr&lt;std::string, StringMatcher const&amp;&gt; expr( exceptionMessage, matcher, matcherString );
        handler.handleExpr( expr );
    }

} // namespace Catch
// end catch_capture_matchers.cpp
// start catch_commandline.cpp

// start catch_commandline.h

// start catch_clara.h

// Use Catch's value for console width (store Clara's off to the side, if present)
#ifdef CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#undef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#endif
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_CONFIG_CONSOLE_WIDTH-1

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wshadow"
#endif

// start clara.hpp
// Copyright 2017 Two Blue Cubes Ltd. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See https://github.com/philsquared/Clara for more details

// Clara v1.1.5


#ifndef CATCH_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_CONFIG_CONSOLE_WIDTH 80
#endif

#ifndef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_CLARA_CONFIG_CONSOLE_WIDTH
#endif

#ifndef CLARA_CONFIG_OPTIONAL_TYPE
#ifdef __has_include
#if __has_include(&lt;optional&gt;) &amp;&amp; __cplusplus &gt;= 201703L
#include &lt;optional&gt;
#define CLARA_CONFIG_OPTIONAL_TYPE std::optional
#endif
#endif
#endif

// ----------- #included from clara_textflow.hpp -----------

// TextFlowCpp
//
// A single-header library for wrapping and laying out basic text, by Phil Nash
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This project is hosted at https://github.com/philsquared/textflowcpp


#include &lt;cassert&gt;
#include &lt;ostream&gt;
#include &lt;sstream&gt;
#include &lt;vector&gt;

#ifndef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch {
namespace clara {
namespace TextFlow {

inline auto isWhitespace(char c) -&gt; bool {
	static std::string chars = " \t\n\r";
	return chars.find(c) != std::string::npos;
}
inline auto isBreakableBefore(char c) -&gt; bool {
	static std::string chars = "[({&lt;|";
	return chars.find(c) != std::string::npos;
}
inline auto isBreakableAfter(char c) -&gt; bool {
	static std::string chars = "])}&gt;.,:;*+-=&amp;/\\";
	return chars.find(c) != std::string::npos;
}

class Columns;

class Column {
	std::vector&lt;std::string&gt; m_strings;
	size_t m_width = CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH;
	size_t m_indent = 0;
	size_t m_initialIndent = std::string::npos;

public:
	class iterator {
		friend Column;

		Column const&amp; m_column;
		size_t m_stringIndex = 0;
		size_t m_pos = 0;

		size_t m_len = 0;
		size_t m_end = 0;
		bool m_suffix = false;

		iterator(Column const&amp; column, size_t stringIndex)
			: m_column(column),
			m_stringIndex(stringIndex) {}

		auto line() const -&gt; std::string const&amp; { return m_column.m_strings[m_stringIndex]; }

		auto isBoundary(size_t at) const -&gt; bool {
			assert(at &gt; 0);
			assert(at &lt;= line().size());

			return at == line().size() ||
				(isWhitespace(line()[at]) &amp;&amp; !isWhitespace(line()[at - 1])) ||
				isBreakableBefore(line()[at]) ||
				isBreakableAfter(line()[at - 1]);
		}

		void calcLength() {
			assert(m_stringIndex &lt; m_column.m_strings.size());

			m_suffix = false;
			auto width = m_column.m_width - indent();
			m_end = m_pos;
			if (line()[m_pos] == '\n') {
				++m_end;
			}
			while (m_end &lt; line().size() &amp;&amp; line()[m_end] != '\n')
				++m_end;

			if (m_end &lt; m_pos + width) {
				m_len = m_end - m_pos;
			} else {
				size_t len = width;
				while (len &gt; 0 &amp;&amp; !isBoundary(m_pos + len))
					--len;
				while (len &gt; 0 &amp;&amp; isWhitespace(line()[m_pos + len - 1]))
					--len;

				if (len &gt; 0) {
					m_len = len;
				} else {
					m_suffix = true;
					m_len = width - 1;
				}
			}
		}

		auto indent() const -&gt; size_t {
			auto initial = m_pos == 0 &amp;&amp; m_stringIndex == 0 ? m_column.m_initialIndent : std::string::npos;
			return initial == std::string::npos ? m_column.m_indent : initial;
		}

		auto addIndentAndSuffix(std::string const &amp;plain) const -&gt; std::string {
			return std::string(indent(), ' ') + (m_suffix ? plain + "-" : plain);
		}

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = value_type * ;
		using reference = value_type &amp; ;
		using iterator_category = std::forward_iterator_tag;

		explicit iterator(Column const&amp; column) : m_column(column) {
			assert(m_column.m_width &gt; m_column.m_indent);
			assert(m_column.m_initialIndent == std::string::npos || m_column.m_width &gt; m_column.m_initialIndent);
			calcLength();
			if (m_len == 0)
				m_stringIndex++; // Empty string
		}

		auto operator *() const -&gt; std::string {
			assert(m_stringIndex &lt; m_column.m_strings.size());
			assert(m_pos &lt;= m_end);
			return addIndentAndSuffix(line().substr(m_pos, m_len));
		}

		auto operator ++() -&gt; iterator&amp; {
			m_pos += m_len;
			if (m_pos &lt; line().size() &amp;&amp; line()[m_pos] == '\n')
				m_pos += 1;
			else
				while (m_pos &lt; line().size() &amp;&amp; isWhitespace(line()[m_pos]))
					++m_pos;

			if (m_pos == line().size()) {
				m_pos = 0;
				++m_stringIndex;
			}
			if (m_stringIndex &lt; m_column.m_strings.size())
				calcLength();
			return *this;
		}
		auto operator ++(int) -&gt; iterator {
			iterator prev(*this);
			operator++();
			return prev;
		}

		auto operator ==(iterator const&amp; other) const -&gt; bool {
			return
				m_pos == other.m_pos &amp;&amp;
				m_stringIndex == other.m_stringIndex &amp;&amp;
				&amp;m_column == &amp;other.m_column;
		}
		auto operator !=(iterator const&amp; other) const -&gt; bool {
			return !operator==(other);
		}
	};
	using const_iterator = iterator;

	explicit Column(std::string const&amp; text) { m_strings.push_back(text); }

	auto width(size_t newWidth) -&gt; Column&amp; {
		assert(newWidth &gt; 0);
		m_width = newWidth;
		return *this;
	}
	auto indent(size_t newIndent) -&gt; Column&amp; {
		m_indent = newIndent;
		return *this;
	}
	auto initialIndent(size_t newIndent) -&gt; Column&amp; {
		m_initialIndent = newIndent;
		return *this;
	}

	auto width() const -&gt; size_t { return m_width; }
	auto begin() const -&gt; iterator { return iterator(*this); }
	auto end() const -&gt; iterator { return { *this, m_strings.size() }; }

	inline friend std::ostream&amp; operator &lt;&lt; (std::ostream&amp; os, Column const&amp; col) {
		bool first = true;
		for (auto line : col) {
			if (first)
				first = false;
			else
				os &lt;&lt; "\n";
			os &lt;&lt; line;
		}
		return os;
	}

	auto operator + (Column const&amp; other)-&gt;Columns;

	auto toString() const -&gt; std::string {
		std::ostringstream oss;
		oss &lt;&lt; *this;
		return oss.str();
	}
};

class Spacer : public Column {

public:
	explicit Spacer(size_t spaceWidth) : Column("") {
		width(spaceWidth);
	}
};

class Columns {
	std::vector&lt;Column&gt; m_columns;

public:

	class iterator {
		friend Columns;
		struct EndTag {};

		std::vector&lt;Column&gt; const&amp; m_columns;
		std::vector&lt;Column::iterator&gt; m_iterators;
		size_t m_activeIterators;

		iterator(Columns const&amp; columns, EndTag)
			: m_columns(columns.m_columns),
			m_activeIterators(0) {
			m_iterators.reserve(m_columns.size());

			for (auto const&amp; col : m_columns)
				m_iterators.push_back(col.end());
		}

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = std::string;
		using pointer = value_type * ;
		using reference = value_type &amp; ;
		using iterator_category = std::forward_iterator_tag;

		explicit iterator(Columns const&amp; columns)
			: m_columns(columns.m_columns),
			m_activeIterators(m_columns.size()) {
			m_iterators.reserve(m_columns.size());

			for (auto const&amp; col : m_columns)
				m_iterators.push_back(col.begin());
		}

		auto operator ==(iterator const&amp; other) const -&gt; bool {
			return m_iterators == other.m_iterators;
		}
		auto operator !=(iterator const&amp; other) const -&gt; bool {
			return m_iterators != other.m_iterators;
		}
		auto operator *() const -&gt; std::string {
			std::string row, padding;

			for (size_t i = 0; i &lt; m_columns.size(); ++i) {
				auto width = m_columns[i].width();
				if (m_iterators[i] != m_columns[i].end()) {
					std::string col = *m_iterators[i];
					row += padding + col;
					if (col.size() &lt; width)
						padding = std::string(width - col.size(), ' ');
					else
						padding = "";
				} else {
					padding += std::string(width, ' ');
				}
			}
			return row;
		}
		auto operator ++() -&gt; iterator&amp; {
			for (size_t i = 0; i &lt; m_columns.size(); ++i) {
				if (m_iterators[i] != m_columns[i].end())
					++m_iterators[i];
			}
			return *this;
		}
		auto operator ++(int) -&gt; iterator {
			iterator prev(*this);
			operator++();
			return prev;
		}
	};
	using const_iterator = iterator;

	auto begin() const -&gt; iterator { return iterator(*this); }
	auto end() const -&gt; iterator { return { *this, iterator::EndTag() }; }

	auto operator += (Column const&amp; col) -&gt; Columns&amp; {
		m_columns.push_back(col);
		return *this;
	}
	auto operator + (Column const&amp; col) -&gt; Columns {
		Columns combined = *this;
		combined += col;
		return combined;
	}

	inline friend std::ostream&amp; operator &lt;&lt; (std::ostream&amp; os, Columns const&amp; cols) {

		bool first = true;
		for (auto line : cols) {
			if (first)
				first = false;
			else
				os &lt;&lt; "\n";
			os &lt;&lt; line;
		}
		return os;
	}

	auto toString() const -&gt; std::string {
		std::ostringstream oss;
		oss &lt;&lt; *this;
		return oss.str();
	}
};

inline auto Column::operator + (Column const&amp; other) -&gt; Columns {
	Columns cols;
	cols += *this;
	cols += other;
	return cols;
}
}

}
}

// ----------- end of #include from clara_textflow.hpp -----------
// ........... back in clara.hpp

#include &lt;cctype&gt;
#include &lt;string&gt;
#include &lt;memory&gt;
#include &lt;set&gt;
#include &lt;algorithm&gt;

#if !defined(CATCH_PLATFORM_WINDOWS) &amp;&amp; ( defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) )
#define CATCH_PLATFORM_WINDOWS
#endif

namespace Catch { namespace clara {
namespace detail {

    // Traits for extracting arg and return type of lambdas (for single argument lambdas)
    template&lt;typename L&gt;
    struct UnaryLambdaTraits : UnaryLambdaTraits&lt;decltype( &amp;L::operator() )&gt; {};

    template&lt;typename ClassT, typename ReturnT, typename... Args&gt;
    struct UnaryLambdaTraits&lt;ReturnT( ClassT::* )( Args... ) const&gt; {
        static const bool isValid = false;
    };

    template&lt;typename ClassT, typename ReturnT, typename ArgT&gt;
    struct UnaryLambdaTraits&lt;ReturnT( ClassT::* )( ArgT ) const&gt; {
        static const bool isValid = true;
        using ArgType = typename std::remove_const&lt;typename std::remove_reference&lt;ArgT&gt;::type&gt;::type;
        using ReturnType = ReturnT;
    };

    class TokenStream;

    // Transport for raw args (copied from main args, or supplied via init list for testing)
    class Args {
        friend TokenStream;
        std::string m_exeName;
        std::vector&lt;std::string&gt; m_args;

    public:
        Args( int argc, char const* const* argv )
            : m_exeName(argv[0]),
              m_args(argv + 1, argv + argc) {}

        Args( std::initializer_list&lt;std::string&gt; args )
        :   m_exeName( *args.begin() ),
            m_args( args.begin()+1, args.end() )
        {}

        auto exeName() const -&gt; std::string {
            return m_exeName;
        }
    };

    // Wraps a token coming from a token stream. These may not directly correspond to strings as a single string
    // may encode an option + its argument if the : or = form is used
    enum class TokenType {
        Option, Argument
    };
    struct Token {
        TokenType type;
        std::string token;
    };

    inline auto isOptPrefix( char c ) -&gt; bool {
        return c == '-'
#ifdef CATCH_PLATFORM_WINDOWS
            || c == '/'
#endif
        ;
    }

    // Abstracts iterators into args as a stream of tokens, with option arguments uniformly handled
    class TokenStream {
        using Iterator = std::vector&lt;std::string&gt;::const_iterator;
        Iterator it;
        Iterator itEnd;
        std::vector&lt;Token&gt; m_tokenBuffer;

        void loadBuffer() {
            m_tokenBuffer.resize( 0 );

            // Skip any empty strings
            while( it != itEnd &amp;&amp; it-&gt;empty() )
                ++it;

            if( it != itEnd ) {
                auto const &amp;next = *it;
                if( isOptPrefix( next[0] ) ) {
                    auto delimiterPos = next.find_first_of( " :=" );
                    if( delimiterPos != std::string::npos ) {
                        m_tokenBuffer.push_back( { TokenType::Option, next.substr( 0, delimiterPos ) } );
                        m_tokenBuffer.push_back( { TokenType::Argument, next.substr( delimiterPos + 1 ) } );
                    } else {
                        if( next[1] != '-' &amp;&amp; next.size() &gt; 2 ) {
                            std::string opt = "- ";
                            for( size_t i = 1; i &lt; next.size(); ++i ) {
                                opt[1] = next[i];
                                m_tokenBuffer.push_back( { TokenType::Option, opt } );
                            }
                        } else {
                            m_tokenBuffer.push_back( { TokenType::Option, next } );
                        }
                    }
                } else {
                    m_tokenBuffer.push_back( { TokenType::Argument, next } );
                }
            }
        }

    public:
        explicit TokenStream( Args const &amp;args ) : TokenStream( args.m_args.begin(), args.m_args.end() ) {}

        TokenStream( Iterator it, Iterator itEnd ) : it( it ), itEnd( itEnd ) {
            loadBuffer();
        }

        explicit operator bool() const {
            return !m_tokenBuffer.empty() || it != itEnd;
        }

        auto count() const -&gt; size_t { return m_tokenBuffer.size() + (itEnd - it); }

        auto operator*() const -&gt; Token {
            assert( !m_tokenBuffer.empty() );
            return m_tokenBuffer.front();
        }

        auto operator-&gt;() const -&gt; Token const * {
            assert( !m_tokenBuffer.empty() );
            return &amp;m_tokenBuffer.front();
        }

        auto operator++() -&gt; TokenStream &amp; {
            if( m_tokenBuffer.size() &gt;= 2 ) {
                m_tokenBuffer.erase( m_tokenBuffer.begin() );
            } else {
                if( it != itEnd )
                    ++it;
                loadBuffer();
            }
            return *this;
        }
    };

    class ResultBase {
    public:
        enum Type {
            Ok, LogicError, RuntimeError
        };

    protected:
        ResultBase( Type type ) : m_type( type ) {}
        virtual ~ResultBase() = default;

        virtual void enforceOk() const = 0;

        Type m_type;
    };

    template&lt;typename T&gt;
    class ResultValueBase : public ResultBase {
    public:
        auto value() const -&gt; T const &amp; {
            enforceOk();
            return m_value;
        }

    protected:
        ResultValueBase( Type type ) : ResultBase( type ) {}

        ResultValueBase( ResultValueBase const &amp;other ) : ResultBase( other ) {
            if( m_type == ResultBase::Ok )
                new( &amp;m_value ) T( other.m_value );
        }

        ResultValueBase( Type, T const &amp;value ) : ResultBase( Ok ) {
            new( &amp;m_value ) T( value );
        }

        auto operator=( ResultValueBase const &amp;other ) -&gt; ResultValueBase &amp; {
            if( m_type == ResultBase::Ok )
                m_value.~T();
            ResultBase::operator=(other);
            if( m_type == ResultBase::Ok )
                new( &amp;m_value ) T( other.m_value );
            return *this;
        }

        ~ResultValueBase() override {
            if( m_type == Ok )
                m_value.~T();
        }

        union {
            T m_value;
        };
    };

    template&lt;&gt;
    class ResultValueBase&lt;void&gt; : public ResultBase {
    protected:
        using ResultBase::ResultBase;
    };

    template&lt;typename T = void&gt;
    class BasicResult : public ResultValueBase&lt;T&gt; {
    public:
        template&lt;typename U&gt;
        explicit BasicResult( BasicResult&lt;U&gt; const &amp;other )
        :   ResultValueBase&lt;T&gt;( other.type() ),
            m_errorMessage( other.errorMessage() )
        {
            assert( type() != ResultBase::Ok );
        }

        template&lt;typename U&gt;
        static auto ok( U const &amp;value ) -&gt; BasicResult { return { ResultBase::Ok, value }; }
        static auto ok() -&gt; BasicResult { return { ResultBase::Ok }; }
        static auto logicError( std::string const &amp;message ) -&gt; BasicResult { return { ResultBase::LogicError, message }; }
        static auto runtimeError( std::string const &amp;message ) -&gt; BasicResult { return { ResultBase::RuntimeError, message }; }

        explicit operator bool() const { return m_type == ResultBase::Ok; }
        auto type() const -&gt; ResultBase::Type { return m_type; }
        auto errorMessage() const -&gt; std::string { return m_errorMessage; }

    protected:
        void enforceOk() const override {

            // Errors shouldn't reach this point, but if they do
            // the actual error message will be in m_errorMessage
            assert( m_type != ResultBase::LogicError );
            assert( m_type != ResultBase::RuntimeError );
            if( m_type != ResultBase::Ok )
                std::abort();
        }

        std::string m_errorMessage; // Only populated if resultType is an error

        BasicResult( ResultBase::Type type, std::string const &amp;message )
        :   ResultValueBase&lt;T&gt;(type),
            m_errorMessage(message)
        {
            assert( m_type != ResultBase::Ok );
        }

        using ResultValueBase&lt;T&gt;::ResultValueBase;
        using ResultBase::m_type;
    };

    enum class ParseResultType {
        Matched, NoMatch, ShortCircuitAll, ShortCircuitSame
    };

    class ParseState {
    public:

        ParseState( ParseResultType type, TokenStream const &amp;remainingTokens )
        : m_type(type),
          m_remainingTokens( remainingTokens )
        {}

        auto type() const -&gt; ParseResultType { return m_type; }
        auto remainingTokens() const -&gt; TokenStream { return m_remainingTokens; }

    private:
        ParseResultType m_type;
        TokenStream m_remainingTokens;
    };

    using Result = BasicResult&lt;void&gt;;
    using ParserResult = BasicResult&lt;ParseResultType&gt;;
    using InternalParseResult = BasicResult&lt;ParseState&gt;;

    struct HelpColumns {
        std::string left;
        std::string right;
    };

    template&lt;typename T&gt;
    inline auto convertInto( std::string const &amp;source, T&amp; target ) -&gt; ParserResult {
        std::stringstream ss;
        ss &lt;&lt; source;
        ss &gt;&gt; target;
        if( ss.fail() )
            return ParserResult::runtimeError( "Unable to convert '" + source + "' to destination type" );
        else
            return ParserResult::ok( ParseResultType::Matched );
    }
    inline auto convertInto( std::string const &amp;source, std::string&amp; target ) -&gt; ParserResult {
        target = source;
        return ParserResult::ok( ParseResultType::Matched );
    }
    inline auto convertInto( std::string const &amp;source, bool &amp;target ) -&gt; ParserResult {
        std::string srcLC = source;
        std::transform( srcLC.begin(), srcLC.end(), srcLC.begin(), []( unsigned char c ) { return static_cast&lt;char&gt;( std::tolower(c) ); } );
        if (srcLC == "y" || srcLC == "1" || srcLC == "true" || srcLC == "yes" || srcLC == "on")
            target = true;
        else if (srcLC == "n" || srcLC == "0" || srcLC == "false" || srcLC == "no" || srcLC == "off")
            target = false;
        else
            return ParserResult::runtimeError( "Expected a boolean value but did not recognise: '" + source + "'" );
        return ParserResult::ok( ParseResultType::Matched );
    }
#ifdef CLARA_CONFIG_OPTIONAL_TYPE
    template&lt;typename T&gt;
    inline auto convertInto( std::string const &amp;source, CLARA_CONFIG_OPTIONAL_TYPE&lt;T&gt;&amp; target ) -&gt; ParserResult {
        T temp;
        auto result = convertInto( source, temp );
        if( result )
            target = std::move(temp);
        return result;
    }
#endif // CLARA_CONFIG_OPTIONAL_TYPE

    struct NonCopyable {
        NonCopyable() = default;
        NonCopyable( NonCopyable const &amp; ) = delete;
        NonCopyable( NonCopyable &amp;&amp; ) = delete;
        NonCopyable &amp;operator=( NonCopyable const &amp; ) = delete;
        NonCopyable &amp;operator=( NonCopyable &amp;&amp; ) = delete;
    };

    struct BoundRef : NonCopyable {
        virtual ~BoundRef() = default;
        virtual auto isContainer() const -&gt; bool { return false; }
        virtual auto isFlag() const -&gt; bool { return false; }
    };
    struct BoundValueRefBase : BoundRef {
        virtual auto setValue( std::string const &amp;arg ) -&gt; ParserResult = 0;
    };
    struct BoundFlagRefBase : BoundRef {
        virtual auto setFlag( bool flag ) -&gt; ParserResult = 0;
        virtual auto isFlag() const -&gt; bool { return true; }
    };

    template&lt;typename T&gt;
    struct BoundValueRef : BoundValueRefBase {
        T &amp;m_ref;

        explicit BoundValueRef( T &amp;ref ) : m_ref( ref ) {}

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            return convertInto( arg, m_ref );
        }
    };

    template&lt;typename T&gt;
    struct BoundValueRef&lt;std::vector&lt;T&gt;&gt; : BoundValueRefBase {
        std::vector&lt;T&gt; &amp;m_ref;

        explicit BoundValueRef( std::vector&lt;T&gt; &amp;ref ) : m_ref( ref ) {}

        auto isContainer() const -&gt; bool override { return true; }

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            T temp;
            auto result = convertInto( arg, temp );
            if( result )
                m_ref.push_back( temp );
            return result;
        }
    };

    struct BoundFlagRef : BoundFlagRefBase {
        bool &amp;m_ref;

        explicit BoundFlagRef( bool &amp;ref ) : m_ref( ref ) {}

        auto setFlag( bool flag ) -&gt; ParserResult override {
            m_ref = flag;
            return ParserResult::ok( ParseResultType::Matched );
        }
    };

    template&lt;typename ReturnType&gt;
    struct LambdaInvoker {
        static_assert( std::is_same&lt;ReturnType, ParserResult&gt;::value, "Lambda must return void or clara::ParserResult" );

        template&lt;typename L, typename ArgType&gt;
        static auto invoke( L const &amp;lambda, ArgType const &amp;arg ) -&gt; ParserResult {
            return lambda( arg );
        }
    };

    template&lt;&gt;
    struct LambdaInvoker&lt;void&gt; {
        template&lt;typename L, typename ArgType&gt;
        static auto invoke( L const &amp;lambda, ArgType const &amp;arg ) -&gt; ParserResult {
            lambda( arg );
            return ParserResult::ok( ParseResultType::Matched );
        }
    };

    template&lt;typename ArgType, typename L&gt;
    inline auto invokeLambda( L const &amp;lambda, std::string const &amp;arg ) -&gt; ParserResult {
        ArgType temp{};
        auto result = convertInto( arg, temp );
        return !result
           ? result
           : LambdaInvoker&lt;typename UnaryLambdaTraits&lt;L&gt;::ReturnType&gt;::invoke( lambda, temp );
    }

    template&lt;typename L&gt;
    struct BoundLambda : BoundValueRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits&lt;L&gt;::isValid, "Supplied lambda must take exactly one argument" );
        explicit BoundLambda( L const &amp;lambda ) : m_lambda( lambda ) {}

        auto setValue( std::string const &amp;arg ) -&gt; ParserResult override {
            return invokeLambda&lt;typename UnaryLambdaTraits&lt;L&gt;::ArgType&gt;( m_lambda, arg );
        }
    };

    template&lt;typename L&gt;
    struct BoundFlagLambda : BoundFlagRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits&lt;L&gt;::isValid, "Supplied lambda must take exactly one argument" );
        static_assert( std::is_same&lt;typename UnaryLambdaTraits&lt;L&gt;::ArgType, bool&gt;::value, "flags must be boolean" );

        explicit BoundFlagLambda( L const &amp;lambda ) : m_lambda( lambda ) {}

        auto setFlag( bool flag ) -&gt; ParserResult override {
            return LambdaInvoker&lt;typename UnaryLambdaTraits&lt;L&gt;::ReturnType&gt;::invoke( m_lambda, flag );
        }
    };

    enum class Optionality { Optional, Required };

    struct Parser;

    class ParserBase {
    public:
        virtual ~ParserBase() = default;
        virtual auto validate() const -&gt; Result { return Result::ok(); }
        virtual auto parse( std::string const&amp; exeName, TokenStream const &amp;tokens) const -&gt; InternalParseResult  = 0;
        virtual auto cardinality() const -&gt; size_t { return 1; }

        auto parse( Args const &amp;args ) const -&gt; InternalParseResult {
            return parse( args.exeName(), TokenStream( args ) );
        }
    };

    template&lt;typename DerivedT&gt;
    class ComposableParserImpl : public ParserBase {
    public:
        template&lt;typename T&gt;
        auto operator|( T const &amp;other ) const -&gt; Parser;

		template&lt;typename T&gt;
        auto operator+( T const &amp;other ) const -&gt; Parser;
    };

    // Common code and state for Args and Opts
    template&lt;typename DerivedT&gt;
    class ParserRefImpl : public ComposableParserImpl&lt;DerivedT&gt; {
    protected:
        Optionality m_optionality = Optionality::Optional;
        std::shared_ptr&lt;BoundRef&gt; m_ref;
        std::string m_hint;
        std::string m_description;

        explicit ParserRefImpl( std::shared_ptr&lt;BoundRef&gt; const &amp;ref ) : m_ref( ref ) {}

    public:
        template&lt;typename T&gt;
        ParserRefImpl( T &amp;ref, std::string const &amp;hint )
        :   m_ref( std::make_shared&lt;BoundValueRef&lt;T&gt;&gt;( ref ) ),
            m_hint( hint )
        {}

        template&lt;typename LambdaT&gt;
        ParserRefImpl( LambdaT const &amp;ref, std::string const &amp;hint )
        :   m_ref( std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( ref ) ),
            m_hint(hint)
        {}

        auto operator()( std::string const &amp;description ) -&gt; DerivedT &amp; {
            m_description = description;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        }

        auto optional() -&gt; DerivedT &amp; {
            m_optionality = Optionality::Optional;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        };

        auto required() -&gt; DerivedT &amp; {
            m_optionality = Optionality::Required;
            return static_cast&lt;DerivedT &amp;&gt;( *this );
        };

        auto isOptional() const -&gt; bool {
            return m_optionality == Optionality::Optional;
        }

        auto cardinality() const -&gt; size_t override {
            if( m_ref-&gt;isContainer() )
                return 0;
            else
                return 1;
        }

        auto hint() const -&gt; std::string { return m_hint; }
    };

    class ExeName : public ComposableParserImpl&lt;ExeName&gt; {
        std::shared_ptr&lt;std::string&gt; m_name;
        std::shared_ptr&lt;BoundValueRefBase&gt; m_ref;

        template&lt;typename LambdaT&gt;
        static auto makeRef(LambdaT const &amp;lambda) -&gt; std::shared_ptr&lt;BoundValueRefBase&gt; {
            return std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( lambda) ;
        }

    public:
        ExeName() : m_name( std::make_shared&lt;std::string&gt;( "&lt;executable&gt;" ) ) {}

        explicit ExeName( std::string &amp;ref ) : ExeName() {
            m_ref = std::make_shared&lt;BoundValueRef&lt;std::string&gt;&gt;( ref );
        }

        template&lt;typename LambdaT&gt;
        explicit ExeName( LambdaT const&amp; lambda ) : ExeName() {
            m_ref = std::make_shared&lt;BoundLambda&lt;LambdaT&gt;&gt;( lambda );
        }

        // The exe name is not parsed out of the normal tokens, but is handled specially
        auto parse( std::string const&amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, tokens ) );
        }

        auto name() const -&gt; std::string { return *m_name; }
        auto set( std::string const&amp; newName ) -&gt; ParserResult {

            auto lastSlash = newName.find_last_of( "\\/" );
            auto filename = ( lastSlash == std::string::npos )
                    ? newName
                    : newName.substr( lastSlash+1 );

            *m_name = filename;
            if( m_ref )
                return m_ref-&gt;setValue( filename );
            else
                return ParserResult::ok( ParseResultType::Matched );
        }
    };

    class Arg : public ParserRefImpl&lt;Arg&gt; {
    public:
        using ParserRefImpl::ParserRefImpl;

        auto parse( std::string const &amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            auto validationResult = validate();
            if( !validationResult )
                return InternalParseResult( validationResult );

            auto remainingTokens = tokens;
            auto const &amp;token = *remainingTokens;
            if( token.type != TokenType::Argument )
                return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, remainingTokens ) );

            assert( !m_ref-&gt;isFlag() );
            auto valueRef = static_cast&lt;detail::BoundValueRefBase*&gt;( m_ref.get() );

            auto result = valueRef-&gt;setValue( remainingTokens-&gt;token );
            if( !result )
                return InternalParseResult( result );
            else
                return InternalParseResult::ok( ParseState( ParseResultType::Matched, ++remainingTokens ) );
        }
    };

    inline auto normaliseOpt( std::string const &amp;optName ) -&gt; std::string {
#ifdef CATCH_PLATFORM_WINDOWS
        if( optName[0] == '/' )
            return "-" + optName.substr( 1 );
        else
#endif
            return optName;
    }

    class Opt : public ParserRefImpl&lt;Opt&gt; {
    protected:
        std::vector&lt;std::string&gt; m_optNames;

    public:
        template&lt;typename LambdaT&gt;
        explicit Opt( LambdaT const &amp;ref ) : ParserRefImpl( std::make_shared&lt;BoundFlagLambda&lt;LambdaT&gt;&gt;( ref ) ) {}

        explicit Opt( bool &amp;ref ) : ParserRefImpl( std::make_shared&lt;BoundFlagRef&gt;( ref ) ) {}

        template&lt;typename LambdaT&gt;
        Opt( LambdaT const &amp;ref, std::string const &amp;hint ) : ParserRefImpl( ref, hint ) {}

        template&lt;typename T&gt;
        Opt( T &amp;ref, std::string const &amp;hint ) : ParserRefImpl( ref, hint ) {}

        auto operator[]( std::string const &amp;optName ) -&gt; Opt &amp; {
            m_optNames.push_back( optName );
            return *this;
        }

        auto getHelpColumns() const -&gt; std::vector&lt;HelpColumns&gt; {
            std::ostringstream oss;
            bool first = true;
            for( auto const &amp;opt : m_optNames ) {
                if (first)
                    first = false;
                else
                    oss &lt;&lt; ", ";
                oss &lt;&lt; opt;
            }
            if( !m_hint.empty() )
                oss &lt;&lt; " &lt;" &lt;&lt; m_hint &lt;&lt; "&gt;";
            return { { oss.str(), m_description } };
        }

        auto isMatch( std::string const &amp;optToken ) const -&gt; bool {
            auto normalisedToken = normaliseOpt( optToken );
            for( auto const &amp;name : m_optNames ) {
                if( normaliseOpt( name ) == normalisedToken )
                    return true;
            }
            return false;
        }

        using ParserBase::parse;

        auto parse( std::string const&amp;, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {
            auto validationResult = validate();
            if( !validationResult )
                return InternalParseResult( validationResult );

            auto remainingTokens = tokens;
            if( remainingTokens &amp;&amp; remainingTokens-&gt;type == TokenType::Option ) {
                auto const &amp;token = *remainingTokens;
                if( isMatch(token.token ) ) {
                    if( m_ref-&gt;isFlag() ) {
                        auto flagRef = static_cast&lt;detail::BoundFlagRefBase*&gt;( m_ref.get() );
                        auto result = flagRef-&gt;setFlag( true );
                        if( !result )
                            return InternalParseResult( result );
                        if( result.value() == ParseResultType::ShortCircuitAll )
                            return InternalParseResult::ok( ParseState( result.value(), remainingTokens ) );
                    } else {
                        auto valueRef = static_cast&lt;detail::BoundValueRefBase*&gt;( m_ref.get() );
                        ++remainingTokens;
                        if( !remainingTokens )
                            return InternalParseResult::runtimeError( "Expected argument following " + token.token );
                        auto const &amp;argToken = *remainingTokens;
                        if( argToken.type != TokenType::Argument )
                            return InternalParseResult::runtimeError( "Expected argument following " + token.token );
                        auto result = valueRef-&gt;setValue( argToken.token );
                        if( !result )
                            return InternalParseResult( result );
                        if( result.value() == ParseResultType::ShortCircuitAll )
                            return InternalParseResult::ok( ParseState( result.value(), remainingTokens ) );
                    }
                    return InternalParseResult::ok( ParseState( ParseResultType::Matched, ++remainingTokens ) );
                }
            }
            return InternalParseResult::ok( ParseState( ParseResultType::NoMatch, remainingTokens ) );
        }

        auto validate() const -&gt; Result override {
            if( m_optNames.empty() )
                return Result::logicError( "No options supplied to Opt" );
            for( auto const &amp;name : m_optNames ) {
                if( name.empty() )
                    return Result::logicError( "Option name cannot be empty" );
#ifdef CATCH_PLATFORM_WINDOWS
                if( name[0] != '-' &amp;&amp; name[0] != '/' )
                    return Result::logicError( "Option name must begin with '-' or '/'" );
#else
                if( name[0] != '-' )
                    return Result::logicError( "Option name must begin with '-'" );
#endif
            }
            return ParserRefImpl::validate();
        }
    };

    struct Help : Opt {
        Help( bool &amp;showHelpFlag )
        :   Opt([&amp;]( bool flag ) {
                showHelpFlag = flag;
                return ParserResult::ok( ParseResultType::ShortCircuitAll );
            })
        {
            static_cast&lt;Opt &amp;&gt;( *this )
                    ("display usage information")
                    ["-?"]["-h"]["--help"]
                    .optional();
        }
    };

    struct Parser : ParserBase {

        mutable ExeName m_exeName;
        std::vector&lt;Opt&gt; m_options;
        std::vector&lt;Arg&gt; m_args;

        auto operator|=( ExeName const &amp;exeName ) -&gt; Parser &amp; {
            m_exeName = exeName;
            return *this;
        }

        auto operator|=( Arg const &amp;arg ) -&gt; Parser &amp; {
            m_args.push_back(arg);
            return *this;
        }

        auto operator|=( Opt const &amp;opt ) -&gt; Parser &amp; {
            m_options.push_back(opt);
            return *this;
        }

        auto operator|=( Parser const &amp;other ) -&gt; Parser &amp; {
            m_options.insert(m_options.end(), other.m_options.begin(), other.m_options.end());
            m_args.insert(m_args.end(), other.m_args.begin(), other.m_args.end());
            return *this;
        }

        template&lt;typename T&gt;
        auto operator|( T const &amp;other ) const -&gt; Parser {
            return Parser( *this ) |= other;
        }

        // Forward deprecated interface with '+' instead of '|'
        template&lt;typename T&gt;
        auto operator+=( T const &amp;other ) -&gt; Parser &amp; { return operator|=( other ); }
        template&lt;typename T&gt;
        auto operator+( T const &amp;other ) const -&gt; Parser { return operator|( other ); }

        auto getHelpColumns() const -&gt; std::vector&lt;HelpColumns&gt; {
            std::vector&lt;HelpColumns&gt; cols;
            for (auto const &amp;o : m_options) {
                auto childCols = o.getHelpColumns();
                cols.insert( cols.end(), childCols.begin(), childCols.end() );
            }
            return cols;
        }

        void writeToStream( std::ostream &amp;os ) const {
            if (!m_exeName.name().empty()) {
                os &lt;&lt; "usage:\n" &lt;&lt; "  " &lt;&lt; m_exeName.name() &lt;&lt; " ";
                bool required = true, first = true;
                for( auto const &amp;arg : m_args ) {
                    if (first)
                        first = false;
                    else
                        os &lt;&lt; " ";
                    if( arg.isOptional() &amp;&amp; required ) {
                        os &lt;&lt; "[";
                        required = false;
                    }
                    os &lt;&lt; "&lt;" &lt;&lt; arg.hint() &lt;&lt; "&gt;";
                    if( arg.cardinality() == 0 )
                        os &lt;&lt; " ... ";
                }
                if( !required )
                    os &lt;&lt; "]";
                if( !m_options.empty() )
                    os &lt;&lt; " options";
                os &lt;&lt; "\n\nwhere options are:" &lt;&lt; std::endl;
            }

            auto rows = getHelpColumns();
            size_t consoleWidth = CATCH_CLARA_CONFIG_CONSOLE_WIDTH;
            size_t optWidth = 0;
            for( auto const &amp;cols : rows )
                optWidth = (std::max)(optWidth, cols.left.size() + 2);

            optWidth = (std::min)(optWidth, consoleWidth/2);

            for( auto const &amp;cols : rows ) {
                auto row =
                        TextFlow::Column( cols.left ).width( optWidth ).indent( 2 ) +
                        TextFlow::Spacer(4) +
                        TextFlow::Column( cols.right ).width( consoleWidth - 7 - optWidth );
                os &lt;&lt; row &lt;&lt; std::endl;
            }
        }

        friend auto operator&lt;&lt;( std::ostream &amp;os, Parser const &amp;parser ) -&gt; std::ostream&amp; {
            parser.writeToStream( os );
            return os;
        }

        auto validate() const -&gt; Result override {
            for( auto const &amp;opt : m_options ) {
                auto result = opt.validate();
                if( !result )
                    return result;
            }
            for( auto const &amp;arg : m_args ) {
                auto result = arg.validate();
                if( !result )
                    return result;
            }
            return Result::ok();
        }

        using ParserBase::parse;

        auto parse( std::string const&amp; exeName, TokenStream const &amp;tokens ) const -&gt; InternalParseResult override {

            struct ParserInfo {
                ParserBase const* parser = nullptr;
                size_t count = 0;
            };
            const size_t totalParsers = m_options.size() + m_args.size();
            assert( totalParsers &lt; 512 );
            // ParserInfo parseInfos[totalParsers]; // &lt;-- this is what we really want to do
            ParserInfo parseInfos[512];

            {
                size_t i = 0;
                for (auto const &amp;opt : m_options) parseInfos[i++].parser = &amp;opt;
                for (auto const &amp;arg : m_args) parseInfos[i++].parser = &amp;arg;
            }

            m_exeName.set( exeName );

            auto result = InternalParseResult::ok( ParseState( ParseResultType::NoMatch, tokens ) );
            while( result.value().remainingTokens() ) {
                bool tokenParsed = false;

                for( size_t i = 0; i &lt; totalParsers; ++i ) {
                    auto&amp;  parseInfo = parseInfos[i];
                    if( parseInfo.parser-&gt;cardinality() == 0 || parseInfo.count &lt; parseInfo.parser-&gt;cardinality() ) {
                        result = parseInfo.parser-&gt;parse(exeName, result.value().remainingTokens());
                        if (!result)
                            return result;
                        if (result.value().type() != ParseResultType::NoMatch) {
                            tokenParsed = true;
                            ++parseInfo.count;
                            break;
                        }
                    }
                }

                if( result.value().type() == ParseResultType::ShortCircuitAll )
                    return result;
                if( !tokenParsed )
                    return InternalParseResult::runtimeError( "Unrecognised token: " + result.value().remainingTokens()-&gt;token );
            }
            // !TBD Check missing required options
            return result;
        }
    };

    template&lt;typename DerivedT&gt;
    template&lt;typename T&gt;
    auto ComposableParserImpl&lt;DerivedT&gt;::operator|( T const &amp;other ) const -&gt; Parser {
        return Parser() | static_cast&lt;DerivedT const &amp;&gt;( *this ) | other;
    }
} // namespace detail

// A Combined parser
using detail::Parser;

// A parser for options
using detail::Opt;

// A parser for arguments
using detail::Arg;

// Wrapper for argc, argv from main()
using detail::Args;

// Specifies the name of the executable
using detail::ExeName;

// Convenience wrapper for option parser that specifies the help option
using detail::Help;

// enum of result types from a parse
using detail::ParseResultType;

// Result type for parser operation
using detail::ParserResult;

}} // namespace Catch::clara

// end clara.hpp
#ifdef __clang__
#pragma clang diagnostic pop
#endif

// Restore Clara's value for console width, if present
#ifdef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#undef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#endif

// end catch_clara.h
namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData&amp; config );

} // end namespace Catch

// end catch_commandline.h
#include &lt;fstream&gt;
#include &lt;ctime&gt;

namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData&amp; config ) {

        using namespace clara;

        auto const setWarning = [&amp;]( std::string const&amp; warning ) {
                auto warningSet = [&amp;]() {
                    if( warning == "NoAssertions" )
                        return WarnAbout::NoAssertions;

                    if ( warning == "NoTests" )
                        return WarnAbout::NoTests;

                    return WarnAbout::Nothing;
                }();

                if (warningSet == WarnAbout::Nothing)
                    return ParserResult::runtimeError( "Unrecognised warning: '" + warning + "'" );
                config.warnings = static_cast&lt;WarnAbout::What&gt;( config.warnings | warningSet );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const loadTestNamesFromFile = [&amp;]( std::string const&amp; filename ) {
                std::ifstream f( filename.c_str() );
                if( !f.is_open() )
                    return ParserResult::runtimeError( "Unable to load input file: '" + filename + "'" );

                std::string line;
                while( std::getline( f, line ) ) {
                    line = trim(line);
                    if( !line.empty() &amp;&amp; !startsWith( line, '#' ) ) {
                        if( !startsWith( line, '"' ) )
                            line = '"' + line + '"';
                        config.testsOrTags.push_back( line );
                        config.testsOrTags.emplace_back( "," );
                    }
                }
                //Remove comma in the end
                if(!config.testsOrTags.empty())
                    config.testsOrTags.erase( config.testsOrTags.end()-1 );

                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setTestOrder = [&amp;]( std::string const&amp; order ) {
                if( startsWith( "declared", order ) )
                    config.runOrder = RunTests::InDeclarationOrder;
                else if( startsWith( "lexical", order ) )
                    config.runOrder = RunTests::InLexicographicalOrder;
                else if( startsWith( "random", order ) )
                    config.runOrder = RunTests::InRandomOrder;
                else
                    return clara::ParserResult::runtimeError( "Unrecognised ordering: '" + order + "'" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setRngSeed = [&amp;]( std::string const&amp; seed ) {
                if( seed != "time" )
                    return clara::detail::convertInto( seed, config.rngSeed );
                config.rngSeed = static_cast&lt;unsigned int&gt;( std::time(nullptr) );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setColourUsage = [&amp;]( std::string const&amp; useColour ) {
                    auto mode = toLower( useColour );

                    if( mode == "yes" )
                        config.useColour = UseColour::Yes;
                    else if( mode == "no" )
                        config.useColour = UseColour::No;
                    else if( mode == "auto" )
                        config.useColour = UseColour::Auto;
                    else
                        return ParserResult::runtimeError( "colour mode must be one of: auto, yes or no. '" + useColour + "' not recognised" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setWaitForKeypress = [&amp;]( std::string const&amp; keypress ) {
                auto keypressLc = toLower( keypress );
                if (keypressLc == "never")
                    config.waitForKeypress = WaitForKeypress::Never;
                else if( keypressLc == "start" )
                    config.waitForKeypress = WaitForKeypress::BeforeStart;
                else if( keypressLc == "exit" )
                    config.waitForKeypress = WaitForKeypress::BeforeExit;
                else if( keypressLc == "both" )
                    config.waitForKeypress = WaitForKeypress::BeforeStartAndExit;
                else
                    return ParserResult::runtimeError( "keypress argument must be one of: never, start, exit or both. '" + keypress + "' not recognised" );
            return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setVerbosity = [&amp;]( std::string const&amp; verbosity ) {
            auto lcVerbosity = toLower( verbosity );
            if( lcVerbosity == "quiet" )
                config.verbosity = Verbosity::Quiet;
            else if( lcVerbosity == "normal" )
                config.verbosity = Verbosity::Normal;
            else if( lcVerbosity == "high" )
                config.verbosity = Verbosity::High;
            else
                return ParserResult::runtimeError( "Unrecognised verbosity, '" + verbosity + "'" );
            return ParserResult::ok( ParseResultType::Matched );
        };
        auto const setReporter = [&amp;]( std::string const&amp; reporter ) {
            IReporterRegistry::FactoryMap const&amp; factories = getRegistryHub().getReporterRegistry().getFactories();

            auto lcReporter = toLower( reporter );
            auto result = factories.find( lcReporter );

            if( factories.end() != result )
                config.reporterName = lcReporter;
            else
                return ParserResult::runtimeError( "Unrecognized reporter, '" + reporter + "'. Check available with --list-reporters" );
            return ParserResult::ok( ParseResultType::Matched );
        };

        auto cli
            = ExeName( config.processName )
            | Help( config.showHelp )
            | Opt( config.listTests )
                ["-l"]["--list-tests"]
                ( "list all/matching test cases" )
            | Opt( config.listTags )
                ["-t"]["--list-tags"]
                ( "list all/matching tags" )
            | Opt( config.showSuccessfulTests )
                ["-s"]["--success"]
                ( "include successful tests in output" )
            | Opt( config.shouldDebugBreak )
                ["-b"]["--break"]
                ( "break into debugger on failure" )
            | Opt( config.noThrow )
                ["-e"]["--nothrow"]
                ( "skip exception tests" )
            | Opt( config.showInvisibles )
                ["-i"]["--invisibles"]
                ( "show invisibles (tabs, newlines)" )
            | Opt( config.outputFilename, "filename" )
                ["-o"]["--out"]
                ( "output filename" )
            | Opt( setReporter, "name" )
                ["-r"]["--reporter"]
                ( "reporter to use (defaults to console)" )
            | Opt( config.name, "name" )
                ["-n"]["--name"]
                ( "suite name" )
            | Opt( [&amp;]( bool ){ config.abortAfter = 1; } )
                ["-a"]["--abort"]
                ( "abort at first failure" )
            | Opt( [&amp;]( int x ){ config.abortAfter = x; }, "no. failures" )
                ["-x"]["--abortx"]
                ( "abort after x failures" )
            | Opt( setWarning, "warning name" )
                ["-w"]["--warn"]
                ( "enable warnings" )
            | Opt( [&amp;]( bool flag ) { config.showDurations = flag ? ShowDurations::Always : ShowDurations::Never; }, "yes|no" )
                ["-d"]["--durations"]
                ( "show test durations" )
            | Opt( config.minDuration, "seconds" )
                ["-D"]["--min-duration"]
                ( "show test durations for tests taking at least the given number of seconds" )
            | Opt( loadTestNamesFromFile, "filename" )
                ["-f"]["--input-file"]
                ( "load test names to run from a file" )
            | Opt( config.filenamesAsTags )
                ["-#"]["--filenames-as-tags"]
                ( "adds a tag for the filename" )
            | Opt( config.sectionsToRun, "section name" )
                ["-c"]["--section"]
                ( "specify section to run" )
            | Opt( setVerbosity, "quiet|normal|high" )
                ["-v"]["--verbosity"]
                ( "set output verbosity" )
            | Opt( config.listTestNamesOnly )
                ["--list-test-names-only"]
                ( "list all/matching test cases names only" )
            | Opt( config.listReporters )
                ["--list-reporters"]
                ( "list all reporters" )
            | Opt( setTestOrder, "decl|lex|rand" )
                ["--order"]
                ( "test case order (defaults to decl)" )
            | Opt( setRngSeed, "'time'|number" )
                ["--rng-seed"]
                ( "set a specific seed for random numbers" )
            | Opt( setColourUsage, "yes|no" )
                ["--use-colour"]
                ( "should output be colourised" )
            | Opt( config.libIdentify )
                ["--libidentify"]
                ( "report name and version according to libidentify standard" )
            | Opt( setWaitForKeypress, "never|start|exit|both" )
                ["--wait-for-keypress"]
                ( "waits for a keypress before exiting" )
            | Opt( config.benchmarkSamples, "samples" )
                ["--benchmark-samples"]
                ( "number of samples to collect (default: 100)" )
            | Opt( config.benchmarkResamples, "resamples" )
                ["--benchmark-resamples"]
                ( "number of resamples for the bootstrap (default: 100000)" )
            | Opt( config.benchmarkConfidenceInterval, "confidence interval" )
                ["--benchmark-confidence-interval"]
                ( "confidence interval for the bootstrap (between 0 and 1, default: 0.95)" )
            | Opt( config.benchmarkNoAnalysis )
                ["--benchmark-no-analysis"]
                ( "perform only measurements; do not perform any analysis" )
            | Opt( config.benchmarkWarmupTime, "benchmarkWarmupTime" )
                ["--benchmark-warmup-time"]
                ( "amount of time in milliseconds spent on warming up each test (default: 100)" )
            | Arg( config.testsOrTags, "test name|pattern|tags" )
                ( "which test or tests to use" );

        return cli;
    }

} // end namespace Catch
// end catch_commandline.cpp
// start catch_common.cpp

#include &lt;cstring&gt;
#include &lt;ostream&gt;

namespace Catch {

    bool SourceLineInfo::operator == ( SourceLineInfo const&amp; other ) const noexcept {
        return line == other.line &amp;&amp; (file == other.file || std::strcmp(file, other.file) == 0);
    }
    bool SourceLineInfo::operator &lt; ( SourceLineInfo const&amp; other ) const noexcept {
        // We can assume that the same file will usually have the same pointer.
        // Thus, if the pointers are the same, there is no point in calling the strcmp
        return line &lt; other.line || ( line == other.line &amp;&amp; file != other.file &amp;&amp; (std::strcmp(file, other.file) &lt; 0));
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, SourceLineInfo const&amp; info ) {
#ifndef __GNUG__
        os &lt;&lt; info.file &lt;&lt; '(' &lt;&lt; info.line &lt;&lt; ')';
#else
        os &lt;&lt; info.file &lt;&lt; ':' &lt;&lt; info.line;
#endif
        return os;
    }

    std::string StreamEndStop::operator+() const {
        return std::string();
    }

    NonCopyable::NonCopyable() = default;
    NonCopyable::~NonCopyable() = default;

}
// end catch_common.cpp
// start catch_config.cpp

namespace Catch {

    Config::Config( ConfigData const&amp; data )
    :   m_data( data ),
        m_stream( openStream() )
    {
        // We need to trim filter specs to avoid trouble with superfluous
        // whitespace (esp. important for bdd macros, as those are manually
        // aligned with whitespace).

        for (auto&amp; elem : m_data.testsOrTags) {
            elem = trim(elem);
        }
        for (auto&amp; elem : m_data.sectionsToRun) {
            elem = trim(elem);
        }

        TestSpecParser parser(ITagAliasRegistry::get());
        if (!m_data.testsOrTags.empty()) {
            m_hasTestFilters = true;
            for (auto const&amp; testOrTags : m_data.testsOrTags) {
                parser.parse(testOrTags);
            }
        }
        m_testSpec = parser.testSpec();
    }

    std::string const&amp; Config::getFilename() const {
        return m_data.outputFilename ;
    }

    bool Config::listTests() const          { return m_data.listTests; }
    bool Config::listTestNamesOnly() const  { return m_data.listTestNamesOnly; }
    bool Config::listTags() const           { return m_data.listTags; }
    bool Config::listReporters() const      { return m_data.listReporters; }

    std::string Config::getProcessName() const { return m_data.processName; }
    std::string const&amp; Config::getReporterName() const { return m_data.reporterName; }

    std::vector&lt;std::string&gt; const&amp; Config::getTestsOrTags() const { return m_data.testsOrTags; }
    std::vector&lt;std::string&gt; const&amp; Config::getSectionsToRun() const { return m_data.sectionsToRun; }

    TestSpec const&amp; Config::testSpec() const { return m_testSpec; }
    bool Config::hasTestFilters() const { return m_hasTestFilters; }

    bool Config::showHelp() const { return m_data.showHelp; }

    // IConfig interface
    bool Config::allowThrows() const                   { return !m_data.noThrow; }
    std::ostream&amp; Config::stream() const               { return m_stream-&gt;stream(); }
    std::string Config::name() const                   { return m_data.name.empty() ? m_data.processName : m_data.name; }
    bool Config::includeSuccessfulResults() const      { return m_data.showSuccessfulTests; }
    bool Config::warnAboutMissingAssertions() const    { return !!(m_data.warnings &amp; WarnAbout::NoAssertions); }
    bool Config::warnAboutNoTests() const              { return !!(m_data.warnings &amp; WarnAbout::NoTests); }
    ShowDurations::OrNot Config::showDurations() const { return m_data.showDurations; }
    double Config::minDuration() const                 { return m_data.minDuration; }
    RunTests::InWhatOrder Config::runOrder() const     { return m_data.runOrder; }
    unsigned int Config::rngSeed() const               { return m_data.rngSeed; }
    UseColour::YesOrNo Config::useColour() const       { return m_data.useColour; }
    bool Config::shouldDebugBreak() const              { return m_data.shouldDebugBreak; }
    int Config::abortAfter() const                     { return m_data.abortAfter; }
    bool Config::showInvisibles() const                { return m_data.showInvisibles; }
    Verbosity Config::verbosity() const                { return m_data.verbosity; }

    bool Config::benchmarkNoAnalysis() const                      { return m_data.benchmarkNoAnalysis; }
    int Config::benchmarkSamples() const                          { return m_data.benchmarkSamples; }
    double Config::benchmarkConfidenceInterval() const            { return m_data.benchmarkConfidenceInterval; }
    unsigned int Config::benchmarkResamples() const               { return m_data.benchmarkResamples; }
    std::chrono::milliseconds Config::benchmarkWarmupTime() const { return std::chrono::milliseconds(m_data.benchmarkWarmupTime); }

    IStream const* Config::openStream() {
        return Catch::makeStream(m_data.outputFilename);
    }

} // end namespace Catch
// end catch_config.cpp
// start catch_console_colour.cpp

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

// start catch_errno_guard.h

namespace Catch {

    class ErrnoGuard {
    public:
        ErrnoGuard();
        ~ErrnoGuard();
    private:
        int m_oldErrno;
    };

}

// end catch_errno_guard.h
#include &lt;sstream&gt;

namespace Catch {
    namespace {

        struct IColourImpl {
            virtual ~IColourImpl() = default;
            virtual void use( Colour::Code _colourCode ) = 0;
        };

        struct NoColourImpl : IColourImpl {
            void use( Colour::Code ) override {}

            static IColourImpl* instance() {
                static NoColourImpl s_instance;
                return &amp;s_instance;
            }
        };

    } // anon namespace
} // namespace Catch

#if !defined( CATCH_CONFIG_COLOUR_NONE ) &amp;&amp; !defined( CATCH_CONFIG_COLOUR_WINDOWS ) &amp;&amp; !defined( CATCH_CONFIG_COLOUR_ANSI )
#   ifdef CATCH_PLATFORM_WINDOWS
#       define CATCH_CONFIG_COLOUR_WINDOWS
#   else
#       define CATCH_CONFIG_COLOUR_ANSI
#   endif
#endif

#if defined ( CATCH_CONFIG_COLOUR_WINDOWS ) /////////////////////////////////////////

namespace Catch {
namespace {

    class Win32ColourImpl : public IColourImpl {
    public:
        Win32ColourImpl() : stdoutHandle( GetStdHandle(STD_OUTPUT_HANDLE) )
        {
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            GetConsoleScreenBufferInfo( stdoutHandle, &amp;csbiInfo );
            originalForegroundAttributes = csbiInfo.wAttributes &amp; ~( BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY );
            originalBackgroundAttributes = csbiInfo.wAttributes &amp; ~( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        }

        void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:      return setTextAttribute( originalForegroundAttributes );
                case Colour::White:     return setTextAttribute( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
                case Colour::Red:       return setTextAttribute( FOREGROUND_RED );
                case Colour::Green:     return setTextAttribute( FOREGROUND_GREEN );
                case Colour::Blue:      return setTextAttribute( FOREGROUND_BLUE );
                case Colour::Cyan:      return setTextAttribute( FOREGROUND_BLUE | FOREGROUND_GREEN );
                case Colour::Yellow:    return setTextAttribute( FOREGROUND_RED | FOREGROUND_GREEN );
                case Colour::Grey:      return setTextAttribute( 0 );

                case Colour::LightGrey:     return setTextAttribute( FOREGROUND_INTENSITY );
                case Colour::BrightRed:     return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_RED );
                case Colour::BrightGreen:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN );
                case Colour::BrightWhite:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
                case Colour::BrightYellow:  return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );

                default:
                    CATCH_ERROR( "Unknown colour requested" );
            }
        }

    private:
        void setTextAttribute( WORD _textAttribute ) {
            SetConsoleTextAttribute( stdoutHandle, _textAttribute | originalBackgroundAttributes );
        }
        HANDLE stdoutHandle;
        WORD originalForegroundAttributes;
        WORD originalBackgroundAttributes;
    };

    IColourImpl* platformColourInstance() {
        static Win32ColourImpl s_instance;

        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config-&gt;useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = UseColour::Yes;
        return colourMode == UseColour::Yes
            ? &amp;s_instance
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#elif defined( CATCH_CONFIG_COLOUR_ANSI ) //////////////////////////////////////

#include &lt;unistd.h&gt;

namespace Catch {
namespace {

    // use POSIX/ ANSI console terminal codes
    // Thanks to Adam Strzelecki for original contribution
    // (http://github.com/nanoant)
    // https://github.com/philsquared/Catch/pull/131
    class PosixColourImpl : public IColourImpl {
    public:
        void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:
                case Colour::White:     return setColour( "[0m" );
                case Colour::Red:       return setColour( "[0;31m" );
                case Colour::Green:     return setColour( "[0;32m" );
                case Colour::Blue:      return setColour( "[0;34m" );
                case Colour::Cyan:      return setColour( "[0;36m" );
                case Colour::Yellow:    return setColour( "[0;33m" );
                case Colour::Grey:      return setColour( "[1;30m" );

                case Colour::LightGrey:     return setColour( "[0;37m" );
                case Colour::BrightRed:     return setColour( "[1;31m" );
                case Colour::BrightGreen:   return setColour( "[1;32m" );
                case Colour::BrightWhite:   return setColour( "[1;37m" );
                case Colour::BrightYellow:  return setColour( "[1;33m" );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );
                default: CATCH_INTERNAL_ERROR( "Unknown colour requested" );
            }
        }
        static IColourImpl* instance() {
            static PosixColourImpl s_instance;
            return &amp;s_instance;
        }

    private:
        void setColour( const char* _escapeCode ) {
            getCurrentContext().getConfig()-&gt;stream()
                &lt;&lt; '\033' &lt;&lt; _escapeCode;
        }
    };

    bool useColourOnPlatform() {
        return
#if defined(CATCH_PLATFORM_MAC) || defined(CATCH_PLATFORM_IPHONE)
            !isDebuggerActive() &amp;&amp;
#endif
#if !(defined(__DJGPP__) &amp;&amp; defined(__STRICT_ANSI__))
            isatty(STDOUT_FILENO)
#else
            false
#endif
            ;
    }
    IColourImpl* platformColourInstance() {
        ErrnoGuard guard;
        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config-&gt;useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = useColourOnPlatform()
                ? UseColour::Yes
                : UseColour::No;
        return colourMode == UseColour::Yes
            ? PosixColourImpl::instance()
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#else  // not Windows or ANSI ///////////////////////////////////////////////

namespace Catch {

    static IColourImpl* platformColourInstance() { return NoColourImpl::instance(); }

} // end namespace Catch

#endif // Windows/ ANSI/ None

namespace Catch {

    Colour::Colour( Code _colourCode ) { use( _colourCode ); }
    Colour::Colour( Colour&amp;&amp; other ) noexcept {
        m_moved = other.m_moved;
        other.m_moved = true;
    }
    Colour&amp; Colour::operator=( Colour&amp;&amp; other ) noexcept {
        m_moved = other.m_moved;
        other.m_moved  = true;
        return *this;
    }

    Colour::~Colour(){ if( !m_moved ) use( None ); }

    void Colour::use( Code _colourCode ) {
        static IColourImpl* impl = platformColourInstance();
        // Strictly speaking, this cannot possibly happen.
        // However, under some conditions it does happen (see #1626),
        // and this change is small enough that we can let practicality
        // triumph over purity in this case.
        if (impl != nullptr) {
            impl-&gt;use( _colourCode );
        }
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Colour const&amp; ) {
        return os;
    }

} // end namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif

// end catch_console_colour.cpp
// start catch_context.cpp

namespace Catch {

    class Context : public IMutableContext, NonCopyable {

    public: // IContext
        IResultCapture* getResultCapture() override {
            return m_resultCapture;
        }
        IRunner* getRunner() override {
            return m_runner;
        }

        IConfigPtr const&amp; getConfig() const override {
            return m_config;
        }

        ~Context() override;

    public: // IMutableContext
        void setResultCapture( IResultCapture* resultCapture ) override {
            m_resultCapture = resultCapture;
        }
        void setRunner( IRunner* runner ) override {
            m_runner = runner;
        }
        void setConfig( IConfigPtr const&amp; config ) override {
            m_config = config;
        }

        friend IMutableContext&amp; getCurrentMutableContext();

    private:
        IConfigPtr m_config;
        IRunner* m_runner = nullptr;
        IResultCapture* m_resultCapture = nullptr;
    };

    IMutableContext *IMutableContext::currentContext = nullptr;

    void IMutableContext::createContext()
    {
        currentContext = new Context();
    }

    void cleanUpContext() {
        delete IMutableContext::currentContext;
        IMutableContext::currentContext = nullptr;
    }
    IContext::~IContext() = default;
    IMutableContext::~IMutableContext() = default;
    Context::~Context() = default;

    SimplePcg32&amp; rng() {
        static SimplePcg32 s_rng;
        return s_rng;
    }

}
// end catch_context.cpp
// start catch_debug_console.cpp

// start catch_debug_console.h

#include &lt;string&gt;

namespace Catch {
    void writeToDebugConsole( std::string const&amp; text );
}

// end catch_debug_console.h
#if defined(CATCH_CONFIG_ANDROID_LOGWRITE)
#include &lt;android/log.h&gt;

    namespace Catch {
        void writeToDebugConsole( std::string const&amp; text ) {
            __android_log_write( ANDROID_LOG_DEBUG, "Catch", text.c_str() );
        }
    }

#elif defined(CATCH_PLATFORM_WINDOWS)

    namespace Catch {
        void writeToDebugConsole( std::string const&amp; text ) {
            ::OutputDebugStringA( text.c_str() );
        }
    }

#else

    namespace Catch {
        void writeToDebugConsole( std::string const&amp; text ) {
            // !TBD: Need a version for Mac/ XCode and other IDEs
            Catch::cout() &lt;&lt; text;
        }
    }

#endif // Platform
// end catch_debug_console.cpp
// start catch_debugger.cpp

#if defined(CATCH_PLATFORM_MAC) || defined(CATCH_PLATFORM_IPHONE)

#  include &lt;cassert&gt;
#  include &lt;sys/types.h&gt;
#  include &lt;unistd.h&gt;
#  include &lt;cstddef&gt;
#  include &lt;ostream&gt;

#ifdef __apple_build_version__
    // These headers will only compile with AppleClang (XCode)
    // For other compilers (Clang, GCC, ... ) we need to exclude them
#  include &lt;sys/sysctl.h&gt;
#endif

    namespace Catch {
        #ifdef __apple_build_version__
        // The following function is taken directly from the following technical note:
        // https://developer.apple.com/library/archive/qa/qa1361/_index.html

        // Returns true if the current process is being debugged (either
        // running under the debugger or has a debugger attached post facto).
        bool isDebuggerActive(){
            int                 mib[4];
            struct kinfo_proc   info;
            std::size_t         size;

            // Initialize the flags so that, if sysctl fails for some bizarre
            // reason, we get a predictable result.

            info.kp_proc.p_flag = 0;

            // Initialize mib, which tells sysctl the info we want, in this case
            // we're looking for information about a specific process ID.

            mib[0] = CTL_KERN;
            mib[1] = KERN_PROC;
            mib[2] = KERN_PROC_PID;
            mib[3] = getpid();

            // Call sysctl.

            size = sizeof(info);
            if( sysctl(mib, sizeof(mib) / sizeof(*mib), &amp;info, &amp;size, nullptr, 0) != 0 ) {
                Catch::cerr() &lt;&lt; "\n** Call to sysctl failed - unable to determine if debugger is active **\n" &lt;&lt; std::endl;
                return false;
            }

            // We're being debugged if the P_TRACED flag is set.

            return ( (info.kp_proc.p_flag &amp; P_TRACED) != 0 );
        }
        #else
        bool isDebuggerActive() {
            // We need to find another way to determine this for non-appleclang compilers on macOS
            return false;
        }
        #endif
    } // namespace Catch

#elif defined(CATCH_PLATFORM_LINUX)
    #include &lt;fstream&gt;
    #include &lt;string&gt;

    namespace Catch{
        // The standard POSIX way of detecting a debugger is to attempt to
        // ptrace() the process, but this needs to be done from a child and not
        // this process itself to still allow attaching to this process later
        // if wanted, so is rather heavy. Under Linux we have the PID of the
        // "debugger" (which doesn't need to be gdb, of course, it could also
        // be strace, for example) in /proc/$PID/status, so just get it from
        // there instead.
        bool isDebuggerActive(){
            // Libstdc++ has a bug, where std::ifstream sets errno to 0
            // This way our users can properly assert over errno values
            ErrnoGuard guard;
            std::ifstream in("/proc/self/status");
            for( std::string line; std::getline(in, line); ) {
                static const int PREFIX_LEN = 11;
                if( line.compare(0, PREFIX_LEN, "TracerPid:\t") == 0 ) {
                    // We're traced if the PID is not 0 and no other PID starts
                    // with 0 digit, so it's enough to check for just a single
                    // character.
                    return line.length() &gt; PREFIX_LEN &amp;&amp; line[PREFIX_LEN] != '0';
                }
            }

            return false;
        }
    } // namespace Catch
#elif defined(_MSC_VER)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#else
    namespace Catch {
       bool isDebuggerActive() { return false; }
    }
#endif // Platform
// end catch_debugger.cpp
// start catch_decomposer.cpp

namespace Catch {

    ITransientExpression::~ITransientExpression() = default;

    void formatReconstructedExpression( std::ostream &amp;os, std::string const&amp; lhs, StringRef op, std::string const&amp; rhs ) {
        if( lhs.size() + rhs.size() &lt; 40 &amp;&amp;
                lhs.find('\n') == std::string::npos &amp;&amp;
                rhs.find('\n') == std::string::npos )
            os &lt;&lt; lhs &lt;&lt; " " &lt;&lt; op &lt;&lt; " " &lt;&lt; rhs;
        else
            os &lt;&lt; lhs &lt;&lt; "\n" &lt;&lt; op &lt;&lt; "\n" &lt;&lt; rhs;
    }
}
// end catch_decomposer.cpp
// start catch_enforce.cpp

#include &lt;stdexcept&gt;

namespace Catch {
#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS) &amp;&amp; !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS_CUSTOM_HANDLER)
    [[noreturn]]
    void throw_exception(std::exception const&amp; e) {
        Catch::cerr() &lt;&lt; "Catch will terminate because it needed to throw an exception.\n"
                      &lt;&lt; "The message was: " &lt;&lt; e.what() &lt;&lt; '\n';
        std::terminate();
    }
#endif

    [[noreturn]]
    void throw_logic_error(std::string const&amp; msg) {
        throw_exception(std::logic_error(msg));
    }

    [[noreturn]]
    void throw_domain_error(std::string const&amp; msg) {
        throw_exception(std::domain_error(msg));
    }

    [[noreturn]]
    void throw_runtime_error(std::string const&amp; msg) {
        throw_exception(std::runtime_error(msg));
    }

} // namespace Catch;
// end catch_enforce.cpp
// start catch_enum_values_registry.cpp
// start catch_enum_values_registry.h

#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    namespace Detail {

        std::unique_ptr&lt;EnumInfo&gt; makeEnumInfo( StringRef enumName, StringRef allValueNames, std::vector&lt;int&gt; const&amp; values );

        class EnumValuesRegistry : public IMutableEnumValuesRegistry {

            std::vector&lt;std::unique_ptr&lt;EnumInfo&gt;&gt; m_enumInfos;

            EnumInfo const&amp; registerEnum( StringRef enumName, StringRef allEnums, std::vector&lt;int&gt; const&amp; values) override;
        };

        std::vector&lt;StringRef&gt; parseEnums( StringRef enums );

    } // Detail

} // Catch

// end catch_enum_values_registry.h

#include &lt;map&gt;
#include &lt;cassert&gt;

namespace Catch {

    IMutableEnumValuesRegistry::~IMutableEnumValuesRegistry() {}

    namespace Detail {

        namespace {
            // Extracts the actual name part of an enum instance
            // In other words, it returns the Blue part of Bikeshed::Colour::Blue
            StringRef extractInstanceName(StringRef enumInstance) {
                // Find last occurence of ":"
                size_t name_start = enumInstance.size();
                while (name_start &gt; 0 &amp;&amp; enumInstance[name_start - 1] != ':') {
                    --name_start;
                }
                return enumInstance.substr(name_start, enumInstance.size() - name_start);
            }
        }

        std::vector&lt;StringRef&gt; parseEnums( StringRef enums ) {
            auto enumValues = splitStringRef( enums, ',' );
            std::vector&lt;StringRef&gt; parsed;
            parsed.reserve( enumValues.size() );
            for( auto const&amp; enumValue : enumValues ) {
                parsed.push_back(trim(extractInstanceName(enumValue)));
            }
            return parsed;
        }

        EnumInfo::~EnumInfo() {}

        StringRef EnumInfo::lookup( int value ) const {
            for( auto const&amp; valueToName : m_values ) {
                if( valueToName.first == value )
                    return valueToName.second;
            }
            return "{** unexpected enum value **}"_sr;
        }

        std::unique_ptr&lt;EnumInfo&gt; makeEnumInfo( StringRef enumName, StringRef allValueNames, std::vector&lt;int&gt; const&amp; values ) {
            std::unique_ptr&lt;EnumInfo&gt; enumInfo( new EnumInfo );
            enumInfo-&gt;m_name = enumName;
            enumInfo-&gt;m_values.reserve( values.size() );

            const auto valueNames = Catch::Detail::parseEnums( allValueNames );
            assert( valueNames.size() == values.size() );
            std::size_t i = 0;
            for( auto value : values )
                enumInfo-&gt;m_values.emplace_back(value, valueNames[i++]);

            return enumInfo;
        }

        EnumInfo const&amp; EnumValuesRegistry::registerEnum( StringRef enumName, StringRef allValueNames, std::vector&lt;int&gt; const&amp; values ) {
            m_enumInfos.push_back(makeEnumInfo(enumName, allValueNames, values));
            return *m_enumInfos.back();
        }

    } // Detail
} // Catch

// end catch_enum_values_registry.cpp
// start catch_errno_guard.cpp

#include &lt;cerrno&gt;

namespace Catch {
        ErrnoGuard::ErrnoGuard():m_oldErrno(errno){}
        ErrnoGuard::~ErrnoGuard() { errno = m_oldErrno; }
}
// end catch_errno_guard.cpp
// start catch_exception_translator_registry.cpp

// start catch_exception_translator_registry.h

#include &lt;vector&gt;
#include &lt;string&gt;
#include &lt;memory&gt;

namespace Catch {

    class ExceptionTranslatorRegistry : public IExceptionTranslatorRegistry {
    public:
        ~ExceptionTranslatorRegistry();
        virtual void registerTranslator( const IExceptionTranslator* translator );
        std::string translateActiveException() const override;
        std::string tryTranslators() const;

    private:
        std::vector&lt;std::unique_ptr&lt;IExceptionTranslator const&gt;&gt; m_translators;
    };
}

// end catch_exception_translator_registry.h
#ifdef __OBJC__
#import "Foundation/Foundation.h"
#endif

namespace Catch {

    ExceptionTranslatorRegistry::~ExceptionTranslatorRegistry() {
    }

    void ExceptionTranslatorRegistry::registerTranslator( const IExceptionTranslator* translator ) {
        m_translators.push_back( std::unique_ptr&lt;const IExceptionTranslator&gt;( translator ) );
    }

#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
    std::string ExceptionTranslatorRegistry::translateActiveException() const {
        try {
#ifdef __OBJC__
            // In Objective-C try objective-c exceptions first
            @try {
                return tryTranslators();
            }
            @catch (NSException *exception) {
                return Catch::Detail::stringify( [exception description] );
            }
#else
            // Compiling a mixed mode project with MSVC means that CLR
            // exceptions will be caught in (...) as well. However, these
            // do not fill-in std::current_exception and thus lead to crash
            // when attempting rethrow.
            // /EHa switch also causes structured exceptions to be caught
            // here, but they fill-in current_exception properly, so
            // at worst the output should be a little weird, instead of
            // causing a crash.
            if (std::current_exception() == nullptr) {
                return "Non C++ exception. Possibly a CLR exception.";
            }
            return tryTranslators();
#endif
        }
        catch( TestFailureException&amp; ) {
            std::rethrow_exception(std::current_exception());
        }
        catch( std::exception&amp; ex ) {
            return ex.what();
        }
        catch( std::string&amp; msg ) {
            return msg;
        }
        catch( const char* msg ) {
            return msg;
        }
        catch(...) {
            return "Unknown exception";
        }
    }

    std::string ExceptionTranslatorRegistry::tryTranslators() const {
        if (m_translators.empty()) {
            std::rethrow_exception(std::current_exception());
        } else {
            return m_translators[0]-&gt;translate(m_translators.begin() + 1, m_translators.end());
        }
    }

#else // ^^ Exceptions are enabled // Exceptions are disabled vv
    std::string ExceptionTranslatorRegistry::translateActiveException() const {
        CATCH_INTERNAL_ERROR("Attempted to translate active exception under CATCH_CONFIG_DISABLE_EXCEPTIONS!");
    }

    std::string ExceptionTranslatorRegistry::tryTranslators() const {
        CATCH_INTERNAL_ERROR("Attempted to use exception translators under CATCH_CONFIG_DISABLE_EXCEPTIONS!");
    }
#endif

}
// end catch_exception_translator_registry.cpp
// start catch_fatal_condition.cpp

#if defined(__GNUC__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#if defined( CATCH_CONFIG_WINDOWS_SEH ) || defined( CATCH_CONFIG_POSIX_SIGNALS )

namespace {
    // Report the error condition
    void reportFatal( char const * const message ) {
        Catch::getCurrentContext().getResultCapture()-&gt;handleFatalErrorCondition( message );
    }
}

#endif // signals/SEH handling

#if defined( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {
    struct SignalDefs { DWORD id; const char* name; };

    // There is no 1-1 mapping between signals and windows exceptions.
    // Windows can easily distinguish between SO and SigSegV,
    // but SigInt, SigTerm, etc are handled differently.
    static SignalDefs signalDefs[] = {
        { static_cast&lt;DWORD&gt;(EXCEPTION_ILLEGAL_INSTRUCTION),  "SIGILL - Illegal instruction signal" },
        { static_cast&lt;DWORD&gt;(EXCEPTION_STACK_OVERFLOW), "SIGSEGV - Stack overflow" },
        { static_cast&lt;DWORD&gt;(EXCEPTION_ACCESS_VIOLATION), "SIGSEGV - Segmentation violation signal" },
        { static_cast&lt;DWORD&gt;(EXCEPTION_INT_DIVIDE_BY_ZERO), "Divide by zero error" },
    };

    LONG CALLBACK FatalConditionHandler::handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo) {
        for (auto const&amp; def : signalDefs) {
            if (ExceptionInfo-&gt;ExceptionRecord-&gt;ExceptionCode == def.id) {
                reportFatal(def.name);
            }
        }
        // If its not an exception we care about, pass it along.
        // This stops us from eating debugger breaks etc.
        return EXCEPTION_CONTINUE_SEARCH;
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        // 32k seems enough for Catch to handle stack overflow,
        // but the value was found experimentally, so there is no strong guarantee
        guaranteeSize = 32 * 1024;
        exceptionHandlerHandle = nullptr;
        // Register as first handler in current chain
        exceptionHandlerHandle = AddVectoredExceptionHandler(1, handleVectoredException);
        // Pass in guarantee size to be filled
        SetThreadStackGuarantee(&amp;guaranteeSize);
    }

    void FatalConditionHandler::reset() {
        if (isSet) {
            RemoveVectoredExceptionHandler(exceptionHandlerHandle);
            SetThreadStackGuarantee(&amp;guaranteeSize);
            exceptionHandlerHandle = nullptr;
            isSet = false;
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

bool FatalConditionHandler::isSet = false;
ULONG FatalConditionHandler::guaranteeSize = 0;
PVOID FatalConditionHandler::exceptionHandlerHandle = nullptr;

} // namespace Catch

#elif defined( CATCH_CONFIG_POSIX_SIGNALS )

namespace Catch {

    struct SignalDefs {
        int id;
        const char* name;
    };

    // 32kb for the alternate stack seems to be sufficient. However, this value
    // is experimentally determined, so that's not guaranteed.
    static constexpr std::size_t sigStackSize = 32768 &gt;= MINSIGSTKSZ ? 32768 : MINSIGSTKSZ;

    static SignalDefs signalDefs[] = {
        { SIGINT,  "SIGINT - Terminal interrupt signal" },
        { SIGILL,  "SIGILL - Illegal instruction signal" },
        { SIGFPE,  "SIGFPE - Floating point error signal" },
        { SIGSEGV, "SIGSEGV - Segmentation violation signal" },
        { SIGTERM, "SIGTERM - Termination request signal" },
        { SIGABRT, "SIGABRT - Abort (abnormal termination) signal" }
    };

    void FatalConditionHandler::handleSignal( int sig ) {
        char const * name = "&lt;unknown signal&gt;";
        for (auto const&amp; def : signalDefs) {
            if (sig == def.id) {
                name = def.name;
                break;
            }
        }
        reset();
        reportFatal(name);
        raise( sig );
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        stack_t sigStack;
        sigStack.ss_sp = altStackMem;
        sigStack.ss_size = sigStackSize;
        sigStack.ss_flags = 0;
        sigaltstack(&amp;sigStack, &amp;oldSigStack);
        struct sigaction sa = { };

        sa.sa_handler = handleSignal;
        sa.sa_flags = SA_ONSTACK;
        for (std::size_t i = 0; i &lt; sizeof(signalDefs)/sizeof(SignalDefs); ++i) {
            sigaction(signalDefs[i].id, &amp;sa, &amp;oldSigActions[i]);
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

    void FatalConditionHandler::reset() {
        if( isSet ) {
            // Set signals back to previous values -- hopefully nobody overwrote them in the meantime
            for( std::size_t i = 0; i &lt; sizeof(signalDefs)/sizeof(SignalDefs); ++i ) {
                sigaction(signalDefs[i].id, &amp;oldSigActions[i], nullptr);
            }
            // Return the old stack
            sigaltstack(&amp;oldSigStack, nullptr);
            isSet = false;
        }
    }

    bool FatalConditionHandler::isSet = false;
    struct sigaction FatalConditionHandler::oldSigActions[sizeof(signalDefs)/sizeof(SignalDefs)] = {};
    stack_t FatalConditionHandler::oldSigStack = {};
    char FatalConditionHandler::altStackMem[sigStackSize] = {};

} // namespace Catch

#else

namespace Catch {
    void FatalConditionHandler::reset() {}
}

#endif // signals/SEH handling

#if defined(__GNUC__)
#    pragma GCC diagnostic pop
#endif
// end catch_fatal_condition.cpp
// start catch_generators.cpp

#include &lt;limits&gt;
#include &lt;set&gt;

namespace Catch {

IGeneratorTracker::~IGeneratorTracker() {}

const char* GeneratorException::what() const noexcept {
    return m_msg;
}

namespace Generators {

    GeneratorUntypedBase::~GeneratorUntypedBase() {}

    auto acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const&amp; lineInfo ) -&gt; IGeneratorTracker&amp; {
        return getResultCapture().acquireGeneratorTracker( generatorName, lineInfo );
    }

} // namespace Generators
} // namespace Catch
// end catch_generators.cpp
// start catch_interfaces_capture.cpp

namespace Catch {
    IResultCapture::~IResultCapture() = default;
}
// end catch_interfaces_capture.cpp
// start catch_interfaces_config.cpp

namespace Catch {
    IConfig::~IConfig() = default;
}
// end catch_interfaces_config.cpp
// start catch_interfaces_exception.cpp

namespace Catch {
    IExceptionTranslator::~IExceptionTranslator() = default;
    IExceptionTranslatorRegistry::~IExceptionTranslatorRegistry() = default;
}
// end catch_interfaces_exception.cpp
// start catch_interfaces_registry_hub.cpp

namespace Catch {
    IRegistryHub::~IRegistryHub() = default;
    IMutableRegistryHub::~IMutableRegistryHub() = default;
}
// end catch_interfaces_registry_hub.cpp
// start catch_interfaces_reporter.cpp

// start catch_reporter_listening.h

namespace Catch {

    class ListeningReporter : public IStreamingReporter {
        using Reporters = std::vector&lt;IStreamingReporterPtr&gt;;
        Reporters m_listeners;
        IStreamingReporterPtr m_reporter = nullptr;
        ReporterPreferences m_preferences;

    public:
        ListeningReporter();

        void addListener( IStreamingReporterPtr&amp;&amp; listener );
        void addReporter( IStreamingReporterPtr&amp;&amp; reporter );

    public: // IStreamingReporter

        ReporterPreferences getPreferences() const override;

        void noMatchingTestCases( std::string const&amp; spec ) override;

        void reportInvalidArguments(std::string const&amp;arg) override;

        static std::set&lt;Verbosity&gt; getSupportedVerbosities();

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
        void benchmarkPreparing(std::string const&amp; name) override;
        void benchmarkStarting( BenchmarkInfo const&amp; benchmarkInfo ) override;
        void benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; benchmarkStats ) override;
        void benchmarkFailed(std::string const&amp;) override;
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

        void testRunStarting( TestRunInfo const&amp; testRunInfo ) override;
        void testGroupStarting( GroupInfo const&amp; groupInfo ) override;
        void testCaseStarting( TestCaseInfo const&amp; testInfo ) override;
        void sectionStarting( SectionInfo const&amp; sectionInfo ) override;
        void assertionStarting( AssertionInfo const&amp; assertionInfo ) override;

        // The return value indicates if the messages buffer should be cleared:
        bool assertionEnded( AssertionStats const&amp; assertionStats ) override;
        void sectionEnded( SectionStats const&amp; sectionStats ) override;
        void testCaseEnded( TestCaseStats const&amp; testCaseStats ) override;
        void testGroupEnded( TestGroupStats const&amp; testGroupStats ) override;
        void testRunEnded( TestRunStats const&amp; testRunStats ) override;

        void skipTest( TestCaseInfo const&amp; testInfo ) override;
        bool isMulti() const override;

    };

} // end namespace Catch

// end catch_reporter_listening.h
namespace Catch {

    ReporterConfig::ReporterConfig( IConfigPtr const&amp; _fullConfig )
    :   m_stream( &amp;_fullConfig-&gt;stream() ), m_fullConfig( _fullConfig ) {}

    ReporterConfig::ReporterConfig( IConfigPtr const&amp; _fullConfig, std::ostream&amp; _stream )
    :   m_stream( &amp;_stream ), m_fullConfig( _fullConfig ) {}

    std::ostream&amp; ReporterConfig::stream() const { return *m_stream; }
    IConfigPtr ReporterConfig::fullConfig() const { return m_fullConfig; }

    TestRunInfo::TestRunInfo( std::string const&amp; _name ) : name( _name ) {}

    GroupInfo::GroupInfo(  std::string const&amp; _name,
                           std::size_t _groupIndex,
                           std::size_t _groupsCount )
    :   name( _name ),
        groupIndex( _groupIndex ),
        groupsCounts( _groupsCount )
    {}

     AssertionStats::AssertionStats( AssertionResult const&amp; _assertionResult,
                                     std::vector&lt;MessageInfo&gt; const&amp; _infoMessages,
                                     Totals const&amp; _totals )
    :   assertionResult( _assertionResult ),
        infoMessages( _infoMessages ),
        totals( _totals )
    {
        assertionResult.m_resultData.lazyExpression.m_transientExpression = _assertionResult.m_resultData.lazyExpression.m_transientExpression;

        if( assertionResult.hasMessage() ) {
            // Copy message into messages list.
            // !TBD This should have been done earlier, somewhere
            MessageBuilder builder( assertionResult.getTestMacroName(), assertionResult.getSourceInfo(), assertionResult.getResultType() );
            builder &lt;&lt; assertionResult.getMessage();
            builder.m_info.message = builder.m_stream.str();

            infoMessages.push_back( builder.m_info );
        }
    }

     AssertionStats::~AssertionStats() = default;

    SectionStats::SectionStats(  SectionInfo const&amp; _sectionInfo,
                                 Counts const&amp; _assertions,
                                 double _durationInSeconds,
                                 bool _missingAssertions )
    :   sectionInfo( _sectionInfo ),
        assertions( _assertions ),
        durationInSeconds( _durationInSeconds ),
        missingAssertions( _missingAssertions )
    {}

    SectionStats::~SectionStats() = default;

    TestCaseStats::TestCaseStats(  TestCaseInfo const&amp; _testInfo,
                                   Totals const&amp; _totals,
                                   std::string const&amp; _stdOut,
                                   std::string const&amp; _stdErr,
                                   bool _aborting )
    : testInfo( _testInfo ),
        totals( _totals ),
        stdOut( _stdOut ),
        stdErr( _stdErr ),
        aborting( _aborting )
    {}

    TestCaseStats::~TestCaseStats() = default;

    TestGroupStats::TestGroupStats( GroupInfo const&amp; _groupInfo,
                                    Totals const&amp; _totals,
                                    bool _aborting )
    :   groupInfo( _groupInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    TestGroupStats::TestGroupStats( GroupInfo const&amp; _groupInfo )
    :   groupInfo( _groupInfo ),
        aborting( false )
    {}

    TestGroupStats::~TestGroupStats() = default;

    TestRunStats::TestRunStats(   TestRunInfo const&amp; _runInfo,
                    Totals const&amp; _totals,
                    bool _aborting )
    :   runInfo( _runInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    TestRunStats::~TestRunStats() = default;

    void IStreamingReporter::fatalErrorEncountered( StringRef ) {}
    bool IStreamingReporter::isMulti() const { return false; }

    IReporterFactory::~IReporterFactory() = default;
    IReporterRegistry::~IReporterRegistry() = default;

} // end namespace Catch
// end catch_interfaces_reporter.cpp
// start catch_interfaces_runner.cpp

namespace Catch {
    IRunner::~IRunner() = default;
}
// end catch_interfaces_runner.cpp
// start catch_interfaces_testcase.cpp

namespace Catch {
    ITestInvoker::~ITestInvoker() = default;
    ITestCaseRegistry::~ITestCaseRegistry() = default;
}
// end catch_interfaces_testcase.cpp
// start catch_leak_detector.cpp

#ifdef CATCH_CONFIG_WINDOWS_CRTDBG
#include &lt;crtdbg.h&gt;

namespace Catch {

    LeakDetector::LeakDetector() {
        int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        flag |= _CRTDBG_LEAK_CHECK_DF;
        flag |= _CRTDBG_ALLOC_MEM_DF;
        _CrtSetDbgFlag(flag);
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
        // Change this to leaking allocation's number to break there
        _CrtSetBreakAlloc(-1);
    }
}

#else

    Catch::LeakDetector::LeakDetector() {}

#endif

Catch::LeakDetector::~LeakDetector() {
    Catch::cleanUp();
}
// end catch_leak_detector.cpp
// start catch_list.cpp

// start catch_list.h

#include &lt;set&gt;

namespace Catch {

    std::size_t listTests( Config const&amp; config );

    std::size_t listTestsNamesOnly( Config const&amp; config );

    struct TagInfo {
        void add( std::string const&amp; spelling );
        std::string all() const;

        std::set&lt;std::string&gt; spellings;
        std::size_t count = 0;
    };

    std::size_t listTags( Config const&amp; config );

    std::size_t listReporters();

    Option&lt;std::size_t&gt; list( std::shared_ptr&lt;Config&gt; const&amp; config );

} // end namespace Catch

// end catch_list.h
// start catch_text.h

namespace Catch {
    using namespace clara::TextFlow;
}

// end catch_text.h
#include &lt;limits&gt;
#include &lt;algorithm&gt;
#include &lt;iomanip&gt;

namespace Catch {

    std::size_t listTests( Config const&amp; config ) {
        TestSpec const&amp; testSpec = config.testSpec();
        if( config.hasTestFilters() )
            Catch::cout() &lt;&lt; "Matching test cases:\n";
        else {
            Catch::cout() &lt;&lt; "All available test cases:\n";
        }

        auto matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCaseInfo : matchedTestCases ) {
            Colour::Code colour = testCaseInfo.isHidden()
                ? Colour::SecondaryText
                : Colour::None;
            Colour colourGuard( colour );

            Catch::cout() &lt;&lt; Column( testCaseInfo.name ).initialIndent( 2 ).indent( 4 ) &lt;&lt; "\n";
            if( config.verbosity() &gt;= Verbosity::High ) {
                Catch::cout() &lt;&lt; Column( Catch::Detail::stringify( testCaseInfo.lineInfo ) ).indent(4) &lt;&lt; std::endl;
                std::string description = testCaseInfo.description;
                if( description.empty() )
                    description = "(NO DESCRIPTION)";
                Catch::cout() &lt;&lt; Column( description ).indent(4) &lt;&lt; std::endl;
            }
            if( !testCaseInfo.tags.empty() )
                Catch::cout() &lt;&lt; Column( testCaseInfo.tagsAsString() ).indent( 6 ) &lt;&lt; "\n";
        }

        if( !config.hasTestFilters() )
            Catch::cout() &lt;&lt; pluralise( matchedTestCases.size(), "test case" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        else
            Catch::cout() &lt;&lt; pluralise( matchedTestCases.size(), "matching test case" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        return matchedTestCases.size();
    }

    std::size_t listTestsNamesOnly( Config const&amp; config ) {
        TestSpec const&amp; testSpec = config.testSpec();
        std::size_t matchedTests = 0;
        std::vector&lt;TestCase&gt; matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCaseInfo : matchedTestCases ) {
            matchedTests++;
            if( startsWith( testCaseInfo.name, '#' ) )
               Catch::cout() &lt;&lt; '"' &lt;&lt; testCaseInfo.name &lt;&lt; '"';
            else
               Catch::cout() &lt;&lt; testCaseInfo.name;
            if ( config.verbosity() &gt;= Verbosity::High )
                Catch::cout() &lt;&lt; "\t@" &lt;&lt; testCaseInfo.lineInfo;
            Catch::cout() &lt;&lt; std::endl;
        }
        return matchedTests;
    }

    void TagInfo::add( std::string const&amp; spelling ) {
        ++count;
        spellings.insert( spelling );
    }

    std::string TagInfo::all() const {
        size_t size = 0;
        for (auto const&amp; spelling : spellings) {
            // Add 2 for the brackes
            size += spelling.size() + 2;
        }

        std::string out; out.reserve(size);
        for (auto const&amp; spelling : spellings) {
            out += '[';
            out += spelling;
            out += ']';
        }
        return out;
    }

    std::size_t listTags( Config const&amp; config ) {
        TestSpec const&amp; testSpec = config.testSpec();
        if( config.hasTestFilters() )
            Catch::cout() &lt;&lt; "Tags for matching test cases:\n";
        else {
            Catch::cout() &lt;&lt; "All available tags:\n";
        }

        std::map&lt;std::string, TagInfo&gt; tagCounts;

        std::vector&lt;TestCase&gt; matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const&amp; testCase : matchedTestCases ) {
            for( auto const&amp; tagName : testCase.getTestCaseInfo().tags ) {
                std::string lcaseTagName = toLower( tagName );
                auto countIt = tagCounts.find( lcaseTagName );
                if( countIt == tagCounts.end() )
                    countIt = tagCounts.insert( std::make_pair( lcaseTagName, TagInfo() ) ).first;
                countIt-&gt;second.add( tagName );
            }
        }

        for( auto const&amp; tagCount : tagCounts ) {
            ReusableStringStream rss;
            rss &lt;&lt; "  " &lt;&lt; std::setw(2) &lt;&lt; tagCount.second.count &lt;&lt; "  ";
            auto str = rss.str();
            auto wrapper = Column( tagCount.second.all() )
                                                    .initialIndent( 0 )
                                                    .indent( str.size() )
                                                    .width( CATCH_CONFIG_CONSOLE_WIDTH-10 );
            Catch::cout() &lt;&lt; str &lt;&lt; wrapper &lt;&lt; '\n';
        }
        Catch::cout() &lt;&lt; pluralise( tagCounts.size(), "tag" ) &lt;&lt; '\n' &lt;&lt; std::endl;
        return tagCounts.size();
    }

    std::size_t listReporters() {
        Catch::cout() &lt;&lt; "Available reporters:\n";
        IReporterRegistry::FactoryMap const&amp; factories = getRegistryHub().getReporterRegistry().getFactories();
        std::size_t maxNameLen = 0;
        for( auto const&amp; factoryKvp : factories )
            maxNameLen = (std::max)( maxNameLen, factoryKvp.first.size() );

        for( auto const&amp; factoryKvp : factories ) {
            Catch::cout()
                    &lt;&lt; Column( factoryKvp.first + ":" )
                            .indent(2)
                            .width( 5+maxNameLen )
                    +  Column( factoryKvp.second-&gt;getDescription() )
                            .initialIndent(0)
                            .indent(2)
                            .width( CATCH_CONFIG_CONSOLE_WIDTH - maxNameLen-8 )
                    &lt;&lt; "\n";
        }
        Catch::cout() &lt;&lt; std::endl;
        return factories.size();
    }

    Option&lt;std::size_t&gt; list( std::shared_ptr&lt;Config&gt; const&amp; config ) {
        Option&lt;std::size_t&gt; listedCount;
        getCurrentMutableContext().setConfig( config );
        if( config-&gt;listTests() )
            listedCount = listedCount.valueOr(0) + listTests( *config );
        if( config-&gt;listTestNamesOnly() )
            listedCount = listedCount.valueOr(0) + listTestsNamesOnly( *config );
        if( config-&gt;listTags() )
            listedCount = listedCount.valueOr(0) + listTags( *config );
        if( config-&gt;listReporters() )
            listedCount = listedCount.valueOr(0) + listReporters();
        return listedCount;
    }

} // end namespace Catch
// end catch_list.cpp
// start catch_matchers.cpp

namespace Catch {
namespace Matchers {
    namespace Impl {

        std::string MatcherUntypedBase::toString() const {
            if( m_cachedToString.empty() )
                m_cachedToString = describe();
            return m_cachedToString;
        }

        MatcherUntypedBase::~MatcherUntypedBase() = default;

    } // namespace Impl
} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch
// end catch_matchers.cpp
// start catch_matchers_exception.cpp

namespace Catch {
namespace Matchers {
namespace Exception {

bool ExceptionMessageMatcher::match(std::exception const&amp; ex) const {
    return ex.what() == m_message;
}

std::string ExceptionMessageMatcher::describe() const {
    return "exception message matches \"" + m_message + "\"";
}

}
Exception::ExceptionMessageMatcher Message(std::string const&amp; message) {
    return Exception::ExceptionMessageMatcher(message);
}

// namespace Exception
} // namespace Matchers
} // namespace Catch
// end catch_matchers_exception.cpp
// start catch_matchers_floating.cpp

// start catch_polyfills.hpp

namespace Catch {
    bool isnan(float f);
    bool isnan(double d);
}

// end catch_polyfills.hpp
// start catch_to_string.hpp

#include &lt;string&gt;

namespace Catch {
    template &lt;typename T&gt;
    std::string to_string(T const&amp; t) {
#if defined(CATCH_CONFIG_CPP11_TO_STRING)
        return std::to_string(t);
#else
        ReusableStringStream rss;
        rss &lt;&lt; t;
        return rss.str();
#endif
    }
} // end namespace Catch

// end catch_to_string.hpp
#include &lt;algorithm&gt;
#include &lt;cmath&gt;
#include &lt;cstdlib&gt;
#include &lt;cstdint&gt;
#include &lt;cstring&gt;
#include &lt;sstream&gt;
#include &lt;type_traits&gt;
#include &lt;iomanip&gt;
#include &lt;limits&gt;

namespace Catch {
namespace {

    int32_t convert(float f) {
        static_assert(sizeof(float) == sizeof(int32_t), "Important ULP matcher assumption violated");
        int32_t i;
        std::memcpy(&amp;i, &amp;f, sizeof(f));
        return i;
    }

    int64_t convert(double d) {
        static_assert(sizeof(double) == sizeof(int64_t), "Important ULP matcher assumption violated");
        int64_t i;
        std::memcpy(&amp;i, &amp;d, sizeof(d));
        return i;
    }

    template &lt;typename FP&gt;
    bool almostEqualUlps(FP lhs, FP rhs, uint64_t maxUlpDiff) {
        // Comparison with NaN should always be false.
        // This way we can rule it out before getting into the ugly details
        if (Catch::isnan(lhs) || Catch::isnan(rhs)) {
            return false;
        }

        auto lc = convert(lhs);
        auto rc = convert(rhs);

        if ((lc &lt; 0) != (rc &lt; 0)) {
            // Potentially we can have +0 and -0
            return lhs == rhs;
        }

        auto ulpDiff = std::abs(lc - rc);
        return static_cast&lt;uint64_t&gt;(ulpDiff) &lt;= maxUlpDiff;
    }

#if defined(CATCH_CONFIG_GLOBAL_NEXTAFTER)

    float nextafter(float x, float y) {
        return ::nextafterf(x, y);
    }

    double nextafter(double x, double y) {
        return ::nextafter(x, y);
    }

#endif // ^^^ CATCH_CONFIG_GLOBAL_NEXTAFTER ^^^

template &lt;typename FP&gt;
FP step(FP start, FP direction, uint64_t steps) {
    for (uint64_t i = 0; i &lt; steps; ++i) {
#if defined(CATCH_CONFIG_GLOBAL_NEXTAFTER)
        start = Catch::nextafter(start, direction);
#else
        start = std::nextafter(start, direction);
#endif
    }
    return start;
}

// Performs equivalent check of std::fabs(lhs - rhs) &lt;= margin
// But without the subtraction to allow for INFINITY in comparison
bool marginComparison(double lhs, double rhs, double margin) {
    return (lhs + margin &gt;= rhs) &amp;&amp; (rhs + margin &gt;= lhs);
}

template &lt;typename FloatingPoint&gt;
void write(std::ostream&amp; out, FloatingPoint num) {
    out &lt;&lt; std::scientific
        &lt;&lt; std::setprecision(std::numeric_limits&lt;FloatingPoint&gt;::max_digits10 - 1)
        &lt;&lt; num;
}

} // end anonymous namespace

namespace Matchers {
namespace Floating {

    enum class FloatingPointKind : uint8_t {
        Float,
        Double
    };

    WithinAbsMatcher::WithinAbsMatcher(double target, double margin)
        :m_target{ target }, m_margin{ margin } {
        CATCH_ENFORCE(margin &gt;= 0, "Invalid margin: " &lt;&lt; margin &lt;&lt; '.'
            &lt;&lt; " Margin has to be non-negative.");
    }

    // Performs equivalent check of std::fabs(lhs - rhs) &lt;= margin
    // But without the subtraction to allow for INFINITY in comparison
    bool WithinAbsMatcher::match(double const&amp; matchee) const {
        return (matchee + m_margin &gt;= m_target) &amp;&amp; (m_target + m_margin &gt;= matchee);
    }

    std::string WithinAbsMatcher::describe() const {
        return "is within " + ::Catch::Detail::stringify(m_margin) + " of " + ::Catch::Detail::stringify(m_target);
    }

    WithinUlpsMatcher::WithinUlpsMatcher(double target, uint64_t ulps, FloatingPointKind baseType)
        :m_target{ target }, m_ulps{ ulps }, m_type{ baseType } {
        CATCH_ENFORCE(m_type == FloatingPointKind::Double
                   || m_ulps &lt; (std::numeric_limits&lt;uint32_t&gt;::max)(),
            "Provided ULP is impossibly large for a float comparison.");
    }

#if defined(__clang__)
#pragma clang diagnostic push
// Clang &lt;3.5 reports on the default branch in the switch below
#pragma clang diagnostic ignored "-Wunreachable-code"
#endif

    bool WithinUlpsMatcher::match(double const&amp; matchee) const {
        switch (m_type) {
        case FloatingPointKind::Float:
            return almostEqualUlps&lt;float&gt;(static_cast&lt;float&gt;(matchee), static_cast&lt;float&gt;(m_target), m_ulps);
        case FloatingPointKind::Double:
            return almostEqualUlps&lt;double&gt;(matchee, m_target, m_ulps);
        default:
            CATCH_INTERNAL_ERROR( "Unknown FloatingPointKind value" );
        }
    }

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

    std::string WithinUlpsMatcher::describe() const {
        std::stringstream ret;

        ret &lt;&lt; "is within " &lt;&lt; m_ulps &lt;&lt; " ULPs of ";

        if (m_type == FloatingPointKind::Float) {
            write(ret, static_cast&lt;float&gt;(m_target));
            ret &lt;&lt; 'f';
        } else {
            write(ret, m_target);
        }

        ret &lt;&lt; " ([";
        if (m_type == FloatingPointKind::Double) {
            write(ret, step(m_target, static_cast&lt;double&gt;(-INFINITY), m_ulps));
            ret &lt;&lt; ", ";
            write(ret, step(m_target, static_cast&lt;double&gt;( INFINITY), m_ulps));
        } else {
            // We have to cast INFINITY to float because of MinGW, see #1782
            write(ret, step(static_cast&lt;float&gt;(m_target), static_cast&lt;float&gt;(-INFINITY), m_ulps));
            ret &lt;&lt; ", ";
            write(ret, step(static_cast&lt;float&gt;(m_target), static_cast&lt;float&gt;( INFINITY), m_ulps));
        }
        ret &lt;&lt; "])";

        return ret.str();
    }

    WithinRelMatcher::WithinRelMatcher(double target, double epsilon):
        m_target(target),
        m_epsilon(epsilon){
        CATCH_ENFORCE(m_epsilon &gt;= 0., "Relative comparison with epsilon &lt;  0 does not make sense.");
        CATCH_ENFORCE(m_epsilon  &lt; 1., "Relative comparison with epsilon &gt;= 1 does not make sense.");
    }

    bool WithinRelMatcher::match(double const&amp; matchee) const {
        const auto relMargin = m_epsilon * (std::max)(std::fabs(matchee), std::fabs(m_target));
        return marginComparison(matchee, m_target,
                                std::isinf(relMargin)? 0 : relMargin);
    }

    std::string WithinRelMatcher::describe() const {
        Catch::ReusableStringStream sstr;
        sstr &lt;&lt; "and " &lt;&lt; m_target &lt;&lt; " are within " &lt;&lt; m_epsilon * 100. &lt;&lt; "% of each other";
        return sstr.str();
    }

}// namespace Floating

Floating::WithinUlpsMatcher WithinULP(double target, uint64_t maxUlpDiff) {
    return Floating::WithinUlpsMatcher(target, maxUlpDiff, Floating::FloatingPointKind::Double);
}

Floating::WithinUlpsMatcher WithinULP(float target, uint64_t maxUlpDiff) {
    return Floating::WithinUlpsMatcher(target, maxUlpDiff, Floating::FloatingPointKind::Float);
}

Floating::WithinAbsMatcher WithinAbs(double target, double margin) {
    return Floating::WithinAbsMatcher(target, margin);
}

Floating::WithinRelMatcher WithinRel(double target, double eps) {
    return Floating::WithinRelMatcher(target, eps);
}

Floating::WithinRelMatcher WithinRel(double target) {
    return Floating::WithinRelMatcher(target, std::numeric_limits&lt;double&gt;::epsilon() * 100);
}

Floating::WithinRelMatcher WithinRel(float target, float eps) {
    return Floating::WithinRelMatcher(target, eps);
}

Floating::WithinRelMatcher WithinRel(float target) {
    return Floating::WithinRelMatcher(target, std::numeric_limits&lt;float&gt;::epsilon() * 100);
}

} // namespace Matchers
} // namespace Catch

// end catch_matchers_floating.cpp
// start catch_matchers_generic.cpp

std::string Catch::Matchers::Generic::Detail::finalizeDescription(const std::string&amp; desc) {
    if (desc.empty()) {
        return "matches undescribed predicate";
    } else {
        return "matches predicate: \"" + desc + '"';
    }
}
// end catch_matchers_generic.cpp
// start catch_matchers_string.cpp

#include &lt;regex&gt;

namespace Catch {
namespace Matchers {

    namespace StdString {

        CasedString::CasedString( std::string const&amp; str, CaseSensitive::Choice caseSensitivity )
        :   m_caseSensitivity( caseSensitivity ),
            m_str( adjustString( str ) )
        {}
        std::string CasedString::adjustString( std::string const&amp; str ) const {
            return m_caseSensitivity == CaseSensitive::No
                   ? toLower( str )
                   : str;
        }
        std::string CasedString::caseSensitivitySuffix() const {
            return m_caseSensitivity == CaseSensitive::No
                   ? " (case insensitive)"
                   : std::string();
        }

        StringMatcherBase::StringMatcherBase( std::string const&amp; operation, CasedString const&amp; comparator )
        : m_comparator( comparator ),
          m_operation( operation ) {
        }

        std::string StringMatcherBase::describe() const {
            std::string description;
            description.reserve(5 + m_operation.size() + m_comparator.m_str.size() +
                                        m_comparator.caseSensitivitySuffix().size());
            description += m_operation;
            description += ": \"";
            description += m_comparator.m_str;
            description += "\"";
            description += m_comparator.caseSensitivitySuffix();
            return description;
        }

        EqualsMatcher::EqualsMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "equals", comparator ) {}

        bool EqualsMatcher::match( std::string const&amp; source ) const {
            return m_comparator.adjustString( source ) == m_comparator.m_str;
        }

        ContainsMatcher::ContainsMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "contains", comparator ) {}

        bool ContainsMatcher::match( std::string const&amp; source ) const {
            return contains( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        StartsWithMatcher::StartsWithMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "starts with", comparator ) {}

        bool StartsWithMatcher::match( std::string const&amp; source ) const {
            return startsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        EndsWithMatcher::EndsWithMatcher( CasedString const&amp; comparator ) : StringMatcherBase( "ends with", comparator ) {}

        bool EndsWithMatcher::match( std::string const&amp; source ) const {
            return endsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        RegexMatcher::RegexMatcher(std::string regex, CaseSensitive::Choice caseSensitivity): m_regex(std::move(regex)), m_caseSensitivity(caseSensitivity) {}

        bool RegexMatcher::match(std::string const&amp; matchee) const {
            auto flags = std::regex::ECMAScript; // ECMAScript is the default syntax option anyway
            if (m_caseSensitivity == CaseSensitive::Choice::No) {
                flags |= std::regex::icase;
            }
            auto reg = std::regex(m_regex, flags);
            return std::regex_match(matchee, reg);
        }

        std::string RegexMatcher::describe() const {
            return "matches " + ::Catch::Detail::stringify(m_regex) + ((m_caseSensitivity == CaseSensitive::Choice::Yes)? " case sensitively" : " case insensitively");
        }

    } // namespace StdString

    StdString::EqualsMatcher Equals( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EqualsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::ContainsMatcher Contains( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::ContainsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::EndsWithMatcher EndsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EndsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::StartsWithMatcher StartsWith( std::string const&amp; str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::StartsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }

    StdString::RegexMatcher Matches(std::string const&amp; regex, CaseSensitive::Choice caseSensitivity) {
        return StdString::RegexMatcher(regex, caseSensitivity);
    }

} // namespace Matchers
} // namespace Catch
// end catch_matchers_string.cpp
// start catch_message.cpp

// start catch_uncaught_exceptions.h

namespace Catch {
    bool uncaught_exceptions();
} // end namespace Catch

// end catch_uncaught_exceptions.h
#include &lt;cassert&gt;
#include &lt;stack&gt;

namespace Catch {

    MessageInfo::MessageInfo(   StringRef const&amp; _macroName,
                                SourceLineInfo const&amp; _lineInfo,
                                ResultWas::OfType _type )
    :   macroName( _macroName ),
        lineInfo( _lineInfo ),
        type( _type ),
        sequence( ++globalCount )
    {}

    bool MessageInfo::operator==( MessageInfo const&amp; other ) const {
        return sequence == other.sequence;
    }

    bool MessageInfo::operator&lt;( MessageInfo const&amp; other ) const {
        return sequence &lt; other.sequence;
    }

    // This may need protecting if threading support is added
    unsigned int MessageInfo::globalCount = 0;

    ////////////////////////////////////////////////////////////////////////////

    Catch::MessageBuilder::MessageBuilder( StringRef const&amp; macroName,
                                           SourceLineInfo const&amp; lineInfo,
                                           ResultWas::OfType type )
        :m_info(macroName, lineInfo, type) {}

    ////////////////////////////////////////////////////////////////////////////

    ScopedMessage::ScopedMessage( MessageBuilder const&amp; builder )
    : m_info( builder.m_info ), m_moved()
    {
        m_info.message = builder.m_stream.str();
        getResultCapture().pushScopedMessage( m_info );
    }

    ScopedMessage::ScopedMessage( ScopedMessage&amp;&amp; old )
    : m_info( old.m_info ), m_moved()
    {
        old.m_moved = true;
    }

    ScopedMessage::~ScopedMessage() {
        if ( !uncaught_exceptions() &amp;&amp; !m_moved ){
            getResultCapture().popScopedMessage(m_info);
        }
    }

    Capturer::Capturer( StringRef macroName, SourceLineInfo const&amp; lineInfo, ResultWas::OfType resultType, StringRef names ) {
        auto trimmed = [&amp;] (size_t start, size_t end) {
            while (names[start] == ',' || isspace(static_cast&lt;unsigned char&gt;(names[start]))) {
                ++start;
            }
            while (names[end] == ',' || isspace(static_cast&lt;unsigned char&gt;(names[end]))) {
                --end;
            }
            return names.substr(start, end - start + 1);
        };
        auto skipq = [&amp;] (size_t start, char quote) {
            for (auto i = start + 1; i &lt; names.size() ; ++i) {
                if (names[i] == quote)
                    return i;
                if (names[i] == '\\')
                    ++i;
            }
            CATCH_INTERNAL_ERROR("CAPTURE parsing encountered unmatched quote");
        };

        size_t start = 0;
        std::stack&lt;char&gt; openings;
        for (size_t pos = 0; pos &lt; names.size(); ++pos) {
            char c = names[pos];
            switch (c) {
            case '[':
            case '{':
            case '(':
            // It is basically impossible to disambiguate between
            // comparison and start of template args in this context
//            case '&lt;':
                openings.push(c);
                break;
            case ']':
            case '}':
            case ')':
//           case '&gt;':
                openings.pop();
                break;
            case '"':
            case '\'':
                pos = skipq(pos, c);
                break;
            case ',':
                if (start != pos &amp;&amp; openings.empty()) {
                    m_messages.emplace_back(macroName, lineInfo, resultType);
                    m_messages.back().message = static_cast&lt;std::string&gt;(trimmed(start, pos));
                    m_messages.back().message += " := ";
                    start = pos;
                }
            }
        }
        assert(openings.empty() &amp;&amp; "Mismatched openings");
        m_messages.emplace_back(macroName, lineInfo, resultType);
        m_messages.back().message = static_cast&lt;std::string&gt;(trimmed(start, names.size() - 1));
        m_messages.back().message += " := ";
    }
    Capturer::~Capturer() {
        if ( !uncaught_exceptions() ){
            assert( m_captured == m_messages.size() );
            for( size_t i = 0; i &lt; m_captured; ++i  )
                m_resultCapture.popScopedMessage( m_messages[i] );
        }
    }

    void Capturer::captureValue( size_t index, std::string const&amp; value ) {
        assert( index &lt; m_messages.size() );
        m_messages[index].message += value;
        m_resultCapture.pushScopedMessage( m_messages[index] );
        m_captured++;
    }

} // end namespace Catch
// end catch_message.cpp
// start catch_output_redirect.cpp

// start catch_output_redirect.h
#ifndef TWOBLUECUBES_CATCH_OUTPUT_REDIRECT_H
#define TWOBLUECUBES_CATCH_OUTPUT_REDIRECT_H

#include &lt;cstdio&gt;
#include &lt;iosfwd&gt;
#include &lt;string&gt;

namespace Catch {

    class RedirectedStream {
        std::ostream&amp; m_originalStream;
        std::ostream&amp; m_redirectionStream;
        std::streambuf* m_prevBuf;

    public:
        RedirectedStream( std::ostream&amp; originalStream, std::ostream&amp; redirectionStream );
        ~RedirectedStream();
    };

    class RedirectedStdOut {
        ReusableStringStream m_rss;
        RedirectedStream m_cout;
    public:
        RedirectedStdOut();
        auto str() const -&gt; std::string;
    };

    // StdErr has two constituent streams in C++, std::cerr and std::clog
    // This means that we need to redirect 2 streams into 1 to keep proper
    // order of writes
    class RedirectedStdErr {
        ReusableStringStream m_rss;
        RedirectedStream m_cerr;
        RedirectedStream m_clog;
    public:
        RedirectedStdErr();
        auto str() const -&gt; std::string;
    };

    class RedirectedStreams {
    public:
        RedirectedStreams(RedirectedStreams const&amp;) = delete;
        RedirectedStreams&amp; operator=(RedirectedStreams const&amp;) = delete;
        RedirectedStreams(RedirectedStreams&amp;&amp;) = delete;
        RedirectedStreams&amp; operator=(RedirectedStreams&amp;&amp;) = delete;

        RedirectedStreams(std::string&amp; redirectedCout, std::string&amp; redirectedCerr);
        ~RedirectedStreams();
    private:
        std::string&amp; m_redirectedCout;
        std::string&amp; m_redirectedCerr;
        RedirectedStdOut m_redirectedStdOut;
        RedirectedStdErr m_redirectedStdErr;
    };

#if defined(CATCH_CONFIG_NEW_CAPTURE)

    // Windows's implementation of std::tmpfile is terrible (it tries
    // to create a file inside system folder, thus requiring elevated
    // privileges for the binary), so we have to use tmpnam(_s) and
    // create the file ourselves there.
    class TempFile {
    public:
        TempFile(TempFile const&amp;) = delete;
        TempFile&amp; operator=(TempFile const&amp;) = delete;
        TempFile(TempFile&amp;&amp;) = delete;
        TempFile&amp; operator=(TempFile&amp;&amp;) = delete;

        TempFile();
        ~TempFile();

        std::FILE* getFile();
        std::string getContents();

    private:
        std::FILE* m_file = nullptr;
    #if defined(_MSC_VER)
        char m_buffer[L_tmpnam] = { 0 };
    #endif
    };

    class OutputRedirect {
    public:
        OutputRedirect(OutputRedirect const&amp;) = delete;
        OutputRedirect&amp; operator=(OutputRedirect const&amp;) = delete;
        OutputRedirect(OutputRedirect&amp;&amp;) = delete;
        OutputRedirect&amp; operator=(OutputRedirect&amp;&amp;) = delete;

        OutputRedirect(std::string&amp; stdout_dest, std::string&amp; stderr_dest);
        ~OutputRedirect();

    private:
        int m_originalStdout = -1;
        int m_originalStderr = -1;
        TempFile m_stdoutFile;
        TempFile m_stderrFile;
        std::string&amp; m_stdoutDest;
        std::string&amp; m_stderrDest;
    };

#endif

} // end namespace Catch

#endif // TWOBLUECUBES_CATCH_OUTPUT_REDIRECT_H
// end catch_output_redirect.h
#include &lt;cstdio&gt;
#include &lt;cstring&gt;
#include &lt;fstream&gt;
#include &lt;sstream&gt;
#include &lt;stdexcept&gt;

#if defined(CATCH_CONFIG_NEW_CAPTURE)
    #if defined(_MSC_VER)
    #include &lt;io.h&gt;      //_dup and _dup2
    #define dup _dup
    #define dup2 _dup2
    #define fileno _fileno
    #else
    #include &lt;unistd.h&gt;  // dup and dup2
    #endif
#endif

namespace Catch {

    RedirectedStream::RedirectedStream( std::ostream&amp; originalStream, std::ostream&amp; redirectionStream )
    :   m_originalStream( originalStream ),
        m_redirectionStream( redirectionStream ),
        m_prevBuf( m_originalStream.rdbuf() )
    {
        m_originalStream.rdbuf( m_redirectionStream.rdbuf() );
    }

    RedirectedStream::~RedirectedStream() {
        m_originalStream.rdbuf( m_prevBuf );
    }

    RedirectedStdOut::RedirectedStdOut() : m_cout( Catch::cout(), m_rss.get() ) {}
    auto RedirectedStdOut::str() const -&gt; std::string { return m_rss.str(); }

    RedirectedStdErr::RedirectedStdErr()
    :   m_cerr( Catch::cerr(), m_rss.get() ),
        m_clog( Catch::clog(), m_rss.get() )
    {}
    auto RedirectedStdErr::str() const -&gt; std::string { return m_rss.str(); }

    RedirectedStreams::RedirectedStreams(std::string&amp; redirectedCout, std::string&amp; redirectedCerr)
    :   m_redirectedCout(redirectedCout),
        m_redirectedCerr(redirectedCerr)
    {}

    RedirectedStreams::~RedirectedStreams() {
        m_redirectedCout += m_redirectedStdOut.str();
        m_redirectedCerr += m_redirectedStdErr.str();
    }

#if defined(CATCH_CONFIG_NEW_CAPTURE)

#if defined(_MSC_VER)
    TempFile::TempFile() {
        if (tmpnam_s(m_buffer)) {
            CATCH_RUNTIME_ERROR("Could not get a temp filename");
        }
        if (fopen_s(&amp;m_file, m_buffer, "w+")) {
            char buffer[100];
            if (strerror_s(buffer, errno)) {
                CATCH_RUNTIME_ERROR("Could not translate errno to a string");
            }
            CATCH_RUNTIME_ERROR("Could not open the temp file: '" &lt;&lt; m_buffer &lt;&lt; "' because: " &lt;&lt; buffer);
        }
    }
#else
    TempFile::TempFile() {
        m_file = std::tmpfile();
        if (!m_file) {
            CATCH_RUNTIME_ERROR("Could not create a temp file.");
        }
    }

#endif

    TempFile::~TempFile() {
         // TBD: What to do about errors here?
         std::fclose(m_file);
         // We manually create the file on Windows only, on Linux
         // it will be autodeleted
#if defined(_MSC_VER)
         std::remove(m_buffer);
#endif
    }

    FILE* TempFile::getFile() {
        return m_file;
    }

    std::string TempFile::getContents() {
        std::stringstream sstr;
        char buffer[100] = {};
        std::rewind(m_file);
        while (std::fgets(buffer, sizeof(buffer), m_file)) {
            sstr &lt;&lt; buffer;
        }
        return sstr.str();
    }

    OutputRedirect::OutputRedirect(std::string&amp; stdout_dest, std::string&amp; stderr_dest) :
        m_originalStdout(dup(1)),
        m_originalStderr(dup(2)),
        m_stdoutDest(stdout_dest),
        m_stderrDest(stderr_dest) {
        dup2(fileno(m_stdoutFile.getFile()), 1);
        dup2(fileno(m_stderrFile.getFile()), 2);
    }

    OutputRedirect::~OutputRedirect() {
        Catch::cout() &lt;&lt; std::flush;
        fflush(stdout);
        // Since we support overriding these streams, we flush cerr
        // even though std::cerr is unbuffered
        Catch::cerr() &lt;&lt; std::flush;
        Catch::clog() &lt;&lt; std::flush;
        fflush(stderr);

        dup2(m_originalStdout, 1);
        dup2(m_originalStderr, 2);

        m_stdoutDest += m_stdoutFile.getContents();
        m_stderrDest += m_stderrFile.getContents();
    }

#endif // CATCH_CONFIG_NEW_CAPTURE

} // namespace Catch

#if defined(CATCH_CONFIG_NEW_CAPTURE)
    #if defined(_MSC_VER)
    #undef dup
    #undef dup2
    #undef fileno
    #endif
#endif
// end catch_output_redirect.cpp
// start catch_polyfills.cpp

#include &lt;cmath&gt;

namespace Catch {

#if !defined(CATCH_CONFIG_POLYFILL_ISNAN)
    bool isnan(float f) {
        return std::isnan(f);
    }
    bool isnan(double d) {
        return std::isnan(d);
    }
#else
    // For now we only use this for embarcadero
    bool isnan(float f) {
        return std::_isnan(f);
    }
    bool isnan(double d) {
        return std::_isnan(d);
    }
#endif

} // end namespace Catch
// end catch_polyfills.cpp
// start catch_random_number_generator.cpp

namespace Catch {

namespace {

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4146) // we negate uint32 during the rotate
#endif
        // Safe rotr implementation thanks to John Regehr
        uint32_t rotate_right(uint32_t val, uint32_t count) {
            const uint32_t mask = 31;
            count &amp;= mask;
            return (val &gt;&gt; count) | (val &lt;&lt; (-count &amp; mask));
        }

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}

    SimplePcg32::SimplePcg32(result_type seed_) {
        seed(seed_);
    }

    void SimplePcg32::seed(result_type seed_) {
        m_state = 0;
        (*this)();
        m_state += seed_;
        (*this)();
    }

    void SimplePcg32::discard(uint64_t skip) {
        // We could implement this to run in O(log n) steps, but this
        // should suffice for our use case.
        for (uint64_t s = 0; s &lt; skip; ++s) {
            static_cast&lt;void&gt;((*this)());
        }
    }

    SimplePcg32::result_type SimplePcg32::operator()() {
        // prepare the output value
        const uint32_t xorshifted = static_cast&lt;uint32_t&gt;(((m_state &gt;&gt; 18u) ^ m_state) &gt;&gt; 27u);
        const auto output = rotate_right(xorshifted, m_state &gt;&gt; 59u);

        // advance state
        m_state = m_state * 6364136223846793005ULL + s_inc;

        return output;
    }

    bool operator==(SimplePcg32 const&amp; lhs, SimplePcg32 const&amp; rhs) {
        return lhs.m_state == rhs.m_state;
    }

    bool operator!=(SimplePcg32 const&amp; lhs, SimplePcg32 const&amp; rhs) {
        return lhs.m_state != rhs.m_state;
    }
}
// end catch_random_number_generator.cpp
// start catch_registry_hub.cpp

// start catch_test_case_registry_impl.h

#include &lt;vector&gt;
#include &lt;set&gt;
#include &lt;algorithm&gt;
#include &lt;ios&gt;

namespace Catch {

    class TestCase;
    struct IConfig;

    std::vector&lt;TestCase&gt; sortTests( IConfig const&amp; config, std::vector&lt;TestCase&gt; const&amp; unsortedTestCases );

    bool isThrowSafe( TestCase const&amp; testCase, IConfig const&amp; config );
    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config );

    void enforceNoDuplicateTestCases( std::vector&lt;TestCase&gt; const&amp; functions );

    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config );
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config );

    class TestRegistry : public ITestCaseRegistry {
    public:
        virtual ~TestRegistry() = default;

        virtual void registerTest( TestCase const&amp; testCase );

        std::vector&lt;TestCase&gt; const&amp; getAllTests() const override;
        std::vector&lt;TestCase&gt; const&amp; getAllTestsSorted( IConfig const&amp; config ) const override;

    private:
        std::vector&lt;TestCase&gt; m_functions;
        mutable RunTests::InWhatOrder m_currentSortOrder = RunTests::InDeclarationOrder;
        mutable std::vector&lt;TestCase&gt; m_sortedFunctions;
        std::size_t m_unnamedCount = 0;
        std::ios_base::Init m_ostreamInit; // Forces cout/ cerr to be initialised
    };

    ///////////////////////////////////////////////////////////////////////////

    class TestInvokerAsFunction : public ITestInvoker {
        void(*m_testAsFunction)();
    public:
        TestInvokerAsFunction( void(*testAsFunction)() ) noexcept;

        void invoke() const override;
    };

    std::string extractClassName( StringRef const&amp; classOrQualifiedMethodName );

    ///////////////////////////////////////////////////////////////////////////

} // end namespace Catch

// end catch_test_case_registry_impl.h
// start catch_reporter_registry.h

#include &lt;map&gt;

namespace Catch {

    class ReporterRegistry : public IReporterRegistry {

    public:

        ~ReporterRegistry() override;

        IStreamingReporterPtr create( std::string const&amp; name, IConfigPtr const&amp; config ) const override;

        void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory );
        void registerListener( IReporterFactoryPtr const&amp; factory );

        FactoryMap const&amp; getFactories() const override;
        Listeners const&amp; getListeners() const override;

    private:
        FactoryMap m_factories;
        Listeners m_listeners;
    };
}

// end catch_reporter_registry.h
// start catch_tag_alias_registry.h

// start catch_tag_alias.h

#include &lt;string&gt;

namespace Catch {

    struct TagAlias {
        TagAlias(std::string const&amp; _tag, SourceLineInfo _lineInfo);

        std::string tag;
        SourceLineInfo lineInfo;
    };

} // end namespace Catch

// end catch_tag_alias.h
#include &lt;map&gt;

namespace Catch {

    class TagAliasRegistry : public ITagAliasRegistry {
    public:
        ~TagAliasRegistry() override;
        TagAlias const* find( std::string const&amp; alias ) const override;
        std::string expandAliases( std::string const&amp; unexpandedTestSpec ) const override;
        void add( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo );

    private:
        std::map&lt;std::string, TagAlias&gt; m_registry;
    };

} // end namespace Catch

// end catch_tag_alias_registry.h
// start catch_startup_exception_registry.h

#include &lt;vector&gt;
#include &lt;exception&gt;

namespace Catch {

    class StartupExceptionRegistry {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
    public:
        void add(std::exception_ptr const&amp; exception) noexcept;
        std::vector&lt;std::exception_ptr&gt; const&amp; getExceptions() const noexcept;
    private:
        std::vector&lt;std::exception_ptr&gt; m_exceptions;
#endif
    };

} // end namespace Catch

// end catch_startup_exception_registry.h
// start catch_singletons.hpp

namespace Catch {

    struct ISingleton {
        virtual ~ISingleton();
    };

    void addSingleton( ISingleton* singleton );
    void cleanupSingletons();

    template&lt;typename SingletonImplT, typename InterfaceT = SingletonImplT, typename MutableInterfaceT = InterfaceT&gt;
    class Singleton : SingletonImplT, public ISingleton {

        static auto getInternal() -&gt; Singleton* {
            static Singleton* s_instance = nullptr;
            if( !s_instance ) {
                s_instance = new Singleton;
                addSingleton( s_instance );
            }
            return s_instance;
        }

    public:
        static auto get() -&gt; InterfaceT const&amp; {
            return *getInternal();
        }
        static auto getMutable() -&gt; MutableInterfaceT&amp; {
            return *getInternal();
        }
    };

} // namespace Catch

// end catch_singletons.hpp
namespace Catch {

    namespace {

        class RegistryHub : public IRegistryHub, public IMutableRegistryHub,
                            private NonCopyable {

        public: // IRegistryHub
            RegistryHub() = default;
            IReporterRegistry const&amp; getReporterRegistry() const override {
                return m_reporterRegistry;
            }
            ITestCaseRegistry const&amp; getTestCaseRegistry() const override {
                return m_testCaseRegistry;
            }
            IExceptionTranslatorRegistry const&amp; getExceptionTranslatorRegistry() const override {
                return m_exceptionTranslatorRegistry;
            }
            ITagAliasRegistry const&amp; getTagAliasRegistry() const override {
                return m_tagAliasRegistry;
            }
            StartupExceptionRegistry const&amp; getStartupExceptionRegistry() const override {
                return m_exceptionRegistry;
            }

        public: // IMutableRegistryHub
            void registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) override {
                m_reporterRegistry.registerReporter( name, factory );
            }
            void registerListener( IReporterFactoryPtr const&amp; factory ) override {
                m_reporterRegistry.registerListener( factory );
            }
            void registerTest( TestCase const&amp; testInfo ) override {
                m_testCaseRegistry.registerTest( testInfo );
            }
            void registerTranslator( const IExceptionTranslator* translator ) override {
                m_exceptionTranslatorRegistry.registerTranslator( translator );
            }
            void registerTagAlias( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) override {
                m_tagAliasRegistry.add( alias, tag, lineInfo );
            }
            void registerStartupException() noexcept override {
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
                m_exceptionRegistry.add(std::current_exception());
#else
                CATCH_INTERNAL_ERROR("Attempted to register active exception under CATCH_CONFIG_DISABLE_EXCEPTIONS!");
#endif
            }
            IMutableEnumValuesRegistry&amp; getMutableEnumValuesRegistry() override {
                return m_enumValuesRegistry;
            }

        private:
            TestRegistry m_testCaseRegistry;
            ReporterRegistry m_reporterRegistry;
            ExceptionTranslatorRegistry m_exceptionTranslatorRegistry;
            TagAliasRegistry m_tagAliasRegistry;
            StartupExceptionRegistry m_exceptionRegistry;
            Detail::EnumValuesRegistry m_enumValuesRegistry;
        };
    }

    using RegistryHubSingleton = Singleton&lt;RegistryHub, IRegistryHub, IMutableRegistryHub&gt;;

    IRegistryHub const&amp; getRegistryHub() {
        return RegistryHubSingleton::get();
    }
    IMutableRegistryHub&amp; getMutableRegistryHub() {
        return RegistryHubSingleton::getMutable();
    }
    void cleanUp() {
        cleanupSingletons();
        cleanUpContext();
    }
    std::string translateActiveException() {
        return getRegistryHub().getExceptionTranslatorRegistry().translateActiveException();
    }

} // end namespace Catch
// end catch_registry_hub.cpp
// start catch_reporter_registry.cpp

namespace Catch {

    ReporterRegistry::~ReporterRegistry() = default;

    IStreamingReporterPtr ReporterRegistry::create( std::string const&amp; name, IConfigPtr const&amp; config ) const {
        auto it =  m_factories.find( name );
        if( it == m_factories.end() )
            return nullptr;
        return it-&gt;second-&gt;create( ReporterConfig( config ) );
    }

    void ReporterRegistry::registerReporter( std::string const&amp; name, IReporterFactoryPtr const&amp; factory ) {
        m_factories.emplace(name, factory);
    }
    void ReporterRegistry::registerListener( IReporterFactoryPtr const&amp; factory ) {
        m_listeners.push_back( factory );
    }

    IReporterRegistry::FactoryMap const&amp; ReporterRegistry::getFactories() const {
        return m_factories;
    }
    IReporterRegistry::Listeners const&amp; ReporterRegistry::getListeners() const {
        return m_listeners;
    }

}
// end catch_reporter_registry.cpp
// start catch_result_type.cpp

namespace Catch {

    bool isOk( ResultWas::OfType resultType ) {
        return ( resultType &amp; ResultWas::FailureBit ) == 0;
    }
    bool isJustInfo( int flags ) {
        return flags == ResultWas::Info;
    }

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs ) {
        return static_cast&lt;ResultDisposition::Flags&gt;( static_cast&lt;int&gt;( lhs ) | static_cast&lt;int&gt;( rhs ) );
    }

    bool shouldContinueOnFailure( int flags )    { return ( flags &amp; ResultDisposition::ContinueOnFailure ) != 0; }
    bool shouldSuppressFailure( int flags )      { return ( flags &amp; ResultDisposition::SuppressFail ) != 0; }

} // end namespace Catch
// end catch_result_type.cpp
// start catch_run_context.cpp

#include &lt;cassert&gt;
#include &lt;algorithm&gt;
#include &lt;sstream&gt;

namespace Catch {

    namespace Generators {
        struct GeneratorTracker : TestCaseTracking::TrackerBase, IGeneratorTracker {
            GeneratorBasePtr m_generator;

            GeneratorTracker( TestCaseTracking::NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent )
            :   TrackerBase( nameAndLocation, ctx, parent )
            {}
            ~GeneratorTracker();

            static GeneratorTracker&amp; acquire( TrackerContext&amp; ctx, TestCaseTracking::NameAndLocation const&amp; nameAndLocation ) {
                std::shared_ptr&lt;GeneratorTracker&gt; tracker;

                ITracker&amp; currentTracker = ctx.currentTracker();
                // Under specific circumstances, the generator we want
                // to acquire is also the current tracker. If this is
                // the case, we have to avoid looking through current
                // tracker's children, and instead return the current
                // tracker.
                // A case where this check is important is e.g.
                //     for (int i = 0; i &lt; 5; ++i) {
                //         int n = GENERATE(1, 2);
                //     }
                //
                // without it, the code above creates 5 nested generators.
                if (currentTracker.nameAndLocation() == nameAndLocation) {
                    auto thisTracker = currentTracker.parent().findChild(nameAndLocation);
                    assert(thisTracker);
                    assert(thisTracker-&gt;isGeneratorTracker());
                    tracker = std::static_pointer_cast&lt;GeneratorTracker&gt;(thisTracker);
                } else if ( TestCaseTracking::ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
                    assert( childTracker );
                    assert( childTracker-&gt;isGeneratorTracker() );
                    tracker = std::static_pointer_cast&lt;GeneratorTracker&gt;( childTracker );
                } else {
                    tracker = std::make_shared&lt;GeneratorTracker&gt;( nameAndLocation, ctx, &amp;currentTracker );
                    currentTracker.addChild( tracker );
                }

                if( !tracker-&gt;isComplete() ) {
                    tracker-&gt;open();
                }

                return *tracker;
            }

            // TrackerBase interface
            bool isGeneratorTracker() const override { return true; }
            auto hasGenerator() const -&gt; bool override {
                return !!m_generator;
            }
            void close() override {
                TrackerBase::close();
                // If a generator has a child (it is followed by a section)
                // and none of its children have started, then we must wait
                // until later to start consuming its values.
                // This catches cases where `GENERATE` is placed between two
                // `SECTION`s.
                // **The check for m_children.empty cannot be removed**.
                // doing so would break `GENERATE` _not_ followed by `SECTION`s.
                const bool should_wait_for_child = [&amp;]() {
                    // No children -&gt; nobody to wait for
                    if ( m_children.empty() ) {
                        return false;
                    }
                    // If at least one child started executing, don't wait
                    if ( std::find_if(
                             m_children.begin(),
                             m_children.end(),
                             []( TestCaseTracking::ITrackerPtr tracker ) {
                                 return tracker-&gt;hasStarted();
                             } ) != m_children.end() ) {
                        return false;
                    }

                    // No children have started. We need to check if they _can_
                    // start, and thus we should wait for them, or they cannot
                    // start (due to filters), and we shouldn't wait for them
                    auto* parent = m_parent;
                    // This is safe: there is always at least one section
                    // tracker in a test case tracking tree
                    while ( !parent-&gt;isSectionTracker() ) {
                        parent = &amp;( parent-&gt;parent() );
                    }
                    assert( parent &amp;&amp;
                            "Missing root (test case) level section" );

                    auto const&amp; parentSection =
                        static_cast&lt;SectionTracker&amp;&gt;( *parent );
                    auto const&amp; filters = parentSection.getFilters();
                    // No filters -&gt; no restrictions on running sections
                    if ( filters.empty() ) {
                        return true;
                    }

                    for ( auto const&amp; child : m_children ) {
                        if ( child-&gt;isSectionTracker() &amp;&amp;
                             std::find( filters.begin(),
                                        filters.end(),
                                        static_cast&lt;SectionTracker&amp;&gt;( *child )
                                            .trimmedName() ) !=
                                 filters.end() ) {
                            return true;
                        }
                    }
                    return false;
                }();

                // This check is a bit tricky, because m_generator-&gt;next()
                // has a side-effect, where it consumes generator's current
                // value, but we do not want to invoke the side-effect if
                // this generator is still waiting for any child to start.
                if ( should_wait_for_child ||
                     ( m_runState == CompletedSuccessfully &amp;&amp;
                       m_generator-&gt;next() ) ) {
                    m_children.clear();
                    m_runState = Executing;
                }
            }

            // IGeneratorTracker interface
            auto getGenerator() const -&gt; GeneratorBasePtr const&amp; override {
                return m_generator;
            }
            void setGenerator( GeneratorBasePtr&amp;&amp; generator ) override {
                m_generator = std::move( generator );
            }
        };
        GeneratorTracker::~GeneratorTracker() {}
    }

    RunContext::RunContext(IConfigPtr const&amp; _config, IStreamingReporterPtr&amp;&amp; reporter)
    :   m_runInfo(_config-&gt;name()),
        m_context(getCurrentMutableContext()),
        m_config(_config),
        m_reporter(std::move(reporter)),
        m_lastAssertionInfo{ StringRef(), SourceLineInfo("",0), StringRef(), ResultDisposition::Normal },
        m_includeSuccessfulResults( m_config-&gt;includeSuccessfulResults() || m_reporter-&gt;getPreferences().shouldReportAllAssertions )
    {
        m_context.setRunner(this);
        m_context.setConfig(m_config);
        m_context.setResultCapture(this);
        m_reporter-&gt;testRunStarting(m_runInfo);
    }

    RunContext::~RunContext() {
        m_reporter-&gt;testRunEnded(TestRunStats(m_runInfo, m_totals, aborting()));
    }

    void RunContext::testGroupStarting(std::string const&amp; testSpec, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter-&gt;testGroupStarting(GroupInfo(testSpec, groupIndex, groupsCount));
    }

    void RunContext::testGroupEnded(std::string const&amp; testSpec, Totals const&amp; totals, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter-&gt;testGroupEnded(TestGroupStats(GroupInfo(testSpec, groupIndex, groupsCount), totals, aborting()));
    }

    Totals RunContext::runTest(TestCase const&amp; testCase) {
        Totals prevTotals = m_totals;

        std::string redirectedCout;
        std::string redirectedCerr;

        auto const&amp; testInfo = testCase.getTestCaseInfo();

        m_reporter-&gt;testCaseStarting(testInfo);

        m_activeTestCase = &amp;testCase;

        ITracker&amp; rootTracker = m_trackerContext.startRun();
        assert(rootTracker.isSectionTracker());
        static_cast&lt;SectionTracker&amp;&gt;(rootTracker).addInitialFilters(m_config-&gt;getSectionsToRun());
        do {
            m_trackerContext.startCycle();
            m_testCaseTracker = &amp;SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(testInfo.name, testInfo.lineInfo));
            runCurrentTest(redirectedCout, redirectedCerr);
        } while (!m_testCaseTracker-&gt;isSuccessfullyCompleted() &amp;&amp; !aborting());

        Totals deltaTotals = m_totals.delta(prevTotals);
        if (testInfo.expectedToFail() &amp;&amp; deltaTotals.testCases.passed &gt; 0) {
            deltaTotals.assertions.failed++;
            deltaTotals.testCases.passed--;
            deltaTotals.testCases.failed++;
        }
        m_totals.testCases += deltaTotals.testCases;
        m_reporter-&gt;testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  redirectedCout,
                                  redirectedCerr,
                                  aborting()));

        m_activeTestCase = nullptr;
        m_testCaseTracker = nullptr;

        return deltaTotals;
    }

    IConfigPtr RunContext::config() const {
        return m_config;
    }

    IStreamingReporter&amp; RunContext::reporter() const {
        return *m_reporter;
    }

    void RunContext::assertionEnded(AssertionResult const &amp; result) {
        if (result.getResultType() == ResultWas::Ok) {
            m_totals.assertions.passed++;
            m_lastAssertionPassed = true;
        } else if (!result.isOk()) {
            m_lastAssertionPassed = false;
            if( m_activeTestCase-&gt;getTestCaseInfo().okToFail() )
                m_totals.assertions.failedButOk++;
            else
                m_totals.assertions.failed++;
        }
        else {
            m_lastAssertionPassed = true;
        }

        // We have no use for the return value (whether messages should be cleared), because messages were made scoped
        // and should be let to clear themselves out.
        static_cast&lt;void&gt;(m_reporter-&gt;assertionEnded(AssertionStats(result, m_messages, m_totals)));

        if (result.getResultType() != ResultWas::Warning)
            m_messageScopes.clear();

        // Reset working state
        resetAssertionInfo();
        m_lastResult = result;
    }
    void RunContext::resetAssertionInfo() {
        m_lastAssertionInfo.macroName = StringRef();
        m_lastAssertionInfo.capturedExpression = "{Unknown expression after the reported line}"_sr;
    }

    bool RunContext::sectionStarted(SectionInfo const &amp; sectionInfo, Counts &amp; assertions) {
        ITracker&amp; sectionTracker = SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(sectionInfo.name, sectionInfo.lineInfo));
        if (!sectionTracker.isOpen())
            return false;
        m_activeSections.push_back(&amp;sectionTracker);

        m_lastAssertionInfo.lineInfo = sectionInfo.lineInfo;

        m_reporter-&gt;sectionStarting(sectionInfo);

        assertions = m_totals.assertions;

        return true;
    }
    auto RunContext::acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const&amp; lineInfo ) -&gt; IGeneratorTracker&amp; {
        using namespace Generators;
        GeneratorTracker&amp; tracker = GeneratorTracker::acquire(m_trackerContext,
                                                              TestCaseTracking::NameAndLocation( static_cast&lt;std::string&gt;(generatorName), lineInfo ) );
        m_lastAssertionInfo.lineInfo = lineInfo;
        return tracker;
    }

    bool RunContext::testForMissingAssertions(Counts&amp; assertions) {
        if (assertions.total() != 0)
            return false;
        if (!m_config-&gt;warnAboutMissingAssertions())
            return false;
        if (m_trackerContext.currentTracker().hasChildren())
            return false;
        m_totals.assertions.failed++;
        assertions.failed++;
        return true;
    }

    void RunContext::sectionEnded(SectionEndInfo const &amp; endInfo) {
        Counts assertions = m_totals.assertions - endInfo.prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);

        if (!m_activeSections.empty()) {
            m_activeSections.back()-&gt;close();
            m_activeSections.pop_back();
        }

        m_reporter-&gt;sectionEnded(SectionStats(endInfo.sectionInfo, assertions, endInfo.durationInSeconds, missingAssertions));
        m_messages.clear();
        m_messageScopes.clear();
    }

    void RunContext::sectionEndedEarly(SectionEndInfo const &amp; endInfo) {
        if (m_unfinishedSections.empty())
            m_activeSections.back()-&gt;fail();
        else
            m_activeSections.back()-&gt;close();
        m_activeSections.pop_back();

        m_unfinishedSections.push_back(endInfo);
    }

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    void RunContext::benchmarkPreparing(std::string const&amp; name) {
        m_reporter-&gt;benchmarkPreparing(name);
    }
    void RunContext::benchmarkStarting( BenchmarkInfo const&amp; info ) {
        m_reporter-&gt;benchmarkStarting( info );
    }
    void RunContext::benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; stats ) {
        m_reporter-&gt;benchmarkEnded( stats );
    }
    void RunContext::benchmarkFailed(std::string const &amp; error) {
        m_reporter-&gt;benchmarkFailed(error);
    }
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    void RunContext::pushScopedMessage(MessageInfo const &amp; message) {
        m_messages.push_back(message);
    }

    void RunContext::popScopedMessage(MessageInfo const &amp; message) {
        m_messages.erase(std::remove(m_messages.begin(), m_messages.end(), message), m_messages.end());
    }

    void RunContext::emplaceUnscopedMessage( MessageBuilder const&amp; builder ) {
        m_messageScopes.emplace_back( builder );
    }

    std::string RunContext::getCurrentTestName() const {
        return m_activeTestCase
            ? m_activeTestCase-&gt;getTestCaseInfo().name
            : std::string();
    }

    const AssertionResult * RunContext::getLastResult() const {
        return &amp;(*m_lastResult);
    }

    void RunContext::exceptionEarlyReported() {
        m_shouldReportUnexpected = false;
    }

    void RunContext::handleFatalErrorCondition( StringRef message ) {
        // First notify reporter that bad things happened
        m_reporter-&gt;fatalErrorEncountered(message);

        // Don't rebuild the result -- the stringification itself can cause more fatal errors
        // Instead, fake a result data.
        AssertionResultData tempResult( ResultWas::FatalErrorCondition, { false } );
        tempResult.message = static_cast&lt;std::string&gt;(message);
        AssertionResult result(m_lastAssertionInfo, tempResult);

        assertionEnded(result);

        handleUnfinishedSections();

        // Recreate section for test case (as we will lose the one that was in scope)
        auto const&amp; testCaseInfo = m_activeTestCase-&gt;getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name);

        Counts assertions;
        assertions.failed = 1;
        SectionStats testCaseSectionStats(testCaseSection, assertions, 0, false);
        m_reporter-&gt;sectionEnded(testCaseSectionStats);

        auto const&amp; testInfo = m_activeTestCase-&gt;getTestCaseInfo();

        Totals deltaTotals;
        deltaTotals.testCases.failed = 1;
        deltaTotals.assertions.failed = 1;
        m_reporter-&gt;testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  std::string(),
                                  std::string(),
                                  false));
        m_totals.testCases.failed++;
        testGroupEnded(std::string(), m_totals, 1, 1);
        m_reporter-&gt;testRunEnded(TestRunStats(m_runInfo, m_totals, false));
    }

    bool RunContext::lastAssertionPassed() {
         return m_lastAssertionPassed;
    }

    void RunContext::assertionPassed() {
        m_lastAssertionPassed = true;
        ++m_totals.assertions.passed;
        resetAssertionInfo();
        m_messageScopes.clear();
    }

    bool RunContext::aborting() const {
        return m_totals.assertions.failed &gt;= static_cast&lt;std::size_t&gt;(m_config-&gt;abortAfter());
    }

    void RunContext::runCurrentTest(std::string &amp; redirectedCout, std::string &amp; redirectedCerr) {
        auto const&amp; testCaseInfo = m_activeTestCase-&gt;getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name);
        m_reporter-&gt;sectionStarting(testCaseSection);
        Counts prevAssertions = m_totals.assertions;
        double duration = 0;
        m_shouldReportUnexpected = true;
        m_lastAssertionInfo = { "TEST_CASE"_sr, testCaseInfo.lineInfo, StringRef(), ResultDisposition::Normal };

        seedRng(*m_config);

        Timer timer;
        CATCH_TRY {
            if (m_reporter-&gt;getPreferences().shouldRedirectStdOut) {
#if !defined(CATCH_CONFIG_EXPERIMENTAL_REDIRECT)
                RedirectedStreams redirectedStreams(redirectedCout, redirectedCerr);

                timer.start();
                invokeActiveTestCase();
#else
                OutputRedirect r(redirectedCout, redirectedCerr);
                timer.start();
                invokeActiveTestCase();
#endif
            } else {
                timer.start();
                invokeActiveTestCase();
            }
            duration = timer.getElapsedSeconds();
        } CATCH_CATCH_ANON (TestFailureException&amp;) {
            // This just means the test was aborted due to failure
        } CATCH_CATCH_ALL {
            // Under CATCH_CONFIG_FAST_COMPILE, unexpected exceptions under REQUIRE assertions
            // are reported without translation at the point of origin.
            if( m_shouldReportUnexpected ) {
                AssertionReaction dummyReaction;
                handleUnexpectedInflightException( m_lastAssertionInfo, translateActiveException(), dummyReaction );
            }
        }
        Counts assertions = m_totals.assertions - prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);

        m_testCaseTracker-&gt;close();
        handleUnfinishedSections();
        m_messages.clear();
        m_messageScopes.clear();

        SectionStats testCaseSectionStats(testCaseSection, assertions, duration, missingAssertions);
        m_reporter-&gt;sectionEnded(testCaseSectionStats);
    }

    void RunContext::invokeActiveTestCase() {
        FatalConditionHandler fatalConditionHandler; // Handle signals
        m_activeTestCase-&gt;invoke();
        fatalConditionHandler.reset();
    }

    void RunContext::handleUnfinishedSections() {
        // If sections ended prematurely due to an exception we stored their
        // infos here so we can tear them down outside the unwind process.
        for (auto it = m_unfinishedSections.rbegin(),
             itEnd = m_unfinishedSections.rend();
             it != itEnd;
             ++it)
            sectionEnded(*it);
        m_unfinishedSections.clear();
    }

    void RunContext::handleExpr(
        AssertionInfo const&amp; info,
        ITransientExpression const&amp; expr,
        AssertionReaction&amp; reaction
    ) {
        m_reporter-&gt;assertionStarting( info );

        bool negated = isFalseTest( info.resultDisposition );
        bool result = expr.getResult() != negated;

        if( result ) {
            if (!m_includeSuccessfulResults) {
                assertionPassed();
            }
            else {
                reportExpr(info, ResultWas::Ok, &amp;expr, negated);
            }
        }
        else {
            reportExpr(info, ResultWas::ExpressionFailed, &amp;expr, negated );
            populateReaction( reaction );
        }
    }
    void RunContext::reportExpr(
            AssertionInfo const &amp;info,
            ResultWas::OfType resultType,
            ITransientExpression const *expr,
            bool negated ) {

        m_lastAssertionInfo = info;
        AssertionResultData data( resultType, LazyExpression( negated ) );

        AssertionResult assertionResult{ info, data };
        assertionResult.m_resultData.lazyExpression.m_transientExpression = expr;

        assertionEnded( assertionResult );
    }

    void RunContext::handleMessage(
            AssertionInfo const&amp; info,
            ResultWas::OfType resultType,
            StringRef const&amp; message,
            AssertionReaction&amp; reaction
    ) {
        m_reporter-&gt;assertionStarting( info );

        m_lastAssertionInfo = info;

        AssertionResultData data( resultType, LazyExpression( false ) );
        data.message = static_cast&lt;std::string&gt;(message);
        AssertionResult assertionResult{ m_lastAssertionInfo, data };
        assertionEnded( assertionResult );
        if( !assertionResult.isOk() )
            populateReaction( reaction );
    }
    void RunContext::handleUnexpectedExceptionNotThrown(
            AssertionInfo const&amp; info,
            AssertionReaction&amp; reaction
    ) {
        handleNonExpr(info, Catch::ResultWas::DidntThrowException, reaction);
    }

    void RunContext::handleUnexpectedInflightException(
            AssertionInfo const&amp; info,
            std::string const&amp; message,
            AssertionReaction&amp; reaction
    ) {
        m_lastAssertionInfo = info;

        AssertionResultData data( ResultWas::ThrewException, LazyExpression( false ) );
        data.message = message;
        AssertionResult assertionResult{ info, data };
        assertionEnded( assertionResult );
        populateReaction( reaction );
    }

    void RunContext::populateReaction( AssertionReaction&amp; reaction ) {
        reaction.shouldDebugBreak = m_config-&gt;shouldDebugBreak();
        reaction.shouldThrow = aborting() || (m_lastAssertionInfo.resultDisposition &amp; ResultDisposition::Normal);
    }

    void RunContext::handleIncomplete(
            AssertionInfo const&amp; info
    ) {
        m_lastAssertionInfo = info;

        AssertionResultData data( ResultWas::ThrewException, LazyExpression( false ) );
        data.message = "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE";
        AssertionResult assertionResult{ info, data };
        assertionEnded( assertionResult );
    }
    void RunContext::handleNonExpr(
            AssertionInfo const &amp;info,
            ResultWas::OfType resultType,
            AssertionReaction &amp;reaction
    ) {
        m_lastAssertionInfo = info;

        AssertionResultData data( resultType, LazyExpression( false ) );
        AssertionResult assertionResult{ info, data };
        assertionEnded( assertionResult );

        if( !assertionResult.isOk() )
            populateReaction( reaction );
    }

    IResultCapture&amp; getResultCapture() {
        if (auto* capture = getCurrentContext().getResultCapture())
            return *capture;
        else
            CATCH_INTERNAL_ERROR("No result capture instance");
    }

    void seedRng(IConfig const&amp; config) {
        if (config.rngSeed() != 0) {
            std::srand(config.rngSeed());
            rng().seed(config.rngSeed());
        }
    }

    unsigned int rngSeed() {
        return getCurrentContext().getConfig()-&gt;rngSeed();
    }

}
// end catch_run_context.cpp
// start catch_section.cpp

namespace Catch {

    Section::Section( SectionInfo const&amp; info )
    :   m_info( info ),
        m_sectionIncluded( getResultCapture().sectionStarted( m_info, m_assertions ) )
    {
        m_timer.start();
    }

    Section::~Section() {
        if( m_sectionIncluded ) {
            SectionEndInfo endInfo{ m_info, m_assertions, m_timer.getElapsedSeconds() };
            if( uncaught_exceptions() )
                getResultCapture().sectionEndedEarly( endInfo );
            else
                getResultCapture().sectionEnded( endInfo );
        }
    }

    // This indicates whether the section should be executed or not
    Section::operator bool() const {
        return m_sectionIncluded;
    }

} // end namespace Catch
// end catch_section.cpp
// start catch_section_info.cpp

namespace Catch {

    SectionInfo::SectionInfo
        (   SourceLineInfo const&amp; _lineInfo,
            std::string const&amp; _name )
    :   name( _name ),
        lineInfo( _lineInfo )
    {}

} // end namespace Catch
// end catch_section_info.cpp
// start catch_session.cpp

// start catch_session.h

#include &lt;memory&gt;

namespace Catch {

    class Session : NonCopyable {
    public:

        Session();
        ~Session() override;

        void showHelp() const;
        void libIdentify();

        int applyCommandLine( int argc, char const * const * argv );
    #if defined(CATCH_CONFIG_WCHAR) &amp;&amp; defined(_WIN32) &amp;&amp; defined(UNICODE)
        int applyCommandLine( int argc, wchar_t const * const * argv );
    #endif

        void useConfigData( ConfigData const&amp; configData );

        template&lt;typename CharT&gt;
        int run(int argc, CharT const * const argv[]) {
            if (m_startupExceptions)
                return 1;
            int returnCode = applyCommandLine(argc, argv);
            if (returnCode == 0)
                returnCode = run();
            return returnCode;
        }

        int run();

        clara::Parser const&amp; cli() const;
        void cli( clara::Parser const&amp; newParser );
        ConfigData&amp; configData();
        Config&amp; config();
    private:
        int runInternal();

        clara::Parser m_cli;
        ConfigData m_configData;
        std::shared_ptr&lt;Config&gt; m_config;
        bool m_startupExceptions = false;
    };

} // end namespace Catch

// end catch_session.h
// start catch_version.h

#include &lt;iosfwd&gt;

namespace Catch {

    // Versioning information
    struct Version {
        Version( Version const&amp; ) = delete;
        Version&amp; operator=( Version const&amp; ) = delete;
        Version(    unsigned int _majorVersion,
                    unsigned int _minorVersion,
                    unsigned int _patchNumber,
                    char const * const _branchName,
                    unsigned int _buildNumber );

        unsigned int const majorVersion;
        unsigned int const minorVersion;
        unsigned int const patchNumber;

        // buildNumber is only used if branchName is not null
        char const * const branchName;
        unsigned int const buildNumber;

        friend std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Version const&amp; version );
    };

    Version const&amp; libraryVersion();
}

// end catch_version.h
#include &lt;cstdlib&gt;
#include &lt;iomanip&gt;
#include &lt;set&gt;
#include &lt;iterator&gt;

namespace Catch {

    namespace {
        const int MaxExitCode = 255;

        IStreamingReporterPtr createReporter(std::string const&amp; reporterName, IConfigPtr const&amp; config) {
            auto reporter = Catch::getRegistryHub().getReporterRegistry().create(reporterName, config);
            CATCH_ENFORCE(reporter, "No reporter registered with name: '" &lt;&lt; reporterName &lt;&lt; "'");

            return reporter;
        }

        IStreamingReporterPtr makeReporter(std::shared_ptr&lt;Config&gt; const&amp; config) {
            if (Catch::getRegistryHub().getReporterRegistry().getListeners().empty()) {
                return createReporter(config-&gt;getReporterName(), config);
            }

            // On older platforms, returning std::unique_ptr&lt;ListeningReporter&gt;
            // when the return type is std::unique_ptr&lt;IStreamingReporter&gt;
            // doesn't compile without a std::move call. However, this causes
            // a warning on newer platforms. Thus, we have to work around
            // it a bit and downcast the pointer manually.
            auto ret = std::unique_ptr&lt;IStreamingReporter&gt;(new ListeningReporter);
            auto&amp; multi = static_cast&lt;ListeningReporter&amp;&gt;(*ret);
            auto const&amp; listeners = Catch::getRegistryHub().getReporterRegistry().getListeners();
            for (auto const&amp; listener : listeners) {
                multi.addListener(listener-&gt;create(Catch::ReporterConfig(config)));
            }
            multi.addReporter(createReporter(config-&gt;getReporterName(), config));
            return ret;
        }

        class TestGroup {
        public:
            explicit TestGroup(std::shared_ptr&lt;Config&gt; const&amp; config)
            : m_config{config}
            , m_context{config, makeReporter(config)}
            {
                auto const&amp; allTestCases = getAllTestCasesSorted(*m_config);
                m_matches = m_config-&gt;testSpec().matchesByFilter(allTestCases, *m_config);
                auto const&amp; invalidArgs = m_config-&gt;testSpec().getInvalidArgs();

                if (m_matches.empty() &amp;&amp; invalidArgs.empty()) {
                    for (auto const&amp; test : allTestCases)
                        if (!test.isHidden())
                            m_tests.emplace(&amp;test);
                } else {
                    for (auto const&amp; match : m_matches)
                        m_tests.insert(match.tests.begin(), match.tests.end());
                }
            }

            Totals execute() {
                auto const&amp; invalidArgs = m_config-&gt;testSpec().getInvalidArgs();
                Totals totals;
                m_context.testGroupStarting(m_config-&gt;name(), 1, 1);
                for (auto const&amp; testCase : m_tests) {
                    if (!m_context.aborting())
                        totals += m_context.runTest(*testCase);
                    else
                        m_context.reporter().skipTest(*testCase);
                }

                for (auto const&amp; match : m_matches) {
                    if (match.tests.empty()) {
                        m_context.reporter().noMatchingTestCases(match.name);
                        totals.error = -1;
                    }
                }

                if (!invalidArgs.empty()) {
                    for (auto const&amp; invalidArg: invalidArgs)
                         m_context.reporter().reportInvalidArguments(invalidArg);
                }

                m_context.testGroupEnded(m_config-&gt;name(), totals, 1, 1);
                return totals;
            }

        private:
            using Tests = std::set&lt;TestCase const*&gt;;

            std::shared_ptr&lt;Config&gt; m_config;
            RunContext m_context;
            Tests m_tests;
            TestSpec::Matches m_matches;
        };

        void applyFilenamesAsTags(Catch::IConfig const&amp; config) {
            auto&amp; tests = const_cast&lt;std::vector&lt;TestCase&gt;&amp;&gt;(getAllTestCasesSorted(config));
            for (auto&amp; testCase : tests) {
                auto tags = testCase.tags;

                std::string filename = testCase.lineInfo.file;
                auto lastSlash = filename.find_last_of("\\/");
                if (lastSlash != std::string::npos) {
                    filename.erase(0, lastSlash);
                    filename[0] = '#';
                }

                auto lastDot = filename.find_last_of('.');
                if (lastDot != std::string::npos) {
                    filename.erase(lastDot);
                }

                tags.push_back(std::move(filename));
                setTags(testCase, tags);
            }
        }

    } // anon namespace

    Session::Session() {
        static bool alreadyInstantiated = false;
        if( alreadyInstantiated ) {
            CATCH_TRY { CATCH_INTERNAL_ERROR( "Only one instance of Catch::Session can ever be used" ); }
            CATCH_CATCH_ALL { getMutableRegistryHub().registerStartupException(); }
        }

        // There cannot be exceptions at startup in no-exception mode.
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
        const auto&amp; exceptions = getRegistryHub().getStartupExceptionRegistry().getExceptions();
        if ( !exceptions.empty() ) {
            config();
            getCurrentMutableContext().setConfig(m_config);

            m_startupExceptions = true;
            Colour colourGuard( Colour::Red );
            Catch::cerr() &lt;&lt; "Errors occurred during startup!" &lt;&lt; '\n';
            // iterate over all exceptions and notify user
            for ( const auto&amp; ex_ptr : exceptions ) {
                try {
                    std::rethrow_exception(ex_ptr);
                } catch ( std::exception const&amp; ex ) {
                    Catch::cerr() &lt;&lt; Column( ex.what() ).indent(2) &lt;&lt; '\n';
                }
            }
        }
#endif

        alreadyInstantiated = true;
        m_cli = makeCommandLineParser( m_configData );
    }
    Session::~Session() {
        Catch::cleanUp();
    }

    void Session::showHelp() const {
        Catch::cout()
                &lt;&lt; "\nCatch v" &lt;&lt; libraryVersion() &lt;&lt; "\n"
                &lt;&lt; m_cli &lt;&lt; std::endl
                &lt;&lt; "For more detailed usage please see the project docs\n" &lt;&lt; std::endl;
    }
    void Session::libIdentify() {
        Catch::cout()
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "description: " &lt;&lt; "A Catch2 test executable\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "category: " &lt;&lt; "testframework\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "framework: " &lt;&lt; "Catch Test\n"
                &lt;&lt; std::left &lt;&lt; std::setw(16) &lt;&lt; "version: " &lt;&lt; libraryVersion() &lt;&lt; std::endl;
    }

    int Session::applyCommandLine( int argc, char const * const * argv ) {
        if( m_startupExceptions )
            return 1;

        auto result = m_cli.parse( clara::Args( argc, argv ) );
        if( !result ) {
            config();
            getCurrentMutableContext().setConfig(m_config);
            Catch::cerr()
                &lt;&lt; Colour( Colour::Red )
                &lt;&lt; "\nError(s) in input:\n"
                &lt;&lt; Column( result.errorMessage() ).indent( 2 )
                &lt;&lt; "\n\n";
            Catch::cerr() &lt;&lt; "Run with -? for usage\n" &lt;&lt; std::endl;
            return MaxExitCode;
        }

        if( m_configData.showHelp )
            showHelp();
        if( m_configData.libIdentify )
            libIdentify();
        m_config.reset();
        return 0;
    }

#if defined(CATCH_CONFIG_WCHAR) &amp;&amp; defined(_WIN32) &amp;&amp; defined(UNICODE)
    int Session::applyCommandLine( int argc, wchar_t const * const * argv ) {

        char **utf8Argv = new char *[ argc ];

        for ( int i = 0; i &lt; argc; ++i ) {
            int bufSize = WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, nullptr, 0, nullptr, nullptr );

            utf8Argv[ i ] = new char[ bufSize ];

            WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, utf8Argv[i], bufSize, nullptr, nullptr );
        }

        int returnCode = applyCommandLine( argc, utf8Argv );

        for ( int i = 0; i &lt; argc; ++i )
            delete [] utf8Argv[ i ];

        delete [] utf8Argv;

        return returnCode;
    }
#endif

    void Session::useConfigData( ConfigData const&amp; configData ) {
        m_configData = configData;
        m_config.reset();
    }

    int Session::run() {
        if( ( m_configData.waitForKeypress &amp; WaitForKeypress::BeforeStart ) != 0 ) {
            Catch::cout() &lt;&lt; "...waiting for enter/ return before starting" &lt;&lt; std::endl;
            static_cast&lt;void&gt;(std::getchar());
        }
        int exitCode = runInternal();
        if( ( m_configData.waitForKeypress &amp; WaitForKeypress::BeforeExit ) != 0 ) {
            Catch::cout() &lt;&lt; "...waiting for enter/ return before exiting, with code: " &lt;&lt; exitCode &lt;&lt; std::endl;
            static_cast&lt;void&gt;(std::getchar());
        }
        return exitCode;
    }

    clara::Parser const&amp; Session::cli() const {
        return m_cli;
    }
    void Session::cli( clara::Parser const&amp; newParser ) {
        m_cli = newParser;
    }
    ConfigData&amp; Session::configData() {
        return m_configData;
    }
    Config&amp; Session::config() {
        if( !m_config )
            m_config = std::make_shared&lt;Config&gt;( m_configData );
        return *m_config;
    }

    int Session::runInternal() {
        if( m_startupExceptions )
            return 1;

        if (m_configData.showHelp || m_configData.libIdentify) {
            return 0;
        }

        CATCH_TRY {
            config(); // Force config to be constructed

            seedRng( *m_config );

            if( m_configData.filenamesAsTags )
                applyFilenamesAsTags( *m_config );

            // Handle list request
            if( Option&lt;std::size_t&gt; listed = list( m_config ) )
                return static_cast&lt;int&gt;( *listed );

            TestGroup tests { m_config };
            auto const totals = tests.execute();

            if( m_config-&gt;warnAboutNoTests() &amp;&amp; totals.error == -1 )
                return 2;

            // Note that on unices only the lower 8 bits are usually used, clamping
            // the return value to 255 prevents false negative when some multiple
            // of 256 tests has failed
            return (std::min) (MaxExitCode, (std::max) (totals.error, static_cast&lt;int&gt;(totals.assertions.failed)));
        }
#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
        catch( std::exception&amp; ex ) {
            Catch::cerr() &lt;&lt; ex.what() &lt;&lt; std::endl;
            return MaxExitCode;
        }
#endif
    }

} // end namespace Catch
// end catch_session.cpp
// start catch_singletons.cpp

#include &lt;vector&gt;

namespace Catch {

    namespace {
        static auto getSingletons() -&gt; std::vector&lt;ISingleton*&gt;*&amp; {
            static std::vector&lt;ISingleton*&gt;* g_singletons = nullptr;
            if( !g_singletons )
                g_singletons = new std::vector&lt;ISingleton*&gt;();
            return g_singletons;
        }
    }

    ISingleton::~ISingleton() {}

    void addSingleton(ISingleton* singleton ) {
        getSingletons()-&gt;push_back( singleton );
    }
    void cleanupSingletons() {
        auto&amp; singletons = getSingletons();
        for( auto singleton : *singletons )
            delete singleton;
        delete singletons;
        singletons = nullptr;
    }

} // namespace Catch
// end catch_singletons.cpp
// start catch_startup_exception_registry.cpp

#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
namespace Catch {
void StartupExceptionRegistry::add( std::exception_ptr const&amp; exception ) noexcept {
        CATCH_TRY {
            m_exceptions.push_back(exception);
        } CATCH_CATCH_ALL {
            // If we run out of memory during start-up there's really not a lot more we can do about it
            std::terminate();
        }
    }

    std::vector&lt;std::exception_ptr&gt; const&amp; StartupExceptionRegistry::getExceptions() const noexcept {
        return m_exceptions;
    }

} // end namespace Catch
#endif
// end catch_startup_exception_registry.cpp
// start catch_stream.cpp

#include &lt;cstdio&gt;
#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;sstream&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    Catch::IStream::~IStream() = default;

    namespace Detail { namespace {
        template&lt;typename WriterF, std::size_t bufferSize=256&gt;
        class StreamBufImpl : public std::streambuf {
            char data[bufferSize];
            WriterF m_writer;

        public:
            StreamBufImpl() {
                setp( data, data + sizeof(data) );
            }

            ~StreamBufImpl() noexcept {
                StreamBufImpl::sync();
            }

        private:
            int overflow( int c ) override {
                sync();

                if( c != EOF ) {
                    if( pbase() == epptr() )
                        m_writer( std::string( 1, static_cast&lt;char&gt;( c ) ) );
                    else
                        sputc( static_cast&lt;char&gt;( c ) );
                }
                return 0;
            }

            int sync() override {
                if( pbase() != pptr() ) {
                    m_writer( std::string( pbase(), static_cast&lt;std::string::size_type&gt;( pptr() - pbase() ) ) );
                    setp( pbase(), epptr() );
                }
                return 0;
            }
        };

        ///////////////////////////////////////////////////////////////////////////

        struct OutputDebugWriter {

            void operator()( std::string const&amp;str ) {
                writeToDebugConsole( str );
            }
        };

        ///////////////////////////////////////////////////////////////////////////

        class FileStream : public IStream {
            mutable std::ofstream m_ofs;
        public:
            FileStream( StringRef filename ) {
                m_ofs.open( filename.c_str() );
                CATCH_ENFORCE( !m_ofs.fail(), "Unable to open file: '" &lt;&lt; filename &lt;&lt; "'" );
            }
            ~FileStream() override = default;
        public: // IStream
            std::ostream&amp; stream() const override {
                return m_ofs;
            }
        };

        ///////////////////////////////////////////////////////////////////////////

        class CoutStream : public IStream {
            mutable std::ostream m_os;
        public:
            // Store the streambuf from cout up-front because
            // cout may get redirected when running tests
            CoutStream() : m_os( Catch::cout().rdbuf() ) {}
            ~CoutStream() override = default;

        public: // IStream
            std::ostream&amp; stream() const override { return m_os; }
        };

        ///////////////////////////////////////////////////////////////////////////

        class DebugOutStream : public IStream {
            std::unique_ptr&lt;StreamBufImpl&lt;OutputDebugWriter&gt;&gt; m_streamBuf;
            mutable std::ostream m_os;
        public:
            DebugOutStream()
            :   m_streamBuf( new StreamBufImpl&lt;OutputDebugWriter&gt;() ),
                m_os( m_streamBuf.get() )
            {}

            ~DebugOutStream() override = default;

        public: // IStream
            std::ostream&amp; stream() const override { return m_os; }
        };

    }} // namespace anon::detail

    ///////////////////////////////////////////////////////////////////////////

    auto makeStream( StringRef const &amp;filename ) -&gt; IStream const* {
        if( filename.empty() )
            return new Detail::CoutStream();
        else if( filename[0] == '%' ) {
            if( filename == "%debug" )
                return new Detail::DebugOutStream();
            else
                CATCH_ERROR( "Unrecognised stream: '" &lt;&lt; filename &lt;&lt; "'" );
        }
        else
            return new Detail::FileStream( filename );
    }

    // This class encapsulates the idea of a pool of ostringstreams that can be reused.
    struct StringStreams {
        std::vector&lt;std::unique_ptr&lt;std::ostringstream&gt;&gt; m_streams;
        std::vector&lt;std::size_t&gt; m_unused;
        std::ostringstream m_referenceStream; // Used for copy state/ flags from

        auto add() -&gt; std::size_t {
            if( m_unused.empty() ) {
                m_streams.push_back( std::unique_ptr&lt;std::ostringstream&gt;( new std::ostringstream ) );
                return m_streams.size()-1;
            }
            else {
                auto index = m_unused.back();
                m_unused.pop_back();
                return index;
            }
        }

        void release( std::size_t index ) {
            m_streams[index]-&gt;copyfmt( m_referenceStream ); // Restore initial flags and other state
            m_unused.push_back(index);
        }
    };

    ReusableStringStream::ReusableStringStream()
    :   m_index( Singleton&lt;StringStreams&gt;::getMutable().add() ),
        m_oss( Singleton&lt;StringStreams&gt;::getMutable().m_streams[m_index].get() )
    {}

    ReusableStringStream::~ReusableStringStream() {
        static_cast&lt;std::ostringstream*&gt;( m_oss )-&gt;str("");
        m_oss-&gt;clear();
        Singleton&lt;StringStreams&gt;::getMutable().release( m_index );
    }

    auto ReusableStringStream::str() const -&gt; std::string {
        return static_cast&lt;std::ostringstream*&gt;( m_oss )-&gt;str();
    }

    ///////////////////////////////////////////////////////////////////////////

#ifndef CATCH_CONFIG_NOSTDOUT // If you #define this you must implement these functions
    std::ostream&amp; cout() { return std::cout; }
    std::ostream&amp; cerr() { return std::cerr; }
    std::ostream&amp; clog() { return std::clog; }
#endif
}
// end catch_stream.cpp
// start catch_string_manip.cpp

#include &lt;algorithm&gt;
#include &lt;ostream&gt;
#include &lt;cstring&gt;
#include &lt;cctype&gt;
#include &lt;vector&gt;

namespace Catch {

    namespace {
        char toLowerCh(char c) {
            return static_cast&lt;char&gt;( std::tolower( static_cast&lt;unsigned char&gt;(c) ) );
        }
    }

    bool startsWith( std::string const&amp; s, std::string const&amp; prefix ) {
        return s.size() &gt;= prefix.size() &amp;&amp; std::equal(prefix.begin(), prefix.end(), s.begin());
    }
    bool startsWith( std::string const&amp; s, char prefix ) {
        return !s.empty() &amp;&amp; s[0] == prefix;
    }
    bool endsWith( std::string const&amp; s, std::string const&amp; suffix ) {
        return s.size() &gt;= suffix.size() &amp;&amp; std::equal(suffix.rbegin(), suffix.rend(), s.rbegin());
    }
    bool endsWith( std::string const&amp; s, char suffix ) {
        return !s.empty() &amp;&amp; s[s.size()-1] == suffix;
    }
    bool contains( std::string const&amp; s, std::string const&amp; infix ) {
        return s.find( infix ) != std::string::npos;
    }
    void toLowerInPlace( std::string&amp; s ) {
        std::transform( s.begin(), s.end(), s.begin(), toLowerCh );
    }
    std::string toLower( std::string const&amp; s ) {
        std::string lc = s;
        toLowerInPlace( lc );
        return lc;
    }
    std::string trim( std::string const&amp; str ) {
        static char const* whitespaceChars = "\n\r\t ";
        std::string::size_type start = str.find_first_not_of( whitespaceChars );
        std::string::size_type end = str.find_last_not_of( whitespaceChars );

        return start != std::string::npos ? str.substr( start, 1+end-start ) : std::string();
    }

    StringRef trim(StringRef ref) {
        const auto is_ws = [](char c) {
            return c == ' ' || c == '\t' || c == '\n' || c == '\r';
        };
        size_t real_begin = 0;
        while (real_begin &lt; ref.size() &amp;&amp; is_ws(ref[real_begin])) { ++real_begin; }
        size_t real_end = ref.size();
        while (real_end &gt; real_begin &amp;&amp; is_ws(ref[real_end - 1])) { --real_end; }

        return ref.substr(real_begin, real_end - real_begin);
    }

    bool replaceInPlace( std::string&amp; str, std::string const&amp; replaceThis, std::string const&amp; withThis ) {
        bool replaced = false;
        std::size_t i = str.find( replaceThis );
        while( i != std::string::npos ) {
            replaced = true;
            str = str.substr( 0, i ) + withThis + str.substr( i+replaceThis.size() );
            if( i &lt; str.size()-withThis.size() )
                i = str.find( replaceThis, i+withThis.size() );
            else
                i = std::string::npos;
        }
        return replaced;
    }

    std::vector&lt;StringRef&gt; splitStringRef( StringRef str, char delimiter ) {
        std::vector&lt;StringRef&gt; subStrings;
        std::size_t start = 0;
        for(std::size_t pos = 0; pos &lt; str.size(); ++pos ) {
            if( str[pos] == delimiter ) {
                if( pos - start &gt; 1 )
                    subStrings.push_back( str.substr( start, pos-start ) );
                start = pos+1;
            }
        }
        if( start &lt; str.size() )
            subStrings.push_back( str.substr( start, str.size()-start ) );
        return subStrings;
    }

    pluralise::pluralise( std::size_t count, std::string const&amp; label )
    :   m_count( count ),
        m_label( label )
    {}

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, pluralise const&amp; pluraliser ) {
        os &lt;&lt; pluraliser.m_count &lt;&lt; ' ' &lt;&lt; pluraliser.m_label;
        if( pluraliser.m_count != 1 )
            os &lt;&lt; 's';
        return os;
    }

}
// end catch_string_manip.cpp
// start catch_stringref.cpp

#include &lt;algorithm&gt;
#include &lt;ostream&gt;
#include &lt;cstring&gt;
#include &lt;cstdint&gt;

namespace Catch {
    StringRef::StringRef( char const* rawChars ) noexcept
    : StringRef( rawChars, static_cast&lt;StringRef::size_type&gt;(std::strlen(rawChars) ) )
    {}

    auto StringRef::c_str() const -&gt; char const* {
        CATCH_ENFORCE(isNullTerminated(), "Called StringRef::c_str() on a non-null-terminated instance");
        return m_start;
    }
    auto StringRef::data() const noexcept -&gt; char const* {
        return m_start;
    }

    auto StringRef::substr( size_type start, size_type size ) const noexcept -&gt; StringRef {
        if (start &lt; m_size) {
            return StringRef(m_start + start, (std::min)(m_size - start, size));
        } else {
            return StringRef();
        }
    }
    auto StringRef::operator == ( StringRef const&amp; other ) const noexcept -&gt; bool {
        return m_size == other.m_size
            &amp;&amp; (std::memcmp( m_start, other.m_start, m_size ) == 0);
    }

    auto operator &lt;&lt; ( std::ostream&amp; os, StringRef const&amp; str ) -&gt; std::ostream&amp; {
        return os.write(str.data(), str.size());
    }

    auto operator+=( std::string&amp; lhs, StringRef const&amp; rhs ) -&gt; std::string&amp; {
        lhs.append(rhs.data(), rhs.size());
        return lhs;
    }

} // namespace Catch
// end catch_stringref.cpp
// start catch_tag_alias.cpp

namespace Catch {
    TagAlias::TagAlias(std::string const &amp; _tag, SourceLineInfo _lineInfo): tag(_tag), lineInfo(_lineInfo) {}
}
// end catch_tag_alias.cpp
// start catch_tag_alias_autoregistrar.cpp

namespace Catch {

    RegistrarForTagAliases::RegistrarForTagAliases(char const* alias, char const* tag, SourceLineInfo const&amp; lineInfo) {
        CATCH_TRY {
            getMutableRegistryHub().registerTagAlias(alias, tag, lineInfo);
        } CATCH_CATCH_ALL {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }

}
// end catch_tag_alias_autoregistrar.cpp
// start catch_tag_alias_registry.cpp

#include &lt;sstream&gt;

namespace Catch {

    TagAliasRegistry::~TagAliasRegistry() {}

    TagAlias const* TagAliasRegistry::find( std::string const&amp; alias ) const {
        auto it = m_registry.find( alias );
        if( it != m_registry.end() )
            return &amp;(it-&gt;second);
        else
            return nullptr;
    }

    std::string TagAliasRegistry::expandAliases( std::string const&amp; unexpandedTestSpec ) const {
        std::string expandedTestSpec = unexpandedTestSpec;
        for( auto const&amp; registryKvp : m_registry ) {
            std::size_t pos = expandedTestSpec.find( registryKvp.first );
            if( pos != std::string::npos ) {
                expandedTestSpec =  expandedTestSpec.substr( 0, pos ) +
                                    registryKvp.second.tag +
                                    expandedTestSpec.substr( pos + registryKvp.first.size() );
            }
        }
        return expandedTestSpec;
    }

    void TagAliasRegistry::add( std::string const&amp; alias, std::string const&amp; tag, SourceLineInfo const&amp; lineInfo ) {
        CATCH_ENFORCE( startsWith(alias, "[@") &amp;&amp; endsWith(alias, ']'),
                      "error: tag alias, '" &lt;&lt; alias &lt;&lt; "' is not of the form [@alias name].\n" &lt;&lt; lineInfo );

        CATCH_ENFORCE( m_registry.insert(std::make_pair(alias, TagAlias(tag, lineInfo))).second,
                      "error: tag alias, '" &lt;&lt; alias &lt;&lt; "' already registered.\n"
                      &lt;&lt; "\tFirst seen at: " &lt;&lt; find(alias)-&gt;lineInfo &lt;&lt; "\n"
                      &lt;&lt; "\tRedefined at: " &lt;&lt; lineInfo );
    }

    ITagAliasRegistry::~ITagAliasRegistry() {}

    ITagAliasRegistry const&amp; ITagAliasRegistry::get() {
        return getRegistryHub().getTagAliasRegistry();
    }

} // end namespace Catch
// end catch_tag_alias_registry.cpp
// start catch_test_case_info.cpp

#include &lt;cctype&gt;
#include &lt;exception&gt;
#include &lt;algorithm&gt;
#include &lt;sstream&gt;

namespace Catch {

    namespace {
        TestCaseInfo::SpecialProperties parseSpecialTag( std::string const&amp; tag ) {
            if( startsWith( tag, '.' ) ||
                tag == "!hide" )
                return TestCaseInfo::IsHidden;
            else if( tag == "!throws" )
                return TestCaseInfo::Throws;
            else if( tag == "!shouldfail" )
                return TestCaseInfo::ShouldFail;
            else if( tag == "!mayfail" )
                return TestCaseInfo::MayFail;
            else if( tag == "!nonportable" )
                return TestCaseInfo::NonPortable;
            else if( tag == "!benchmark" )
                return static_cast&lt;TestCaseInfo::SpecialProperties&gt;( TestCaseInfo::Benchmark | TestCaseInfo::IsHidden );
            else
                return TestCaseInfo::None;
        }
        bool isReservedTag( std::string const&amp; tag ) {
            return parseSpecialTag( tag ) == TestCaseInfo::None &amp;&amp; tag.size() &gt; 0 &amp;&amp; !std::isalnum( static_cast&lt;unsigned char&gt;(tag[0]) );
        }
        void enforceNotReservedTag( std::string const&amp; tag, SourceLineInfo const&amp; _lineInfo ) {
            CATCH_ENFORCE( !isReservedTag(tag),
                          "Tag name: [" &lt;&lt; tag &lt;&lt; "] is not allowed.\n"
                          &lt;&lt; "Tag names starting with non alphanumeric characters are reserved\n"
                          &lt;&lt; _lineInfo );
        }
    }

    TestCase makeTestCase(  ITestInvoker* _testCase,
                            std::string const&amp; _className,
                            NameAndTags const&amp; nameAndTags,
                            SourceLineInfo const&amp; _lineInfo )
    {
        bool isHidden = false;

        // Parse out tags
        std::vector&lt;std::string&gt; tags;
        std::string desc, tag;
        bool inTag = false;
        for (char c : nameAndTags.tags) {
            if( !inTag ) {
                if( c == '[' )
                    inTag = true;
                else
                    desc += c;
            }
            else {
                if( c == ']' ) {
                    TestCaseInfo::SpecialProperties prop = parseSpecialTag( tag );
                    if( ( prop &amp; TestCaseInfo::IsHidden ) != 0 )
                        isHidden = true;
                    else if( prop == TestCaseInfo::None )
                        enforceNotReservedTag( tag, _lineInfo );

                    // Merged hide tags like `[.approvals]` should be added as
                    // `[.][approvals]`. The `[.]` is added at later point, so
                    // we only strip the prefix
                    if (startsWith(tag, '.') &amp;&amp; tag.size() &gt; 1) {
                        tag.erase(0, 1);
                    }
                    tags.push_back( tag );
                    tag.clear();
                    inTag = false;
                }
                else
                    tag += c;
            }
        }
        if( isHidden ) {
            // Add all "hidden" tags to make them behave identically
            tags.insert( tags.end(), { ".", "!hide" } );
        }

        TestCaseInfo info( static_cast&lt;std::string&gt;(nameAndTags.name), _className, desc, tags, _lineInfo );
        return TestCase( _testCase, std::move(info) );
    }

    void setTags( TestCaseInfo&amp; testCaseInfo, std::vector&lt;std::string&gt; tags ) {
        std::sort(begin(tags), end(tags));
        tags.erase(std::unique(begin(tags), end(tags)), end(tags));
        testCaseInfo.lcaseTags.clear();

        for( auto const&amp; tag : tags ) {
            std::string lcaseTag = toLower( tag );
            testCaseInfo.properties = static_cast&lt;TestCaseInfo::SpecialProperties&gt;( testCaseInfo.properties | parseSpecialTag( lcaseTag ) );
            testCaseInfo.lcaseTags.push_back( lcaseTag );
        }
        testCaseInfo.tags = std::move(tags);
    }

    TestCaseInfo::TestCaseInfo( std::string const&amp; _name,
                                std::string const&amp; _className,
                                std::string const&amp; _description,
                                std::vector&lt;std::string&gt; const&amp; _tags,
                                SourceLineInfo const&amp; _lineInfo )
    :   name( _name ),
        className( _className ),
        description( _description ),
        lineInfo( _lineInfo ),
        properties( None )
    {
        setTags( *this, _tags );
    }

    bool TestCaseInfo::isHidden() const {
        return ( properties &amp; IsHidden ) != 0;
    }
    bool TestCaseInfo::throws() const {
        return ( properties &amp; Throws ) != 0;
    }
    bool TestCaseInfo::okToFail() const {
        return ( properties &amp; (ShouldFail | MayFail ) ) != 0;
    }
    bool TestCaseInfo::expectedToFail() const {
        return ( properties &amp; (ShouldFail ) ) != 0;
    }

    std::string TestCaseInfo::tagsAsString() const {
        std::string ret;
        // '[' and ']' per tag
        std::size_t full_size = 2 * tags.size();
        for (const auto&amp; tag : tags) {
            full_size += tag.size();
        }
        ret.reserve(full_size);
        for (const auto&amp; tag : tags) {
            ret.push_back('[');
            ret.append(tag);
            ret.push_back(']');
        }

        return ret;
    }

    TestCase::TestCase( ITestInvoker* testCase, TestCaseInfo&amp;&amp; info ) : TestCaseInfo( std::move(info) ), test( testCase ) {}

    TestCase TestCase::withName( std::string const&amp; _newName ) const {
        TestCase other( *this );
        other.name = _newName;
        return other;
    }

    void TestCase::invoke() const {
        test-&gt;invoke();
    }

    bool TestCase::operator == ( TestCase const&amp; other ) const {
        return  test.get() == other.test.get() &amp;&amp;
                name == other.name &amp;&amp;
                className == other.className;
    }

    bool TestCase::operator &lt; ( TestCase const&amp; other ) const {
        return name &lt; other.name;
    }

    TestCaseInfo const&amp; TestCase::getTestCaseInfo() const
    {
        return *this;
    }

} // end namespace Catch
// end catch_test_case_info.cpp
// start catch_test_case_registry_impl.cpp

#include &lt;algorithm&gt;
#include &lt;sstream&gt;

namespace Catch {

    namespace {
        struct TestHasher {
            explicit TestHasher(Catch::SimplePcg32&amp; rng_instance) {
                basis = rng_instance();
                basis &lt;&lt;= 32;
                basis |= rng_instance();
            }

            uint64_t basis;

            uint64_t operator()(TestCase const&amp; t) const {
                // Modified FNV-1a hash
                static constexpr uint64_t prime = 1099511628211;
                uint64_t hash = basis;
                for (const char c : t.name) {
                    hash ^= c;
                    hash *= prime;
                }
                return hash;
            }
        };
    } // end unnamed namespace

    std::vector&lt;TestCase&gt; sortTests( IConfig const&amp; config, std::vector&lt;TestCase&gt; const&amp; unsortedTestCases ) {
        switch( config.runOrder() ) {
            case RunTests::InDeclarationOrder:
                // already in declaration order
                break;

            case RunTests::InLexicographicalOrder: {
                std::vector&lt;TestCase&gt; sorted = unsortedTestCases;
                std::sort( sorted.begin(), sorted.end() );
                return sorted;
            }

            case RunTests::InRandomOrder: {
                seedRng( config );
                TestHasher h( rng() );

                using hashedTest = std::pair&lt;uint64_t, TestCase const*&gt;;
                std::vector&lt;hashedTest&gt; indexed_tests;
                indexed_tests.reserve( unsortedTestCases.size() );

                for (auto const&amp; testCase : unsortedTestCases) {
                    indexed_tests.emplace_back(h(testCase), &amp;testCase);
                }

                std::sort(indexed_tests.begin(), indexed_tests.end(),
                          [](hashedTest const&amp; lhs, hashedTest const&amp; rhs) {
                          if (lhs.first == rhs.first) {
                              return lhs.second-&gt;name &lt; rhs.second-&gt;name;
                          }
                          return lhs.first &lt; rhs.first;
                });

                std::vector&lt;TestCase&gt; sorted;
                sorted.reserve( indexed_tests.size() );

                for (auto const&amp; hashed : indexed_tests) {
                    sorted.emplace_back(*hashed.second);
                }

                return sorted;
            }
        }
        return unsortedTestCases;
    }

    bool isThrowSafe( TestCase const&amp; testCase, IConfig const&amp; config ) {
        return !testCase.throws() || config.allowThrows();
    }

    bool matchTest( TestCase const&amp; testCase, TestSpec const&amp; testSpec, IConfig const&amp; config ) {
        return testSpec.matches( testCase ) &amp;&amp; isThrowSafe( testCase, config );
    }

    void enforceNoDuplicateTestCases( std::vector&lt;TestCase&gt; const&amp; functions ) {
        std::set&lt;TestCase&gt; seenFunctions;
        for( auto const&amp; function : functions ) {
            auto prev = seenFunctions.insert( function );
            CATCH_ENFORCE( prev.second,
                    "error: TEST_CASE( \"" &lt;&lt; function.name &lt;&lt; "\" ) already defined.\n"
                    &lt;&lt; "\tFirst seen at " &lt;&lt; prev.first-&gt;getTestCaseInfo().lineInfo &lt;&lt; "\n"
                    &lt;&lt; "\tRedefined at " &lt;&lt; function.getTestCaseInfo().lineInfo );
        }
    }

    std::vector&lt;TestCase&gt; filterTests( std::vector&lt;TestCase&gt; const&amp; testCases, TestSpec const&amp; testSpec, IConfig const&amp; config ) {
        std::vector&lt;TestCase&gt; filtered;
        filtered.reserve( testCases.size() );
        for (auto const&amp; testCase : testCases) {
            if ((!testSpec.hasFilters() &amp;&amp; !testCase.isHidden()) ||
                (testSpec.hasFilters() &amp;&amp; matchTest(testCase, testSpec, config))) {
                filtered.push_back(testCase);
            }
        }
        return filtered;
    }
    std::vector&lt;TestCase&gt; const&amp; getAllTestCasesSorted( IConfig const&amp; config ) {
        return getRegistryHub().getTestCaseRegistry().getAllTestsSorted( config );
    }

    void TestRegistry::registerTest( TestCase const&amp; testCase ) {
        std::string name = testCase.getTestCaseInfo().name;
        if( name.empty() ) {
            ReusableStringStream rss;
            rss &lt;&lt; "Anonymous test case " &lt;&lt; ++m_unnamedCount;
            return registerTest( testCase.withName( rss.str() ) );
        }
        m_functions.push_back( testCase );
    }

    std::vector&lt;TestCase&gt; const&amp; TestRegistry::getAllTests() const {
        return m_functions;
    }
    std::vector&lt;TestCase&gt; const&amp; TestRegistry::getAllTestsSorted( IConfig const&amp; config ) const {
        if( m_sortedFunctions.empty() )
            enforceNoDuplicateTestCases( m_functions );

        if(  m_currentSortOrder != config.runOrder() || m_sortedFunctions.empty() ) {
            m_sortedFunctions = sortTests( config, m_functions );
            m_currentSortOrder = config.runOrder();
        }
        return m_sortedFunctions;
    }

    ///////////////////////////////////////////////////////////////////////////
    TestInvokerAsFunction::TestInvokerAsFunction( void(*testAsFunction)() ) noexcept : m_testAsFunction( testAsFunction ) {}

    void TestInvokerAsFunction::invoke() const {
        m_testAsFunction();
    }

    std::string extractClassName( StringRef const&amp; classOrQualifiedMethodName ) {
        std::string className(classOrQualifiedMethodName);
        if( startsWith( className, '&amp;' ) )
        {
            std::size_t lastColons = className.rfind( "::" );
            std::size_t penultimateColons = className.rfind( "::", lastColons-1 );
            if( penultimateColons == std::string::npos )
                penultimateColons = 1;
            className = className.substr( penultimateColons, lastColons-penultimateColons );
        }
        return className;
    }

} // end namespace Catch
// end catch_test_case_registry_impl.cpp
// start catch_test_case_tracker.cpp

#include &lt;algorithm&gt;
#include &lt;cassert&gt;
#include &lt;stdexcept&gt;
#include &lt;memory&gt;
#include &lt;sstream&gt;

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace Catch {
namespace TestCaseTracking {

    NameAndLocation::NameAndLocation( std::string const&amp; _name, SourceLineInfo const&amp; _location )
    :   name( _name ),
        location( _location )
    {}

    ITracker::~ITracker() = default;

    ITracker&amp; TrackerContext::startRun() {
        m_rootTracker = std::make_shared&lt;SectionTracker&gt;( NameAndLocation( "{root}", CATCH_INTERNAL_LINEINFO ), *this, nullptr );
        m_currentTracker = nullptr;
        m_runState = Executing;
        return *m_rootTracker;
    }

    void TrackerContext::endRun() {
        m_rootTracker.reset();
        m_currentTracker = nullptr;
        m_runState = NotStarted;
    }

    void TrackerContext::startCycle() {
        m_currentTracker = m_rootTracker.get();
        m_runState = Executing;
    }
    void TrackerContext::completeCycle() {
        m_runState = CompletedCycle;
    }

    bool TrackerContext::completedCycle() const {
        return m_runState == CompletedCycle;
    }
    ITracker&amp; TrackerContext::currentTracker() {
        return *m_currentTracker;
    }
    void TrackerContext::setCurrentTracker( ITracker* tracker ) {
        m_currentTracker = tracker;
    }

    TrackerBase::TrackerBase( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent ):
        ITracker(nameAndLocation),
        m_ctx( ctx ),
        m_parent( parent )
    {}

    bool TrackerBase::isComplete() const {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }
    bool TrackerBase::isSuccessfullyCompleted() const {
        return m_runState == CompletedSuccessfully;
    }
    bool TrackerBase::isOpen() const {
        return m_runState != NotStarted &amp;&amp; !isComplete();
    }
    bool TrackerBase::hasChildren() const {
        return !m_children.empty();
    }

    void TrackerBase::addChild( ITrackerPtr const&amp; child ) {
        m_children.push_back( child );
    }

    ITrackerPtr TrackerBase::findChild( NameAndLocation const&amp; nameAndLocation ) {
        auto it = std::find_if( m_children.begin(), m_children.end(),
            [&amp;nameAndLocation]( ITrackerPtr const&amp; tracker ){
                return
                    tracker-&gt;nameAndLocation().location == nameAndLocation.location &amp;&amp;
                    tracker-&gt;nameAndLocation().name == nameAndLocation.name;
            } );
        return( it != m_children.end() )
            ? *it
            : nullptr;
    }
    ITracker&amp; TrackerBase::parent() {
        assert( m_parent ); // Should always be non-null except for root
        return *m_parent;
    }

    void TrackerBase::openChild() {
        if( m_runState != ExecutingChildren ) {
            m_runState = ExecutingChildren;
            if( m_parent )
                m_parent-&gt;openChild();
        }
    }

    bool TrackerBase::isSectionTracker() const { return false; }
    bool TrackerBase::isGeneratorTracker() const { return false; }

    void TrackerBase::open() {
        m_runState = Executing;
        moveToThis();
        if( m_parent )
            m_parent-&gt;openChild();
    }

    void TrackerBase::close() {

        // Close any still open children (e.g. generators)
        while( &amp;m_ctx.currentTracker() != this )
            m_ctx.currentTracker().close();

        switch( m_runState ) {
            case NeedsAnotherRun:
                break;

            case Executing:
                m_runState = CompletedSuccessfully;
                break;
            case ExecutingChildren:
                if( std::all_of(m_children.begin(), m_children.end(), [](ITrackerPtr const&amp; t){ return t-&gt;isComplete(); }) )
                    m_runState = CompletedSuccessfully;
                break;

            case NotStarted:
            case CompletedSuccessfully:
            case Failed:
                CATCH_INTERNAL_ERROR( "Illogical state: " &lt;&lt; m_runState );

            default:
                CATCH_INTERNAL_ERROR( "Unknown state: " &lt;&lt; m_runState );
        }
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::fail() {
        m_runState = Failed;
        if( m_parent )
            m_parent-&gt;markAsNeedingAnotherRun();
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::markAsNeedingAnotherRun() {
        m_runState = NeedsAnotherRun;
    }

    void TrackerBase::moveToParent() {
        assert( m_parent );
        m_ctx.setCurrentTracker( m_parent );
    }
    void TrackerBase::moveToThis() {
        m_ctx.setCurrentTracker( this );
    }

    SectionTracker::SectionTracker( NameAndLocation const&amp; nameAndLocation, TrackerContext&amp; ctx, ITracker* parent )
    :   TrackerBase( nameAndLocation, ctx, parent ),
        m_trimmed_name(trim(nameAndLocation.name))
    {
        if( parent ) {
            while( !parent-&gt;isSectionTracker() )
                parent = &amp;parent-&gt;parent();

            SectionTracker&amp; parentSection = static_cast&lt;SectionTracker&amp;&gt;( *parent );
            addNextFilters( parentSection.m_filters );
        }
    }

    bool SectionTracker::isComplete() const {
        bool complete = true;

        if (m_filters.empty()
            || m_filters[0] == ""
            || std::find(m_filters.begin(), m_filters.end(), m_trimmed_name) != m_filters.end()) {
            complete = TrackerBase::isComplete();
        }
        return complete;
    }

    bool SectionTracker::isSectionTracker() const { return true; }

    SectionTracker&amp; SectionTracker::acquire( TrackerContext&amp; ctx, NameAndLocation const&amp; nameAndLocation ) {
        std::shared_ptr&lt;SectionTracker&gt; section;

        ITracker&amp; currentTracker = ctx.currentTracker();
        if( ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
            assert( childTracker );
            assert( childTracker-&gt;isSectionTracker() );
            section = std::static_pointer_cast&lt;SectionTracker&gt;( childTracker );
        }
        else {
            section = std::make_shared&lt;SectionTracker&gt;( nameAndLocation, ctx, &amp;currentTracker );
            currentTracker.addChild( section );
        }
        if( !ctx.completedCycle() )
            section-&gt;tryOpen();
        return *section;
    }

    void SectionTracker::tryOpen() {
        if( !isComplete() )
            open();
    }

    void SectionTracker::addInitialFilters( std::vector&lt;std::string&gt; const&amp; filters ) {
        if( !filters.empty() ) {
            m_filters.reserve( m_filters.size() + filters.size() + 2 );
            m_filters.emplace_back(""); // Root - should never be consulted
            m_filters.emplace_back(""); // Test Case - not a section filter
            m_filters.insert( m_filters.end(), filters.begin(), filters.end() );
        }
    }
    void SectionTracker::addNextFilters( std::vector&lt;std::string&gt; const&amp; filters ) {
        if( filters.size() &gt; 1 )
            m_filters.insert( m_filters.end(), filters.begin()+1, filters.end() );
    }

    std::vector&lt;std::string&gt; const&amp; SectionTracker::getFilters() const {
        return m_filters;
    }

    std::string const&amp; SectionTracker::trimmedName() const {
        return m_trimmed_name;
    }

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;

} // namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif
// end catch_test_case_tracker.cpp
// start catch_test_registry.cpp

namespace Catch {

    auto makeTestInvoker( void(*testAsFunction)() ) noexcept -&gt; ITestInvoker* {
        return new(std::nothrow) TestInvokerAsFunction( testAsFunction );
    }

    NameAndTags::NameAndTags( StringRef const&amp; name_ , StringRef const&amp; tags_ ) noexcept : name( name_ ), tags( tags_ ) {}

    AutoReg::AutoReg( ITestInvoker* invoker, SourceLineInfo const&amp; lineInfo, StringRef const&amp; classOrMethod, NameAndTags const&amp; nameAndTags ) noexcept {
        CATCH_TRY {
            getMutableRegistryHub()
                    .registerTest(
                        makeTestCase(
                            invoker,
                            extractClassName( classOrMethod ),
                            nameAndTags,
                            lineInfo));
        } CATCH_CATCH_ALL {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }

    AutoReg::~AutoReg() = default;
}
// end catch_test_registry.cpp
// start catch_test_spec.cpp

#include &lt;algorithm&gt;
#include &lt;string&gt;
#include &lt;vector&gt;
#include &lt;memory&gt;

namespace Catch {

    TestSpec::Pattern::Pattern( std::string const&amp; name )
    : m_name( name )
    {}

    TestSpec::Pattern::~Pattern() = default;

    std::string const&amp; TestSpec::Pattern::name() const {
        return m_name;
    }

    TestSpec::NamePattern::NamePattern( std::string const&amp; name, std::string const&amp; filterString )
    : Pattern( filterString )
    , m_wildcardPattern( toLower( name ), CaseSensitive::No )
    {}

    bool TestSpec::NamePattern::matches( TestCaseInfo const&amp; testCase ) const {
        return m_wildcardPattern.matches( testCase.name );
    }

    TestSpec::TagPattern::TagPattern( std::string const&amp; tag, std::string const&amp; filterString )
    : Pattern( filterString )
    , m_tag( toLower( tag ) )
    {}

    bool TestSpec::TagPattern::matches( TestCaseInfo const&amp; testCase ) const {
        return std::find(begin(testCase.lcaseTags),
                         end(testCase.lcaseTags),
                         m_tag) != end(testCase.lcaseTags);
    }

    TestSpec::ExcludedPattern::ExcludedPattern( PatternPtr const&amp; underlyingPattern )
    : Pattern( underlyingPattern-&gt;name() )
    , m_underlyingPattern( underlyingPattern )
    {}

    bool TestSpec::ExcludedPattern::matches( TestCaseInfo const&amp; testCase ) const {
        return !m_underlyingPattern-&gt;matches( testCase );
    }

    bool TestSpec::Filter::matches( TestCaseInfo const&amp; testCase ) const {
        return std::all_of( m_patterns.begin(), m_patterns.end(), [&amp;]( PatternPtr const&amp; p ){ return p-&gt;matches( testCase ); } );
    }

    std::string TestSpec::Filter::name() const {
        std::string name;
        for( auto const&amp; p : m_patterns )
            name += p-&gt;name();
        return name;
    }

    bool TestSpec::hasFilters() const {
        return !m_filters.empty();
    }

    bool TestSpec::matches( TestCaseInfo const&amp; testCase ) const {
        return std::any_of( m_filters.begin(), m_filters.end(), [&amp;]( Filter const&amp; f ){ return f.matches( testCase ); } );
    }

    TestSpec::Matches TestSpec::matchesByFilter( std::vector&lt;TestCase&gt; const&amp; testCases, IConfig const&amp; config ) const
    {
        Matches matches( m_filters.size() );
        std::transform( m_filters.begin(), m_filters.end(), matches.begin(), [&amp;]( Filter const&amp; filter ){
            std::vector&lt;TestCase const*&gt; currentMatches;
            for( auto const&amp; test : testCases )
                if( isThrowSafe( test, config ) &amp;&amp; filter.matches( test ) )
                    currentMatches.emplace_back( &amp;test );
            return FilterMatch{ filter.name(), currentMatches };
        } );
        return matches;
    }

    const TestSpec::vectorStrings&amp; TestSpec::getInvalidArgs() const{
        return  (m_invalidArgs);
    }

}
// end catch_test_spec.cpp
// start catch_test_spec_parser.cpp

namespace Catch {

    TestSpecParser::TestSpecParser( ITagAliasRegistry const&amp; tagAliases ) : m_tagAliases( &amp;tagAliases ) {}

    TestSpecParser&amp; TestSpecParser::parse( std::string const&amp; arg ) {
        m_mode = None;
        m_exclusion = false;
        m_arg = m_tagAliases-&gt;expandAliases( arg );
        m_escapeChars.clear();
        m_substring.reserve(m_arg.size());
        m_patternName.reserve(m_arg.size());
        m_realPatternPos = 0;

        for( m_pos = 0; m_pos &lt; m_arg.size(); ++m_pos )
          //if visitChar fails
           if( !visitChar( m_arg[m_pos] ) ){
               m_testSpec.m_invalidArgs.push_back(arg);
               break;
           }
        endMode();
        return *this;
    }
    TestSpec TestSpecParser::testSpec() {
        addFilter();
        return m_testSpec;
    }
    bool TestSpecParser::visitChar( char c ) {
        if( (m_mode != EscapedName) &amp;&amp; (c == '\\') ) {
            escape();
            addCharToPattern(c);
            return true;
        }else if((m_mode != EscapedName) &amp;&amp; (c == ',') )  {
            return separate();
        }

        switch( m_mode ) {
        case None:
            if( processNoneChar( c ) )
                return true;
            break;
        case Name:
            processNameChar( c );
            break;
        case EscapedName:
            endMode();
            addCharToPattern(c);
            return true;
        default:
        case Tag:
        case QuotedName:
            if( processOtherChar( c ) )
                return true;
            break;
        }

        m_substring += c;
        if( !isControlChar( c ) ) {
            m_patternName += c;
            m_realPatternPos++;
        }
        return true;
    }
    // Two of the processing methods return true to signal the caller to return
    // without adding the given character to the current pattern strings
    bool TestSpecParser::processNoneChar( char c ) {
        switch( c ) {
        case ' ':
            return true;
        case '~':
            m_exclusion = true;
            return false;
        case '[':
            startNewMode( Tag );
            return false;
        case '"':
            startNewMode( QuotedName );
            return false;
        default:
            startNewMode( Name );
            return false;
        }
    }
    void TestSpecParser::processNameChar( char c ) {
        if( c == '[' ) {
            if( m_substring == "exclude:" )
                m_exclusion = true;
            else
                endMode();
            startNewMode( Tag );
        }
    }
    bool TestSpecParser::processOtherChar( char c ) {
        if( !isControlChar( c ) )
            return false;
        m_substring += c;
        endMode();
        return true;
    }
    void TestSpecParser::startNewMode( Mode mode ) {
        m_mode = mode;
    }
    void TestSpecParser::endMode() {
        switch( m_mode ) {
        case Name:
        case QuotedName:
            return addNamePattern();
        case Tag:
            return addTagPattern();
        case EscapedName:
            revertBackToLastMode();
            return;
        case None:
        default:
            return startNewMode( None );
        }
    }
    void TestSpecParser::escape() {
        saveLastMode();
        m_mode = EscapedName;
        m_escapeChars.push_back(m_realPatternPos);
    }
    bool TestSpecParser::isControlChar( char c ) const {
        switch( m_mode ) {
            default:
                return false;
            case None:
                return c == '~';
            case Name:
                return c == '[';
            case EscapedName:
                return true;
            case QuotedName:
                return c == '"';
            case Tag:
                return c == '[' || c == ']';
        }
    }

    void TestSpecParser::addFilter() {
        if( !m_currentFilter.m_patterns.empty() ) {
            m_testSpec.m_filters.push_back( m_currentFilter );
            m_currentFilter = TestSpec::Filter();
        }
    }

    void TestSpecParser::saveLastMode() {
      lastMode = m_mode;
    }

    void TestSpecParser::revertBackToLastMode() {
      m_mode = lastMode;
    }

    bool TestSpecParser::separate() {
      if( (m_mode==QuotedName) || (m_mode==Tag) ){
         //invalid argument, signal failure to previous scope.
         m_mode = None;
         m_pos = m_arg.size();
         m_substring.clear();
         m_patternName.clear();
         m_realPatternPos = 0;
         return false;
      }
      endMode();
      addFilter();
      return true; //success
    }

    std::string TestSpecParser::preprocessPattern() {
        std::string token = m_patternName;
        for (std::size_t i = 0; i &lt; m_escapeChars.size(); ++i)
            token = token.substr(0, m_escapeChars[i] - i) + token.substr(m_escapeChars[i] - i + 1);
        m_escapeChars.clear();
        if (startsWith(token, "exclude:")) {
            m_exclusion = true;
            token = token.substr(8);
        }

        m_patternName.clear();
        m_realPatternPos = 0;

        return token;
    }

    void TestSpecParser::addNamePattern() {
        auto token = preprocessPattern();

        if (!token.empty()) {
            TestSpec::PatternPtr pattern = std::make_shared&lt;TestSpec::NamePattern&gt;(token, m_substring);
            if (m_exclusion)
                pattern = std::make_shared&lt;TestSpec::ExcludedPattern&gt;(pattern);
            m_currentFilter.m_patterns.push_back(pattern);
        }
        m_substring.clear();
        m_exclusion = false;
        m_mode = None;
    }

    void TestSpecParser::addTagPattern() {
        auto token = preprocessPattern();

        if (!token.empty()) {
            // If the tag pattern is the "hide and tag" shorthand (e.g. [.foo])
            // we have to create a separate hide tag and shorten the real one
            if (token.size() &gt; 1 &amp;&amp; token[0] == '.') {
                token.erase(token.begin());
                TestSpec::PatternPtr pattern = std::make_shared&lt;TestSpec::TagPattern&gt;(".", m_substring);
                if (m_exclusion) {
                    pattern = std::make_shared&lt;TestSpec::ExcludedPattern&gt;(pattern);
                }
                m_currentFilter.m_patterns.push_back(pattern);
            }

            TestSpec::PatternPtr pattern = std::make_shared&lt;TestSpec::TagPattern&gt;(token, m_substring);

            if (m_exclusion) {
                pattern = std::make_shared&lt;TestSpec::ExcludedPattern&gt;(pattern);
            }
            m_currentFilter.m_patterns.push_back(pattern);
        }
        m_substring.clear();
        m_exclusion = false;
        m_mode = None;
    }

    TestSpec parseTestSpec( std::string const&amp; arg ) {
        return TestSpecParser( ITagAliasRegistry::get() ).parse( arg ).testSpec();
    }

} // namespace Catch
// end catch_test_spec_parser.cpp
// start catch_timer.cpp

#include &lt;chrono&gt;

static const uint64_t nanosecondsInSecond = 1000000000;

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -&gt; uint64_t {
        return std::chrono::duration_cast&lt;std::chrono::nanoseconds&gt;( std::chrono::high_resolution_clock::now().time_since_epoch() ).count();
    }

    namespace {
        auto estimateClockResolution() -&gt; uint64_t {
            uint64_t sum = 0;
            static const uint64_t iterations = 1000000;

            auto startTime = getCurrentNanosecondsSinceEpoch();

            for( std::size_t i = 0; i &lt; iterations; ++i ) {

                uint64_t ticks;
                uint64_t baseTicks = getCurrentNanosecondsSinceEpoch();
                do {
                    ticks = getCurrentNanosecondsSinceEpoch();
                } while( ticks == baseTicks );

                auto delta = ticks - baseTicks;
                sum += delta;

                // If we have been calibrating for over 3 seconds -- the clock
                // is terrible and we should move on.
                // TBD: How to signal that the measured resolution is probably wrong?
                if (ticks &gt; startTime + 3 * nanosecondsInSecond) {
                    return sum / ( i + 1u );
                }
            }

            // We're just taking the mean, here. To do better we could take the std. dev and exclude outliers
            // - and potentially do more iterations if there's a high variance.
            return sum/iterations;
        }
    }
    auto getEstimatedClockResolution() -&gt; uint64_t {
        static auto s_resolution = estimateClockResolution();
        return s_resolution;
    }

    void Timer::start() {
       m_nanoseconds = getCurrentNanosecondsSinceEpoch();
    }
    auto Timer::getElapsedNanoseconds() const -&gt; uint64_t {
        return getCurrentNanosecondsSinceEpoch() - m_nanoseconds;
    }
    auto Timer::getElapsedMicroseconds() const -&gt; uint64_t {
        return getElapsedNanoseconds()/1000;
    }
    auto Timer::getElapsedMilliseconds() const -&gt; unsigned int {
        return static_cast&lt;unsigned int&gt;(getElapsedMicroseconds()/1000);
    }
    auto Timer::getElapsedSeconds() const -&gt; double {
        return getElapsedMicroseconds()/1000000.0;
    }

} // namespace Catch
// end catch_timer.cpp
// start catch_tostring.cpp

#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wexit-time-destructors"
#    pragma clang diagnostic ignored "-Wglobal-constructors"
#endif

// Enable specific decls locally
#if !defined(CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER)
#define CATCH_CONFIG_ENABLE_CHRONO_STRINGMAKER
#endif

#include &lt;cmath&gt;
#include &lt;iomanip&gt;

namespace Catch {

namespace Detail {

    const std::string unprintableString = "{?}";

    namespace {
        const int hexThreshold = 255;

        struct Endianness {
            enum Arch { Big, Little };

            static Arch which() {
                int one = 1;
                // If the lowest byte we read is non-zero, we can assume
                // that little endian format is used.
                auto value = *reinterpret_cast&lt;char*&gt;(&amp;one);
                return value ? Little : Big;
            }
        };
    }

    std::string rawMemoryToString( const void *object, std::size_t size ) {
        // Reverse order for little endian architectures
        int i = 0, end = static_cast&lt;int&gt;( size ), inc = 1;
        if( Endianness::which() == Endianness::Little ) {
            i = end-1;
            end = inc = -1;
        }

        unsigned char const *bytes = static_cast&lt;unsigned char const *&gt;(object);
        ReusableStringStream rss;
        rss &lt;&lt; "0x" &lt;&lt; std::setfill('0') &lt;&lt; std::hex;
        for( ; i != end; i += inc )
             rss &lt;&lt; std::setw(2) &lt;&lt; static_cast&lt;unsigned&gt;(bytes[i]);
       return rss.str();
    }
}

template&lt;typename T&gt;
std::string fpToString( T value, int precision ) {
    if (Catch::isnan(value)) {
        return "nan";
    }

    ReusableStringStream rss;
    rss &lt;&lt; std::setprecision( precision )
        &lt;&lt; std::fixed
        &lt;&lt; value;
    std::string d = rss.str();
    std::size_t i = d.find_last_not_of( '0' );
    if( i != std::string::npos &amp;&amp; i != d.size()-1 ) {
        if( d[i] == '.' )
            i++;
        d = d.substr( 0, i+1 );
    }
    return d;
}

//// ======================================================= ////
//
//   Out-of-line defs for full specialization of StringMaker
//
//// ======================================================= ////

std::string StringMaker&lt;std::string&gt;::convert(const std::string&amp; str) {
    if (!getCurrentContext().getConfig()-&gt;showInvisibles()) {
        return '"' + str + '"';
    }

    std::string s("\"");
    for (char c : str) {
        switch (c) {
        case '\n':
            s.append("\\n");
            break;
        case '\t':
            s.append("\\t");
            break;
        default:
            s.push_back(c);
            break;
        }
    }
    s.append("\"");
    return s;
}

#ifdef CATCH_CONFIG_CPP17_STRING_VIEW
std::string StringMaker&lt;std::string_view&gt;::convert(std::string_view str) {
    return ::Catch::Detail::stringify(std::string{ str });
}
#endif

std::string StringMaker&lt;char const*&gt;::convert(char const* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker&lt;char*&gt;::convert(char* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}

#ifdef CATCH_CONFIG_WCHAR
std::string StringMaker&lt;std::wstring&gt;::convert(const std::wstring&amp; wstr) {
    std::string s;
    s.reserve(wstr.size());
    for (auto c : wstr) {
        s += (c &lt;= 0xff) ? static_cast&lt;char&gt;(c) : '?';
    }
    return ::Catch::Detail::stringify(s);
}

# ifdef CATCH_CONFIG_CPP17_STRING_VIEW
std::string StringMaker&lt;std::wstring_view&gt;::convert(std::wstring_view str) {
    return StringMaker&lt;std::wstring&gt;::convert(std::wstring(str));
}
# endif

std::string StringMaker&lt;wchar_t const*&gt;::convert(wchar_t const * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker&lt;wchar_t *&gt;::convert(wchar_t * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}
#endif

#if defined(CATCH_CONFIG_CPP17_BYTE)
#include &lt;cstddef&gt;
std::string StringMaker&lt;std::byte&gt;::convert(std::byte value) {
    return ::Catch::Detail::stringify(std::to_integer&lt;unsigned long long&gt;(value));
}
#endif // defined(CATCH_CONFIG_CPP17_BYTE)

std::string StringMaker&lt;int&gt;::convert(int value) {
    return ::Catch::Detail::stringify(static_cast&lt;long long&gt;(value));
}
std::string StringMaker&lt;long&gt;::convert(long value) {
    return ::Catch::Detail::stringify(static_cast&lt;long long&gt;(value));
}
std::string StringMaker&lt;long long&gt;::convert(long long value) {
    ReusableStringStream rss;
    rss &lt;&lt; value;
    if (value &gt; Detail::hexThreshold) {
        rss &lt;&lt; " (0x" &lt;&lt; std::hex &lt;&lt; value &lt;&lt; ')';
    }
    return rss.str();
}

std::string StringMaker&lt;unsigned int&gt;::convert(unsigned int value) {
    return ::Catch::Detail::stringify(static_cast&lt;unsigned long long&gt;(value));
}
std::string StringMaker&lt;unsigned long&gt;::convert(unsigned long value) {
    return ::Catch::Detail::stringify(static_cast&lt;unsigned long long&gt;(value));
}
std::string StringMaker&lt;unsigned long long&gt;::convert(unsigned long long value) {
    ReusableStringStream rss;
    rss &lt;&lt; value;
    if (value &gt; Detail::hexThreshold) {
        rss &lt;&lt; " (0x" &lt;&lt; std::hex &lt;&lt; value &lt;&lt; ')';
    }
    return rss.str();
}

std::string StringMaker&lt;bool&gt;::convert(bool b) {
    return b ? "true" : "false";
}

std::string StringMaker&lt;signed char&gt;::convert(signed char value) {
    if (value == '\r') {
        return "'\\r'";
    } else if (value == '\f') {
        return "'\\f'";
    } else if (value == '\n') {
        return "'\\n'";
    } else if (value == '\t') {
        return "'\\t'";
    } else if ('\0' &lt;= value &amp;&amp; value &lt; ' ') {
        return ::Catch::Detail::stringify(static_cast&lt;unsigned int&gt;(value));
    } else {
        char chstr[] = "' '";
        chstr[1] = value;
        return chstr;
    }
}
std::string StringMaker&lt;char&gt;::convert(char c) {
    return ::Catch::Detail::stringify(static_cast&lt;signed char&gt;(c));
}
std::string StringMaker&lt;unsigned char&gt;::convert(unsigned char c) {
    return ::Catch::Detail::stringify(static_cast&lt;char&gt;(c));
}

std::string StringMaker&lt;std::nullptr_t&gt;::convert(std::nullptr_t) {
    return "nullptr";
}

int StringMaker&lt;float&gt;::precision = 5;

std::string StringMaker&lt;float&gt;::convert(float value) {
    return fpToString(value, precision) + 'f';
}

int StringMaker&lt;double&gt;::precision = 10;

std::string StringMaker&lt;double&gt;::convert(double value) {
    return fpToString(value, precision);
}

std::string ratio_string&lt;std::atto&gt;::symbol() { return "a"; }
std::string ratio_string&lt;std::femto&gt;::symbol() { return "f"; }
std::string ratio_string&lt;std::pico&gt;::symbol() { return "p"; }
std::string ratio_string&lt;std::nano&gt;::symbol() { return "n"; }
std::string ratio_string&lt;std::micro&gt;::symbol() { return "u"; }
std::string ratio_string&lt;std::milli&gt;::symbol() { return "m"; }

} // end namespace Catch

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif

// end catch_tostring.cpp
// start catch_totals.cpp

namespace Catch {

    Counts Counts::operator - ( Counts const&amp; other ) const {
        Counts diff;
        diff.passed = passed - other.passed;
        diff.failed = failed - other.failed;
        diff.failedButOk = failedButOk - other.failedButOk;
        return diff;
    }

    Counts&amp; Counts::operator += ( Counts const&amp; other ) {
        passed += other.passed;
        failed += other.failed;
        failedButOk += other.failedButOk;
        return *this;
    }

    std::size_t Counts::total() const {
        return passed + failed + failedButOk;
    }
    bool Counts::allPassed() const {
        return failed == 0 &amp;&amp; failedButOk == 0;
    }
    bool Counts::allOk() const {
        return failed == 0;
    }

    Totals Totals::operator - ( Totals const&amp; other ) const {
        Totals diff;
        diff.assertions = assertions - other.assertions;
        diff.testCases = testCases - other.testCases;
        return diff;
    }

    Totals&amp; Totals::operator += ( Totals const&amp; other ) {
        assertions += other.assertions;
        testCases += other.testCases;
        return *this;
    }

    Totals Totals::delta( Totals const&amp; prevTotals ) const {
        Totals diff = *this - prevTotals;
        if( diff.assertions.failed &gt; 0 )
            ++diff.testCases.failed;
        else if( diff.assertions.failedButOk &gt; 0 )
            ++diff.testCases.failedButOk;
        else
            ++diff.testCases.passed;
        return diff;
    }

}
// end catch_totals.cpp
// start catch_uncaught_exceptions.cpp

// start catch_config_uncaught_exceptions.hpp

//              Copyright Catch2 Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE_1_0.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#ifndef CATCH_CONFIG_UNCAUGHT_EXCEPTIONS_HPP
#define CATCH_CONFIG_UNCAUGHT_EXCEPTIONS_HPP

#if defined(_MSC_VER)
#  if _MSC_VER &gt;= 1900 // Visual Studio 2015 or newer
#    define CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#  endif
#endif

#include &lt;exception&gt;

#if defined(__cpp_lib_uncaught_exceptions) \
    &amp;&amp; !defined(CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS)

#  define CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#endif // __cpp_lib_uncaught_exceptions

#if defined(CATCH_INTERNAL_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS) \
    &amp;&amp; !defined(CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS) \
    &amp;&amp; !defined(CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS)

#  define CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#endif

#endif // CATCH_CONFIG_UNCAUGHT_EXCEPTIONS_HPP
// end catch_config_uncaught_exceptions.hpp
#include &lt;exception&gt;

namespace Catch {
    bool uncaught_exceptions() {
#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
        return false;
#elif defined(CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS)
        return std::uncaught_exceptions() &gt; 0;
#else
        return std::uncaught_exception();
#endif
  }
} // end namespace Catch
// end catch_uncaught_exceptions.cpp
// start catch_version.cpp

#include &lt;ostream&gt;

namespace Catch {

    Version::Version
        (   unsigned int _majorVersion,
            unsigned int _minorVersion,
            unsigned int _patchNumber,
            char const * const _branchName,
            unsigned int _buildNumber )
    :   majorVersion( _majorVersion ),
        minorVersion( _minorVersion ),
        patchNumber( _patchNumber ),
        branchName( _branchName ),
        buildNumber( _buildNumber )
    {}

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, Version const&amp; version ) {
        os  &lt;&lt; version.majorVersion &lt;&lt; '.'
            &lt;&lt; version.minorVersion &lt;&lt; '.'
            &lt;&lt; version.patchNumber;
        // branchName is never null -&gt; 0th char is \0 if it is empty
        if (version.branchName[0]) {
            os &lt;&lt; '-' &lt;&lt; version.branchName
               &lt;&lt; '.' &lt;&lt; version.buildNumber;
        }
        return os;
    }

    Version const&amp; libraryVersion() {
        static Version version( 2, 13, 3, "", 0 );
        return version;
    }

}
// end catch_version.cpp
// start catch_wildcard_pattern.cpp

namespace Catch {

    WildcardPattern::WildcardPattern( std::string const&amp; pattern,
                                      CaseSensitive::Choice caseSensitivity )
    :   m_caseSensitivity( caseSensitivity ),
        m_pattern( normaliseString( pattern ) )
    {
        if( startsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 1 );
            m_wildcard = WildcardAtStart;
        }
        if( endsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 0, m_pattern.size()-1 );
            m_wildcard = static_cast&lt;WildcardPosition&gt;( m_wildcard | WildcardAtEnd );
        }
    }

    bool WildcardPattern::matches( std::string const&amp; str ) const {
        switch( m_wildcard ) {
            case NoWildcard:
                return m_pattern == normaliseString( str );
            case WildcardAtStart:
                return endsWith( normaliseString( str ), m_pattern );
            case WildcardAtEnd:
                return startsWith( normaliseString( str ), m_pattern );
            case WildcardAtBothEnds:
                return contains( normaliseString( str ), m_pattern );
            default:
                CATCH_INTERNAL_ERROR( "Unknown enum" );
        }
    }

    std::string WildcardPattern::normaliseString( std::string const&amp; str ) const {
        return trim( m_caseSensitivity == CaseSensitive::No ? toLower( str ) : str );
    }
}
// end catch_wildcard_pattern.cpp
// start catch_xmlwriter.cpp

#include &lt;iomanip&gt;
#include &lt;type_traits&gt;

namespace Catch {

namespace {

    size_t trailingBytes(unsigned char c) {
        if ((c &amp; 0xE0) == 0xC0) {
            return 2;
        }
        if ((c &amp; 0xF0) == 0xE0) {
            return 3;
        }
        if ((c &amp; 0xF8) == 0xF0) {
            return 4;
        }
        CATCH_INTERNAL_ERROR("Invalid multibyte utf-8 start byte encountered");
    }

    uint32_t headerValue(unsigned char c) {
        if ((c &amp; 0xE0) == 0xC0) {
            return c &amp; 0x1F;
        }
        if ((c &amp; 0xF0) == 0xE0) {
            return c &amp; 0x0F;
        }
        if ((c &amp; 0xF8) == 0xF0) {
            return c &amp; 0x07;
        }
        CATCH_INTERNAL_ERROR("Invalid multibyte utf-8 start byte encountered");
    }

    void hexEscapeChar(std::ostream&amp; os, unsigned char c) {
        std::ios_base::fmtflags f(os.flags());
        os &lt;&lt; "\\x"
            &lt;&lt; std::uppercase &lt;&lt; std::hex &lt;&lt; std::setfill('0') &lt;&lt; std::setw(2)
            &lt;&lt; static_cast&lt;int&gt;(c);
        os.flags(f);
    }

    bool shouldNewline(XmlFormatting fmt) {
        return !!(static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(fmt &amp; XmlFormatting::Newline));
    }

    bool shouldIndent(XmlFormatting fmt) {
        return !!(static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(fmt &amp; XmlFormatting::Indent));
    }

} // anonymous namespace

    XmlFormatting operator | (XmlFormatting lhs, XmlFormatting rhs) {
        return static_cast&lt;XmlFormatting&gt;(
            static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(lhs) |
            static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(rhs)
        );
    }

    XmlFormatting operator &amp; (XmlFormatting lhs, XmlFormatting rhs) {
        return static_cast&lt;XmlFormatting&gt;(
            static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(lhs) &amp;
            static_cast&lt;std::underlying_type&lt;XmlFormatting&gt;::type&gt;(rhs)
        );
    }

    XmlEncode::XmlEncode( std::string const&amp; str, ForWhat forWhat )
    :   m_str( str ),
        m_forWhat( forWhat )
    {}

    void XmlEncode::encodeTo( std::ostream&amp; os ) const {
        // Apostrophe escaping not necessary if we always use " to write attributes
        // (see: http://www.w3.org/TR/xml/#syntax)

        for( std::size_t idx = 0; idx &lt; m_str.size(); ++ idx ) {
            unsigned char c = m_str[idx];
            switch (c) {
            case '&lt;':   os &lt;&lt; "&amp;lt;"; break;
            case '&amp;':   os &lt;&lt; "&amp;amp;"; break;

            case '&gt;':
                // See: http://www.w3.org/TR/xml/#syntax
                if (idx &gt; 2 &amp;&amp; m_str[idx - 1] == ']' &amp;&amp; m_str[idx - 2] == ']')
                    os &lt;&lt; "&amp;gt;";
                else
                    os &lt;&lt; c;
                break;

            case '\"':
                if (m_forWhat == ForAttributes)
                    os &lt;&lt; "&amp;quot;";
                else
                    os &lt;&lt; c;
                break;

            default:
                // Check for control characters and invalid utf-8

                // Escape control characters in standard ascii
                // see http://stackoverflow.com/questions/404107/why-are-control-characters-illegal-in-xml-1-0
                if (c &lt; 0x09 || (c &gt; 0x0D &amp;&amp; c &lt; 0x20) || c == 0x7F) {
                    hexEscapeChar(os, c);
                    break;
                }

                // Plain ASCII: Write it to stream
                if (c &lt; 0x7F) {
                    os &lt;&lt; c;
                    break;
                }

                // UTF-8 territory
                // Check if the encoding is valid and if it is not, hex escape bytes.
                // Important: We do not check the exact decoded values for validity, only the encoding format
                // First check that this bytes is a valid lead byte:
                // This means that it is not encoded as 1111 1XXX
                // Or as 10XX XXXX
                if (c &lt;  0xC0 ||
                    c &gt;= 0xF8) {
                    hexEscapeChar(os, c);
                    break;
                }

                auto encBytes = trailingBytes(c);
                // Are there enough bytes left to avoid accessing out-of-bounds memory?
                if (idx + encBytes - 1 &gt;= m_str.size()) {
                    hexEscapeChar(os, c);
                    break;
                }
                // The header is valid, check data
                // The next encBytes bytes must together be a valid utf-8
                // This means: bitpattern 10XX XXXX and the extracted value is sane (ish)
                bool valid = true;
                uint32_t value = headerValue(c);
                for (std::size_t n = 1; n &lt; encBytes; ++n) {
                    unsigned char nc = m_str[idx + n];
                    valid &amp;= ((nc &amp; 0xC0) == 0x80);
                    value = (value &lt;&lt; 6) | (nc &amp; 0x3F);
                }

                if (
                    // Wrong bit pattern of following bytes
                    (!valid) ||
                    // Overlong encodings
                    (value &lt; 0x80) ||
                    (0x80 &lt;= value &amp;&amp; value &lt; 0x800   &amp;&amp; encBytes &gt; 2) ||
                    (0x800 &lt; value &amp;&amp; value &lt; 0x10000 &amp;&amp; encBytes &gt; 3) ||
                    // Encoded value out of range
                    (value &gt;= 0x110000)
                    ) {
                    hexEscapeChar(os, c);
                    break;
                }

                // If we got here, this is in fact a valid(ish) utf-8 sequence
                for (std::size_t n = 0; n &lt; encBytes; ++n) {
                    os &lt;&lt; m_str[idx + n];
                }
                idx += encBytes - 1;
                break;
            }
        }
    }

    std::ostream&amp; operator &lt;&lt; ( std::ostream&amp; os, XmlEncode const&amp; xmlEncode ) {
        xmlEncode.encodeTo( os );
        return os;
    }

    XmlWriter::ScopedElement::ScopedElement( XmlWriter* writer, XmlFormatting fmt )
    :   m_writer( writer ),
        m_fmt(fmt)
    {}

    XmlWriter::ScopedElement::ScopedElement( ScopedElement&amp;&amp; other ) noexcept
    :   m_writer( other.m_writer ),
        m_fmt(other.m_fmt)
    {
        other.m_writer = nullptr;
        other.m_fmt = XmlFormatting::None;
    }
    XmlWriter::ScopedElement&amp; XmlWriter::ScopedElement::operator=( ScopedElement&amp;&amp; other ) noexcept {
        if ( m_writer ) {
            m_writer-&gt;endElement();
        }
        m_writer = other.m_writer;
        other.m_writer = nullptr;
        m_fmt = other.m_fmt;
        other.m_fmt = XmlFormatting::None;
        return *this;
    }

    XmlWriter::ScopedElement::~ScopedElement() {
        if (m_writer) {
            m_writer-&gt;endElement(m_fmt);
        }
    }

    XmlWriter::ScopedElement&amp; XmlWriter::ScopedElement::writeText( std::string const&amp; text, XmlFormatting fmt ) {
        m_writer-&gt;writeText( text, fmt );
        return *this;
    }

    XmlWriter::XmlWriter( std::ostream&amp; os ) : m_os( os )
    {
        writeDeclaration();
    }

    XmlWriter::~XmlWriter() {
        while (!m_tags.empty()) {
            endElement();
        }
        newlineIfNecessary();
    }

    XmlWriter&amp; XmlWriter::startElement( std::string const&amp; name, XmlFormatting fmt ) {
        ensureTagClosed();
        newlineIfNecessary();
        if (shouldIndent(fmt)) {
            m_os &lt;&lt; m_indent;
            m_indent += "  ";
        }
        m_os &lt;&lt; '&lt;' &lt;&lt; name;
        m_tags.push_back( name );
        m_tagIsOpen = true;
        applyFormatting(fmt);
        return *this;
    }

    XmlWriter::ScopedElement XmlWriter::scopedElement( std::string const&amp; name, XmlFormatting fmt ) {
        ScopedElement scoped( this, fmt );
        startElement( name, fmt );
        return scoped;
    }

    XmlWriter&amp; XmlWriter::endElement(XmlFormatting fmt) {
        m_indent = m_indent.substr(0, m_indent.size() - 2);

        if( m_tagIsOpen ) {
            m_os &lt;&lt; "/&gt;";
            m_tagIsOpen = false;
        } else {
            newlineIfNecessary();
            if (shouldIndent(fmt)) {
                m_os &lt;&lt; m_indent;
            }
            m_os &lt;&lt; "&lt;/" &lt;&lt; m_tags.back() &lt;&lt; "&gt;";
        }
        m_os &lt;&lt; std::flush;
        applyFormatting(fmt);
        m_tags.pop_back();
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeAttribute( std::string const&amp; name, std::string const&amp; attribute ) {
        if( !name.empty() &amp;&amp; !attribute.empty() )
            m_os &lt;&lt; ' ' &lt;&lt; name &lt;&lt; "=\"" &lt;&lt; XmlEncode( attribute, XmlEncode::ForAttributes ) &lt;&lt; '"';
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeAttribute( std::string const&amp; name, bool attribute ) {
        m_os &lt;&lt; ' ' &lt;&lt; name &lt;&lt; "=\"" &lt;&lt; ( attribute ? "true" : "false" ) &lt;&lt; '"';
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeText( std::string const&amp; text, XmlFormatting fmt) {
        if( !text.empty() ){
            bool tagWasOpen = m_tagIsOpen;
            ensureTagClosed();
            if (tagWasOpen &amp;&amp; shouldIndent(fmt)) {
                m_os &lt;&lt; m_indent;
            }
            m_os &lt;&lt; XmlEncode( text );
            applyFormatting(fmt);
        }
        return *this;
    }

    XmlWriter&amp; XmlWriter::writeComment( std::string const&amp; text, XmlFormatting fmt) {
        ensureTagClosed();
        if (shouldIndent(fmt)) {
            m_os &lt;&lt; m_indent;
        }
        m_os &lt;&lt; "&lt;!--" &lt;&lt; text &lt;&lt; "--&gt;";
        applyFormatting(fmt);
        return *this;
    }

    void XmlWriter::writeStylesheetRef( std::string const&amp; url ) {
        m_os &lt;&lt; "&lt;?xml-stylesheet type=\"text/xsl\" href=\"" &lt;&lt; url &lt;&lt; "\"?&gt;\n";
    }

    XmlWriter&amp; XmlWriter::writeBlankLine() {
        ensureTagClosed();
        m_os &lt;&lt; '\n';
        return *this;
    }

    void XmlWriter::ensureTagClosed() {
        if( m_tagIsOpen ) {
            m_os &lt;&lt; '&gt;' &lt;&lt; std::flush;
            newlineIfNecessary();
            m_tagIsOpen = false;
        }
    }

    void XmlWriter::applyFormatting(XmlFormatting fmt) {
        m_needsNewline = shouldNewline(fmt);
    }

    void XmlWriter::writeDeclaration() {
        m_os &lt;&lt; "&lt;?xml version=\"1.0\" encoding=\"UTF-8\"?&gt;\n";
    }

    void XmlWriter::newlineIfNecessary() {
        if( m_needsNewline ) {
            m_os &lt;&lt; std::endl;
            m_needsNewline = false;
        }
    }
}
// end catch_xmlwriter.cpp
// start catch_reporter_bases.cpp

#include &lt;cstring&gt;
#include &lt;cfloat&gt;
#include &lt;cstdio&gt;
#include &lt;cassert&gt;
#include &lt;memory&gt;

namespace Catch {
    void prepareExpandedExpression(AssertionResult&amp; result) {
        result.getExpandedExpression();
    }

    // Because formatting using c++ streams is stateful, drop down to C is required
    // Alternatively we could use stringstream, but its performance is... not good.
    std::string getFormattedDuration( double duration ) {
        // Max exponent + 1 is required to represent the whole part
        // + 1 for decimal point
        // + 3 for the 3 decimal places
        // + 1 for null terminator
        const std::size_t maxDoubleSize = DBL_MAX_10_EXP + 1 + 1 + 3 + 1;
        char buffer[maxDoubleSize];

        // Save previous errno, to prevent sprintf from overwriting it
        ErrnoGuard guard;
#ifdef _MSC_VER
        sprintf_s(buffer, "%.3f", duration);
#else
        std::sprintf(buffer, "%.3f", duration);
#endif
        return std::string(buffer);
    }

    bool shouldShowDuration( IConfig const&amp; config, double duration ) {
        if ( config.showDurations() == ShowDurations::Always ) {
            return true;
        }
        if ( config.showDurations() == ShowDurations::Never ) {
            return false;
        }
        const double min = config.minDuration();
        return min &gt;= 0 &amp;&amp; duration &gt;= min;
    }

    std::string serializeFilters( std::vector&lt;std::string&gt; const&amp; container ) {
        ReusableStringStream oss;
        bool first = true;
        for (auto&amp;&amp; filter : container)
        {
            if (!first)
                oss &lt;&lt; ' ';
            else
                first = false;

            oss &lt;&lt; filter;
        }
        return oss.str();
    }

    TestEventListenerBase::TestEventListenerBase(ReporterConfig const &amp; _config)
        :StreamingReporterBase(_config) {}

    std::set&lt;Verbosity&gt; TestEventListenerBase::getSupportedVerbosities() {
        return { Verbosity::Quiet, Verbosity::Normal, Verbosity::High };
    }

    void TestEventListenerBase::assertionStarting(AssertionInfo const &amp;) {}

    bool TestEventListenerBase::assertionEnded(AssertionStats const &amp;) {
        return false;
    }

} // end namespace Catch
// end catch_reporter_bases.cpp
// start catch_reporter_compact.cpp

namespace {

#ifdef CATCH_PLATFORM_MAC
    const char* failedString() { return "FAILED"; }
    const char* passedString() { return "PASSED"; }
#else
    const char* failedString() { return "failed"; }
    const char* passedString() { return "passed"; }
#endif

    // Colour::LightGrey
    Catch::Colour::Code dimColour() { return Catch::Colour::FileName; }

    std::string bothOrAll( std::size_t count ) {
        return count == 1 ? std::string() :
               count == 2 ? "both " : "all " ;
    }

} // anon namespace

namespace Catch {
namespace {
// Colour, message variants:
// - white: No tests ran.
// -   red: Failed [both/all] N test cases, failed [both/all] M assertions.
// - white: Passed [both/all] N test cases (no assertions).
// -   red: Failed N tests cases, failed M assertions.
// - green: Passed [both/all] N tests cases with M assertions.
void printTotals(std::ostream&amp; out, const Totals&amp; totals) {
    if (totals.testCases.total() == 0) {
        out &lt;&lt; "No tests ran.";
    } else if (totals.testCases.failed == totals.testCases.total()) {
        Colour colour(Colour::ResultError);
        const std::string qualify_assertions_failed =
            totals.assertions.failed == totals.assertions.total() ?
            bothOrAll(totals.assertions.failed) : std::string();
        out &lt;&lt;
            "Failed " &lt;&lt; bothOrAll(totals.testCases.failed)
            &lt;&lt; pluralise(totals.testCases.failed, "test case") &lt;&lt; ", "
            "failed " &lt;&lt; qualify_assertions_failed &lt;&lt;
            pluralise(totals.assertions.failed, "assertion") &lt;&lt; '.';
    } else if (totals.assertions.total() == 0) {
        out &lt;&lt;
            "Passed " &lt;&lt; bothOrAll(totals.testCases.total())
            &lt;&lt; pluralise(totals.testCases.total(), "test case")
            &lt;&lt; " (no assertions).";
    } else if (totals.assertions.failed) {
        Colour colour(Colour::ResultError);
        out &lt;&lt;
            "Failed " &lt;&lt; pluralise(totals.testCases.failed, "test case") &lt;&lt; ", "
            "failed " &lt;&lt; pluralise(totals.assertions.failed, "assertion") &lt;&lt; '.';
    } else {
        Colour colour(Colour::ResultSuccess);
        out &lt;&lt;
            "Passed " &lt;&lt; bothOrAll(totals.testCases.passed)
            &lt;&lt; pluralise(totals.testCases.passed, "test case") &lt;&lt;
            " with " &lt;&lt; pluralise(totals.assertions.passed, "assertion") &lt;&lt; '.';
    }
}

// Implementation of CompactReporter formatting
class AssertionPrinter {
public:
    AssertionPrinter&amp; operator= (AssertionPrinter const&amp;) = delete;
    AssertionPrinter(AssertionPrinter const&amp;) = delete;
    AssertionPrinter(std::ostream&amp; _stream, AssertionStats const&amp; _stats, bool _printInfoMessages)
        : stream(_stream)
        , result(_stats.assertionResult)
        , messages(_stats.infoMessages)
        , itMessage(_stats.infoMessages.begin())
        , printInfoMessages(_printInfoMessages) {}

    void print() {
        printSourceInfo();

        itMessage = messages.begin();

        switch (result.getResultType()) {
        case ResultWas::Ok:
            printResultType(Colour::ResultSuccess, passedString());
            printOriginalExpression();
            printReconstructedExpression();
            if (!result.hasExpression())
                printRemainingMessages(Colour::None);
            else
                printRemainingMessages();
            break;
        case ResultWas::ExpressionFailed:
            if (result.isOk())
                printResultType(Colour::ResultSuccess, failedString() + std::string(" - but was ok"));
            else
                printResultType(Colour::Error, failedString());
            printOriginalExpression();
            printReconstructedExpression();
            printRemainingMessages();
            break;
        case ResultWas::ThrewException:
            printResultType(Colour::Error, failedString());
            printIssue("unexpected exception with message:");
            printMessage();
            printExpressionWas();
            printRemainingMessages();
            break;
        case ResultWas::FatalErrorCondition:
            printResultType(Colour::Error, failedString());
            printIssue("fatal error condition with message:");
            printMessage();
            printExpressionWas();
            printRemainingMessages();
            break;
        case ResultWas::DidntThrowException:
            printResultType(Colour::Error, failedString());
            printIssue("expected exception, got none");
            printExpressionWas();
            printRemainingMessages();
            break;
        case ResultWas::Info:
            printResultType(Colour::None, "info");
            printMessage();
            printRemainingMessages();
            break;
        case ResultWas::Warning:
            printResultType(Colour::None, "warning");
            printMessage();
            printRemainingMessages();
            break;
        case ResultWas::ExplicitFailure:
            printResultType(Colour::Error, failedString());
            printIssue("explicitly");
            printRemainingMessages(Colour::None);
            break;
            // These cases are here to prevent compiler warnings
        case ResultWas::Unknown:
        case ResultWas::FailureBit:
        case ResultWas::Exception:
            printResultType(Colour::Error, "** internal error **");
            break;
        }
    }

private:
    void printSourceInfo() const {
        Colour colourGuard(Colour::FileName);
        stream &lt;&lt; result.getSourceInfo() &lt;&lt; ':';
    }

    void printResultType(Colour::Code colour, std::string const&amp; passOrFail) const {
        if (!passOrFail.empty()) {
            {
                Colour colourGuard(colour);
                stream &lt;&lt; ' ' &lt;&lt; passOrFail;
            }
            stream &lt;&lt; ':';
        }
    }

    void printIssue(std::string const&amp; issue) const {
        stream &lt;&lt; ' ' &lt;&lt; issue;
    }

    void printExpressionWas() {
        if (result.hasExpression()) {
            stream &lt;&lt; ';';
            {
                Colour colour(dimColour());
                stream &lt;&lt; " expression was:";
            }
            printOriginalExpression();
        }
    }

    void printOriginalExpression() const {
        if (result.hasExpression()) {
            stream &lt;&lt; ' ' &lt;&lt; result.getExpression();
        }
    }

    void printReconstructedExpression() const {
        if (result.hasExpandedExpression()) {
            {
                Colour colour(dimColour());
                stream &lt;&lt; " for: ";
            }
            stream &lt;&lt; result.getExpandedExpression();
        }
    }

    void printMessage() {
        if (itMessage != messages.end()) {
            stream &lt;&lt; " '" &lt;&lt; itMessage-&gt;message &lt;&lt; '\'';
            ++itMessage;
        }
    }

    void printRemainingMessages(Colour::Code colour = dimColour()) {
        if (itMessage == messages.end())
            return;

        const auto itEnd = messages.cend();
        const auto N = static_cast&lt;std::size_t&gt;(std::distance(itMessage, itEnd));

        {
            Colour colourGuard(colour);
            stream &lt;&lt; " with " &lt;&lt; pluralise(N, "message") &lt;&lt; ':';
        }

        while (itMessage != itEnd) {
            // If this assertion is a warning ignore any INFO messages
            if (printInfoMessages || itMessage-&gt;type != ResultWas::Info) {
                printMessage();
                if (itMessage != itEnd) {
                    Colour colourGuard(dimColour());
                    stream &lt;&lt; " and";
                }
                continue;
            }
            ++itMessage;
        }
    }

private:
    std::ostream&amp; stream;
    AssertionResult const&amp; result;
    std::vector&lt;MessageInfo&gt; messages;
    std::vector&lt;MessageInfo&gt;::const_iterator itMessage;
    bool printInfoMessages;
};

} // anon namespace

        std::string CompactReporter::getDescription() {
            return "Reports test results on a single line, suitable for IDEs";
        }

        void CompactReporter::noMatchingTestCases( std::string const&amp; spec ) {
            stream &lt;&lt; "No test cases matched '" &lt;&lt; spec &lt;&lt; '\'' &lt;&lt; std::endl;
        }

        void CompactReporter::assertionStarting( AssertionInfo const&amp; ) {}

        bool CompactReporter::assertionEnded( AssertionStats const&amp; _assertionStats ) {
            AssertionResult const&amp; result = _assertionStats.assertionResult;

            bool printInfoMessages = true;

            // Drop out if result was successful and we're not printing those
            if( !m_config-&gt;includeSuccessfulResults() &amp;&amp; result.isOk() ) {
                if( result.getResultType() != ResultWas::Warning )
                    return false;
                printInfoMessages = false;
            }

            AssertionPrinter printer( stream, _assertionStats, printInfoMessages );
            printer.print();

            stream &lt;&lt; std::endl;
            return true;
        }

        void CompactReporter::sectionEnded(SectionStats const&amp; _sectionStats) {
            double dur = _sectionStats.durationInSeconds;
            if ( shouldShowDuration( *m_config, dur ) ) {
                stream &lt;&lt; getFormattedDuration( dur ) &lt;&lt; " s: " &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; std::endl;
            }
        }

        void CompactReporter::testRunEnded( TestRunStats const&amp; _testRunStats ) {
            printTotals( stream, _testRunStats.totals );
            stream &lt;&lt; '\n' &lt;&lt; std::endl;
            StreamingReporterBase::testRunEnded( _testRunStats );
        }

        CompactReporter::~CompactReporter() {}

    CATCH_REGISTER_REPORTER( "compact", CompactReporter )

} // end namespace Catch
// end catch_reporter_compact.cpp
// start catch_reporter_console.cpp

#include &lt;cfloat&gt;
#include &lt;cstdio&gt;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // Not all labels are EXPLICITLY handled in switch
 // Note that 4062 (not all labels are handled and default is missing) is enabled
#endif

#if defined(__clang__)
#  pragma clang diagnostic push
// For simplicity, benchmarking-only helpers are always enabled
#  pragma clang diagnostic ignored "-Wunused-function"
#endif

namespace Catch {

namespace {

// Formatter impl for ConsoleReporter
class ConsoleAssertionPrinter {
public:
    ConsoleAssertionPrinter&amp; operator= (ConsoleAssertionPrinter const&amp;) = delete;
    ConsoleAssertionPrinter(ConsoleAssertionPrinter const&amp;) = delete;
    ConsoleAssertionPrinter(std::ostream&amp; _stream, AssertionStats const&amp; _stats, bool _printInfoMessages)
        : stream(_stream),
        stats(_stats),
        result(_stats.assertionResult),
        colour(Colour::None),
        message(result.getMessage()),
        messages(_stats.infoMessages),
        printInfoMessages(_printInfoMessages) {
        switch (result.getResultType()) {
        case ResultWas::Ok:
            colour = Colour::Success;
            passOrFail = "PASSED";
            //if( result.hasMessage() )
            if (_stats.infoMessages.size() == 1)
                messageLabel = "with message";
            if (_stats.infoMessages.size() &gt; 1)
                messageLabel = "with messages";
            break;
        case ResultWas::ExpressionFailed:
            if (result.isOk()) {
                colour = Colour::Success;
                passOrFail = "FAILED - but was ok";
            } else {
                colour = Colour::Error;
                passOrFail = "FAILED";
            }
            if (_stats.infoMessages.size() == 1)
                messageLabel = "with message";
            if (_stats.infoMessages.size() &gt; 1)
                messageLabel = "with messages";
            break;
        case ResultWas::ThrewException:
            colour = Colour::Error;
            passOrFail = "FAILED";
            messageLabel = "due to unexpected exception with ";
            if (_stats.infoMessages.size() == 1)
                messageLabel += "message";
            if (_stats.infoMessages.size() &gt; 1)
                messageLabel += "messages";
            break;
        case ResultWas::FatalErrorCondition:
            colour = Colour::Error;
            passOrFail = "FAILED";
            messageLabel = "due to a fatal error condition";
            break;
        case ResultWas::DidntThrowException:
            colour = Colour::Error;
            passOrFail = "FAILED";
            messageLabel = "because no exception was thrown where one was expected";
            break;
        case ResultWas::Info:
            messageLabel = "info";
            break;
        case ResultWas::Warning:
            messageLabel = "warning";
            break;
        case ResultWas::ExplicitFailure:
            passOrFail = "FAILED";
            colour = Colour::Error;
            if (_stats.infoMessages.size() == 1)
                messageLabel = "explicitly with message";
            if (_stats.infoMessages.size() &gt; 1)
                messageLabel = "explicitly with messages";
            break;
            // These cases are here to prevent compiler warnings
        case ResultWas::Unknown:
        case ResultWas::FailureBit:
        case ResultWas::Exception:
            passOrFail = "** internal error **";
            colour = Colour::Error;
            break;
        }
    }

    void print() const {
        printSourceInfo();
        if (stats.totals.assertions.total() &gt; 0) {
            printResultType();
            printOriginalExpression();
            printReconstructedExpression();
        } else {
            stream &lt;&lt; '\n';
        }
        printMessage();
    }

private:
    void printResultType() const {
        if (!passOrFail.empty()) {
            Colour colourGuard(colour);
            stream &lt;&lt; passOrFail &lt;&lt; ":\n";
        }
    }
    void printOriginalExpression() const {
        if (result.hasExpression()) {
            Colour colourGuard(Colour::OriginalExpression);
            stream &lt;&lt; "  ";
            stream &lt;&lt; result.getExpressionInMacro();
            stream &lt;&lt; '\n';
        }
    }
    void printReconstructedExpression() const {
        if (result.hasExpandedExpression()) {
            stream &lt;&lt; "with expansion:\n";
            Colour colourGuard(Colour::ReconstructedExpression);
            stream &lt;&lt; Column(result.getExpandedExpression()).indent(2) &lt;&lt; '\n';
        }
    }
    void printMessage() const {
        if (!messageLabel.empty())
            stream &lt;&lt; messageLabel &lt;&lt; ':' &lt;&lt; '\n';
        for (auto const&amp; msg : messages) {
            // If this assertion is a warning ignore any INFO messages
            if (printInfoMessages || msg.type != ResultWas::Info)
                stream &lt;&lt; Column(msg.message).indent(2) &lt;&lt; '\n';
        }
    }
    void printSourceInfo() const {
        Colour colourGuard(Colour::FileName);
        stream &lt;&lt; result.getSourceInfo() &lt;&lt; ": ";
    }

    std::ostream&amp; stream;
    AssertionStats const&amp; stats;
    AssertionResult const&amp; result;
    Colour::Code colour;
    std::string passOrFail;
    std::string messageLabel;
    std::string message;
    std::vector&lt;MessageInfo&gt; messages;
    bool printInfoMessages;
};

std::size_t makeRatio(std::size_t number, std::size_t total) {
    std::size_t ratio = total &gt; 0 ? CATCH_CONFIG_CONSOLE_WIDTH * number / total : 0;
    return (ratio == 0 &amp;&amp; number &gt; 0) ? 1 : ratio;
}

std::size_t&amp; findMax(std::size_t&amp; i, std::size_t&amp; j, std::size_t&amp; k) {
    if (i &gt; j &amp;&amp; i &gt; k)
        return i;
    else if (j &gt; k)
        return j;
    else
        return k;
}

struct ColumnInfo {
    enum Justification { Left, Right };
    std::string name;
    int width;
    Justification justification;
};
struct ColumnBreak {};
struct RowBreak {};

class Duration {
    enum class Unit {
        Auto,
        Nanoseconds,
        Microseconds,
        Milliseconds,
        Seconds,
        Minutes
    };
    static const uint64_t s_nanosecondsInAMicrosecond = 1000;
    static const uint64_t s_nanosecondsInAMillisecond = 1000 * s_nanosecondsInAMicrosecond;
    static const uint64_t s_nanosecondsInASecond = 1000 * s_nanosecondsInAMillisecond;
    static const uint64_t s_nanosecondsInAMinute = 60 * s_nanosecondsInASecond;

    double m_inNanoseconds;
    Unit m_units;

public:
    explicit Duration(double inNanoseconds, Unit units = Unit::Auto)
        : m_inNanoseconds(inNanoseconds),
        m_units(units) {
        if (m_units == Unit::Auto) {
            if (m_inNanoseconds &lt; s_nanosecondsInAMicrosecond)
                m_units = Unit::Nanoseconds;
            else if (m_inNanoseconds &lt; s_nanosecondsInAMillisecond)
                m_units = Unit::Microseconds;
            else if (m_inNanoseconds &lt; s_nanosecondsInASecond)
                m_units = Unit::Milliseconds;
            else if (m_inNanoseconds &lt; s_nanosecondsInAMinute)
                m_units = Unit::Seconds;
            else
                m_units = Unit::Minutes;
        }

    }

    auto value() const -&gt; double {
        switch (m_units) {
        case Unit::Microseconds:
            return m_inNanoseconds / static_cast&lt;double&gt;(s_nanosecondsInAMicrosecond);
        case Unit::Milliseconds:
            return m_inNanoseconds / static_cast&lt;double&gt;(s_nanosecondsInAMillisecond);
        case Unit::Seconds:
            return m_inNanoseconds / static_cast&lt;double&gt;(s_nanosecondsInASecond);
        case Unit::Minutes:
            return m_inNanoseconds / static_cast&lt;double&gt;(s_nanosecondsInAMinute);
        default:
            return m_inNanoseconds;
        }
    }
    auto unitsAsString() const -&gt; std::string {
        switch (m_units) {
        case Unit::Nanoseconds:
            return "ns";
        case Unit::Microseconds:
            return "us";
        case Unit::Milliseconds:
            return "ms";
        case Unit::Seconds:
            return "s";
        case Unit::Minutes:
            return "m";
        default:
            return "** internal error **";
        }

    }
    friend auto operator &lt;&lt; (std::ostream&amp; os, Duration const&amp; duration) -&gt; std::ostream&amp; {
        return os &lt;&lt; duration.value() &lt;&lt; ' ' &lt;&lt; duration.unitsAsString();
    }
};
} // end anon namespace

class TablePrinter {
    std::ostream&amp; m_os;
    std::vector&lt;ColumnInfo&gt; m_columnInfos;
    std::ostringstream m_oss;
    int m_currentColumn = -1;
    bool m_isOpen = false;

public:
    TablePrinter( std::ostream&amp; os, std::vector&lt;ColumnInfo&gt; columnInfos )
    :   m_os( os ),
        m_columnInfos( std::move( columnInfos ) ) {}

    auto columnInfos() const -&gt; std::vector&lt;ColumnInfo&gt; const&amp; {
        return m_columnInfos;
    }

    void open() {
        if (!m_isOpen) {
            m_isOpen = true;
            *this &lt;&lt; RowBreak();

			Columns headerCols;
			Spacer spacer(2);
			for (auto const&amp; info : m_columnInfos) {
				headerCols += Column(info.name).width(static_cast&lt;std::size_t&gt;(info.width - 2));
				headerCols += spacer;
			}
			m_os &lt;&lt; headerCols &lt;&lt; '\n';

            m_os &lt;&lt; Catch::getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
        }
    }
    void close() {
        if (m_isOpen) {
            *this &lt;&lt; RowBreak();
            m_os &lt;&lt; std::endl;
            m_isOpen = false;
        }
    }

    template&lt;typename T&gt;
    friend TablePrinter&amp; operator &lt;&lt; (TablePrinter&amp; tp, T const&amp; value) {
        tp.m_oss &lt;&lt; value;
        return tp;
    }

    friend TablePrinter&amp; operator &lt;&lt; (TablePrinter&amp; tp, ColumnBreak) {
        auto colStr = tp.m_oss.str();
        const auto strSize = colStr.size();
        tp.m_oss.str("");
        tp.open();
        if (tp.m_currentColumn == static_cast&lt;int&gt;(tp.m_columnInfos.size() - 1)) {
            tp.m_currentColumn = -1;
            tp.m_os &lt;&lt; '\n';
        }
        tp.m_currentColumn++;

        auto colInfo = tp.m_columnInfos[tp.m_currentColumn];
        auto padding = (strSize + 1 &lt; static_cast&lt;std::size_t&gt;(colInfo.width))
            ? std::string(colInfo.width - (strSize + 1), ' ')
            : std::string();
        if (colInfo.justification == ColumnInfo::Left)
            tp.m_os &lt;&lt; colStr &lt;&lt; padding &lt;&lt; ' ';
        else
            tp.m_os &lt;&lt; padding &lt;&lt; colStr &lt;&lt; ' ';
        return tp;
    }

    friend TablePrinter&amp; operator &lt;&lt; (TablePrinter&amp; tp, RowBreak) {
        if (tp.m_currentColumn &gt; 0) {
            tp.m_os &lt;&lt; '\n';
            tp.m_currentColumn = -1;
        }
        return tp;
    }
};

ConsoleReporter::ConsoleReporter(ReporterConfig const&amp; config)
    : StreamingReporterBase(config),
    m_tablePrinter(new TablePrinter(config.stream(),
        [&amp;config]() -&gt; std::vector&lt;ColumnInfo&gt; {
        if (config.fullConfig()-&gt;benchmarkNoAnalysis())
        {
            return{
                { "benchmark name", CATCH_CONFIG_CONSOLE_WIDTH - 43, ColumnInfo::Left },
                { "     samples", 14, ColumnInfo::Right },
                { "  iterations", 14, ColumnInfo::Right },
                { "        mean", 14, ColumnInfo::Right }
            };
        }
        else
        {
            return{
                { "benchmark name", CATCH_CONFIG_CONSOLE_WIDTH - 43, ColumnInfo::Left },
                { "samples      mean       std dev", 14, ColumnInfo::Right },
                { "iterations   low mean   low std dev", 14, ColumnInfo::Right },
                { "estimated    high mean  high std dev", 14, ColumnInfo::Right }
            };
        }
    }())) {}
ConsoleReporter::~ConsoleReporter() = default;

std::string ConsoleReporter::getDescription() {
    return "Reports test results as plain lines of text";
}

void ConsoleReporter::noMatchingTestCases(std::string const&amp; spec) {
    stream &lt;&lt; "No test cases matched '" &lt;&lt; spec &lt;&lt; '\'' &lt;&lt; std::endl;
}

void ConsoleReporter::reportInvalidArguments(std::string const&amp;arg){
    stream &lt;&lt; "Invalid Filter: " &lt;&lt; arg &lt;&lt; std::endl;
}

void ConsoleReporter::assertionStarting(AssertionInfo const&amp;) {}

bool ConsoleReporter::assertionEnded(AssertionStats const&amp; _assertionStats) {
    AssertionResult const&amp; result = _assertionStats.assertionResult;

    bool includeResults = m_config-&gt;includeSuccessfulResults() || !result.isOk();

    // Drop out if result was successful but we're not printing them.
    if (!includeResults &amp;&amp; result.getResultType() != ResultWas::Warning)
        return false;

    lazyPrint();

    ConsoleAssertionPrinter printer(stream, _assertionStats, includeResults);
    printer.print();
    stream &lt;&lt; std::endl;
    return true;
}

void ConsoleReporter::sectionStarting(SectionInfo const&amp; _sectionInfo) {
    m_tablePrinter-&gt;close();
    m_headerPrinted = false;
    StreamingReporterBase::sectionStarting(_sectionInfo);
}
void ConsoleReporter::sectionEnded(SectionStats const&amp; _sectionStats) {
    m_tablePrinter-&gt;close();
    if (_sectionStats.missingAssertions) {
        lazyPrint();
        Colour colour(Colour::ResultError);
        if (m_sectionStack.size() &gt; 1)
            stream &lt;&lt; "\nNo assertions in section";
        else
            stream &lt;&lt; "\nNo assertions in test case";
        stream &lt;&lt; " '" &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; "'\n" &lt;&lt; std::endl;
    }
    double dur = _sectionStats.durationInSeconds;
    if (shouldShowDuration(*m_config, dur)) {
        stream &lt;&lt; getFormattedDuration(dur) &lt;&lt; " s: " &lt;&lt; _sectionStats.sectionInfo.name &lt;&lt; std::endl;
    }
    if (m_headerPrinted) {
        m_headerPrinted = false;
    }
    StreamingReporterBase::sectionEnded(_sectionStats);
}

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
void ConsoleReporter::benchmarkPreparing(std::string const&amp; name) {
	lazyPrintWithoutClosingBenchmarkTable();

	auto nameCol = Column(name).width(static_cast&lt;std::size_t&gt;(m_tablePrinter-&gt;columnInfos()[0].width - 2));

	bool firstLine = true;
	for (auto line : nameCol) {
		if (!firstLine)
			(*m_tablePrinter) &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak();
		else
			firstLine = false;

		(*m_tablePrinter) &lt;&lt; line &lt;&lt; ColumnBreak();
	}
}

void ConsoleReporter::benchmarkStarting(BenchmarkInfo const&amp; info) {
    (*m_tablePrinter) &lt;&lt; info.samples &lt;&lt; ColumnBreak()
        &lt;&lt; info.iterations &lt;&lt; ColumnBreak();
    if (!m_config-&gt;benchmarkNoAnalysis())
        (*m_tablePrinter) &lt;&lt; Duration(info.estimatedDuration) &lt;&lt; ColumnBreak();
}
void ConsoleReporter::benchmarkEnded(BenchmarkStats&lt;&gt; const&amp; stats) {
    if (m_config-&gt;benchmarkNoAnalysis())
    {
        (*m_tablePrinter) &lt;&lt; Duration(stats.mean.point.count()) &lt;&lt; ColumnBreak();
    }
    else
    {
        (*m_tablePrinter) &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.mean.point.count()) &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.mean.lower_bound.count()) &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.mean.upper_bound.count()) &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.standardDeviation.point.count()) &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.standardDeviation.lower_bound.count()) &lt;&lt; ColumnBreak()
            &lt;&lt; Duration(stats.standardDeviation.upper_bound.count()) &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak() &lt;&lt; ColumnBreak();
    }
}

void ConsoleReporter::benchmarkFailed(std::string const&amp; error) {
	Colour colour(Colour::Red);
    (*m_tablePrinter)
        &lt;&lt; "Benchmark failed (" &lt;&lt; error &lt;&lt; ')'
        &lt;&lt; ColumnBreak() &lt;&lt; RowBreak();
}
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

void ConsoleReporter::testCaseEnded(TestCaseStats const&amp; _testCaseStats) {
    m_tablePrinter-&gt;close();
    StreamingReporterBase::testCaseEnded(_testCaseStats);
    m_headerPrinted = false;
}
void ConsoleReporter::testGroupEnded(TestGroupStats const&amp; _testGroupStats) {
    if (currentGroupInfo.used) {
        printSummaryDivider();
        stream &lt;&lt; "Summary for group '" &lt;&lt; _testGroupStats.groupInfo.name &lt;&lt; "':\n";
        printTotals(_testGroupStats.totals);
        stream &lt;&lt; '\n' &lt;&lt; std::endl;
    }
    StreamingReporterBase::testGroupEnded(_testGroupStats);
}
void ConsoleReporter::testRunEnded(TestRunStats const&amp; _testRunStats) {
    printTotalsDivider(_testRunStats.totals);
    printTotals(_testRunStats.totals);
    stream &lt;&lt; std::endl;
    StreamingReporterBase::testRunEnded(_testRunStats);
}
void ConsoleReporter::testRunStarting(TestRunInfo const&amp; _testInfo) {
    StreamingReporterBase::testRunStarting(_testInfo);
    printTestFilters();
}

void ConsoleReporter::lazyPrint() {

    m_tablePrinter-&gt;close();
    lazyPrintWithoutClosingBenchmarkTable();
}

void ConsoleReporter::lazyPrintWithoutClosingBenchmarkTable() {

    if (!currentTestRunInfo.used)
        lazyPrintRunInfo();
    if (!currentGroupInfo.used)
        lazyPrintGroupInfo();

    if (!m_headerPrinted) {
        printTestCaseAndSectionHeader();
        m_headerPrinted = true;
    }
}
void ConsoleReporter::lazyPrintRunInfo() {
    stream &lt;&lt; '\n' &lt;&lt; getLineOfChars&lt;'~'&gt;() &lt;&lt; '\n';
    Colour colour(Colour::SecondaryText);
    stream &lt;&lt; currentTestRunInfo-&gt;name
        &lt;&lt; " is a Catch v" &lt;&lt; libraryVersion() &lt;&lt; " host application.\n"
        &lt;&lt; "Run with -? for options\n\n";

    if (m_config-&gt;rngSeed() != 0)
        stream &lt;&lt; "Randomness seeded to: " &lt;&lt; m_config-&gt;rngSeed() &lt;&lt; "\n\n";

    currentTestRunInfo.used = true;
}
void ConsoleReporter::lazyPrintGroupInfo() {
    if (!currentGroupInfo-&gt;name.empty() &amp;&amp; currentGroupInfo-&gt;groupsCounts &gt; 1) {
        printClosedHeader("Group: " + currentGroupInfo-&gt;name);
        currentGroupInfo.used = true;
    }
}
void ConsoleReporter::printTestCaseAndSectionHeader() {
    assert(!m_sectionStack.empty());
    printOpenHeader(currentTestCaseInfo-&gt;name);

    if (m_sectionStack.size() &gt; 1) {
        Colour colourGuard(Colour::Headers);

        auto
            it = m_sectionStack.begin() + 1, // Skip first section (test case)
            itEnd = m_sectionStack.end();
        for (; it != itEnd; ++it)
            printHeaderString(it-&gt;name, 2);
    }

    SourceLineInfo lineInfo = m_sectionStack.back().lineInfo;

    stream &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
    Colour colourGuard(Colour::FileName);
    stream &lt;&lt; lineInfo &lt;&lt; '\n';
    stream &lt;&lt; getLineOfChars&lt;'.'&gt;() &lt;&lt; '\n' &lt;&lt; std::endl;
}

void ConsoleReporter::printClosedHeader(std::string const&amp; _name) {
    printOpenHeader(_name);
    stream &lt;&lt; getLineOfChars&lt;'.'&gt;() &lt;&lt; '\n';
}
void ConsoleReporter::printOpenHeader(std::string const&amp; _name) {
    stream &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
    {
        Colour colourGuard(Colour::Headers);
        printHeaderString(_name);
    }
}

// if string has a : in first line will set indent to follow it on
// subsequent lines
void ConsoleReporter::printHeaderString(std::string const&amp; _string, std::size_t indent) {
    std::size_t i = _string.find(": ");
    if (i != std::string::npos)
        i += 2;
    else
        i = 0;
    stream &lt;&lt; Column(_string).indent(indent + i).initialIndent(indent) &lt;&lt; '\n';
}

struct SummaryColumn {

    SummaryColumn( std::string _label, Colour::Code _colour )
    :   label( std::move( _label ) ),
        colour( _colour ) {}
    SummaryColumn addRow( std::size_t count ) {
        ReusableStringStream rss;
        rss &lt;&lt; count;
        std::string row = rss.str();
        for (auto&amp; oldRow : rows) {
            while (oldRow.size() &lt; row.size())
                oldRow = ' ' + oldRow;
            while (oldRow.size() &gt; row.size())
                row = ' ' + row;
        }
        rows.push_back(row);
        return *this;
    }

    std::string label;
    Colour::Code colour;
    std::vector&lt;std::string&gt; rows;

};

void ConsoleReporter::printTotals( Totals const&amp; totals ) {
    if (totals.testCases.total() == 0) {
        stream &lt;&lt; Colour(Colour::Warning) &lt;&lt; "No tests ran\n";
    } else if (totals.assertions.total() &gt; 0 &amp;&amp; totals.testCases.allPassed()) {
        stream &lt;&lt; Colour(Colour::ResultSuccess) &lt;&lt; "All tests passed";
        stream &lt;&lt; " ("
            &lt;&lt; pluralise(totals.assertions.passed, "assertion") &lt;&lt; " in "
            &lt;&lt; pluralise(totals.testCases.passed, "test case") &lt;&lt; ')'
            &lt;&lt; '\n';
    } else {

        std::vector&lt;SummaryColumn&gt; columns;
        columns.push_back(SummaryColumn("", Colour::None)
                          .addRow(totals.testCases.total())
                          .addRow(totals.assertions.total()));
        columns.push_back(SummaryColumn("passed", Colour::Success)
                          .addRow(totals.testCases.passed)
                          .addRow(totals.assertions.passed));
        columns.push_back(SummaryColumn("failed", Colour::ResultError)
                          .addRow(totals.testCases.failed)
                          .addRow(totals.assertions.failed));
        columns.push_back(SummaryColumn("failed as expected", Colour::ResultExpectedFailure)
                          .addRow(totals.testCases.failedButOk)
                          .addRow(totals.assertions.failedButOk));

        printSummaryRow("test cases", columns, 0);
        printSummaryRow("assertions", columns, 1);
    }
}
void ConsoleReporter::printSummaryRow(std::string const&amp; label, std::vector&lt;SummaryColumn&gt; const&amp; cols, std::size_t row) {
    for (auto col : cols) {
        std::string value = col.rows[row];
        if (col.label.empty()) {
            stream &lt;&lt; label &lt;&lt; ": ";
            if (value != "0")
                stream &lt;&lt; value;
            else
                stream &lt;&lt; Colour(Colour::Warning) &lt;&lt; "- none -";
        } else if (value != "0") {
            stream &lt;&lt; Colour(Colour::LightGrey) &lt;&lt; " | ";
            stream &lt;&lt; Colour(col.colour)
                &lt;&lt; value &lt;&lt; ' ' &lt;&lt; col.label;
        }
    }
    stream &lt;&lt; '\n';
}

void ConsoleReporter::printTotalsDivider(Totals const&amp; totals) {
    if (totals.testCases.total() &gt; 0) {
        std::size_t failedRatio = makeRatio(totals.testCases.failed, totals.testCases.total());
        std::size_t failedButOkRatio = makeRatio(totals.testCases.failedButOk, totals.testCases.total());
        std::size_t passedRatio = makeRatio(totals.testCases.passed, totals.testCases.total());
        while (failedRatio + failedButOkRatio + passedRatio &lt; CATCH_CONFIG_CONSOLE_WIDTH - 1)
            findMax(failedRatio, failedButOkRatio, passedRatio)++;
        while (failedRatio + failedButOkRatio + passedRatio &gt; CATCH_CONFIG_CONSOLE_WIDTH - 1)
            findMax(failedRatio, failedButOkRatio, passedRatio)--;

        stream &lt;&lt; Colour(Colour::Error) &lt;&lt; std::string(failedRatio, '=');
        stream &lt;&lt; Colour(Colour::ResultExpectedFailure) &lt;&lt; std::string(failedButOkRatio, '=');
        if (totals.testCases.allPassed())
            stream &lt;&lt; Colour(Colour::ResultSuccess) &lt;&lt; std::string(passedRatio, '=');
        else
            stream &lt;&lt; Colour(Colour::Success) &lt;&lt; std::string(passedRatio, '=');
    } else {
        stream &lt;&lt; Colour(Colour::Warning) &lt;&lt; std::string(CATCH_CONFIG_CONSOLE_WIDTH - 1, '=');
    }
    stream &lt;&lt; '\n';
}
void ConsoleReporter::printSummaryDivider() {
    stream &lt;&lt; getLineOfChars&lt;'-'&gt;() &lt;&lt; '\n';
}

void ConsoleReporter::printTestFilters() {
    if (m_config-&gt;testSpec().hasFilters()) {
        Colour guard(Colour::BrightYellow);
        stream &lt;&lt; "Filters: " &lt;&lt; serializeFilters(m_config-&gt;getTestsOrTags()) &lt;&lt; '\n';
    }
}

CATCH_REGISTER_REPORTER("console", ConsoleReporter)

} // end namespace Catch

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#if defined(__clang__)
#  pragma clang diagnostic pop
#endif
// end catch_reporter_console.cpp
// start catch_reporter_junit.cpp

#include &lt;cassert&gt;
#include &lt;sstream&gt;
#include &lt;ctime&gt;
#include &lt;algorithm&gt;

namespace Catch {

    namespace {
        std::string getCurrentTimestamp() {
            // Beware, this is not reentrant because of backward compatibility issues
            // Also, UTC only, again because of backward compatibility (%z is C++11)
            time_t rawtime;
            std::time(&amp;rawtime);
            auto const timeStampSize = sizeof("2017-01-16T17:06:45Z");

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&amp;timeInfo, &amp;rawtime);
#else
            std::tm* timeInfo;
            timeInfo = std::gmtime(&amp;rawtime);
#endif

            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &amp;timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }

        std::string fileNameTag(const std::vector&lt;std::string&gt; &amp;tags) {
            auto it = std::find_if(begin(tags),
                                   end(tags),
                                   [] (std::string const&amp; tag) {return tag.front() == '#'; });
            if (it != tags.end())
                return it-&gt;substr(1);
            return std::string();
        }
    } // anonymous namespace

    JunitReporter::JunitReporter( ReporterConfig const&amp; _config )
        :   CumulativeReporterBase( _config ),
            xml( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = true;
            m_reporterPrefs.shouldReportAllAssertions = true;
        }

    JunitReporter::~JunitReporter() {}

    std::string JunitReporter::getDescription() {
        return "Reports test results in an XML format that looks like Ant's junitreport target";
    }

    void JunitReporter::noMatchingTestCases( std::string const&amp; /*spec*/ ) {}

    void JunitReporter::testRunStarting( TestRunInfo const&amp; runInfo )  {
        CumulativeReporterBase::testRunStarting( runInfo );
        xml.startElement( "testsuites" );
    }

    void JunitReporter::testGroupStarting( GroupInfo const&amp; groupInfo ) {
        suiteTimer.start();
        stdOutForSuite.clear();
        stdErrForSuite.clear();
        unexpectedExceptions = 0;
        CumulativeReporterBase::testGroupStarting( groupInfo );
    }

    void JunitReporter::testCaseStarting( TestCaseInfo const&amp; testCaseInfo ) {
        m_okToFail = testCaseInfo.okToFail();
    }

    bool JunitReporter::assertionEnded( AssertionStats const&amp; assertionStats ) {
        if( assertionStats.assertionResult.getResultType() == ResultWas::ThrewException &amp;&amp; !m_okToFail )
            unexpectedExceptions++;
        return CumulativeReporterBase::assertionEnded( assertionStats );
    }

    void JunitReporter::testCaseEnded( TestCaseStats const&amp; testCaseStats ) {
        stdOutForSuite += testCaseStats.stdOut;
        stdErrForSuite += testCaseStats.stdErr;
        CumulativeReporterBase::testCaseEnded( testCaseStats );
    }

    void JunitReporter::testGroupEnded( TestGroupStats const&amp; testGroupStats ) {
        double suiteTime = suiteTimer.getElapsedSeconds();
        CumulativeReporterBase::testGroupEnded( testGroupStats );
        writeGroup( *m_testGroups.back(), suiteTime );
    }

    void JunitReporter::testRunEndedCumulative() {
        xml.endElement();
    }

    void JunitReporter::writeGroup( TestGroupNode const&amp; groupNode, double suiteTime ) {
        XmlWriter::ScopedElement e = xml.scopedElement( "testsuite" );

        TestGroupStats const&amp; stats = groupNode.value;
        xml.writeAttribute( "name", stats.groupInfo.name );
        xml.writeAttribute( "errors", unexpectedExceptions );
        xml.writeAttribute( "failures", stats.totals.assertions.failed-unexpectedExceptions );
        xml.writeAttribute( "tests", stats.totals.assertions.total() );
        xml.writeAttribute( "hostname", "tbd" ); // !TBD
        if( m_config-&gt;showDurations() == ShowDurations::Never )
            xml.writeAttribute( "time", "" );
        else
            xml.writeAttribute( "time", suiteTime );
        xml.writeAttribute( "timestamp", getCurrentTimestamp() );

        // Write properties if there are any
        if (m_config-&gt;hasTestFilters() || m_config-&gt;rngSeed() != 0) {
            auto properties = xml.scopedElement("properties");
            if (m_config-&gt;hasTestFilters()) {
                xml.scopedElement("property")
                    .writeAttribute("name", "filters")
                    .writeAttribute("value", serializeFilters(m_config-&gt;getTestsOrTags()));
            }
            if (m_config-&gt;rngSeed() != 0) {
                xml.scopedElement("property")
                    .writeAttribute("name", "random-seed")
                    .writeAttribute("value", m_config-&gt;rngSeed());
            }
        }

        // Write test cases
        for( auto const&amp; child : groupNode.children )
            writeTestCase( *child );

        xml.scopedElement( "system-out" ).writeText( trim( stdOutForSuite ), XmlFormatting::Newline );
        xml.scopedElement( "system-err" ).writeText( trim( stdErrForSuite ), XmlFormatting::Newline );
    }

    void JunitReporter::writeTestCase( TestCaseNode const&amp; testCaseNode ) {
        TestCaseStats const&amp; stats = testCaseNode.value;

        // All test cases have exactly one section - which represents the
        // test case itself. That section may have 0-n nested sections
        assert( testCaseNode.children.size() == 1 );
        SectionNode const&amp; rootSection = *testCaseNode.children.front();

        std::string className = stats.testInfo.className;

        if( className.empty() ) {
            className = fileNameTag(stats.testInfo.tags);
            if ( className.empty() )
                className = "global";
        }

        if ( !m_config-&gt;name().empty() )
            className = m_config-&gt;name() + "." + className;

        writeSection( className, "", rootSection );
    }

    void JunitReporter::writeSection(  std::string const&amp; className,
                        std::string const&amp; rootName,
                        SectionNode const&amp; sectionNode ) {
        std::string name = trim( sectionNode.stats.sectionInfo.name );
        if( !rootName.empty() )
            name = rootName + '/' + name;

        if( !sectionNode.assertions.empty() ||
            !sectionNode.stdOut.empty() ||
            !sectionNode.stdErr.empty() ) {
            XmlWriter::ScopedElement e = xml.scopedElement( "testcase" );
            if( className.empty() ) {
                xml.writeAttribute( "classname", name );
                xml.writeAttribute( "name", "root" );
            }
            else {
                xml.writeAttribute( "classname", className );
                xml.writeAttribute( "name", name );
            }
            xml.writeAttribute( "time", ::Catch::Detail::stringify( sectionNode.stats.durationInSeconds ) );
            // This is not ideal, but it should be enough to mimic gtest's
            // junit output.
            // Ideally the JUnit reporter would also handle `skipTest`
            // events and write those out appropriately.
            xml.writeAttribute( "status", "run" );

            writeAssertions( sectionNode );

            if( !sectionNode.stdOut.empty() )
                xml.scopedElement( "system-out" ).writeText( trim( sectionNode.stdOut ), XmlFormatting::Newline );
            if( !sectionNode.stdErr.empty() )
                xml.scopedElement( "system-err" ).writeText( trim( sectionNode.stdErr ), XmlFormatting::Newline );
        }
        for( auto const&amp; childNode : sectionNode.childSections )
            if( className.empty() )
                writeSection( name, "", *childNode );
            else
                writeSection( className, name, *childNode );
    }

    void JunitReporter::writeAssertions( SectionNode const&amp; sectionNode ) {
        for( auto const&amp; assertion : sectionNode.assertions )
            writeAssertion( assertion );
    }

    void JunitReporter::writeAssertion( AssertionStats const&amp; stats ) {
        AssertionResult const&amp; result = stats.assertionResult;
        if( !result.isOk() ) {
            std::string elementName;
            switch( result.getResultType() ) {
                case ResultWas::ThrewException:
                case ResultWas::FatalErrorCondition:
                    elementName = "error";
                    break;
                case ResultWas::ExplicitFailure:
                case ResultWas::ExpressionFailed:
                case ResultWas::DidntThrowException:
                    elementName = "failure";
                    break;

                // We should never see these here:
                case ResultWas::Info:
                case ResultWas::Warning:
                case ResultWas::Ok:
                case ResultWas::Unknown:
                case ResultWas::FailureBit:
                case ResultWas::Exception:
                    elementName = "internalError";
                    break;
            }

            XmlWriter::ScopedElement e = xml.scopedElement( elementName );

            xml.writeAttribute( "message", result.getExpression() );
            xml.writeAttribute( "type", result.getTestMacroName() );

            ReusableStringStream rss;
            if (stats.totals.assertions.total() &gt; 0) {
                rss &lt;&lt; "FAILED" &lt;&lt; ":\n";
                if (result.hasExpression()) {
                    rss &lt;&lt; "  ";
                    rss &lt;&lt; result.getExpressionInMacro();
                    rss &lt;&lt; '\n';
                }
                if (result.hasExpandedExpression()) {
                    rss &lt;&lt; "with expansion:\n";
                    rss &lt;&lt; Column(result.getExpandedExpression()).indent(2) &lt;&lt; '\n';
                }
            } else {
                rss &lt;&lt; '\n';
            }

            if( !result.getMessage().empty() )
                rss &lt;&lt; result.getMessage() &lt;&lt; '\n';
            for( auto const&amp; msg : stats.infoMessages )
                if( msg.type == ResultWas::Info )
                    rss &lt;&lt; msg.message &lt;&lt; '\n';

            rss &lt;&lt; "at " &lt;&lt; result.getSourceInfo();
            xml.writeText( rss.str(), XmlFormatting::Newline );
        }
    }

    CATCH_REGISTER_REPORTER( "junit", JunitReporter )

} // end namespace Catch
// end catch_reporter_junit.cpp
// start catch_reporter_listening.cpp

#include &lt;cassert&gt;

namespace Catch {

    ListeningReporter::ListeningReporter() {
        // We will assume that listeners will always want all assertions
        m_preferences.shouldReportAllAssertions = true;
    }

    void ListeningReporter::addListener( IStreamingReporterPtr&amp;&amp; listener ) {
        m_listeners.push_back( std::move( listener ) );
    }

    void ListeningReporter::addReporter(IStreamingReporterPtr&amp;&amp; reporter) {
        assert(!m_reporter &amp;&amp; "Listening reporter can wrap only 1 real reporter");
        m_reporter = std::move( reporter );
        m_preferences.shouldRedirectStdOut = m_reporter-&gt;getPreferences().shouldRedirectStdOut;
    }

    ReporterPreferences ListeningReporter::getPreferences() const {
        return m_preferences;
    }

    std::set&lt;Verbosity&gt; ListeningReporter::getSupportedVerbosities() {
        return std::set&lt;Verbosity&gt;{ };
    }

    void ListeningReporter::noMatchingTestCases( std::string const&amp; spec ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;noMatchingTestCases( spec );
        }
        m_reporter-&gt;noMatchingTestCases( spec );
    }

    void ListeningReporter::reportInvalidArguments(std::string const&amp;arg){
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;reportInvalidArguments( arg );
        }
        m_reporter-&gt;reportInvalidArguments( arg );
    }

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    void ListeningReporter::benchmarkPreparing( std::string const&amp; name ) {
		for (auto const&amp; listener : m_listeners) {
			listener-&gt;benchmarkPreparing(name);
		}
		m_reporter-&gt;benchmarkPreparing(name);
	}
    void ListeningReporter::benchmarkStarting( BenchmarkInfo const&amp; benchmarkInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;benchmarkStarting( benchmarkInfo );
        }
        m_reporter-&gt;benchmarkStarting( benchmarkInfo );
    }
    void ListeningReporter::benchmarkEnded( BenchmarkStats&lt;&gt; const&amp; benchmarkStats ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;benchmarkEnded( benchmarkStats );
        }
        m_reporter-&gt;benchmarkEnded( benchmarkStats );
    }

	void ListeningReporter::benchmarkFailed( std::string const&amp; error ) {
		for (auto const&amp; listener : m_listeners) {
			listener-&gt;benchmarkFailed(error);
		}
		m_reporter-&gt;benchmarkFailed(error);
	}
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    void ListeningReporter::testRunStarting( TestRunInfo const&amp; testRunInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testRunStarting( testRunInfo );
        }
        m_reporter-&gt;testRunStarting( testRunInfo );
    }

    void ListeningReporter::testGroupStarting( GroupInfo const&amp; groupInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testGroupStarting( groupInfo );
        }
        m_reporter-&gt;testGroupStarting( groupInfo );
    }

    void ListeningReporter::testCaseStarting( TestCaseInfo const&amp; testInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testCaseStarting( testInfo );
        }
        m_reporter-&gt;testCaseStarting( testInfo );
    }

    void ListeningReporter::sectionStarting( SectionInfo const&amp; sectionInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;sectionStarting( sectionInfo );
        }
        m_reporter-&gt;sectionStarting( sectionInfo );
    }

    void ListeningReporter::assertionStarting( AssertionInfo const&amp; assertionInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;assertionStarting( assertionInfo );
        }
        m_reporter-&gt;assertionStarting( assertionInfo );
    }

    // The return value indicates if the messages buffer should be cleared:
    bool ListeningReporter::assertionEnded( AssertionStats const&amp; assertionStats ) {
        for( auto const&amp; listener : m_listeners ) {
            static_cast&lt;void&gt;( listener-&gt;assertionEnded( assertionStats ) );
        }
        return m_reporter-&gt;assertionEnded( assertionStats );
    }

    void ListeningReporter::sectionEnded( SectionStats const&amp; sectionStats ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;sectionEnded( sectionStats );
        }
        m_reporter-&gt;sectionEnded( sectionStats );
    }

    void ListeningReporter::testCaseEnded( TestCaseStats const&amp; testCaseStats ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testCaseEnded( testCaseStats );
        }
        m_reporter-&gt;testCaseEnded( testCaseStats );
    }

    void ListeningReporter::testGroupEnded( TestGroupStats const&amp; testGroupStats ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testGroupEnded( testGroupStats );
        }
        m_reporter-&gt;testGroupEnded( testGroupStats );
    }

    void ListeningReporter::testRunEnded( TestRunStats const&amp; testRunStats ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;testRunEnded( testRunStats );
        }
        m_reporter-&gt;testRunEnded( testRunStats );
    }

    void ListeningReporter::skipTest( TestCaseInfo const&amp; testInfo ) {
        for ( auto const&amp; listener : m_listeners ) {
            listener-&gt;skipTest( testInfo );
        }
        m_reporter-&gt;skipTest( testInfo );
    }

    bool ListeningReporter::isMulti() const {
        return true;
    }

} // end namespace Catch
// end catch_reporter_listening.cpp
// start catch_reporter_xml.cpp

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4061) // Not all labels are EXPLICITLY handled in switch
                              // Note that 4062 (not all labels are handled
                              // and default is missing) is enabled
#endif

namespace Catch {
    XmlReporter::XmlReporter( ReporterConfig const&amp; _config )
    :   StreamingReporterBase( _config ),
        m_xml(_config.stream())
    {
        m_reporterPrefs.shouldRedirectStdOut = true;
        m_reporterPrefs.shouldReportAllAssertions = true;
    }

    XmlReporter::~XmlReporter() = default;

    std::string XmlReporter::getDescription() {
        return "Reports test results as an XML document";
    }

    std::string XmlReporter::getStylesheetRef() const {
        return std::string();
    }

    void XmlReporter::writeSourceInfo( SourceLineInfo const&amp; sourceInfo ) {
        m_xml
            .writeAttribute( "filename", sourceInfo.file )
            .writeAttribute( "line", sourceInfo.line );
    }

    void XmlReporter::noMatchingTestCases( std::string const&amp; s ) {
        StreamingReporterBase::noMatchingTestCases( s );
    }

    void XmlReporter::testRunStarting( TestRunInfo const&amp; testInfo ) {
        StreamingReporterBase::testRunStarting( testInfo );
        std::string stylesheetRef = getStylesheetRef();
        if( !stylesheetRef.empty() )
            m_xml.writeStylesheetRef( stylesheetRef );
        m_xml.startElement( "Catch" );
        if( !m_config-&gt;name().empty() )
            m_xml.writeAttribute( "name", m_config-&gt;name() );
        if (m_config-&gt;testSpec().hasFilters())
            m_xml.writeAttribute( "filters", serializeFilters( m_config-&gt;getTestsOrTags() ) );
        if( m_config-&gt;rngSeed() != 0 )
            m_xml.scopedElement( "Randomness" )
                .writeAttribute( "seed", m_config-&gt;rngSeed() );
    }

    void XmlReporter::testGroupStarting( GroupInfo const&amp; groupInfo ) {
        StreamingReporterBase::testGroupStarting( groupInfo );
        m_xml.startElement( "Group" )
            .writeAttribute( "name", groupInfo.name );
    }

    void XmlReporter::testCaseStarting( TestCaseInfo const&amp; testInfo ) {
        StreamingReporterBase::testCaseStarting(testInfo);
        m_xml.startElement( "TestCase" )
            .writeAttribute( "name", trim( testInfo.name ) )
            .writeAttribute( "description", testInfo.description )
            .writeAttribute( "tags", testInfo.tagsAsString() );

        writeSourceInfo( testInfo.lineInfo );

        if ( m_config-&gt;showDurations() == ShowDurations::Always )
            m_testCaseTimer.start();
        m_xml.ensureTagClosed();
    }

    void XmlReporter::sectionStarting( SectionInfo const&amp; sectionInfo ) {
        StreamingReporterBase::sectionStarting( sectionInfo );
        if( m_sectionDepth++ &gt; 0 ) {
            m_xml.startElement( "Section" )
                .writeAttribute( "name", trim( sectionInfo.name ) );
            writeSourceInfo( sectionInfo.lineInfo );
            m_xml.ensureTagClosed();
        }
    }

    void XmlReporter::assertionStarting( AssertionInfo const&amp; ) { }

    bool XmlReporter::assertionEnded( AssertionStats const&amp; assertionStats ) {

        AssertionResult const&amp; result = assertionStats.assertionResult;

        bool includeResults = m_config-&gt;includeSuccessfulResults() || !result.isOk();

        if( includeResults || result.getResultType() == ResultWas::Warning ) {
            // Print any info messages in &lt;Info&gt; tags.
            for( auto const&amp; msg : assertionStats.infoMessages ) {
                if( msg.type == ResultWas::Info &amp;&amp; includeResults ) {
                    m_xml.scopedElement( "Info" )
                            .writeText( msg.message );
                } else if ( msg.type == ResultWas::Warning ) {
                    m_xml.scopedElement( "Warning" )
                            .writeText( msg.message );
                }
            }
        }

        // Drop out if result was successful but we're not printing them.
        if( !includeResults &amp;&amp; result.getResultType() != ResultWas::Warning )
            return true;

        // Print the expression if there is one.
        if( result.hasExpression() ) {
            m_xml.startElement( "Expression" )
                .writeAttribute( "success", result.succeeded() )
                .writeAttribute( "type", result.getTestMacroName() );

            writeSourceInfo( result.getSourceInfo() );

            m_xml.scopedElement( "Original" )
                .writeText( result.getExpression() );
            m_xml.scopedElement( "Expanded" )
                .writeText( result.getExpandedExpression() );
        }

        // And... Print a result applicable to each result type.
        switch( result.getResultType() ) {
            case ResultWas::ThrewException:
                m_xml.startElement( "Exception" );
                writeSourceInfo( result.getSourceInfo() );
                m_xml.writeText( result.getMessage() );
                m_xml.endElement();
                break;
            case ResultWas::FatalErrorCondition:
                m_xml.startElement( "FatalErrorCondition" );
                writeSourceInfo( result.getSourceInfo() );
                m_xml.writeText( result.getMessage() );
                m_xml.endElement();
                break;
            case ResultWas::Info:
                m_xml.scopedElement( "Info" )
                    .writeText( result.getMessage() );
                break;
            case ResultWas::Warning:
                // Warning will already have been written
                break;
            case ResultWas::ExplicitFailure:
                m_xml.startElement( "Failure" );
                writeSourceInfo( result.getSourceInfo() );
                m_xml.writeText( result.getMessage() );
                m_xml.endElement();
                break;
            default:
                break;
        }

        if( result.hasExpression() )
            m_xml.endElement();

        return true;
    }

    void XmlReporter::sectionEnded( SectionStats const&amp; sectionStats ) {
        StreamingReporterBase::sectionEnded( sectionStats );
        if( --m_sectionDepth &gt; 0 ) {
            XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResults" );
            e.writeAttribute( "successes", sectionStats.assertions.passed );
            e.writeAttribute( "failures", sectionStats.assertions.failed );
            e.writeAttribute( "expectedFailures", sectionStats.assertions.failedButOk );

            if ( m_config-&gt;showDurations() == ShowDurations::Always )
                e.writeAttribute( "durationInSeconds", sectionStats.durationInSeconds );

            m_xml.endElement();
        }
    }

    void XmlReporter::testCaseEnded( TestCaseStats const&amp; testCaseStats ) {
        StreamingReporterBase::testCaseEnded( testCaseStats );
        XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResult" );
        e.writeAttribute( "success", testCaseStats.totals.assertions.allOk() );

        if ( m_config-&gt;showDurations() == ShowDurations::Always )
            e.writeAttribute( "durationInSeconds", m_testCaseTimer.getElapsedSeconds() );

        if( !testCaseStats.stdOut.empty() )
            m_xml.scopedElement( "StdOut" ).writeText( trim( testCaseStats.stdOut ), XmlFormatting::Newline );
        if( !testCaseStats.stdErr.empty() )
            m_xml.scopedElement( "StdErr" ).writeText( trim( testCaseStats.stdErr ), XmlFormatting::Newline );

        m_xml.endElement();
    }

    void XmlReporter::testGroupEnded( TestGroupStats const&amp; testGroupStats ) {
        StreamingReporterBase::testGroupEnded( testGroupStats );
        // TODO: Check testGroupStats.aborting and act accordingly.
        m_xml.scopedElement( "OverallResults" )
            .writeAttribute( "successes", testGroupStats.totals.assertions.passed )
            .writeAttribute( "failures", testGroupStats.totals.assertions.failed )
            .writeAttribute( "expectedFailures", testGroupStats.totals.assertions.failedButOk );
        m_xml.scopedElement( "OverallResultsCases")
            .writeAttribute( "successes", testGroupStats.totals.testCases.passed )
            .writeAttribute( "failures", testGroupStats.totals.testCases.failed )
            .writeAttribute( "expectedFailures", testGroupStats.totals.testCases.failedButOk );
        m_xml.endElement();
    }

    void XmlReporter::testRunEnded( TestRunStats const&amp; testRunStats ) {
        StreamingReporterBase::testRunEnded( testRunStats );
        m_xml.scopedElement( "OverallResults" )
            .writeAttribute( "successes", testRunStats.totals.assertions.passed )
            .writeAttribute( "failures", testRunStats.totals.assertions.failed )
            .writeAttribute( "expectedFailures", testRunStats.totals.assertions.failedButOk );
        m_xml.scopedElement( "OverallResultsCases")
            .writeAttribute( "successes", testRunStats.totals.testCases.passed )
            .writeAttribute( "failures", testRunStats.totals.testCases.failed )
            .writeAttribute( "expectedFailures", testRunStats.totals.testCases.failedButOk );
        m_xml.endElement();
    }

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
    void XmlReporter::benchmarkPreparing(std::string const&amp; name) {
        m_xml.startElement("BenchmarkResults")
            .writeAttribute("name", name);
    }

    void XmlReporter::benchmarkStarting(BenchmarkInfo const &amp;info) {
        m_xml.writeAttribute("samples", info.samples)
            .writeAttribute("resamples", info.resamples)
            .writeAttribute("iterations", info.iterations)
            .writeAttribute("clockResolution", info.clockResolution)
            .writeAttribute("estimatedDuration", info.estimatedDuration)
            .writeComment("All values in nano seconds");
    }

    void XmlReporter::benchmarkEnded(BenchmarkStats&lt;&gt; const&amp; benchmarkStats) {
        m_xml.startElement("mean")
            .writeAttribute("value", benchmarkStats.mean.point.count())
            .writeAttribute("lowerBound", benchmarkStats.mean.lower_bound.count())
            .writeAttribute("upperBound", benchmarkStats.mean.upper_bound.count())
            .writeAttribute("ci", benchmarkStats.mean.confidence_interval);
        m_xml.endElement();
        m_xml.startElement("standardDeviation")
            .writeAttribute("value", benchmarkStats.standardDeviation.point.count())
            .writeAttribute("lowerBound", benchmarkStats.standardDeviation.lower_bound.count())
            .writeAttribute("upperBound", benchmarkStats.standardDeviation.upper_bound.count())
            .writeAttribute("ci", benchmarkStats.standardDeviation.confidence_interval);
        m_xml.endElement();
        m_xml.startElement("outliers")
            .writeAttribute("variance", benchmarkStats.outlierVariance)
            .writeAttribute("lowMild", benchmarkStats.outliers.low_mild)
            .writeAttribute("lowSevere", benchmarkStats.outliers.low_severe)
            .writeAttribute("highMild", benchmarkStats.outliers.high_mild)
            .writeAttribute("highSevere", benchmarkStats.outliers.high_severe);
        m_xml.endElement();
        m_xml.endElement();
    }

    void XmlReporter::benchmarkFailed(std::string const &amp;error) {
        m_xml.scopedElement("failed").
            writeAttribute("message", error);
        m_xml.endElement();
    }
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

    CATCH_REGISTER_REPORTER( "xml", XmlReporter )

} // end namespace Catch

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
// end catch_reporter_xml.cpp

namespace Catch {
    LeakDetector leakDetector;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_impl.hpp
#endif

#ifdef CATCH_CONFIG_MAIN
// start catch_default_main.hpp

#ifndef __OBJC__

#if defined(CATCH_CONFIG_WCHAR) &amp;&amp; defined(CATCH_PLATFORM_WINDOWS) &amp;&amp; defined(_UNICODE) &amp;&amp; !defined(DO_NOT_USE_WMAIN)
// Standard C/C++ Win32 Unicode wmain entry point
extern "C" int wmain (int argc, wchar_t * argv[], wchar_t * []) {
#else
// Standard C/C++ main entry point
int main (int argc, char * argv[]) {
#endif

    return Catch::Session().run( argc, argv );
}

#else // __OBJC__

// Objective-C entry point
int main (int argc, char * const argv[]) {
#if !CATCH_ARC_ENABLED
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#endif

    Catch::registerTestMethods();
    int result = Catch::Session().run( argc, (char**)argv );

#if !CATCH_ARC_ENABLED
    [pool drain];
#endif

    return result;
}

#endif // __OBJC__

// end catch_default_main.hpp
#endif

#if !defined(CATCH_CONFIG_IMPL_ONLY)

#ifdef CLARA_CONFIG_MAIN_NOT_DEFINED
#  undef CLARA_CONFIG_MAIN
#endif

#if !defined(CATCH_CONFIG_DISABLE)
//////
// If this config identifier is defined then all CATCH macros are prefixed with CATCH_
#ifdef CATCH_CONFIG_PREFIX_ALL

#define CATCH_REQUIRE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )

#define CATCH_REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "CATCH_REQUIRE_THROWS", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#define CATCH_REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif// CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CATCH_CHECK( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CATCH_CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CATCH_CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CATCH_CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CATCH_CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CATCH_CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#define CATCH_CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#define CATCH_REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define CATCH_INFO( msg ) INTERNAL_CATCH_INFO( "CATCH_INFO", msg )
#define CATCH_UNSCOPED_INFO( msg ) INTERNAL_CATCH_UNSCOPED_INFO( "CATCH_UNSCOPED_INFO", msg )
#define CATCH_WARN( msg ) INTERNAL_CATCH_MSG( "CATCH_WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define CATCH_CAPTURE( ... ) INTERNAL_CATCH_CAPTURE( INTERNAL_CATCH_UNIQUE_NAME(capturer), "CATCH_CAPTURE",__VA_ARGS__ )

#define CATCH_TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define CATCH_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define CATCH_REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define CATCH_SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define CATCH_DYNAMIC_SECTION( ... ) INTERNAL_CATCH_DYNAMIC_SECTION( __VA_ARGS__ )
#define CATCH_FAIL( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_SUCCEED( ... ) INTERNAL_CATCH_MSG( "CATCH_SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#define CATCH_ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define CATCH_TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG( __VA_ARGS__ )
#define CATCH_TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ )
#else
#define CATCH_TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ ) )
#define CATCH_TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG( __VA_ARGS__ ) )
#define CATCH_TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ ) )
#define CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ ) )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE( __VA_ARGS__ ) )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( __VA_ARGS__ ) )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, __VA_ARGS__ ) )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ ) )
#endif

#if !defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
#define CATCH_STATIC_REQUIRE( ... )       static_assert(   __VA_ARGS__ ,      #__VA_ARGS__ );     CATCH_SUCCEED( #__VA_ARGS__ )
#define CATCH_STATIC_REQUIRE_FALSE( ... ) static_assert( !(__VA_ARGS__), "!(" #__VA_ARGS__ ")" ); CATCH_SUCCEED( #__VA_ARGS__ )
#else
#define CATCH_STATIC_REQUIRE( ... )       CATCH_REQUIRE( __VA_ARGS__ )
#define CATCH_STATIC_REQUIRE_FALSE( ... ) CATCH_REQUIRE_FALSE( __VA_ARGS__ )
#endif

// "BDD-style" convenience wrappers
#define CATCH_SCENARIO( ... ) CATCH_TEST_CASE( "Scenario: " __VA_ARGS__ )
#define CATCH_SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )
#define CATCH_GIVEN( desc )     INTERNAL_CATCH_DYNAMIC_SECTION( "    Given: " &lt;&lt; desc )
#define CATCH_AND_GIVEN( desc ) INTERNAL_CATCH_DYNAMIC_SECTION( "And given: " &lt;&lt; desc )
#define CATCH_WHEN( desc )      INTERNAL_CATCH_DYNAMIC_SECTION( "     When: " &lt;&lt; desc )
#define CATCH_AND_WHEN( desc )  INTERNAL_CATCH_DYNAMIC_SECTION( " And when: " &lt;&lt; desc )
#define CATCH_THEN( desc )      INTERNAL_CATCH_DYNAMIC_SECTION( "     Then: " &lt;&lt; desc )
#define CATCH_AND_THEN( desc )  INTERNAL_CATCH_DYNAMIC_SECTION( "      And: " &lt;&lt; desc )

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
#define CATCH_BENCHMARK(...) \
    INTERNAL_CATCH_BENCHMARK(INTERNAL_CATCH_UNIQUE_NAME(____C_A_T_C_H____B_E_N_C_H____), INTERNAL_CATCH_GET_1_ARG(__VA_ARGS__,,), INTERNAL_CATCH_GET_2_ARG(__VA_ARGS__,,))
#define CATCH_BENCHMARK_ADVANCED(name) \
    INTERNAL_CATCH_BENCHMARK_ADVANCED(INTERNAL_CATCH_UNIQUE_NAME(____C_A_T_C_H____B_E_N_C_H____), name)
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

// If CATCH_CONFIG_PREFIX_ALL is not defined then the CATCH_ prefix is not required
#else

#define REQUIRE( ... ) INTERNAL_CATCH_TEST( "REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__  )
#define REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )

#define REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "REQUIRE_THROWS", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#define REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CHECK( ... ) INTERNAL_CATCH_TEST( "CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#define CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#define REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define INFO( msg ) INTERNAL_CATCH_INFO( "INFO", msg )
#define UNSCOPED_INFO( msg ) INTERNAL_CATCH_UNSCOPED_INFO( "UNSCOPED_INFO", msg )
#define WARN( msg ) INTERNAL_CATCH_MSG( "WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define CAPTURE( ... ) INTERNAL_CATCH_CAPTURE( INTERNAL_CATCH_UNIQUE_NAME(capturer), "CAPTURE",__VA_ARGS__ )

#define TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define DYNAMIC_SECTION( ... ) INTERNAL_CATCH_DYNAMIC_SECTION( __VA_ARGS__ )
#define FAIL( ... ) INTERNAL_CATCH_MSG( "FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define SUCCEED( ... ) INTERNAL_CATCH_MSG( "SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG( __VA_ARGS__ )
#define TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ )
#define TEMPLATE_LIST_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE(__VA_ARGS__)
#define TEMPLATE_LIST_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD( className, __VA_ARGS__ )
#else
#define TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ ) )
#define TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG( __VA_ARGS__ ) )
#define TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ ) )
#define TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ ) )
#define TEMPLATE_PRODUCT_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE( __VA_ARGS__ ) )
#define TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( __VA_ARGS__ ) )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, __VA_ARGS__ ) )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, __VA_ARGS__ ) )
#define TEMPLATE_LIST_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE( __VA_ARGS__ ) )
#define TEMPLATE_LIST_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_LIST_TEST_CASE_METHOD( className, __VA_ARGS__ ) )
#endif

#if !defined(CATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
#define STATIC_REQUIRE( ... )       static_assert(   __VA_ARGS__,  #__VA_ARGS__ ); SUCCEED( #__VA_ARGS__ )
#define STATIC_REQUIRE_FALSE( ... ) static_assert( !(__VA_ARGS__), "!(" #__VA_ARGS__ ")" ); SUCCEED( "!(" #__VA_ARGS__ ")" )
#else
#define STATIC_REQUIRE( ... )       REQUIRE( __VA_ARGS__ )
#define STATIC_REQUIRE_FALSE( ... ) REQUIRE_FALSE( __VA_ARGS__ )
#endif

#endif

#define CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature )

// "BDD-style" convenience wrappers
#define SCENARIO( ... ) TEST_CASE( "Scenario: " __VA_ARGS__ )
#define SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )

#define GIVEN( desc )     INTERNAL_CATCH_DYNAMIC_SECTION( "    Given: " &lt;&lt; desc )
#define AND_GIVEN( desc ) INTERNAL_CATCH_DYNAMIC_SECTION( "And given: " &lt;&lt; desc )
#define WHEN( desc )      INTERNAL_CATCH_DYNAMIC_SECTION( "     When: " &lt;&lt; desc )
#define AND_WHEN( desc )  INTERNAL_CATCH_DYNAMIC_SECTION( " And when: " &lt;&lt; desc )
#define THEN( desc )      INTERNAL_CATCH_DYNAMIC_SECTION( "     Then: " &lt;&lt; desc )
#define AND_THEN( desc )  INTERNAL_CATCH_DYNAMIC_SECTION( "      And: " &lt;&lt; desc )

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
#define BENCHMARK(...) \
    INTERNAL_CATCH_BENCHMARK(INTERNAL_CATCH_UNIQUE_NAME(____C_A_T_C_H____B_E_N_C_H____), INTERNAL_CATCH_GET_1_ARG(__VA_ARGS__,,), INTERNAL_CATCH_GET_2_ARG(__VA_ARGS__,,))
#define BENCHMARK_ADVANCED(name) \
    INTERNAL_CATCH_BENCHMARK_ADVANCED(INTERNAL_CATCH_UNIQUE_NAME(____C_A_T_C_H____B_E_N_C_H____), name)
#endif // CATCH_CONFIG_ENABLE_BENCHMARKING

using Catch::Detail::Approx;

#else // CATCH_CONFIG_DISABLE

//////
// If this config identifier is defined then all CATCH macros are prefixed with CATCH_
#ifdef CATCH_CONFIG_PREFIX_ALL

#define CATCH_REQUIRE( ... )        (void)(0)
#define CATCH_REQUIRE_FALSE( ... )  (void)(0)

#define CATCH_REQUIRE_THROWS( ... ) (void)(0)
#define CATCH_REQUIRE_THROWS_AS( expr, exceptionType ) (void)(0)
#define CATCH_REQUIRE_THROWS_WITH( expr, matcher )     (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif// CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_REQUIRE_NOTHROW( ... ) (void)(0)

#define CATCH_CHECK( ... )         (void)(0)
#define CATCH_CHECK_FALSE( ... )   (void)(0)
#define CATCH_CHECKED_IF( ... )    if (__VA_ARGS__)
#define CATCH_CHECKED_ELSE( ... )  if (!(__VA_ARGS__))
#define CATCH_CHECK_NOFAIL( ... )  (void)(0)

#define CATCH_CHECK_THROWS( ... )  (void)(0)
#define CATCH_CHECK_THROWS_AS( expr, exceptionType ) (void)(0)
#define CATCH_CHECK_THROWS_WITH( expr, matcher )     (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_CHECK_NOTHROW( ... ) (void)(0)

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THAT( arg, matcher )   (void)(0)

#define CATCH_REQUIRE_THAT( arg, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define CATCH_INFO( msg )          (void)(0)
#define CATCH_UNSCOPED_INFO( msg ) (void)(0)
#define CATCH_WARN( msg )          (void)(0)
#define CATCH_CAPTURE( msg )       (void)(0)

#define CATCH_TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_METHOD_AS_TEST_CASE( method, ... )
#define CATCH_REGISTER_TEST_CASE( Function, ... ) (void)(0)
#define CATCH_SECTION( ... )
#define CATCH_DYNAMIC_SECTION( ... )
#define CATCH_FAIL( ... ) (void)(0)
#define CATCH_FAIL_CHECK( ... ) (void)(0)
#define CATCH_SUCCEED( ... ) (void)(0)

#define CATCH_ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define CATCH_TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(__VA_ARGS__)
#define CATCH_TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(__VA_ARGS__)
#define CATCH_TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION(className, __VA_ARGS__)
#define CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION(className, __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE( ... ) CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#else
#define CATCH_TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(__VA_ARGS__) )
#define CATCH_TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(__VA_ARGS__) )
#define CATCH_TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION(className, __VA_ARGS__ ) )
#define CATCH_TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION(className, __VA_ARGS__ ) )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE( ... ) CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) CATCH_TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) CATCH_TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#endif

// "BDD-style" convenience wrappers
#define CATCH_SCENARIO( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define CATCH_SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), className )
#define CATCH_GIVEN( desc )
#define CATCH_AND_GIVEN( desc )
#define CATCH_WHEN( desc )
#define CATCH_AND_WHEN( desc )
#define CATCH_THEN( desc )
#define CATCH_AND_THEN( desc )

#define CATCH_STATIC_REQUIRE( ... )       (void)(0)
#define CATCH_STATIC_REQUIRE_FALSE( ... ) (void)(0)

// If CATCH_CONFIG_PREFIX_ALL is not defined then the CATCH_ prefix is not required
#else

#define REQUIRE( ... )       (void)(0)
#define REQUIRE_FALSE( ... ) (void)(0)

#define REQUIRE_THROWS( ... ) (void)(0)
#define REQUIRE_THROWS_AS( expr, exceptionType ) (void)(0)
#define REQUIRE_THROWS_WITH( expr, matcher ) (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define REQUIRE_NOTHROW( ... ) (void)(0)

#define CHECK( ... ) (void)(0)
#define CHECK_FALSE( ... ) (void)(0)
#define CHECKED_IF( ... ) if (__VA_ARGS__)
#define CHECKED_ELSE( ... ) if (!(__VA_ARGS__))
#define CHECK_NOFAIL( ... ) (void)(0)

#define CHECK_THROWS( ... )  (void)(0)
#define CHECK_THROWS_AS( expr, exceptionType ) (void)(0)
#define CHECK_THROWS_WITH( expr, matcher ) (void)(0)
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CHECK_NOTHROW( ... ) (void)(0)

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THAT( arg, matcher ) (void)(0)

#define REQUIRE_THAT( arg, matcher ) (void)(0)
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define INFO( msg ) (void)(0)
#define UNSCOPED_INFO( msg ) (void)(0)
#define WARN( msg ) (void)(0)
#define CAPTURE( msg ) (void)(0)

#define TEST_CASE( ... )  INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))
#define METHOD_AS_TEST_CASE( method, ... )
#define REGISTER_TEST_CASE( Function, ... ) (void)(0)
#define SECTION( ... )
#define DYNAMIC_SECTION( ... )
#define FAIL( ... ) (void)(0)
#define FAIL_CHECK( ... ) (void)(0)
#define SUCCEED( ... ) (void)(0)
#define ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ))

#ifndef CATCH_CONFIG_TRADITIONAL_MSVC_PREPROCESSOR
#define TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(__VA_ARGS__)
#define TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(__VA_ARGS__)
#define TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION(className, __VA_ARGS__)
#define TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION(className, __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE( ... ) TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#else
#define TEMPLATE_TEST_CASE( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_NO_REGISTRATION(__VA_ARGS__) )
#define TEMPLATE_TEST_CASE_SIG( ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_SIG_NO_REGISTRATION(__VA_ARGS__) )
#define TEMPLATE_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_NO_REGISTRATION(className, __VA_ARGS__ ) )
#define TEMPLATE_TEST_CASE_METHOD_SIG( className, ... ) INTERNAL_CATCH_EXPAND_VARGS( INTERNAL_CATCH_TEMPLATE_TEST_CASE_METHOD_SIG_NO_REGISTRATION(className, __VA_ARGS__ ) )
#define TEMPLATE_PRODUCT_TEST_CASE( ... ) TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_SIG( ... ) TEMPLATE_TEST_CASE( __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD( className, ... ) TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG( className, ... ) TEMPLATE_TEST_CASE_METHOD( className, __VA_ARGS__ )
#endif

#define STATIC_REQUIRE( ... )       (void)(0)
#define STATIC_REQUIRE_FALSE( ... ) (void)(0)

#endif

#define CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION_NO_REG( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// "BDD-style" convenience wrappers
#define SCENARIO( ... ) INTERNAL_CATCH_TESTCASE_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ) )
#define SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TESTCASE_METHOD_NO_REGISTRATION(INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), className )

#define GIVEN( desc )
#define AND_GIVEN( desc )
#define WHEN( desc )
#define AND_WHEN( desc )
#define THEN( desc )
#define AND_THEN( desc )

using Catch::Detail::Approx;

#endif

#endif // ! CATCH_CONFIG_IMPL_ONLY

// start catch_reenable_warnings.h


#ifdef __clang__
#    ifdef __ICC // icpc defines the __clang__ macro
#        pragma warning(pop)
#    else
#        pragma clang diagnostic pop
#    endif
#elif defined __GNUC__
#    pragma GCC diagnostic pop
#endif

// end catch_reenable_warnings.h
// end catch.hpp
#endif // TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED

</pre></body></html>