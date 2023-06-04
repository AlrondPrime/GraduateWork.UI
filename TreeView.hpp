#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

#include "pch.h"

class TreeView : public QTreeView{

    Q_OBJECT

public:
    TreeView(QWidget *parent):QTreeView(parent)
    {
        model = new QFileSystemModel(this);
        model->setRootPath(QDir::currentPath());
        setModel(model);
        setExpandsOnDoubleClick(true);
    }

    void mouseDoubleClickEvent(QMouseEvent * event) override
    {
        QModelIndex index = currentIndex();
        QString path;
        if (index.isValid())
            path = model->filePath(index);
        else
            return;
        QFileInfo info(model->fileInfo(index));
        QUrl url("file:" + path);
        if(info.exists() && info.isFile()){
            QDesktopServices::openUrl(url);
        }

        QTreeView::mouseDoubleClickEvent(event);
    }

private:
    QFileSystemModel *model{nullptr};
};

#endif // TREEVIEW_HPP
