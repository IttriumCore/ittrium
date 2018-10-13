#ifndef MULTISENDDIALOG_H
#define MULTISENDDIALOG_H

#include <QDialog>

namespace Ui
{
class MultiSendDialog;
}

class WalletModel;
class MultiSendDialog : public QDialog
{
    Q_OBJECT
    void updateStatus();
	void updateCheckBoxes();	

private:
	Ui::MultiSendDialog* ui;
	WalletModel* model;

public:
    explicit MultiSendDialog(QWidget* parent = 0);
    ~MultiSendDialog();
    void setModel(WalletModel* model);
    
private slots:
	void addAddress(std::string address, bool onLoad);
	void deleteFrame();
    void on_activateButton_clicked();
    void on_disableButton_clicked();
    void on_addressBookButton_clicked();
	void configureMultiSend();


};

#endif // MULTISENDDIALOG_H
