/* soapwebProxy.cpp
   Generated by gSOAP 2.8.30 for webapi.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapwebProxy.h"

webProxy::webProxy() : soap(SOAP_IO_DEFAULT)
{	webProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

webProxy::webProxy(const webProxy& rhs)
{	soap_copy_context(this, &rhs);
	this->soap_endpoint = rhs.soap_endpoint;
}

webProxy::webProxy(const struct soap &_soap) : soap(_soap)
{ }

webProxy::webProxy(const char *endpoint) : soap(SOAP_IO_DEFAULT)
{	webProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = endpoint;
}

webProxy::webProxy(soap_mode iomode) : soap(iomode)
{	webProxy_init(iomode, iomode);
}

webProxy::webProxy(const char *endpoint, soap_mode iomode) : soap(iomode)
{	webProxy_init(iomode, iomode);
	soap_endpoint = endpoint;
}

webProxy::webProxy(soap_mode imode, soap_mode omode) : soap(imode, omode)
{	webProxy_init(imode, omode);
}

webProxy::~webProxy()
{
	this->destroy();
	}

void webProxy::webProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] = {
        {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
        {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
        {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
        {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
        {"api", "urn:web", NULL, NULL},
        {NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this, namespaces);
}

#ifndef WITH_PURE_VIRTUAL
webProxy *webProxy::copy()
{	webProxy *dup = SOAP_NEW_COPY(webProxy(*(struct soap*)this));
	return dup;
}
#endif

webProxy& webProxy::operator=(const webProxy& rhs)
{	soap_copy_context(this, &rhs);
	this->soap_endpoint = rhs.soap_endpoint;
	return *this;
}

void webProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void webProxy::reset()
{	this->destroy();
	soap_done(this);
	soap_initialize(this);
	webProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void webProxy::soap_noheader()
{	this->header = NULL;
}

::SOAP_ENV__Header *webProxy::soap_header()
{	return this->header;
}

::SOAP_ENV__Fault *webProxy::soap_fault()
{	return this->fault;
}

const char *webProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *webProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int webProxy::soap_close_socket()
{	return soap_closesock(this);
}

int webProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void webProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void webProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *webProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int webProxy::encrypt(const char *endpoint, const char *soap_action, char *input, char **output)
{	struct soap *soap = this;
	struct api__encrypt soap_tmp_api__encrypt;
	struct api__encryptResponse *soap_tmp_api__encryptResponse;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/web.cgi";
	soap_tmp_api__encrypt.input = input;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_api__encrypt(soap, &soap_tmp_api__encrypt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_api__encrypt(soap, &soap_tmp_api__encrypt, "api:encrypt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_api__encrypt(soap, &soap_tmp_api__encrypt, "api:encrypt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!output)
		return soap_closesock(soap);
	*output = NULL;
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_api__encryptResponse = soap_get_api__encryptResponse(soap, NULL, "", NULL);
	if (!soap_tmp_api__encryptResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (output && soap_tmp_api__encryptResponse->output)
		*output = *soap_tmp_api__encryptResponse->output;
	return soap_closesock(soap);
}

int webProxy::login_by_key(const char *endpoint, const char *soap_action, char *usr, char *psw, struct api__result &flag)
{	struct soap *soap = this;
	struct api__login_by_key soap_tmp_api__login_by_key;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://localhost/web.cgi";
	soap_tmp_api__login_by_key.usr = usr;
	soap_tmp_api__login_by_key.psw = psw;
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_api__login_by_key(soap, &soap_tmp_api__login_by_key);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_api__login_by_key(soap, &soap_tmp_api__login_by_key, "api:login-by-key", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_api__login_by_key(soap, &soap_tmp_api__login_by_key, "api:login-by-key", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&flag)
		return soap_closesock(soap);
	soap_default_api__result(soap, &flag);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_get_api__result(soap, &flag, "", NULL);
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
