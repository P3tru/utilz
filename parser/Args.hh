//
// Created by Stephane Zsoldos on 11/14/21.
//

#ifndef _INCLUDE_ARGS_HH_
#define _INCLUDE_ARGS_HH_

#include <string>
#include <vector>
#include <iostream>

//
//
//
struct BaseArg {
  std::string flag_short, flag_long;
  BaseArg(const std::string &flag_short, const std::string &flag_long)
    : flag_short(flag_short), flag_long(flag_long) {}
  virtual bool operator()(const std::string &arg,
			  const int& argc, char *argv[], int &i) = 0;
  virtual ~BaseArg() = default;
};
template <typename T>
struct TArg : public BaseArg {
  T val;
  TArg(const std::string &flag_short, const std::string &flag_long)
    : BaseArg(flag_short, flag_long) {}
  TArg(const std::string &flag_short, const std::string &flag_long, T val)
    : BaseArg(flag_short, flag_long), val(std::move(val)) {}
  ~TArg() override = default;
};
#include <boost/algorithm/string/predicate.hpp>
typedef struct sArg : public TArg<std::string>{
  sArg(const std::string &flag_short, const std::string &flag_long)
    : TArg(flag_short, flag_long) {}
  sArg(const std::string &flag_short, const std::string &flag_long, const std::string &val)
    : TArg(flag_short, flag_long, val) {}
  bool operator()(const std::string &arg,
		  const int& argc, char *argv[], int &i) override {
    if (boost::iequals(arg, flag_short) || boost::iequals(arg, flag_long)) {
      val=argv[++i];
      return true;
    } else {
      return false;
    }
  }
} sArg;
typedef struct bArg : public TArg<bool>{
  bArg(const std::string &flag_short, const std::string &flag_long)
    : TArg(flag_short, flag_long) { val = false;}
  bool operator()(const std::string &arg,
		  const int& argc, char *argv[], int &i) override {
    if (boost::iequals(arg, flag_short) || boost::iequals(arg, flag_long)) {
      val=true;
      return true;
    } else {
      return false;
    }
  }
} bArg;
typedef struct iArg : public TArg<int>{
  iArg(const std::string &flag_short, const std::string &flag_long)
    : TArg(flag_short, flag_long) { val = 0;}
  iArg(const std::string &flag_short, const std::string &flag_long, int val)
    : TArg(flag_short, flag_long, val) {}
  bool operator()(const std::string &arg,
		  const int& argc, char *argv[], int &i) override {
    if (boost::iequals(arg, flag_short) || boost::iequals(arg, flag_long)) {
      val=std::stoi(argv[++i]);
      return true;
    } else {
      return false;
    }
  }
} iArg;
typedef struct fArg : public TArg<float>{
  fArg(const std::string &flag_short, const std::string &flag_long)
    : TArg(flag_short, flag_long) { val = 0.f;}
  fArg(const std::string &flag_short, const std::string &flag_long, float val)
    : TArg(flag_short, flag_long, val) {}
  bool operator()(const std::string &arg,
		  const int& argc, char *argv[], int &i) override {
    if (boost::iequals(arg, flag_short) || boost::iequals(arg, flag_long)) {
      val=std::stof(argv[++i]);
      return true;
    } else {
      return false;
    }
  }
} fArg;
typedef struct vfArg : public TArg<std::vector<float>>{
  vfArg(const std::string &flag_short, const std::string &flag_long)
    : TArg(flag_short, flag_long) {}
  vfArg(const std::string &flag_short, const std::string &flag_long, const std::vector<float> &val)
    : TArg(flag_short, flag_long, val) {}
  bool operator()(const std::string &arg,
		  const int& argc, char *argv[], int &i) override {
    if (boost::iequals(arg, flag_short) || boost::iequals(arg, flag_long)) {
      val.clear();
      for(++i; i<argc; i++){
	std::string argg = argv[i];
	if( argg[0] == '-' )
	  if( !std::isdigit(argg[1]) )
	    break;
	val.emplace_back(std::stof(argg));
      }
      return !val.empty();
    } else {
      return false;
    }
  }
} vfArg;

//
//
//
typedef struct Args {
  //
  std::vector<BaseArg*> v;
  Args() = default;
  explicit Args(const std::vector<BaseArg *> &v) : v(v) {}
  //
  virtual void ShowUsage(const std::string &name) = 0;
  void ProcessArgs(const int& argc, char *argv[]);
  void operator()(const int& argc, char *argv[]) {
    ProcessArgs(argc, argv);
  }
} Args;

#endif //_INCLUDE_ARGS_HH_
