/*
 * Copyright (c) 2001-2017 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/* 
 * Modification History
 *
 * November 1, 2001	Dieter Siegmund (dieter@apple.com)
 * - created
 */

#ifndef _EAP8021X_EAPCLIENTPLUGIN_H
#define _EAP8021X_EAPCLIENTPLUGIN_H

#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFString.h>
#include <EAP8021X/EAP.h>
#include <EAP8021X/EAPClientTypes.h>
#include <Security/SecIdentity.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t EAPClientPluginVersion;

/*
 * Constant: kEAPClientPluginVersion
 * Purpose:
 *   The version of this header file.  Plug-ins that correspond
 *   to this version must return kEAPClientPluginTypesVersion
 *   in their "version" function (see below).
 */
#define kEAPClientPluginVersion		((EAPClientPluginVersion)1)

typedef void * EAPClientPluginPrivateData;

enum {
    kEAPClientStateAuthenticating = 0,
    kEAPClientStateSuccess = 1,
    kEAPClientStateFailure = 2,
};
typedef uint32_t EAPClientState;

typedef void * (*EAPClientPluginFuncRef)();

typedef const char * EAPClientPluginFuncName;

/*
 * Type: EAPClientPluginData, EAPClientPluginDataRef
 * Purpose:
 *   Structure to hold EAP client information, supplied by caller.
 * Fields:
 *   private
 *     used by the plug-in to store private data.
 *   mtu
 *     Value is the MTU of the underlying hardware minus
 *     the framing overhead.  The size of frames generated by the client 
 *     "process" function (see below)  must not exceed this value.
 *  unique_id, unique_id_length
 *     A sequence of bytes that uniquely identifies this instance,
 *     used for TLS session resumption.
 */
typedef struct EAPClientPluginData_s {
    /* for plug-in use: */
    EAPClientPluginPrivateData	private;

    /* remaining fields are read-only: */
    const bool			log_enabled;
    const uint32_t		log_level;
    const uint32_t		mtu;
    const uint32_t		generation; /* changed when user updates */

    const void *		unique_id;/* used for TLS session resumption */
    const uint32_t		unique_id_length;

    const uint8_t *		username;
    const uint32_t		username_length;

    CFDataRef			encryptedEAPIdentity; /* used for privacy protection in EAP-SIM and EAP-AKA */

    const uint8_t *		password; 	/* may be NULL */
    const uint32_t		password_length;

    const CFDictionaryRef	properties;	/* may be NULL */

    const bool			system_mode;

    SecIdentityRef		sec_identity;	/* may be NULL */

    const void *		reserved[6];	/* reserved, don't use */
} EAPClientPluginData, *EAPClientPluginDataRef;

/*
 * Constants: kEAPClientPluginFuncName*
 * Purpose:
 *   Definitions for the constants passed to the "introspect" function
 *   to retrieve the corresponding functions.
 * Note:
 *   If the "introspect" function wants to advertise
 *   itself for use beyond load time, it should 
 *   return its function pointer when queried for that function name.
 */
#define kEAPClientPluginFuncNameIntrospect	"introspect"
#define kEAPClientPluginFuncNameVersion		"version"
#define kEAPClientPluginFuncNameEAPType		"eap_type"
#define kEAPClientPluginFuncNameEAPName		"eap_name"
#define kEAPClientPluginFuncNameInit		"init"
#define kEAPClientPluginFuncNameFree		"free"
#define kEAPClientPluginFuncNameProcess		"process"
#define kEAPClientPluginFuncNameFreePacket	"free_packet"
#define kEAPClientPluginFuncNameFailureString	"failure_string"
#define kEAPClientPluginFuncNameSessionKey	"session_key"
#define kEAPClientPluginFuncNameServerKey	"server_key"
#define kEAPClientPluginFuncNameMasterSessionKeyCopyBytes	\
    "master_session_key_copy_bytes"
#define kEAPClientPluginFuncNameRequireProperties	"require_properties"
#define kEAPClientPluginFuncNamePublishProperties	"publish_properties"
#define kEAPClientPluginFuncNamePacketDump	"packet_dump"
#define kEAPClientPluginFuncNameUserName	"user_name"
#define kEAPClientPluginFuncNameCopyIdentity 	"copy_identity"
#define kEAPClientPluginFuncNameCopyPacketDescription "copy_packet_description"

/*
 * Type: EAPClientPluginFuncIntrospect
 * Purpose:
 *   Prototype for the "introspect" function.
 *
 *   This function is used to get the address of the given
 *   function name.
 *
 *   A loadable module must supply a public entry point called
 *   introspect().
 *
 *   For a built-in modules, the address of the introspect() function
 *   is passed as an argument to EAPClientModuleAddBuiltin().

 * Returns:
 *   The corresponding function pointer if one is defined, NULL otherwise.
 */
typedef EAPClientPluginFuncRef
(EAPClientPluginFuncIntrospect)(EAPClientPluginFuncName name);

/*
 * Type: EAPClientPluginFuncVersion
 * Purpose:
 *   Prototype for the "version" function.
 *
 * Returns:
 *   The version of this plugin.  Must return kEAPClientPluginVersion.
 */
typedef EAPClientPluginVersion (EAPClientPluginFuncVersion)(void);

/*
 * Type: EAPClientPluginFuncEAPType
 * Purpose:
 *   Prototype for the "eap_type" function.
 *
 * Returns:
 *   The EAPType of this plugin.
 */
typedef EAPType (EAPClientPluginFuncEAPType)(void);

/*
 * Type: EAPClientPluginFuncType
 * Purpose:
 *   Prototype for the "eap_name" function.
 *
 * Returns:
 *   The name of the EAP type provided by this plug-in.
 */
typedef const char * (EAPClientPluginFuncEAPName)(void);

/*
 * Type: EAPClientPluginFuncInit
 * Purpose:
 *   Prototype for the "init" function.
 *
 *   This function allows the EAPClientPlugin to allocate/initialize a 
 *   private data structure to store context across calls.  The plugin
 *   may store persistent information in the "private" field of the
 *   plugin structure.  However, it must not do so unless it returns
 *   kEAPClientStatusOK.
 *
 * Returns:
 *   kEAPClientStatusOK if successful.
 *   kEAPClientStatusConfigurationIncomplete if initialization failed
 *   due to incomplete configuration; also returns the name(s) of the
 *   missing properties in the CFArray[CFString] require_props.
 *   
 * Note:
 *   The value of error is only meaningful if the returned status is 
 *   >= kEAPClientStatusDomainSpecificErrorStart.
 */
typedef EAPClientStatus
(EAPClientPluginFuncInit)(EAPClientPluginDataRef plugin,
			  CFArrayRef * require_props,
			  EAPClientDomainSpecificError * error);

/*
 * Type: EAPClientPluginFuncFree
 * Purpose:
 *   Prototype for the "free" function.
 *
 *   This function frees the private data structure allocated via the
 *   "init" function, if it allocated any.
 */
typedef void (EAPClientPluginFuncFree)(EAPClientPluginDataRef plugin);

/*
 * Type: EAPClientPluginFuncProcess
 * Purpose:
 *   Prototype for the "process" function.
 *
 *   This function takes an input EAP packet, returns its current state,
 *   and produces an optional output EAP packet to be delivered to the
 *   Authenticator.
 *   
 *   If the value of *out_pkt_p is not NULL, it will be delivered to the
 *   Authenticator.  Once delivered, the "free_packet" function is called
 *   on *out_pkt_p.  The size of the packet pointed to by *out_pkt_p must 
 *   be less than or equal to the "mtu" value (see "init" above).  That is:
 *   	(*out_pkt_p)->length <= mtu
 *   must be true.
 *
 *   If the return value is kEAPClientStateAuthenticating,
 *   further calls to "process" will be made as relevant packets arrive.
 *
 *   If the return value is kEAPClientStateSuccess,
 *   authentication is complete.
 * 
 *   If the return value is kEAPClientStateFailure, authentication
 *   has failed, or some other unrecoverable error has occurred.
 *   
 *   kEAPClientStatusConfigurationIncomplete if initialization failed
 * Returns:
 *   The current plugin state, status, and possibly a domain-specific error.
 */
typedef EAPClientState
(EAPClientPluginFuncProcess)(EAPClientPluginDataRef plugin,
			     const EAPPacketRef in_pkt,
			     EAPPacketRef * out_pkt_p,
			     EAPClientStatus * status,
			     EAPClientDomainSpecificError * error);

/*
 * Type: EAPClientPluginFuncFreePacket
 * Purpose:
 *   Prototype for the "free_packet" function.
 *
 *   This function is called to free the output packet 
 *   provided by the EAPClientPlugin's "process" function after the packet
 *   is delivered.
 */
typedef void 
(EAPClientPluginFuncFreePacket)(EAPClientPluginDataRef plugin,
				EAPPacketRef out_pkt);

/* 
 * Type: EAPClientPluginFuncFailureString
 * Purpose:
 *   Prototype for the "failure_string" function.
 *   
 *   Returns a non-NULL failure debugging string if one is available,
 *   NULL otherwise.
 *
 *   Called after the "process" function returns kEAPClientStateFailure.
 */
typedef const char * 
(EAPClientPluginFuncFailureString)(EAPClientPluginDataRef plugin);

/*
 * Type: EAPClientPluginFuncSessionKey
 * Purpose:
 *   Prototype for "session_key" retrieval function.
 *   This is the key used to encrypt data from the client to the server.
 *   Returns a non-NULL pointer to the key, and its length if a session
 *   key was generated during authentication.  Returns NULL otherwise.
 *   This pointer is not dynamically allocated, so must not be free'd.
 *
 *   Called after the "process" function returns kEAPClientStateSuccess.
 */
typedef void * 
(EAPClientPluginFuncSessionKey)(EAPClientPluginDataRef plugin, int * key_length);

/*
 * Type: EAPClientPluginFuncServerKey
 * Purpose:
 *   Prototype for "server_key" retrieval function.
 *   This is the key used to encrypt data from the server to the client.
 *   Returns a non-NULL pointer to the key, and its length if a session
 *   key was generated during authentication.  Returns NULL otherwise.
 *   This pointer is not dynamically allocated, so must not be free'd.
 *
 *   Called after the "process" function returns kEAPClientStateSuccess.
 */
typedef void * 
(EAPClientPluginFuncServerKey)(EAPClientPluginDataRef plugin, int * key_length);

/*
 * Type: EAPClientPluginFuncMasterSessionKeyCopyBytes
 * Purpose:
 *   Prototype for "master_session_key_copy_bytes" function.
 *   
 *   The buffer 'msk' must be at least kEAPMasterSessionKeyMinimumSize
 *   bytes in length. 
 *
 *   'msk_size' must be set to at least kEAPMasterSessionKeyMinimumSize.
 *   
 *   Returns the actual number of bytes that were copied, not more than
 *   'msk_size'.  Returns 0 if no MSK is available.
 *
 *   Called after the "process" function returns kEAPClientStateSuccess.
 */
typedef int
(EAPClientPluginFuncMasterSessionKeyCopyBytes)(EAPClientPluginDataRef plugin,
					       void * msk, int msk_size);

/* 
 * Type: EAPClientPluginFuncRequireProperties
 * Purpose:
 *   Prototype for the "require_properties" function.
 *   Called if the "process" function returns kEAPClientStateAuthenticating,
 *   and the client status returned is kEAPClientStatusConfigurationIncomplete.
 *
 *   Returned value must be released using CFRelease().
 *
 * Returns:
 *   A CFArray of CFString property names that the EAP method requires,
 *   NULL if none are needed.
 */
typedef CFArrayRef
(EAPClientPluginFuncRequireProperties)(EAPClientPluginDataRef plugin);

/* 
 * Type: EAPClientPluginFuncPublishProperties
 * Purpose:
 *   Prototype for the "publish_properties" function.
 *   Called anytime after the "init" function to allow the plugin to publish
 *   additional properties.
 *
 *   Returned value must be released using CFRelease().
 *
 * Returns:
 *   A CFDictionary containing key/value pairs of additional information
 *   to publish, NULL to publish no information.
 * Note:
 *   The types must be CFPropertyListRef types only.
 */
typedef CFDictionaryRef
(EAPClientPluginFuncPublishProperties)(EAPClientPluginDataRef plugin);

/* 
 * Type: EAPClientPluginFuncPacketDump
 * Purpose:
 *   Prototype for the "packet_dump" function.
 * Returns:
 *   FALSE if did not dump packet, TRUE otherwise.
 */
typedef bool
(EAPClientPluginFuncPacketDump)(FILE * out_f, const EAPPacketRef packet);

/* 
 * Type: EAPClientPluginFuncUserName
 *
 * Purpose:
 *   Prototype for the "user_name" function.
 *
 *   This entry point is called in case the user does not specify a user name
 *   to use as the identity.  The returned CFStringRef must be released
 *   using CFRelease().
 *
 * Returns:
 *   NULL if this method could not determine a user name, non-NULL CFString
 *   containing username otherwise.
 */
typedef CFStringRef
(EAPClientPluginFuncUserName)(CFDictionaryRef properties);

/* 
 * Type: EAPClientPluginFuncCopyIdentity
 *
 * Purpose:
 *   Prototype for the "copy_identity" function.
 *
 *   This function is called to determine an identity to use after the
 *   plugin is active and has a valid context.
 *
 *   The returned CFStringRef must be released using CFRelease().
 * 
 * Returns:
 *   NULL if this method could not retrieve an identity to use,
 *   non-NULL CFStringRef containing identity otherwise.
 */
typedef CFStringRef
(EAPClientPluginFuncCopyIdentity)(EAPClientPluginDataRef plugin);

/* 
 * Type: EAPClientPluginFuncCopyPacketDescription
 * Purpose:
 *   Prototype for the "copy_packet_description" function.
 * Returns:
 *   Non-NULL CFStringRef containing packet description, NULL if failed.
 */
typedef CFStringRef
(EAPClientPluginFuncCopyPacketDescription)(const EAPPacketRef packet, bool * packet_is_valid);

#endif /* _EAP8021X_EAPCLIENTPLUGIN_H */
