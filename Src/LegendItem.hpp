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

#ifndef _LEGEND_ITEM_HPP_
#define _LEGEND_ITEM_HPP_

#include "stdafx.h"

/**
 * @class LegendItem
 * @brief Widget representing a legend item.
 */
class LegendItem: public QWidget
{
	Q_OBJECT

public:
	LegendItem(QWidget* parent = 0);

	virtual ~LegendItem() {}

	/** Get checkbox. */
	QCheckBox* GetCheckbox() const { return m_checkbox; }

	/** Check legend item. */
	void SetChecked() { m_checkbox->setCheckState(Qt::Checked); }

	/** Uncheck legend item. */
	void SetUnchecked() { m_checkbox->setCheckState(Qt::Unchecked); }

	/** Partially check legend item. */
	void SetPartiallyChecked() { m_checkbox->setCheckState(Qt::PartiallyChecked); }

	/** Set flag indicating if plot symbol is to be shown in the legend. */
	void setItemMode( QwtLegend::LegendItemMode m) { m_legendItem->setItemMode(m); }

	/** Set legend item text. */
	void setText( const QwtText & t) { m_legendItem->setText(t); }

	/** Set pixmap representing legend symbol. */
	void setIdentifier( const QPixmap & p) { m_legendItem->setIdentifier(p); }

	/** Set size of legend symbol. */
	void setIdentifierSize( const QSize & s) { m_legendItem->setIdentifierSize(s); }

	/** Get size of legend symbol. */
	QSize identifierSize() const { return m_legendItem->identifierSize(); }

private:
	/** Handle right-click pop-up menu. */
	virtual void contextMenuEvent(QContextMenuEvent * event);

signals:
	/** Signal indicating the samples associated with this legend item should be made visible in all views. */
	void GuaranteeVisibility();

	/** Signal indicating the user wishes to change the visual properties of this lengend item. */ 
	void ChangeProperties();

	/** Signal indicating all samples in this legend item should be selected. */
	void SelectSamples();

	/** Signal indicating the legend item was clicked. */
	void CheckboxClicked();

private:
	/** Checkbox used to set visibility of samples associated with legend item. */
	QCheckBox* m_checkbox;

	/** Widget to paint the legend symbol. */
	QwtLegendItem* m_legendItem;
};

/**
 * @class PlotMarkerLegend
 * @brief Plot marker which returns a custom legend item.
 */
class PlotMarkerLegend: public QwtPlotMarker
{
public:
	/** Constructor. */
	PlotMarkerLegend(): QwtPlotMarker() {}

	/** Destructor. */
	virtual ~PlotMarkerLegend() {}

	/** Get widget used to represent legend item in the legend frame. */
	virtual QWidget* legendItem() const;

	/** Update widget representing a legend item. */
	virtual void updateLegend( QwtLegend * ) const;
};

#endif

