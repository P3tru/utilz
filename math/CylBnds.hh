#ifndef _CYLBNDS_HH_
#define _CYLBNDS_HH_

#include "TBnds.hh"

struct CylBnds : public bnds {
  CylBnds() {
    vPos = {{0., 0.}, {0., 0.}};
    vT = {0., 0.};
  };
  explicit CylBnds(const bnds& b) {
    vPos = b.vPos;
    vT = b.vT;
  }
  CylBnds(const double& radius, const double& hheight,
          const double& SoL) {
    vPos = {{0, radius}, {0, hheight}};
    vT = {0, std::min(radius, hheight) / SoL};
  }
  CylBnds(const double& radius, const double& hheight,
          const std::vector<double>& TBnds) {
    vPos = {{0, radius}, {0, hheight}};
    vT = {TBnds[0], TBnds[1]};
  }
  CylBnds(const double& radius, const double& hheight, const double& TMin,
          const double& TMax) {
    vPos = {{0, radius}, {0, hheight}};
    vT = {TMin, TMax};
  }

  double GetRadius() const { return vPos[0].max; }

  double GetHHeight() const { return vPos[1].max; }

  bool IsInPos(const TVector3& v) const override {
    return vPos[0].IsIn(v.Perp()) && vPos[1].IsIn(std::abs(v.z()));
  }

  double GetDWall(const TVector3& v) const override {
    return std::min(GetRadius() - v.Perp(), GetHHeight() - std::abs(v.z()));
  }

  TVector3 GetTVector3() const override {
    return TVector3(GetRadius(), GetRadius(), GetHHeight());
  }

  double GetMaxDWall() const override {
    return std::min(GetRadius(), GetHHeight());
  }

  std::vector<double> GetVDetBnds() const override {
    return {GetRadius(), GetRadius(), GetHHeight()};
  }

  std::vector<double> GetVLB() const override {
    return {-GetRadius(), -GetRadius(), -GetHHeight(), -vT.max};
  }

  std::vector<double> GetVUB() const override {
    return {GetRadius(), GetRadius(), GetHHeight(), -vT.min};
  }
};

#endif