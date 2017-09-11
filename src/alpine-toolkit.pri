# -*- mode: qmake -*-

####################################################################################################

HEADERS += \
  src/bleaudb/bleau_schema.h \
  src/bleaudb/bleau_schema_manager.h \
  src/bleaudb/bleau_sqlite_database.h

HEADERS += \
  src/checksum/checksum.h

HEADERS += \
  src/camptocamp/camptocamp_api_cache.h \
  src/camptocamp/camptocamp_client.h \
  src/camptocamp/camptocamp_document.h \
  src/camptocamp/camptocamp_login.h \
  src/camptocamp/camptocamp_login_data.h \
  src/camptocamp/camptocamp_media_cache.h \
  src/camptocamp/camptocamp_qml.h \
  src/camptocamp/camptocamp_search_settings.h

HEADERS += \
  src/document/document.h \
  src/document/document_database.h

HEADERS += \
  src/ephemeride/ephemeride.h

HEADERS += \
  src/full_text_search/phonetic_encoder.h \
  src/full_text_search/stemmer.h \
  src/full_text_search/text_document.h \
  src/full_text_search/token.h \
  src/full_text_search/tokenizer.h

HEADERS += \
  src/international_morse_code_engine/international_morse_code_engine.h

HEADERS += \
  src/network/network_downloader.h \
  src/network/network_reply.h \
  src/network/network_request.h \
  src/network/network_request_manager.h

HEADERS += \
  src/orm/database.h \
  src/orm/database_connection.h \
  src/orm/database_query.h \
  src/orm/database_schema.h \
  src/orm/database_table.h \
  src/orm/json_adaptator.h \
  src/orm/network_database.h \
  src/orm/schema.h \
  src/orm/schema_manager.h \
  src/orm/sql_query_model.h \
  src/orm/sqlite_database.h \
  src/orm/type_conversion.h

HEADERS += \
  src/platform_abstraction/platform_abstraction.h

HEADERS += \
  src/refuge/refuge_schema.h \
  src/refuge/refuge_schema_manager.h \
  src/refuge/refuge_sqlite_database.h

HEADERS += \
  src/rrd/rrd.h

HEADERS += \
  src/settings/settings_database.h \
  src/settings/settings_tree.h

HEADERS += \
  src/third_party_license/third_party_license_schema.h \
  src/third_party_license/third_party_license_schema_manager.h \
  src/third_party_license/third_party_license_sqlite_database.h

####################################################################################################

#document/document_manager.cpp
SOURCES += \
  src/checksum/checksum.cpp

SOURCES += \
  src/bleaudb/bleau_schema.cpp \
  src/bleaudb/bleau_schema_manager.cpp \
  src/bleaudb/bleau_sqlite_database.cpp

SOURCES += \
  src/camptocamp/camptocamp_api_cache.cpp \
  src/camptocamp/camptocamp_client.cpp \
  src/camptocamp/camptocamp_document.cpp \
  src/camptocamp/camptocamp_login.cpp \
  src/camptocamp/camptocamp_login_data.cpp \
  src/camptocamp/camptocamp_media_cache.cpp \
  src/camptocamp/camptocamp_qml.cpp \
  src/camptocamp/camptocamp_search_settings.cpp

SOURCES += \
  src/document/document.cpp \
  src/document/document_database.cpp

SOURCES += \
  src/ephemeride/ephemeride.cpp

SOURCES += \
  src/full_text_search/phonetic_encoder.cpp \
  src/full_text_search/stemmer.cpp \
  src/full_text_search/text_document.cpp \
  src/full_text_search/token.cpp \
  src/full_text_search/tokenizer.cpp

SOURCES += \
  src/international_morse_code_engine/international_morse_code_engine.cpp

SOURCES += \
  src/network/network_downloader.cpp \
  src/network/network_reply.cpp \
  src/network/network_request.cpp \
  src/network/network_request_manager.cpp

SOURCES += \
  src/orm/database.cpp \
  src/orm/database_connection.cpp \
  src/orm/database_query.cpp \
  src/orm/database_schema.cpp \
  src/orm/database_table.cpp \
  src/orm/json_adaptator.cpp \
  src/orm/network_database.cpp \
  src/orm/schema.cpp \
  src/orm/schema_manager.cpp \
  src/orm/sql_query_model.cpp \
  src/orm/sqlite_database.cpp \
  src/orm/type_conversion.cpp

SOURCES += \
  src/platform_abstraction/platform_abstraction.cpp

SOURCES += \
  src/refuge/refuge_schema.cpp \
  src/refuge/refuge_schema_custom_code.cpp \
  src/refuge/refuge_schema_manager.cpp \
  src/refuge/refuge_sqlite_database.cpp

SOURCES += \
  src/rrd/rrd.cpp \

SOURCES += \
  src/settings/settings_database.cpp \
  src/settings/settings_tree.cpp

SOURCES += \
  src/third_party_license/third_party_license_schema.cpp \
  src/third_party_license/third_party_license_schema_manager.cpp \
  src/third_party_license/third_party_license_sqlite_database.cpp
