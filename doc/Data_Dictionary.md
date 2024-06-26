# Data Dictionary

|    Name     |              Type              |            Source            |                           Use                            |                    Description                     |
|:-----------:|:------------------------------:|:----------------------------:|:--------------------------------------------------------:|:--------------------------------------------------:|
| `ui_status` |      `xblock::UI_Status`       | Generated by program running |  Determines the current logic and drawing UI interface   |               The status of the UI.                |
|   `data`    |       `std::vector<int>`       | Generated by program running |            Store the matrix data of the game             |               The data of the game.                |
|   `rule`    | `std::unordered_map<int, int>` | Generated by program running |               Store the rules of the game                |       The transformation rules of the game.        |
| `win_time`  |           `sf::Time`           | Generated by program running | Record the time it takes for a player to achieve victory | The time it takes for a player to achieve victory. |
|   `clock`   |          `sf::Clock`           | Generated by program running |               Record the time of the game                |               The time of the game.                |

![dfd](img/Data_Flow_Diagram.svg)