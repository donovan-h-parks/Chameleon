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

#ifndef _METADATA_HPP_
#define _METADATA_HPP_

#include "stdafx.h"

class Metadata: public QObject
{
	Q_OBJECT

public:
	enum DATA_TYPE { NUMERICAL_DATA, CATEGORICAL_DATA };

public:
	Metadata(Samples* samples);
	~Metadata() {}

	bool Load(const QString& filename);

	QStringList GetFields() const { return m_metadata.keys(); }
	QStringList GetQuantitativeFields() const;

	const QVector<QString>& GetValues(const QString& field) { return m_metadata[field]; }
	const QString& GetValue(const QString& field, uint sampleId) { return m_metadata.value(field).at(sampleId); }

	DATA_TYPE GetDatatype(const QString& field) const { return m_dataType.value(field); }

	void PopulateTable(QTableWidget* table);

	void SetSelectedRows();

	void MarkActiveSamplesInTable();

private:
	void SetDefaultMetadata();
	
private slots:
	void CellClicked(const QModelIndex& index);
	
private:
	Samples* m_samples;

	/** Specifies metadata for a given field for each sample. */
	QMap<QString, QVector<QString> > m_metadata;
	QMap<QString, DATA_TYPE> m_dataType;

	QTableWidget* m_table;


};

#endif