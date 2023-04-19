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
        //string btnType = json["type"].toString().toStdString();
        QString btnType = json["type"].toString();
        if(btnType == "Yes"){
            mButton = QMessageBox::Yes;
        } else if(btnType == "No"){
            mButton = QMessageBox::No;
        } else if(btnType == "Help"){
            mButton = QMessageBox::Help;
        } else if(btnType == "Close"){
            mButton = QMessageBox::Close;
        } else if(btnType == "Cancel"){
            mButton = QMessageBox::Cancel;
        } else if(btnType == "Ok"){
            mButton = QMessageBox::Ok;
        } else if(btnType == "YesToAll"){
            mButton = QMessageBox::YesToAll;
        } else if(btnType == "NoToAll"){
            mButton = QMessageBox::NoToAll;
        } else if(btnType == "Abort"){
            mButton = QMessageBox::Abort;
        } else if(btnType == "Open"){
            mButton = QMessageBox::Open;
        } else if(btnType == "Save"){
            mButton = QMessageBox::Save;
        } else if(btnType == "Apply"){
            mButton = QMessageBox::Apply;
        } else if(btnType == "Reset"){
            mButton = QMessageBox::Reset;
        } else if(btnType == "Retry"){
            mButton = QMessageBox::Retry;
        } else if(btnType == "Ignore"){
            mButton = QMessageBox::Ignore;
        } else if(btnType == "Discard"){
            mButton = QMessageBox::Discard;
        } else if(btnType == "SaveAll"){
            mButton = QMessageBox::SaveAll;
        } else if(btnType == "RestoreDefaults"){
            mButton = QMessageBox::RestoreDefaults;
        }
            else {
                mButton = QMessageBox::Ok;
            }


        //QMetaEnum metaEnum = QMetaEnum::fromType<QMessageBox::StandardButton>();
        //mButton = QMessageBox::StandardButton(metaEnum.keysToValue(json["type"].toString().toStdString().c_str()));
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
