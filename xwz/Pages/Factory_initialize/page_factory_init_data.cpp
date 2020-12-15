#include "page_factory_init_data.h"

#include <QDebug>
#include <QFile>
#include <unistd.h>

Page_factory_init_data::
Page_factory_init_data(QObject *parent):QObject(parent)
{
}

Page_factory_init_data::
~Page_factory_init_data()
{
}


void Page_factory_init_data::
confirm_init_clicked()
{
    int ret = replace_file( QString("setting.json"),QString("setting_def.json"));
    if ( ret < 0 ){
        emit initialze_failed();
    }
    emit initialze_success();
}

int Page_factory_init_data::
replace_file( QString _des_file_name, QString _src_file_name)
{
    // 生成目标文件名，目标文件和中间文件对象
    QFile src_file(_src_file_name);
    QFile des_file(_des_file_name);

    // 备份文件，如果已经存在备份文件，则先删除该备份
    QString _des_file_name_temp = QString(_des_file_name)+".temp";

    QFile temp_file( _des_file_name_temp );
    if ( temp_file.exists() ){
        temp_file.remove();
        sync();
    }

    QFileDevice::Permissions des_file_permission;
    // 如果已经存在同名文件，则首先提取权限
    if ( des_file.exists() ){
        des_file_permission = QFile::permissions( _des_file_name );
        // 待替换文件备份为temp文件
        if ( ! des_file.copy( _des_file_name_temp ) ){
            /// 生成备份文件失败
            return -1;
        }
        // 删除准备替换的目标文件
        des_file.remove();
        sync();
        // 新文件复制出待替换文件
        if ( ! src_file.copy( _des_file_name ) ){
            ///新文件复制待替换文件失败
            if ( ! temp_file.copy( _des_file_name ) ){
                ///还原待替换文件
                return -1;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }
}
