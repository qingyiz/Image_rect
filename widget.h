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
    void mousePressEvent(QMouseEvent *event);   /*鼠标按下事件处理函数*/
    void mouseReleaseEvent(QMouseEvent *event); /*鼠标释放事件处理函数*/
    void mouseMoveEvent(QMouseEvent *event);    /*鼠标移动事件处理函数*/
    void paintEvent(QPaintEvent *event);        /*绘制事件处理函数*/

    bool judgeMouseInRect(QMouseEvent *event); /*判断鼠标是否在矩形内*/

private:
    Ui::Widget *ui;
    QPixmap pix;        /*全局变量保存绘制的图片*/
    QPoint lastPoint;   /*保存鼠标上一个值*/
    QPoint endPoint;    /*保存鼠标最后的值*/
    QString filename ;  /*保存选择图片的路径*/
    QPoint movePoint;  /*移动矩形*/

    /*记录坐标值*/
    int rect_x;
    int rect_y;
    int rect_w;
    int rect_h;


};

#endif // WIDGET_H
