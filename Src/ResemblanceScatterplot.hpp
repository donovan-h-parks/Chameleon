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

#ifndef RESEMBLANCE_SCATTERPLOT_HPP
#define RESEMBLANCE_SCATTERPLOT_HPP

#include "stdafx.h"

class QwtPlot;
class QwtPlotRescaler;
class MdsSelection;

class ResemblanceScatterplot: public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param plot Plot on which to display scatterplot.
	 */
	ResemblanceScatterplot(QwtPlot* plot);

	/** Create clone of plot. */
	void Clone(QwtPlot* plot);

public slots:
	void Plot(const Matrix& xMatrix, const Matrix& yMatrix, const QStringList& sampleNames,
							const QString& xMeasureLabel, const QString& yMeasureLabel,
							uint size, bool bShowBestFitLine);
	void UpdateMarkers(int size);

	void PopupMenu(const QPoint & pos);
	void SendToDetachedWindow();

	void ShowBestFitLine(int bShow) { m_bShowBestFitLine = bShow; UpdateMarkers(m_size); }

	void SetBackgroundColor(const QColor& color);

private:
	void Plot(QwtPlot* plot);

private:
	QwtPlot* m_plot;

	PlotPickerPtr m_plotPicker;

	Matrix m_xMatrix;
	Matrix m_yMatrix;
	QStringList m_sampleNames;
	QString m_xMeasureLabel;
	QString m_yMeasureLabel;

	bool m_bShowBestFitLine;
	uint m_size;
};


#endif
