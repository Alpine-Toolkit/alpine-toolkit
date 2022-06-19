/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "international_morse_code_engine.h"
#include "international_morse_code_engine_table.cpp"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

MorseCodeDecoderNode::MorseCodeDecoderNode()
  : m_dot_branch(nullptr),
    m_dash_branch(nullptr),
    m_character('\0')
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
    if (m_character == QChar('\0') && character.isLower())
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
    if (code.size())
      m_root_node.add(code, QChar(i));
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
      if (previous_bit == QChar('\0')) {
	previous_bit = bit;
	count = 1;
      } else if (bit == previous_bit) {
	count += 1;
      } else {
	// encoded_message += QString::asprintf("%d%c", count, (previous_bit == '0') ? 'f' : 't');
        // Append previous
	encoded_message += QString::asprintf("%i", count);
	previous_bit = bit;
	count = 1;
      }
    }
    // Append last
    encoded_message += QString::asprintf("%i", count);
  }

  return encoded_message;
}

QString
InternationalMorseCodeEngine::decode(const QString & encoded_message, bool & succeed) const
{
  QString message;
  const MorseCodeDecoderNode * node = &m_root_node;
  for (QChar part : encoded_message + letter_space) {
    // qATInfo() << part << message;
    if (part == dot or part == dash) {
      if (part == dot)
        node = node->dot_branch();
      else
        node = node->dash_branch();
      if (not node) {
        qWarning() << "Error node is null";
        succeed = false;
        return message;
      }
    } else {
      if (node) {
    	QChar character = node->character();
        if (character != QChar('\0'))
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

  succeed = true;
  return message;
}
