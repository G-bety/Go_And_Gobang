#ifndef OLDGAMELISTSHOW_H
#define OLDGAMELISTSHOW_H
#include <QString>
#include <QListView>
#include <QStringListModel>
#include <QWidget>

class OldgameListShow:public QWidget
{
    Q_OBJECT
public:
    OldgameListShow(QStringList filenames);
private:
    QListView* listView;
    QStringListModel* model;

signals:
    void pro_oldgameinfo(QString);
};

#endif // OLDGAMELISTSHOW_H
