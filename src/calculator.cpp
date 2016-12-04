#include <iostream>
#include "parser.h"
#include <guisan.hpp>
#include <guisan/sdl.hpp>
#include <guisan/sdl/sdltruetypefont.hpp>
#include "SDL2/SDL.h"

bool running = true;

const int WIDTH=405;
const int HEIGHT=720;

SDL_Window* window;
SDL_Surface* screen;
SDL_Event event;

gcn::SDLInput* input;
gcn::SDLGraphics* graphics;
gcn::SDLImageLoader* imageLoader;

gcn::Gui* gui;
gcn::Container* top;
gcn::SDLTrueTypeFont* font;
gcn::TextBox* textBox;
gcn::TextBox* textBoxAns;
gcn::ScrollArea *textBoxScrollArea,*textBoxAnsScrollArea;
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

Parser parser;
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
		if(preCalculated!="Error"){
		    textBoxAns->setText("="+preCalculated);
		    textBoxAns->setWidth(WIDTH);
		}else{
		    textBoxAns->setText(preCalculated);
		    textBoxAns->setWidth(WIDTH);
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
		if(preCalculated!="Error"){
			textBoxAns->setText("="+preCalculated);
			textBoxAns->setWidth(WIDTH);
		}else{
			textBoxAns->setText("=");
			textBoxAns->setWidth(WIDTH);
		}
		textBox->setCaretColumn(0xffffff);
		textBox->scrollToCaret();
	}
}*buttonListener;
void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Science Calculator",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
		0);

	screen = SDL_GetWindowSurface(window);
	imageLoader = new gcn::SDLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	graphics = new gcn::SDLGraphics();
	graphics->setTarget(screen);
	input = new gcn::SDLInput();

	top = new gcn::Container();
	top->setDimension(gcn::Rectangle(0, 0, WIDTH, HEIGHT));
	gui = new gcn::Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);
	TTF_Init();
	font = new gcn::SDLTrueTypeFont("font/FreeSans.ttf",40);

	gcn::Widget::setGlobalFont(font);
	gcn::Color white(255,255,255);
	gcn::Color red(255,99,71);
	gcn::Color yellow(255,255,0);
	gcn::Color blue(0,205,205);
	gcn::Color orange(255,165,79);
	top->setBaseColor(white);

	textBox=new gcn::TextBox("");
	textBox->setEditable(false);
	textBoxScrollArea = new gcn::ScrollArea(textBox);
	textBoxScrollArea->setWidth(WIDTH);
	textBoxScrollArea->setHeight((HEIGHT-WIDTH*6/5)/3);
	textBoxScrollArea->setBaseColor(white);
	top->add(textBoxScrollArea,0,(HEIGHT-WIDTH*6/5)/9);	
	
	textBoxAns=new gcn::TextBox("=");
	textBoxAns->setEditable(false);
	textBoxAnsScrollArea=new gcn::ScrollArea(textBoxAns);
	textBoxAnsScrollArea->setWidth(WIDTH);
	textBoxAnsScrollArea->setHeight((HEIGHT-WIDTH*6/5)/3);
	top->add(textBoxAnsScrollArea,0,(HEIGHT-WIDTH*6/5)*5/9);

	buttonListener=new ButtonListener();
	buttonEmpty=new gcn::Button("");
	buttonEmpty->setWidth(WIDTH/5);
	buttonEmpty->setHeight(WIDTH/5);
	buttonEmpty->setBaseColor(blue);
	buttonEmpty->addActionListener(buttonListener);
	top->add(buttonEmpty,0,HEIGHT-WIDTH*6/5);
	
	buttonSqrt=new gcn::Button("sqrt");
	buttonSqrt->setWidth(WIDTH/5);
	buttonSqrt->setHeight(WIDTH/5);
	buttonSqrt->setBaseColor(blue);
	buttonSqrt->addActionListener(buttonListener);
	top->add(buttonSqrt,WIDTH/5,HEIGHT-WIDTH*6/5);
	
	buttonPow=new gcn::Button("^");
	buttonPow->setWidth(WIDTH/5);
	buttonPow->setHeight(WIDTH/5);
	buttonPow->setBaseColor(blue);
	buttonPow->addActionListener(buttonListener);
	top->add(buttonPow,WIDTH*2/5,HEIGHT-WIDTH*6/5);
	
	buttonPi=new gcn::Button("pi");
	buttonPi->setWidth(WIDTH/5);
	buttonPi->setHeight(WIDTH/5);
	buttonPi->setBaseColor(blue);
	buttonPi->addActionListener(buttonListener);
	top->add(buttonPi,WIDTH*3/5,HEIGHT-WIDTH*6/5);
	
	buttonCls=new gcn::Button("cls");
	buttonCls->setWidth(WIDTH/5);
	buttonCls->setHeight(WIDTH/5);
	buttonCls->setBaseColor(yellow);
	buttonCls->addActionListener(buttonListener);
	top->add(buttonCls,WIDTH*4/5,HEIGHT-WIDTH*6/5);
	
	buttonSin=new gcn::Button("sin");
	buttonSin->setWidth(WIDTH/5);
	buttonSin->setHeight(WIDTH/5);
	buttonSin->setBaseColor(blue);
	buttonSin->addActionListener(buttonListener);
	top->add(buttonSin,0,HEIGHT-WIDTH*5/5);

	buttonL=new gcn::Button("(");
	buttonL->setWidth(WIDTH/5);
	buttonL->setHeight(WIDTH/5);
	buttonL->setBaseColor(blue);
	buttonL->addActionListener(buttonListener);
	top->add(buttonL,WIDTH/5,HEIGHT-WIDTH*5/5);

	buttonR=new gcn::Button(")");
	buttonR->setWidth(WIDTH/5);
	buttonR->setHeight(WIDTH/5);
	buttonR->setBaseColor(blue);
	buttonR->addActionListener(buttonListener);
	top->add(buttonR,WIDTH*2/5,HEIGHT-WIDTH*5/5);

	buttonE=new gcn::Button("e");
	buttonE->setWidth(WIDTH/5);
	buttonE->setHeight(WIDTH/5);
	buttonE->setBaseColor(blue);
	buttonE->addActionListener(buttonListener);
	top->add(buttonE,WIDTH*3/5,HEIGHT-WIDTH*5/5);

	buttonDel=new gcn::Button("del");
	buttonDel->setWidth(WIDTH/5);
	buttonDel->setHeight(WIDTH/5);
	buttonDel->setBaseColor(yellow);
	buttonDel->addActionListener(buttonListener);
	top->add(buttonDel,WIDTH*4/5,HEIGHT-WIDTH*5/5);

	buttonCos=new gcn::Button("cos");
	buttonCos->setWidth(WIDTH/5);
	buttonCos->setHeight(WIDTH/5);
	buttonCos->setBaseColor(blue);
	buttonCos->addActionListener(buttonListener);
	top->add(buttonCos,0,HEIGHT-WIDTH*4/5);

	button[7]=new gcn::Button("7");
	button[7]->setWidth(WIDTH/5);
	button[7]->setHeight(WIDTH/5);
	button[7]->setBaseColor(white);
	button[7]->addActionListener(buttonListener);
	top->add(button[7],WIDTH/5,HEIGHT-WIDTH*4/5);

	button[8]=new gcn::Button("8");
	button[8]->setWidth(WIDTH/5);
	button[8]->setHeight(WIDTH/5);
	button[8]->setBaseColor(white);
	button[8]->addActionListener(buttonListener);
	top->add(button[8],WIDTH*2/5,HEIGHT-WIDTH*4/5);

	button[9]=new gcn::Button("9");
	button[9]->setWidth(WIDTH/5);
	button[9]->setHeight(WIDTH/5);
	button[9]->setBaseColor(white);
	button[9]->addActionListener(buttonListener);
	top->add(button[9],WIDTH*3/5,HEIGHT-WIDTH*4/5);

	buttonDiv=new gcn::Button("/");
	buttonDiv->setWidth(WIDTH/5);
	buttonDiv->setHeight(WIDTH/5);
	buttonDiv->setBaseColor(red);
	buttonDiv->addActionListener(buttonListener);
	top->add(buttonDiv,WIDTH*4/5,HEIGHT-WIDTH*4/5);

	buttonTan=new gcn::Button("tan");
	buttonTan->setWidth(WIDTH/5);
	buttonTan->setHeight(WIDTH/5);
	buttonTan->setBaseColor(blue);
	buttonTan->addActionListener(buttonListener);
	top->add(buttonTan,0,HEIGHT-WIDTH*3/5);

	button[4]=new gcn::Button("4");
	button[4]->setWidth(WIDTH/5);
	button[4]->setHeight(WIDTH/5);
	button[4]->setBaseColor(white);
	button[4]->addActionListener(buttonListener);
	top->add(button[4],WIDTH/5,HEIGHT-WIDTH*3/5);

	button[5]=new gcn::Button("5");
	button[5]->setWidth(WIDTH/5);
	button[5]->setHeight(WIDTH/5);
	button[5]->setBaseColor(white);
	button[5]->addActionListener(buttonListener);
	top->add(button[5],WIDTH*2/5,HEIGHT-WIDTH*3/5);

	button[6]=new gcn::Button("6");
	button[6]->setWidth(WIDTH/5);
	button[6]->setHeight(WIDTH/5);
	button[6]->setBaseColor(white);
	button[6]->addActionListener(buttonListener);
	top->add(button[6],WIDTH*3/5,HEIGHT-WIDTH*3/5);

	buttonMul=new gcn::Button("*");
	buttonMul->setWidth(WIDTH/5);
	buttonMul->setHeight(WIDTH/5);
	buttonMul->setBaseColor(red);
	buttonMul->addActionListener(buttonListener);
	top->add(buttonMul,WIDTH*4/5,HEIGHT-WIDTH*3/5);

	buttonLn=new gcn::Button("ln");
	buttonLn->setWidth(WIDTH/5);
	buttonLn->setHeight(WIDTH/5);
	buttonLn->setBaseColor(blue);
	buttonLn->addActionListener(buttonListener);
	top->add(buttonLn,0,HEIGHT-WIDTH*2/5);

	button[1]=new gcn::Button("1");
	button[1]->setWidth(WIDTH/5);
	button[1]->setHeight(WIDTH/5);
	button[1]->setBaseColor(white);
	button[1]->addActionListener(buttonListener);
	top->add(button[1],WIDTH/5,HEIGHT-WIDTH*2/5);

	button[2]=new gcn::Button("2");
	button[2]->setWidth(WIDTH/5);
	button[2]->setHeight(WIDTH/5);
	button[2]->setBaseColor(white);
	button[2]->addActionListener(buttonListener);
	top->add(button[2],WIDTH*2/5,HEIGHT-WIDTH*2/5);

	button[3]=new gcn::Button("3");
	button[3]->setWidth(WIDTH/5);
	button[3]->setHeight(WIDTH/5);
	button[3]->setBaseColor(white);
	button[3]->addActionListener(buttonListener);
	top->add(button[3],WIDTH*3/5,HEIGHT-WIDTH*2/5);

	buttonMinus=new gcn::Button("-");
	buttonMinus->setWidth(WIDTH/5);
	buttonMinus->setHeight(WIDTH/5);
	buttonMinus->setBaseColor(red);
	buttonMinus->addActionListener(buttonListener);
	top->add(buttonMinus,WIDTH*4/5,HEIGHT-WIDTH*2/5);

	buttonLg=new gcn::Button("lg");
	buttonLg->setWidth(WIDTH/5);
	buttonLg->setHeight(WIDTH/5);
	buttonLg->setBaseColor(blue);
	buttonLg->addActionListener(buttonListener);
	top->add(buttonLg,0,HEIGHT-WIDTH/5);

	button[0]=new gcn::Button("0");
	button[0]->setWidth(WIDTH/5);
	button[0]->setHeight(WIDTH/5);
	button[0]->setBaseColor(white);
	button[0]->addActionListener(buttonListener);
	top->add(button[0],WIDTH/5,HEIGHT-WIDTH/5);

	buttonDot=new gcn::Button(".");
	buttonDot->setWidth(WIDTH/5);
	buttonDot->setHeight(WIDTH/5);
	buttonDot->setBaseColor(white);
	buttonDot->addActionListener(buttonListener);
	top->add(buttonDot,WIDTH*2/5,HEIGHT-WIDTH/5);

	buttonEq=new gcn::Button("=");
	buttonEq->setWidth(WIDTH/5);
	buttonEq->setHeight(WIDTH/5);
	buttonEq->setBaseColor(orange);
	buttonEq->addActionListener(buttonListener);
	top->add(buttonEq,WIDTH*3/5,HEIGHT-WIDTH/5);

	buttonPlus=new gcn::Button("+");
	buttonPlus->setWidth(WIDTH/5);
	buttonPlus->setHeight(WIDTH/5);
	buttonPlus->setBaseColor(red);
	buttonPlus->addActionListener(buttonListener);
	top->add(buttonPlus,WIDTH*4/5,HEIGHT-WIDTH/5);

}

void halt()
{
	delete font;
	delete top;
	delete gui;

	delete input;
	delete graphics;
	delete imageLoader;

	delete textBox;
	delete textBoxAns;
	delete textBoxScrollArea,textBoxAnsScrollArea;
	delete buttonSin,
           buttonCos,
           buttonTan,
           buttonLn,
           buttonLg,
           buttonPow,
           buttonSqrt,
           buttonPi,
           buttonE,
           buttonCls,
           buttonL,
           buttonR,
           buttonDel,
           button[10],
           buttonDot,
           buttonEq,
           buttonDiv,
           buttonMul,
           buttonPlus,
           buttonMinus,
           buttonEmpty;



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
