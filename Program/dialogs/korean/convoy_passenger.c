//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("아, 젠장! 네가 누군지 알아! 네 배에 승객으로 타는 건 완전 바보나 할 짓이지! 잘 가라!","오, 네가 누군지 알아! 네 배에는 절대 타지 않을 거야. 내가 바보인 줄 알아?");
				link.l1 = RandPhraseSimple("헤, 뭐 이런 겁쟁이가 다 있나!","요즘 사람들은 정말 겁쟁이가 다 됐군!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! 나는 "+GetFullName(NPChar)+". 손님을 태운다고 들었는데?";
				link.l1 = "아마도. 내 이익에 달려 있지.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "나를 선술집으로 데려다줘야 해 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", 그날 "+XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination)+"Dat")+", 왜냐하면 "+FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time))+", 그래서 내가 돈을 주겠다 "+FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money))+". 동의하십니까?";
			link.l1 = "그래, 그렇다.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "흥미로운 제안이라고는 생각하지 않아.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернём его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap(false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "감사하오. 그대는 의무를 다했소. 나는 목적지에 도착했으니, 여기 보상일세. 자, 받으시오.";
			Link.l1 = "감사합니다.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("One person by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted, since "+ GetSexPhrase("he","she") +" had easily delivered him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Passenger named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He delivered","She delivered") +" him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " absolutelly safely.", 
				"I heard that you are a captain who keeps his word given to passengers. Huckster named " + GetFullName(npchar) + " is giving high praises to you."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterComplexReputation(pchar, "nobility",1);
			ChangeCharacterComplexReputation(pchar, "fame",1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear()+"선장님, 시간이 다 됐습니다. 도대체 언제야, 젠장, 내가 드디어 \n "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?",RandSwear()+"선장님, 도대체 언제까지 어디로 떠돌 셈입니까?! 언제쯤이면 우리가 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?",RandSwear()+"이봐, 선장, 나 거기로 가야 해 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", 그리고 이것이 언제 일어날지 분명하고 간단하게 대답해 주길 원하오!"),RandPhraseSimple("선장님, 또다시 당신의 의무에 대해 질문을 드려야겠습니다. 우리는 언제쯤 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?","선장님, 제 여정에 대해 다시 한 번 여쭙게 되는군요. 도대체 언제쯤이면 우리가 저 해안을 볼 수 있겠습니까 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?"),RandPhraseSimple(RandSwear()+"선장님, 세 번째 묻습니다 - 언제쯤 도착합니까 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?","선장님, 우리 정말 많은 시간을 허비했어요! 언제 저를 데려다 주실 건가요 "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?"),"이봐요, 선장님, 이건 정말 너무하잖아요!","block",0,npchar,Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("부디 용서해 주십시오, 처리해야 할 일이 너무 많았습니다... 일주일 후면 분명히 원하는 곳에 도착하실 겁니다.","미안하오, "+GetAddress_Form(NPChar)+", 정말 당신께 제 의무를 다하지 못했을 겁니다. 하지만 걱정 마십시오, 일주일 안에 도착할 것입니다."),RandPhraseSimple("다시 한 번 사과드려야겠군요. 일주일 안에 목적지에 도착할 것입니다.","다시 한 번 사과드립니다. 일주일 안에 목적지에 도착하겠습니다."),RandPhraseSimple("그리고 다시 한 번, 용서를 구해야겠군요... 일주일 안에 목적지에 도착할 것입니다.","그리고 다시 한 번, 미안하오. 일주일 안에 목적지에 도착할 것이니, 약속하오."),"알겠습니다. "+GetAddress_Form(NPChar)+", 하지만 제발, 조금만 참으십시오... 길어도 이레 안에 목적지까지 모셔다 드리겠습니다!",npchar,Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("오... 승객이었지... 너를 잊고 있었군... 이제 더 이상 나를 귀찮게 못 하도록 창고에 가두는 게 너한테도 더 편할 거다.","이런, 이런, 내 눈을 의심하겠군! 내 배에 낯선 놈이 들어오다니! 좋아, 그만 떠들고 당장 내 창고로 들어가!"),"두 번째라고? 오, 정말이군... 하지만 말이지, 어쩌면 너를 '구금실'로 구경 보내줄지도 모르겠다.","세 번째라고? 그거 참 안됐군, 헤헤... 자, 친구야, 내 선창에 온 걸 환영하지. 내 배 갑판에서 어슬렁거리며 나를 귀찮게 굴지 말았어야지.","아, 그렇군, 그 정도면 정말 짜증이 극에 달했겠지! 좋아, 이쯤에서 그만하자. 창고에 온 걸 환영한다. "+GetAddress_Form(NPChar)+".",npchar,Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("좋아, 하지만 지연된 만큼 보수는 깎겠어.","좋아, 믿어보지... 하지만 네 보수는 깎을 거야!","글쎄, 어차피 내가 갈 곳도 없지만, 네 보수는 깎을 거라는 건 명심해라....");
			Link.l1 = LinkRandPhrase("좋아.","좋아, 그럼...","알겠소, 말씀대로 하겠소.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("이번에는 당신이 의무를 다할 것이라 믿고 싶군.","이 불쾌한 주제에 대해 이번이 마지막 대화이길 진심으로 바랍니다.");
			Link.l1 = "물론이지.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear()+"어떤 창고? 무슨 말인지 모르겠어!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "더 이상 이해할 필요 없어! 이제부터 넌 내 포로다! 젠장, 창고로 들어가, 어서 움직여!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "그냥 농담이야... 일주일 후면 네 마을에 도착할 거야.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear()+"이 일에 대해 대가를 치르게 될 거야, "+GetSexPhrase("쓰레기","악취 나는 놈")+"!";
			Link.l1 = "다들 그렇게 말하지. 하지만 결국엔 다들 내게 돈을 내지!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("It has been reported that a captain named " + GetFullName(pchar) + " obliged to deliver a passenger by the name of " + GetFullName(npchar) + ", but didn't stay true to "+ GetSexPhrase("his","her") +" word. Besides, "+ GetSexPhrase("he","she") +" imprisoned a poor guy. That's what happens when you trust strange people...", 
				"What's wrong with this world?! Captain " + GetFullName(pchar) + " imprisoned a poor guy by the name of " + GetFullName(npchar) + ", despite him being a passenger on his ship...", 
				"People say, captain, that you are "+ GetSexPhrase("a real scoundrel","a really vile bitch") +". They say that poor " + GetFullName(npchar) + " was taken prisoner on board your ship. And you promised to deliver him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Very, very ugly ..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}
