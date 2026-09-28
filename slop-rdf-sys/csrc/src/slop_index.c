#include "../runtime/slop_runtime.h"
#include "slop_index.h"

index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena);
index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t);
uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t);
slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj);
void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback);
int64_t rdf_indexed_graph_size(index_IndexedGraph g);
slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj);
slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred);

index_IndexedGraph rdf_indexed_graph_create(slop_arena* arena) {
    index_IndexedGraph _retval = {0};
    _retval = ((index_IndexedGraph){.triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .index = ((index_TripleIndex){.spo = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .pso = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .osp = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term), .pos = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term)}), .size = 0});
    SLOP_POST(((_retval.size == 0)), "(== (. $result size) 0)");
    return _retval;
}

index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    index_IndexedGraph _retval = {0};
    if (rdf_indexed_graph_contains(g, t)) {
        _retval = g;
    }
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type spo_idx = g.index.spo;
            __auto_type _mv_72 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_72.has_value) {
                __auto_type pred_map = _mv_72.value;
                __auto_type _mv_74 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_74.has_value) {
                    __auto_type obj_set = _mv_74.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, obj_set, &(o), &_dummy); });
                } else if (!_mv_74.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    }
                }
            } else if (!_mv_72.has_value) {
                {
                    __auto_type pred_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pred_map, &(p), _vptr); });
                    ({ __auto_type _val = pred_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, spo_idx, &(s), _vptr); });
                }
            }
        }
        {
            __auto_type pso_idx = g.index.pso;
            __auto_type _mv_82 = ({ void* _ptr = slop_map_get(pso_idx, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_82.has_value) {
                __auto_type subj_map = _mv_82.value;
                __auto_type _mv_84 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_84.has_value) {
                    __auto_type obj_set = _mv_84.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, obj_set, &(o), &_dummy); });
                } else if (!_mv_84.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_82.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(o), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pso_idx, &(p), _vptr); });
                }
            }
        }
        {
            __auto_type osp_idx = g.index.osp;
            __auto_type _mv_92 = ({ void* _ptr = slop_map_get(osp_idx, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_92.has_value) {
                __auto_type subj_map = _mv_92.value;
                __auto_type _mv_94 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_94.has_value) {
                    __auto_type pred_set = _mv_94.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, pred_set, &(p), &_dummy); });
                } else if (!_mv_94.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(p), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    }
                }
            } else if (!_mv_92.has_value) {
                {
                    __auto_type subj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(p), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, subj_map, &(s), _vptr); });
                    ({ __auto_type _val = subj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, osp_idx, &(o), _vptr); });
                }
            }
        }
        {
            __auto_type pos_idx = g.index.pos;
            __auto_type _mv_102 = ({ void* _ptr = slop_map_get(pos_idx, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_102.has_value) {
                __auto_type obj_map = _mv_102.value;
                __auto_type _mv_104 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_104.has_value) {
                    __auto_type subj_set = _mv_104.value;
                    ({ uint8_t _dummy = 1; slop_map_put(arena, subj_set, &(s), &_dummy); });
                } else if (!_mv_104.has_value) {
                    {
                        __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                        ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(s), &_dummy); });
                        ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, obj_map, &(o), _vptr); });
                    }
                }
            } else if (!_mv_102.has_value) {
                {
                    __auto_type obj_map = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    __auto_type ts = slop_map_new_ptr(arena, 16, sizeof(rdf_Term), slop_hash_rdf_Term, slop_eq_rdf_Term);
                    ({ uint8_t _dummy = 1; slop_map_put(arena, ts, &(s), &_dummy); });
                    ({ __auto_type _val = ts; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, obj_map, &(o), _vptr); });
                    ({ __auto_type _val = obj_map; void* _vptr = slop_arena_alloc(arena, sizeof(_val)); memcpy(_vptr, &_val, sizeof(_val)); slop_map_put(arena, pos_idx, &(p), _vptr); });
                }
            }
        }
        _retval = ((index_IndexedGraph){.triples = g.triples, .index = g.index, .size = (g.size + 1)});
    }
    SLOP_POST(((_retval.size >= g.size)), "(>= (. $result size) (. g size))");
    return _retval;
}

uint8_t rdf_indexed_graph_contains(index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    uint8_t _retval = {0};
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_112 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_112.has_value) {
            __auto_type pred_map = _mv_112.value;
            __auto_type _mv_114 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_114.has_value) {
                __auto_type obj_set = _mv_114.value;
                return (slop_map_get(obj_set, &(o)) != NULL);
            } else if (!_mv_114.has_value) {
                return 0;
            }
            SLOP_UNREACHABLE();
        } else if (!_mv_112.has_value) {
            return 0;
        }
        SLOP_UNREACHABLE();
    }
    return _retval;
}

slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type result = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 });
        __auto_type _mv_116 = subj;
        if (_mv_116.has_value) {
            __auto_type s = _mv_116.value;
            __auto_type _mv_118 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_118.has_value) {
                __auto_type pred_map = _mv_118.value;
                __auto_type _mv_119 = pred;
                if (_mv_119.has_value) {
                    __auto_type p = _mv_119.value;
                    __auto_type _mv_121 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_121.has_value) {
                        __auto_type term_set = _mv_121.value;
                        __auto_type _mv_122 = obj;
                        if (_mv_122.has_value) {
                            __auto_type o = _mv_122.value;
                            if (slop_map_get(term_set, &(o)) != NULL) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        } else if (!_mv_122.has_value) {
                            {
                                slop_map* _coll = (slop_map*)term_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_121.has_value) {
                    }
                } else if (!_mv_119.has_value) {
                    {
                        slop_map* _coll = (slop_map*)pred_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                __auto_type _mv_124 = obj;
                                if (_mv_124.has_value) {
                                    __auto_type o = _mv_124.value;
                                    if (slop_map_get(term_set, &(o)) != NULL) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                } else if (!_mv_124.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_118.has_value) {
            }
        } else if (!_mv_116.has_value) {
            __auto_type _mv_126 = pred;
            if (_mv_126.has_value) {
                __auto_type p = _mv_126.value;
                __auto_type _mv_127 = obj;
                if (_mv_127.has_value) {
                    __auto_type o = _mv_127.value;
                    __auto_type _mv_129 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_129.has_value) {
                        __auto_type obj_map = _mv_129.value;
                        __auto_type _mv_131 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                        if (_mv_131.has_value) {
                            __auto_type subj_set = _mv_131.value;
                            {
                                slop_map* _coll = (slop_map*)subj_set;
                                for (size_t _i = 0; _i < _coll->cap; _i++) {
                                    if (_coll->entries[_i].occupied) {
                                        rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        } else if (!_mv_131.has_value) {
                        }
                    } else if (!_mv_129.has_value) {
                    }
                } else if (!_mv_127.has_value) {
                    __auto_type _mv_133 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_133.has_value) {
                        __auto_type subj_map = _mv_133.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_133.has_value) {
                    }
                }
            } else if (!_mv_126.has_value) {
                __auto_type _mv_134 = obj;
                if (_mv_134.has_value) {
                    __auto_type o = _mv_134.value;
                    __auto_type _mv_136 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_136.has_value) {
                        __auto_type subj_map = _mv_136.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                                            if (_coll->entries[_i].occupied) {
                                                rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_136.has_value) {
                    }
                } else if (!_mv_134.has_value) {
                    {
                        __auto_type _coll = g.triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    __auto_type _mv_137 = subj;
    if (_mv_137.has_value) {
        __auto_type s = _mv_137.value;
        __auto_type _mv_139 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_139.has_value) {
            __auto_type pred_map = _mv_139.value;
            __auto_type _mv_140 = pred;
            if (_mv_140.has_value) {
                __auto_type p = _mv_140.value;
                __auto_type _mv_142 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_142.has_value) {
                    __auto_type term_set = _mv_142.value;
                    __auto_type _mv_143 = obj;
                    if (_mv_143.has_value) {
                        __auto_type o = _mv_143.value;
                        if (slop_map_get(term_set, &(o)) != NULL) {
                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                        }
                    } else if (!_mv_143.has_value) {
                        {
                            slop_map* _coll = (slop_map*)term_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    }
                } else if (!_mv_142.has_value) {
                }
            } else if (!_mv_140.has_value) {
                {
                    slop_map* _coll = (slop_map*)pred_map;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                            index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                            __auto_type _mv_145 = obj;
                            if (_mv_145.has_value) {
                                __auto_type o = _mv_145.value;
                                if (slop_map_get(term_set, &(o)) != NULL) {
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            } else if (!_mv_145.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_139.has_value) {
        }
    } else if (!_mv_137.has_value) {
        __auto_type _mv_147 = pred;
        if (_mv_147.has_value) {
            __auto_type p = _mv_147.value;
            __auto_type _mv_148 = obj;
            if (_mv_148.has_value) {
                __auto_type o = _mv_148.value;
                __auto_type _mv_150 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_150.has_value) {
                    __auto_type obj_map = _mv_150.value;
                    __auto_type _mv_152 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                    if (_mv_152.has_value) {
                        __auto_type subj_set = _mv_152.value;
                        {
                            slop_map* _coll = (slop_map*)subj_set;
                            for (size_t _i = 0; _i < _coll->cap; _i++) {
                                if (_coll->entries[_i].occupied) {
                                    rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    } else if (!_mv_152.has_value) {
                    }
                } else if (!_mv_150.has_value) {
                }
            } else if (!_mv_148.has_value) {
                __auto_type _mv_154 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_154.has_value) {
                    __auto_type subj_map = _mv_154.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_154.has_value) {
                }
            }
        } else if (!_mv_147.has_value) {
            __auto_type _mv_155 = obj;
            if (_mv_155.has_value) {
                __auto_type o = _mv_155.value;
                __auto_type _mv_157 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
                if (_mv_157.has_value) {
                    __auto_type subj_map = _mv_157.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->cap; _i++) {
                            if (_coll->entries[_i].occupied) {
                                rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                                index_TermSet term_set = *(index_TermSet*)_coll->entries[_i].value;
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                                        if (_coll->entries[_i].occupied) {
                                            rdf_Term p = *(rdf_Term*)_coll->entries[_i].key;
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_157.has_value) {
                }
            } else if (!_mv_155.has_value) {
                {
                    __auto_type _coll = g.triples;
                    for (size_t _i = 0; _i < _coll.len; _i++) {
                        __auto_type t = _coll.data[_i];
                        ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, t);
                    }
                }
            }
        }
    }
}

int64_t rdf_indexed_graph_size(index_IndexedGraph g) {
    int64_t _retval = {0};
    _retval = g.size;
    SLOP_POST(((_retval == g.size)), "(== $result (. g size))");
    return _retval;
}

slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type pos_idx = g.index.pos;
        __auto_type _mv_159 = ({ void* _ptr = slop_map_get(pos_idx, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_159.has_value) {
            __auto_type obj_map = _mv_159.value;
            __auto_type _mv_161 = ({ void* _ptr = slop_map_get(obj_map, &(obj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_161.has_value) {
                __auto_type subj_set = _mv_161.value;
                {
                    slop_map* _coll = (slop_map*)subj_set;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term s = *(rdf_Term*)_coll->entries[_i].key;
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_161.has_value) {
            }
        } else if (!_mv_159.has_value) {
        }
        return result;
    }
}

slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = (rdf_Term*)slop_arena_alloc(arena, 16 * sizeof(rdf_Term)), .len = 0, .cap = 16 });
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_163 = ({ void* _ptr = slop_map_get(spo_idx, &(subj)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
        if (_mv_163.has_value) {
            __auto_type pred_map = _mv_163.value;
            __auto_type _mv_165 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_ptr){ .has_value = true, .value = *(void**)_ptr } : (slop_option_ptr){ .has_value = false }; });
            if (_mv_165.has_value) {
                __auto_type obj_set = _mv_165.value;
                {
                    slop_map* _coll = (slop_map*)obj_set;
                    for (size_t _i = 0; _i < _coll->cap; _i++) {
                        if (_coll->entries[_i].occupied) {
                            rdf_Term o = *(rdf_Term*)_coll->entries[_i].key;
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (o); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_165.has_value) {
            }
        } else if (!_mv_163.has_value) {
        }
        return result;
    }
}

