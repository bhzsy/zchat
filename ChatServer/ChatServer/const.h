#pragma once;
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "Singleton.h"
#include <map>
#include <queue>
#include <unordered_map>
#include <functional>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "hiredis.h"
#include <chrono>
#include <assert.h>
#include "data.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    VarifyExpired = 1003, //验证码过期
    VarifyCodeErr = 1004, //验证码错误
    UserExist = 1005,       //用户已经存在
    PasswdErr = 1006,    //密码错误
    EmailNotMatch = 1007,  //邮箱不匹配
    PasswdUpFailed = 1008,  //更新密码失败
    PasswdInvalid = 1009,   //密码更新失败
    TokenInvalid = 1010,   //Token失效
    UidInvalid = 1011,  //uid无效
};
class ConfigMgr;
extern ConfigMgr gcfgMgr;

#define MAX_LENGTH  1024*2
//ͷ���ܳ���
#define HEAD_TOTAL_LEN 4
//ͷ��id����
#define HEAD_ID_LEN 2
//ͷ�����ݳ���
#define HEAD_DATA_LEN 2
#define MAX_RECVQUE  10000
#define MAX_SENDQUE 1000


enum MSG_IDS {
    MSG_CHAT_LOGIN = 1005, //�û���½
    MSG_CHAT_LOGIN_RSP = 1006, //�û���½�ذ�
    ID_SEARCH_USER_REQ = 1007, //�û���������
    ID_SEARCH_USER_RSP = 1008, //�����û��ذ�
    ID_ADD_FRIEND_REQ = 1009, //�������Ӻ�������
    ID_ADD_FRIEND_RSP = 1010, //�������Ӻ��ѻظ�
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //֪ͨ�û����Ӻ�������
    ID_AUTH_FRIEND_REQ = 1013,  //��֤��������
    ID_AUTH_FRIEND_RSP = 1014,  //��֤���ѻظ�
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //֪ͨ�û���֤��������
    ID_TEXT_CHAT_MSG_REQ = 1017, //�ı�������Ϣ����
    ID_TEXT_CHAT_MSG_RSP = 1018, //�ı�������Ϣ�ظ�
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //֪ͨ�û��ı�������Ϣ
};
class Defer {
public:
    // 接受一个lambda表达式或者函数指针
    Defer(std::function<void()> func) : func_(func) {}

    // 析构函数中执行传入的函数
    ~Defer() {
        func_();
    }

private:
    std::function<void()> func_;
};
#define USERIPPREFIX  "uip_"
#define USERTOKENPREFIX  "utoken_"
#define IPCOUNTPREFIX  "ipcount_"
#define USER_BASE_INFO "ubaseinfo_"
#define LOGIN_COUNT  "logincount"
#define NAME_INFO  "nameinfo_"