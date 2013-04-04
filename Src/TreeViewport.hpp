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

#ifndef TREE_VIEWPORT_HPP
#define TREE_VIEWPORT_HPP

#include "stdafx.h"

class TreeViewport: public QGraphicsView
{
	Q_OBJECT

public:
	TreeViewport(QWidget* parent = 0);
	~TreeViewport() {}

signals:
	void ViewportResized(int width, int height);

public slots:
	void SetBackgroundColor(const QColor& color);

private slots:
	//void resetView();
	//void toggleAntialiasing();
	//void print(); 

	void ViewRoot();

	void ZoomIn();
	void ZoomOut();
	void ZoomDefault();

	void SetProjectionMatrix();

protected:
	void keyPressEvent(QKeyEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event);

private:
	float m_zoom;
};

#endif
