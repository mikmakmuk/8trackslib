#ifndef EIGHT_TRACKS_API_HPP
#define EIGHT_TRACKS_API_HPP

#include <string>
#include <map>

#include <jsoncpp/json/json.h>

#include <curlpp/Easy.hpp>

namespace eighttracks {
    enum status_t {
        OK = 200,
        MOVED_PERMANENTLY = 301,
        MOVED = 302,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        UNPROCESSABLE_ENTITY = 422,
        INTERNAL_SERVER_ERROR = 500,
        UNKNOWN_ERROR = 999
    };

    struct Track {
        std::string track_id;
        std::string name;
        std::string performer;
        std::string release_name;
        std::string track_file_stream_url;
        std::string url;
    };

    struct MixSet {
        std::string mix_id;
        bool at_beginning;
        bool at_last_track;
        bool at_end;
        bool skip_allowed;
        Track track;
    };

    class API {
        std::string apikey;
        std::string version;
        std::string base_url;
        std::string play_token;
        curlpp::Easy handle;
        typedef std::map<std::string,std::string> curlParams;
        Json::Reader reader;
        Json::Value root;

    public:
        API();
        ~API();
        MixSet play_mix ( const std::string& mix_id );
        MixSet next_track ( const std::string& mix_id );
        MixSet skip_track ( const std::string& mix_id );
        void report_track ( const std::string& mix_id, const std::string& track_id );

    private:
        std::string params_string ( const curlParams& params );
        void add_param ( curlParams& params, const std::string& key, const std::string& value );
        void get ( const std::string& request );
        void get ( const std::string& request, const curlParams& params );
        std::string obtain_play_token();
        MixSet playback_control ( const std::string& command, const std::string& mix_id );
        status_t response_status( const Json::Value& status );
    };

}

#endif // #ifndef EIGHT_TRACKS_API_HPP
