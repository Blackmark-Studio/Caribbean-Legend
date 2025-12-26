// boal 10.06.05
//   DICE GAME
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start, x_rand, y_rand, r_delta;
bool openExit;
int  money_i, moneyOp_i;
string money_s;

bool bTip[5], bEffect[5];

ref npchar;

int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;
int iHeroLose, iHeroWin;
int iTurnGame; // count for time

object  DiceState;

bool  bLockClick;
bool  bSetRandDice; // жухло компа

string ResultStr;

#define RESULT_FIVE			1
#define RESULT_FOUR			2
#define RESULT_FULL			3
#define RESULT_STRAIGHT		4
#define RESULT_THREE		5
#define RESULT_TWO_PAIRS	6
#define RESULT_PAIR			7
#define RESULT_NOTHING		8

void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eContinueGame","ContinueGame",0);
	SetEventHandler("My_eNewNextGame","NewNextGame",0);
	SetEventHandler("My_eCompTurn","CompTurn",0);
	SetEventHandler("My_eCheckGame","CheckGame",0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("HideInfoWindow","HideInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("Event_NodeMouseEffect", "MouseEffect", 0);
	/*
	gold, silver   - 100x100
	screen: -40..680 x -30..510  (720x540)
	cup: 219x178
	dice: 92x84
	таблица (в прорядке убывания значимости)
	1) Покер - 5 одинаковых
	2) Каре - 4 одинаковых
	3) Фул - 3 + 2
	4) Стрит Бол.стрит - 2,3,4,5,6 Мал.стрит - 1,2,3,4,5
	5) триада - 3 одинаковых
	6) две пары 2 + 2
	7) одна пара 2- одинаковых
	8) ничего нет
	*/
	r_delta = makeint(Bring2Range(20.0, 5.0, 5.0, 20.0, GetRDeltaTime() * 1.0));
    sgxy = 120;
    ssxy = 120;
    
    scx = 92;
    scy = 87;
    
    spx = 354;
    spy = 282;
	
	x_rand = -1;
	y_rand = -1;
    
    openExit = false;  // можно ли прервать игру
    
    pchar = GetMainCharacter();
    
    iRate  = sti(pchar.GenQuest.Dice.iRate); // ставки золотых
    
    npchar = GetCharacter(sti(pchar.GenQuest.Dice.npcharIdx));
    
	iMoneyP = sti(pchar.Money); // mitrokosta реальные деньги смотрим только в начале и в конце
	iMoneyN = sti(npchar.Money);
    
	// mitrokosta фикс опыта за некратные ставки -->
	if (iRate >= 50) {
            money_s = "silver";
            iExpRate = 1;
	}
	if (iRate >= 200) {
            money_s = "gold";
            iExpRate = 2;
	}
	if (iRate >= 500) {
            money_s = "silver";
            SetNewPicture("MAIN_BACK", "interfaces\le\card_sukno.tga");
            iExpRate = 4;
	}
	if (iRate >= 2000) {
            money_s = "gold";
            SetNewPicture("MAIN_BACK", "interfaces\le\card_sukno.tga");
            iExpRate = 8;
	}
	// <--
    
    if (money_s == "gold")
    {
        smxy = sgxy;
    }
    else
    {
        smxy = ssxy;
    }
	
	for(int i = 1; i<=5; i++)
	{
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "HeroDice" + i, 100);
		SetNodeUsing("HeroDice" + i, false);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "CompDice" + i, 100);
		SetNodeUsing("CompDice" + i, false);
		bTip[i-1] = false;
		bEffect[i-1] = false;
	}
	
	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "DiceCup", 100);
	SetNewGroupPicture("DiceCup", "DICE", "cup");
	SetNodePosition("DiceCup", 170, 160, 170 + spx, 160 + spy);

	// CreateImage("GOLD","GOLD","GOLD", 482,444,524,486);
	SetNewPicture("ICON_1", "interfaces\le\portraits\512\face_" + npchar.faceId+ ".tga");
    SetNewPicture("ICON_2", "interfaces\le\portraits\512\face_" + pchar.faceId+ ".tga");
    
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY, 1550,620,SCRIPT_ALIGN_CENTER,2.0);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,1550,520,SCRIPT_ALIGN_CENTER,2.0);
    
    if (rand(1) == 1)
    {
        dir_i  = -1;  // кто ходит - комп
    }
    else
    {
        dir_i  = 1;  // кто ходит - ГГ
    }
    dir_i_start = dir_i; // запомним кто начал
    
    CreateString(true,"Beta_N", "", "INTERFACE_NORMAL",COLOR_NORMAL, 960, 350, SCRIPT_ALIGN_CENTER,2.0);
    CreateString(true,"Beta_P", "", "INTERFACE_NORMAL",COLOR_NORMAL, 960, 710, SCRIPT_ALIGN_CENTER,2.0);
    CreateString(true,"Beta_Next", "", "INTERFACE_NORMAL",COLOR_NORMAL, 580, 520, SCRIPT_ALIGN_LEFT,2.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_NORMAL",COLOR_NORMAL, 1560, 350, SCRIPT_ALIGN_CENTER,2.0);
	CreateString(true,"Beta_TXT", "", "INTERFACE_NORMAL",COLOR_NORMAL, 1560, 250, SCRIPT_ALIGN_CENTER,2.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_NORMAL",COLOR_NORMAL, 1560, 710, SCRIPT_ALIGN_CENTER,1.8);
    iHeroLose = 0;
    iHeroWin  = 0;
    iTurnGame = 1;
    // новая игра
    NewGameBegin(true);
}

void ProcessBreakExit()
{
	Exit();
}

void ProcessCancelExit()
{
	Exit();
}

void Exit()
{
    if (openExit || bBettaTestMode)
    {
        DelEventHandler("InterfaceBreak","ProcessBreakExit");
    	DelEventHandler("exitCancel","ProcessCancelExit");
    	DelEventHandler("ievnt_command","ProcessCommandExecute");
    	DelEventHandler("My_eventMoveImg","MoveImg");
    	DelEventHandler("My_eStartGame","StartGame");
    	DelEventHandler("My_eContinueGame","ContinueGame");
    	DelEventHandler("My_eNewNextGame","NewNextGame");
    	DelEventHandler("My_eCompTurn","CompTurn");
    	DelEventHandler("My_eCheckGame","CheckGame");
		DelEventHandler("ShowInfoWindow","ShowInfoWindow");
		DelEventHandler("HideInfoWindow","HideInfoWindow");
		DelEventHandler("MouseRClickUp","HideInfoWindow");
		DelEventHandler("Event_NodeMouseEffect", "MouseEffect");

        if (sti(pchar.GenQuest.Dice.SitType) == true)
    	{
            DoQuestCheckDelay("exit_sit", 0.6);
    	}
        interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

		bool isWin = (iMoneyP > sti(pchar.Money));

		AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
		AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));
    	Statistic_AddValue(Pchar, "GameDice_Win", iHeroWin);
    	Statistic_AddValue(Pchar, "GameDice_WinMoney", iMoneyP);
		if(!CheckAttribute(Pchar,"questTemp.hat7"))
		{
			if(Statistic_AddValue(Pchar, "GameDice_WinMoney", 0) + Statistic_AddValue(Pchar, "GameCards_WinMoney", 0) > 7776)
			{
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					locations[FindLocation("My_Deck")].box1.items.hat7 = 1;
					Pchar.questTemp.hat7 = true;
				}
			}
		}
		Achievment_SetStat(25, iHeroWin);
		pchar.systeminfo.InGameNotifications = true;
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*4*iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
		DeleteAttribute(pchar,"systeminfo.InGameNotifications");
    	Statistic_AddValue(Pchar, "GameDice_Lose", iHeroLose);
		Achievment_SetStat(26, iHeroLose);
		NPChar.Quest.HeroLose = (iHeroWin < iHeroLose); //navy -- в итоге проиграл или выйграл. (не по деньгам.)

    	bQuestCheckProcessFreeze = true;
    	if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, iTurnGame*15);
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
    	EndCancelInterface(true);

		if (isWin && CheckAttribute(pchar, "GenQuest.Dice.OnWin")) {
			DoQuestFunctionDelay(pchar.GenQuest.Dice.OnWin, 1.0);
		}
		if (!isWin && CheckAttribute(pchar, "GenQuest.Dice.OnLoss")) {
			DoQuestFunctionDelay(pchar.GenQuest.Dice.OnLoss, 1.0);
		}
		DeleteAttribute(pchar, "GenQuest.Dice.OnWin");
		DeleteAttribute(pchar, "GenQuest.Dice.OnLoss");
		DeleteAttribute(pchar, "GenQuest.Dice.DontStop");
	}
	else
    {
        PlaySound("interface\knock.wav");
    }

}

void ShowInfoWindow()
{
	string sHeader,sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	string sCurrentNode = GetEventData();
	sHeader = XI_ConvertString("titleDice");
	sText1 = XI_ConvertString("RulesDice1");
	sText2 = XI_ConvertString("RulesDice2");
	sText3 = XI_ConvertString("RulesDice3");
	
	CreateTooltipNew(sCurrentNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64, false);
}

void HideInfoWindow()
{
	CloseTooltipNew();
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

    if (bLockClick) return;
    
	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   // ещё одна игра
                	dir_i = -dir_i_start;
                	dir_i_start = dir_i;
                    ClearDiceOnTable();
                    iTurnGame++;
                    NewGameBegin(true);
                }
                else
                {
					// ГГ перебрасывает часть кубиков
					// ГГ бросает кубики первый раз кубики
					if (dir_i == 1 && CheckCupForDice())
					{
						SetDiceTip("");
                        bLockClick = true;
						move_i = 0;
				        PlaySound("interface\dice_mix.wav");
						PostEvent("My_eventMoveImg", 100);
					}
					else
					{
					    PlaySound("interface\knock.wav");
					}
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
				if (dir_i_start == 1 && bStartGame == 2)  // пропуск хода
				{
				    CheckGame();
				    break;
				}
				if (dir_i_start == -1 && bStartGame == 3)  // пропуск хода
				{
				    CheckGame();
				    break;
				}
				PlaySound("interface\knock.wav");
    		}
    	break;
    	
    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                //PlaySound("interface\knock.wav");
    		}
    	break;
    	
    	case "B_HeroDice1":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(1);
    		}
    	break;
    	
    	case "B_HeroDice2":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(2);
    		}
    	break;
    	case "B_HeroDice3":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(3);
    		}
    	break;
    	case "B_HeroDice4":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(4);
    		}
    	break;
    	case "B_HeroDice5":
    		if(comName=="activate" || comName=="click")
    		{
                ClickHeroDice(5);
    		}
    	break;
	}
}

void MoveImg()
{
    float t;
	int x1 = 170;
	int y1 = 160;
	int x2 = 770;
	int y2 = 410;
	int x, y;
	move_i++;
	if (move_i < 50)
    {
		if(move_i == 1)
		{
			x_rand = x1 - 150 + rand(x2 - x1 + 300);
			y_rand = y1 - 150 + rand(y2 - y1 + 300);
		}
		t = move_i / 50.0;
		x1 = 170;
		y1 = 160;
		x2 = 770;
		y2 = 410;
		x = makeint((1.0 - t) * (1.0 - t) * x1 + 2.0 * (1.0 - t) * t * x_rand + t * t * x2);
		y = makeint((1.0 - t) * (1.0 - t) * y1 + 2.0 * (1.0 - t) * t * y_rand + t * t * y2);
		SetNodePosition("DiceCup", x, y, x + spx, y + spy);
        PostEvent("My_eventMoveImg", r_delta);
    }
    else
    {
		if(move_i == 50)
		{
			x_rand = x1 + x2 - x_rand;
			y_rand = y1 + y2 - y_rand;
		}

		t = (move_i - 50) / 50.0;
		x = makeint((1.0 - t) * (1.0 - t) * x2 + 2.0 * (1.0 - t) * t * x_rand + t * t * x1);
		y = makeint((1.0 - t) * (1.0 - t) * y2 + 2.0 * (1.0 - t) * t * y_rand + t * t * y1);
        if (move_i <= 100)
        {
			SetNodePosition("DiceCup", x, y, x + spx, y + spy);
            
            if (move_i == 100) // все - собрать кубики в линеку
			{
            	PostEvent("My_eventMoveImg", 200);
            }
			else
			{
            	PostEvent("My_eventMoveImg", r_delta);
            }
        }
        // сброс
        if (move_i == 60)
        {
            PlaySound("interface\dice_end.wav");
			if (bSetRandDice)
			{
            	SetDiceForTableRand(); // случайно, 2й ход компа будем жухлить!!!
            }
            else
            {
                bSetRandDice = true;
            }
            PutDiceOnTable();
        }
		// все - собрать кубики в линеку
        if (move_i == 101)
        {
            SetLineAfterDeck();
        }
    }
}

void PutNextCoin()
{
	CreateImage("Money_"+money_i,"CARDS",money_s, 200+money_i*3, 580-money_i*3, 200+money_i*3 + smxy, 580-money_i*3 + smxy);
}
void PutNextCoinOp()
{
	CreateImage("Money_"+(18+moneyOp_i),"CARDS",money_s, 390+moneyOp_i*3, 580-moneyOp_i*3, 390+moneyOp_i*3 + smxy, 580-moneyOp_i*3 + smxy);
}

void RedrawDeck(bool _newGame, bool _clearDice)
{
    // монетки с запасом
    int i;
    if (_newGame)
    {
	    for (i=55; i>=0; i--)
		{
	        CreateImage("Money_"+i,"","", 0, 0, 0, 0);
		}
		money_i = 0; // индекс монетки
	    moneyOp_i = 0;
	    iChest = 0; // на кону
    }
	// место под кубики
	if (_clearDice)
	{
		for(i = 1; i <= 5; i++)
		{
			SetNodeUsing("HeroDice" + i, false);
			SetNodeUsing("CompDice" + i, false);
		}
    }

    ShowMoney();
    
    SetNextTip();
    BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
    }
    else
    {
    }
}

void BetaInfo()
{
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_MoneyN = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_DiceN  = "Beta_DiceN Type: " + DiceState.Comp.Result.Type + " Rate1: " + DiceState.Comp.Result.Rate1 + " Rate2: " +DiceState.Comp.Result.Rate2;
        GameInterface.strings.Beta_DiceP  = "Beta_DiceP Type: " + DiceState.Hero.Result.Type + " Rate1: " + DiceState.Hero.Result.Rate1 + " Rate2: " +DiceState.Hero.Result.Rate2;
        GameInterface.strings.Beta_TXT    = "dir_i_start " + dir_i_start + " dir_i " + dir_i + " Position " + bStartGame;
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameDice_Win", 0) + iHeroWin)+ " Lose " + (Statistic_AddValue(Pchar, "GameDice_Lose", 0) + iHeroLose)+ " Turn " + iTurnGame;
		if (CheckAttribute(NPchar, "Quest.DiceCheats")) GameInterface.strings.Beta_WinLose = GameInterface.strings.Beta_WinLose + " Cheats " + NPchar.Quest.DiceCheats;
    }
	else
	{
		GameInterface.strings.Beta_WinLose = XI_ConvertString("Win") + iHeroWin + " / " + XI_ConvertString("Lose") + iHeroLose;
	}
}

// сдать карту
void StartGame()
{
	int i;
	move_i = 0;

    PlaySound("interface\took_item.wav");
	if (dir_i == -1) // комп первый
	{
        PlaySound("interface\dice_mix.wav");
		SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase1"));
		PostEvent("My_eventMoveImg", 100);
    }
	else
	{
	    SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase2"));
	    bLockClick = false;
		SetDiceTip("action");
	}
	// оба ставят
	for (i=0; i<5; i++)
	{
		PutNextCoin();
        money_i++;
        iMoneyP = iMoneyP - iRate;
    }
    for (i=0; i<5; i++)
	{
		PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
	}
    iChest += 10*iRate;
    PlaySound("interface\took_item.wav");
    ShowMoney();
}

void ShowMoney()
{
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

void NewGameBegin(bool _newGame)
{
    InitDiceState();
	RedrawDeck(_newGame, true); // новая игра
    bStartGame = 0;
    if (_newGame)
    {
    	SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase3_1")+NewStr()+XI_ConvertString("DicePhrase3_2"));
    }
    else
    {
        SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase4_1")+NewStr()+XI_ConvertString("DicePhrase4_2"));
    }
    bSetRandDice = true;
    PostEvent("My_eStartGame", 1000);
    bLockClick = true;
    openExit = false;
    BetaInfo();
	SetDiceTip("");
}
// деньги в карман
// mitrokosta а теперь не в карман
void EndGameCount(int who)
{
    //openExit = true;
    if (who == 1) // ГГ
    {
		iMoneyP += iChest;
    }
    if (who == -1)
    {
		iMoneyN += iChest;
    }
}

// проверить деньги для след игры
bool CheckNextGame()
{
    bool ret = true;
    if (iRate*6 > iMoneyN) ret = false;
    if (iRate*6 > iMoneyP) ret = false;
    
    return ret;
}

void PutDiceOnTable()
{
    int ix, iy;
    if (DiceState.Desk.d1.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice1","DICE","dice_"+DiceState.Desk.d1+"_" + rand(2), 760+ix, 450+iy, 760 +ix+ + scx, 450 +iy+ scy);
    }
    if (DiceState.Desk.d2.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice2","DICE","dice_"+DiceState.Desk.d2+"_" + rand(2), 880+ix, 420+iy, 880 +ix+ + scx, 420 +iy+ scy);
	}
	if (DiceState.Desk.d3.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice3","DICE","dice_"+DiceState.Desk.d3+"_" + rand(2), 750+ix, 550+iy, 750 +ix+ + scx, 550 +iy+ scy);
	}
	if (DiceState.Desk.d4.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice4","DICE","dice_"+DiceState.Desk.d4+"_" + rand(2), 860+ix, 580+iy, 860 +ix+ + scx, 580 +iy+ scy);
    }
    if (DiceState.Desk.d5.Mix == true)
    {
	    ix = rand(40);
	    iy = rand(40);
	    CreateImage("Dice5","DICE","dice_"+DiceState.Desk.d5+"_" + rand(2), 950+ix, 530+iy, 950 +ix+ + scx, 530 +iy+ scy);
    }
}

void ClearDiceOnTable()
{
    CreateImage("Dice1","","", 0, 0, 0, 0);
    CreateImage("Dice2","","", 0, 0, 0, 0);
    CreateImage("Dice3","","", 0, 0, 0, 0);
    CreateImage("Dice4","","", 0, 0, 0, 0);
    CreateImage("Dice5","","", 0, 0, 0, 0);
}

void InitDiceState()
{
	DeleteAttribute(&DiceState, "");
	
	DiceState.Desk.d1 = "";
    DiceState.Desk.d2 = "";
    DiceState.Desk.d3 = "";
    DiceState.Desk.d4 = "";
    DiceState.Desk.d5 = "";
    
    DiceState.Desk.d1.Mix = true; //сброс
    DiceState.Desk.d2.Mix = true;
    DiceState.Desk.d3.Mix = true;
    DiceState.Desk.d4.Mix = true;
    DiceState.Desk.d5.Mix = true;
    
    DiceState.Hero.d1 = "";
    DiceState.Hero.d2 = "";
    DiceState.Hero.d3 = "";
    DiceState.Hero.d4 = "";
    DiceState.Hero.d5 = "";
    DiceState.Hero.Result.Type  = ""; // тип комбинации
    DiceState.Hero.Result.Rate1 = ""; // значение старшей пары
    DiceState.Hero.Result.Rate2 = "";
    
    DiceState.Hero.d1.Mix = false;
    DiceState.Hero.d2.Mix = false;
    DiceState.Hero.d3.Mix = false;
    DiceState.Hero.d4.Mix = false;
    DiceState.Hero.d5.Mix = false;
    
    DiceState.Comp.d1 = "";
    DiceState.Comp.d2 = "";
    DiceState.Comp.d3 = "";
    DiceState.Comp.d4 = "";
    DiceState.Comp.d5 = "";
    DiceState.Comp.Result.Type  = ""; // тип комбинации
    DiceState.Comp.Result.Rate1 = ""; // значение старшей пары
    DiceState.Comp.Result.Rate2 = ""; // значение младшей пары (если есть, для сравнения фул и две пары, когда старшие равны)
    DiceState.Comp.Result.d1 = ""; // 1-6 колво фишек
    
    DiceState.Comp.d1.Mix = false;
    DiceState.Comp.d2.Mix = false;
    DiceState.Comp.d3.Mix = false;
    DiceState.Comp.d4.Mix = false;
    DiceState.Comp.d5.Mix = false;
}

void ClickHeroDice(int d)
{
	if (bLockClick) return;
	if (bStartGame < 2 || bStartGame > 3)  return;
	sGlobalTemp = "d"+d;
	if (DiceState.Hero.(sGlobalTemp).Mix == true) return; // mitrokosta фикс множественного переброса
	if (iMoneyP >= iRate)
	{
		SetNodeUsing("HeroDice" + d, false);
		DiceState.Hero.(sGlobalTemp).Mix = true;
		DiceState.Desk.(sGlobalTemp).Mix = true;
		PutNextCoin();
	    money_i++;
	    iMoneyP = iMoneyP - iRate;
	    iChest += iRate;
	    PlaySound("interface\took_item.wav");
	    ShowMoney();
		SetDiceTip("action");
		SetNodeUsing("TIP_REROLL", false);
    }
    else
    {
        PlaySound("interface\knock.wav");
    }
}

void SetLineAfterDeck()
{
    int i;
    ClearDiceOnTable();

	if (dir_i == -1) // комп первый
	{
        for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (DiceState.Desk.(sGlobalTemp).Mix == true)
	        {
	            DiceState.Comp.(sGlobalTemp)     = DiceState.Desk.(sGlobalTemp);
	            DiceState.Comp.(sGlobalTemp).Mix = false;
	            if (bStartGame >0 ) DiceState.Desk.(sGlobalTemp).Mix = false;

			}
		}
		SortDiceOnHand("Comp");
		RecalcDiceOnHand("Comp");
		RecalcAIDice("Comp");
		PutCompLine();
	}
	else
	{
        for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (DiceState.Desk.(sGlobalTemp).Mix == true)
	        {
	            DiceState.Hero.(sGlobalTemp)     = DiceState.Desk.(sGlobalTemp);
	            DiceState.Hero.(sGlobalTemp).Mix = false;
	            if (bStartGame >0) DiceState.Desk.(sGlobalTemp).Mix = false;
			}
		}
		SortDiceOnHand("Hero");
		RecalcDiceOnHand("Hero");
		RecalcAIDice("Hero");
		PutHeroLine();
	}
	CheckGame();
}

bool CheckGame()
{
    int i;

	if (dir_i == -1) // комп первый
	{
		dir_i = 1;
		bLockClick = false;
		if (bStartGame <1 )// первый заход
		{
			SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase5"));
		}
		else
		{
			SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase6"));
		}
	}
	else
	{
        dir_i = -1;
        bLockClick = true;
		if (bStartGame <1 )// первый заход
		{
			SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase7"));
			move_i = 0;
	        PlaySound("interface\dice_mix.wav");
	        PostEvent("My_eventMoveImg", 500);
        }
        else
        {
			if (bStartGame <3)
			{
				// решаем ходить ли вообще
	            SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase8"));
	            PostEvent("My_eCompTurn", 800);
            }
        }
	}
	bStartGame++;
	if (bStartGame > 3)
	{
		// подвод итога
		openExit = false;
		bLockClick = true;
		SetDiceTip("");
		if (EndTurnGame())
		{
			PostEvent("My_eNewNextGame", 2000);
		}
		else
		{
			PostEvent("My_eContinueGame", 3500);
		}
	}
	else
	{
		if(dir_i == 1)
			SetDiceTip("action");
		else
			SetDiceTip("");
	}
	BetaInfo();
	return true;
}

void PutCompLine()
{
	int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (DiceState.Comp.(sGlobalTemp).Mix == false)
        {
			SetNodeUsing("CompDice" + i, true);
			SetNewGroupPicture("CompDice" + i, "DICE", "dice_" + DiceState.Comp.(sGlobalTemp) + "_1");
			SetNodePosition("CompDice" + i, 730 + 80*(i-1), 200, 730 + 80*(i-1) + scx, 200 + scy);
		}
	}
}

void PutHeroLine()
{
	int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (DiceState.Hero.(sGlobalTemp).Mix == false)
        {
			SetNodeUsing("HeroDice" + i, true);
			SetNewGroupPicture("HeroDice" + i, "DICE", "dice_" + DiceState.Hero.(sGlobalTemp) + "_1");
			SetNodePosition("HeroDice" + i, 730 + 80*(i-1), 820, 730 + 80*(i-1) + scx, 820 + scy);
		}
	}
}

bool CheckCupForDice()
{
    int i;
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.Desk.(sGlobalTemp).Mix) == true)
        {
            return true;
		}
	}
	return false;
}
// посчитать комбинацию
void RecalcDiceOnHand(string _whom)
{
	int    i, k, iOk;
	string sTemp;
	bool   ok;
	// 1) Покер - 5 одинаковых
	ok = true;
	for (i = 2; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.(_whom).d1) != sti(DiceState.(_whom).(sGlobalTemp)))
        {
            ok = false;
            break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_FIVE;
        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).d1);
        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).d1);
		return;
	}
	// 2) Каре - 4 одинаковых
	ok = true;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 4)
		{
	        DiceState.(_whom).Result.Type  = RESULT_FOUR;
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp));
			return;
		}
	}
	// 3) Фул - 3 + 2
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 3)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
	    ok = false;
	    for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate1)) continue;
			
			for (i = 1; i<=5; i++)
			{
		        sGlobalTemp = "d"+i;
		        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
		        {
		            iOk--;
				}
			}
		 	if (iOk >= 2)
			{
		        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp));
		        ok = true;
		        break;
			}
		}
	}
 	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_FULL;
		return;
	}

    // 4) Стрит Бол.стрит - 2,3,4,5,6 Мал.стрит - 1,2,3,4,5
	ok = true;
	for (i = 1; i<=4; i++)
	{
        sGlobalTemp = "d"+i;
        sTemp       = "d"+(i+1);
        if (sti(DiceState.(_whom).(sGlobalTemp)) != (sti(DiceState.(_whom).(sTemp)) - 1) )
        {
            ok = false;
            break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_STRAIGHT;
        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).d5);
        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).d5);
		return;
	}

	// 5) триада - 3 одинаковых
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 3)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_THREE;
        DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 6) две пары 2 + 2
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 2)
		{
	        DiceState.(_whom).Result.Rate2  = sti(DiceState.(_whom).(sTemp)); // младшая
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
	    ok = false;
	    for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate2)) continue;

			for (i = 1; i<=5; i++)
			{
		        sGlobalTemp = "d"+i;
		        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
		        {
		            iOk--;
				}
			}
		 	if (iOk >= 2)
			{
		        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp)); // старшая
		        ok = true;
		        break;
			}
		}
	}
 	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_TWO_PAIRS;
		return;
	}
	// 7) одна пара 2- одинаковых
	ok = false;
    for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
	        sGlobalTemp = "d"+i;
	        if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sGlobalTemp)))
	        {
	            iOk--;
			}
		}
	 	if (iOk >= 2)
		{
	        DiceState.(_whom).Result.Rate1  = sti(DiceState.(_whom).(sTemp));
	        ok = true;
	        break;
		}
	}
	if (ok)
	{
        DiceState.(_whom).Result.Type  = RESULT_PAIR;
        DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 8) ничего нет
	DiceState.(_whom).Result.Type  = RESULT_NOTHING;
    DiceState.(_whom).Result.Rate1 = 0;
	DiceState.(_whom).Result.Rate2 = 0;
}
// сортирова по возрастанию, нужно для визуализации и аглоритма вычисления комбинаций
void SortDiceOnHand(string _whom)
{
    int  j,k,w,m;
    string sTemp;
    /*
	Поиск наименьшего (простой выбор).

  При первом проходе находим наименьший элемент и ставим его на первое место,
потом наименьший из оставшихся...
	*/
	
	for (k = 1; k<=4; k++)
	{
        sGlobalTemp = "d"+k;
        w = sti(DiceState.(_whom).(sGlobalTemp));
		j = k;
		for (m = k+1; m<=5; m++)
		{
            sGlobalTemp = "d"+m;
			if (sti(DiceState.(_whom).(sGlobalTemp)) < w)
			{
			    j = m;
			    w = sti(DiceState.(_whom).(sGlobalTemp));
			}
		}
		sGlobalTemp = "d"+j;
		sTemp       = "d"+k;
		DiceState.(_whom).(sGlobalTemp) = DiceState.(_whom).(sTemp);
		DiceState.(_whom).(sTemp) = w;
	}
}
// сравнение результата
int GetResult()
{
	if (sti(DiceState.Hero.Result.Type) < sti(DiceState.Comp.Result.Type))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Type) > sti(DiceState.Comp.Result.Type))
	{
	    return -1;
	}
	if (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Rate1) < sti(DiceState.Comp.Result.Rate1))
	{
	    return -1;
	}
	if (sti(DiceState.Hero.Result.Rate2) > sti(DiceState.Comp.Result.Rate2))
	{
	    return 1;
	}
	if (sti(DiceState.Hero.Result.Rate2) < sti(DiceState.Comp.Result.Rate2))
	{
	    return -1;
	}
	return 0; // ничья
}


bool EndTurnGame()
{
    string sTemp;
    int   ok = 0;
    bool  ret = true;

	ok = GetResult();
	sTemp = XI_ConvertString("DicePhrase9_1") + GetTypeName(sti(DiceState.Comp.Result.Type)) + XI_ConvertString("DicePhrase9_2") + GetTypeName(sti(DiceState.Hero.Result.Type)) + ".";
    if (ok == 0)
    {
        sTemp += NewStr() + XI_ConvertString("DicePhrase10");
		ret = false;
    }
    if (ok == -1)
    {
        sTemp += NewStr() + XI_ConvertString("DicePhrase11");
        iHeroLose++;
    }
    if (ok == 1)
    {
        sTemp += NewStr() +  RandSwear() + XI_ConvertString("DicePhrase12");
        iHeroWin++;
    }
    EndGameCount(ok);
    ResultStr = sTemp;
    SetFormatedText("INFO_TEXT", sTemp);
    return ret;
}

void ContinueGame()
{
	if (CheckNextGame())
	{
		dir_i       = -dir_i_start;
	    dir_i_start = dir_i;
		NewGameBegin(false);
	}
	else
	{
        if (iRate*6 > iMoneyP)
    	{
    	    ResultStr = XI_ConvertString("DicePhrase13_1") + NewStr() + XI_ConvertString("DicePhrase13_2");
			SetFormatedText("INFO_TEXT",ResultStr);
    	    EndGameCount(-1);
    	    iHeroLose++;
    	}
		else//if (iRate*6 > iMoneyN)
	    {
	        ResultStr = XI_ConvertString("DicePhrase14_1") + NewStr() + XI_ConvertString("DicePhrase14_2");
	        SetFormatedText("INFO_TEXT",ResultStr);
	        EndGameCount(1);
	        iHeroWin++;
	    }
     	RedrawDeck(true, true);
		openExit = true;
	    bLockClick = true;
	}
}

void NewNextGame()
{
    RedrawDeck(true, false);
    openExit = true;
	bool wantToContinue = (CheckAttribute(pchar, "GenQuest.Dice.DontStop")) || (rand(10) < 10);
	if (CheckNextGame() && wantToContinue) // есть деньги на игру
    {
        ResultStr += NewStr() + XI_ConvertString("DicePhrase15");
		bLockClick = false;
		SetDiceTip("");
		SetDiceTip("restart");
	}
	else
	{
        ResultStr += NewStr() + XI_ConvertString("DicePhrase16");
		bLockClick = true;
	}
	SetFormatedText("INFO_TEXT",ResultStr);
}

string GetTypeName(int _type)
{
	string ret = XI_ConvertString("DiceNothing");
	
	switch (_type)
	{
	    case RESULT_FIVE:
	        ret = XI_ConvertString("Five");
	    break;
	    
	    case RESULT_FOUR:
	        ret = XI_ConvertString("Four");
	    break;
	    
	    case RESULT_FULL:
	        ret = XI_ConvertString("Full");
	    break;
	    
	    case RESULT_STRAIGHT:
	        ret = XI_ConvertString("Straight");
	    break;

	    case RESULT_THREE:
	        ret = XI_ConvertString("Three");
	    break;
	    
	    case RESULT_TWO_PAIRS:
	        ret = XI_ConvertString("Two_pairs");
	    break;
	    
	    case RESULT_PAIR:
	        ret = XI_ConvertString("Pair");
	    break;
	}
	return ret;
}

void SetDiceForTableRand()
{
	int i;
	// belamour читерство Джокера -->
	if(dir_i == 1 && IsCharacterEquippedArtefact(pchar, "totem_13") && 11 + GetCharacterSkill(pchar, SKILL_FORTUNE)/2 > rand(100))
	{
		int iR = rand(5);
		int iV = rand(4);
		for (i = 1; i<=5; i++)
		{
			sGlobalTemp = "d"+i;
			if (sti(DiceState.Desk.(sGlobalTemp).Mix) == true)
			{
				if(iV == 2) DiceState.Desk.(sGlobalTemp) = iR+1; // покер
				else
				{
					if(i == iV + 1) DiceState.Desk.(sGlobalTemp) = rand(5)+1;
					else DiceState.Desk.(sGlobalTemp) = iR+1; // каре или покер(17%) 
				} 
			}
		}
	}
	// <-- просто везение, капитан )))
	else
	{
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d"+i;
        if (sti(DiceState.Desk.(sGlobalTemp).Mix) == true)
        {
            DiceState.Desk.(sGlobalTemp) = (rand(5)+1);
		}
	}
}
}
/////////////////////////// AI //////////////////////////////////
void CompTurn()
{
    int i, d, j;
    bool ok, ok2, ok3, b;
    
	// если комп ходит последним и у него уже больше, то нафиг ему бросать???
	ok = true;
	if (GetResult() == -1 && dir_i_start == 1 && bStartGame == 3) // пропуск хода
	{
        ok = false;
	}
	if (ok)
	{
    	if (sti(DiceState.Comp.Result.Type) == RESULT_NOTHING && sti(DiceState.Hero.Result.Type) >= RESULT_FOUR)
    	{
            //перебросим всегда первую фишку (это 100% 1)
            SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase17"));
    		// for test
    		ClickCompDice(1);
    		move_i = 0;
            PlaySound("interface\dice_mix.wav");
            PostEvent("My_eventMoveImg", 500);
            return;
    	}

    	// две пары бросаем на фул (один кубик)
        ok3 = (sti(DiceState.Comp.Result.Type) == RESULT_TWO_PAIRS) && (sti(DiceState.Hero.Result.Type) >= RESULT_THREE);
        ok  = (sti(DiceState.Comp.Result.Type) == RESULT_TWO_PAIRS) && (sti(DiceState.Hero.Result.Type) == RESULT_FULL) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate2));
        ok3 = ok3 || ok;
        // пара бросаем триаду, каре или две пары, а может фулл??
        ok = (sti(DiceState.Comp.Result.Type) == RESULT_PAIR) || (sti(DiceState.Comp.Result.Type) == RESULT_THREE);
        // ok = ok && (sti(DiceState.Hero.Result.Type) >= 3); // типа стрит фулом/каре не перекрыть - теперь устарело
        // каре, но у ГГ больше
        ok2 = (sti(DiceState.Hero.Result.Type) == RESULT_FOUR) && (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1));
        b   = (sti(DiceState.Hero.Result.Type) == RESULT_FIVE) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate1));
        ok2 = ok2 || b;
        ok2 = (sti(DiceState.Comp.Result.Type) == RESULT_FOUR) && ok2;
        if (ok || ok2 || ok3)
        {
            ok = false;
            SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase18"));
            for (i = 1; i<=6; i++)
    		{
    	        sGlobalTemp = "d"+i;
    	        if (sti(DiceState.Comp.Result.(sGlobalTemp)) == 1)
    	        {
                    d = i; // че за фишка
                    for (j = 1; j<=5; j++)
            		{
            	        sGlobalTemp = "d"+j;
            	        if (sti(DiceState.Comp.(sGlobalTemp).Mix) == true) continue;
            	        if (sti(DiceState.Comp.(sGlobalTemp)) == d)
            	        {
                            ok = ClickCompDice(j) || ok;
                            break;
            			}
            		}
    			}
    		}

    		if (ok)
    		{
                move_i = 0;
    	        PlaySound("interface\dice_mix.wav");
    	        PostEvent("My_eventMoveImg", 500);
    	        return;
    		}
        }

        // супер жухло!!!!! -->
        if (sti(DiceState.Comp.Result.Type) > sti(DiceState.Hero.Result.Type) && GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(12) && rand(4) > 1)
        {
			//navy --> счетчик жульничеств
			if (!CheckAttribute(npchar, "Quest.DiceCheats")) npchar.Quest.DiceCheats = 0;
			npchar.Quest.DiceCheats = sti(npchar.Quest.DiceCheats) + 1;
			//navy <--
            SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase18"));
            ok = false;
            if (sti(DiceState.Hero.Result.Type) == 1)
            {
                d = sti(DiceState.Hero.Result.Rate1) + 1;
            }
            else
            {
                d = rand(5) + 1;
            }
            if (d > 6) d = 6;

    		for (i = 1; i<=5; i++)
    		{
    	        sGlobalTemp = "d"+i;
    	        if (sti(DiceState.Comp.(sGlobalTemp)) != d)
    	        {
                    ok = ClickCompDice(i) || ok;
    	            DiceState.Desk.(sGlobalTemp) = d;
    			}
    		}
    		if (ok)
    		{
        		move_i = 0;
        		bSetRandDice = false;
                PlaySound("interface\dice_mix.wav");
                PostEvent("My_eventMoveImg", 500);
                return;
            }
        }
        // жухло!!!!! <--
    }
	// решаем не перебрасывать
	SetFormatedText("INFO_TEXT",XI_ConvertString("DicePhrase19"));
	PostEvent("My_eCheckGame", 800);
}

bool ClickCompDice(int d)
{
    sGlobalTemp = "d"+d;
    
	if (iMoneyN >= iRate && sti(DiceState.Comp.(sGlobalTemp).Mix) == false)
	{
		SetNodeUsing("CompDice" + d, false);
		DiceState.Comp.(sGlobalTemp).Mix = true;
		DiceState.Desk.(sGlobalTemp).Mix = true;
  		PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
	    iChest += iRate;
	    PlaySound("interface\took_item.wav");
	    ShowMoney();
	    return true;
    }
    return false;
}
// заполнить колвом атрибуты фишек
void RecalcAIDice(string _whom)
{
    int    i;
	string sTemp;
	bool   ok;
	
	for (i = 1; i<=6; i++)
	{
        sGlobalTemp = "d"+i;
        DiceState.(_whom).Result.(sGlobalTemp) = 0;
	}
	
	for (i = 1; i<=5; i++)
	{
        sGlobalTemp = "d" + i;
        sTemp       = "d" + sti(DiceState.(_whom).(sGlobalTemp));
        DiceState.(_whom).Result.(sTemp) = sti(DiceState.(_whom).Result.(sTemp)) + 1;
	}
}

/*
restart - новый кон
action - перебросить кубик, сделать бросок, передать ход, подсчитать очки
*/
void SetDiceTip(string tag)
{
	int i;
	string sDice;
	switch(tag)
	{
		case "":	// убираем все подсказки
			for(i = 1; i <= 5; i++)
			{
				SetPictureBlind("HeroDice" + i, false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
				bTip[i-1] = false;
			}
			SetPictureBlind("DiceCup", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetNodeUsing("TIP_RESTART", false);
			SetNodeUsing("TIP_TURN", false);
			SetNodeUsing("TIP_ROLL", false);
			SetNodeUsing("TIP_REROLL", false);
			SetNodeUsing("TIP_SHOW", false);
		break;
		case "restart":
			if(!bLockClick && openExit)	// можно начать новую игру - колода
			{
				SetPictureBlind("DiceCup", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
				SetNodeUsing("TIP_RESTART", true);
			}
		break;
		case "action":
			if(!bLockClick && dir_i == 1)
			{
				if(bStartGame >= 2 && bStartGame <= 3 && iMoneyP >= iRate)	// хватает денег на переброс
				{
					for(i = 1; i <= 5; i++)
					{
						sDice = "d" + i;
						if(DiceState.Hero.(sDice).Mix == false)	// есть ли на столе
						{
							SetPictureBlind("HeroDice" + i, true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
							bTip[i-1] = true;
						}
						else
							bTip[i-1] = false;
					}
				}
				if(CheckCupForDice())	// в стакане что-то есть
				{
					SetPictureBlind("DiceCup", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					SetNodeUsing("TIP_ROLL", true);
					SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
					SetNodeUsing("TIP_TURN", false);
					SetNodeUsing("TIP_SHOW", false);
				}
				else
				{
					if(dir_i_start == 1 && bStartGame == 2)	// передача хода
					{
						SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
						SetNodeUsing("TIP_TURN", true);
					}
					if(dir_i_start == -1 && bStartGame == 3)	// подсчёт очков
					{
						SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
						SetNodeUsing("TIP_SHOW", true);
					}
				}
			}
		break;
	}
}

void MouseEffect()
{
	string sNode = GetEventData();
	int isEffect = GetEventData();
	int x = 0;
	int y = 840 + scy;
	int iDice = -1;
	switch(sNode)
	{
		case "B_HeroDice1":		iDice = 0;	x = 730;	break;
		case "B_HeroDice2":		iDice = 1;	x = 810;	break;
		case "B_HeroDice3":		iDice = 2;	x = 890;	break;
		case "B_HeroDice4":		iDice = 3;	x = 970;	break;
		case "B_HeroDice5":		iDice = 4;	x = 1050;	break;
	}
	if(iDice >= 0 && iDice <= 4)
	{
		bEffect[iDice] = (isEffect != 0);
		if(bEffect[0] || bEffect[1] || bEffect[2] || bEffect[3] || bEffect[4])
			SetNodeUsing("TIP_REROLL", bTip[iDice]);
		else
			SetNodeUsing("TIP_REROLL", false);
	}
	else
		SetNodeUsing("TIP_REROLL", false);
	if(isEffect != 0)
		SetNodePosition("TIP_REROLL", x, y, x + scx + 20, y + 50);
}