/*******************************************************************************
GPU OPTIMIZED MONTE CARLO (GOMC) 2.31
Copyright (C) 2018  GOMC Group
A copy of the GNU General Public License can be found in the COPYRIGHT.txt
along with this program, also can be found at <http://www.gnu.org/licenses/>.
********************************************************************************/
#ifndef SIMULATION_H
#define SIMULATION_H

//Member vars
#include "CPUSide.h"
#include "System.h"
#include "StaticVals.h"
#include "BasicTypes.h"

#include "Repl_Ex.h"
#include <omp.h>

class Simulation
{
public:
// GJS  
  bool usingRE;
  std::string replica_log;

  std::vector<float> replica_temps;
  std::vector<double> replica_pressures;
#if ENSEMBLE == NVT
  double volume = 0.0;
#endif

// GJS
  explicit Simulation(char const*const configFileName);
  explicit Simulation(char const*const configFileName, int initiatingLoopIteration, ReplicaExchangeParameters* replExParams);
  Simulation(void);
  ~Simulation();

  void RunSimulation(void);
  void RunSimulation(ReplicaExchangeParameters* replExParams, Simulation** sim_exchangers);
  void GetTemp(System* system, Simulation* sim);
  void SetTemp(System* system_set, Simulation* sim);

#ifndef NDEBUG
  void RunningCheck(const uint step);
#endif

private:
  System * system;
  StaticVals * staticValues;
  CPUSide * cpu;
  ulong totalSteps;
};

#endif /*SIMULATION_H*/
