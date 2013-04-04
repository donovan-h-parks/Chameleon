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

#ifndef TEXTSEARCH_HPP
#define TEXTSEARCH_HPP

#include "stdafx.h"

/**
 * @brief Search a list of words. Functionality is provided to
 *				filter the list of words based on different criteria. 
 *				The node assoicated with a word is stored for later 
 *				retrieval.
 */
class TextSearch
{
public:
	/** Constructor. */
	TextSearch() {}

	/** Clear the list of words. */
	void clear() { m_words.clear(); }

	/**
	 * @brief Add a word to the list.
	 * @param word Word to add to the list.
	 * @param id Node id to associate with the given word.
	 */
	void add(const QString& word, uint id) { m_words[word] = id; }

	/**
	 * @brief Get a vector of all words which match the specified search.
	 *				A filter of "" will return the entire list of words.
	 * @param searchStr String to search for.
	 * @param searchType Type of search to perform (i.e., starts with, contains, ends with, matches)
	 */
	QStringList filterData(const QString& searchStr, const QString& searchType)
	{
		m_wordFilter.clear();

		QString searchLower = searchStr.toLower();

		// Add in all text that match the specified search.
		QMap<QString, uint>::const_iterator it;
		for(it = m_words.begin(); it != m_words.end(); ++it)
		{
			QString strLower = it.key().toLower();

			bool match = true;
			if(searchType == "matches")
			{
				if(searchLower.size() != strLower.size())
				{
					match = false;
				}
				else
				{
					uint pos = strLower.indexOf(searchLower);
					if(pos != 0)
						match = false;
				}
			}
			else if(searchType == "starts with")
			{
				uint pos = strLower.indexOf(searchLower);
				if(pos != 0)
					match = false;
			}
			else if(searchType == "ends with")
			{
				for(int j = 0; j < searchLower.size(); ++j)
				{
					if(searchLower[searchLower.size()-j-1] != strLower[strLower.size()-j-1])
					{
						match = false;
						break;
					}
				}
			}
			else if(searchType == "contains")
			{
				if(strLower.indexOf(searchLower) == -1)
					match = false;
			}

			if(match)
				m_wordFilter.push_back(it.key());
		}

		return m_wordFilter;		
	}

	/**
	 * @brief Get data associated with a given word.
	 * @param word Word to retrieve data for.
	 * @param id Id associated with the given word.
	 * @return True if the word was found, else false.
	 */
	bool data(const QString& word, uint& id)
	{ 
		QMap<QString, uint>::iterator it;
		
		it = m_words.find(word);
		if(it != m_words.end())
		{
			id = it.value();
			return true;
		}

		return false; 
	}

private:
	/** Map words to associated data. */
	QMap<QString, uint> m_words;

	/** List of filtered words. */
	QStringList m_wordFilter;
};

#endif

