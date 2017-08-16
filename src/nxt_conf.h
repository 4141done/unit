
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Valentin V. Bartenev
 * Copyright (C) NGINX, Inc.
 */

#ifndef _NXT_CONF_INCLUDED_
#define _NXT_CONF_INCLUDED_


#define NXT_CONF_NULL     0x01
#define NXT_CONF_BOOLEAN  0x02
#define NXT_CONF_INTEGER  0x04
#define NXT_CONF_NUMBER   0x08
#define NXT_CONF_STRING   0x10
#define NXT_CONF_ARRAY    0x20
#define NXT_CONF_OBJECT   0x40


typedef struct nxt_conf_value_s  nxt_conf_value_t;
typedef struct nxt_conf_op_s     nxt_conf_op_t;


typedef struct {
    u_char               *pos;
    u_char               *detail;
} nxt_conf_json_error_t;


typedef enum {
    NXT_CONF_MAP_INT8,
    NXT_CONF_MAP_INT32,
    NXT_CONF_MAP_INT64,
    NXT_CONF_MAP_INT,
    NXT_CONF_MAP_SIZE,
    NXT_CONF_MAP_OFF,
    NXT_CONF_MAP_MSEC,
    NXT_CONF_MAP_DOUBLE,
    NXT_CONF_MAP_STR,
    NXT_CONF_MAP_STR_COPY,
    NXT_CONF_MAP_CSTRZ,
    NXT_CONF_MAP_PTR,
} nxt_conf_map_type_t;


typedef struct {
    nxt_str_t            name;
    nxt_conf_map_type_t  type;
    size_t               offset;
} nxt_conf_map_t;


typedef struct {
    uint32_t             level;
    uint8_t              more_space;  /* 1 bit. */
} nxt_conf_json_pretty_t;


nxt_uint_t nxt_conf_type(nxt_conf_value_t *value);

nxt_conf_value_t *nxt_conf_get_path(nxt_conf_value_t *value, nxt_str_t *path);
nxt_conf_value_t *nxt_conf_get_object_member(nxt_conf_value_t *value,
    nxt_str_t *name, uint32_t *index);
nxt_conf_value_t *nxt_conf_next_object_member(nxt_conf_value_t *value,
    nxt_str_t *name, uint32_t *next);
nxt_conf_value_t *nxt_conf_get_array_element(nxt_conf_value_t *value,
    uint32_t index);

nxt_int_t nxt_conf_map_object(nxt_mp_t *mp, nxt_conf_value_t *value,
    nxt_conf_map_t *map, nxt_uint_t n, void *data);

nxt_int_t nxt_conf_op_compile(nxt_mp_t *mp, nxt_conf_op_t **ops,
    nxt_conf_value_t *root, nxt_str_t *path, nxt_conf_value_t *value);
nxt_conf_value_t *nxt_conf_clone(nxt_mp_t *mp, nxt_conf_op_t *op,
    nxt_conf_value_t *value);

nxt_conf_value_t *nxt_conf_json_parse(nxt_mp_t *mp, u_char *start, u_char *end,
    nxt_conf_json_error_t *error);

#define nxt_conf_json_parse_str(mp, str)                                      \
    nxt_conf_json_parse(mp, (str)->start, (str)->start + (str)->length, NULL)

size_t nxt_conf_json_length(nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);
u_char *nxt_conf_json_print(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);
void nxt_conf_json_position(u_char *start, u_char *pos, nxt_uint_t *line,
    nxt_uint_t *column);

nxt_int_t nxt_conf_validate(nxt_conf_value_t *value);

void nxt_conf_get_string(nxt_conf_value_t *value, nxt_str_t *str);

// FIXME reimplement and reorder functions below
nxt_uint_t nxt_conf_object_members_count(nxt_conf_value_t *value);
nxt_conf_value_t *nxt_conf_create_object(nxt_mp_t *mp, nxt_uint_t count);
void nxt_conf_set_member(nxt_conf_value_t *object, nxt_str_t *name,
    nxt_conf_value_t *value, uint32_t index);
void nxt_conf_set_member_string(nxt_conf_value_t *object, nxt_str_t *name,
    nxt_str_t *value, uint32_t index);
void nxt_conf_set_member_integer(nxt_conf_value_t *object, nxt_str_t *name,
    int64_t value, uint32_t index);


#endif /* _NXT_CONF_INCLUDED_ */
