//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// Based on code by: Julien Dutheil and Celine Scornavacca (Bio++ project)
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

#ifndef VISUAL_AXIS
#define VISUAL_AXIS

class VisualAxis: public QGraphicsItem
{
public:
	VisualAxis();

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	const QFont& GetFont() const { return m_font; }
	
	void SetData(MetadataPtr metadata, const QString& field);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetFont(const QFont& font, const QColor& color);
	void SetVisibility(bool bVisible);
	void SetLabelVisibility(bool bVisible);

	QRectF boundingRect() const;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	QFont m_font;
	QColor m_fontColor;
	bool m_bLabelVisibility;
	int m_width;
	int m_height;

	QString m_field;
	QVector<double> m_values;

	int m_labelHeight;
	int m_maxLabelWidth;
};

#endif