// unicode_formal.h                                                   -*-C++-*-
#ifndef INCLUDED_UNICODE_FORMAL
#define INCLUDED_UNICODE_FORMAL

#include <iostream>

namespace unicode_formal {
// codepoints
/**
 * Is this code point a Unicode non-character?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_unicode_nonchar(char32_t codepoint) noexcept;

/**
 * Is this code point one that can be assigned a character?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_unicode_char(char32_t codepoint) noexcept;

/**
 * Is this code point in the Basic Multilingual Plane (U+0000..U+ffff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_bmp(char32_t codepoint) noexcept;

/**
 * Is this code point supplementary code point (U+10000..U+10ffff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_supplementary(char32_t codepoint) noexcept;

/**
 * Is this code point a lead surrogate (U+d800..U+dbff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_lead(char32_t codepoint) noexcept;

/**
 * Is this code point a trail surrogate (U+dc00..U+dfff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_trail(char32_t codepoint) noexcept;

/**
 * Is this code point a surrogate (U+d800..U+dfff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
inline constexpr bool is_surrogate(char32_t codepoint) noexcept;

// The following are ICU API that are unsafe but provide no benfit
// /**
//  * Is this code point a lead surrogate (U+d800..U+dbff)?
//  * @param codepoint 32-bit code point
//  * @return true or false
//  * @pre is_surrogate(codepoint)
//  */
// inline constexpr bool is_surrogate_lead(char32_t codepoint) noexcept;

// /**
//  * Is this code point a trail surrogate (U+dc00..U+dfff)?
//  * @param codepoint 32-bit code point
//  * @return true or false
//  * @pre is_surrogate(codepoint)
//  */
// inline constexpr bool is_surrogate_trail(char32_t codepoint) noexcept;

// utf-16

/**
 * Does this code unit alone encode a full non-surrogate code point?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
inline constexpr bool is_single(char16_t codeunit) noexcept;

/**
 * Is this code unit a lead surrogate (U+d800..U+dbff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
inline constexpr bool is_lead(char16_t codeunit) noexcept;

/**
 * Is this code unit a trail surrogate (U+dc00..U+dfff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
inline constexpr bool is_trail(char16_t codeunit) noexcept;

/**
 * Is this code unit a surrogate (U+d800..U+dfff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
inline constexpr bool is_surrogate(char16_t codeunit) noexcept;

// The following are ICU API that are unsafe but provide no benfit

// inline constexpr bool is_surrogate_lead(char16_t codeunit) noexcept;

// inline constexpr bool is_surrogate_trail(char16_t codeunit) noexcept;

/**
 * Code point offset for surrogate pair calculation
 */
inline constexpr unsigned long surrogate_offset() noexcept;

/**
 * Calculate a supplementary code point value (U+10000..U+10ffff)
 * from a pair of its lead and trail surrogates.
 * The result is unspecified if the input values are not
 * lead and trail surrogates.
 *
 * @param lead lead surrogate (U+d800..U+dbff)
 * @param trail trail surrogate (U+dc00..U+dfff)
 * @return supplementary code point (U+10000..U+10ffff)
 */
inline constexpr char32_t get_supplementary(char32_t lead,
                                            char32_t trail) noexcept;

/**
 * The lead surrogate code unit (0xd800..0xdbff) for a
 * supplementary code point (0x10000..0x10ffff).
 * The result is unspecified if the code point is not assignable.
 * @param supplementary 32-bit code point
 * @return lead surrogate
 */
inline constexpr char16_t surrogate_lead(char32_t supplementary) noexcept;

/**
 * The trail surrogate code unit (0xdc00..0xdfff) for a
 * supplementary code point (0x10000..0x10ffff).
 * The result is unspecified if the code point is not assignable.
 * @param supplementary 32-bit code point
 * @return lead surrogate
 */
inline constexpr char16_t surrogate_trail(char32_t supplementary) noexcept;

/**
 * The number of char16_t code units necessary to encode the code point.
 * The result is unspecified if the code point is not assignable.
 * @param codepoint 32-bit code point
 * @return 1 or 2
 */
inline constexpr int utf16_length(char32_t codepoint) noexcept;

/**
 * The maximum number of char16_t code units necessary to encode any code
 * point. The result is unspecified if the code point is not assignable.
 * @return 2
 */
inline constexpr int utf16_max_length() noexcept;

// utf-8
/**
 * Does this code unit encode a code point by itself, equivalent to 7 bit
 * US-ASCII (0..0x7f)?
 * @param codeunit 8-bit code unit
 * @return true or false
 */
inline constexpr bool is_utf8_single(char8_t codeunit) noexcept;

/**
 * Is this code unit (byte) a well-formed UTF-8 lead byte? (0xC2..0xF4)
 * @param codeunit 8-bit code unit
 * @return true or false
 */
inline constexpr bool is_utf8_lead(char8_t codeunit) noexcept;

/**
 * Is this code unit (byte) a well-formed UTF-8 trail byte? (0x80..0xBF)
 * @param codeunit 8-bit code unit
 * @return true or false
 */
inline constexpr bool is_utf8_trail(char8_t codeunit) noexcept;

/**
 * Counts the trail bytes for a UTF-8 lead byte.
 * Returns 0 for 0..0xc1 as well as for 0xf5..0xff.
 *
 * @param leadByte The first byte of a UTF-8 sequence.
 */
inline constexpr int count_utf8_trail_bytes(char8_t leadByte) noexcept;

/**
 * Counts the trail bytes for a UTF-8 lead byte.
 * Unspecified if the leadByte is not well-formed.
 * Does not branch.
 *
 * @param leadByte The first byte of a UTF-8 sequence.
 */
inline constexpr int count_utf8_trail_bytes_unsafe(char8_t leadByte) noexcept;

/**
 * How many code units are used for the UTF-8 encoding of the codepoint
 * @param codepoint 32-bit code point
 * @return 1..4, or 0 if c is a surrogate or not a Unicode code point
 */
inline constexpr int utf8_length(char32_t codepoint) noexcept;

/**
 * The maximum number of char8_t code units necessary to encode any code
 * point. The result is unspecified if the code point is not assignable.
 * @return 4
 */
inline constexpr int utf8_max_length() noexcept;

// Implementation

// codepoint
inline constexpr bool is_unicode_nonchar(char32_t codepoint) noexcept {
    return (codepoint >= 0xfdd0 &&
            (codepoint <= 0xfdef || (codepoint & 0xfffe) == 0xfffe) &&
            codepoint <= 0x10ffff);
}

inline constexpr bool is_unicode_char(char32_t codepoint) noexcept {
    return (static_cast<uint32_t>(codepoint) < 0xd800 ||
            (0xdfff < codepoint && codepoint <= 0x10ffff &&
             !is_unicode_nonchar(codepoint)));
}

inline constexpr bool is_bmp(char32_t codepoint) noexcept {
    return (static_cast<uint32_t>(codepoint) <= 0xffff);
}

inline constexpr bool is_supplementary(char32_t codepoint) noexcept {
    return (static_cast<uint32_t>(codepoint - 0x10000) <= 0xfffff);
}

inline constexpr bool is_lead(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffffc00) == 0xd800);
}

inline constexpr bool is_trail(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffffc00) == 0xdc00);
}

inline constexpr bool is_surrogate(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffff800) == 0xd800);
}

// The following are ICU API that are unsafe but provide no benfit

// inline constexpr bool is_surrogate_lead(char32_t codepoint) noexcept {
//     return ((codepoint & 0x400) == 0);
// }

// inline constexpr bool is_surrogate_trail(char32_t codepoint) noexcept {
//     return ((codepoint & 0x400) != 0);
// }

// UTF-16
inline constexpr bool is_single(char16_t codeunit) noexcept {
    return !is_surrogate(static_cast<char32_t>(codeunit));
}

inline constexpr bool is_lead(char16_t codeunit) noexcept {
    return (((codeunit)&0xfffffc00) == 0xd800);
}

inline constexpr bool is_trail(char16_t codeunit) noexcept {
    return (((codeunit)&0xfffffc00) == 0xdc00);
}

inline constexpr bool is_surrogate(char16_t codeunit) noexcept {
    return is_surrogate(static_cast<char32_t>(codeunit));
}

// The following are ICU API that are unsafe but provide no benfit

// inline constexpr bool is_surrogate_lead(char16_t codeunit) noexcept {
//     return (((codeunit)&0x400) == 0);
// }

// inline constexpr bool is_surrogate_trail(char16_t codeunit) noexcept {
//     return (((codeunit)&0x400) != 0);
// }

inline constexpr unsigned long surrogate_offset() noexcept {
    return ((0xd800 << 10UL) + 0xdc00 - 0x10000);
}

inline constexpr char32_t get_supplementary(char32_t lead,
                                            char32_t trail) noexcept {
    return ((static_cast<char32_t>(lead) << 10UL) +
            static_cast<char32_t>(trail) - surrogate_offset());
}

inline constexpr char16_t surrogate_lead(char32_t supplementary) noexcept {
    return (((supplementary) >> 10) + 0xd7c0);
}

inline constexpr char16_t surrogate_trail(char32_t supplementary) noexcept {
    return (((supplementary)&0x3ff) | 0xdc00);
}

inline constexpr int utf16_length(char32_t codeunit) noexcept {
    return (static_cast<uint32_t>(codeunit) <= 0xffff ? 1 : 2);
}

inline constexpr int utf16_max_length() noexcept { return 2; }

// UTF-8

inline constexpr bool is_utf8_single(char8_t c) noexcept {
    return ((c & 0x80) == 0);
}

inline constexpr bool is_utf8_lead(char8_t c) noexcept {
    return (static_cast<uint8_t>(c - 0xc2) <= 0x32);
}

inline constexpr bool is_utf8_trail(char8_t c) noexcept {
    return (static_cast<int8_t>(c) < -0x40);
}

inline constexpr int count_utf8_trail_bytes(char8_t leadByte) noexcept {
    return is_utf8_lead(leadByte)
               ? (static_cast<uint8_t>(leadByte) >= 0xe0) +
                     (static_cast<uint8_t>(leadByte) >= 0xf0) + 1
               : 0;
}

inline constexpr int count_utf8_trail_bytes_unsafe(char8_t leadByte) noexcept {
    return ((static_cast<uint8_t>(leadByte) >= 0xc2) +
            (static_cast<uint8_t>(leadByte) >= 0xe0) +
            (static_cast<uint8_t>(leadByte) >= 0xf0));
}

inline constexpr int utf8_length(char32_t codepoint) noexcept {
    return (
        static_cast<uint32_t>(codepoint) <= 0x7f
            ? 1
            : (static_cast<uint32_t>(codepoint) <= 0x7ff
                   ? 2
                   : (static_cast<uint32_t>(codepoint) <= 0xd7ff
                          ? 3
                          : (static_cast<uint32_t>(codepoint) <= 0xdfff ||
                                     static_cast<uint32_t>(codepoint) >
                                         0x10ffff
                                 ? 0
                                 : (static_cast<uint32_t>(codepoint) <= 0xffff
                                        ? 3
                                        : 4)))));
}

inline constexpr int utf8_max_length() noexcept { return 4; }

} // namespace unicode_formal

#endif
