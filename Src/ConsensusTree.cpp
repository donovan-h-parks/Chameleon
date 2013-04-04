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

#include "ConsensusTree.hpp"

#include "SplitSystem.hpp"
#include "NewickIO.hpp"

void ConsensusTree::AddTree(const Tree<VisualNode>& tree)
{
	m_trees.push_back(tree);
}

bool nodeSizeLessThan(const VisualNode* s1, const VisualNode* s2)
{
	uint s1Size = s1->GetNumberOfChildren();
	uint s2Size = s2->GetNumberOfChildren();

	return s1Size < s2Size;
}

void ConsensusTree::MajorityRuleTree(Tree<VisualNode>& tree)
{
	NewickIO newickIO;
	QString newickStrs;
	for(int treeId = 0; treeId < m_trees.size(); ++treeId)
	{
		QString newickStr;
		newickIO.CreateNewickStr(m_trees[treeId], newickStr);
		newickStrs += newickStr;
	}

	QFile file("output/Trees.tre");
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to create file: output/Trees.tre");
		return;
	}

	QTextStream out(&file);

	out << newickStrs;

	file.close();
}

QString ConsensusTree::CreateUniqueId(const VisualNode* node)
{
	QList<VisualNode*> children = node->GetChildren();
	QStringList childrenNames;
	for(int childId = 0; childId < children.size(); ++childId)
		childrenNames.push_back(children.at(childId)->GetName());

	qSort(childrenNames);

	QString id;
	for(int childId = 0; childId < childrenNames.size(); ++childId)
		id += childrenNames.at(childId) + "|";

	return id;
}
