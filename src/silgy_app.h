/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
   silgy.com
-----------------------------------------------------------------------------
   Device configuration example
   Extra care for limited resources
-------------------------------------------------------------------------- */

#ifndef SILGY_APP_H
#define SILGY_APP_H


#define APP_WEBSITE                     "Device Configurator"
#define APP_DOMAIN                      "example.com"

#define DEF_RES_AUTH_LEVEL              AUTH_LEVEL_ANONYMOUS

#define MEM_TINY


#define SETTINGS_FILE                   "/cpp/iot/settings.json"


#define MSG_SETTINGS_SAVED              1201


#define SET_STRING1_LEN                 255


/* app user session */

typedef struct {
    /* devive settings */
    char  set_string1[SET_STRING1_LEN+1];
    int   set_int1;
    float set_float1;
    /* end of settings */
} ausession_t;


#endif  /* SILGY_APP_H */
