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

#include "stdafx.h"

#include "ColorMaps.hpp"

#include "Log.hpp"

ColorMaps::ColorMaps()
{

}

bool ColorMaps::Load()
{
	QDir dir(QCoreApplication::applicationDirPath() + "/colourMaps");
	QStringList colorMapFiles = dir.entryList(QStringList("*.cm"), QDir::Files, QDir::Name);
	if(colorMapFiles.size() == 0)
	{
		Log::Inst().Error("Problem locating color maps. Try executing program from the directory containing the executable.");
		return false;
	}

	foreach(const QString& colorMapFile, colorMapFiles)
	{
		// open color map file.
		QFile file(QCoreApplication::applicationDirPath() + "/colourMaps/" + colorMapFile);
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			Log::Inst().Warning("Problem loading color map: " + QCoreApplication::applicationDirPath() + "/" + colorMapFile);
			return false;
		}

		// parse colour map file
		QTextStream textStream(&file);
		QString type = textStream.readLine();
		QString name = textStream.readLine();
		name = name.mid(name.indexOf(':')+1).trimmed();
		QString numColorsStr = textStream.readLine();
		uint numColors = numColorsStr.mid(numColorsStr.indexOf(':')+1).toInt();
		QList<QColor> colors;
		for(uint i = 0; i < numColors; ++i)
		{
			QString data = textStream.readLine();
			QStringList colorList = data.split(QRegExp("\\s+"), QString::SkipEmptyParts);
			QColor color(colorList.at(0).toInt(), colorList.at(1).toInt(), colorList.at(2).toInt());
			colors.push_back(color);
		}

		// create color map
		QwtLinearColorMapPtr colorMap(new QwtLinearColorMap(colors.at(0), colors.at(colors.size()-1)));
		QString colorMapName = "<unknown>";
		if(type == "Type: CONTINUOUS")
		{
			for(int i = 1; i < colors.size()-1; ++i)
				colorMap->addColorStop(double(i) / (colors.size()-1), colors.at(i));

			colorMap->setMode(QwtLinearColorMap::ScaledColors);
			colorMapName = name + " (continuous)";
		}
		else if(type == "Type: DISCRETE")
		{			
			for(int i = 1; i < colors.size(); ++i)
				colorMap->addColorStop(double(i) / colors.size(), colors.at(i));

			colorMap->setMode(QwtLinearColorMap::FixedColors);
			colorMapName = name + " (discrete - " + QString::number(numColors) + ")";
		}
		else if(type == "Type: CATEGORICAL")
		{
			for(int i = 1; i < colors.size(); ++i)
				colorMap->addColorStop(double(i) / colors.size(), colors.at(i));

			colorMap->setMode(QwtLinearColorMap::FixedColors);
			colorMapName = name + " (categorical - " + QString::number(numColors) + ")";
		}

		m_colorMaps.insert(colorMapName, colorMap);

		file.close();
	}

	return true;
}

void ColorMaps::PopulateComboBox(QComboBox* comboBox)
{
	foreach(const QString& name, m_colorMaps.keys())
		comboBox->addItem(name);

	comboBox->setCurrentIndex(comboBox->findText("Ware (categorical - 9)"));
}

QLinearGradient ColorMaps::GetLinearGradient(const QString& name)
{
	QwtLinearColorMapPtr colorMap = m_colorMaps.value(name);

	// create linear gradient
	QLinearGradient linearGradient;
	QVector<double> colorStops = colorMap->colorStops();
	QwtInterval colorMapInterval(colorStops.at(0), colorStops.at(colorStops.size()-1));
	if(name.contains("continuous"))
	{
		for(int i = 0; i < colorStops.size(); ++i)
		{
			QColor color = colorMap->color(colorMapInterval, colorStops.at(i));
			linearGradient.setColorAt(colorStops.at(i), color);
		}
	}
	else // we have a discrete or categorical colour map
	{
		for(int i = 0; i < colorStops.size()-1; ++i)
		{
			QColor color = colorMap->color(colorMapInterval, colorStops.at(i));
			if(i == 0)
			{
				linearGradient.setColorAt(0, color);
				linearGradient.setColorAt(colorStops.at(i+1) - 1e-6, color);
			}
			else if(i == colorStops.size()-2)
			{
				linearGradient.setColorAt(colorStops.at(i), color);
				linearGradient.setColorAt(colorStops.at(i+1), color);
			}
			else
			{
				linearGradient.setColorAt(colorStops.at(i), color);
				linearGradient.setColorAt(colorStops.at(i+1) - 1e-6, color);
			}
		}
	}

	return linearGradient;
}