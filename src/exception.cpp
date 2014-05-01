#include "exception.hpp"

namespace eighttracks {

    /*RuntimeError::~RuntimeError() throw()
    {}

    RuntimeError::RuntimeError ( const char * reason )
        : std::runtime_error ( std::string ( reason ) )
    {}

    RuntimeError::RuntimeError ( const std::string & reason )
        : std::runtime_error ( reason )
    {}

    LogicError::~LogicError() throw()
    {}

    LogicError::LogicError ( const char * reason )
        : std::logic_error ( std::string ( reason ) )
    {}

    LogicError::LogicError ( const std::string & reason )
        : std::logic_error ( reason )
    {}
    
    ApiLogicError::ApiLogicError ( const Json::Value& status ) 
        : eighttracks::LogicError ( status.get( "errors", Json::Value( "Unknown API error" ) ).asString() ),
        status_code ( status.get( "status", Json::Value( "Unknown status code" ) ) ),
        notice ( status.get( "notice", Json::Value( "Unknown notice" ) ) )
    {}
    
    const char* ApiLogicError::what() const throw() {
        std::string msg;
        if ( !status_code.isNull() )
            msg = status_code.asString();
        
        msg += ": " + std::string(LogicError::what());
        
        if ( !notice.isNull() )
            msg += " / " + notice.asString();
        
        return msg.c_str();
    }
    
    ApiLogicError::~ApiLogicError() throw() 
    {}*/
    
    ApiRuntimeError::ApiRuntimeError ( const Json::Value& status ) 
        : std::runtime_error ( status.get( "errors", Json::Value( "Unknown API error" ) ).asString() ),
        status_code ( status.get( "status", Json::Value( "Unknown status code" ) ) ),
        notices ( status.get( "notice", Json::Value( "Unknown notice" ) ) )
    {}
    
    ApiRuntimeError::~ApiRuntimeError() throw() 
    {}
   
    const char* ApiRuntimeError::what() const throw() {
        using std::string;
        
        string msg;
        
        if ( !status_code.isNull() )
            msg = status_code.asString();
        
        msg += ": " + string(std::runtime_error::what());
        
        if ( !notices.isNull() )
            msg += " / " + notices.asString();
        
        return msg.c_str();
    }
    
    
    ApiLogicError::ApiLogicError ( const std::string& s ) : 
        std::logic_error( s ) 
    {}
    
    ApiLogicError::~ApiLogicError() throw() 
    {}
}