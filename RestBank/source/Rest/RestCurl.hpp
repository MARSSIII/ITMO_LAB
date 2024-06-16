#pragma once

#include <curl/curl.h>
#include <string>

class Rest {
public:
  std::string Exchange(const std::string &Date, const std::string &CurCode,
                       int Vnom);
  std::string ExchangeDateDate(const std::string &Date,
                               const std::string &CurCode, int Vnom);

  struct ExRest {
    std::string Error;

    explicit ExRest(std::string Error) : Error(Error) {}
  };

private:
  CURL *curl;
  CURLcode res;

  std::string URL = "http://cbr.ru/scripts/XML_daily.asp?date_req=";
  std::string URLDate = "http://www.cbr.ru/scripts/XML_dynamic.asp?date_req1=";

  std::string m_SearchNumberID(const std::string &Date,
                               const std::string &currencyCode);

  static size_t m_Fun(char *p, size_t s, size_t n, std::string *d);
};
