#ifndef _MATHUTILS_HH_
#define _MATHUTILS_HH_

#define PI 3.14159265359
#define SQRT2 1.41421356237
#define RINDEX_WATER 1.33
#define SOL_VACUUM 299.792
#define SOL SOL_VACUUM / RINDEX_WATER

const double GetPI() { return PI; }

const double GetSQRT2() { return SQRT2; }

const double GetSOL() { return SOL; }

#include "BoxBnds.hh"
#include "CylBnds.hh"
#include "Fit.hh"
#include "Hist.hh"
#include "Matrix.hh"
#include "NLL.hh"
#include "Sensitivity.hh"

const std::vector<std::vector<double> > Get4DSmplGuess(
    const std::vector<double>& xGuess, const std::vector<double>& vScale) {
  const unsigned int nDim = 4;
  const std::size_t nPts = std::pow(2, nDim);
  std::vector<std::vector<double> > vSmplGuess;
  vSmplGuess.reserve(nPts + 1);
  vSmplGuess.emplace_back(xGuess);

  auto GetBnd = [](const unsigned int& b, const double& x) {
    return b ? x : -x;
  };

  for (auto i = 0; i < nPts; i++) {
    std::bitset<nDim> word(i);
    std::vector<double> v(nDim);
    for (auto iDim = 0; iDim < nDim; iDim++) {
      v[iDim] = xGuess[iDim] + GetBnd(word[iDim], vScale[iDim]);
    }
    vSmplGuess.emplace_back(v);
  }

  return vSmplGuess;
}

const std::vector<std::vector<double> > Get4DSmplGuess(
    const std::vector<double>& xGuess, const double& Scale) {
  const unsigned int nDim = 4;
  const std::size_t nPts = std::pow(2, nDim);
  std::vector<std::vector<double> > vSmplGuess;
  vSmplGuess.reserve(nPts + 1);
  vSmplGuess.emplace_back(xGuess);

  auto GetBnd = [](const unsigned int& b, const double& x) {
    return b ? x : -x;
  };

  for (auto i = 0; i < nPts; i++) {
    std::bitset<nDim> word(i);
    std::vector<double> v(nDim);
    for (auto iDim = 0; iDim < nDim; iDim++) {
      v[iDim] = xGuess[iDim] + GetBnd(word[iDim], Scale);
    }
    vSmplGuess.emplace_back(v);
  }

  return vSmplGuess;

#endif