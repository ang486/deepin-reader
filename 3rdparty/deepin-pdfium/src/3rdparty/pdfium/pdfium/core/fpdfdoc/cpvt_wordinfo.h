// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFDOC_CPVT_WORDINFO_H_
#define CORE_FPDFDOC_CPVT_WORDINFO_H_

#include "core/fxcrt/fx_system.h"

struct CPVT_WordInfo {
  CPVT_WordInfo();
  CPVT_WordInfo(uint16_t word, int32_t charset, int32_t fontIndex);
  CPVT_WordInfo(const CPVT_WordInfo& word);
  ~CPVT_WordInfo();

  CPVT_WordInfo& operator=(const CPVT_WordInfo& word);

  uint16_t Word;
  int32_t nCharset;
  float fWordX;
  float fWordY;
  float fWordTail;
  int32_t nFontIndex;
};

#endif  // CORE_FPDFDOC_CPVT_WORDINFO_H_
