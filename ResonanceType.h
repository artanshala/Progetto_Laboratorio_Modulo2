#include "ParticleType.h"

#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

class ResonanceType : public ParticleType {
    private:
    double const fWidth_;

    public:
    double GetResonanceTypeWidth () const;
    ResonanceType (char* fName, double fMass, int fCharge, double fWidth);
    void Print() const;

};
#endif