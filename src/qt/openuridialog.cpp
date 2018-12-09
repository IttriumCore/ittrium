// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Ittrium developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "openuridialog.h"
#include "ui_openuridialog.h"
#include "qtmaterialflatbutton.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

OpenURIDialog::OpenURIDialog(QWidget* parent) : QDialog(parent),
                                                ui(new Ui::OpenURIDialog)
{
    ui->setupUi(this);
    ui->uriEdit->setPlaceholderText("ittrium:");
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::on_acceptButton_clicked()
{
    SendCoinsRecipient rcp;
    if (GUIUtil::parseBitcoinURI(getURI(), &rcp)) {
        /* Only accept value URIs */
        QDialog::accept();
    } else {
        ui->uriEdit->setValid(false);
    }
}

void OpenURIDialog::on_cancelButton_clicked() {
	this->close();
}

void OpenURIDialog::on_selectFileButton_clicked()
{
    QString filename = GUIUtil::getOpenFileName(this, tr("Select payment request file to open"), "", "", NULL);
    if (filename.isEmpty())
        return;
    QUrl fileUri = QUrl::fromLocalFile(filename);
    ui->uriEdit->setText("ittrium:?r=" + QUrl::toPercentEncoding(fileUri.toString()));
}
