/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: Ana Marin, Kathrin Koch, Kenneth Aamodt                        *
 * Version 1.1                                                            *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

////////////////////////////////////////////////
//--------------------------------------------- 
// Class used to do analysis on conversion pairs
//---------------------------------------------
////////////////////////////////////////////////

#include "AliGammaConversionHistograms.h"
#include "TMath.h"
#include "TObjString.h"
#include "TMap.h"
#include "TList.h"
#include "TH1F.h"
#include "TH2F.h"


using namespace std;

ClassImp(AliGammaConversionHistograms)


AliGammaConversionHistograms::AliGammaConversionHistograms() :
  fHistogramMap(new TMap()),
  fNPhiIndex(0),
  fNRIndex(0),
  fNZIndex(0),
  fRBinLimits(0),
  fZBinLimits(0),
  fMinRadius(0.),
  fMaxRadius(0.),
  fDeltaR(0.),
  fMinPhi(0.),
  fMaxPhi(0.),
  fDeltaPhi(0.),
  fMappingContainer(NULL),
  fBackgroundContainer(NULL),
  fDebugContainer(NULL),
  fResolutionContainer(NULL),
  fMatchContainer(NULL),
  fESDContainer(NULL),
  fMCContainer(NULL),
  fTableContainer(NULL),	
  fOtherContainer(NULL)
{
  // see header file for documenation
}


AliGammaConversionHistograms::AliGammaConversionHistograms(const AliGammaConversionHistograms & original) :
  fHistogramMap(original.fHistogramMap),
  fNPhiIndex(original.fNPhiIndex),
  fNRIndex(original.fNRIndex),
  fNZIndex(original.fNZIndex),
  fRBinLimits(original.fRBinLimits),
  fZBinLimits(original.fZBinLimits),
  fMinRadius(original.fMinRadius),
  fMaxRadius(original.fMaxRadius),
  fDeltaR(original.fDeltaR),
  fMinPhi(original.fMinPhi),
  fMaxPhi(original.fMaxPhi),
  fDeltaPhi(original.fDeltaPhi),
  fMappingContainer(original.fMappingContainer),
  fBackgroundContainer(original.fBackgroundContainer),
  fDebugContainer(original.fDebugContainer),
  fResolutionContainer(original.fResolutionContainer),
  fMatchContainer(original.fMatchContainer),
  fESDContainer(original.fESDContainer),
  fMCContainer(original.fMCContainer),
  fTableContainer(original.fTableContainer), 
  fOtherContainer(original.fOtherContainer)
{    
  //see header file for documentation
}


AliGammaConversionHistograms & AliGammaConversionHistograms::operator = (const AliGammaConversionHistograms & /*original*/)
{
  // assignment operator
  return *this;
}


AliGammaConversionHistograms::~AliGammaConversionHistograms() {
  //destructor
	
	
}

void AliGammaConversionHistograms::AddHistogram(TString histogramName, TString histogramTitle, Int_t nXBins, Double_t firstX,Double_t lastX,TString xAxisTitle, TString yAxisTitle){
  // see header file for documentation
  TH1F *tmp = new TH1F(histogramName, histogramTitle,nXBins,firstX,lastX);
  tmp->GetXaxis()->SetTitle(xAxisTitle);
  tmp->GetYaxis()->SetTitle(yAxisTitle);
  TObjString* tobjstring = new TObjString(histogramName.Data());
  fHistogramMap->Add((TObject*)tobjstring,(TObject*)tmp);
}

void AliGammaConversionHistograms::AddHistogram(TString histogramName, TString histogramTitle, Int_t nXBins, Double_t firstX, Double_t lastX, Int_t nYBins, Double_t firstY, Double_t lastY, TString xAxisTitle, TString yAxisTitle){
  // see header file for documentation
  TH2F *tmp = new TH2F(histogramName, histogramTitle,nXBins,firstX,lastX,nYBins,firstY,lastY);
  tmp->GetXaxis()->SetTitle(xAxisTitle);
  tmp->GetYaxis()->SetTitle(yAxisTitle);
  TObjString *tobjstring = new TObjString(histogramName.Data());
  fHistogramMap->Add((TObject*)tobjstring,(TObject*)tmp);
}

void AliGammaConversionHistograms::AddTable(TString tableName,TString tableTitle,Int_t nXBins,const char * axesLabel[]){
  //see header file for documentation

  TH1F *tmp = new TH1F(tableName,tableTitle,nXBins,0,nXBins);
  for(Int_t xbin=1; xbin<=nXBins; xbin++){
    tmp->GetXaxis()->SetBinLabel(xbin,axesLabel[xbin-1]);
  }
  tmp->SetStats(0);

  TObjString *tobjstring = new TObjString(tableName.Data());
  fHistogramMap->Add((TObject*)tobjstring,(TObject*)tmp);
}

void AliGammaConversionHistograms::FillTable(TString tableName,Double_t xValue) const {
  //see header file for documentation
  TH1 *tmp = (TH1*)fHistogramMap->GetValue(tableName.Data());
  if(tmp){
    tmp->Fill(xValue);
  }
}

void AliGammaConversionHistograms::FillHistogram(TString histogramName, Double_t xValue) const{
  //see header file for documentation
  TH1 *tmp = (TH1*)fHistogramMap->GetValue(histogramName.Data());
  if(tmp){
    tmp->Fill(xValue);
  }
}

void AliGammaConversionHistograms::FillHistogram(TString histogramName, Double_t xValue, Double_t yValue) const{
  //see header file for documentation
  TH1 *tmp = (TH1*)fHistogramMap->GetValue(histogramName.Data());
  if(tmp){
    tmp->Fill(xValue, yValue);
  }
}

void AliGammaConversionHistograms::GetOutputContainer(TList *fOutputContainer){
  //checking if the container is alrerady created
	
  if(fOutputContainer == NULL){
    cout<<"WARNING: GetOutputContainer: output container object is NULL"<<endl;
    return;
  }

  if(fHistogramMap != NULL){
    TIter iter(fHistogramMap);
    TObjString *histogramName;
    while ((histogramName = (TObjString*) iter.Next())) {
      TString histogramString = histogramName->GetString();
      if(histogramString.Contains("Mapping")){// means it should be put in the mapping folder
	if(fMappingContainer == NULL){
	  fMappingContainer = new TList();
	  fMappingContainer->SetName("Mapping histograms");
	}
	if(fMappingContainer != NULL){
	  fMappingContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("Background")){// means it should be put in the background folder
	if(fBackgroundContainer == NULL){
	  fBackgroundContainer = new TList();
	  fBackgroundContainer->SetName("Background histograms");
	}
	if(fBackgroundContainer != NULL){
	  fBackgroundContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("Debug")){// means it should be put in the debug folder
	if(fDebugContainer == NULL){
	  fDebugContainer = new TList();
	  fDebugContainer->SetName("Debug histograms");
	}
	if(fDebugContainer != NULL){
	  fDebugContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("Resolution")){// means it should be put in the resolution folder
	if(fResolutionContainer == NULL){
	  fResolutionContainer = new TList();
	  fResolutionContainer->SetName("Resolution histograms");
	}
	if(fResolutionContainer != NULL){
	  fResolutionContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("TrueConv")){// means it should be put in the true conv folder
	if(fMatchContainer == NULL){
	  fMatchContainer = new TList();
	  fMatchContainer->SetName("True conversion histograms");
	}
	if(fMatchContainer != NULL){
	  fMatchContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("ESD")){// means it should be put in the ESD folder
	if(fESDContainer == NULL){
	  fESDContainer = new TList();
	  fESDContainer->SetName("ESD histograms");
	}
	if(fESDContainer != NULL){
	  fESDContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("MC")){// means it should be put in the MC folder
	if(fMCContainer == NULL){
	  fMCContainer = new TList();
	  fMCContainer->SetName("MC histograms");
	}
	if(fMCContainer != NULL){
	  fMCContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      else if(histogramString.Contains("Table")){// means it should be put in the Table Folder
	if(fTableContainer == NULL){
	   fTableContainer = new TList();
	   fTableContainer->SetName("Tables");
	}
	if(fTableContainer != NULL){
	   fTableContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }			
      else{
	if(fOtherContainer == NULL){
	  fOtherContainer = new TList();
	  fOtherContainer->SetName("Other histograms");
	}
	if(fOtherContainer != NULL){
	  fOtherContainer->Add((TH1*)fHistogramMap->GetValue(histogramString.Data()));
	}
      }
      histogramName = NULL;
    } // end while
    if(fMappingContainer != NULL){
      fOutputContainer->Add(fMappingContainer);
    }
    if(fBackgroundContainer != NULL){
      fOutputContainer->Add(fBackgroundContainer);
    }
    if(fDebugContainer != NULL){
      fOutputContainer->Add(fDebugContainer);
    }
    if(fResolutionContainer != NULL){
      fOutputContainer->Add(fResolutionContainer);
    }
    if(fMatchContainer != NULL){
      fOutputContainer->Add(fMatchContainer);
    }
    if(fESDContainer != NULL){
      fOutputContainer->Add(fESDContainer);
    }
    if(fMCContainer != NULL){
      fOutputContainer->Add(fMCContainer);
    }
    if(fTableContainer !=  NULL){
       fOutputContainer->Add(fTableContainer);	
    }		
    if(fOtherContainer != NULL){
      fOutputContainer->Add(fOtherContainer);
    }
  }
}

Int_t AliGammaConversionHistograms::GetRBin(Double_t radius) const{
  // see header file for documentation
  Int_t iResult=0;
//   if(fDeltaR>0){
//     iResult = (Int_t)((radius - fMinRadius)/fDeltaR);
//   }
  for(Int_t i=0;i<fNRIndex;i++){
    //    cout<<"Test-limits::"<< fRBinLimits[i]<<endl;
    if( radius>=fRBinLimits[i] && radius<fRBinLimits[i+1] ){
      iResult=i;
    }
  }
  return iResult;
}

Int_t AliGammaConversionHistograms::GetZBin(Double_t zPos) const{
  // see header file for documentation
  Int_t iResult=0;

  for(Int_t i=0;i<fNZIndex;i++){
    //    cout<<"Test-limits::"<< fZBinLimits[i]<<endl;
    if( TMath::Abs(zPos)>=fZBinLimits[i] && TMath::Abs(zPos)<fZBinLimits[i+1] ){
      iResult=i;
    }
  }
  return iResult;
}



Int_t AliGammaConversionHistograms::GetPhiBin(Double_t phi) const{
  // see header file for documentation
  Int_t iResult=0;
  if(fDeltaPhi>0){
    if(phi>TMath::Pi()){
      phi-=2*TMath::Pi();
    }
    iResult = (Int_t)((phi - fMinPhi)/fDeltaPhi);
  }
  return iResult;
}



void AliGammaConversionHistograms::InitializeMappingValues(Int_t nPhiIndex, Int_t nRIndex, Int_t nBinsR, Double_t minRadius, Double_t maxRadius,Int_t nBinsPhi, Double_t minPhi, Double_t maxPhi){
  // Initializing the valuse for the mapping
	
  fNPhiIndex = nPhiIndex;
  fNRIndex   = nRIndex;
  fNZIndex = 6;

  fRBinLimits= new Double_t[8];
  fRBinLimits[0]=0.;
  fRBinLimits[1]=12.;
  fRBinLimits[2]=22.;
  fRBinLimits[3]=35.;
  fRBinLimits[4]=55.;
  fRBinLimits[5]=72.;
  fRBinLimits[6]=90.;
  fRBinLimits[7]=500.;

  fZBinLimits= new Double_t[7];
  fZBinLimits[0]=0.;
  fZBinLimits[1]=15.;
  fZBinLimits[2]=30.;
  fZBinLimits[3]=50.;
  fZBinLimits[4]=100.;
  fZBinLimits[5]=200.;
  fZBinLimits[6]=500.;


  fMinRadius      = minRadius;
  fMaxRadius      = maxRadius;
  if(nBinsR>0 && nRIndex!=0){
    fDeltaR       = (fMaxRadius - fMinRadius)/nRIndex;
  }
  fMinPhi         = minPhi;
  fMaxPhi         = maxPhi;
  if(nBinsPhi>0 && nPhiIndex!=0){
    fDeltaPhi     = (fMaxPhi-fMinPhi)/nPhiIndex;
  }
}


//mapping
void AliGammaConversionHistograms::AddMappingHistograms(Int_t nPhiIndex, Int_t nRIndex,Int_t nXBins, Double_t firstX, Double_t lastX, Int_t nYBins, Double_t firstY, Double_t lastY, TString xAxisTitle, TString yAxisTitle){
  // see header file for documentation
	
  for(Int_t phi =0; phi<fNPhiIndex;phi++){
		
    for(Int_t r =0; r<fNRIndex;r++){
			
      // setting axis to "" changes below
      xAxisTitle="z [cm]";
      yAxisTitle="#eta";
	  
      //Creating the axis titles
      //if(xAxisTitle.Length() == 0){
	//xAxisTitle.Form("Phi %02d",phi);
	 //      }
			
      //if(yAxisTitle.Length() == 0){
	//yAxisTitle.Form("R %02d",phi);
		// }
			
      //MC
      TString nameMC="";
      nameMC.Form("MC_Conversion_Mapping_Phi%02d_R%02d",phi,r);
      TString titleMC="";
      titleMC.Form("Electron-Positron MC Mapping-Phi%02d-R%02d",phi,r);
			
      AddHistogram(nameMC, titleMC, nXBins, firstX, lastX, nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
			
      //ESD
      TString nameESD="";
      nameESD.Form("ESD_Conversion_Mapping_Phi%02d_R%02d",phi,r);
      TString titleESD="";
      titleESD.Form("Electron-Positron ESD Mapping-Phi%02d-R%02d",phi,r);
			
      AddHistogram(nameESD, titleESD, nXBins, firstX, lastX, nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
    }
  }
	
	
  for(Int_t phi =0; phi<=nPhiIndex;phi++){ 
		
    // setting axis to "" changes below
     xAxisTitle="z [cm]";
      yAxisTitle="#eta";
   //Creating the axis titles
    //if(xAxisTitle.Length() == 0){
    //  xAxisTitle.Form("Phi %02d",phi);
    //}
    //if(yAxisTitle.Length() == 0){
    //  yAxisTitle = "Counts";
    //}
		
    //MC
    TString nameMC="";
    nameMC.Form("MC_Conversion_Mapping_Phi%02d",phi);
    TString titleMC="";
    titleMC.Form("Electron-Positron MC Mapping-Phi%02d",phi);
		
    AddHistogram(nameMC, titleMC, nXBins, firstX, lastX, nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
		
    //MC
    TString nameESD="";
    nameESD.Form("ESD_Conversion_Mapping_Phi%02d",phi);
    TString titleESD="";
    titleESD.Form("Electron-Positron ESD Mapping-Phi%02d",phi);
		
    AddHistogram(nameESD, titleESD, nXBins, firstX, lastX,nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
  }
	
	
  for(Int_t r =0; r<nRIndex;r++){
		
    // setting axis to "" changes below
    xAxisTitle="#phi";
      yAxisTitle="counts";
    //Creating the axis titles
    //if(xAxisTitle.Length() == 0){
    //  xAxisTitle.Form("R %02d",r);
    //}
    //if(yAxisTitle.Length() == 0){
    //  yAxisTitle = "Counts";
    //}
		
    //MC
    TString nameMC="";
    nameMC.Form("MC_Conversion_Mapping_R%02d",r);
    TString titleMC="";
    titleMC.Form("Electron-Positron MC Mapping-R%02d",r);
		
    AddHistogram(nameMC, titleMC, nXBins, firstX, lastX, nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
		
    //ESD
    TString nameESD="";
    nameESD.Form("ESD_Conversion_Mapping_R%02d",r);
    TString titleESD="";
    titleESD.Form("Electron-Positron ESD Mapping-R%02d",r);
		
    AddHistogram(nameESD, titleESD, nXBins, firstX, lastX,nYBins, firstY, lastY, xAxisTitle, yAxisTitle);
		
    //Mapping Phi in R
    TString nameMCPhiInR="";
    nameMCPhiInR.Form("MC_Conversion_Mapping_Phi_in_R_%02d",r);
    TString titleMCPhiInR="";
    titleMCPhiInR.Form("MC Mapping of Phi in R%02d",r);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);
		

    //Mapping Z in R
    TString nameMCZInR="";
    nameMCZInR.Form("MC_Conversion_Mapping_Z_in_R_%02d",r);
    TString titleMCZInR="";
    titleMCZInR.Form("MC Mapping of Z in R%02d",r);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCZInR, titleMCZInR, nXBins, -300, 300, xAxisTitle, yAxisTitle);


   //Mapping Phi in R Middle Pt
    TString nameMCMidPtPhiInR="";
    nameMCMidPtPhiInR.Form("MC_Conversion_Mapping_MidPt_Phi_in_R_%02d",r);
    TString titleMCMidPtPhiInR="";
    titleMCMidPtPhiInR.Form("MC Mapping Middle Pt of Phi in R%02d",r);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCMidPtPhiInR, titleMCMidPtPhiInR, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);
		

    //Mapping Z in R Middle Pt
    TString nameMCMidPtZInR="";
    nameMCMidPtZInR.Form("MC_Conversion_Mapping_MidPt_Z_in_R_%02d",r);
    TString titleMCMidPtZInR="";
    titleMCMidPtZInR.Form("MC Mapping Middle Pt of Z in R%02d",r);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCMidPtZInR, titleMCMidPtZInR, nXBins, -300, 300, xAxisTitle, yAxisTitle);




    //Mapping Phi in R
    TString nameESDPhiInR="";
    nameESDPhiInR.Form("ESD_Conversion_Mapping_Phi_in_R_%02d",r);
    TString titleESDPhiInR="";
    titleESDPhiInR.Form("ESD Mapping of Phi in R%02d",r);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);    

   //Mapping Z in R
    TString nameESDZInR="";
    nameESDZInR.Form("ESD_Conversion_Mapping_Z_in_R_%02d",r);
    TString titleESDZInR="";
    titleESDZInR.Form("ESD Mapping of Z in R%02d",r);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDZInR, titleESDZInR, nXBins, -300, 300, xAxisTitle, yAxisTitle);    

    //Mapping Phi in R Middle Pt 
    TString nameESDMidPtPhiInR="";
    nameESDMidPtPhiInR.Form("ESD_Conversion_Mapping_MidPt_Phi_in_R_%02d",r);
    TString titleESDMidPtPhiInR="";
    titleESDMidPtPhiInR.Form("ESD Mapping Middle Pt of Phi in R%02d",r);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDMidPtPhiInR, titleESDMidPtPhiInR, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);    

   //Mapping Z in R Middle Pt
    TString nameESDMidPtZInR="";
    nameESDMidPtZInR.Form("ESD_Conversion_Mapping_MidPt_Z_in_R_%02d",r);
    TString titleESDMidPtZInR="";
    titleESDMidPtZInR.Form("ESD Mapping Middle Pt of Z in R%02d",r);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDMidPtZInR, titleESDMidPtZInR, nXBins, -300, 300, xAxisTitle, yAxisTitle);    


 
  }



  for(Int_t z =0; z<fNZIndex;z++){
    //Mapping Phi in Z
    TString nameMCPhiInZ="";
    nameMCPhiInZ.Form("MC_Conversion_Mapping_Phi_in_Z_%02d",z);
    TString titleMCPhiInZ="";
    titleMCPhiInZ.Form("MC Mapping of Phi in Z%02d",z);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCPhiInZ, titleMCPhiInZ, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);
		

    //Mapping R in Z
    TString nameMCRInZ="";
    nameMCRInZ.Form("MC_Conversion_Mapping_R_in_Z_%02d",z);
    TString titleMCRInZ="";
    titleMCRInZ.Form("MC Mapping of R in Z%02d",z);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCRInZ, titleMCRInZ, nXBins, fMinRadius, fMaxRadius, xAxisTitle, yAxisTitle);

   //Mapping Phi in Z Middle Pt
    TString nameMCMidPtPhiInZ="";
    nameMCMidPtPhiInZ.Form("MC_Conversion_Mapping_MidPt_Phi_in_Z_%02d",z);
    TString titleMCMidPtPhiInZ="";
    titleMCMidPtPhiInZ.Form("MC Mapping Middle Pt of Phi in Z%02d",z);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCMidPtPhiInZ, titleMCMidPtPhiInZ, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);
		

    //Mapping R in Z Middle Pt
    TString nameMCMidPtRInZ="";
    nameMCMidPtRInZ.Form("MC_Conversion_Mapping_MidPt_R_in_Z_%02d",z);
    TString titleMCMidPtRInZ="";
    titleMCMidPtRInZ.Form("MC Mapping Middle Pt of R in Z%02d",z);
    //    AddHistogram(nameMCPhiInR, titleMCPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);
    AddHistogram(nameMCMidPtRInZ, titleMCMidPtRInZ, nXBins, fMinRadius, fMaxRadius, xAxisTitle, yAxisTitle);




    //Mapping Phi in Z
    TString nameESDPhiInZ="";
    nameESDPhiInZ.Form("ESD_Conversion_Mapping_Phi_in_Z_%02d",z);
    TString titleESDPhiInZ="";
    titleESDPhiInZ.Form("ESD Mapping of Phi in R%02d",z);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDPhiInZ, titleESDPhiInZ, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);    

   //Mapping R in Z
    TString nameESDRInZ="";
    nameESDRInZ.Form("ESD_Conversion_Mapping_R_in_Z_%02d",z);
    TString titleESDRInZ="";
    titleESDRInZ.Form("ESD Mapping of R in Z%02d",z);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDRInZ, titleESDRInZ, nXBins, fMinRadius, fMaxRadius, xAxisTitle, yAxisTitle);    


   //Mapping Phi in Z Middle Pt
    TString nameESDMidPtPhiInZ="";
    nameESDMidPtPhiInZ.Form("ESD_Conversion_Mapping_MidPt_Phi_in_Z_%02d",z);
    TString titleESDMidPtPhiInZ="";
    titleESDMidPtPhiInZ.Form("ESD Mapping Middle Ptof Phi in R%02d",z);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDMidPtPhiInZ, titleESDMidPtPhiInZ, nXBins, -TMath::Pi(), TMath::Pi(), xAxisTitle, yAxisTitle);    

   //Mapping R in Z Middle Pt
    TString nameESDMidPtRInZ="";
    nameESDMidPtRInZ.Form("ESD_Conversion_Mapping_MidPt_R_in_Z_%02d",z);
    TString titleESDMidPtRInZ="";
    titleESDMidPtRInZ.Form("ESD Mapping Middle Pt of R in Z%02d",z);
    //    AddHistogram(nameESDPhiInR, titleESDPhiInR, nXBins, firstX, lastX, xAxisTitle, yAxisTitle);    
    AddHistogram(nameESDMidPtRInZ, titleESDMidPtRInZ, nXBins, fMinRadius, fMaxRadius, xAxisTitle, yAxisTitle);    



  }



}
