use fltk::app::redraw;
use fltk::prelude::*;
use crate::xpack::game_ui::ApplicationUI;
use crate::xpack::graph;
use crate::xpack::graph::{gen_data, gen_rule, transform};


pub struct GameData {
    pub was_pressed: bool,
    pub ui_id: u8,        // 0 -> home, 1 -> 3x3, 2 -> 4x4, 3 -> 5x5, 4 -> help, 5 -> win
    pub t_start: Option<usize>,
    pub rule: Option<std::collections::HashMap<usize, usize>>,
    pub data: Option<Vec<usize>>
}


pub fn handle_events(gd: &mut GameData, app_ui: &mut ApplicationUI, mouse_x: i32, mouse_y: i32) {
    match gd.ui_id {
        0 => {      // home
            handle_home(gd, app_ui, mouse_x, mouse_y);
        }
        1 => {      // 3x3
            handle_3x3(gd, app_ui, mouse_x, mouse_y);
        }
        2 => {      // 4x4
            handle_4x4(gd, app_ui, mouse_x, mouse_y);
        }
        3 => {      // 5x5
            handle_5x5(gd, app_ui, mouse_x, mouse_y);
        }
        4..=5 => {  // help
            handle_other(gd, app_ui);
        }
        _ => {}     // impossible
    }
}


fn handle_home(gd: &mut GameData, app_ui: &mut ApplicationUI, mouse_x: i32, mouse_y: i32) {
    if 100 <= mouse_x && mouse_x <= 500 {
        match mouse_y {
            180..=280 => {        // click 3x3
                gd.ui_id = 1;
                gd.t_start = Some(std::time::SystemTime::now()       // 单位毫秒
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize);
                gd.data = Some(gen_data(9));
                gd.rule = Some(gen_rule(9));
                app_ui.ui_3x3.update(&gd.data.clone().unwrap());
                app_ui.switch_ui(gd.ui_id);
                app_ui.f_time.show();
            }
            330..=430 => {        // click 4x4
                gd.ui_id = 2;
                gd.t_start = Some(std::time::SystemTime::now()       // 单位毫秒
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize);
                gd.data = Some(gen_data(16));
                gd.rule = Some(gen_rule(16));
                app_ui.ui_4x4.update(&gd.data.clone().unwrap());
                app_ui.switch_ui(gd.ui_id);
                app_ui.f_time.show();
            }
            480..=580 => {        // click 5x5
                gd.ui_id = 3;
                gd.t_start = Some(std::time::SystemTime::now()       // 单位毫秒
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize);
                gd.data = Some(gen_data(25));
                gd.rule = Some(gen_rule(25));
                app_ui.ui_5x5.update(&gd.data.clone().unwrap());
                app_ui.switch_ui(gd.ui_id);
                app_ui.f_time.show();
            }
            630..=730 => {        // Quit
                fltk::app::quit();
            }
            _ => {/*do nothing*/}
        }
    } else if 480 <= mouse_x && mouse_x <= 540 && 70 <= mouse_y && mouse_y <= 130 {    // click help
        gd.ui_id = 4;
        app_ui.f_time.hide();
        app_ui.switch_ui(gd.ui_id);
    }
}

fn _handle_if_menu(
    gd: &mut GameData,
    app_ui: &mut ApplicationUI,
    mouse_x: i32,
    mouse_y: i32
) -> bool {
    if 70 <= mouse_y && mouse_y <= 150 {
        if 60 <= mouse_x && mouse_x <= 180 {              // home
            gd.data = None;
            gd.rule = None;
            gd.ui_id = 0;
            gd.t_start = None;
            app_ui.switch_ui(gd.ui_id);
            return true;
        } else if 420 <= mouse_x && mouse_x <= 540  {     // reset
            let d_len = [9, 16, 25];
            gd.data = Some(gen_data(d_len[(gd.ui_id - 1) as usize]));
            gd.rule = Some(gen_rule(d_len[(gd.ui_id - 1) as usize]));
            gd.t_start = Some(std::time::SystemTime::now()       // 单位毫秒
                .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize);
            let data = gd.data.clone().unwrap();
            match gd.ui_id {
                1 => {
                    app_ui.ui_3x3.update(&data);
                }
                2 => {
                    app_ui.ui_4x4.update(&data);
                }
                3 => {
                    app_ui.ui_5x5.update(&data);
                }
                _ => {/*do nothing*/}
            }
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


fn handle_3x3(gd: &mut GameData, app_ui: &mut ApplicationUI, mouse_x: i32, mouse_y: i32) {
    if _handle_if_menu(gd, app_ui, mouse_x, mouse_y) {
        return;
    }
    for i in 0..9 {
        if 60 + (i % 3) * 180 <= mouse_x && mouse_x <= 180 + (i % 3) * 180 &&
            240 + (i / 3) * 180 <= mouse_y && mouse_y <= 360 + (i / 3) * 180 {
            transform(gd, i as usize);
            let _data = gd.data.clone().unwrap();
            let _rule = gd.rule.clone().unwrap();
            if graph::check_win(&_data) {
                gd.ui_id = 5;
                let t_end = std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize;
                let t_cost = t_end - gd.t_start.unwrap();
                app_ui.ui_win.update(t_cost);
                app_ui.switch_ui(gd.ui_id);
            }
            app_ui.ui_3x3.update(&_data);
            break;
        }
    }
}


fn handle_4x4(gd: &mut GameData, app_ui: &mut ApplicationUI, mouse_x: i32, mouse_y: i32) {
    if _handle_if_menu(gd, app_ui, mouse_x, mouse_y) {
        return;
    }
    for i in 0..16 {
        if 55 + (i % 4) * 130 <= mouse_x && mouse_x <= 155 + (i % 4) * 130 &&
            240 + (i / 4) * 130 <= mouse_y && mouse_y <= 340 + (i / 4) * 130 {
            transform(gd, i as usize);
            let _data = gd.data.clone().unwrap();
            let _rule = gd.rule.clone().unwrap();
            if graph::check_win(&_data) {
                gd.ui_id = 5;
                let t_end = std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize;
                let t_cost = t_end - gd.t_start.unwrap();
                app_ui.ui_win.update(t_cost);
                app_ui.switch_ui(gd.ui_id);
            }
            app_ui.ui_4x4.update(&_data);
            break;
        }
    }
}


fn handle_5x5(gd: &mut GameData, app_ui: &mut ApplicationUI, mouse_x: i32, mouse_y: i32) {
    if _handle_if_menu(gd, app_ui, mouse_x, mouse_y) {
        return;
    }
    for i in 0..25 {
        if 60 + (i % 5) * 100 <= mouse_x && mouse_x <= 140 + (i % 5) * 100 &&
            240 + (i / 5) * 100 <= mouse_y && mouse_y <= 320 + (i / 5) * 100 {
            transform(gd, i as usize);
            let _data = gd.data.clone().unwrap();
            let _rule = gd.rule.clone().unwrap();
            if graph::check_win(&_data) {
                gd.ui_id = 5;
                let t_end = std::time::SystemTime::now()
                    .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize;
                let t_cost = t_end - gd.t_start.unwrap();
                app_ui.ui_win.update(t_cost);
                app_ui.switch_ui(gd.ui_id);
            }
            app_ui.ui_5x5.update(&_data);
            break;
        }
    }
}


fn handle_other(gd: &mut GameData,  app_ui: &mut ApplicationUI) {
    gd.ui_id = 0;         // return to home
    gd.t_start = None;
    gd.data = None;
    gd.rule = None;
    app_ui.switch_ui(gd.ui_id);
}