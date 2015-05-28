// ---------------------------------------------------------------------
// pion:  a Boost C++ framework for building lightweight HTTP interfaces
// ---------------------------------------------------------------------
// Copyright (C) 2007-2014 Splunk Inc.  (https://github.com/splunk/pion)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//

#ifndef __PION_HTTP_COOKIE_AUTH_HEADER__
#define __PION_HTTP_COOKIE_AUTH_HEADER__

#include <map>
#include <string>
#include <boost/random.hpp>
#include <pion/config.hpp>
#include <pion/http/auth.hpp>


namespace pion {    // begin namespace pion
namespace http {    // begin namespace http


///
/// cookie_auth: handles HTTP authentication and session management in
/// accordance with RFC 2617 (http://tools.ietf.org/html/rfc2617 ) using cookies.
///
class PION_API cookie_auth :
    public http::auth
{
public:
    
    /**
     * default constructor
     *
     * @param userManager
     * @param login - URL resource for login request. Typical login request has format:
     *              http://website/login?user="username"&pass="password"&url="redirection_url"
     * @param logout - URL resource for logout request. Typical logout request has format:
     *              http://website/logout?url="redirection_url"
     * @param redirect - if not empty, URL for redirection in case of authentication failure
     *                  if empty - send code 401 on authentication failure
     */
    cookie_auth(user_manager_ptr userManager, 
        const std::string& login="/login",
        const std::string& logout="/logout",
        const std::string& redirect="");
    
    /// virtual destructor
    virtual ~cookie_auth() {}
    
    /**
     * attempts to validate authentication of a new HTTP request. 
     * If request valid, pointer to user identity object (if any) will be preserved in 
     * the request and return "true". 
     * If request not authenticated, appropriate response is sent over tcp_conn
     * and return "false";
     *
     * Note: if request matches "login" resource, then login sequences attempted. 
     * If "name" and "pass" attributes match user definition, a random cookie is created
     * and associated with given user session. If request contains "url" attribute,
     * then page redirection response returned. Otherwise - empty 204 response.
     *
     * @param http_request_ptr the new HTTP request to handle
     * @param tcp_conn the TCP connection that has the new request
     *
     * @return true if request valid and user identity inserted into request 
     */
    virtual bool handle_request(http::request_ptr& http_request_ptr, tcp::connection_ptr& tcp_conn);
    
    /**
     * sets a configuration option
     * Valid options:
     *    - "login" - URL resource for login request. Typical login request has format:
     *              http://website/login?user="username"&pass="password"&url="redirection_url"
     *    - "logout" - URL resource for logout request. Typical logout request has format:
     *              http://website/logout?url="redirection_url"
     *    - "redirect" - if not empty, URL for redirection in case of authentication failure
     *                  if empty - send code 401 on authentication failure
     *
     * @param name the name of the option to change
     * @param value the value of the option
     */
    virtual void set_option(const std::string& name, const std::string& value);

    
protected:

    /**
     * check if given request is a login/logout and process it
     *
     * @param http_request_ptr the new HTTP request to handle
     * @param tcp_conn the TCP connection that has the new request
     *
     * @return true if it was a login/logout request and no future processing required.
     */
    bool process_login(http::request_ptr& http_request_ptr, tcp::connection_ptr& tcp_conn);

    /**
     * used to send responses when access to resource is not authorized
     *
     * @param http_request_ptr the new HTTP request to handle
     * @param tcp_conn the TCP connection that has the new request
     */
    void handle_unauthorized(http::request_ptr& http_request_ptr, tcp::connection_ptr& tcp_conn);
    
    /**
     * used to send redirection responses 
     *
     * @param http_request_ptr the new HTTP request to handle
     * @param tcp_conn the TCP connection that has the new request
     */
    void handle_redirection(http::request_ptr& http_request_ptr, tcp::connection_ptr& tcp_conn,
        const std::string &redirection_url, const std::string &new_cookie="", bool delete_cookie=false);

    /**
     * used to send OK responses with new cookie
     *
     * @param http_request_ptr the new HTTP request to handle
     * @param tcp_conn the TCP connection that has the new request
     */
    void handle_ok(http::request_ptr& http_request_ptr, tcp::connection_ptr& tcp_conn,
        const std::string &new_cookie="", bool delete_cookie=false);

    /**
     * Cache expiration cleanup. (Call it periodically)
     */
    void expire_cache(const boost::posix_time::ptime &time_now);

    
private:
    
    /// number of seconds after which entries in the user cache will be expired
    static const unsigned int   CACHE_EXPIRATION;

    /// number of random bytes to use for cookie generation
    static const unsigned int   RANDOM_COOKIE_BYTES;

    /// name of cookie used for authentication
    static const std::string    AUTH_COOKIE_NAME;

    /// value of "login" resource 
    std::string                 m_login; 

    /// value of "logout" resource 
    std::string                 m_logout; 

    /// value of "redirection" resource 
    std::string                 m_redirect;
    
    /// random number generator used for cookie generation
    boost::mt19937              m_random_gen;

    /// random number range used for cookie generation
    boost::uniform_int<>        m_random_range;

    /// random dice that uses m_random_gen to produce ints within m_random_range
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> >    m_random_die;

    /// time of the last cache clean up
    boost::posix_time::ptime    m_cache_cleanup_time;
        
    /// cache of users that are currently active
    user_cache_type             m_user_cache;
    
    /// mutex used to protect access to the user cache
    mutable boost::mutex        m_cache_mutex;
};

    
}   // end namespace http
}   // end namespace pion

#endif
