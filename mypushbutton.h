/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: Custom MyPushButton header class of QPushButton which overides mousePressEvent
 *              to handle both left and right clicks, emitting the standard(left click) and customClickSignal(right click)
 *
 */

#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

//defines the MyPushButton class
class MyPushButton : public QPushButton {
    Q_OBJECT

public:
    explicit MyPushButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void customRightClickSignal(); //custom signal
};

#endif
