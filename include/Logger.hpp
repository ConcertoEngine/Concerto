//
// Created by arthur on 25/05/22.
//

#include <iostream>
#include <version>
#include <experimental/source_location>

namespace Concerto
{
    namespace Terminal::Color {
        static constexpr auto DEFAULT = "\x1B[0m";
        static constexpr auto RED = "\x1B[31m";
        static constexpr auto GREEN = "\x1B[32m";
        static constexpr auto YELLOW = "\x1B[33m";
        static constexpr auto BLUE = "\x1B[34m";
        static constexpr auto MAGENTA = "\x1B[35m";
        static constexpr auto CYAN = "\x1B[36m";
    }
    class Logger
    {
        public:
            enum class LoggingLevel {
                DEBUG,
                INFO,
                WARNING,
                ERROR
            };

        /**
        * @brief Log a message with the DEBUG level = INFO
        * @param message The message to log
        */
        template<typename T>
        static void info(const T& message)
        {
            log(message, LoggingLevel::INFO);
        }
        /**
        * @brief Log a message with the DEBUG level = DEBUG
        * @param message The message to log
        */
        template<typename T>
        static void debug(const T& message, const std::experimental::source_location& location = std::experimental::source_location::current())
        {
            log(message, LoggingLevel::DEBUG, location);
        }
        /**
        * @brief Log a message with the DEBUG level = WARNING
        * @param message The message to log
        */
        template<typename T>
        static void warning(const T& message)
        {
            log(message, LoggingLevel::WARNING);
        }
        /**
        * @brief Log a message with the DEBUG level = ERROR
        * @param message The message to log
        */
        template<typename T>
        static void error(const T& message)
        {
            log(message, LoggingLevel::ERROR);
        }
        /**
        * @brief Log a message
        * @param level The level of the message
        * @param message The message to log
        * @param location The location of the message
        */
        template<typename T>
        static void log(const T& message, LoggingLevel level, const std::experimental::source_location& location = std::experimental::source_location::current())
        {
            switch (level)
            {
                case LoggingLevel::DEBUG:
                    std::cout << Terminal::Color::CYAN << "[D] " << location.function_name() << ":" << location.line()  << " message: " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LoggingLevel::INFO:
                    std::cout << Terminal::Color::GREEN << "[i] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LoggingLevel::WARNING:
                    std::cout << Terminal::Color::YELLOW << "[!] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LoggingLevel::ERROR:
                    std::cerr << Terminal::Color::RED << "[X] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
            }
        }
    };
}