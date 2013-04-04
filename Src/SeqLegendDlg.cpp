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

#include "SeqLegendDlg.hpp"

#include "Log.hpp"
#include "SeqMetadata.hpp"

SeqLegendDlg::SeqLegendDlg(SeqMetadataPtr seqMetadata, QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags), m_seqMetadata(seqMetadata), m_otherPercentage(5.0)
{
	ui.setupUi(this);

	QObject::connect(ui.btnOtherPercentage, SIGNAL(clicked()), this, SLOT(ChangeOtherPercentage()));

	updateGeometry();
}

SeqLegendDlg::~SeqLegendDlg()
{

}

void SeqLegendDlg::SetLegend(const QMap<QString, QColor>& legend, const QMap<QString, float>& percentages, bool bNumeric)
{	
	Log::Inst().Debug("SeqLegendDlg::SetLegend(...)");

	m_legend = legend;
	m_percentages = percentages;
	m_bNumeric = bNumeric;

	// clear previous legend items
	//qDeleteAll(m_legendItems);
	//m_legendItems.clear();

	// setup new legend
	QVBoxLayout *vlay = new QVBoxLayout();
	vlay->setSizeConstraint(QLayout::SetMinAndMaxSize);
	vlay->setContentsMargins(0, 6, 0, 6);
	vlay->setSpacing(0);

	QList<QString> keys = legend.keys();
	if(bNumeric)
		qSort(keys.begin(), keys.end(), numericStrLessThan);
	else
		qSort(keys.begin(), keys.end(), caseInsensitiveLessThan);

	float otherPercentageTotal = 0.0;
	QColor otherColor;

	float missingDataTotal = 0.0;
	QColor missingDataColor;

	foreach(const QString& key, keys)
	{
		float percentage = percentages.value(key);
		if(percentage < GetOtherPercentage())
		{
			otherPercentageTotal += percentage;
			otherColor = legend.value(key);		
			continue;
		}

		if(key == "" || key == "X")
		{
			missingDataTotal += percentage;
			missingDataColor = legend.value(key);	
			continue;
		}

		QColor color = legend.value(key);		
		QString label = key + " (" + QString::number(percentage, 'g', 3) + ")";

		QHBoxLayout *hlay = new QHBoxLayout();
		hlay->setSizeConstraint(QLayout::SetMinAndMaxSize);
		hlay->setContentsMargins(0, 0, 0, 0);

		/****
		QwtSymbol symbol(QwtSymbol::Rect, QBrush(color, Qt::SolidPattern), QPen(Qt::black, 1), QSize(14, 14));
		QwtLegendItem* legendItem = new QwtLegendItem(symbol, QPen(Qt::black), label);
		legendItem->setIdentifierMode(QwtLegendItem::ShowSymbol | QwtLegendItem::ShowText);
		legendItem->setItemMode(QwtLegend::ClickableItem);
		legendItem->setWindowTitle(key);
		legendItem->setIdentifierWidth(20);
		m_legendItems.append(legendItem);

		hlay->addWidget(legendItem);	

		QSpacerItem *horizontalSpacer = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
		hlay->addItem(horizontalSpacer);
		hlay->setSpacing(0);

		QObject::connect(legendItem, SIGNAL(clicked()), this, SLOT(ChangeLegendItem()));

		vlay->addLayout(hlay);
				****/
	}

	// other percentage category
	if(missingDataTotal != 0.0)
	{
		/***
		QColor color = missingDataColor;		
		QString label = "Missing data (" + QString::number(missingDataTotal, 'g', 3) + ")";

		QHBoxLayout *hlay = new QHBoxLayout();
		hlay->setSizeConstraint(QLayout::SetMinAndMaxSize);
		hlay->setContentsMargins(0, 0, 0, 0);

		QwtSymbol symbol(QwtSymbol::Rect, QBrush(color, Qt::SolidPattern), QPen(Qt::black, 1), QSize(14, 14));
		QwtLegendItem* legendItem = new QwtLegendItem(symbol, QPen(Qt::black), label);
		legendItem->setIdentifierMode(QwtLegendItem::ShowSymbol | QwtLegendItem::ShowText);
		legendItem->setItemMode(QwtLegend::ClickableItem);
		legendItem->setWindowTitle("Missing data");
		legendItem->setIdentifierWidth(20);
		m_legendItems.append(legendItem);

		hlay->addWidget(legendItem);	

		QSpacerItem *horizontalSpacer = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
		hlay->addItem(horizontalSpacer);
		hlay->setSpacing(0);

		QObject::connect(legendItem, SIGNAL(clicked()), this, SLOT(ChangeLegendItem()));

		vlay->addLayout(hlay);
		***/
	}

	// missing data percentage category
	if(otherPercentageTotal != 0.0)
	{
		/***
		QColor color = otherColor;		
		QString label = "Other (" + QString::number(otherPercentageTotal, 'g', 3) + ")";

		QHBoxLayout *hlay = new QHBoxLayout();
		hlay->setSizeConstraint(QLayout::SetMinAndMaxSize);
		hlay->setContentsMargins(0, 0, 0, 0);

		QwtSymbol symbol(QwtSymbol::Rect, QBrush(color, Qt::SolidPattern), QPen(Qt::black, 1), QSize(14, 14));
		QwtLegendItem* legendItem = new QwtLegendItem(symbol, QPen(Qt::black), label);
		legendItem->setIdentifierMode(QwtLegendItem::ShowSymbol | QwtLegendItem::ShowText);
		legendItem->setItemMode(QwtLegend::ClickableItem);
		legendItem->setWindowTitle("Other");
		legendItem->setIdentifierWidth(20);
		m_legendItems.append(legendItem);

		hlay->addWidget(legendItem);	

		QSpacerItem *horizontalSpacer = new QSpacerItem(10, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
		hlay->addItem(horizontalSpacer);
		hlay->setSpacing(0);

		QObject::connect(legendItem, SIGNAL(clicked()), this, SLOT(ChangeLegendItem()));

		vlay->addLayout(hlay);
		***/
	}

	// show new lengend layout
	QSpacerItem *verticalSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
	vlay->addItem(verticalSpacer);
	
	//delete ui.scrollArea->widget()->layout();
	//ui.scrollArea->widget()->setLayout(vlay);
}

void SeqLegendDlg::ChangeLegendItem()
{
	Log::Inst().Debug("SeqLegendDlg::ChangeLegendItem()");

	if(sender()->isWidgetType())
	{
		/***
		QwtLegendItem* legendItem = (QwtLegendItem*)sender();
		
		QColor color = QColorDialog::getColor(legendItem->symbol().brush().color(), this, "Select color", QColorDialog::ShowAlphaChannel);
		if(color.isValid())
		{	
			// set new color
			QwtSymbol newSymbol = legendItem->symbol();
			QBrush newBrush = newSymbol.brush();
			newBrush.setColor(color);
			newSymbol.setBrush(newBrush);

			legendItem->setSymbol(newSymbol);

			QString category = legendItem->windowTitle();
			if(category == "Other")
				m_seqMetadata->SetOtherColor(color);
			else if(category == "Missing data")
				m_seqMetadata->SetMissingDataColor(color);
			else
				m_legend[category] = color;

			m_seqMetadata->SetColorMap(m_legend);

			//emit Changed();
		}		
		***/
	}
}

void SeqLegendDlg::ChangeOtherPercentage()
{
	Log::Inst().Debug("SeqLegendDlg::ChangeOtherPercentage()");

	m_otherPercentage = ui.spinOtherPercentage->value();
	emit OtherPercentageChanged();
}