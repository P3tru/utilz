#ifndef _SENSITIVITY_HH_
#define _SENSITIVITY_HH_

const double ErrRate(const double& S, const double& T) {
  return std::sqrt(S) / T + S / std::pow(T, 2);
}

const double GetSignificance(const double& S, const double& B) {
  return S + B != 0 ? S / std::sqrt(S + B) : 0;
}

const double GetSigStatUn(const double& S, const double& B, const double& dS,
                          const double& dB) {
  if (S + B > 0) {
    double dSigdS, dSigdB;
    dSigdS = (2 * B + S) / (2 * std::pow(S + B, 3 / 2));
    dSigdB = -S / (2 * std::pow(S + B, 3 / 2));
    return std::sqrt(std::pow(dSigdS * dS, 2) + std::pow(dSigdB * dB, 2));
  } else {
    return 0.;
  };
}

const double GetSigStatUn(const double& S, const double& B, const double& T) {
  if (S + B > 0) {
    double dSigdS, dS, dSigdB, dB;
    dSigdS = (2 * B + S) / (2 * std::pow(S + B, 3 / 2));
    dSigdB = -S / (2 * std::pow(S + B, 3 / 2));
    dS = ErrRate(S, T);
    dB = ErrRate(B, T);
    return std::sqrt(std::pow(dSigdS * dS, 2) + std::pow(dSigdB * dB, 2));
  } else {
    return 0.;
  };
}

#endif