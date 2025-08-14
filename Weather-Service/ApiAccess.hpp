#ifndef APIACCESS_H
#define APIACCESS_H

#include <QProcessEnvironment>
#include <QString>

namespace ApiAccess {
    inline const QString GEOCODE_URL = "http://api.openweathermap.org/geo/1.0/";
    inline const QString WEATHER_URL = "https://api.openweathermap.org/data/2.5/";
    inline const QString UNITS = "metric";

    inline const QString API_KEY = QProcessEnvironment::systemEnvironment().value("API_KEY", "");

    // City & Country(ISO 3166 code) divided by comma
    inline const QString API_CITY_COUNTRY = QProcessEnvironment::systemEnvironment().value("API_CITY_COUNTRY", "");
}

#endif // APIACCESS_H
