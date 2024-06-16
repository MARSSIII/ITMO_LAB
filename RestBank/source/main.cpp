#include "Rest/RestCurl.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#define log(x) std::cerr << x << std::endl

struct RequaestParameters {
  std::string Vname;
  int Vnom = 1;
  std::string Date;
  std::string DateDate;
  std::string FileName;
} ReqPar;

int main(int argc, char *argv[]) {

  std::string TmpArg;

  for (int i = 1; i < argc; ++i) {
    TmpArg = argv[i];

    if (TmpArg.substr(0, 8) == "--Vname=") {
      ReqPar.Vname = TmpArg.substr(8);
    }

    else if (TmpArg.substr(0, 7) == "--Vnom=") {
      ReqPar.Vnom = std::stoi(TmpArg.substr(7));
    }

    else if (TmpArg.substr(0, 11) == "--DateDate=") {
      ReqPar.DateDate = TmpArg.substr(11);
    }

    else if (TmpArg.substr(0, 7) == "--Date=") {
      ReqPar.Date = TmpArg.substr(7);
    }

    else if (TmpArg.substr(0, 11) == "--FileName=") {
      ReqPar.FileName = TmpArg.substr(11);
    }
  }

  if (ReqPar.Vname.empty()) {
    log("Write --Vname.\n");
    return 1;
  }

  std::string answer;

  Rest RestBank;

  if (!ReqPar.FileName.empty()) {

    std::ofstream File(ReqPar.FileName);

    if (!File.is_open()) {
      log("Error open file.\n");
      return 1;
    }

    if (!ReqPar.DateDate.empty()) {

      try {
        answer = RestBank.ExchangeDateDate(ReqPar.DateDate, ReqPar.Vname,
                                           ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(Exp.Error);
        return 1;
      }

      File << answer;

      std::cout << "Completed!" << std::endl;
    } else if (ReqPar.Date.empty()) {

      time_t Time = time(nullptr);

      tm *CurLocalTime = localtime(&Time);

      std::string Day = CurLocalTime->tm_mday < 10
                            ? std::to_string(CurLocalTime->tm_mday)
                            : "0" + std::to_string(CurLocalTime->tm_mday);

      std::string Month = CurLocalTime->tm_mon + 1 < 10
                              ? std::to_string(CurLocalTime->tm_mon + 1)
                              : "0" + std::to_string(CurLocalTime->tm_mon + 1);

      std::string tmpDate =
          Day + Month + std::to_string(CurLocalTime->tm_year + 1900);

      try {
        answer = RestBank.Exchange(tmpDate, ReqPar.Vname, ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(Exp.Error);
        return 1;
      }

      File << answer;
      std::cout << "Completed!" << std::endl;

    } else {

      try {
        answer = RestBank.Exchange(ReqPar.Date, ReqPar.Vname, ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(Exp.Error);
        return 1;
      }

      File << answer;
      std::cout << "Completed!" << std::endl;
    }
  }

  if (ReqPar.FileName.empty()) {

    if (!ReqPar.DateDate.empty()) {

      try {
        answer = RestBank.ExchangeDateDate(ReqPar.DateDate, ReqPar.Vname,
                                           ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(Exp.Error);
        return 1;
      }

      std::cout << answer << std::endl;

    } else if (ReqPar.Date.empty()) {
      time_t Time = time(nullptr);
      tm *CurLocalTime = localtime(&Time);

      std::string Day = CurLocalTime->tm_mday > 10
                            ? std::to_string(CurLocalTime->tm_mday)
                            : "0" + std::to_string(CurLocalTime->tm_mday);

      std::string Month = CurLocalTime->tm_mon + 1 > 10
                              ? std::to_string(CurLocalTime->tm_mon + 1)
                              : "0" + std::to_string(CurLocalTime->tm_mon + 1);

      std::string tmpDate = Day + "." + Month + "." +
                            std::to_string(CurLocalTime->tm_year + 1900);

      try {
        answer = RestBank.Exchange(tmpDate, ReqPar.Vname, ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(answer);
        return 1;
      }

      std::cout << answer << std::endl;
    } else {

      try {
        answer = RestBank.Exchange(ReqPar.Date, ReqPar.Vname, ReqPar.Vnom);
      } catch (Rest::ExRest &Exp) {
        log(Exp.Error);
        return 1;
      }

      std::cout << answer << std::endl;
    }
  }

  return 0;
}
