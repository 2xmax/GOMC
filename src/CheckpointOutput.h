/*******************************************************************************
GPU OPTIMIZED MONTE CARLO (GOMC) 2.50
Copyright (C) 2018  GOMC Group
A copy of the GNU General Public License can be found in the COPYRIGHT.txt
along with this program, also can be found at <http://www.gnu.org/licenses/>.
********************************************************************************/
#pragma once

#include "OutputAbstracts.h"
#include "MoveSettings.h"
#include "Coordinates.h"
#include "MoveBase.h"
#include <iostream>
#include "GOMC_Config.h"

class CheckpointOutput : public OutputableBase
{
public:
  CheckpointOutput(System & sys, StaticVals const& statV);

  ~CheckpointOutput()
  {
    if(outputFile)
      fclose(outputFile);
  }

  virtual void DoOutput(const ulong step);
  virtual void Init(pdb_setup::Atoms const& atoms,
                    config_setup::Output const& output);
  virtual void Sample(const ulong step) {}
  virtual void Output(const ulong step)
  {
    if(!enableOutCheckpoint) {
      return;
    }

    if((step + 1) % stepsPerCheckpoint == 0) {
      DoOutput(step);
    }
  }

private:
  MoveSettings & moveSetRef;
  MoleculeLookup & molLookupRef;
  BoxDimensions & boxDimRef;
  Molecules const & molRef;
  PRNG & prngRef;
  Coordinates & coordCurrRef;

  bool enableOutCheckpoint;
  std::string filename;
  FILE* outputFile;
  ulong stepsPerCheckpoint;

  void openOutputFile();
  void printStepNumber(ulong step);
  void printRandomNumbers();
  void printCoordinates();
  void printMoleculeLookupData();
  void printMoveSettingsData();
  void printBoxDimensionsData();

  void printVector3DDouble(vector< vector< vector <double> > > data);
  void printVector3DUint(vector< vector< vector <uint> > > data);
  void printVector2DUint(vector< vector< uint > > data);
  void printVector1DDouble(vector< double > data);
  void outputDoubleIn8Chars(double data);
  void outputUintIn8Chars(uint32_t data);

};
