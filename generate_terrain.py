# generate_terrain.py
tile_width = 100  # Modifier selon vos besoins
tile_height = 100

with open('res/maps/terrain.txt', 'w') as file:
    for j in range(tile_height):
        line = []
        for i in range(tile_width):
            if j == 0:
                if i == 0:
                    line.append('63')  # Premier élément de la première ligne
                elif i == tile_width - 1:
                    line.append('64')  # Dernier élément de la première ligne
                else:
                    line.append(str(60 * 3 + 2))  # Éléments intermédiaires de la première ligne (182)
            else:
                if i == 0:
                    line.append(str(60 * 2 + 3))  # Premier élément de chaque ligne (123)
                else:
                    line.append(str(60 * 2 + 2))  # Éléments restants de chaque ligne (122)
        file.write(' '.join(line) + '\n')
