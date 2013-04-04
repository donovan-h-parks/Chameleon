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

#ifndef SEQ_LEGEND_DLG_HPP
#define SEQ_LEGEND_DLG_HPP

#include "ui_SeqLegendDialog.h"

#include "stdafx.h"

class SeqLegendDlg : public QDockWidget
{
	Q_OBJECT

public:
	SeqLegendDlg(SeqMetadataPtr seqMetadata, QWidget *parent = 0, Qt::WFlags flags = 0);
	~SeqLegendDlg();

	double GetOtherPercentage() const { return m_otherPercentage; }

signals:
	void Changed();
	void OtherPercentageChanged();

public slots:
	void SetLegend(const QMap<QString, QColor>& legend, const QMap<QString, float>& percentages, bool bNumeric);

private slots:
	void ChangeLegendItem();
	void ChangeOtherPercentage();

private:
	Ui::SeqLegendDlg ui;

	SeqMetadataPtr m_seqMetadata;

	QList<QwtLegendItem*> m_legendItems;

	QMap<QString, QColor> m_legend;
	QMap<QString, float> m_percentages;
	bool m_bNumeric;

	double m_otherPercentage;
};

#endif 
