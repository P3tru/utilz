#ifndef _FIT_HH_
#define _FIT_HH_

#include <TMath.h>

const double PoissonScaled(const double &x, const double &lambda,
                           const double &fScale) {
  return std::pow(lambda / fScale, x / fScale) * std::exp(-lambda / fScale) /
         std::tgamma(x / fScale);
}

Double_t FitPoisson(const Double_t *x, const Double_t *par) {
  Double_t xx = x[0];
  Double_t lambda = par[0];

  return PoissonScaled(xx, lambda, 1000.);
}

Double_t FitGaus(const Double_t *x, const Double_t *par) {
  Double_t arg = 0;
  if (par[2] != 0) arg = (x[0] - par[1]) / par[2];
  Double_t fitval = par[0] * TMath::Exp(-0.5 * arg * arg);
  return fitval;
}

Double_t FitExp(const Double_t *x, const Double_t *par) {
  Double_t xx = x[0];
  Double_t A = par[0];
  Double_t t0 = par[1];
  Double_t tau = par[2];

  Double_t arg = 0;
  if (tau != 0) arg = (xx - t0) / tau;
  Double_t fitval = par[0] * TMath::Exp(-arg);
  return fitval;
}

#endif