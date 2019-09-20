// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "ChangeLanguageDialog.h"
#include "ui_changelanguagedialog.h"
#include "Settings.h"

namespace WalletGui {

ChangeLanguageDialog::ChangeLanguageDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::ChangeLanguageDialog) {
  m_ui->setupUi(this);
}

ChangeLanguageDialog::~ChangeLanguageDialog() {
}

void ChangeLanguageDialog::initLangList() {
 QString currentlang = Settings::instance().getLanguage();

     int index = 0;

         if(currentlang.compare("en") == 0)
         {
             index = 1;
         }
         else if(currentlang.compare("es") == 0)
         {
             index = 2;
         }

         m_ui->ChangeLangComboBox->setCurrentIndex(index);

}

QString ChangeLanguageDialog::getLang() const {

    QString lang;
     int n = m_ui->ChangeLangComboBox->currentIndex();
         if (n == 1)
         {
             lang = "en";
         }
         else if (n == 2)
         {
             lang = "es";
         }
         else
         {
             lang = "es";
         }
     return lang;
}

}
