/* конфигурационный файл DWM. By DevFalongor (c), 2023 */

/* Внещний вид */
static const unsigned int borderpx  = 1;        /* толщина рамки вокруг окна */
static const unsigned int snap      = 32;       /* на каком расстоянии окно прилипает к краю экрана, другому окну... */
static const int showbar            = 1;        /* 0 не показывать панель, можно все равно показать по mod+b */
static const int gappx              = 5;        /* размер гапсов работает при установке патча dwm-ru_gaps-6.2.diff */
static const int topbar             = 1;        /* 0 панель внизу */
static const char *fonts[]          = { "Source Code Pro:size=10" };
static const char dmenufont[]       = "Source Code Pro:size=10";
static const char col_gray1[]       = "#191716";
static const char col_gray2[]       = "#272727";
static const char col_gray3[]       = "#50c878";
static const char col_gray4[]       = "#50c878";
static const char col_cyan[]        = "#7d98a1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* Названия тегов */
static const char *tags[] = { "▲", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]" };

/* Правила запуска приложений, узнать класс окна xprop | grep WM_CLASS */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* Layouts */
static const float mfact     = 0.65; /* размер мастер-окна по дефолту [0.05..0.95] */
static const int nmaster     = 1;    /* количество приложений в мастер-зоне */
static const int resizehints = 10;    /* 1 means respect size hints in tiled resizals яхз */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */ /* обзначения для каждого из режимов */
	{ "[Tile]",      tile },    /* тайлинг */
	{ "[Float]",      NULL },    /* плавающий */
	{ "[Monocle]",      monocle }, /* монокль */
};

/* key definitions */
#define MODKEY Mod4Mask /* Mod1Mask - alt */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Наши команды */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* настройки кнопок мыши */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} }, /* выбрать приложение */
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} }, /* выбрать приложение */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} }, /* при нажатии по заголовку в баре переключается между окнами */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } }, /* запустить эмуулятор терминала */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, /* переместить прилжение */
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} }, /* сделать приложение плавающим */
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} }, /* изменение размеров приложения */
	{ ClkTagBar,            0,              Button1,        view,           {0} }, /* перейти на воркспэйс */
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} }, /* объединить воркспэйсы в один */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} }, /* перенести приложение на воркспэйс */
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} }, /* продублировать приложение на воркспэйс */
};
