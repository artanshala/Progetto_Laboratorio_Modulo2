#include <iostream>

#include "ParticleType.h"
#include "ResonanceType.h"

int main() {
  char e{'e'}, f{'f'};
  ParticleType* Test[2];
  Test[0] = new ParticleType{&e, 1.5, 2};
  Test[1] = new ResonanceType{&f, 0.5, 1, 3.3};
  for (int i = 0; i < 2; i++) {
    Test[i]->Print();
  }
}