//#ifndef PIEVIEW_H
//#define PIEVIEW_H

//#include <QObject>
//#include <QWidget>
//#include <QAbstractItemView>

//class PieView : public QAbstractItemView
//{
//    Q_OBJECT
//public:
//    explicit PieView(QWidget *parent);
//    void paintEvent(QPaintEvent *event);
//    void setSelectionModel(QItemSelectionModel *selectionModel);
//    QRegion itemRegion(QModelIndex index);
//    QRect visualRect(const QModelIndex &index) const;
//    void scrollTo(const QModelIndex &index,ScrollHint hit = EnsureVisible);
//    QModelIndex indexAt(const QPoint &point) const;

//private:
//    void setSelection(const QRect &rect,QItemSelectionModel::SelectionFlags command);
//    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
//    int horizontalOffset();
//    int verticalOffset();
//    QRegion visualRegionForSelection(const QItemSelection &selection) const;
//    bool isIndexHidden(const QModelIndex &index) const;



//private:
//    QItemSelectionModel *selection;
//    QList<QRegion> RegionList;
//signals:
//public slots:
//};

//#endif // PIEVIEW_H
