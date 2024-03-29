/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "geoportail_plugin.h"
#include "qtcarto.h"

#include <QString>
#include <QXmlStreamWriter>

/**************************************************************************************************/

QcGeoportailLayer::QcGeoportailLayer(QcGeoportailPlugin * plugin,
                                     int map_id,
                                     int position,
                                     const QString & title,
                                     const QString & name,
                                     const QString & image_format,
                                     const QString & style)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, image_format),
    m_style(style)
{}

QcGeoportailLayer::QcGeoportailLayer(const QcGeoportailLayer & other)
  : QcWmtsPluginLayer(other),
    m_style(other.m_style)
{}

QcGeoportailLayer::~QcGeoportailLayer()
{}

QcGeoportailLayer &
QcGeoportailLayer::operator=(const QcGeoportailLayer & other)
{
  if (this != &other) {
    QcWmtsPluginLayer::operator=(other);
    m_style = other.m_style;
  }

  return *this;
}

QUrl
QcGeoportailLayer::url(const QcTileSpec & tile_spec) const
{
  /*
   * Vue aérienne LAYER = ORTHOIMAGERY.ORTHOPHOTOS
   * http://wxs.ign.fr/<KEY>/geoportail/wmts?
   * SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=ORTHOIMAGERY.ORTHOPHOTOS
   * &STYLE=normal&TILEMATRIXSET=PM&TILEMATRIX=16&TILEROW=23327&TILECOL=33919&FORMAT=image/jpeg
   *
   * Carte LAYER = GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN-EXPRESS.STANDARD
   * http://wxs.ign.fr/<KEY>/geoportail/wmts?
   * SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN-EXPRESS.STANDARD
   * &STYLE=normal&TILEMATRIXSET=PM&TILEMATRIX=16&TILEROW=23327&TILECOL=33920&FORMAT=image/jpeg
   *
   * Carte topographique LAYER = GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN25TOUR
   * http://wxs.ign.fr/<KEY>/geoportail/wmts?
   * SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN25TOUR
   * &STYLE=normal&TILEMATRIXSET=PM&TILEMATRIX=16&TILEROW=23326&TILECOL=33920&FORMAT=image/jpeg
   *
   * Parcelles cadastrales
   * http://wxs.ign.fr/<KEY>/geoportail/wmts?
   * SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=CADASTRALPARCELS.PARCELS
   * &STYLE=bdparcellaire&TILEMATRIXSET=PM&TILEMATRIX=16&TILEROW=23325&TILECOL=33915&FORMAT=image/png
   *
   * Routes
   * http://wxs.ign.fr/<KEY>/geoportail/wmts?
   * SERVICE=WMTS&REQUEST=GetTile&VERSION=1.0.0&LAYER=TRANSPORTNETWORKS.ROADS&STYLE=normal
   * &TILEMATRIXSET=PM&TILEMATRIX=16&TILEROW=23326&TILECOL=33917&FORMAT=image/png
   *
   */

  // Fixme: name, split ???
  QStringList parameters;
  parameters << QStringLiteral("SERVICE=WMTS");
  parameters << QStringLiteral("VERSION=1.0.0");
  parameters << QStringLiteral("REQUEST=GetTile");
  parameters << QStringLiteral("LAYER=") + name();
  parameters << QStringLiteral("STYLE=") + m_style;
  parameters << QStringLiteral("FORMAT=image/") + image_format();
  parameters << QStringLiteral("TILEMATRIXSET=PM");
  parameters << QStringLiteral("TILEMATRIX=") + QString::number(tile_spec.level());
  parameters << QStringLiteral("TILEROW=") + QString::number(tile_spec.y());
  parameters << QStringLiteral("TILECOL=") + QString::number(tile_spec.x());

  QString api_key = static_cast<QcGeoportailPlugin *>(plugin())->license().api_key();

  return QUrl(QStringLiteral("http://wxs.ign.fr/") + // https
              api_key +
              QStringLiteral("/geoportail/wmts?") +
              parameters.join(QString('&')));
}

/**************************************************************************************************/

const QString QcGeoportailPlugin::PLUGIN_NAME = "geoportail";
const QString PLUGIN_TITLE = "Géoportail";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 256;

QcGeoportailPlugin::QcGeoportailPlugin(const QcGeoportailWmtsLicense & license)
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new QcMercatorTileMatrixSet(NUMBER_OF_LEVELS, TILE_SIZE)),
    m_license(license)
{
  connect(network_manager(),
          SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
	  this,
	  SLOT(on_authentication_request_slot(QNetworkReply*, QAuthenticator*)));

  // Fixme: to json
  int map_id = -1;
  add_layer(new QcGeoportailLayer(this,
                                  ++map_id, // 1
                                  2,
                                  QStringLiteral("Carte topographique"),
                                  QStringLiteral("GEOGRAPHICALGRIDSYSTEMS.MAPS"), // .SCAN25TOUR
                                  QStringLiteral("jpeg"),
                                  QStringLiteral("normal")
                                  ));
  add_layer(new QcGeoportailLayer(this,
                                  ++map_id, // 2
                                  3,
                                  QStringLiteral("Vue aérienne"),
                                  QStringLiteral("ORTHOIMAGERY.ORTHOPHOTOS"),
                                  QStringLiteral("jpeg"),
                                  QStringLiteral("normal")
                                  ));
  add_layer(new QcGeoportailLayer(this,
                                  ++map_id, // 0
                                  1,
                                  QStringLiteral("Carte"),
                                  QStringLiteral("GEOGRAPHICALGRIDSYSTEMS.MAPS.SCAN-EXPRESS.STANDARD"),
                                  QStringLiteral("jpeg"),
                                  QStringLiteral("normal")
                                  ));
  add_layer(new QcGeoportailLayer(this,
                                  ++map_id, // 3
                                  4,
                                  QStringLiteral("Routes"),
                                  QStringLiteral("TRANSPORTNETWORKS.ROADS"),
                                  QStringLiteral("png"),
                                  QStringLiteral("normal")
                                  ));
  add_layer(new QcGeoportailLayer(this,
                                  ++map_id, // 4
                                  5,
                                  QStringLiteral("Parcelles cadastrales"),
                                  QStringLiteral("CADASTRALPARCELS.PARCELS"),
                                  QStringLiteral("png"),
                                  QStringLiteral("bdparcellaire")
                                  ));

  // QVector<QcWgsCoordinate> coordinates;
  // coordinates << QcWgsCoordinate(0.23, 48.05);
  // coordinates << QcWgsCoordinate(2.15, 46.60);
  // coordinates << QcWgsCoordinate(4.39, 43.91);
  // m_elevation_reply = coordinate_elevations(coordinates);

  // QcLocationServiceQuery query;
  // query.set_request_id(QString::number(1));
  // query.set_maximum_responses(1);
  // query.set_srs_name(QStringLiteral("epsg:4326"));
  // query.set_country_code(QStringLiteral("StreetAddress"));
  // // QStringLiteral("PositionOfInterest")
  // // QStringLiteral("Administratif")
  // // QStringLiteral("CadastralParcel")
  // query.set_free_form_address("7 rue jean baillet 95870 bezons");
  // m_location_reply = geocode_request(query);

  // QcLocationServiceReverseQuery query;
  // query.set_request_id(QString::number(1));
  // query.set_maximum_responses(1);
  // // query.set_srs_name(QStringLiteral("epsg:4326"));
  // query.set_coordinate(QcWgsCoordinate(2.3241667, 48.8033333));
  // m_location_reverse_reply = reverse_geocode_request(query);
}

QcGeoportailPlugin::~QcGeoportailPlugin()
{}

void
QcGeoportailPlugin::on_authentication_request_slot(QNetworkReply * reply,
                                                   QAuthenticator * authenticator)
{
  Q_UNUSED(reply);
  // qQCInfo() << "on_authentication_request_slot";
  authenticator->setUser(m_license.user());
  authenticator->setPassword(m_license.password());
}

QSharedPointer<QcLocationServiceReply>
QcGeoportailPlugin::geocode_request(const QcLocationServiceQuery & query)
{
  QByteArray xml_request;
  QXmlStreamWriter stream(&xml_request);
  stream.setAutoFormatting(true);
  stream.setCodec("UTF-8");
  stream.writeStartDocument();
  stream.writeStartElement(QStringLiteral("XLS"));
  QXmlStreamAttributes xls_attributes;
  xls_attributes.append(QStringLiteral("xmlns:xls"), QStringLiteral("http://www.opengis.net/xls"));
  xls_attributes.append(QStringLiteral("xmlns:gml"), QStringLiteral("http://www.opengis.net/gml"));
  xls_attributes.append(QStringLiteral("xmlns"), QStringLiteral("http://www.opengis.net/xls"));
  xls_attributes.append(QStringLiteral("xmlns:xsi"), QStringLiteral("http://www.w3.org/2001/XMLSchema-instance"));
  xls_attributes.append(QStringLiteral("version"), QStringLiteral("1.2"));
  xls_attributes.append(QStringLiteral("xsi:schemaLocation"), QStringLiteral("http://www.opengis.net/xls http://schemas.opengis.net/ols/1.2/olsAll.xsd"));
  stream.writeAttributes(xls_attributes);
  stream.writeEmptyElement(QStringLiteral("RequestHeader"));
  QXmlStreamAttributes header_attributes;
  header_attributes.append(QStringLiteral("srsName"), query.srs_name());
  stream.writeStartElement(QStringLiteral("Request"));
  QXmlStreamAttributes request_attributes;
  request_attributes.append(QStringLiteral("maximumResponses"), QString::number(query.maximum_responses()));
  request_attributes.append(QStringLiteral("requestID"), query.request_id());
  request_attributes.append(QStringLiteral("version"), QStringLiteral("1.2"));
  request_attributes.append(QStringLiteral("methodName"), QStringLiteral("LocationUtilityService"));
  stream.writeAttributes(request_attributes);

  stream.writeStartElement(QStringLiteral("GeocodeRequest"));
  stream.writeAttribute(QStringLiteral("returnFreeForm"), QStringLiteral("false"));
  stream.writeStartElement(QStringLiteral("Address"));
  stream.writeAttribute(QStringLiteral("countryCode"), query.country_code());
  if (!query.free_form_address().isEmpty())
    stream.writeTextElement(QStringLiteral("freeFormAddress"), query.free_form_address());
  else if (!query.street().isEmpty()) {
    stream.writeStartElement(QStringLiteral("StreetAddress"));
    stream.writeTextElement(QStringLiteral("Street"), query.street());
    stream.writeEndElement();
    stream.writeTextElement(QStringLiteral("PostalCode"), query.postale_code());
    // for (const auto & pair : query.place()) {
    const QMap<QString, QString> & place = query.place();
    QMap<QString, QString>::const_iterator it;
    for (it = place.begin(); it != place.end(); ++it)
      stream.writeTextElement(it.key(), it.value());
  }
  stream.writeEndElement();

  stream.writeEndElement();
  stream.writeEndDocument();

  // http://wxs.ign.fr/<API_KEY>/geoportail/ols?
  QUrl url = QStringLiteral("https://wxs.ign.fr/") +
    m_license.api_key() +
    QStringLiteral("/geoportail/ols?");

  QNetworkReply * reply = post(url, xml_request);

  return QSharedPointer<QcLocationServiceReply>(new QcGeoportailLocationServiceReply(reply, query));
}

QSharedPointer<QcLocationServiceReverseReply>
QcGeoportailPlugin::reverse_geocode_request(const QcLocationServiceReverseQuery & query)
{
  // Fixme: duplicated code

  QByteArray xml_request;
  QXmlStreamWriter stream(&xml_request);
  stream.setAutoFormatting(true);
  stream.setCodec("UTF-8");
  stream.writeStartDocument();
  stream.writeStartElement(QStringLiteral("XLS"));
  QXmlStreamAttributes xls_attributes;
  xls_attributes.append(QStringLiteral("xmlns:xls"), QStringLiteral("http://www.opengis.net/xls"));
  xls_attributes.append(QStringLiteral("xmlns:gml"), QStringLiteral("http://www.opengis.net/gml"));
  xls_attributes.append(QStringLiteral("xmlns"), QStringLiteral("http://www.opengis.net/xls"));
  xls_attributes.append(QStringLiteral("xmlns:xsi"), QStringLiteral("http://www.w3.org/2001/XMLSchema-instance"));
  xls_attributes.append(QStringLiteral("version"), QStringLiteral("1.2"));
  xls_attributes.append(QStringLiteral("xsi:schemaLocation"), QStringLiteral("http://www.opengis.net/xls http://schemas.opengis.net/ols/1.2/olsAll.xsd"));
  stream.writeAttributes(xls_attributes);
  stream.writeEmptyElement(QStringLiteral("RequestHeader"));
  QXmlStreamAttributes header_attributes;
  // header_attributes.append(QStringLiteral("srsName"), query.srs_name());
  stream.writeStartElement(QStringLiteral("Request"));
  QXmlStreamAttributes request_attributes;
  request_attributes.append(QStringLiteral("maximumResponses"), QString::number(query.maximum_responses()));
  request_attributes.append(QStringLiteral("requestID"), query.request_id());
  request_attributes.append(QStringLiteral("version"), QStringLiteral("1.2"));
  request_attributes.append(QStringLiteral("methodName"), QStringLiteral("ReverseGeocodeRequest"));
  stream.writeAttributes(request_attributes);

  stream.writeStartElement(QStringLiteral("ReverseGeocodeRequest"));
  // stream.writeAttribute(QStringLiteral("returnFreeForm"), QStringLiteral("false"));
  stream.writeTextElement(QStringLiteral("ReverseGeocodePreference"), QStringLiteral("StreetAddress"));
  stream.writeStartElement(QStringLiteral("Position"));
  stream.writeStartElement(QStringLiteral("gml:Point"));
  const QcWgsCoordinate & coordinate = query.coordinate();
  QString coordinate_string = QString::number(coordinate.latitude()) + ' ' + QString::number(coordinate.longitude());
  stream.writeTextElement(QStringLiteral("gml:pos"), coordinate_string);
  stream.writeEndElement();
  if (query.radius()) {
    stream.writeStartElement(QStringLiteral("gml:CircleByCenterPoint"));
    stream.writeTextElement(QStringLiteral("gml:pos"), coordinate_string);
    stream.writeTextElement(QStringLiteral("gml:radius"), QString::number(query.radius()));
  stream.writeEndElement();
  }
  stream.writeEndElement();
  stream.writeEndElement();

  stream.writeEndElement();
  stream.writeEndDocument();

  // http://wxs.ign.fr/<API_KEY>/geoportail/ols?
  QUrl url = QStringLiteral("https://wxs.ign.fr/") +
    m_license.api_key() +
    QStringLiteral("/geoportail/ols?");

  QNetworkReply * reply = post(url, xml_request);

  return QSharedPointer<QcLocationServiceReverseReply>(new QcGeoportailLocationServiceReverseReply(reply, query));
}

QSharedPointer<QcElevationServiceReply>
QcGeoportailPlugin::coordinate_elevations(const QVector<QcWgsCoordinate> & coordinates)
{
  QStringList longitudes;
  QStringList latitudes;
  for (const auto & coordinate : coordinates) {
    longitudes << QString::number(coordinate.longitude());
    latitudes  << QString::number(coordinate.latitude());
  }

  // https://wxs.ign.fr/<API_KEY>/alti/rest/elevation.json?lon=0.2367|2.1570|4.3907&lat=48.0551|46.6077|43.91
  // https://wxs.ign.fr/<API_KEY>/alti/rest/elevationLine.json?sampling=10&lon=0.2367|2.1570|4.3907&lat=48.0551|46.6077|43.91

  // ==========================================================
  // WARNING: USE GEOPORTAIL KEY FOR TEST PURPOSE ONLY
  // QString api_key = m_license.api_key();
  QString api_key = QStringLiteral("j5tcdln4ya4xggpdu4j0f0cn");
  // ==========================================================

  QUrl url = QStringLiteral("https://wxs.ign.fr/") +
    api_key +
    QStringLiteral("/alti/rest/elevation.json?") +
    QStringLiteral("lon=") + longitudes.join(QString('|')) +
    QStringLiteral("&lat=") + latitudes.join(QString('|'))
    ;
  // qQCInfo() << url;

  QNetworkReply * reply = get(url);

  return QSharedPointer<QcElevationServiceReply>(new QcGeoportailElevationServiceReply(reply, coordinates));
}

/**************************************************************************************************/

// #include "geoportail_plugin.moc"
