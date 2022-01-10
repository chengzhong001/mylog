#ifndef __LOG__
#define __LOG__
#include <string>
#include <stdint.h>
#include <memory>

namespace MyLogger
{
    // 日志时间
    class LogEvent
    {
    public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent();

    private:
        const char *m_file = nullptr; //文件名
        int32_t m_line = 0;           //行号
        unit32_t m_elapse = 0;        //程序启动开始到现在的毫秒数
        uint32_t m_threadId = 0;      //线程id
        uint32_t m_fiberId = 0;       //协程id
        uint64_t m_time;              //时间戳
        std::string m_content;
    };
    class LogLevel
    {
    public:
        enum Level
        {
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
    };

    //日志输出地
    class LogAppender
    {
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender() {}
        void log(LogLevel::Level level, const LogEvent::ptr &event);

    private:
        LogLevel::Level m_level;
    };

    class LogFormater
    {
    public:
        typedef std::shared_ptr<LogFormater> ptr;
        std::string format(LogEvent::ptr event);

    private:
    };

    // 日志器
    class Logger
    {
    public:
        typedef std::shared_ptr<Logger> ptr;

        Logger(const std::string &name = "root");

    private:
        std::string m_name;
        LogAppender::ptr appender;
    };

    class StdoutLogAppender : public LogAppender
    {
    };
    class FileLogAppender : public LogAppender
    {
    };
};

#endif