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
    QVector<int> Stations;
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
    bool cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
};
/* На всякий случай
class Click
{
public:
    int onClick(int x, int y);
};
*/

#endif // MAINWINDOW_H
