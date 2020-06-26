// Author: Claude Pruneau   09/25/2019

/***********************************************************************
 * Copyright (C) 2019, Claude Pruneau.
 * All rights reserved.
 * Based on the ROOT package and environment
 *
 * For the licensing terms see LICENSE.
 **********************************************************************/

#ifndef WAC_NuDynTask
#define WAC_NuDynTask
#include <TParameter.h>
#include "TFile.h"
#include "TList.h"
#include "Task.hpp"
#include "Event.hpp"
#include "EventFilter.hpp"
#include "NuDynHistos.hpp"
#include "NuDynDerivedHistos.hpp"

class NuDynTask : public Task
{
public:

  //////////////////////////////////////////////////////////////
  // CTOR
  //////////////////////////////////////////////////////////////
  NuDynTask(const TString &  name,
        TaskConfiguration * configuration,
        Event * event,
        EventFilter * eventFilter,
        ParticleFilter * particleFilter1,
        ParticleFilter * particleFilter2);
  virtual ~NuDynTask();
  virtual void execute();
  virtual void createHistograms();
  virtual void loadHistograms(TFile * inputFile);
  //virtual void loadBaseHistograms(TFile * inputFile);
  virtual void saveHistograms(TFile * outputFile);
//  virtual void addHistogramsToExtList(TList *list, bool all=false);
  virtual void scaleHistograms(double factor);
  virtual void calculateDerivedHistograms();

  //////////////////////////////////////////////////////////////
  // Data Members
  //////////////////////////////////////////////////////////////
  NuDynHistos * nuDynHistos;
  NuDynDerivedHistos * nuDynDerivedHistos;
  EventFilter     * eventFilter;
  ParticleFilter  * particleFilter1;
  ParticleFilter  * particleFilter2;
  TString partName1;
  TString partName2;

  ClassDef(NuDynTask,0)
};


#endif /* WAC_NuDynTask */