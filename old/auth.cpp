//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "slack/auth.h"
#include "config.h"
#include <cpr.h>
#include <json/json.h>

namespace slack_config
{
extern std::string token_;
}
namespace slack
{

namespace auth
{


::slack::response::auth::test test_wrapper::get_response()
{
    cpr::Parameters params; //no need for a token here
    params.AddParameter({"token", slack_config::token_});

    auto result = cpr::Post(cpr::Url{slack_config::HOSTNAME + "auth.test"}, params);
    if (result.status_code != 200)
    {
        //error path
        return {result.text}; //TODO
    }
    //happy path
    Json::Value result_ob;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(result.text, result_ob, false);
    if (!parsedSuccess)
    {
        return {result.text}; //TODO
    }

    return {result.text,
            result_ob["ok"].asBool(),
            std::experimental::nullopt,
            result_ob["url"].asString(),
            result_ob["team"].asString(),
            result_ob["user"].asString(),
            result_ob["team_id"].asString(),
            result_ob["user_id"].asString()};

}

::slack::response::auth::test test()
{
    test_wrapper wrapper;
    return wrapper.get_response();
}

} //namespace auth
} //namespace slack