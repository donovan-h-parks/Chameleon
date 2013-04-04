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

#include "VisualMatrix.hpp"

#include "Log.hpp"
#include "Samples.hpp"
#include "Metadata.hpp"
#include "Legends.hpp"

#include "ColorMaps.hpp"
#include "Properties.hpp"

#include "VisualMatrixSlider.hpp"

VisualMatrix::VisualMatrix(LegendsPtr legends, ColorMapsPtr colorMaps, QLabel* reportLabel)
	: m_scene(new QGraphicsScene()), m_legends(legends), m_colorMaps(colorMaps),
		m_reportLabel(reportLabel), m_bFullColorMapRange(true), m_sortingMethod("Unsorted"), m_minCellSize(1),
		m_bThreshold(false), m_bApplySelectionTransparency(true)
{
	m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	m_scene->addItem(this);

	setAcceptHoverEvents(true);

	QPolygonF poly;
	poly << QPointF(0,0) << QPointF(15, -5) << QPointF(15, 5);
	m_thresholdMarker = new VisualMatrixSlider(poly, this);	
	m_thresholdMarker->setVisible(m_bThreshold);
}

void VisualMatrix::SetSamples(SamplesPtr samples)
{
	m_samples = samples;
}

struct Score
{
	Score(double _score, int _index): score(_score), index(_index) {}

	double score;
	int index;
};

bool ScoreSorter(const Score& s1, const Score& s2)
{
	return s1.score > s2.score;
}

void VisualMatrix::Sort(SORT_METHOD method)
{
	if(m_dissMatrix.size() == 0)
		return;

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if(method == SIDE_TO_SIDE)
	{
		m_sortingMethod = "Side-to-side";
		SideToSideSort();
	}
	else if(method == NEIGHBOURHOOD)
	{
		m_sortingMethod = "Neighbourhood";
		NeighbourhoodSort();
	}
	else if(method == SIMULATED_ANNEALING)
	{
		m_sortingMethod = "Simulated annealing";
		SimulatedAnnealingSort();
	}
	else if(method == RANDOMIZE)
	{
		m_sortingMethod = "Randomized";
		RandomizeSort();
	}

	QApplication::restoreOverrideCursor();
}

void VisualMatrix::RandomizeSort()
{
	QList<int> curOrdering;
	for(int i = 0; i < m_dissMatrix.size(); ++i)
		curOrdering.append(i);

	// randomize ordering
	for(int r = 0; r < m_dissMatrix.size(); ++r)
	{
		int p = rand() % m_dissMatrix.size();
		int q = rand() % m_dissMatrix.size();
		qSwap(curOrdering[p], curOrdering[q]);
	}

	// Set permutated matrix and labels
	Matrix permutedDissMatrix;
	QStringList permutedSampleLabels;
	foreach(uint indexR, curOrdering)
	{
		QVector<double> row;
		foreach(uint indexC, curOrdering)
			row.append(m_dissMatrix[indexR][indexC]);
		permutedDissMatrix.append(row);

		permutedSampleLabels.append(m_sampleLabels.at(indexR));
	}

	m_dissMatrix = permutedDissMatrix; 
	m_sampleLabels = permutedSampleLabels;
	SetData();
}

void VisualMatrix::SimulatedAnnealingSort()
{
	QList<int> curOrdering;
	for(int i = 0; i < m_dissMatrix.size(); ++i)
		curOrdering.append(i);

	// Perform simulated annealing to minimize cost
	// of dissimilarity matrix
	int N = m_dissMatrix.size();

	// calculate cost of initial ordering
	float C = 0.0;
	for(int i = 0; i < N; ++i)
		for(int j = i+1; j < N; ++j)
			C += (1.0 - m_dissMatrix[i][j])*(j-i);
	C = 2*C / N;

	int notChanged = 0;
	float T = -1.0;
	int iter = 0;
	float currentBestC = C;
	while(notChanged < 20)
	{
		float lastIterBestC = currentBestC;
		for(int move = 0; move < qMax<int>(N, 100); ++move)
		{
			// generate new state by swapping two adjacent elements
			uint r = rand() % (N-1);
			qSwap(curOrdering[r], curOrdering[r+1]);

			// calculte cost of new ordering
			float C = 0.0;
			for(int i = 0; i < N; ++i)
				for(int j = i+1; j < N; ++j)
					C += (1.0 - m_dissMatrix[curOrdering[i]][curOrdering[j]])*(j-i);
			C = 2*C / N;

			// set initial temperature on first iteration
			if(T < 0.0)
				T = -abs(currentBestC - C) / log(0.5);

			// accept new ordering with a given probability
			float acceptanceProb = exp((currentBestC - C)/T);
			float prob = float(rand()) /RAND_MAX;
			if(prob <= acceptanceProb)
				currentBestC = C;
			else
				qSwap(curOrdering[r], curOrdering[r+1]); // swap back
		}

		if(currentBestC == lastIterBestC)
			notChanged++;
		else
			notChanged = 0;

		T *= 0.98f;
		iter++;
	}	

	// Set permutated matrix and labels
	Matrix permutedDissMatrix;
	QStringList permutedSampleLabels;
	foreach(uint indexR, curOrdering)
	{
		QVector<double> row;
		foreach(uint indexC, curOrdering)
			row.append(m_dissMatrix[indexR][indexC]);
		permutedDissMatrix.append(row);

		permutedSampleLabels.append(m_sampleLabels.at(indexR));
	}

	m_dissMatrix = permutedDissMatrix; 
	m_sampleLabels = permutedSampleLabels;
	SetData();
}

void VisualMatrix::NeighbourhoodSort()
{
	const double sigma = 4.0;
	Matrix permutedDissMatrix = m_dissMatrix;
	int N = permutedDissMatrix.size();

	// *** Construct weight matrix
	Matrix W;
	double num = 2*sigma*sigma;
	for(int i = 0; i < N; ++i)
	{
		QVector<double> row;
		for(int j = 0; j < N; ++j)
		{
			double denom = (i-j)*(i-j);
			double weight = exp(-denom/num);
			row.append(weight);
		}

		W.append(row);
	}

	// *** Normalize weight matrix
	bool bDone = false;
	while(!bDone)
	{
		QList<double> rowNorms;
		for(int i = 0; i < N; ++i)
		{
			double sum = 0.0;
			for(int j = 0; j < N; ++j)
				sum += W.at(i).at(j);

			rowNorms.append(sum);
		}

		for(int i = 0; i < N; ++i)
		{
			for(int j = 0; j < N; ++j)
				W[i][j] = W[i][j] / rowNorms.at(i);
		}

		QList<double> colNorms;
		bDone = true;
		for(int i = 0; i < N; ++i)
		{
			double sum = 0.0;
			for(int j = 0; j < N; ++j)
				sum += W.at(j).at(i);

			colNorms.append(sum);

			if(sum > 1.01 || sum < 0.99)
				bDone = false;
		}

		for(int i = 0; i < N; ++i)
		{
			for(int j = 0; j < N; ++j)
				W[j][i] = W[j][i] / colNorms.at(i);
		}
	}

	// *** Perform neighbourhood sort
	QStringList permutedSampleLabels = m_sampleLabels;

	bool bChanged = true;
	uint iter = 0;
	while(bChanged && iter < 10000)
	{
		// 1. Calculate score of current permutation
		Matrix S(N, QVector<double>(N, 0.0));
		for(int i=0; i < N; ++i)
		{
			for(int j=0; j < N; ++j)
			{
				for(int k=0; k < N; ++k)
				{
					S[i][j] += permutedDissMatrix[i][k]*W[k][j];
				}
			}
		}

		// 2. Find optimal position for each 
		QList<uint> optimalPositions;
		for(int i=0; i < N; ++i)
		{
			double min = INT_MAX;
			uint index = 0;
			for(int j=0; j < N; ++j)
			{
				if(S[i][j] < min)
				{
					min = S[i][j];
					index = j;
				}
			}

			optimalPositions.append(index);
		}

		// 3. Determine new ordering (breaking ties in order of occurance)
		QVector<uint> newOrdering(N);

		uint currentPos = 0;
		for(int i = 0; i < N; ++i)
		{
			bool bPrevFound = false;
			for(int j=0; j < N; ++j)
			{
				if(optimalPositions.at(j) == i)
				{
					if(bPrevFound)
					{
						// a tie has occured
						newOrdering[j] = currentPos;
						currentPos++;
					}
					else
					{
						newOrdering[j] = currentPos;
						currentPos++;

						bPrevFound = true;
					}
				}
			}
		}

		// 4. Check if ordering has changed
		bChanged = false;
		for(int i = 0; i < N; ++i)
		{
			if(newOrdering.at(i) != i)
			{
				bChanged = true;
				break;
			}
		}

		// 5. If ordering has changed, permute matrix and continue
		if(bChanged)
		{
			Matrix prevDissMatrix = permutedDissMatrix;
			QStringList prevSampleLabels = permutedSampleLabels;

			permutedDissMatrix.clear();
			permutedSampleLabels.clear();
			foreach(uint indexR, newOrdering)
			{
				permutedSampleLabels.append(prevSampleLabels.at(indexR));

				QVector<double> row;
				foreach(uint indexC, newOrdering)
					row.append(prevDissMatrix[indexR][indexC]);
				permutedDissMatrix.append(row);
			}
		}

		iter++;
	}

	m_dissMatrix = permutedDissMatrix; 
	m_sampleLabels = permutedSampleLabels;
	SetData();
}

// Implementation based on description at:
//   http://www.weizmann.ac.il/home/fedomany/Bioinfo05/lecture4.pdf
void VisualMatrix::SideToSideSort()
{
	QList<int> curOrdering;
	for(int i = 0; i < m_dissMatrix.size(); ++i)
		curOrdering.append(i);

	bool bChanged = true;
	while(bChanged)
	{
		// 1. Calculate score of current permutation
		QList<Score> scores;
		for(int i = 0; i < m_dissMatrix.size(); ++i)
		{
			double score = 0.0;
			for(int j = 0; j < m_dissMatrix.size(); ++j)
			{
				double dist = m_dissMatrix[curOrdering[i]][curOrdering[j]];
				double xj = (j+1) - (m_dissMatrix.size() + 1.0) / 2.0;
				score += dist*xj;
			}

			scores.append(Score(score, curOrdering.at(i)));
		}

		// 2. Sort score vector in desending order.
		qSort(scores.begin(), scores.end(), ScoreSorter);

		// 3. Check if ordering has changed
		bChanged = false;
		for(int i = 0; i < m_dissMatrix.size(); ++i)
		{
			if(curOrdering.at(i) != scores.at(i).index)
			{
				bChanged = true;
				break;
			}
		}

		// 4. If ordering has changed, permute matrix and continue
		if(bChanged)
		{
			curOrdering.clear();
			foreach(Score scoreR, scores)
				curOrdering.append(scoreR.index);
		}
	}

	// Set permutated matrix and labels
	Matrix permutedDissMatrix;
	QStringList permutedSampleLabels;
	foreach(uint indexR, curOrdering)
	{
		QVector<double> row;
		foreach(uint indexC, curOrdering)
			row.append(m_dissMatrix[indexR][indexC]);
		permutedDissMatrix.append(row);

		permutedSampleLabels.append(m_sampleLabels.at(indexR));
	}

	m_dissMatrix = permutedDissMatrix; 
	m_sampleLabels = permutedSampleLabels;
	SetData();
}

QRectF VisualMatrix::boundingRect() const
{
	float width = qMax<float>(m_matrixSize + 2*BORDER_SIZE + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, 
																m_scene->views()[0]->viewport()->width());
	float height = qMax<float>(m_matrixSize + 2*BORDER_SIZE, 
															m_scene->views()[0]->viewport()->height());
	return QRectF(0, 0, width, height);
}

void VisualMatrix::SetData(const Matrix& dissMatrix, const QStringList& sampleLabels) 
{
	m_sortingMethod = "Unsorted";

	m_dissMatrix = dissMatrix; 
	m_sampleLabels = sampleLabels;

	SetData();
}

void VisualMatrix::SetData() 
{ 
	m_sampleIds.clear();
	foreach(const QString& sampleName, m_sampleLabels)
	{
		if(m_samples)	// will be NULL during unit tests
		{
			Sample sample;
			if(!m_samples->GetSample(sampleName, sample))
				Log::Inst().Error("Invalid sample specified in SetData(): " + sampleName);

			m_sampleIds.append(sample.GetId());
		}
	}

	m_minDist = INT_MAX;
	m_maxDist = -INT_MAX;
	m_distLabels.clear();
	if(m_dissMatrix.size() != 0)
	{
		// get labels for each cell
		for(int c = 0; c < m_dissMatrix.size(); ++c)
		{
			QStringList labelsForRow;
			for(int r = 0; r < m_dissMatrix.size(); ++r)
			{
				double dist = m_dissMatrix[r][c];
				labelsForRow.append(m_sampleLabels.at(r) + ", " + m_sampleLabels.at(c) + ": " + QString::number(dist, 'g', 3));

				if(dist < m_minDist && dist != 0.0)
					m_minDist = dist;

				if(dist > m_maxDist)
					m_maxDist = dist;
			}

			m_distLabels.append(labelsForRow);
		}
	}

	update();
}

void VisualMatrix::SetColorMap(const QString& colorMapName)
{
	m_colorMapName = colorMapName;
	update();
}

void VisualMatrix::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	const int DRAW_BORDER_SIZE = 5;

	painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing, false);

	uint width = m_scene->views()[0]->viewport()->width();
	uint height = m_scene->views()[0]->viewport()->height();

	uint matrixWidth = width-2*BORDER_SIZE;
	uint matrixHeight = height-2*BORDER_SIZE;

	// ** Set range of color map
	QwtLinearColorMapPtr colorMap = m_colorMaps->GetColorMap(m_colorMapName);
	QwtInterval colorMapInterval;
	if(m_bFullColorMapRange)
	{
		colorMapInterval.setMinValue(0);
		colorMapInterval.setMaxValue(qMax<double>(m_maxDist, 1.0));
	}
	else
	{
		colorMapInterval.setMinValue(m_minDist);
		colorMapInterval.setMaxValue(m_maxDist);
	}

	// ** Set mapping from rows to visible samples
	m_visibleRowToSampleId.clear();
	uint visibleSamples = 0;
	uint originalRow = 0;
	foreach(uint sampleId, m_sampleIds)
	{
		Sample sample = m_samples->GetSample(sampleId);
		if(sample.IsVisible())
		{
			m_visibleRowToOriginalRow.insert(visibleSamples, originalRow);
			m_visibleRowToSampleId.insert(visibleSamples, sampleId);
			visibleSamples++;
		}

		originalRow++;
	}
	
	if(m_dissMatrix.size() != 0)
	{
		m_cellSize = qMin<uint>(matrixWidth, matrixHeight) / visibleSamples;
		if(m_cellSize < m_minCellSize)
			m_cellSize = m_minCellSize;

		if(m_matrixSize != m_cellSize*visibleSamples)
		{
			m_matrixSize = m_cellSize*visibleSamples;
			ColorMapScaleChanged();
		}		

		m_scene->setSceneRect(0, 0, 
									m_matrixSize + 2*BORDER_SIZE + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, 
									m_matrixSize + 2*BORDER_SIZE);

		// ** draw hatch patten as background
		painter->setBrush(QBrush(Qt::gray, Qt::BDiagPattern));
		painter->setPen(Qt::NoPen);
		painter->drawRect(BORDER_SIZE, BORDER_SIZE, m_matrixSize, m_matrixSize);

		// ** Mark selected samples
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->setPen(Properties::Inst().GetHighlightPen());
		QSet<uint> selectedSampleIds = m_samples->GetSelectedSampleIds();
		for(uint r = 0; r < visibleSamples; ++r)
		{
			uint visibleId = m_visibleRowToSampleId[r];
			if(selectedSampleIds.contains(visibleId))
			{
				painter->drawRect(BORDER_SIZE + r*m_cellSize, SAMPLE_COL_START-HIGHLIGHT_OFFSET, 
															m_cellSize, (SAMPLE_COL_END-SAMPLE_COL_START)+2*HIGHLIGHT_OFFSET);

				painter->drawRect(SAMPLE_COL_START-HIGHLIGHT_OFFSET, BORDER_SIZE + r*m_cellSize, 
															(SAMPLE_COL_END-SAMPLE_COL_START)+2*HIGHLIGHT_OFFSET, m_cellSize);
			}
		}

		// ** Draw matrix
		for(uint c = 0; c < visibleSamples; ++c)
		{
			uint colId = m_visibleRowToOriginalRow.value(c);

			QStringList labelsForRow;
			for(uint r = 0; r < visibleSamples; ++r)
			{
				uint rowId = m_visibleRowToOriginalRow.value(r);
				
				double dist = m_dissMatrix[rowId][colId];

				QColor color;
				if(!m_bThreshold || dist < m_thresholdMarker->GetValue())
					color = colorMap->color(colorMapInterval, dist);
				else
					color = colorMap->color(colorMapInterval, qMax<float>(1.0, m_maxDist));

				if(m_bApplySelectionTransparency && selectedSampleIds.size() > 0)
				{
					// make non-selected items more transparent
					uint visibleColId = m_visibleRowToSampleId[c];
					uint visibleRowId = m_visibleRowToSampleId[r];					
					if(!selectedSampleIds.contains(visibleColId) || !selectedSampleIds.contains(visibleRowId))
						color.setAlpha(Properties::Inst().GetSelectionOpacity());
				}
					
				QBrush brush(color);
				painter->setBrush(brush);

				if(!m_bFullColorMapRange && r == c)
				{
					brush.setStyle(Qt::BDiagPattern);
					brush.setColor(Qt::black);
				}

				if(m_cellSize < DRAW_BORDER_SIZE)
					painter->setPen(Qt::NoPen);
				else
				{
					QPen pen;
					pen.setCosmetic(true);
					pen.setColor(Qt::white);
					painter->setPen(pen);
				}

				painter->drawRect(BORDER_SIZE + r*m_cellSize, BORDER_SIZE + c*m_cellSize, m_cellSize, m_cellSize);
				//painter->drawEllipse(BORDER_SIZE + r*m_cellSize, BORDER_SIZE + c*m_cellSize, m_cellSize, m_cellSize);
			}
		}

		// ** Mark square around selected samples
		painter->setBrush(Qt::NoBrush);
		painter->setPen(Properties::Inst().GetHighlightPen());
		QList<uint> selectedCells;
		for(uint r = 0; r < visibleSamples; ++r)
		{
			uint visibleId = m_visibleRowToSampleId[r];
			if(selectedSampleIds.contains(visibleId))
			{
				selectedCells.append(r);
			}
			else
			{
				if(selectedCells.size() > 0)
				{
					uint start = selectedCells.at(0);
					uint end = selectedCells.at(selectedCells.size()-1);
					painter->drawRect(BORDER_SIZE + start*m_cellSize, BORDER_SIZE + start*m_cellSize, 
															(end-start+1)*m_cellSize, (end-start+1)*m_cellSize);

				}

				selectedCells.clear();
			}
		}

		if(selectedCells.size() > 0)
		{
			uint start = selectedCells.at(0);
			uint end = selectedCells.at(selectedCells.size()-1);
			painter->drawRect(BORDER_SIZE + start*m_cellSize, BORDER_SIZE + start*m_cellSize, 
													(end-start+1)*m_cellSize, (end-start+1)*m_cellSize);

		}

		// ** Draw sample marker row and column
		for(uint c = 0; c < visibleSamples; ++c)
		{
			uint visibleId = m_visibleRowToSampleId[c];

			QColor color = m_samples->GetSample(visibleId).GetColor();

			if(m_cellSize < DRAW_BORDER_SIZE)
				painter->setPen(QPen(color));
			else
				painter->setPen(Qt::white);

			painter->setBrush(QBrush(color));

			painter->drawRect(BORDER_SIZE + c*m_cellSize, SAMPLE_COL_START, m_cellSize, SAMPLE_COL_END-SAMPLE_COL_START);
			painter->drawRect(SAMPLE_COL_START, BORDER_SIZE + c*m_cellSize, SAMPLE_COL_END-SAMPLE_COL_START, m_cellSize);
		}

		// ** Draw colour map
		QLinearGradient linearGradient = m_colorMaps->GetLinearGradient(m_colorMapName);
		linearGradient.setStart(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + 0.5*COLOR_MAP_WIDTH, BORDER_SIZE + m_matrixSize);
		linearGradient.setFinalStop(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + 0.5*COLOR_MAP_WIDTH, BORDER_SIZE);
		
		painter->setPen(Qt::black);
		painter->setBrush(QBrush(linearGradient));
		painter->drawRect(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE, COLOR_MAP_WIDTH, m_matrixSize);

		if(m_bThreshold)
		{
			QColor color = colorMap->color(colorMapInterval, qMax<float>(1.0, m_maxDist));
			painter->setBrush(color);
			painter->drawRect(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE, 
																		COLOR_MAP_WIDTH, m_thresholdMarker->GetPos().y()-BORDER_SIZE);
		}

		// ** Colour map text
		painter->setPen(Qt::black);

		int labelOffset = 0.5 * painter->fontMetrics().ascent();

		QString minDist, maxDist;
		if(m_bFullColorMapRange)
		{
			minDist = "0.0";
			if(m_maxDist <= 1.0)
				maxDist = "1.0";
			else
				maxDist = QString::number(m_maxDist, 'g', 3);
		}
		else
		{
			minDist = QString::number(m_minDist, 'g', 3);
			maxDist = QString::number(m_maxDist, 'g', 3);
		}

		painter->drawText(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH + 5, BORDER_SIZE + labelOffset, maxDist);
		painter->drawText(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH + 5, BORDER_SIZE + m_matrixSize + labelOffset, minDist);
		
		// *** Draw borders around matrix, sample marker row, sample marker column, and colour map
		QPen outlinePen;
		outlinePen.setCosmetic(true);
		outlinePen.setColor(Qt::black);
		painter->setPen(outlinePen);

		painter->drawLine(BORDER_SIZE, BORDER_SIZE, BORDER_SIZE + m_matrixSize, BORDER_SIZE);
		painter->drawLine(BORDER_SIZE + m_matrixSize, BORDER_SIZE, BORDER_SIZE + m_matrixSize, BORDER_SIZE + m_matrixSize);
		painter->drawLine(BORDER_SIZE + m_matrixSize, BORDER_SIZE + m_matrixSize, BORDER_SIZE, BORDER_SIZE + m_matrixSize);
		painter->drawLine(BORDER_SIZE, BORDER_SIZE + m_matrixSize, BORDER_SIZE, BORDER_SIZE);

		painter->drawLine(BORDER_SIZE, SAMPLE_COL_START, BORDER_SIZE + m_matrixSize, SAMPLE_COL_START);
		painter->drawLine(BORDER_SIZE + m_matrixSize, SAMPLE_COL_START, BORDER_SIZE + m_matrixSize, SAMPLE_COL_END);
		painter->drawLine(BORDER_SIZE + m_matrixSize, SAMPLE_COL_END, BORDER_SIZE, SAMPLE_COL_END);
		painter->drawLine(BORDER_SIZE, SAMPLE_COL_END, BORDER_SIZE, SAMPLE_COL_START);

		painter->drawLine(SAMPLE_COL_START, BORDER_SIZE, SAMPLE_COL_START, BORDER_SIZE + m_matrixSize);
		painter->drawLine(SAMPLE_COL_START, BORDER_SIZE + m_matrixSize, SAMPLE_COL_END, BORDER_SIZE + m_matrixSize);
		painter->drawLine(SAMPLE_COL_END, BORDER_SIZE + m_matrixSize, SAMPLE_COL_END, BORDER_SIZE);
		painter->drawLine(SAMPLE_COL_END, BORDER_SIZE, SAMPLE_COL_START, BORDER_SIZE);

		painter->drawLine(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE, 
												BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE);
		painter->drawLine(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE,
												BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE + m_matrixSize);
		painter->drawLine(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE + m_matrixSize,
												BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE + m_matrixSize);
		painter->drawLine(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE + m_matrixSize,
												BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET, BORDER_SIZE);
	}
}

void VisualMatrix::resizeEvent(QResizeEvent* e)
{
	update();
}

void VisualMatrix::hoverMoveEvent(QGraphicsSceneHoverEvent* e)
{
	static int prevCellX = -1;
	static int prevCellY = -1;

	if(m_dissMatrix.size() == 0)
		return;

	QPointF mousePos = e->pos();

	int cellX = (mousePos.x() - BORDER_SIZE) / m_cellSize;
	int cellY = (mousePos.y() - BORDER_SIZE) / m_cellSize;

	if(cellX >= 0 && cellX < m_distLabels.size() && cellY >= 0 && cellY < m_distLabels.size())
	{
		uint origX = m_visibleRowToOriginalRow.value(cellX);
		uint origY = m_visibleRowToOriginalRow.value(cellY);

		if(cellX != prevCellX || cellY != prevCellY)
			m_reportLabel->setText(m_distLabels.at(origX).at(origY));
	}
	else
	{
		m_reportLabel->setText("");
	}

	prevCellX = cellX;
	prevCellY = cellY;
}

void VisualMatrix::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
	static int prevCellX = -1;

	QPointF mousePos = e->pos();

	if(mousePos.x() < BORDER_SIZE || mousePos.y() < SAMPLE_COL_START 
			|| mousePos.x() > BORDER_SIZE + m_matrixSize || mousePos.y() > BORDER_SIZE + m_matrixSize)
	{
		// selected point is outside of the matrix area
		if(e->modifiers() != Qt::ControlModifier && e->modifiers() != Qt::ShiftModifier)
			m_samples->ClearSelectedSamples();
	}
	else if(e->button() == Qt::LeftButton)
	{
		int cellX = (mousePos.x() - BORDER_SIZE) / m_cellSize;

		uint visibleId = m_visibleRowToSampleId.value(cellX);

		if(e->modifiers() == Qt::ControlModifier)
		{	
			// add row to selection set
			QSet<uint> sampleId;
			sampleId.insert(visibleId);
			m_samples->ToggleSelectedSamples(sampleId);
		}
		else if(e->modifiers() == Qt::ShiftModifier)
		{
			// select all rows between previously selected row and 
			// the currently selected row
			uint minRow = qMin<uint>(cellX, prevCellX);
			uint maxRow = qMax<uint>(cellX, prevCellX);

			QSet<uint> sampleIds;
			for(uint r = minRow; r <= maxRow; ++r)
			{
				uint sampleId = m_visibleRowToSampleId.value(r);
				sampleIds.insert(sampleId);
			}

			m_samples->SetSamplesToSelected(sampleIds);
		}
		else
		{
			// set selection set to the sample id of the specified row
			m_samples->ClearSelectedSamples();
			m_samples->SetSampleToSelected(visibleId);
		}

		prevCellX = cellX;
	}
	
	update();

	QGraphicsItem::mousePressEvent(e);
}

void VisualMatrix::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e)
{
	QPointF mousePos = e->pos();

	if(e->button() == Qt::LeftButton &&
			mousePos.x() >= BORDER_SIZE && mousePos.y() >= SAMPLE_COL_START 
			&& mousePos.x()<= BORDER_SIZE + m_matrixSize && mousePos.y() <= SAMPLE_COL_END)
	{
		int cellX = (mousePos.x() - BORDER_SIZE) / m_cellSize;
		uint visibleId = m_visibleRowToSampleId.value(cellX);

		// find all adjacent cells of the same colour
		QColor color = m_samples->GetSample(visibleId).GetColor();
		QSet<uint> selectedSampleIds;
		selectedSampleIds.insert(visibleId);

		int minX = cellX;
		while(minX-1 >= 0)
		{
			visibleId = m_visibleRowToSampleId.value(minX-1);
			if(m_samples->GetSample(visibleId).GetColor() != color)
				break;

			minX--;
			selectedSampleIds.insert(visibleId);
		}

		int maxX = cellX;
		while(maxX+1 < m_visibleRowToSampleId.size())
		{
			visibleId = m_visibleRowToSampleId.value(maxX+1);
			if(m_samples->GetSample(visibleId).GetColor() != color)
				break;

			maxX++;
			selectedSampleIds.insert(visibleId);
		}

		if(e->modifiers() == Qt::ControlModifier || e->modifiers() == Qt::ShiftModifier)
		{	
			// add row to selection set
			m_samples->SetSamplesToSelected(selectedSampleIds);
		}
		else
		{
			// set selection set to the sample of the specified row
			m_samples->ClearSelectedSamples();
			m_samples->SetSamplesToSelected(selectedSampleIds);
		}
	}

	update();
}

void VisualMatrix::ColorMapScaleChanged()
{
	// ** Set slider position
	float curValue = m_thresholdMarker->GetValue();

	QPointF sliderStart(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE + m_matrixSize);
	QPointF sliderEnd(BORDER_SIZE + m_matrixSize + COLOR_MAP_OFFSET + COLOR_MAP_WIDTH, BORDER_SIZE);
	m_thresholdMarker->SetSliderRange(sliderStart, sliderEnd);
	if(m_bFullColorMapRange)
		m_thresholdMarker->SetValueRange(0.0, qMax<float>(1.0, m_maxDist));
	else
		m_thresholdMarker->SetValueRange(m_minDist, m_maxDist);

	// make sure new range is within value range of color map
	m_thresholdMarker->SetValue(curValue);
	if(!m_bFullColorMapRange)
	{
		if(curValue > m_maxDist)
			m_thresholdMarker->SetValue(m_maxDist);
		else if(curValue < m_minDist)
			m_thresholdMarker->SetValue(m_minDist);
	}

	m_thresholdMarker->update();
}

void VisualMatrix::SetColorMapThreshold(bool bThreshold) 
{ 
	m_bThreshold = bThreshold; 

	m_thresholdMarker->setVisible(bThreshold);
	if(bThreshold)
		m_thresholdMarker->update();

	update(); 
}