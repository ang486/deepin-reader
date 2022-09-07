// Copyright 2020 PDFium Authors. All rights reserved.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FPDFSDK_CPDFSDK_RENDERPAGE_H_
#define FPDFSDK_CPDFSDK_RENDERPAGE_H_

#include "public/fpdfview.h"

class CFX_Matrix;
class CPDFSDK_PauseAdapter;
class CPDF_Page;
class CPDF_PageRenderContext;
struct FX_RECT;

void CPDFSDK_RenderPage(CPDF_PageRenderContext *pContext,
                        CPDF_Page *pPage,
                        const CFX_Matrix &matrix,
                        const FX_RECT &clipping_rect,
                        int flags,
                        const FPDF_COLORSCHEME *color_scheme);

// TODO(thestig): Consider giving this a better name, and make its parameters
// more similar to those of CPDFSDK_RenderPage().
void CPDFSDK_RenderPageWithContext(CPDF_PageRenderContext *pContext,
                                   CPDF_Page *pPage,
                                   int start_x,
                                   int start_y,
                                   int size_x,
                                   int size_y,
                                   int src_size_w,
                                   int src_size_h,
                                   int rotate,
                                   int flags,
                                   const FPDF_COLORSCHEME *color_scheme,
                                   bool need_to_restore,
                                   CPDFSDK_PauseAdapter *pause);

#endif  // FPDFSDK_CPDFSDK_RENDERPAGE_H_
