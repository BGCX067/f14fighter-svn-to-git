#include "CEGUIKeyboard.h"
#include "../Manager/DataManager/DataManager.h"

CEGUIKeyboard::CEGUIKeyboard(void)
:	buttonA(0), buttonB(0), buttonC(0), buttonD(0), buttonE(0), buttonF(0), buttonG(0), buttonH(0), buttonI(0), 
	buttonJ(0), buttonK(0), buttonL(0), buttonM(0), buttonN(0), buttonO(0), buttonP(0), buttonQ(0), buttonR(0), 
	buttonS(0), buttonT(0), buttonU(0), buttonV(0), buttonW(0), buttonX(0), buttonY(0), buttonZ(0), 
	buttonDel(0), buttonReturn(0), text(0),showKeyboard(false), buttonAT(0),buttonATFhsalzburg(0), buttonATGmx(0), buttonATHotmail(0),
	buttonATGmail(0), buttonATYahoo(0), buttonDot(0), buttonUnderline(0), buttonMinus(0)
{
	dataManager = DataManager::getDataManagerAsSingleton();
}

CEGUIKeyboard::~CEGUIKeyboard(void)
{
	CEGUIWin->destroyAllWindows();

	if(buttonA)	{	buttonA->removeAllEvents();	buttonA->destroy();	buttonA = 0;	}
	if(buttonB)	{	buttonB->removeAllEvents();	buttonB->destroy();	buttonB = 0;	}
	if(buttonC)	{	buttonC->removeAllEvents();	buttonC->destroy();	buttonC = 0;	}
	if(buttonD)	{	buttonD->removeAllEvents();	buttonD->destroy();	buttonD = 0;	}
	if(buttonE)	{	buttonE->removeAllEvents();	buttonE->destroy();	buttonE = 0;	}
	if(buttonF)	{	buttonF->removeAllEvents();	buttonF->destroy();	buttonF = 0;	}
	if(buttonG)	{	buttonG->removeAllEvents();	buttonG->destroy();	buttonG = 0;	}
	if(buttonH)	{	buttonH->removeAllEvents();	buttonH->destroy();	buttonH = 0;	}
	if(buttonI)	{	buttonI->removeAllEvents();	buttonI->destroy();	buttonI = 0;	}
	if(buttonJ)	{	buttonJ->removeAllEvents();	buttonJ->destroy();	buttonJ = 0;	}
	if(buttonK)	{	buttonK->removeAllEvents();	buttonK->destroy();	buttonK = 0;	}
	if(buttonL)	{	buttonL->removeAllEvents();	buttonL->destroy();	buttonL = 0;	}
	if(buttonM)	{	buttonM->removeAllEvents();	buttonM->destroy();	buttonM = 0;	}
	if(buttonN)	{	buttonN->removeAllEvents();	buttonN->destroy();	buttonN = 0;	}
	if(buttonO)	{	buttonO->removeAllEvents();	buttonO->destroy();	buttonO = 0;	}
	if(buttonP)	{	buttonP->removeAllEvents();	buttonP->destroy();	buttonP = 0;	}
	if(buttonQ)	{	buttonQ->removeAllEvents();	buttonQ->destroy();	buttonQ = 0;	}
	if(buttonR)	{	buttonR->removeAllEvents();	buttonR->destroy();	buttonR = 0;	}
	if(buttonS)	{	buttonS->removeAllEvents();	buttonS->destroy();	buttonS = 0;	}
	if(buttonT)	{	buttonT->removeAllEvents();	buttonT->destroy();	buttonT = 0;	}
	if(buttonU)	{	buttonU->removeAllEvents();	buttonU->destroy();	buttonU = 0;	}
	if(buttonV)	{	buttonV->removeAllEvents();	buttonV->destroy();	buttonV = 0;	}
	if(buttonW)	{	buttonW->removeAllEvents();	buttonW->destroy();	buttonW = 0;	}
	if(buttonX)	{	buttonX->removeAllEvents();	buttonX->destroy();	buttonX = 0;	}
	if(buttonY)	{	buttonY->removeAllEvents();	buttonY->destroy();	buttonY = 0;	}
	if(buttonZ)	{	buttonZ->removeAllEvents();	buttonZ->destroy();	buttonZ = 0;	}
	if(buttonDel)		{	buttonDel->removeAllEvents();		buttonDel->destroy();		buttonDel = 0;	}
	if(buttonReturn)	{	buttonReturn->removeAllEvents();	buttonReturn->destroy();	buttonReturn = 0;	}
	if(text)			{	text->removeAllEvents();			text->destroy();			text = 0;	}
	if(buttonAT)
		
	if(buttonATFhsalzburg)	{	buttonATFhsalzburg->removeAllEvents();	buttonATFhsalzburg->destroy();	buttonATFhsalzburg = 0;	}
	if(buttonATGmx)			{	buttonATGmx->removeAllEvents();			buttonATGmx->destroy();			buttonATGmx = 0;	}
	if(buttonATHotmail)		{	buttonATHotmail->removeAllEvents();		buttonATHotmail->destroy();		buttonATHotmail = 0;	}
	if(buttonATGmail)		{	buttonATGmail->removeAllEvents();		buttonATGmail->destroy();		buttonATGmail = 0;	}
	if(buttonATYahoo)		{	buttonATYahoo->removeAllEvents();		buttonATYahoo->destroy();		buttonATYahoo = 0;	}
	if(buttonDot)			{	buttonDot->removeAllEvents();			buttonDot->destroy();			buttonDot = 0;	}
	if(buttonUnderline)		{	buttonUnderline->removeAllEvents();		buttonUnderline->destroy();		buttonUnderline = 0;	}
	if(buttonMinus)			{	buttonMinus->removeAllEvents();			buttonMinus->destroy();			buttonMinus = 0;	}
}
void CEGUIKeyboard::setupGUI(float positionX, float positionY)
{
	if(dataManager->CEGUISystem)
	{
		//WINDOW AND SHEET FOR DataManagerMenu
		// Quit button
		CEGUIWin = CEGUI::WindowManager::getSingletonPtr();
		CEGUISheet = CEGUIWin->createWindow("DefaultGUISheet", "F14/Keyboard");

		inputText ="";
		/////////////////
		//Text
		text = CEGUIWin->createWindow("TaharezLook/StaticText", "F14/keyboard/text");
	    text->setSize(CEGUI::UVector2(CEGUI::UDim(0.05*10, 0), CEGUI::UDim(0.05, 0)));
		text->setPosition(CEGUI::UVector2(CEGUI::UDim(positionX, 0), CEGUI::UDim(positionY, 0)));
		CEGUISheet->addChildWindow(text);


		///////////////////
		////make buttons
	    buttonA = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonA");
		buttonB = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonB");
		buttonC = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonC");
		buttonD = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonD");
		buttonE = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonE");
		buttonF = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonF");
		buttonG = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonG");
		buttonH = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonH");
		buttonI = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonI");
		buttonJ = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonJ");
		buttonK = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonK");
		buttonL = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonL");
		buttonM = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonM");
		buttonN = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonN");
		buttonO = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonO");
		buttonP = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonP");
		buttonQ = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonQ");
		buttonR = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonR");
		buttonS = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonS");
		buttonT = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonT");
		buttonU = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonU");
		buttonV = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonV");
		buttonW = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonW");
		buttonX = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonX");
		buttonY = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonY");
		buttonZ = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonZ");

		buttonDel = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonDel");
		buttonReturn = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonReturn");

		buttonAT = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonAT");
		buttonATFhsalzburg = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonATFhsalzburg");
		buttonATGmx = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonATGmx");
		buttonATHotmail = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonATHotmail");
		buttonATGmail = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonATGmail");
		buttonATYahoo = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonATYahoo");
	
		buttonDot = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonDot");
		buttonUnderline = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonUnderline");
		buttonMinus = CEGUIWin->createWindow("TaharezLook/Button", "f14/keyboard/buttonMinus");


	    buttonA->setText("A");
		buttonB->setText("B");
		buttonC->setText("C");
		buttonD->setText("D");
		buttonE->setText("E");
		buttonF->setText("F");
		buttonG->setText("G");
		buttonH->setText("H");
		buttonI->setText("I");
		buttonJ->setText("J");
		buttonK->setText("K");
		buttonL->setText("L");
		buttonM->setText("M");
		buttonN->setText("N");
		buttonO->setText("O");
		buttonP->setText("P");
		buttonQ->setText("Q");
		buttonR->setText("R");
		buttonS->setText("S");
		buttonT->setText("T");
		buttonU->setText("U");
		buttonV->setText("V");
		buttonW->setText("W");
		buttonX->setText("X");
		buttonY->setText("Y");
		buttonZ->setText("Z");

		buttonDel->setText("Del");
		buttonReturn->setText("Return");
	
		buttonAT->setText("@");
		buttonATFhsalzburg->setText("@fh-salzburg.ac.at");
		buttonATGmx->setText("@gmx.at");
		buttonATHotmail->setText("@hotmail.at");
		buttonATGmail->setText("@gmail.at");
		buttonATYahoo->setText("@yahoo.at");

		buttonDot->setText(".");
		buttonUnderline->setText("_");
		buttonMinus->setText("-");
	
		float size = 0.05;
		buttonA->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonB->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonC->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonD->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonE->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonF->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonG->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonH->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonI->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonJ->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonK->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonL->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonM->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonN->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonO->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonP->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonQ->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonR->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonS->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonT->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonU->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonV->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonW->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonX->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonY->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonZ->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		
		buttonDel->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonReturn->setSize(CEGUI::UVector2(CEGUI::UDim(size*2, 0), CEGUI::UDim(size, 0)));
		
		buttonAT->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonATFhsalzburg->setSize(CEGUI::UVector2(CEGUI::UDim(size*3, 0), CEGUI::UDim(size, 0)));
		buttonATGmx->setSize(CEGUI::UVector2(CEGUI::UDim(size*2, 0), CEGUI::UDim(size, 0)));
		buttonATHotmail->setSize(CEGUI::UVector2(CEGUI::UDim(size*2, 0), CEGUI::UDim(size, 0)));
		buttonATGmail->setSize(CEGUI::UVector2(CEGUI::UDim(size*2, 0), CEGUI::UDim(size, 0)));
		buttonATYahoo->setSize(CEGUI::UVector2(CEGUI::UDim(size*2, 0), CEGUI::UDim(size, 0)));
		
		buttonDot->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonUnderline->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));
		buttonMinus->setSize(CEGUI::UVector2(CEGUI::UDim(size, 0), CEGUI::UDim(size, 0)));

		float position1, position2, position3, position4, position5, position6, position7, position8, position9, position10;
		float row1, row2, row3, row4, row5, row6, row7, row8;
		
		position1	= 0.00 + positionX;
		position2	= 0.05 + positionX;
		position3	= 0.10 + positionX;
		position4	= 0.15 + positionX;
		position5	= 0.20 + positionX;
		position6	= 0.25 + positionX;
		position7	= 0.30 + positionX;
		position8	= 0.35 + positionX;
		position9	= 0.40 + positionX;
		position10	= 0.45 + positionX;

		row1 = 0.05 + positionY;
		row2 = 0.10 + positionY;
		row3 = 0.15 + positionY;
		row4 = 0.25 + positionY;
		row5 = 0.30 + positionY;
		row6 = 0.35 + positionY;
		row7 = 0.40 + positionY;
		row8 = 0.45 + positionY;

		float row2Xoffset = 0.02;
		float row3Xoffset = 0.04;
		//ROW ONE
		buttonQ->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row1, 0)));
		buttonW->setPosition(CEGUI::UVector2(CEGUI::UDim(position2, 0), CEGUI::UDim(row1, 0)));
		buttonE->setPosition(CEGUI::UVector2(CEGUI::UDim(position3, 0), CEGUI::UDim(row1, 0)));
		buttonR->setPosition(CEGUI::UVector2(CEGUI::UDim(position4, 0), CEGUI::UDim(row1, 0)));
		buttonT->setPosition(CEGUI::UVector2(CEGUI::UDim(position5, 0), CEGUI::UDim(row1, 0)));
		buttonZ->setPosition(CEGUI::UVector2(CEGUI::UDim(position6, 0), CEGUI::UDim(row1, 0)));
		buttonU->setPosition(CEGUI::UVector2(CEGUI::UDim(position7, 0), CEGUI::UDim(row1, 0)));
		buttonI->setPosition(CEGUI::UVector2(CEGUI::UDim(position8, 0), CEGUI::UDim(row1, 0)));
		buttonO->setPosition(CEGUI::UVector2(CEGUI::UDim(position9, 0), CEGUI::UDim(row1, 0)));
		buttonP->setPosition(CEGUI::UVector2(CEGUI::UDim(position10, 0), CEGUI::UDim(row1, 0)));

		//ROW TWO
		buttonA->setPosition(CEGUI::UVector2(CEGUI::UDim(position1 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonS->setPosition(CEGUI::UVector2(CEGUI::UDim(position2 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonD->setPosition(CEGUI::UVector2(CEGUI::UDim(position3 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonF->setPosition(CEGUI::UVector2(CEGUI::UDim(position4 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonG->setPosition(CEGUI::UVector2(CEGUI::UDim(position5 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonH->setPosition(CEGUI::UVector2(CEGUI::UDim(position6 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonJ->setPosition(CEGUI::UVector2(CEGUI::UDim(position7 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonK->setPosition(CEGUI::UVector2(CEGUI::UDim(position8 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		buttonL->setPosition(CEGUI::UVector2(CEGUI::UDim(position9 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));
		
		buttonDel->setPosition(CEGUI::UVector2(CEGUI::UDim(position10 + row2Xoffset, 0), CEGUI::UDim(row2, 0)));

		//ROW THREE
		buttonAT->setPosition(CEGUI::UVector2(CEGUI::UDim(position1 - 0.01, 0), CEGUI::UDim(row3, 0)));
		buttonY->setPosition(CEGUI::UVector2(CEGUI::UDim(position1 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonX->setPosition(CEGUI::UVector2(CEGUI::UDim(position2 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonC->setPosition(CEGUI::UVector2(CEGUI::UDim(position3 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonV->setPosition(CEGUI::UVector2(CEGUI::UDim(position4 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonB->setPosition(CEGUI::UVector2(CEGUI::UDim(position5 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonN->setPosition(CEGUI::UVector2(CEGUI::UDim(position6 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		buttonM->setPosition(CEGUI::UVector2(CEGUI::UDim(position7 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));
		
		buttonReturn->setPosition(CEGUI::UVector2(CEGUI::UDim(position8 + row3Xoffset, 0), CEGUI::UDim(row3, 0)));

		buttonATFhsalzburg->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row4, 0)));
		buttonATGmx->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row5, 0)));
		buttonATHotmail->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row6, 0)));
		buttonATGmail->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row7, 0)));
		buttonATYahoo->setPosition(CEGUI::UVector2(CEGUI::UDim(position1, 0), CEGUI::UDim(row8, 0)));


		buttonDot->setPosition(CEGUI::UVector2(CEGUI::UDim(position5, 0), CEGUI::UDim(row4, 0)));
		buttonUnderline->setPosition(CEGUI::UVector2(CEGUI::UDim(position5, 0), CEGUI::UDim(row5, 0)));
		buttonMinus->setPosition(CEGUI::UVector2(CEGUI::UDim(position5, 0), CEGUI::UDim(row6, 0)));


		CEGUISheet->addChildWindow(buttonA);
		CEGUISheet->addChildWindow(buttonB);
		CEGUISheet->addChildWindow(buttonC);
		CEGUISheet->addChildWindow(buttonD);
		CEGUISheet->addChildWindow(buttonE);
		CEGUISheet->addChildWindow(buttonF);
		CEGUISheet->addChildWindow(buttonG);
		CEGUISheet->addChildWindow(buttonH);
		CEGUISheet->addChildWindow(buttonI);
		CEGUISheet->addChildWindow(buttonJ);
		CEGUISheet->addChildWindow(buttonK);
		CEGUISheet->addChildWindow(buttonL);
		CEGUISheet->addChildWindow(buttonM);
		CEGUISheet->addChildWindow(buttonN);
		CEGUISheet->addChildWindow(buttonO);
		CEGUISheet->addChildWindow(buttonP);
		CEGUISheet->addChildWindow(buttonQ);
		CEGUISheet->addChildWindow(buttonR);
		CEGUISheet->addChildWindow(buttonS);
		CEGUISheet->addChildWindow(buttonT);
		CEGUISheet->addChildWindow(buttonU);
		CEGUISheet->addChildWindow(buttonV);
		CEGUISheet->addChildWindow(buttonW);
		CEGUISheet->addChildWindow(buttonX);
		CEGUISheet->addChildWindow(buttonY);
		CEGUISheet->addChildWindow(buttonZ);

		CEGUISheet->addChildWindow(buttonDel);
		CEGUISheet->addChildWindow(buttonReturn);

		CEGUISheet->addChildWindow(buttonAT);
		CEGUISheet->addChildWindow(buttonATFhsalzburg);
		CEGUISheet->addChildWindow(buttonATGmx);
		CEGUISheet->addChildWindow(buttonATHotmail);
		CEGUISheet->addChildWindow(buttonATGmail);
		CEGUISheet->addChildWindow(buttonATYahoo);
	
		CEGUISheet->addChildWindow(buttonDot);
		CEGUISheet->addChildWindow(buttonUnderline);
		CEGUISheet->addChildWindow(buttonMinus);
		
		dataManager->CEGUISystem->setGUISheet(CEGUISheet);
		
		CEGUISheet->show();
	}
}
void CEGUIKeyboard::setupEventHandler(void)
{
	buttonA->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::aPressed, this));
	buttonB->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::bPressed, this));
	buttonC->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::cPressed, this));
	buttonD->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::dPressed, this));
	buttonE->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::ePressed, this));
	buttonF->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::fPressed, this));
	buttonG->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::gPressed, this));
	buttonH->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::hPressed, this));
	buttonI->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::iPressed, this));
	buttonJ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::jPressed, this));
	buttonK->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::kPressed, this));
	buttonL->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::lPressed, this));
	buttonM->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::mPressed, this));
	buttonN->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::nPressed, this));
	buttonO->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::oPressed, this));
	buttonP->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::pPressed, this));
	buttonQ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::qPressed, this));
	buttonR->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::rPressed, this));
	buttonS->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::sPressed, this));
	buttonT->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::tPressed, this));
	buttonU->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::uPressed, this));
	buttonV->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::vPressed, this));
	buttonW->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::wPressed, this));
	buttonX->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::xPressed, this));
	buttonY->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::yPressed, this));
	buttonZ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::zPressed, this));

	buttonDel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::delPressed, this));
	buttonReturn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::returnPressed, this));

	buttonAT->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATPressed, this));
	buttonATFhsalzburg->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATFhsalzburgPressed, this));
	buttonATGmx->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATGmxPressed, this));
	buttonATHotmail->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATHotmailPressed, this));
	buttonATGmail->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATGmailPressed, this));
	buttonATYahoo->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonATYahooPressed, this));

	buttonDot->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonDotPressed, this));
	buttonUnderline->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonUnderlinePressed, this));
	buttonMinus->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIKeyboard::buttonMinusPressed, this));
}
void CEGUIKeyboard::updateKeyboard(void)
{
	if(showKeyboard)
		CEGUI::MouseCursor::getSingleton().show();
	else
		CEGUI::MouseCursor::getSingleton().hide();
	text->setText(inputText);
}

bool CEGUIKeyboard::aPressed(const CEGUI::EventArgs &e)
{
	inputText += "A";
	return true;
}

bool CEGUIKeyboard::bPressed(const CEGUI::EventArgs &e)
{
	inputText += "B";
	return true;
}

bool CEGUIKeyboard::cPressed(const CEGUI::EventArgs &e)
{
	inputText += "C";
	return true;
}

bool CEGUIKeyboard::dPressed(const CEGUI::EventArgs &e)
{
	inputText += "D";
	return true;
}

bool CEGUIKeyboard::ePressed(const CEGUI::EventArgs &e)
{
	inputText += "E";
	return true;
}

bool CEGUIKeyboard::fPressed(const CEGUI::EventArgs &e)
{
	inputText += "F";
	return true;
}

bool CEGUIKeyboard::gPressed(const CEGUI::EventArgs &e)
{
	inputText += "G";
	return true;
}

bool CEGUIKeyboard::hPressed(const CEGUI::EventArgs &e)
{
	inputText += "H";
	return true;
}

bool CEGUIKeyboard::iPressed(const CEGUI::EventArgs &e)
{
	inputText += "I";
	return true;
}

bool CEGUIKeyboard::jPressed(const CEGUI::EventArgs &e)
{
	inputText += "J";
	return true;
}

bool CEGUIKeyboard::kPressed(const CEGUI::EventArgs &e)
{
	inputText += "K";
	return true;
}

bool CEGUIKeyboard::lPressed(const CEGUI::EventArgs &e)
{
	inputText += "L";
	return true;
}

bool CEGUIKeyboard::mPressed(const CEGUI::EventArgs &e)
{
	inputText += "M";
	return true;
}

bool CEGUIKeyboard::nPressed(const CEGUI::EventArgs &e)
{
	inputText += "N";
	return true;
}

bool CEGUIKeyboard::oPressed(const CEGUI::EventArgs &e)
{
	inputText += "O";
	return true;
}

bool CEGUIKeyboard::pPressed(const CEGUI::EventArgs &e)
{
	inputText += "P";
	return true;
}

bool CEGUIKeyboard::qPressed(const CEGUI::EventArgs &e)
{
	inputText += "Q";
	return true;
}

bool CEGUIKeyboard::rPressed(const CEGUI::EventArgs &e)
{
	inputText += "R";
	return true;
}

bool CEGUIKeyboard::sPressed(const CEGUI::EventArgs &e)
{
	inputText += "S";
	return true;
}

bool CEGUIKeyboard::tPressed(const CEGUI::EventArgs &e)
{
	inputText += "T";
	return true;
}

bool CEGUIKeyboard::uPressed(const CEGUI::EventArgs &e)
{
	inputText += "U";
	return true;
}

bool CEGUIKeyboard::vPressed(const CEGUI::EventArgs &e)
{
	inputText += "V";
	return true;
}

bool CEGUIKeyboard::wPressed(const CEGUI::EventArgs &e)
{
	inputText += "W";
	return true;
}

bool CEGUIKeyboard::xPressed(const CEGUI::EventArgs &e)
{
	inputText += "X";
	return true;
}

bool CEGUIKeyboard::yPressed(const CEGUI::EventArgs &e)
{
	inputText += "Y";
	return true;
}

bool CEGUIKeyboard::zPressed(const CEGUI::EventArgs &e)
{
	inputText += "Z";
	return true;
}
bool CEGUIKeyboard::buttonATPressed(const CEGUI::EventArgs &e)
{
	inputText += "@";
	return true;
}
bool CEGUIKeyboard::buttonATFhsalzburgPressed(const CEGUI::EventArgs &e)
{
	inputText += "@fh-salzburg.ac.at";
	return true;
}
bool CEGUIKeyboard::buttonATGmxPressed(const CEGUI::EventArgs &e)
{
	inputText += "@gmx.at";
	return true;
}
bool CEGUIKeyboard::buttonATHotmailPressed(const CEGUI::EventArgs &e)
{
	inputText += "@hotmail.at";
	return true;
}
bool CEGUIKeyboard::buttonATGmailPressed(const CEGUI::EventArgs &e)
{
	inputText += "@gmail.at";
	return true;
}
bool CEGUIKeyboard::buttonATYahooPressed(const CEGUI::EventArgs &e)
{
	inputText += "@yahoo.at";
	return true;
}

bool CEGUIKeyboard::buttonDotPressed(const CEGUI::EventArgs &e)
{
	inputText += ".";
	return true;
}
bool CEGUIKeyboard::buttonUnderlinePressed(const CEGUI::EventArgs &e)
{
	inputText += "_";
	return true;
}
bool CEGUIKeyboard::buttonMinusPressed(const CEGUI::EventArgs &e)
{
	inputText += "-";
	return true;
}


bool CEGUIKeyboard::delPressed(const CEGUI::EventArgs &e)
{
	if(inputText.length())
		inputText = inputText.substr(0, inputText.length() - 1);	
	return true;
}

bool CEGUIKeyboard::returnPressed(const CEGUI::EventArgs &e)
{
	showKeyboard = false;	
	return true;
}
