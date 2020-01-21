static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=11:style=bold", "Font Awesome 5 Brands Regular:size=11:style=bold", "Font Awesome 5 Free Solid:size=11:style=bold", "Font Awesome 5 Free Regular:size=11:style=bold"};
static const char dmenufont[]       = "Hack Nerd Font:size=12";
static const char col_gray[]       = "#aaaaaa";
static const char col_red[]       = "#ff0000";
static const char col_green[]       = "#00ff00";
static const char col_yellow[]     = "#ff5555";
static const char col_black[]      = "#0e151b";
static const char col_white[]      = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_green },
	[SchemeSel]  = { col_black, col_yellow, col_red },
	[SchemeTitle]  = { col_yellow, col_black, col_black  },
};

/* tagging */
// static const char *tags[] = { "", "", "", "", ""};
static const char *tags[] = { "", "", "", "", ""};

static const Rule rules[] = {

	/* class      	instance    title       tags mask     isfloating   monitor */
	{ "firefox",  		NULL,       NULL,       1<<0,       0,           -1 },
	{ "ranger",  		NULL,       NULL,       1<<1,       0,           -1 },
	{ "St",				NULL,       NULL,       1<<2,       0,           -1 },
	{ "Subl3",  		NULL,       NULL,       1<<3,       0,           -1 },
	{ "Zathura",  		NULL,       NULL,       1<<4,       1,           -1 },
	{ "mail",  			NULL,       NULL,       NULL,       1,           -1 },
	{ "downloads",		NULL,       NULL,       NULL,       1,           -1 },
	{ "uninstall",		NULL,       NULL,       NULL,       1,           -1 },
	{ "mocp",			NULL,       NULL,       NULL,       1,           -1 },
	{ "Pqiv",			NULL,       NULL,       NULL,       1,           -1 },
	{ "dwm",			NULL,       NULL,       NULL,       1,           -1 },
	{ "qalc",			NULL,       "qalc",     NULL,       1,           -1 },
	{ "qalc",			NULL,       NULL,     	NULL,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_a,	   spawn,          SHCMD("dmenu_run") },
	// { MODKEY|ControlMask,			XK_b,      togglebar,      {0} },
	{ MODKEY|ControlMask,			XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,  incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,			XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,			XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Down,     setcfact,       {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_Up,   setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_Page_Up,zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_x,      killclient,     {0} },
	{ MODKEY|ControlMask,			XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,      		XK_m,	   setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,				 XK_r,        spawn,    SHCMD("st -c dwm bash -c \"cd /home/kirito/.cache/yay/dwm && makepkg -if && killall dwm || read\"") },
	{ MODKEY,                        XK_s,     spawn,       SHCMD("subl3") },
    { MODKEY,                        XK_b,     spawn,       SHCMD("pgrep firefox && wmctrl -x -a Firefox || firefox") },
    { MODKEY,                        XK_e,     spawn,       SHCMD("wmctrl -x -a mpv || wmctrl -x -a ranger || st -c ranger -n ranger bash -c \"wmctrl -lp | grep $$ | awk '{print $1}' | xargs wmctrl -i -a; ranger\"") },
    { MODKEY|ShiftMask,              XK_e,     spawn,       SHCMD("st -c ranger -n ranger bash -c \"wmctrl -lp | grep $$ | awk '{print $1}' | xargs wmctrl -i -a; ranger\"") },
    { MODKEY,                        XK_t,        spawn,       SHCMD("wmctrl -x -a St || st bash -c \"wmctrl -lp | grep $$ | awk '{print $1}' | xargs wmctrl -i -a; bash\"") },
    { MODKEY,                        XK_Return,   spawn,       SHCMD("st bash -c \"wmctrl -lp | grep $$ | awk '{print $1}' | xargs wmctrl -i -a; bash\"") },
    { MODKEY,                        XK_n,        spawn,       SHCMD("network") },
    { MODKEY|ControlMask,            XK_f,        spawn,       SHCMD("mocp --seek 10") },
    { MODKEY|ControlMask,            XK_g,        spawn,       SHCMD("mocp --seek -10") },
    { MODKEY|ShiftMask,				 XK_n,        spawn,       SHCMD("nmcli radio wifi | grep disable && nmcli radio wifi on || nmcli radio wifi off") },
    { NULL,                          XK_Print,    spawn,       SHCMD("gnome-screenshot -f /storage/pictures/$(date '+%F_%T').png") },
    { MODKEY,                        XK_Print,    spawn,       SHCMD("gnome-screenshot -a -f /storage/pictures/$(date '+%F_%T').png") },
    { MODKEY,                        XK_i,        spawn,       SHCMD("subl3 -w ~/.config/dwm/config.h") },
    { MODKEY,                        XK_u,        spawn,       SHCMD("unmount") },
    { MODKEY,                        XK_g,        spawn,       SHCMD("pgrep mutt && wmctrl -x -a mail || st -c mail -n mail -g 100x25+350+200 bash -c \"wmctrl -x -a mail;mutt\"") },
    { MODKEY,                        XK_m,        spawn,       SHCMD("mount-all") },
    { MODKEY,                        XK_r,        spawn,       SHCMD("subl3 ~/.config/ranger/rc.conf") },
    { MODKEY|ShiftMask,            XK_t,        spawn,       SHCMD("task-manager") },
    { MODKEY|ControlMask,            XK_y,        spawn,       SHCMD("firefox-search y") },
    { MODKEY|ControlMask,            XK_l,        spawn,       SHCMD("firefox-search") },
    { MODKEY|ShiftMask,              XK_b,        spawn,       SHCMD("open-book") },
    { MODKEY|ShiftMask,              XK_c,        spawn,       SHCMD("open-config") },
    // { MODKEY ,           			 XK_q,   	  spawn,       SHCMD("rofi -show calc -modi \"calc:qalc +u8 -nocurrencies\"") },
    { MODKEY ,           			 XK_q,   	  spawn,       SHCMD("st -c qalc qalc") },
    { MODKEY|ShiftMask,              XK_y,        spawn,       SHCMD("loginctl reboot") },
    { MODKEY|ShiftMask,              XK_s,        spawn,       SHCMD("loginctl suspend") },
    { MODKEY|ShiftMask,              XK_x,        spawn,       SHCMD("killall xinit") },
    // { MODKEY,                        XK_a,       spawn,     	SHCMD("rofi -show run") },
    { MODKEY|ShiftMask,              XK_Delete,  spawn,       SHCMD("delete-song-wallpaper s") },
    { MODKEY|ControlMask,            XK_Delete,  spawn,       SHCMD("delete-song-wallpaper i") },
    { MODKEY|ControlMask,            XK_x,  spawn,       SHCMD("xrdb -load ~/.Xresources") },
    { MODKEY,                       XK_d,       spawn,     	   SHCMD("song-select") },
    { MODKEY|ShiftMask,				XK_d,       spawn,     	   SHCMD("song-select a") },
    // { MODKEY,                       XK_f,		fullscreen,     {0} },
    // { MODKEY,             			XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_f,       spawn,     	   SHCMD("tog-fs") },
    { MODKEY,                       XK_p,       spawn,     	   SHCMD("uninstall") },
    { MODKEY|ShiftMask,             XK_s,       spawn,     	   SHCMD("systemctl suspend -i") },
    { MODKEY|ShiftMask,             XK_y,       spawn,     	   SHCMD("reboot") },
    { MODKEY|ShiftMask,             XK_l,       spawn,     	   SHCMD("slock") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

