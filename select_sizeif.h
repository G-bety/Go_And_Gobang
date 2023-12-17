#ifndef SELECT_SIZEIF_H
#define SELECT_SIZEIF_H

#include <QWidget>


class Select_sizeIF : public QWidget
{
    Q_OBJECT

public:
    explicit Select_sizeIF(QWidget *parent = nullptr);
    virtual ~Select_sizeIF();
private:
    virtual void setupUi()=0;
public:
    void closeEvent(QCloseEvent *event) override;
signals:
    void emit_sizesig(int size);
    void emit_closesig();
};

#endif // SELECT_SIZEIF_H
