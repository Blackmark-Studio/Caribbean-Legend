// boal 13.05.05
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start, x_rand, y_rand, r_delta;
bool openExit;
bool cardMove;
int  money_i, moneyOp_i;
string money_s;

ref npchar;

int cardsPack[36], cardsP[36], cardsN[36];
int howCard;

int howPchar, howNpchar;
int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;

int iTurnGame;
int iHeroLose, iHeroWin;
int NArand = 3+rand(2); // belamour ночной приключенец

void InitInterface(string iniName)
{
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eOpenCards","OpenCards",0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("HideInfoWindow","HideInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	/*
	hearts_A,diamonds_A,clubs_A,spades_A  - 124x184
	blank - 124x184
	pack -  186x202
	gold, silver   - 100x100
	A - ace
	J - Jack
	Q - Queen
	K - King
	10..6 - other
	
	screen: -40..680 x -30..510  (720x540)
	*/
	r_delta = makeint(Bring2Range(20.0, 5.0, 5.0, 20.0, GetRDeltaTime() * 1.0));
    sgxy = 120;
    ssxy = 120;
    
    scx = 180;
    scy = 300;    
    // spx = 172;
    // spy = 188;
	
	// spx = 240;
    // spy = 330;
    
    openExit = false;  // можно ли прервать игру
	cardMove = false; // игрок перемещает карту
    
    pchar = GetMainCharacter();
    
    iRate  = sti(pchar.GenQuest.Cards.iRate); // ставки золотых
    
    //pchar.GenQuest.Cards.npcharIdx = GetCharacterIndex("Filosof"); // test
    
    npchar = GetCharacter(sti(pchar.GenQuest.Cards.npcharIdx));
    
	iMoneyP = sti(pchar.Money); // mitrokosta теперь смотрим на реальные деньги только в начале и в конце
	iMoneyN = sti(npchar.Money);
    
	// mitrokosta фикс опыта за некратные ставки -->
	if (iRate >= 100) {
            money_s = "silver";
            iExpRate = 1;
	}
	if (iRate >= 500) {
            money_s = "gold";
            iExpRate = 2;
	}
	if (iRate >= 1000) {
            money_s = "silver";
            SetNewPicture("MAIN_BACK", "interfaces\le\card_sukno.tga");
            iExpRate = 3;
	}
	if (iRate >= 5000) {
            money_s = "gold";
            SetNewPicture("MAIN_BACK", "interfaces\le\card_sukno.tga");
            iExpRate = 6;
	}
	if (iRate >= 10000) { // Jason Дороже золота
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
	
    XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Pack", 100);
	SetNewGroupPicture("Pack", "CARDS", "pack");
	SetNodePosition("Pack", 310, 390, 550, 710);
	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Blank", 100);
	SetNewGroupPicture("Blank", "CARDS", "blank");
	SetNodePosition("Blank", 310, 390, 310+scx, 390+scy);
	SetNodeUsing("Blank", false);
	SetNewPicture("ICON_1", "interfaces\le\portraits\512\face_" + npchar.faceId+ ".tga");
    SetNewPicture("ICON_2", "interfaces\le\portraits\512\face_" + pchar.faceId+ ".tga");
    SetCardTip("");
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
    CreateString(true,"Beta_P", "", "INTERFACE_NORMAL",COLOR_NORMAL, 960, 700, SCRIPT_ALIGN_CENTER,2.5);
    CreateString(true,"Beta_Next", "", "INTERFACE_NORMAL",COLOR_NORMAL, 580, 520, SCRIPT_ALIGN_LEFT,2.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_NORMAL",COLOR_NORMAL, 1560, 350, SCRIPT_ALIGN_CENTER,2.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_NORMAL",COLOR_NORMAL, 1560, 710, SCRIPT_ALIGN_CENTER,1.8);
    // новая игра
    NewGameBegin();
    iTurnGame = 1; // игра первая
    iHeroLose = 0;
    iHeroWin  = 0;
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
    	DelEventHandler("My_eOpenCards","OpenCards");
		DelEventHandler("ShowInfoWindow","ShowInfoWindow");
		DelEventHandler("HideInfoWindow","HideInfoWindow");
		DelEventHandler("MouseRClickUp","HideInfoWindow");

        if (CheckAttribute(pchar,"GenQuest.Cards.SitType") && sti(pchar.GenQuest.Cards.SitType) == true)
    	{
			if(npchar.id == "AffairOfHonor_WolvesAndSheeps_Man")
			{
				DoQuestFunctionDelay("AffairOfHonor_AfterCards", 0.6);
			}
			else
			{
				DoQuestCheckDelay("exit_sit", 0.6);
			}
    	}
        interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

		// belamour ночной приключенец
		if(CheckAttribute(pchar, "questTemp.NA.Cards")) 
		{
			DoQuestCheckDelay("NightAdventure_GameRes", 0.6);
			pchar.GenQuest.NightAdventure_money = abs(iMoneyP - sti(pchar.Money));
		}
		
		bool isWin = iMoneyP > sti(pchar.Money) && iMoneyN < iRate*3;
		
		AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
		AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));
    	Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
    	Statistic_AddValue(Pchar, "GameCards_WinMoney", iMoneyP);
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
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
    	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
		DeleteAttribute(pchar,"systeminfo.InGameNotifications");
    	Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);
		Achievment_SetStat(26, iHeroLose);
    	
    	bQuestCheckProcessFreeze = true;
    	if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, iTurnGame*15);
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
    	EndCancelInterface(true);
		// Jason Дороже золота
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game")) // идёт квестовая игра
		{
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G1")) DoQuestCheckDelay("GoldenGirl_Game1Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G2")) DoQuestCheckDelay("GoldenGirl_Game2Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G3")) DoQuestCheckDelay("GoldenGirl_Game3Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.G4")) DoQuestCheckDelay("GoldenGirl_Game4Res", 1.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.IslaMona")) DoQuestCheckDelay("IslaMona_CardsGameRes", 1.0); // Jason Исла Мона
		}
		if (isWin && CheckAttribute(pchar, "GenQuest.Cards.OnWin")) {
			DoQuestFunctionDelay(pchar.GenQuest.Cards.OnWin, 1.0);
		}
		if (!isWin && CheckAttribute(pchar, "GenQuest.Cards.OnLoss")) {
			DoQuestFunctionDelay(pchar.GenQuest.Cards.OnLoss, 1.0);
		}
		DeleteAttribute(pchar, "GenQuest.Cards.OnWin");
		DeleteAttribute(pchar, "GenQuest.Cards.OnLoss");
		DeleteAttribute(pchar, "GenQuest.Cards.DontStop");
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
	sHeader = XI_ConvertString("titleCards");
	sText1 = XI_ConvertString("RulesCards1");
	sText2 = XI_ConvertString("RulesCards2");
	sText3 = XI_ConvertString("RulesCards3");
	
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

	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   // ещё одна игра
                    if (bStartGame != 100)
                    {
                        dir_i = -dir_i_start;
                        dir_i_start = dir_i;
                        iTurnGame++;
                        NewGameBegin();
                        openExit = false;
                    }
                    else
                    {
                        PlaySound("interface\knock.wav");
                    }
                }
                else
                {   // ГГ берёт карты
                    if (bStartGame <2) break; // ещё сдают
                    if (bStartGame == 100) break; // открываемся
                    
                    if (dir_i == 1 && (iMoneyP - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase1"));
                        break;
                    }
                    if (dir_i == -1 && (iMoneyN - iRate) < 0)
                    {
                        PlaySound("interface\knock.wav");
                        SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase2"));
                        break;
                    }
                    
                    if (dir_i == 1)
                    {
						if (cardMove) { // mitrokosta фикс множественного взятия
							break;
						} else {
							cardMove = true; // начинаем перемещение
						}
                        move_i = 0;
                        PlaySound("interface\took_item.wav");
						SetCardTip("");
                        PostEvent("My_eventMoveImg", 100);
                        
                        PutNextCoin();
                        money_i++;

                        iMoneyP = iMoneyP - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsP[howPchar] = cardsPack[howCard];
                        howPchar++;
                    }
                    /*
                    else
                    {
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                    }  */
                    ShowMoney();
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) // только передача хода или открываемся
                {
					SetCardTip("");
                    dir_i = -1; // смена хода
                    SetNextTip();
                    if (dir_i_start == -1)// комп начинал игру первый
                    {
                        SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase3"));
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    {// комп должен себе набрать
                        SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase4"));
                        
                        move_i = 0;
                        PlaySound("interface\took_item.wav");
                        PostEvent("My_eventMoveImg", 500);
                        
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                        ShowMoney();
                    }
                }
                else
                {
                    PlaySound("interface\knock.wav");
                }
    		}
    	break;
    	
    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                //PlaySound("interface\knock.wav");
    		}
    	break;
	}
}

void MoveImg()
{
	int k = scx;
	int n;
	if(dir_i > 0)
		n = howPchar;
	else
		n = howNpchar;
    if (n > 6)
        k = scx/2;
	float t;
    int x1 = 360;
    int y1 = 390;
    int x2 = 950 - n * k / 2 + (n - 1) * k;	// карта летит к следующему слоту
    int y2 = 390 + dir_i * 345;
    int i, x, y;

    if (move_i == 0)
    {
		SetNodeUsing("Blank", true);
		// случайная промежуточная точка
        x_rand = x1 + (x2 - x1) / 2 - 200 + rand(400);
        y_rand = y1 + dir_i * 120 - 150 + rand(300);
    }

    t = move_i / 50.0;
    t = t * t * (3.0 - 2.0 * t);	// ускорение в начале, замедление в конце
    x = makeint((1.0 - t)*(1.0 - t)*x1 + 2.0*(1.0 - t)*t*x_rand + t*t*x2);
    y = makeint((1.0 - t)*(1.0 - t)*y1 + 2.0*(1.0 - t)*t*y_rand + t*t*y2);
	float scale = 1.0 + 0.1 * 4.0 * t * (1.0 - t);	// плавное увеличение карты к середине, уменьшение после середины
	SetNodePosition("Blank", x, y, x + makeint(scx * scale), y + makeint(scy * scale));
	
	string sCard;
	if(t > 0.5)	// карты в руке плавно сдвигаются влево
	{
		if(dir_i > 0)
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = 950 - (n - 1) * k / 2 + i * k;
				x2 = 950 - n * k / 2 + i * k;
				x = makeint(x1 + (x2 - x1) * (t - 0.5) * 2.0);
				sCard = "c"+cardsP[i];
				CreateImage("PCard"+i, "CARDS", NullCharacter.Cards.(sCard).pic, x, 740, x + scx, 740 + scy);
			}
		}
		else
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = 950 - (n - 1) * k / 2 + i * k;
				x2 = 950 - n * k / 2 + i * k;
				x = makeint(x1 + (x2 - x1) * (t - 0.5) * 2.0);
				CreateImage("PCard" + (18 + i), "CARDS", "blank", x, 50, x + scx, 50 + scy);
			}
		}
	}

    move_i++;
    if (move_i < 50)
    {
        PostEvent("My_eventMoveImg", r_delta);
    }
    else
    {
		cardMove = false; // закончили перемещение
		SetNodeUsing("Blank", false);
        PlaySound("interface\button3.wav");
        // перерисуем все карты на руках
        RedrawCards();
        
        // начало игры, по карте каждому -->
        if (bStartGame < 2)
        {
            dir_i = -dir_i; // смена хода
            bStartGame++;
            if (bStartGame == 1)  PostEvent("My_eStartGame", 500);
        }
        // начало игры, по карте каждому <--
        SetNextTip();
        BetaInfo();
        CheckGame();
		if(bStartGame >= 2 && dir_i == 1)
			SetCardTip("action");
    }
}

void PutNextCoin()
{
    CreateImage("Money_"+money_i,"CARDS",money_s, 800+money_i*3, 480-money_i*3, 800+money_i*3 + smxy, 480-money_i*3 + smxy);
}
void PutNextCoinOp()
{
    CreateImage("Money_"+(18+moneyOp_i),"CARDS",money_s, 990+moneyOp_i*3, 480-moneyOp_i*3, 990+moneyOp_i*3 + smxy, 480-moneyOp_i*3 + smxy);
}

void PackShake()
{
    // тасуем карты
    int  i;
    bool ok;
    int  nextCard;
    
    howCard = 0;
    while (howCard <36)
    {
        ok = false;
        while (!ok)
        {
            ok = true;
            nextCard = rand(35)+1;
            for (i=0; i<howCard; i++)
        	{
                if (nextCard == cardsPack[i])
                {
                    ok = false;
                    break;
                }
        	}
        	if (ok)
        	{
                cardsPack[howCard] = nextCard;
                //log_info(""+nextCard);
                howCard++;
                
        	}
    	}
    }
    /*howCard = 36;
    for (i=0; i<howCard; i++)
	{
        cardsPack[i] = i-20;
	}*/
}
void RedrawCards()
{
    int i;
    string sTemp;
    int k;
    k = scx;
    if (howPchar > 6)
    {
        k = scx/2;
    }
    for (i=0; i<howPchar; i++)
	{
        sTemp = "c"+cardsP[i];
        CreateImage("PCard"+i,"CARDS", NullCharacter.Cards.(sTemp).pic, 950 - howPchar*k/2 + i*k , 740, 950 - howPchar*k/2 + i*k + scx, 740 + scy);
	}
	k = scx;
	if (howNpchar > 6)
    {
        k = scx/2;
    }
	for (i=0; i<howNpchar; i++)
	{
        sTemp = "c"+cardsN[i];
        sTemp = NullCharacter.Cards.(sTemp).pic;
        if (!openExit)
        {
            sTemp = "blank";
        }
        CreateImage("PCard"+(18+i),"CARDS", sTemp, 950 - howNpchar*k/2 + i*k , 50, 950 - howNpchar*k/2 + i*k + scx, 50 + scy);
	}
}
void RedrawDeck()
{
    // монетки с запасом
    int i;
    for (i=35; i>=0; i--)
	{
        CreateImage("Money_"+i,"","", 0, 0, 0, 0);
        CreateImage("PCard"+i, "", "", 0, 0, 0, 0);
	}
	money_i = 0; // индекс монетки
    moneyOp_i = 0;
    iChest = 0; // на кону
    
    ShowMoney();
    
    // тасуем карты
    PackShake();
    howPchar  = 0; // карты на руках
    howNpchar = 0;
    SetNextTip();
    BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
		// belamour читерство Джокера -->
		if(IsCharacterEquippedArtefact(pchar, "totem_13") && CountCardsP() > 9 && 11 + GetCharacterSkill(pchar, SKILL_FORTUNE)/2 > rand(100))
		{
			for(int p = 1; p<=howCard; p++)
			{
				string sPNum = "c"+cardsPack[p];
				int iPValue = sti(NullCharacter.Cards.(sPNum).count);
				if((CountCardsP() + iPValue) != 21) continue;
				if(iPValue<2) break;
				cardsPack[howCard-1] = cardsPack[p];
			}
		}
		// <-- под рукой всегда нужная карта					
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT",XI_ConvertString("CardsPhrase5_1")+NewStr()+XI_ConvertString("CardsPhrase5_2"));
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(XI_ConvertString("CardsPhrase6_1"), XI_ConvertString("CardsPhrase6_2"), RandSwear() + XI_ConvertString("CardsPhrase6_3")));
        }
    }
    else
    {
		// belamour подменим карту -->
		if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && 
		   pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel" && CountCardsN() > 9)
		{
			for(int i = 1; i<=howCard; i++)
			{
				string sNum = "c"+cardsPack[i];
				int iValue = sti(NullCharacter.Cards.(sNum).count);
				if((CountCardsN() + iValue) != 21) continue;
				if(iValue<2) break;
				cardsPack[howCard-1] = cardsPack[i];
			}
		}
		// <-- ночной приключенец
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT",XI_ConvertString("CardsPhrase7_1")+NewStr()+XI_ConvertString("CardsPhrase7_2"));
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(XI_ConvertString("CardsPhrase8_1"), XI_ConvertString("CardsPhrase8_2"), XI_ConvertString("CardsPhrase8_3")));
        }
    }
}
int CountCardsP()
{
    int ret = 0;
    int i;
    string sTemp;
    
    for (i = 0; i < howPchar; i++)
    {
        sTemp = "c"+cardsP[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}

int CountCardsN()
{
    int ret = 0;
    int i;
    string sTemp;

    for (i = 0; i < howNpchar; i++)
    {
        sTemp = "c"+cardsN[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}
void BetaInfo()
{
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_P       = "Beta_P " + CountCardsP();
        GameInterface.strings.Beta_N       = "Beta_N " + CountCardsN();
        GameInterface.strings.Beta_Next    = "Beta_Next " + NextCardPack();
        GameInterface.strings.Beta_MoneyN  = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameCards_Win", 0)+iHeroWin) + " Lose " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0)+iHeroLose);
    }
	else
	{
		GameInterface.strings.Beta_P       = CountCardsP();
        GameInterface.strings.Beta_WinLose = XI_ConvertString("Win") + iHeroWin + " / " + XI_ConvertString("Lose") + iHeroLose;
	}
}
int NextCardPack()
{
    string sTemp;
    int ret;
    
    sTemp = "c"+cardsPack[howCard-1];
    ret = sti(NullCharacter.Cards.(sTemp).count);
    
    return ret;
}
// сдать карту
void StartGame()
{
    move_i = 0;

    PlaySound("interface\took_item.wav");
	SetCardTip("");
    PostEvent("My_eventMoveImg", 100);

    if (dir_i == 1)
    {
        PutNextCoin();
        money_i++;

        iMoneyP = iMoneyP - iRate;

        howCard--;
        cardsP[howPchar] = cardsPack[howCard];
        howPchar++;
    }
    else
    {
        PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
        howCard--;
        cardsN[howNpchar] = cardsPack[howCard];
        howNpchar++;
    }
    iChest += iRate;
    ShowMoney();
}

void ShowMoney()
{
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

bool CheckGame()
{
    string sTemp;
    int   ok = 0;
    bool  ok1;
    bool  ret = false;
    
    if (CountCardsP() > 21)
    {
        ok = -1; // выиграл комп
        sTemp = XI_ConvertString("CardsPhrase9");
        iHeroLose++;
    }
    if (CountCardsN() > 21)
    {
        ok = 1; // выиграл ГГ
        sTemp = RandSwear() + XI_ConvertString("CardsPhrase10");
        iHeroWin++;
    }
    if (ok != 0)
    {
        EndGameCount(ok);
        if (ok == 1) RedrawCards(); // покажем перебор
        
		// Jason Дороже золота, belamour:  Ночной приключенец 
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game") || CheckAttribute(pchar, "questTemp.NA.Cards")) // идёт квестовая игра
		{
			if (ok == -1) // выиграл комп
			{
				if(CheckAttribute(pchar, "questTemp.NA.Cards")) // ночной приключенец
				{
					if(iTurnGame > NArand) // играем не больше 5 партий
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase11");
						// ГГ проиграл по "сумме встреч"
						if(iMoneyP - sti(pchar.Money) < 0) pchar.questTemp.NA.Cards.Fail = true;  
						else pchar.questTemp.NA.Cards.Win = true;
					}
					else 
					{
						if (iMoneyP > iRate)
						{
							sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase12_1"),XI_ConvertString("CardsPhrase12_2"));
						}
						else
						{
							bStartGame = 100;//признак запрета новой игры
							sTemp += NewStr() + XI_ConvertString("CardsPhrase13");
							pchar.questTemp.NA.Cards.Fail = true; // ГГ проиграл
						}
					}
				}
				else // Дороже золота
				{
					if (iMoneyP > iRate)
					{
						sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase14_1"),XI_ConvertString("CardsPhrase14_2"));
					}
					else
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase15");
						pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
					}
				}
			}
			else // выиграл ГГ
			{
				if(CheckAttribute(pchar, "questTemp.NA.Cards")) // ночной приключенец
				{
					if(iTurnGame > NArand) // играем не больше 5 партий
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase16");
						// ГГ проиграл по "сумме встреч"
						if(iMoneyP - sti(pchar.Money) < 0) pchar.questTemp.NA.Cards.Fail = true;  
						else pchar.questTemp.NA.Cards.Win = true;
					}
					else
					{
						if (iMoneyN > iRate) // у НПС есть деньги на игру
						{
							if (iMoneyP > iRate)
							{
								sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase17_1"),XI_ConvertString("CardsPhrase17_2"));
							}
							else
							{
								bStartGame = 100;//признак запрета новой игры
								sTemp += NewStr() + XI_ConvertString("CardsPhrase18");
								pchar.questTemp.NA.Cards.Fail = true; // ГГ проиграл
							}
						}
						else
						{
							bStartGame = 100;//признак запрета новой игры
							sTemp += NewStr() + XI_ConvertString("CardsPhrase19");
							pchar.questTemp.NA.Cards.Win = true;
						}
					}
				}
				else // Дороже золота
				{
					if (iMoneyN > iRate) // есть деньги на игру
					{
						if (iMoneyP > iRate)
						{
							sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase20_1"),XI_ConvertString("CardsPhrase20_2"));
						}
						else
						{
							bStartGame = 100;//признак запрета новой игры
							sTemp += NewStr() + XI_ConvertString("CardsPhrase21");
							pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
						}
					}
					else
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase22");
						pchar.questTemp.GoldenGirl.Game.Win = "true"; // ГГ выиграл
					}	
				}
			}
		}
		else
		{
			bool wantToContinue = (CheckAttribute(pchar, "GenQuest.Cards.DontStop")) || (rand(10) < 10);
			if (CheckNextGame() && wantToContinue) // есть деньги на игру
			{
				sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase23_1"), XI_ConvertString("CardsPhrase23_2"));
			}
			else
			{
				bStartGame = 100;//признах запрета новой игры
				sTemp += NewStr() + XI_ConvertString("CardsPhrase24");
			}
		}
        SetFormatedText("INFO_TEXT", sTemp);
        ret = true;
		SetCardTip("");
		SetCardTip("restart");
    }
    else
    {
        ok1 = (CountCardsN() > 16) && (CountCardsN() <22);
        // жухло!!!!! -->
        if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game") && GetCharacterSkillToOld(pchar, SKILL_FORTUNE) + makeint(isEquippedArtefactUse(pchar, "totem_13", 0.0, 2.0)) < rand(12)) // Jason Дороже золота
        {
            if (ok1 && (CountCardsN() + NextCardPack()) <= 21)
            {
                ok1 = false;
            }
            if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) - makeint(isEquippedArtefactUse(pchar, "totem_13", 0.0, 2.0)) < rand(10) && CountCardsN() < 17 && (CountCardsN() + NextCardPack()) > 21)
            {
                ok1 = true;
            }
        }
        // жухло!!!!! <--
		// belamour это не жухло, вот ЭТО жухло -->
		if(ok1 && CheckAttribute(pchar, "GenQuest.NightAdventureVar") && 
		   pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel" )
        {
            ok1 = (CountCardsN() > 19);
        }
        // <-- ночной приключенец
        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1)// комп ходит последним
            {
                SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase25"));
                bStartGame = 100;
				SetCardTip("");
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1)// комп начинает
            {
                dir_i = 1;
                SetFormatedText("INFO_TEXT", XI_ConvertString("CardsPhrase26"));
                ret = true;
            }
        }
        else
        {
            if (dir_i == -1 && bStartGame >= 2) // комп играет сам
            {
				cardMove = true; // начинаем перемещение
                move_i = 0;
                PlaySound("interface\took_item.wav");
				SetCardTip("");
                PostEvent("My_eventMoveImg", 500);

                PutNextCoinOp();
                moneyOp_i++;
                iMoneyN = iMoneyN - iRate;
                iChest += iRate;
                howCard--;
                cardsN[howNpchar] = cardsPack[howCard];
                howNpchar++;
                ShowMoney();
                
                ret = true;
            }
        }
    }
    return ret;
}

void NewGameBegin()
{
	SetCardTip("");
    RedrawDeck(); // новая игра
    bStartGame = 0;
    SetFormatedText("INFO_TEXT",XI_ConvertString("CardsPhrase28_1")+NewStr()+XI_ConvertString("CardsPhrase28_2"));
    PostEvent("My_eStartGame", 1000);
}

void EndGameCount(int who)
{
    openExit = true;
    if (who == 1) // ГГ
    {
		iMoneyP += iChest;
    }
    else
    {
		iMoneyN += iChest;
    }
}

void OpenCards();
{
	int iRes = 0; // Jason Дороже золота
    string sTemp;
    if (CountCardsP() > makefloat(CountCardsN() + 0.1*dir_i_start)) // преимущество тому, кто сдает (те ходит последним)
    {
        EndGameCount(1);
        sTemp = RandSwear() + XI_ConvertString("CardsPhrase29_1") + CountCardsP() + XI_ConvertString("CardsPhrase29_2") + CountCardsN()+"." ;
        iHeroWin++;
		iRes = 1; // Jason Дороже золота выиграл ГГ
    }
    else
    {
        EndGameCount(-1);
        sTemp = XI_ConvertString("CardsPhrase30_1") + CountCardsN() + XI_ConvertString("CardsPhrase30_2") + CountCardsP()+ XI_ConvertString("CardsPhrase30_3");
        iHeroLose++;
		iRes = -1; // Jason Дороже золота выиграл комп
    }
	// Jason Дороже золота, belamour ночной приключенец 
	if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game") || CheckAttribute(pchar, "questTemp.NA.Cards")) // идёт квестовая игра
	{
		if (iRes == -1) // выиграл комп
		{
			if(CheckAttribute(pchar, "questTemp.NA.Cards")) // ночной приключенец
			{
				if(iTurnGame > NArand) // играем не больше 5 партий
				{
					bStartGame = 100;//признак запрета новой игры
					sTemp += NewStr() + XI_ConvertString("CardsPhrase31");
					// ГГ проиграл по "сумме встреч"
					if(iMoneyP - sti(pchar.Money) < 0) pchar.questTemp.NA.Cards.Fail = true;  
					else pchar.questTemp.NA.Cards.Win = true;
				}
				else 
				{
					if (iMoneyP > iRate)
					{
						sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase32_1"),XI_ConvertString("CardsPhrase32_2"));
						bStartGame = 2;
					}
					else
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase33");
						pchar.questTemp.NA.Cards.Fail = true; // ГГ проиграл
					}
				}
			}
			else // дороже золота
			{
				if (iMoneyP > iRate)
				{
					sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase34_1"),XI_ConvertString("CardsPhrase34_2"));
					bStartGame = 2;
				}
				else
				{
					bStartGame = 100;//признак запрета новой игры
					sTemp += NewStr() + XI_ConvertString("CardsPhrase35");
					pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
				}
			}
		}
		else
		{
			if(CheckAttribute(pchar, "questTemp.NA.Cards")) // ночной приключенец
			{
				if(iTurnGame > NArand) // играем не больше 5 партий
				{
					bStartGame = 100;//признак запрета новой игры
					sTemp += NewStr() + XI_ConvertString("CardsPhrase36");
					// ГГ проиграл по "сумме встреч"
					if(iMoneyP - sti(pchar.Money) < 0) pchar.questTemp.NA.Cards.Fail = true;  
					else pchar.questTemp.NA.Cards.Win = true;
				}
				else 
				{
					if(iMoneyN > iRate)
					{
						if (iMoneyP > iRate)
						{
							sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase37_1"),XI_ConvertString("CardsPhrase37_2"));
							bStartGame = 2;
						}
						else
						{
							bStartGame = 100;//признак запрета новой игры
							sTemp += NewStr() + XI_ConvertString("CardsPhrase38");
							pchar.questTemp.NA.Cards.Fail = true; // ГГ проиграл
						}
					}
					else
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase39");
						pchar.questTemp.NA.Cards.Win = true; // ГГ выиграл
					}
				}
			}
			else // дороже золота
			{
				if (iMoneyN > iRate) // есть деньги на игру
				{
					if (iMoneyP > iRate)
					{
						sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase40_1"),XI_ConvertString("CardsPhrase40_2"));
						bStartGame = 2;
					}
					else
					{
						bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase41");
						pchar.questTemp.GoldenGirl.Game.Fail = "true"; // ГГ проиграл
					}
				}
				else
				{
					bStartGame = 100;//признак запрета новой игры
						sTemp += NewStr() + XI_ConvertString("CardsPhrase42");
					pchar.questTemp.GoldenGirl.Game.Win = "true"; // ГГ выиграл
				}	
			}
		}
	}
	else
	{
		bool wantToContinue = (CheckAttribute(pchar, "GenQuest.Cards.DontStop")) || (rand(10) < 10);
		if (CheckNextGame() && wantToContinue) // есть деньги на игру
		{
			sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("CardsPhrase43_1"),XI_ConvertString("CardsPhrase43_2"));
			bStartGame = 2;
		}
		else
		{
			bStartGame = 100;//признак запрета новой игры
			sTemp += NewStr() + XI_ConvertString("CardsPhrase44");
		}
    }
    SetFormatedText("INFO_TEXT", sTemp);
    RedrawCards();
	SetCardTip("restart");
}
bool CheckNextGame()
{
    bool ret = true;
    if (iRate*3 > iMoneyN) ret = false;
    if (iRate*3 > iMoneyP) ret = false;
    
    return ret;
}

/*
restart - новый кон
action - взять карту, передать ход, открыть карты
*/
void SetCardTip(string tag)
{
	switch(tag)
	{
		case "":	// убираем все подсказки
			SetPictureBlind("Pack", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetNodeUsing("TIP_RESTART", false);
			SetNodeUsing("TIP_TURN", false);
			SetNodeUsing("TIP_DRAW", false);
			SetNodeUsing("TIP_SHOW", false);
		break;
		case "restart":
			if(bStartGame >= 2 && bStartGame != 100)	// можно начать новую игру - колода
			{
				SetPictureBlind("Pack", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
				SetNodeUsing("TIP_RESTART", true);
			}
		break;
		case "action":
			if(dir_i == 1 && bStartGame >= 2 && !openExit && bStartGame != 100)
			{
				if(iMoneyP - iRate >= 0)	// хватает денег на ставку - колода
				{
					SetPictureBlind("Pack", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					SetNodeUsing("TIP_DRAW", true);
				}
				if(dir_i_start == 1)	// передача хода - портрет
				{
					SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					SetNodeUsing("TIP_TURN", true);
				}
				else	// вскрываемся - портрет
				{
					SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					SetNodeUsing("TIP_SHOW", true);
				}
			}
		break;
	}
}