#include "RestCurl.hpp"
#include <algorithm>

size_t Rest::m_Fun(char *p, size_t s, size_t n, std::string *d) {
  d->append(p, s * n);
  return s * n;
}

std::string Rest::Exchange(const std::string &Date, const std::string &CurCode,
                           int Vnom) {
  std::string AnswerServer;
  std::string result;

  std::string nURL = URL + Date;

  // инициализация, а затем генерация curl
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  // проверка, что curl создана
  if (!curl) {
    throw ExRest("Error curl in Exchange");
  }

  // установка параметров объекта curl

  // установка параметра URL
  curl_easy_setopt(curl, CURLOPT_URL, nURL.c_str());

  // установка параметра обратного вызова
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_Fun);

  // установка записи
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &AnswerServer);

  // делает запрос и возвращает результат своей работы в типе CURLcode
  res = curl_easy_perform(curl);

  // чистим выделенную память, закрываем дескриптор curl
  curl_easy_cleanup(curl);

  // глобальная очистка библиотеки
  curl_global_cleanup();

  if (res != CURLE_OK) {
    throw ExRest("Error : " + std::string(curl_easy_strerror(res)));
  }

  size_t posRes = AnswerServer.find("<CharCode>" + CurCode + "</CharCode>");

  if (posRes == std::string::npos) {
    throw ExRest("Currency not found");
  }

  size_t posValue = AnswerServer.find("<Value>", posRes);
  size_t endValue = AnswerServer.find("</Value>", posValue);
  std::string valueStr =
      AnswerServer.substr(posValue + 7, endValue - posValue - 7);

  std::replace(valueStr.begin(), valueStr.end(), ',', '.');
  float exchangeValue = std::stof(valueStr);

  std::string tmpValue = std::to_string(exchangeValue * Vnom);

  std::string firstStr;
  std::string secondStr;

  bool flag = false;
  for (char el : tmpValue) {

    if (!flag) {

      if (el == '.') {
        flag = true;
      } else {
        firstStr += el;
      }
    } else {
      secondStr += el;
    }
  }

  result = CurCode + " " + std::to_string(Vnom) + " " + Date + " " +
           std::to_string(std::stoi(firstStr)) + " " +
           std::to_string(std::stoi(secondStr)) + '\n';

  return result;
}

std::string Rest::m_SearchNumberID(const std::string &Date,
                                   const std::string &CurCode) {
  std::string nURL = URL + Date;

  std::string AnswerServer;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (!curl) {
    throw ExRest("Error curl in searchNumber");
  }

  curl_easy_setopt(curl, CURLOPT_URL, nURL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_Fun);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &AnswerServer);

  res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  if (res != CURLE_OK) {
    throw ExRest("Error : " + std::string(curl_easy_strerror(res)));
  }

  std::string SearchString = "<CharCode>" + CurCode + "</CharCode>";

  size_t posCur = AnswerServer.find(SearchString);

  if (posCur == std::string::npos) {
    throw ExRest("Code not found");
  }

  size_t StartPos = AnswerServer.rfind('<', posCur);

  StartPos = AnswerServer.rfind('<', StartPos - 1);

  StartPos = AnswerServer.find('"', StartPos);

  size_t endPos = AnswerServer.find('"', StartPos + 1);

  std::string numberID =
      AnswerServer.substr(StartPos + 1, endPos - StartPos - 1);

  return numberID;
}

std::string Rest::ExchangeDateDate(const std::string &Date,
                                   const std::string &CurCode, int Vnom) {
  std::string AnswerServer;

  size_t posDate = Date.find('-');
  if (posDate == std::string::npos) {
    throw ExRest("Write Correct format pls");
  }

  std::string firDate = Date.substr(0, posDate);
  std::string secDate = Date.substr(posDate + 1);

  std::string numberID;

  try {
    numberID = m_SearchNumberID(firDate, CurCode);
  } catch (ExRest &exeption) {
    throw ExRest(exeption.Error);
  }

  std::string nURL =
      URLDate + firDate + "&date_req2=" + secDate + "&VAL_NM_RQ=" + numberID;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (!curl) {
    throw ExRest("Error curl in DateDate");
  }

  curl_easy_setopt(curl, CURLOPT_URL, nURL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_Fun);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &AnswerServer);
  res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  if (res != CURLE_OK) {
    throw ExRest("Error : " + std::string(curl_easy_strerror(res)));
  }

  std::string result;
  size_t start = 0;

  while ((start = AnswerServer.find("Date=", start)) != std::string::npos) {
    std::string curDate = AnswerServer.substr(start + 6, 10);

    size_t valueStart = AnswerServer.find("<Value>", start);
    size_t valueEnd = AnswerServer.find("</Value>", valueStart);
    std::string value =
        AnswerServer.substr(valueStart + 7, valueEnd - valueStart - 7);

    std::replace(value.begin(), value.end(), ',', '.');
    float exchangeValue = std::stof(value);

    std::string tmpValue = std::to_string(exchangeValue * Vnom);

    std::string firstStr;
    std::string secondStr;

    bool flag = false;
    for (char el : tmpValue) {

      if (!flag) {

        if (el == '.') {
          flag = true;
        } else {
          firstStr += el;
        }
      } else {
        secondStr += el;
      }
    }

    result += CurCode + " " + std::to_string(Vnom) + " " + curDate + " " +
              std::to_string(std::stoi(firstStr)) + " " +
              std::to_string(std::stoi(secondStr)) + "\n";
    start = valueEnd;
  }

  return result;
}
