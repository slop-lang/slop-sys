#ifndef SLOP_n3_H
#define SLOP_n3_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_common.h"
#include "slop_ttl.h"
#include "slop_file.h"
#include "slop_strlib.h"

typedef struct n3_Formula n3_Formula;
typedef struct n3_QuickVar n3_QuickVar;
typedef struct n3_N3Term n3_N3Term;
typedef struct n3_N3Triple n3_N3Triple;
typedef struct n3_N3Graph n3_N3Graph;
typedef struct n3_N3ParseContext n3_N3ParseContext;
typedef struct n3_GenFormulaResult n3_GenFormulaResult;
typedef struct n3_N3TermResult n3_N3TermResult;
typedef struct n3_FormulaResult n3_FormulaResult;
typedef struct n3_N3TripleResult n3_N3TripleResult;
typedef struct n3_N3FileError n3_N3FileError;

typedef int64_t n3_FormulaId;

static inline n3_FormulaId n3_FormulaId_new(int64_t v) {
return SLOP_RANGE(n3_FormulaId, v, 1, 0, 0, 0, "FormulaId (Int 0 ..)");
}

struct n3_Formula {
    n3_FormulaId id;
    rdf_Graph graph;
};
typedef struct n3_Formula n3_Formula;

#ifndef SLOP_OPTION_N3_FORMULA_DEFINED
#define SLOP_OPTION_N3_FORMULA_DEFINED
SLOP_OPTION_DEFINE(n3_Formula, slop_option_n3_Formula)
#endif

#ifndef SLOP_LIST_N3_FORMULA_DEFINED
#define SLOP_LIST_N3_FORMULA_DEFINED
#define SLOP_LIST_N3_FORMULA_IMPL_DEFINED
SLOP_LIST_DEFINE(n3_Formula, slop_list_n3_Formula)
#endif

struct n3_QuickVar {
    slop_string name;
};
typedef struct n3_QuickVar n3_QuickVar;

#ifndef SLOP_OPTION_N3_QUICKVAR_DEFINED
#define SLOP_OPTION_N3_QUICKVAR_DEFINED
SLOP_OPTION_DEFINE(n3_QuickVar, slop_option_n3_QuickVar)
#endif

typedef enum {
    n3_N3Term_n3_rdf,
    n3_N3Term_n3_formula,
    n3_N3Term_n3_quick_var
} n3_N3Term_tag;

struct n3_N3Term {
    n3_N3Term_tag tag;
    union {
        rdf_Term n3_rdf;
        n3_Formula n3_formula;
        n3_QuickVar n3_quick_var;
    } data;
};
typedef struct n3_N3Term n3_N3Term;

#ifndef SLOP_OPTION_N3_N3TERM_DEFINED
#define SLOP_OPTION_N3_N3TERM_DEFINED
SLOP_OPTION_DEFINE(n3_N3Term, slop_option_n3_N3Term)
#endif

struct n3_N3Triple {
    n3_N3Term subject;
    n3_N3Term predicate;
    n3_N3Term object;
};
typedef struct n3_N3Triple n3_N3Triple;

#ifndef SLOP_OPTION_N3_N3TRIPLE_DEFINED
#define SLOP_OPTION_N3_N3TRIPLE_DEFINED
SLOP_OPTION_DEFINE(n3_N3Triple, slop_option_n3_N3Triple)
#endif

#ifndef SLOP_LIST_N3_N3TRIPLE_DEFINED
#define SLOP_LIST_N3_N3TRIPLE_DEFINED
#define SLOP_LIST_N3_N3TRIPLE_IMPL_DEFINED
SLOP_LIST_DEFINE(n3_N3Triple, slop_list_n3_N3Triple)
#endif

struct n3_N3Graph {
    slop_list_n3_N3Triple triples;
    slop_list_n3_Formula formulas;
    int64_t size;
};
typedef struct n3_N3Graph n3_N3Graph;

#ifndef SLOP_OPTION_N3_N3GRAPH_DEFINED
#define SLOP_OPTION_N3_N3GRAPH_DEFINED
SLOP_OPTION_DEFINE(n3_N3Graph, slop_option_n3_N3Graph)
#endif

#ifndef SLOP_OPTION_N3_FORMULAID_DEFINED
#define SLOP_OPTION_N3_FORMULAID_DEFINED
SLOP_OPTION_DEFINE(n3_FormulaId, slop_option_n3_FormulaId)
#endif

struct n3_N3ParseContext {
    ttl_TtlParseContext ttl_ctx;
    n3_FormulaId formula_counter;
    uint8_t in_formula;
    slop_option_n3_FormulaId current_formula_id;
};
typedef struct n3_N3ParseContext n3_N3ParseContext;

#ifndef SLOP_OPTION_N3_N3PARSECONTEXT_DEFINED
#define SLOP_OPTION_N3_N3PARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(n3_N3ParseContext, slop_option_n3_N3ParseContext)
#endif

struct n3_GenFormulaResult {
    n3_FormulaId id;
    n3_N3ParseContext ctx;
};
typedef struct n3_GenFormulaResult n3_GenFormulaResult;

#ifndef SLOP_OPTION_N3_GENFORMULARESULT_DEFINED
#define SLOP_OPTION_N3_GENFORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(n3_GenFormulaResult, slop_option_n3_GenFormulaResult)
#endif

struct n3_N3TermResult {
    n3_N3Term term;
    n3_N3ParseContext ctx;
};
typedef struct n3_N3TermResult n3_N3TermResult;

#ifndef SLOP_OPTION_N3_N3TERMRESULT_DEFINED
#define SLOP_OPTION_N3_N3TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(n3_N3TermResult, slop_option_n3_N3TermResult)
#endif

struct n3_FormulaResult {
    n3_Formula formula;
    n3_N3ParseContext ctx;
};
typedef struct n3_FormulaResult n3_FormulaResult;

#ifndef SLOP_OPTION_N3_FORMULARESULT_DEFINED
#define SLOP_OPTION_N3_FORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(n3_FormulaResult, slop_option_n3_FormulaResult)
#endif

struct n3_N3TripleResult {
    n3_N3Triple triple;
    n3_N3ParseContext ctx;
};
typedef struct n3_N3TripleResult n3_N3TripleResult;

#ifndef SLOP_OPTION_N3_N3TRIPLERESULT_DEFINED
#define SLOP_OPTION_N3_N3TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(n3_N3TripleResult, slop_option_n3_N3TripleResult)
#endif

typedef enum {
    n3_N3FileError_n3_parse_error,
    n3_N3FileError_n3_file_error
} n3_N3FileError_tag;

struct n3_N3FileError {
    n3_N3FileError_tag tag;
    union {
        common_ParseError n3_parse_error;
        file_FileError n3_file_error;
    } data;
};
typedef struct n3_N3FileError n3_N3FileError;

#ifndef SLOP_OPTION_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(n3_N3FileError, slop_option_n3_N3FileError)
#endif

#ifndef SLOP_RESULT_N3_N3TERMRESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_N3_N3TERMRESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { n3_N3TermResult ok; common_ParseError err; } data; } slop_result_n3_N3TermResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_N3_FORMULARESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_N3_FORMULARESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { n3_FormulaResult ok; common_ParseError err; } data; } slop_result_n3_FormulaResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_N3_N3TRIPLERESULT_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_N3_N3TRIPLERESULT_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { n3_N3TripleResult ok; common_ParseError err; } data; } slop_result_n3_N3TripleResult_common_ParseError;
#endif

#ifndef SLOP_RESULT_N3_N3GRAPH_COMMON_PARSEERROR_DEFINED
#define SLOP_RESULT_N3_N3GRAPH_COMMON_PARSEERROR_DEFINED
typedef struct { bool is_ok; union { n3_N3Graph ok; common_ParseError err; } data; } slop_result_n3_N3Graph_common_ParseError;
#endif

#ifndef SLOP_RESULT_N3_N3GRAPH_N3_N3FILEERROR_DEFINED
#define SLOP_RESULT_N3_N3GRAPH_N3_N3FILEERROR_DEFINED
typedef struct { bool is_ok; union { n3_N3Graph ok; n3_N3FileError err; } data; } slop_result_n3_N3Graph_n3_N3FileError;
#endif

n3_N3ParseContext n3_make_n3_context(slop_arena* arena, slop_string input);
n3_GenFormulaResult n3_context_gen_formula_id(slop_arena* arena, n3_N3ParseContext ctx);
n3_N3ParseContext n3_context_enter_formula(slop_arena* arena, n3_N3ParseContext ctx, n3_FormulaId formula_id);
n3_N3ParseContext n3_context_exit_formula(slop_arena* arena, n3_N3ParseContext ctx);
uint8_t n3_is_formula_start(uint8_t c);
uint8_t n3_is_formula_end(uint8_t c);
uint8_t n3_is_path_operator(uint8_t c);
uint8_t n3_is_quick_var_start(uint8_t c);
slop_result_n3_N3TermResult_common_ParseError n3_parse_quick_variable(slop_arena* arena, n3_N3ParseContext ctx);
slop_result_n3_FormulaResult_common_ParseError n3_parse_formula(slop_arena* arena, n3_N3ParseContext ctx);
slop_result_n3_N3TermResult_common_ParseError n3_parse_path_expression(slop_arena* arena, n3_N3ParseContext ctx, n3_N3Term base);
slop_result_n3_N3TermResult_common_ParseError n3_parse_n3_term(slop_arena* arena, n3_N3ParseContext ctx);
slop_result_n3_N3TripleResult_common_ParseError n3_parse_n3_triple(slop_arena* arena, n3_N3ParseContext ctx);
uint8_t n3_is_implication_predicate(n3_N3Term term);
uint8_t n3_is_reverse_implication_predicate(n3_N3Term term);
uint8_t n3_is_equivalence_predicate(n3_N3Term term);
slop_result_n3_N3TripleResult_common_ParseError n3_parse_implication(slop_arena* arena, n3_N3ParseContext ctx);
rdf_Term n3_make_builtin_iri(slop_arena* arena, slop_string local_name);
n3_N3Graph n3_make_n3_graph(slop_arena* arena);
n3_N3Graph n3_n3_graph_add_triple(slop_arena* arena, n3_N3Graph g, n3_N3Triple t);
n3_N3Graph n3_n3_graph_add_formula(slop_arena* arena, n3_N3Graph g, n3_Formula f);
slop_result_n3_N3Graph_common_ParseError n3_parse_n3_string(slop_arena* arena, slop_string input);
slop_result_n3_N3Graph_n3_N3FileError n3_parse_n3_file(slop_arena* arena, slop_string path);
rdf_Graph n3_n3_to_rdf_graph(slop_arena* arena, n3_N3Graph n3g);

#ifndef SLOP_OPTION_N3_FORMULA_DEFINED
#define SLOP_OPTION_N3_FORMULA_DEFINED
SLOP_OPTION_DEFINE(n3_Formula, slop_option_n3_Formula)
#endif

#ifndef SLOP_OPTION_N3_QUICKVAR_DEFINED
#define SLOP_OPTION_N3_QUICKVAR_DEFINED
SLOP_OPTION_DEFINE(n3_QuickVar, slop_option_n3_QuickVar)
#endif

#ifndef SLOP_OPTION_N3_N3TERM_DEFINED
#define SLOP_OPTION_N3_N3TERM_DEFINED
SLOP_OPTION_DEFINE(n3_N3Term, slop_option_n3_N3Term)
#endif

#ifndef SLOP_OPTION_N3_N3TRIPLE_DEFINED
#define SLOP_OPTION_N3_N3TRIPLE_DEFINED
SLOP_OPTION_DEFINE(n3_N3Triple, slop_option_n3_N3Triple)
#endif

#ifndef SLOP_OPTION_N3_N3GRAPH_DEFINED
#define SLOP_OPTION_N3_N3GRAPH_DEFINED
SLOP_OPTION_DEFINE(n3_N3Graph, slop_option_n3_N3Graph)
#endif

#ifndef SLOP_OPTION_N3_FORMULAID_DEFINED
#define SLOP_OPTION_N3_FORMULAID_DEFINED
SLOP_OPTION_DEFINE(n3_FormulaId, slop_option_n3_FormulaId)
#endif

#ifndef SLOP_OPTION_N3_N3PARSECONTEXT_DEFINED
#define SLOP_OPTION_N3_N3PARSECONTEXT_DEFINED
SLOP_OPTION_DEFINE(n3_N3ParseContext, slop_option_n3_N3ParseContext)
#endif

#ifndef SLOP_OPTION_N3_GENFORMULARESULT_DEFINED
#define SLOP_OPTION_N3_GENFORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(n3_GenFormulaResult, slop_option_n3_GenFormulaResult)
#endif

#ifndef SLOP_OPTION_N3_N3TERMRESULT_DEFINED
#define SLOP_OPTION_N3_N3TERMRESULT_DEFINED
SLOP_OPTION_DEFINE(n3_N3TermResult, slop_option_n3_N3TermResult)
#endif

#ifndef SLOP_OPTION_N3_FORMULARESULT_DEFINED
#define SLOP_OPTION_N3_FORMULARESULT_DEFINED
SLOP_OPTION_DEFINE(n3_FormulaResult, slop_option_n3_FormulaResult)
#endif

#ifndef SLOP_OPTION_N3_N3TRIPLERESULT_DEFINED
#define SLOP_OPTION_N3_N3TRIPLERESULT_DEFINED
SLOP_OPTION_DEFINE(n3_N3TripleResult, slop_option_n3_N3TripleResult)
#endif

#ifndef SLOP_OPTION_N3_N3FILEERROR_DEFINED
#define SLOP_OPTION_N3_N3FILEERROR_DEFINED
SLOP_OPTION_DEFINE(n3_N3FileError, slop_option_n3_N3FileError)
#endif


#endif
