source = '''
QBitArray 	toBitArray() const
bool 	toBool() const
QByteArray 	toByteArray() const
QChar 	toChar() const
QDate 	toDate() const
QDateTime 	toDateTime() const
double 	toDouble(bool *ok = Q_NULLPTR) const
QEasingCurve 	toEasingCurve() const
float 	toFloat(bool *ok = Q_NULLPTR) const
QHash<QString, QVariant> 	toHash() const
int 	toInt(bool *ok = Q_NULLPTR) const
QJsonArray 	toJsonArray() const
QJsonDocument 	toJsonDocument() const
QJsonObject 	toJsonObject() const
QJsonValue 	toJsonValue() const
QLine 	toLine() const
QLineF 	toLineF() const
QList<QVariant> 	toList() const
QLocale 	toLocale() const
qlonglong 	toLongLong(bool *ok = Q_NULLPTR) const
QMap<QString, QVariant> 	toMap() const
QModelIndex 	toModelIndex() const
QPersistentModelIndex 	toPersistentModelIndex() const
QPoint 	toPoint() const
QPointF 	toPointF() const
qreal 	toReal(bool *ok = Q_NULLPTR) const
QRect 	toRect() const
QRectF 	toRectF() const
QRegExp 	toRegExp() const
QRegularExpression 	toRegularExpression() const
QSize 	toSize() const
QSizeF 	toSizeF() const
QString 	toString() const
QStringList 	toStringList() const
QTime 	toTime() const
uint 	toUInt(bool *ok = Q_NULLPTR) const
qulonglong 	toULongLong(bool *ok = Q_NULLPTR) const
QUrl 	toUrl() const
QUuid 	toUuid() const
'''

template = """
  {} {}(int position = 0) const {{
    return value(position).{}();
  }}"""

for decl in source.split('\n'):
    decl = decl.strip()
    if decl:
        qt_type, method = [x.strip() for x in decl.split('\t')]
        position = method.find('(')
        method = method[:position]
        print(template.format(qt_type, method, method))
