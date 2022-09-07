// Copyright 2014 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "public/fpdf_searchex.h"

#include "core/fpdftext/cpdf_textpage.h"
#include "fpdfsdk/cpdfsdk_helpers.h"

FPDF_EXPORT int FPDF_CALLCONV
FPDFText_GetCharIndexFromTextIndex(FPDF_TEXTPAGE text_page, int nTextIndex) {
  if (!text_page)
    return -1;
  return CPDFTextPageFromFPDFTextPage(text_page)->CharIndexFromTextIndex(
      nTextIndex);
}

FPDF_EXPORT int FPDF_CALLCONV
FPDFText_GetTextIndexFromCharIndex(FPDF_TEXTPAGE text_page, int nCharIndex) {
  if (!text_page)
    return -1;
  return CPDFTextPageFromFPDFTextPage(text_page)->TextIndexFromCharIndex(
      nCharIndex);
}
