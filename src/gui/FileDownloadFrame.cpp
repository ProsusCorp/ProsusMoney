// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "AddressBookModel.h"
#include "CurrencyAdapter.h"
#include "NodeAdapter.h"
#include "FileDownloadFrame.h"
#include "TransferFrame.h"
#include "WalletAdapter.h"
#include "WalletEvents.h"
#include <QRegExpValidator>
#include <QUrlQuery>
#include "ui_filedownloadframe.h"
#include "Settings.h"
#include "AddressProvider.h"
#include "OpenUriDialog.h"
#include <Logging/LoggerManager.h>
#include "Common/PathTools.h"
#include <Logging/LoggerRef.h>
#include <System/Dispatcher.h>
#include "NodeRpcProxy/NodeRpcProxy.h"
#include "Wallet/WalletGreen.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <Common/StringTools.h>
#include <CryptoNoteCore/CryptoNoteBasicImpl.h>

using namespace Logging;
using Common::JsonValue;

namespace WalletGui {

    FileDownloadFrame::FileDownloadFrame(QWidget *_parent) : QFrame(_parent), m_ui(new Ui::FileDownloadFrame),
                                                             m_addressProvider(new AddressProvider(this)),
                                                             m_glassFrame(new SendGlassFrame(nullptr)) {
        m_ui->setupUi(this);
        m_glassFrame->setObjectName("m_sendGlassFrame");
        remote_node_fee = 0;

//  connect(&WalletAdapter::instance(), &WalletAdapter::walletSynchronizationProgressUpdatedSignal,
//    this, &FileDownloadFrame::walletSynchronizationInProgress, Qt::QueuedConnection);

//  QRegExp hexMatcher("^[0-9A-F]{64}$", Qt::CaseInsensitive);
//  QValidator *validator = new QRegExpValidator(hexMatcher, this);
//  m_ui->m_paymentIdEdit->setValidator(validator);

    }

    FileDownloadFrame::~FileDownloadFrame() {
        m_transfers.clear();
        m_glassFrame->deleteLater();
    }

//void FileDownloadFrame::walletSynchronizationInProgress(quint64 _current, quint64 _total) {
//  m_glassFrame->install(this);
//  m_glassFrame->updateSynchronizationState(_current, _total);
//}
    JsonValue buildLoggerConfiguration(Level level, const std::string &logfile) {
        JsonValue loggerConfiguration(JsonValue::OBJECT);
        loggerConfiguration.insert("globalLevel", static_cast<int64_t>(level));

        JsonValue &cfgLoggers = loggerConfiguration.insert("loggers", JsonValue::ARRAY);

        JsonValue &consoleLogger = cfgLoggers.pushBack(JsonValue::OBJECT);
        consoleLogger.insert("type", "console");
        consoleLogger.insert("level", static_cast<int64_t>(TRACE));
        consoleLogger.insert("pattern", "%D %T %L ");

        JsonValue &fileLogger = cfgLoggers.pushBack(JsonValue::OBJECT);
        fileLogger.insert("type", "file");
        fileLogger.insert("filename", logfile);
        fileLogger.insert("level", static_cast<int64_t>(TRACE));

        return loggerConfiguration;
    }

    void FileDownloadFrame::downloadClicked() {
        auto private_view_key_string = m_ui->m_viewKey->text().toStdString();
        auto address = m_ui->m_address->text().toStdString();
        auto creationTimestamp = m_ui->m_timestamp->text().toStdString();

        LoggerManager logManager;
        Logging::ILogger &m_loggerGroup(logManager);

        Logging::Level logLevel = Logging::DEBUGGING;
        auto modulePath = Common::NativePathToGeneric("");
        auto cfgLogFile = Common::NativePathToGeneric("");
        if (cfgLogFile.empty()) {
            cfgLogFile = Common::ReplaceExtenstion(modulePath, ".log");
        } else {
            if (!Common::HasParentPath(cfgLogFile)) {
                cfgLogFile = Common::CombinePath(Common::GetPathDirectory(modulePath), cfgLogFile);
            }
        }
        logManager.configure(buildLoggerConfiguration(logLevel, cfgLogFile));

        System::Dispatcher dispatcher;

        auto log = new Logging::LoggerGroup(DEBUGGING);
        log->addLogger(logManager);

        std::promise<std::error_code> errorPromise;
        std::future<std::error_code> f_error = errorPromise.get_future();
        //std::unique_ptr<CryptoNote::INode> node(new CryptoNote::NodeRpcProxy("seed01.prosus.money", 16181));
        std::unique_ptr<CryptoNote::INode> node(new CryptoNote::NodeRpcProxy("localhost", 16181));
        auto callback = [&errorPromise](std::error_code e) { errorPromise.set_value(e); };
        node->init(callback);
        auto currency = CryptoNote::CurrencyBuilder(logManager).currency();

        CryptoNote::AccountPublicAddress publicKeys;
        currency.parseAccountAddressString(address, publicKeys);

        auto wallet_green = new CryptoNote::WalletGreen(dispatcher, currency, *node, logManager, 1);
        wallet_green->start();

        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        auto path = "/tmp/wallet_" + to_string(uuid) + ".wallet";

        Crypto::Hash private_view_key_hash;
        Common::podFromHex(private_view_key_string, private_view_key_hash);
        Crypto::SecretKey private_view_key  = *(struct Crypto::SecretKey*) &private_view_key_hash;
        auto creationTimestampInt = strtoll(creationTimestamp.c_str(), NULL, 10);

        wallet_green->initializeWithViewKeyAndTimestamp(
                path,
                "", //password
                private_view_key,
                creationTimestampInt
                );

        wallet_green->doCreateAddress(publicKeys.spendPublicKey, CryptoNote::NULL_SECRET_KEY, creationTimestampInt);

        std::cout << "Address: " << address << std::endl;

        for (;;) {
            wallet_green->save();

            auto txCount = wallet_green->getTransactionCount();
            std::cout << "TX Count: " << txCount << std::endl;

            auto balance = wallet_green->getActualBalance();
            std::cout << "Balance: " << balance << std::endl;

            auto event = wallet_green->getEvent();
            std::cout << "Received event: " << event.type << std::endl;
        }
    }

}
