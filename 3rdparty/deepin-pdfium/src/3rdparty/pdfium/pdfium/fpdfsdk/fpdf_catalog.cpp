// Copyright 2017 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "public/fpdf_catalog.h"

#include "core/fpdfapi/parser/cpdf_dictionary.h"
#include "core/fpdfapi/parser/cpdf_document.h"
#include "fpdfsdk/cpdfsdk_helpers.h"

FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV
FPDFCatalog_IsTagged(FPDF_DOCUMENT document) {
  CPDF_Document* pDoc = CPDFDocumentFromFPDFDocument(document);
  if (!pDoc)
    return false;

  const CPDF_Dictionary* pCatalog = pDoc->GetRoot();
  if (!pCatalog)
    return false;

  const CPDF_Dictionary* pMarkInfo = pCatalog->GetDictFor("MarkInfo");
  return pMarkInfo && pMarkInfo->GetIntegerFor("Marked") != 0;
}
