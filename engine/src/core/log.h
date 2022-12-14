
#ifndef ENGINE_SRC_CORE_LOG_H
#define ENGINE_SRC_CORE_LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <mutex>

#ifndef NDEBUG
#define LOG_LEVEL spdlog::level::trace
#else
#define LOG_LEVEL spdlog::level::warn
#endif

namespace impl {
    template<const char *name>
    class Log;

    constexpr const char coreLoggerName[] = "CORE";
    constexpr const char openglLoggerName[] = "OPENGL";
    constexpr const char appLoggerName[] = "APP";
}

typedef impl::Log<impl::coreLoggerName> LogCore;
typedef impl::Log<impl::openglLoggerName> LogOpenGL;
typedef impl::Log<impl::appLoggerName> Log;

namespace impl {

    template<const char *name>
    class Log {
    private:
        static std::shared_ptr<spdlog::logger> getLogger() {
            static std::shared_ptr<spdlog::logger> logger = spdlog::get(name);
            if (!logger) {
                try {
                    logger = spdlog::stdout_color_mt(name);
                    logger->set_pattern("[%H:%M:%S] [t %t] [%^%n %L%$]: %v");
                    logger->set_level(LOG_LEVEL);
                } catch (spdlog::spdlog_ex &ex) {
                    logger = spdlog::get(name);
                }
            }
            assert(logger);
            return logger;
        }

    public:
        Log() = delete;

        template<typename... Args>
        static void trace(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void debug(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void info(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void warning(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void error(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void critical(fmt::format_string<Args...> fmt, Args &&...args) {
            getLogger()->log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
        }
    };
}

#endif //ENGINE_SRC_CORE_LOG_H
