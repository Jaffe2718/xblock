#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]
#![allow(clippy::unnecessary_wraps)]

mod xpack;

use std::fs::File;
use std::io::{BufReader};
use fltk;
use fltk::{app, prelude::*};
use rodio::{Decoder, OutputStream, Sink};


fn main() {
    let mut game_data = xpack::event::GameData {
        was_pressed: false,
        ui_id: 0,
        t_start: None,
        rule: None,
        data: None
    };
    // play bgm
    let (_stream, stream_handle) = OutputStream::try_default().unwrap();
    let sink = Sink::try_new(&stream_handle).unwrap();
    let mp3_path = std::env::current_exe().unwrap().parent().unwrap().join("res/xnftj.mp3");
    let file = File::open(mp3_path).unwrap();
    sink.append(Decoder::new(BufReader::new(file)).unwrap());
    sink.play();
    // init app
    app::App::default();
    app::background(243, 243, 243);
    let mut wind = fltk::window::SingleWindow::new(100, 100, 600, 800, "Block Transform");
    let icon = fltk::image::PngImage::load(std::env::current_exe().unwrap().parent().unwrap().join("res/icon.png")).unwrap();
    wind.set_icon(Some(icon));
    let mut app_ui = xpack::game_ui::ApplicationUI::new(&mut wind);
    app_ui.switch_ui(game_data.ui_id);
    wind.show();
    while true {
        // handle events
        if app::wait_for(0.1).unwrap() &&app::event_is_click() {
            if !game_data.was_pressed {
                xpack::event::handle_events(
                    &mut game_data,
                    &mut app_ui,
                    app::event_x(),
                    app::event_y());
            }
            game_data.was_pressed = true;
        } else if game_data.was_pressed {
            game_data.was_pressed = false;
        }
        // update time
        if game_data.t_start.is_some() && (game_data.ui_id == 1 || game_data.ui_id == 2 || game_data.ui_id == 3) {
            let mut time_str = String::new();
            let t_now = std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH).unwrap().as_millis() as usize;
            let t = t_now - game_data.t_start.unwrap();
            let t_min = t / 60000;
            let t_sec = (t % 60000) / 1000;
            if t_min < 10 {
                time_str.push('0');
            }
            time_str.push_str(&t_min.to_string());
            time_str.push(':');
            if t_sec < 10 {
                time_str.push('0');
            }
            time_str.push_str(&t_sec.to_string());
            if app_ui.f_time.label() != time_str {
                app_ui.f_time.set_label(&time_str);
            }
        } else {
            app_ui.f_time.hide();
        }
        // check window close
        if !ind.shown() {
            return;
        }
    }
}
