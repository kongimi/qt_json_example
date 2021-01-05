#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString val;
    QFile file;

    //========================== read json file methode 1===================================
    file.setFileName("/home/pi/sourcecode/test_json/test_trans.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    qDebug() << sett2;

    QJsonArray value = sett2["hose_delivery"].toArray();  // get data in hose_delivery (QJsonValue)
    qDebug() << value;

    QJsonObject item = value[1].toObject();                        // make QJsonValue to Object
    qDebug() << item;

    QJsonValue text1 = item.value(QString("money"));
    qDebug() << text1;
    qDebug() << QString::number(text1.toDouble());

    //============================ write json file =======================================
    file.setFileName("/home/pi/sourcecode/test_json/test_trans2.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    val = file.readAll();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject abc = doc.object();
    qDebug() << abc;

    QJsonArray valuez = abc["HoseDelivery"].toArray();  // get data in hose_delivery (QJsonValue)
    qDebug() << valuez;
    QJsonObject hose_delivery;
    hose_delivery.insert("id",5);
    hose_delivery.insert("hose_num",1);

    valuez.append(hose_delivery);
    qDebug() << valuez;
    abc.insert("HoseDelivery",valuez);

    file.resize(0);
    file.write(QJsonDocument(abc).toJson(QJsonDocument::Indented));
    file.close();   // Close file

    return a.exec();
}

