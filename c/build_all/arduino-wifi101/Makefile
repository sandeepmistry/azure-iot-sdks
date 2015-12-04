# Copyright (c) Microsoft. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

ROOT_C_DIR                = ../..
COMMON_DIR                = $(ROOT_C_DIR)/common
COMMON_SRC_DIR            = $(COMMON_DIR)/src
SERIALIZER_DIR            = $(ROOT_C_DIR)/serializer
SERIALIZER_SRC_DIR        = $(SERIALIZER_DIR)/src
SERIALIZER_SAMPLES_DIR    = $(SERIALIZER_DIR)/samples
IOTHUB_CLIENT_DIR         = $(ROOT_C_DIR)/iothub_client
IOTHUB_CLIENT_SRC_DIR     = $(IOTHUB_CLIENT_DIR)/src
IOTHUB_CLIENT_SAMPLES_DIR = $(IOTHUB_CLIENT_DIR)/samples

COMMON_SRC = \
	$(COMMON_SRC_DIR)/base64.c \
	$(COMMON_SRC_DIR)/buffer.c \
	$(COMMON_SRC_DIR)/certs.c \
	$(COMMON_SRC_DIR)/crt_abstractions.c \
	$(COMMON_SRC_DIR)/doublylinkedlist.c \
	$(COMMON_SRC_DIR)/gballoc.c \
	$(COMMON_SRC_DIR)/hmac.c \
	$(COMMON_SRC_DIR)/hmacsha256.c \
	$(COMMON_SRC_DIR)/httpapiex.c \
	$(COMMON_SRC_DIR)/httpapiexsas.c \
	$(COMMON_SRC_DIR)/httpheaders.c \
	$(COMMON_SRC_DIR)/map.c \
	$(COMMON_SRC_DIR)/sastoken.c \
	$(COMMON_SRC_DIR)/sha1.c \
	$(COMMON_SRC_DIR)/sha224.c \
	$(COMMON_SRC_DIR)/sha384-512.c \
	$(COMMON_SRC_DIR)/string_tokenizer.c \
	$(COMMON_SRC_DIR)/strings.c \
	$(COMMON_SRC_DIR)/urlencode.c \
	$(COMMON_SRC_DIR)/usha.c \
	$(COMMON_SRC_DIR)/vector.c

SERIALIZER_SRC = \
	$(SERIALIZER_SRC_DIR)/agenttypesystem.c \
	$(SERIALIZER_SRC_DIR)/codefirst.c \
	$(SERIALIZER_SRC_DIR)/commanddecoder.c \
	$(SERIALIZER_SRC_DIR)/datamarshaller.c \
	$(SERIALIZER_SRC_DIR)/datapublisher.c \
	$(SERIALIZER_SRC_DIR)/dataserializer.c \
	$(SERIALIZER_SRC_DIR)/iotdevice.c \
	$(SERIALIZER_SRC_DIR)/jsondecoder.c \
	$(SERIALIZER_SRC_DIR)/jsonencoder.c \
	$(SERIALIZER_SRC_DIR)/multitree.c \
	$(SERIALIZER_SRC_DIR)/schema.c \
	$(SERIALIZER_SRC_DIR)/schemalib.c \
	$(SERIALIZER_SRC_DIR)/schemaserializer.c

IOTHUB_CLIENT_SRC = \
	$(IOTHUB_CLIENT_SRC_DIR)/iothub_client.c \
	$(IOTHUB_CLIENT_SRC_DIR)/iothub_client_ll.c \
	$(IOTHUB_CLIENT_SRC_DIR)/iothub_message.c \
	$(IOTHUB_CLIENT_SRC_DIR)/iothubtransporthttp.c \
	$(IOTHUB_CLIENT_SRC_DIR)/version.c

LIB_SRC = \
	$(COMMON_SRC) \
	$(SERIALIZER_SRC) \
	$(IOTHUB_CLIENT_SRC)

LIB_HEADERS = \
	$(COMMON_DIR)/inc/*.h \
	$(SERIALIZER_DIR)/inc/*.h \
	$(IOTHUB_CLIENT_DIR)/inc/*.h \

LIB_DIR          = AzureIoT
LIB_SRC_DIR      = ${LIB_DIR}/src
LIB_EXAMPLES_DIR = ${LIB_DIR}/examples
LIB_SRC_SDK_DIR  = ${LIB_SRC_DIR}/sdk

default_target: all

sdk: $(LIB_SRC) $(LIB_HEADERS)
	cp $(LIB_SRC) $(LIB_SRC_SDK_DIR)
	cp $(LIB_HEADERS) $(LIB_SRC_SDK_DIR)

examples:
	cp $(SERIALIZER_SAMPLES_DIR)/simplesample_http/simplesample_http.h $(LIB_EXAMPLES_DIR)/serializer/simplesample_http/.
	cp $(SERIALIZER_SAMPLES_DIR)/simplesample_http/simplesample_http.c $(LIB_EXAMPLES_DIR)/serializer/simplesample_http/.
	cp $(IOTHUB_CLIENT_SAMPLES_DIR)/iothub_client_sample_http/iothub_client_sample_http.h $(LIB_EXAMPLES_DIR)/iothub_client/iothub_client_sample_http/.
	cp $(IOTHUB_CLIENT_SAMPLES_DIR)/iothub_client_sample_http/iothub_client_sample_http.c $(LIB_EXAMPLES_DIR)/iothub_client/iothub_client_sample_http/.


$(LIBAZUREIOT): $(COMMON_OBJ) $(SERIALIZER_OBJ) $(IOTHUB_CLIENT_OBJ)
	$(AR) rcs $@ $^

all: sdk examples
