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

#include "NewickIO.hpp"

#include "Log.hpp"
#include "TreeTools.hpp"

#include "SplitSystem.hpp"
#include "Split.hpp"

using namespace std;

bool NewickIO::Read(Tree<VisualNode>& tree, const QString& filename)
{
	Log::Inst().Debug("NewickIO::Read(Tree<VisualNode>& tree, const QString& filename)");
	return ParseNewickFile(tree, NULL, filename, false);
}

bool NewickIO::Read(SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted)
{
	Log::Inst().Debug("NewickIO::Read(SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted)");
	return ParseNewickFile(*splitSystem->GetTree(), splitSystem, filename, bImplicitlyRooted);
}

bool NewickIO::ParseNewickFile(Tree<VisualNode>& tree, SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted)
{
	Log::Inst().Debug("NewickIO::ParseNewickFile()");

	// Parse Newick file
	QString newickFile = filename;
	newickFile.replace('\\', '/');

	QFile file(newickFile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open file: " + filename);
		return false;
	}

	// Concatenate lines in file until we reach the ending semi colon:
	QString temp, newickStr;
	QStringList newickTrees;
	QTextStream textStream(&file);
	while(!textStream.atEnd())
  {
		temp = textStream.readLine();
    int index = temp.indexOf(";");
		if(index != -1)
    {
			newickStr += temp.left(index + 1);
			newickTrees.push_back(newickStr);
			newickStr = "";
		}
    else 
		{
			newickStr += temp;
		}
	}

	file.close();

	// Parse each tree and add to split system
	if(newickTrees.size() == 1)
	{
		bool bSuccess = ParseNewickString(tree, splitSystem, newickTrees.at(0), bImplicitlyRooted);
		if(splitSystem)
		{
			if(splitSystem->GetSamples()->GetSequences()->GetNumberOutgroupSeq() == 1 && splitSystem->GetSamples()->GetSequences()->IsOutgroupSequence("Implicit root"))
				Log::Inst().Write("Phylogeney contains " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumSequences()) + " taxa and is implicitly rooted.");
			else
				Log::Inst().Write("Phylogeney contains " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumSequences()) + " taxa and " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumberOutgroupSeq()) + " outgroup taxa.");
		}
		return bSuccess;
	}
	else if(newickTrees.size() > 1)
	{
		Log::Inst().Write("Creating split system from " + QString("%1").arg(newickTrees.size()) + " trees.");
		bool bSuccess = true;
		foreach(const QString& newickStr, newickTrees)
		{
			Tree<VisualNode> tree;
			bSuccess &= ParseNewickString(tree, splitSystem, newickStr, bImplicitlyRooted);
		}

		if(bImplicitlyRooted)
			Log::Inst().Write("Phylogeney contains " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumSequences()) + " taxa and is implicitly rooted.");
		else
			Log::Inst().Write("Phylogeney contains " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumSequences()) + " taxa and " + QString("%1").arg(splitSystem->GetSamples()->GetSequences()->GetNumberOutgroupSeq()) + " outgroup taxa.");
		return bSuccess;
	}

	Log::Inst().Error("File does not contain a valid Newick string. Trees must end with a semicolon.");
	return false;
}

void NewickIO::ParseNodeInfo(VisualNode* node, QString& nodeInfo, bool bLeafVisualNode)
{	
	QString length;
	QString name;
	QString supportValue;

	// check if this element has length
	int colon = nodeInfo.lastIndexOf(':');
  if(colon != -1)
  {
    length = nodeInfo.mid(colon + 1).trimmed();
		nodeInfo = nodeInfo.left(colon).trimmed();
  }

	// check for name and/or support value
	int lastP = nodeInfo.lastIndexOf('\'');
	int firstP = nodeInfo.indexOf('\'');
	if(firstP != -1)
	{
		name = nodeInfo.mid(firstP+1, lastP-firstP-1);
		supportValue = nodeInfo.mid(lastP+1).trimmed();
	}
	else
	{
		int spacePos = nodeInfo.indexOf(' ');
		if(spacePos != -1)
		{
			// parse the name and support value
			name = nodeInfo.mid(0, spacePos-1);	
			supportValue = nodeInfo.mid(spacePos+1).trimmed();
		}
		else
		{
			// The remaining description is either a name of support value depending 
			// on whether this is a leaf or internal node.
			if(bLeafVisualNode)
			{
				name = nodeInfo.trimmed();
			}
			else
			{
				bool bOK;
				int value = nodeInfo.toInt(&bOK);
				if(bOK)
					supportValue = nodeInfo.trimmed();
				else
				{
					name = nodeInfo.trimmed();
				}
			}
		}
	}	

	if(!name.isEmpty())
		node->SetName(name);

	if(!length.isEmpty())
		node->SetDistanceToParent(length.toDouble());

	if(!supportValue.isEmpty())
		node->SetSupport(supportValue.toInt());		
}

bool NewickIO::ParseNewickString(Tree<VisualNode>& tree, SplitSystem *const splitSystem, const QString& newickStr, bool bImplicitlyRooted)
{
	Log::Inst().Debug("Entering NewickIO::ParseNewickString()");

	// create root node
	uint internalNodeId = Tree<VisualNode>::ROOT_ID - 1;
	VisualNode* root;
	if(bImplicitlyRooted)
		root = new VisualNode(Tree<VisualNode>::ROOT_ID);
	else
		root = new VisualNode(internalNodeId--);

	tree.SetRootNode(root);

	int lastP  = newickStr.lastIndexOf(')');
  int firstP = newickStr.indexOf('(');
  int semi = newickStr.lastIndexOf(';');

	QString content = newickStr.mid(firstP + 1, lastP - firstP);
  QString rootElements = newickStr.mid(lastP + 1, semi - lastP - 1);
  
	ParseNodeInfo(root, rootElements, false);

	// parse newick string
	QStack<VisualNode*> nodeStack;
	nodeStack.push(root);
	QString nodeInfo;
	VisualNode* activeVisualNode = NULL;	
	uint leafId = 0;
	QStringList missingSeqs;
	QStringList validSeqs;
	for(int i = 0; i < content.size(); ++i)
	{
		QChar ch = content.at(i);

		if(ch == '(')
		{
			// create a new internal node which will be the child 
			// of the node on the top of the stack
			VisualNode* node(new VisualNode(internalNodeId--));
			nodeStack.top()->AddChild(node);
			nodeStack.push(node);
		}
		else if(ch == ')' || ch == ',')
		{
			if(activeVisualNode)
			{
				// if there is a currently active node, then we are
				// processing an internal node
				ParseNodeInfo(activeVisualNode, nodeInfo, false);				
			}
			else
			{
				// if there is no currently active node, then we
				// must create a new leaf node
				VisualNode* node(new VisualNode(leafId++));
				nodeStack.top()->AddChild(node);

				ParseNodeInfo(node, nodeInfo, true);		

				if(splitSystem)
				{
					uint seqId;
					bool bPresent = splitSystem->GetSamples()->GetSequences()->GetSequenceId(node->GetName(), seqId);
					if(!bPresent)
					{
						bool bOutgroup = splitSystem->GetSamples()->GetSequences()->IsOutgroupSequence(node->GetName());
						if(bOutgroup)
						{
							node->SetId(Tree<VisualNode>::ROOT_ID);
							validSeqs.push_back(node->GetName());
						}
						else
							missingSeqs.push_back(node->GetName());
					}
					else
					{
						node->SetId(seqId);
						validSeqs.push_back(node->GetName());
					}
				}
			}

			activeVisualNode = NULL;
			nodeInfo = "";

			// we are finished processing all children of the node on the top of the stack
			if(ch == ')')
				activeVisualNode = nodeStack.pop();
		}
		else
		{
			// character is indicate the properties of a node
			nodeInfo += ch;
		}
	}

	if(missingSeqs.size() > 0)
	{
		QString missingSeqStr = "The following " + QString("%1").arg(missingSeqs.size()) + " sequences are contained in the phylogeny file, but not the sample file: \n";
		qSort(missingSeqs.begin(), missingSeqs.end());
		
		foreach(QString seqName, missingSeqs)
			missingSeqStr += seqName + ",";
		missingSeqStr = missingSeqStr.left(missingSeqStr.size()-1);	// remove last comma

		Log::Inst().Warning(missingSeqStr);

		Log::Inst().Warning("Lineages containing only missing sequences have been removed from the tree.");

		tree.Project(validSeqs);
		Write(tree, "ProjectedTree.tre");
	}

	if(!nodeStack.isEmpty())
	{
		Log::Inst().Error("Failed to parse Newick string. There does not appear to be an even number of opening and closing parentheses.");
		return false;
	}

	Log::Inst().Debug("NewickIO::ParseNewickString() - setting up split system");

	// setup implicit rooting
	if(splitSystem != NULL)
	{
		if(!splitSystem->GetSamples()->GetSequences()->IsOutgroupSequence("Implicit root"))
		{
			// Check if an implicit root should be added. A split system may already contain an implicit root if we
			// are building a split system from multiple sources (e.g., a forest of bootstrap trees).
			if(bImplicitlyRooted)
			{
				if(!splitSystem->GetSamples()->GetSequences()->IsOutgroup())
				{
					tree.GetRootNode()->SetName("Implicit root");
					splitSystem->GetSamples()->GetSequences()->AddOutgroupSequence("Implicit root");
				}
				else
				{
					Log::Inst().Warning("Tree contains outgroup sequences and implicit rooting was requested. Implicit rooting is being ignored.");
				}
			}
		}
	}

	Log::Inst().Debug("Leaving NewickIO::ParseNewickString()");
	return true;
}

void NewickIO::Write(Tree<VisualNode>& tree, const QString& filename) const
{
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to create file: " + filename);
		return;
	}

	QTextStream out(&file);
	Write(tree, out);

	file.close();
}

void NewickIO::CreateNewickStr(Tree<VisualNode>& tree, QString& newickStr) const
{
	Log::Inst().Debug("NewickIO::CreateNewickStr()");

	QTextStream out(&newickStr);
	Write(tree, out);
}

void NewickIO::Write(Tree<VisualNode>& tree, QTextStream& out) const
{
	out << "(";

	VisualNode* root = tree.GetRootNode();
	
  if(tree.GetNumberOfLeaves() == 0)
  {
    QString name = root->GetName();
		out <<  name;

		double dist = root->GetDistanceToParent();
		if(dist != VisualNode::NO_DISTANCE)
			out << " " << dist;
  }
  else
  {
		WriteNodes(tree, out, root);
  }
	out << ")";
	
	// Output the name of the root if it has one
	if(!root->GetName().isEmpty())
	{
		QString name = root->GetName();
		out <<  name;
	}
	
	out << ";";
}

void NewickIO::WriteNodes(Tree<VisualNode>& tree, QTextStream& out, VisualNode* parent) const
{
	QList<uint> childrenId = parent->GetChildrenIds();

	WriteElements(tree, out, parent->GetChild(0));
	for(int i = 1; i < childrenId.size(); i++)
	{
		out << ",";
		WriteElements(tree, out, parent->GetChild(i));
	}
}

void NewickIO::WriteElements(Tree<VisualNode>& tree, QTextStream& out, VisualNode* child) const
{	
  if(child->GetNumberOfChildren() != 0)
  {
    out << "(";
		WriteNodes(tree, out, child); 
    out << ")";
  }

	if(!child->GetName().isEmpty())
	{
		QString name = child->GetName();
		if(name.contains(' '))
			out << "\"" << name << "\"";
		else
			out << name;
	}
	
	if(!child->IsLeaf() && child->GetSupport() != VisualNode::NO_DISTANCE)
		out << child->GetSupport();

	if(child->GetDistanceToParent() != VisualNode::NO_DISTANCE)
		out << ":" << child->GetDistanceToParent();
}
