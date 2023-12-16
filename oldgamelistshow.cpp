#include "oldgamelistshow.h"

OldgameListShow::OldgameListShow(QStringList filenames)
{
    listView = new QListView;
    model = new QStringListModel(filenames);
    listView->setModel(model);
    QObject::connect(listView, &QListView::doubleClicked, [&](const QModelIndex &index) {
        QString fileName = model->data(index).toString();
        listView->hide();
        emit pro_oldgameinfo(fileName);
    });
    listView->show();
}
