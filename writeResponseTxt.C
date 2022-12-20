// ROOT script to write a response matrix from a Geant4 simulation and 
// put it in the form of Mike's matrices. 
// *******

void writeResponseTxt()
{
  int nFiles;
  cout << "Enter number of files (240 for Ohio matrix): " ;
  cin  >> nFiles;

  double enIn = 0.05;
  double lIn = 0.01;
  int nBins = 600;

  ofstream myfile;
  myfile.open ("matrix.txt");

  myfile << nBins << " " << nFiles << " " << 1 << " " << lIn << endl;

  for(int i=0; i<nFiles+1; i++)
  {  
    //_en_0.root
    stringstream ss;                                                            
    double en = (i) * enIn;                          
    ss << "dStilResponse/_en_" << en << ".root";                            
    TString fN = ss.str();
    cout << fN << endl;
    TFile *f1 = new TFile( fN,"read" ); 
    TH1F  *hist = (TH1F*)f1->Get("Det0_smear");                                                                              
    for(int j=0; j<nBins; j++)
    {
      myfile << hist->GetBinContent(j+1) << " ";
    }
    myfile << endl;
  }




}
