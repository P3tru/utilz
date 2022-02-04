#ifndef _NLL_HH_
#define _NLL_HH_

#include <TMath.h>

const double EvalLL(double nObs, double nPred) {
  return nObs * TMath::Log(nPred);
}

const double EvalExtendedLL(double nObs, double nPred) {
  return nObs * TMath::Log(nPred) - nPred;
}

const double EvalNLL(double nObs, double nPred) {
  double L;
  if (nObs > 0 && nPred > 0)
    L = nObs * TMath::Log(nObs / nPred) + nPred - nObs;
  else
    L = nPred;
  return -L;
}

template <typename T>
double CalculateLL(T const *hPDF, T const *hExp, bool isNormalized = true) {
  auto nBinsX = hPDF->GetNbinsX();
  auto nBinsY = hPDF->GetNbinsY();

  auto normPDF = 1.;
  auto normExp = 1.;
  if (!isNormalized) {
    normPDF = hPDF->Integral();
    normExp = hExp->Integral();
  }

  auto Chi2 = 0.;

  auto NonNullBin = 0;

  for (auto iBinX = 1; iBinX < nBinsX + 1; iBinX++) {
    for (auto iBinY = 1; iBinY < nBinsY + 1; iBinY++) {
      auto nObs = hExp->GetBinContent(hExp->GetBin(iBinX, iBinY)) / normExp;
      auto nPred = hPDF->GetBinContent(hPDF->GetBin(iBinX, iBinY)) / normPDF;

      // Chi2 += EvalLL(nObs, nPred);
      // Chi2 += EvalExtendedLL(nObs, nPred);
      Chi2 += EvalNLL(nObs, nPred);
    }
  }

  return Chi2 /*/ static_cast<double>(nBinsX + nBinsY)*/;
}

#endif