#include<QAbstractProxyModel>

class TreeProxy : public QAbstractProxyModel
{
	Q_OBJECT

public:
	TreeProxy(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &) const;

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const
 {
 QModelIndex sourceParent;
 if (parent.isValid())
 sourceParent = mapToSource(parent);
 QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(proxySourceParent);
 while (it.hasNext()) {
 it.next();
 if (it.value()  sourceParent && it.key().row()  row &&
 it.key().column() == column)
 return it.key();
 }
 return QModelIndex();
 }

QModelIndex parent(const QModelIndex &child) const
 {
 QModelIndex mi = proxySourceParent.value(child);
 if (mi.isValid())
 return mapFromSource(mi);
 return QModelIndex();
 }

QModelIndex mapToSource(const QModelIndex &proxyIndex) const
 {
 if (!proxyIndex.isValid())
 return QModelIndex();
 return mapping.key(proxyIndex);
 }

QModelIndex mapFromSource(const QModelIndex &sourceIndex) const
 {
 if (!sourceIndex.isValid())
 return QModelIndex();
 return mapping.value(sourceIndex);
 }

public slots:
 void hideEverythingButA1AndChildren()
 {
 hideThem = !hideThem;
 // Now we set up the proxy <-> source mappings
 emit layoutAboutToBeChanged();
 fixModel();
 emit layoutChanged();
 }

private:
 void fixModel()
 {
 mapping.clear();
 proxySourceParent.clear();
 for (int i=0;i<list.size();i+'') {
 QStandardItem *si = list.at(i);
 if (hideThem) {
 if (!si->text().startsWith("A") || !si->parent())
 continue;
 QModelIndex proxy = createIndex(si->row(), si->column(), si->index().internalPointer());
 mapping.insert(QPersistentModelIndex(si->index()), proxy);
 QModelIndex sourceParent;
 if (si->parent()->parent())
 sourceParent = si->parent()->index();
 proxySourceParent.insert(proxy, sourceParent);
 } else {
 QModelIndex proxy = createIndex(si->row(), si->column(), si->index().internalPointer());
 mapping.insert(QPersistentModelIndex(si->index()), proxy);
 QModelIndex sourceParent;
 if (si->parent())
 sourceParent = si->parent()->index();
 proxySourceParent.insert(proxy, sourceParent);
 }
 }
 }
 QMap<QPersistentModelIndex, QPersistentModelIndex> mapping;
 QMap<QPersistentModelIndex, QPersistentModelIndex> proxySourceParent;
 bool hideThem;
};

