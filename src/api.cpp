#include <sstream>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "api.hpp"
#include "exception.hpp"

using std::string;
using std::list;
using std::map;
using std::pair;
using std::ostringstream;

namespace eighttracks {
    API::API() :
        apikey ( "43dd5bc5854281df4c8d21fa0853726841feab3a" ),
        version ( "3" ),
        base_url ( "https://8tracks.com/" ),
        play_token ( "" ) {

        curlpp::initialize();
        list<string> headers;
        headers.push_back ( string ( "X-Api-Version: " ) + version );
        headers.push_back ( string ( "X-Api-Key: " ) + apikey );
        handle.setOpt ( curlpp::Options::HttpHeader ( headers ) );
    }

    API::~API() {
        curlpp::terminate();
    }

    MixSet API::play_mix ( const string& mix_id ) {
        return playback_control ( "play", mix_id );
    }
    
    MixSet API::next_track ( const string& mix_id ) {
        return playback_control ( "next", mix_id );
    }

    MixSet API::skip_track ( const string& mix_id ) {
        return playback_control( "skip", mix_id );
    }
    
    void API::report_track ( const string& mix_id, const string& track_id ) {
        string play_token = obtain_play_token();

        string request = "/sets/" + play_token + "/report.json";
        curlParams params;
        add_param ( params, "mix_id", mix_id );
        get ( request, params );
    }


    string API::params_string ( const curlParams& params ) {
        if ( params.empty() )
            return "";

        curlParams::const_iterator pb = params.begin();
        curlParams::const_iterator pe = params.end();

        string data = "?" + pb->first + "=" + pb->second;
        pb++;
        if ( pb == pe )
            return data;

        for ( ; pb != pe; pb++ )
            data += "&" + pb->first + "=" + pb->second;

        return data;
    }

    void API::add_param ( curlParams& params, const string& key, const string& value ) {
        params.insert ( pair<string,string> ( key, value ) );
    }


    void API::get ( const string& request ) {
        curlParams p;
        get ( request, p );
    }

    void API::get ( const string& request, const curlParams& params ) {
        ostringstream os;
        string url;
        url = base_url + request + params_string ( params );

        curlpp::Options::WriteStream ws ( &os );
        handle.setOpt ( ws );
        handle.setOpt ( curlpp::Options::Url ( url ) );
        handle.perform();
        
        string reply = os.str();
        bool parseok = reader.parse( reply, root );
        if ( !parseok ) {
            throw ApiRuntimeError( reader.getFormatedErrorMessages() );
        }
        
        switch ( response_status( root["status"] ) ) {
            case OK:
                break;
            default:
                throw ApiRuntimeError( root );
        }
    }

    std::string API::obtain_play_token() {
        if ( play_token.empty() ) {
            get ( "sets/new.json" );
            play_token = root["play_token"].asString();
        }

        return play_token;
    }

    MixSet API::playback_control ( const string& command, const string& mix_id ) {
        MixSet mixset;
        mixset.mix_id = mix_id;

        string play_token = obtain_play_token();

        string request = "/sets/" + play_token + "/" + command + ".json";
        curlParams params;
        add_param ( params, "mix_id", mix_id );
        get ( request, params );

        mixset.at_beginning = root["set"]["at_beginning"].asBool();
        mixset.at_end = root["set"]["at_end"].asBool();
        mixset.at_last_track = root["set"]["at_last_track"].asBool();
        mixset.skip_allowed = root["set"]["skip_allowed"].asBool();
        mixset.track.track_id = root["set"]["track"]["id"].asInt();
        mixset.track.name = root["set"]["track"]["name"].asString();
        mixset.track.performer = root["set"]["track"]["performer"].asString();
        mixset.track.release_name = root["set"]["track"]["release_name"].asString();
        mixset.track.track_file_stream_url = root["set"]["track"]["track_file_stream_url"].asString();
        mixset.track.url = root["set"]["track"]["url"].asString();

        return mixset;
    }
    
    status_t API::response_status ( const Json::Value& status ) {
        string s = status.asString();
        
        if ( s == "200 OK" )
            return OK;
        else if ( s == "301 Moved Permanently" )
            return MOVED_PERMANENTLY;
        else if ( s == "302 Moved" )
            return MOVED;
        else if ( s == "401 Unauthorized" )
            return UNAUTHORIZED;
        else if ( s == "403 Forbidden" )
            return FORBIDDEN;
        else if ( s == "404 Not Found" )
            return NOT_FOUND;
        else if ( s == "422 Unprocessable Entity" )
            return UNPROCESSABLE_ENTITY;
        else if ( s == "500 Internal Server Error" )
            return INTERNAL_SERVER_ERROR;
        else
            return UNKNOWN_ERROR;
    }


}