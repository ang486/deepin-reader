// Copyright 2016 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_PARSER_CPDF_NULL_H_
#define CORE_FPDFAPI_PARSER_CPDF_NULL_H_

#include "core/fpdfapi/parser/cpdf_object.h"

class CPDF_Null final : public CPDF_Object {
 public:
  CONSTRUCT_VIA_MAKE_RETAIN;

  // CPDF_Object.
  Type GetType() const override;
  RetainPtr<CPDF_Object> Clone() const override;
  bool WriteTo(IFX_ArchiveStream* archive,
               const CPDF_Encryptor* encryptor) const override;
  bool IsNull() const override;

 private:
  CPDF_Null();
};

#endif  // CORE_FPDFAPI_PARSER_CPDF_NULL_H_
