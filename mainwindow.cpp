#include <QMdiSubWindow>
#include <QFileDialog>
#include <QSignalMapper>
#include <QMessageBox>

#include "mainwindow.h"
#include "mdichild.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建并设计间隔器
    actionSeparator = new QAction(this);
    actionSeparator->setSeparator(true);
    //更新菜单
    updateMenus();
    //当有活动窗口时更新菜单
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),this, SLOT(updateMenus()));

    windowMapper = new QSignalMapper(this); // 创建信号映射器
    connect(windowMapper, SIGNAL(mapped(QWidget*)), // 映射器重新发射信号
            this, SLOT(setActiveSubWindow(QWidget*))); // 设置活动窗口
    updateWindowMenu();

    // 更新窗口菜单，并且设置当窗口菜单将要显示的时候更新窗口菜单
    connect(ui->menu_W,SIGNAL(aboutToShow()),this,SLOT(updateWindowMenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    //创建MdiChild
    MdiChild *child = createMdiChild();
    //新建文件
    child->newFile();
    //显示子窗口
    child->show();
}

void MainWindow::updateMenus() //更新菜单
{
    bool hasMdiChild = (activeMdiChild() != 0); //是否有活动窗口
    ui->action_Save->setEnabled(hasMdiChild);    //设置各个动作是否可用
    ui->action_SaveAs->setEnabled(hasMdiChild);
    ui->action_Paste->setEnabled(hasMdiChild);
    ui->action_Close->setEnabled(hasMdiChild);
    ui->action_CloseAll->setEnabled(hasMdiChild);
    ui->action_Tile->setEnabled(hasMdiChild);
    ui->action_Cascade->setEnabled(hasMdiChild);
    ui->action_Next->setEnabled(hasMdiChild);
    ui->action_Previous->setEnabled(hasMdiChild);
    actionSeparator->setVisible(hasMdiChild);   //设置间隔器是否显示

    bool hasSelection = (activeMdiChild()
                         && activeMdiChild()->textCursor().hasSelection());

    // 有活动窗口且有被选择的文本，剪切复制才可用
    ui->action_Cut->setEnabled(hasSelection);
    ui->action_Copy->setEnabled(hasSelection);

    // 有活动窗口且文档有撤销操作
    ui->action_Undo->setEnabled(activeMdiChild()
                          && activeMdiChild()->document()->isUndoAvailable());

    // 有活动窗口且文档有恢复操作
    ui->action_Redo->setEnabled(activeMdiChild()
                          && activeMdiChild()->document()->isRedoAvailable());
}

MdiChild * MainWindow::activeMdiChild() //活动窗口
{
    // 如果有活动窗口，则将其内的中心部件转换为MdiChild类型
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0; // 没有活动窗口，直接返回0
}

MdiChild * MainWindow::createMdiChild() //创建子窗口部件
{
    MdiChild *child = new MdiChild; //创建MdiChild部件
    ui->mdiArea->addSubWindow(child); //向多文档区域添加子窗口，child为中心部件
    connect(child,SIGNAL(copy_Available(bool)),ui->action_Cut,
            SLOT(setEnabled(bool)));

    // 根据QTextEdit类的是否可以复制信号设置剪切复制动作是否可用
    connect(child,SIGNAL(copyAvailable(bool)),ui->action_Copy,
            SLOT(setEnabled(bool)));

    // 根据QTextDocument类的是否可以撤销恢复信号设置撤销恢复动作是否可用
    connect(child->document(),SIGNAL(undoAvailable(bool)),
            ui->action_Undo,SLOT(setEnabled(bool)));
    connect(child->document(),SIGNAL(redoAvailable(bool)),
            ui->action_Redo,SLOT(setEnabled(bool)));

    return child;
}

QMdiSubWindow * MainWindow::findMdiChild(const QString &fileName) // 查找子窗口
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    // 利用foreach语句遍历子窗口列表，如果其文件路径和要查找的路径相同，则返回该窗口
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window) // 设置活动子窗口
{
    if (!window) // 如果传递了窗口部件，则将其设置为活动窗口
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}


void MainWindow::on_action_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this); // 获取文件路径
    if (!fileName.isEmpty()) { // 如果路径不为空，则查看该文件是否已经打开
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) { // 如果已经存在，则将对应的子窗口设置为活动窗口
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild *child = createMdiChild(); // 如果没有打开，则新建子窗口
        if (child->loadFile(fileName)) {
            ui->statusBar->showMessage(tr("打开文件成功"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

void MainWindow::updateWindowMenu() // 更新口菜单窗
{
    ui->menu_W->clear(); // 先清空菜单，然后再添加各个菜单动作
    ui->menu_W->addAction(ui->action_Close);
    ui->menu_W->addAction(ui->action_CloseAll);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->action_Tile);
    ui->menu_W->addAction(ui->action_Cascade);
    ui->menu_W->addSeparator();
    ui->menu_W->addAction(ui->action_Next);
    ui->menu_W->addAction(ui->action_Previous);
    ui->menu_W->addAction(actionSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());
    // 如果有活动窗口，则显示间隔器
    for (int i = 0; i < windows.size(); ++i) { // 遍历各个子窗口
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());

        QString text;
        if (i < 9) { // 如果窗口数小于9，则设置编号为快捷键
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = ui->menu_W->addAction(text); // 添加动作到菜单
        action->setCheckable(true); // 设置动作可以选择

        // 设置当前活动窗口动作为选中状态
        action ->setChecked(child == activeMdiChild());

        // 关联动作的触发信号到信号映射器的map()槽函数上，这个函数会发射mapped()信号
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));

        // 将动作与相应的窗口部件进行映射，在发射mapped()信号时就会以这个窗口部件为参数
        windowMapper->setMapping(action, windows.at(i));

    }
}

void MainWindow::on_action_Save_triggered()
{
    if(activeMdiChild() && activeMdiChild()->save())
           ui->statusBar->showMessage(tr("文件保存成功"),2000);
}

void MainWindow::on_action_SaveAs_triggered()
{
    if(activeMdiChild() && activeMdiChild()->saveAs())
            ui->statusBar->showMessage(tr("文件保存成功"),2000);
}

void MainWindow::on_action_Undo_triggered()
{
    if(activeMdiChild()) activeMdiChild()->undo();
}

void MainWindow::on_action_Cut_triggered()
{
    if(activeMdiChild()) activeMdiChild()->cut();
}

void MainWindow::on_action_Redo_triggered()
{
    if(activeMdiChild()) activeMdiChild()->redo();
}

void MainWindow::on_action_Copy_triggered()
{
    if(activeMdiChild()) activeMdiChild()->copy();
}

void MainWindow::on_action_Paste_triggered()
{
     if(activeMdiChild()) activeMdiChild()->paste();
}

void MainWindow::on_action_Close_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_action_CloseAll_triggered()
{
     ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_action_Tile_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_action_Cascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_action_Next_triggered()
{
    ui->mdiArea->activateNextSubWindow();
}

void MainWindow::on_action_Previous_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,tr("本软件的功能..."),tr("我懒得写了= ="));
}
