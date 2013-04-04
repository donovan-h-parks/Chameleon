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

#ifndef PARALLEL_COORD_CURVE_HPP
#define PARALLEL_COORD_CURVE_HPP

#include "stdafx.h"

class ParallelCoordData;

class ParallelCoordCurve: public QwtPlotCurve
{
public:
	static const int Rtti_ParallelCoordCurve = QwtPlotItem::Rtti_PlotUserItem + 2;

public:
	ParallelCoordCurve(uint sampleId);

	virtual int rtti () const { return Rtti_ParallelCoordCurve; }

	void SetSampleId(uint id) { m_sampleId = id; }
	uint GetSampleId() const { return m_sampleId; }

	void SetMarker(ParallelCoordData* data, 
									QwtSymbol::Style shape, QColor& color, uint size, 
									bool bVisible, bool bSelected, bool bGuaranteedVisiblity, 
									bool bFittedCurves, bool bShowCurves);

	void SetVisualProperties(QwtSymbol::Style shape, QColor& color, uint size, 
																bool bVisible, bool bSelected, bool bGuaranteedVisiblity,
																bool bFittedCurves, bool bShowCurves);

	QRectF boundingRect() const;
	void draw(QPainter* p, const QwtScaleMap& xMap, const QwtScaleMap& yMap, const QRectF& canvasRect) const;

private:
	uint m_sampleId;

	QwtPlotCurve* m_selectedCurve;

	bool m_bSelected;
};

#endif