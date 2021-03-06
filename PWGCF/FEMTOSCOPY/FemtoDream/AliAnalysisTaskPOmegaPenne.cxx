// /*
//  * AliAnalysisTaskPOmegaPenne.cxx
//  *
//  *  Created on: 11 Dec 2019
//  *      Author: Boris Bajtl
//  */



#include "AliAnalysisTaskPOmegaPenne.h"
#include <string.h>
#include "AliNanoAODTrack.h"
#include "TDatabasePDG.h"

ClassImp(AliAnalysisTaskPOmegaPenne)

    AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne() :  AliAnalysisTaskSE(),
                                                                fIsMC(false),
                                                                fmixBeforePC(0),
                                                                fmixAfterPC(0),
                                                                fisInvMassPairClean(0),
                                                                fmultTrigger(0),
                                                                ffullBlastQA(0),
                                                                VEvent(0),
                                                                VTrack(0),
                                                                fEvent(0),
                                                                fTrack(0),
                                                                fEventCuts(0),
                                                                fEventCuts2(0),
                                                                fv0(0),
                                                                fv0_2(0),
                                                                fCascade(0),
                                                                fCascade2(0),
                                                                fLambdaV0Cuts(0),
                                                                fLambdaV0Cuts2(0),
                                                                fAntiLambdaV0Cuts(0),
                                                                fAntiLambdaV0Cuts2(0),
                                                                fCascadeCutsXi(0),
                                                                fCascadeCutsXi2(0),
                                                                fCascadeCutsAntiXi(0),
                                                                fCascadeCutsAntiXi2(0),
                                                                fConfig(0),
                                                                fPairCleaner(0),
                                                                fPairCleaner2(0),
                                                                fPartColl(0),
                                                                fPartColl2(0),
                                                                fGTI(0),
                                                                fTrackBufferSize(10000),
                                                                tlEventCuts(0),
                                                                tlLambdaList(0),
                                                                tlAntiLambdaList(0),
                                                                tlCascadeCutsXi(0),
                                                                tlAntiCascadeCutsXi(0),
                                                                tlEventCuts2(0),
                                                                tlLambdaList2(0),
                                                                tlAntiLambdaList2(0),
                                                                tlCascadeCutsXi2(0),
                                                                tlAntiCascadeCutsXi2(0),
                                                                tlResults(0),
                                                                tlResults2(0),
                                                                tlResultsQA(0),
                                                                tlResultsQA2(0),
                                                                tlLambdaMC(0),
                                                                tlAntiLambdaMC(0),
                                                                tlXiMC(0),
                                                                tlAntiXiMC(0),
                                                                tlRecombination_before(0),  // recombination TList before
                                                                tlRecombination_after(0),  // recombination TList after
                                                                // mixing before
                                                                hInvMassLambda_sanityCheck_before(0),
                                                                hInvMassLambda_total_before(0),
                                                                hInvMassLambda_shared_pion_before(0),
                                                                hInvMassLambda_shared_proton_before(0),
                                                                hInvMassLambda_shared_lambda_before(0),
                                                                hInvMassXi_sanityCheck_before(0),
                                                                hInvMassXi_total_before(0),
                                                                hInvMassXi_shared_bach_before(0),
                                                                hInvMassXi_shared_pi_daugh_before(0),
                                                                hInvMassXi_shared_prot_daugh_before(0),
                                                                hInvMassXi_shared_Lambda_before(0),
                                                                hInvMassXi_shared_pion_bach_prot_daugh_before(0),
                                                                hInvMassXi_nothing_shared(0),
                                                                hInvMassAntiLambda_sanityCheck_before(0),
                                                                hInvMassAntiLambda_total_before(0),
                                                                hInvMassAntiLambda_shared_pion_before(0),
                                                                hInvMassAntiLambda_shared_proton_before(0),
                                                                hInvMassAntiXi_sanityCheck_before(0),
                                                                hInvMassAntiXi_total_before(0),
                                                                hInvMassAntiXi_shared_bach_before(0),
                                                                hInvMassAntiXi_shared_pi_daugh_before(0),
                                                                hInvMassAntiXi_shared_prot_daugh_before(0),
                                                                hInvMassAntiXi_shared_Lambda_before(0),
                                                                hInvMassAntiXi_shared_pion_bach_prot_daugh_before(0),
                                                                hInvMassAntiXi_nothing_shared(0),
                                                                fEvtCounterBefore(0),
                                                                // mixing after
                                                                tlLambdaRecombination_after(0),
                                                                tlAntiLambdaRecombination_after(0),
                                                                tlXiRecombination_after(0),
                                                                tlAntiXiRecombination_after(0),
                                                                hInvMassLambda_sanityCheck_after(0),
                                                                hInvMassLambda_pi_bach_Xi_after(0),
                                                                hInvMassLambda_pi_daugh_Xi_after(0),
                                                                hInvMassLambda_prot_Xi_after(0),
                                                                hInvMassLambda_full_lambda_from_Xi_after(0),
                                                                hInvMassXi_sanityCheck_after(0),
                                                                hInvMassXi_Lamda_pi_daugh_after(0),
                                                                hInvMassXi_Lamda_prot_daugh_after(0),
                                                                hInvMassXi_Lamda_pi_bach_after(0),
                                                                hInvMassXi_Lamda_full_after(0),
                                                                hInvMassXi_Lamda_pi_no_correctLambdaMass(0),
                                                                hInvMassXi_Lamda_prot_no_correctLambdaMass(0),
                                                                hInvMassAntiLambda_sanityCheck_after(0),
                                                                hInvMassAntiLambda_pi_bach_Xi_after(0),
                                                                hInvMassAntiLambda_pi_daugh_Xi_after(0),
                                                                hInvMassAntiLambda_prot_Xi_after(0),
                                                                hInvMassAntiLambda_full_lambda_from_Xi_after(0),
                                                                hInvMassAntiXi_sanityCheck_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_daugh_after(0),
                                                                hInvMassAntiXi_AntiLamda_antiprot_daugh_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_bach_after(0),
                                                                hInvMassAntiXi_AntiLamda_full_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass(0),
                                                                hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass(0),
                                                                fEvtCounterAfter(0),
                                                                // inv mass pair cleaner
                                                                tlInvMassPairClean(0),
                                                                tlCleanDecay(0),
                                                                tlCleanDecayAndDecay(0),
                                                                hLambdaCleanedPartMassDiffToPDG_Decay(0),
                                                                hAntiLambdaCleanedPartMassDiffToPDG_Decay(0),
                                                                hXiCleanedPartMassDiffToPDG_Decay(0),
                                                                hAntiXiCleanedPartMassDiffToPDG_Decay(0),
                                                                hLambdaCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                hXiCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                hAntiXiCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                hLambdaCleanedPartMass_Decay(0),
                                                                hAntiLambdaCleanedPartMass_Decay(0),
                                                                hXiCleanedPartMass_Decay(0),
                                                                hAntiXiCleanedPartMass_Decay(0),
                                                                hLambdaCleanedPartMass_DecayDecay(0),
                                                                hAntiLambdaCleanedPartMass_DecayDecay(0),
                                                                hXiCleanedPartMass_DecayDecay(0),
                                                                hAntiXiCleanedPartMass_DecayDecay(0),
                                                                // weird stuff
                                                                kStarXiLambda_unchanged(0),
                                                                kStarXiLambda_changed(0),
                                                                kStarAntiXiAntiLambda_unchanged(0),
                                                                kStarAntiXiAntiLambda_changed(0)
{
}
AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne(const char *name, bool isMC) : AliAnalysisTaskSE(name),
                                                                                      fIsMC(isMC),
                                                                                      fmixBeforePC(0),
                                                                                      fmixAfterPC(0),
                                                                                      fisInvMassPairClean(0),
                                                                                      fmultTrigger(0),
                                                                                      ffullBlastQA(0),
                                                                                      VEvent(0),
                                                                                      VTrack(0),
                                                                                      fEvent(0),
                                                                                      fTrack(0),
                                                                                      fEventCuts(0),
                                                                                      fEventCuts2(0),
                                                                                      fv0(0),
                                                                                      fv0_2(0),
                                                                                      fCascade(0),
                                                                                      fCascade2(0),
                                                                                      fLambdaV0Cuts(0),
                                                                                      fAntiLambdaV0Cuts(0),
                                                                                      fCascadeCutsXi(0),
                                                                                      fCascadeCutsAntiXi(0),
                                                                                      fLambdaV0Cuts2(0),
                                                                                      fAntiLambdaV0Cuts2(0),
                                                                                      fCascadeCutsXi2(0),
                                                                                      fCascadeCutsAntiXi2(0),
                                                                                      fConfig(0),
                                                                                      fPairCleaner(0),
                                                                                      fPairCleaner2(0),
                                                                                      fPartColl(0),
                                                                                      fPartColl2(0),
                                                                                      fGTI(0),
                                                                                      fTrackBufferSize(10000),
                                                                                      tlEventCuts(0),
                                                                                      tlLambdaList(0),
                                                                                      tlAntiLambdaList(0),
                                                                                      tlCascadeCutsXi(0),
                                                                                      tlAntiCascadeCutsXi(0),
                                                                                      tlEventCuts2(0),
                                                                                      tlLambdaList2(0),
                                                                                      tlAntiLambdaList2(0),
                                                                                      tlCascadeCutsXi2(0),
                                                                                      tlAntiCascadeCutsXi2(0),
                                                                                      tlResults(0),
                                                                                      tlResults2(0),
                                                                                      tlResultsQA(0),
                                                                                      tlResultsQA2(0),
                                                                                      tlLambdaMC(0),
                                                                                      tlAntiLambdaMC(0),
                                                                                      tlXiMC(0),
                                                                                      tlAntiXiMC(0),
                                                                                      tlRecombination_before(0),  // recombination TList before
                                                                                      tlRecombination_after(0),  // recombination TList after
                                                                                      // mixing before
                                                                                      hInvMassLambda_sanityCheck_before(0),
                                                                                      hInvMassLambda_total_before(0),
                                                                                      hInvMassLambda_shared_pion_before(0),
                                                                                      hInvMassLambda_shared_proton_before(0),
                                                                                      hInvMassLambda_shared_lambda_before(0),
                                                                                      hInvMassXi_sanityCheck_before(0),
                                                                                      hInvMassXi_total_before(0),
                                                                                      hInvMassXi_shared_bach_before(0),
                                                                                      hInvMassXi_shared_pi_daugh_before(0),
                                                                                      hInvMassXi_shared_prot_daugh_before(0),
                                                                                      hInvMassXi_shared_Lambda_before(0),
                                                                                      hInvMassXi_shared_pion_bach_prot_daugh_before(0),
                                                                                      hInvMassXi_nothing_shared(0),
                                                                                      hInvMassAntiLambda_sanityCheck_before(0),
                                                                                      hInvMassAntiLambda_total_before(0),
                                                                                      hInvMassAntiLambda_shared_pion_before(0),
                                                                                      hInvMassAntiLambda_shared_proton_before(0),
                                                                                      hInvMassAntiXi_sanityCheck_before(0),
                                                                                      hInvMassAntiXi_total_before(0),
                                                                                      hInvMassAntiXi_shared_bach_before(0),
                                                                                      hInvMassAntiXi_shared_pi_daugh_before(0),
                                                                                      hInvMassAntiXi_shared_prot_daugh_before(0),
                                                                                      hInvMassAntiXi_shared_Lambda_before(0),
                                                                                      hInvMassAntiXi_shared_pion_bach_prot_daugh_before(0),
                                                                                      hInvMassAntiXi_nothing_shared(0),
                                                                                      fEvtCounterBefore(0),
                                                                                      // mixing after
                                                                                      tlLambdaRecombination_after(0),
                                                                                      tlAntiLambdaRecombination_after(0),
                                                                                      tlXiRecombination_after(0),
                                                                                      tlAntiXiRecombination_after(0),
                                                                                      hInvMassLambda_sanityCheck_after(0),
                                                                                      hInvMassLambda_pi_bach_Xi_after(0),
                                                                                      hInvMassLambda_pi_daugh_Xi_after(0),
                                                                                      hInvMassLambda_prot_Xi_after(0),
                                                                                      hInvMassLambda_full_lambda_from_Xi_after(0),
                                                                                      hInvMassXi_sanityCheck_after(0),
                                                                                      hInvMassXi_Lamda_pi_daugh_after(0),
                                                                                      hInvMassXi_Lamda_prot_daugh_after(0),
                                                                                      hInvMassXi_Lamda_pi_bach_after(0),
                                                                                      hInvMassXi_Lamda_full_after(0),
                                                                                      hInvMassXi_Lamda_pi_no_correctLambdaMass(0),
                                                                                      hInvMassXi_Lamda_prot_no_correctLambdaMass(0),
                                                                                      hInvMassAntiLambda_sanityCheck_after(0),
                                                                                      hInvMassAntiLambda_pi_bach_Xi_after(0),
                                                                                      hInvMassAntiLambda_pi_daugh_Xi_after(0),
                                                                                      hInvMassAntiLambda_prot_Xi_after(0),
                                                                                      hInvMassAntiLambda_full_lambda_from_Xi_after(0),
                                                                                      hInvMassAntiXi_sanityCheck_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_daugh_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antiprot_daugh_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_bach_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_full_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass(0),
                                                                                      hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass(0),
                                                                                      fEvtCounterAfter(0),
                                                                                      // inv mass pair cleaner
                                                                                      tlInvMassPairClean(0),
                                                                                      tlCleanDecay(0),
                                                                                      tlCleanDecayAndDecay(0),
                                                                                      hLambdaCleanedPartMassDiffToPDG_Decay(0),
                                                                                      hAntiLambdaCleanedPartMassDiffToPDG_Decay(0),
                                                                                      hXiCleanedPartMassDiffToPDG_Decay(0),
                                                                                      hAntiXiCleanedPartMassDiffToPDG_Decay(0),
                                                                                      hLambdaCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                                      hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                                      hXiCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                                      hAntiXiCleanedPartMassDiffToPDG_DecayDecay(0),
                                                                                      hLambdaCleanedPartMass_Decay(0),
                                                                                      hAntiLambdaCleanedPartMass_Decay(0),
                                                                                      hXiCleanedPartMass_Decay(0),
                                                                                      hAntiXiCleanedPartMass_Decay(0),
                                                                                      hLambdaCleanedPartMass_DecayDecay(0),
                                                                                      hAntiLambdaCleanedPartMass_DecayDecay(0),
                                                                                      hXiCleanedPartMass_DecayDecay(0),
                                                                                      hAntiXiCleanedPartMass_DecayDecay(0),
                                                                                      // weird stuff
                                                                                      kStarXiLambda_unchanged(0),
                                                                                      kStarXiLambda_changed(0),
                                                                                      kStarAntiXiAntiLambda_unchanged(0),
                                                                                      kStarAntiXiAntiLambda_changed(0)
{
    DefineOutput(1, TList::Class());    // Event Cuts
    DefineOutput(2, TList::Class());    // Lambda Track Cuts
    DefineOutput(3, TList::Class());    // Anti Lambda Track Cuts
    DefineOutput(4, TList::Class());    // Xi Track Cuts
    DefineOutput(5, TList::Class());    // Anti Xi Track Cuts
    DefineOutput(6, TList::Class());    // Results - PairCleaner  - Keep Lambda
    DefineOutput(7, TList::Class());    // QA Results             - Keep Lambda

    DefineOutput(8, TList::Class());    // Event Cuts             - Keep Xi
    DefineOutput(9, TList::Class());    // Lambda Track Cuts      - Keep Xi
    DefineOutput(10, TList::Class());   // Anti Lambda Track Cuts - Keep Xi
    DefineOutput(11, TList::Class());   // Xi Track Cuts          - Keep Xi
    DefineOutput(12, TList::Class());   // Anti Xi Track Cuts     - Keep Xi
    DefineOutput(13, TList::Class());   // Results2 - PairCleaner - Keep Xi
    DefineOutput(14, TList::Class());   // QA Results2            - Keep Xi
    DefineOutput(15, TList::Class());       // reconstruction from daugthers histograms BEFORE Paricleaner
    DefineOutput(16, TList::Class());       // reconstruction from daugthers histograms AFTER PairCleaner

    if (isMC)
    {
        DefineOutput(17, TList::Class());    // MC V0 - Lamba
        DefineOutput(18, TList::Class());    // MC V0 - AntiLamba
        DefineOutput(19, TList::Class());    // MC Casc - Xi
        DefineOutput(20, TList::Class());    // MC Casc - AntiXi
    }
    
}

AliAnalysisTaskPOmegaPenne::~AliAnalysisTaskPOmegaPenne()       // Destructor
{
    delete VEvent;
    delete VTrack;
    delete fEvent;
    delete fTrack;
    delete fEventCuts;
    delete fEventCuts2;
    delete fv0;
    delete fv0_2;
    delete fCascade;
    delete fCascade2;
    delete fLambdaV0Cuts;
    delete fAntiLambdaV0Cuts;
    delete fCascadeCutsXi;
    delete fCascadeCutsAntiXi;
    delete fLambdaV0Cuts2;
    delete fAntiLambdaV0Cuts2;
    delete fCascadeCutsXi2;
    delete fCascadeCutsAntiXi2;
    delete fConfig;
    delete fPairCleaner;
    delete fPairCleaner2;
    delete fPartColl;
    delete fPairCleaner2;
    delete *fGTI;
    
    if (fGTI) delete fGTI;
}

// // Copy Constructor
AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne(const AliAnalysisTaskPOmegaPenne &obj) : AliAnalysisTaskSE(obj),
                                                                                                fIsMC(obj.fIsMC),
                                                                                                fisInvMassPairClean(0),
                                                                                                fmultTrigger(0),
                                                                                                fmixBeforePC(obj.fmixBeforePC),
                                                                                                fmixAfterPC(obj.fmixAfterPC),
                                                                                                ffullBlastQA(obj.ffullBlastQA),
                                                                                                VEvent(obj.VEvent),
                                                                                                VTrack(obj.VTrack),
                                                                                                fEvent(obj.fEvent),
                                                                                                fTrack(obj.fTrack),
                                                                                                fEventCuts(obj.fEventCuts),
                                                                                                fEventCuts2(obj.fEventCuts2),
                                                                                                fv0(obj.fv0),
                                                                                                fv0_2(obj.fv0_2),
                                                                                                fCascade(obj.fCascade),
                                                                                                fCascade2(obj.fCascade2),
                                                                                                fLambdaV0Cuts(obj.fLambdaV0Cuts),
                                                                                                fAntiLambdaV0Cuts(obj.fAntiLambdaV0Cuts),
                                                                                                fCascadeCutsXi(obj.fCascadeCutsXi),
                                                                                                fCascadeCutsAntiXi(obj.fCascadeCutsAntiXi),
                                                                                                fLambdaV0Cuts2(obj.fLambdaV0Cuts2),
                                                                                                fAntiLambdaV0Cuts2(obj.fAntiLambdaV0Cuts2),
                                                                                                fCascadeCutsXi2(obj.fCascadeCutsXi2),
                                                                                                fCascadeCutsAntiXi2(obj.fCascadeCutsAntiXi2),
                                                                                                fConfig(obj.fConfig),
                                                                                                fPairCleaner(obj.fPairCleaner),
                                                                                                fPartColl(obj.fPartColl),
                                                                                                fPartColl2(obj.fPartColl2),
                                                                                                fPairCleaner2(obj.fPairCleaner2),
                                                                                                fGTI(obj.fGTI),
                                                                                                fTrackBufferSize(obj.fTrackBufferSize),
                                                                                                tlEventCuts(obj.tlEventCuts),
                                                                                                tlLambdaList(obj.tlLambdaList),
                                                                                                tlAntiLambdaList(obj.tlAntiLambdaList),
                                                                                                tlCascadeCutsXi(obj.tlCascadeCutsXi),
                                                                                                tlAntiCascadeCutsXi(obj.tlAntiCascadeCutsXi),
                                                                                                tlEventCuts2(obj.tlEventCuts2),
                                                                                                tlLambdaList2(obj.tlLambdaList2),
                                                                                                tlAntiLambdaList2(obj.tlAntiLambdaList2),
                                                                                                tlCascadeCutsXi2(obj.tlCascadeCutsXi2),
                                                                                                tlAntiCascadeCutsXi2(obj.tlAntiCascadeCutsXi2),
                                                                                                tlResults(obj.tlResults),
                                                                                                tlResults2(obj.tlResults2),
                                                                                                tlResultsQA(obj.tlResultsQA),
                                                                                                tlResultsQA2(obj.tlResultsQA2),
                                                                                                tlLambdaMC(obj.tlLambdaMC),
                                                                                                tlAntiLambdaMC(obj.tlAntiLambdaMC),
                                                                                                tlXiMC(0),
                                                                                                tlAntiXiMC(0),
                                                                                                tlRecombination_before(obj.tlRecombination_before),     // recombination TList before
                                                                                                tlRecombination_after(obj.tlRecombination_after),       // recombination TList after
                                                                                                // mixing before
                                                                                                hInvMassLambda_sanityCheck_before(obj.hInvMassLambda_sanityCheck_before),
                                                                                                hInvMassLambda_total_before(obj.hInvMassLambda_total_before),
                                                                                                hInvMassLambda_shared_pion_before(obj.hInvMassLambda_shared_pion_before),
                                                                                                hInvMassLambda_shared_proton_before(obj.hInvMassLambda_shared_proton_before),
                                                                                                hInvMassLambda_shared_lambda_before(obj.hInvMassLambda_shared_lambda_before),
                                                                                                hInvMassXi_sanityCheck_before(obj.hInvMassXi_sanityCheck_before),
                                                                                                hInvMassXi_total_before(obj.hInvMassXi_total_before),
                                                                                                hInvMassXi_shared_bach_before(obj.hInvMassXi_shared_bach_before),
                                                                                                hInvMassXi_shared_pi_daugh_before(obj.hInvMassXi_shared_pi_daugh_before),
                                                                                                hInvMassXi_shared_prot_daugh_before(obj.hInvMassXi_shared_prot_daugh_before),
                                                                                                hInvMassXi_shared_Lambda_before(obj.hInvMassXi_shared_Lambda_before),
                                                                                                hInvMassXi_shared_pion_bach_prot_daugh_before(obj.hInvMassXi_shared_pion_bach_prot_daugh_before),
                                                                                                hInvMassXi_nothing_shared(obj.hInvMassXi_nothing_shared),
                                                                                                hInvMassAntiLambda_sanityCheck_before(obj.hInvMassAntiLambda_sanityCheck_before),
                                                                                                hInvMassAntiLambda_total_before(obj.hInvMassAntiLambda_total_before),
                                                                                                hInvMassAntiLambda_shared_pion_before(obj.hInvMassAntiLambda_shared_pion_before),
                                                                                                hInvMassAntiLambda_shared_proton_before(obj.hInvMassAntiLambda_shared_proton_before),
                                                                                                hInvMassAntiXi_sanityCheck_before(obj.hInvMassAntiXi_sanityCheck_before),
                                                                                                hInvMassAntiXi_total_before(obj.hInvMassAntiXi_total_before),
                                                                                                hInvMassAntiXi_shared_bach_before(obj.hInvMassAntiXi_shared_bach_before),
                                                                                                hInvMassAntiXi_shared_pi_daugh_before(obj.hInvMassAntiXi_shared_pi_daugh_before),
                                                                                                hInvMassAntiXi_shared_prot_daugh_before(obj.hInvMassAntiXi_shared_prot_daugh_before),
                                                                                                hInvMassAntiXi_shared_Lambda_before(obj.hInvMassAntiXi_shared_Lambda_before),
                                                                                                hInvMassAntiXi_shared_pion_bach_prot_daugh_before(obj.hInvMassAntiXi_shared_pion_bach_prot_daugh_before),
                                                                                                hInvMassAntiXi_nothing_shared(obj.hInvMassAntiXi_nothing_shared),
                                                                                                fEvtCounterBefore(obj.fEvtCounterBefore),
                                                                                                // mixing after
                                                                                                tlLambdaRecombination_after(obj.tlLambdaRecombination_after),
                                                                                                tlAntiLambdaRecombination_after(obj.tlAntiLambdaRecombination_after),
                                                                                                tlXiRecombination_after(obj.tlXiRecombination_after),
                                                                                                tlAntiXiRecombination_after(obj.tlAntiXiRecombination_after),
                                                                                                hInvMassLambda_sanityCheck_after(obj.hInvMassLambda_sanityCheck_after),
                                                                                                hInvMassLambda_pi_bach_Xi_after(obj.hInvMassLambda_pi_bach_Xi_after),
                                                                                                hInvMassLambda_pi_daugh_Xi_after(obj.hInvMassLambda_pi_daugh_Xi_after),
                                                                                                hInvMassLambda_prot_Xi_after(obj.hInvMassLambda_prot_Xi_after),
                                                                                                hInvMassLambda_full_lambda_from_Xi_after(obj.hInvMassLambda_full_lambda_from_Xi_after),
                                                                                                hInvMassXi_sanityCheck_after(obj.hInvMassXi_sanityCheck_after),
                                                                                                hInvMassXi_Lamda_pi_daugh_after(obj.hInvMassXi_Lamda_pi_daugh_after),
                                                                                                hInvMassXi_Lamda_prot_daugh_after(obj.hInvMassXi_Lamda_prot_daugh_after),
                                                                                                hInvMassXi_Lamda_pi_bach_after(obj.hInvMassXi_Lamda_pi_bach_after),
                                                                                                hInvMassXi_Lamda_full_after(obj.hInvMassXi_Lamda_full_after),
                                                                                                hInvMassXi_Lamda_pi_no_correctLambdaMass(obj.hInvMassXi_Lamda_pi_no_correctLambdaMass),
                                                                                                hInvMassXi_Lamda_prot_no_correctLambdaMass(obj.hInvMassXi_Lamda_prot_no_correctLambdaMass),
                                                                                                hInvMassAntiLambda_sanityCheck_after(obj.hInvMassAntiLambda_sanityCheck_after),
                                                                                                hInvMassAntiLambda_pi_bach_Xi_after(obj.hInvMassAntiLambda_pi_bach_Xi_after),
                                                                                                hInvMassAntiLambda_pi_daugh_Xi_after(obj.hInvMassAntiLambda_pi_daugh_Xi_after),
                                                                                                hInvMassAntiLambda_prot_Xi_after(obj.hInvMassAntiLambda_prot_Xi_after),
                                                                                                hInvMassAntiLambda_full_lambda_from_Xi_after(obj.hInvMassAntiLambda_full_lambda_from_Xi_after),
                                                                                                hInvMassAntiXi_sanityCheck_after(obj.hInvMassAntiXi_sanityCheck_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_daugh_after(obj.hInvMassAntiXi_AntiLamda_antipi_daugh_after),
                                                                                                hInvMassAntiXi_AntiLamda_antiprot_daugh_after(obj.hInvMassAntiXi_AntiLamda_antiprot_daugh_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_bach_after(obj.hInvMassAntiXi_AntiLamda_antipi_bach_after),
                                                                                                hInvMassAntiXi_AntiLamda_full_after(obj.hInvMassAntiXi_AntiLamda_full_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass(obj.hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass),
                                                                                                hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass(obj.hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass),
                                                                                                fEvtCounterAfter(obj.fEvtCounterAfter),
                                                                                                // inv mass pair cleaner
                                                                                                tlInvMassPairClean(obj.tlInvMassPairClean),
                                                                                                tlCleanDecay(obj.tlCleanDecay),
                                                                                                tlCleanDecayAndDecay(obj.tlCleanDecayAndDecay),
                                                                                                hLambdaCleanedPartMassDiffToPDG_Decay(obj.hLambdaCleanedPartMassDiffToPDG_Decay),
                                                                                                hAntiLambdaCleanedPartMassDiffToPDG_Decay(obj.hAntiLambdaCleanedPartMassDiffToPDG_Decay),
                                                                                                hXiCleanedPartMassDiffToPDG_Decay(obj.hXiCleanedPartMassDiffToPDG_Decay),
                                                                                                hAntiXiCleanedPartMassDiffToPDG_Decay(obj.hAntiXiCleanedPartMassDiffToPDG_Decay),
                                                                                                hLambdaCleanedPartMassDiffToPDG_DecayDecay(obj.hLambdaCleanedPartMassDiffToPDG_DecayDecay),
                                                                                                hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay(obj.hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay),
                                                                                                hXiCleanedPartMassDiffToPDG_DecayDecay(obj.hXiCleanedPartMassDiffToPDG_DecayDecay),
                                                                                                hAntiXiCleanedPartMassDiffToPDG_DecayDecay(obj.hAntiXiCleanedPartMassDiffToPDG_DecayDecay),
                                                                                                hLambdaCleanedPartMass_Decay(obj.hLambdaCleanedPartMass_Decay),
                                                                                                hAntiLambdaCleanedPartMass_Decay(obj.hAntiLambdaCleanedPartMass_Decay),
                                                                                                hXiCleanedPartMass_Decay(obj.hXiCleanedPartMass_Decay),
                                                                                                hAntiXiCleanedPartMass_Decay(obj.hAntiXiCleanedPartMass_Decay),
                                                                                                hLambdaCleanedPartMass_DecayDecay(obj.hLambdaCleanedPartMass_DecayDecay),
                                                                                                hAntiLambdaCleanedPartMass_DecayDecay(obj.hAntiLambdaCleanedPartMass_DecayDecay),
                                                                                                hXiCleanedPartMass_DecayDecay(obj.hXiCleanedPartMass_DecayDecay),
                                                                                                hAntiXiCleanedPartMass_DecayDecay(obj.hAntiXiCleanedPartMass_DecayDecay),
                                                                                                kStarXiLambda_unchanged(obj.kStarXiLambda_unchanged),
                                                                                                kStarXiLambda_changed(obj.kStarXiLambda_changed),
                                                                                                kStarAntiXiAntiLambda_unchanged(obj.kStarAntiXiAntiLambda_unchanged),
                                                                                                kStarAntiXiAntiLambda_changed(obj.kStarAntiXiAntiLambda_changed)
{
}

// AliAnalysisTaskPOmegaPenne& AliAnalysisTaskPOmegaPenne::operator=(const AliAnalysisTaskPOmegaPenne &other)
// {
//     AliAnalysisTaskSE::operator=(other);
//     this->fIsMC = other.fIsMC;
//     this->aaEvent = other.aaEvent;
//     this->aaTrack = other.aaTrack;
//     this->fOutput = other.fOutput;
//     this->fEvent = other.fEvent;
//     this->fTrack = other.fTrack;
//     this->fCascade = other.fCascade;
//     this->fEventCuts = other.fEventCuts;
//     this->fTrackCutsProton = other.fTrackCutsProton;
//     this->fTrackCutsAntiProton = other.fTrackCutsAntiProton;
//     this->fCascadeCutsXi = other.fCascadeCutsXi;
//     this->fCascadeCutsAntiXi = other.fCascadeCutsAntiXi;
//     this->fConfig = other.fConfig;
//     this->fPairCleaner = other.fPairCleaner;
//     this->fPartColl = other.fPartColl;
//     this->fGTI = other.fGTI;
//     this->fTrackBufferSize = other.fTrackBufferSize;

//     return *this;
// }

void AliAnalysisTaskPOmegaPenne::UserCreateOutputObjects()
{
   
    fEvent = new AliFemtoDreamEvent(true, ffullBlastQA, GetCollisionCandidates(), false);
    fEvent->SetMultiplicityEstimator(fConfig->GetMultiplicityEstimator());


    // fTrack = new AliFemtoDreamTrack();
    // fTrack->SetUseMCInfo(fIsMC);
    fGTI = new AliVTrack *[fTrackBufferSize];
    
    fEventCuts->InitQA();
    
 
    // Lambda Cutys    ###########
    if (!fLambdaV0Cuts){AliFatal("Track Cuts for Particle Lambda not set!");}
    fLambdaV0Cuts->Init();
    fLambdaV0Cuts->SetName("Lambda");
    // ##

    // AntiLambda Cutys    ###########
    if (!fAntiLambdaV0Cuts){AliFatal("Track Cuts for Particle AntiLambda not set!");}
    fAntiLambdaV0Cuts->Init();
    fAntiLambdaV0Cuts->SetName("AntiLambda");
    // ##

    // V0 Candidates
    fv0 = new AliFemtoDreamv0();
    fv0->SetUseMCInfo(fIsMC);
    fv0->GetPosDaughter()->SetUseMCInfo(fIsMC); 
    fv0->GetNegDaughter()->SetUseMCInfo(fIsMC); 
    fv0->SetPDGCode(3122);
    fv0->SetPDGDaughterPos(2212);
    fv0->SetPDGDaughterNeg(211);
    // ##

    // Xi Cuts    ###########
    if (!fCascadeCutsXi){AliFatal("Track Cuts for Particle Xi not set!");}
    fCascadeCutsXi->Init();
    fCascadeCutsXi->SetName("Xi");
    // ##
    
    // AntiXi Cuts    ###########
    if (!fCascadeCutsAntiXi){AliFatal("Track Cuts for Particle AntiXi not set!");}
    fCascadeCutsAntiXi->Init();
    fCascadeCutsAntiXi->SetName("AntiXi");
    // ##

    // Cascade Cuts     #########
    fCascade = new AliFemtoDreamCascade();          // Initial Cascade Object
    fCascade->              SetUseMCInfo(fCascadeCutsXi->GetIsMonteCarlo() || fCascadeCutsAntiXi->GetIsMonteCarlo());
    //PDG Codes should be set assuming Xi- to also work for Xi+
    fCascade->SetPDGCode(3312);
    fCascade->SetPDGDaugPos(2212);
    fCascade->GetPosDaug()->SetUseMCInfo(fCascadeCutsXi->GetIsMonteCarlo() || fCascadeCutsAntiXi->GetIsMonteCarlo());
    fCascade->SetPDGDaugNeg(211);
    fCascade->GetNegDaug()->SetUseMCInfo(fCascadeCutsXi->GetIsMonteCarlo() || fCascadeCutsAntiXi->GetIsMonteCarlo());
    fCascade->SetPDGDaugBach(211);
    fCascade->GetBach()   ->SetUseMCInfo(fCascadeCutsXi->GetIsMonteCarlo() || fCascadeCutsAntiXi->GetIsMonteCarlo());
    fCascade->Setv0PDGCode(3122);
    // ##

    fEventCuts2->InitQA();
    // ############################################# NUMMER 2 - only Xi left alive ############################
    // Lambda Cutys    ###########
    if (!fLambdaV0Cuts2){AliFatal("Track Cuts for Particle Lambda not set!");}
    fLambdaV0Cuts2->Init();
    fLambdaV0Cuts2->SetName("Lambda");
    // ##

    // AntiLambda Cutys    ###########
    if (!fAntiLambdaV0Cuts2){AliFatal("Track Cuts for Particle AntiLambda not set!");}
    fAntiLambdaV0Cuts2->Init();
    fAntiLambdaV0Cuts2->SetName("AntiLambda");
    // ##

    // V0 Candidates
    fv0_2 = new AliFemtoDreamv0();
    fv0_2->                  SetUseMCInfo(fLambdaV0Cuts2->GetIsMonteCarlo() || fAntiLambdaV0Cuts2->GetIsMonteCarlo());
    fv0_2->GetPosDaughter()->SetUseMCInfo(fLambdaV0Cuts2->GetIsMonteCarlo() || fAntiLambdaV0Cuts2->GetIsMonteCarlo()); 
    fv0_2->GetNegDaughter()->SetUseMCInfo(fLambdaV0Cuts2->GetIsMonteCarlo() || fAntiLambdaV0Cuts2->GetIsMonteCarlo()); 
    
    fv0_2->SetPDGCode(3122);
    fv0_2->SetPDGDaughterPos(2212);
    fv0_2->SetPDGDaughterNeg(211);
    // ##

    // Xi Cuts    ###########
    if (!fCascadeCutsXi2){AliFatal("Track Cuts for Particle Xi not set!");}
    fCascadeCutsXi2->Init();
    fCascadeCutsXi2->SetName("Xi");
    // ##
    
    // AntiXi Cuts    ###########
    if (!fCascadeCutsAntiXi2){AliFatal("Track Cuts for Particle AntiXi not set!");}
    fCascadeCutsAntiXi2->Init();
    fCascadeCutsAntiXi2->SetName("AntiXi");
    // ##

    // Cascade Cuts     #########
    fCascade2 = new AliFemtoDreamCascade();          // Initial Cascade Object
    fCascade2->              SetUseMCInfo(fCascadeCutsXi2->GetIsMonteCarlo() || fCascadeCutsAntiXi2->GetIsMonteCarlo());
    //PDG Codes should be set assuming Xi- to also work for Xi+
    fCascade2->SetPDGCode(3312);
    fCascade2->SetPDGDaugPos(2212);
    fCascade2->GetPosDaug()->SetUseMCInfo(fCascadeCutsXi2->GetIsMonteCarlo() || fCascadeCutsAntiXi2->GetIsMonteCarlo());
    fCascade2->SetPDGDaugNeg(211);
    fCascade2->GetNegDaug()->SetUseMCInfo(fCascadeCutsXi2->GetIsMonteCarlo() || fCascadeCutsAntiXi2->GetIsMonteCarlo());
    fCascade2->SetPDGDaugBach(211);
    fCascade2->GetBach()->   SetUseMCInfo(fCascadeCutsXi2->GetIsMonteCarlo() || fCascadeCutsAntiXi2->GetIsMonteCarlo());
    fCascade2->Setv0PDGCode(3122);
    // ##
    // ############################################# ENDE - NUMMER 2 - only Xi left alive ######################


    // ############################################# Recombination Cuts ######################
    // Lambda Cutys    ###########
    // if (!fLambdaV0Cuts_rec){AliFatal("Track Cuts for Particle Lambda_recombination not set!");}
    // fLambdaV0Cuts_rec->Init();
    // fLambdaV0Cuts_rec->SetName("Lambda_rec");
    // ##
    // AntiLambda Cutys    ###########
    // if (!fAntiLambdaV0Cuts_rec){AliFatal("Track Cuts for Particle AntiLambda_recombination not set!");}
    // fAntiLambdaV0Cuts_rec->Init();
    // fAntiLambdaV0Cuts_rec->SetName("AntiLambda_rec");
    // ##
    // ############################################# ENDE - Recombination Cuts ######################


    fPairCleaner = new AliFemtoDreamPairCleaner(0, 4, false);
    fPairCleaner2 = new AliFemtoDreamPairCleaner(0, 4, false);
    fPartColl = new AliFemtoDreamPartCollection(fConfig, false);
    fPartColl2 = new AliFemtoDreamPartCollection(fConfig, false);
    
    tlCascadeCutsXi = new TList();
    tlCascadeCutsXi->SetName("XiCascade");
    tlCascadeCutsXi->SetOwner();

    tlAntiCascadeCutsXi = new TList();
    tlAntiCascadeCutsXi->SetName("AntiXiCascade");
    tlAntiCascadeCutsXi->SetOwner();

    tlResultsQA = new TList();
    tlResultsQA->SetName("ResultsQA");
    tlResultsQA->SetOwner();

    tlResultsQA2 = new TList();
    tlResultsQA2->SetName("ResultsQA2");
    tlResultsQA2->SetOwner();

    /////////////////////////////
    // BEFORE Paircleaning histos
    /////////////////////////////
    tlRecombination_before = new TList();        // Lambda and Xi recombination statistic histogramms for interchanged daughters
    tlRecombination_before->SetName("Recombination_before_pairclean");
    tlRecombination_before->SetOwner();
    
    if (fmixBeforePC)
    {

        // particles
        hInvMassLambda_sanityCheck_before = new TH1F("InvariantMassLambdaSanityCheck_before", "Invariant Mass LAMBDA Sanity Check before", 400, 1.00, 1.20);                                  // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassLambda_total_before = new TH1F("InvariantMassLambdatotal_before", "Invariant Mass LAMBDA total before", 400, 1.00, 1.20);                                                     // summe kombinationen mit shared tracks und non-shared
        hInvMassLambda_shared_pion_before = new TH1F("InvariantMassLambdaSharedPion_before", "Invariant Mass LAMBDA shared Pion before", 800, 1.00, 1.40);                                    // shared Pion - blödsinnig, hier hat man beim mixing einfach einmal das eine Lambda dann dass andere
        hInvMassLambda_shared_proton_before = new TH1F("InvariantMassLambdaSharedProton_before", "Invariant Mass LAMBDA shared Proton before", 800, 1.00, 1.40);                              // shared Proton - blödsinnig, hier hat man beim mixing einfach einmal das eine Lambda dann dass andere
        hInvMassLambda_shared_lambda_before = new TH1F("InvariantMassLambdaSharedLambda_before", "Invariant Mass LAMBDA shared Lambda before", 800, 1.00, 1.40);                              // fully shared Lambda - sollte leer sein
        hInvMassXi_sanityCheck_before = new TH1F("InvariantMassXiSanityCheck_before", "Invariant Mass XI Sanity Check before", 800, 1.200, 1.600);                                            // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassXi_total_before = new TH1F("InvariantMassXiTotal_before", "Invariant Mass XI total before", 500, 1.1898, 1.7186);                                                             // summe kombinationen aus shared tracks und non-shared
        hInvMassXi_shared_bach_before = new TH1F("InvariantMassXiSharedBach_before", "Invariant Mass XI shared Bachelor Pi before", 500, 1.1898, 1.7186);                                     // shared Bachelor Pion
        hInvMassXi_shared_pi_daugh_before = new TH1F("InvariantMassXiSharedPiDaugh_before", "Invariant Mass XI shared Pi Daugh before", 500, 1.1898, 1.7186);                                 // shared Daughter Pion
        hInvMassXi_shared_prot_daugh_before = new TH1F("InvariantMassXiSharedProtDaugh_before", "Invariant Mass XI shared Prot Daugh before", 500, 1.1898, 1.7186);                           // shared Daughter Proton
        hInvMassXi_shared_Lambda_before = new TH1F("InvariantMassXiSharedLambda_before", "Invariant Mass XI shared Lambda before", 500, 1.1898, 1.7186);                                      // shared Daughter Pion and Proton - i.e. shared Lambda
        hInvMassXi_shared_pion_bach_prot_daugh_before = new TH1F("InvariantMassXiSharedPiBachProtDaugh_before", "Invariant Mass XI shared Pion Bach Prot Daugh before", 500, 1.1898, 1.7186); // nur der vollständigkeitshalber (sollte nix drin sein) - geteiltes Bachelor Pion und gleichzeitig Proton Daughter
        hInvMassXi_nothing_shared = new TH1F("InvariantMassXiNothingShared_before", "Invariant Mass XI nothing shared before", 500, 1.1898, 1.7186);
        // anti particles
        hInvMassAntiLambda_sanityCheck_before = new TH1F("InvariantMassAntiLambdaSanityCheck_before", "Invariant Mass Anti LAMBDA Sanity Check before", 400, 1.00, 1.20); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassAntiLambda_total_before = new TH1F("InvariantMassAntiLambdatotal_before", "Invariant Mass Anti LAMBDA total before", 400, 1.00, 1.20);
        hInvMassAntiLambda_shared_pion_before = new TH1F("InvariantMassAntiLambdaSharedPion_before", "Invariant Mass Anti LAMBDA shared Pion before", 800, 1.00, 1.40);
        hInvMassAntiLambda_shared_proton_before = new TH1F("InvariantMassAntiLambdaSharedProton_before", "Invariant Mass Anti LAMBDA shared Proton before", 800, 1.00, 1.40);
        hInvMassAntiLambda_shared_lambda_before = new TH1F("InvariantMassAntiLambdaSharedLambda_before", "Invariant Mass Anti LAMBDA shared Lambda before", 800, 1.00, 1.40);
        hInvMassAntiXi_sanityCheck_before = new TH1F("InvariantMassAntiXiSanityCheck_before", "Invariant Mass Anti XI Sanity Check before", 800, 1.200, 1.600); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassAntiXi_total_before = new TH1F("InvariantMassAntiXiTotal_before", "Invariant Mass Anti XI total before", 500, 1.1898, 1.7186);
        hInvMassAntiXi_shared_bach_before = new TH1F("InvariantMassAntiXiSharedBach_before", "Invariant Mass Anti XI shared Bachelor Pi before", 500, 1.1898, 1.7186);
        hInvMassAntiXi_shared_pi_daugh_before = new TH1F("InvariantMassAntiXiSharedPiDaugh_before", "Invariant Mass Anti XI shared Pi Daugh before", 500, 1.1898, 1.7186);
        hInvMassAntiXi_shared_prot_daugh_before = new TH1F("InvariantMassAntiXiSharedProtDaugh_before", "Invariant Mass Anti XI shared Prot Daugh before", 500, 1.1898, 1.7186);
        hInvMassAntiXi_shared_Lambda_before = new TH1F("InvariantMassAntiXiSharedLambda_before", "Invariant Mass Anti XI shared Lambda before", 500, 1.1898, 1.7186);
        hInvMassAntiXi_shared_pion_bach_prot_daugh_before = new TH1F("InvariantMassAntiXiSharedPiBachProtDaugh_before", "Invariant Mass Anti XI shared Pion Bach Prot Daugh before", 500, 1.1898, 1.7186); // nur der vollständigkeitshalber (sollte nix drin sein) - geteiltes Bachelor Pion und gleichzeitig proton daughter
        hInvMassAntiXi_nothing_shared = new TH1F("InvariantMassAntiXiNothingShared_before", "Invariant Mass Anti XI nothing shared before", 500, 1.1898, 1.7186);
        //
        // Event counter for what happened how often
        fEvtCounterBefore = new TH1F("EventCounter", "Event Counter", 7, 0, 7);
        fEvtCounterBefore->GetXaxis()->SetBinLabel(1, "Prot_Lambda + pi_Xi1");    // reconstruct Lambda
        fEvtCounterBefore->GetXaxis()->SetBinLabel(2, "Prot_Lambda + pi_Xi2");    //
        fEvtCounterBefore->GetXaxis()->SetBinLabel(3, "Prot_Xi + pi_Lambda");     //
        fEvtCounterBefore->GetXaxis()->SetBinLabel(4, "Lambda + pi_Xi1");         // reconstruct Xi
        fEvtCounterBefore->GetXaxis()->SetBinLabel(5, "Lambda + pi_Xi2");         //
        fEvtCounterBefore->GetXaxis()->SetBinLabel(6, "Lambda + pi_Lambda");      //
        fEvtCounterBefore->GetXaxis()->SetBinLabel(7, "prot_Lambda + pi_Lambda"); //s reconstruct Lambda from other Lambda

        // connect to Output List
        tlRecombination_before->Add(hInvMassLambda_sanityCheck_before);
        tlRecombination_before->Add(hInvMassLambda_total_before);
        tlRecombination_before->Add(hInvMassLambda_shared_pion_before);
        tlRecombination_before->Add(hInvMassLambda_shared_proton_before);
        tlRecombination_before->Add(hInvMassLambda_shared_lambda_before);
        tlRecombination_before->Add(hInvMassXi_sanityCheck_before);
        tlRecombination_before->Add(hInvMassXi_total_before);
        tlRecombination_before->Add(hInvMassXi_shared_bach_before);
        tlRecombination_before->Add(hInvMassXi_shared_pi_daugh_before);
        tlRecombination_before->Add(hInvMassXi_shared_prot_daugh_before);
        tlRecombination_before->Add(hInvMassXi_shared_Lambda_before);
        tlRecombination_before->Add(hInvMassXi_shared_pion_bach_prot_daugh_before);
        tlRecombination_before->Add(hInvMassXi_nothing_shared);

        tlRecombination_before->Add(hInvMassAntiLambda_sanityCheck_before);
        tlRecombination_before->Add(hInvMassAntiLambda_total_before);
        tlRecombination_before->Add(hInvMassAntiLambda_shared_pion_before);
        tlRecombination_before->Add(hInvMassAntiLambda_shared_proton_before);
        tlRecombination_before->Add(hInvMassAntiLambda_shared_lambda_before);
        tlRecombination_before->Add(hInvMassAntiXi_sanityCheck_before);
        tlRecombination_before->Add(hInvMassAntiXi_total_before);
        tlRecombination_before->Add(hInvMassAntiXi_shared_bach_before);
        tlRecombination_before->Add(hInvMassAntiXi_shared_pi_daugh_before);
        tlRecombination_before->Add(hInvMassAntiXi_shared_prot_daugh_before);
        tlRecombination_before->Add(hInvMassAntiXi_shared_Lambda_before);
        tlRecombination_before->Add(hInvMassAntiXi_shared_pion_bach_prot_daugh_before);
        tlRecombination_before->Add(hInvMassAntiXi_nothing_shared);

        tlRecombination_before->Add(fEvtCounterBefore);
    }
    // $$$ END - BEFORE Paircleaning $$$

    ////////////////////////////
    // AFTER Paircleaning histos
    ////////////////////////////
    tlRecombination_after = new TList();
    tlRecombination_after->SetName("Recombination_after_pairclean");
    tlRecombination_after->SetOwner();

    if(fmixAfterPC)
    {
        tlLambdaRecombination_after = new TList();
        tlLambdaRecombination_after->SetName("LambdaRecombination_after");
        tlLambdaRecombination_after->SetOwner();

        tlAntiLambdaRecombination_after = new TList();
        tlAntiLambdaRecombination_after->SetName("AntiLambdaRecombination_after");
        tlAntiLambdaRecombination_after->SetOwner();

        tlXiRecombination_after = new TList();
        tlXiRecombination_after->SetName("XiRecombination_after");
        tlXiRecombination_after->SetOwner();

        tlAntiXiRecombination_after = new TList();
        tlAntiXiRecombination_after->SetName("AntiXiRecombination_after");
        tlAntiXiRecombination_after->SetOwner();
        // particles
        hInvMassLambda_sanityCheck_after = new TH1F("InvariantMassLambdaSanityCheck_after", "Invariant Mass LAMBDA Sanity Check AFTER", 400, 1.00, 1.20); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassLambda_pi_bach_Xi_after = new TH1F("InvariantMassLambdaPiBachXi_after", "Invariant Mass Lambda - Pi Bachelor Xi AFTER", 400, 1.00, 1.20);
        hInvMassLambda_pi_daugh_Xi_after = new TH1F("InvMassLambda_Pi_daugh_Xi_after", "InvMassLambda_Pi_daugh_Xi_after", 800, 1.00, 1.40);
        hInvMassLambda_prot_Xi_after = new TH1F("InvMassLambda_Prot_Xi_after", "InvMassLambda_Prot_Xi_after", 800, 1.00, 1.40);
        hInvMassLambda_full_lambda_from_Xi_after = new TH1F("InvMassLambda_Full_Lambda_Xi_after", "InvMassLambda_Full_Lambda_from_Xi_after", 800, 1.00, 1.40);
        hInvMassXi_sanityCheck_after = new TH1F("InvariantMassXiSanityCheck_after", "Invariant_after Mass XI Sanity Check", 800, 1.200, 1.600); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassXi_Lamda_pi_daugh_after = new TH1F("InvMassXi_Lamda_pi_daugh_after", "InvMassXi_Lamda_pi_daugh_after", 3600, 0.700, 2.500);
        hInvMassXi_Lamda_prot_daugh_after = new TH1F("InvMassXi_Lamda_prot_daugh_after", "InvMassXi_Lamda_prot_daugh_after", 500, 1.1898, 1.7186);
        hInvMassXi_Lamda_pi_bach_after = new TH1F("InvMassXi_Lamda_pi_bach_after", "InvMassXi_Lamda_pi_bach_after", 500, 1.1898, 1.7186);
        hInvMassXi_Lamda_full_after = new TH1F("InvMassXi_Lamda_full_after", "InvMassXi_Lamda_full_after", 500, 1.1898, 1.7186); // komplettes Lambda ersetzten (ohne shared Track!!)
        hInvMassXi_Lamda_pi_no_correctLambdaMass = new TH1F("InvMassXi_Lamda_pi_no_correctLambdaMass", "InvMassXi_Lamda_pi_no_correctLambdaMass", 500, 1.1898, 1.7186);
        hInvMassXi_Lamda_prot_no_correctLambdaMass = new TH1F("InvMassXi_Lamda_proton_no_correctLambdaMass", "InvMassXi_Lamda_proton_no_correctLambdaMass", 500, 1.1898, 1.7186);
        // anti particles
        hInvMassAntiLambda_sanityCheck_after = new TH1F("InvariantMassANTILambdaSanityCheck_after", "Invariant Mass ANTILAMBDA Sanity Check AFTER", 400, 1.00, 1.20); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassAntiLambda_pi_bach_Xi_after = new TH1F("InvariantMassANTILambdaPiBachXi_after", "Invariant Mass ANTILambda - Pi Bachelor ANTIXi AFTER", 400, 1.00, 1.20);
        hInvMassAntiLambda_pi_daugh_Xi_after = new TH1F("InvMassANTILambda_Pi_daugh_Xi_after", "InvMassANTILambda_Pi_daugh_ANTIXi_after", 800, 1.00, 1.40);
        hInvMassAntiLambda_prot_Xi_after = new TH1F("InvMassANTILambda_Prot_Xi_after", "InvMassANTILambda_Prot_ANTIXi_after", 800, 1.00, 1.40);
        hInvMassAntiLambda_full_lambda_from_Xi_after = new TH1F("InvMassANTILambda_Full_Lambda_Xi_after", "InvMassLambda_Full_Lambda_from_Xi_after", 4000, 0.5, 2.5);
        hInvMassAntiXi_sanityCheck_after = new TH1F("InvariantMassANTIXiSanityCheck_after", "Invariant_after Mass ANTIXI Sanity Check", 500, 1.1898, 1.7186); // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
        hInvMassAntiXi_AntiLamda_antipi_daugh_after = new TH1F("InvMassANTIXi_ANTILamda_pi_after", "InvMassXi_ANTILamda_pi_after", 500, 1.1898, 1.7186);
        hInvMassAntiXi_AntiLamda_antiprot_daugh_after = new TH1F("InvMassANTIXi_ANTILamda_prot_after", "InvMassXi_ANTILamda_prot_after", 500, 1.1898, 1.7186);
        hInvMassAntiXi_AntiLamda_antipi_bach_after = new TH1F("InvMassANTIXi_ANTILamda_pi_bach_after", "InvMassANTIXi_ANTILamda_pi_bach_after", 500, 1.1898, 1.7186);
        hInvMassAntiXi_AntiLamda_full_after = new TH1F("InvMassXi_AntiLamda_full_after", "InvMassXi_AntiLamda_full_after", 500, 1.1898, 1.7186); // komplettes Lambda ersetzten (ohne shared Track!!)
        hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass = new TH1F("InvMassANTIXi_ANTILamda_antipi_no_correctLambdaMass", "InvMassANTIXi_ANTILamda_antipi_no_correctLambdaMass", 500, 1.1898, 1.7186);
        hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass = new TH1F("InvMassANTIXi_ANTILamda_antiproton_no_correctLambdaMass", "InvMassANTIXi_ANTILamda_antiroton_no_correctLambdaMass", 500, 1.1898, 1.7186);

        // Event counter for what happened how often
        fEvtCounterAfter = new TH1F("EventCounterAfter", "Event Counter After", 7, 0, 7);
        fEvtCounterAfter->GetXaxis()->SetBinLabel(1, "Prot_Lambda + pi_Xi1");    // reconstruct Lambda
        fEvtCounterAfter->GetXaxis()->SetBinLabel(2, "Prot_Lambda + pi_Xi2");    //
        fEvtCounterAfter->GetXaxis()->SetBinLabel(3, "Prot_Xi + pi_Lambda");     //
        fEvtCounterAfter->GetXaxis()->SetBinLabel(4, "Lambda + pi_Xi1");         // reconstruct Xi
        fEvtCounterAfter->GetXaxis()->SetBinLabel(5, "Lambda + pi_Xi2");         //
        fEvtCounterAfter->GetXaxis()->SetBinLabel(6, "Lambda + pi_Lambda");      //
        fEvtCounterAfter->GetXaxis()->SetBinLabel(7, "prot_Lambda + pi_Lambda"); //s reconstruct Lambda from other Lambda

        // connect to Output Lists
        tlLambdaRecombination_after->Add(hInvMassLambda_sanityCheck_after);
        tlLambdaRecombination_after->Add(hInvMassLambda_pi_bach_Xi_after);
        tlLambdaRecombination_after->Add(hInvMassLambda_pi_daugh_Xi_after);
        tlLambdaRecombination_after->Add(hInvMassLambda_prot_Xi_after);
        tlLambdaRecombination_after->Add(hInvMassLambda_full_lambda_from_Xi_after);

        tlXiRecombination_after->Add(hInvMassXi_sanityCheck_after);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_pi_daugh_after);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_prot_daugh_after);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_pi_bach_after);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_full_after);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_pi_no_correctLambdaMass);
        tlXiRecombination_after->Add(hInvMassXi_Lamda_prot_no_correctLambdaMass);

        tlAntiLambdaRecombination_after->Add(hInvMassAntiLambda_sanityCheck_after);
        tlAntiLambdaRecombination_after->Add(hInvMassAntiLambda_pi_bach_Xi_after);
        tlAntiLambdaRecombination_after->Add(hInvMassAntiLambda_pi_daugh_Xi_after);
        tlAntiLambdaRecombination_after->Add(hInvMassAntiLambda_prot_Xi_after);
        tlAntiLambdaRecombination_after->Add(hInvMassAntiLambda_full_lambda_from_Xi_after);

        tlAntiXiRecombination_after->Add(hInvMassAntiXi_sanityCheck_after);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_daugh_after);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_antiprot_daugh_after);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_bach_after);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_full_after);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass);
        tlAntiXiRecombination_after->Add(hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass);

        tlRecombination_after->Add(fEvtCounterAfter);

        tlRecombination_after->Add(tlLambdaRecombination_after);
        tlRecombination_after->Add(tlAntiLambdaRecombination_after);
        tlRecombination_after->Add(tlXiRecombination_after);
        tlRecombination_after->Add(tlAntiXiRecombination_after);

    }
    //////////////////////
    // Inv Mass PC   /////
    //////////////////////
    tlInvMassPairClean = new TList();
    tlInvMassPairClean->SetName("InvariantMassPairCleaner");
    tlInvMassPairClean->SetOwner();

    tlCleanDecay = new TList();
    tlCleanDecay->SetName("CleanDecay");
    tlCleanDecay->SetOwner();

    tlCleanDecayAndDecay = new TList();
    tlCleanDecayAndDecay->SetName("CleanDecayAndDecay");
    tlCleanDecayAndDecay->SetOwner();

        // Decay Diff To PDG Mass
    hLambdaCleanedPartMassDiffToPDG_Decay = new TH1F("LambdaCleanedParticleDifferenceToPDGMass", "Lambda Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hAntiLambdaCleanedPartMassDiffToPDG_Decay = new TH1F("AntiLambdaCleanedParticleDifferenceToPDGMass", "Anti Lambda Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hXiCleanedPartMassDiffToPDG_Decay = new TH1F("XiCleanedParticleDifferenceToPDGMass", "Xi Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hAntiXiCleanedPartMassDiffToPDG_Decay = new TH1F("AntiXiCleanedParticleDifferenceToPDGMass", "Anti Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);

        // DecayAndDecay Diff To PDG Mass
    hLambdaCleanedPartMassDiffToPDG_DecayDecay = new TH1F("LambdaCleanedParticleDifferenceToPDGMass", "Lambda Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay = new TH1F("AntiLambdaCleanedParticleDifferenceToPDGMass", "Anti Lambda Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hXiCleanedPartMassDiffToPDG_DecayDecay = new TH1F("XiCleanedParticleDifferenceToPDGMass", "Xi Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);
    hAntiXiCleanedPartMassDiffToPDG_DecayDecay = new TH1F("AntiXiCleanedParticleDifferenceToPDGMass", "Anti Cleaned Particle Difference To PDG Mass", 300, 0.0, 5.0);

        // Decay Mass
    hLambdaCleanedPartMass_Decay = new TH1F("LambdaCleanedParticleDifferenceToPDGMass", "Lambda Cleaned Particle Mass", 800, 1.00, 1.40);
    hAntiLambdaCleanedPartMass_Decay = new TH1F("AntiLambdaCleanedParticleDifferenceToPDGMass", "Anti Lambda Cleaned Mass", 800, 1.00, 1.40);
    hXiCleanedPartMass_Decay = new TH1F("XiCleanedParticleDifferenceToPDGMass", "Xi Cleaned Particle Mass", 500, 1.1898, 1.7186);
    hAntiXiCleanedPartMass_Decay = new TH1F("AntiXiCleanedParticleDifferenceToPDGMass", "Anti Cleaned Particle Mass", 500, 1.1898, 1.7186);

        // DecayAndDecay Mass                             
    hLambdaCleanedPartMass_DecayDecay = new TH1F("LambdaCleanedParticleMass", "Lambda Cleaned Particle Mass", 800, 1.00, 1.40);
    hAntiLambdaCleanedPartMass_DecayDecay = new TH1F("AntiLambdaCleanedParticleMass", "Anti Lambda Cleaned Particle Mass", 800, 1.00, 1.40);
    hXiCleanedPartMass_DecayDecay = new TH1F("XiCleanedParticleMass", "Xi Cleaned Particle Mass", 500, 1.1898, 1.7186);
    hAntiXiCleanedPartMass_DecayDecay = new TH1F("AntiXiCleanedParticleMass", "Anti Cleaned Particle Mass", 500, 1.1898, 1.7186);

        //
        // Connect Histogramms to Lists
        //
    tlInvMassPairClean->Add(tlCleanDecay);
    tlInvMassPairClean->Add(tlCleanDecayAndDecay);
    
    tlCleanDecay->Add(hLambdaCleanedPartMassDiffToPDG_Decay);
    tlCleanDecay->Add(hAntiLambdaCleanedPartMassDiffToPDG_Decay);
    tlCleanDecay->Add(hXiCleanedPartMassDiffToPDG_Decay);
    tlCleanDecay->Add(hAntiXiCleanedPartMassDiffToPDG_Decay);
    
    tlCleanDecayAndDecay->Add(hLambdaCleanedPartMassDiffToPDG_DecayDecay);
    tlCleanDecayAndDecay->Add(hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay);
    tlCleanDecayAndDecay->Add(hXiCleanedPartMassDiffToPDG_DecayDecay);
    tlCleanDecayAndDecay->Add(hAntiXiCleanedPartMassDiffToPDG_DecayDecay);

    tlCleanDecay->Add(hLambdaCleanedPartMass_Decay);
    tlCleanDecay->Add(hAntiLambdaCleanedPartMass_Decay);
    tlCleanDecay->Add(hXiCleanedPartMass_Decay);
    tlCleanDecay->Add(hAntiXiCleanedPartMass_Decay);
    
    tlCleanDecayAndDecay->Add(hLambdaCleanedPartMass_DecayDecay);
    tlCleanDecayAndDecay->Add(hAntiLambdaCleanedPartMass_DecayDecay);
    tlCleanDecayAndDecay->Add(hXiCleanedPartMass_DecayDecay);
    tlCleanDecayAndDecay->Add(hAntiXiCleanedPartMass_DecayDecay);

        // connect to output List tlRecombination_after
    tlRecombination_after->Add(tlInvMassPairClean);

    // weird stuff
    kStarXiLambda_unchanged = new TH1F("kStarXiLambda_unchanged", "kStarXiLambda_unchanged", 250, 0.0, 1.0);
    kStarXiLambda_changed = new TH1F("kStarXiLambda_changed", "kStarXiLambda_changed", 250, 0.0, 1.0);
    tlRecombination_after->Add(kStarXiLambda_unchanged);
    tlRecombination_after->Add(kStarXiLambda_changed);
    kStarAntiXiAntiLambda_unchanged = new TH1F("kStarAntiXiAntiLambda_unchanged", "kStarAntiXiAntiLambda_unchanged", 250, 0.0, 1.0);
    kStarAntiXiAntiLambda_changed = new TH1F("kStarAntiXiAntiLambda_changed", "kStarAntiXiAntiLambda_changed", 250, 0.0, 1.0);
    tlRecombination_after->Add(kStarAntiXiAntiLambda_unchanged);
    tlRecombination_after->Add(kStarAntiXiAntiLambda_changed);
    ///////////////////////////////////////
    // Connect Cuts to OutputContainers ///
    ///////////////////////////////////////
    if(!fEventCuts->GetMinimalBooking())
    {
        tlEventCuts             = fEventCuts->GetHistList();
    } else
    {
        tlEventCuts = new TList();
        tlEventCuts->SetName("EventCuts");
        tlEventCuts->SetOwner();
    }
    
    tlLambdaList            = fLambdaV0Cuts->GetQAHists();
    tlAntiLambdaList        = fAntiLambdaV0Cuts->GetQAHists();
    tlCascadeCutsXi         = fCascadeCutsXi->GetQAHists();
    tlAntiCascadeCutsXi     = fCascadeCutsAntiXi->GetQAHists();

    // initialize and connect RESULTS
    if (fConfig->GetUseEventMixing())
    {
        tlResults = fPartColl->GetHistList();
        if (!fConfig->GetMinimalBookingME())
        {
            tlResultsQA->Add(fPartColl->GetQAList());
            tlResultsQA->Add(fPairCleaner->GetHistList());
        }
    }
    else
    {
        tlResults = new TList();
        tlResults->SetOwner();
        tlResults->SetName("Results");
    }
    
    if(!fEventCuts2->GetMinimalBooking())
    {
        tlEventCuts2             = fEventCuts2->GetHistList();
    } else
    {
        tlEventCuts2 = new TList();
        tlEventCuts2->SetName("EventCuts");
        tlEventCuts2->SetOwner();
    }
    tlLambdaList2            = fLambdaV0Cuts2->GetQAHists();
    tlAntiLambdaList2        = fAntiLambdaV0Cuts2->GetQAHists();
    tlCascadeCutsXi2         = fCascadeCutsXi2->GetQAHists();
    tlAntiCascadeCutsXi2     = fCascadeCutsAntiXi2->GetQAHists();
    tlResults2               = fPartColl2->GetHistList();
    tlResultsQA2->Add(         fPartColl2->GetQAList());
    tlResultsQA2->Add(         fPairCleaner2->GetHistList());
    tlResultsQA2->Add(         fEvent->GetEvtCutList());

    PostData(1, tlEventCuts);           // cuts keeping Lambda
    PostData(2, tlLambdaList);
    PostData(3, tlAntiLambdaList);
    PostData(4, tlCascadeCutsXi);
    PostData(5, tlAntiCascadeCutsXi);
    PostData(6, tlResults);
    PostData(7, tlResultsQA);
    PostData(8, tlEventCuts2);          //  cuts keeping Xi
    PostData(9, tlLambdaList2);
    PostData(10, tlAntiLambdaList2);
    PostData(11, tlCascadeCutsXi2);
    PostData(12, tlAntiCascadeCutsXi2);
    PostData(13, tlResults2);
    PostData(14, tlResultsQA2);

    PostData(15, tlRecombination_before);         // reconstruction from daugthers histograms
    PostData(16, tlRecombination_after);

    ////////
    // #1 //
    ////////
    if (fLambdaV0Cuts->GetIsMonteCarlo())
    {
        if (!fLambdaV0Cuts->GetMinimalBooking())
        {
            tlLambdaMC = fLambdaV0Cuts->GetMCQAHists();
        }
        else{
            tlLambdaMC = new TList();
            tlLambdaMC->SetName("LambdaMC");
            tlLambdaMC->SetOwner();
        }
        PostData(17, tlLambdaMC);
    }
    if (fAntiLambdaV0Cuts->GetIsMonteCarlo())
    {
        if (!fAntiLambdaV0Cuts->GetMinimalBooking())
        {
            tlAntiLambdaMC = fAntiLambdaV0Cuts->GetMCQAHists();
        }
        else{
            tlAntiLambdaMC = new TList();
            tlAntiLambdaMC->SetName("LambdaMC");
            tlAntiLambdaMC->SetOwner();
        }
        PostData(18, tlAntiLambdaMC);
    }
    if (fCascadeCutsXi->GetIsMonteCarlo())
    {
        if (!fCascadeCutsXi->GetMinimalBooking())
        {
            tlXiMC = fCascadeCutsXi->GetMCQAHists();
        }
        else
        {
            tlXiMC = new TList();
            tlXiMC->SetName("MCXiCuts");
            tlXiMC->SetOwner();
        }
        PostData(19, tlXiMC);
    }
    if (fCascadeCutsAntiXi->GetIsMonteCarlo())
    {
        if (!fCascadeCutsAntiXi->GetMinimalBooking())
        {
            tlAntiXiMC = fCascadeCutsAntiXi->GetMCQAHists();
        }
        else
        {
            tlAntiXiMC = new TList();
            tlAntiXiMC->SetName("MCAntiv0Cuts");
            tlAntiXiMC->SetOwner();
        }
        PostData(20, tlAntiCascadeCutsXi);
    }
    ////////
    // #2 //
    ////////
    // if (fLambdaV0Cuts2->GetIsMonteCarlo())
    // {
    //     if (!fLambdaV0Cuts2->GetMinimalBooking())
    //     {
    //         tlLambdaMC2 = fLambdaV0Cuts2->GetMCQAHists();
    //     }
    //     else{
    //         tlLambdaMC2 = new TList();
    //         tlLambdaMC2->SetName("LambdaMC");
    //         tlLambdaMC2->SetOwner();
    //     }
    //     PostData(21, tlLambdaMC2);
    // }
    // if (fAntiLambdaV0Cuts2->GetIsMonteCarlo())
    // {
    //     if (!fAntiLambdaV0Cuts2->GetMinimalBooking())
    //     {
    //         tlAntiLambdaMC2 = fAntiLambdaV0Cuts2->GetMCQAHists();
    //     }
    //     else{
    //         tlAntiLambdaMC2 = new TList();
    //         tlAntiLambdaMC2->SetName("LambdaMC");
    //         tlAntiLambdaMC2->SetOwner();
    //     }
    //     PostData(22, tlAntiLambdaMC2);
    // }
    // if (fCascadeCutsXi2->GetIsMonteCarlo())
    // {
    //     if (!fCascadeCutsXi2->GetMinimalBooking())
    //     {
    //         tlXiMC2 = fCascadeCutsXi2->GetMCQAHists();
    //     }
    //     else
    //     {
    //         tlXiMC2 = new TList();
    //         tlXiMC2->SetName("MCXiCuts");
    //         tlXiMC2->SetOwner();
    //     }
    //     PostData(23, tlXiMC2);
    // }
    // if (fCascadeCutsAntiXi2->GetIsMonteCarlo())
    // {
    //     if (!fCascadeCutsAntiXi2->GetMinimalBooking())
    //     {
    //         tlAntiXiMC2 = fCascadeCutsAntiXi2->GetMCQAHists();
    //     }
    //     else
    //     {
    //         tlAntiXiMC2 = new TList();
    //         tlAntiXiMC2->SetName("MCAntiv0Cuts");
    //         tlAntiXiMC2->SetOwner();
    //     }
    //     PostData(24, tlAntiCascadeCutsXi2);
    // }
}         

// static int iLambda_counter_before = 0;
// static int iAntiLambda_counter_before = 0;
// static int iXi_counter_before = 0;
// static int iAntiXi_counter_before = 0;
// static int iLambda_counter_after = 0;
// static int iAntiLambda_counter_after = 0;
// static int iXi_counter_after = 0;
// static int iAntiXi_counter_after = 0;

void AliAnalysisTaskPOmegaPenne::UserExec(Option_t *)
{
    // VEvent = dynamic_cast<AliVEvent *>(fInputEvent);
    VEvent = fInputEvent;
    
    if (!fInputEvent)
    {
        AliWarning("No Input VEvent");
        return;
    }

    fEvent->SetEvent(fInputEvent);
    if (fEventCuts->isSelected(fEvent))
    {
        ResetGlobalTrackReference();
        for (int iTrack = 0; iTrack < fInputEvent->GetNumberOfTracks(); ++iTrack)
        {
            VTrack = dynamic_cast<AliVTrack *>(fInputEvent->GetTrack(iTrack));
            if (!VTrack)
            {
                AliFatal("No Standard AOD");
                return;
            }
            StoreGlobalTrackReference(VTrack);
        }
        

        std::vector<AliFemtoDreamBasePart> vLambda;         // keep Xi after OPairCleaner
        std::vector<AliFemtoDreamBasePart> vAntiLambda;
        std::vector<AliFemtoDreamBasePart> vXi;
        std::vector<AliFemtoDreamBasePart> vAntiXi;
        std::vector<AliFemtoDreamBasePart> vLambda2;        // keep Lambda after OPairCleaner
        std::vector<AliFemtoDreamBasePart> vAntiLambda2;
        std::vector<AliFemtoDreamBasePart> vXi2;
        std::vector<AliFemtoDreamBasePart> vAntiXi2;

    
        // irgendwie benötigt um GetV0s() und GetCascade() zu holen
        AliAODEvent *aodEvent = dynamic_cast<AliAODEvent *>(fInputEvent); // caste input event auf ein AODEvent

        //###########################################
        // Particle Selections
        //###########################################
        // ## Lambda Selection ## keep Lambdas
        fv0->SetGlobalTrackInfo(fGTI, fTrackBufferSize);
        fv0_2->SetGlobalTrackInfo(fGTI, fTrackBufferSize);

        for (int iv0 = 0; iv0 < dynamic_cast<TClonesArray *>(aodEvent->GetV0s())->GetEntriesFast(); ++iv0)
        {
            AliAODv0 *v0 = aodEvent->GetV0(iv0);
            
            fv0->Setv0(fInputEvent, v0, fEvent->GetMultiplicity());
            // ## Lambda Selection 1 ## 
            if (fLambdaV0Cuts->isSelected(fv0))
            {
                vLambda.push_back(*fv0);
                // vLambda[vLambda.size() - 1].SetCPA(1.0);
            }
            if (fAntiLambdaV0Cuts->isSelected(fv0))
            {
                vAntiLambda.push_back(*fv0);
                // vAntiLambda[vAntiLambda.size() - 1].SetCPA(1.0);
            }
            
            fv0_2->Setv0(fInputEvent, v0, fEvent->GetMultiplicity());

            // ## Lambda Selection 2 ## 
            if (fLambdaV0Cuts2->isSelected(fv0_2))
            {
                vLambda2.push_back(*fv0_2);
                // vLambda2[vLambda2.size() - 1].SetCPA(0.5);
            }
            if (fAntiLambdaV0Cuts2->isSelected(fv0_2))
            {
                vAntiLambda2.push_back(*fv0_2);
                // vAntiLambda2[vAntiLambda2.size() - 1].SetCPA(0.5);
            }

        }
        // ## Xi selection
        for (int iCasc = 0; iCasc < dynamic_cast<TClonesArray *>(aodEvent->GetCascades())->GetEntriesFast(); ++iCasc)
        {
            AliAODcascade *casc = aodEvent->GetCascade(iCasc);
            
            fCascade->SetCascade(fInputEvent, casc);
            // ## Xi selection 2 ### 
            if (fCascadeCutsXi->isSelected(fCascade))
            {
                vXi.push_back(*fCascade);
                // vXi[vXi.size() - 1].SetCPA(0.5);
            }
            if (fCascadeCutsAntiXi->isSelected(fCascade))
            {
                vAntiXi.push_back(*fCascade);
                // vAntiXi[vAntiXi.size() - 1].SetCPA(0.5);
            }
            fCascade2->SetCascade(fInputEvent, casc);

            // ## Xi selection 1 ### 
            if (fCascadeCutsXi2->isSelected(fCascade2))
            {
                vXi.push_back(*fCascade2);
                // vXi[vXi.size() - 1].SetCPA(1.0);
            }
            if (fCascadeCutsAntiXi2->isSelected(fCascade2))
            {
                vAntiXi.push_back(*fCascade2);
                // vAntiXi[vAntiXi.size() - 1].SetCPA(1.0);
            }
        }
        // for(auto it : vLambda)
        // {
        //     // iLambda_counter_before++;
        //     TVector3 momP = it.GetMomentum(1);
        //     TVector3 momN = it.GetMomentum(2);
        //     hInvMassLambda_sanityCheck_before->Fill(CalculateInvMassLambda(&it, false));
        // }
        // for(auto it : vAntiLambda)
        // {
        //     // iAntiLambda_counter_before++;
        //     TVector3 momN = it.GetMomentum(1);
        //     TVector3 momP = it.GetMomentum(2);
        //     // hInvMassAntiLambda_sanityCheck_before->Fill(CalculateInvMassLambda(momN, 2212, momP, 211));
        //     hInvMassAntiLambda_sanityCheck_before->Fill(CalculateInvMassLambda(&it, true));
        // }
        // for(auto it : vXi)
        // {
        //     // iXi_counter_before++;
        //     TVector3 momB = it.GetMomentum(3);
        //     TVector3 momP = it.GetMomentum(1);
        //     TVector3 momN = it.GetMomentum(2);
        //     // hInvMassXi_sanityCheck_before->Fill( CalculateInvMassXi(momB, 211, momP, 2212, momN, 211) );
        //     hInvMassXi_sanityCheck_before->Fill( CalculateInvMassXi(&it, false) );
        // }
        // for(auto it : vAntiXi)
        // {
        //     // iAntiXi_counter_before++;
        //     TVector3 momB = it.GetMomentum(3);
        //     TVector3 momP = it.GetMomentum(1);
        //     TVector3 momN = it.GetMomentum(2);
        //     hInvMassAntiXi_sanityCheck_before->Fill( CalculateInvMassXi(&it, true)  );
        // }

        
        //###########################################
        // Lambda - Lambda recombinations   -   BEFORE PAIRCLEANING
        //###########################################
        std::vector<AliFemtoDreamBasePart> vLambda_recomb;
        std::vector<AliFemtoDreamBasePart> tmpLambda_recomb(0); // recombination Vector for the loop
        std::vector<AliFemtoDreamBasePart> tmpXi_recomb(0);     // temporary recombination vector to calculate new invMasses

        if(fmixBeforePC)    // dont mix when steering param says NO
        {
        // ein lambda mit allen höheren kombinieren (siehe zweite schleife)
        for (size_t iterLamb = 0; iterLamb + 1 < vLambda.size(); iterLamb++)       // schleife läuft nur bis zum vorletzten lambda
        {
            if(vLambda.size() == 1) break;        // abbrechen wenn Lambda nur ein Teilchen enthält oder 

            // recombiniere lambda[iterLamb] mit den darauf folgenden Lambdas 
            // - dadurch werden nicht doppelt Lambdas aber im moment noch doppelt Tracks wenn sie sich zwei Lambdas teilen  
            // tausche nur den Impuls der für die invariante Masse benötigt wird
            // 
            // GetMomentum(0) - Lambda
            // GetMomentum(1) - Pion
            // GetMomentum(2) - Proton

            for (size_t iterUpwards = iterLamb + 1; iterUpwards < vLambda.size(); iterUpwards++) 
            {
                tmpLambda_recomb.clear();
                // check for shared tracks
                if(vLambda[iterLamb].GetIDTracks().size() < 2 || vLambda[iterUpwards].GetIDTracks().size() < 2 ) 
                {
                    continue;    // failsafe if the Lambda has no 2 tracks
                }
                
                if ( vLambda[iterLamb].GetIDTracks()[0] == vLambda[iterUpwards].GetIDTracks()[0])       // ## shared Pion
                {
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb[ 0 ].SetMomentum(2, vLambda[iterUpwards].GetMomentum(2));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassLambda_shared_pion_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], false));
                        hInvMassLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], false));
                    }
                }
                else if(vLambda[iterLamb].GetIDTracks()[1] == vLambda[iterUpwards].GetIDTracks()[1])     // ## shared Proton
                {
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb[ 0 ].SetMomentum(1, vLambda[iterUpwards].GetMomentum(1));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassLambda_shared_proton_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], false));
                        hInvMassLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], false));
                    }
                }
                else 
                {
                    // save recombination lambda twice for each for manipulation of each track
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);                    
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    // take next lambdas (iterUpwards) and manipulate the two lambdas before
                    tmpLambda_recomb[0].SetMomentum(1, vLambda[iterUpwards].GetMomentum(1));
                    tmpLambda_recomb[1].SetMomentum(2, vLambda[iterUpwards].GetMomentum(2));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    vLambda_recomb.push_back(tmpLambda_recomb[1]);
                    fEvtCounterBefore->Fill(6);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], false));
                    }
                }
            }
        }

        vLambda_recomb.clear();
        //******************************************
        // END - Lambda - Lambda recombinations
        //******************************************

        //###########################################
        // Lambda - Xi recombinations   -   BEFORE PAIRCLEANING
        //##########################################

        for (size_t iterLamb = 0; iterLamb < vLambda.size(); iterLamb++)   // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
        {
            if( !vLambda.size() || !vXi.size() ) break;        // abbrechen wenn lambda oder Xi leer ist/sind

            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            if(vLambda[iterLamb].GetIDTracks().size() < 2) 
            {
                continue;    // failsafe if the Lambda has no 2 tracks
            }

            // recombiniere vLambda[iterLamb] mit jeder Tochter der Xi's
            // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
            // ## XI
            // GetMomentum(0) - Xi
            // GetMomentum(1) - Pi-Daughter
            // GetMomentum(2) - Proton-Daughter
            // GetMomentum(3) - Pi-Bachelor
            // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            // [2] - Bachelor
            for (size_t iterXi = 0; iterXi < vXi.size(); iterXi++) 
            {
                if(vXi[iterXi].GetMomenta().size() < 4) 
                {
                    continue;   // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                }
                // reset temporary recombination vectors
                tmpLambda_recomb.clear();
                tmpXi_recomb.clear();
                
                // safe recombination lambda three times for each following lambda 
                // - for all combinations - Xi_1pi-Lambda_prot ; Xi_2pi-Lambda_prot ; Xi_prot-Lambda_pi
                tmpLambda_recomb.push_back(vLambda[iterLamb]);
                tmpLambda_recomb.push_back(vLambda[iterLamb]);
                tmpLambda_recomb.push_back(vLambda[iterLamb]);
                
                if(tmpLambda_recomb.size() >= 3 && vXi[iterXi].GetMomenta().size() >=3)
                {
                    // take Xi's constituents and manipulate the three lambdas before
                    tmpLambda_recomb[0].SetMomentum(1, vXi[iterXi].GetMomentum(0)); // Bachelor Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[1].SetMomentum(1, vXi[iterXi].GetMomentum(2)); // Daughter Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[2].SetMomentum(2, vXi[iterXi].GetMomentum(3)); // Daughter Xi-Proton mit Lambda-Pion
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    vLambda_recomb.push_back(tmpLambda_recomb[1]);
                    vLambda_recomb.push_back(tmpLambda_recomb[2]);
                }
                // ## Xi pairing
                if (vXi[iterXi].GetIDTracks()[2] == vLambda[iterLamb].GetIDTracks()[0])     // ## ## Bachelor shared ## ##
                {
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(1, vLambda[iterLamb].GetMomentum(1));   // set Pi-Daughter
                    tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2));   // set Proton-Daughter
                    tmpXi_recomb[2].SetMomentum(1, vLambda[iterLamb].GetMomentum(1));   // set full Lambda
                    tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2));   // set full Lambda
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        float invMassToStore = CalculateInvMassXi(&tmpXi_recomb[j], false); 
                        hInvMassXi_shared_bach_before->Fill(invMassToStore);
                        hInvMassXi_total_before->Fill(invMassToStore);
                    }
                }
                else if (vXi[iterXi].GetIDTracks()[0] == vLambda[iterLamb].GetIDTracks()[0])    // ## ## pion daughter shared ## ##
                {
                    if (vXi[iterXi].GetIDTracks()[1] == vLambda[iterLamb].GetIDTracks()[1]) // ## ## and daughter proton shared -> full lambda shared ## ##
                    {
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1));   // set only Bachelor

                    hInvMassXi_shared_Lambda_before->Fill(CalculateInvMassXi(&tmpXi_recomb[0], false));
                    }
                    else // ## ## only daughter pion shared ## ##
                    {
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        
                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            float invMassToStore = CalculateInvMassXi(&tmpXi_recomb[j], false);

                            hInvMassXi_shared_pi_daugh_before->Fill(invMassToStore);
                            hInvMassXi_total_before->Fill(invMassToStore);
                        }
                    }
                }
                else if (vXi[iterXi].GetIDTracks()[1] == vLambda[iterLamb].GetIDTracks()[1] && vXi[iterXi].GetIDTracks()[0] != vLambda[iterLamb].GetIDTracks()[0])     // ## ## only daughter proton shared ## ##
                {
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb.push_back(vXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                    tmpXi_recomb[1].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        hInvMassXi_shared_prot_daugh_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], false));
                        hInvMassXi_total_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], false));
                    }
                }
                else   // ## ## nothing shared ## ##
                {
                    // get the Xi and manipulate the Bachelor and Daughters
                    for (int j = 0; j < 4; j++)
                    {
                        tmpXi_recomb.push_back(vXi[iterXi]);
                    }

                    tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                    tmpXi_recomb[1].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                    tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                    tmpXi_recomb[3].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set full Lambda
                    tmpXi_recomb[3].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set full Lambda
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        hInvMassXi_nothing_shared->Fill(CalculateInvMassXi(&tmpXi_recomb[j], false));
                        hInvMassXi_total_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], false));
                    }
                }
            }
        }
        vLambda_recomb.clear();
        //*****************************************
        // ENDE - Lambda - Xi recombinations
        //*****************************************

        //###########################################
        // ANTI Lambda - ANTI Lambda recombinations   -   BEFORE PAIRCLEANING
        //###########################################
        tmpLambda_recomb.clear(); 
        
        // ein lambda mit allen höheren kombinieren (siehe zweite schleife)
        for (size_t iterLamb = 0; iterLamb + 1 < vAntiLambda.size(); iterLamb++)       // schleife läuft nur bis zum vorletzten lambda
        {
            if(vAntiLambda.size() == 1) break;        // abbrechen wenn Lambda nur ein Teilchen enthält oder 

            // recombiniere lambda[iterLamb] mit den darauf folgenden Lambdas 
            // - dadurch werden nicht doppelt Lambdas aber im moment noch doppelt Tracks wenn sie sich zwei Lambdas teilen  
            // tausche nur den Impuls der für die invariante Masse benötigt wird
            // 
            // GetMomentum(0) - Lambda
            // GetMomentum(1) - Pion
            // GetMomentum(2) - Proton

            for (size_t iterUpwards = iterLamb + 1; iterUpwards < vAntiLambda.size(); iterUpwards++) 
            {
                tmpLambda_recomb.clear();
                // check for shared tracks
                if(vAntiLambda[iterLamb].GetIDTracks().size() < 2 || vAntiLambda[iterUpwards].GetIDTracks().size() < 2 ) 
                {
                    continue;    // failsafe if the Lambda has no 2 tracks
                }
                
                if ( vAntiLambda[iterLamb].GetIDTracks()[0] == vAntiLambda[iterUpwards].GetIDTracks()[0])       // ## shared Pion
                {
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                    tmpLambda_recomb[ 0 ].SetMomentum(2, vAntiLambda[iterUpwards].GetMomentum(2));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassAntiLambda_shared_pion_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], true));
                        hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], true));
                    }
                }
                else if(vAntiLambda[iterLamb].GetIDTracks()[1] == vAntiLambda[iterUpwards].GetIDTracks()[1])     // ## shared Proton
                {
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                    tmpLambda_recomb[ 0 ].SetMomentum(1, vAntiLambda[iterUpwards].GetMomentum(1));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassAntiLambda_shared_proton_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], true));
                        hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], true));
                    }
                }
                else 
                {
                    // save recombination lambda twice for each for manipulation of each track
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);                    
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                    // take next lambdas (iterUpwards) and manipulate the two lambdas before
                    tmpLambda_recomb[0].SetMomentum(1, vAntiLambda[iterUpwards].GetMomentum(1));
                    tmpLambda_recomb[1].SetMomentum(2, vAntiLambda[iterUpwards].GetMomentum(2));
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    vLambda_recomb.push_back(tmpLambda_recomb[1]);
                    fEvtCounterBefore->Fill(6);
                    fEvtCounterBefore->Fill(6);
                    for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                    {
                        hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(&vLambda_recomb[iterLamb_recomb], true));
                    }
                }
            }
        }

        vLambda_recomb.clear();

        //*****************************************
        // ENDE - AntiLambda recombinations
        //*****************************************


        //###########################################
        // ANTI Lambda - ANTI Xi recombinations   -   BEFORE PAIRCLEANING
        //##########################################

        for (size_t iterLamb = 0; iterLamb < vAntiLambda.size(); iterLamb++)   // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
        {
            if( !vAntiLambda.size() || !vAntiXi.size() ) break;        // abbrechen wenn lambda oder Xi leer ist/sind

            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            if(vAntiLambda[iterLamb].GetIDTracks().size() < 2) 
            {
                continue;    // failsafe if the Lambda has no 2 tracks
            }

            // recombiniere vAntiLambda[iterLamb] mit jeder Tochter der Xi's
            // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
            // ## XI
            // GetMomentum(0) - Xi
            // GetMomentum(1) - Pi-Daughter
            // GetMomentum(2) - Proton-Daughter
            // GetMomentum(3) - Pi-Bachelor
            // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            // [2] - Bachelor
            for (size_t iterXi = 0; iterXi < vAntiXi.size(); iterXi++) 
            {
                if(vAntiXi[iterXi].GetMomenta().size() < 4) 
                {
                    continue;   // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                }
                // reset temporary recombination vectors
                tmpLambda_recomb.clear();
                tmpXi_recomb.clear();
                
                // safe recombination lambda three times for each following lambda 
                // - for all combinations - Xi_1pi-Lambda_prot ; Xi_2pi-Lambda_prot ; Xi_prot-Lambda_pi
                tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                
                if(tmpLambda_recomb.size() >= 3 && vAntiXi[iterXi].GetMomenta().size() >=3)
                {
                    // take Xi's constituents and manipulate the three lambdas before
                    tmpLambda_recomb[0].SetMomentum(1, vAntiXi[iterXi].GetMomentum(0)); // Bachelor Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[1].SetMomentum(1, vAntiXi[iterXi].GetMomentum(2)); // Daughter Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[2].SetMomentum(2, vAntiXi[iterXi].GetMomentum(3)); // Daughter Xi-Proton mit Lambda-Pion
                    vLambda_recomb.push_back(tmpLambda_recomb[0]);
                    vLambda_recomb.push_back(tmpLambda_recomb[1]);
                    vLambda_recomb.push_back(tmpLambda_recomb[2]);
                }
                // ## Xi pairing
                if (vAntiXi[iterXi].GetIDTracks()[2] == vAntiLambda[iterLamb].GetIDTracks()[0])     // ## ## Bachelor shared ## ##
                {
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1));   // set Pi-Daughter
                    tmpXi_recomb[1].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2));   // set Proton-Daughter
                    tmpXi_recomb[2].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1));   // set full Lambda
                    tmpXi_recomb[2].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2));   // set full Lambda
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        float invMassToStore = CalculateInvMassXi(&tmpXi_recomb[j], true); 
                        hInvMassXi_shared_bach_before->Fill(invMassToStore);
                        hInvMassXi_total_before->Fill(invMassToStore);
                    }
                }
                else if (vAntiXi[iterXi].GetIDTracks()[0] == vAntiLambda[iterLamb].GetIDTracks()[0])    // ## ## pion daughter shared ## ##
                {
                    if (vAntiXi[iterXi].GetIDTracks()[1] == vAntiLambda[iterLamb].GetIDTracks()[1]) // ## ## and daughter proton shared -> full lambda shared ## ##
                    {
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1));   // set only Bachelor

                    hInvMassXi_shared_Lambda_before->Fill(CalculateInvMassXi(&tmpXi_recomb[0], true));
                    }
                    else // ## ## only daughter pion shared ## ##
                    {
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        
                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            float invMassToStore = CalculateInvMassXi(&tmpXi_recomb[j], true);

                            hInvMassXi_shared_pi_daugh_before->Fill(invMassToStore);
                            hInvMassXi_total_before->Fill(invMassToStore);
                        }
                    }
                }
                else if (vAntiXi[iterXi].GetIDTracks()[1] == vAntiLambda[iterLamb].GetIDTracks()[1] && vAntiXi[iterXi].GetIDTracks()[0] != vAntiLambda[iterLamb].GetIDTracks()[0])     // ## ## only daughter proton shared ## ##
                {
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                    tmpXi_recomb[1].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        hInvMassXi_shared_prot_daugh_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], true));
                        hInvMassXi_total_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], true));
                    }
                }
                else   // ## ## nothing shared ## ##
                {
                    // get the Xi and manipulate the Bachelor and Daughters
                    for (int j = 0; j < 4; j++)
                    {
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                    }

                    tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                    tmpXi_recomb[1].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                    tmpXi_recomb[2].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                    tmpXi_recomb[3].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set full Lambda
                    tmpXi_recomb[3].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set full Lambda
                    
                    for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                    {
                        hInvMassXi_nothing_shared->Fill(CalculateInvMassXi(&tmpXi_recomb[j], true));
                        hInvMassXi_total_before->Fill(CalculateInvMassXi(&tmpXi_recomb[j], true));
                    }
                }
            }
        }
        vLambda_recomb.clear();
        
        //*****************************************
        // ENDE - AntiLambda - AntiXi recombinations
        //*****************************************
        }
        //###########################################
        //###########################################
        // Cleanup and Postdata
        //###########################################
        //###########################################
        // remove double-matched tracks

        fPairCleaner ->ResetArray();
        fPairCleaner2->ResetArray();

        // #1
        // fPairCleaner->CleanDecayAndDecay(&vXi, &vLambda, 0);
        // fPairCleaner->CleanDecayAndDecay(&vAntiXi, &vAntiLambda, 1);
        // fPairCleaner->CleanDecay(&vLambda, 2);
        // fPairCleaner->CleanDecay(&vAntiLambda, 3);

        // fPairCleaner->CleanDecay(&vXi, 0);
        // fPairCleaner->CleanDecay(&vAntiXi, 1);

        // CleanDecayAndDecay(&vLambda, &vXi, false);
        // CleanDecayAndDecay(&vAntiLambda, &vAntiXi, true);

        CleanDecay(&vLambda, "Lambda");
        CleanDecay(&vAntiLambda, "AntiLambda");
        CleanDecay(&vXi, "Xi");
        CleanDecay(&vAntiXi, "AntiXi");

        fPairCleaner->StoreParticle(vLambda);
        fPairCleaner->StoreParticle(vAntiLambda);
        fPairCleaner->StoreParticle(vXi);
        fPairCleaner->StoreParticle(vAntiXi);

        // #2
        fPairCleaner2->CleanDecayAndDecay(&vXi2, &vLambda2, 0);
        fPairCleaner2->CleanDecayAndDecay(&vAntiXi2, &vAntiLambda2, 1);
        fPairCleaner2->CleanDecay(&vLambda2, 2);
        fPairCleaner2->CleanDecay(&vAntiLambda2, 3);

        fPairCleaner2->StoreParticle(vLambda2);
        fPairCleaner2->StoreParticle(vAntiLambda2);
        fPairCleaner2->StoreParticle(vXi2);
        fPairCleaner2->StoreParticle(vAntiXi2);

        fPartColl->SetEvent(fPairCleaner->GetCleanParticles(), fEvent->GetZVertex(), fEvent->GetRefMult08(), fEvent->GetV0MCentrality()); 
        fPartColl2->SetEvent(fPairCleaner2->GetCleanParticles(), fEvent->GetZVertex(), fEvent->GetRefMult08(), fEvent->GetV0MCentrality()); 
        // soweit ich das richtig verstanden habe wird pairQA mit den teilchen gemacht die im pairCleaner
        // sind und pdgCodes in der richtigen Reihenfolge vorhanden sind.


        // std::cout << "dimensions of cleanParticles: " << fPairCleaner->GetCleanParticles().size() << "x" << fPairCleaner->GetCleanParticles()[0].size() << std::endl;        ### makes particleTypeXparticleNumber
        // if(fPairCleaner->GetCleanParticles()[0].size() || fPairCleaner->GetCleanParticles()[1].size() || fPairCleaner->GetCleanParticles()[2].size() || fPairCleaner->GetCleanParticles()[3].size())
        // {
        //     std::cout << "### New EVENT ###" << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[0].size()==0) std::cout << "Lambdas: " << fPairCleaner->GetCleanParticles()[0].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[1].size()==0)std::cout << "AntiLambdas: " << fPairCleaner->GetCleanParticles()[1].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[2].size()==0)std::cout << "Xi: " << fPairCleaner->GetCleanParticles()[2].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[3].size()==0)std::cout << "AntiXi: " << fPairCleaner->GetCleanParticles()[3].size() << std::endl;
        // }
        // if(vLambda.size() > 0 && vXi.size() > 0)
        // {
        //     std::cout << "after paircleaner vLambda und vXi größe: " << vLambda.size() << " und " << vXi.size() << std::endl;
        // }

        if(fmixAfterPC)
        {
        //###########################################
        // Lambda - Xi recombinations   -   AFTER PAIRCLEANING
        //#########################################
        for (size_t iterLamb = 0; iterLamb < vLambda.size(); iterLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
        {
            if (!vLambda.size() || !vXi.size())     // abbrechen wenn lambda oder Xi leer ist/sind
            {
                break; 
            }

            if (!vLambda[iterLamb].UseParticle())        // continue wenn der Paircleaner sie aussortiert hat
            {
                continue;
            }
            
            // recombiniere vLambda[iterLamb] mit jeder Tochter der Xi's
            // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
            // ## XI - PDG-3312
            // GetMomentum(0) - Xi 
            // GetMomentum(1) - Pi-Daughter
            // GetMomentum(2) - Proton-Daughter
            // GetMomentum(3) - Pi-Bachelor
            // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            // [2] - Bachelor
            for (size_t iterXi = 0; iterXi < vXi.size(); iterXi++)
            {
                if (!vXi[iterXi].UseParticle())        // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                if (vXi[iterXi].GetMomenta().size() < 4)
                {
                    continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                }
                // reset temporary recombination vectors
                tmpLambda_recomb.clear();
                tmpXi_recomb.clear();

                // ## Lambda pairing
                tmpLambda_recomb.push_back(vLambda[iterLamb]);
                tmpLambda_recomb.push_back(vLambda[iterLamb]);
                tmpLambda_recomb.push_back(vLambda[iterLamb]);

                if (tmpLambda_recomb.size() >= 3 && vXi[iterXi].GetMomenta().size() >= 3)
                {
                    // take Xi's constituents and manipulate the three lambdas before
                    tmpLambda_recomb[0].SetMomentum(1, vXi[iterXi].GetMomentum(0)); // [0] Bachelor Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[1].SetMomentum(1, vXi[iterXi].GetMomentum(2)); // [1] Daughter Xi-Pion mit Lambda-Proton
                    tmpLambda_recomb[2].SetMomentum(2, vXi[iterXi].GetMomentum(3)); // [2] Daughter Xi-Proton mit Lambda-Pion

                    hInvMassLambda_pi_bach_Xi_after ->Fill(CalculateInvMassLambda(&tmpLambda_recomb[0], false));
                    hInvMassLambda_pi_daugh_Xi_after->Fill(CalculateInvMassLambda(&tmpLambda_recomb[1], false));
                    hInvMassLambda_prot_Xi_after    ->Fill(CalculateInvMassLambda(&tmpLambda_recomb[2], false));
                }

                // ## Xi pairing ###################################### Xi STARTS HERE ################
                for (size_t mixCombinations = 0; mixCombinations < 5; mixCombinations++)
                {
                    tmpXi_recomb.push_back(vXi[iterXi]);
                }
                if(tmpXi_recomb.size() > 4)
                {
                    tmpXi_recomb[0].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // [0] set Pi-Daughter
                    tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [1] set Proton-Daughter
                    tmpXi_recomb[2].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // [2] set full Lambda
                    tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [2] set full Lambda
                    tmpXi_recomb[3].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [3] set Pi-Bachelor
                    tmpXi_recomb[4].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [4] set Pi-Bachelor and Proton-Daughter

                    if (TMath::Abs( CalculateInvMassLambda(tmpXi_recomb[0].GetMomentum(1), 211, tmpXi_recomb[0].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassXi_Lamda_pi_daugh_after             ->Fill(CalculateInvMassXi(&tmpXi_recomb[0], false));
                        vXi[iterXi].SetUse(false);
                        kStarXiLambda_unchanged                     ->Fill(RelativePairMomentum(&vXi[iterXi], 3312, &vLambda[iterLamb], 3122));        // relative momentum Xi - Lambda
                        kStarXiLambda_changed                       ->Fill(RelativePairMomentum(&tmpXi_recomb[0], 3312, &vLambda[iterLamb], 3122));        // relative momentum Xi - Lambda
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpXi_recomb[0].GetMomentum(1), 211, tmpXi_recomb[0].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) > 0.005 )
                    {
                        hInvMassXi_Lamda_pi_no_correctLambdaMass   ->Fill(CalculateInvMassXi(&tmpXi_recomb[0], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpXi_recomb[1].GetMomentum(1), 211, tmpXi_recomb[1].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassXi_Lamda_prot_daugh_after           ->Fill(CalculateInvMassXi(&tmpXi_recomb[1], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpXi_recomb[1].GetMomentum(1), 211, tmpXi_recomb[1].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) > 0.005 )
                    {
                        hInvMassXi_Lamda_prot_no_correctLambdaMass  ->Fill(CalculateInvMassXi(&tmpXi_recomb[1], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpXi_recomb[2].GetMomentum(1), 211, tmpXi_recomb[2].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassXi_Lamda_full_after                 ->Fill(CalculateInvMassXi(&tmpXi_recomb[2], false));
                    }

                    hInvMassXi_Lamda_pi_bach_after                  ->Fill(CalculateInvMassXi(&tmpXi_recomb[3], false));
                }
            }
        }

        //###########################################
        // Anti-Lambda - Anti-Xi recombinations   -   AFTER PAIRCLEANING
        //#########################################
        std::vector<AliFemtoDreamBasePart> tmpAntiLambda_recomb(0); // recombination Vector for the loop
        std::vector<AliFemtoDreamBasePart> tmpAntiXi_recomb(0);     // temporary recombination vector to calculate new invMasses
        
        for (size_t iterAntiLamb = 0; iterAntiLamb < vAntiLambda.size(); iterAntiLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
        {
            if (!vAntiLambda.size() || !vAntiXi.size())     // abbrechen wenn lambda oder Xi leer ist/sind
            {
                break; 
            }

            if (!vAntiLambda[iterAntiLamb].UseParticle())        // continue wenn der Paircleaner sie aussortiert hat
            {
                continue;
            }
            // recombiniere vAntiLambda[iterAntiLamb] mit jeder Tochter der Xi's
            // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
            // ## XI - PDG-3312
            // GetMomentum(0) - Xi
            // GetMomentum(1) - Pi-Daughter
            // GetMomentum(2) - Proton-Daughter
            // GetMomentum(3) - Pi-Bachelor
            // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
            // GetIDTracks()
            // [0] - negativeDaughter
            // [1] - positiveDaughter
            // [2] - Bachelor
            for (size_t iterAntiXi = 0; iterAntiXi < vAntiXi.size(); iterAntiXi++)
            {
                if (!vAntiXi[iterAntiXi].UseParticle())        // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                if (vAntiXi[iterAntiXi].GetMomenta().size() < 4)
                {
                    continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                }
                // reset temporary recombination vectors
                tmpAntiLambda_recomb.clear();
                tmpAntiXi_recomb.clear();

                // ## Anti-Lambda pairing
                for (size_t antiLambdaSize = 0; antiLambdaSize < 4; antiLambdaSize++)
                {
                    tmpAntiLambda_recomb.push_back(vAntiLambda[iterAntiLamb]);
                }

                if (tmpAntiLambda_recomb.size() >= 4 && vAntiXi[iterAntiXi].GetMomenta().size() >= 3)
                {
                    // take Xi's constituents and manipulate the three lambdas before
                    tmpAntiLambda_recomb[0].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(0)); // [0] Bachelor Xi-Pion mit Lambda-Proton
                    tmpAntiLambda_recomb[1].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(2)); // [1] Daughter Xi-Pion mit Lambda-Proton
                    tmpAntiLambda_recomb[2].SetMomentum(2, vAntiXi[iterAntiXi].GetMomentum(3)); // [2] Daughter Xi-Proton mit Lambda-Pion
                    tmpAntiLambda_recomb[3].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(2)); // [3] Full Lambda from Xi sharing
                    tmpAntiLambda_recomb[3].SetMomentum(2, vAntiXi[iterAntiXi].GetMomentum(3)); // [3] Full Lambda from Xi sharing

                hInvMassAntiLambda_pi_bach_Xi_after          ->Fill(CalculateInvMassLambda(&tmpAntiLambda_recomb[0], true));
                hInvMassAntiLambda_pi_daugh_Xi_after         ->Fill(CalculateInvMassLambda(&tmpAntiLambda_recomb[1], true));
                hInvMassAntiLambda_prot_Xi_after             ->Fill(CalculateInvMassLambda(&tmpAntiLambda_recomb[2], true));
                hInvMassAntiLambda_full_lambda_from_Xi_after ->Fill(CalculateInvMassLambda(&tmpAntiLambda_recomb[3], true));
                }

                // ## Anti-Xi pairing ###################################### Anti-Xi STARTS HERE ################
                for (size_t mixCombinations = 0; mixCombinations < 5; mixCombinations++)
                {
                    tmpAntiXi_recomb.push_back(vAntiXi[iterAntiXi]);
                }
                if(tmpAntiXi_recomb.size() > 4)
                {
                    tmpAntiXi_recomb[0].SetMomentum(1, vAntiLambda[iterAntiLamb].GetMomentum(1)); // [0] set Pi-Daughter
                    tmpAntiXi_recomb[1].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [1] set Proton-Daughter
                    tmpAntiXi_recomb[2].SetMomentum(1, vAntiLambda[iterAntiLamb].GetMomentum(1)); // [2] set full Lambda
                    tmpAntiXi_recomb[2].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [2] set full Lambda
                    tmpAntiXi_recomb[3].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [3] set Pi-Bachelor
                    tmpAntiXi_recomb[4].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [4] set Pi-Bachelor and Proton-Daughter
                    
                    if (TMath::Abs( CalculateInvMassLambda(tmpAntiXi_recomb[0].GetMomentum(1), 211, tmpAntiXi_recomb[0].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassAntiXi_AntiLamda_antipi_daugh_after             ->Fill(CalculateInvMassXi(&tmpAntiXi_recomb[0], false));
                        vAntiXi[iterAntiXi].SetUse(false);

                        kStarAntiXiAntiLambda_unchanged                     ->Fill(RelativePairMomentum(&vAntiXi[iterAntiXi], 3312, &vAntiLambda[iterAntiLamb], 3122));        // relative momentum AntiXi - AntiLambda
                        kStarAntiXiAntiLambda_changed                       ->Fill(RelativePairMomentum(&tmpAntiXi_recomb[0], 3312, &vAntiLambda[iterAntiLamb], 3122));        // relative momentum AntiXi - AntiLambda
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpAntiXi_recomb[0].GetMomentum(1), 211, tmpAntiXi_recomb[0].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) > 0.005 )
                    {
                        hInvMassAntiXi_AntiLamda_antipi_no_correctAntiLambdaMass   ->Fill(CalculateInvMassXi(&tmpAntiXi_recomb[0], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpAntiXi_recomb[1].GetMomentum(1), 211, tmpAntiXi_recomb[1].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassAntiXi_AntiLamda_antiprot_daugh_after           ->Fill(CalculateInvMassXi(&tmpAntiXi_recomb[1], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpAntiXi_recomb[1].GetMomentum(1), 211, tmpAntiXi_recomb[1].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) > 0.005 )
                    {
                        hInvMassAntiXi_AntiLamda_antiprot_no_correctAntiLambdaMass           ->Fill(CalculateInvMassXi(&tmpAntiXi_recomb[1], false));
                    }
                    if (TMath::Abs( CalculateInvMassLambda(tmpAntiXi_recomb[2].GetMomentum(1), 211, tmpAntiXi_recomb[2].GetMomentum(2), 2212) - TDatabasePDG::Instance()->GetParticle(3122)->Mass() ) < 0.005 )
                    {
                        hInvMassAntiXi_AntiLamda_full_after                 ->Fill(CalculateInvMassXi(&tmpAntiXi_recomb[2], false));
                    }

                    hInvMassAntiXi_AntiLamda_antipi_bach_after               ->Fill( CalculateInvMassXi(&tmpAntiXi_recomb[3], true) );
                }
            }
        }
        }
        // if (fPairCleaner->GetCleanParticles().size() == 4)
        // {
        //     for (auto it : fPairCleaner->GetCleanParticles()[0])
        //     {
        //         hInvMassLambda_sanityCheck_after->Fill(CalculateInvMassLambda(&it, false));
        //     }
        //     for (auto it : fPairCleaner->GetCleanParticles()[1])
        //     {
        //             hInvMassAntiLambda_sanityCheck_after->Fill(CalculateInvMassLambda(&it, true));
        //     }
        //     for (auto it : fPairCleaner->GetCleanParticles()[2])
        //     {
        //         hInvMassXi_sanityCheck_after->Fill(CalculateInvMassXi(&it, false));
        //     }
        //     for (auto it : fPairCleaner->GetCleanParticles()[3])
        //     {
        //         hInvMassAntiXi_sanityCheck_after->Fill(CalculateInvMassXi(&it, true));
        //     }
        // }
        PostData(1, tlEventCuts);
        PostData(2, tlLambdaList);
        PostData(3, tlAntiLambdaList);
        PostData(4, tlCascadeCutsXi);
        PostData(5, tlAntiCascadeCutsXi);
        PostData(6, tlResults);
        PostData(7, tlResultsQA);

        PostData(8, tlEventCuts2);
        PostData(9, tlLambdaList2);
        PostData(10, tlAntiLambdaList2);
        PostData(11, tlCascadeCutsXi2);
        PostData(12, tlAntiCascadeCutsXi2);
        PostData(13, tlResults2);
        PostData(14, tlResultsQA2);

        PostData(15, tlRecombination_before); // reconstruction from daugthers histograms
        PostData(16, tlRecombination_after);  // reconstruction from daugthers histograms

        if (fIsMC)
        {
            PostData(17, tlLambdaMC);

            PostData(18, tlAntiLambdaMC);
        }
    }
    // std::cout << "Lambda Before: " << iLambda_counter_before << std::endl;
    // std::cout << "AntiLambda Before: " << iLambda_counter_before << std::endl;
    // std::cout << "Xi Before: " << iLambda_counter_before << std::endl;
    // std::cout << "AntiXi Before: " << iLambda_counter_before << std::endl << std::endl;
    // std::cout << "Lambda After: " << iLambda_counter_before << std::endl;
    // std::cout << "AntiLambda After: " << iLambda_counter_before << std::endl;
    // std::cout << "Xi After: " << iLambda_counter_before << std::endl;
    // std::cout << "AntiXi After: " << iLambda_counter_before << std::endl;

    
    // std::cout << "fmixBeforePC:     " << fmixBeforePC << std::endl;
    // std::cout << "fmixAfterPC:          " << fmixAfterPC << std::endl;
    // std::cout << "ffullBlastQA:             " << ffullBlastQA << std::endl;
    // std::cout << "fisInvMassPairClean:          " << fmixAfterPC << std::endl;
    // std::cout << "fmultTrigger:                     " << ffullBlastQA << std::endl;
    // std::cout << std::endl;
}

void AliAnalysisTaskPOmegaPenne::ResetGlobalTrackReference()
{
    //This method was inherited form H. Beck analysis
    for (UShort_t i = 0; i < fTrackBufferSize; i++)
    {
        fGTI[i] = nullptr;
        // std::fill(fGTI.begin(),fGTI.end(), nullptr);
    }
}

//  Stores TrackID in Global Track Reference Array 'fGTI' if ID > 0
//
void AliAnalysisTaskPOmegaPenne::StoreGlobalTrackReference(AliVTrack *vTrack)
{
    //This method was inherited form H. Beck analysis
    AliNanoAODTrack *nanoTrack = dynamic_cast<AliNanoAODTrack*>(vTrack);
    const int trackID = vTrack->GetID();
    if (trackID < 0)
    {
        return;
    }
    if (trackID >= fTrackBufferSize)
    {
        printf("Warning: track ID too big for buffer: ID: %d, buffer %d\n", trackID, fTrackBufferSize);
        return;
    }

    if (fGTI[trackID])
    {
        if ((!nanoTrack->GetFilterMap()) && (!vTrack->GetTPCNcls()))
        {
            return;
        }
        if (dynamic_cast<AliNanoAODTrack *>(fGTI[trackID])->GetFilterMap() || fGTI[trackID]->GetTPCNcls())
        {
            printf("WARNING! global track info already there!");
            printf("    ###     TPCNcls track1 %u Track2 %u", (fGTI[trackID])->GetTPCNcls(), vTrack->GetTPCNcls());
            printf("   ###     FilterMap Track1 %u track2 %u\n", dynamic_cast<AliNanoAODTrack *>(fGTI[trackID])->GetFilterMap(), nanoTrack->GetFilterMap());
        }
    }
    fGTI[trackID] = vTrack;

}
float AliAnalysisTaskPOmegaPenne::CalculateInvMassLambda(TVector3 momNegDaughter, int PDGnegDaughter, TVector3 momPosDaughter, int PDGposDaughter)
{
    float invMass = 0;
    
    float massDP = TDatabasePDG::Instance()->GetParticle(PDGposDaughter)->Mass(); // Proton
    float massDN = TDatabasePDG::Instance()->GetParticle(PDGnegDaughter)->Mass();  // Pion
    float EDaugP = TMath::Sqrt(
        massDP * massDP + 
        momPosDaughter.X() * momPosDaughter.X() + 
        momPosDaughter.Y() * momPosDaughter.Y() + 
        momPosDaughter.Z() * momPosDaughter.Z()
    );
    float EDaugN = TMath::Sqrt(
        massDN * massDN + 
        momNegDaughter.X() * momNegDaughter.X() + 
        momNegDaughter.Y() * momNegDaughter.Y() + 
        momNegDaughter.Z() * momNegDaughter.Z()
    );
    float energysum = EDaugP + EDaugN;
    float pSum2 = 
        ( momNegDaughter.X() + momPosDaughter.X() ) * 
        ( momNegDaughter.X() + momPosDaughter.X() ) 
        +
        ( momNegDaughter.Y() + momPosDaughter.Y() ) * 
        ( momNegDaughter.Y() + momPosDaughter.Y() ) 
        + 
        ( momNegDaughter.Z() + momPosDaughter.Z() ) * 
        ( momNegDaughter.Z() + momPosDaughter.Z() )
    ;
    invMass = TMath::Sqrt(energysum * energysum - pSum2);
    return invMass;
}
float AliAnalysisTaskPOmegaPenne::CalculateInvMassLambda(AliFemtoDreamBasePart *lambdaParticle, bool isAntiParticle)
{
    if(!isAntiParticle)
    {
        return CalculateInvMassLambda(lambdaParticle->GetMomentum(1), 211,
                                      lambdaParticle->GetMomentum(2), 2212);
    }
    else
    {
        return CalculateInvMassLambda(lambdaParticle->GetMomentum(1), 2212,
                                      lambdaParticle->GetMomentum(2), 211);
    }
}
float AliAnalysisTaskPOmegaPenne::CalculateInvMassXi(TVector3 momBach, int PGGbach, TVector3 momPosDaughter, int PDGposDaughter, TVector3 momNegDaughter, int PDGnegDaughter)
{
    float massPosDaugh = TDatabasePDG::Instance()->GetParticle(PDGposDaughter)->Mass();  // Proton 2212 or antiPion 211
    float massNegDaugh = TDatabasePDG::Instance()->GetParticle(PDGnegDaughter)->Mass();   // Pion 211 or antiProton 2212
    float massBach = TDatabasePDG::Instance()->GetParticle(PGGbach)->Mass();            // Pion 211 or antiPion 211
    // float massV0 = CalculateInvMassLambda(momNegDaughter, PDGnegDaughter, momPosDaughter, PDGposDaughter);                 // Lambda
    float massV0 = TDatabasePDG::Instance()->GetParticle(3122)->Mass();     // lambda 3122
    
    TVector3 PtotV0 = (momPosDaughter + momNegDaughter);
    float Ev0 = TMath::Sqrt(massV0 * massV0 + PtotV0.Mag2());

    float EBach = TMath::Sqrt(TMath::Power(massBach, 2) + momBach.Mag2());

    float Ptot2Casc = (PtotV0 + momBach).Mag2();

    return TMath::Sqrt(TMath::Power(Ev0 + EBach,2) - Ptot2Casc);
}
float AliAnalysisTaskPOmegaPenne::CalculateInvMassXi(AliFemtoDreamBasePart *xiParticle, bool isAntiParticle)
{
    if(!isAntiParticle)
    {
        return CalculateInvMassXi(xiParticle->GetMomentum(3), 211, 
                                  xiParticle->GetMomentum(2), 2212,
                                  xiParticle->GetMomentum(1), 211);
    }
    else
    {
        return CalculateInvMassXi(xiParticle->GetMomentum(3), 211, 
                                  xiParticle->GetMomentum(2), 211,
                                  xiParticle->GetMomentum(1), 2212);
    }
}

float AliAnalysisTaskPOmegaPenne::CalculateInvMassHere(AliFemtoDreamv0 *v0, int PDGPosDaug, int PDGNegDaug)     // copied from AliFemtoDreamv0Cuts
{
    Double_t invMass = 0;
    
    float massDP = TDatabasePDG::Instance()->GetParticle(PDGPosDaug)->Mass();
    float massDN = TDatabasePDG::Instance()->GetParticle(PDGNegDaug)->Mass();
    float EDaugP = TMath::Sqrt(
        massDP * massDP + 
        v0->GetPosDaughter()->GetMomentum().X() * v0->GetPosDaughter()->GetMomentum().X() + 
        v0->GetPosDaughter()->GetMomentum().Y() * v0->GetPosDaughter()->GetMomentum().Y() + 
        v0->GetPosDaughter()->GetMomentum().Z() * v0->GetPosDaughter()->GetMomentum().Z()
    );
    float EDaugN = TMath::Sqrt(
        massDN * massDN + 
        v0->GetNegDaughter()->GetMomentum().X() * v0->GetNegDaughter()->GetMomentum().X() + 
        v0->GetNegDaughter()->GetMomentum().Y() * v0->GetNegDaughter()->GetMomentum().Y() + 
        v0->GetNegDaughter()->GetMomentum().Z() * v0->GetNegDaughter()->GetMomentum().Z())
    ;
    float energysum = EDaugP + EDaugN;
    float pSum2 = 
        (v0->GetNegDaughter()->GetMomentum().X() + v0->GetPosDaughter()->GetMomentum().X()) * 
        (v0->GetNegDaughter()->GetMomentum().X() + v0->GetPosDaughter()->GetMomentum().X()) +

        (v0->GetNegDaughter()->GetMomentum().Y() + v0->GetPosDaughter()->GetMomentum().Y()) * 
        (v0->GetNegDaughter()->GetMomentum().Y() + v0->GetPosDaughter()->GetMomentum().Y()) + 

        (v0->GetNegDaughter()->GetMomentum().Z() + v0->GetPosDaughter()->GetMomentum().Z()) * 
        (v0->GetNegDaughter()->GetMomentum().Z() + v0->GetPosDaughter()->GetMomentum().Z())
        ;
    invMass = TMath::Sqrt(energysum * energysum - pSum2);
    return invMass;
}
void AliAnalysisTaskPOmegaPenne::CleanDecay(std::vector<AliFemtoDreamBasePart> *Decay, string particleSteering)
{
    float fPDGMassPart = 1.0;
    float fWeightPart1 = 1.0;
    float fWeightPart2 = 1.0;
    float fMassPart1 = 0.0;
    float fMassPart2 = 0.0;
    float fMassToPDG1 = 0.0;
    float fMassToPDG2 = 0.0;
    if(particleSteering == "Lambda" || particleSteering == "AntiLambda")
    {
        fPDGMassPart = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    }
    else if(particleSteering == "Xi" || particleSteering == "AntiXi")
    {
        fPDGMassPart = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    }
    for (std::vector<AliFemtoDreamBasePart>::iterator itDecay1 = Decay->begin();
         itDecay1 != Decay->end(); ++itDecay1)
    {
        if (itDecay1->UseParticle())
        {
            for (auto itDecay2 = itDecay1 + 1; itDecay2 != Decay->end(); ++itDecay2)
            {
                if (itDecay2->UseParticle())
                {
                    std::vector<int> IDDaug1 = itDecay1->GetIDTracks();
                    std::vector<int> IDDaug2 = itDecay2->GetIDTracks();
                    for (auto itID1s = IDDaug1.begin(); itID1s != IDDaug1.end(); ++itID1s)
                    {
                        for (auto itID2s = IDDaug2.begin(); itID2s != IDDaug2.end(); ++itID2s)
                        {
                            if (*itID1s == *itID2s)
                            {
                                fWeightPart1 = 1.0;
                                fWeightPart2 = 1.0;
                                fMassPart1 = 0.0;
                                fMassPart2 = 0.0;
                                fMassToPDG1 = 0.0;
                                fMassToPDG2 = 0.0;
                                
                                if(particleSteering == "Lambda")
                                {
                                    fMassPart1 = CalculateInvMassLambda(itDecay1->GetMomentum(1), 211, itDecay1->GetMomentum(2), 2212);
                                    fMassPart2 = CalculateInvMassLambda(itDecay2->GetMomentum(1), 211, itDecay2->GetMomentum(2), 2212);
                                    fWeightPart1 = WeightLambda(itDecay1->GetPt());
                                    fWeightPart2 = WeightLambda(itDecay2->GetPt());
                                    // PDG - 3122 - Lambda
                                    // fPDGMassPart = TDatabasePDG::Instance()->GetParticle(3122)->Mass();

                                    fMassToPDG1 = ::abs((fMassPart1 - fPDGMassPart)*1000.0)/fWeightPart1;
                                    fMassToPDG2 = ::abs((fMassPart2 - fPDGMassPart)*1000.0)/fWeightPart2;
                                }
                                else if(particleSteering == "AntiLambda")
                                {
                                    fMassPart1 = CalculateInvMassLambda(itDecay1->GetMomentum(2), 2212, itDecay1->GetMomentum(1), 211);
                                    fMassPart2 = CalculateInvMassLambda(itDecay2->GetMomentum(2), 2212, itDecay2->GetMomentum(1), 211);
                                    fWeightPart1 = WeightAntiLambda(itDecay1->GetPt());
                                    fWeightPart2 = WeightAntiLambda(itDecay2->GetPt());
                                    // PDG - 3122 - Lambda
                                    // fPDGMassPart = TDatabasePDG::Instance()->GetParticle(3122)->Mass();

                                    fMassToPDG1 = ::abs((fMassPart1 - fPDGMassPart)*1000.0)/fWeightPart1;
                                    fMassToPDG2 = ::abs((fMassPart2 - fPDGMassPart)*1000.0)/fWeightPart2;
                                }
                                else if(particleSteering == "Xi")
                                {
                                    fMassPart1 = CalculateInvMassXi(itDecay1->GetMomentum(3), 211, itDecay1->GetMomentum(2), 2212, itDecay1->GetMomentum(1), 211);
                                    fMassPart2 = CalculateInvMassXi(itDecay2->GetMomentum(3), 211, itDecay2->GetMomentum(2), 2212, itDecay2->GetMomentum(1), 211);
                                    fWeightPart1 = WeightXi(itDecay1->GetPt());
                                    fWeightPart2 = WeightXi(itDecay2->GetPt());
                                    // PDG - 3312 - Xi

                                    fMassToPDG1 = ::abs((fMassPart1 - fPDGMassPart)*1000.0)/fWeightPart1;
                                    fMassToPDG2 = ::abs((fMassPart2 - fPDGMassPart)*1000.0)/fWeightPart2;
                                }
                                else if(particleSteering == "AntiXi")
                                {
                                    fMassPart1 = CalculateInvMassXi(itDecay1->GetMomentum(3), 211, itDecay1->GetMomentum(2), 211, itDecay1->GetMomentum(1), 2212);
                                    fMassPart2 = CalculateInvMassXi(itDecay2->GetMomentum(3), 211, itDecay2->GetMomentum(2), 211, itDecay2->GetMomentum(1), 2212);
                                    fWeightPart1 = WeightAntiXi(itDecay1->GetPt());
                                    fWeightPart2 = WeightAntiXi(itDecay2->GetPt());
                                    // PDG - 3312 - Xi
                                    fMassToPDG1 = ::abs((fMassPart1 - fPDGMassPart)*1000.0)/fWeightPart1;
                                    fMassToPDG2 = ::abs((fMassPart2 - fPDGMassPart)*1000.0)/fWeightPart2;
                                }
                                if (fMassToPDG1 > fMassToPDG2)
                                {
                                    itDecay1->SetUse(false);
                                    if (particleSteering == "Lambda")
                                    {
                                        hLambdaCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG1);
                                    }
                                    if (particleSteering == "AntiLambda")
                                    {
                                        hAntiLambdaCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG1);
                                    }
                                    if (particleSteering == "Xi")
                                    {
                                        hXiCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG1);
                                    }
                                    if (particleSteering == "AntiXi")
                                    {
                                        hAntiXiCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG1);
                                    }
                                }
                                else
                                {
                                    itDecay2->SetUse(false);
                                    if (particleSteering == "Lambda")
                                    {
                                        hLambdaCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG2);
                                    }
                                    if (particleSteering == "AntiLambda")
                                    {
                                        hAntiLambdaCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG2);
                                    }
                                    if (particleSteering == "Xi")
                                    {
                                        hXiCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG2);
                                    }
                                    if (particleSteering == "AntiXi")
                                    {
                                        hAntiXiCleanedPartMassDiffToPDG_Decay->Fill(fMassToPDG2);
                                    }
                                }
                                // std::cout << "######################################################" << std::endl; 
                                // std::cout << "*************** CleanDecay ***************" << std::endl;
                                // if(particleSteering == "Lambda") std::cout << "Lambda" << std::endl;
                                // if(particleSteering == "AntiLambda") std::cout << "AntiLambda" << std::endl;
                                // if(particleSteering == "Xi") std::cout << "Xi" << std::endl;
                                // if(particleSteering == "AntiXi") std::cout << "AntiXi" << std::endl;
                                // std::cout << "fWeightPart1: " << fWeightPart1 << std::endl; 
                                // std::cout << "fWeightPart2: " << fWeightPart2 << std::endl; 
                                // std::cout << "itDecay1->Pt: " << itDecay1->GetPt() << std::endl;
                                // std::cout << "itDecay2->Pt: " << itDecay2->GetPt() << std::endl; 
                                // std::cout << "fMassPart1: " << fMassPart1 << std::endl; 
                                // std::cout << "fMassPart2: " << fMassPart2 << std::endl; 
                                // std::cout << "fMassToPDG1: " << fMassToPDG1 << std::endl; 
                                // std::cout << "fMassToPDG2: " << fMassToPDG2 << std::endl;
                                // std::cout << "######################################################" << std::endl; 
                            }
                        }
                    }
                }
                else
                    continue;
            }
        }
        else
            continue;
    }
}
void AliAnalysisTaskPOmegaPenne::CleanDecayAndDecay(std::vector<AliFemtoDreamBasePart> *vecLambda,
                                                    std::vector<AliFemtoDreamBasePart> *vecXi,
                                                    bool isAntiParticle)
{
    int counter = 0;
    float fPDGMassLambda = 1.0;
    float fPDGMassXi = 1.0;
    float fWeightLambda = 1.0;
    float fWeightXi = 1.0;
    float fMassLambda = 0.0;
    float fMassXi = 0.0;
    float fMassToPDGLambda = 0.0;
    float fMassToPDGXi = 0.0;

    fPDGMassLambda = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    fPDGMassXi = TDatabasePDG::Instance()->GetParticle(3312)->Mass();

    for (auto itDecay1 = vecLambda->begin(); itDecay1 != vecLambda->end(); ++itDecay1)
    {
        if (itDecay1->UseParticle())
        {
            for (auto itDecay2 = vecXi->begin(); itDecay2 != vecXi->end(); ++itDecay2)
            {
                if (itDecay2->UseParticle())
                {
                    std::vector<int> IDDaug1 = itDecay1->GetIDTracks();
                    std::vector<int> IDDaug2 = itDecay2->GetIDTracks();
                    for (auto itID1s = IDDaug1.begin(); itID1s != IDDaug1.end(); ++itID1s)
                    {
                        for (auto itID2s = IDDaug2.begin(); itID2s != IDDaug2.end(); ++itID2s)
                        {
                            if (*itID1s == *itID2s)
                            {
                                fWeightLambda = 1.0;
                                fWeightXi = 1.0;
                                fMassLambda = 0.0;
                                fMassXi = 0.0;
                                fMassToPDGLambda = 0.0;
                                fMassToPDGXi = 0.0;

                                if (!isAntiParticle)
                                {
                                    fMassLambda = CalculateInvMassLambda(itDecay1->GetMomentum(1), 211, itDecay1->GetMomentum(2), 2212);
                                    fMassXi = CalculateInvMassXi(itDecay2->GetMomentum(3), 211, itDecay2->GetMomentum(2), 2212, itDecay2->GetMomentum(1), 211);
                                    
                                    fWeightLambda = WeightLambda(itDecay1->GetPt());
                                    fWeightXi = WeightXi(itDecay2->GetPt());
                                    
                                    fMassToPDGLambda = ::abs((fMassLambda - fPDGMassLambda)*1000.0)/fWeightLambda;
                                    fMassToPDGXi = ::abs((fMassXi - fPDGMassXi)*1000.0)/fWeightXi;

                                }
                                else
                                {
                                    fMassLambda = CalculateInvMassLambda(itDecay1->GetMomentum(1), 2212, itDecay1->GetMomentum(2), 211);
                                    fMassXi = CalculateInvMassXi(itDecay2->GetMomentum(3), 211, itDecay2->GetMomentum(2), 211, itDecay2->GetMomentum(1), 2212);

                                    fWeightLambda = WeightAntiLambda(itDecay1->GetPt());
                                    fWeightXi = WeightAntiXi(itDecay2->GetPt());
                                    
                                    fMassToPDGLambda = ::abs((fMassLambda - fPDGMassLambda)*1000.0)/fWeightLambda;
                                    fMassToPDGXi = ::abs((fMassXi - fPDGMassXi)*1000.0)/fWeightXi;

                                }
                                if (fMassToPDGLambda < fMassToPDGXi)
                                {
                                    itDecay2->SetUse(false);
                                    if (!isAntiParticle)
                                    {
                                        hLambdaCleanedPartMassDiffToPDG_DecayDecay->Fill(fMassToPDGLambda);
                                        hLambdaCleanedPartMass_DecayDecay->Fill(fMassLambda);
                                    }
                                    else
                                    {
                                        hAntiLambdaCleanedPartMassDiffToPDG_DecayDecay->Fill(fMassToPDGLambda);
                                        hAntiLambdaCleanedPartMass_DecayDecay->Fill(fMassLambda);
                                    }
                                    counter++;
                                }
                                else
                                {
                                    itDecay2->SetUse(false);
                                    if (!isAntiParticle)
                                    {
                                        hXiCleanedPartMassDiffToPDG_DecayDecay->Fill(fMassToPDGXi);
                                        hXiCleanedPartMass_DecayDecay->Fill(fMassXi);
                                    }
                                    else
                                    {
                                        hAntiXiCleanedPartMassDiffToPDG_DecayDecay->Fill(fMassToPDGXi);
                                        hAntiXiCleanedPartMass_DecayDecay->Fill(fMassXi);
                                    }
                                    
                                    counter++;
                                }
                                // std::cout << "######################################################" << std::endl; 
                                // std::cout << "*************** CleanDecayAndDecay ***************" << std::endl;
                                // if(isAntiParticle == true ) std::cout << "*** ANTI Teilchen ***" << std::endl;
                                // if(isAntiParticle == false) std::cout << "*** Teilchen ***" << std::endl;
                                // std::cout << "fWeightLambda: " << fWeightLambda << std::endl; 
                                // std::cout << "fWeightXi: " << fWeightXi << std::endl; 
                                // std::cout << "itDecay1->Pt: " << itDecay1->GetPt() << std::endl;
                                // std::cout << "itDecay2->Pt: " << itDecay2->GetPt() << std::endl; 
                                // std::cout << "fMassLambda: " << fMassLambda << std::endl; 
                                // std::cout << "fMassXi: " << fMassXi << std::endl; 
                                // std::cout << "fMassToPDGLambda: " << fMassToPDGLambda << std::endl; 
                                // std::cout << "fMassToPDGXi: " << fMassToPDGXi << std::endl;
                                // std::cout << "######################################################" << std::endl; 
                            }
                        }
                    }
                }
                else
                    continue;
            }
        }
        else
            continue;
    }
}

//                                            //
// weights from nanoAOD run 503_20200611-1233 //
//          12.06.2020                        //
//                                            //
float AliAnalysisTaskPOmegaPenne::WeightLambda(float pT)
{
    if (pT > 4.05)
    {
        return 1.8;
    }
    else if (pT < 0.55)
    {
        return 1.7;
    }
    else
    {    
        return ( 
    //          - 0.050794086228099  * ::pow(pT,7)
    //          + 0.746673693291143  * ::pow(pT,6)
    //          - 4.390268634722629  * ::pow(pT,5) 
    //          + 13.225494868295858 * ::pow(pT,4) 
    //          - 21.7930393826395   * ::pow(pT,3) 
    //          + 19.5918494155083   * ::pow(pT,2) 
    //          - 9.12713731127836   *       pT 
    //          + 3.410052828696105
             - 0.05079408f  * ::pow(pT,7)
             + 0.7466736f   * ::pow(pT,6)
             - 4.390268f    * ::pow(pT,5) 
             + 13.22549f    * ::pow(pT,4) 
             - 21.79303f    * ::pow(pT,3) 
             + 19.59184f    * ::pow(pT,2) 
             - 9.1271373f   *       pT 
             + 3.4100528f
        );
    }
}
float AliAnalysisTaskPOmegaPenne::WeightAntiLambda(float pT)
{
    if (pT > 4.05)
    {
        return 1.8;
    }
    else if (pT < 0.55)
    {
        return 1.7;
    }
    else
    {    
        return (  
                //   0.002539743703452  * ::pow(pT,7)
                // - 0.072000987373043  * ::pow(pT,6)
                // + 0.732584302358743  * ::pow(pT,5) 
                // - 3.62492271888172   * ::pow(pT,4) 
                // + 9.481334073591578  * ::pow(pT,3) 
                // - 12.903222262109562 * ::pow(pT,2) 
                // + 8.182929410257247  *       pT 
                // - 0.178055770090033
                  0.002539743f  * ::pow(pT,7)
                - 0.07200098f   * ::pow(pT,6)
                + 0.7325843f    * ::pow(pT,5) 
                - 3.624922f     * ::pow(pT,4) 
                + 9.481334f     * ::pow(pT,3) 
                - 12.90322f     * ::pow(pT,2) 
                + 8.182929f     *       pT 
                - 0.1780557f
        );
    }
}
float AliAnalysisTaskPOmegaPenne::WeightXi(float pT)
{
    if (pT > 6.3)
    {
        return 2.8;
    }
    else if (pT < 0.55)
    {
        return 2.3;
    }
    else
    {    
        return (
            // - 0.00005897109513  * ::pow(pT,7)
            // + 0.002190119023293 * ::pow(pT,6)
            // - 0.027809111659546 * ::pow(pT,5) 
            // + 0.174286508765234 * ::pow(pT,4) 
            // - 0.628992064780411 * ::pow(pT,3) 
            // + 1.407963402631568 * ::pow(pT,2) 
            // - 1.710865466687404 *       pT 
            // + 2.90331311301965
            - 0.00005897109f * ::pow(pT,7)
            + 0.002190119f   * ::pow(pT,6)
            - 0.02780911f    * ::pow(pT,5) 
            + 0.1742865f     * ::pow(pT,4) 
            - 0.6289920f     * ::pow(pT,3) 
            + 1.407963f      * ::pow(pT,2) 
            - 1.710865f      *       pT 
            + 2.903313f
        );
    }
}
float AliAnalysisTaskPOmegaPenne::WeightAntiXi(float pT)
{
    if (pT > 6.3)
    {
        return 2.8;
    }
    else if (pT < 0.55)
    {
        return 2.3;
    }
    else
    {    
        return (  
            //   0.001766952359948   * ::pow(pT,9)
            // - 0.053782480701883   * ::pow(pT,8)
            // + 0.698362038014072   * ::pow(pT,7)
            // - 5.045875635116904   * ::pow(pT,6)
            // + 22.182635161635314  * ::pow(pT,5) 
            // - 60.92189512030214   * ::pow(pT,4) 
            // + 103.17632848184287  * ::pow(pT,3) 
            // - 102.12557567019556  * ::pow(pT,2) 
            // + 52.4700107450488    *       pT 
            // - 8.24370641612618
              0.001766952f  * ::pow(pT,9)
            - 0.05378248f   * ::pow(pT,8)
            + 0.6983620f    * ::pow(pT,7)
            - 5.045875f     * ::pow(pT,6)
            + 22.18263f     * ::pow(pT,5) 
            - 60.92189f     * ::pow(pT,4) 
            + 103.1763f     * ::pow(pT,3) 
            - 102.1255f     * ::pow(pT,2) 
            + 52.47001f     *       pT 
            - 8.243706f
        );
    }
}

float AliAnalysisTaskPOmegaPenne::RelativePairMomentum(AliFemtoDreamBasePart *part1, const int pdg1, AliFemtoDreamBasePart *part2, const int pdg2) 
{
  TLorentzVector PartOne, PartTwo;

  PartOne.SetXYZM(part1->GetMomentum().X(), part1->GetMomentum().Y(), part1->GetMomentum().Z(), TDatabasePDG::Instance()->GetParticle(pdg1)->Mass());
  PartTwo.SetXYZM(part2->GetMomentum().X(), part2->GetMomentum().Y(), part2->GetMomentum().Z(), TDatabasePDG::Instance()->GetParticle(pdg2)->Mass());

  TLorentzVector trackSum = PartOne + PartTwo;
  
  float beta = trackSum.Beta();
  float betax = beta * cos(trackSum.Phi()) * sin(trackSum.Theta());
  float betay = beta * sin(trackSum.Phi()) * sin(trackSum.Theta());
  float betaz = beta * cos(trackSum.Theta());

  TLorentzVector PartOneCMS = PartOne;
  TLorentzVector PartTwoCMS = PartTwo;

  PartOneCMS.Boost(-betax, -betay, -betaz);
  PartTwoCMS.Boost(-betax, -betay, -betaz);

  TLorentzVector trackRelK = PartOneCMS - PartTwoCMS;

  return 0.5 * trackRelK.P();
}
