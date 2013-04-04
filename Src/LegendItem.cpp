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

#include "LegendItem.hpp"

#include "Log.hpp"

#include "Metadata.hpp"

LegendItem::LegendItem(QWidget* parent): QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setAlignment(Qt::AlignVCenter);
	layout->setMargin(0);

	m_checkbox = new QCheckBox(this);
	m_checkbox->setChecked(true);
	layout->addWidget(m_checkbox);

	m_legendItem = new QwtLegendItem(this);
	layout->addWidget(m_legendItem);

	QObject::connect(m_legendItem, SIGNAL(clicked()), this, SIGNAL(ChangeProperties()));
	QObject::connect(m_checkbox, SIGNAL(stateChanged(int)), this, SIGNAL(CheckboxClicked()));
}

void LegendItem::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu menu;
	menu.addAction("Guarantee visibility", this, SIGNAL(GuaranteeVisibility()));
	menu.addSeparator();
	menu.addAction("Select samples", this, SIGNAL(SelectSamples()));
	menu.addSeparator();
	menu.addAction("Change properties", this, SIGNAL(ChangeProperties()));

	menu.exec(event->globalPos());
}

QWidget* PlotMarkerLegend::legendItem() const
{
	LegendItem* item = new LegendItem;
	if(plot())
	{
		QObject::connect(item, SIGNAL(clicked()), plot(), SLOT(legendItemClicked()));
		QObject::connect(item, SIGNAL(checked(bool)), plot(), SLOT(legendItemChecked(bool)));
	}

	return item;
}

void PlotMarkerLegend::updateLegend(QwtLegend* legend) const
{
	if ( legend == NULL )
		return;

	if ( legend && testItemAttribute( QwtPlotItem::Legend ) && symbol() && symbol()->style() != QwtSymbol::NoSymbol )
	{
		QWidget *lgdItem = legend->find( this );
		if ( lgdItem == NULL )
		{
			lgdItem = legendItem();
			if ( lgdItem )
				legend->insert( this, lgdItem );
		}

		LegendItem *l = qobject_cast<LegendItem *>( lgdItem );
		if ( l )
			l->setIdentifierSize( symbol()->boundingSize() );
	}

	QWidget *lgdItem = legend->find( this );
	if ( testItemAttribute( QwtPlotItem::Legend ) )
	{
		LegendItem *label = qobject_cast<LegendItem *>( lgdItem );
		if ( label )
		{
			// paint the identifier
			const QSize sz = label->identifierSize();

			QPixmap identifier( sz.width(), sz.height() );
			identifier.fill( Qt::transparent );

			QPainter painter( &identifier );
			painter.setRenderHint( QPainter::Antialiasing, testRenderHint( QwtPlotItem::RenderAntialiased ) );
			drawLegendIdentifier( &painter, QRect( 0, 0, sz.width(), sz.height() ) );
			painter.end();

			const bool doUpdate = label->updatesEnabled();
			if ( doUpdate )
				label->setUpdatesEnabled( false );

			label->setText( title() );
			label->setIdentifier( identifier );
			label->setItemMode( legend->itemMode() );

			if ( doUpdate )
				label->setUpdatesEnabled( true );

			label->update();
		}
	}
	else
	{
		if ( lgdItem )
		{
			lgdItem->hide();
			lgdItem->deleteLater();
		}
	}
}
