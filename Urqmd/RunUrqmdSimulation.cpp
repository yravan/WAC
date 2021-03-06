#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TROOT.h>

#include "EventLoop.hpp"
#include "Event.hpp"
#include "EventFilter.hpp"
#include "ParticleFilter.hpp"
#include "UrqmdEventReader.hpp"
#include "TwoPartCorrelationAnalyzer.hpp"
#include "NuDynTask.hpp"

/////////////////////////////////////////////////////////////////////////////////////////
// Run an analysis with Urqmd events
/////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  cout << "<INFO> Urqmd Analysis - Starting" << endl;

  long nEventsRequested = 1000000;
  int  nEventsReport    = 10000;

  AnalysisConfiguration * ac = new AnalysisConfiguration("Urqmd","Urqmd","1.0");
  ac->loadHistograms  = false;
  ac->createHistograms  = true;
  ac->scaleHistograms  = true;
  ac->calculateDerivedHistograms  = true;
  ac->saveHistograms  = true;
  ac->resetHistograms  = false;
  ac->clearHistograms  = false;
  ac->forceHistogramsRewrite  = true;
  ac->inputPath = "./";
  ac->configurationFileName = "configuration";
  ac->rootInputFileName = "";
  ac->outputPath = "./";
  ac->rootOuputFileName =  "output";
  ac->histoBaseName =  "Urqmd";


  ac->nBins_pt    = 40;
  ac->min_pt      = 0.2;
  ac->max_pt      = 3.0;
  ac->nBins_eta   = 20;
  ac->min_eta     = -2;
  ac->max_eta     = 2;
  ac->nBins_y     = 20;
  ac->min_y       = -2;
  ac->max_y       = 2;
  ac->nBins_phi   = 36;
  ac->min_phi     = 0.0;
  ac->max_phi     = 2.0*3.1415927;

  ac->nBins_DeltaPlong = 40;
  ac->min_DeltaPlong   = -1.0;
  ac->max_DeltaPlong   =  1.0;
  ac->nBins_DeltaPside = 40;
  ac->min_DeltaPside   = -1.0;
  ac->max_DeltaPside   =  1.0;
  ac->nBins_DeltaPout  = 40;
  ac->min_DeltaPout    = -1.0;
  ac->max_DeltaPout    =  1.0;

  ac->fillPairs        = true;
  ac->fill3D           = false;
  ac->fill6D           = false;
  ac->fillQ3D          = false;
  ac->fillY            = true;

  EventFilter     * eventFilter      = new EventFilter(EventFilter::MinBias,0.0,0.0);

  ParticleFilter  * particleFilter   = new ParticleFilter(ParticleFilter::Hadron, ParticleFilter::Charged,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter1  = new ParticleFilter(ParticleFilter::Hadron, ParticleFilter::Positive,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter2  = new ParticleFilter(ParticleFilter::Hadron, ParticleFilter::Negative,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter3  = new ParticleFilter(ParticleFilter::Pion,   ParticleFilter::Positive,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter4  = new ParticleFilter(ParticleFilter::Pion,   ParticleFilter::Negative,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter5  = new ParticleFilter(ParticleFilter::Kaon,   ParticleFilter::Positive,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter6  = new ParticleFilter(ParticleFilter::Kaon,   ParticleFilter::Negative,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only ParticleFilter  * particleFilter5  = new ParticleFilter(ParticleFilter::Pion, ParticleFilter::Positive,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter7  = new ParticleFilter(ParticleFilter::Proton, ParticleFilter::Positive,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only
  ParticleFilter  * particleFilter8  = new ParticleFilter(ParticleFilter::Proton, ParticleFilter::Negative,ac->min_pt+0.001,ac->max_pt,ac->min_eta,ac->max_eta, ac->min_y,ac->max_y); // +ve only

  Event * event = Event::getEvent();
  UrqmdEventReader * gen  = new UrqmdEventReader("Urqmd",0, event,eventFilter,particleFilter);
  TwoPartCorrelationAnalyzer  * ana1 = new TwoPartCorrelationAnalyzer ("Urqmd_TPCA_ALL",  ac,  event, eventFilter,particleFilter1,particleFilter2);
  TwoPartCorrelationAnalyzer  * ana2 = new TwoPartCorrelationAnalyzer ("Urqmd_TPCA_PiPi", ac,  event, eventFilter,particleFilter3,particleFilter4);
  TwoPartCorrelationAnalyzer  * ana3 = new TwoPartCorrelationAnalyzer ("Urqmd_TPCA_KK",   ac,  event, eventFilter,particleFilter5,particleFilter6);
  TwoPartCorrelationAnalyzer  * ana4 = new TwoPartCorrelationAnalyzer ("Urqmd_TPCA_PP",   ac,  event, eventFilter,particleFilter7,particleFilter8);

  NuDynTask * nudyn1 = new NuDynTask("Urqmd_NuDyn_ALL",    ac,  event, eventFilter,particleFilter1,particleFilter2);
  NuDynTask * nudyn2 = new NuDynTask("Urqmd_NuDyn_PiPi",   ac,  event, eventFilter,particleFilter3,particleFilter4);
  NuDynTask * nudyn3 = new NuDynTask("Urqmd_NuDyn_KK",     ac,  event, eventFilter,particleFilter5,particleFilter6);
  NuDynTask * nudyn4 = new NuDynTask("Urqmd_NuDyn_PP",     ac,  event, eventFilter,particleFilter7,particleFilter8);

  EventLoop * eventLoop = new EventLoop();

  gen->setReportLevel(MessageLogger::Info);
  ana1->setReportLevel(MessageLogger::Info);
  ana2->setReportLevel(MessageLogger::Info);
  ana3->setReportLevel(MessageLogger::Info);
  ana4->setReportLevel(MessageLogger::Info);
  nudyn1->setReportLevel(MessageLogger::Info);
  nudyn2->setReportLevel(MessageLogger::Info);
  nudyn3->setReportLevel(MessageLogger::Info);
  nudyn4->setReportLevel(MessageLogger::Info);
  eventLoop->setReportLevel(MessageLogger::Info);

  eventLoop->addTask(gen);
  eventLoop->addTask(ana1);
  eventLoop->addTask(ana2);
  eventLoop->addTask(ana3);
  eventLoop->addTask(ana4);
  eventLoop->addTask(nudyn1);
  eventLoop->addTask(nudyn2);
  eventLoop->addTask(nudyn3);
  eventLoop->addTask(nudyn4);
  eventLoop->run(nEventsRequested,nEventsReport);



  cout << "<INFO> Urqmd Model Analysis - Completed" << endl;

}
