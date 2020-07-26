#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Collision.h"


void events_controller(sf::RenderWindow &window ,bool &band , sf::Sprite &cursor, sf::Sprite &select , sf::Vector2i &aux,sf::Vector2i &cell );

int main()
{
	
	std::list<int> tiles;
	std::list<int>::iterator i;
	
	std::list< std::list<int> > matriz; 
	std::list< std::list<int> >::iterator m_iterator; 
	
	sf::Vector2f origen;//varibles del pitado del mapa
	sf::Vector2f origen_punto;
	sf::Vector2f posicion;
	
	sf::Vector2i select_position;
	
	
	
	
//	sf::Texture select_texture;
//	select_texture.loadFromFile("assets/tile2.png");
//	select.setTexture(&select_texture);
//	select.setOrigin({0,0});
	
	//
		
	bool band=false;

	for(int i=0;i<20;i++){
		
		tiles.push_back(1);
	}
	for(int i=0;i<20;i++){
		
		matriz.push_back(tiles);	
	}
	
	std::cout<<matriz.size()<<std::endl;
	m_iterator=matriz.begin();

	
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("assets/tile.png"))
        return EXIT_FAILURE;
    
        
    sf::Sprite sprite(texture);
    
    sprite.scale(10,10);
    
    
    
    
            
    sf::Sprite sprite2(texture);
    sprite2.setColor(sf::Color::Red);
    sprite2.scale(10,10);
//    sprite.setOrigin({20,10});
    // Create a graphical text to display
	
	origen.x=(matriz.size())*((texture.getSize().x)/2);
	
	if(matriz.size()%2==0){
		origen_punto.x= matriz.size()/2;
	}else{
		origen_punto.x= 1 + (matriz.size()/2); 
	}
	
	origen_punto.y=0;

	
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML window");
    
    window.setFramerateLimit(10);

		sf::Texture triangulox;
		triangulox.loadFromFile("assets/prueba.png");
		sf::Image img;
		img.loadFromFile("assets/prueba.png");
		
		sf::Sprite triangulo_s;
		triangulo_s.setTexture(triangulox);
		triangulo_s.scale(10,10);
	
		
		sf::Texture cursor;
		cursor.loadFromFile("assets/cursor.png");
		
		sf::Sprite cursor_s(cursor);
		
		
		sf::Vector2i mouse_pos;
			
		window.display();
		
		
		sf::Vector2f r_size;
		r_size.x=400;
		r_size.y=200;
		sf::RectangleShape select(r_size);
		select.setFillColor(sf::Color(0,0,0,0));
		select.setOutlineColor(sf::Color(255,0,0));
		select.setOutlineThickness(-1);
		
		
		
		sf::Vector2i select_cell(0,0);
		
		
		

		
		
    while (window.isOpen())
    {
//
		window.clear();
		
		events_controller(window,band,cursor_s,triangulo_s, mouse_pos, select_cell);

		for(int i=0;i<4;i++){
			
			//cada linea siempre tendra el mismo pos en y 
			
			posicion.y = ( ( 100  * i ) );
			posicion.x = origen.x - ( i*200 )- 200;
			
			for(int y=0;y<4;y++){
				
				posicion.x +=  ( 200 );
				sprite.setPosition(posicion);
				posicion.y +=  ( 100 );
				
				window.draw(sprite);	
				
			}
		}
//		
//			select.setPosition( mouse_pos.x*400 , mouse_pos.y*200);
//			triangulo_s.setPosition( mouse_pos.x*400 , mouse_pos.y*200);
			
//			window.draw(select);
//			window.draw(triangulo_s);
			
			
		if(Collision::PixelPerfectTest(triangulo_s,cursor_s)){
				
//				std::cout<<"colision  " << mouse_pos.x%400 <<" : " <<mouse_pos.y%200<<std::endl;
				
				if(mouse_pos.x%400<200 && mouse_pos.y%200<100){
					
					std::cout<<"Esquina superior\n";
					
					sprite2.setPosition(triangulo_s.getPosition().x-200 ,triangulo_s.getPosition().y-100 );
					
				}
				if(mouse_pos.x%400>200 && mouse_pos.y%200<100){
					
					std::cout<<"Esquina superior der \n";
					sprite2.setPosition(triangulo_s.getPosition().x+200 ,triangulo_s.getPosition().y-100 );
				}				
				if(mouse_pos.x%400<200 && mouse_pos.y%200>100){
					
					std::cout<<"Esquina inferior\n";
					sprite2.setPosition(triangulo_s.getPosition().x-200 ,triangulo_s.getPosition().y+100 );
				}				
				if(mouse_pos.x%400>200 && mouse_pos.y%200>100){
					
					std::cout<<"Esquina inferior der\n";
					sprite2.setPosition(triangulo_s.getPosition().x+200 ,triangulo_s.getPosition().y+100 );
				}
				
				
				
				
		}else{
			
				sprite2.setPosition(triangulo_s.getPosition().x ,triangulo_s.getPosition().y );				
		}
		
		window.draw(sprite2);
		
		window.display();
    }

		
		std::cin.get();
    return EXIT_SUCCESS;
}

void events_controller(sf::RenderWindow &window ,  bool &band ,sf::Sprite &cursor , sf::Sprite &select ,sf::Vector2i &aux,sf::Vector2i &cell ){
		
	sf::Event event;
	sf::Vector2i mouse_position;
	sf::Vector2i origen(sf::Vector2f(10,0));

		
	while(window.pollEvent(event)){
		
		switch(event.type){
			
			case sf::Event::Closed:
				window.close();exit(1);
				break;
			
			case sf::Event::MouseEntered:
				band=true;
				break;
			case sf::Event::MouseLeft:
				band=false;
				break;					
			case sf::Event::MouseMoved:
			
				if(band){
					mouse_position = sf::Mouse::getPosition(window);
					mouse_position= (sf::Vector2i)window.mapPixelToCoords(mouse_position);
					
//					std::cout<<(mouse_position.x / 400 ) <<":"<<mouse_position.y / 200<<std::endl;
//					std::cout<<(mouse_position.x % 256) <<":"<<mouse_position.y % 128<<std::endl;
					
					cursor.setPosition((sf::Vector2f)mouse_position);
					
//					
//				if( (mouse_position.x < 200  && mouse_position.y < 100 )){
//					
//					std::cout<<"Esquina superior "<<std::endl;
//					
//				}

					
						aux.x=mouse_position.x/400;
						aux.y=mouse_position.y/200;
						
					select.setPosition(sf::Vector2f(aux.x*400, aux.y*200));
						
						
						
						
					
					aux= mouse_position;

				}
				break;
		}
			 			
	}	
}
