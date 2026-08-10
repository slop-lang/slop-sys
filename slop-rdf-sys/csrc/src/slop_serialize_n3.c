#include "../runtime/slop_runtime.h"
#include "slop_serialize_n3.h"

slop_string serialize_n3_serialize_quick_var(slop_arena* arena, n3_QuickVar var);
slop_string serialize_n3_serialize_formula(slop_arena* arena, n3_Formula f, ttl_PrefixMap prefixes);
slop_string serialize_n3_serialize_n3_term(slop_arena* arena, n3_N3Term t, ttl_PrefixMap prefixes);
slop_string serialize_n3_serialize_n3_string(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config);
slop_result_u8_serialize_n3_N3FileError serialize_n3_serialize_n3_file(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config, slop_string path);

slop_string serialize_n3_serialize_quick_var(slop_arena* arena, n3_QuickVar var) {
    SLOP_PRE(((string_len(var.name) > 0)), "(> (string-len var.name) 0)");
    slop_string _retval = {0};
    _retval = string_concat(arena, SLOP_STR("?"), var.name);
    SLOP_POST((strlib_starts_with(_retval, SLOP_STR("?"))), "(starts-with $result \"?\")");
    return _retval;
}

slop_string serialize_n3_serialize_formula(slop_arena* arena, n3_Formula f, ttl_PrefixMap prefixes) {
    slop_string _retval = {0};
    {
        __auto_type g = f.graph;
        if (rdf_graph_size(g) == 0) {
            _retval = SLOP_STR("{ }");
        } else {
            {
                __auto_type result = SLOP_STR("{\n");
                {
                    __auto_type _coll = g.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type triple = _coll.data[_i];
                        result = string_concat(arena, result, SLOP_STR("  "));
                        result = string_concat(arena, result, serialize_ttl_serialize_term(arena, triple.subject, prefixes));
                        result = string_concat(arena, result, SLOP_STR(" "));
                        result = string_concat(arena, result, serialize_ttl_serialize_term(arena, triple.predicate, prefixes));
                        result = string_concat(arena, result, SLOP_STR(" "));
                        result = string_concat(arena, result, serialize_ttl_serialize_term(arena, triple.object, prefixes));
                        result = string_concat(arena, result, SLOP_STR(" .\n"));
                    }
                }
                result = string_concat(arena, result, SLOP_STR("}"));
                _retval = result;
            }
        }
    }
    SLOP_POST((strlib_starts_with(_retval, SLOP_STR("{"))), "(starts-with $result \"{\")");
    return _retval;
}

slop_string serialize_n3_serialize_n3_term(slop_arena* arena, n3_N3Term t, ttl_PrefixMap prefixes) {
    slop_string _retval = {0};
    __auto_type _mv_153 = t;
    switch (_mv_153.tag) {
        case n3_N3Term_n3_rdf:
        {
            __auto_type term = _mv_153.data.n3_rdf;
            return serialize_ttl_serialize_term(arena, term, prefixes);
        }
        case n3_N3Term_n3_formula:
        {
            __auto_type f = _mv_153.data.n3_formula;
            return serialize_n3_serialize_formula(arena, f, prefixes);
        }
        case n3_N3Term_n3_quick_var:
        {
            __auto_type qv = _mv_153.data.n3_quick_var;
            return serialize_n3_serialize_quick_var(arena, qv);
        }
    }
    SLOP_POST(((string_len(_retval) > 0)), "(> (string-len $result) 0)");
    return _retval;
}

slop_string serialize_n3_serialize_n3_string(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config) {
    slop_string _retval = {0};
    {
        __auto_type prefixes = config.prefixes;
        __auto_type base = config.base_iri;
        {
            __auto_type result = SLOP_STR("");
            result = string_concat(arena, result, serialize_ttl_serialize_base(arena, base));
            {
                __auto_type prefix_str = serialize_ttl_serialize_prefixes(arena, prefixes);
                if (string_len(prefix_str) > 0) {
                    result = string_concat(arena, result, prefix_str);
                    result = string_concat(arena, result, SLOP_STR("\n"));
                }
            }
            {
                __auto_type _coll = g.triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type triple = _coll.data[_i];
                    result = string_concat(arena, result, serialize_n3_serialize_n3_term(arena, triple.subject, prefixes));
                    result = string_concat(arena, result, SLOP_STR(" "));
                    result = string_concat(arena, result, serialize_n3_serialize_n3_term(arena, triple.predicate, prefixes));
                    result = string_concat(arena, result, SLOP_STR(" "));
                    result = string_concat(arena, result, serialize_n3_serialize_n3_term(arena, triple.object, prefixes));
                    result = string_concat(arena, result, SLOP_STR(" .\n"));
                }
            }
            _retval = result;
        }
    }
    SLOP_POST(((string_len(_retval) >= 0)), "(>= (string-len $result) 0)");
    return _retval;
}

slop_result_u8_serialize_n3_N3FileError serialize_n3_serialize_n3_file(slop_arena* arena, n3_N3Graph g, serialize_ttl_SerializeConfig config, slop_string path) {
    SLOP_PRE(((string_len(path) > 0)), "(> (string-len path) 0)");
    {
        __auto_type content = serialize_n3_serialize_n3_string(arena, g, config);
        {
            __auto_type f = file_file_open(path, file_FileMode_write);
            __auto_type _mv_154 = f;
            if (_mv_154.is_ok) {
                __auto_type handle = _mv_154.data.ok;
                file_file_write_line((&handle), content);
                file_file_close((&handle));
                return ((slop_result_u8_serialize_n3_N3FileError){ .is_ok = true, .data.ok = 1 });
            } else if (!_mv_154.is_ok) {
                __auto_type e = _mv_154.data.err;
                return ((slop_result_u8_serialize_n3_N3FileError){ .is_ok = false, .data.err = ((serialize_n3_N3FileError){ .tag = serialize_n3_N3FileError_n3_file_error, .data.n3_file_error = e }) });
            }
        }
    }
}

