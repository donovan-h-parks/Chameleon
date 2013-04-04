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

#ifndef CLUSTER_TREE_ANALYSIS_DLG_HPP
#define CLUSTER_TREE_ANALYSIS_DLG_HPP

#include "ui_ClusterTreeAnalysisDialog.h"

#include "stdafx.h"
#include "Cluster.hpp"

class ClusterTreeAnalysisDlg : public QDockWidget
{
	Q_OBJECT

public:
	ClusterTreeAnalysisDlg(SystemPtr system, UniSplitPtr uniSplit, QWidget *parent = 0, Qt::WFlags flags = 0);
	~ClusterTreeAnalysisDlg();

	/** Type of clustering to perform. */
	Cluster::CLUSTER_TYPE GetClusteringMethod() const;

	/** Flag indicating if a normalized analysis is to be performed. */
	bool GetNormalized() const;

	/** Flag indicating if a weighted analysis is to be performed. */
	bool GetWeighted() const;

	/** Number of jackknife or permutation test iterations to perform. */
	uint GetNumberIterations() const;

	/** Number of sequence to retain in jackknife analysis. */
	uint GetSeqToRetain() const;

	/** Indicate the underlying split system or diversity measure has changed. */
	void AnalysisChanged();

signals:
	void Run();

private slots:
	void Execute();
	void SetToMinSeq();

private:
	Ui::ClusterTreeAnalysisDlg ui;

	SystemPtr m_activeSystem;
	UniSplitPtr m_uniSplit;
};

#endif 
