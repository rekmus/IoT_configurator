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
#define ASYNC_EXCLUDE_AUSES

#define DUMP


#define SETTINGS_FILE                   "/cpp/iot/settings.json"
#define PASSWORD_FILE                   "/cpp/iot/passwd.txt"


#define MSG_SETTINGS_SAVED              1201


#define PASSWORD_LEN                    255
#define SET_STRING1_LEN                 255



/* app user session */

typedef struct {
    char  login[LOGIN_LEN+1];
    char  password[PASSWORD_LEN+1];
    bool  authenticated;
} ausession_t;


#endif  /* SILGY_APP_H */
