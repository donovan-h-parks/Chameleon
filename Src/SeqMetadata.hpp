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

#ifndef _SEQ_METADATA_HPP_
#define _SEQ_METADATA_HPP_

#include "stdafx.h"

#include "ColorMaps.hpp"

class SeqMetadata: public QObject
{
	Q_OBJECT

public:
	enum DATA_TYPE { NUMERICAL_DATA, CATEGORICAL_DATA };

public:
	SeqMetadata(ColorMapsPtr colorMaps);
	~SeqMetadata() {}

	bool Load(const QString& filename);

	QStringList GetFields() const { return m_metadata.keys(); }

	QString GetMetadataValue(const QString& seqName);
	QColor GetMetadataColor(const QString& seqName);

	void SetField(const QString& field);
	void SetColorMap(const QString& colorMapName);
	void SetColorMap(const QMap<QString, QColor>& colorMap);

	void SetOtherPercentage(double percentage);
	void SetOtherColor(const QColor& color) { m_otherColor = color; }
	void SetMissingDataColor(const QColor& color) { m_missingDataColor = color; }

	DATA_TYPE GetDatatype(const QString& field) { return m_dataType.value(field); }

signals:
	void ColorMapChanged(const QMap<QString, QColor>& colorMap, const QMap<QString, float>& percentages, bool bNumeric);

protected:
	double FindMaximumOfSortedValue(const QList<QString>& values);

private:
	/** Specifies metadata for a given field for each sequence. */
	QMap<QString, QMap<QString, QString> > m_metadata;
	QMap<QString, DATA_TYPE> m_dataType;
	QMap<QString, QColor> m_colorMap;

	QMap<QString, float> m_percentages;

	QColor m_missingDataColor;

	QColor m_otherColor;
	float m_otherPercentage;

	QString m_field;
	QString m_colorMapName;

	ColorMapsPtr m_colorMaps;
};

#endif