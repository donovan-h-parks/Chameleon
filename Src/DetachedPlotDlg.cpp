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

#include "DetachedPlotDlg.hpp"

#include "Log.hpp"

DetachedPlotDlg::DetachedPlotDlg(bool bRescaler, QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags | Qt::WindowMinMaxButtonsHint)
{
	ui.setupUi(this);

	// event handlers
	QObject::connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(reject()));
	QObject::connect(ui.btnSaveRaster, SIGNAL(clicked()), this, SLOT(SavePlot()));

	if(bRescaler)
	{
		m_rescaler = new QwtPlotRescaler(ui.qwtPlot->canvas(), QwtPlot::xBottom, QwtPlotRescaler::Fitting); 
		m_rescaler->setExpandingDirection(QwtPlotRescaler::ExpandBoth);
	}
}

DetachedPlotDlg::~DetachedPlotDlg()
{

}

void DetachedPlotDlg::SavePlot()
{
	QPixmap qPix = QPixmap::grabWidget(ui.plotFrame);

	if(qPix.isNull())
	{
		Log::Inst().Warning("Failed to capture the plot or legend for saving.");
		return;
	}

	QString types( "Portable Network Graphics (*.png);;JPEG file (*.jpg *.jpeg);;Bitmap file (*.bmp)");
	QString filename = QFileDialog::getSaveFileName(this, "Save plot...", "", types);
	if(!filename.isEmpty()) 
	{
		if(filename.contains(".png"))
			qPix.save( filename, "PNG" );
		else if(filename.contains(".jpeg") || filename.contains(".jpg"))  
			qPix.save( filename, "JPG" );
		else if(filename.contains(".bmp"))  
			qPix.save( filename, "BMP" );
	}
}

void DetachedPlotDlg::SetBackgroundColor(const QColor& color)
{
	ui.plotFrame->setAutoFillBackground(true);
	ui.plotFrame->setPalette(color);
	ui.plotFrame->repaint();
}
