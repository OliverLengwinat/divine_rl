import pygame
from math import pi
 

# basically

# env = Environment(descr)
# observer = Observer(env) # <-- ego_state, ego_antenna, ego_image, world_image, ...

# agents = env.get_agents()

# agent.step(u, dt) 
# observer.observe(agent)

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