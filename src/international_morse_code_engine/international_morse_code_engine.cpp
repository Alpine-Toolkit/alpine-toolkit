/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "international_morse_code_engine.h"
#include "international_morse_code_engine_table.cpp"

#include <QtDebug>

/**************************************************************************************************/

MorseCodeDecoderNode::MorseCodeDecoderNode()
  : m_dot_branch(nullptr), m_dash_branch(nullptr), m_character('\0')
{}

/**************************************************************************************************/

MorseCodeDecoderNode::~MorseCodeDecoderNode()
{
  if (m_dot_branch)
    delete m_dot_branch;
  if (m_dash_branch)
    delete m_dash_branch;
}

/**************************************************************************************************/

void
MorseCodeDecoderNode::add(QString code, QChar character, int level)
{
  if (level == code.size()) {
    if (m_character == '\0' && character.isLower())
      m_character = character;
  } else {
    QChar part = code[level];
    MorseCodeDecoderNode * branch;
    if (part == '.') {
      if (!m_dot_branch)
	m_dot_branch = new MorseCodeDecoderNode();
      branch = m_dot_branch;
    }
    else {
      if (!m_dash_branch)
	m_dash_branch = new MorseCodeDecoderNode();
      branch = m_dash_branch;
    }
    branch->add(code, character, level+1);
  }
}

/**************************************************************************************************/

/*
 QString::const_iterator stream = encoded_message.cbegin();
 while (stream != encoded_message.cend()) {
 part = *stream;
 return m_dot_branch.decode(++stream);

QChar
MorseCodeDecoderNode::decode(QString::const_iterator & stream) const
{
  part = *stream;
  switch (part) {
  case '.':
    return m_dot_branch.decode(++stream);
  case '-':
    return m_dot_branch.decode(++stream);
  case '/':
    return m_character;
  }
}
*/

/**************************************************************************************************/

InternationalMorseCodeEngine::InternationalMorseCodeEngine()
  : m_root_node()
{
  for (int i = 0; i < 256; i++) {
    QString code(international_morse_codes[i]);
    if (code.size()) {
      m_root_node.add(code, QChar(i));
    }
  }
}

/**************************************************************************************************/

InternationalMorseCodeEngine::~InternationalMorseCodeEngine()
{}

/**************************************************************************************************/

QString
InternationalMorseCodeEngine::encode(const QString & message, bool use_bit, bool compress_bit) const
{
  QString encoded_message;
  bool add_letter_space = false;
  for (QChar character : message) {
    if (character.isSpace()) {
      encoded_message += use_bit ? bit_word_space : word_space;
      add_letter_space = false;
    } else {
      int unicode = character.unicode();
      if (unicode < 256) {
	QString encoded_character(international_morse_codes[unicode]);
	int encoded_character_size = encoded_character.size();
	if (encoded_character_size) {
	  if (add_letter_space)
	    encoded_message += use_bit ? bit_letter_space : letter_space;
	  for (int j = 0; j < encoded_character.size(); j++) {
	    if (j)
	      if (use_bit)
		encoded_message += bit_letter_space;
	    encoded_message += (encoded_character[j] == dot) ?
	      (use_bit ? bit_dot : dot) :
	      (use_bit ? bit_dash : dash);
	  }
	  add_letter_space = true;
	}
      }
    }
  }

  if (use_bit && compress_bit) {
    QString bits = encoded_message;
    encoded_message.clear();

    QChar previous_bit = '\0';
    int count = 0;
    for (QChar bit : bits) {
      if (previous_bit == '\0') {
	previous_bit = bit;
	count = 1;
      } else if (bit == previous_bit) {
	count += 1;
      } else {
	// encoded_message += QString::asprintf("%d%c", count, (previous_bit == '0') ? 'f' : 't');
	encoded_message += QString::asprintf("%i", count);
	previous_bit = bit;
	count = 1;
      }
    }
  }

  return encoded_message;
}

QString
InternationalMorseCodeEngine::decode(const QString & encoded_message) const
{
  QString message;
  const MorseCodeDecoderNode * node = &m_root_node;
  for (QChar part : encoded_message + letter_space) {
    // qInfo() << part << message;
    if (part == dot)
      node = node->dot_branch();
    else if (part == dash)
      node = node->dash_branch();
    else {
      if (node) {
    	QChar character = node->character();
    	if (character != '\0')
    	  message += character;
	else
	  qWarning() << "Character is null";
      } else
    	qWarning() << "Node is null";

      if (part == word_space)
	message += word_space;
      node = &m_root_node;
    }
  }

  return message;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
