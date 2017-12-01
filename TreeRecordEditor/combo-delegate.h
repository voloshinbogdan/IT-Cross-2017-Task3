#include <QStyledItemDelegate>

class ComboDelegate : public QStyledItemDelegate
{
public:
	ComboDelegate(QObject *pParent = 0)

	virtual QWidget *createEditor(
			QWidget *pParent,
			const QStyleOptionViewItem &rcOption,
			const QModelIndex &rcIndex) const;
	virtual void setEditorData(
			QWidget *pEditor,
			const QModelIndex &rcIndex) const;
	virtual void setModelData(
			QWidget *pEditor,
			QAbstractItemModel *pModel,
			const QModelIndex &rcIndex) const;
	virtual void updateEditorGeometry(
			QWidget *pEditor,
			const QStyleOptionViewItem &rcOption,
			const QModelIndex &rcIndex) const;
}; // class ComboDelegate
