#include <encrypt.h>
#include <QCryptographicHash>

QString encrypt(const QByteArray password){
    QString crypto_password;
    crypto_password = QString(QCryptographicHash::hash((password),QCryptographicHash::Sha3_512).toHex());
    return crypto_password;
}
