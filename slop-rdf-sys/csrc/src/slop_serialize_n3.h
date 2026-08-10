#ifndef SLOP_serialize_n3_H
#define SLOP_serialize_n3_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_ttl.h"
#include "slop_n3.h"
#include "slop_serialize_ttl.h"
#include "slop_file.h"
#include "slop_strlib.h"

typedef struct serialize_n3_N3FileError serialize_n3_N3FileError;

typedef enum {
    serialize_n3_N3FileError_n3_serialize_error,
    serialize_n3_N3FileError_n3_file_error
} serialize_n3_N3FileError_tag;

struct serialize_n3_N3FileError {
    serialize_n3_N3FileError_tag tag;
    union {
        serialize_ttl_SerializeError n3_serialize_error;
        file_FileError n3_file_error;
    } data;
};
typedef struct serialize_n3_N3FileError serialize_n3_N3FileError;

#ifndef SLOP_OPTION_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_n3_N3FileError, slop_option_serialize_n3_N3FileError)
#endif

#ifndef SLOP_RESULT_U8_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_RESULT_U8_SERIALIZE_N3_N3FILEERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; serialize_n3_N3FileError err; } data; } slop_result_u8_serialize_n3_N3FileError;
#endif

slop_string serialize_n3_serialize_quick_var(slop_arena* arena, n3_QuickVar var);
slop_string serialize_n3_serialize_formula(slop_arena* arena, n3_Formula f, ttl_PrefixMap prefixes);
slop_string serialize_n3_serialize_n3_term(slop_arena* arena, n3_N3Term t, ttl_PrefixMap prefixes);
slop_string serialize_n3_serialize_n3_string(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config);
slop_result_u8_serialize_n3_N3FileError serialize_n3_serialize_n3_file(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config, slop_string path);

#ifndef SLOP_OPTION_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SERIALIZE_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(serialize_n3_N3FileError, slop_option_serialize_n3_N3FileError)
#endif


#endif
