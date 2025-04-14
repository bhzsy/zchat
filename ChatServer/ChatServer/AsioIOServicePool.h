#pragma once
#include <vector>
#include <boost/asio.hpp>
#include "Singleton.h"
class AsioIOServicePool :public Singleton<AsioIOServicePool>
{
    friend Singleton<AsioIOServicePool>;
public:
    using IOService = boost::asio::io_context;
    using Work = boost::asio::io_context::work;
    using WorkPtr = std::unique_ptr<Work>;
    ~AsioIOServicePool();
    AsioIOServicePool(const AsioIOServicePool&) = delete; //赋值构造删掉
    AsioIOServicePool& operator=(const AsioIOServicePool&) = delete; //拷贝构造删掉
    boost::asio::io_context& GetIOService();   
    void Stop();
private:
    AsioIOServicePool(std::size_t size = 2/*std::thread::hardware_concurrency()*/); //线程的数量
    std::vector<IOService> _ioServices; //vector存上下文
    std::vector<WorkPtr> _works; //指向work的智能指针
    std::vector<std::thread> _threads; //存线程
    std::size_t     _nextIOService;
};