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

#ifndef _PARALLEL_COORD_SELECTION_
#define _PARALLEL_COORD_SELECTION_

#include "stdafx.h"

#include "Samples.hpp"
#include "ParallelCoordCurve.hpp"

class ParallelCoordSelectionMachine: public QwtPickerMachine
{
public:
	ParallelCoordSelectionMachine(): QwtPickerMachine(QwtPickerMachine::RectSelection), m_bAddToSelection(false) { }

  virtual QList< Command > transition(const QwtEventPattern& eventPattern, const QEvent* e)
	{
		QList< Command > cmdList;

		switch(e->type())
		{
			case QEvent::MouseButtonPress:
			{
				const QMouseEvent *mouseEvent = (QMouseEvent*)e;

				if(eventPattern.mouseMatch(QwtEventPattern::MouseSelect1, mouseEvent)
						|| (mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ControlModifier)
						|| (mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ShiftModifier))
				{
					if(state() == 0)
					{
						cmdList += Begin;
						cmdList += Append;
						cmdList += Append;
						setState(2);
					}

					if(mouseEvent->modifiers() == Qt::ControlModifier || mouseEvent->modifiers() == Qt::ShiftModifier)
						m_bAddToSelection = true;
					else 
						m_bAddToSelection = false;
				}
				break;
			}

			case QEvent::MouseMove:
			case QEvent::Wheel:
			{
				if ( state() != 0 )
					cmdList += Move;
				break;
			}

			case QEvent::MouseButtonRelease:
			{
				if ( state() == 2 )
				{
					cmdList += End;
					setState(0);
				}
				break;
			}

			case QEvent::KeyPress:
			{
				if(eventPattern.keyMatch(QwtEventPattern::KeySelect1, (const QKeyEvent *)e))
				{
					if ( state() == 0 )
					{
						cmdList += Begin;
						cmdList += Append;
						cmdList += Append;
						setState(2);
					}
					else
					{
						cmdList += End;
						setState(0);
					}
				}
				break;
			}

			default:
			break;
		}

		return cmdList;
	}

	bool IsAddToSelection() const { return m_bAddToSelection; }

private:
	bool m_bAddToSelection;
};

class ParallelCoordSelection: public QwtPlotPicker
{
	Q_OBJECT

public:
    ParallelCoordSelection(QwtPlotCanvas *canvas, SamplesPtr samples)
			:QwtPlotPicker(canvas), m_canvas(canvas), m_samples(samples), m_bAddToSelection(false)
    {
			// We want the focus, but no focus rect. The selected point will be highlighted instead.
			m_stateMachine = new ParallelCoordSelectionMachine();
			setStateMachine(m_stateMachine);
      setTrackerMode(QwtPicker::AlwaysOn);
			setRubberBand(QwtPicker::RectRubberBand);

			QPen rubberBandPen(QPen(QColor(150, 190, 240)));
			rubberBandPen.setStyle(Qt::DashLine);
			rubberBandPen.setWidth(2);
			setRubberBandPen(rubberBandPen);

			setEnabled(true);

			QObject::connect(this, SIGNAL(selected(const QRectF&)), this, SLOT(ProcessRect(const QRectF&)));
    }

		virtual QwtText trackerText(const QPoint& pos) const
		{
			// find all points near cursor
			QSet<uint> nearbySampleIds = GetNearbySamples(pos);

			QString tooltipStr;
			if(nearbySampleIds.size() != 0)
			{				
				foreach(uint sampleId, nearbySampleIds)
					tooltipStr += m_samples->GetSample(sampleId).GetName() + QString(", ");
				tooltipStr = tooltipStr.left(tooltipStr.size()-2);
			}

			QwtText tooltipText;
			if(!tooltipStr.isEmpty())
			{
				tooltipText.setText(tooltipStr);
				tooltipText.setBackgroundBrush(QBrush(QColor(255,255,255,192)));
			}

			return tooltipText;
		}

private slots:
	void ProcessRect(const QRectF &rect)
	{
		if(rect.width() == 0 && rect.height() == 0)
		{
			QPoint mousePos = transform(QPointF(rect.x(), rect.y()));

			// user has clicked on one or more points
			QSet<uint> selectedSampleIds = GetNearbySamples(mousePos);

			if(m_stateMachine->IsAddToSelection())
				m_samples->ToggleSelectedSamples(selectedSampleIds);
			else
			{
				m_samples->ClearSelectedSamples();
				m_samples->SetSamplesToSelected(selectedSampleIds);
			}
		}
		else
		{
			// user has drawn a bounding box around points
			QSet<uint> selectedSampleIds;

			const QwtPlotItemList& itmList = plot()->itemList();
			for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it)
			{
				if((*it)->rtti() == ParallelCoordCurve::Rtti_ParallelCoordCurve)
				{
					ParallelCoordCurve *curve = (ParallelCoordCurve*)(*it);
					
					for(uint i = 0; i < curve->dataSize(); ++i)
					{
						if(rect.contains(curve->sample(i)))
						{
							selectedSampleIds.insert(curve->GetSampleId());
							break;
						}
					}
				}
			}

			if(m_stateMachine->IsAddToSelection())
				m_samples->SetSamplesToSelected(selectedSampleIds);
			else
			{
				m_samples->ClearSelectedSamples();
				m_samples->SetSamplesToSelected(selectedSampleIds);
			}
		}

		emit SelectionSetChanged();
	}

	QSet<uint> GetNearbySamples(const QPoint& mousePos) const
	{
		QSet<uint> nearbySamples;

		const QwtPlotItemList& itmList = plot()->itemList();
		for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it)
		{
			if((*it)->rtti() == ParallelCoordCurve::Rtti_ParallelCoordCurve)
			{
				ParallelCoordCurve *curve = (ParallelCoordCurve*)(*it);

				for(uint i = 0; i < curve->dataSize(); ++i)
				{
					QPoint pt = transform(curve->sample(i));
					float distSqrd = (mousePos.x() - pt.x())*(mousePos.x() - pt.x()) 
															+ (mousePos.y() - pt.y())*(mousePos.y() - pt.y());

					if(distSqrd < 25) // clicked point is within 5 pixels of marker center
						nearbySamples.insert(curve->GetSampleId());
				}
			}
		}

		return nearbySamples;
	}

signals:
	void SelectionSetChanged();

private:
	QwtPlotCanvas* m_canvas;
	ParallelCoordSelectionMachine* m_stateMachine;

	SamplesPtr m_samples;

	bool m_bAddToSelection;
};

#endif