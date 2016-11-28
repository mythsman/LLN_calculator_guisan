#include <iostream>
#include "parser.h"
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include <guisan/sdl/sdltruetypefont.hpp>
#include "SDL2/SDL.h"

bool running = true;

SDL_Window* window;
SDL_Surface* screen;
SDL_Event event;

gcn::SDLInput* input;
gcn::SDLGraphics* graphics;
gcn::SDLImageLoader* imageLoader;

gcn::Gui* gui;
gcn::Container* top;
gcn::SDLTrueTypeFont* font;
gcn::Label* label;
gcn::TextBox* textBox;
gcn::TextBox* textBoxAns;
gcn::ScrollArea* textBoxScrollArea;
gcn::Button *buttonSin,
			*buttonCos,
			*buttonTan,
			*buttonLn,
			*buttonLg,
			*buttonPow,
			*buttonSqrt,
			*buttonPi,
			*buttonE,
			*buttonCls,
			*buttonL,
			*buttonR,
			*buttonDel,
			*button[10],
			*buttonDot,
			*buttonEq,
			*buttonDiv,
			*buttonMul,
			*buttonPlus,
			*buttonMinus,
			*buttonEmpty;

Parser::Parser parser;
class ButtonListener : public gcn::ActionListener{
public:
	void action(const gcn::ActionEvent& actionEvent){
		bool end=false;
		if(actionEvent.getSource()==buttonSin){
			textBox->setText(textBox->getText()+"sin(");
		}else if(actionEvent.getSource()==buttonCos){
			textBox->setText(textBox->getText()+"cos(");
		}else if(actionEvent.getSource()==buttonTan){
			textBox->setText(textBox->getText()+"tan(");
		}else if(actionEvent.getSource()==buttonLn){
			textBox->setText(textBox->getText()+"ln(");
		}else if(actionEvent.getSource()==buttonLg){
			textBox->setText(textBox->getText()+"lg(");
		}else if(actionEvent.getSource()==buttonPow){
			textBox->setText(textBox->getText()+"^");
		}else if(actionEvent.getSource()==buttonSqrt){
			textBox->setText(textBox->getText()+"sqrt(");
		}else if(actionEvent.getSource()==buttonPi){
			textBox->setText(textBox->getText()+"PI");
		}else if(actionEvent.getSource()==buttonE){
			textBox->setText(textBox->getText()+"e");
		}else if(actionEvent.getSource()==buttonCls){
			textBox->setText("");
		}else if(actionEvent.getSource()==buttonL){
			textBox->setText(textBox->getText()+"(");
		}else if(actionEvent.getSource()==buttonR){
			textBox->setText(textBox->getText()+")");
		}else if(actionEvent.getSource()==buttonDel){
			textBox->setText(textBox->getText().substr(0,textBox->getText().length()-1));
		}else if(actionEvent.getSource()==buttonDot){
			textBox->setText(textBox->getText()+".");
		}else if(actionEvent.getSource()==buttonEq){
			end=true;
			std::string preCalculated=parser.calculate(textBox->getText());
		if(parser.getStatus()==Parser::SUCCESS){
		    textBoxAns->setText(preCalculated);
		    textBoxAns->setWidth(520);
		}else{
		    textBoxAns->setText("Error!");
		    textBoxAns->setWidth(520);
		}
		textBox->setCaretColumn(0xffffff);
		textBox->scrollToCaret();
		}else if(actionEvent.getSource()==buttonDiv){
			textBox->setText(textBox->getText()+"/");
		}else if(actionEvent.getSource()==buttonMul){
			textBox->setText(textBox->getText()+"*");
		}else if(actionEvent.getSource()==buttonPlus){
			textBox->setText(textBox->getText()+"+");
		}else if(actionEvent.getSource()==buttonMinus){
			textBox->setText(textBox->getText()+"-");
		}else if(actionEvent.getSource()==buttonEmpty){
			//do nothing
		}else if(actionEvent.getSource()==button[0]){
			textBox->setText(textBox->getText()+"0");
		}else if(actionEvent.getSource()==button[1]){
			textBox->setText(textBox->getText()+"1");
		}else if(actionEvent.getSource()==button[2]){
			textBox->setText(textBox->getText()+"2");
		}else if(actionEvent.getSource()==button[3]){
			textBox->setText(textBox->getText()+"3");
		}else if(actionEvent.getSource()==button[4]){
			textBox->setText(textBox->getText()+"4");
		}else if(actionEvent.getSource()==button[5]){
			textBox->setText(textBox->getText()+"5");
		}else if(actionEvent.getSource()==button[6]){
			textBox->setText(textBox->getText()+"6");
		}else if(actionEvent.getSource()==button[7]){
			textBox->setText(textBox->getText()+"7");
		}else if(actionEvent.getSource()==button[8]){
			textBox->setText(textBox->getText()+"8");
		}else if(actionEvent.getSource()==button[9]){
			textBox->setText(textBox->getText()+"9");
		}
		if(end)
			return ;
		std::string preCalculated=parser.calculate(textBox->getText());
		if(parser.getStatus()==Parser::SUCCESS){
			textBoxAns->setText(preCalculated);
			textBoxAns->setWidth(520);
		}else{
			textBoxAns->setText("");
			textBoxAns->setWidth(520);
		}
		textBox->setCaretColumn(0xffffff);
		textBox->scrollToCaret();
	}
}*buttonListener;
void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Science Calculator",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 540, 720,
		0);

	screen = SDL_GetWindowSurface(window);
	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::SDLGraphics();
	graphics->setTarget(screen);
	input = new gcn::SDLInput();

	top = new gcn::Container();
	top->setDimension(gcn::Rectangle(0, 0, 540, 720));
	gui = new gcn::Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);
	TTF_Init();
	font = new gcn::SDLTrueTypeFont("font/FreeSans.ttf",50);
	gcn::Widget::setGlobalFont(font);

	label = new gcn::Label("Science Calculator");
	label->setPosition(80, 20);
	top->add(label);
	
	textBox=new gcn::TextBox("");
	textBox->setEditable(false);
	textBoxScrollArea = new gcn::ScrollArea(textBox);
	textBoxScrollArea->setScrollPolicy(gcn::ScrollArea::SHOW_ALWAYS,gcn::ScrollArea::SHOW_NEVER);
	textBoxScrollArea->setWidth(520);
	textBoxScrollArea->setHeight(70);
	textBoxScrollArea->setBorderSize(1);
	top->add(textBoxScrollArea, 10,100 );	
	
	textBoxAns=new gcn::TextBox("");
	textBoxAns->setWidth(520);
	textBoxAns->setEditable(false);
	top->add(textBoxAns,10,200);

	buttonListener=new ButtonListener();
	buttonEmpty=new gcn::Button("");
	buttonEmpty->setWidth(96);
	buttonEmpty->setHeight(60);
	buttonEmpty->addActionListener(buttonListener);
	top->add(buttonEmpty,10,290);
	
	buttonSqrt=new gcn::Button("sqrt");
	buttonSqrt->setWidth(96);
	buttonSqrt->setHeight(60);
	buttonSqrt->addActionListener(buttonListener);
	top->add(buttonSqrt,116,290);
	
	buttonPow=new gcn::Button("^");
	buttonPow->setWidth(96);
	buttonPow->setHeight(60);
	buttonPow->addActionListener(buttonListener);
	top->add(buttonPow,222,290);
	
	buttonPi=new gcn::Button("pi");
	buttonPi->setWidth(96);
	buttonPi->setHeight(60);
	buttonPi->addActionListener(buttonListener);
	top->add(buttonPi,328,290);
	
	buttonCls=new gcn::Button("cls");
	buttonCls->setWidth(96);
	buttonCls->setHeight(60);
	buttonCls->addActionListener(buttonListener);
	top->add(buttonCls,434,290);
	
	buttonSin=new gcn::Button("sin");
	buttonSin->setWidth(96);
	buttonSin->setHeight(60);
	buttonSin->addActionListener(buttonListener);
	top->add(buttonSin,10,360);

	buttonL=new gcn::Button("(");
	buttonL->setWidth(96);
	buttonL->setHeight(60);
	buttonL->addActionListener(buttonListener);
	top->add(buttonL,116,360);

	buttonR=new gcn::Button(")");
	buttonR->setWidth(96);
	buttonR->setHeight(60);
	buttonR->addActionListener(buttonListener);
	top->add(buttonR,222,360);

	buttonE=new gcn::Button("e");
	buttonE->setWidth(96);
	buttonE->setHeight(60);
	buttonE->addActionListener(buttonListener);
	top->add(buttonE,328,360);

	buttonDel=new gcn::Button("del");
	buttonDel->setWidth(96);
	buttonDel->setHeight(60);
	buttonDel->addActionListener(buttonListener);
	top->add(buttonDel,434,360);

	buttonCos=new gcn::Button("cos");
	buttonCos->setWidth(96);
	buttonCos->setHeight(60);
	buttonCos->addActionListener(buttonListener);
	top->add(buttonCos,10,430);

	button[7]=new gcn::Button("7");
	button[7]->setWidth(96);
	button[7]->setHeight(60);
	button[7]->addActionListener(buttonListener);
	top->add(button[7],116,430);

	button[8]=new gcn::Button("8");
	button[8]->setWidth(96);
	button[8]->setHeight(60);
	button[8]->addActionListener(buttonListener);
	top->add(button[8],222,430);

	button[9]=new gcn::Button("9");
	button[9]->setWidth(96);
	button[9]->setHeight(60);
	button[9]->addActionListener(buttonListener);
	top->add(button[9],328,430);

	buttonDiv=new gcn::Button("/");
	buttonDiv->setWidth(96);
	buttonDiv->setHeight(60);
	buttonDiv->addActionListener(buttonListener);
	top->add(buttonDiv,434,430);

	buttonTan=new gcn::Button("tan");
	buttonTan->setWidth(96);
	buttonTan->setHeight(60);
	buttonTan->addActionListener(buttonListener);
	top->add(buttonTan,10,500);

	button[4]=new gcn::Button("4");
	button[4]->setWidth(96);
	button[4]->setHeight(60);
	button[4]->addActionListener(buttonListener);
	top->add(button[4],116,500);

	button[5]=new gcn::Button("5");
	button[5]->setWidth(96);
	button[5]->setHeight(60);
	button[5]->addActionListener(buttonListener);
	top->add(button[5],222,500);

	button[6]=new gcn::Button("6");
	button[6]->setWidth(96);
	button[6]->setHeight(60);
	button[6]->addActionListener(buttonListener);
	top->add(button[6],328,500);

	buttonMul=new gcn::Button("*");
	buttonMul->setWidth(96);
	buttonMul->setHeight(60);
	buttonMul->addActionListener(buttonListener);
	top->add(buttonMul,434,500);

	buttonLn=new gcn::Button("ln");
	buttonLn->setWidth(96);
	buttonLn->setHeight(60);
	buttonLn->addActionListener(buttonListener);
	top->add(buttonLn,10,570);

	button[1]=new gcn::Button("1");
	button[1]->setWidth(96);
	button[1]->setHeight(60);
	button[1]->addActionListener(buttonListener);
	top->add(button[1],116,570);

	button[2]=new gcn::Button("2");
	button[2]->setWidth(96);
	button[2]->setHeight(60);
	button[2]->addActionListener(buttonListener);
	top->add(button[2],222,570);

	button[3]=new gcn::Button("3");
	button[3]->setWidth(96);
	button[3]->setHeight(60);
	button[3]->addActionListener(buttonListener);
	top->add(button[3],328,570);

	buttonMinus=new gcn::Button("-");
	buttonMinus->setWidth(96);
	buttonMinus->setHeight(60);
	buttonMinus->addActionListener(buttonListener);
	top->add(buttonMinus,434,570);

	buttonLg=new gcn::Button("lg");
	buttonLg->setWidth(96);
	buttonLg->setHeight(60);
	buttonLg->addActionListener(buttonListener);
	top->add(buttonLg,10,640);

	buttonLg=new gcn::Button("lg");
	buttonLg->setWidth(96);
	buttonLg->setHeight(60);
	buttonLg->addActionListener(buttonListener);
	top->add(buttonLg,10,640);

	button[0]=new gcn::Button("0");
	button[0]->setWidth(96);
	button[0]->setHeight(60);
	button[0]->addActionListener(buttonListener);
	top->add(button[0],116,640);

	buttonDot=new gcn::Button(".");
	buttonDot->setWidth(96);
	buttonDot->setHeight(60);
	buttonDot->addActionListener(buttonListener);
	top->add(buttonDot,222,640);

	buttonEq=new gcn::Button("=");
	buttonEq->setWidth(96);
	buttonEq->setHeight(60);
	buttonEq->addActionListener(buttonListener);
	top->add(buttonEq,328,640);

	buttonPlus=new gcn::Button("+");
	buttonPlus->setWidth(96);
	buttonPlus->setHeight(60);
	buttonPlus->addActionListener(buttonListener);
	top->add(buttonPlus,434,640);

}

void halt()
{
	delete label;
	delete font;
	delete top;
	delete gui;

	delete input;
	delete graphics;
	delete imageLoader;

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void checkInput()
{
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}
		}
		else if(event.type == SDL_QUIT)
		{
			running = false;
		}
		input->pushInput(event);
	}
}
void run()
{
	while(running)
	{
		checkInput();
		gui->logic();
		gui->draw();
		SDL_UpdateWindowSurface(window);
	}
}

int main(int argc, char **argv)
{
 	init();
	run();
	halt();
	return 0;
}
