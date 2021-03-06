/*********************************************************************
*                           登陆界面模块头文件
*                       (c)copyright 2014,jdh
*                         All Right Reserved
**********************************************************************/

#ifndef LOGIN_GUI_H
#define LOGIN_GUI_H


//#include "world.h"
#include <QObject>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QTextStream>



//登录间隔 ms

#define INTERVAL_LOGIN          500


//最大登录次数


#define NUM_LOGIN               5

#define VALID_FLAG              0

#define LEN_FRAME_HEAD          0

#define CMD_USER_LOGIN_REQUEST  0




class Login_Gui : public QObject
{
    Q_OBJECT
    //属性:用户名
    Q_PROPERTY(QString user_id READ user_id WRITE set_user_id NOTIFY sig_user_id_changed)
    //属性:密码
    Q_PROPERTY(QString password READ password WRITE set_password NOTIFY sig_password_changed)
    //属性:记住密码标志
    Q_PROPERTY(bool flag_remember READ flag_remember \
               WRITE set_flag_remember NOTIFY sig_flag_remember_changed)
    //属性:自动登录标志
    Q_PROPERTY(bool flag_auto READ flag_auto \
               WRITE set_flag_auto NOTIFY sig_flag_auto_changed)

public:



    Login_Gui();



    ~Login_Gui();


    QString user_id();


    void set_user_id(QString str);


    QString password();



    void set_password(QString str);



    bool flag_remember();


    void set_flag_remember(bool flag);


    bool flag_auto();

    /*********************************************************************
    *                           属性写入:自动登陆标志
    **********************************************************************/

    void set_flag_auto(bool flag);

signals:

    /*********************************************************************
    *                           属性改变信号:用户号
    **********************************************************************/

    void sig_user_id_changed();

    /*********************************************************************
    *                           属性改变信号:密码
    **********************************************************************/

    void sig_password_changed();

    /*********************************************************************
    *                           属性改变信号:记住密码标志
    **********************************************************************/

    void sig_flag_remember_changed();

    /*********************************************************************
    *                           属性改变信号:自动登陆标志
    **********************************************************************/

    void sig_flag_auto_changed();

    /*********************************************************************
    *                           信号:登陆结果
    *参数:result:0:成功
    *           1:无此用户名
    *           2:密码错误
    *           3:达到登陆的最大次数
    **********************************************************************/

    void sig_login_result(int result);

    /*********************************************************************
    *                               发送网络帧
    *参数:id:用户名
    *    password:密码
    *    cmd:帧命令
    *    index:发送序列号
    *    frame:发送的报文
    **********************************************************************/

    void sig_net_tx_frame_with_id(uint32_t id,uint32_t password,int cmd,uint16_t index,QByteArray frame);

public slots:

    /*********************************************************************
    *                           槽函数:登陆请求
    **********************************************************************/

    void slot_login_req();

    /*********************************************************************
    *                           槽函数:登陆响应
    *参数:data:接收的数据
    **********************************************************************/

    void slot_login_ack(QByteArray data);

private slots:

    /*********************************************************************
    *                           槽函数:心跳滴答函数
    *说明:1滴答触发1次
    **********************************************************************/

    void slot_tick();

private:

    /*********************************************************************
    *                           变量
    **********************************************************************/

    /*********************************************************************
    *                           属性:用户号
    **********************************************************************/

    QString _user_id;

    /*********************************************************************
    *                           属性:密码
    **********************************************************************/

    QString _password;

    /*********************************************************************
    *                           属性:记住密码标志
    **********************************************************************/

    bool _flag_remember;

    /*********************************************************************
    *                           属性:自动登录标志
    **********************************************************************/

    bool _flag_auto;

    /*********************************************************************
    *                           滴答定时器
    **********************************************************************/

    QTimer *timer;

    /*********************************************************************
    *                           登录计数器
    **********************************************************************/

    int Login_Counter;
};

#endif // LOGIN_GUI_H
