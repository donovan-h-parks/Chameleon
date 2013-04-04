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

#ifndef _PROPERTIES_HPP_
#define _PROPERTIES_HPP_

#include "stdafx.h"

/**
 * @brief Singleton class for holding current application properties.
 */
class Properties
{
public:
	/** Destructor */
	~Properties() {}

	/** Get the one and only instance of the state class. */
	static Properties& Inst()
	{
		static Properties state;	
		return state;
	}

	/** Restore default values. */
	void RestoreDefaultValues()
	{
		SetSelectionTransparency(85);
		SetBackgroundColor(Qt::white);
	}
	
	/** Size of viewport border. */
	int GetViewportBorderSize() { return 25; }

	/** Set highlight brush color. */
	void SetHighlightBrush(const QBrush& brush) { m_highlightBrush = brush; }

	/** Get highlight brush color. */
	const QBrush& GetHighlightBrush() { return m_highlightBrush; }

	/** Set text highlight brush color. */
	void SetTextHighlightBrush(const QBrush& brush) { m_textHighlightBrush = brush; }

	/** Get text highlight brush color. */
	const QBrush& GetTextHighlightBrush() { return m_textHighlightBrush; }

	/** Set highlight pen color. */
	void SetHighlightPen(const QPen& pen) { m_highlightPen = pen; }

	/** Get highlight pen color. */
	const QPen& GetHighlightPen() { return m_highlightPen; }

	/** Set text highlight pen color. */
	void SetTextHighlightPen(const QPen& pen) { m_textHighlightPen = pen; }

	/** Get text highlight pen color. */
	const QPen& GetTextHighlightPen() { return m_textHighlightPen; }
	
	/** Set selection opacity value. */
	void SetSelectionTransparency(int value)
	{
		m_selectionOpacity = (100.0-value)/100 * 255;
		m_settings.setValue("selectionOpacity", m_selectionOpacity);
	}

	/** Get selection opacity value. */
	int GetSelectionOpacity() const { return m_selectionOpacity; }

	/** Set background colour. */
	void SetBackgroundColor(const QColor& color)
	{
		m_backgroundColor = color;
		m_settings.setValue("backgroundColor", m_backgroundColor);
	}

	/** Get background colour. */
	QColor GetBackgroundColor() const { return m_backgroundColor; }

protected:
	/** Private singleton constructor (must instantiate  this class through Inst()). */
	Properties() 
	{
		m_textHighlightPen = QPen(QColor(130, 170, 220));
		m_textHighlightBrush = QBrush(QColor(230, 240, 255));

		m_highlightPen = QPen(QColor(255, 0, 0));
		m_highlightBrush = QBrush(QColor(255,0,0,32));

		m_selectionOpacity = m_settings.value("selectionOpacity", 38).toInt();
		m_backgroundColor = m_settings.value("backgroundColor", Qt::white).value<QColor>();
	}

	/** Private copy constructor (must instantiate  this class through Inst()). */
	Properties(const Properties&) {}

	/** Private assignment constructor (must instantiate  this class through Inst()). */
	Properties& operator= (const Properties&) {}

private:
	/** Save/restore properties. */
	QSettings m_settings;

	QBrush m_highlightBrush;
	QPen m_highlightPen;

	QBrush m_textHighlightBrush;
	QPen m_textHighlightPen;

	int m_selectionOpacity; 

	QColor m_backgroundColor;
};

#endif