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

#ifndef _DATA_TYPES_
#define _DATA_TYPES_

// basic data types
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long ulong;

// advanced data types
typedef QVector< QVector<double> > Matrix;
typedef QVector< QVector<bool> > MatrixBool;

// smart pointers
class UniSplit;
typedef QSharedPointer<UniSplit> UniSplitPtr;

class Samples;
typedef QSharedPointer<Samples> SamplesPtr;

class Sequences;
typedef QSharedPointer<Sequences> SequencesPtr;

class System;
typedef QSharedPointer<System> SystemPtr;

class SplitSystem;
typedef QSharedPointer<SplitSystem> SplitSystemPtr;

class MatrixSystem;
typedef QSharedPointer<MatrixSystem> MatrixSystemPtr;

class Split;
typedef QSharedPointer<Split> SplitPtr;

class OrdinationPlots;
typedef QSharedPointer<OrdinationPlots> OrdinationPlotsPtr;

class ParallelCoordPlot;
typedef QSharedPointer<ParallelCoordPlot> ParallelCoordPlotPtr;

class ResemblanceScatterplot;
typedef QSharedPointer<ResemblanceScatterplot> ResemblanceScatterplotPtr;

class Legends;
typedef QSharedPointer<Legends> LegendsPtr;

class Metadata;
typedef QSharedPointer<Metadata> MetadataPtr;

class QwtLinearColorMap;
typedef QSharedPointer<QwtLinearColorMap> QwtLinearColorMapPtr;

class PlotPicker;
typedef QSharedPointer<PlotPicker> PlotPickerPtr;

class VisualTree;
typedef QSharedPointer<VisualTree> VisualTreePtr;

class VisualClusterTree;
typedef QSharedPointer<VisualClusterTree> VisualClusterTreePtr;

class VisualPhylogeny;
typedef QSharedPointer<VisualPhylogeny> VisualPhylogenyPtr;

class VisualMatrix;
typedef QSharedPointer<VisualMatrix> VisualMatrixPtr;

class ParsimonyCalculator;
typedef QSharedPointer<ParsimonyCalculator> ParsimonyCalculatorPtr;

class ColorMaps;
typedef QSharedPointer<ColorMaps> ColorMapsPtr;

class SeqMetadata;
typedef QSharedPointer<SeqMetadata> SeqMetadataPtr;

#endif

