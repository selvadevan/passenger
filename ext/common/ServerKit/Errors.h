/*
 *  Phusion Passenger - https://www.phusionpassenger.com/
 *  Copyright (c) 2012-2014 Phusion
 *
 *  "Phusion Passenger" is a trademark of Hongli Lai & Ninh Bui.
 *
 *  See LICENSE file for license information.
 */
#ifndef _PASSENGER_SERVER_KIT_ERRORS_H_
#define _PASSENGER_SERVER_KIT_ERRORS_H_

#include <cstring>
#include <ServerKit/http_parser.h>

namespace Passenger {
namespace ServerKit {


enum Error {
	// HttpChunkedBodyParser errors
	CHUNK_SIZE_TOO_LARGE        = -1000,
	CHUNK_SIZE_PARSE_ERROR      = -1001,
	CHUNK_FOOTER_PARSE_ERROR    = -1002,
	CHUNK_FINALIZER_PARSE_ERROR = -1003,
	UNEXPECTED_EOF              = -1004,

	// HttpHeaderParser errors
	HTTP_VERSION_NOT_SUPPORTED                             = -1010,
	REQUEST_CONTAINS_CONTENT_LENGTH_AND_TRANSFER_ENCODING  = -1011,
	UPGRADE_NOT_ALLOWED_WHEN_REQUEST_BODY_EXISTS           = -1012,
	UPGRADE_NOT_ALLOWED_FOR_HEAD_REQUESTS                  = -1013,
	RESPONSE_CONTAINS_CONTENT_LENGTH_AND_TRANSFER_ENCODING = -1014,
	SECURITY_PASSWORD_MISMATCH                             = -1015,
	SECURITY_PASSWORD_DUPLICATE                            = -1016,
	ERROR_SECURE_HEADER_NOT_ALLOWED                        = -1017,
	NORMAL_HEADER_NOT_ALLOWED_AFTER_SECURITY_PASSWORD      = -1018,

	// Error codes below -2000 are http_parser errors
	HTTP_PARSER_ERRNO_BEGIN     = -2000,
};

inline const char *
getErrorDesc(int errcode) {
	switch (errcode) {
	case CHUNK_SIZE_TOO_LARGE:
		return "Chunked encoding size too large";
	case CHUNK_SIZE_PARSE_ERROR:
		return "Chunked encoding size string parse error";
	case CHUNK_FOOTER_PARSE_ERROR:
		return "Chunked encoding footer parse error";
	case CHUNK_FINALIZER_PARSE_ERROR:
		return "Chunked encoding final chunk parse error";
	case UNEXPECTED_EOF:
		return "Unexpected end-of-stream";
	case HTTP_VERSION_NOT_SUPPORTED:
		return "HTTP Version Not Supported";
	case REQUEST_CONTAINS_CONTENT_LENGTH_AND_TRANSFER_ENCODING:
		return "Bad request (request may not contain both Content-Length and Transfer-Encoding)";
	case UPGRADE_NOT_ALLOWED_WHEN_REQUEST_BODY_EXISTS:
		return "Bad request (Connection upgrading is only allowed for requests without request body)";
	case UPGRADE_NOT_ALLOWED_FOR_HEAD_REQUESTS:
		return "Bad request (Connection upgrading is not allowed for HEAD requests)";
	case RESPONSE_CONTAINS_CONTENT_LENGTH_AND_TRANSFER_ENCODING:
		return "Response may not contain both Content-Length and Transfer-Encoding";
	case SECURITY_PASSWORD_MISMATCH:
		return "Security password mismatch";
	case SECURITY_PASSWORD_DUPLICATE:
		return "A duplicate security password header was encountered";
	case ERROR_SECURE_HEADER_NOT_ALLOWED:
		return "A secure header was provided, but no security password was provided";
	case NORMAL_HEADER_NOT_ALLOWED_AFTER_SECURITY_PASSWORD:
		return "A normal header was encountered after the security password header";
	default:
		if (errcode <= HTTP_PARSER_ERRNO_BEGIN) {
			return http_errno_description((enum http_errno)
				(-errcode + HTTP_PARSER_ERRNO_BEGIN));
		} else {
			return std::strerror(errcode);
		}
	}
}


} // namespace ServerKit
} // namespace Passenger

#endif /* _PASSENGER_SERVER_KIT_ERRORS_H_ */