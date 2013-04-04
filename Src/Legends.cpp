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

#include "Legends.hpp"

#include "LegendItem.hpp"
#include "Log.hpp"
#include "Samples.hpp"
#include "ColorMaps.hpp"

Legends::Legends(QwtLegend* colorLegend, QwtLegend* shapeLegend, QwtLegend* sizeLegend, 
								  QGroupBox* colorGroupBox, QGroupBox* shapeGroupBox, 
									QGroupBox* sizeGroupBox, ColorMapsPtr colorMaps)
	: m_colorLegend(colorLegend), m_shapeLegend(shapeLegend), m_sizeLegend(sizeLegend),
		m_colorGroupBox(colorGroupBox), m_shapeGroupBox(shapeGroupBox), m_sizeGroupBox(sizeGroupBox),
		m_colorMaps(colorMaps)
{
	colorLegend->setWindowTitle("Color");
	colorLegend->setItemMode(QwtLegend::ClickableItem);
	QwtDynGridLayout* colorLegendLayout = qobject_cast<QwtDynGridLayout*>(colorLegend->contentsWidget()->layout());
	colorLegendLayout->setMaxCols(1);
	colorLegendLayout->setAlignment(Qt::AlignLeft);
	colorLegendLayout->setContentsMargins(5, 5, 5, 5);

	shapeLegend->setWindowTitle("Shape");
	shapeLegend->setItemMode(QwtLegend::ClickableItem);
	QwtDynGridLayout* shapeLegendLayout = qobject_cast<QwtDynGridLayout*>(shapeLegend->contentsWidget()->layout());
	shapeLegendLayout->setMaxCols(1);
	shapeLegendLayout->setAlignment(Qt::AlignLeft);
	shapeLegendLayout->setContentsMargins(5, 5, 5, 5);

	sizeLegend->setWindowTitle("Size");
	sizeLegend->setItemMode(QwtLegend::ClickableItem);
	QwtDynGridLayout* sizeLegendLayout = qobject_cast<QwtDynGridLayout*>(sizeLegend->contentsWidget()->layout());
	sizeLegendLayout->setMaxCols(1);
	sizeLegendLayout->setAlignment(Qt::AlignLeft);
	sizeLegendLayout->setContentsMargins(5, 5, 5, 5);
}

Legends::~Legends() 
{

}

void Legends::AddLegendItems(QwtLegend* legend, const QList<QwtSymbol*>& symbols, const QList<QString>& labels, const QList<QString>& toolTips)
{
	legend->clear();

	for(int i = 0; i < symbols.size(); ++i)
	{
		PlotMarkerLegend* marker = new PlotMarkerLegend();
		marker->setSymbol(symbols.at(i));
		marker->setTitle(labels.at(i));
		marker->setItemAttribute(QwtPlotItem::Legend, true);
		marker->setItemAttribute(QwtPlotItem::AutoScale, true);
		marker->setRenderHint(QwtPlotItem::RenderAntialiased, true);
		marker->updateLegend(legend);

		LegendItem* legendItem = qobject_cast<LegendItem *>(legend->find(marker));
		legendItem->setToolTip(toolTips.at(i));
		legendItem->setWindowTitle(legend->windowTitle());
		QObject::connect(legendItem, SIGNAL(GuaranteeVisibility()), this, SLOT(GuaranteeVisibility()));
		QObject::connect(legendItem, SIGNAL(SelectSamples()), this, SLOT(SelectSamples()));
		QObject::connect(legendItem, SIGNAL(ChangeProperties()), this, SLOT(ChangeLegendItem()));
		QObject::connect(legendItem, SIGNAL(CheckboxClicked()), this, SLOT(ChangeCheckbox()));
	}
}

void Legends::SetSamples(SamplesPtr samples) 
{ 
	m_samples = samples; 
}

void Legends::SetDefaultLegend()
{
	SetProperties("SampleID", QString("Ware (categorical - 9)"),
										"SampleID", true, "Circle",
										"SampleID", 10, 10, false);

}

void Legends::SetProperties(const QString& colorField, const QString& colorMapName,
														const QString& shapeField, bool bUseFixedShape, const QString& fixedShape,
														const QString& sizeField, uint minSize, uint maxSize, bool bUseLogScale)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	// setup new legend widgets
	if(colorField != m_colorField || colorMapName != m_colorMapName)
		SetColorLegend(colorField, colorMapName);

	if(shapeField != m_shapeField || bUseFixedShape != m_bFixedShape || fixedShape != m_fixedShape)
		SetShapeLegend(shapeField, bUseFixedShape, fixedShape);
	
	if(sizeField != m_sizeField || minSize != m_minSize || maxSize != m_maxSize || bUseLogScale != m_bLogScale)
		SetSizeLegend(sizeField, minSize, maxSize, bUseLogScale);

	// save legend property values
	bool bCategoryChanged = false;
	if(m_colorField != colorField || m_shapeField != shapeField || m_sizeField != sizeField)
		bCategoryChanged = true;

	m_colorField = colorField;
	m_colorMapName = colorMapName;

	m_shapeField = shapeField;
	m_bFixedShape = bUseFixedShape;
	m_fixedShape = fixedShape;

	m_sizeField = sizeField;
	m_minSize = minSize;
	m_maxSize = maxSize;
	m_bLogScale = bUseLogScale;

	emit VisualPropertiesChanged();

	if(bCategoryChanged)
		emit CategoryChanged();

	QApplication::restoreOverrideCursor();
}

void Legends::SetColorLegend(const QString& colorField, const QString& colorMapName)
{
	m_colorGroupBox->setTitle("Color: " + colorField);

	// setup new color legend
	if(colorMapName == "<custom>")
		m_colorMap = m_colorMaps->GetColorMap("Ware (categorical - 9)");
	else
		m_colorMap = m_colorMaps->GetColorMap(colorMapName);

	// sort values into ascending order, but keep a map so we can track the original sample metadata
	QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();
	QVector<QString> values = m_samples->GetMetadata()->GetValues(colorField);
	QMap<uint, QString> indexMap;
	QSet<QString> uniqueValues;
	QMap<QString, QList<uint>> valueToSampleIds;
	foreach(uint sampleId, activeSampleIds)
	{
		QString value = values.at(sampleId);
		indexMap[sampleId] = value;
		uniqueValues.insert(value);
		valueToSampleIds[value].push_back(sampleId);
	}
	QList<QString> fieldValues = uniqueValues.toList();

	Metadata::DATA_TYPE dataType = m_samples->GetMetadata()->GetDatatype(colorField);
	QwtInterval colorMapInterval;
	if(dataType == Metadata::CATEGORICAL_DATA)
	{
		qSort(fieldValues.begin(), fieldValues.end());

		colorMapInterval.setMinValue(0);

		if(m_colorMap->colorStops().size() > uniqueValues.size())
			colorMapInterval.setMaxValue(m_colorMap->colorStops().size()-1);
		else
			colorMapInterval.setMaxValue(uniqueValues.size()-1);
	}
	else
	{
		qSort(fieldValues.begin(), fieldValues.end(), numericStrLessThan);

		double minValue = fieldValues.at(0).toDouble();
		double maxValue = FindMaximumOfSortedValue(fieldValues);

		colorMapInterval.setMinValue(minValue);
		colorMapInterval.setMaxValue(maxValue);
	}

	// create legend items
	QMap<QString, QColor> valueMap;
	QList<QwtSymbol*> symbols;
	for(int i = 0; i < fieldValues.size(); ++i)
	{
		QColor color;
		if(!valueMap.contains(fieldValues.at(i)))
		{
			if(fieldValues.at(i) == "" || fieldValues.at(i) == "X")		
				color = Qt::black; // missing data
			else if(dataType == Metadata::CATEGORICAL_DATA)
				color = m_colorMap->color(colorMapInterval, valueMap.size());
			else
				color = m_colorMap->color(colorMapInterval, fieldValues.at(i).toDouble());

			symbols.push_back(new QwtSymbol(QwtSymbol::Rect, QBrush(color, Qt::SolidPattern), QPen(Qt::black, 1), QSize(14,14)));
			valueMap[fieldValues.at(i)] = color;
		}
	}

	// set sample colors
	foreach(uint sampleId, activeSampleIds)
		m_samples->GetSample(sampleId).SetColor(valueMap.value(indexMap.value(sampleId)));

	// construct legend tooltips and labels
	QList<QString> toolTips;
	QList<QString> labels;
	GenerateLegendToolTipsAndLabels(valueToSampleIds, toolTips, labels);

	// hide degenerate legends
	if(symbols.size() <= 1)
		m_colorGroupBox->hide();
	else
		m_colorGroupBox->show();

	AddLegendItems(m_colorLegend, symbols, labels, toolTips);
}

void Legends::SetShapeLegend(const QString& shapeField, bool bUsedFixedShape, const QString& fixedShape)
{
	m_shapeGroupBox->setTitle("Shape: " + shapeField); 
	
	// setup new legend
	QList<QString> fieldValues;
	QList<QwtSymbol*> symbols;
	QList<QString> toolTips;
	QList<QString> labels;
	if(!bUsedFixedShape)
	{
		// sort values into ascending order, but keep a map so we can track the original sample metadata
		QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();
		QVector<QString> values = m_samples->GetMetadata()->GetValues(shapeField);
		QMap<uint, QString> indexMap;
		QSet<QString> uniqueValues;
		QMap<QString, QList<uint>> valueToSampleIds;
		foreach(uint sampleId, activeSampleIds)
		{
			QString value = values.at(sampleId);
			indexMap[sampleId] = value;
			uniqueValues.insert(value);
			valueToSampleIds[value].push_back(sampleId);
		}
		fieldValues = uniqueValues.toList();

		if(m_samples->GetMetadata()->GetDatatype(shapeField) == Metadata::CATEGORICAL_DATA)
			qSort(fieldValues.begin(), fieldValues.end());
		else
			qSort(fieldValues.begin(), fieldValues.end(), numericStrLessThan);

		// create legend items
		QMap<QString, QwtSymbol::Style> valueMap;
		for(int i = 0; i < fieldValues.size(); ++i)
		{
			QwtSymbol::Style shape;
			if(!valueMap.contains(fieldValues.at(i)))
			{
				if(fieldValues.at(i) == "" || fieldValues.at(i) == "X")		
					shape = QwtSymbol::XCross; // missing data
				else
					shape = GetShape(valueMap.size());

				symbols.push_back(new QwtSymbol(shape, QBrush(Qt::black, Qt::SolidPattern), QPen(Qt::black, 1), QSize(14,14)));
				valueMap[fieldValues.at(i)] = shape;
			}
		}

		// set sample shapes
		foreach(uint sampleId, activeSampleIds)
			m_samples->GetSample(sampleId).SetShape(valueMap.value(indexMap.value(sampleId)));

		// construct legend tooltips and labels
		GenerateLegendToolTipsAndLabels(valueToSampleIds, toolTips, labels);
	}
	else
	{
		// set fixed shape
		for(uint i = 0; i < m_samples->GetNumSamples(); ++i)
			m_samples->GetSample(i).SetShape(GetShape(fixedShape));
	}

	// hide degenerate legends
	if(symbols.size() <= 1)
		m_shapeGroupBox->hide();
	else
		m_shapeGroupBox->show();

	AddLegendItems(m_shapeLegend, symbols, labels, toolTips);
}

void Legends::SetSizeLegend(const QString& sizeField, uint minSize, uint maxSize, bool bUseLogScale)
{
	m_sizeGroupBox->setTitle("Size: " + sizeField);

	// setup new legend
	QList<QString> fieldValues;
	QList<QwtSymbol*> symbols;
	QList<QString> toolTips;
	QList<QString> labels;
	if(minSize < maxSize)
	{
		// sort values into ascending order, but keep a map so we can track the original sample metadata
		QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();
		QVector<QString> values = m_samples->GetMetadata()->GetValues(sizeField);
		QMap<uint, QString> indexMap;
		QSet<QString> uniqueValues;
		QMap<QString, QList<uint>> valueToSampleIds;
		foreach(uint sampleId, activeSampleIds)
		{
			QString value = values.at(sampleId);
			indexMap[sampleId] = value;
			uniqueValues.insert(value);
			valueToSampleIds[value].push_back(sampleId);
		}
		fieldValues = uniqueValues.toList();

		Metadata::DATA_TYPE dataType = m_samples->GetMetadata()->GetDatatype(sizeField);
		double minValue, maxValue;
		if(dataType == Metadata::CATEGORICAL_DATA)
		{
			qSort(fieldValues.begin(), fieldValues.end());

			minValue = 0;
			maxValue = fieldValues.size()-1;
		}
		else
		{
			qSort(fieldValues.begin(), fieldValues.end(), numericStrLessThan);
			if(bUseLogScale)
			{
				minValue = log10(fieldValues.at(0).toDouble());
				maxValue = log10(FindMaximumOfSortedValue(fieldValues));
			}
			else
			{
				minValue = fieldValues.at(0).toDouble();
				maxValue = FindMaximumOfSortedValue(fieldValues);
			}
		}

		double range = maxValue - minValue;

		// create legend items
		QMap<QString, double> valueMap;
		for(int i = 0; i < fieldValues.size(); ++i)
		{
			double size;
			if(!valueMap.contains(fieldValues.at(i)))
			{
				if(range != 0)
				{
					double relSize;
					if(fieldValues.at(i) == "" || fieldValues.at(i) == "X")	
					{
						size = minSize / 2; // missing data
					}
					if(dataType == Metadata::CATEGORICAL_DATA)
					{
						double value = i;
						relSize = (value - minValue) / range;
					}
					else
					{
						double value;
						if(bUseLogScale)
							value = log10(fieldValues.at(i).toDouble());
						else
							value = fieldValues.at(i).toDouble();

						relSize = (value - minValue) / range;
					}
					size = (maxSize - minSize)*relSize + minSize + 0.5;
				}
				else
				{
					size = minSize;
				}

				symbols.push_back(new QwtSymbol(QwtSymbol::Ellipse, QBrush(Qt::black, Qt::SolidPattern), QPen(Qt::black, 1), QSize(size,size)));
				valueMap[fieldValues.at(i)] = size;
			}
		}

		// set sample size
		foreach(uint sampleId, activeSampleIds)
			m_samples->GetSample(sampleId).SetSize(valueMap.value(indexMap.value(sampleId)));

		// set tooltips and labels for legend items
		GenerateLegendToolTipsAndLabels(valueToSampleIds, toolTips, labels);
	}
	else
	{
		for(uint i = 0; i < m_samples->GetNumSamples(); ++i)
			m_samples->GetSample(i).SetSize(minSize);
	}

	// hide degenerate legends
	if(symbols.size() <= 1)
		m_sizeGroupBox->hide();
	else
		m_sizeGroupBox->show();
	
	AddLegendItems(m_sizeLegend, symbols, labels, toolTips);
}

void Legends::GenerateLegendToolTipsAndLabels(const QMap<QString, QList<uint>>& valueToSampleIds, QList<QString>& toolTips, QList<QString>& labels)
{
	foreach(QString value, valueToSampleIds.keys())
	{
		QStringList sampleNames;
		QList<uint> sampleIds = valueToSampleIds[value];
		foreach(uint sampleId, sampleIds)
			sampleNames.push_back(m_samples->GetMetadata()->GetValue("SampleID", sampleId));

		QString toolTip;
		qSort(sampleNames.begin(), sampleNames.end());
		foreach(const QString& sampleName, sampleNames)
			toolTip += sampleName + ", ";
		toolTip = toolTip.left(toolTip.size()-2);	// remove trailing comma and space

		toolTips.append(toolTip);

		labels.push_back(value + QString(" (%1)").arg(sampleNames.size()));
	}
}

void Legends::SetCheckboxStates()
{
	SetCheckboxStates(m_colorLegend);
	SetCheckboxStates(m_shapeLegend);
	SetCheckboxStates(m_sizeLegend);
}

void Legends::SetCheckboxStates(const QwtLegend* legend)
{
	QList<QWidget *> legendItems = legend->legendItems();

	for(int i = 0; i < legendItems.size(); ++i)
	{
		bool bVisible = false;
		bool bHidden = false;

		QString toolTip = legendItems.at(i)->toolTip();
		QStringList sampleIdStrs = toolTip.split(',');
		foreach(const QString& sampleIdStr, sampleIdStrs)
		{
			Sample sample;
			if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
			{
				if(sample.IsVisible())
					bVisible = true;
				else
					bHidden = true;
			}
			else
				Log::Inst().Error("Invalid sample specified in SetCheckboxStates(): " + sampleIdStr.trimmed());
		}

		LegendItem* legendItem = dynamic_cast<LegendItem*>(legendItems.at(i));
		if(bVisible && bHidden)
			legendItem->SetPartiallyChecked();
		else if(bVisible)
			legendItem->SetChecked();
		else
			legendItem->SetUnchecked();
	}
}

void Legends::ChangeLegendItem()
{
	if(sender()->isWidgetType())
	{
		LegendItem* legendItem = (LegendItem*)sender();

		QString type = legendItem->windowTitle();

		if(type == "Color")
			ChangeLegendColor(legendItem);
		else if(type == "Shape")
			ChangeLegendShape(legendItem);
		else if(type == "Size")
			ChangeLengendSize(legendItem);
		else
			Log::Inst().Error("Unknown legend item type.");

		emit VisualPropertiesChanged();
	}
}

void Legends::ChangeLegendColor(LegendItem* item)
{
	PlotMarkerLegend* plotMarker = dynamic_cast<PlotMarkerLegend*>(m_colorLegend->find(item));
	QColor color = QColorDialog::getColor(plotMarker->symbol()->brush().color(), 0, "Select color", QColorDialog::ShowAlphaChannel);

	if(color.isValid())
	{	
		// set new color
		QwtSymbol* newSymbol = new QwtSymbol(*plotMarker->symbol());
		QBrush newBrush = newSymbol->brush();
		newBrush.setColor(color);
		newSymbol->setBrush(newBrush);

		plotMarker->setSymbol(newSymbol);
		plotMarker->updateLegend(m_colorLegend);

		// update color assigned to samples of this legend item
		QString toolTip = item->toolTip();
		QStringList sampleIdStrs = toolTip.split(',');
		foreach(const QString& sampleIdStr, sampleIdStrs)
		{
			Sample sample;
			if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
				sample.SetColor(color);
			else
				Log::Inst().Error("Invalid sample specified in colour legend: " + sampleIdStr.trimmed());
		}

		m_colorMapName = "<custom>";
	}
}

void Legends::ChangeLegendShape(LegendItem* item)
{
	PlotMarkerLegend* plotMarker = dynamic_cast<PlotMarkerLegend*>(m_shapeLegend->find(item));

	QStringList shapes;
	shapes <<	"Circle"
         << "Square"
         << "Triangle (up)"
         << "Star (style 1)"
         << "Star (style 2)"
				 << "Diamond"
         << "Hexagon"
			   << "Cross"
				 << "Triangle (down)"
         << "Triangle (left)"
         << "Triangle (right)"
	       << "Horizontal line"
         << "Vertical line"
				 << "Diagonal cross";

	bool ok;
	QString shapeName = QInputDialog::getItem(0, "Select shape", "New shape:", shapes, 0, false, &ok);
	if(ok)
	{
		QwtSymbol::Style shape = GetShape(shapeName);

		// set new shape
		QwtSymbol* newSymbol = new QwtSymbol(*plotMarker->symbol());
		newSymbol->setStyle(shape);
		plotMarker->setSymbol(newSymbol);
		plotMarker->updateLegend(m_shapeLegend);

		// update shape assigned to samples of this legend item
		QString toolTip = item->toolTip();
		QStringList sampleIdStrs = toolTip.split(',');
		foreach(const QString& sampleIdStr, sampleIdStrs)
		{
			Sample sample;
			if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
				sample.SetShape(shape);
			else
				Log::Inst().Error("Invalid sample specified in shape legend: " + sampleIdStr.trimmed());
		}

		m_bFixedShape = false;
		m_fixedShape = "<custom>";
	}
}

void Legends::ChangeLengendSize(LegendItem* item)
{
	PlotMarkerLegend* plotMarker = dynamic_cast<PlotMarkerLegend*>(m_sizeLegend->find(item));

	uint curSize = plotMarker->symbol()->size().width();
	uint size = QInputDialog::getInt(0, "Select size", "New size:", curSize, 1, 100, 1);
	if(size != curSize)
	{
		// set new shape
		QwtSymbol* newSymbol = new QwtSymbol(*plotMarker->symbol());
		newSymbol->setSize(size, size);
		plotMarker->setSymbol(newSymbol);
		plotMarker->updateLegend(m_sizeLegend);

		// update shape assigned to samples of this legend item
		QString toolTip = item->toolTip();
		QStringList sampleIdStrs = toolTip.split(',');
		foreach(const QString& sampleIdStr, sampleIdStrs)
		{
			Sample sample;
			if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
				sample.SetSize(size);
			else
				Log::Inst().Error("Invalid sample specified in size legend: " + sampleIdStr.trimmed());
		}

		m_minSize = 0;
		m_maxSize = 0;
	}
}

void Legends::ChangeCheckbox()
{
	if(sender()->isWidgetType())
	{
		LegendItem* legendItem = (LegendItem*)sender();
		Qt::CheckState state = legendItem->GetCheckbox()->checkState();

		// update visibility of samples associated with checkbox
		QString toolTip = legendItem->toolTip();
		QStringList sampleIdStrs = toolTip.split(',');
		foreach(const QString& sampleIdStr, sampleIdStrs)
		{
			Sample sample;
			uint sampleId;
			if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
				sampleId = sample.GetId();
			else
				Log::Inst().Error("Invalid sample specified when changing legend checkbox: " + sampleIdStr.trimmed());

			if(state != Qt::Unchecked)
				m_samples->GetSample(sampleId).SetVisible(true);
			else
				m_samples->GetSample(sampleId).SetVisible(false);
		}

		// update state of check boxes
		SetCheckboxStates();

		// signal change
		emit VisibileCategoriesChanged();
		emit VisualPropertiesChanged();
	}
}

double Legends::FindMaximumOfSortedValue(const QList<QString>& values)
{
	// this function assumes the values are already sorted with
	// unknown values placed at the end
	for(int i = values.size()-1; i >= 0; --i)
	{
		if(values.at(i) != "X" && values.at(i) != "")
			return values.at(i).toDouble();
	}

	// all values are unknown
	return 0;
}

void Legends::GuaranteeVisibility() 
{ 
	for(uint i = 0; i < m_samples->GetNumSamples(); ++i)
		m_samples->GetSample(i).SetGuaranteedVisible(false);

	LegendItem* legendItem = (LegendItem*)sender();
	QStringList sampleIdStrs = legendItem->toolTip().split(',');
	foreach(const QString& sampleIdStr, sampleIdStrs)
	{
		Sample sample;
		if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
			sample.SetGuaranteedVisible(true);
		else
			Log::Inst().Error("Invalid sample specified in GuaranteeVisibility: " + sampleIdStr.trimmed());
	}

	emit VisualPropertiesChanged(); 
}

void Legends::SelectSamples()
{
	LegendItem* legendItem = (LegendItem*)sender();
	QStringList sampleIdStrs = legendItem->toolTip().split(',');
	QSet<uint> sampleIds;
	foreach(const QString& sampleIdStr, sampleIdStrs)
	{
		Sample sample;
		if(m_samples->GetSample(sampleIdStr.trimmed(), sample))
			sampleIds.insert(sample.GetId());
		else
			Log::Inst().Error("Invalid sample specified in SelectSamples: " + sampleIdStr.trimmed());
	}

	m_samples->SetSamplesToSelected(sampleIds);

	emit SelectionSetChanged();
}

void Legends::ChangeActiveSamples()
{
	SetColorLegend(m_colorField, m_colorMapName);
	SetShapeLegend(m_shapeField, m_bFixedShape, m_fixedShape);
	SetSizeLegend(m_sizeField, m_minSize, m_maxSize, m_bLogScale);

	SetCheckboxStates();
}

QwtSymbol::Style Legends::GetShape(int index)
{
	switch(index)
	{
		case 0:
			return QwtSymbol::Ellipse;
		case 1:
			return QwtSymbol::Rect;
		case 2:
			return QwtSymbol::Triangle;
		case 8:
			return QwtSymbol::Star1;
		case 9:
			return QwtSymbol::Star2;
		case 12:
			return QwtSymbol::Diamond;
		case 13:
			return QwtSymbol::Hexagon;
		case 6:
			return QwtSymbol::Cross;
		case 3:
			return QwtSymbol::DTriangle;
		case 4:
			return QwtSymbol::LTriangle;
		case 5:
			return QwtSymbol::RTriangle;
		case 10:
			return QwtSymbol::HLine;
		case 11:
			return QwtSymbol::VLine;
		case 7:
			return QwtSymbol::XCross;
		default:
			return QwtSymbol::Ellipse;
	}
}

QwtSymbol::Style Legends::GetShape(const QString& shapeName)
{
	if(shapeName == "Circle")
		return QwtSymbol::Ellipse;
	else if(shapeName == "Square")
		return QwtSymbol::Rect;
	else if(shapeName == "Triangle (up)")
		return QwtSymbol::Triangle;
	else if(shapeName == "Star (style 1)")
		return QwtSymbol::Star1;
	else if(shapeName == "Star (style 2)")
		return QwtSymbol::Star2;
	else if(shapeName == "Diamond")
		return QwtSymbol::Diamond;
	else if(shapeName == "Hexagon")
		return QwtSymbol::Hexagon;
	else if(shapeName == "Cross")
		return QwtSymbol::Cross;
	else if(shapeName == "Triangle (down)")
		return QwtSymbol::DTriangle;
	else if(shapeName == "Triangle (left)")
		return QwtSymbol::LTriangle;
	else if(shapeName == "Triangle (right)")
		return QwtSymbol::RTriangle;
	else if(shapeName == "Horizontal line")
		return QwtSymbol::HLine;
	else if(shapeName == "Vertical line")
		return QwtSymbol::VLine;
	else if(shapeName == "Diagonal cross")
		return QwtSymbol::XCross;

	return QwtSymbol::NoSymbol;
}