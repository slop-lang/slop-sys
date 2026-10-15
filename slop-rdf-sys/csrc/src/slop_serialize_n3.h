#ifndef SLOP_serialize_n3_H
#define SLOP_serialize_n3_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_ttl.h"
#include "slop_n3.h"
#include "slop_serialize_ttl.h"
#include "slop_file.h"
#include "slop_strlib.h"

typedef struct slop_rdf_serialize_n3_N3FileError slop_rdf_serialize_n3_N3FileError;

typedef enum {
    slop_rdf_serialize_n3_N3FileError_n3_serialize_error,
    slop_rdf_serialize_n3_N3FileError_n3_file_error
} slop_rdf_serialize_n3_N3FileError_tag;

struct slop_rdf_serialize_n3_N3FileError {
    slop_rdf_serialize_n3_N3FileError_tag tag;
    union {
        slop_rdf_serialize_ttl_SerializeError n3_serialize_error;
        std_file_FileError n3_file_error;
    } data;
};
typedef struct slop_rdf_serialize_n3_N3FileError slop_rdf_serialize_n3_N3FileError;

#ifndef SLOP_OPTION_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_serialize_n3_N3FileError, slop_option_slop_rdf_serialize_n3_N3FileError)
#endif

#ifndef SLOP_RESULT_U8_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_RESULT_U8_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; slop_rdf_serialize_n3_N3FileError err; } data; } slop_result_u8_slop_rdf_serialize_n3_N3FileError;
#endif

slop_string slop_rdf_serialize_n3_serialize_quick_var(slop_arena* arena, slop_rdf_n3_QuickVar var);
slop_string slop_rdf_serialize_n3_serialize_formula(slop_arena* arena, slop_rdf_n3_Formula f, slop_rdf_ttl_PrefixMap prefixes);
slop_string slop_rdf_serialize_n3_serialize_n3_term(slop_arena* arena, slop_rdf_n3_N3Term t, slop_rdf_ttl_PrefixMap prefixes);
slop_string slop_rdf_serialize_n3_serialize_n3_string(slop_arena* arena, slop_rdf_n3_N3Graph g, slop_rdf_serialize_ttl_SerializeConfig config);
slop_result_u8_slop_rdf_serialize_n3_N3FileError slop_rdf_serialize_n3_serialize_n3_file(slop_arena* arena, slop_rdf_n3_N3Graph g, slop_rdf_serialize_ttl_SerializeConfig config, slop_string path);

#ifndef SLOP_OPTION_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_SERIALIZE_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_serialize_n3_N3FileError, slop_option_slop_rdf_serialize_n3_N3FileError)
#endif


#endif
