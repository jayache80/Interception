#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <thread>
#include <chrono>

#include <utils.h>
#include <interception.h>

#include "json.hpp"

using json = nlohmann::json;

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

InterceptionKeyStroke numrow_1_down = {scancode::numrow_1, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_2_down = {scancode::numrow_2, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_3_down = {scancode::numrow_3, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_4_down = {scancode::numrow_4, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_5_down = {scancode::numrow_5, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_6_down = {scancode::numrow_6, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_7_down = {scancode::numrow_7, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_8_down = {scancode::numrow_8, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_9_down = {scancode::numrow_9, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke numrow_0_down = {scancode::numrow_0, INTERCEPTION_KEY_DOWN, 0};

InterceptionKeyStroke numrow_1_up = {scancode::numrow_1, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_2_up = {scancode::numrow_2, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_3_up = {scancode::numrow_3, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_4_up = {scancode::numrow_4, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_5_up = {scancode::numrow_5, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_6_up = {scancode::numrow_6, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_7_up = {scancode::numrow_7, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_8_up = {scancode::numrow_8, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_9_up = {scancode::numrow_9, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke numrow_0_up = {scancode::numrow_0, INTERCEPTION_KEY_UP, 0};

InterceptionKeyStroke q_down = {scancode::q, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke w_down = {scancode::w, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke e_down = {scancode::e, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke r_down = {scancode::r, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke t_down = {scancode::t, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke y_down = {scancode::y, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke u_down = {scancode::u, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke i_down = {scancode::i, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke o_down = {scancode::o, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke p_down = {scancode::p, INTERCEPTION_KEY_DOWN, 0};

InterceptionKeyStroke q_up = {scancode::q, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke w_up = {scancode::w, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke e_up = {scancode::e, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke r_up = {scancode::r, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke t_up = {scancode::t, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke y_up = {scancode::y, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke u_up = {scancode::u, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke i_up = {scancode::i, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke o_up = {scancode::o, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke p_up = {scancode::p, INTERCEPTION_KEY_UP, 0};

InterceptionKeyStroke a_down = {scancode::a, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke s_down = {scancode::s, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke d_down = {scancode::d, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke f_down = {scancode::f, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke g_down = {scancode::g, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke h_down = {scancode::h, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke j_down = {scancode::j, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke k_down = {scancode::k, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke l_down = {scancode::l, INTERCEPTION_KEY_DOWN, 0};

InterceptionKeyStroke a_up = {scancode::a, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke s_up = {scancode::s, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke d_up = {scancode::d, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke f_up = {scancode::f, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke g_up = {scancode::g, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke h_up = {scancode::h, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke j_up = {scancode::j, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke k_up = {scancode::k, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke l_up = {scancode::l, INTERCEPTION_KEY_UP, 0};

InterceptionKeyStroke z_down = {scancode::z, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke x_down = {scancode::x, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke c_down = {scancode::c, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke v_down = {scancode::v, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke b_down = {scancode::b, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke n_down = {scancode::n, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke m_down = {scancode::m, INTERCEPTION_KEY_DOWN, 0};

InterceptionKeyStroke z_up = {scancode::z, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke x_up = {scancode::x, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke c_up = {scancode::c, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke v_up = {scancode::v, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke b_up = {scancode::b, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke n_up = {scancode::n, INTERCEPTION_KEY_UP, 0};
InterceptionKeyStroke m_up = {scancode::m, INTERCEPTION_KEY_UP, 0};

InterceptionKeyStroke enter_down = {scancode::enter, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke enter_up = {scancode::enter, INTERCEPTION_KEY_UP, 0};

InterceptionKeyStroke spacebar_down = {scancode::spacebar, INTERCEPTION_KEY_DOWN, 0};
InterceptionKeyStroke spacebar_up = {scancode::spacebar, INTERCEPTION_KEY_UP, 0};

std::map<std::string, InterceptionKeyStroke> string_to_keystroke {
    {"numrow_1_down", numrow_1_down},
    {"numrow_2_down", numrow_2_down},
    {"numrow_3_down", numrow_3_down},
    {"numrow_4_down", numrow_4_down},
    {"numrow_5_down", numrow_5_down},
    {"numrow_6_down", numrow_6_down},
    {"numrow_7_down", numrow_7_down},
    {"numrow_8_down", numrow_8_down},
    {"numrow_9_down", numrow_9_down},
    {"numrow_0_down", numrow_0_down},
    {"numrow_1_up", numrow_1_up},
    {"numrow_2_up", numrow_2_up},
    {"numrow_3_up", numrow_3_up},
    {"numrow_4_up", numrow_4_up},
    {"numrow_5_up", numrow_5_up},
    {"numrow_6_up", numrow_6_up},
    {"numrow_7_up", numrow_7_up},
    {"numrow_8_up", numrow_8_up},
    {"numrow_9_up", numrow_9_up},
    {"numrow_0_up", numrow_0_up},
    {"q_down", q_down},
    {"w_down", w_down},
    {"e_down", e_down},
    {"r_down", r_down},
    {"t_down", t_down},
    {"y_down", y_down},
    {"u_down", u_down},
    {"i_down", i_down},
    {"o_down", o_down},
    {"p_down", p_down},
    {"q_up", q_up},
    {"w_up", w_up},
    {"e_up", e_up},
    {"r_up", r_up},
    {"t_up", t_up},
    {"y_up", y_up},
    {"u_up", u_up},
    {"i_up", i_up},
    {"o_up", o_up},
    {"p_up", p_up},
    {"a_down", a_down},
    {"s_down", s_down},
    {"d_down", d_down},
    {"f_down", f_down},
    {"g_down", g_down},
    {"h_down", h_down},
    {"j_down", j_down},
    {"k_down", k_down},
    {"l_down", l_down},
    {"a_up", a_up},
    {"s_up", s_up},
    {"d_up", d_up},
    {"f_up", f_up},
    {"g_up", g_up},
    {"h_up", h_up},
    {"j_up", j_up},
    {"k_up", k_up},
    {"l_up", l_up},
    {"z_down", z_down},
    {"x_down", x_down},
    {"c_down", c_down},
    {"v_down", v_down},
    {"b_down", b_down},
    {"n_down", n_down},
    {"m_down", m_down},
    {"z_up", z_up},
    {"x_up", x_up},
    {"c_up", c_up},
    {"v_up", v_up},
    {"b_up", b_up},
    {"n_up", n_up},
    {"m_up", m_up},
    {"enter_down", enter_down},
    {"enter_up", enter_up},
    {"spacebar_down", spacebar_down},
    {"spacebar_up", spacebar_up},
};

std::map<std::string, unsigned int> string_to_sleep_time {
    {"sleep_250", 250},
    {"sleep_500", 500},
    {"sleep_750", 750},
    {"sleep_1000", 1000},
};

class MacroKeyStroke {
    public:
        MacroKeyStroke() : sleep_time(0) {}
        unsigned int sleep_time;
        InterceptionKeyStroke keystroke;
};

std::wstring to_wide_string(std::string& in)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    return utf8_conv.from_bytes(in);
}

bool operator==(
        const InterceptionKeyStroke& first,
        const InterceptionKeyStroke& second
        ) {
    return first.code == second.code && first.state == second.state;
}

bool operator<(
        const InterceptionKeyStroke& first,
        const InterceptionKeyStroke& second
        ) {
    if (first.state < second.state) {
        return true;
    }

    if (first.state == second.state) {
        return first.code < second.code;
    }

    return false;
}

std::vector<InterceptionKeyStroke> process(
        const InterceptionKeyStroke& kstroke,
        const std::map<InterceptionKeyStroke, std::vector<MacroKeyStroke>>& macros,
        const InterceptionContext& context,
        const InterceptionDevice& device,
        bool filter_device = true
        ) {
    std::vector<InterceptionKeyStroke> kstrokes;

    // Bail if we shouldn't be filtering this device or if we don't have a
    // macro defined for this key
    if (!filter_device || (macros.count(kstroke) == 0)) {
        // Pass through an unmapped key
        kstrokes.push_back(kstroke);
    } else {
        for (const auto& macro_keystroke : macros.at(kstroke)) {
            if (macro_keystroke.sleep_time != 0) {
                // Send we what have so far
                if (kstrokes.size() > 0) {
                    interception_send(
                            context,
                            device,
                            reinterpret_cast<InterceptionStroke*>(&kstrokes[0]),
                            static_cast<unsigned int>(kstrokes.size())
                    );
                }

                // Clear what we've sent
                kstrokes.clear();

                // Sleep
                std::cout << "sleeping for " << macro_keystroke.sleep_time << " ms\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(macro_keystroke.sleep_time));
                continue;
            }

            kstrokes.push_back(macro_keystroke.keystroke);
        }
    }

    // Send whatever remaining
    if (kstrokes.size() > 0) {
        interception_send(
                context,
                device,
                reinterpret_cast<InterceptionStroke*>(&kstrokes[0]),
                static_cast<unsigned int>(kstrokes.size())
        );
    }

    return kstrokes;
}

MacroKeyStroke parse_macro_keystroke(std::string macro_keystroke) {
    // Normal keystroke
    if (string_to_keystroke.count(macro_keystroke) != 0) {
        auto ret = MacroKeyStroke();
        ret.keystroke = string_to_keystroke[macro_keystroke];
        return ret;
    }

    // Sleep keystroke
    if (string_to_sleep_time.count(macro_keystroke) != 0) {
        auto ret = MacroKeyStroke();
        ret.sleep_time = string_to_sleep_time[macro_keystroke];
        return ret;
    }

    throw std::invalid_argument(
            "\"" + macro_keystroke + "\" is not a valid keystroke."
            );
}

void usage(char* prog_name) {
    std::cerr << "usage: " << prog_name << ": config_file";
}

int main(size_t argc, char** argv) {
    void *program_instance = try_open_single_program("407631B6-78D3-4EFC-A868-40BBB7204CF1");

    if (!program_instance) {
        return 1;
    }

    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    std::ifstream config_file(argv[1]);

    if (config_file.fail()) {
        std::cerr << "Error: Could not open config file: " << argv[1] << "\n";
        return 1;
    }

    json config_data;

    try {
        config_data = json::parse(config_file);
    } catch (json::parse_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke kstroke;

    wchar_t hardware_id[500];
    std::string hardware_id_to_filter;

    try {
        hardware_id_to_filter = config_data["hardware_id"].get<std::string>();
    } catch (json::type_error& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Error: failed parsing hardware_id\n";
        return 1;
    }

    std::wstring hardware_id_to_filter_w = to_wide_string(hardware_id_to_filter);
    bool filter_device = false;

    std::map<InterceptionKeyStroke, std::vector<MacroKeyStroke>> macros;

    int parsing_errors = 0;

    for (auto& el : config_data.items()) {
        if (el.key() == "hardware_id") {
            continue;
        }

        if (string_to_keystroke.count(el.key()) == 0) {
            std::cerr << "Error: Cannot map key: " << el.key() << "\n";
            parsing_errors++;
            continue;
        }

        std::vector<MacroKeyStroke> macro_keystrokes;

        // TODO: Check for valid list of strings
        for (auto& macro_keystroke : el.value()) {
            std::string macro_keystroke_s = macro_keystroke.get<std::string>();
            MacroKeyStroke macro_keystroke_;
            try {
                macro_keystrokes.push_back(parse_macro_keystroke(macro_keystroke_s));
            } catch (std::exception const& ex) {
                std::cerr << "Error: " << ex.what() << "\n";
                return 1;
            }
        }

        macros[string_to_keystroke[el.key()]] = macro_keystrokes;
    }

    if (parsing_errors != 0) {
        std::cerr << "Error: config file could not be parsed.\n";
        return 1;
    }

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

        if (hardware_id_length > 0 && hardware_id_length < sizeof(hardware_id)) {
            if (wcscmp(hardware_id, hardware_id_to_filter_w.c_str()) == 0) {
                std::cout << ".";
                filter_device = true;
            }
        }

        std::vector<InterceptionKeyStroke> kstrokes = process(
                kstroke,
                macros,
                context,
                device,
                filter_device
                );
        filter_device = false;

    }

    interception_destroy_context(context);

    close_single_program(program_instance);
}
