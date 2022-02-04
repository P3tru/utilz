#ifndef _DRAWING_HH_
#define _DRAWING_HH_

#include <TCanvas.h>

#include "ZColors.hh"

template <typename T>
TCanvas *PlotAHist(T *h, const char *opt = ""){

  auto *c1 = new TCanvas(Form("c%s", h->GetName()), Form("c%s", h->GetName()), 800, 600);
  c1->SetGrid();
  h->Draw(opt);
  return c1;

}

template <typename T>
void SetBasicTStyle(T *h, int Color = kBlue - 4,
                    int LineWidth = 1, int LineStyle = kSolid,
                    int MarkerSize = 1, int MarkerStyle = kPlus){

  h->SetLineColor(Color);
  h->SetLineWidth(LineWidth);
  h->SetLineStyle(LineStyle);

  h->SetMarkerColor(Color);
  h->SetMarkerSize(MarkerSize);
  h->SetMarkerStyle(MarkerStyle);

}

#endif // _DRAWING_HH_
