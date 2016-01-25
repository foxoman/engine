//
// Created by D.E. Goodman-Wilson on 12/8/15.
//

#include "private.h"
#include "slack/http.h"

namespace slack_private
{


Json::Value parse(slack::base::response *obj, const std::string &json)
{
    obj->raw_json = json;

    Json::Value result_ob;

    Json::Reader reader;
    bool parsed_success = reader.parse(json, result_ob, false);
    if (!parsed_success)
    {
        obj->error_message = std::string{"json_parse_failure"};
        return result_ob;
    }

    if (!result_ob["ok"].isBool())
    {
        obj->error_message = std::string{"invalid_response"};
        return result_ob;
    }

    auto ok = result_ob["ok"].asBool();

    if (!ok)
    {
        obj->error_message = result_ob["error"].asString();
        return result_ob;
    }

    return result_ob;
}

std::string make_hostname()
{
    return "https://" + slack::get_host() + "/api/";
}


Json::Value get(slack::base::response *obj, std::string endpoint, slack::http::params params, bool auth)
{
    Json::Value result_ob;

    if (auth)
    {
        params["token"] = slack::get_token();
    }

    if(!slack::get_http())
    {
        //TODO only if opted in! Otherwise we need to error out!
        slack::set_http(std::make_shared<slack::simple_http>());
    }

    auto response = slack::get_http()->get(make_hostname() + endpoint, params);
    if (response.status_code != 200)
    {
        //TODO do something!
        obj->error_message = std::string{"TODO"};
        return result_ob;
    }

    return parse(obj, response.body);
}

factory<slack::base::event> events_factory;

} //namespace slack_private