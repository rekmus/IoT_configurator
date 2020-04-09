/* --------------------------------------------------------------------------
   Silgy Web App
   Jurek Muszynski
   silgy.com
-----------------------------------------------------------------------------
   Hello World Sample Silgy Web Application
-------------------------------------------------------------------------- */


#include <silgy.h>


/* --------------------------------------------------------------------------------
   Render main menu
-------------------------------------------------------------------------------- */
static void main_menu(int ci)
{
    char lnk_home[256]="<a href=\"/\">Home</a>";
    char lnk_settings[256]="<a href=\"/settings\">Settings</a>";
    char lnk_website[256];
    snprintf(lnk_website, 255, "<a href=\"https://%s\">Website</a>", APP_DOMAIN);
    char lnk_logout[256]="<a href=\"/logout\">Logout</a>";

    if ( REQ("") )
        COPY(lnk_home, "<b>Home</b>", 255);
    else if ( REQ("settings") )
        COPY(lnk_settings, "<b>Settings</b>", 255);

    OUT("<p>");

    OUT(lnk_home);
    OUT(" | ");
    OUT(lnk_settings);
    OUT(" | ");
    OUT(lnk_website);

    if ( AUS.authenticated )
    {
        OUT(" | ");
        OUT(lnk_logout);
    }

    OUT("</p>");
}


/* --------------------------------------------------------------------------------
   Render HTML header
-------------------------------------------------------------------------------- */
static void header(int ci)
{
    OUT("<!DOCTYPE html>");
    OUT("<html>");
    OUT("<head>");
    OUT("<meta charset=\"UTF-8\">");
    OUT("<title>%s</title>", APP_WEBSITE);
//    OUT("<meta name=\"description\" content=\"%s\">", APP_DESCRIPTION);
//    OUT("<meta name=\"keywords\" content=\"%s\">", APP_KEYWORDS);
    OUT("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//    OUT("<link rel=\"stylesheet\" type=\"text/css\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">");
    OUT("<link rel=\"stylesheet\" type=\"text/css\" href=\"/silgy.css\">");
    OUT("<link rel=\"stylesheet\" type=\"text/css\" href=\"/style.css\">");
//    OUT("<script src=\"/silgy.js\"></script>");
    OUT("</head>");

    OUT("<body>");
    OUT("<h1>%s</h1>", APP_WEBSITE);

    main_menu(ci);
}


/* --------------------------------------------------------------------------------
   Render HTML footer
-------------------------------------------------------------------------------- */
static void footer(int ci)
{
    OUT_HTML_FOOTER;
}


/* --------------------------------------------------------------------------
   Show error message if present in URI
-------------------------------------------------------------------------- */
static int check_error_msg(int ci)
{
    int msg;

    if ( !QSI("msg", &msg) || msg==OK ) return OK;

    OUT("<p class=\"ct m25 brd\">%s</p>", silgy_message(msg));

    return msg;
}


/* --------------------------------------------------------------------------------
   Render landing page
-------------------------------------------------------------------------------- */
static void render_landing(int ci)
{
    header(ci);
    OUT("<p class=m20>Welcome to %s!</p>", APP_WEBSITE);
    footer(ci);
}


/* --------------------------------------------------------------------------
   Render page
-------------------------------------------------------------------------- */
static void render_login(int ci)
{
    header(ci);
    OUT("<h2>Login</h2>");
    check_error_msg(ci);

    OUT("<form action=\"do_login\" method=\"POST\" novalidate>");

    OUT("<table%s>", REQ_DSK?"":" class=w100p");

    if ( REQ_DSK )
    {
        OUT("<tr><td class=rt>Login:</td><td><input name=\"login\" autofocus></td></tr>");
        OUT("<tr><td class=rt>Password:</td><td><input type=\"password\" name=\"passwd\"></td></tr>");
        OUT("<tr><td colspan=2>&nbsp;</td></tr>");
        OUT("<tr><td></td><td><input type=\"submit\" value=\"Login\"></td></tr>");
    }
    else    /* phone */
    {
        OUT("<tr><td>Login:</td></tr>");
        OUT("<tr><td><input class=w100p name=\"login\" autofocus></td></tr>");
        OUT("<tr><td class=pt>Password:</td></tr>");
        OUT("<tr><td><input class=w100p type=\"password\" name=\"passwd\"></td></tr>");
        OUT("<tr><td>&nbsp;</td></tr>");
        OUT("<tr><td><input type=\"submit\" value=\"Login\"></td></tr>");
    }

    OUT("</table>");

    OUT("</form>");

    footer(ci);
}


/* --------------------------------------------------------------------------
   Login
-------------------------------------------------------------------------- */
static int do_login(int ci)
{
    QSVAL qsval;
    char passwd[PASSWORD_LEN+1];

    if ( QS("passwd", qsval) )
        COPY(passwd, qsval, PASSWORD_LEN);

    if ( 0==strcmp(passwd, AUS.password) )
    {
        AUS.authenticated = true;
        return OK;
    }

    return ERR_UNAUTHORIZED;
}


/* --------------------------------------------------------------------------------
   Render settings page
-------------------------------------------------------------------------------- */
static void render_settings(int ci)
{
    header(ci);
    OUT("<h2>Settings</h2>");
    check_error_msg(ci);

    OUT("<form action=\"save_settings\" method=\"POST\" novalidate>");

    OUT("<table%s>", REQ_DSK?"":" class=w100p");

    if ( REQ_DSK )
    {
        OUT("<tr><td class=rt>Password:</td><td><input name=\"password\" value=\"%s\" autofocus></td></tr>", AUS.password);
        OUT("<tr><td class=rt>String value:</td><td><input name=\"string1\" value=\"%s\"></td></tr>", AUS.set_string1);
        OUT("<tr><td class=rt>Integer value:</td><td><input name=\"int1\" value=\"%d\"></td></tr>", AUS.set_int1);
        OUT("<tr><td class=rt>Float value:</td><td><input name=\"float1\" value=\"%f\"></td></tr>", AUS.set_float1);
        OUT("<tr><td colspan=2>&nbsp;</td></tr>");
        OUT("<tr><td></td><td><input type=\"submit\" value=\"Save settings\"></td></tr>");
    }
    else    /* phone */
    {
        OUT("<tr><td class=pt>Password:</td></tr>");
        OUT("<tr><td><input class=w100p name=\"password\" value=\"%s\" autofocus></td></tr>", AUS.password);
        OUT("<tr><td class=pt>String value:</td></tr>");
        OUT("<tr><td><input class=w100p name=\"string1\" value=\"%s\"></td></tr>", AUS.set_string1);
        OUT("<tr><td class=pt>Integer value:</td></tr>");
        OUT("<tr><td><input type=\"number\" name=\"int1\" value=\"%d\"></td></tr>", AUS.set_int1);
        OUT("<tr><td class=pt>Float value:</td></tr>");
        OUT("<tr><td><input type=\"number\" name=\"float1\" value=\"%f\"></td></tr>", AUS.set_float1);
        OUT("<tr><td>&nbsp;</td></tr>");
        OUT("<tr><td><input type=\"submit\" value=\"Save settings\"></td></tr>");
    }

    OUT("</table>");

    OUT("</form>");

    footer(ci);
}


/* --------------------------------------------------------------------------------
   Save settings to a file
-------------------------------------------------------------------------------- */
static int save_settings(int ci)
{
    // read query string values

    QSVAL qsval;

    if ( QS("password", qsval) )
        COPY(AUS.password, qsval, PASSWORD_LEN);

    if ( QS("string1", qsval) )
        COPY(AUS.set_string1, qsval, SET_STRING1_LEN);

    QSI("int1", &AUS.set_int1);
    QSF("float1", &AUS.set_float1);

    // render JSON

    JSON j={0};

    JSON_ADD_STR(j, "password", AUS.password);
    JSON_ADD_STR(j, "string1", AUS.set_string1);
    JSON_ADD_INT(j, "int1", AUS.set_int1);
    JSON_ADD_FLOAT(j, "float1", AUS.set_float1);

    char data[JSON_BUFSIZE];

    COPY(data, JSON_TO_STRING_PRETTY(j), JSON_BUFSIZE-1);

    // save JSON to a file

    FILE *fd;

    if ( NULL == (fd=fopen(SETTINGS_FILE, "w")) )
    {
        WAR("Couldn't open %s\n", SETTINGS_FILE);
        return ERR_INT_SERVER_ERROR;
    }
    else    /* OK */
    {
        fwrite(data, strlen(data), 1, fd);
    }

    fclose(fd);

    return OK;
}


/* --------------------------------------------------------------------------------
   Called after parsing HTTP request header
   ------------------------------
   This is the main entry point for a request
   ------------------------------
   Response status will be 200 by default
   Use RES_STATUS() if you want to change it
-------------------------------------------------------------------------------- */
void silgy_app_main(int ci)
{
    int ret=OK;

    if ( REQ("login") )
    {
        render_login(ci);
    }
    else if ( REQ("do_login") )
    {
        ret = do_login(ci);

        if ( ret == OK )
            RES_LOCATION("/settings");
        else
            RES_LOCATION("/login?msg=%d", ret);
    }
    else if ( REQ("settings") )
    {
        if ( AUS.authenticated )
            render_settings(ci);
        else
            RES_LOCATION("/login");
    }
    else if ( REQ("save_settings") )
    {
        if ( AUS.authenticated )
        {
            ret = save_settings(ci);
            RES_LOCATION("/settings?msg=%d", ret==OK?MSG_SETTINGS_SAVED:ret);
        }
        else
            RES_LOCATION("/login");
    }
    else if ( REQ("logout") )
    {
        AUS.authenticated = false;
        RES_LOCATION("/");
    }
    else
    {
        render_landing(ci);
    }

    RES_DONT_CACHE;
}


/* --------------------------------------------------------------------------------
   Called when application starts
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will stop booting process,
   silgy_app_done() will be called and application will be terminated
-------------------------------------------------------------------------------- */
bool silgy_app_init(int argc, char *argv[])
{
    silgy_add_message(MSG_SETTINGS_SAVED, "EN-US", "Settings have been saved");

    return true;
}


/* --------------------------------------------------------------------------------
   Called when new anonymous user session starts
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be closed
   and silgy_app_session_done() will be called
   Response status will be set to 500
-------------------------------------------------------------------------------- */
bool silgy_app_session_init(int ci)
{
    // read settings from a file

    FILE *fd;

    if ( NULL == (fd=fopen(SETTINGS_FILE, "r")) )
    {
        WAR("Couldn't open %s\n", SETTINGS_FILE);
//        return false;
        return true;
    }

    fseek(fd, 0, SEEK_END);     /* determine the file size */
    unsigned len = ftell(fd);
    rewind(fd);

    char *data;

    if ( NULL == (data=(char*)malloc(len+1)) )
    {
        ERR("Couldn't allocate %u bytes for %s", len, SETTINGS_FILE);
        fclose(fd);
        return false;
    }

    fread(data, len, 1, fd);
    *(data+len) = EOS;

    fclose(fd);

    JSON j={0};
    JSON_FROM_STRING(j, data);

    COPY(AUS.password, JSON_GET_STR(j, "password"), PASSWORD_LEN);
    COPY(AUS.set_string1, JSON_GET_STR(j, "string1"), SET_STRING1_LEN);
    AUS.set_int1 = JSON_GET_INT(j, "int1");
    AUS.set_float1 = JSON_GET_FLOAT(j, "float1");

    free(data);

    return true;
}


/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called after successful authentication (using password or cookie)
   when user session is upgraded from anonymous to logged in
   ------------------------------
   Return true if everything OK
   ------------------------------
   Returning false will cause the session to be downgraded back to anonymous
   and silgy_app_user_logout() will be called
-------------------------------------------------------------------------------- */
bool silgy_app_user_login(int ci)
{
    return true;
}


/* --------------------------------------------------------------------------------
   ******* Only for USERS *******
   ------------------------------
   Called when downgrading logged in user session to anonymous
-------------------------------------------------------------------------------- */
void silgy_app_user_logout(int ci)
{
}


/* --------------------------------------------------------------------------------
   Called when closing anonymous user session
   After calling this the session memory will be zero-ed
-------------------------------------------------------------------------------- */
void silgy_app_session_done(int ci)
{
}


/* --------------------------------------------------------------------------------
   Called when application shuts down
-------------------------------------------------------------------------------- */
void silgy_app_done()
{
}
