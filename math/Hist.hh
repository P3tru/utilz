#ifndef _HIST_HH_
#define _HIST_HH_

#include <TAxis.h>

#include <numeric>

typedef struct zAxis {
  int nBins;
  double min, max;

  zAxis() = default;

  zAxis(int n, double mmin, double mmax) : nBins(n), min(mmin), max(mmax) {}

  explicit zAxis(TAxis* ax)
      : nBins(ax->GetNbins()), min(ax->GetXmin()), max(ax->GetXmax()) {}

  void Set(TAxis* ax) {
    nBins = ax->GetNbins();
    min = ax->GetXmin();
    max = ax->GetXmax();
  }

  std::vector<double> GetStdVec() const {
    std::vector<double> v(nBins + 1);
    const double width = (max - min) / static_cast<double>(nBins);
    std::iota(v.begin(), v.end(), 0);
    std::transform(v.begin(), v.end(), v.begin(), [&](const double& val) {
      return min + (val + 0.5) * width;
    });
    return v;
  }

} zAxis;

std::vector<double> GetIntSpace(const unsigned int& nSteps,
                                const double& min = -1,
                                const double& max = 1.) {
  const double step = (max - min) / (double)(nSteps);
  std::vector<double> v(nSteps);
  for (auto i = 0; i < nSteps; i++) v[i] = min + i * step;
  v.emplace_back(max);
  return v;
}

#endif