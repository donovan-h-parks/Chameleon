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

#ifndef PARALLEL_COORDINATE_PLOT_HPP
#define PARALLEL_COORDINATE_PLOT_HPP

#include "stdafx.h"

class ParallelCoordSelection;

class ParallelCoordPlot : public QObject
{
	Q_OBJECT

public:
	ParallelCoordPlot(QwtPlot* plot, LegendsPtr legends);

	/** Set samples to plot. */
	void SetSamples(SamplesPtr samples);

	/** Set data to plot. */
	void SetData(const Matrix& embedding, const QVector<double>& variance);

	/** Indicate if curves should be shown. */
	void SetShowCurves(bool state) { m_bShowCurves = state; UpdateMarkers();  }

	/** Indicate if curves should be fitted or not. */
	void SetFittedCurves(bool state) { m_bFittedCurves = state; Plot();  }

	/** Indicate if labels indicating the variance of each principal component should be shown. */
	void ShowVarianceLabels(bool state) { m_bShowVariance = state; Plot(); }

	/** Indicate if non-selected samples should be made transparent. */
	void SetSelectionTransparency(bool state) { m_bApplySelectionTransparency = state; UpdateMarkers(); }

	/** Set number of dimensions to display. */
	void SetNumDimensions(uint dim) { m_dimToDisplay = dim; Plot(); }

	/** Create clone of plot. */
	void Clone(QwtPlot* plot);

public slots:
	/** Produce parallel coordinate plot of data. */
	void Plot();

	void PopupMenu(const QPoint & pos);
	void SendToDetachedWindow();

	void UpdateMarkers();

	void SetBackgroundColor(const QColor& color);

private:
	void Plot(QwtPlot* plot);

private:
	QwtPlot* m_plot;

	Matrix m_embedding;
	QVector<double> m_variance;

	LegendsPtr m_legends;
	SamplesPtr m_samples;

	bool m_bShowCurves;
	bool m_bFittedCurves;
	bool m_bShowVariance;

	uint m_dimToDisplay;

	bool m_bApplySelectionTransparency;
};


/**
 * @brief Provide access to specific data points within a data matrix.
 */
class ParallelCoordData: public QwtPointSeriesData
{
public:
		/**
		 * @brief Constructor.
		 * @param projectedMatrix Matrix containing results of an MDS analysis.
		 * @param dimToDisplay Number of dimensions to display.
		 * @param index Desired row (data point) to plot.
		 */
    ParallelCoordData(const Matrix& matrix, int dimToDisplay, uint index): m_matrix(matrix), m_dimToDisplay(dimToDisplay), m_index(index) {}

    virtual size_t size() const { return qMin(m_matrix.at(0).size(), m_dimToDisplay);	}

    virtual QPointF sample(size_t i) const { return QPointF(i+1, m_matrix.at(m_index).at(i)); }

		virtual void setIndex(uint index) { m_index = index; }

		virtual int getDimToDisplay() const { return m_dimToDisplay; }

private:
    const Matrix& m_matrix;
		int m_dimToDisplay;
		int m_index;		
};

#endif
