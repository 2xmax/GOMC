/*******************************************************************************
GPU OPTIMIZED MONTE CARLO (GOMC) 2.50
Copyright (C) 2018  GOMC Group
A copy of the GNU General Public License can be found in the COPYRIGHT.txt
along with this program, also can be found at <http://www.gnu.org/licenses/>.
********************************************************************************/
#ifndef DCFREECYCLESEED_H
#define DCFREECYCLESEED_H
#include "DCComponent.h"
#include "DCHedronCycle.h"
#include "CBMC.h"

namespace mol_setup
{
class MolKind;
}

namespace cbmc
{
class DCData;

class DCFreeCycleSeed : public DCComponent
{
public:
  DCFreeCycleSeed(DCData* data, const mol_setup::MolKind& kind,
                  std::vector<int> cycAtoms, uint focus, uint prev);
  void PrepareNew(TrialMol& newMol, uint molIndex);
  void PrepareOld(TrialMol& oldMol, uint molIndex);
  void BuildOld(TrialMol& oldMol, uint molIndex);
  void BuildNew(TrialMol& newMol, uint molIndex);
  void SetBondLengthNew(TrialMol& newMol);
  void SetBondLengthOld(TrialMol& oldMol);

  DCComponent* Clone()
  {
    return new DCFreeCycleSeed(*this);
  };

private:
  DCData* data;
  DCHedronCycle hed;
  //bond length of prev bonded to focus
  double anchorBond, anchorBondOld;
  //bond energy of built branch
  double bondEnergy;
  uint anchorKind;

  //bond length of atom bonded to focus
  double bondLength[MAX_BONDS];
  double bondLengthOld[MAX_BONDS];
  //bondKind between bonded[i] and focus
  uint bondKinds[MAX_BONDS];
  bool bondedInRing[MAX_BONDS];
};
}

#endif
