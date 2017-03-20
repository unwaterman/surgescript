/*
 * SurgeScript
 * A lightweight programming language for computer games and interactive apps
 * Copyright (C) 2017  Alexandre Martins <alemartf(at)gmail(dot)com>
 *
 * util/application.c
 * SurgeScript standard library: routines for the Application object
 */

#include <stdio.h>
#include "../vm.h"
#include "../../util/util.h"

/* private stuff */
static surgescript_var_t* fun_exit(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_print(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_crash(surgescript_object_t* object, const surgescript_var_t** param, int num_params);


/*
 * surgescript_sslib_register_application()
 * Register methods
 */
void surgescript_sslib_register_application(surgescript_vm_t* vm)
{
    surgescript_vm_bind(vm, "Application", "exit", fun_exit, 0);
    surgescript_vm_bind(vm, "Application", "print", fun_print, 1);
    surgescript_vm_bind(vm, "Application", "crash", fun_crash, 1);
}



/* my functions */

/* exits the app */
surgescript_var_t* fun_exit(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    surgescript_object_kill(object);
    return NULL;
}

/* prints param[0] to stdout */
surgescript_var_t* fun_print(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    char* text = surgescript_var_get_string(param[0]);
    puts(text);
    ssfree(text);
    return NULL;
}

/* crashes the engine with a message */
surgescript_var_t* fun_crash(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    char* text = surgescript_var_get_string(param[0]);
    ssfatal("Script Error: %s", text); /* change ssfatal to something else? */
    ssfree(text);
    surgescript_object_kill(object);
    return NULL;
}