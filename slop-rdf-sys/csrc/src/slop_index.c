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
    _retval = ((index_IndexedGraph){.triples = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena }), .index = ((index_TripleIndex){.spo = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .pso = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .osp = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); }), .pos = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); })}), .size = 0});
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval.size == 0)), "(== (. $result size) 0)");
    return _retval;
}

index_IndexedGraph rdf_indexed_graph_add(slop_arena* arena, index_IndexedGraph g, rdf_Triple t) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    index_IndexedGraph _retval = {0};
    if (rdf_indexed_graph_contains(g, t)) {
        _retval = g;
        goto _slop_post;
    }
    {
        __auto_type s = rdf_triple_subject(t);
        __auto_type p = rdf_triple_predicate(t);
        __auto_type o = rdf_triple_object(t);
        ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
        {
            __auto_type spo_idx = g.index.spo;
            __auto_type _mv_73 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_73.has_value) {
                __auto_type pred_map = _mv_73.value;
                __auto_type _mv_75 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_75.has_value) {
                    __auto_type obj_set = _mv_75.value;
                    ({ slop_map_put(NULL, obj_set, &(o), NULL, 0); });
                } else if (!_mv_75.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, pred_map, &(p), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_73.has_value) {
                {
                    __auto_type pred_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, pred_map, &(p), &_val, sizeof(_val)); });
                    ({ slop_map* _val = pred_map; slop_map_put(NULL, spo_idx, &(s), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type pso_idx = g.index.pso;
            __auto_type _mv_83 = ({ void* _ptr = slop_map_get(pso_idx, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_83.has_value) {
                __auto_type subj_map = _mv_83.value;
                __auto_type _mv_85 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_85.has_value) {
                    __auto_type obj_set = _mv_85.value;
                    ({ slop_map_put(NULL, obj_set, &(o), NULL, 0); });
                } else if (!_mv_85.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_83.has_value) {
                {
                    __auto_type subj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(o), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    ({ slop_map* _val = subj_map; slop_map_put(NULL, pso_idx, &(p), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type osp_idx = g.index.osp;
            __auto_type _mv_93 = ({ void* _ptr = slop_map_get(osp_idx, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_93.has_value) {
                __auto_type subj_map = _mv_93.value;
                __auto_type _mv_95 = ({ void* _ptr = slop_map_get(subj_map, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_95.has_value) {
                    __auto_type pred_set = _mv_95.value;
                    ({ slop_map_put(NULL, pred_set, &(p), NULL, 0); });
                } else if (!_mv_95.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(p), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_93.has_value) {
                {
                    __auto_type subj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(p), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, subj_map, &(s), &_val, sizeof(_val)); });
                    ({ slop_map* _val = subj_map; slop_map_put(NULL, osp_idx, &(o), &_val, sizeof(_val)); });
                }
            }
        }
        {
            __auto_type pos_idx = g.index.pos;
            __auto_type _mv_103 = ({ void* _ptr = slop_map_get(pos_idx, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_103.has_value) {
                __auto_type obj_map = _mv_103.value;
                __auto_type _mv_105 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_105.has_value) {
                    __auto_type subj_set = _mv_105.value;
                    ({ slop_map_put(NULL, subj_set, &(s), NULL, 0); });
                } else if (!_mv_105.has_value) {
                    {
                        __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                        ({ slop_map_put(NULL, ts, &(s), NULL, 0); });
                        ({ slop_map* _val = ts; slop_map_put(NULL, obj_map, &(o), &_val, sizeof(_val)); });
                    }
                }
            } else if (!_mv_103.has_value) {
                {
                    __auto_type obj_map = ({ static const slop_map_desc _d = SLOP_MAP_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED, slop_map*); slop_map_new_ptr(arena, 0, &_d); });
                    __auto_type ts = ({ static const slop_map_desc _d = SLOP_SET_DESC(rdf_Term, slop_hash_rdf_Term, slop_eq_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
                    ({ slop_map_put(NULL, ts, &(s), NULL, 0); });
                    ({ slop_map* _val = ts; slop_map_put(NULL, obj_map, &(o), &_val, sizeof(_val)); });
                    ({ slop_map* _val = obj_map; slop_map_put(NULL, pos_idx, &(p), &_val, sizeof(_val)); });
                }
            }
        }
        _retval = ((index_IndexedGraph){.triples = g.triples, .index = g.index, .size = (g.size + 1)});
        goto _slop_post;
    }
    _slop_post: ;
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
        __auto_type _mv_113 = ({ void* _ptr = slop_map_get(spo_idx, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_113.has_value) {
            __auto_type pred_map = _mv_113.value;
            __auto_type _mv_115 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_115.has_value) {
                __auto_type obj_set = _mv_115.value;
                _retval = slop_map_has(obj_set, &(o));
                goto _slop_post;
            } else if (!_mv_115.has_value) {
                _retval = 0;
                goto _slop_post;
            }
            SLOP_UNREACHABLE();
        } else if (!_mv_113.has_value) {
            _retval = 0;
            goto _slop_post;
        }
        SLOP_UNREACHABLE();
    }
    _slop_post: ;
    return _retval;
}

slop_list_rdf_Triple rdf_indexed_graph_match(slop_arena* arena, index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    slop_list_rdf_Triple _retval = {0};
    {
        __auto_type result = ((slop_list_rdf_Triple){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type _mv_117 = subj;
        if (_mv_117.has_value) {
            __auto_type s = _mv_117.value;
            __auto_type _mv_119 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_119.has_value) {
                __auto_type pred_map = _mv_119.value;
                __auto_type _mv_120 = pred;
                if (_mv_120.has_value) {
                    __auto_type p = _mv_120.value;
                    __auto_type _mv_122 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_122.has_value) {
                        __auto_type term_set = _mv_122.value;
                        __auto_type _mv_123 = obj;
                        if (_mv_123.has_value) {
                            __auto_type o = _mv_123.value;
                            if (slop_map_has(term_set, &(o))) {
                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                            }
                        } else if (!_mv_123.has_value) {
                            {
                                slop_map* _coll = (slop_map*)term_set;
                                for (size_t _i = 0; _i < _coll->len; _i++) {
                                    {
                                        rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        }
                    } else if (!_mv_122.has_value) {
                    }
                } else if (!_mv_120.has_value) {
                    {
                        slop_map* _coll = (slop_map*)pred_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                rdf_Term p = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                                __auto_type _mv_125 = obj;
                                if (_mv_125.has_value) {
                                    __auto_type o = _mv_125.value;
                                    if (slop_map_has(term_set, &(o))) {
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                } else if (!_mv_125.has_value) {
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (!_mv_119.has_value) {
            }
        } else if (!_mv_117.has_value) {
            __auto_type _mv_127 = pred;
            if (_mv_127.has_value) {
                __auto_type p = _mv_127.value;
                __auto_type _mv_128 = obj;
                if (_mv_128.has_value) {
                    __auto_type o = _mv_128.value;
                    __auto_type _mv_130 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_130.has_value) {
                        __auto_type obj_map = _mv_130.value;
                        __auto_type _mv_132 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                        if (_mv_132.has_value) {
                            __auto_type subj_set = _mv_132.value;
                            {
                                slop_map* _coll = (slop_map*)subj_set;
                                for (size_t _i = 0; _i < _coll->len; _i++) {
                                    {
                                        rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                        ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                    }
                                }
                            }
                        } else if (!_mv_132.has_value) {
                        }
                    } else if (!_mv_130.has_value) {
                    }
                } else if (!_mv_128.has_value) {
                    __auto_type _mv_134 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_134.has_value) {
                        __auto_type subj_map = _mv_134.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                    index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_134.has_value) {
                    }
                }
            } else if (!_mv_127.has_value) {
                __auto_type _mv_135 = obj;
                if (_mv_135.has_value) {
                    __auto_type o = _mv_135.value;
                    __auto_type _mv_137 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_137.has_value) {
                        __auto_type subj_map = _mv_137.value;
                        {
                            slop_map* _coll = (slop_map*)subj_map;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                    index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                                    {
                                        slop_map* _coll = (slop_map*)term_set;
                                        for (size_t _i = 0; _i < _coll->len; _i++) {
                                            {
                                                rdf_Term p = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                                ({ __auto_type _lst_p = &(result); __auto_type _item = (((rdf_Triple){.subject = s, .predicate = p, .object = o})); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (!_mv_137.has_value) {
                    }
                } else if (!_mv_135.has_value) {
                    {
                        __auto_type _coll = g.triples;
                        for (size_t _i = 0; _i < _coll.len; _i++) {
                            __auto_type t = _coll.data[_i];
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            }
        }
        _retval = result;
        goto _slop_post;
    }
    _slop_post: ;
    SLOP_POST(((((int64_t)((_retval).len)) >= 0)), "(>= (list-len $result) 0)");
    return _retval;
}

void rdf_indexed_graph_for_each(index_IndexedGraph g, slop_option_rdf_Term subj, slop_option_rdf_Term pred, slop_option_rdf_Term obj, slop_closure_t callback) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    __auto_type _mv_138 = subj;
    if (_mv_138.has_value) {
        __auto_type s = _mv_138.value;
        __auto_type _mv_140 = ({ void* _ptr = slop_map_get(g.index.spo, &(s)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_140.has_value) {
            __auto_type pred_map = _mv_140.value;
            __auto_type _mv_141 = pred;
            if (_mv_141.has_value) {
                __auto_type p = _mv_141.value;
                __auto_type _mv_143 = ({ void* _ptr = slop_map_get(pred_map, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_143.has_value) {
                    __auto_type term_set = _mv_143.value;
                    __auto_type _mv_144 = obj;
                    if (_mv_144.has_value) {
                        __auto_type o = _mv_144.value;
                        if (slop_map_has(term_set, &(o))) {
                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                        }
                    } else if (!_mv_144.has_value) {
                        {
                            slop_map* _coll = (slop_map*)term_set;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    }
                } else if (!_mv_143.has_value) {
                }
            } else if (!_mv_141.has_value) {
                {
                    slop_map* _coll = (slop_map*)pred_map;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            rdf_Term p = *(rdf_Term*)slop_map_key_at(_coll, _i);
                            index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                            __auto_type _mv_146 = obj;
                            if (_mv_146.has_value) {
                                __auto_type o = _mv_146.value;
                                if (slop_map_has(term_set, &(o))) {
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            } else if (!_mv_146.has_value) {
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (!_mv_140.has_value) {
        }
    } else if (!_mv_138.has_value) {
        __auto_type _mv_148 = pred;
        if (_mv_148.has_value) {
            __auto_type p = _mv_148.value;
            __auto_type _mv_149 = obj;
            if (_mv_149.has_value) {
                __auto_type o = _mv_149.value;
                __auto_type _mv_151 = ({ void* _ptr = slop_map_get(g.index.pos, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_151.has_value) {
                    __auto_type obj_map = _mv_151.value;
                    __auto_type _mv_153 = ({ void* _ptr = slop_map_get(obj_map, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                    if (_mv_153.has_value) {
                        __auto_type subj_set = _mv_153.value;
                        {
                            slop_map* _coll = (slop_map*)subj_set;
                            for (size_t _i = 0; _i < _coll->len; _i++) {
                                {
                                    rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                    ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                }
                            }
                        }
                    } else if (!_mv_153.has_value) {
                    }
                } else if (!_mv_151.has_value) {
                }
            } else if (!_mv_149.has_value) {
                __auto_type _mv_155 = ({ void* _ptr = slop_map_get(g.index.pso, &(p)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_155.has_value) {
                    __auto_type subj_map = _mv_155.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_155.has_value) {
                }
            }
        } else if (!_mv_148.has_value) {
            __auto_type _mv_156 = obj;
            if (_mv_156.has_value) {
                __auto_type o = _mv_156.value;
                __auto_type _mv_158 = ({ void* _ptr = slop_map_get(g.index.osp, &(o)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
                if (_mv_158.has_value) {
                    __auto_type subj_map = _mv_158.value;
                    {
                        slop_map* _coll = (slop_map*)subj_map;
                        for (size_t _i = 0; _i < _coll->len; _i++) {
                            {
                                rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                index_TermSet term_set = *(index_TermSet*)slop_map_value_at(_coll, _i);
                                {
                                    slop_map* _coll = (slop_map*)term_set;
                                    for (size_t _i = 0; _i < _coll->len; _i++) {
                                        {
                                            rdf_Term p = *(rdf_Term*)slop_map_key_at(_coll, _i);
                                            ((void(*)(void*, rdf_Triple))callback.fn)(callback.env, ((rdf_Triple){.subject = s, .predicate = p, .object = o}));
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if (!_mv_158.has_value) {
                }
            } else if (!_mv_156.has_value) {
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
    goto _slop_post;
    _slop_post: ;
    SLOP_POST(((_retval == g.size)), "(== $result (. g size))");
    return _retval;
}

slop_list_rdf_Term rdf_indexed_graph_subjects(slop_arena* arena, index_IndexedGraph g, rdf_Term pred, rdf_Term obj) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type pos_idx = g.index.pos;
        __auto_type _mv_160 = ({ void* _ptr = slop_map_get(pos_idx, &(pred)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_160.has_value) {
            __auto_type obj_map = _mv_160.value;
            __auto_type _mv_162 = ({ void* _ptr = slop_map_get(obj_map, &(obj)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_162.has_value) {
                __auto_type subj_set = _mv_162.value;
                {
                    slop_map* _coll = (slop_map*)subj_set;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            rdf_Term s = *(rdf_Term*)slop_map_key_at(_coll, _i);
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (s); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_162.has_value) {
            }
        } else if (!_mv_160.has_value) {
        }
        return result;
    }
}

slop_list_rdf_Term rdf_indexed_graph_objects(slop_arena* arena, index_IndexedGraph g, rdf_Term subj, rdf_Term pred) {
    SLOP_PRE(((g.size >= 0)), "(>= (. g size) 0)");
    {
        __auto_type result = ((slop_list_rdf_Term){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        __auto_type spo_idx = g.index.spo;
        __auto_type _mv_164 = ({ void* _ptr = slop_map_get(spo_idx, &(subj)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
        if (_mv_164.has_value) {
            __auto_type pred_map = _mv_164.value;
            __auto_type _mv_166 = ({ void* _ptr = slop_map_get(pred_map, &(pred)); _ptr ? (slop_option_map_ptr){ .has_value = true, .value = *(slop_map**)_ptr } : (slop_option_map_ptr){ .has_value = false }; });
            if (_mv_166.has_value) {
                __auto_type obj_set = _mv_166.value;
                {
                    slop_map* _coll = (slop_map*)obj_set;
                    for (size_t _i = 0; _i < _coll->len; _i++) {
                        {
                            rdf_Term o = *(rdf_Term*)slop_map_key_at(_coll, _i);
                            ({ __auto_type _lst_p = &(result); __auto_type _item = (o); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; });
                        }
                    }
                }
            } else if (!_mv_166.has_value) {
            }
        } else if (!_mv_164.has_value) {
        }
        return result;
    }
}

