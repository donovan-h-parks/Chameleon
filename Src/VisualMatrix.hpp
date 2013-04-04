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

#ifndef VISUAL_MATRIX
#define VISUAL_MATRIX

#include "stdafx.h"

class VisualMatrixSlider;

class VisualMatrix: public QGraphicsItem
{
public:
	enum SORT_METHOD { SIDE_TO_SIDE, NEIGHBOURHOOD, SIMULATED_ANNEALING, RANDOMIZE };

public:
	VisualMatrix(LegendsPtr legends, ColorMapsPtr colorMaps, QLabel* reportLabel);

	/** Set samples to plot. */
	void SetSamples(SamplesPtr samples);
	
	void SetData(const Matrix& dissMatrix, const QStringList& sampleLabels);

	void Sort(SORT_METHOD method);

	QString GetSortingMethod() const { return m_sortingMethod; }

	void SetColorMapRange(bool state) { m_bFullColorMapRange = state; ColorMapScaleChanged(); update(); }

	void SetColorMap(const QString& colorMapName);

	void SetMinCellSize(int size) { m_minCellSize = size; update(); }

	void SetColorMapThreshold(bool bThreshold);

	QGraphicsScene* GetScene() const { return m_scene; }

	QRectF boundingRect() const;

	QStringList GetSortedLabels() const { return m_sampleLabels; }

	void SetSelectionTransparency(bool state) { m_bApplySelectionTransparency = state; update(); }

	void SetBackgroundColor(const QColor& color) { m_scene->setBackgroundBrush(QBrush(color)); }

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void resizeEvent(QResizeEvent* e);

	void hoverMoveEvent( QGraphicsSceneHoverEvent* e);
	void mousePressEvent( QGraphicsSceneMouseEvent * e);
	void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * e );

	void SideToSideSort();
	void NeighbourhoodSort();
	void SimulatedAnnealingSort();
	void RandomizeSort();
	
	void ColorMapScaleChanged();

	void SetData();

private:
	static const int BORDER_SIZE = 40;

	static const int SAMPLE_COL_OFFSET = 15;
	static const int SAMPLE_COL_START = BORDER_SIZE-SAMPLE_COL_OFFSET;
	static const int SAMPLE_COL_END = BORDER_SIZE-5;
	
	static const int COLOR_MAP_OFFSET = 8;
	static const int COLOR_MAP_WIDTH = 20;

	static const int HIGHLIGHT_OFFSET = 3;

	QGraphicsScene* m_scene;

	SamplesPtr m_samples;
	LegendsPtr m_legends;
	ColorMapsPtr m_colorMaps;

	QString m_colorMapName;
	QLabel* m_reportLabel;

	Matrix m_dissMatrix;

	QStringList m_sampleLabels;
	QList<uint> m_sampleIds;
	QList<QStringList> m_distLabels;

	QMap<uint, uint> m_visibleRowToSampleId;
	QMap<uint, uint> m_visibleRowToOriginalRow;

	uint m_minCellSize;

	uint m_cellSize;
	uint m_matrixSize;	

	double m_minDist, m_maxDist;

	QString m_sortingMethod;

	bool m_bFullColorMapRange;

	bool m_bThreshold;
	VisualMatrixSlider* m_thresholdMarker;

	bool m_bApplySelectionTransparency;
};

#endif