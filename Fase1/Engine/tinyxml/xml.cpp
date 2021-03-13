#define TIXML_USE_STL
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

// g++ -o xmlTest tinyxml.cpp tinystr.cpp tinyxmlparser.cpp tinyxmlerror.cpp xml.cpp


int main(int argc, char** argv) {

    TiXmlDocument doc( "demo.xml" );
    bool loadOk = doc.LoadFile();

    if (loadOk) {
        TiXmlElement * scene = doc.FirstChildElement( "scene" );
        if( scene ) {
            TiXmlElement * figure = scene->FirstChildElement( "model" );
            if (figure) {
                printf("%s \n", figure->Attribute("file"));
            }
        }

    } else {
        //load failed
    }


}