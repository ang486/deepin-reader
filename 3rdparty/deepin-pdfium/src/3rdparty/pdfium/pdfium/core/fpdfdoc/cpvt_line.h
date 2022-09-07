// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFDOC_CPVT_LINE_H_
#define CORE_FPDFDOC_CPVT_LINE_H_

#include "core/fpdfdoc/cpvt_wordplace.h"
#include "core/fxcrt/fx_coordinates.h"
#include "core/fxcrt/fx_system.h"

class CPVT_Line {
 public:
  CPVT_Line();

  CPVT_WordPlace lineplace;
  CPVT_WordPlace lineEnd;
  CFX_PointF ptLine;
  float fLineWidth;
  float fLineAscent;
  float fLineDescent;
};

inline CPVT_Line::CPVT_Line()
    : fLineWidth(0.0f), fLineAscent(0.0f), fLineDescent(0.0f) {}

#endif  // CORE_FPDFDOC_CPVT_LINE_H_
