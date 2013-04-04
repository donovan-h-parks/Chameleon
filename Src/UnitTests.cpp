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

#include <QtTest/QtTest>

#include "UnitTests.hpp"

#include "Log.hpp"

#include "NewickIO.hpp"
#include "SplitSystem.hpp"
#include "UniSplit.hpp"
#include "Cluster.hpp"
#include "StatsUtils.hpp"
#include "LinearRegression.hpp"
#include "VisualMatrix.hpp"
#include "BoxPlot.hpp"

#include "PCoA.hpp"

#include "Legends.hpp"
#include "ColorMaps.hpp"

// -- Execute unit tests --

void ExecuteUnitTests()
{
	UnitTests unitTests;
	QTest::qExec(&unitTests);
}


// --- Test cases ---

void UnitTests::TestBoxPlotStats1()
{
	Matrix dissVectors(1);
	dissVectors[0] << 6 << 47 << 49 << 15 << 43 << 41 << 7 << 39 << 43 << 41 << 36;

	QStringList labels;
	labels << "test";

	BoxPlot boxPlot;
	boxPlot.SetData(dissVectors, labels);
	QList<BoxPlot::BoxPlotData> boxPlotData = boxPlot.GetBoxPlotData();

	QCOMPARE(boxPlotData.at(0).median, 41.0);
	QCOMPARE(boxPlotData.at(0).lowerQuartile, 15.0);
	QCOMPARE(boxPlotData.at(0).upperQuartile, 43.0);
}
	
void UnitTests::TestBoxPlotStats2()
{
	Matrix dissVectors(1);
	dissVectors[0] << 34 << 47 << 1 << 15 << 57 << 24 << 20 << 11 << 19 << 50 << 28 << 37;

	QStringList labels;
	labels << "test";

	BoxPlot boxPlot;
	boxPlot.SetData(dissVectors, labels);
	QList<BoxPlot::BoxPlotData> boxPlotData = boxPlot.GetBoxPlotData();

	QCOMPARE(boxPlotData.at(0).median, 26.0);
	QCOMPARE(boxPlotData.at(0).lowerQuartile, 17.0);
	QCOMPARE(boxPlotData.at(0).upperQuartile, 42.0);
	QCOMPARE(boxPlotData.at(0).iqr, 25.0);
}

void UnitTests::SandboxTesting()
{
	Log::Inst().Debug("UnitTests::SandboxTesting()");

	QStringList labels;

	int size = 1000;
	Matrix dist;
	dist.reserve(size);
	dist.resize(size);
	for(int i = 0; i < size; ++i)
	{
		dist[i].reserve(size);
		dist[i].resize(size);
	}

	for(int i = 0; i < size; ++i)
	{
		labels.append(QString::number(i));
		dist[i][i] = 0;
		for(int j = i+1; j < size; ++j)
			dist[i][j] = dist[j][i] = rand();
	}

	Tree<VisualNode> tree;
	Cluster::UPGMA(dist, labels, tree);
}

void UnitTests::TestMissingSampleSeq()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	bool bLoaded = splitSystem->LoadData("../TestCases/MissingSeqsInSampleFile.tre", "../TestCases/MissingSeqsInSampleFile.env", "", true);

	QVERIFY(bLoaded == true);
}

void UnitTests::TestNewickIO()
{
	NewickIO newickIO;

	Tree<VisualNode> tree;
	newickIO.Read(tree, "../TestCases/TestNewickIO.tre");
	newickIO.Write(tree, "../TestCases/TestNewickIO.tre");

	QFile file("../TestCases/TestNewickIO.tre");
	QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));

	QTextStream textStream(&file);
	QString newickStr = textStream.readLine();

	QVERIFY(newickStr == "((raccoon:19.1996,bear:6.80041)50:0.846,((sea_lion:11.997,seal:12.003)100:7.52973,((monkey:100.859,cat:47.1407)80:20.592,weasel:18.8795)75:2.0946)50:3.87382,dog:25.4615);");

	file.close();
}

void UnitTests::TestSplitSystemFromForest()
{
	/*

	// Implementation not complete.

	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/Forest.tre", "../TestCases/Forest.env", "", true);

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	Matrix distMatrix = uniSplit->Run(false, false);	
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.9);
	QCOMPARE(distMatrix.at(1).at(0), 0.9);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	*/
}

void UnitTests::TestCompleteLinkage()
{
	Matrix dist(4);
	dist[0] << 0 << 3 << 4 << 5;
	dist[1] << 3 << 0 << 2 << 6;
	dist[2] << 4 << 2 << 0 << 7;
	dist[3] << 5 << 6 << 7 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D";

	Tree<VisualNode> tree;
	Cluster::CompleteLinkage(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);

	QVERIFY(newickStr.compare("((A:4,(B:2,C:2)0:2)0:3,D:7);") == 0);
}

void UnitTests::TestSingleLinkage()
{
	Matrix dist(4);
	dist[0] << 0 << 3 << 4 << 5;
	dist[1] << 3 << 0 << 2 << 6;
	dist[2] << 4 << 2 << 0 << 7;
	dist[3] << 5 << 6 << 7 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D";

	Tree<VisualNode> tree;
	Cluster::SingleLinkage(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);

	QVERIFY(newickStr.compare("((A:3,(B:2,C:2)0:1)0:2,D:5);") == 0);
}

void UnitTests::TestUPGMA()
{
	Matrix dist(4);
	dist[0] << 0 << 3 << 4 << 5;
	dist[1] << 3 << 0 << 2 << 6;
	dist[2] << 4 << 2 << 0 << 7;
	dist[3] << 5 << 6 << 7 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D";

	Tree<VisualNode> tree;
	Cluster::UPGMA(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);

	QVERIFY(newickStr == "((A:3.5,(B:2,C:2)0:1.5)0:2.5,D:6);");
}

void UnitTests::TestUPGMA2()
{
	Matrix dist(6);
	dist[0] << 0 << 3 << 4 << 5 << 8 << 1;
	dist[1] << 3 << 0 << 2 << 6 << 7 << 12;
	dist[2] << 4 << 2 << 0 << 7 << 13 << 5;
	dist[3] << 5 << 6 << 7 << 0 << 9 << 10;
	dist[4] << 8 << 7 << 13 << 9 << 0 << 14;
	dist[5] << 1 << 12 << 5 << 10 << 14 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D" << "E" << "F";

	Tree<VisualNode> tree;
	Cluster::UPGMA(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);

	QVERIFY(newickStr == "((((A:1,F:1)0:5,(B:2,C:2)0:4)0:1,D:7)0:3.2,E:10.2);");
}

void UnitTests::TestUPGMA3()
{
	Matrix dist(4);
	dist[0] << 0 << 0.3411 << 0.3559 << 0.4203;
	dist[1] << 0.3411 << 0 << 0.2265 << 0.2362;
	dist[2] << 0.3559 << 0.2265 << 0 << 0.2101;
	dist[3] << 0.4203 << 0.2362 << 0.2101 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D";

	Tree<VisualNode> tree;
	Cluster::UPGMA(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);

	QVERIFY(newickStr == "(A:0.372433,(B:0.23135,(C:0.2101,D:0.2101)0:0.02125)0:0.141083);");
}

void UnitTests::TestNJ()
{
	Matrix dist(6);
	dist[0] << 0 << 5 << 4 << 7 << 6 << 8;
	dist[1] << 5 << 0 << 7 << 10 << 9 << 11;
	dist[2] << 4 << 7 << 0 << 7 << 6 << 8;
	dist[3] << 7 << 10 << 7 << 0 << 5 << 9;
	dist[4] << 6 << 9 << 6 << 5 << 0 << 8;
	dist[5] << 8 << 11 << 8 << 9 << 8 << 0;

	QStringList labels;
	labels << "A" << "B" << "C" << "D" << "E" << "F";

	Tree<VisualNode> tree;
	Cluster::NJ(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);
	QVERIFY(newickStr == "((((A:1,B:4)0:1,C:2)0:1,F:5)0:1,D:3,E:2);");
}

void UnitTests::TestNJ2()
{
	Matrix dist(5);
	dist[0] << 0 << 0.1890 << 0.1100 << 0.1130 << 0.2150;
	dist[1] << 0.1890 << 0 << 0.1790 << 0.1920 << 0.2110;
	dist[2] << 0.1100 << 0.1790 << 0 << 0.0940 << 0.2050;
	dist[3] << 0.1130 << 0.1920 << 0.0940 << 0 << 0.2140;
	dist[4] << 0.2150 << 0.2110 << 0.2050 << 0.2140 << 0;

	QStringList labels;
	labels << "Gorilla" << "Orangutan" << "Human" << "Chimp" << "Gibbon";

	Tree<VisualNode> tree;
	Cluster::NJ(dist, labels, tree);

	NewickIO newickIO;
	QString newickStr;
	newickIO.CreateNewickStr(tree, newickStr);
	QVERIFY(newickStr == "((Gorilla:0.058,(Orangutan:0.0931667,Gibbon:0.117833)0:0.0385)0:0.0065,Human:0.0435,Chimp:0.0505);");
}

void UnitTests::TestLinearRegression()
{
	QList<double> x;
	QList<double> y;

	x << 0.3 << 0.2 << 0.5 << 0.4 << 0.35 << 0.45;
	y << 0.4 << 0.3 << 0.4 << 0.2 << 0.45 << 0.35;
	LinearRegression linearRegression;
	LinearRegression::RESULTS results;
	linearRegression.LeastSquaresEstimate(x, y, results);

	QCOMPARE(results.cod, 0.010714285714285267);
	QCOMPARE(results.slope, 0.085714285714284022);
	QCOMPARE(results.offset, 0.31857142857142923);
}

void UnitTests::TestSideToSideSort()
{
	VisualMatrix visualMatrix(LegendsPtr(NULL), ColorMapsPtr(NULL), NULL);

	Matrix dissMatrix(4);
	dissMatrix[0] << 0 << 10 << 10.77 << 2.82;
	dissMatrix[1] << 10 << 0 << 2.82 << 7.21;
	dissMatrix[2] << 10.77 << 2.82 << 0 << 8.24;
	dissMatrix[3] << 2.82 << 7.21 << 8.24 << 0;

	QStringList sampleLabels;
	sampleLabels << "5" << "19" << "27" << "37";

	visualMatrix.SetData(dissMatrix, sampleLabels);
	visualMatrix.Sort(VisualMatrix::SIDE_TO_SIDE);

	QStringList sortedLabels = visualMatrix.GetSortedLabels();

	QCOMPARE(QString("5"), sortedLabels.at(0));
	QCOMPARE(QString("37"), sortedLabels.at(1));
	QCOMPARE(QString("19"), sortedLabels.at(2));
	QCOMPARE(QString("27"), sortedLabels.at(3));
}

void UnitTests::TestNeighbourSort()
{
	/*
	VisualMatrix visualMatrix(SystemPtr(NULL), LegendsPtr(NULL), ColorMapsPtr(NULL), NULL);

	Matrix dissMatrix(4);
	dissMatrix[0] << 0 << 1 << 6 << 1;
	dissMatrix[1] << 1 << 0 << 1 << 1;
	dissMatrix[2] << 6 << 1 << 0 << 6;
	dissMatrix[3] << 1 << 1 << 6 << 0;

	QStringList sampleLabels;
	sampleLabels << "A" << "B" << "C" << "D";

	visualMatrix.SetData(dissMatrix, sampleLabels);
	visualMatrix.Sort(VisualMatrix::NEIGHBOURHOOD);

	QStringList sortedLabels = visualMatrix.GetSortedLabels();

	QCOMPARE(QString("5"), sortedLabels.at(0));
	QCOMPARE(QString("37"), sortedLabels.at(1));
	QCOMPARE(QString("19"), sortedLabels.at(2));
	QCOMPARE(QString("27"), sortedLabels.at(3));
	*/
}

void UnitTests::TestSupportTree()
{
	NewickIO newickIO;

	QString newickStr = "(((A:1.0,B:0.5):0.5,C:1.0):1.5,D:2.0);";

	// original tree
	Tree<VisualNode> origTree;
	newickIO.ParseNewickString(origTree, NULL, newickStr, true);

	// support trees (9 in perfect agreement, 1 with no splits appearing in the original tree)
	QList< Tree<VisualNode> > supportTrees;
	Tree<VisualNode> temp;
	for(uint i = 0; i < 9; ++i)
	{
		newickIO.ParseNewickString(temp, NULL, newickStr, true);
		supportTrees.push_back(temp);
	}

	newickIO.ParseNewickString(temp, NULL, "(((C:1.0,D:1.0):2.0,B:1.0):1.0,A:1.0);", true);
	supportTrees.push_back(temp);

	// evaluate support for original tree
	Cluster::SupportTree(origTree, supportTrees);

	// verify results
	QString supportStr;
	newickIO.CreateNewickStr(origTree, supportStr);

	QVERIFY(supportStr == "(((A:1,B:0.5)90:0.5,C:1)90:1.5,D:2);");
}

void UnitTests::TestPCoA1()
{
	Matrix test(3);
	test[0] << 0 << 0.466666667 << 0.266666667;
	test[1] << 0.466666667 << 0 << 0.2;
	test[2] << 0.266666667 << 0.2 << 0;

	PCoA pcoa;
	pcoa.Project(test);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(0), -0.2444444446666);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(0), 0.2222222223333);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(0), 0.02222222233333);

	QCOMPARE(pcoa.GetEigenvalues().at(0), 0.10962962979259253);

	// other terms are small and numerically unstable
}

void UnitTests::TestPCoA2()
{
	Matrix test(4);
  test[0] <<          0 <<   0.341124 <<   0.355898 <<    0.42025;
  test[1] <<   0.341124 <<          0 <<   0.226498 <<    0.23623;
  test[2] <<   0.355898 <<   0.226498 <<          0 <<   0.210076;
  test[3] <<    0.42025  <<   0.23623 <<   0.210076  <<         0;

	PCoA pcoa;
	pcoa.Project(test);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(0), -0.26092865126115938);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(1), -0.020286129157634523);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(2), -0.027104663802232330);

	QCOMPARE(pcoa.GetProjectedData().at(1).at(0), 0.038068027417227153);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(1), 0.13337862335689821);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(2), 0.030806590284871496);

	QCOMPARE(pcoa.GetProjectedData().at(2).at(0), 0.069062991966193449);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(1), -0.082878317381072888);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(2), 0.090586116539785766);

	QCOMPARE(pcoa.GetProjectedData().at(3).at(0), 0.15379763187773879);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(1), -0.030214176818190715);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(2), -0.094288043022424869);

	QCOMPARE(pcoa.GetEigenvalues().at(0), 0.097956344190929440);
	QCOMPARE(pcoa.GetEigenvalues().at(1), 0.025983096177500279);
	QCOMPARE(pcoa.GetEigenvalues().at(2), 0.018779788371570277);

	// other terms are small and numerically unstable
}

void UnitTests::TestPCoA3()
{
	Matrix test(5);
  test[0] <<   0 <<  167 <<  169 <<  159 <<  180;
  test[1] << 167 <<    0 <<   96 <<   79 <<  163;
  test[2] << 169 <<   96 <<    0 <<  141 <<  166;
  test[3] << 159 <<   79 <<  141 <<    0 <<  172;
  test[4] << 180 <<  163 <<  166 <<  172 <<    0;

	PCoA pcoa;
	pcoa.Project(test);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(0), 66.180265767533953);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(1), 94.754495080664839);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(2), 11.215357673511061);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(3), -3.8799274738122080);

	QCOMPARE(pcoa.GetProjectedData().at(1).at(0), -59.739859203966866);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(1), -9.8771465595611865);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(2), -8.4749507419849497);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(3), -30.292679116448156);

	QCOMPARE(pcoa.GetProjectedData().at(2).at(0), -41.027787044024066);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(1), -18.311668416284661);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(2), 74.160044267091521);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(3), 14.048890503711354);

	QCOMPARE(pcoa.GetProjectedData().at(3).at(0), -48.268436184946324);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(1), 15.991476874507002);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(2), -62.274859884897857);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(3), 20.163148611965674);

	QCOMPARE(pcoa.GetProjectedData().at(4).at(0), 82.855816665403211);
	QCOMPARE(pcoa.GetProjectedData().at(4).at(1), -82.557156979325953);
	QCOMPARE(pcoa.GetProjectedData().at(4).at(2), -14.625591313719825);
	QCOMPARE(pcoa.GetProjectedData().at(4).at(3), -0.039432525416653638);

	QCOMPARE(pcoa.GetEigenvalues().at(0), 18826.885951532149);
	QCOMPARE(pcoa.GetEigenvalues().at(1), 16482.701063475710);
	QCOMPARE(pcoa.GetEigenvalues().at(2), 9789.3872984804548);
	QCOMPARE(pcoa.GetEigenvalues().at(3), 1536.6256865116814);
}

void UnitTests::TestPCoA4()
{
	Matrix test(4);
	test[0] << 0 << 1 << 0.3 << 1.0440306508910551;
	test[1] << 1 << 0 << 1.0440306508910551 << 0.3;
	test[2] << 0.3 << 1.0440306508910551 << 0 << 1;
	test[3] << 1.0440306508910551 << 0.3 << 1 << 0;

	PCoA pcoa;
	pcoa.Project(test);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(0), -0.5);
	QCOMPARE(pcoa.GetProjectedData().at(0).at(1), 0.15);

	QCOMPARE(pcoa.GetProjectedData().at(1).at(0), 0.5);
	QCOMPARE(pcoa.GetProjectedData().at(1).at(1), 0.15);

	QCOMPARE(pcoa.GetProjectedData().at(2).at(0), -0.5);
	QCOMPARE(pcoa.GetProjectedData().at(2).at(1), -0.15);

	QCOMPARE(pcoa.GetProjectedData().at(3).at(0), 0.5);
	QCOMPARE(pcoa.GetProjectedData().at(3).at(1), -0.15);
}

void UnitTests::TestPolyphyleticOutgroup()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/PolyphyleticTree.tre", "../TestCases/PolyphyleticTree.env", "", false);	
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());
	
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == false);
}

void UnitTests::Test1_Sample_Counts()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.nex", "../TestCases/TestCase1Rooted.env", "");	

	QHash<QString, uint> sampleCounts = splitSystem->GetSamples()->GetSequences()->GetSequenceCounts(true);

	QVERIFY(sampleCounts.value("com1") == 3);
	QVERIFY(sampleCounts.value("com2") == 3);
	QVERIFY(sampleCounts.value("com3") == 3);
}

void UnitTests::Test2_Sample_Counts()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2.tre", "../TestCases/TestCase2.env", "");	
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	QHash<QString, uint> sampleCounts = splitSystem->GetSamples()->GetSequences()->GetSequenceCounts(true);

	QVERIFY(sampleCounts.value("com1") == 200);
	QVERIFY(sampleCounts.value("com2") == 200);
}

void UnitTests::Test3_Sample_Counts()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3.tre", "../TestCases/TestCase3.env", "");	
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	QHash<QString, uint> sampleCounts = splitSystem->GetSamples()->GetSequences()->GetSequenceCounts(true);

	QVERIFY(sampleCounts.value("A") == 55);
	QVERIFY(sampleCounts.value("B") == 50);
	QVERIFY(sampleCounts.value("C") == 42);
	QVERIFY(sampleCounts.value("D") == 49);
}

void UnitTests::Test4_Sample_Counts()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase4.tre", "../TestCases/TestCase4.env", "");	
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	QHash<QString, uint> sampleCounts = splitSystem->GetSamples()->GetSequences()->GetSequenceCounts(true);

	QVERIFY(sampleCounts.value("sample1") == 17);
	QVERIFY(sampleCounts.value("sample2") == 10);
}

void UnitTests::Qualitative_MRCA_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 1.0);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 1.0);
	QCOMPARE(distMatrix.at(2).at(0), 1.0);
	QCOMPARE(distMatrix.at(2).at(1), 1.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteTree_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();	
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.0/4.0);
	QCOMPARE(distMatrix.at(0).at(2), 3.0/4.0);
	QCOMPARE(distMatrix.at(1).at(0), 3.0/4.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(0), 3.0/4.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteLineage_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 1.0);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/3.0);
	QCOMPARE(distMatrix.at(2).at(0), 1.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/3.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_MRCA_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 1.0);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 1.0);
	QCOMPARE(distMatrix.at(2).at(0), 1.0);
	QCOMPARE(distMatrix.at(2).at(1), 1.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteTree_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.0/4.0);
	QCOMPARE(distMatrix.at(0).at(2), 3.0/4.0);
	QCOMPARE(distMatrix.at(1).at(0), 3.0/4.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(0), 3.0/4.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteLineage_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 1.0);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/3.0);
	QCOMPARE(distMatrix.at(2).at(0), 1.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/3.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_UniFrac_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 1.0);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(0), 1.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/4.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_Unnormalized_Test0()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase0.tre", "../TestCases/TestCase0.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.0);
	QCOMPARE(distMatrix.at(0).at(2), 3.0);
	QCOMPARE(distMatrix.at(1).at(0), 3.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0);
	QCOMPARE(distMatrix.at(2).at(0), 3.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test1_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1.tre", "../TestCases/TestCase1.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545177457745);
	QCOMPARE(distMatrix.at(0).at(2), 0.74000000110268593);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545177457745);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(0), 0.74000000110268593);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test1_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.tre", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545177457745);
	QCOMPARE(distMatrix.at(0).at(2), 0.74000000110268593);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545177457745);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(0), 0.74000000110268593);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test1_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.nex", "../TestCases/TestCase1Rooted.env", "");
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545454545453);
	QCOMPARE(distMatrix.at(0).at(2), 0.73999999999999999);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545454545453);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(0), 0.73999999999999999);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test1_Rooted_Network_TreeBlock()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted_TreeBlock.nex", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545454545453);
	QCOMPARE(distMatrix.at(0).at(2), 0.73999999999999999);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545454545453);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(0), 0.73999999999999999);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest1_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1.tre", "../TestCases/TestCase1.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.34482758279610759);
	QCOMPARE(distMatrix.at(0).at(2), 0.63793103530223383);
	QCOMPARE(distMatrix.at(1).at(0), 0.34482758279610759);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.56896552182601123);
	QCOMPARE(distMatrix.at(2).at(0), 0.63793103530223383);
	QCOMPARE(distMatrix.at(2).at(1), 0.56896552182601123);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest1_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.tre", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.34482758279610759);
	QCOMPARE(distMatrix.at(0).at(2), 0.63793103530223383);
	QCOMPARE(distMatrix.at(1).at(0), 0.34482758279610759);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.56896552182601112);
	QCOMPARE(distMatrix.at(2).at(0), 0.63793103530223383);
	QCOMPARE(distMatrix.at(2).at(1), 0.56896552182601112);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest1_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.nex", "../TestCases/TestCase1Rooted.env", "");
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.34482758620689652);
	QCOMPARE(distMatrix.at(0).at(2), 0.63793103448275867);
	QCOMPARE(distMatrix.at(1).at(0), 0.34482758620689652);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.56896551724137934);
	QCOMPARE(distMatrix.at(2).at(0), 0.63793103448275867);
	QCOMPARE(distMatrix.at(2).at(1), 0.56896551724137934);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest1_Rooted_Network_TreeBlock()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted_TreeBlock.nex", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.34482758620689652);
	QCOMPARE(distMatrix.at(0).at(2), 0.63793103448275867);
	QCOMPARE(distMatrix.at(1).at(0), 0.34482758620689652);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.56896551724137934);
	QCOMPARE(distMatrix.at(2).at(0), 0.63793103448275867);
	QCOMPARE(distMatrix.at(2).at(1), 0.56896551724137934);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest1_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1.tre", "../TestCases/TestCase1.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));
	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545177457745);
	QCOMPARE(distMatrix.at(0).at(2), 0.74000000110268593);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545177457745);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(0), 0.74000000110268593);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest1_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.tre", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545177457750);
	QCOMPARE(distMatrix.at(0).at(2), 0.74000000110268593);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545177457750);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(0), 0.74000000110268593);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130688299524);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest1_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted.nex", "../TestCases/TestCase1Rooted.env", "");
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545454545453);
	QCOMPARE(distMatrix.at(0).at(2), 0.73999999999999999);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545454545453);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(0), 0.73999999999999999);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest1_Rooted_Network_TreeBlock()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase1Rooted_TreeBlock.nex", "../TestCases/TestCase1Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.45454545454545453);
	QCOMPARE(distMatrix.at(0).at(2), 0.73999999999999999);
	QCOMPARE(distMatrix.at(1).at(0), 0.45454545454545453);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(0), 0.73999999999999999);
	QCOMPARE(distMatrix.at(2).at(1), 0.71739130434782605);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test2_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2.tre", "../TestCases/TestCase2.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::MRCA_Test2_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.tre", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::MRCA_Test2_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.nex", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteTreeTest2_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2.tre", "../TestCases/TestCase2.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteTreeTest2_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.tre", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteTreeTest2_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.nex", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteLineageTest2_Implicitly_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2.tre", "../TestCases/TestCase2.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263059);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteLineageTest2_Rooted_Tree()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.tre", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472612263070);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteLineageTest2_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase2Rooted.nex", "../TestCases/TestCase2Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(0), 0.50112472543467323);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteTreeTest3_Implicitly_Rooted_Tree_Weighted_Normalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3.tre", "../TestCases/TestCase3.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.51988720856664794);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.56245570936245548);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.73569820314972811);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.51988720856664794);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.44245310848139691);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.50167884460097401);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.56245570936245548);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.44245310848139691);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.45797168824764994);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.73569820314972811);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.50167884460097401);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.45797168824764994);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::CompleteTreeTest3_Implicitly_Rooted_Tree_Weighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3.tre", "../TestCases/TestCase3.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.080459036686489446);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.087047043682587047);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.11385848265166520);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.080459036686489446);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.068475142878596670);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.077641065018453484);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.087047043682587047);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.068475142878596670);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.070876836857907369);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.11385848265166520);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.077641065018453484);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.070876836857907369);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::CompleteTreeTest3_Rooted_Tree_Weighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3Rooted.tre", "../TestCases/TestCase3Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.080459036686489419);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.087047043682587047);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.11385848265166519);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.080459036686489419);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.068475142878596656);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.077641065018453456);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.087047043682587047);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.068475142878596656);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.070876836857907355);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.11385848265166519);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.077641065018453456);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.070876836857907355);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::CompleteTreeTest3_Rooted_Network_Weighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3Rooted.nex", "../TestCases/TestCase3Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.0804590363636);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.0870470432900);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.1138584823747);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.0804590363636);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.0684751428571);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.0776410653061);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.0870470432900);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.0684751428571);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.0708768367347);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.1138584823747);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.0776410653061);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.0708768367347);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::CompleteLineageTest3_Implicitly_Rooted_Tree_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3.tre", "../TestCases/TestCase3.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.51222634167346048);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.49845715625030729);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.57332678414666249);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.51222634167346048);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.59567092110128794);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.52184666883521436);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.49845715625030729);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.59567092110128794);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.47230961841172248);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.57332678414666249);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.52184666883521436);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.47230961841172248);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}


void UnitTests::CompleteLineageTest3_Rooted_Network_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3Rooted.nex", "../TestCases/TestCase3Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.5122263432566);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.4984571564206);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.5733267862988);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.5122263432566);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.5956709224655);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.5218466725624);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.4984571564206);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.5956709224655);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.4723096195303);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.5733267862988);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.5218466725624);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.4723096195303);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::UniFracTest3_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3.tre", "../TestCases/TestCase3.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.34112409423029977);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.35589827195933887);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.42025001028131065);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.34112409423029977);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.22649825534812917);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.23623008599679307);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.35589827195933887);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.22649825534812917);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.21007592174560324);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.42025001028131065);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.23623008599679307);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.21007592174560324);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::UniFracTest3_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3Rooted.tre", "../TestCases/TestCase3Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();		

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.34112409423029960);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.35589827195933887);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.42025001028131059);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.34112409423029960);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.22649825534812909);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.23623008599679296);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.35589827195933887);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.22649825534812909);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.21007592174560313);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.42025001028131059);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.23623008599679296);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.21007592174560313);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::UniFracTest3_Rooted_Network_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase3Rooted.nex", "../TestCases/TestCase3Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();		

	QStringList labels = splitSystem->GetSamples()->GetActiveSampleNames();
	Matrix sortedMatrix = StatsUtils::AlphabeticallyOrderMatrix(distMatrix, labels);

	QCOMPARE(sortedMatrix.at(0).at(0), 0.0);
	QCOMPARE(sortedMatrix.at(0).at(1), 0.3411240957151);
	QCOMPARE(sortedMatrix.at(0).at(2), 0.3558982732359);
	QCOMPARE(sortedMatrix.at(0).at(3), 0.4202500121583);
	QCOMPARE(sortedMatrix.at(1).at(0), 0.3411240957151);
	QCOMPARE(sortedMatrix.at(1).at(1), 0.0);
	QCOMPARE(sortedMatrix.at(1).at(2), 0.2264982569133);
	QCOMPARE(sortedMatrix.at(1).at(3), 0.2362300883617);
	QCOMPARE(sortedMatrix.at(2).at(0), 0.3558982732359);
	QCOMPARE(sortedMatrix.at(2).at(1), 0.2264982569133);
	QCOMPARE(sortedMatrix.at(2).at(2), 0.0);
	QCOMPARE(sortedMatrix.at(2).at(3), 0.2100759226753);
	QCOMPARE(sortedMatrix.at(3).at(0), 0.4202500121583);
	QCOMPARE(sortedMatrix.at(3).at(1), 0.2362300883617);
	QCOMPARE(sortedMatrix.at(3).at(2), 0.2100759226753);
	QCOMPARE(sortedMatrix.at(3).at(3), 0.0);
}

void UnitTests::UniFracTest4_Implicitly_Rooted_Tree_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase4.tre", "../TestCases/TestCase4.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.85507246451927721);
	QCOMPARE(distMatrix.at(1).at(0), 0.85507246451927721);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::UniFracTest4_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase4.tre", "../TestCases/TestCase4.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.75457481225526291);
	QCOMPARE(distMatrix.at(1).at(0), 0.75457481225526291);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::UniFracTest4_Rooted_Network_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase4Rooted.nex", "../TestCases/TestCase4Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();	

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.8550724637681);
	QCOMPARE(distMatrix.at(1).at(0), 0.8550724637681);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::UniFracTest4_Rooted_Network_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase4Rooted.nex", "../TestCases/TestCase4Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.7545748116254);
	QCOMPARE(distMatrix.at(1).at(0), 0.7545748116254);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::MRCA_Test5_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase5Rooted.nex", "../TestCases/TestCase5Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(0), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteTreeTest5_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase5Rooted.nex", "../TestCases/TestCase5Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(0), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::CompleteLineageTest5_Rooted_Network()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase5Rooted.nex", "../TestCases/TestCase5Rooted.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(0), 0.7222222222222);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
}

void UnitTests::MRCA_Test6_Implicitly_Rooted_Tree_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.46666666467984524);
	QCOMPARE(distMatrix.at(0).at(2), 0.26666666269302380);
	QCOMPARE(distMatrix.at(1).at(0), 0.46666666467984524);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(0), 0.26666666269302380);
	QCOMPARE(distMatrix.at(2).at(1), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest6_Implicitly_Rooted_Tree_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.46666666467984524);
	QCOMPARE(distMatrix.at(0).at(2), 0.26666666269302380);
	QCOMPARE(distMatrix.at(1).at(0), 0.46666666467984524);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(0), 0.26666666269302380);
	QCOMPARE(distMatrix.at(2).at(1), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest6_Implicitly_Rooted_Tree_Unweighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.46666666467984524);
	QCOMPARE(distMatrix.at(0).at(2), 0.26666666269302380);
	QCOMPARE(distMatrix.at(1).at(0), 0.46666666467984524);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(0), 0.26666666269302380);
	QCOMPARE(distMatrix.at(2).at(1), 0.20000000198682144);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest6_Implicitly_Rooted_Tree_Weighted()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.71991343893014004);
	QCOMPARE(distMatrix.at(0).at(2), 0.30476191285110654);
	QCOMPARE(distMatrix.at(1).at(0), 0.71991343893014004);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.41515152607903344);
	QCOMPARE(distMatrix.at(2).at(0), 0.30476191285110654);
	QCOMPARE(distMatrix.at(2).at(1), 0.41515152607903344);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::MRCA_Test6_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.83191595698446053);
	QCOMPARE(distMatrix.at(0).at(2), 0.45390070706874236);
	QCOMPARE(distMatrix.at(1).at(0), 0.83191595698446053);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.65550239211934802);
	QCOMPARE(distMatrix.at(2).at(0), 0.45390070706874236);
	QCOMPARE(distMatrix.at(2).at(1), 0.65550239211934802);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteTreeTest6_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 1.0);
	QCOMPARE(distMatrix.at(0).at(2), 0.42333132897756681);
	QCOMPARE(distMatrix.at(1).at(0), 1.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.57666867102243313);
	QCOMPARE(distMatrix.at(2).at(0), 0.42333132897756681);
	QCOMPARE(distMatrix.at(2).at(1), 0.57666867102243313);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::CompleteLineageTest6_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.67246259367040473);
	QCOMPARE(distMatrix.at(0).at(2), 0.38787878556356620);
	QCOMPARE(distMatrix.at(1).at(0), 0.67246259367040473);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.42153846007127033);
	QCOMPARE(distMatrix.at(2).at(0), 0.38787878556356620);
	QCOMPARE(distMatrix.at(2).at(1), 0.42153846007127033);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::UniFracTest6_Implicitly_Rooted_Tree_WeightedNormalized()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase6.tre", "../TestCases/TestCase6.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.50654888552605393);
	QCOMPARE(distMatrix.at(0).at(2), 0.24060150197772881);
	QCOMPARE(distMatrix.at(1).at(0), 0.50654888552605393);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.26705652903668692);
	QCOMPARE(distMatrix.at(2).at(0), 0.24060150197772881);
	QCOMPARE(distMatrix.at(2).at(1), 0.26705652903668692);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::UniFracTest7()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase7.tre", "../TestCases/TestCase7.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.4615384615384);
	QCOMPARE(distMatrix.at(0).at(2), 0.9298245614035);
	QCOMPARE(distMatrix.at(1).at(0), 0.4615384615384);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.4545454545454);
	QCOMPARE(distMatrix.at(2).at(0), 0.9298245614035);
	QCOMPARE(distMatrix.at(2).at(1), 0.4545454545454);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_MRCA_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();
	
	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/6.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/6.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteTree_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/13.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/13.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteLineage_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/9.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/9.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_MRCA_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 2*3.3/(3.3+4.5));
	QCOMPARE(distMatrix.at(0).at(2), 0.909090909090909);
	QCOMPARE(distMatrix.at(1).at(0), 2*3.3/(3.3+4.5));
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2*0.9/(0.9+3.5));
	QCOMPARE(distMatrix.at(2).at(0), 0.909090909090909);
	QCOMPARE(distMatrix.at(2).at(1), 2*0.9/(0.9+3.5));
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteTree_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.3/4.1);
	QCOMPARE(distMatrix.at(0).at(2), 4.0/4.1);
	QCOMPARE(distMatrix.at(1).at(0), 3.3/4.1);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.9/4.1);
	QCOMPARE(distMatrix.at(2).at(0), 4.0/4.1);
	QCOMPARE(distMatrix.at(2).at(1), 0.9/4.1);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteLineage_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 2*3.3/(3.3+8.7));
	QCOMPARE(distMatrix.at(0).at(2), 0.615384615384615);
	QCOMPARE(distMatrix.at(1).at(0), 2*3.3/(3.3+8.7));
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2*0.9/(0.9+9.7));
	QCOMPARE(distMatrix.at(2).at(0), 0.615384615384615);
	QCOMPARE(distMatrix.at(2).at(1), 2*0.9/(0.9+9.7));
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_UniFrac_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.379310344827586);
	QCOMPARE(distMatrix.at(0).at(2), 0.444444444444444);
	QCOMPARE(distMatrix.at(1).at(0), 0.379310344827586);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.0927835051546391);
	QCOMPARE(distMatrix.at(2).at(0), 0.444444444444444);
	QCOMPARE(distMatrix.at(2).at(1), 0.0927835051546391);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_Unnormalized_Test8()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase8.tre", "../TestCases/TestCase8.env", "", true);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.3);
	QCOMPARE(distMatrix.at(0).at(2), 4.0);
	QCOMPARE(distMatrix.at(1).at(0), 3.3);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.9);
	QCOMPARE(distMatrix.at(2).at(0), 4.0);
	QCOMPARE(distMatrix.at(2).at(1), 0.9);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_MRCA_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/6.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/6.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteTree_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/13.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/13.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Qualitative_CompleteLineage_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::UNWEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 8.0/13.0);
	QCOMPARE(distMatrix.at(0).at(2), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2.0/9.0);
	QCOMPARE(distMatrix.at(2).at(0), 8.0/13.0);
	QCOMPARE(distMatrix.at(2).at(1), 2.0/9.0);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_MRCA_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 2*3.3/(3.3+4.5));
	QCOMPARE(distMatrix.at(0).at(2), 0.909090909090909);
	QCOMPARE(distMatrix.at(1).at(0), 2*3.3/(3.3+4.5));
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2*0.9/(0.9+3.5));
	QCOMPARE(distMatrix.at(2).at(0), 0.909090909090909);
	QCOMPARE(distMatrix.at(2).at(1), 2*0.9/(0.9+3.5));
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteTree_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.3/4.1);
	QCOMPARE(distMatrix.at(0).at(2), 4.0/4.1);
	QCOMPARE(distMatrix.at(1).at(0), 3.3/4.1);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.9/4.1);
	QCOMPARE(distMatrix.at(2).at(0), 4.0/4.1);
	QCOMPARE(distMatrix.at(2).at(1), 0.9/4.1);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_CompleteLineage_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::COMPLETE_LINEAGE);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 2*3.3/(3.3+8.7));
	QCOMPARE(distMatrix.at(0).at(2), 0.615384615384615);
	QCOMPARE(distMatrix.at(1).at(0), 2*3.3/(3.3+8.7));
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 2*0.9/(0.9+9.7));
	QCOMPARE(distMatrix.at(2).at(0), 0.615384615384615);
	QCOMPARE(distMatrix.at(2).at(1), 2*0.9/(0.9+9.7));
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_UniFrac_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
	uniSplit->SetSplitsToConsider(UniSplit::NORMALIZED_WEIGHTED_UNIFRAC);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 0.379310344827586);
	QCOMPARE(distMatrix.at(0).at(2), 0.444444444444444);
	QCOMPARE(distMatrix.at(1).at(0), 0.379310344827586);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.0927835051546391);
	QCOMPARE(distMatrix.at(2).at(0), 0.444444444444444);
	QCOMPARE(distMatrix.at(2).at(1), 0.0927835051546391);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}

void UnitTests::Quantitative_Unnormalized_Test9()
{
	SplitSystemPtr splitSystem(new SplitSystem());
	splitSystem->LoadData("../TestCases/TestCase9.tre", "../TestCases/TestCase9.env", "", false);
	splitSystem->CreateFromTree(splitSystem->GetTree()->GetRootNode());

	UniSplitPtr uniSplit(new UniSplit(splitSystem));

	QVERIFY(splitSystem->IsOutgroupMonophyletic() == true);

	uniSplit->SetMeasureType(UniSplit::WEIGHTED);
	uniSplit->SetSplitsToConsider(UniSplit::ALL_SPLITS);
	Matrix distMatrix = uniSplit->Run();

	QCOMPARE(distMatrix.at(0).at(0), 0.0);
	QCOMPARE(distMatrix.at(0).at(1), 3.3);
	QCOMPARE(distMatrix.at(0).at(2), 4.0);
	QCOMPARE(distMatrix.at(1).at(0), 3.3);
	QCOMPARE(distMatrix.at(1).at(1), 0.0);
	QCOMPARE(distMatrix.at(1).at(2), 0.9);
	QCOMPARE(distMatrix.at(2).at(0), 4.0);
	QCOMPARE(distMatrix.at(2).at(1), 0.9);
	QCOMPARE(distMatrix.at(2).at(2), 0.0);
}