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

#ifndef _LEGENDS_HPP_
#define _LEGENDS_HPP_

#include "stdafx.h"

class LegendItem;

/**
 * @class Legends
 * @brief Create interactive legends for plots.
 */
class Legends: public QObject
{
	Q_OBJECT

public:
	/** Constructor. */
	Legends(QwtLegend* colorLegend, QwtLegend* shapeLegend, QwtLegend* sizeLegend, 
					QGroupBox* colorGroupBox, QGroupBox* shapeGroupBox, QGroupBox* sizeGroupBox,
					ColorMapsPtr colorMaps);

	/** Destructor. */
	virtual ~Legends();

	/** Set samples to base legend on. */
	void SetSamples(SamplesPtr samples);

	/** Setup a new default legend. */
	void SetDefaultLegend();

	/** Set legend properties based on sample metadata. */
	void SetProperties(const QString& colorField, const QString& colorMapName,
											const QString& shapeField, bool bUseFixedShape, const QString& fixedShape,
											const QString& sizeField, uint minSize, uint maxSize, bool bLogScale);

	QString GetColorField() const { return m_colorField; }
	QString GetColorMapName() const { return m_colorMapName; }

	QString GetShapeField() const { return m_shapeField; }
	bool IsFixedShape() const { return m_bFixedShape; }
	QString GetFixedShape() const { return m_fixedShape; }

	QString GetSizeField() const { return m_sizeField; }
	uint GetMinSize() const { return m_minSize; }
	uint GetMaxSize() const { return m_maxSize; }
	bool IsLogScale() const { return m_bLogScale; }

	uint GetNumColorLegendItems() { return m_colorLegend->itemCount(); }
	uint GetNumShapeLegendItems() { return m_shapeLegend->itemCount(); }
	uint GetNumSizeLegendItems() { return m_sizeLegend->itemCount(); }

	static QwtSymbol::Style GetShape(int index);
	static QwtSymbol::Style GetShape(const QString& shapeName);

signals:
	void VisualPropertiesChanged();
	void SelectionSetChanged();
	void VisibileCategoriesChanged();
	void CategoryChanged();
	
private slots:
	void ChangeLegendItem();
	void ChangeCheckbox();
	void ChangeActiveSamples();

	void GuaranteeVisibility();
	void SelectSamples();

private:
	void AddLegendItems(QwtLegend* legend, const QList<QwtSymbol*>& symbols, const QList<QString>& labels, const QList<QString>& toolTips);
	void SetColorLegend(const QString& colorField, const QString& colorMapName);
	void SetShapeLegend(const QString& shapeField, bool bUsedFixedShape, const QString& fixedShape);
	void SetSizeLegend(const QString& sizeField, uint minSize, uint maxSize, bool bUseLogScale);

	void ChangeLegendColor(LegendItem* item);
	void ChangeLegendShape(LegendItem* item);
	void ChangeLengendSize(LegendItem* item);

	void SetCheckboxStates();
	void SetCheckboxStates(const QwtLegend* legend);

	void GenerateLegendToolTipsAndLabels(const QMap<QString, QList<uint>>& valueToSampleIds, QList<QString>& toolTips, QList<QString>& labels);
	double FindMaximumOfSortedValue(const QList<QString>& values);

private:
	QwtLegend* m_colorLegend;
	QwtLegend* m_shapeLegend; 
	QwtLegend* m_sizeLegend;

	QGroupBox* m_colorGroupBox;
	QGroupBox* m_shapeGroupBox;
	QGroupBox* m_sizeGroupBox;

	QString m_colorField;
	QString m_colorMapName;

	ColorMapsPtr m_colorMaps;
	QwtLinearColorMapPtr m_colorMap;

	QString m_shapeField;
	bool m_bFixedShape;
	QString m_fixedShape;

	QString m_sizeField;
	uint m_minSize;
	uint m_maxSize;
	bool m_bLogScale;

	SamplesPtr m_samples;
};

#endif

