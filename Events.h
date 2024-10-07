#ifndef EVENTS_H
#define EVENTS_H

enum class EventType {
    LMOUSE_PRESS,
    LMOUSE_RELEASE,
    RMOUSE_PRESS,
    RMOUSE_RELEASE,
    MOUSE_MOVE,
    MOUSE_SCROLL,
    KEY_PRESS,
    KEY_RELEASE
};

struct LMousePress {

};

struct LMouseRelease {

};

struct RMousePress {

};

struct RMouseRelease {

};

struct MouseMove {

};

struct MouseScroll {

};

struct KeyPress {

};

struct KeyRelease {

};

// struct Event {
//     EventType type;

//     union {
//         LMousePress lmouse_press;
//         LMouseRelease lmouse_press;

//     };
// };

#endif