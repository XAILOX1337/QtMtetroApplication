#include "mainwindow.h"
#include <QCursor>
#include <QVector>

#include <QMouseEvent>
#include "ui_mainwindow.h"
//хуйня (конструктор класса) ниже создает то что в ней написано при старте приложения
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QVector<int> Stations;
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int px = event->pos().x(), py = event->pos().y();
    qDebug() << "Real pos=" << event->pos();
    ui->label->setText(QString("x = %1").arg(px));
    ui->label_2->setText(QString("y = %1").arg(py));
    ellipse_ = event->pos();
    //int ellipseCoords [2] {px,py};
    Stations.push_back(px);
    Stations.push_back(py);
    qDebug() << "Real pos=" << Stations;
    repaint(); //или update()
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    //рисует кружочки и линии между ними
    if (!ellipse_.isNull()) {
        for (int i = 0; i < Stations.size(); i += 2) {
            painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.setBrush(QColor(0, 100, 100));
            painter.drawEllipse(Stations[i], Stations[i + 1], 20, 20);
            if (i >= 2) {
                painter.setPen(
                    QPen(QColor(0, 100, 100), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
                painter.drawLine(Stations[i - 2] + 10,  //x 1-первой точки
                                 Stations[i - 1] + 10,  //y 1-ой точки
                                 Stations[i] + 10,      //x 2-ой точки
                                 Stations[i + 1] + 10); //y 2-ой точки
            }
        }
    }
    painter.end();
}
MainWindow::~MainWindow(){
    delete ui;
}
