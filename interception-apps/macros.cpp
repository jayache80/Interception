#include <vector>
#include <iostream>

#include <utils.h>
#include <interception.h>

namespace scancode {
    enum {
        esc = 0x01,

        numrow_1 = 0x02,
        numrow_2 = 0x03,
        numrow_3 = 0x04,
        numrow_4 = 0x05,
        numrow_5 = 0x06,
        numrow_6 = 0x07,
        numrow_7 = 0x08,
        numrow_8 = 0x09,
        numrow_9 = 0x0a,
        numrow_0 = 0x0b,
        minus = 0x0c,
        equals = 0x0d,
        backspace = 0x0e,

        tab = 0x0f,
        q = 0x10,
        w = 0x11,
        e = 0x12,
        r = 0x13,
        t = 0x14,
        y = 0x15,
        u = 0x16,
        i = 0x17,
        o = 0x18,
        p = 0x19,
        left_bracket = 0x1a,
        right_bracket = 0x1b,

        enter = 0x1c,

        left_ctrl = 0x1d,
        a = 0x1e,
        s = 0x1f,
        d = 0x20,
        f = 0x21,
        g = 0x22,
        h = 0x23,
        j = 0x24,
        k = 0x25,
        l = 0x26,
        semicolon = 0x27,
        quote = 0x28,

        tilde = 0x29,
        left_shift = 0x2a,
        backslash = 0x2b,

        z = 0x2c,
        x = 0x2d,
        c = 0x2e,
        v = 0x2f,
        b = 0x30,
        n = 0x31,
        m = 0x32,
        less_than = 0x33,
        greater_than = 0x34,
        slash = 0x35,
        right_shift = 0x36,

        keypad_asterisk = 0x37,
        left_alt = 0x38,
        spacebar = 0x39,
        capslock = 0x3a,

        f1 = 0x3b,
        f2 = 0x3c,
        f3 = 0x3d,
        f4 = 0x3e,
        f5 = 0x3f,
        f6 = 0x40,
        f7 = 0x41,
        f8 = 0x42,
        f9 = 0x43,
        f10 = 0x44,

        numlock = 0x45,
        scrolllock = 0x46,

        keypad_home = 0x47,
        keypad_8 = 0x48,
        keypad_9 = 0x49,
        keypad_minus = 0x4a,
        keypad_4 = 0x4b,
        keypad_5 = 0x4c,
        keypad_6 = 0x4d,
        keypad_plus = 0x4e,
        keypad_1 = 0x4f,
        keypad_2 = 0x50,
        keypad_3 = 0x51,
        keypad_0 = 0x52,
        keypad_del = 0x53,
    };
}

InterceptionKeyStroke j_down = {scancode::j, INTERCEPTION_KEY_DOWN, 0};

InterceptionKeyStroke h_down = {scancode::h, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke e_down = {scancode::e, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke l_down = {scancode::l, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke o_down = {scancode::o, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke h_up = {scancode::h, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke e_up = {scancode::e, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke l_up = {scancode::l, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke o_up = {scancode::o, INTERCEPTION_KEY_UP, 0};

bool operator==(const InterceptionKeyStroke &first,
                const InterceptionKeyStroke &second) {
    return first.code == second.code && first.state == second.state;
}

std::vector<InterceptionKeyStroke> process(
        const InterceptionKeyStroke &kstroke,
        bool filter_device = true
        ) {
    std::vector<InterceptionKeyStroke> kstrokes;

    // Bail if we shouldn't be filtering this device
    if (!filter_device) {
        // Pass through an unmapped key
        kstrokes.push_back(kstroke);
        return kstrokes;
    }

    // Map "j" to "hello"
    if (kstroke == j_down) {
        kstrokes.push_back(h_down);
        kstrokes.push_back(h_up);
        kstrokes.push_back(e_down);
        kstrokes.push_back(e_up);
        kstrokes.push_back(l_down);
        kstrokes.push_back(l_up);
        kstrokes.push_back(l_down);
        kstrokes.push_back(l_up);
        kstrokes.push_back(o_down);
        kstrokes.push_back(o_up);
    }

    // Pass through an unmapped key
    if (kstrokes.empty()) {
        kstrokes.push_back(kstroke);
        return kstrokes;
    }

    return kstrokes;
}

int main() {
    void *program_instance = try_open_single_program("407631B6-78D3-4EFC-A868-40BBB7204CF1");
    if (!program_instance) {
        return 0;
    }

    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke kstroke;

    wchar_t hardware_id[500];
    wchar_t hardware_id_to_filter[] = L"TS_INPT\\TS_KBD";
    bool filter_device = false;

    raise_process_priority();

    context = interception_create_context();

    interception_set_filter(context, interception_is_keyboard,
                            INTERCEPTION_FILTER_KEY_DOWN |
                            INTERCEPTION_FILTER_KEY_UP);

    while (interception_receive(context, device = interception_wait(context),
                                (InterceptionStroke *)&kstroke, 1) > 0) {

        size_t hardware_id_length = interception_get_hardware_id(
                context,
                device,
                hardware_id,
                sizeof(hardware_id)
                );

        if(hardware_id_length > 0 && hardware_id_length < sizeof(hardware_id)) {
            if (wcscmp(hardware_id, hardware_id_to_filter) == 0) {
                std::wcout << L"Filtering " << hardware_id << "\n";
                filter_device = true;
            }
        }

        std::vector<InterceptionKeyStroke> kstrokes = process(kstroke, filter_device);
        filter_device = false;

        if (kstrokes.size() > 0) {
            interception_send(
                    context,
                    device,
                    reinterpret_cast<InterceptionStroke*>(&kstrokes[0]),
                    static_cast<unsigned int>(kstrokes.size())
            );
        }
    }

    interception_destroy_context(context);

    close_single_program(program_instance);
}
