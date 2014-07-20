all: bounce

bounce: main.o gui.o pump.o spider.o arrow.o water.o game.o level.o painter.o wall.o gameObject.o dynamicBody.o player.o sprite.o contactListener.o spike.o checkpoint.o portal.o ring.o life.o
	g++ -g -o bounce gui.o pump.o spider.o water.o arrow.o main.o game.o painter.o level.o wall.o gameObject.o dynamicBody.o player.o sprite.o contactListener.o spike.o checkpoint.o ring.o life.o portal.o -lSDL2 -lSDL2_image -lBox2D -ltinyxml -lz -ltmxparser

# bounce: main.o
# 	g++ -g -o bounce main.o -lSDL2 -lSDL2_image

# # %o: %.cpp
# # 	g++ -c $<

# main.o: game.o ResInit.o
# 	g++ -c main.cpp game.cpp ResInit.cpp -lSDL2 -lSDL2_image

# game.o:
# 	g++ -c game.cpp

# # # levels.o:
# # # 	g++ -c levels.cpp

# # # gameObject.o:
# # # 	g++ -c gameObject.cpp

# # # player.o:
# # # 	g++ -c player.cpp

# # # wall.o:
# # # 	g++ -c wall.cpp

# # game.o: game.h game.cpp player.h
# # 	g++ -c game.cpp

# # player.o: player.h player.cpp
# # 	g++ -c player.cpp
# # 	# g++ -c main.cpp levels.cpp player.cpp wall.cpp -lSDL2 -lSDL2_image -lBox2D

# # gameObject.o: gameObject.cpp dynamicBody.h
# #  	g++ -c gameObject.cpp -lSDL2 -lSDL2_image -lBox2D

# # dynamicBody.o:dynamicBody.cpp
# # 	g++ -c dynamicBody.cpp -lBox2D

# # game.o:
#  	# g++ -c game.cpp

# # levels.o:
# # 	g++ -c levels.cpp

# # gameObject.o:
# # 	g++ -c gameObject.cpp

# # player.o:
# # 	g++ -c player.cpp

# spike.o: spike.cpp
# 	g++ -c spike.cpp

# wall.o:
# 	g++ -c wall.cpp

# gameObject.o: gameObject.cpp
# 	g++ -c gameObject.cpp -lBox2D

# dynamicBody.o: dynamicBody.cpp
# 	g++ -c dynamicBody.cpp -lBox2D

# sprite.o: sprite.cpp
# 	g++ -c sprite.cpp -lSDL2 -lSDL2_image

clean:
	rm *.o