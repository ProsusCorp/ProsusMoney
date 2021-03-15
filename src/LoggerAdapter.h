// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include "Logging/LoggerManager.h"

namespace WalletGui {

class LoggerAdapter {

public:
  static LoggerAdapter& instance();
  void init();
  Logging::LoggerManager& getLoggerManager();

private:
  Logging::LoggerManager m_logManager;

  LoggerAdapter();
  ~LoggerAdapter();
};

}
