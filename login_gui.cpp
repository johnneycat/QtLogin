/*********************************************************************
*                           登陆界面模块主文件
*                       (c)copyright 2014,jdh
*                         All Right Reserved
*新建日期:2014/1/29 by jdh
*修改日期:2014/2/1 by jdh
*修改日期:2014/2/17 by jdh
*修改日期:2014/2/18 by jdh
*修改日期:2014/2/16 by jdh
*修改日期:2014/5/4 by jdh
*修改日期:2014/5/5 by jdh
*修改日期:2014/5/13 by jdh
**********************************************************************/

/*********************************************************************
*                           头文件
**********************************************************************/

#include "login_gui.h"



Login_Gui::Login_Gui()
{
    qDebug("--------");
    qDebug(QObject::metaObject()->className());
    qDebug("--------");    //初始化变量
    Login_Counter = 0;

    //滴答初始化
    timer = new QTimer(this);
    //绑定信号槽
    connect(timer, SIGNAL (timeout()), this , SLOT(slot_tick()));

    QFile file_cfg("cfg.txt");
    QByteArray arr;
    bool ok;
    int flag_remember = 0;
    int flag_auto_login = 0;
    int id = 0;
    int password = 0;
    QString str;
    int i = 0;
    int j = 0;

    //属性初始化
    _user_id = "";
    _password = "";
    _flag_remember = false;
    _flag_auto = false;

    //判断文件是否存在
    if (!file_cfg.exists())
    {
        file_cfg.close();
    }
    else
    {
        //文件存在
        file_cfg.open(QIODevice::ReadOnly);
        //读取文件
        do
        {
            str.clear();
            arr = file_cfg.readLine();
            for (i = 0;i < arr.count();i++)
            {
                if ((arr.at(i) >= '0' && arr.at(i) <= '9') || \
                    (arr.at(i) >= 'a' && arr.at(i) <= 'f') || \
                     arr.at(i) == 'x')
                {
                    str[j++] = arr.at(i);
                }
            }
            flag_remember = str.toInt(&ok,16);
            if (!ok)
            {
                break;
            }

            str.clear();
            arr = file_cfg.readLine();
            for (i = 0;i < arr.count();i++)
            {
                if ((arr.at(i) >= '0' && arr.at(i) <= '9') || \
                    (arr.at(i) >= 'a' && arr.at(i) <= 'f') || \
                     arr.at(i) == 'x')
                {
                    str[j++] = arr.at(i);
                }
            }
            flag_auto_login = str.toInt(&ok,16);
            if (!ok)
            {
                break;
            }

            str.clear();
            arr = file_cfg.readLine();
            for (i = 0;i < arr.count();i++)
            {
                if ((arr.at(i) >= '0' && arr.at(i) <= '9') || \
                    (arr.at(i) >= 'a' && arr.at(i) <= 'f') || \
                     arr.at(i) == 'x')
                {
                    str[j++] = arr.at(i);
                }
            }
            id = str.toInt(&ok,16);
            if (!ok)
            {
                break;
            }

            str.clear();
            arr = file_cfg.readLine();
            for (i = 0;i < arr.count();i++)
            {
                if ((arr.at(i) >= '0' && arr.at(i) <= '9') || \
                    (arr.at(i) >= 'a' && arr.at(i) <= 'f') || \
                     arr.at(i) == 'x')
                {
                    str[j++] = arr.at(i);
                }
            }
            password = str.toInt(&ok,16);
            if (!ok)
            {
                break;
            }

            //判断是否记住密码
            if (flag_remember == VALID_FLAG)
            {
                _user_id = QString::number(id,10);
                _password = QString::number(password,10);
                _flag_remember = true;

                //判断是否自动登录
                if (flag_auto_login == VALID_FLAG)
                {
                    _flag_auto = true;
                    slot_login_req();
                }
            }
        } while (0);



file_cfg.close();
    }
}

/*********************************************************************
*                           解构函数
**********************************************************************/

Login_Gui::~Login_Gui()
{
}

/*********************************************************************
*                           属性读取:用户号
**********************************************************************/

QString Login_Gui::user_id()
{
    return _user_id;
}

/*********************************************************************
*                           属性写入:用户号
**********************************************************************/

void Login_Gui::set_user_id(QString str)
{
    if (_user_id != str)
    {
        _user_id = str;
        emit sig_user_id_changed();
    }
}

/*********************************************************************
*                           属性读取:密码
**********************************************************************/

QString Login_Gui::password()
{
    return _password;
}

/*********************************************************************
*                           属性写入:密码
**********************************************************************/

void Login_Gui::set_password(QString str)
{
    if (_password != str)
    {
        _password = str;
        emit sig_password_changed();
    }
}

/*********************************************************************
*                           属性读取:记住密码标志
**********************************************************************/

bool Login_Gui::flag_remember()
{
    return _flag_remember;
}

/*********************************************************************
*                           属性写入:记住密码标志
**********************************************************************/

void Login_Gui::set_flag_remember(bool flag)
{
    if (_flag_remember != flag)
    {
        _flag_remember = flag;
        emit sig_flag_remember_changed();
    }
}

/*********************************************************************
*                           属性读取:自动登陆标志
**********************************************************************/

bool Login_Gui::flag_auto()
{
    return _flag_auto;
}

/*********************************************************************
*                           属性写入:自动登陆标志
**********************************************************************/

void Login_Gui::set_flag_auto(bool flag)
{
    if (_flag_auto != flag)
    {
        _flag_auto = flag;
        emit sig_flag_auto_changed();
    }
}

/*********************************************************************
*                           槽函数:登陆请求
**********************************************************************/

void Login_Gui::slot_login_req()
{
    //初始化计数器
    Login_Counter = 0;
    //开始尝试登陆
    timer->start(INTERVAL_LOGIN);
    slot_tick();
}

/*********************************************************************
*                           槽函数:登陆响应
*参数:data:接收的数据
**********************************************************************/

void Login_Gui::slot_login_ack(QByteArray data)
{
    /*
    uint32_t id = 0;
    uint32_t password = 0;
    int flag_remember = 0;
    int flag_auto_login = 0;
    uint8_t result = 0;
    bool ok;

#ifdef DEBUG
    qDebug() << "接收帧:尝试登陆" << (uint8_t)data[0] << (uint8_t)data[1] << (uint8_t)data[2];
#endif

    //清除计数器
    Login_Counter = 0;
    //停止登录尝试
    timer->stop();

    //判断用户号和密码是否匹配
    id = ((uint8_t)data[6] << 24) +\
         ((uint8_t)data[7] << 16) + \
         ((uint8_t)data[8] << 8) + \
          (uint8_t)data[9];
    password = ((uint8_t)data[10] << 24) +\
               ((uint8_t)data[11] << 16) + \
               ((uint8_t)data[12] << 8) + \
                (uint8_t)data[13];
    //登陆结果
    result = (uint8_t)data[LEN_FRAME_HEAD];
    //判断登陆结果
    switch (result)
    {
        //登陆成功
    case 0:
        {
            //判断用户名和密码是否正确
            if (id == (uint32_t)_user_id.toInt(&ok) && password == (uint32_t)_password.toInt(&ok))
            {
                //发送登陆成功信号
                emit sig_login_result(0);

            #ifdef DEBUG
                qDebug() << "登陆成功" << "用户号" << _user_id << "密码" << _password;
            #endif

                //判断是否勾选记住密码以及自动登录
                if (_flag_remember)
                {
                    flag_remember = VALID_FLAG;
                }
                if (_flag_auto)
                {
                    flag_auto_login = VALID_FLAG;
                }

                //将用户名密码保存
                QFile file_cfg("cfg.txt");
                file_cfg.open(QIODevice::WriteOnly);
                QTextStream out(&file_cfg);
                out << QString::number(flag_remember,16) << "\r\n" \
                    << QString::number(flag_auto_login,16) << "\r\n" \
                    << _user_id << "\r\n" \
                    << _password << "\r\n";
                file_cfg.close();
            }

            break;
        }
        //无此用户名
    case 1:
        {
        #ifdef DEBUG
            qDebug() << "登陆失败" << "用户号不存在";
        #endif

            //发送登录失败信号
            emit sig_login_result(1);

            break;
        }
        //密码错误
    case 2:
        {
        #ifdef DEBUG
            qDebug() << "登陆失败" << "密码错误";
        #endif

            //发送登录失败信号
            emit sig_login_result(2);

            break;
        }
    }
    */
}

/*********************************************************************
*                           槽函数:心跳滴答函数
*说明:1滴答触发1次
**********************************************************************/

void Login_Gui::slot_tick()
{
    /*
    QByteArray frame;
    bool ok;

    //登录计数器
    Login_Counter++;
    if (Login_Counter > NUM_LOGIN)
    {
    #ifdef DEBUG
        qDebug() << "登录失败" << "达到最大尝试登陆次数:" << NUM_LOGIN;
    #endif

        //清除计数器
        Login_Counter = 0;

        //停止登陆尝试
        timer->stop();
        //发送登陆失败信号
        emit sig_login_result(3);

        return;
    }

    //发送登陆请求
    //报文
    frame.clear();
    //发送网络帧
#ifdef DEBUG
    qDebug() << "发送帧:发送登陆请求";
#endif
    emit sig_net_tx_frame_with_id((uint32_t)_user_id.toInt(&ok),(uint32_t)_password.toInt(&ok),\
                                  CMD_USER_LOGIN_REQUEST,0,frame);
   */
}
