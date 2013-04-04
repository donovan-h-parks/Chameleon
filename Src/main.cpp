//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// This file is part of Chameleon.
//
// Chameleon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chameleon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Chameleon. If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "GUI.h"
#include "Log.hpp"
#include "GetOpt.hpp"
#include "StringUtils.hpp"
#include "SplitSystem.hpp"
#include "UniSplit.hpp"
#include "NewickIO.hpp"
#include "Cluster.hpp"
#include "PCoA.hpp"
#include "LinearRegression.hpp"
#include "MatrixSystem.hpp"

#include "UnitTests.hpp"
#include "Sandbox.hpp"

#ifdef USE_OMP
	#include <omp.h>
#endif
#include <iostream>

void qtMessageHandler(QtMsgType type, const char *msg)
{
	switch (type) {
	case QtDebugMsg:
		 fprintf(stderr, "Debug: %s\n", msg);
		 break;
	case QtWarningMsg:
		 fprintf(stderr, "Warning: %s\n", msg);
		 break;
	case QtCriticalMsg:
		 fprintf(stderr, "Critical: %s\n", msg);
		 break;
	case QtFatalMsg:
		 fprintf(stderr, "Fatal: %s\n", msg);
		 abort();
	}
 }

int main(int argc, char *argv[])
{
	srand((unsigned)time(0));
	QCoreApplication::setOrganizationName("Robert G. Beiko Lab");
	QCoreApplication::setApplicationName("Chameleon: many visualizations of biodiversity.");

	//qInstallMsgHandler(qtMessageHandler);
	QApplication app(argc, argv);
	if(argc > 1)
	{		
		// setup command line arguments
		GetOpt opts;

		bool bShowHelp;
		opts.addSwitch("help", &bShowHelp);
		
		bool bShowVersion;
		opts.addSwitch("version", &bShowVersion);

		bool bShowContactInfo;
		opts.addSwitch("contact", &bShowContactInfo);

		bool bShowCountTable;
		opts.addSwitch("count-table", &bShowCountTable);

		bool bExecuteUnitTests;
		opts.addSwitch("unit-tests", &bExecuteUnitTests);

		QString phylogenyFile;
		opts.addOption('p', "phylogeny-file", &phylogenyFile);

		bool bImplicitlyRooted;
		opts.addSwitch("rooted", &bImplicitlyRooted);

		QString samplesFile;
		opts.addOption('s', "samples-file", &samplesFile);

		QString outputDissFile;
		opts.addOptionalOption('d', "output-diss-file", &outputDissFile, "dissimilarity.txt");

		bool bWeighted;
		opts.addSwitch("weighted", &bWeighted);

		bool bNormalized;
		opts.addSwitch("normalized", &bNormalized);

		QString splitsToConsider;
		opts.addOptionalOption("splits-to-consider", &splitsToConsider, "COMMON_SPLIT_SET");

		QString numPermutations;
		opts.addOptionalOption('#', "permutations", &numPermutations, "0");

		QString outputJackknifeFile;
		opts.addOptionalOption('t', "output-tree", &outputJackknifeFile, "tree.tre");

		QString outputSignFile;
		opts.addOptionalOption('o', "output-sign-file", &outputSignFile, "sign.txt");

		QString numJackknifeSeq;
		opts.addOptionalOption('j', "jackknife", &numJackknifeSeq, "0");

		QString numJackknifeIter;
		opts.addOptionalOption('i', "iterations", &numJackknifeIter, "100");

		QString numCoresStr;
		opts.addOptionalOption('c', "cores", &numCoresStr, "1");

		bool bExecuteSandbox;
		opts.addSwitch("sandbox", &bExecuteSandbox);

		bool bClusteringUPGMA;
		opts.addSwitch("clusteringUPGMA", &bClusteringUPGMA);

		bool bClusteringSL;
		opts.addSwitch("clusterSL", &bClusteringSL);

		bool bClusteringCL;
		opts.addSwitch("clusterCL", &bClusteringCL);

		bool bClusteringNJ;
		opts.addSwitch("clusterNJ", &bClusteringNJ);

		QString clusterFilename;
		opts.addOption('x', "cluster-filename", &clusterFilename);

		bool bPCoA;
		opts.addSwitch("pcoa", &bPCoA);

		QString pcoaFilename;
		opts.addOption('y', "pcoa-filename", &pcoaFilename);

		bool bLinearRegression;
		opts.addSwitch("linear-regression", &bLinearRegression);

		QString lrMatrix1;
		opts.addOption('1', "lr-matrix-1", &lrMatrix1);

		QString lrMatrix2;
		opts.addOption('2', "lr-matrix-2", &lrMatrix2);

		QString lrResultsFilename;
		opts.addOptionalOption('l', "lr-filename", &lrResultsFilename, "linReg.txt");

		#ifdef WIN32
				QFile log("Log.txt");
				log.open(QFile::WriteOnly | QFile::Truncate);
				QTextStream stream(&log);
		#else
				QTextStream stream(stdout, QIODevice::WriteOnly);
		#endif

		if(!opts.parse() || bShowHelp) 
		{			
			stream << "Usage: " << opts.appName() << " -p <phylogeny file> --rooted -s <sample file> -d <output file>" << endl;
			stream << "  --help                 Produce help message." << endl;
			stream << "  --version              Print version information." << endl;
			stream << "  --contact              Print contact information." << endl;
			stream << "  --unit-tests           Execute unit tests." << endl;
			stream << endl;
			stream << "  -p, --phylogeny-file   Tree in Newick format (*.tre, *.tree or *.new) or a split system in Nexus format (*.nex, *.nxs, or *.nexus)." << endl;
			stream << "  --rooted               Indicates that tree file should be treated as implicitly rooted." << endl;
			stream << "  -s, --samples-file     Environment file in UniFrac/TreeClimber format." << endl;
			stream << "  -d, --output-diss-file File where dissimilarity matrix will be written to (default = dissimilarity.txt)." << endl;
			stream << endl;
			stream << "  --weighted             Indicates a weighted analysis should be perfromed ." << endl;
			stream << "  --normalized           Indicates results of a weighted analysis should be normalized." << endl;
			stream << "  --splits-to-consider   Indicates splits to be consider when calculating dissimilarity:" << endl;
			stream << "                           COMMON_SPLIT_SET" << endl;
			stream << "                           COMPLETE_LINEAGE" << endl;
			stream << "                           ALL_SPLITS" << endl;
			stream << "                           NORMALIZED_WEIGHTED_UNIFRAC" << endl; 
			stream << "                           (default = COMPLETE_SPLIT_SET)." << endl;
			stream << endl;
			stream << "  -j, --jackknife        Perform jackknife clustering analysis with the specified number of sequences (default = 0)." << endl;
			stream << "  -i, --iterations       Number of jackknife iterations to perform (default = 100)." << endl;
			stream << "  -t, --output-tree      File where jackknife tree will be written to (default = tree.tre)." << endl;
			//stream << "  -#, --permutations			Performing Monte Carlo permutation test with the specified number of permutations (default = 0)." << endl;
			//stream << "  -o, --output-sign-file	File where uncorrected significance matrix will be written to (default = sign.txt)." << endl;
			stream << endl;
			stream << "  --count-table          Indicate number of samples from each environment." << endl;
			stream << "  -c, --cores            Indicates number of cores (shared memory processors) to use (default = all available)." << endl;
			stream << endl;
			stream << "  --clusteringUPGMA      Perform UPGMA hierarchical clustering on resulting dissimilarity matrix (upgma.tre)." << endl;
			stream << "  --clusterSL						Perform single linkage clustering on resulting dissimilarity matrix (sl.tre)." << endl;
			stream << "  --clusterCL						Perform complete linkage clustering on resulting dissimilarity matrix (cl.tre)." << endl;
			stream << "  --clusterNJ	          Perform single linkage clustering on resulting dissimilarity matrix (nj.tre)." << endl;
			stream << "  -x, --cluster-filename	Write results of hierarchical clustering to specified file (overwrite default filename)." << endl;
			stream << endl;
			stream << "  --pcoa                 Perform PCoA on resulting dissimilarity matrix (pcoa.txt)." << endl;
			stream << "  -y, --pcoa-filename    Write results of PCoA to specified file (overwrite default filename)." << endl;
			stream << endl;
			stream << "  --linear-regression    Perform linear regression against two dissimilarity matrices." << endl;
			stream << "  -1, --lr-matrix-1			Filename of first dissimilarity matrix." << endl;
			stream << "  -2, --lr-matrix-2			Filename of second dissimilarity matrix." << endl;
			stream << "  -l, --lr-filename      Write resulst of linear regression to file (default = linReg.txt)." << endl;
						
      return 1;
    }

		Log::Inst().Write("Chameleon initialized successfully.");

		if(bShowVersion)
		{
			stream << "Chameleon, version 1.0" << endl;
			return 0;
		}

		if(bShowContactInfo)
		{
			stream << "Comments and suggests can be sent to Donovan Parks (parks@cs.dal.ca) or Rob Beiko (beiko@cs.dal.ca)." << endl;
			return 0;
		}

		int numCores = numCoresStr.toInt();
		if(numCores > 0)
		{
			#ifdef USE_OMP
				omp_set_num_threads(numCores);
			#endif
		}

		if(bExecuteUnitTests)
		{
			ExecuteUnitTests();
			return 0;
		}

		if(bExecuteSandbox)
		{
			ExecuteSandbox();
			return 0;
		}

		// perform linear regression between matrices
		if(bLinearRegression)
		{
			Log::Inst().Write("Performing linear regression.");

			Matrix xMatrix;
			MatrixSystem::ReadFromFile(lrMatrix1, xMatrix);

			Matrix yMatrix;
			MatrixSystem::ReadFromFile(lrMatrix2, yMatrix);

			QList<double> x, y;
			for(int r = 0; r < xMatrix.size(); ++r)
			{
				for(int c = r+1; c < xMatrix[0].size(); ++c)
				{
					x.append(xMatrix.at(r).at(c));
					y.append(yMatrix.at(r).at(c));
				}
			}

			LinearRegression linearRegression;
			LinearRegression::RESULTS results;
			linearRegression.LeastSquaresEstimate(x, y, results);

			QFile file(lrResultsFilename);
			if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				Log::Inst().Warning("Unable to open linear regression file: " + lrResultsFilename);
				return -1;
			}

			QTextStream out(&file);
			out << "R^2: " << results.cod << endl;
			out << "Slope: " << results.slope << endl;
			out << "Intercept: " << results.offset <<endl;
			out << "Standard deviation of residuals: " << results.sd << endl;

			file.close();

			return 0;
		}

		// create split system
		SplitSystemPtr splitSystem(new SplitSystem());
		splitSystem->LoadData(phylogenyFile, samplesFile, "", bImplicitlyRooted);
		splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

		if(bShowCountTable)
		{
			QHash<QString, uint> countMap = splitSystem->GetSamples()->GetSequences()->GetSequenceCounts(bWeighted);

			QHashIterator<QString, uint> iter(countMap);
			while(iter.hasNext())
			{
				iter.next();
				stream << iter.key() << ": " << iter.value() << endl;
			}

			return 0;
		}

		if(!splitSystem->IsOutgroupMonophyletic())
		{
			stream << "Warning: specified outgroup is not monophyletic." << endl;
			stream << "Splits which induce subsets which both contain outgroups will be ignored." << endl;
		}

		// determine tree type
		UniSplit::SPLITS_TO_CONSIDER splitSet;
		if(splitsToConsider == "COMMON_SPLIT_SET")
			splitSet = UniSplit::COMMON_SPLIT_SET;
		else if(splitsToConsider == "COMPLETE_LINEAGE")
			splitSet = UniSplit::COMPLETE_LINEAGE;
		else if(splitsToConsider == "ALL_SPLITS") 
			splitSet = UniSplit::ALL_SPLITS;
		else if(splitsToConsider == "NORMALIZED_WEIGHTED_UNIFRAC")
			splitSet = UniSplit::NORMALIZED_WEIGHTED_UNIFRAC;
		else
		{
			stream << "Error: unrecognized value given to splits-to-consider parameter." << endl;
			exit(0);
		}
	
		// run UniSplit
		UniSplitPtr uniSplit(new UniSplit(splitSystem));

		if(!bWeighted)
			uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
		else
		{
			if(bNormalized)
				uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
			else
				uniSplit->SetMeasureType(UniSplit::WEIGHTED);
		}
		uniSplit->SetSplitsToConsider(splitSet);

		// calculate dissimilarity matrix
		Matrix dissimilarityMatrix = uniSplit->Run();
		StringUtils::WriteMatrix(outputDissFile, dissimilarityMatrix, splitSystem->GetSamples()->GetActiveSampleNames());

		// run clustering methods
		if(bClusteringUPGMA)
		{
			uniSplit->Cluster(Cluster::AVERAGE_LINKAGE);

			NewickIO newickIO;
			if(clusterFilename.isEmpty())
				newickIO.Write(*uniSplit->GetClusterTree(), "upgma.tre");
			else
				newickIO.Write(*uniSplit->GetClusterTree(), clusterFilename);
		}

		if(bClusteringSL)
		{
			uniSplit->Cluster(Cluster::SINGLE_LINKAGE);

			NewickIO newickIO;
			if(clusterFilename.isEmpty())
				newickIO.Write(*uniSplit->GetClusterTree(), "sl.tre");
			else
				newickIO.Write(*uniSplit->GetClusterTree(), clusterFilename);
		}

		if(bClusteringCL)
		{
			uniSplit->Cluster(Cluster::COMPLETE_LINKAGE);

			NewickIO newickIO;
			if(clusterFilename.isEmpty())
				newickIO.Write(*uniSplit->GetClusterTree(), "cl.tre");
			else
				newickIO.Write(*uniSplit->GetClusterTree(), clusterFilename);
		}

		if(bClusteringNJ)
		{
			uniSplit->Cluster(Cluster::NEIGHBOUR_JOINING);

			NewickIO newickIO;
			if(clusterFilename.isEmpty())
				newickIO.Write(*uniSplit->GetClusterTree(), "nj.tre");
			else
				newickIO.Write(*uniSplit->GetClusterTree(), clusterFilename);
		}

		// run PCoA
		if(bPCoA)
		{
			PCoA pcoa;
			pcoa.Project(dissimilarityMatrix);
		
			if(pcoaFilename.isEmpty())
				pcoa.WriteToFile("pcoa.txt");
			else
				pcoa.WriteToFile(pcoaFilename);
		}

		// run jackknife analysis
		if(numJackknifeSeq != "0")
		{
			uniSplit->Jackknife(Cluster::AVERAGE_LINKAGE, numJackknifeIter.toInt(), numJackknifeSeq.toInt());
			NewickIO newickIO;
			newickIO.Write(*uniSplit->GetClusterTree(), outputJackknifeFile);
		}

		// run permutation test
		if(numPermutations != "0")
		{
			Matrix signMatrix;
			uniSplit->SignificanceTest(numPermutations.toInt(), signMatrix);
			StringUtils::WriteMatrix(outputSignFile, signMatrix, splitSystem->GetSamples()->GetActiveSampleNames());
		}
	}
	else
	{
		/*
		QPixmap pixmap("splash.png");
		QSplashScreen splash(pixmap);
		splash.show();
		splash.setMask(pixmap.mask());
		splash.showMessage("This is a message", Qt::AlignHCenter|Qt::AlignVCenter, Qt::black);
		app.processEvents();

		Sleep(20000);
		*/


		GUI w;
		w.show();
		
		w.LoadData("../Examples/Hydrocarbon/RandomTree_2k.tre", "", "../Examples/Hydrocarbon/Hydrocarbon.env", "../Examples/Hydrocarbon/Hydrocarbon.metadata.txt", true, true);
		//w.LoadData("../Examples/RandomTrees/RandomTree_2k.tre", "", "../Examples/RandomTrees/RandomTree_2k.env", "", true, false);
		//w.LoadData("../Examples/CostelloBody/Costello16S.97.final.tre", "", "../Examples/CostelloBody/Costello16S.97.orgAgg.env", "../Examples/CostelloBody/Costello.txt", true, false);
		//w.LoadData("../Examples/RandomTrees/RandomTree_2k.tre", "", "../Examples/RandomTrees/RandomTree_2k.env", "", true, false);
		//w.LoadData("../Examples/CostelloBody/Costello16S.97.final.tre", "", "../Examples/CostelloBody/Costello16S.97.final.env", "../Examples/CostelloBody/Costello.txt", true, false);
		//w.LoadData("../Examples/UbedaMouse/UbedaMouse.derep.tre", "", "../Examples/UbedaMouse/UbedaMouse.derep.env", "../Examples/UbedaMouse/UbedaMouse.txt", true, true);
		//w.LoadData("../Examples/LeyMouse/LeyMouse.tre", "", "../Examples/LeyMouse/LeyMouse.env", "../Examples/LeyMouse/LeyMouse.txt", true, true);
		//w.LoadData("../Examples/salivary/salivary.final.tre", "", "../Examples/salivary/salivary_combined.env", "../Examples/salivary/salivary_combined.txt", true);
		//w.LoadData("../Examples/salivary/salivary.final.tre", "", "../Examples/salivary/salivary.env", "../Examples/salivary/salivary.txt", true);
		//w.LoadData("../Examples/ProjectedTree.tre", "", "../Examples/Ley.env", "../Examples/Ley.dat", true);
		//w.LoadData("../Examples/GreenGenesCore-May09.tre", "", "../Examples/Ley.env", "../Examples/Ley.dat", true, true);
		//w.LoadData("../Examples/ssDNA.tre", "", "../Examples/ssDNA.env", "../Examples/ssDNA.dat", false);
		//w.LoadData("../Examples/ToyExample.tre", "", "../Examples/ToyExample.env", "../Examples/ToyExample.dat", true, true);
		//w.LoadData("../Examples/TestCase0.tre", "", "../Examples/TestCase0.env", "", true, true);
		//w.LoadData("../Examples/TestCase0_simple.tre", "", "../Examples/TestCase0_simple.env", "", true, true);
		//w.LoadData("", "../Examples/SimpleDissimilarityMatrix.dst", "../Examples/SimpleDissimilarityMatrix.env", "", false);
		//w.LoadData("../Examples/Proteorhodopsin/proteorhodopsin.bestTree.spectral.all.tre", "", "../Examples/Proteorhodopsin/proteorhodopsin.aa.spectral.all.env", "../Examples/Proteorhodopsin/proteorhodopsin.spectral.all.tsv", true, true);
		//w.LoadData("../Examples/Proteorhodopsin/proteorhodopsin.bestTree.aa.tre", "", "../Examples/Proteorhodopsin/proteorhodopsin.aa.smp", "../Examples/Proteorhodopsin/proteorhodopsin.tsv", true, true);
		//w.LoadData("../Examples/Conor/K02112_RefQin.tree", "", "../Examples/Conor/K02112_RefQin_sampleIdMap.txt", "../Examples/Conor/K02112_RefQin_sampleCategories.txt", true, true);
		//w.LoadData("", "../Examples/Matrix.dst", "../Examples/Matrix.smp", "../Examples/Matrix.txt", true, false);
		//w.LoadData("", "../Examples/Enterotype/EnteroGenusDiss.dst", "../Examples/Enterotype/Enterotype.RITA.Arumugam.sample.env", "../Examples/Enterotype/Enterotypes.RITA.Arumugam.metadata.tsv", true, false);
		//w.LoadData("", "../Examples/Enterotype/EnteroGenusDiss.dst", "../Examples/Enterotype/Enterotype.RITA.sample.env", "../Examples/Enterotype/Enterotypes.RITA.metadata.tsv", true, false);
		//w.LoadData("", "../Examples/Enterotype/EnteroGenusDiss.Euclidean.Arumugam.dst", "../Examples/Enterotype/Enterotypes.Arumugam.sample.env", "../Examples/Enterotype/Enterotypes.Arumugam.metadata.tsv", true, false);
		//w.LoadData("", "../Examples/Enterotype/EnteroGenusDiss.Arumugam.JSD.dst", "../Examples/Enterotype/Enterotypes.Arumugam.sample.env", "../Examples/Enterotype/Enterotypes.Arumugam.metadata.tsv", true, false);
		//w.LoadData("", "../Examples/SimpleDissimilarityMatrix.dst", "", "../Examples/SimpleDissimilarityMatrix.txt", false, false);
		//w.LoadData("", "../Examples/PneumococcusMLST/Serotype14/Serotype14.UPGMA.results.manhattan.phylo.dis", "", "../Examples/PneumococcusMLST/Serotype14/Serotype14.metadata.txt", false, false);
	//	w.LoadData("", "../Examples/PneumococcusMLST/Combined/Combined.Seq.NNet.results.manhattan.phylo.dis", "", "../Examples/PneumococcusMLST/Combined/Combined.metadata.txt", false, false);
		//w.LoadData("", "../Examples/PneumococcusMLST/Combined/Combined.Seq.NJ.results.manhattan.phylo.dis", "", "../Examples/PneumococcusMLST/Combined/Combined.metadata.txt", false, false);
		//w.LoadData("", "../Examples/PneumococcusMLST/Combined/Combined.profile.dst", "", "../Examples/PneumococcusMLST/Combined/Combined.metadata.txt", false, false);

		Log::Inst().Write("Initialized successfully.");

		//splash.finish(&w);
		return app.exec();
	}

	Log::Inst().Write("Program closed successfully.");
	return 0;
}
