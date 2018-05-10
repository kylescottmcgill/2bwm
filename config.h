
#define MOD XCB_MOD_MASK_4 /* Super/Windows key  or check xmodmap(1) with -pm  defined in /usr/include/xcb/xproto.h */
#define CURSOR_POSITION MIDDLE
static const float resize_keep_aspect_ratio = 1.03;
static const bool resize_by_line = true;
static const bool inverted_colors = false;

static const uint16_t movements[] = {
  2, // Move Step Slow
  20, // Move Step Fast
  2, // Mouse Slow
  20  // Mouse Fast
};

static const uint8_t offsets[] = {
  10, // offsetx
  10, // offsety
  20, // max width
  20  // max height
};

static const char * colors[] = {
  "#ffffff", // focus
  "#cccccc", // unfocus
  "#cccccc", // fixed
  "#ab1b1b", // unkil
  "#cccccc", // fixedunkil
  "#ffffff", // outerborder
  "#cccccc"  // emptycol
};

static const uint8_t borders[] = {
  0, // out border size
  1, // full border size
  1, // magnet border size
  1  // resize border size
};

#define LOOK_INTO "WM_CLASS"
static const char * ignore_names[] = {
  "chromium",
  "bar",
  "rofi",
};

//
///--Menus and Programs---///
static const char *terminal[] =             { "/usr/bin/alacritty", NULL };
static const char *rofi[] =                 { "/usr/bin/rofi", "-show", "run", NULL};
static const char *browser[] =              { "/usr/bin/chromium", NULL };
static const char *screenshot_selection[] = { "screenshot", "--selection", NULL };
static const char *screenshot_window[] =    { "screenshot", "--window", NULL };

///---Media and Audio---///
static const char *volup[] =                { "pavol", "up", NULL };
static const char *voldown[] =              { "pavol", "down", NULL };
static const char *volmute[] =              { "pavol", "mute", NULL };

///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
    Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
    maxhalf(&arg2);
    Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
    teleport(&arg3);
}
///---Shortcuts---///
/* Check /usr/include/X11/keysymdef.h for the list of all keys
 * 0x000000 is for no modkey
 * If you are having trouble finding the right keycode use the `xev` to get it
 * For example:
 * KeyRelease event, serial 40, synthetic NO, window 0x1e00001,
 *  root 0x98, subw 0x0, time 211120530, (128,73), root:(855,214),
 *  state 0x10, keycode 171 (keysym 0x1008ff17, XF86AudioNext), same_screen YES,
 *  XLookupString gives 0 bytes:
 *  XFilterEvent returns: False
 *
 *  The keycode here is keysym 0x1008ff17, so use  0x1008ff17
 */

#define DESKTOPCHANGE(K,N) \
{  MOD ,             K,              changeworkspace, {.i=N}}, \
{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_NEXT}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=TWOBWM_FOCUS_PREVIOUS}},
    // Kill a window
    {  MOD ,              XK_q,          deletewin,         {}},
    // Resize a window
    {  MOD |SHIFT,    XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP}},
    {  MOD |SHIFT,    XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN}},
    {  MOD |SHIFT,    XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT}},
    {  MOD |SHIFT,    XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT}},
    // Resize a window slower
    {  MOD |SHIFT|ALT,        XK_k,          resizestep,        {.i=TWOBWM_RESIZE_UP_SLOW}},
    {  MOD |SHIFT|ALT,        XK_j,          resizestep,        {.i=TWOBWM_RESIZE_DOWN_SLOW}},
    {  MOD |SHIFT|ALT,        XK_l,          resizestep,        {.i=TWOBWM_RESIZE_RIGHT_SLOW}},
    {  MOD |SHIFT|ALT,        XK_h,          resizestep,        {.i=TWOBWM_RESIZE_LEFT_SLOW}},
    // Move a window
    {  MOD,                   XK_k,          movestep,          {.i=TWOBWM_MOVE_UP}},
    {  MOD,                   XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN}},
    {  MOD,                   XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT}},
    {  MOD,                   XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT}},
    // Move a window slower
    {  MOD |ALT,              XK_k,          movestep,          {.i=TWOBWM_MOVE_UP_SLOW}},
    {  MOD |ALT,              XK_j,          movestep,          {.i=TWOBWM_MOVE_DOWN_SLOW}},
    {  MOD |ALT,              XK_l,          movestep,          {.i=TWOBWM_MOVE_RIGHT_SLOW}},
    {  MOD |ALT,              XK_h,          movestep,          {.i=TWOBWM_MOVE_LEFT_SLOW}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER}},
    // Center y:
    {  MOD |SHIFT,        XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_Y}},
    // Center x:
    {  MOD |CONTROL,      XK_g,          teleport,          {.i=TWOBWM_TELEPORT_CENTER_X}},
    // Top left:
    {  MOD ,              XK_y,          teleport,          {.i=TWOBWM_TELEPORT_TOP_LEFT}},
    // Top right:
    {  MOD ,              XK_u,          teleport,          {.i=TWOBWM_TELEPORT_TOP_RIGHT}},
    // Bottom left:
    {  MOD ,              XK_b,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_LEFT}},
    // Bottom right:
    {  MOD ,              XK_n,          teleport,          {.i=TWOBWM_TELEPORT_BOTTOM_RIGHT}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Home,       resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_GROW}},
    {  MOD ,              XK_End,        resizestep_aspect, {.i=TWOBWM_RESIZE_KEEP_ASPECT_SHRINK}},
    // Full screen window without borders
    {  MOD |SHIFT,              XK_x,          maximize,          {.i=TWOBWM_FULLSCREEN}},
    //Full screen window without borders overiding offsets
    {  MOD ,       XK_x,          maximize,          {.i=TWOBWM_FULLSCREEN_OVERRIDE_OFFSETS}},
    // Maximize vertically
    {  MOD ,              XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_VERTICALLY}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=TWOBWM_MAXIMIZE_HORIZONTALLY}},
    // Maximize and move
    // vertically left
    {  MOD |SHIFT,        XK_y,          maxhalf,       {.i=TWOBWM_MAXHALF_VERTICAL_LEFT}},
    // vertically right
    {  MOD |SHIFT,        XK_u,          maxhalf,       {.i=TWOBWM_MAXHALF_VERTICAL_RIGHT}},
    // horizontally left
    {  MOD |SHIFT,        XK_b,          maxhalf,       {.i=TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
    // horizontally right
    {  MOD |SHIFT,        XK_n,          maxhalf,       {.i=TWOBWM_MAXHALF_HORIZONTAL_TOP}},
    //fold half vertically
    {  MOD |SHIFT|CONTROL,XK_y,          maxhalf,       {.i=TWOBWM_MAXHALF_FOLD_VERTICAL}},
    //fold half horizontally
    {  MOD |SHIFT|CONTROL,XK_b,          maxhalf,       {.i=TWOBWM_MAXHALF_FOLD_HORIZONTAL}},
    //unfold vertically
    {  MOD |SHIFT|CONTROL,XK_u,         maxhalf,        {.i=TWOBWM_MAXHALF_UNFOLD_VERTICAL}},
    //unfold horizontally
    {  MOD |SHIFT|CONTROL,XK_n,         maxhalf,        {.i=TWOBWM_MAXHALF_UNFOLD_HORIZONTAL}},
    // Center and Min-Max
    {  MOD ,              XK_z,     halfandcentered,{.i=0}},
    {  MOD ,              XK_period,    changescreen,   {.i=TWOBWM_NEXT_SCREEN}}, // Next Screen
    {  MOD ,              XK_comma,     changescreen,   {.i=TWOBWM_PREVIOUS_SCREEN}}, // Previous Screen
    {  MOD ,              XK_f,         fix,            {}}, // Make the window present on all workspaces
    {  MOD ,              XK_space,     start,          {.com = rofi}},
    {  MOD ,              XK_a,         start,          {.com = browser}},
    {  MOD ,              XK_Return,    start,          {.com = terminal}},
    {  MOD ,              XK_w,         start,          {.com = screenshot_window}},
    {  MOD ,              XK_e,         start,          {.com = screenshot_selection}},
    // Media and Audio Keys
    {  0x000000,          0x1008ff13,   start,          {.com = volup}},
    {  0x000000,          0x1008ff11,   start,          {.com = voldown}},
    {  0x000000,          0x1008ff12,   start,          {.com = volmute}},
    {  MOD,                     XK_d,   start,          {.com = volup}},
    {  MOD,                     XK_s,   start,          {.com = voldown}},

    //{  0x000000,        0x1008ff03,   start,          {.com = brightdown}},
    //{  0x000000,        0x1008ff02,   start,          {.com = brightup}},
      // Exit or restart 2bwm
    {  MOD |CONTROL,      XK_q,         twobwm_exit,    {.i=0}},
    {  MOD |CONTROL,      XK_r,         twobwm_restart, {.i=0}},

    // Change current workspace
       DESKTOPCHANGE(     XK_1,                             0)
       DESKTOPCHANGE(     XK_2,                             1)
       DESKTOPCHANGE(     XK_3,                             2)
       DESKTOPCHANGE(     XK_4,                             3)
       DESKTOPCHANGE(     XK_5,                             4)
       DESKTOPCHANGE(     XK_6,                             5)
       DESKTOPCHANGE(     XK_7,                             6)
       DESKTOPCHANGE(     XK_8,                             7)
       DESKTOPCHANGE(     XK_9,                             8)
       DESKTOPCHANGE(     XK_0,                             9)

    // Raise or lower a window
    //{  MOD ,              XK_r,          raiseorlower,      {}},
    // Next/Previous workspace
    //{  MOD ,              XK_v,          nextworkspace,     {}},
    //{  MOD ,              XK_c,          prevworkspace,     {}},
    // Move to Next/Previous workspace
    //{  MOD |SHIFT ,       XK_v,          sendtonextworkspace,{}},
    //{  MOD |SHIFT ,       XK_c,          sendtoprevworkspace,{}},
    // Iconify the window
    //{  MOD ,              XK_i,          hide,              {}},
    // Make the window unkillable
    //{  MOD ,              XK_a,          unkillable,        {}},
    // Make the window appear always on top
    //{  MOD ,              XK_t,          always_on_top,     {}},
    // Move the cursor
    //{  MOD ,              XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP_SLOW}},
    //{  MOD ,              XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN_SLOW}},
    //{  MOD ,              XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT_SLOW}},
    //{  MOD ,              XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT_SLOW}},
    // Move the cursor faster
    //{  MOD |SHIFT,        XK_Up,         cursor_move,       {.i=TWOBWM_CURSOR_UP}},
    //{  MOD |SHIFT,        XK_Down,       cursor_move,       {.i=TWOBWM_CURSOR_DOWN}},
    //{  MOD |SHIFT,        XK_Right,      cursor_move,       {.i=TWOBWM_CURSOR_RIGHT}},
    //{  MOD |SHIFT,        XK_Left,       cursor_move,       {.i=TWOBWM_CURSOR_LEFT}},
};
// the last argument makes it a root window only event
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}},
    {  MOD|CONTROL,XCB_BUTTON_INDEX_3,     start,         {.com = rofi}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}}
    //{ CONTROL, XCB_BUTTON_INDEX_4, start, {.com = dummy}},
    //{ CONTROL, XCB_BUTTON_INDEX_5, start, {.com = dummy}}
};


// vim: ft=c ts=4 sw=4 tw=0 fdm=marker foldlevel=0
