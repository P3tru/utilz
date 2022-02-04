#ifndef _BOXBNDS_HH
#define _BOXBNDS_HH

#include <iostream>

#include "TBnds.hh"

struct BoxBnds : public bnds{

  BoxBnds(){
    vPos = { {0, 0}, {0, 0}, {0, 0} };
    vT = {0, 0};
  };
  explicit BoxBnds(const bnds& b){
    vPos = b.vPos;
    vT = b.vT;
  }
  explicit BoxBnds(const std::vector<double>& vvPos, const double& SoL) : BoxBnds(){
    if(vPos.size() != vvPos.size())
      std::cerr << "BoxBnds::BoxBnds() NOT ALL DIMS ARE SPECIFIED" << std::endl;
    double min = *std::min_element(vvPos.begin(), vvPos.end());
    for(auto i=0; i<vvPos.size();i++){
      vPos[i] = {0, vvPos[i]};
    }
    vT = {0, min/SoL};
  }
  explicit BoxBnds(const std::vector<std::vector<double>>& vvPos, const double& SoL) : BoxBnds(){
    if(vPos.size() != vvPos.size())
      std::cerr << "BoxBnds::BoxBnds() NOT ALL DIMS ARE SPECIFIED" << std::endl;
    auto min =
      *std::min_element(vvPos.begin(), vvPos.end(),
			[](const std::vector<double>&v1, const std::vector<double>&v2){
			  return *std::min_element(v1.begin(), v1.end()) < *std::min_element(v2.begin(), v2.end());
			}
			);
    for(auto i=0; i<vvPos.size();i++){
      vPos[i] = {vvPos[i][0], vvPos[i][1]};
    }
    vT = {0, *std::min_element(min.begin(), min.end())/SoL};
  }
  BoxBnds(const std::vector<std::vector<double>>& vvPos,
	  const std::vector<double>& TBnds) : BoxBnds(){
    if(vPos.size() != vvPos.size())
      std::cerr << "BoxBnds::BoxBnds() NOT ALL DIMS ARE SPECIFIED" << std::endl;
    for(auto i=0; i<vvPos.size();i++){
      vPos[i] = {vvPos[i][0], vvPos[i][1]};
    }
    vT = {TBnds[0], TBnds[1]};
  }
  BoxBnds(const std::vector<std::vector<double>>& vvPos,
	  const double& TMin, const double& TMax) : BoxBnds(){
    if(vPos.size() != vvPos.size())
      std::cerr << "BoxBnds::BoxBnds() NOT ALL DIMS ARE SPECIFIED" << std::endl;
    for(auto i=0; i<vvPos.size();i++){
      vPos[i] = {vvPos[i][0], vvPos[i][1]};
    }
    vT = {TMin, TMax};
  }

  bool IsInPos(const TVector3&v) const override {
    for(auto i=0; i<3; i++){
      if(!vPos[i].IsIn(v[i]))
	return false;
    }
    return true;
  }

  double GetDWall(const TVector3& v) const override {
    double dWall = std::numeric_limits<double>::max();
    for(auto i=0; i<3; i++) {
      double absv = std::abs(v[i]);
      double min = std::min(std::abs(vPos[0].min) - absv, std::abs(vPos[0].max) - absv);
      dWall = min < dWall ? min : dWall;
    }
    return dWall;
  }

  TVector3 GetTVector3() const override {
    return TVector3(vPos[0].max, vPos[1].max, vPos[2].max);
  }

};


#endif