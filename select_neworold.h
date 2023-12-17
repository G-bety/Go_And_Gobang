#ifndef SELECT_NEWOROLD_H
#define SELECT_NEWOROLD_H

#include <QWidget>

namespace Ui {
class Select_neworold;
}

class Select_neworold : public QWidget
{
    Q_OBJECT

public:
    explicit Select_neworold(QWidget *parent = nullptr);
    ~Select_neworold();
    void closeEvent(QCloseEvent *event) override;
signals:
    void emit_newgamesig();
    void emit_loadoldgamesig();
    void emit_closesig();

private slots:
    void on_newgame_clicked(bool checked);

    void on_load_oldgame_clicked(bool checked);

private:
    Ui::Select_neworold *ui;
};

#endif // SELECT_NEWOROLD_H
