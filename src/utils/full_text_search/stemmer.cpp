/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "stemmer.h"
#include "alpine_toolkit.h"

#include <QHash>
#include <QtDebug>

/**************************************************************************************************/

QHash<QString, LanguageCode> language_map = {
  { QLatin1String("english"), QLocale::English },
  { QLatin1String("french"), QLocale::French },
  { QLatin1String("german"), QLocale::German },
  { QLatin1String("italian"), QLocale::Italian },
  { QLatin1String("portuguese"), QLocale::Portuguese },
  { QLatin1String("spanish"), QLocale::Spanish },
};

Stemmer::LanguageCodeList
Stemmer::available_languages()
{
  LanguageCodeList languages;

  const char ** c_languages = sb_stemmer_list();

  int i = 0;
  const char * c_language;
  while((c_language = c_languages[i++]) != NULL) {
    QString language = c_language;
    if (language_map.contains(language)) {
      languages << language_map[language];
    } else
      qWarning() << QStringLiteral("Stemmer language %1 is unknown").arg(language);
  }

  return languages;
}

Stemmer::Stemmer(const LanguageCode & language)
{
  QString language_name = QLocale::languageToString(language).toLower();
  const char * c_language_name = language_name.toLatin1().data();
  m_stemmer = sb_stemmer_new(c_language_name, NULL); // "UTF_8"
  if (not m_stemmer)
    qATCritical() << QLatin1String("Stemmer is not available for") << language_name;
}

Stemmer::~Stemmer()
{
  if (m_stemmer)
    sb_stemmer_delete(m_stemmer);
}

QString
Stemmer::process(const QString & word) const
{
  if (not m_stemmer)
    return QString();

  QByteArray utf8_word = word.toUtf8();
  // typedef unsigned char sb_symbol
  const char * stemmed =
    (const char *) sb_stemmer_stem(m_stemmer,
                                   (const sb_symbol *) utf8_word.data(), utf8_word.size());
  if (stemmed == NULL) {
    qATCritical() << QLatin1String("Out of memory");
    return QString();
  } else {
    // sb_stemmer_length(stemmer)
    return QString(stemmed);
  }
}
