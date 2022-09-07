// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFDOC_CPDF_ICONFIT_H_
#define CORE_FPDFDOC_CPDF_ICONFIT_H_

#include "core/fxcrt/fx_coordinates.h"
#include "core/fxcrt/fx_system.h"
#include "core/fxcrt/retain_ptr.h"

class CPDF_Dictionary;

class CPDF_IconFit {
 public:
  enum class ScaleMethod { kAlways = 0, kBigger, kSmaller, kNever };

  explicit CPDF_IconFit(const CPDF_Dictionary* pDict);
  CPDF_IconFit(const CPDF_IconFit& that);
  ~CPDF_IconFit();

  ScaleMethod GetScaleMethod() const;
  bool IsProportionalScale() const;
  bool GetFittingBounds() const;
  CFX_PointF GetIconBottomLeftPosition() const;
  CFX_PointF GetIconPosition() const;

 private:
  RetainPtr<const CPDF_Dictionary> const m_pDict;
};

#endif  // CORE_FPDFDOC_CPDF_ICONFIT_H_
