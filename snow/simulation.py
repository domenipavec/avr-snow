#!/usr/bin/env python

import pygame
import random
import sys

pygame.init()

size = width, height = 1500, 1300
speed = [2, 2]
position = pygame.Rect(0, 0, 0, 0)
black = 0, 0, 0
gray = 0, 30, 75
white = 0xff, 0xff, 0xff
blue = 0, 20, 50

screen = pygame.display.set_mode(size)

cloud = pygame.image.load("cloud.png")
cloud = pygame.transform.scale(cloud, (210, 150))

mode = 'snow'

led_radius = 2
led_panel = (160, 100)
led_spacing = (20, 25)

panels = [{
    'x': 100,
    'y': 450,
    'height': 4,
    'stars': [
        (3, 1),
        (1, 4),
        (4, 6),
        (2, 10),
        (7, 10),
    ],
}, {
    'x': 550,
    'y': 200,
    'height': 3,
    'stars': [
        (7, 0),
        (5, 1),
        (4, 3),
        (3, 6),
        (0, 7),
        (4, 10),
        (1, 11),
    ],
}, {
    'x': 450,
    'y': 680,
    'height': 2,
    'stars': [
        (0, 0),
        (7, 3),
        (3, 5),
        (4, 2),
        (0, 4),
    ],
}, {
    'x': 1200,
    'y': 250,
    'height': 6,
    'stars': [
        (1, 0),
        (5, 0),
        (6, 6),
        (3, 7),
        (1, 11),
        (0, 15),
        (3, 20),
    ],
}, {
    'x': 880,
    'y': 540,
    'height': 3,
    'stars': [
        (4, 0),
        (5, 2),
        (1, 1),
        (6, 3),
        (7, 7),
        (1, 4),
        (4, 9),
        (1, 8),
        (3, 6),
        (7, 10),
        (1, 11),
    ],
}]


for panel in panels:
    panel['animation'] = []
    panel['next'] = 0
    panel['ledsw'] = led_panel[0] / led_spacing[0]
    panel['ledsh'] = led_panel[1] * panel['height'] / led_spacing[1]
    panel['leds'] = [
        [panel['x'] + led_spacing[0]*x, panel['y'] + led_spacing[1]*y] for y in range(panel['ledsh']) for x in range(panel['ledsw'])
    ]

print(sum(len(panel['leds']) for panel in panels))

clock = pygame.time.Clock()


def anim_map(an):
    x = an[0] + an[2]
    y = an[1] + an[3]
    return x, y, an[2], an[3]


while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            print(pygame.mouse.get_pos())
        elif event.type == pygame.KEYDOWN and event.key == pygame.K_a:
            if mode == 'snow':
                mode = 'stars'
            else:
                mode = 'snow'

    screen.fill(black)
    pygame.draw.rect(screen, blue, pygame.Rect(0, 0, 1500, 900))

    for panel in panels:
        panel['animation'] = filter(
            lambda an: round(an[0]) >= 0 and round(an[0]) < panel['ledsw'] and int(an[1]) < panel['ledsh'],
            map(anim_map, panel['animation']))

        panel['next'] -= 1
        if panel['next'] <= 0:
            vabs = max(0.01, random.normalvariate(0.07, 0.01))
            y = led_panel[1] * panel['height']
            x = led_panel[0] * random.normalvariate(0, 0.5)
            c = (x**2+y**2)**0.5
            vx = x*vabs/c
            vy = y*vabs/c

            panel['animation'].append([
                random.randrange(panel['ledsw']),  # x
                0,  # y
                vx,
                vy,
            ])
            panel['next'] = random.gammavariate(3, 10)

        for led in panel['leds']:
            pygame.draw.circle(screen, gray, led, led_radius)

        if mode == 'snow':
            cloudrect = cloud.get_rect()
            cloudrect = cloudrect.move([panel['x'] - 30, panel['y'] - 150])
            screen.blit(cloud, cloudrect)

            for an in panel['animation']:
                index = int(round(an[0]) + panel['ledsw'] * int(an[1]))
                pygame.draw.circle(screen, white, panel['leds'][index], led_radius)
        else:
            for panel in panels:
                for star in panel['stars']:
                    index = star[0] + panel['ledsw'] * star[1]
                    pygame.draw.circle(screen, white, panel['leds'][index], led_radius)

    pygame.display.flip()

    clock.tick(60)
