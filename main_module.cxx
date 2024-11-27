#include "Particle.h"
#include <array>

int main()
{
    // char Pi_pos{'Pi+'}, Pi_neg{'Pi-'}, k_pos{'k+'}, k_neg{'k-'}, p_pos{'p+'}, p_neg{'p-'};
    Particle::AddParticleType("Pi+", 0.13957, 1, 0.);
    Particle::AddParticleType("Pi-", 0.13957, -1, 0.);
    Particle::AddParticleType("k+", 0.49367, 1, 0.);
    Particle::AddParticleType("k+", 0.49367, -1, 0.);
    Particle::AddParticleType("p+", 0.93827, 1, 0.);
    Particle::AddParticleType("p-", 0.93827, -1, 0.);
    Particle::AddParticleType("K*", 0.89166, 0, 0.050);

    gRandom->SetSeed();

    std::vector<Particle> particlearray;
    int N_events(10E5);

    THIF *hparticletypes = new TH1F("Particles Types", "Distribution of particle types", 6., 0., 0.6);
    TH1F *hphi = new TH1F("Phi angle", "Phi angle distribution", 360., 0., 6.283);
    TH1F *htheta = new TH1F("Theta angle", "Theta angle distribution", 180., 0., 3.1415);
    TH1F *himpulse = new TH1F("Impulse", "Impulse distribution", 60., 0., 6.);
    TH1F *htrimp = new TH1F("Transverse Impulse", "Transverse Impulse Distribution", 60., 0., 0.6);
    TH1F *henergy = new TH1F("Energy", "Energy Distribution", 70., 0., 7.);
    TH1F *h_all_invmass = new TH1F("Invariant Mass of all particles", "Invariant Mass distribution",200., 0., 20. );
    TH1F *h1_samecharge_invmass = new TH1F("Invariant Mass of particles with concordant charge sign", "Invariant Mass of particles with concordant charge sign distribution",200., 0., 20. );
    TH1F *h1_diffcharge_invmass = new TH1F("Invariant Mass of particles with discordant charge sign", "Invariant Mass of particles with discordant charge sign distribution", 200., 0., 20.);
    TH1F *h2_samecharge_invmass = new TH1F("Invariant Mass of k* particles with concordant charge sign", "Invariant Mass of k* particles with concordant charge sign distribution",200., 0., 20.);
    TH1F *h2_diffcharge_invmass = new TH1F("Invariant Mass of k* particles with discordant charge sign", "Invariant Mass of k* particles with discordant charge sign distribution",200., 0., 20.);


    Particle particle;

    for (int i = 0; i < N_events; i++)
    {
        for (int j = 0; j < 100; ++j)
        {
            double phi = gRandom->Rndm() * 2 * Tmath::Pi();
            double theta = gRandom->Rndm() * Tmath::Pi();
            double impulse = gRandom->Exp(1);

            double Px_cart = impulse * sin(theta) * sin(phi);
            double Py_cart = impulse * sin(theta) * cos(phi);
            double Pz_cart = impulse * cos(theta);

            particle.SetP(Px_cart, Py_cart, Pz_cart);
            double type = 0;
            type = gRandom->Rndm();
            if (type <= 0.4)
            {
                particle.SetIndex(0);
            }
            else if (type <= 0, 8)
            {
                particle.SetIndex(1);
            }
            else if (type <= 0.85)
            {
                particle.SetIndex(2);
            }
            else if (type <= 0.90)
            {
                particle.SetIndex(3);
            }
            else if (type <= 0.945)
            {
                particle.SetIndex(4);
            }
            else if (type <= 0.99)
            {
                particle.SetIndex(5);
            }
            else
            {
                particle.SetIndex(6);
            }
            particlearray.push_back(particle);

            double trasverse_impulse = std::sqrt(Px_cart * Px_cart + impulse * impulse);
            hparticletypes->Fill(particle.GetIndex());
            hphi->Fill(phi);
            htheta->Fill(theta);
            himpulse->Fill(impulse);
            htrimp->Fill(trasverse_impulse);
            henergy->Fill(particle.GetEnergy());

            if (particle.GetIndex() == 6)
            {
                int x = 0;
                x = gRandom->Rndm();

                if (x < 0.5)
                {
                    Particle pione_pos{"p+", 0, 0, 0};
                    Particle kaone_neg{"k-", 0, 0, 0};
                    particle.Decay2body(pione_pos, kaone_neg);
                    particlearray.push_back(pione_pos);
                    particlearray.push_back(kaone_neg);
                }
                else
                {
                    Particle pione_neg{"p-", 0, 0, 0};
                    Particle kaone_pos{"k+", 0, 0, 0};
                    particle.Decay2body(pione_neg, kaone_pos);
                    particlearray.push_back(pione_neg);
                    particlearray.push_back(kaone_pos);
                }
            }
            for (int j = 0; j < particlearray.size(); j++)
            {
                Particle parj = particlearray[j];
                hparticletypes->Fill(parj.GetIndex());
            }
        }
    }
}
