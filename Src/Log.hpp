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

#ifndef _LOG_
#define _LOG_

#include "stdafx.h"

/**
 * @brief Singleton class for writing general information, warnings, and errors 
 *				to both the application console and to file.
 */
class Log
{
public:
	/** Destructor */
	~Log()
	{
		m_log.close();
	}

	/** Get the one and only instance of this class.. */
	static Log& Inst()
	{
		static Log log;
		return log;
	}

	/** Add QTextBrowser to report logged data to. */
	void AddTextBrowser(QTextEdit* textBrowser, QTabWidget* tabWidget, QWidget* logTab)
	{
		//m_textEdit = QSharedPointer<QTextEdit>(textBrowser);
		//m_tabWidget = QSharedPointer<QTabWidget>(tabWidget);
		//m_logTab = QSharedPointer<QWidget>(logTab);
	}

	/** Clear all text from log window. */
	void Clear()
	{
		if(m_textEdit)
			m_textEdit->clear();
	}

	void Write(const char* text)
	{
		m_log << text << std::endl;

		if(m_textEdit)
		{
			m_textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
			m_textEdit->setFontWeight(QFont::Normal);
			m_textEdit->setFontFamily("Courier New");
			m_textEdit->setTextColor(QColor(0,0,0));
			m_textEdit->append(text);
		}
		else
		{
			m_stdout << text << endl;
		}
	}

	void Write(const std::string& text)
	{
		Write(text.c_str());
	}

	void Write(const QString& text)
	{
		Write(text.toStdString().c_str());
	}

	void Write(const Matrix& matrix)
	{
		for(int i = 0; i < matrix.size(); ++i)
		{
			QString row = "";
			for(int j = 0; j < matrix.at(i).size(); ++j)
			{
				QString data = QString("%1").arg(matrix.at(i).at(j), 12, 'g', 4);
				row += data;
			}

			Write(row);
		}
	}

	void Write(const QHash<QString, uint>& map)
	{
		QHashIterator<QString, uint> iter(map);

		// find longest key
		int longestKey = 0;
		while(iter.hasNext())
		{
			iter.next();
			if(iter.key().size() > longestKey)
				longestKey = iter.key().size();
		}

		iter.toFront();
		while(iter.hasNext())
		{
			iter.next();
			QString key = QString("%1").arg(iter.key(), longestKey, ' ');
			QString value = QString("%1").arg(iter.value());
			Write(key + ": " + value);
		}
	}
  
	void Warning(const char* text)
	{
		m_log << "(Warning) " << text << std::endl;

		if(m_textEdit)
		{
			m_textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
			m_textEdit->setFontWeight(QFont::Normal);
			m_textEdit->setFontFamily("Courier New");
			m_textEdit->setTextColor(QColor(127,0,0));
			m_textEdit->append("(Warning) " + QString(text));		

			// switch to log tab
			m_tabWidget->setCurrentWidget(m_logTab.data());
		}
		else
		{
			m_stdout << "(Warning) " << text << endl;
		}
	}

	void Warning(const std::string& text)
	{
		Warning(text.data());
	}

	void Warning(const QString& text)
	{
		Warning(text.toStdString().c_str());
	}

	void Error(const char* text)
	{
		m_log << "(Error) " << text << std::endl;

		if(m_textEdit)
		{
			m_textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
			m_textEdit->setFontWeight(QFont::Bold);
			m_textEdit->setFontFamily("Courier New");
			m_textEdit->setTextColor(QColor(255,0,0));
			m_textEdit->append("(Error) " + QString(text));

			// switch to log tab
			m_tabWidget->setCurrentWidget(m_logTab.data());
		}
		else
		{
			m_stdout << "(Error) " << text << endl;
		}
	}

	void Error(const std::string& text)
	{
		Error(text.c_str());
	}

	void Error(const QString& text)
	{
		Error(text.toStdString().c_str());
	}

	void Debug(const char* text)
	{
		#ifdef DEBUG_LOG
		{
			time_t seconds = time(NULL);
			m_log << "[" << seconds << "]" << text << std::endl;

			if(m_textEdit)
			{
				m_textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
				m_textEdit->setFontWeight(QFont::Normal);
				m_textEdit->setFontFamily("Courier New");
				m_textEdit->setTextColor(QColor(0,0,0));
				m_textEdit->append(text);
			}
			else
			{
				m_stdout << text << endl;
			}
		}
		#endif
	}

	void Debug(const std::string& text)
	{
		Debug(text.c_str());
	}

	void Debug(const QString& text)
	{
		Debug(text.toStdString().c_str());
	}

protected:
	/** Private singleton constructor (must instantiate this class through Inst()). */
	Log(): m_stdout(stdout, QIODevice::WriteOnly)
	{
		m_log.open("Log.txt");
	}

	/** Private copy constructor (must instantiate this class through Inst()). */
  Log(const Log&);

	/** Private assignment constructor (must instantiate this class through Inst()). */
  Log& operator= (const Log&);


private:
	/** Log reports to file. */
	std::ofstream m_log;

	/** Graphical textbox to report logged data to. */
	QSharedPointer<QTextEdit> m_textEdit;

	/** Tab widget and page where log textbox is contained. */
	QSharedPointer<QTabWidget> m_tabWidget;
	QSharedPointer<QWidget> m_logTab;

	/** Console to report logged data to. */
	QTextStream m_stdout;
};

#endif