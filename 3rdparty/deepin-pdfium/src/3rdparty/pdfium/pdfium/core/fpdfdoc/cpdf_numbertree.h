// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFDOC_CPDF_NUMBERTREE_H_
#define CORE_FPDFDOC_CPDF_NUMBERTREE_H_

#include "core/fxcrt/retain_ptr.h"

class CPDF_Dictionary;
class CPDF_Object;

class CPDF_NumberTree {
 public:
  explicit CPDF_NumberTree(const CPDF_Dictionary* pRoot);
  ~CPDF_NumberTree();

  const CPDF_Object* LookupValue(int num) const;

 protected:
  RetainPtr<const CPDF_Dictionary> const m_pRoot;
};

#endif  // CORE_FPDFDOC_CPDF_NUMBERTREE_H_
