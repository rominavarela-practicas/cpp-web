// ---------------------------------------------------------------------
// pion:  a Boost C++ framework for building lightweight HTTP interfaces
// ---------------------------------------------------------------------
// Copyright (C) 2007-2014 Splunk Inc.  (https://github.com/splunk/pion)
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//

#ifndef __PION_SPDYPARSER_HEADER__
#define __PION_SPDYPARSER_HEADER__


#include <boost/shared_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/once.hpp>
#include <pion/config.hpp>
#include <pion/logger.hpp>
#include <pion/spdy/types.hpp>
#include <pion/spdy/decompressor.hpp>

#ifndef BOOST_SYSTEM_NOEXCEPT
    #define BOOST_SYSTEM_NOEXCEPT BOOST_NOEXCEPT
#endif


namespace pion {    // begin namespace pion
namespace spdy {    // begin namespace spdy

    
///
/// parser : parsers and reads the SPDY frames
///

class PION_API parser
{
public:
    
    /// class-specific error code values
    enum error_value_t {
        ERROR_INVALID_SPDY_FRAME = 1,
        ERROR_INVALID_SPDY_VERSION,
        ERROR_DECOMPRESSION,
        ERROR_PROTOCOL_ERROR,
        ERROR_INTERNAL_SPDY_ERROR,
        ERROR_MISSING_HEADER_DATA
    };
    
    /// class-specific error category
    class error_category_t
        : public boost::system::error_category
    {
    public:
        const char *name() const BOOST_SYSTEM_NOEXCEPT { return "SPDYParser"; }
        std::string message(int ev) const {
            switch (ev) {
                case ERROR_INVALID_SPDY_FRAME:
                    return "invalid spdy frame";
                case ERROR_INVALID_SPDY_VERSION:
                    return "invalid spdy version";
                case ERROR_DECOMPRESSION:
                    return "error in decompression";
                case ERROR_MISSING_HEADER_DATA:
                    return "missing header data";
                    
            }
            return "SPDYParser error";
        }
    };
    
    /// constructs a new parser object (default constructor)
    parser();
    
    /// destructor
    ~parser() {}
    
    /**
     * parse a SPDY packet
     *
     * @return boost::tribool result of parsing:
     *                        false = SPDY frame has an error,
     *                        true = finished parsing SPDY frame,
     *                        indeterminate = not yet finished parsing SPDY frame
     */
    boost::tribool parse(http_protocol_info& http_headers,
                         boost::system::error_code& ec,
                         decompressor_ptr& decompressor,
                         const char *packet_ptr,
                         boost::uint32_t& length_packet,
                         boost::uint32_t current_stream_count);
    
    /// Get the pointer to the first character to the spdy data contect 
    const char * get_spdy_data_content( ) { return m_last_data_chunk_ptr; }
    
    /// Get the pointer to the first character to the spdy data contect
    const char * get_spdy_read_pointer( ) { return m_read_ptr; }
    
    /**
     * checks if the frame is spdy frame or not
     *
     * @return true if it is a frame else returns false
     */
    static spdy_frame_type get_spdy_frame_type(const char *ptr);
    
    /**
     * checks if the frame is spdy control frame or not
     *
     * @return true if it is a control frame else returns false
     */
    static bool is_spdy_control_frame(const char *ptr);
    
    /**
     * get the stream id for the spdy control frame
     *
     * @return true if it is a control frame else returns false
     */
    static boost::uint32_t get_control_frame_stream_id(const char *ptr);
    
    
protected:
    
    /// resets the read pointer
    inline void set_read_ptr(const char *ptr) { m_read_ptr = m_current_data_chunk_ptr = ptr; }
    
    /// populates the frame for every spdy packet
    /// Returns false if there was an error else returns true
    bool populate_frame(boost::system::error_code& ec,
                        spdy_control_frame_info& frame,
                        boost::uint32_t& length_packet,
                        boost::uint32_t& stream_id,
                        http_protocol_info& http_headers);
    
    /// creates the unique parser error_category_t
    static void create_error_category(void);
    
    /// returns an instance of parser::error_category_t
    static inline error_category_t& get_error_category(void) {
        boost::call_once(parser::create_error_category, m_instance_flag);
        return *m_error_category_ptr;
    }

    /**
     * sets an error code
     *
     * @param ec error code variable to define
     * @param ev error value to raise
     */
    static inline void set_error(boost::system::error_code& ec, error_value_t ev) {
        ec = boost::system::error_code(static_cast<int>(ev), get_error_category());
    }
    
    /**
     * parses an the header payload for SPDY
     *
     */
    void parse_header_payload(boost::system::error_code& ec,
                              decompressor_ptr& decompressor,
                              const spdy_control_frame_info& frame,
                              http_protocol_info& http_headers,
                              boost::uint32_t current_stream_count);
    
    /**
     * parses the data for SPDY
     *
     */
    void parse_spdy_data(boost::system::error_code& ec,
                         const spdy_control_frame_info& frame,
                         boost::uint32_t stream_id,
                         http_protocol_info& http_info);
    
    /**
     * parses an the Settings Frame for SPDY
     *
     */
    void parse_spdy_settings_frame(boost::system::error_code& ec,
                                   const spdy_control_frame_info& frame);
    
    /**
     * parses an the RST stream for SPDY
     *
     */
    void parse_spdy_rst_stream(boost::system::error_code& ec,
                               const spdy_control_frame_info& frame);
    
    /**
     * parses an the Ping Frame for SPDY
     *
     */
    void parse_spdy_ping_frame(boost::system::error_code& ec,
                               const spdy_control_frame_info& frame);
    
    /**
     * parses an the GoAway Frame for SPDY
     *
     */
    void parse_spdy_goaway_frame(boost::system::error_code& ec,
                                 const spdy_control_frame_info& frame);
    
    /**
     * parses an the WindowUpdate Frame for SPDY
     *
     */
    void parse_spdy_window_update_frame(boost::system::error_code& ec,
                                        const spdy_control_frame_info& frame);
    
    /**
     * parse a SPDY frame (protected implementation)
     *
     * @return boost::tribool result of parsing:
     *                        false = SPDY frame has an error,
     *                        true = finished parsing SPDY frame,
     *                        indeterminate = not yet finished parsing SPDY frame
     */
    boost::tribool parse_spdy_frame(boost::system::error_code& ec,
                                    decompressor_ptr& decompressor,
                                    http_protocol_info& http_headers,
                                    boost::uint32_t& length_packet,
                                    boost::uint32_t current_stream_count);
    
private:
    
    /// generic read pointer which parses the spdy data
    const char *                        m_read_ptr;
    
    /// points to the first character of the uncompressed http headers
    const char *                        m_uncompressed_ptr;
    
    /// SPDY has interleaved frames and this will point to start of the current chunk data
    const char *                        m_current_data_chunk_ptr;
    
    /// SPDY has interleaved frames and this will point to start of the the last chunk data
    const char *                        m_last_data_chunk_ptr;
    
    /// primary logging interface used by this class
    mutable logger                      m_logger;
    
    /// points to a single and unique instance of the HTTPParser ErrorCategory
    static error_category_t *           m_error_category_ptr;
    
    /// used to ensure thread safety of the HTTPParser ErrorCategory
    static boost::once_flag             m_instance_flag;
};

/// data type for a spdy reader pointer
typedef boost::shared_ptr<parser>       parser_ptr;
        
        
}   // end namespace spdy
}   // end namespace pion

#endif

