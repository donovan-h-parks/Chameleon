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

#ifndef _PLOT_PICKER_HPP_
#define _PLOT_PICKER_HPP_

#include "stdafx.h"

class QPoint;
class QCustomEvent;
class QwtPlot;
class QwtPlotCanvas;

class PlotPicker: public QObject
{
    Q_OBJECT
public:
    PlotPicker(QwtPlot *plot);
    virtual bool eventFilter(QObject *, QEvent *);

    virtual bool event(QEvent *);

private:
    void select(const QPoint &);
    void release();

    QwtPlot *plot() { return (QwtPlot *)parent(); }
    const QwtPlot *plot() const { return (QwtPlot *)parent(); }

		QwtPlotCanvas* m_canvas;
};

#endif
