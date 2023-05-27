import os
import pygame
import sys

import game_ui
import graph

def get_resource_path(relative_path):
    if hasattr(sys, '_MEIPASS'):
        return os.path.join(sys._MEIPASS, relative_path)
    return os.path.join(os.path.abspath("."), relative_path)


pygame.init()

pygame.mixer.music.load(get_resource_path('assets/xnftj.mp3'))
ui_id = 0        # Unique ID for each UI element, 0->home, 1->3x3, 2->4x4, 3->5x5, 4->win, 5->help
graph_rule = {}  # transform rule for each block
data = []        # number of each block 3x3: 1~9, 4x4: 1~16, 5x5: 1~25
start = 0        # start time seconds
tick = 0         # time seconds

# Create the screen
screen = pygame.display.set_mode((600, 800))

# Title and Icon
pygame.display.set_caption("Block Transform")
# icon = pygame.image.load('icon.png')
# pygame.display.set_icon(icon)

# Game Loop
if __name__ == '__main__':
    while True:             # main loop
        if not pygame.mixer.music.get_busy():
            pygame.mixer.music.play()
        match ui_id:  # draw ui
            case 0:  # main
                game_ui.ui_main(screen)
            case 1:  # 3x3
                tick = (pygame.time.get_ticks() - start) / 1000
                game_ui.ui_3x3(screen, data, int(tick))
                if data == list(range(1, 10)):
                    # if all blocks are in order, show win screen
                    ui_id = 4
            case 2:  # 4x4
                tick = (pygame.time.get_ticks() - start) / 1000
                game_ui.ui_4x4(screen, data, int(tick))
                if data == list(range(1, 17)):
                    # if all blocks are in order, show win screen
                    ui_id = 4
            case 3:  # 5x5
                tick = (pygame.time.get_ticks() - start) / 1000
                game_ui.ui_5x5(screen, data, int(tick))
                if data == list(range(1, 26)):
                    # if all blocks are in order, show win screen
                    ui_id = 4
            case 4:  # win
                game_ui.ui_win(screen, tick)
            case 5:  # help
                game_ui.ui_help(screen)
        for event in pygame.event.get():
            if event.type == pygame.MOUSEBUTTONDOWN:
                match ui_id:    # mouse click
                    case 0:  # main
                        if 100 <= event.pos[0] <= 500:
                            start = pygame.time.get_ticks()
                            if 170 <= event.pos[1] <= 270:      # 3x3
                                ui_id = 1
                                graph_rule = graph.gen_rule(9)
                                data = graph.gen_data(9)
                            elif 320 <= event.pos[1] <= 420:    # 4x4
                                ui_id = 2
                                graph_rule = graph.gen_rule(16)
                                data = graph.gen_data(16)
                            elif 470 <= event.pos[1] <= 570:    # 5x5
                                ui_id = 3
                                graph_rule = graph.gen_rule(25)
                                data = graph.gen_data(25)
                            elif 620 <= event.pos[1] <= 720:    # quit
                                pygame.quit()
                                raise SystemExit
                        elif 500 <= event.pos[0] <= 570 and 45 <= event.pos[1] <= 115:  # help
                            ui_id = 5
                    case 1:  # 3x3
                        # if mouse click on home button or reset button
                        if 60 <= event.pos[1] <= 140:
                            if 60 <= event.pos[0] <= 180:  # home
                                ui_id = 0
                            elif 420 <= event.pos[0] <= 540:  # reset
                                data = graph.gen_data(9)
                                start = pygame.time.get_ticks()
                        # if mouse click on block
                        if 60 <= event.pos[0] <= 180:  # column 1
                            if 240 <= event.pos[1] <= 360:  # row 1
                                data = graph.transform(data, graph_rule, 0)
                            elif 420 <= event.pos[1] <= 540:  # row 2
                                data = graph.transform(data, graph_rule, 3)
                            elif 600 <= event.pos[1] <= 720:  # row 3
                                data = graph.transform(data, graph_rule, 6)
                        elif 240 <= event.pos[0] <= 360:  # column 2
                            if 240 <= event.pos[1] <= 360:  # row 1
                                data = graph.transform(data, graph_rule, 1)
                            elif 420 <= event.pos[1] <= 540:  # row 2
                                data = graph.transform(data, graph_rule, 4)
                            elif 600 <= event.pos[1] <= 720:  # row 3
                                data = graph.transform(data, graph_rule, 7)
                        elif 420 <= event.pos[0] <= 540:  # column 3
                            if 240 <= event.pos[1] <= 360:  # row 1
                                data = graph.transform(data, graph_rule, 2)
                            elif 420 <= event.pos[1] <= 540:  # row 2
                                data = graph.transform(data, graph_rule, 5)
                            elif 600 <= event.pos[1] <= 720:  # row 3
                                data = graph.transform(data, graph_rule, 8)

                    case 2:  # 4x4
                        # if mouse click on home button or reset button
                        if 60 <= event.pos[1] <= 140:
                            if 60 <= event.pos[0] <= 180:  # home
                                ui_id = 0
                            elif 420 <= event.pos[0] <= 540:  # reset
                                graph_rule = graph.gen_rule(16)
                                data = graph.gen_data(16)
                                start = pygame.time.get_ticks()
                        elif 70 <= event.pos[0] <= 170:  # column 1
                            if 230 <= event.pos[1] <= 330:  # row 1
                                data = graph.transform(data, graph_rule, 0)
                            elif 350 <= event.pos[1] <= 450:  # row 2
                                data = graph.transform(data, graph_rule, 4)
                            elif 470 <= event.pos[1] <= 570:  # row 3
                                data = graph.transform(data, graph_rule, 8)
                            elif 590 <= event.pos[1] <= 690:  # row 4
                                data = graph.transform(data, graph_rule, 12)
                        elif 190 <= event.pos[0] <= 290:  # column 2
                            if 230 <= event.pos[1] <= 330:  # row 1
                                data = graph.transform(data, graph_rule, 1)
                            elif 350 <= event.pos[1] <= 450:  # row 2
                                data = graph.transform(data, graph_rule, 5)
                            elif 470 <= event.pos[1] <= 570:  # row 3
                                data = graph.transform(data, graph_rule, 9)
                            elif 590 <= event.pos[1] <= 690:  # row 4
                                data = graph.transform(data, graph_rule, 13)
                        elif 310 <= event.pos[0] <= 410:  # column 3
                            if 230 <= event.pos[1] <= 330:  # row 1
                                data = graph.transform(data, graph_rule, 2)
                            elif 350 <= event.pos[1] <= 450:  # row 2
                                data = graph.transform(data, graph_rule, 6)
                            elif 470 <= event.pos[1] <= 570:  # row 3
                                data = graph.transform(data, graph_rule, 10)
                            elif 590 <= event.pos[1] <= 690:  # row 4
                                data = graph.transform(data, graph_rule, 14)
                        elif 430 <= event.pos[0] <= 530:  # column 4
                            if 230 <= event.pos[1] <= 330:  # row 1
                                data = graph.transform(data, graph_rule, 3)
                            elif 350 <= event.pos[1] <= 450:  # row 2
                                data = graph.transform(data, graph_rule, 7)
                            elif 470 <= event.pos[1] <= 570:  # row 3
                                data = graph.transform(data, graph_rule, 11)
                            elif 590 <= event.pos[1] <= 690:  # row 4
                                data = graph.transform(data, graph_rule, 15)

                    case 3:  # 5x5
                        # if mouse click on home button or reset button
                        if 60 <= event.pos[1] <= 140:
                            if 60 <= event.pos[0] <= 180:  # home
                                ui_id = 0
                            elif 420 <= event.pos[0] <= 540:  # reset
                                graph_rule = graph.gen_rule(25)
                                data = graph.gen_data(25)
                                start = pygame.time.get_ticks()
                        elif 70 <= event.pos[0] <= 150:  # column 1
                            if 240 <= event.pos[1] <= 320:  # row 1
                                data = graph.transform(data, graph_rule, 0)
                            elif 335 <= event.pos[1] <= 415:  # row 2
                                data = graph.transform(data, graph_rule, 5)
                            elif 430 <= event.pos[1] <= 510:  # row 3
                                data = graph.transform(data, graph_rule, 10)
                            elif 525 <= event.pos[1] <= 605:  # row 4
                                data = graph.transform(data, graph_rule, 15)
                            elif 620 <= event.pos[1] <= 700:  # row 5
                                data = graph.transform(data, graph_rule, 20)
                        elif 165 <= event.pos[0] <= 245:  # column 2
                            if 240 <= event.pos[1] <= 320:  # row 1
                                data = graph.transform(data, graph_rule, 1)
                            elif 335 <= event.pos[1] <= 415:  # row 2
                                data = graph.transform(data, graph_rule, 6)
                            elif 430 <= event.pos[1] <= 510:  # row 3
                                data = graph.transform(data, graph_rule, 11)
                            elif 525 <= event.pos[1] <= 605:  # row 4
                                data = graph.transform(data, graph_rule, 16)
                            elif 620 <= event.pos[1] <= 700:  # row 5
                                data = graph.transform(data, graph_rule, 21)
                        elif 260 <= event.pos[0] <= 340:  # column 3
                            if 240 <= event.pos[1] <= 320:  # row 1
                                data = graph.transform(data, graph_rule, 2)
                            elif 335 <= event.pos[1] <= 415:  # row 2
                                data = graph.transform(data, graph_rule, 7)
                            elif 430 <= event.pos[1] <= 510:  # row 3
                                data = graph.transform(data, graph_rule, 12)
                            elif 525 <= event.pos[1] <= 605:  # row 4
                                data = graph.transform(data, graph_rule, 17)
                            elif 620 <= event.pos[1] <= 700:  # row 5
                                data = graph.transform(data, graph_rule, 22)
                        elif 355 <= event.pos[0] <= 435:  # column 4
                            if 240 <= event.pos[1] <= 320:  # row 1
                                data = graph.transform(data, graph_rule, 3)
                            elif 335 <= event.pos[1] <= 415:  # row 2
                                data = graph.transform(data, graph_rule, 8)
                            elif 430 <= event.pos[1] <= 510:  # row 3
                                data = graph.transform(data, graph_rule, 13)
                            elif 525 <= event.pos[1] <= 605:  # row 4
                                data = graph.transform(data, graph_rule, 18)
                            elif 620 <= event.pos[1] <= 700:  # row 5
                                data = graph.transform(data, graph_rule, 23)
                        elif 450 <= event.pos[0] <= 530:  # column 5
                            if 240 <= event.pos[1] <= 320:  # row 1
                                data = graph.transform(data, graph_rule, 4)
                            elif 335 <= event.pos[1] <= 415:  # row 2
                                data = graph.transform(data, graph_rule, 9)
                            elif 430 <= event.pos[1] <= 510:  # row 3
                                data = graph.transform(data, graph_rule, 14)
                            elif 525 <= event.pos[1] <= 605:  # row 4
                                data = graph.transform(data, graph_rule, 19)
                            elif 620 <= event.pos[1] <= 700:  # row 5
                                data = graph.transform(data, graph_rule, 24)

                    case _:  # win or help
                        pygame.time.delay(10)
                        ui_id = 0

            elif event.type == pygame.QUIT:
                pygame.quit()
                raise SystemExit
        pygame.display.update()
