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

#ifndef ORDINATION_PLOTS_HPP
#define ORDINATION_PLOTS_HPP

#include "stdafx.h"

class QwtPlot;
class OrdinationPlot;
class OrdinationSelection;

class OrdinationPlots: public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param plots Set of four plots on which to display MDS plots.
	 * @param legends Legends indicating marker styles for data to be plotted.
	 */
	OrdinationPlots(const QList<OrdinationPlot*>& plots, LegendsPtr legend);

	/** Set samples to plot. */
	void SetSamples(SamplesPtr samples);

	/** Set results of multidimensional scaling analysis. */
	void SetData(const Matrix& embedding, const QVector<double>& variance, const QVector<double>& sumVariance, Matrix neighbourhoodGraph);

	/** Show name of each sample. */
	void SetShowSampleNames(bool state) { m_bShowSampleNames = state; UpdateMarkers(); }

	void SetSelectionTransparency(bool state) { m_bApplySelectionTransparency = state; UpdateMarkers(); }

	QString GetMethodMessage() const { return m_methodMessage; }
	void SetMethodMessage(const QString& message) { m_methodMessage = message; }

	/** Create clone of plot. */
	void Clone(QwtPlot* plot, uint plotIndex);

public slots:
	/** Produce a set of plots showing results of multidimensional scaling (MDS) analysis. */
	void Plot();

	void PopupMenu(const QPoint & pos);
	void SendToDetachedWindow();

	void UpdateMarkers();
	void UpdateMarkers(const QVector<QPointF>& selectedPts);
	void SetAxes();

	void SetBackgroundColor(const QColor& color);

private:
	/** Produce plot of specified principal components. */
	void Plot(QwtPlot* plot, uint component1, uint component2);
	void ScreePlot(QwtPlot* plot);

	void UpdateMarkers(QwtPlot* plot);

private:
	QList<OrdinationPlot*> m_plots;
	QVector<QwtInterval> m_axes;

	Matrix m_embedding;
	QVector<double> m_variance;
	QVector<double> m_sumVariance;
	QVector<double> m_xAxis;
	Matrix m_neighbourhoodGraph;
	
	LegendsPtr m_legends;
	SamplesPtr m_samples;

	QString m_methodMessage;

	bool m_bShowSampleNames;
	bool m_bApplySelectionTransparency;
};

#endif
