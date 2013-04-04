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

#include "ClusterTreeAnalysisDlg.hpp"

#include "Log.hpp"

#include "SplitSystem.hpp"
#include "UniSplit.hpp"
#include "GUI.h"

ClusterTreeAnalysisDlg::ClusterTreeAnalysisDlg(SystemPtr system, UniSplitPtr uniSplit, QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags), m_activeSystem(system), m_uniSplit(uniSplit)
{
	ui.setupUi(this);

	QObject::connect(ui.btnRun,  SIGNAL(clicked()), this, SLOT(Execute()));
	QObject::connect(ui.btnMinSeq,  SIGNAL(clicked()), this, SLOT(SetToMinSeq()));

	SetToMinSeq();

	updateGeometry();
}

ClusterTreeAnalysisDlg::~ClusterTreeAnalysisDlg()
{

}

void ClusterTreeAnalysisDlg::Execute()
{
	emit Run();

	if(isFloating())
		setVisible(false);
}

uint ClusterTreeAnalysisDlg::GetNumberIterations() const
{
	return ui.spinJackknifeIterations->value();
}

uint ClusterTreeAnalysisDlg::GetSeqToRetain() const
{
	return ui.spinSeqToRetain->value();
}

Cluster::CLUSTER_TYPE ClusterTreeAnalysisDlg::GetClusteringMethod() const
{
	if(ui.cboClusteringMethod->currentText() == "Complete linkage")
		return Cluster::COMPLETE_LINKAGE;
	else if(ui.cboClusteringMethod->currentText() == "Neighbour joining")
		return Cluster::NEIGHBOUR_JOINING;
	else if(ui.cboClusteringMethod->currentText() == "Single linkage")
		return Cluster::SINGLE_LINKAGE;
	else if(ui.cboClusteringMethod->currentText() == "UPGMA")
		return Cluster::AVERAGE_LINKAGE;

	Log::Inst().Error("Unrecognized clustering method specified.");
	return Cluster::AVERAGE_LINKAGE;
}

void ClusterTreeAnalysisDlg::AnalysisChanged()
{
	SetToMinSeq();
}

void ClusterTreeAnalysisDlg::SetToMinSeq()
{
	uint minSeqs = INT_MAX;
	foreach(uint sampleId, m_activeSystem->GetSamples()->GetActiveSampleIds())
	{
		uint seqs = m_activeSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(sampleId, m_uniSplit->IsWeighted());
		if(seqs < minSeqs)
			minSeqs = seqs;
	}

	ui.spinSeqToRetain->setValue(minSeqs);
}