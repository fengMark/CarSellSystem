//#include "pieview.h"
//#include <QPainter>
//PieView::PieView(QWidget *parent):QAbstractItemView(parent)
//{

//}
//void PieView::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(viewport());

//    painter.setPen(Qt::black);
//    unsigned int x0 = 40;
//    unsigned int y0 = 250;
//    painter.drawLine(x0,y0,40,30);
//    painter.drawLine(38,32,40,30);
//    painter.drawLine(40,30,42,32);
//    painter.drawText(20,30,tr("销售数量"));

//    //y坐标轴
//    for(int uLoopi=0;uLoopi<5;uLoopi++)
//    {
//        painter.drawLine(-1,-uLoopi*50,1,-uLoopi*50);
//        painter.drawText(-20,-uLoopi*50,tr("%1").arg(i*5));
//    }
//    //x坐标轴
//    painter.drawLine(x0,y0,540,250);
//    painter.drawLine(538,248,540,250);
//    painter.drawLine(540,250,538,252);
//    painter.drawText(545,250,tr("品牌"));

//    int pos = x0+20;
//    int row;
//    for(row = 0;row<model()->rowCount(rootIndex());row++)
//    {
//        QModelIndex index = model()->index(row,0,rootIndex());
//        QString dep = model()->data(index).toString();
//        painter.drawText(pos,y0+20,dep);
//        pos+=50;
//    }
//    int posN = x0+20;
//    for(row = 0;row<model()->rowCount(rootIndex());row++)
//    {
//        QModelIndex index = model()->index(row,1,rootIndex());
//        int sell = model()->data(index).toDouble();
//        int width = 10;
//        QModelIndex colorIndex = model()->index(row,0,rootIndex());
//        QColor color = QColor(model()->data(colorIndex,Qt::DecorationRole).toString());
//        if(selection->isSelected(index))
//        {
//            painter.setBrush(QBrush(color,Qt::Dense3Pattern));
//        }
//        else
//        {
//            painter.setBrush(QBrush(color));
//        }
//        painter.drawRect(QRect(posN,u0-sell*10,width,sell*10));
//        QRegion regionM(posN,y0-sell*10,width,sell*10);
//        RegionList<<regionM;
//        posN+=50;
//    }
//}


//void PieView::setSelectionModel(QItemSelectionModel *selectionModel)
//{
//    selection = selectionModel;
//}

//QRegion PieView::itemRegion(QModelIndex index)
//{
//    QRegion region;
//    if(index.column()==1)
//    {
//        region = RegionList[index.row()];
//    }
//    return region;
//}

//QRect PieView::visualRect(const QModelIndex &index) const
//{

//}

//void PieView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hit)
//{

//}

//QModelIndex PieView::indexAt(const QPoint &point) const
//{
//    QPoint newPoint(point.x(),point.y());
//    QRegion region;
//    foreach (region, RegionList) {
//        if(region.contains(newPoint))
//        {
//            int row = RegionList.indexOf(region);
//            QModelIndex index = model()->index(row,1,rootIndex());
//            return index;
//        }
//    }
//    return QModelIndex();
//}

//QModelIndex PieView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
//{

//}

//int PieView::horizontalOffset()
//{

//}

//int PieView::verticalOffset()
//{

//}

//bool PieView::isIndexHidden(const QModelIndex &index) const
//{

//}

//void PieView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
//{

//}

//QRegion PieView::visualRegionForSelection(const QItemSelection &selection) const
//{

//}

