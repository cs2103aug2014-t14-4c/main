#pragma once
#include <QObject>
#include <QTextEdit>
#include <QCompleter>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QString>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStringList>
#include <QStringListModel>

class TextEdit : public QTextEdit {
	Q_OBJECT

	public:
		TextEdit(QWidget *parent = 0);
		~TextEdit();

		void setCompleter(QCompleter *c);
		QCompleter *completer() const;

	protected:
		void keyPressEvent(QKeyEvent *e);
		void focusInEvent(QFocusEvent *e);

	private slots:
		void insertCompletion(const QString &completion);

	private:
		QString textUnderCursor() const;

	private:
		QCompleter *c;
};