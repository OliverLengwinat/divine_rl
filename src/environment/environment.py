import pygame
from math import pi
 

# basically

# env = Environment(descr, dt, max_steps, ...)
# observer = Observer(env) # <-- ego_state, ego_antenna, ego_image, world_image, ...


# important: 2 lines.. intersection distance
# observer has all lines.. knows where the vehicles are.. calculates the d_col

# agents = env.get_agents()

# state, action, next_state, reward = observer.step( agent, u, dt )
# observer.step(agent, u, dt)


# Initialize the game engine
pygame.init()
WHITE = (255, 255, 255)
BLACK = (  0,   0,   0)


# Set the height and width of the screen
size = [400, 300]
screen = pygame.display.set_mode(size)

pygame.display.set_caption("Example code for the draw module")
done = False

 
while not done:
    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
            done=True # Flag that we are done so we exit this loop
 
    # All drawing code happens after the for loop and but
    # inside the main while done==False loop.
     
    # Clear the screen and set the screen background
    screen.fill(WHITE)

    pygame.draw.polygon(screen, BLACK, [[100, 100], [0, 200], [200, 200]], 1)

    pygame.display.flip()

pygame.quit()