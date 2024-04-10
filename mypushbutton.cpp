/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: Custom MyPushButton subclass of QPushButton which overides mousePressEvent
 *              to handle both left and right clicks, emitting the standard(left click) and customClickSignal(right click)
 *
 */

#include "mypushbutton.h"

//constructor for MyPushButton
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent) {

}

//override the mousePressEvent
void MyPushButton::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
      //handles left click
      emit clicked(); //emit the standard clicked signal for left click
  } 
  else if (event->button() == Qt::RightButton) {
      //handles right click
      emit customRightClickSignal(); //emit a custom signal for right click
  }
}
