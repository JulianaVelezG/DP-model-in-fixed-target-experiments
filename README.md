# DP-model-in-fixed-target-experiments
Simulating DUNE-LBNF and SNS(COHERENT) in Geant4. Analizing DP signals in DUNE-LBNF using data from MadGraph and Geant4.

This repository contains the full simulation and analysis workflow used in my project on a dark matter model involving a dark photon ($A'$). The goal of the project is to evaluate the sensitivity of fixed-target experiments, particularly DUNE-LBNF, to the decay process \( $\pi^0→\gamma$ $A'$).

The Geant4 code simulates the collision of a proton with the DUNE-LBNF and SNS targets, and records information about the simulation outputs. Specifically, it stores data on:

- Neutral pions ($\pi^0$) produced in the collision,

- Photons resulting from $\pi^0→γγ$ decays,

- All photons that exit the target

- The subset of photons from $\pi^0$ decays that exit the target.

This information is saved in both .root and .txt formats for further analysis.

This repository includes a MadDump run card used to simulate the decay $\pi^0 →γA$. MadDump is used to simulate the decay of neutral pions from the DUNE-LBNF flux into photons and dark photons, for three masses of the dark photon:

- $m_A'= 0.01 GeV$
- $m_A'=0.05GeV$
- $m_A'= 0.1 GeV$

The resulting photon energy spectra are used to modify the expected SM photon distribution and estimate the sensitivity of DUNE to dark photons.

## Repository Structure

```bash
├── Geant4/
│   ├── src/
│   └── macros/
│       └── run.mac
├── MadGraph/
│   ├── cards/
│   │   └── param_card.dat
│   └── events_mass1.lhe, events_mass2.lhe, events_mass3.lhe
├── Analysis/
│   └── chi2_pvalue_analysis.py
├── gammaPiZeroExit.txt
├── README.md
