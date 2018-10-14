#include "multisendconfigdialog.h"
#include "ui_multisendconfigdialog.h"
#include "addressbookpage.h"
#include "addresstablemodel.h"
#include "base58.h"
#include "init.h"
#include "walletmodel.h"
#include "qvalidatedlineedit.h"
#include "qtmaterialflatbutton.h"

#include <QFrame>
#include <QString>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QDoubleSpinBox>
#include <QClipboard>
#include <QMessageBox>
#include <algorithm>



using namespace std;
using namespace boost;

MultiSendConfigDialog::MultiSendConfigDialog(QWidget* parent, std::string addy) : QDialog(parent),
																address(addy),
																ui(new Ui::MultiSendConfigDialog),
																model(0)
{
    ui->setupUi(this);
	unsigned int indexOfEntry = pwalletMain->indexOfMSAddress(address);
	for (unsigned int i = 0; i < pwalletMain->vMultiSend[indexOfEntry].second.size(); i++) {
		loadEntry(pwalletMain->vMultiSend[indexOfEntry].second[i]);
	}
    updateStatus();
}

MultiSendConfigDialog::~MultiSendConfigDialog()
{
    delete ui;
}

void MultiSendConfigDialog::setModel(WalletModel* model)
{
    this->model = model;
}

void MultiSendConfigDialog::updateStatus()
{   

}

void MultiSendConfigDialog::loadEntry(std::pair<std::string, int> entry)
{
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	QFrame* addressFrame = new QFrame();
	sizePolicy.setHeightForWidth(addressFrame->sizePolicy().hasHeightForWidth());
	addressFrame->setSizePolicy(sizePolicy);
	addressFrame->setFrameShape(QFrame::StyledPanel);
	addressFrame->setFrameShadow(QFrame::Raised);
	addressFrame->setObjectName(QStringLiteral("addressFrame"));

	QVBoxLayout* frameLayout = new QVBoxLayout(addressFrame);
	frameLayout->setSpacing(2);
	frameLayout->setObjectName(QStringLiteral("frameLayout"));
	frameLayout->setContentsMargins(6, 6, 6, 6);

	QHBoxLayout* addressLayout = new QHBoxLayout();
	addressLayout->setSpacing(4);
	addressLayout->setObjectName(QStringLiteral("addressLayout"));

	QValidatedLineEdit* addressLine = new QValidatedLineEdit(addressFrame);
	addressLine->setObjectName(QStringLiteral("addressLine"));
	addressLine->setText(QString::fromStdString(entry.first));
	addressLayout->addWidget(addressLine);

	QDoubleSpinBox* percentageSpinBox = new QDoubleSpinBox(addressFrame);
	percentageSpinBox->setObjectName(QStringLiteral("percentageSpinBox"));
	percentageSpinBox->setDecimals(1);
	percentageSpinBox->setRange(0.1,100);
	percentageSpinBox->setSuffix("%");
	percentageSpinBox->setValue(entry.second);
	addressLayout->addWidget(percentageSpinBox);

	QtMaterialFlatButton* sendingAddressButton = new QtMaterialFlatButton(addressFrame);
	sendingAddressButton->setObjectName(QStringLiteral("sendingAddressButton"));
	QIcon icon1;
	icon1.addFile(QStringLiteral(":/icons/address-book"), QSize(), QIcon::Normal, QIcon::Off);
	sendingAddressButton->setIcon(icon1);
	sendingAddressButton->setAutoDefault(false);
	connect(sendingAddressButton, SIGNAL(clicked()), this, SLOT(selectSendingAddress()));
	addressLayout->addWidget(sendingAddressButton);

	QtMaterialFlatButton* pasteButton = new QtMaterialFlatButton(addressFrame);
	pasteButton->setObjectName(QStringLiteral("pasteButton"));
	QIcon icon2;
	icon2.addFile(QStringLiteral(":/icons/editpaste"), QSize(), QIcon::Normal, QIcon::Off);
	pasteButton->setIcon(icon2);
	pasteButton->setAutoDefault(false);
	connect(pasteButton, SIGNAL(clicked()), this, SLOT(pasteText()));
	addressLayout->addWidget(pasteButton);

	QtMaterialFlatButton* addressDeleteButton = new QtMaterialFlatButton(addressFrame);
	addressDeleteButton->setObjectName(QStringLiteral("addressDeleteButton"));
	QIcon icon3;
	icon3.addFile(QStringLiteral(":/icons/remove"), QSize(), QIcon::Normal, QIcon::Off);
	addressDeleteButton->setIcon(icon3);
	addressDeleteButton->setAutoDefault(false);
	connect(addressDeleteButton, SIGNAL(clicked()), this, SLOT(deleteFrame()));
	addressLayout->addWidget(addressDeleteButton);

	frameLayout->addLayout(addressLayout);
	ui->addressList->addWidget(addressFrame);
}

void MultiSendConfigDialog::on_addEntryButton_clicked()
{
	if (model) {
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		QFrame* addressFrame = new QFrame();
		sizePolicy.setHeightForWidth(addressFrame->sizePolicy().hasHeightForWidth());
		addressFrame->setSizePolicy(sizePolicy);
		addressFrame->setFrameShape(QFrame::StyledPanel);
		addressFrame->setFrameShadow(QFrame::Raised);
		addressFrame->setObjectName(QStringLiteral("addressFrame"));

		QVBoxLayout* frameLayout = new QVBoxLayout(addressFrame);
		frameLayout->setSpacing(2);
		frameLayout->setObjectName(QStringLiteral("frameLayout"));
		frameLayout->setContentsMargins(6, 6, 6, 6);

		QHBoxLayout* addressLayout = new QHBoxLayout();
		addressLayout->setSpacing(4);
		addressLayout->setObjectName(QStringLiteral("addressLayout"));

		QValidatedLineEdit* addressLine = new QValidatedLineEdit(addressFrame);
		addressLine->setObjectName(QStringLiteral("addressLine"));
		addressLayout->addWidget(addressLine);

		QDoubleSpinBox* percentageSpinBox = new QDoubleSpinBox(addressFrame);
		percentageSpinBox->setObjectName(QStringLiteral("percentageSpinBox"));
		percentageSpinBox->setDecimals(1);
		percentageSpinBox->setRange(0.1, 100);
		percentageSpinBox->setSuffix("%");
		addressLayout->addWidget(percentageSpinBox);

		QtMaterialFlatButton* sendingAddressButton = new QtMaterialFlatButton(addressFrame);
		sendingAddressButton->setObjectName(QStringLiteral("sendingAddressButton"));
		QIcon icon1;
		icon1.addFile(QStringLiteral(":/icons/address-book"), QSize(), QIcon::Normal, QIcon::Off);
		sendingAddressButton->setIcon(icon1);
		sendingAddressButton->setAutoDefault(false);
		connect(sendingAddressButton, SIGNAL(clicked()), this, SLOT(selectSendingAddress()));
		addressLayout->addWidget(sendingAddressButton);

		QtMaterialFlatButton* pasteButton = new QtMaterialFlatButton(addressFrame);
		pasteButton->setObjectName(QStringLiteral("pasteButton"));
		QIcon icon2;
		icon2.addFile(QStringLiteral(":/icons/editpaste"), QSize(), QIcon::Normal, QIcon::Off);
		pasteButton->setIcon(icon2);
		pasteButton->setAutoDefault(false);
		connect(pasteButton, SIGNAL(clicked()), this, SLOT(pasteText()));
		addressLayout->addWidget(pasteButton);			

		QtMaterialFlatButton* addressDeleteButton = new QtMaterialFlatButton(addressFrame);
		addressDeleteButton->setObjectName(QStringLiteral("addressDeleteButton"));
		QIcon icon3;
		icon3.addFile(QStringLiteral(":/icons/remove"), QSize(), QIcon::Normal, QIcon::Off);
		addressDeleteButton->setIcon(icon3);
		addressDeleteButton->setAutoDefault(false);
		connect(addressDeleteButton, SIGNAL(clicked()), this, SLOT(deleteFrame()));
		addressLayout->addWidget(addressDeleteButton);

		frameLayout->addLayout(addressLayout);
		ui->addressList->addWidget(addressFrame);
}
}

void MultiSendConfigDialog::selectSendingAddress()
{	
		QWidget* addressButton = qobject_cast<QWidget*>(sender());
		if (!addressButton)return;

		QFrame* addressFrame = qobject_cast<QFrame*>(addressButton->parentWidget());
		if (!addressFrame)return;

		QValidatedLineEdit* vle = addressFrame->findChild<QValidatedLineEdit*>("addressLine");
		if (!vle)return;

		if (model && model->getAddressTableModel()) {
			AddressBookPage dlg(AddressBookPage::ForSelection, AddressBookPage::SendingTab, this);
			dlg.setModel(model->getAddressTableModel());
			if (dlg.exec()) {
				vle->setText(dlg.getReturnValue());
			}
		}	
}

void MultiSendConfigDialog::pasteText()
{
	QWidget* pasteButton = qobject_cast<QWidget*>(sender());
	if (!pasteButton)return;

	QFrame* addressFrame = qobject_cast<QFrame*>(pasteButton->parentWidget());
	if (!addressFrame)return;

	QValidatedLineEdit* vle = addressFrame->findChild<QValidatedLineEdit*>("addressLine");
	if (!vle)return;

	vle->setText(QApplication::clipboard()->text());
}


void MultiSendConfigDialog::deleteFrame() {
	
		QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
		if (!buttonWidget)return;

		QFrame* frame = qobject_cast<QFrame*>(buttonWidget->parentWidget());
		if (!frame)return;

		delete frame;
	
}

void MultiSendConfigDialog::on_activateButton_clicked()
{
	if (!pwalletMain->isMSAddressEnabled(address)) {	
			pwalletMain->vDisabledAddresses.erase(std::remove(pwalletMain->vDisabledAddresses.begin(), pwalletMain->vDisabledAddresses.end(), address), pwalletMain->vDisabledAddresses.end());
   }
}

void MultiSendConfigDialog::on_disableButton_clicked()
{
	if (pwalletMain->isMSAddressEnabled(address)) {
		pwalletMain->vDisabledAddresses.push_back(address);
  }
}

void MultiSendConfigDialog::on_saveButton_clicked()
{
	int indexOfEntry = pwalletMain->indexOfMSAddress(address);
	if (indexOfEntry == -1) {
		QMessageBox::warning(this, tr("Address not found"),
			tr("Address does not exist inside MultiSend Vector anymore"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	std::vector <std::pair<std::string, int>> vSending;
	std::pair<std::string, int> pMultiSendAddress;
	int total=0;
	for (unsigned int i = 0; i < ui->addressList->count(); i++) {
		QWidget* addressEntry = ui->addressList->itemAt(i)->widget();
		QValidatedLineEdit* vle = addressEntry->findChild<QValidatedLineEdit*>("addressLine");
		if (CBitcoinAddress(vle->text().toStdString()).IsValid()) {
			QDoubleSpinBox* psb = addressEntry->findChild<QDoubleSpinBox*>("percentageSpinBox");
			total += psb->value();
			if (total > 100) {
				QMessageBox::warning(this, tr("MultiSend"),
					tr("The total percentage set is higher than 100"),
					QMessageBox::Ok, QMessageBox::Ok);
				return;
			}
			pMultiSendAddress = std::make_pair(vle->text().toStdString(), psb->value());
			if (!(std::find(vSending.begin(), vSending.end(), pMultiSendAddress) != vSending.end())) {
				vSending.push_back(pMultiSendAddress);
			}
			else {
				QMessageBox::warning(this, tr("Duplicate Address"),
					tr("One of the entered Addresses is a duplicate"),
					QMessageBox::Ok, QMessageBox::Ok);
				return;
			}	
		}
		else {
			QMessageBox::warning(this, tr("Invalid Address"),
				tr("One of the entered Addresses is invalid"),
				QMessageBox::Ok, QMessageBox::Ok);
			return;
		}		
 }
	pwalletMain->vMultiSend[indexOfEntry].second.clear();
	CWalletDB walletdb(pwalletMain->strWalletFile);
	walletdb.EraseMultiSend(pwalletMain->vMultiSend);
	pwalletMain->vMultiSend[indexOfEntry].second = vSending;
	walletdb.WriteMultiSend(pwalletMain->vMultiSend);	
}