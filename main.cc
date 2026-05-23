#include <drogon/drogon.h>
// #include  <yaml-cpp/yaml.h>
#include <iostream>

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", 5555);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    // std::cout << drogon::getVersion() << std::endl;
    auto handlers =
     drogon::app().getHandlersInfo();

    for (const auto& handler : handlers)
    {
        std::cout
            << "Path: "
            << std::get<0>(handler)
            << " Method: "
            << std::get<1>(handler)
            << " Description: "
            << std::get<2>(handler)
            << std::endl;
    }

    drogon::app().run();
    return 0;
}
