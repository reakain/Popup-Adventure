#include "choice.h"

Choice::Choice(const QString &goToName) : mGoToName(goToName)
{
    mButton = QMessageBox::Ok;
}

QString Choice::goToName() const
{
    return mGoToName;
}

QMessageBox::StandardButton Choice::button() const
{
    return mButton;
}

//! [0]
void Choice::read(const QJsonObject &json)
{
    if (json.contains("goto") && json["goto"].isString())
        mGoToName = json["goto"].toString();

    if (json.contains("type") && json["type"].isString()) {
        QMetaEnum metaEnum = QMetaEnum::fromType<QMessageBox::StandardButton>();
        mButton = QMessageBox::StandardButton(metaEnum.keysToValue(json["type"].toString().toStdString().c_str()));
    }
    else mButton = QMessageBox::Ok;

}
//! [0]

//! [1]
void Choice::write(QJsonObject &json) const
{
    json["goto"] = mGoToName;
    json["type"] = mButton;

}

void Choice::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "GoTo:\t" << mGoToName << "\n";

    QTextStream(stdout) << indent << "Type:\t" << mButton << "\n";

}
