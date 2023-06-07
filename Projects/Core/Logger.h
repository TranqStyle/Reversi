#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>

namespace {
    char indentationStr('\t');

    std::string indentationAtLevel(size_t level)
    {
        std::ostringstream levelTabsOss;
        for (size_t i = 0; i < level; ++i)
        {
            levelTabsOss << indentationStr;
        }
        return levelTabsOss.str();
    }
}

class Logger
{
public:
    Logger(const std::string& owner = "") :
    _useLevel(s_useLevel),
    _indentation(indentationAtLevel(s_useLevel))
    {
        std::ostringstream owneross;
        owneross << "(@" << owner << ") ";
        _owner = owneross.str();
        
        ++s_useLevel;
    }
    
    ~Logger()
    {
        --s_useLevel;
    }
    
    static void setSilent(bool silent_)
    {
        s_silent = silent_;
    }
    
    static bool getSilent()
    {
        return s_silent;
    }
    
    // ====== Log the start of a unit (titleless units will be logged as "[Empty Unit]") ======
    void logUnitHead() const
    {
        if (! s_silent)
        {
            logUnitHead("[Empty Unit]");
        }
    }

    template<typename ... Arguments>
    void logUnitHead(const Arguments&... arguments) const
    {
        if (! s_silent)
        {
            std::cerr << _indentation << _owner << "====== Start of ";
            logBlock(arguments...);
            std::cerr << " ======" << std::endl;
        }
    }

    // ====== Log the end of a unit (titleless units will be logged as "[Empty Unit]") ======
    void logUnitTail() const
    {
        if (! s_silent)
        {
            logUnitTail("[Empty Unit]");
        }
    }

    template<typename ... Arguments>
    void logUnitTail(const Arguments&... arguments) const
    {
        if (! s_silent)
        {
            std::cerr << _indentation << _owner << "====== End of ";
            logBlock(arguments...);
            std::cerr << " ======" << std::endl;
        }
    }

    // ====== Log a single line (empty lines will be logged as "[Empty line]") ======
    void log() const
    {
        if (! s_silent)
        {
            log("[Empty line]");
        }
    }

    template<typename ... Arguments>
    void log(const Arguments&... arguments) const
    {
        if (! s_silent)
        {
            logBlock(_indentation, _owner, arguments...);
            std::cerr << std::endl;
        }
    }

    // ====== Log a continuous string (without new line) (empty strings will not be logged) ======
    void logBlock() const
    {
    }

    template <typename First, typename ... Rest>
    void logBlock(First arg, const Rest&... rest) const
    {
        if (! s_silent)
        {
            std::cerr << arg;
        }
            
        logBlock(rest...);
    }
    
private:
    static size_t s_useLevel;
    static bool s_silent;
    
    const size_t _useLevel;
    const std::string _indentation;
    
    std::string _owner;
};

#endif // LOGGER_H

