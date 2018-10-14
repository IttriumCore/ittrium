#ifndef MULTISENDCONFIGDIALOG_H
#define MULTISENDCONFIGDIALOG_H

#include <QDialog>
#include <utility>
#include <vector>

namespace Ui
{
class MultiSendConfigDialog;
}

class WalletModel;
class MultiSendConfigDialog : public QDialog
{
    Q_OBJECT
    void updateStatus();

private:
	Ui::MultiSendConfigDialog* ui;
	WalletModel* model;
	std::string address;

public:
    explicit MultiSendConfigDialog(QWidget* parent, std::string addy);
    ~MultiSendConfigDialog();
    void setModel(WalletModel* model);
	void loadEntry(std::pair<std::string,int> entry);
    
private slots:
	void deleteFrame();
    void on_activateButton_clicked();
    void on_disableButton_clicked();
    void selectSendingAddress();
	void pasteText();
	void on_addEntryButton_clicked();
	void on_saveButton_clicked();
};

#endif // MULTISENDDIALOG_H
