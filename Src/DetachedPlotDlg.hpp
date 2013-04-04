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

#ifndef DETACHED_PLOT_DLG_HPP
#define DETACHED_PLOT_DLG_HPP

#include "ui_DetachedPlotDialog.h"

#include "stdafx.h"

class QwtPlot;
class QwtPlotRescaler;

class DetachedPlotDlg : public QDialog
{
	Q_OBJECT

public:
	DetachedPlotDlg(bool bRescaler = true, QWidget *parent = 0, Qt::WFlags flags = 0);
	~DetachedPlotDlg();

	QwtPlot* GetPlot() { return ui.qwtPlot; }
	QwtPlotRescaler* GetRescaler() { return m_rescaler; }

	void SetBackgroundColor(const QColor& color);

private slots:
	void SavePlot();

private:
	Ui::DetachedPlotDlg ui;

	QwtPlotRescaler* m_rescaler;
};

#endif 
