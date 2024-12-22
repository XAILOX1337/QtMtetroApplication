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

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    int getX(int x);
    int getY(int y);
    void Click(int x, int y);
};

/* На всякий случай
class Click
{
public:
    int onClick(int x, int y);
};
*/

#endif // MAINWINDOW_H
