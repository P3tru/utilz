#ifndef _TBNDS_HH_
#define _TBNDS_HH_

#include <cmath>
#include <vector>

#include <TVector3.h>

template <typename T>
struct Bnd {
  T min, max;

  Bnd() = default;
  Bnd(T min, T max) : min(min), max(max) {}
  Bnd(const Bnd<T>& rhs) {
    min = rhs.min;
    max = rhs.max;
  }

  bool IsIn(const T& val) const { return val > min && val < max; }
};

template <typename T, typename U>
struct Bnds {
  std::vector<Bnd<T>> vPos;
  Bnd<U> vT;

  Bnds() = default;
  Bnds(const std::vector<Bnd<T>>& v_pos, const Bnd<U>& v_t)
      : vPos(v_pos), vT(v_t) {}
  Bnds(const Bnds& rhs) {
    vPos = rhs.vPos;
    vT = rhs.vT;
  }

  virtual bool IsInPos(const std::vector<T>& v) const {
    if (v.size() != vPos.size()) {
      std::cerr << "Bnds::InInPos() DIM BOUNDS != DIM V" << std::endl;
      return false;
    }

    for (auto i = 0; i < v.size(); i++) {
      if (!vPos[i].IsIn(v[i])) return false;
    }
    return true;
  }

  virtual bool IsInT(const U& val) const { return vT.IsIn(val); }

  virtual bool IsInPos(const TVector3& v) const { return false; }
  virtual T GetDWall(const TVector3& v) const {
    return -std::numeric_limits<T>::max();
  }
  virtual TVector3 GetTVector3() const { return TVector3(); }
  virtual void Print() const {
    for (const auto& bnd : vPos) {
      std::cout << "[" << bnd.min << ", " << bnd.max << "]mm ";
    }
    std::cout << "[" << vT.min << ", " << vT.max << "]ns" << std::endl;
  }
  virtual T GetMaxDWall() const {
    T maxdwall = std::numeric_limits<T>::max();
    for (const auto& bnd : vPos) {
      maxdwall =
          std::min(maxdwall, std::min(std::abs(bnd.min), std::abs(bnd.max)));
    }
    return maxdwall;
  }
  virtual std::vector<T> GetVDetBnds() const {
    std::vector<T> v;
    for (const auto& bnd : vPos) {
      v.push_back(std::max(std::abs(bnd.min), std::abs(bnd.max)));
    }
    return v;
  }

  virtual std::vector<T> GetVLB() const {
    std::vector<T> v;
    for (const auto& bnd : vPos) {
      v.push_back(bnd.min);
    }
    v.push_back(-vT.max);
    return v;
  }
  virtual std::vector<T> GetVUB() const {
    std::vector<T> v;
    for (const auto& bnd : vPos) {
      v.push_back(bnd.max);
    }
    v.push_back(-vT.min);
    return v;
  }
};

typedef struct Bnds<double, double> bnds;

#endif