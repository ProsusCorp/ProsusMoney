// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QMessageBox>
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
                                                             m_glassFrame(new SendGlassFrame(nullptr)) {
        m_ui->setupUi(this);
        m_glassFrame->setObjectName("m_sendGlassFrame");
    }

    FileDownloadFrame::~FileDownloadFrame() {
        m_transfers.clear();
        m_glassFrame->deleteLater();
    }

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
        auto private_view_key_string = m_ui->m_trackingKey->text().toStdString();
        CryptoNote::AccountKeys keys;
        this->readKeys(m_ui->m_trackingKey->text(), keys);
        auto address = keys.address;

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
        std::unique_ptr<CryptoNote::INode> node(
                new CryptoNote::NodeRpcProxy(
                        NodeAdapter::instance().getDaemonHost(),
                        NodeAdapter::instance().getDaemonPort()));
        auto callback = [&errorPromise](std::error_code e) { errorPromise.set_value(e); };
        node->init(callback);
        auto currency = CryptoNote::CurrencyBuilder(logManager).currency();

        auto addressString = currency.accountAddressAsString(address);

        CryptoNote::AccountPublicAddress publicKeys;
        currency.parseAccountAddressString(
                addressString,
                publicKeys);

        Logging::LoggerRef logger = Logging::LoggerRef(logManager, "FileDownload");
        logger(DEBUGGING) << "Initalizing Wallet with address: " << addressString;

        auto wallet_green = new CryptoNote::WalletGreen(
                dispatcher,
                currency,
                *node,
                logManager,
                1);


        wallet_green->start();

        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        auto path = "/tmp/wallet_" + to_string(uuid) + ".wallet";

        Crypto::Hash private_view_key_hash;
        Common::podFromHex(private_view_key_string, private_view_key_hash);
        Crypto::SecretKey private_view_key = *(struct Crypto::SecretKey *) &private_view_key_hash;
        //auto creationTimestampInt = strtoll(creationTimestamp.c_str(), NULL, 10);
        int creationTimestampInt = 0L;

        wallet_green->initializeWithViewKeyAndTimestamp(
                path,
                "", //password
                private_view_key,
                creationTimestampInt);
        //wallet_green->load("/tmp/wallet_8814561e-e95e-481d-895c-f55f0b1a9ce9.wallet", "");

        wallet_green->doCreateAddress(
                keys.address.spendPublicKey,
                CryptoNote::NULL_SECRET_KEY,
                creationTimestampInt);

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

    /**
     * Reads and parses a tracking key from the UI
     * @param trackingKey
     * @param keys
     */
    void FileDownloadFrame::readKeys(QString trackingKey, CryptoNote::AccountKeys &keys) {
        std::string public_spend_key_string = trackingKey.mid(0, 64).toStdString();
        std::string public_view_key_string = trackingKey.mid(64, 64).toStdString();
        std::string private_spend_key_string = trackingKey.mid(128, 64).toStdString();
        std::string private_view_key_string = trackingKey.mid(192, 64).toStdString();

        Crypto::Hash public_spend_key_hash;
        Crypto::Hash public_view_key_hash;
        Crypto::Hash private_spend_key_hash;
        Crypto::Hash private_view_key_hash;

        size_t size;
        if (!Common::fromHex(public_spend_key_string, &public_spend_key_hash, sizeof(public_spend_key_hash), size) ||
            size != sizeof(public_spend_key_hash)) {
            QMessageBox::warning(this, tr("Key is not valid"), tr("The public spend key you entered is not valid."),
                                 QMessageBox::Ok);
            return;
        } else if (
                !Common::fromHex(public_view_key_string, &public_view_key_hash, sizeof(public_view_key_hash), size) ||
                size != sizeof(public_view_key_hash)) {
            QMessageBox::warning(this, tr("Key is not valid"), tr("The public view key you entered is not valid."),
                                 QMessageBox::Ok);
            return;
        }
        if (!Common::fromHex(private_spend_key_string, &private_spend_key_hash, sizeof(private_spend_key_hash), size) ||
            size != sizeof(private_spend_key_hash)) {
            QMessageBox::warning(this, tr("Key is not valid"), tr("The private spend key you entered is not valid."),
                                 QMessageBox::Ok);
            return;
        }
        if (!Common::fromHex(private_view_key_string, &private_view_key_hash, sizeof(private_view_key_hash), size) ||
            size != sizeof(private_spend_key_hash)) {
            QMessageBox::warning(this, tr("Key is not valid"), tr("The private view key you entered is not valid."),
                                 QMessageBox::Ok);
            return;
        }

        Crypto::PublicKey public_spend_key = *(struct Crypto::PublicKey *) &public_spend_key_hash;
        Crypto::PublicKey public_view_key = *(struct Crypto::PublicKey *) &public_view_key_hash;
        Crypto::SecretKey private_spend_key = *(struct Crypto::SecretKey *) &private_spend_key_hash;
        Crypto::SecretKey private_view_key = *(struct Crypto::SecretKey *) &private_view_key_hash;

        keys.address.spendPublicKey = public_spend_key;
        keys.address.viewPublicKey = public_view_key;
        keys.spendSecretKey = private_spend_key;
        keys.viewSecretKey = private_view_key;
    }

}
