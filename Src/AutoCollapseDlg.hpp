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

#ifndef AUTO_COLLAPSE_DLG_HPP
#define AUTO_COLLAPSE_DLG_HPP

#include "ui_AutoCollapseDialog.h"

#include "stdafx.h"
#include "VisualTree.hpp"

class AutoCollapseDlg : public QDockWidget
{
	Q_OBJECT

public:
	AutoCollapseDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AutoCollapseDlg() {}

	VisualTree::AUTO_COLLAPSE_CONSTRAINT GetCollapseVariable();
	float GetCollapseConstraint() { return ui.spinFilterValue->value(); }

signals:
	void Run();
	
private slots:
	void Execute();
	void TopLevelChanged(bool bFloating); 

private:
	Ui::AutoCollapseDlg ui;

};

#endif 
