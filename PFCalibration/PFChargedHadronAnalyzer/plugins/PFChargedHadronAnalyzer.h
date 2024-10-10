#ifndef RecoParticleFlow_PFPatProducer_PFChargedHadronAnalyzer_
#define RecoParticleFlow_PFPatProducer_PFChargedHadronAnalyzer_

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "DataFormats/ParticleFlowReco/interface/PFSimParticle.h"
#include "DataFormats/ParticleFlowReco/interface/PFSimParticleFwd.h"

#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"


#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <TH1.h>
#include <TH2.h>
#include <math.h>

#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
//#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"


#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"


/**\class PFChargedHadronAnalyzer
\brief selects isolated charged hadrons from PF Charged Hadrons

\author Patrick Janot
\date   September 13, 2010
*/

class PFChargedHadronAnalyzer : public edm::one::EDAnalyzer<> {
 public:

  typedef reco::PFCandidateCollection::const_iterator CI;

  explicit PFChargedHadronAnalyzer(const edm::ParameterSet&);

  ~PFChargedHadronAnalyzer();

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

  virtual void beginRun(const edm::Run & r, const edm::EventSetup & c);

 private:

  /// PFCandidates in which we'll look for pile up particles
  edm::InputTag   inputTagPFCandidates_;
  edm::InputTag   inputTagPFSimParticles_;
  edm::InputTag   inputTagEcalPFRechit_;
  edm::InputTag   inputTagHcalPFRechit_;
  edm::InputTag   inputTagEcalPFClusters_;
  edm::EDGetTokenT<reco::PFCandidateCollection> tokenPFCandidates_;
  edm::EDGetTokenT<reco::PFSimParticleCollection>   tokenPFSimParticles_;
  edm::EDGetTokenT<reco::PFClusterCollection>   tokenEcalPFClusters_;
  edm::EDGetTokenT<reco::PFRecHitCollection>  tokenEcalPFRechit_;
  edm::EDGetTokenT<reco::PFRecHitCollection>  tokenHcalPFRechit_;

  /// Min pt for charged hadrons
  double ptMin_;

  /// Min p for charged hadrons
  double pMin_;

  /// Min hcal raw energy for charged hadrons
  double hcalMin_;

  /// Max ecal raw energy to define a MIP
  double ecalMax_;

  /// Min number of pixel hits for charged hadrons
  int nPixMin_;

  // isMInbias simulation
  bool isMBMC_;

  /// Min number of track hits for charged hadrons
  std::vector<int> nHitMin_;
  std::vector<double> nEtaMin_;

  // Number of tracks after cuts
  std::vector<unsigned int> nCh;
  std::vector<unsigned int> nEv;

  // Consider on ly leading (smallest dR) clusters?
  bool leadingPFNHOnly_;
  bool leadingPFPhotonOnly_;

  std::string outputfile_;
  TFile *tf1;
  TTree* s;

  float true_,p_,ecal_,hcal_,eta_,phi_,ho_;
  float etaEcal_,phiEcal_;
  int charge_;
  std::vector<float> dr_,Eecal_,Ehcal_,pfcID_;
  //bhumika Nov 2018
  std::vector<float> EcalRechit_posx_,EcalRechit_posy_,EcalRechit_posz_,EcalRechit_E_,HcalRechit_posx_,HcalRechit_posy_,HcalRechit_posz_,HcalRechit_E_,EcalRechit_dr_,EcalRechit_depth_,HcalRechit_dr_,HcalRechit_depth_,HcalRechit_eta_,HcalRechit_phi_,EcalRechit_eta_,EcalRechit_phi_,EcalPFclustereta_,HcalPFclustereta_,emHitX,emHitY,emHitZ,emHitE,emHitF,hadHitX,hadHitY,hadHitZ,hadHitE,hadHitF;
  std::vector<float> correcal_,corrhcal_;
  std::vector<unsigned int> emHitIndex;
  std::vector<unsigned int> hadHitIndex;

  float Ccorrecal_,Ccorrhcal_,HcalRechit_totE_,EcalRechit_totE_;
  float emHitEtot,hadHitEtot;
  float emHitEFtot,hadHitEFtot;
  size_t orun,oevt,olumiBlock,otime;

  TH1F* h_true_barrel = new TH1F("h_true_barrel","input Energy in barrel",500,0,500);
  TH1F* h_true_ec_in = new TH1F("h_true_ec_in","input Energy in EC,in tracker",500,0,500);
  TH1F* h_true_ec_out = new TH1F("h_true_ec_out","input Energy in EC,out tracker",500,0,500);
  TH1F* h_true_hf = new TH1F("h_true_hf","input Energy in HF",500,0,500);

  edm::RunNumber_t run;
  edm::EventNumber_t evt;
  edm::LuminosityBlockNumber_t lumiBlock;
  edm::Timestamp time;

  std::vector<float> addDr,addEmE,addHadE,addEta,addPhi;
  std::vector<int> addPdgId;
  std::vector<float> genDr,genE,genEta,genPhi;
  std::vector<int> genPdgId;

  std::vector<float> cluEcalE;
  std::vector<float> cluEcalEta;
  std::vector<float> cluEcalPhi;

  std::vector<float> distEcalTrk;

  std::vector<float> cluHcalE;
  std::vector<float> cluHcalEta;
  std::vector<float> cluHcalPhi;

  float cluEcalEtot,cluHcalEtot;

  std::vector<float> distHcalTrk;
  std::vector<std::vector<float> > distHcalEcal;

  std::vector<int> pfcsID;

  std::vector<float> cluHadE;

  //Basic clusters ECAL
  std::vector<float> bcEcalE;
  std::vector<float> bcEcalEta;
  std::vector<float> bcEcalPhi;

  //SimHits
  std::vector<float> EcalSimHits;
  std::vector<float> ESSimHits;
  std::vector<float> HcalSimHits;

  std::vector<float> EcalRecHits;
  std::vector<float> ESRecHits;
  std::vector<float> HcalRecHits;

  std::vector<float> EcalRecHitsDr;
  std::vector<float> ESRecHitsDr;
  std::vector<float> HcalRecHitsDr;

  const CaloGeometry*    theCaloGeom;

  //  void SaveRecHits(const edm::Event& iEvent, float eta_, float phi_);

  void SaveSimHit(const edm::Event& iEvent, float eta_, float phi_);
  float Eta( float theta);

  /// verbose ?
  bool   verbose_;

  float dR(float eta1, float eta2, float phi1, float phi2 );

  float phi(float, float);
  float dPhi(float, float);


};

#endif
