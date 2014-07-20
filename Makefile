all: bounce

bounce: main.o game.o player.o wall.o gameObject.o dynamicBody.o ResInit.o contactListener.o sprite.o portal.o spike.o level.o checkpoint.o ring.o gui.o life.o
	g++ -g -o bounce main.o game.o player.o wall.o gameObject.o dynamicBody.o ResInit.o contactListener.o sprite.o portal.o spike.o level.o ring.o gui.o checkpoint.o life.o -lSDL2 -lSDL2_image -lBox2D -ltinyxml -lz -ltmxparser

# %o: %.cpp
# 	g++ -c $<

# # main.o: main.cpp game.cpp player.cpp
# # 	# g++ -c main.cpp levels.cpp player.cpp wall.cpp -lSDL2 -lSDL2_image -lBox2D

# # game.o:
# # 	g++ -c game.cpp

# # levels.o:
# # 	g++ -c levels.cpp

# # gameObject.o:
# # 	g++ -c gameObject.cpp

# # player.o:
# # 	g++ -c player.cpp

# # wall.o:
# # 	g++ -c wall.cpp

# game.o: game.h game.cpp player.h
# 	g++ -c game.cpp

# player.o: player.h player.cpp
# 	g++ -c player.cpp
# 	# g++ -c main.cpp levels.cpp player.cpp wall.cpp -lSDL2 -lSDL2_image -lBox2D

# gameObject.o: gameObject.cpp dynamicBody.h
#  	g++ -c gameObject.cpp -lSDL2 -lSDL2_image -lBox2D

# dynamicBody.o:dynamicBody.cpp
# 	g++ -c dynamicBody.cpp -lBox2D

# game.o:
 	# g++ -c game.cpp

# levels.o:
# 	g++ -c levels.cpp

# gameObject.o:
# 	g++ -c gameObject.cpp

# player.o:
# 	g++ -c player.cpp

# wall.o:
# 	g++ -c wall.cpp

#network.o: network.cpp
#	g++ -c network.cpp

#neuron.o:  neuron.cpp
#	g++ -c neuron.cpp

#painter:o painter.cpp
#	g++ -c painter.cpp -lGL -lGLU -lglut -lGLEW

#neuronInterface.o: neuronInterface.cpp
#	g++ -c neuronInterface.cpp