#include <iostream>

#include <TFile.h>

template <typename T>
T* GetROOTObj(const char* filename, const char* objname) {
  T* obj = nullptr;
  TFile f(filename, "READ");
  if (f.IsOpen()) {
    try {
      obj = (T*)f.Get(objname);
      try {
        obj->SetDirectory(nullptr);
      } catch (...) {
        std::cerr << objname << " not owned" << std::endl;
      }
    } catch (...) {
      std::cerr << objname << " not exist in: " << filename << std::endl;
    }
    f.Close();
  } else {
    std::cerr << filename << " not exist" << std::endl;
  }
  return obj;
}
