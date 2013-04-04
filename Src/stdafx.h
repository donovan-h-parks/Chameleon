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

#ifndef _STD_AFX_
#define _STD_AFX_

// Generally only 3rd party header files should be included in this file. That is, header files that will
// almost never be changed. If a project header is added to this file, the entire project will need to be
// recompiled whenever this file changes. There are cases where this is reasonable (i.e., header files specifying
// common typedef's or constants that must be included in almost every file anyways).

// C/C++ includes
#include <fstream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <float.h>	// defines DBL_MAX

// Qt includes
#include <QtCore>
#include <QtGui>
#include <QtSvg\QSvgGenerator.h>

// Qwt includes
#include <qwt_color_map.h>
#include <qwt_dyngrid_layout.h>
#include <qwt_interval.h>
#include <qwt_legend_item.h>
#include <qwt_picker_machine.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_item.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_rescaler.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_map.h>
#include <qwt_scale_widget.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>

// Window specific includes
#if defined(_WIN32)
	#define NOMINMAX
	#include <windows.h>
#endif

// Project files (add with caution!)
#include "DataTypes.hpp"
#include "Common.hpp"

#endif



