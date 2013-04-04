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

#ifndef VISUAL_SCALE
#define VISUAL_SCALE

class VisualScale: public QGraphicsItem
{
public:
	VisualScale();

	double GetScale() const { return m_scale; }
	double GetPixelsPerUnitBranchLength() const { return m_pixelsToBranchLength; }
	int GetSignificantDigits() const { return m_numSignDigits; }	
	int GetLineWidth() const { return m_lineWidth; }
	const QFont& GetFont() const { return m_font; }
	bool IsAutomaticScale() { return m_bAutomatic; }

	double SetAutomaticLength();

	void SetScale(double scale);
	void SetPixelsPerUnitBranchLength(float pixelsToBranchLength);
	void SetSignificantDigits(int digits);
	void SetLineWidth(int width);
	void SetFont(const QFont& font, const QColor& color);
	void SetAutomaticScale(bool bAutomatic);
	void SetVisibility(bool bVisible);

	QRectF boundingRect() const;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	float m_scale;
	float m_pixelsToBranchLength;
	int m_numSignDigits;
	QFont m_font;
	QColor m_fontColor;
	int m_lineWidth;
	bool m_bAutomatic;

	float m_labelWidth;
	float m_labelHeight;
};

#endif