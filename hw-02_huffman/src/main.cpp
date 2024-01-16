#include <memory>
#include <optional>
#include <algorithm>

#include "Archiver.h"
#include "test.h"


class Manager {
public:
    Manager(char** flags, int argc){
        parsFlags(flags, argc);
    }

    bool Process() {
        if(IsValid()){
            Request* request = nullptr;
            switch (mode) {
                case Mode::Comp:
                    request = new EncodeRequest(is, os);
                    break;
                case Mode::Decomp:
                    request = new DecodeRequest(is, os);
                    break;
                case Mode::Undef:
                    break;
            }
            if(request){
                request->Read();
                request->Process();
                request->Write();
                request->PrintMetadata();
            }

            delete request;
        }
        return false;
    }

private:

    bool IsValid(){
        return mode != Mode::Undef && is && os;
    }

    void parsFlags(char** flags, int argc){
        if(argc >= 5) {
            mode = std::string(flags[1]) == "-c" ? Mode::Comp : std::string(flags[1]) == "-u" ? Mode::Decomp
                   : Mode::Undef;
            if(std::string(flags[2]) == "-f")
                is.open(std::string(flags[3]), std::ios::binary);
            if(std::string(flags[4]) == "-o")
                os.open(std::string(flags[5]), std::ios::binary);
        }
    }

    enum class Mode {
        Comp,
        Decomp,
        Undef
    };

    Mode mode = Mode::Undef;
    std::ifstream is;
    std::ofstream os;
};

int main(int argc, char** argv) {

    AllTests();
    Manager manager(argv, argc);
    manager.Process();

    return 0;

}