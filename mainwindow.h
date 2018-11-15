#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mdichild.h"

class MdiChild;
class QMdiSubWindow;
class QSignalMapper;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateMenus();         //菜单更新
    void on_action_New_triggered();//新建文件菜单
    MdiChild *createMdiChild(); //创建子窗口
    void setActiveSubWindow(QWidget *window); // 设置活动子窗口
    void on_action_open_triggered(); // 打开文件菜单
    void updateWindowMenu(); // 更新窗口菜单

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Undo_triggered();

    void on_action_Cut_triggered();

    void on_action_Redo_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Close_triggered();

    void on_action_CloseAll_triggered();

    void on_action_Tile_triggered();

    void on_action_Cascade_triggered();

    void on_action_Next_triggered();

    void on_action_Previous_triggered();

    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;
    QAction *actionSeparator;       //间隔器
    MdiChild *activeMdiChild();       //活动窗口
    QMdiSubWindow *findMdiChild(const QString &fileName); // 查找子窗口
    QSignalMapper *windowMapper; // 信号映射器
};

#endif // MAINWINDOW_H
