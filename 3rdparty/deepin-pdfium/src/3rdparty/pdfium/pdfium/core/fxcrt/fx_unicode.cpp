// Copyright 2014 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fxcrt/fx_unicode.h"

#include "third_party/base/stl_util.h"

namespace {

// Format of uint16_t values in kTextLayoutCodeProperties[].
constexpr uint16_t kBidiClassBitPos = 0;
constexpr uint16_t kBidiClassBitCount = 5;
constexpr uint16_t kBidiClassBitMask =
    (((1u << kBidiClassBitCount) - 1) << kBidiClassBitPos);

constexpr uint16_t kMirrorBitPos = 5;
constexpr uint16_t kMirrorBitCount = 9;
constexpr uint16_t kMirrorMax = (1 << kMirrorBitCount) - 1;

#undef CHARPROP____
#define CHARPROP____(mirror, ct, bd, bt) \
  ((mirror << kMirrorBitPos) |           \
   (static_cast<uint16_t>(FX_BIDICLASS::bd) << kBidiClassBitPos)),
constexpr uint16_t kTextLayoutCodeProperties[] = {
#include "core/fxcrt/fx_ucddata.inc"  // NOLINT(build/include)
};
#undef CHARPROP____

constexpr size_t kTextLayoutCodePropertiesSize =
    pdfium::size(kTextLayoutCodeProperties);

static_assert(kTextLayoutCodePropertiesSize == 65536, "missing characters");

uint16_t GetUnicodeProperties(wchar_t wch) {
  size_t idx = static_cast<size_t>(wch);
  if (idx < kTextLayoutCodePropertiesSize)
    return kTextLayoutCodeProperties[idx];
  return 0;
}

#ifdef PDF_ENABLE_XFA
// Format of uint16_t values in kExtendedTextLayoutCodeProperties[].
constexpr uint16_t kBreakTypeBitPos = 0;
constexpr uint16_t kBreakTypeBitCount = 6;
constexpr uint16_t kBreakTypeBitMask =
    (((1u << kBreakTypeBitCount) - 1) << kBreakTypeBitPos);

constexpr uint16_t kCharTypeBitPos = 6;
constexpr uint16_t kCharTypeBitCount = 4;
constexpr uint16_t kCharTypeBitMask =
    (((1u << kCharTypeBitCount) - 1) << kCharTypeBitPos);

#undef CHARPROP____
#define CHARPROP____(mirror, ct, bd, bt)                         \
  ((static_cast<uint16_t>(FX_CHARTYPE::ct) << kCharTypeBitPos) | \
   (static_cast<uint16_t>(FX_BREAKPROPERTY::bt) << kBreakTypeBitPos)),
constexpr uint16_t kExtendedTextLayoutCodeProperties[] = {
#include "core/fxcrt/fx_ucddata.inc"  // NOLINT(build/include)
};
#undef CHARPROP____

constexpr size_t kExtendedTextLayoutCodePropertiesSize =
    pdfium::size(kExtendedTextLayoutCodeProperties);

static_assert(kExtendedTextLayoutCodePropertiesSize == 65536,
              "missing characters");

uint16_t GetExtendedUnicodeProperties(wchar_t wch) {
  size_t idx = static_cast<size_t>(wch);
  if (idx < kExtendedTextLayoutCodePropertiesSize)
    return kExtendedTextLayoutCodeProperties[idx];
  return 0;
}

#endif  // PDF_ENABLE_XFA

constexpr uint16_t kFXTextLayoutBidiMirror[] = {
    0x0029, 0x0028, 0x003E, 0x003C, 0x005D, 0x005B, 0x007D, 0x007B, 0x00BB,
    0x00AB, 0x0F3B, 0x0F3A, 0x0F3D, 0x0F3C, 0x169C, 0x169B, 0x2019, 0x2018,
    0x201D, 0x201C, 0x203A, 0x2039, 0x2046, 0x2045, 0x207E, 0x207D, 0x208E,
    0x208D, 0x220B, 0x220C, 0x220D, 0x2208, 0x2209, 0x220A, 0x29F5, 0x223D,
    0x223C, 0x22CD, 0x2253, 0x2252, 0x2255, 0x2254, 0x2265, 0x2264, 0x2267,
    0x2266, 0x2269, 0x2268, 0x226B, 0x226A, 0x226F, 0x226E, 0x2271, 0x2270,
    0x2273, 0x2272, 0x2275, 0x2274, 0x2277, 0x2276, 0x2279, 0x2278, 0x227B,
    0x227A, 0x227D, 0x227C, 0x227F, 0x227E, 0x2281, 0x2280, 0x2283, 0x2282,
    0x2285, 0x2284, 0x2287, 0x2286, 0x2289, 0x2288, 0x228B, 0x228A, 0x2290,
    0x228F, 0x2292, 0x2291, 0x29B8, 0x22A3, 0x22A2, 0x2ADE, 0x2AE4, 0x2AE3,
    0x2AE5, 0x22B1, 0x22B0, 0x22B3, 0x22B2, 0x22B5, 0x22B4, 0x22B7, 0x22B6,
    0x22CA, 0x22C9, 0x22CC, 0x22CB, 0x2243, 0x22D1, 0x22D0, 0x22D7, 0x22D6,
    0x22D9, 0x22D8, 0x22DB, 0x22DA, 0x22DD, 0x22DC, 0x22DF, 0x22DE, 0x22E1,
    0x22E0, 0x22E3, 0x22E2, 0x22E5, 0x22E4, 0x22E7, 0x22E6, 0x22E9, 0x22E8,
    0x22EB, 0x22EA, 0x22ED, 0x22EC, 0x22F1, 0x22F0, 0x22FA, 0x22FB, 0x22FC,
    0x22FD, 0x22FE, 0x22F2, 0x22F3, 0x22F4, 0x22F6, 0x22F7, 0x2309, 0x2308,
    0x230B, 0x230A, 0x232A, 0x2329, 0x2769, 0x2768, 0x276B, 0x276A, 0x276D,
    0x276C, 0x276F, 0x276E, 0x2771, 0x2770, 0x2773, 0x2772, 0x2775, 0x2774,
    0x27C4, 0x27C3, 0x27C6, 0x27C5, 0x27C9, 0x27C8, 0x27D6, 0x27D5, 0x27DE,
    0x27DD, 0x27E3, 0x27E2, 0x27E5, 0x27E4, 0x27E7, 0x27E6, 0x27E9, 0x27E8,
    0x27EB, 0x27EA, 0x27ED, 0x27EC, 0x27EF, 0x27EE, 0x2984, 0x2983, 0x2986,
    0x2985, 0x2988, 0x2987, 0x298A, 0x2989, 0x298C, 0x298B, 0x2990, 0x298F,
    0x298E, 0x298D, 0x2992, 0x2991, 0x2994, 0x2993, 0x2996, 0x2995, 0x2998,
    0x2997, 0x2298, 0x29C1, 0x29C0, 0x29C5, 0x29C4, 0x29D0, 0x29CF, 0x29D2,
    0x29D1, 0x29D5, 0x29D4, 0x29D9, 0x29D8, 0x29DB, 0x29DA, 0x2215, 0x29F9,
    0x29F8, 0x29FD, 0x29FC, 0x2A2C, 0x2A2B, 0x2A2E, 0x2A2D, 0x2A35, 0x2A34,
    0x2A3D, 0x2A3C, 0x2A65, 0x2A64, 0x2A7A, 0x2A79, 0x2A7E, 0x2A7D, 0x2A80,
    0x2A7F, 0x2A82, 0x2A81, 0x2A84, 0x2A83, 0x2A8C, 0x2A8B, 0x2A92, 0x2A91,
    0x2A94, 0x2A93, 0x2A96, 0x2A95, 0x2A98, 0x2A97, 0x2A9A, 0x2A99, 0x2A9C,
    0x2A9B, 0x2AA2, 0x2AA1, 0x2AA7, 0x2AA6, 0x2AA9, 0x2AA8, 0x2AAB, 0x2AAA,
    0x2AAD, 0x2AAC, 0x2AB0, 0x2AAF, 0x2AB4, 0x2AB3, 0x2ABC, 0x2ABB, 0x2ABE,
    0x2ABD, 0x2AC0, 0x2ABF, 0x2AC2, 0x2AC1, 0x2AC4, 0x2AC3, 0x2AC6, 0x2AC5,
    0x2ACE, 0x2ACD, 0x2AD0, 0x2ACF, 0x2AD2, 0x2AD1, 0x2AD4, 0x2AD3, 0x2AD6,
    0x2AD5, 0x22A6, 0x22A9, 0x22A8, 0x22AB, 0x2AED, 0x2AEC, 0x2AF8, 0x2AF7,
    0x2AFA, 0x2AF9, 0x2E03, 0x2E02, 0x2E05, 0x2E04, 0x2E0A, 0x2E09, 0x2E0D,
    0x2E0C, 0x2E1D, 0x2E1C, 0x2E21, 0x2E20, 0x2E23, 0x2E22, 0x2E25, 0x2E24,
    0x2E27, 0x2E26, 0x2E29, 0x2E28, 0x3009, 0x3008, 0x300B, 0x300A, 0x300D,
    0x300C, 0x300F, 0x300E, 0x3011, 0x3010, 0x3015, 0x3014, 0x3017, 0x3016,
    0x3019, 0x3018, 0x301B, 0x301A, 0xFE5A, 0xFE59, 0xFE5C, 0xFE5B, 0xFE5E,
    0xFE5D, 0xFE65, 0xFE64, 0xFF09, 0xFF08, 0xFF1E, 0xFF1C, 0xFF3D, 0xFF3B,
    0xFF5D, 0xFF5B, 0xFF60, 0xFF5F, 0xFF63, 0xFF62,
};

constexpr size_t kFXTextLayoutBidiMirrorSize =
    pdfium::size(kFXTextLayoutBidiMirror);

// Check that the mirror indicies in the fx_ucddata.inc table are in bounds.
#undef CHARPROP____
#define CHARPROP____(mirror, ct, bd, bt)                                      \
  static_assert(mirror == kMirrorMax || mirror < kFXTextLayoutBidiMirrorSize, \
                "Bad mirror index");
#include "core/fxcrt/fx_ucddata.inc"  // NOLINT(build/include)
#undef CHARPROP____

}  // namespace

wchar_t FX_GetMirrorChar(wchar_t wch) {
  uint16_t prop = GetUnicodeProperties(wch);
  size_t idx = prop >> kMirrorBitPos;
  if (idx == kMirrorMax)
    return wch;
  ASSERT(idx < kFXTextLayoutBidiMirrorSize);
  return kFXTextLayoutBidiMirror[idx];
}

FX_BIDICLASS FX_GetBidiClass(wchar_t wch) {
  uint16_t prop = GetUnicodeProperties(wch);
  uint16_t result = (prop & kBidiClassBitMask) >> kBidiClassBitPos;
  ASSERT(result <= static_cast<uint16_t>(FX_BIDICLASS::kPDF));
  return static_cast<FX_BIDICLASS>(result);
}

#ifdef PDF_ENABLE_XFA
FX_CHARTYPE FX_GetCharType(wchar_t wch) {
  uint16_t prop = GetExtendedUnicodeProperties(wch);
  uint16_t result = (prop & kCharTypeBitMask) >> kCharTypeBitPos;
  ASSERT(result <= static_cast<uint16_t>(FX_CHARTYPE::kArabic));
  return static_cast<FX_CHARTYPE>(result);
}

FX_BREAKPROPERTY FX_GetBreakProperty(wchar_t wch) {
  uint16_t prop = GetExtendedUnicodeProperties(wch);
  uint16_t result = (prop & kBreakTypeBitMask) >> kBreakTypeBitPos;
  ASSERT(result <= static_cast<uint16_t>(FX_BREAKPROPERTY::kTB));
  return static_cast<FX_BREAKPROPERTY>(result);
}
#endif  // PDF_ENABLE_XFA
