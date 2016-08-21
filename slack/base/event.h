//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>
#include <slack/types.h>

namespace slack { namespace base
{

struct event
{
    //This space left intentionally blank
    event() = default;
    virtual ~event() = default;

    template<class json>
    event(const slack::team_id &team_id, const json &parsed_json) : team_id{team_id}
    {}

    slack::team_id team_id;
};

}} //namespace base slack