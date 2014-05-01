#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

#include <jsoncpp/json/json.h>

namespace eighttracks {

    /*class RuntimeError : public std::runtime_error {
    public:
        RuntimeError ( const char * reason );
        RuntimeError ( const std::string & reason );
        virtual ~RuntimeError() throw();
    };

    class LogicError : public std::logic_error {
    public:
        LogicError ( const char * reason );
        LogicError ( const std::string & reason );
        virtual ~LogicError() throw();
    };
    
    class ApiRuntimeError : public eighttracks::RuntimeError {
    public:
        ApiRuntimeError ( const Json::Value& status );
    };
    
    class ApiLogicError : public eighttracks::LogicError {
    public:
        ApiLogicError ( const Json::Value& status );
        virtual const char* what() const throw();
        virtual ~ApiLogicError() throw();
    private:
        Json::Value status_code;
        Json::Value notice;
    };*/
    
       
    class ApiRuntimeError : public std::runtime_error {
    public:
        ApiRuntimeError ( const Json::Value& status );
        virtual ~ApiRuntimeError() throw();
        virtual const char* what() const throw();
    private:
        Json::Value status_code;
        Json::Value notices;
    };

    class ApiLogicError : public std::logic_error {
    public:
        ApiLogicError ( const std::string& s );
        virtual ~ApiLogicError() throw();
    };
}

#endif // #ifndef EXCEPTION_HPP
