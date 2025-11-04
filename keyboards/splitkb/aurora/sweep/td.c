
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Tap Dance declarations
enum {
  // a -> ä
  TD_E_AE,
  // w -> å
  TD_W_AA,
  // o -> ö
  TD_O_OE,
  // . -> ?
  TD_DOTQU,
  // , -> !
  TD_COMEX,
  // enter -> ctrl + enter
  TD_ENTER,
  // ()
  TD_PAREN,
  // {}
  TD_CURLY,
  // <>
  TD_ANGLE,
  // []
  TD_BRACKET,
  // ''
  TD_QUOT,
  // ""
  TD_DQUO,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

void paren_finished(tap_dance_state_t *state, void *user_data);
void paren_reset(tap_dance_state_t *state, void *user_data);
void curly_finished(tap_dance_state_t *state, void *user_data);
void curly_reset(tap_dance_state_t *state, void *user_data);
void angle_finished(tap_dance_state_t *state, void *user_data);
void angle_reset(tap_dance_state_t *state, void *user_data);
void bracket_finished(tap_dance_state_t *state, void *user_data);
void bracket_reset(tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

static td_tap_t paren_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t curly_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t angle_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t bracket_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t quot_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t dquo_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void paren_finished(tap_dance_state_t *state, void *user_data) {
    paren_tap_state.state = cur_dance(state);
    switch (paren_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: register_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP: tap_code16(KC_LPRN); tap_code16(KC_RPRN); register_code(KC_LEFT); break;
        default: break;
    }
}

void paren_reset(tap_dance_state_t *state, void *user_data) {
    switch (paren_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LPRN); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RPRN); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default: break;
    }
    paren_tap_state.state = TD_NONE;
}

void curly_finished(tap_dance_state_t *state, void *user_data) {
    curly_tap_state.state = cur_dance(state);
    switch (curly_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: register_code16(KC_RCBR); break;
        case TD_DOUBLE_TAP: tap_code16(KC_LCBR); tap_code16(KC_RCBR); register_code(KC_LEFT); break;
        default: break;
    }
}

void curly_reset(tap_dance_state_t *state, void *user_data) {
    switch (curly_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LCBR); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RCBR); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default: break;
    }
    curly_tap_state.state = TD_NONE;
}

void bracket_finished(tap_dance_state_t *state, void *user_data) {
    bracket_tap_state.state = cur_dance(state);
    switch (bracket_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: register_code16(KC_RBRC); break;
        case TD_DOUBLE_TAP: tap_code16(KC_LBRC); tap_code16(KC_RBRC); register_code(KC_LEFT); break;
        default: break;
    }
}

void bracket_reset(tap_dance_state_t *state, void *user_data) {
    switch (bracket_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_RBRC); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default: break;
    }
    bracket_tap_state.state = TD_NONE;
}

void angle_finished(tap_dance_state_t *state, void *user_data) {
    angle_tap_state.state = cur_dance(state);
    switch (angle_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_LT); break;
        case TD_SINGLE_HOLD: register_code16(KC_GT); break;
        case TD_DOUBLE_TAP: tap_code16(KC_LT); tap_code16(KC_GT); register_code(KC_LEFT); break;
        default: break;
    }
}

void angle_reset(tap_dance_state_t *state, void *user_data) {
    switch (angle_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LT); break;
        case TD_SINGLE_HOLD: unregister_code16(KC_GT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        default: break;
    }
    angle_tap_state.state = TD_NONE;
}


void quot_finished(tap_dance_state_t *state, void *user_data) {
    quot_tap_state.state = cur_dance(state);
    switch (quot_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_QUOT); break;
        case TD_DOUBLE_TAP: tap_code16(KC_QUOT); tap_code16(KC_QUOT); register_code(KC_LEFT); break;
        default: break;
    }
}

void quot_reset(tap_dance_state_t *state, void *user_data) {
    switch (quot_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_QUOT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        default: break;
    }
    quot_tap_state.state = TD_NONE;
}


void dquo_finished(tap_dance_state_t *state, void *user_data) {
    dquo_tap_state.state = cur_dance(state);
    switch (dquo_tap_state.state) {
        case TD_SINGLE_TAP: register_code16(KC_DQUO); break;
        case TD_DOUBLE_TAP: tap_code16(KC_DQUO); tap_code16(KC_DQUO); register_code(KC_LEFT); break;
        default: break;
    }
}

void dquo_reset(tap_dance_state_t *state, void *user_data) {
    switch (dquo_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(KC_DQUO); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT); break;
        default: break;
    }
    dquo_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_E_AE] = ACTION_TAP_DANCE_TAP_HOLD(KC_E, RALT(KC_A)),
  [TD_W_AA] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, RALT(KC_W)),
  [TD_O_OE] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, RALT(KC_O)),
  [TD_DOTQU] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, KC_QUES),
  [TD_COMEX] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_EXLM),
  [TD_ENTER] = ACTION_TAP_DANCE_TAP_HOLD(KC_ENT, LCTL(KC_ENT)),
  [TD_PAREN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren_finished, paren_reset),
  [TD_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, curly_finished, curly_reset),
  [TD_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bracket_finished, bracket_reset),
  [TD_ANGLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, angle_finished, angle_reset),
  [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
  [TD_DQUO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dquo_finished, dquo_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_E_AE):
        case TD(TD_W_AA):
        case TD(TD_O_OE):
        case TD(TD_ENTER):
        case TD(TD_DOTQU):
        case TD(TD_COMEX):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}
