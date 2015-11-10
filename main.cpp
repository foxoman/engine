#include <iostream>
#include <slack/slack.h>
#include <cpr.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];

    slack::set_token(token);

    std::cout << slack::api::test() << std::endl;
    slack::api::error e{"error"};
    slack::api::foo f{"bar"};
    std::cout << slack::api::test(e) << std::endl;
    std::cout << slack::api::test(slack::api::error{"error"}, slack::api::foo{"bar"}) << std::endl;
    std::cout << slack::api::test(e, slack::api::foo{"bar"}) << std::endl;


    std::cout << slack::auth::test().url << std::endl;

    return 0;
}