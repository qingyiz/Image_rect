#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_closeButton_clicked();

    void on_minsizeButton_clicked();


protected:
    void mousePressEvent(QMouseEvent *event);   /*��갴���¼�������*/
    void mouseReleaseEvent(QMouseEvent *event); /*����ͷ��¼�������*/
    void mouseMoveEvent(QMouseEvent *event);    /*����ƶ��¼�������*/
    void paintEvent(QPaintEvent *event);        /*�����¼�������*/

    bool judgeMouseInRect(QMouseEvent *event); /*�ж�����Ƿ��ھ�����*/

private:
    Ui::Widget *ui;
    QPixmap pix;        /*ȫ�ֱ���������Ƶ�ͼƬ*/
    QPoint lastPoint;   /*���������һ��ֵ*/
    QPoint endPoint;    /*�����������ֵ*/
    QString filename ;  /*����ѡ��ͼƬ��·��*/
    QPoint movePoint;  /*�ƶ�����*/

    /*��¼����ֵ*/
    int rect_x;
    int rect_y;
    int rect_w;
    int rect_h;


};

#endif // WIDGET_H
