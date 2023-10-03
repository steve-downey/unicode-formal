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
constexpr bool is_unicode_nonchar(char32_t codepoint) noexcept;

/**
 * Is this code point one that can be assigned a character?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_unicode_char(char32_t codepoint) noexcept;

/**
 * Is this code point in the Basic Multilingual Plane (U+0000..U+ffff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_bmp(char32_t codepoint) noexcept;

/**
 * Is this code point supplementary code point (U+10000..U+10ffff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_supplementary(char32_t codepoint) noexcept;

/**
 * Is this code point a high surrogate (U+d800..U+dbff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_high_surrogate(char32_t codepoint) noexcept;

/**
 * Is this code point a low surrogate (U+dc00..U+dfff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_low_surrogate(char32_t codepoint) noexcept;

/**
 * Is this code point a surrogate (U+d800..U+dfff)?
 * @param codepoint 32-bit code point
 * @return true or false
 */
constexpr bool is_surrogate(char32_t codepoint) noexcept;


// utf-16

/**
 * Does this code unit alone encode a full non-surrogate code point?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
constexpr bool is_single(char16_t codeunit) noexcept;

/**
 * Is this code unit a high surrogate (U+d800..U+dbff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
constexpr bool is_high_surrogate(char16_t codeunit) noexcept;

/**
 * Is this code unit a low surrogate (U+dc00..U+dfff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
constexpr bool is_low_surrogate(char16_t codeunit) noexcept;

/**
 * Is this code unit a surrogate (U+d800..U+dfff)?
 * @param codeunit 16-bit code unit
 * @return true or false
 */
constexpr bool is_surrogate(char16_t codeunit) noexcept;


/**
 * Code point offset for surrogate pair calculation
 */
constexpr unsigned long surrogate_offset() noexcept;

/**
 * Calculate a supplementary code point value (U+10000..U+10ffff)
 * from a pair of its high and low surrogates.
 * The result is unspecified if the input values are not
 * high and low surrogates.
 *
 * @param high high surrogate (U+d800..U+dbff)
 * @param low low surrogate (U+dc00..U+dfff)
 * @return supplementary code point (U+10000..U+10ffff)
 */
constexpr char32_t get_supplementary(char32_t high, char32_t low) noexcept;

/**
 * The high surrogate code unit (0xd800..0xdbff) for a
 * supplementary code point (0x10000..0x10ffff).
 * The result is unspecified if the code point is not assignable.
 * @param supplementary 32-bit code point
 * @return high surrogate
 */
constexpr char16_t surrogate_high(char32_t supplementary) noexcept;

/**
 * The low surrogate code unit (0xdc00..0xdfff) for a
 * supplementary code point (0x10000..0x10ffff).
 * The result is unspecified if the code point is not assignable.
 * @param supplementary 32-bit code point
 * @return high surrogate
 */
constexpr char16_t surrogate_low(char32_t supplementary) noexcept;

/**
 * The number of char16_t code units necessary to encode the code point.
 * The result is unspecified if the code point is not assignable.
 * @param codepoint 32-bit code point
 * @return 1 or 2
 */
constexpr int utf16_length(char32_t codepoint) noexcept;

/**
 * The maximum number of char16_t code units necessary to encode any code
 * point. The result is unspecified if the code point is not assignable.
 * @return 2
 */
constexpr int utf16_max_length() noexcept;

// utf-8
/**
 * Does this code unit encode a code point by itself, equivalent to 7 bit
 * US-ASCII (0..0x7f)?
 * @param codeunit 8-bit code unit
 * @return true or false
 */
constexpr bool is_utf8_single(char8_t codeunit) noexcept;

/**
 * Is this code unit (byte) a well-formed UTF-8 lead byte? (0xC2..0xF4)
 * @param codeunit 8-bit code unit
 * @return true or false
 */
constexpr bool is_utf8_lead(char8_t codeunit) noexcept;

/**
 * Is this code unit (byte) a well-formed UTF-8 trail byte? (0x80..0xBF)
 * @param codeunit 8-bit code unit
 * @return true or false
 */
constexpr bool is_utf8_trail(char8_t codeunit) noexcept;

/**
 * Counts the trail bytes for a UTF-8 lead byte.
 * Returns 0 for 0..0xc1 as well as for 0xf5..0xff.
 *
 * @param lead_byte The first byte of a UTF-8 sequence.
 */
constexpr int count_utf8_trail_bytes(char8_t lead_byte) noexcept;

/**
 * Counts the trail bytes for a UTF-8 lead byte.
 * Unspecified if the lead_byte is not well-formed.
 * Does not branch.
 *
 * @param lead_byte The first byte of a UTF-8 sequence.
 */
constexpr int count_utf8_trail_bytes_unsafe(char8_t lead_byte) noexcept;

/**
 * How many code units are used for the UTF-8 encoding of the codepoint
 * @param codepoint 32-bit code point
 * @return 1..4, or 0 if c is a surrogate or not a Unicode code point
 */
constexpr int utf8_length(char32_t codepoint) noexcept;

/**
 * The maximum number of char8_t code units necessary to encode any code
 * point. The result is unspecified if the code point is not assignable.
 * @return 4
 */
constexpr int utf8_max_length() noexcept;
} // namespace unicode_formal

// Implementation
struct codepoint_constants {
  constexpr static uint32_t high_surrogate_start = 0xd800;
  constexpr static uint32_t low_surrogate_start = 0xdc00;
  constexpr static uint32_t end_bmp_scalar = 0xdfff;
  constexpr static uint32_t high_bmp = 0xffff;
  constexpr static uint32_t max_codepoint = 0x10ffff;
  constexpr static uint32_t supplemental_start = 0x10000;
};

struct utf8_constants {
  constexpr static uint32_t max_one_byte = 0x7f;
  constexpr static uint32_t max_two_byte = 0x7ff;
  constexpr static uint32_t max_three_byte = 0xd7ff;
};

// codepoint
inline constexpr bool unicode_formal::is_unicode_nonchar(char32_t codepoint) noexcept {
    return (codepoint >= 0xfdd0 &&
            (codepoint <= 0xfdef || (codepoint & 0xfffe) == 0xfffe) &&
            codepoint <= codepoint_constants::max_codepoint);
}

inline constexpr bool unicode_formal::is_unicode_char(char32_t codepoint) noexcept {
  return (static_cast<uint32_t>(codepoint) < codepoint_constants::high_surrogate_start ||
            (codepoint_constants::end_bmp_scalar < codepoint && codepoint <= codepoint_constants::max_codepoint &&
             !is_unicode_nonchar(codepoint)));
}

inline constexpr bool unicode_formal::is_bmp(char32_t codepoint) noexcept {
    return (static_cast<uint32_t>(codepoint) <= codepoint_constants::high_bmp);
}

inline constexpr bool unicode_formal::is_supplementary(char32_t codepoint) noexcept {
    return (static_cast<uint32_t>(codepoint - codepoint_constants::supplemental_start) <= 0xfffff);
}

inline constexpr bool unicode_formal::is_high_surrogate(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffffc00) == codepoint_constants::high_surrogate_start);
}

inline constexpr bool unicode_formal::is_low_surrogate(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffffc00) == codepoint_constants::low_surrogate_start);
}

inline constexpr bool unicode_formal::is_surrogate(char32_t codepoint) noexcept {
    return ((codepoint & 0xfffff800) == codepoint_constants::high_surrogate_start);
}


// UTF-16
inline constexpr bool unicode_formal::is_single(char16_t codeunit) noexcept {
    return !is_surrogate(static_cast<char32_t>(codeunit));
}

inline constexpr bool unicode_formal::is_high_surrogate(char16_t codeunit) noexcept {
    return ((codeunit & 0xfffffc00) == codepoint_constants::high_surrogate_start);
}

inline constexpr bool unicode_formal::is_low_surrogate(char16_t codeunit) noexcept {
    return ((codeunit & 0xfffffc00) == codepoint_constants::low_surrogate_start);
}

inline constexpr bool unicode_formal::is_surrogate(char16_t codeunit) noexcept {
    return is_surrogate(static_cast<char32_t>(codeunit));
}

inline constexpr unsigned long unicode_formal::surrogate_offset() noexcept {
    return ((codepoint_constants::high_surrogate_start << 10UL) + codepoint_constants::low_surrogate_start - codepoint_constants::supplemental_start);
}

inline constexpr char32_t unicode_formal::get_supplementary(char32_t high,
                                            char32_t trail) noexcept {
    return ((static_cast<char32_t>(high) << 10UL) +
            static_cast<char32_t>(trail) - surrogate_offset());
}

inline constexpr char16_t unicode_formal::surrogate_high(char32_t supplementary) noexcept {
    return (((supplementary) >> 10) + 0xd7c0);
}

inline constexpr char16_t unicode_formal::surrogate_low(char32_t supplementary) noexcept {
  return (((supplementary)&0x3ff) | codepoint_constants::low_surrogate_start);
}

inline constexpr int unicode_formal::utf16_length(char32_t codeunit) noexcept {
    return (static_cast<uint32_t>(codeunit) <= codepoint_constants::high_bmp ? 1 : 2);
}

inline constexpr int unicode_formal::utf16_max_length() noexcept { return 2; }

// UTF-8

inline constexpr bool unicode_formal::is_utf8_single(char8_t octet) noexcept {
    return ((octet & 0b10000000) == 0);
}

inline constexpr bool unicode_formal::is_utf8_lead(char8_t octet) noexcept {
    return (static_cast<uint8_t>(octet - 0xc2) <= 0x32);
}

inline constexpr bool unicode_formal::is_utf8_trail(char8_t octet) noexcept {
    return (static_cast<int8_t>(octet) < -0x40);
}

inline constexpr int unicode_formal::count_utf8_trail_bytes(char8_t lead_byte) noexcept {
    return is_utf8_lead(lead_byte)
               ? (static_cast<uint8_t>(lead_byte) >= 0b11100000) +
                     (static_cast<uint8_t>(lead_byte) >= 0b11110000) + 1
               : 0;
}

inline constexpr int unicode_formal::count_utf8_trail_bytes_unsafe(char8_t lead_byte) noexcept {
    return ((static_cast<uint8_t>(lead_byte) >= 0b11000010) +
            (static_cast<uint8_t>(lead_byte) >= 0b11100000) +
            (static_cast<uint8_t>(lead_byte) >= 0b11110000));
}

inline constexpr int unicode_formal::utf8_length(char32_t codepoint) noexcept {
  if (static_cast<uint32_t>(codepoint) <= utf8_constants::max_one_byte) {
        return 1;
    } else if (static_cast<uint32_t>(codepoint) <= utf8_constants::max_two_byte) {
        return 2;
  } else if (static_cast<uint32_t>(codepoint) <= utf8_constants::max_three_byte) {
        return 3;
    } else if (static_cast<uint32_t>(codepoint) <= codepoint_constants::end_bmp_scalar ||
               static_cast<uint32_t>(codepoint) > codepoint_constants::max_codepoint) {
        return 0;
    } else if (static_cast<uint32_t>(codepoint) <= codepoint_constants::high_bmp) {
        return 3;
    }
    return 4;
}

inline constexpr int unicode_formal::utf8_max_length() noexcept { return 4; }


#endif
