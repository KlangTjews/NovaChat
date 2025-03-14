#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QList>
#include <QListWidgetItem>
#include <memory>
//#include "statelabel.h"
#include "global.h"
#include "statewidget.h"
#include "userdata.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

protected:
    //void CloseFindDlg();


private:
    void addChatUserList();
    void AddLBGroup(StateWidget* lb);
    void ClearLabelState(StateWidget* lb);

    void ShowSearch(bool bsearch = false);

    Ui::ChatDialog *ui;
    bool _b_loading;
    QList<StateWidget*> _lb_list;

    ChatUIMode _mode;
    ChatUIMode _state;
    QWidget* _last_widget;
    //todo...
    QMap<int, QListWidgetItem*> _chat_items_added;
    int _cur_chat_uid;

public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString & str);

};

#endif // CHATDIALOG_H
