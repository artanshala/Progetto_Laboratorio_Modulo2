#include "ResonanceType.h"

#include <iostream>

ResonanceType::ResonanceType(char* const fName, double const fMass,
                             int const fCharge, double const fWidth)
    : ParticleType(fName, fMass, fCharge), fWidth_(fWidth) {};

double ResonanceType::GetResonanceTypeWidth() const { return fWidth_; }

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "Width: " << fWidth_ << "\n";
}