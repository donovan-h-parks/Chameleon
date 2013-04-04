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

#include "ParsimonyCalculator.hpp"
#include "Metadata.hpp"
#include "Samples.hpp"

using namespace std;

QString ParsimonyData::field;

uint ParsimonyCalculator::Calculate(Tree<VisualNode>* tree, SamplesPtr samples, const QString& field, bool bPhylogeny)
{
	Log::Inst().Debug("ParsimonyCalculator::Calculate(...)");

	ParsimonyData::field = field;

	// get unique characters within this field
	QVector<QString> values = samples->GetMetadata()->GetValues(field);
	QSet<QString> uniqueCharacters;
	for(int i = 0; i < values.size(); ++i)
		uniqueCharacters.insert(values.at(i));

	QStringList characters = uniqueCharacters.toList();

	// initialize leaf nodes
	QList<VisualNode*> leaves = tree->GetLeaves();
	foreach(VisualNode* leaf, leaves)
	{
		ParsimonyData parsimonyData;
		parsimonyData.nodeScore = 0;

		foreach(const QString& character, characters)
		{
			parsimonyData.characterScores[character].score = INT_MAX;
			parsimonyData.characterScores[character].bPresent = false;
		}
	
		QList<QString> charactersPresent;
		if(bPhylogeny)
		{
			charactersPresent = samples->GetSampleMetadataFromSeq(field, leaf->GetName());
		}
		else // dealing with a cluster tree where the leaf names correspond to sample ids
		{
			Sample sample;
			uint sampleId;
			if(samples->GetSample(leaf->GetName(), sample))
				sampleId = sample.GetId();
			else
				Log::Inst().Error("Invalid sample specified in parsimony calculation: " + leaf->GetName());

			charactersPresent.append(samples->GetMetadata()->GetValue(field, sampleId));
		}

		foreach(QString character, charactersPresent)
		{
			parsimonyData.characterScores[character].score = 0;
			parsimonyData.characterScores[character].bPresent = true;
		}

		m_parsimonyData[leaf->GetId()] = parsimonyData;
	}

	// Propagate parsimony scores up tree
	CalculateUp(tree, field, characters);

	// Propagate most parsimonious character states down tree.
	CalculateDown(tree, field, characters);

	return m_parsimonyData[tree->GetRootNode()->GetId()].GetNodeScore();
}

void ParsimonyCalculator::CalculateUp(Tree<VisualNode>* tree, const QString& field, const QStringList& characters)
{
	Log::Inst().Debug("ParsimonyCalculator::CalculateUp(...)");

	QList<VisualNode*> postOrderNodes = tree->PostOrder();
	foreach(VisualNode* node, postOrderNodes)
	{
		if(node->IsLeaf())
			continue;

		// calculate parsimony data for internal node
		ParsimonyData parsimonyData;
		parsimonyData.nodeScore = INT_MAX;
		foreach(const QString& character, characters)
		{
			parsimonyData.characterScores[character].score = 0;
			parsimonyData.characterScores[character].bPresent = false;
			foreach(VisualNode* child, node->GetChildren())
			{
				uint nodeScore = m_parsimonyData[child->GetId()].GetNodeScore() + 1;
				uint characterScore = m_parsimonyData[child->GetId()].GetScore(character);

				if(nodeScore < characterScore)
					parsimonyData.characterScores[character].score += nodeScore;
				else
					parsimonyData.characterScores[character].score += characterScore;

				if(m_parsimonyData[child->GetId()].characterScores[character].bPresent)
					parsimonyData.characterScores[character].bPresent = true;
			}

			if(parsimonyData.characterScores[character].score < parsimonyData.nodeScore)
				parsimonyData.nodeScore = parsimonyData.characterScores[character].score;
		}

		m_parsimonyData[node->GetId()] = parsimonyData;
	}
}

void ParsimonyCalculator::CalculateDown(Tree<VisualNode>* tree, const QString& field, const QStringList& characters)
{
	Log::Inst().Debug("ParsimonyCalculator::CalculateDown(...)");

	// assign parsimonious characters to root node
	ParsimonyData& data = m_parsimonyData[tree->GetRootNode()->GetId()];
	foreach(const QString& character, characters)
	{
		if(data.GetScore(character) == data.GetNodeScore())
			data.parsimoniousCharacters.insert(character);
	}

	// assign parsimonious characters to internal nodes in a breadth-first manner
	QQueue<VisualNode*> queue;
	queue.enqueue(tree->GetRootNode());
	while(!queue.empty())
	{
		VisualNode* node = queue.dequeue();

		// assign parsimonious characters to node
		uint numCharacters = 0;
		ParsimonyData& dataNode = m_parsimonyData[node->GetId()];
		foreach(const QString& character, characters)
		{	
			if(dataNode.GetNodeScore() == dataNode.GetScore(character))
				dataNode.parsimoniousCharacters.insert(character);

			if(dataNode.characterScores[character].bPresent)
				numCharacters++;
		}

		if(dataNode.GetNodeScore() > 0)
			dataNode.consistencyIndex = float(numCharacters-1) / dataNode.GetNodeScore();
		else
			dataNode.consistencyIndex = 1.0;
		
		node->SetParsimonyData(&dataNode);
		
		// process children
		foreach(VisualNode* child,  node->GetChildren())
			queue.enqueue(child);
	}
}
