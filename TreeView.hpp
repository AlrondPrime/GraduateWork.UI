#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

class TreeView : public QTreeView{

    Q_OBJECT

public:
    TreeView(QWidget *parent):QTreeView(parent)
    {
        model = new QFileSystemModel(this);
        model->setRootPath(workingDir);
        setModel(model);
        setRootIndex(model->index(workingDir));
        setExpandsOnDoubleClick(true);
    }

    void mouseDoubleClickEvent(QMouseEvent * event) override
    {
        QString path {currentPath()};
        QUrl url("file:" + path);
        QDesktopServices::openUrl(url);

        QTreeView::mouseDoubleClickEvent(event);
    }

    QString currentPath()
    {
        QModelIndex index = currentIndex();
        QString path;
        if (index.isValid() && model->fileInfo(index).isFile())
            path = model->filePath(index);

        return path;
    }

private:
    QFileSystemModel *model{nullptr};
    QString workingDir{R"(C:\Users\alrondprime\CLionProjects\GraduateWork\cmake-build-debug)"};
};

#endif // TREEVIEW_HPP
