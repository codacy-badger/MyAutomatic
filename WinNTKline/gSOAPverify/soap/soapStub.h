/* soapStub.h
   Generated by gSOAP 2.8.30 for F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/


#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#if GSOAP_VERSION != 20830
# error "GSOAP VERSION 20830 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes, Structs and Unions                                                *
 *                                                                            *
\******************************************************************************/

struct api__result;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:13 */
struct ArrayOfEmp2;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:22 */
struct api__encryptResponse;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:26 */
struct api__encrypt;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:26 */
struct api__login_by_keyResponse;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
struct api__login_by_key;	/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:13 */
#ifndef SOAP_TYPE_api__result
#define SOAP_TYPE_api__result (10)
/* complex XSD type 'api:result': */
struct api__result {
      public:
        /** Required element 'flag' of XSD type 'xsd-int' */
        long flag;
        /** Required element 'idx' of XSD type 'xsd-int' */
        long idx;
        /** Required element 'age' of XSD type 'xsd-int' */
        long age;
        /** Optional element 'tell' of XSD type 'xsd-string' */
        char *tell;
        /** Optional element 'email' of XSD type 'xsd-string' */
        char *email;
      public:
        /** Return unique type id SOAP_TYPE_api__result */
        int soap_type() const { return SOAP_TYPE_api__result; }
        /** Constructor with member initializations */
        api__result()
        {
          flag = (long)0;
          idx = (long)0;
          age = (long)0;
          tell = (char *)0;
          email = (char *)0;
        }
        /** Friend allocator used by soap_new_api__result(struct soap*, int) */
        friend SOAP_FMAC1 api__result * SOAP_FMAC2 soap_instantiate_api__result(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:22 */
#ifndef SOAP_TYPE_ArrayOfEmp2
#define SOAP_TYPE_ArrayOfEmp2 (11)
/* complex XSD type 'ArrayOfEmp2': */
struct ArrayOfEmp2 {
      public:
        /** Required element 'rslt' of XSD type 'api:result' */
        struct api__result rslt;
      public:
        /** Return unique type id SOAP_TYPE_ArrayOfEmp2 */
        int soap_type() const { return SOAP_TYPE_ArrayOfEmp2; }
        /** Constructor with member initializations */
        ArrayOfEmp2()
        {
        }
        /** Friend allocator used by soap_new_ArrayOfEmp2(struct soap*, int) */
        friend SOAP_FMAC1 ArrayOfEmp2 * SOAP_FMAC2 soap_instantiate_ArrayOfEmp2(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:26 */
#ifndef SOAP_TYPE_api__encryptResponse
#define SOAP_TYPE_api__encryptResponse (14)
/* complex XSD type 'api:encryptResponse': */
struct api__encryptResponse {
      public:
        /** Optional element 'out' of XSD type 'xsd:string' */
        char **out;
      public:
        /** Return unique type id SOAP_TYPE_api__encryptResponse */
        int soap_type() const { return SOAP_TYPE_api__encryptResponse; }
        /** Constructor with member initializations */
        api__encryptResponse()
        {
          out = (char **)0;
        }
        /** Friend allocator used by soap_new_api__encryptResponse(struct soap*, int) */
        friend SOAP_FMAC1 api__encryptResponse * SOAP_FMAC2 soap_instantiate_api__encryptResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:26 */
#ifndef SOAP_TYPE_api__encrypt
#define SOAP_TYPE_api__encrypt (15)
/* complex XSD type 'api:encrypt': */
struct api__encrypt {
      public:
        /** Optional element 'in' of XSD type 'xsd:string' */
        char *in;
      public:
        /** Return unique type id SOAP_TYPE_api__encrypt */
        int soap_type() const { return SOAP_TYPE_api__encrypt; }
        /** Constructor with member initializations */
        api__encrypt()
        {
          in = (char *)0;
        }
        /** Friend allocator used by soap_new_api__encrypt(struct soap*, int) */
        friend SOAP_FMAC1 api__encrypt * SOAP_FMAC2 soap_instantiate_api__encrypt(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef SOAP_TYPE_api__login_by_keyResponse
#define SOAP_TYPE_api__login_by_keyResponse (18)
/* complex XSD type 'api:login-by-keyResponse': */
struct api__login_by_keyResponse {
      public:
        /** Required element 'ccc' of XSD type 'ArrayOfEmp2' */
        struct ArrayOfEmp2 ccc;
      public:
        /** Return unique type id SOAP_TYPE_api__login_by_keyResponse */
        int soap_type() const { return SOAP_TYPE_api__login_by_keyResponse; }
        /** Constructor with member initializations */
        api__login_by_keyResponse()
        {
        }
        /** Friend allocator used by soap_new_api__login_by_keyResponse(struct soap*, int) */
        friend SOAP_FMAC1 api__login_by_keyResponse * SOAP_FMAC2 soap_instantiate_api__login_by_keyResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef SOAP_TYPE_api__login_by_key
#define SOAP_TYPE_api__login_by_key (19)
/* complex XSD type 'api:login-by-key': */
struct api__login_by_key {
      public:
        /** Optional element 'usr' of XSD type 'xsd-string' */
        char *usr;
        /** Optional element 'psw' of XSD type 'xsd-string' */
        char *psw;
      public:
        /** Return unique type id SOAP_TYPE_api__login_by_key */
        int soap_type() const { return SOAP_TYPE_api__login_by_key; }
        /** Constructor with member initializations */
        api__login_by_key()
        {
          usr = (char *)0;
          psw = (char *)0;
        }
        /** Friend allocator used by soap_new_api__login_by_key(struct soap*, int) */
        friend SOAP_FMAC1 api__login_by_key * SOAP_FMAC2 soap_instantiate_api__login_by_key(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (20)
/* SOAP_ENV__Header: */
struct SOAP_ENV__Header {
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Header */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Header; }
        /** Constructor with member initializations */
        SOAP_ENV__Header()
        {
        }
        /** Friend allocator used by soap_new_SOAP_ENV__Header(struct soap*, int) */
        friend SOAP_FMAC1 SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (21)
/* Type SOAP_ENV__Code is a recursive data type, (in)directly referencing itself through its (base or derived class) members */
/* SOAP_ENV__Code: */
struct SOAP_ENV__Code {
      public:
        /** Optional element 'SOAP-ENV:Value' of XSD type 'xsd:QName' */
        char *SOAP_ENV__Value;
        /** Optional element 'SOAP-ENV:Subcode' of XSD type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Subcode;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Code */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Code; }
        /** Constructor with member initializations */
        SOAP_ENV__Code()
        {
          SOAP_ENV__Value = (char *)0;
          SOAP_ENV__Subcode = (struct SOAP_ENV__Code *)0;
        }
        /** Friend allocator used by soap_new_SOAP_ENV__Code(struct soap*, int) */
        friend SOAP_FMAC1 SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (23)
/* SOAP_ENV__Detail: */
struct SOAP_ENV__Detail {
      public:
        char *__any;
        /** Any type of element 'fault' assigned to fault with its SOAP_TYPE_T assigned to __type */
        /** Do not create a cyclic data structure throught this member unless SOAP encoding or SOAP_XML_GRAPH are used for id-ref serialization */
        int __type;
        void *fault;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Detail */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Detail; }
        /** Constructor with member initializations */
        SOAP_ENV__Detail()
        {
          __any = (char *)0;
          __type = 0;
          fault = NULL;
        }
        /** Friend allocator used by soap_new_SOAP_ENV__Detail(struct soap*, int) */
        friend SOAP_FMAC1 SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (26)
/* SOAP_ENV__Reason: */
struct SOAP_ENV__Reason {
      public:
        /** Optional element 'SOAP-ENV:Text' of XSD type 'xsd:string' */
        char *SOAP_ENV__Text;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Reason */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Reason; }
        /** Constructor with member initializations */
        SOAP_ENV__Reason()
        {
          SOAP_ENV__Text = (char *)0;
        }
        /** Friend allocator used by soap_new_SOAP_ENV__Reason(struct soap*, int) */
        friend SOAP_FMAC1 SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:27 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (27)
/* SOAP_ENV__Fault: */
struct SOAP_ENV__Fault {
      public:
        /** Optional element 'faultcode' of XSD type 'xsd:QName' */
        char *faultcode;
        /** Optional element 'faultstring' of XSD type 'xsd:string' */
        char *faultstring;
        /** Optional element 'faultactor' of XSD type 'xsd:string' */
        char *faultactor;
        /** Optional element 'detail' of XSD type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *detail;
        /** Optional element 'SOAP-ENV:Code' of XSD type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Code;
        /** Optional element 'SOAP-ENV:Reason' of XSD type 'SOAP-ENV:Reason' */
        struct SOAP_ENV__Reason *SOAP_ENV__Reason;
        /** Optional element 'SOAP-ENV:Node' of XSD type 'xsd:string' */
        char *SOAP_ENV__Node;
        /** Optional element 'SOAP-ENV:Role' of XSD type 'xsd:string' */
        char *SOAP_ENV__Role;
        /** Optional element 'SOAP-ENV:Detail' of XSD type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *SOAP_ENV__Detail;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Fault */
        int soap_type() const { return SOAP_TYPE_SOAP_ENV__Fault; }
        /** Constructor with member initializations */
        SOAP_ENV__Fault()
        {
          faultcode = (char *)0;
          faultstring = (char *)0;
          faultactor = (char *)0;
          detail = (struct SOAP_ENV__Detail *)0;
          SOAP_ENV__Code = (struct SOAP_ENV__Code *)0;
          SOAP_ENV__Reason = (struct SOAP_ENV__Reason *)0;
          SOAP_ENV__Node = (char *)0;
          SOAP_ENV__Role = (char *)0;
          SOAP_ENV__Detail = (struct SOAP_ENV__Detail *)0;
        }
        /** Friend allocator used by soap_new_SOAP_ENV__Fault(struct soap*, int) */
        friend SOAP_FMAC1 SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/


/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:9 */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:9 */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:9 */
#ifndef SOAP_TYPE_xsd_string
#define SOAP_TYPE_xsd_string (7)
typedef char *xsd_string;
#endif

/* F:\dell-pc\Documents\GitHub\MyAutomatic\WinNTKline\gSOAPverify\soap\webapi.h:10 */
#ifndef SOAP_TYPE_xsd_int
#define SOAP_TYPE_xsd_int (9)
typedef long xsd_int;
#endif

/******************************************************************************\
 *                                                                            *
 * Serializable Types                                                         *
 *                                                                            *
\******************************************************************************/


/* char has binding name 'byte' for type 'xsd:byte' */
#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif

/* int has binding name 'int' for type 'xsd:int' */
#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif

/* xsd_int has binding name 'xsd_int' for type 'xsd-int' */
#ifndef SOAP_TYPE_xsd_int
#define SOAP_TYPE_xsd_int (9)
#endif

/* long has binding name 'long' for type 'xsd:long' */
#ifndef SOAP_TYPE_long
#define SOAP_TYPE_long (8)
#endif

/* struct SOAP_ENV__Fault has binding name 'SOAP_ENV__Fault' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (27)
#endif

/* struct SOAP_ENV__Reason has binding name 'SOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (26)
#endif

/* struct SOAP_ENV__Detail has binding name 'SOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (23)
#endif

/* struct SOAP_ENV__Code has binding name 'SOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (21)
#endif

/* struct SOAP_ENV__Header has binding name 'SOAP_ENV__Header' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (20)
#endif

/* struct api__login_by_key has binding name 'api__login_by_key' for type 'api:login-by-key' */
#ifndef SOAP_TYPE_api__login_by_key
#define SOAP_TYPE_api__login_by_key (19)
#endif

/* struct api__login_by_keyResponse has binding name 'api__login_by_keyResponse' for type 'api:login-by-keyResponse' */
#ifndef SOAP_TYPE_api__login_by_keyResponse
#define SOAP_TYPE_api__login_by_keyResponse (18)
#endif

/* struct api__encrypt has binding name 'api__encrypt' for type 'api:encrypt' */
#ifndef SOAP_TYPE_api__encrypt
#define SOAP_TYPE_api__encrypt (15)
#endif

/* struct api__encryptResponse has binding name 'api__encryptResponse' for type 'api:encryptResponse' */
#ifndef SOAP_TYPE_api__encryptResponse
#define SOAP_TYPE_api__encryptResponse (14)
#endif

/* struct ArrayOfEmp2 has binding name 'ArrayOfEmp2' for type 'ArrayOfEmp2' */
#ifndef SOAP_TYPE_ArrayOfEmp2
#define SOAP_TYPE_ArrayOfEmp2 (11)
#endif

/* struct api__result has binding name 'api__result' for type 'api:result' */
#ifndef SOAP_TYPE_api__result
#define SOAP_TYPE_api__result (10)
#endif

/* struct SOAP_ENV__Reason * has binding name 'PointerToSOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (29)
#endif

/* struct SOAP_ENV__Detail * has binding name 'PointerToSOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (28)
#endif

/* struct SOAP_ENV__Code * has binding name 'PointerToSOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (22)
#endif

/* char ** has binding name 'PointerTostring' for type 'xsd:string' */
#ifndef SOAP_TYPE_PointerTostring
#define SOAP_TYPE_PointerTostring (12)
#endif

/* xsd_string has binding name 'xsd_string' for type 'xsd-string' */
#ifndef SOAP_TYPE_xsd_string
#define SOAP_TYPE_xsd_string (7)
#endif

/* _XML has binding name '_XML' for type '' */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
#endif

/* _QName has binding name '_QName' for type 'xsd:QName' */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
#endif

/* char * has binding name 'string' for type 'xsd:string' */
#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stub Functions                                            *
 *                                                                            *
\******************************************************************************/

    SOAP_FMAC5 int SOAP_FMAC6 soap_call_api__encrypt(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *in, char **out);
    SOAP_FMAC5 int SOAP_FMAC6 soap_call_api__login_by_key(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *usr, char *psw, struct ArrayOfEmp2 &ccc);

/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
\******************************************************************************/

    /** Web service operation 'api__encrypt' (returns SOAP_OK or error code) */
    SOAP_FMAC5 int SOAP_FMAC6 api__encrypt(struct soap*, char *in, char **out);
    /** Web service operation 'api__login_by_key' (returns SOAP_OK or error code) */
    SOAP_FMAC5 int SOAP_FMAC6 api__login_by_key(struct soap*, char *usr, char *psw, struct ArrayOfEmp2 &ccc);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_api__encrypt(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_api__login_by_key(struct soap*);

#endif

/* End of soapStub.h */
