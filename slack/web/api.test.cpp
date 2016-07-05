//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include "slack/web/api.test.h"
#include "private.h"
#include <json/json.h>

namespace slack { namespace api
{

void test::initialize_()
{
    http::params params;

    if (error_)
    {
        params.emplace("error", *error_);
    }
    if (foo_)
    {
        params.emplace("foo", *foo_);
    }

    auto result_ob = slack_private::get(this, "api.test", params, false);

    if (!result_ob["args"].isNull() && result_ob["args"].isObject())
    {
        args = std::map<std::string, std::string>{};

        for (auto arg: result_ob["args"].getMemberNames())
        {
            args->emplace(arg, result_ob["args"][arg].asString());
        }
    }
}

}} //namespace api slack