//
// Created by arthur on 25/05/22.
//

#include <iostream>
#include <version>
#include <stdexcept>
//#include <source_location>

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
        * @param message The message to Log
        */
        template<typename T>
        static void Info(const T& message)
        {
			Log(message, LoggingLevel::INFO);
        }
        /**
        * @brief Log a message with the DEBUG level = DEBUG
        * @param message The message to Log
        */
        template<typename T>
        static void Debug(const T& message/*, const std::source_location& location = std::source_location::current()*/)
        {
			Log(message, LoggingLevel::DEBUG/*, location*/);
        }
        /**
        * @brief Log a message with the DEBUG level = WARNING
        * @param message The message to Log
        */
        template<typename T>
        static void Warning(const T& message)
        {
			Log(message, LoggingLevel::WARNING);
        }
        /**
        * @brief Log a message with the DEBUG level = ERROR
        * @param message The message to Log
        */
        template<typename T>
        static void Error(const T& message)
        {
			Log(message, LoggingLevel::ERROR);
			throw std::runtime_error(message);
        }
        /**
        * @brief Log a message
        * @param level The level of the message
        * @param message The message to Log
        * @param location The location of the message
        */
        template<typename T>
        static void Log(const T& message, LoggingLevel level/*, const std::source_location& location = std::experimental::source_location::current()*/)
        {
            switch (level)
            {
                case LoggingLevel::DEBUG:
                    std::cout << Terminal::Color::CYAN << "[D] "/* << location.function_name() << ":" << location.line()  */<< " message: " << message << Terminal::Color::DEFAULT << std::endl;
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