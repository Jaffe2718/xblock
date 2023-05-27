var canvas = document.getElementById("gameCanvas");
var ctx = canvas.getContext("2d");
var data = [];           // 1~n 的数组
var graph_rule = {};       // 交换规则
var  ui_id = 0;       // 0:Home  1: 3x3  2: 4x4  3: 5x5  4: Win  5: Help
var  start = 0;       // 开始计时的时间，会根据游戏状态变化
var tick = 0;         // 计时器，单位为秒，根据start和当前时间计算得到

// 添加鼠标点击事件监听器
document.addEventListener("click", userClick);

// 设置画布宽高
canvas.width = 600;
canvas.height = 800;

function genRule(n) {
    // 生成规则对象（类似于Python中的字典），从数据结构的角度来看，这是一个单向图，出度为1，入度可变
    const graph = {};
    const nodes = Array.from({ length: n }, (_, i) => i + 1);
    shuffleArray(nodes);

    const mainLoopSize = getRandomInt(2, n);

    for (let i = 0; i < mainLoopSize; i++) {
        graph[nodes[i]] = nodes[(i + 1) % mainLoopSize];
    }

    let loopSize = mainLoopSize;
    for (let i = mainLoopSize; i < n; i++) {
        graph[nodes[i]] = nodes[getRandomInt(0, loopSize - 1)];
        loopSize++;
    }

    return graph;
}

function genData(n) {
    // 生成 1~n 的数组并且打乱
    const data = Array.from({ length: n }, (_, i) => i + 1);
    shuffleArray(data);
    return data;
}

function transform(data, rule, pos) {
    // 交换 data[pos] 和 data[rule[pos + 1] - 1]
    const m = data[pos];
    const n = data[rule[pos + 1] - 1];
    [data[pos], data[rule[pos + 1] - 1]] = [n, m];
    return data;
}

function checkWin(arr) {
    // 检查是否胜利，即 data = [1, 2, 3, ..., n]
    return arr.every((v, i) => v === i + 1);
}

function shuffleArray(arr) {
    for (let i = arr.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }
}

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}
// 绘制主菜单界面
function drawHomeMenu() {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 设置字体样式
    ctx.font = "bold 36px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    // 绘制游戏标题
    ctx.fillText("Block Transform", canvas.width / 2, 80 + 50);
    // 绘制按钮
    var buttonWidth = 400;
    var buttonHeight = 100;
    var buttonPadding = 50;
    var buttonY = 270;
    // 3x3 按钮
    ctx.strokeStyle = "#000000";
    ctx.strokeRect(100, buttonY, buttonWidth, buttonHeight);
    ctx.fillText("3x3", canvas.width / 2, buttonY + buttonHeight / 2);
    // 4x4 按钮
    buttonY += buttonHeight + buttonPadding;
    ctx.strokeStyle = "#000000";
    ctx.strokeRect(100, buttonY, buttonWidth, buttonHeight);
    ctx.fillText("4x4", canvas.width / 2, buttonY + buttonHeight / 2);
    // 5x5 按钮
    buttonY += buttonHeight + buttonPadding;
    ctx.strokeStyle = "#000000";
    ctx.strokeRect(100, buttonY, buttonWidth, buttonHeight);
    ctx.fillText("5x5", canvas.width / 2, buttonY + buttonHeight / 2);
    // 绘制帮助按钮
    ctx.strokeStyle = "#000000";
    ctx.strokeRect(500, 45 + 50, 70, 70);
    ctx.fillText("?", 535, 80 + 50);
}

// 绘制游戏内部菜单栏
function _drawMenu(tick) {
    // 绘制菜单栏区域：屏幕顶部的矩形边框
    ctx.strokeStyle = "#000000";
    ctx.strokeRect(40, 40, 520, 120);

    // 绘制计时器
    ctx.font = "bold 32px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    ctx.fillText(
        `${Math.floor(tick / 60).toString().padStart(2, '0')}:${(tick % 60).toString().padStart(2, '0')}`,
        300,
        100
    );

    // 绘制主页按钮
    ctx.fillText("Home", 120, 100);
    ctx.strokeRect(60, 60, 120, 80);

    // 绘制重置按钮
    ctx.fillText("Reset", 480, 100);
    ctx.strokeRect(420, 60, 120, 80);
}

// 绘制3x3 UI
function drawUI_3x3(data, tick) {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制菜单栏和计时器
    _drawMenu(tick);
    // 绘制9个方块
    var centers = [
        [120, 300], [300, 300], [480, 300],
        [120, 480], [300, 480], [480, 480],
        [120, 660], [300, 660], [480, 660]
    ];

    ctx.font = "bold 32px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";

    for (var i = 0; i < 9; i++) {
        // 绘制方块边框
        ctx.strokeStyle = "#000000";
        ctx.strokeRect(centers[i][0] - 60, centers[i][1] - 60, 120, 120);
        // 绘制方块数字
        ctx.fillText(data[i].toString(), centers[i][0], centers[i][1]);
    }
}

// 绘制 4x4 界面
function drawUI_4x4(data, tick) {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制菜单栏
    _drawMenu(tick);
    // 绘制 16 个方块，大小为 100x100
    var centers = [
        [120, 280], [240, 280], [360, 280], [480, 280],
        [120, 400], [240, 400], [360, 400], [480, 400],
        [120, 520], [240, 520], [360, 520], [480, 520],
        [120, 640], [240, 640], [360, 640], [480, 640]
    ];

    ctx.font = "bold 32px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";

    for (var i = 0; i < 16; i++) {
        // 绘制方块边框
        ctx.strokeStyle = "#000000";
        ctx.strokeRect(centers[i][0] - 50, centers[i][1] - 50, 100, 100);
        // 绘制方块数字
        ctx.fillText(data[i].toString(), centers[i][0], centers[i][1]);
    }
}

// 绘制 5x5 界面
function drawUI_5x5(data, tick) {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制菜单栏
    _drawMenu(tick);
    // 绘制 25 个方块，大小为 80x80
    var centers = [
        [110, 280], [205, 280], [300, 280], [395, 280], [490, 280],
        [110, 375], [205, 375], [300, 375], [395, 375], [490, 375],
        [110, 470], [205, 470], [300, 470], [395, 470], [490, 470],
        [110, 565], [205, 565], [300, 565], [395, 565], [490, 565],
        [110, 660], [205, 660], [300, 660], [395, 660], [490, 660]
    ];

    ctx.font = "bold 32px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";

    for (var i = 0; i < 25; i++) {
        // 绘制方块边框
        ctx.strokeStyle = "#000000";
        ctx.strokeRect(centers[i][0] - 40, centers[i][1] - 40, 80, 80);
        // 绘制方块数字
        ctx.fillText(data[i].toString(), centers[i][0], centers[i][1]);
    }
}

// 绘制胜利界面
function drawUI_Win(tick) {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // 显示恭喜文本
    ctx.font = "bold 64px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    ctx.fillText("Congratulation!", canvas.width / 2, 220);

    // 显示时间
    ctx.font = "bold 32px Arial";
    ctx.fillText("Time: " + tick + " seconds", canvas.width / 2, 400);

    // 显示返回首页提示
    ctx.font = "bold 24px Arial";
    ctx.fillText("Click anywhere to return to the Home Page", canvas.width / 2, 600);
}

// 绘制帮助界面
function drawUI_Help() {
    // 清空画布
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // 显示标题
    ctx.font = "bold 32px Arial";
    ctx.fillStyle = "#000000";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    ctx.fillText("Block Transform Help", canvas.width / 2, 80);

    // 显示文字内容
    ctx.font = "bold 24px Arial";
    var textLines = [
        "This game requires players to arrange the",
        "disordered number blocks in ascending order",
        "from left to right and from top to bottom.",
        "In each game, the rules for exchanging",
        "numbers for each block are determined and",
        "players need to explore them themselves.",
        "For example, a 3x3 game should be like this:"
    ];

    for (i = 0; i < textLines.length; i++) {
        ctx.fillText(textLines[i], canvas.width / 2, 160 + i * 30);
    }

    // 显示示例
    ctx.font = "bold 32px Arial";
    var numbers = [
        ["1", "2", "3"],
        ["4", "5", "6"],
        ["7", "8", "9"]
    ];

    for (i = 0; i < 3; i++) {
        for (var j = 0; j < 3; j++) {
            ctx.strokeRect(140 + j * 120, 420 + i * 120, 80, 80);
            ctx.fillText(numbers[i][j], 180 + j * 120, 460 + i * 120);
        }
    }
}


// Home UI 事件处理
function handleHomeUI(event) {
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;
    if (clickX > 100 && clickX < 500) {
        if (clickY > 270 && clickY < 370) {  // 3x3
            graph_rule = genRule(9);
            data = genData(9);
            start = Date.now();
            ui_id = 1;
        } else if (clickY > 420 && clickY < 520) { // 4x4
            graph_rule = genRule(16);
            data = genData(16);
            start = Date.now();
            ui_id = 2;
        } else if (clickY > 570 && clickY < 670) { // 5x5
            graph_rule = genRule(25);
            data = genData(25);
            start = Date.now();
            ui_id = 3;
        }
    }
    else if (clickX > 500 && clickX < 570 && clickY > 45 + 50 && clickY < 115 + 50) {  // Help
        ui_id = 5; // 切换到 Help UI
    }
}

function handle3x3UI(event) {
    // 获取鼠标点击画布的相对位置
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;

    // 点击游戏界面菜单栏的 Home 按钮
    if (clickX >= 60 && clickX <= 180 && clickY >= 60 && clickY <= 140) {
        ui_id = 0; // 切换到 HomeMenu 界面
    }
    // 点击游戏界面菜单栏的 Reset 按钮
    else if (clickX >= 420 && clickX <= 540 && clickY >= 60 && clickY <= 140) {
        // 重置计时和题目
        start = Date.now();
        data = genData(9);
        graph_rule = genRule(9);
    }
    else {  // 点击 3x3 区域内的方块
        var centers = [
            [120, 300], [300, 300], [480, 300],
            [120, 480], [300, 480], [480, 480],
            [120, 660], [300, 660], [480, 660]
        ];
        for (var i = 0; i < 9; i++) {
            var centerX = centers[i][0];
            var centerY = centers[i][1];
            var left = centerX - 60;
            var right = centerX + 60;
            var top = centerY - 60;
            var bottom = centerY + 60;

            if (clickX >= left && clickX <= right && clickY >= top && clickY <= bottom) {
                // 根据交换规则交换数字
                data = transform(data, graph_rule, i);
                break;
            }
        }
        // 检查是否完成拼图
        if (checkWin(data)) {
            ui_id = 4; // switch to Win UI
        }
    }
}

function handle4x4UI(event) {
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;

    if (clickX >= 60 && clickX <= 180 && clickY >= 60 && clickY <= 140) {
        ui_id = 0; // 切换到 HomeMenu 界面
    } else if (clickX >= 420 && clickX <= 540 && clickY >= 60 && clickY <= 140) {
        start = Date.now();
        data = genData(16);
        graph_rule = genRule(16);
    } else {
        var centers = [
            [120, 280], [240, 280], [360, 280], [480, 280],
            [120, 400], [240, 400], [360, 400], [480, 400],
            [120, 520], [240, 520], [360, 520], [480, 520],
            [120, 640], [240, 640], [360, 640], [480, 640]
        ];

        for (var i = 0; i < 16; i++) {
            var centerX = centers[i][0];
            var centerY = centers[i][1];
            var left = centerX - 50;
            var right = centerX + 50;
            var top = centerY - 50;
            var bottom = centerY + 50;

            if (clickX >= left && clickX <= right && clickY >= top && clickY <= bottom) {
                data = transform(data, graph_rule, i);
                break;
            }
        }

        if (checkWin(data)) {
            ui_id = 4; // 切换到 Win UI
        }
    }
}

function handle5x5UI(event) {
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;

    if (clickX >= 60 && clickX <= 180 && clickY >= 60 && clickY <= 140) {
        ui_id = 0; // 切换到 HomeMenu 界面
    } else if (clickX >= 420 && clickX <= 540 && clickY >= 60 && clickY <= 140) {
        start = Date.now();
        data = genData(25);
        graph_rule = genRule(25);
    } else {
        var centers = [
            [110, 280], [205, 280], [300, 280], [395, 280], [490, 280],
            [110, 375], [205, 375], [300, 375], [395, 375], [490, 375],
            [110, 470], [205, 470], [300, 470], [395, 470], [490, 470],
            [110, 565], [205, 565], [300, 565], [395, 565], [490, 565],
            [110, 660], [205, 660], [300, 660], [395, 660], [490, 660]
        ];

        for (var i = 0; i < 25; i++) {
            var centerX = centers[i][0];
            var centerY = centers[i][1];
            var left = centerX - 40;
            var right = centerX + 40;
            var top = centerY - 40;
            var bottom = centerY + 40;

            if (clickX >= left && clickX <= right && clickY >= top && clickY <= bottom) {
                data = transform(data, graph_rule, i);
                break;
            }
        }

        if (checkWin(data)) {
            ui_id = 4; // 切换到 Win UI
        }
    }
}

function handleWinUI(event) {
    // 获取鼠标点击的位置
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;
    // 检查鼠标是否点击在画布内部
    if (clickX > 0 && clickX < canvas.width && clickY > 0 && clickY < canvas.height) {
        ui_id = 0; // switch to Home UI
    }
}

function handleHelpUI(event) {
    // 获取鼠标点击的位置
    var clickX = event.clientX - canvas.offsetLeft;
    var clickY = event.clientY - canvas.offsetTop;
    // 检查鼠标是否点击在画布内部
    if (clickX > 0 && clickX < canvas.width && clickY > 0 && clickY < canvas.height) {
        ui_id = 0; // switch to Home UI
    }
}

// 主事件监听处理函数
function userClick(event) {
    if (event.button === 0) {
         switch (ui_id) {
             case 0: // Home UI
                 handleHomeUI(event);
                 break;
             case 1: // 3x3 UI
                 handle3x3UI(event);
                 break;
             case 2: // 4x4 UI
                 handle4x4UI(event);
                 break;
             case 3: // 5x5 UI
                 handle5x5UI(event);
                 break;
             case 4: // Win UI
                 handleWinUI(event);
                 break;
             case 5: // Help UI
                 handleHelpUI(event);
                 break;
             default:
                 break;
         }
    }
}

// 主函数
function main() {
    switch (ui_id) {
            case 0: // Home UI
                drawHomeMenu();
                break;
            case 1: // 3x3 UI
                tick = (new Date().getTime() - start) / 1000;
                drawUI_3x3(data, Math.floor(tick));
                break;
            case 2: // 4x4 UI
                tick = (new Date().getTime() - start) / 1000;
                drawUI_4x4(data, Math.floor(tick));
                break;
            case 3: // 5x5 UI
                tick = (new Date().getTime() - start) / 1000;
                drawUI_5x5(data, Math.floor(tick));
                break;
            case 4: // Win UI
                drawUI_Win(tick);
                break;
            case 5: // Help UI
                drawUI_Help();
                break;
            default:
                break;
        }
    requestAnimationFrame(main);
}

requestAnimationFrame(main);