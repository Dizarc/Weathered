#ifndef APIACCESS_H
#define APIACCESS_H

#include <QProcessEnvironment>
#include <QString>

namespace WeatherAPI {
    inline const QString GEOCODE_URL = "http://api.openweathermap.org/geo/1.0/";
    inline const QString WEATHER_URL = "https://api.openweathermap.org/data/2.5/";
    inline const QString UNITS = "metric";

    inline const QString KEY = QProcessEnvironment::systemEnvironment().value("WEATHER_API_KEY", "");

    // City & Country(ISO 3166 code) divided by comma
    inline const QString CITY_COUNTRY = QProcessEnvironment::systemEnvironment().value("WEATHER_API_CITY_COUNTRY", "");
}

namespace ModelAPI {
    inline const QString URL = QProcessEnvironment::systemEnvironment().value("LM_URL", "http://127.0.0.1:8080/v1/chat/completions");
}

namespace NewsAPI {
    inline const QString URL = "https://api.thenewsapi.com/v1/news/";
    inline const QString CATEGORIES = "tech"; // remove if you want all
    inline const QString LANG = "en"; // remove if you want all

    inline const QString KEY = QProcessEnvironment::systemEnvironment().value("NEWS_API_KEY", "");
}

#endif // APIACCESS_H
