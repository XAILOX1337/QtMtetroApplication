#include "mainwindow.h"
#include <QApplication>
#include <QCursor>
#include <QLineF>
#include <QVector>
#include <math.h>
//
#include <QMouseEvent>
#include "ui_mainwindow.h"
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isEdit(false)
    , permision(true)

{
    ui->setupUi(this);
    connect(ui->EditButton, &QPushButton::clicked, this, &MainWindow::on_EditButton_clicked);
}

QVector<int> RedStations;
void MainWindow::on_EditButton_clicked()
{
    qDebug() << "Button has been pressed";
    isEdit = !isEdit; //
}
QPoint TempPoint;
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();

    if (!isEdit && RedStations.size() >= 6) {
        bool canAddStation = true; // ‘лаг дл€ проверки возможности добавлени€ станции

        for (int i = 0; i <= RedStations.size() - 5; i += 2) {
            QPointF p1(RedStations[RedStations.size() - 2], RedStations[RedStations.size() - 1]);
            QPointF q1(px, py);
            QPointF p2(RedStations[i], RedStations[i + 1]);
            QPointF q2(RedStations[i + 2], RedStations[i + 3]);

            if (areLinesIntersecting(p1, q1, p2, q2)) {
                canAddStation = false; // ≈сли пересекаетс€, устанавливаем флаг в false
                ui->label_3->setText(
                    QString("Paths cross! Please place the station in a different location!"));
                break; // ¬ыходим из цикла, так как уже нашли пересечение
            }
        }

        // ≈сли не было пересечений, добавл€ем новую станцию
        if (canAddStation) {
            repaint();
        }

    } else if (!isEdit && RedStations.size() < 6) {
        TempPoint.setX(px);
        TempPoint.setY(py);
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    } else {
        closestIndex = -1;
        minDistance = 50;

        for (int i = 0; i < RedStations.size(); i += 2) {
            float distance_to_click = sqrt(pow(px - RedStations[i], 2)
                                           + pow(py - RedStations[i + 1], 2));
            qDebug() << "Distance to point:" << distance_to_click;

            if (distance_to_click < minDistance) {
                minDistance = distance_to_click;
                closestIndex = i;
            }
        }

        if (closestIndex != -1) {
            qDebug() << "Nearest point:" << RedStations[closestIndex]
                     << RedStations[closestIndex + 1];
            qDebug() << "min distance:" << minDistance;
        } else {
            qDebug() << "No points in RedStations.";
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();

    if (isEdit && closestIndex != -1) {
        bool canAddStation = true; // ‘лаг дл€ проверки возможности добавлени€ станции
        for (int i = 0; i <= RedStations.size() - 5; i += 2) {
            QPointF p1(RedStations[RedStations.size() - 2] + 10,
                       RedStations[RedStations.size() - 1] + 10);
            QPointF q1(px + 10, py + 10);
            QPointF p2(RedStations[i] + 10, RedStations[i + 1] + 10);
            QPointF q2(RedStations[i + 2] + 10, RedStations[i + 3] + 10);

            if (areLinesIntersecting(p1, q1, p2, q2)) {
                canAddStation = false; // ≈сли пересекаетс€, устанавливаем флаг в false
                ui->label_3->setText(
                    QString("Paths cross! Please place the station in a different location!"));
                break; // ¬ыходим из цикла, так как уже нашли пересечение
            }
        }

        // ≈сли не было пересечений, добавл€ем новую станцию
        if (canAddStation) {
            RedStations[closestIndex] = px;
            RedStations[closestIndex + 1] = py;
            ui->label_3->setText(QString("The station was successfully placed!"));
            repaint();
        }
    } else if (!isEdit) {
        TempPoint.setX(px);
        TempPoint.setY(py);
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    }
    }

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();

    if (!isEdit && RedStations.size() >= 6) {
        bool canAddStation = true; // ‘лаг дл€ проверки возможности добавлени€ станции

        for (int i = 0; i <= RedStations.size() - 5; i += 2) {
            QPointF p1(RedStations[RedStations.size() - 2], RedStations[RedStations.size() - 1]);
            QPointF q1(px, py);
            QPointF p2(RedStations[i], RedStations[i + 1]);
            QPointF q2(RedStations[i + 2], RedStations[i + 3]);

            if (areLinesIntersecting(p1, q1, p2, q2)) {
                canAddStation = false; // ≈сли пересекаетс€, устанавливаем флаг в false
                ui->label_3->setText(
                    QString("Paths cross! Please place the station in a different location!"));
                break; // ¬ыходим из цикла, так как уже нашли пересечение
            }
        }

        // ≈сли не было пересечений, добавл€ем новую станцию
        if (canAddStation) {
            RedStations.push_back(px);
            RedStations.push_back(py);
            ui->label_3->setText(QString("The station was successfully placed!"));
            repaint();
        }

    } else if (!isEdit && RedStations.size() < 6) {
        RedStations.push_back(px);
        RedStations.push_back(py);
        ui->label_3->setText(QString("The station was successfully placed!"));
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    }
}

bool MainWindow::areLinesIntersecting(QPointF p1, QPointF q1, QPointF p2, QPointF q2)
{
    QLineF line1(p1, q1);
    QLineF line2(p2, q2);

    return line1.intersects(line2, nullptr) == QLineF::BoundedIntersection;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (int i = 0; i < RedStations.size(); i += 2) {
        painter.setPen(QPen(QColor(255, 0, 25), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(QColor(255, 0, 25));
        painter.drawEllipse(RedStations[i], RedStations[i + 1], 20, 20);
        if (i >= 2) {
            painter.setPen(QPen(QColor(255, 0, 25), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.drawLine(RedStations[i - 2] + 10,
                             RedStations[i - 1] + 10,
                             RedStations[i] + 10,
                             RedStations[i + 1] + 10);
        }
    }
    if (RedStations.size() >= 2 && isEdit == false) {
        painter.setPen(QPen(QColor(255, 0, 25), 2, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin));
        painter.drawLine(RedStations[RedStations.size() - 2] + 10,
                         RedStations[RedStations.size() - 1] + 10,
                         TempPoint.x() + 10,
                         TempPoint.y() + 10);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
