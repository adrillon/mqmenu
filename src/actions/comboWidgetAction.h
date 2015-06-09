#ifndef __COMBOWIDGETACTION_H__
#define __COMBOWIDGETACTION_H__

#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include "myWidgetAction.h"

class comboWidgetAction : public myWidgetAction {
    Q_OBJECT

public:
    comboWidgetAction(QObject* parent);

    virtual void setParameters(QMap<QString, QString>& map);

    virtual void setText(const QString& text);
    virtual void setIcon(const QIcon& icon);

public slots:
    virtual void runCommand();

private:
    QWidget* _mainWidget;
    QHBoxLayout* _layout;
    QLabel* _iconLabel;
    QLabel* _titleLabel;
    QComboBox* _comboBox;

    QStringList _comboValues;
    QStringList _comboTexts;
    QStringList _comboIcons;
};

#endif // __COMBOWIDGETACTION_H__
