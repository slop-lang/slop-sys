#ifndef SLOP_n3_H
#define SLOP_n3_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_common.h"
#include "slop_ttl.h"
#include "slop_file.h"
#include "slop_strlib.h"

typedef struct slop_rdf_n3_Formula slop_rdf_n3_Formula;
typedef struct slop_rdf_n3_QuickVar slop_rdf_n3_QuickVar;
typedef struct slop_rdf_n3_N3Term slop_rdf_n3_N3Term;
typedef struct slop_rdf_n3_N3Triple slop_rdf_n3_N3Triple;
typedef struct slop_rdf_n3_N3Graph slop_rdf_n3_N3Graph;
typedef struct slop_rdf_n3_N3ParseContext slop_rdf_n3_N3ParseContext;
typedef struct slop_rdf_n3_GenFormulaResult slop_rdf_n3_GenFormulaResult;
typedef struct slop_rdf_n3_N3TermResult slop_rdf_n3_N3TermResult;
typedef struct slop_rdf_n3_FormulaResult slop_rdf_n3_FormulaResult;
typedef struct slop_rdf_n3_N3TripleResult slop_rdf_n3_N3TripleResult;
typedef struct slop_rdf_n3_N3FileError slop_rdf_n3_N3FileError;

typedef int64_t slop_rdf_n3_FormulaId;

static inline slop_rdf_n3_FormulaId slop_rdf_n3_FormulaId_new(int64_t v) {
return SLOP_RANGE(slop_rdf_n3_FormulaId, v, 1, 0, 0, 0, "FormulaId (Int 0 ..)");
}

struct slop_rdf_n3_Formula {
    slop_rdf_n3_FormulaId id;
    slop_rdf_rdf_Graph graph;
};
typedef struct slop_rdf_n3_Formula slop_rdf_n3_Formula;

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULA_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULA_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_Formula, slop_option_slop_rdf_n3_Formula)
#endif

#ifndef SLOP_LIST_SLOP_RDF_N3_FORMULA_DEFINED
#define SLOP_LIST_SLOP_RDF_N3_FORMULA_DEFINED
#define SLOP_LIST_SLOP_RDF_N3_FORMULA_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_n3_Formula, slop_list_slop_rdf_n3_Formula)
#endif

struct slop_rdf_n3_QuickVar {
    slop_string name;
};
typedef struct slop_rdf_n3_QuickVar slop_rdf_n3_QuickVar;

#ifndef SLOP_OPTION_SLOP_RDF_N3_QUICKVAR_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_QUICKVAR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_QuickVar, slop_option_slop_rdf_n3_QuickVar)
#endif

typedef enum {
    slop_rdf_n3_N3Term_n3_rdf,
    slop_rdf_n3_N3Term_n3_formula,
    slop_rdf_n3_N3Term_n3_quick_var
} slop_rdf_n3_N3Term_tag;

struct slop_rdf_n3_N3Term {
    slop_rdf_n3_N3Term_tag tag;
    union {
        slop_rdf_rdf_Term n3_rdf;
        slop_rdf_n3_Formula n3_formula;
        slop_rdf_n3_QuickVar n3_quick_var;
    } data;
};
typedef struct slop_rdf_n3_N3Term slop_rdf_n3_N3Term;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Term, slop_option_slop_rdf_n3_N3Term)
#endif

struct slop_rdf_n3_N3Triple {
    slop_rdf_n3_N3Term subject;
    slop_rdf_n3_N3Term predicate;
    slop_rdf_n3_N3Term object;
};
typedef struct slop_rdf_n3_N3Triple slop_rdf_n3_N3Triple;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Triple, slop_option_slop_rdf_n3_N3Triple)
#endif

#ifndef SLOP_LIST_SLOP_RDF_N3_N3TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_N3_N3TRIPLE_DEFINED
#define SLOP_LIST_SLOP_RDF_N3_N3TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(slop_rdf_n3_N3Triple, slop_list_slop_rdf_n3_N3Triple)
#endif

struct slop_rdf_n3_N3Graph {
    slop_list_slop_rdf_n3_N3Triple triples;
    slop_list_slop_rdf_n3_Formula formulas;
    int64_t size;
};
typedef struct slop_rdf_n3_N3Graph slop_rdf_n3_N3Graph;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3GRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3GRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Graph, slop_option_slop_rdf_n3_N3Graph)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULAID_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULAID_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_FormulaId, slop_option_slop_rdf_n3_FormulaId)
#endif

struct slop_rdf_n3_N3ParseContext {
    slop_rdf_ttl_TtlParseContext ttl_ctx;
    slop_rdf_n3_FormulaId formula_counter;
    uint8_t in_formula;
    slop_option_slop_rdf_n3_FormulaId current_formula_id;
};
typedef struct slop_rdf_n3_N3ParseContext slop_rdf_n3_N3ParseContext;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3PARSECONTEXT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3PARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3ParseContext, slop_option_slop_rdf_n3_N3ParseContext)
#endif

struct slop_rdf_n3_GenFormulaResult {
    slop_rdf_n3_FormulaId id;
    slop_rdf_n3_N3ParseContext ctx;
};
typedef struct slop_rdf_n3_GenFormulaResult slop_rdf_n3_GenFormulaResult;

#ifndef SLOP_OPTION_SLOP_RDF_N3_GENFORMULARESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_GENFORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_GenFormulaResult, slop_option_slop_rdf_n3_GenFormulaResult)
#endif

struct slop_rdf_n3_N3TermResult {
    slop_rdf_n3_N3Term term;
    slop_rdf_n3_N3ParseContext ctx;
};
typedef struct slop_rdf_n3_N3TermResult slop_rdf_n3_N3TermResult;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TERMRESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3TermResult, slop_option_slop_rdf_n3_N3TermResult)
#endif

struct slop_rdf_n3_FormulaResult {
    slop_rdf_n3_Formula formula;
    slop_rdf_n3_N3ParseContext ctx;
};
typedef struct slop_rdf_n3_FormulaResult slop_rdf_n3_FormulaResult;

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULARESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_FormulaResult, slop_option_slop_rdf_n3_FormulaResult)
#endif

struct slop_rdf_n3_N3TripleResult {
    slop_rdf_n3_N3Triple triple;
    slop_rdf_n3_N3ParseContext ctx;
};
typedef struct slop_rdf_n3_N3TripleResult slop_rdf_n3_N3TripleResult;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TRIPLERESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3TripleResult, slop_option_slop_rdf_n3_N3TripleResult)
#endif

typedef enum {
    slop_rdf_n3_N3FileError_n3_parse_error,
    slop_rdf_n3_N3FileError_n3_file_error
} slop_rdf_n3_N3FileError_tag;

struct slop_rdf_n3_N3FileError {
    slop_rdf_n3_N3FileError_tag tag;
    union {
        slop_rdf_common_ParseError n3_parse_error;
        std_file_FileError n3_file_error;
    } data;
};
typedef struct slop_rdf_n3_N3FileError slop_rdf_n3_N3FileError;

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3FileError, slop_option_slop_rdf_n3_N3FileError)
#endif

#ifndef SLOP_RESULT_SLOP_RDF_N3_N3TERMRESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_N3_N3TERMRESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_n3_N3TermResult ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_n3_N3TermResult_slop_rdf_common_ParseError;
#endif

#ifndef SLOP_RESULT_SLOP_RDF_N3_FORMULARESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_N3_FORMULARESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_n3_FormulaResult ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_n3_FormulaResult_slop_rdf_common_ParseError;
#endif

#ifndef SLOP_RESULT_SLOP_RDF_N3_N3TRIPLERESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_N3_N3TRIPLERESULT_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_n3_N3TripleResult ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_n3_N3TripleResult_slop_rdf_common_ParseError;
#endif

#ifndef SLOP_RESULT_SLOP_RDF_N3_N3GRAPH_SLOP_RDF_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_N3_N3GRAPH_SLOP_RDF_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_n3_N3Graph ok; slop_rdf_common_ParseError err; } data; } slop_result_slop_rdf_n3_N3Graph_slop_rdf_common_ParseError;
#endif

#ifndef SLOP_RESULT_SLOP_RDF_N3_N3GRAPH_SLOP_RDF_N3_N3FILEERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_N3_N3GRAPH_SLOP_RDF_N3_N3FILEERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_n3_N3Graph ok; slop_rdf_n3_N3FileError err; } data; } slop_result_slop_rdf_n3_N3Graph_slop_rdf_n3_N3FileError;
#endif

slop_rdf_n3_N3ParseContext slop_rdf_n3_make_n3_context(slop_arena* arena, slop_string input);
slop_rdf_n3_GenFormulaResult slop_rdf_n3_context_gen_formula_id(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
slop_rdf_n3_N3ParseContext slop_rdf_n3_context_enter_formula(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx, slop_rdf_n3_FormulaId formula_id);
slop_rdf_n3_N3ParseContext slop_rdf_n3_context_exit_formula(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
uint8_t slop_rdf_n3_is_formula_start(uint8_t c);
uint8_t slop_rdf_n3_is_formula_end(uint8_t c);
uint8_t slop_rdf_n3_is_path_operator(uint8_t c);
uint8_t slop_rdf_n3_is_quick_var_start(uint8_t c);
slop_result_slop_rdf_n3_N3TermResult_slop_rdf_common_ParseError slop_rdf_n3_parse_quick_variable(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
slop_result_slop_rdf_n3_FormulaResult_slop_rdf_common_ParseError slop_rdf_n3_parse_formula(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
slop_result_slop_rdf_n3_N3TermResult_slop_rdf_common_ParseError slop_rdf_n3_parse_path_expression(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx, slop_rdf_n3_N3Term base);
slop_result_slop_rdf_n3_N3TermResult_slop_rdf_common_ParseError slop_rdf_n3_parse_n3_term(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
slop_result_slop_rdf_n3_N3TripleResult_slop_rdf_common_ParseError slop_rdf_n3_parse_n3_triple(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
uint8_t slop_rdf_n3_is_implication_predicate(slop_rdf_n3_N3Term term);
uint8_t slop_rdf_n3_is_reverse_implication_predicate(slop_rdf_n3_N3Term term);
uint8_t slop_rdf_n3_is_equivalence_predicate(slop_rdf_n3_N3Term term);
slop_result_slop_rdf_n3_N3TripleResult_slop_rdf_common_ParseError slop_rdf_n3_parse_implication(slop_arena* arena, slop_rdf_n3_N3ParseContext ctx);
slop_rdf_rdf_Term slop_rdf_n3_make_builtin_iri(slop_arena* arena, slop_string local_name);
slop_rdf_n3_N3Graph slop_rdf_n3_make_n3_graph(slop_arena* arena);
slop_rdf_n3_N3Graph slop_rdf_n3_n3_graph_add_triple(slop_arena* arena, slop_rdf_n3_N3Graph g, slop_rdf_n3_N3Triple t);
slop_rdf_n3_N3Graph slop_rdf_n3_n3_graph_add_formula(slop_arena* arena, slop_rdf_n3_N3Graph g, slop_rdf_n3_Formula f);
slop_result_slop_rdf_n3_N3Graph_slop_rdf_common_ParseError slop_rdf_n3_parse_n3_string(slop_arena* arena, slop_string input);
slop_result_slop_rdf_n3_N3Graph_slop_rdf_n3_N3FileError slop_rdf_n3_parse_n3_file(slop_arena* arena, slop_string path);
slop_rdf_rdf_Graph slop_rdf_n3_n3_to_rdf_graph(slop_arena* arena, slop_rdf_n3_N3Graph n3g);

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULA_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULA_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_Formula, slop_option_slop_rdf_n3_Formula)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_QUICKVAR_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_QUICKVAR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_QuickVar, slop_option_slop_rdf_n3_QuickVar)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TERM_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TERM_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Term, slop_option_slop_rdf_n3_N3Term)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TRIPLE_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TRIPLE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Triple, slop_option_slop_rdf_n3_N3Triple)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3GRAPH_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3GRAPH_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3Graph, slop_option_slop_rdf_n3_N3Graph)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULAID_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULAID_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_FormulaId, slop_option_slop_rdf_n3_FormulaId)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3PARSECONTEXT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3PARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3ParseContext, slop_option_slop_rdf_n3_N3ParseContext)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_GENFORMULARESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_GENFORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_GenFormulaResult, slop_option_slop_rdf_n3_GenFormulaResult)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TERMRESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3TermResult, slop_option_slop_rdf_n3_N3TermResult)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_FORMULARESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_FORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_FormulaResult, slop_option_slop_rdf_n3_FormulaResult)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3TRIPLERESULT_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3TripleResult, slop_option_slop_rdf_n3_N3TripleResult)
#endif

#ifndef SLOP_OPTION_SLOP_RDF_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_SLOP_RDF_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_n3_N3FileError, slop_option_slop_rdf_n3_N3FileError)
#endif


#endif
