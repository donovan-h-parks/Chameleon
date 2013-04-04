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

#ifndef _SAMPLE_HPP_
#define _SAMPLE_HPP_

#include "stdafx.h"

/**
 * @class Sample data.
 * @brief Holds data for a sample so it can be explicitly shared.
 */
class SampleData: public QSharedData
{
public:
	SampleData();
	SampleData(const QString& name, uint id);

	~SampleData() {}

	QString m_name;
	uint m_id;

	uint m_numSequences;

	bool m_bVisible;
	bool m_bGuaranteedVisible;

	QColor m_color;
	QwtSymbol::Style m_shape;
	double m_size;
};


/**
 * @class Sample (explicitly shared).
 * @brief Holds data and functions for a single sample.
 */
class Sample
{
public:
	/** Constructor. */
	Sample();

	/** Constructor. */
	Sample(const QString& name, uint id);

	/** Destructor. */
	~Sample() {}

	const QString& GetName() const { return d->m_name; }
	void SetName(const QString& name) { d->m_name = name; }

	uint GetId() const { return d->m_id; }
	void SetId(uint id) { d->m_id = id; }

	uint GetNumSequences() const { return d->m_numSequences; }
	void SetNumSequences(uint numSequences) { d->m_numSequences = numSequences; }

	bool IsVisible() const { return d->m_bVisible; }
	void SetVisible(bool state) { d->m_bVisible = state; }

	bool IsGuaranteedVisible() const { return d->m_bGuaranteedVisible; }
	void SetGuaranteedVisible(bool state) { d->m_bGuaranteedVisible = state; }

	const QColor& GetColor() const { return d->m_color; }
	void SetColor(const QColor& color) { d->m_color = color; }

	QwtSymbol::Style GetShape() const { return d->m_shape; }
	void SetShape(QwtSymbol::Style shape) { d->m_shape = shape; }

	double GetSize() const { return d->m_size; }
	void SetSize(double size) { d->m_size = size; }

	void DeepCopy() { d.detach(); }

private:
	QExplicitlySharedDataPointer<SampleData> d;
};

#endif

