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
// along with Chameleon.  If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "AutoCollapseDlg.hpp"


AutoCollapseDlg::AutoCollapseDlg(QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags)
{
	ui.setupUi(this);

	QObject::connect(ui.btnRun,  SIGNAL(clicked()), this, SLOT(Execute()));
	QObject::connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(TopLevelChanged(bool)));

	updateGeometry();
}

void AutoCollapseDlg::Execute()
{
	emit Run();
}

void AutoCollapseDlg::TopLevelChanged(bool bFloating)
{
	if(bFloating)
	{
		updateGeometry();
		update();
	}
}

VisualTree::AUTO_COLLAPSE_CONSTRAINT AutoCollapseDlg::GetCollapseVariable()
{
	if(ui.cboFilterVariable->currentText() == "distance to the furthest leaf node is below")
		return VisualTree::DIST_TO_FURTHEST_LEAF_NODE_CONSTRAINT;
	else if(ui.cboFilterVariable->currentText() == "distance to the root is above")
		return VisualTree::DIST_TO_ROOT_CONSTRAINT;
	else if(ui.cboFilterVariable->currentText() == "total branch length is below")
		return VisualTree::TOTAL_BRANCH_LENGTH_CONSTRAINT;
	else if(ui.cboFilterVariable->currentText() == "consistency index is above")
		return VisualTree::CONSISTENCY_INDEX_CONSTRAINT;
	else // support value is below
		return VisualTree::SUPPORT_VALUE_CONSTRAINT;
}
