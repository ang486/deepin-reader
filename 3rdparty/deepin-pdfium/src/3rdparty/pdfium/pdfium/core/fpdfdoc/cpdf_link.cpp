// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fpdfdoc/cpdf_link.h"

#include "core/fpdfapi/parser/cpdf_dictionary.h"

CPDF_Link::CPDF_Link() = default;

CPDF_Link::CPDF_Link(CPDF_Dictionary* pDict) : m_pDict(pDict) {}

CPDF_Link::CPDF_Link(const CPDF_Link& that) = default;

CPDF_Link::~CPDF_Link() = default;

CFX_FloatRect CPDF_Link::GetRect() {
  return m_pDict->GetRectFor("Rect");
}

CPDF_Dest CPDF_Link::GetDest(CPDF_Document* pDoc) {
  return CPDF_Dest::Create(pDoc, m_pDict->GetDirectObjectFor("Dest"));
}

CPDF_Action CPDF_Link::GetAction() {
  return CPDF_Action(m_pDict->GetDictFor("A"));
}
