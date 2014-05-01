#include "api.hpp"
#include "exception.hpp"



int main ( int argc, char **argv ) {
    using namespace std;
    eighttracks::API api;

    eighttracks::MixSet s = api.play_mix ( "3934951" );
    std::cout << s.track.track_file_stream_url << std::endl;
    
    /*string jsontest("{ \"testnul\": \"null\" }");
    Json::Value root;
    Json::Reader reader;
    bool parseok = reader.parse( jsontest, root );
    if ( !parseok ) {
        cout << "Invalid json!" << std::endl;
    } 
    else {
        //cout << root["testnul"].isNull() << endl;
        Json::Value s = root["Bla"];
        cout << s.asString() << endl;
    }*/
    
    /*try {
        Json::Value resp;
        resp["status"] = "404 Not found";
        //resp["errors"] = "Page not found";
        resp["notice"] = "null";
        
        throw eighttracks::ApiRuntimeError(resp);
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }*/

    return 0;
}
