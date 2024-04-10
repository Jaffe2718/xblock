use std::env;
use std::fs;
use std::path::PathBuf;

fn main() {
    embed_resource::compile("./icon.rc");
    // 获取当前工作目录
    let current_dir = env::current_dir().unwrap();
    // 获取输出目录
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let exe_dir = out_dir.parent().unwrap().parent().unwrap().parent().unwrap();
    // 假设资源文件的相对路径是"resources/music.mp3"
    let src_path = current_dir.join("res");
    let dst_dir = exe_dir.join("res");
    // 创建目标文件夹res
    match fs::create_dir_all(&dst_dir) {
        Ok(_) => {
            // 目标文件夹已经存在或者创建成功，复制资源文件到目标文件
            fs::copy(src_path.clone().join("xnftj.mp3"), dst_dir.clone().join("xnftj.mp3")).unwrap();
            fs::copy(src_path.clone().join("icon.png"), dst_dir.clone().join("icon.png")).unwrap();
        }
        Err(e) => {
            // 创建目标文件夹失败
            eprintln!("failed to create target directory: {}", e);
        }
    }
}