//
// Created by D.E. Goodman-Wilson on 11/5/15.
//

#pragma once

#include "api_base.h"
#include "auth.h"
#include <boost/network/protocol/http/client.hpp>
#include <optional/optional.hpp>
#include <string>
#include <map>

namespace slack
{

class plaid
{
public:
    plaid(std::string token);

    friend class api_base;
    auth auth;

protected:
    boost::network::http::client::response get_(const std::string &method,
                                                const std::experimental::optional<std::multimap<std::string, std::string>> params = std::experimental::nullopt);

private:
    std::string token_;
    boost::network::http::client client_;

};

} //namespace slack