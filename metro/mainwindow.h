#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>

#include <QMainWindow>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    QPoint ellipse_;
    QVector<int> RedStations;
    bool isEdit;
    bool permision;
    float minDistance = INFINITY;
    int closestIndex = -1;

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    void on_EditButton_clicked();
    bool areLinesIntersecting(QPointF p1, QPointF q1, QPointF p2, QPointF q2);
};

#endif // MAINWINDOW_H
