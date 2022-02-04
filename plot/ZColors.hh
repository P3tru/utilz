//
// Created by zsoldos on 7/22/20.
//

#ifndef _ZCOLORS_HH_
#define _ZCOLORS_HH_

#include <TColor.h>

std::vector<int> vPalClassic(){
  return { kBlue - 4, kRed - 4, kGreen + 1 } ;
};

std::vector<int> vPal0() {
  return {
	  TColor::GetColor("#080F0F"),
	  TColor::GetColor("#A4BAB7"),
	  TColor::GetColor("#EFF2C0"),
	  TColor::GetColor("#BEA57D"),
	  TColor::GetColor("#A52422")
  };
};

std::vector<int> vPal1() {
  return {
	  TColor::GetColor("#083D77"),
	  TColor::GetColor("#EBEBD3"),
	  TColor::GetColor("#F4D35E"),
	  TColor::GetColor("#EE964B"),
	  TColor::GetColor("#F95738")
  };
};

const std::vector<int> vPal2 {
	TColor::GetColor("#EDAE49"),
	TColor::GetColor("#D1495B"),
	TColor::GetColor("#00798C"),
	TColor::GetColor("#30638E"),
	TColor::GetColor("#003D5B")
};

const std::vector<int> vPal3 {
	TColor::GetColor("#ACF39D"),
	TColor::GetColor("#E85F5C"),
	TColor::GetColor("#9CFFFA"),
	TColor::GetColor("#773344"),
	TColor::GetColor("#E3B5A4")
};

const std::vector<int> vPal {
	TColor::GetColor("#080F0F"),
	TColor::GetColor("#A4BAB7"),
	TColor::GetColor("#EFF2C0"),
	TColor::GetColor("#BEA57D"),
	TColor::GetColor("#A52422"),
	TColor::GetColor("#083D77"),
	TColor::GetColor("#EBEBD3"),
	TColor::GetColor("#F4D35E"),
	TColor::GetColor("#EE964B"),
	TColor::GetColor("#F95738"),
	TColor::GetColor("#EDAE49"),
	TColor::GetColor("#D1495B"),
	TColor::GetColor("#00798C"),
	TColor::GetColor("#30638E"),
	TColor::GetColor("#003D5B"),
	TColor::GetColor("#ACF39D"),
	TColor::GetColor("#E85F5C"),
	TColor::GetColor("#9CFFFA"),
	TColor::GetColor("#773344"),
	TColor::GetColor("#E3B5A4")
};

int GetColFromPal(const std::vector<int>& vP, const int& i){
  return vP[i % vP.size()];
}

#endif //_ZCOLORS_HH_
