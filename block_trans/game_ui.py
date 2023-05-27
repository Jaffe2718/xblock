# game_ui.py
from typing import Union

import pygame

def ui_main(screen: pygame.Surface):
    # screen = pygame.display.set_mode((600, 800))
    """
    Main UI
    This is the main menu UI, which is the first screen when the game starts.
    There are 4 buttons on the screen, which are 3x3, 4x4, 5x5, and Quit.
    The 3x3, 4x4, and 5x5 buttons will lead to the corresponding UI.
    The Quit button will quit the game.
    :param screen: pygame.Surface
    :param data: list[int]
    :return: int  # ui_id
    """
    screen.fill((255, 255, 255))
    font = pygame.font.Font('freesansbold.ttf', 32)
    texts = ('3x3', '4x4', '5x5', 'QUIT')
    # draw the title
    text_surface = font.render('Block Transform', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 80)
    screen.blit(text_surface, text_rect)
    # draw help button
    text_surface = font.render('?', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (535, 80)
    pygame.draw.rect(screen, (0, 0, 0), (500, 45, 70, 70), 5)
    screen.blit(text_surface, text_rect)
    # draw the buttons
    for text in texts:
        # create 4 buttons, 3x3, 4x4, 5x5, and Quit
        # length of the button is 400, height is 100, padding is 50
        text_surface = font.render(text, True, (0, 0, 0))
        text_rect = text_surface.get_rect()
        text_rect.center = (300, texts.index(text) * 150 + 220)
        pygame.draw.rect(screen, (0, 0, 0), (100, texts.index(text) * 150 + 170, 400, 100), 5)
        screen.blit(text_surface, text_rect)


def _draw_menu(screen: pygame.Surface, tick: int):
    screen.fill((255, 255, 255))
    # draw the menu area: a rectangle at the top of the screen
    pygame.draw.rect(screen, (0, 0, 0), (40, 40, 520, 120), 5)
    # draw the timer
    font = pygame.font.Font('freesansbold.ttf', 32)
    text_surface = font.render(f'{tick // 60:02d}:{tick % 60:02d}', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 100)
    screen.blit(text_surface, text_rect)
    # draw the Home button
    text_surface = font.render('Home', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (120, 100)
    pygame.draw.rect(screen, (0, 0, 0), (60, 60, 120, 80), 5)
    screen.blit(text_surface, text_rect)
    # draw the reset button
    text_surface = font.render('Reset', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (480, 100)
    pygame.draw.rect(screen, (0, 0, 0), (420, 60, 120, 80), 5)
    screen.blit(text_surface, text_rect)


def ui_3x3(screen: pygame.Surface, data: list[int], tick: int):
    '''
    3x3 UI
    This is the UI for 3x3 blocks game.
    There is a menu area at the top of the screen, which contains the main menu button and the quit button and timer.
    There are 9 blocks on the screen, which are 3x3.
    :param screen: pygame.Surface
    :param data: list[int]           # number of each block, 1~9
    :param tick: int                 # time seconds
    :return: int  # ui_id
    '''
    _draw_menu(screen, tick)
    centers = ((120, 300), (300, 300), (480, 300),
               (120, 480), (300, 480), (480, 480),
               (120, 660), (300, 660), (480, 660))
    font = pygame.font.Font('freesansbold.ttf', 32)
    for i in range(9):
        # draw the 9 blocks, 120x120
        text_surface = font.render(f'{data[i]}', True, (0, 0, 0))
        text_rect = text_surface.get_rect()
        text_rect.center = centers[i]
        pygame.draw.rect(screen, (0, 0, 0), (centers[i][0] - 60, centers[i][1] - 60, 120, 120), 5)
        screen.blit(text_surface, text_rect)


def ui_4x4(screen: pygame.Surface, data: list[int], tick: int):
    '''
    4x4 UI
    This is the UI for 4x4 blocks game.
    There is a menu area at the top of the screen, which contains the main menu button and the quit button and timer.
    There are 16 blocks on the screen, which are 4x4.
    :param screen: pygame.Surface
    :param data: list[int]           # number of each block, 1~16
    :param tick: int                 # time seconds
    :return: int  # ui_id
    '''
    _draw_menu(screen, tick)
    # draw the 16 blocks, 100x100
    centers = ((120, 280), (240, 280), (360, 280), (480, 280),
               (120, 400), (240, 400), (360, 400), (480, 400),
               (120, 520), (240, 520), (360, 520), (480, 520),
               (120, 640), (240, 640), (360, 640), (480, 640))
    font = pygame.font.Font('freesansbold.ttf', 32)
    for i in range(16):
        text_surface = font.render(f'{data[i]}', True, (0, 0, 0))
        text_rect = text_surface.get_rect()
        text_rect.center = centers[i]
        pygame.draw.rect(screen, (0, 0, 0), (centers[i][0] - 50, centers[i][1] - 50, 100, 100), 5)
        screen.blit(text_surface, text_rect)


def ui_5x5(screen: pygame.Surface, data: list[int], tick: int):
    '''
    5x5 UI
    This is the UI for 5x5 blocks game.
    There is a menu area at the top of the screen, which contains the main menu button and the quit button and timer.
    There are 25 blocks on the screen, which are 5x5.
    :param screen: pygame.Surface
    :param data: list[int]           # number of each block, 1~25
    :param tick: int                 # time seconds
    :return: int  # ui_id
    '''
    _draw_menu(screen, tick)
    # draw the 25 blocks, 80x80
    centers = ((110, 280), (205, 280), (300, 280), (395, 280), (490, 280),
               (110, 375), (205, 375), (300, 375), (395, 375), (490, 375),
               (110, 470), (205, 470), (300, 470), (395, 470), (490, 470),
               (110, 565), (205, 565), (300, 565), (395, 565), (490, 565),
               (110, 660), (205, 660), (300, 660), (395, 660), (490, 660))
    font = pygame.font.Font('freesansbold.ttf', 32)
    for i in range(25):
        text_surface = font.render(f'{data[i]}', True, (0, 0, 0))
        text_rect = text_surface.get_rect()
        text_rect.center = centers[i]
        pygame.draw.rect(screen, (0, 0, 0), (centers[i][0] - 40, centers[i][1] - 40, 80, 80), 5)
        screen.blit(text_surface, text_rect)


def ui_win(screen: pygame.Surface, tick: Union[float, int]):
    screen.fill((255, 255, 255))
    # show Congratulation
    font = pygame.font.Font('freesansbold.ttf', 64)
    text_surface = font.render('Congratulation!', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 220)
    screen.blit(text_surface, text_rect)
    # show the time
    font = pygame.font.Font('freesansbold.ttf', 32)
    text_surface = font.render(f'Time: {tick} seconds', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 400)
    screen.blit(text_surface, text_rect)
    # show "Click anywhere to return to the Home Page"
    font = pygame.font.Font('freesansbold.ttf', 24)
    text_surface = font.render('Click anywhere to return to the Home Page', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 600)
    screen.blit(text_surface, text_rect)


def ui_help(screen: pygame.Surface):
    # show the help
    # screen.blit(img, (0, 0))
    screen.fill((255, 255, 255))
    # show the title
    font = pygame.font.Font('freesansbold.ttf', 32)
    text_surface = font.render('Block Transform Help', True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (300, 80)
    screen.blit(text_surface, text_rect)
    # show the text
    font = pygame.font.Font('freesansbold.ttf', 24)
    text_lines = ('This game requires players to arrange the',
                  'disordered number blocks in ascending order',
                  'from left to right and from top to bottom.',
                  'In each game, the rules for exchanging',
                  'numbers for each block are determined and',
                  'players need to explore them themselves.',
                  'For example, a 3x3 game should be like this:')
    for i in range(len(text_lines)):
        text_surface = font.render(text_lines[i], True, (0, 0, 0))
        text_rect = text_surface.get_rect()
        text_rect.center = (300, 160 + i * 30)
        screen.blit(text_surface, text_rect)
    # show the example
    font = pygame.font.Font('freesansbold.ttf', 32)
    numbers = (('1', '2', '3'),
                  ('4', '5', '6'),
                  ('7', '8', '9'))
    for i in range(3):
        for j in range(3):
            text_surface = font.render(numbers[i][j], True, (0, 0, 0))
            text_rect = text_surface.get_rect()
            text_rect.center = (180 + j * 120, 460 + i * 120)
            screen.blit(text_surface, text_rect)
            pygame.draw.rect(screen, (0, 0, 0), (140 + j * 120, 420 + i * 120, 80, 80), 5)
