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

#ifndef _UNITTESTS_
#define _UNITTESTS_

#include "stdafx.h"

// Performs unit testing
void ExecuteUnitTests();

// Defines all unit tests
class UnitTests: public QObject
{
	Q_OBJECT
private slots:
	void SandboxTesting();

	// Test box plot statistics
	// Ground truth from http://www.statcan.gc.ca/edu/power-pouvoir/ch12/5214890-eng.htm
	void TestBoxPlotStats1();
	void TestBoxPlotStats2();

	// Test tree where sequences are missing from the sample file.
	// Ground truth determined with UniFrac web service.
	void TestMissingSampleSeq();

	// Test Newick IO.
	// Ground truth determined by hand.
	void TestNewickIO();

	// Test creation of split system from forest of trees.
	// Ground truth determiend by hand.
	void TestSplitSystemFromForest();

	// Test clustering algorithms.
	// Ground truth determined using SciPy (scipy.cluster.hierarchy.complete)
	void TestCompleteLinkage();
	void TestSingleLinkage();
	void TestUPGMA();
	void TestUPGMA2();
	void TestUPGMA3();
	void TestNJ();
	void TestNJ2();

	// Test linear regression.
	// Ground truth determined using Microsoft Excel.
	void TestLinearRegression();

	// Test side-to-side sorting method.
	// Ground truth from http://www.weizmann.ac.il/home/fedomany/Bioinfo05/lecture4.pdf
	void TestSideToSideSort();
	void TestNeighbourSort();

	// Test support value tree constuction algorithm.
	// Ground truth determined by hand.
	void TestSupportTree();

	// Test PCoA algorithm.
	// Ground truth found using PyCogent's cogent.cluster.metric_scaling.principal_coordinates_analysis() function
	// and MATLAB's mdscale function.
	void TestPCoA1();
	void TestPCoA2();
	void TestPCoA3();
	void TestPCoA4();

	// Test identification of polyphyletic outgroup.
	// Groud truth determined by hand.
	void TestPolyphyleticOutgroup();

	// Test reading of environment file by checking number of taxa from each sample
	// Ground truth determined by hand.
	void Test1_Sample_Counts();
	void Test2_Sample_Counts();
	void Test3_Sample_Counts();
	void Test4_Sample_Counts();

	// Simplest possible test of all measures.
	// Ground truth determined by hand.
	void Qualitative_MRCA_Test0();
	void Qualitative_CompleteTree_Test0();
	void Qualitative_CompleteLineage_Test0();
	void Quantitative_MRCA_Test0();
	void Quantitative_CompleteTree_Test0();
	void Quantitative_CompleteLineage_Test0();
	void Quantitative_UniFrac_Test0();
	void Quantitative_Unnormalized_Test0();

	// Qualitative MRCA tests: test results on a simple tree with multiple sample sites.
	// Ground truth determined by hand.
	void MRCA_Test1_Implicitly_Rooted_Tree();
	void MRCA_Test1_Rooted_Tree();
	void MRCA_Test1_Rooted_Network();
	void MRCA_Test1_Rooted_Network_TreeBlock();

	// Qualitative complete tree tests: test results on a simple tree with multiple sample sites.
	// Ground truth determined by hand.
	void CompleteTreeTest1_Implicitly_Rooted_Tree();
	void CompleteTreeTest1_Rooted_Tree();
	void CompleteTreeTest1_Rooted_Network();
	void CompleteTreeTest1_Rooted_Network_TreeBlock();

	// Qualitative complete lineage (i.e., UniFrac) tests: test results on a simple tree with multiple sample sites.
	// Ground truth determined with UniFrac web service.	
	void CompleteLineageTest1_Implicitly_Rooted_Tree();
	void CompleteLineageTest1_Rooted_Tree();
	void CompleteLineageTest1_Rooted_Network();
	void CompleteLineageTest1_Rooted_Network_TreeBlock();

	// Qualitative MRCA tests: test results on a large tree.
	// Ground truth determined by hand.
	void MRCA_Test2_Implicitly_Rooted_Tree();	
	void MRCA_Test2_Rooted_Tree();
	void MRCA_Test2_Rooted_Network();

	// Qualitative complete tree tests: test results on a large tree.
	// Ground truth determined by hand.
	void CompleteTreeTest2_Implicitly_Rooted_Tree();	
	void CompleteTreeTest2_Rooted_Tree();
	void CompleteTreeTest2_Rooted_Network();

	// Qualitative complete lineage (i.e., UniFrac) tests: test results on a large tree.
	// Ground truth determined with UniFrac web service.
	void CompleteLineageTest2_Implicitly_Rooted_Tree();	
	void CompleteLineageTest2_Rooted_Tree();
	void CompleteLineageTest2_Rooted_Network();

	// Unnormalized quantitative measure: results when there are sequences present multiple times at a sample site.
	// Ground truth determined by hand.
	void CompleteTreeTest3_Implicitly_Rooted_Tree_Weighted();
	void CompleteTreeTest3_Rooted_Tree_Weighted();
	void CompleteTreeTest3_Rooted_Network_Weighted();
	
	// Complete lineage tests: results when there are sequences present multiple times at a sample site.
	// Ground truth determined by hand.
	void CompleteLineageTest3_Implicitly_Rooted_Tree_Unweighted();
	void CompleteLineageTest3_Rooted_Network_Unweighted();

	// Normalized complete tree test: results when there are sequences present multiple times at a sample site.
	// Ground truth compared with mothur implementation.
	void CompleteTreeTest3_Implicitly_Rooted_Tree_Weighted_Normalized();

	// Normalized weighted UniFrac tests: results when there are sequences present multiple times at a sample site.
	// Ground truth determined with UniFrac web service.
	void UniFracTest3_Implicitly_Rooted_Tree_WeightedNormalized();	
	void UniFracTest3_Rooted_Tree_WeightedNormalized();	
	void UniFracTest3_Rooted_Network_WeightedNormalized();

	// UniFrac test: Test results on a multi-furicating tree.
	// Ground truth determined with UniFrac web service.
	void UniFracTest4_Implicitly_Rooted_Tree_Unweighted();
	void UniFracTest4_Implicitly_Rooted_Tree_WeightedNormalized();
	void UniFracTest4_Rooted_Network_Unweighted();
	void UniFracTest4_Rooted_Network_WeightedNormalized();

	// Qualitative tests on incompatible split system. 
	// Ground truth determined by hand.
	void MRCA_Test5_Rooted_Network();
	void CompleteTreeTest5_Rooted_Network();
	void CompleteLineageTest5_Rooted_Network();

	// Tests involving identical sequences in multiple samples.
	// Ground truth determined by hand.
	void MRCA_Test6_Implicitly_Rooted_Tree_Unweighted();
	void CompleteTreeTest6_Implicitly_Rooted_Tree_Unweighted();
	void CompleteLineageTest6_Implicitly_Rooted_Tree_Unweighted();
	void CompleteTreeTest6_Implicitly_Rooted_Tree_Weighted();
	void MRCA_Test6_Implicitly_Rooted_Tree_WeightedNormalized();
	void CompleteTreeTest6_Implicitly_Rooted_Tree_WeightedNormalized();
	void CompleteLineageTest6_Implicitly_Rooted_Tree_WeightedNormalized();
	void UniFracTest6_Implicitly_Rooted_Tree_WeightedNormalized();

	// Test illustrating normalized weighted UniFrac is not metric.
	// Ground truth determined by hand.
	void UniFracTest7();

	// General test of all qualitative and quantitative measures.
	// Ground truth determined by hand.
	void Qualitative_MRCA_Test8();
	void Qualitative_CompleteTree_Test8();
	void Qualitative_CompleteLineage_Test8();
	void Quantitative_MRCA_Test8();
	void Quantitative_CompleteTree_Test8();
	void Quantitative_CompleteLineage_Test8();
	void Quantitative_UniFrac_Test8();
	void Quantitative_Unnormalized_Test8();

	// General test of all qualitative and quantitative measures on explictly
	// rooted tree in order to test the outgroup branches are being properly ignored.
	// Ground truth determined by hand.
	void Qualitative_MRCA_Test9();
	void Qualitative_CompleteTree_Test9();
	void Qualitative_CompleteLineage_Test9();
	void Quantitative_MRCA_Test9();
	void Quantitative_CompleteTree_Test9();
	void Quantitative_CompleteLineage_Test9();
	void Quantitative_UniFrac_Test9();
	void Quantitative_Unnormalized_Test9();
};

#endif
