#if !defined(__MATH_APPLEEXTS_H__) /* guard */
#define __MATH_APPLEEXTS_H__ /* guard */

#if !defined(__MATH__NO_APPLE_EXTENSIONS)

#include <sys/cdefs.h>

/* Apple's Extensions to Exponential Functions */
/* =========================================== */

/* __exp10[f]: calculate 10**x */
extern double   __exp10(double x);
extern float    __exp10f(float x);

/* Apple's Extensions to Trigonometric Functions */
/* ============================================= */

/* [sin|cos|tan]pi[f]: calculate the sine, cosine or tangent of the product
 * of pi and x. */
extern double   __sinpi(double x);
extern float    __sinpif(float x);
extern double   __cospi(double x);
extern float    __cospif(float x);
extern double   __tanpi(double x);
extern float    __tanpif(float x);

/* __double_double      Return type for __sincos_stret
 * __float_float        Return type for __sincosf_stret
 *
 * __sincos[f]_stret    Return a structure containing the sine and cosine of x.
 *                      Used internally by __sincos[f].
 *                      Do not use this function directly, instead use
 *                      __sincos[f], and allow the compiler to automatically
 *                      generate calls to it.
 * __sincospi[f]_stret  Return a structure containing the sine and cosine of
 *                      the product of pi and x.
 *                      Used internally by __sincospi[f].
 *                      Do not use this function directly, instead use
 *                      __sincospi[f], and allow the compiler to automatically
 *                      generate calls to it.
 */
struct __double_double {
    double  __sin_result;
    double  __cos_result;
};

struct __float_float {
    float   __sin_result;
    float   __cos_result;
};

extern struct __double_double   __sincos_stret(double x);
extern struct __float_float     __sincosf_stret(float x);
extern struct __double_double   __sincospi_stret(double x);
extern struct __float_float     __sincospif_stret(float x);

#if defined(__APPLEEXT_NO_USE_SINCOS_STRET__)
/* If we have __sincos[pi][f]_stret available, mimic the behaivour on macOS
 * and use that, else just use split these functions into different calls.
 * Which is probably going to be quicker since I haven't bothered to
 * optimise any of these. */

 /* __sincos[f]: calculate the sine and cosine of x in one function call */
__header_always_inline void
__sincos(double x, double *__sin_result, double *__cos_result)
{
    (*__sin_result) = sin(x);
    (*__cos_result) = cos(x);
}

__header_always_inline void
__sincosf(float x, float *__sin_result, float *__cos_result)
{
    (*__sin_result) = sinf(x);
    (*__cos_result) = cosf(x);
}

/* __sincospi[f]: calculate the sine and cosine of the product of pi and x in
 * one function call */
__header_always_inline void
__sincospi(double x, double *__sin_result, double *__cos_result)
{
    (*__sin_result) = __sinpi(x);
    (*__cos_result) = __cospi(x);
}

__header_always_inline void
__sincospif(float x, float *__sin_result, float *__cos_result)
{
    (*__sin_result) = __sinpif(x);
    (*__cos_result) = __cospif(x);
}
#else /* !defined(__APPLEEXT_NO_USE_SINCOS_STRET__) */
__header_always_inline void
__sincos(double x, double *__sin_result, double *__cos_result)
{
    const struct __double_double    __stret = __sincos_stret(x);

    (*__sin_result) = __stret.__sin_result;
    (*__cos_result) = __stret.__cos_result;
}

__header_always_inline void
__sincosf(float  x, float  *__sin_result, float  *__cos_result)
{
    const struct __float_float      __stret = __sincosf_stret(x);

    (*__sin_result) = __stret.__sin_result;
    (*__cos_result) = __stret.__cos_result;
}

__header_always_inline void
__sincospi(double x, double *__sin_result, double *__cos_result)
{
    const struct __double_double    __stret = __sincospi_stret(x);

    (*__sin_result) = __stret.__sin_result;
    (*__cos_result) = __stret.__cos_result;
}

__header_always_inline void
__sincospif(float  x, float  *__sin_result, float  *__cos_result)
{
    const struct __float_float      __stret = __sincospif_stret(x);

    (*__sin_result) = __stret.__sin_result;
    (*__cos_result) = __stret.__cos_result;
}
#endif /* defined(__APPLEEXT_NO_USE_SINCOS_STRET__) */

#endif /* !defined(__MATH__NO_APPLE_EXTENSIONS) */

#endif /* guard: defined(__MATH_APPLEEXTS_H__) */
