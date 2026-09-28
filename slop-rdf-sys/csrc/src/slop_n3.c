#include "../runtime/slop_runtime.h"
#include "slop_n3.h"

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

static uint8_t _wrap_ttl_is_pn_chars(void* _env, uint8_t _p0) { return ttl_is_pn_chars(_p0); }

n3_N3ParseContext n3_make_n3_context(slop_arena* arena, slop_string input) {
    n3_N3ParseContext _retval = {0};
    _retval = ((n3_N3ParseContext){.ttl_ctx = ttl_make_ttl_context(arena, input), .formula_counter = 0, .in_formula = 0, .current_formula_id = (slop_option_n3_FormulaId){.has_value = false}});
    SLOP_POST(((_retval.formula_counter == 0)), "(== $result.formula-counter 0)");
    SLOP_POST(((_retval.in_formula == 0)), "(== $result.in-formula false)");
    return _retval;
}

n3_GenFormulaResult n3_context_gen_formula_id(slop_arena* arena, n3_N3ParseContext ctx) {
    n3_GenFormulaResult _retval = {0};
    _retval = ((n3_GenFormulaResult){.id = ctx.formula_counter, .ctx = ((n3_N3ParseContext){.ttl_ctx = ctx.ttl_ctx, .formula_counter = (ctx.formula_counter + 1), .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id})});
    SLOP_POST(((_retval.id == ctx.formula_counter)), "(== $result.id ctx.formula-counter)");
    SLOP_POST(((_retval.ctx.formula_counter == (ctx.formula_counter + 1))), "(== $result.ctx.formula-counter (+ ctx.formula-counter 1))");
    return _retval;
}

n3_N3ParseContext n3_context_enter_formula(slop_arena* arena, n3_N3ParseContext ctx, n3_FormulaId formula_id) {
    n3_N3ParseContext _retval = {0};
    _retval = ((n3_N3ParseContext){.ttl_ctx = ctx.ttl_ctx, .formula_counter = ctx.formula_counter, .in_formula = 1, .current_formula_id = (slop_option_n3_FormulaId){.has_value = 1, .value = formula_id}});
    SLOP_POST(((_retval.in_formula == 1)), "(== $result.in-formula true)");
    SLOP_POST((({ __auto_type _mv = _retval.current_formula_id; _mv.has_value ? ({ __auto_type id = _mv.value; (id == formula_id); }) : (0); })), "(match $result.current-formula-id ((some id) (== id formula-id)) ((none) false))");
    return _retval;
}

n3_N3ParseContext n3_context_exit_formula(slop_arena* arena, n3_N3ParseContext ctx) {
    SLOP_PRE(((ctx.in_formula == 1)), "(== ctx.in-formula true)");
    n3_N3ParseContext _retval = {0};
    _retval = ((n3_N3ParseContext){.ttl_ctx = ctx.ttl_ctx, .formula_counter = ctx.formula_counter, .in_formula = 0, .current_formula_id = (slop_option_n3_FormulaId){.has_value = false}});
    SLOP_POST(((_retval.in_formula == 0)), "(== $result.in-formula false)");
    SLOP_POST((({ __auto_type _mv = _retval.current_formula_id; _mv.has_value ? ({ __auto_type _ = _mv.value; 0; }) : (1); })), "(match $result.current-formula-id ((none) true) ((some _) false))");
    return _retval;
}

uint8_t n3_is_formula_start(uint8_t c) {
    return (c == 123);
}

uint8_t n3_is_formula_end(uint8_t c) {
    return (c == 125);
}

uint8_t n3_is_path_operator(uint8_t c) {
    return ((c == 33) || (c == 94));
}

uint8_t n3_is_quick_var_start(uint8_t c) {
    return (c == 63);
}

slop_result_n3_N3TermResult_common_ParseError n3_parse_quick_variable(slop_arena* arena, n3_N3ParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.ttl_ctx.state) == 63)), "(== (state-peek ctx.ttl-ctx.state) 63)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.ttl_ctx.state);
        {
            __auto_type name_result = common_parse_while(arena, s1, (slop_closure_t){(void*)_wrap_ttl_is_pn_chars, NULL});
            return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TermResult){.term = ((n3_N3Term){ .tag = n3_N3Term_n3_quick_var, .data.n3_quick_var = ((n3_QuickVar){.name = name_result.result}) }), .ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx.ttl_ctx.prefixes, .base_iri = ctx.ttl_ctx.base_iri, .blank_labels = ctx.ttl_ctx.blank_labels, .blank_counter = ctx.ttl_ctx.blank_counter, .state = name_result.state}), .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id})}) });
        }
    }
}

slop_result_n3_FormulaResult_common_ParseError n3_parse_formula(slop_arena* arena, n3_N3ParseContext ctx) {
    SLOP_PRE(((common_state_peek(ctx.ttl_ctx.state) == 123)), "(== (state-peek ctx.ttl-ctx.state) 123)");
    {
        __auto_type s1 = common_state_advance(arena, ctx.ttl_ctx.state);
        {
            __auto_type ctx1 = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx.ttl_ctx.prefixes, .base_iri = ctx.ttl_ctx.base_iri, .blank_labels = ctx.ttl_ctx.blank_labels, .blank_counter = ctx.ttl_ctx.blank_counter, .state = s1}), .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
            {
                __auto_type gen = n3_context_gen_formula_id(arena, ctx1);
                {
                    __auto_type fid = gen.id;
                    __auto_type ctx2 = n3_context_enter_formula(arena, gen.ctx, fid);
                    {
                        __auto_type g = rdf_make_graph(arena);
                        __auto_type cur_ctx = ctx2;
                        {
                            __auto_type s = common_skip_whitespace(arena, cur_ctx.ttl_ctx.state);
                            cur_ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.ttl_ctx.prefixes, .base_iri = cur_ctx.ttl_ctx.base_iri, .blank_labels = cur_ctx.ttl_ctx.blank_labels, .blank_counter = cur_ctx.ttl_ctx.blank_counter, .state = s}), .formula_counter = cur_ctx.formula_counter, .in_formula = cur_ctx.in_formula, .current_formula_id = cur_ctx.current_formula_id});
                            while (!(n3_is_formula_end(common_state_peek(cur_ctx.ttl_ctx.state)))) {
                                {
                                    __auto_type triple_result = n3_parse_n3_triple(arena, cur_ctx);
                                    __auto_type _mv_46 = triple_result;
                                    if (_mv_46.is_ok) {
                                        __auto_type tr = _mv_46.data.ok;
                                        cur_ctx = tr.ctx;
                                        {
                                            __auto_type s2 = common_skip_whitespace(arena, cur_ctx.ttl_ctx.state);
                                            cur_ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = cur_ctx.ttl_ctx.prefixes, .base_iri = cur_ctx.ttl_ctx.base_iri, .blank_labels = cur_ctx.ttl_ctx.blank_labels, .blank_counter = cur_ctx.ttl_ctx.blank_counter, .state = s2}), .formula_counter = cur_ctx.formula_counter, .in_formula = cur_ctx.in_formula, .current_formula_id = cur_ctx.current_formula_id});
                                        }
                                    } else if (!_mv_46.is_ok) {
                                        __auto_type e = _mv_46.data.err;
                                        return ((slop_result_n3_FormulaResult_common_ParseError){ .is_ok = false, .data.err = e });
                                        /* empty list */;
                                    }
                                }
                            }
                            {
                                __auto_type s3 = common_state_advance(arena, cur_ctx.ttl_ctx.state);
                                {
                                    __auto_type ctx3 = n3_context_exit_formula(arena, cur_ctx);
                                    return ((slop_result_n3_FormulaResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_FormulaResult){.formula = ((n3_Formula){.id = fid, .graph = g}), .ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx3.ttl_ctx.prefixes, .base_iri = ctx3.ttl_ctx.base_iri, .blank_labels = ctx3.ttl_ctx.blank_labels, .blank_counter = ctx3.ttl_ctx.blank_counter, .state = s3}), .formula_counter = ctx3.formula_counter, .in_formula = ctx3.in_formula, .current_formula_id = ctx3.current_formula_id})}) });
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

slop_result_n3_N3TermResult_common_ParseError n3_parse_path_expression(slop_arena* arena, n3_N3ParseContext ctx, n3_N3Term base) {
    {
        __auto_type op = common_state_peek(ctx.ttl_ctx.state);
        {
            __auto_type s1 = common_state_advance(arena, ctx.ttl_ctx.state);
            {
                __auto_type ctx1 = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx.ttl_ctx.prefixes, .base_iri = ctx.ttl_ctx.base_iri, .blank_labels = ctx.ttl_ctx.blank_labels, .blank_counter = ctx.ttl_ctx.blank_counter, .state = s1}), .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
                {
                    __auto_type pred_result = n3_parse_n3_term(arena, ctx1);
                    __auto_type _mv_47 = pred_result;
                    if (_mv_47.is_ok) {
                        __auto_type pr = _mv_47.data.ok;
                        return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TermResult){.term = pr.term, .ctx = pr.ctx}) });
                    } else if (!_mv_47.is_ok) {
                        __auto_type e = _mv_47.data.err;
                        return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                    SLOP_UNREACHABLE();
                }
            }
        }
    }
}

slop_result_n3_N3TermResult_common_ParseError n3_parse_n3_term(slop_arena* arena, n3_N3ParseContext ctx) {
    {
        __auto_type c = common_state_peek(ctx.ttl_ctx.state);
        if (n3_is_formula_start(c)) {
            {
                __auto_type f_result = n3_parse_formula(arena, ctx);
                __auto_type _mv_48 = f_result;
                if (_mv_48.is_ok) {
                    __auto_type fr = _mv_48.data.ok;
                    return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TermResult){.term = ((n3_N3Term){ .tag = n3_N3Term_n3_formula, .data.n3_formula = fr.formula }), .ctx = fr.ctx}) });
                } else if (!_mv_48.is_ok) {
                    __auto_type e = _mv_48.data.err;
                    return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = false, .data.err = e });
                }
                SLOP_UNREACHABLE();
            }
        } else if (n3_is_quick_var_start(c)) {
            return n3_parse_quick_variable(arena, ctx);
        } else {
            {
                __auto_type t_result = ttl_parse_term(arena, ctx.ttl_ctx);
                __auto_type _mv_49 = t_result;
                if (_mv_49.is_ok) {
                    __auto_type tr = _mv_49.data.ok;
                    {
                        __auto_type new_ctx = ((n3_N3ParseContext){.ttl_ctx = tr.ctx, .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
                        if (n3_is_path_operator(common_state_peek(tr.ctx.state))) {
                            return n3_parse_path_expression(arena, new_ctx, ((n3_N3Term){ .tag = n3_N3Term_n3_rdf, .data.n3_rdf = tr.term }));
                        } else {
                            return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TermResult){.term = ((n3_N3Term){ .tag = n3_N3Term_n3_rdf, .data.n3_rdf = tr.term }), .ctx = new_ctx}) });
                        }
                    }
                } else if (!_mv_49.is_ok) {
                    __auto_type e = _mv_49.data.err;
                    return ((slop_result_n3_N3TermResult_common_ParseError){ .is_ok = false, .data.err = e });
                }
                SLOP_UNREACHABLE();
            }
        }
    }
}

slop_result_n3_N3TripleResult_common_ParseError n3_parse_n3_triple(slop_arena* arena, n3_N3ParseContext ctx) {
    {
        __auto_type sub_result = n3_parse_n3_term(arena, ctx);
        __auto_type _mv_50 = sub_result;
        if (_mv_50.is_ok) {
            __auto_type sr = _mv_50.data.ok;
            {
                __auto_type s1 = common_skip_whitespace(arena, sr.ctx.ttl_ctx.state);
                {
                    __auto_type ctx1 = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = sr.ctx.ttl_ctx.prefixes, .base_iri = sr.ctx.ttl_ctx.base_iri, .blank_labels = sr.ctx.ttl_ctx.blank_labels, .blank_counter = sr.ctx.ttl_ctx.blank_counter, .state = s1}), .formula_counter = sr.ctx.formula_counter, .in_formula = sr.ctx.in_formula, .current_formula_id = sr.ctx.current_formula_id});
                    {
                        __auto_type pred_result = n3_parse_n3_term(arena, ctx1);
                        __auto_type _mv_51 = pred_result;
                        if (_mv_51.is_ok) {
                            __auto_type pr = _mv_51.data.ok;
                            {
                                __auto_type s2 = common_skip_whitespace(arena, pr.ctx.ttl_ctx.state);
                                {
                                    __auto_type ctx2 = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = pr.ctx.ttl_ctx.prefixes, .base_iri = pr.ctx.ttl_ctx.base_iri, .blank_labels = pr.ctx.ttl_ctx.blank_labels, .blank_counter = pr.ctx.ttl_ctx.blank_counter, .state = s2}), .formula_counter = pr.ctx.formula_counter, .in_formula = pr.ctx.in_formula, .current_formula_id = pr.ctx.current_formula_id});
                                    {
                                        __auto_type obj_result = n3_parse_n3_term(arena, ctx2);
                                        __auto_type _mv_52 = obj_result;
                                        if (_mv_52.is_ok) {
                                            __auto_type objr = _mv_52.data.ok;
                                            {
                                                __auto_type s3 = common_skip_whitespace(arena, objr.ctx.ttl_ctx.state);
                                                {
                                                    __auto_type c3 = common_state_peek(s3);
                                                    if (objr.ctx.in_formula && ((c3 == 125) || common_state_at_end(s3))) {
                                                        {
                                                            __auto_type final_state = (((c3 == 46)) ? common_state_advance(arena, s3) : s3);
                                                            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TripleResult){.triple = ((n3_N3Triple){.subject = sr.term, .predicate = pr.term, .object = objr.term}), .ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = objr.ctx.ttl_ctx.prefixes, .base_iri = objr.ctx.ttl_ctx.base_iri, .blank_labels = objr.ctx.ttl_ctx.blank_labels, .blank_counter = objr.ctx.ttl_ctx.blank_counter, .state = final_state}), .formula_counter = objr.ctx.formula_counter, .in_formula = objr.ctx.in_formula, .current_formula_id = objr.ctx.current_formula_id})}) });
                                                        }
                                                    } else {
                                                        {
                                                            __auto_type s4 = common_expect_char(arena, s3, 46);
                                                            __auto_type _mv_53 = s4;
                                                            if (_mv_53.is_ok) {
                                                                __auto_type s5 = _mv_53.data.ok;
                                                                return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TripleResult){.triple = ((n3_N3Triple){.subject = sr.term, .predicate = pr.term, .object = objr.term}), .ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = objr.ctx.ttl_ctx.prefixes, .base_iri = objr.ctx.ttl_ctx.base_iri, .blank_labels = objr.ctx.ttl_ctx.blank_labels, .blank_counter = objr.ctx.ttl_ctx.blank_counter, .state = s5}), .formula_counter = objr.ctx.formula_counter, .in_formula = objr.ctx.in_formula, .current_formula_id = objr.ctx.current_formula_id})}) });
                                                            } else if (!_mv_53.is_ok) {
                                                                __auto_type e = _mv_53.data.err;
                                                                return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                                            }
                                                            SLOP_UNREACHABLE();
                                                        }
                                                    }
                                                }
                                            }
                                        } else if (!_mv_52.is_ok) {
                                            __auto_type e = _mv_52.data.err;
                                            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                        }
                                        SLOP_UNREACHABLE();
                                    }
                                }
                            }
                        } else if (!_mv_51.is_ok) {
                            __auto_type e = _mv_51.data.err;
                            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                        }
                        SLOP_UNREACHABLE();
                    }
                }
            }
        } else if (!_mv_50.is_ok) {
            __auto_type e = _mv_50.data.err;
            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
        }
        SLOP_UNREACHABLE();
    }
}

uint8_t n3_is_implication_predicate(n3_N3Term term) {
    __auto_type _mv_54 = term;
    switch (_mv_54.tag) {
        case n3_N3Term_n3_rdf:
        {
            __auto_type t = _mv_54.data.n3_rdf;
            __auto_type _mv_55 = t;
            switch (_mv_55.tag) {
                case rdf_Term_term_iri:
                {
                    __auto_type iri = _mv_55.data.term_iri;
                    return string_eq(iri.value, SLOP_STR("http://www.w3.org/2000/10/swap/log#implies"));
                }
                default: {
                    return 0;
                }
            }
        }
        default: {
            return 0;
        }
    }
}

uint8_t n3_is_reverse_implication_predicate(n3_N3Term term) {
    __auto_type _mv_56 = term;
    switch (_mv_56.tag) {
        case n3_N3Term_n3_rdf:
        {
            __auto_type t = _mv_56.data.n3_rdf;
            __auto_type _mv_57 = t;
            switch (_mv_57.tag) {
                case rdf_Term_term_iri:
                {
                    __auto_type iri = _mv_57.data.term_iri;
                    return string_eq(iri.value, SLOP_STR("http://www.w3.org/2000/10/swap/log#reverseImplies"));
                }
                default: {
                    return 0;
                }
            }
        }
        default: {
            return 0;
        }
    }
}

uint8_t n3_is_equivalence_predicate(n3_N3Term term) {
    __auto_type _mv_58 = term;
    switch (_mv_58.tag) {
        case n3_N3Term_n3_rdf:
        {
            __auto_type t = _mv_58.data.n3_rdf;
            __auto_type _mv_59 = t;
            switch (_mv_59.tag) {
                case rdf_Term_term_iri:
                {
                    __auto_type iri = _mv_59.data.term_iri;
                    return string_eq(iri.value, SLOP_STR("http://www.w3.org/2000/10/swap/log#equivalence"));
                }
                default: {
                    return 0;
                }
            }
        }
        default: {
            return 0;
        }
    }
}

slop_result_n3_N3TripleResult_common_ParseError n3_parse_implication(slop_arena* arena, n3_N3ParseContext ctx) {
    {
        __auto_type ante_result = n3_parse_formula(arena, ctx);
        __auto_type _mv_60 = ante_result;
        if (_mv_60.is_ok) {
            __auto_type ar = _mv_60.data.ok;
            {
                __auto_type s1 = common_skip_whitespace(arena, ar.ctx.ttl_ctx.state);
                {
                    __auto_type s2 = common_expect_char(arena, s1, 61);
                    __auto_type _mv_61 = s2;
                    if (_mv_61.is_ok) {
                        __auto_type s3 = _mv_61.data.ok;
                        {
                            __auto_type s4 = common_expect_char(arena, s3, 62);
                            __auto_type _mv_62 = s4;
                            if (_mv_62.is_ok) {
                                __auto_type s5 = _mv_62.data.ok;
                                {
                                    __auto_type s6 = common_skip_whitespace(arena, s5);
                                    {
                                        __auto_type ctx1 = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ar.ctx.ttl_ctx.prefixes, .base_iri = ar.ctx.ttl_ctx.base_iri, .blank_labels = ar.ctx.ttl_ctx.blank_labels, .blank_counter = ar.ctx.ttl_ctx.blank_counter, .state = s6}), .formula_counter = ar.ctx.formula_counter, .in_formula = ar.ctx.in_formula, .current_formula_id = ar.ctx.current_formula_id});
                                        {
                                            __auto_type cons_result = n3_parse_formula(arena, ctx1);
                                            __auto_type _mv_63 = cons_result;
                                            if (_mv_63.is_ok) {
                                                __auto_type cr = _mv_63.data.ok;
                                                {
                                                    __auto_type s7 = common_skip_whitespace(arena, cr.ctx.ttl_ctx.state);
                                                    {
                                                        __auto_type s8 = common_expect_char(arena, s7, 46);
                                                        __auto_type _mv_64 = s8;
                                                        if (_mv_64.is_ok) {
                                                            __auto_type s9 = _mv_64.data.ok;
                                                            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = true, .data.ok = ((n3_N3TripleResult){.triple = ((n3_N3Triple){.subject = ((n3_N3Term){ .tag = n3_N3Term_n3_formula, .data.n3_formula = ar.formula }), .predicate = ((n3_N3Term){ .tag = n3_N3Term_n3_rdf, .data.n3_rdf = rdf_make_iri(arena, SLOP_STR("http://www.w3.org/2000/10/swap/log#implies")) }), .object = ((n3_N3Term){ .tag = n3_N3Term_n3_formula, .data.n3_formula = cr.formula })}), .ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = cr.ctx.ttl_ctx.prefixes, .base_iri = cr.ctx.ttl_ctx.base_iri, .blank_labels = cr.ctx.ttl_ctx.blank_labels, .blank_counter = cr.ctx.ttl_ctx.blank_counter, .state = s9}), .formula_counter = cr.ctx.formula_counter, .in_formula = cr.ctx.in_formula, .current_formula_id = cr.ctx.current_formula_id})}) });
                                                        } else if (!_mv_64.is_ok) {
                                                            __auto_type e = _mv_64.data.err;
                                                            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                                        }
                                                        SLOP_UNREACHABLE();
                                                    }
                                                }
                                            } else if (!_mv_63.is_ok) {
                                                __auto_type e = _mv_63.data.err;
                                                return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                                            }
                                            SLOP_UNREACHABLE();
                                        }
                                    }
                                }
                            } else if (!_mv_62.is_ok) {
                                __auto_type e = _mv_62.data.err;
                                return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                            }
                            SLOP_UNREACHABLE();
                        }
                    } else if (!_mv_61.is_ok) {
                        __auto_type e = _mv_61.data.err;
                        return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
                    }
                    SLOP_UNREACHABLE();
                }
            }
        } else if (!_mv_60.is_ok) {
            __auto_type e = _mv_60.data.err;
            return ((slop_result_n3_N3TripleResult_common_ParseError){ .is_ok = false, .data.err = e });
        }
        SLOP_UNREACHABLE();
    }
}

rdf_Term n3_make_builtin_iri(slop_arena* arena, slop_string local_name) {
    return rdf_make_iri(arena, string_concat(arena, SLOP_STR("http://www.w3.org/2000/10/swap/log#"), local_name));
}

n3_N3Graph n3_make_n3_graph(slop_arena* arena) {
    n3_N3Graph _retval = {0};
    _retval = ((n3_N3Graph){.triples = ((slop_list_n3_N3Triple){ .data = (n3_N3Triple*)slop_arena_alloc(arena, 16 * sizeof(n3_N3Triple)), .len = 0, .cap = 16 }), .formulas = ((slop_list_n3_Formula){ .data = (n3_Formula*)slop_arena_alloc(arena, 16 * sizeof(n3_Formula)), .len = 0, .cap = 16 }), .size = 0});
    SLOP_POST(((_retval.size == 0)), "(== $result.size 0)");
    return _retval;
}

n3_N3Graph n3_n3_graph_add_triple(slop_arena* arena, n3_N3Graph g, n3_N3Triple t) {
    n3_N3Graph _retval = {0};
    ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
    _retval = ((n3_N3Graph){.triples = g.triples, .formulas = g.formulas, .size = (g.size + 1)});
    SLOP_POST(((_retval.size >= g.size)), "(>= $result.size g.size)");
    return _retval;
}

n3_N3Graph n3_n3_graph_add_formula(slop_arena* arena, n3_N3Graph g, n3_Formula f) {
    ({ __auto_type _lst_p = &(g.formulas); __auto_type _item = (f); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
    return ((n3_N3Graph){.triples = g.triples, .formulas = g.formulas, .size = g.size});
}

slop_result_n3_N3Graph_common_ParseError n3_parse_n3_string(slop_arena* arena, slop_string input) {
    SLOP_PRE(((string_len(input) > 0)), "(> (string-len input) 0)");
    {
        __auto_type ctx = n3_make_n3_context(arena, input);
        __auto_type g = n3_make_n3_graph(arena);
        {
            __auto_type s = common_skip_whitespace(arena, ctx.ttl_ctx.state);
            ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx.ttl_ctx.prefixes, .base_iri = ctx.ttl_ctx.base_iri, .blank_labels = ctx.ttl_ctx.blank_labels, .blank_counter = ctx.ttl_ctx.blank_counter, .state = s}), .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
            while (!(common_state_at_end(ctx.ttl_ctx.state))) {
                {
                    __auto_type c = common_state_peek(ctx.ttl_ctx.state);
                    if (c == 64) {
                        {
                            __auto_type dir_result = ttl_parse_directive(arena, ctx.ttl_ctx);
                            __auto_type _mv_65 = dir_result;
                            if (_mv_65.is_ok) {
                                __auto_type new_ttl_ctx = _mv_65.data.ok;
                                ctx = ((n3_N3ParseContext){.ttl_ctx = new_ttl_ctx, .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
                            } else if (!_mv_65.is_ok) {
                                __auto_type e = _mv_65.data.err;
                                return ((slop_result_n3_N3Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                /* empty list */;
                            }
                        }
                    } else {
                        if (c == 123) {
                            {
                                __auto_type impl_result = n3_parse_implication(arena, ctx);
                                __auto_type _mv_66 = impl_result;
                                if (_mv_66.is_ok) {
                                    __auto_type ir = _mv_66.data.ok;
                                    g = n3_n3_graph_add_triple(arena, g, ir.triple);
                                    ctx = ir.ctx;
                                } else if (!_mv_66.is_ok) {
                                    __auto_type e = _mv_66.data.err;
                                    return ((slop_result_n3_N3Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                    /* empty list */;
                                }
                            }
                        } else {
                            {
                                __auto_type triple_result = n3_parse_n3_triple(arena, ctx);
                                __auto_type _mv_67 = triple_result;
                                if (_mv_67.is_ok) {
                                    __auto_type tr = _mv_67.data.ok;
                                    g = n3_n3_graph_add_triple(arena, g, tr.triple);
                                    ctx = tr.ctx;
                                } else if (!_mv_67.is_ok) {
                                    __auto_type e = _mv_67.data.err;
                                    return ((slop_result_n3_N3Graph_common_ParseError){ .is_ok = false, .data.err = e });
                                    /* empty list */;
                                }
                            }
                        }
                    }
                }
                {
                    __auto_type s2 = common_skip_whitespace(arena, ctx.ttl_ctx.state);
                    ctx = ((n3_N3ParseContext){.ttl_ctx = ((ttl_TtlParseContext){.prefixes = ctx.ttl_ctx.prefixes, .base_iri = ctx.ttl_ctx.base_iri, .blank_labels = ctx.ttl_ctx.blank_labels, .blank_counter = ctx.ttl_ctx.blank_counter, .state = s2}), .formula_counter = ctx.formula_counter, .in_formula = ctx.in_formula, .current_formula_id = ctx.current_formula_id});
                }
            }
        }
        return ((slop_result_n3_N3Graph_common_ParseError){ .is_ok = true, .data.ok = g });
    }
}

slop_result_n3_N3Graph_n3_N3FileError n3_parse_n3_file(slop_arena* arena, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type f = file_file_open(path, file_FileMode_read);
        __auto_type _mv_68 = f;
        if (_mv_68.is_ok) {
            __auto_type handle = _mv_68.data.ok;
            {
                __auto_type content = file_file_read_all(arena, (&handle));
                __auto_type _mv_69 = content;
                if (_mv_69.is_ok) {
                    __auto_type text = _mv_69.data.ok;
                    file_file_close((&handle));
                    __auto_type _mv_70 = n3_parse_n3_string(arena, text);
                    if (_mv_70.is_ok) {
                        __auto_type g = _mv_70.data.ok;
                        return ((slop_result_n3_N3Graph_n3_N3FileError){ .is_ok = true, .data.ok = g });
                    } else if (!_mv_70.is_ok) {
                        __auto_type e = _mv_70.data.err;
                        return ((slop_result_n3_N3Graph_n3_N3FileError){ .is_ok = false, .data.err = ((n3_N3FileError){ .tag = n3_N3FileError_n3_parse_error, .data.n3_parse_error = e }) });
                    }
                    SLOP_UNREACHABLE();
                } else if (!_mv_69.is_ok) {
                    __auto_type e = _mv_69.data.err;
                    file_file_close((&handle));
                    return ((slop_result_n3_N3Graph_n3_N3FileError){ .is_ok = false, .data.err = ((n3_N3FileError){ .tag = n3_N3FileError_n3_file_error, .data.n3_file_error = e }) });
                }
                SLOP_UNREACHABLE();
            }
        } else if (!_mv_68.is_ok) {
            __auto_type e = _mv_68.data.err;
            return ((slop_result_n3_N3Graph_n3_N3FileError){ .is_ok = false, .data.err = ((n3_N3FileError){ .tag = n3_N3FileError_n3_file_error, .data.n3_file_error = e }) });
        }
        SLOP_UNREACHABLE();
    }
}

rdf_Graph n3_n3_to_rdf_graph(slop_arena* arena, n3_N3Graph n3g) {
    {
        __auto_type g = rdf_make_graph(arena);
        {
            __auto_type _coll = n3g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type s = ({ __auto_type _mv = t.subject; rdf_Term _mr = {0}; switch (_mv.tag) { case n3_N3Term_n3_rdf: { __auto_type term = _mv.data.n3_rdf; _mr = term; break; } case n3_N3Term_n3_formula: { __auto_type f = _mv.data.n3_formula; _mr = rdf_make_blank(arena, ((rdf_BlankNodeId)(f.id))); break; } case n3_N3Term_n3_quick_var: { __auto_type qv = _mv.data.n3_quick_var; _mr = rdf_make_blank(arena, 0); break; }  } _mr; });
                    __auto_type p = ({ __auto_type _mv = t.predicate; rdf_Term _mr = {0}; switch (_mv.tag) { case n3_N3Term_n3_rdf: { __auto_type term = _mv.data.n3_rdf; _mr = term; break; } case n3_N3Term_n3_formula: { __auto_type f = _mv.data.n3_formula; _mr = rdf_make_blank(arena, ((rdf_BlankNodeId)(f.id))); break; } case n3_N3Term_n3_quick_var: { __auto_type qv = _mv.data.n3_quick_var; _mr = rdf_make_blank(arena, 0); break; }  } _mr; });
                    __auto_type o = ({ __auto_type _mv = t.object; rdf_Term _mr = {0}; switch (_mv.tag) { case n3_N3Term_n3_rdf: { __auto_type term = _mv.data.n3_rdf; _mr = term; break; } case n3_N3Term_n3_formula: { __auto_type f = _mv.data.n3_formula; _mr = rdf_make_blank(arena, ((rdf_BlankNodeId)(f.id))); break; } case n3_N3Term_n3_quick_var: { __auto_type qv = _mv.data.n3_quick_var; _mr = rdf_make_blank(arena, 0); break; }  } _mr; });
                    g = rdf_graph_add(arena, g, rdf_make_triple(arena, s, p, o));
                }
            }
        }
        return g;
    }
}

