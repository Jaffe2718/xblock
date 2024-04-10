use fltk::{app, draw, enums, frame};
use fltk::prelude::*;

pub struct ApplicationUI {
    pub ui_home: UiHome,
    pub ui_3x3: Ui3x3,
    pub ui_4x4: Ui4x4,
    pub ui_5x5: Ui5x5,
    pub ui_help: UiHelp,
    pub ui_win: UiWin,
    pub f_time: frame::Frame,
}


pub struct UiHome {
    pub f_title: frame::Frame,
    pub f_3x3: frame::Frame,
    pub f_4x4: frame::Frame,
    pub f_5x5: frame::Frame,
    pub f_quit: frame::Frame,
    pub f_help: frame::Frame,
}


pub struct _Menu {
    pub f_menu: frame::Frame,
    pub f_home: frame::Frame,
    pub f_reset: frame::Frame,
}



pub struct Ui3x3 {
    pub menu: _Menu,
    pub blocks: Vec<frame::Frame>
}


pub struct Ui4x4 {
    pub menu: _Menu,
    pub blocks: Vec<frame::Frame>
}


pub struct Ui5x5 {
    pub menu: _Menu,
    pub blocks: Vec<frame::Frame>
}


pub struct UiHelp {
    pub f_title: frame::Frame,
    pub tips: Vec<frame::Frame>,
    pub example: Vec<frame::Frame>,
}


pub struct UiWin {
    pub f_title: frame::Frame,
    pub f_time: frame::Frame,
    pub f_tip: frame::Frame,
}


fn _draw_broader(w: &mut frame::Frame) {
    draw::set_line_style(draw::LineStyle::Solid, 4);
    draw::draw_line(w.x() + w.w(), w.y() + 2, w.x(), w.y() + 2);
    draw::draw_line(w.x() + 2, w.y(), w.x() + 2, w.y() + w.h());
    draw::draw_line(w.x(), w.y() + w.h() - 2, w.x() + w.w(), w.y() + w.h() - 2);
    draw::draw_line(w.x() + w.w() - 2, w.y() + w.h(), w.x() + w.w() - 2, w.y());
}


impl ApplicationUI {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {
        let mut _f_time = frame::Frame::new(240, 70, 120, 80, "");
        _f_time.set_label_size(24);
        _f_time.set_label_font(enums::Font::TimesBold);
        let mut _ui_home = UiHome::new(wind);
        let mut _ui_3x3 = Ui3x3::new(wind);
        let mut _ui_4x4 = Ui4x4::new(wind);
        let mut _ui_5x5 = Ui5x5::new(wind);
        let mut _ui_help = UiHelp::new(wind);
        let mut _ui_win = UiWin::new(wind);

        let mut _app_ui = ApplicationUI {
            ui_home: _ui_home,
            ui_3x3: _ui_3x3,
            ui_4x4: _ui_4x4,
            ui_5x5: _ui_5x5,
            ui_help: _ui_help,
            ui_win: _ui_win,
            f_time: _f_time,
        };
        _app_ui.ui_home.show();
        _app_ui.ui_3x3.hide();
        _app_ui.ui_4x4.hide();
        _app_ui.ui_5x5.hide();
        _app_ui.ui_help.hide();
        _app_ui.ui_win.hide();
        wind.add(&_app_ui.f_time);
        _app_ui.f_time.hide();
        return _app_ui;
    }

    pub fn switch_ui(&mut self, ui_id: u8) {  // 0 -> home, 1 -> 3x3, 2 -> 4x4, 3 -> 5x5, 4 -> help, 5 -> win
        match ui_id {
            0 => {                    // switch to home
                self.ui_home.show();
                self.ui_3x3.hide();
                self.ui_4x4.hide();
                self.ui_5x5.hide();
                self.ui_help.hide();
                self.ui_win.hide();
            }
            1 => {                    // switch to 3x3
                self.ui_home.hide();
                self.ui_3x3.show();
                self.ui_4x4.hide();
                self.ui_5x5.hide();
                self.ui_help.hide();
                self.ui_win.hide();
            }
            2 => {                    // switch to 4x4
                self.ui_home.hide();
                self.ui_3x3.hide();
                self.ui_4x4.show();
                self.ui_5x5.hide();
                self.ui_help.hide();
                self.ui_win.hide();
            }
            3 => {                    // switch to 5x5
                self.ui_home.hide();
                self.ui_3x3.hide();
                self.ui_4x4.hide();
                self.ui_5x5.show();
                self.ui_help.hide();
                self.ui_win.hide();
            }
            4 => {                    // switch to help
                self.ui_home.hide();
                self.ui_3x3.hide();
                self.ui_4x4.hide();
                self.ui_5x5.hide();
                self.ui_help.show();
                self.ui_win.hide();
            }
            5 => {                    // switch to win
                self.ui_home.hide();
                self.ui_3x3.hide();
                self.ui_4x4.hide();
                self.ui_5x5.hide();
                self.ui_help.hide();
                self.ui_win.show();
            }
            _ => {}
        }
    }

    pub fn set_time(&mut self, time_ms: usize) {
        // time_ms: millisecond, turn to mm:ss
        let mut _time = String::new();
        let _min = time_ms / 60000;
        let _sec = (time_ms - _min * 60000) / 1000;
        if _min < 10 {
            _time.push_str("0");
        }
        _time.push_str(&_min.to_string());
        _time.push_str(":");
        if _sec < 10 {
            _time.push_str("0");
        }
        _time.push_str(&_sec.to_string());
        self.f_time.set_label(&_time);
    }
}


impl UiHome {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {
        let mut _f_title = frame::Frame::new(100, 50, 400, 100, "Block Transform");
        _f_title.set_label_font(enums::Font::TimesBold);
        _f_title.set_label_size(40);
        let mut _f_3x3 = frame::Frame::new(100, 180, 400, 100, "3x3");
        _f_3x3.set_label_size(28);
        _f_3x3.set_label_font(enums::Font::TimesBold);
        _f_3x3.draw(_draw_broader);
        let mut _f_4x4 = frame::Frame::new(100, 330, 400, 100, "4x4");
        _f_4x4.set_label_size(28);
        _f_4x4.set_label_font(enums::Font::TimesBold);
        _f_4x4.draw(_draw_broader);
        let mut _f_5x5 = frame::Frame::new(100, 480, 400, 100, "5x5");
        _f_5x5.set_label_size(28);
        _f_5x5.set_label_font(enums::Font::TimesBold);
        _f_5x5.draw(_draw_broader);
        let mut _f_quit = frame::Frame::new(100, 630, 400, 100, "Quit");
        _f_quit.set_label_size(28);
        _f_quit.set_label_font(enums::Font::TimesBold);
        _f_quit.draw(_draw_broader);
        let mut _f_help = frame::Frame::new(480, 70, 60, 60, "?");
        _f_help.set_label_size(26);
        _f_help.set_label_font(enums::Font::TimesBold);
        _f_help.draw(_draw_broader);

        let mut ui_home =  Self {
            f_title: _f_title,
            f_3x3: _f_3x3,
            f_4x4: _f_4x4,
            f_5x5: _f_5x5,
            f_quit: _f_quit,
            f_help: _f_help
        };
        wind.add(&ui_home.f_title);
        wind.add(&ui_home.f_3x3);
        wind.add(&ui_home.f_4x4);
        wind.add(&ui_home.f_5x5);
        wind.add(&ui_home.f_quit);
        wind.add(&ui_home.f_help);
        return ui_home;
    }

    pub fn show(&mut self) {
        self.f_title.show();
        self.f_3x3.show();
        self.f_4x4.show();
        self.f_5x5.show();
        self.f_quit.show();
        self.f_help.show();
    }

    pub fn hide(&mut self) {
        self.f_title.hide();
        self.f_3x3.hide();
        self.f_4x4.hide();
        self.f_5x5.hide();
        self.f_quit.hide();
        self.f_help.hide();
    }
}


impl _Menu {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {
        let mut _f_menu = frame::Frame::new(40, 50, 520, 120, "");
        _f_menu.draw(_draw_broader);
        let mut _f_home = frame::Frame::new(60, 70, 120, 80, "Home");
        _f_home.set_label_size(26);
        _f_home.set_label_font(enums::Font::TimesBold);
        _f_home.draw(_draw_broader);
        let mut _f_reset = frame::Frame::new(420, 70, 120, 80, "Reset");
        _f_reset.set_label_size(26);
        _f_reset.set_label_font(enums::Font::TimesBold);
        _f_reset.draw(_draw_broader);

        let mut _menu = Self {
            f_menu: _f_menu,
            f_home: _f_home,
            f_reset: _f_reset,
        };
        wind.add(&_menu.f_menu);
        wind.add(&_menu.f_home);
        wind.add(&_menu.f_reset);
        return _menu;
    }

    pub fn show(&mut self) {
        self.f_menu.show();
        self.f_home.show();
        self.f_reset.show();
    }

    pub fn hide(&mut self) {
        self.f_menu.hide();
        self.f_home.hide();
        self.f_reset.hide();
    }
}


impl Ui3x3 {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {   // create block without number
        let mut _blocks = Vec::new();
        for i in 0..9 {
            let mut block = frame::Frame::new(60 + (i % 3) * 180, 240 + (i / 3) * 180,
                                              120, 120,"");
            block.set_label_size(36);
            block.set_label_font(enums::Font::TimesBold);
            block.draw(_draw_broader);
            _blocks.push(block);
        }
        let mut ui_3x3 = Self {
            menu: _Menu::new(wind),
            blocks: _blocks,
        };
        for i in 0..9 {  // add blocks to window
            wind.add(&ui_3x3.blocks[i]);
        }
        return ui_3x3;
    }

    pub fn show(&mut self) {
        self.menu.show();
        for block in &mut self.blocks {
            block.show();
        }
    }

    pub fn hide(&mut self) {
        self.menu.hide();
        for block in &mut self.blocks {
            block.hide();
        }
    }

    pub fn update(&mut self, _data: &Vec<usize>) {
        // update blocks' number by _data
        for i in 0..9 {
            if self.blocks[i].label() != _data[i].to_string() {
                self.blocks[i].set_label(&_data[i].to_string());
            }
        }
    }
}


impl Ui4x4 {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {   // create block without number
        let mut _blocks = Vec::new();
        for i in 0..16 {
            let mut block = frame::Frame::new(55 + (i % 4) * 130, 240 + (i / 4) * 130,
                                                 100, 100, "");
            block.set_label_size(36);
            block.set_label_font(enums::Font::TimesBold);
            block.draw(_draw_broader);
            _blocks.push(block);
        }
        let mut ui_4x4 = Self {
            menu: _Menu::new(wind),
            blocks: _blocks,
        };
        for i in 0..16 {  // add blocks to window
            wind.add(&ui_4x4.blocks[i]);
        }
        return ui_4x4;
    }

    pub fn show(&mut self) {
        self.menu.show();
        for block in &mut self.blocks {
            block.show();
        }
    }

    pub fn hide(&mut self) {
        self.menu.hide();
        for block in &mut self.blocks {
            block.hide();
        }
    }

    pub fn update(&mut self, _data: &Vec<usize>) {
        // update blocks' number by _data
        for i in 0..16 {
            if self.blocks[i].label() != _data[i].to_string() {
                self.blocks[i].set_label(&_data[i].to_string());
            }
        }
    }
}


impl Ui5x5 {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {   // create block without number
        let mut _blocks = Vec::new();
        for i in 0..25 {
            let mut block = frame::Frame::new(60 + (i % 5) * 100, 240 + (i / 5) * 100,
                                              80, 80, "");
            block.set_label_size(36);
            block.set_label_font(enums::Font::TimesBold);
            block.draw(_draw_broader);
            _blocks.push(block);
        }
        let mut ui_5x5 = Self {
            menu: _Menu::new(wind),
            blocks: _blocks,
        };
        for i in 0..25 {  // add blocks to window
            wind.add(&ui_5x5.blocks[i]);
        }
        return ui_5x5;
    }

    pub fn show(&mut self) {
        self.menu.show();
        for block in &mut self.blocks {
            block.show();
        }
    }

    pub fn hide(&mut self) {
        self.menu.hide();
        for block in &mut self.blocks {
            block.hide();
        }
    }

    pub fn update(&mut self, _data: &Vec<usize>) {
        // update blocks' number by _data
        for i in 0..25 {
            if self.blocks[i].label() != _data[i].to_string() {
                self.blocks[i].set_label(&_data[i].to_string());
            }
        }
    }
}


impl UiHelp {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self {
        let mut _f_title = frame::Frame::new(0, 50, 600, 60, "Block Transform Help");
        _f_title.set_label_size(32);
        _f_title.set_label_font(enums::Font::TimesBold);
        let help_text = ["This game requires players to arrange the",
            "disordered number blocks in ascending order",
            "from left to right and from top to bottom.",
            "In each game, the rules for exchanging",
            "numbers for each block are determined and",
            "players need to explore them themselves.",
            "For example, a 3x3 game should be like this:"];
        let mut _tips = Vec::new();
        for i in 0..7 {
            let mut _label = frame::Frame::new(0, 120 + 35 * i, 600, 35, help_text[i as usize]);
            _label.set_label_size(22);
            _label.set_label_font(enums::Font::TimesBold);
            _tips.push(_label);
        }
        let mut _example = Vec::new();
        let nums = ["1", "2", "3",
            "4", "5", "6",
            "7", "8", "9"];
        for i in 0..9 {
            let mut _block = frame::Frame::new(115 + 135 * (i % 3), 380 + 135 * (i / 3), 100, 100, nums[i as usize]);
            _block.set_label_size(32);
            _block.set_label_font(enums::Font::TimesBold);
            _block.draw(_draw_broader);
            _example.push(_block);
        }
        let mut ui_help = Self {
            f_title: _f_title,
            tips: _tips,
            example: _example,
        };
        wind.add(&ui_help.f_title);
        for _tip in &mut ui_help.tips {
            wind.add(_tip);
        }
        for _block in &mut ui_help.example {
            wind.add(_block);
        }
        return ui_help;
    }

    pub fn show(&mut self) {
        self.f_title.show();
        for _tip in &mut self.tips {
            _tip.show();
        }
        for _block in &mut self.example {
            _block.show();
        }
    }

    pub fn hide(&mut self) {
        self.f_title.hide();
        for _tip in &mut self.tips {
            _tip.hide();
        }
        for _block in &mut self.example {
            _block.hide();
        }
    }
}


impl UiWin {
    pub fn new(wind: &mut fltk::window::SingleWindow) -> Self{
        let mut _f_title = frame::Frame::new(0, 100, 600, 80, "Congratulations!");
        _f_title.set_label_font(enums::Font::TimesBold);
        _f_title.set_label_size(40);

        let mut _f_time = frame::Frame::new(0, 420, 600, 60, "");  // no time info, use update()
        _f_time.set_label_font(enums::Font::TimesBold);
        _f_time.set_label_size(32);

        let mut _f_tip = frame::Frame::new(0, 600, 600, 60, "Click anywhere to return to home page");
        _f_tip.set_label_font(enums::Font::TimesBold);
        _f_tip.set_label_size(24);

        let mut ui_win = Self {
            f_title: _f_title,
            f_time: _f_time,
            f_tip: _f_tip,
        };
        wind.add(&ui_win.f_title);
        wind.add(&ui_win.f_time);
        wind.add(&ui_win.f_tip);
        return ui_win;
    }

    pub fn show(&mut self) {
        self.f_title.show();
        self.f_time.show();
        self.f_tip.show();
    }

    pub fn hide(&mut self) {
        self.f_title.hide();
        self.f_time.hide();
        self.f_tip.hide();
    }

    pub fn update(&mut self, time_ms: usize) {  // update time use seconds as unit, example: 100.67s
        let mut time_str = String::new();
        // turn time_ms into seconds, use 2 decimal places, f64
        let time_s = (time_ms as f64) / 1000.0;
        let time_s_str = format!("Time: {:.2} sec", time_s);
        time_str.push_str(&time_s_str);
        self.f_time.set_label(&time_str);
    }
}