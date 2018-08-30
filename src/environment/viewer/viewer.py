import matplotlib.pyplot as plt

class Viewer(object):
    def __init__(self):
        pass

    def draw_world(self, world, color='gray'):
        for obj in world.get_objects():
            if obj.get_type() == 1:
                polygon = obj.get_shape()
                self.draw_polygon(polygon, color='gray')
            elif obj.get_type() == 0:
                polygon = obj.get_transformed_shape()
                self.draw_polygon(polygon, color='blue')

    def draw_polygon(self, polygon, color='gray'):
        pts = polygon.to_numpy()
        plt.plot(pts[:,0], pts[:,1], color=color)

    def show(self):
        plt.axis("equal")
        plt.show()