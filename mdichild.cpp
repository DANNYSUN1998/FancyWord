#include "mdichild.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QString>
#include <QApplication>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>

MdiChild::MdiChild(QWidget *parent)
{
    //设置在子窗口关闭时销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);

    //初始isUtitled 为true
    isUntitled = true;
}

void MdiChild::newFile()
{
    //设置窗口编号
    static int seqNum = 1;

    //新建文档的状态：未被保存
    isUntitled = true;

    //将新建文档命名为“未命名文档+编号”
    curFile = tr("未命名文档%1.txt").arg(seqNum++);

    //设置窗口标题
    setWindowTitle(curFile + "[*]"+tr("-多文档编辑器"));

    //如果文件被更改，会显示【*】
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}

void MdiChild::documentWasModified()
{
    setWindowModified(document()->isModified());
}

bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);

    //只读方式打开
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("多人文档编辑器"),
                             tr("无法读取文件 %1:\n %2.").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    //设置鼠标事件状态为等待
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //读取文件全部文本内容，添加到编辑器里
    setPlainText(in.readAll());
    //恢复鼠标状态
    QApplication::restoreOverrideCursor();
    //设置当前文件
    setCurrentFile(fileName);
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    return true;
}

void MdiChild::setCurrentFile(const QString &fileName)
{
    /* 将加载文件的路径保存到curFile中， 并进行一些状态设置 */

    //去除路径中的符号连接
    curFile = QFileInfo(fileName).canonicalFilePath();

    isUntitled = false;
    document()->setModified(false);
    //窗口不显示被更改标志
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile()+ "[ * ]");
}

QString MdiChild::userFriendlyCurrentFile()
{
    /* 从文件路径中提取文件名 */
    return QFileInfo(curFile).fileName();
}

bool MdiChild::save()
{
    //如果保存过，另存为，否则保存
    if (isUntitled){
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"),curFile);
    //判断文件路径是否为空
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, tr("多文档编辑器"),tr("无法写入文件 %1:\n%2.").
                             arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out (&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //以纯文本写入
    out << toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    //判断关闭前是否已经保存，让用户做出选择
    if(maybeSave())
        event->accept();
    else
        event->ignore();
}

bool MdiChild::maybeSave()
{
    //如果文档被更改过
    if (document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(tr("多文档编辑器"));
        box.setText(tr("是否保存对“%1”的更改？").arg(userFriendlyCurrentFile()));
        box.setIcon(QMessageBox::Warning);

        QPushButton *yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("取消"), QMessageBox::RejectRole);

        //弹出对话框，让用户选择是否保存修改，或取消关闭
        box.exec();
        if(box.clickedButton() == yesBtn)
            return save();
        else if (box.clickedButton() == cancelBtn)
            return false;
    }

    //若文档没有被更改过
    return true;
}
