#ifndef ADJUNCTUPLOADER_H
#define ADJUNCTUPLOADER_H

#include <QObject>
#include <QMap>
#include <QtQml>
#include <QQmlEngine>
#include <QJSEngine>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDebug>
#include "adjunctuploadthread.h"

class AdjunctUploader : public QObject
{
    Q_OBJECT
public:
    static AdjunctUploader * getInstance();
    ~AdjunctUploader();

    Q_INVOKABLE void uploadAdjunct(const QString &filePath);
    Q_INVOKABLE void cancelUpload(const QString &filePath);
    Q_INVOKABLE bool isInUploadedList(const QString &filePath);
    Q_INVOKABLE QString getBucketUrl(const QString &filePath);
    Q_INVOKABLE QString getFileNameByPath(const QString &filePath);
    Q_INVOKABLE QString getMimeType(const QString &filePath);
    static QObject * uploaderObj(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:
    void uploadProgress(QString filePath, int progress);//progress: 0 ~ 100
    void uploadFailed(QString filePath, QString message);
    void uploadFinish(QString filePath, QString bucketUrl);

private slots:
    void slotUploadFinish(QString filePath, QString resourceUrl);
    void slotUploadFailed(const QString &filePath);

private:
    explicit AdjunctUploader(QObject *parent = 0);
    void insertToUploadedList(const QString &filePath, const QString &bucketUrl);
    void deleteFromUploadedList(const QString &filePath);

    QJsonObject getJsonObjFromFile();
private:
    static AdjunctUploader * adjunctUploader;
    QMap<QString, AdjunctUploadThread *> threadMap;

    const QString DRAFT_SAVE_PATH = QDir::homePath() + "/.cache/deepin-feedback/draft/";
    const QString UPLOAD_RECORD_FILE = DRAFT_SAVE_PATH + "uploadrecord.json";
};

#endif // ADJUNCTUPLOADER_H
