void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("마을에 경보가 울렸군. 이제 나도 무기를 들어야 할 때인 것 같아...","혹시 도시 경비병들이 너를 쫓고 있는 건 아니냐? ","여기서는 피난처를 찾을 수 없을 거다. 대신 네 갈비뼈 사이에 차가운 강철 몇 인치가 박힐 수는 있겠지!"),LinkRandPhrase("무슨 일이야?"+GetSexPhrase("악당","놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았어, 멀리 못 갈 거야, "+GetSexPhrase("더러운 해적","이 해적 계집아")+"!","더러운 살인자! 경비병들아!!!","난 너 따위 안 무서워, "+GetSexPhrase("기어가다","계집")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 도망가..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("살고 싶은 마음이 없는 모양이군...","그런 것 같군, 이곳 시민들에게 평화로운 삶이란 없는 모양이야 "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("지옥에나 떨어져라!","헤, 이게 네 인생의 마지막 몇 초가 되겠군..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "경고는 했어. 이제 네가 직접 결정해, 문제에 휘말릴지 말지.";
					link.l1 = "헤헷!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "내 집에 뭐 하러 왔어, 이 망할 놈아?! 열 초 안에 꺼지지 않으면 가만두지 않겠다!";
					link.l1 = LinkRandPhrase("헤헤, 여기서도 나를 아는 모양이군!","내 명성이 방금 앞서 갔군...","흠, 알겠군.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("내 집에 오신 걸 환영하오. 무슨 일로 오셨소?","무엇을 도와드릴까요?","흠... 뭘 도와줄까?","죄송하지만, 볼일이 없다면 제게 방해하지 말아 주십시오...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("아니, 그냥 둘러보고 새로운 사람들을 만나고 있을 뿐이야...","아니, 특별한 건 없어...","아무것도...","좋소, 말씀대로 하겠소.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("죄송하지만, 밤에는 방문하기에 적절한 시간이 아니니, 지금 당장 제 집에서 나가 주시기 바랍니다!","이미 말했소, 지금은 늦었으니 나가주시오.","무례하게 보이고 싶진 않지만, 당장 내 집에서 나가주시오!","젠장, 무슨 일이야?! 경비병! 도둑이다!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("그래, 알겠어...","그래, 잠깐만...","알겠어, 너무 흥분하지 마.","도둑이라니?! 닥쳐!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "아, 제 소개를 하겠습니다 - "+GetFullName(npchar)+". 당신을 우리 손님으로 모시게 되어 매우 기쁩니다. 이 마을에서는 환대의 법도가 존중받고 있습니다.";
			link.l1 = GetFullName(pchar)+", 부탁하오...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이군! 경비병들, 저 자를 잡아라","도둑이로군! 경비병들, 저 여자 잡아라")+"!!!","믿을 수가 없어! 잠깐 한눈판 사이에 내 물건을 뒤지고 있잖아! 멈춰, 도둑놈아!!!","경비병들! 도둑이다! 도둑을 잡아라!!!");
			link.l1 = "아아악, 악마다!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("경고하는데, 내 남편이 곧 돌아올 거야! 당장 내 집에서 나가는 게 좋을 거야!","도망칠 수 있을 것 같지 않군! 그리고 내 남편이 곧 집에 온다는 걸 알아둬!","제 남편이 곧 집에 올 거예요! 당장 나가셔야 해요!"),LinkRandPhrase("남편이 집에 없어서 유감이군... 나가! 당장!!!","더러운 살인자, 당장 내 집에서 나가! 경비병!",""+GetSexPhrase("정말 못된 놈이군","이 더러운 것")+"... 곧 내 남편이 돌아올 거야. 그 사람이 네 피가 무슨 색인지 보게 될 거다!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("오, 당신 남편이... 오오오... 나는 떨리고 있어...","헤... 있잖아, 아가씨, 네 남편도 결국 한 사람일 뿐이야... 네 발밑에 죽어 있는 꼴은 보고 싶지 않겠지?"),RandPhraseSimple("닥쳐, 계집아, 배를 가르기 전에...","나는 내가 원하는 만큼 여기 있을 거야. 그리고 네가 잘 알고 싶으면 입 다물고 있는 게 좋을 거다..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "경고했잖아. 나가, 아니면 후회하게 될 거야!";
					link.l1 = "참 어리석은 계집이군...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "내 집에서 뭐 하고 있는 거야, "+GetSexPhrase("놈","놈")+"?! 10초 안에 나가지 않으면 경비병을 부를 거야!";
					link.l1 = "정말 멍청한 계집이군...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("우리 집에 오신 걸 반갑게 생각합니다. 제 이름은 "+GetFullName(npchar)+". 무엇을 도와드릴까요?","아직도 여기 있어?","음, 실례지만 이제 떠날 때가 되지 않았소?","저희의 환대를 남용하지 말아 주시길 정중히 부탁드립니다.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" 언제든지 도와드리겠습니다. 특별한 이유 없이, 그냥 당신을 한번 뵙고 싶어서 왔습니다.","아직 여기 있군.","글쎄, 잘 모르겠는데...","좋아.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("이런, 이런 시간에 왜 우리 집에 들이닥치는 거요! 정말 깜짝 놀랐잖아요... 제발, 내일 다시 찾아와 주세요!","제발, 우리 집에서 나가시오!"+GetSexPhrase("","나는 결혼한 여자야!")+"","이번이 마지막이니 우리 집에서 나가 주시오!","그런데 도대체 여기서 무슨 일이 벌어지고 있는 거야?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("겁내지 마, 해치지 않을 테니까.","알겠어, 그렇게 흥분하지 마.","나는 떠난다.","무슨 일이야?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "우리는 손님이 오시면 언제나 반갑지. 하지만 너무 오래 머무르지는 마시오,"+GetSexPhrase(", 나는 유부녀이니까..."," 할 일이 많으니까...")+"";
			link.l1 = "아, 예, 물론이지...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "그런 거였나? 내가 손님으로 맞이했더니 우리 궤짝을 뒤지고 있군?! 경비병들!";
			link.l1 = "닥쳐, 이 년아!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "정중하게 우리 집에서 나가 달라고 했는데도, 당신은 전혀 듣지 않았어! 이제 그만! 도와줘요! 경비병!";
			link.l1 = "닥쳐, 이 멍청한 여자야! 미쳤어?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울렸군. 이제 나도 무기를 들어야 할 때인 것 같아...","혹시 도시 경비병들이 너를 쫓고 있는 거 아니야? ","여기서는 피난처를 찾지 못할 거다, 대신 네 갈비뼈 사이에 차가운 강철 몇 치쯤은 꽂힐 수 있겠지!"),LinkRandPhrase("무슨 일이야?"+GetSexPhrase("놈","놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았어, 멀리 못 갈 거야, "+GetSexPhrase("더러운 해적","계집")+"!","더러운 살인자야! 경비병들!!!","난 너 따위 안 두려워, "+GetSexPhrase("기어가다","계집")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 거야..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("살고 싶은 마음이 없는 모양이군...","그렇군, 이곳 시민들에게 평화로운 삶이란 없는 것 같아 "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("지옥에나 떨어져라!","헤, 이게 네 인생의 마지막 몇 초가 되겠군..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("환영합니다! 제 이름은 "+GetFullName(npchar)+". 여긴 내가 책임지고 있으니, 뭐든 가져가려는 생각은 꿈도 꾸지 마라...","행동 똑바로 하고, 내가 널 지켜보고 있다는 걸 명심해.","네가 상자 안을 들여다보지만 않으면 여기 있어도 돼. 어차피 혼자 있으니 심심하거든...",RandPhraseSimple("아이고, 정말 심심하구나!","젠장, 어쩌지? 여기 있으니 너무 지루하잖아!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("알겠어, 걱정하지 마.","물론이지!","그렇군...","그래, 그거 문제인 것 같군.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울렸군. 이제 나도 무기를 들어야 할 때인 것 같아...","혹시 도시 경비병들이 너를 쫓고 있는 거 아니야? ","여기서는 피신처를 찾을 수 없을 거다. 대신 네 갈비뼈 사이에 차가운 강철 몇 치쯤은 박힐 수 있겠지!"),LinkRandPhrase("무슨 일이야?"+GetSexPhrase("놈","놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았어, 멀리 못 가. "+GetSexPhrase("더러운 해적","계집")+"!",""+GetSexPhrase("Filthy","Filthy")+" 살인자다! 경비병들아!!!","나는 너 따위 안 무서워, "+GetSexPhrase("기어가다","계집")+"! 곧 우리 요새에서 목이 매달릴 테니, 멀리 못 갈 거다..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("살고 싶은 마음이 없는 모양이군...","그런 것 같군, 이곳 시민들에게는 평화로운 삶이란 없는 모양이야 "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("지옥에나 떨어져라!","헤, 이게 네 인생의 마지막 몇 초가 되겠군..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("여기서는 내가 책임자니까, 뭐라도 가져가려는 생각은 꿈도 꾸지 마라...","행동 조심하고, 내가 너를 지켜보고 있다는 걸 명심해.","상자 안을 들여다보지만 않으면 여기 있어도 된다. 어차피 나 혼자 있으니 심심하거든...",RandPhraseSimple("아이고, 정말 심심하구나!","젠장, 어쩌지? 여기 있으니까 너무 지루해!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("알았어, 걱정하지 마.","물론이지!","그렇군...","그래, 그거 문제인 것 같군.",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "이봐, 친구, 솔직하게 할 말이 있어.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "당신에게 솔깃한 제안이 있어. 혹시 관심 있겠나?";
					link.l7 = "정말이야? 좋아, 듣고 있어.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "창고로 데려가라. 상태가 어떤지 보고 싶다.";
						link.l7.go = "storage_0";
						link.l8 = "나는 창고를 비우기로 했어. 이제 더 이상 필요 없거든.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "창고 얘기를 했었지. 아직 비어 있나?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "창고로 쓰기 좋은 공간이 있습니다. 적당한 가격에 임대하시겠습니까? \n 생각해 보세요, 귀중한 화물을 보관할 당신만의 창고가 생기는 겁니다...";
			link.l1 = "창고라니, 그렇군... 정말 솔깃하군. 크기는 충분한가? 그리고 임대료는 얼마를 받을 생각이지?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "항구 창고치고는 꽤 넓군요. 음, 5만 센트너의 화물을 보관할 수 있습니다. \n "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  한 달마다 당신의 물품을 안전하게 보관해 드릴 수 있습니다. "+"이 일에는 내 부하들과 함께 지키는 것, 습기로부터 보호하는 것, 쥐들과 싸우는 것까지 포함돼. 어때, 할 생각 있나? 아, 그리고 비밀 유지도 물론 당연한 거지.";
			link.l1 = "알겠소. 내가 한 번 봐도 되겠소?";	
			link.l1.go = "storage_rent2";
			link.l2 = "너무 비싸. 게다가 물에 잠겼을 테고 쥐들로 들끓겠지.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "알겠어, 알겠어. 하지만... 한 달치 선금을 미리 받아야겠어. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "당신은... 정말 대단한 상인이군요. 여기 돈이요 ... 이 창고를 빌리겠소.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "당신은... 꽤 장사꾼 기질이 있군요, 인정해야겠소. 좋아요, 돈을 가져오겠소.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "원하시는 대로 하십시오. 마음이 바뀌면 언제든 말씀해 주십시오. 그리고 이렇게 좋은 창고가 오래 비어 있지는 않을 거라는 점도 기억해 두시길...";
			link.l1 = "문제 없어. 필요하면 내가 말할게.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "그리고 집세는 아직도 나한테 빚졌어  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "좋아, 지금 임대료를 내겠어.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "나중에 다시 올게.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "앞서 가.";
				link.l1 = "고맙다.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("선장님, 배는 어디 있습니까? 화물을 어떻게 옮길 계획이십니까?","네 배가 항구에 정박해 있는 게 안 보이는데, 도대체 어떻게 선적할 생각이지?");
                link.l1 = RandPhraseSimple("아... 그걸 완전히 잊고 있었네!","젠장, 맞아!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "아니, 마음이 바뀌었어.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "아니, "+GetSexPhrase("나리","마님")+", 아직도 비어 있고 당신을 기다리고 있소. 결국 내 제안을 거절하지 않을 거라는 걸 알고 있었지.";
			link.l1 = "아주 좋아. 내가 빌릴게.";
			link.l1.go = "storage_1";
			link.l2 = "아니, 그냥 문득 생각나서...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "기억하고 있겠지만, 한 달치 선불이 필요하네.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "물론이지, 기억하고 있어. 자, 여기 있다.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "젠장. 알겠어, 돈 가져올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "벌써 떠나시나? 아쉽군, 여기 조건이 정말 훌륭한데. 내가 장담하는데, 카리브 해 어디에서도 이런 거래는 못 할 걸세.";
			link.l1 = "내가 말했잖아, 내가 방을 비운다고. 아니면 내가 공기 저장하는 데 돈을 내야 하오? 다른 세입자를 찾아보시오.";
			link.l1.go = "storage_4";
			link.l2 = "카리브 해 어디에도 없다고? 좋아, 그럼 잠시 가지고 있지. 하지만 임대료가 좀 너무 비싸네.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "그리고 집세는 아직도 내게 빚졌소 "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "좋아.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "물건을 챙기시오, 내가 창고를 닫겠소.";
				link.l1 = "좋아.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("선장님, 배는 어디 있습니까? 화물을 어떻게 옮길 생각이십니까?","네 배가 항구에 정박해 있는 게 안 보이는데, 도대체 어떻게 배에 짐을 싣겠다는 거지?");
                link.l1 = RandPhraseSimple("아... 그걸 완전히 잊고 있었네!","젠장, 맞아!");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "헤! 좋아, 얘기하자.";
			link.l1 = "밤에, 아무도 없을 때 조선소에 가야 해.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "너 좀 봐라! 이봐, 경비병들, 여기 도둑이 있어!!!";
				link.l1 = "도둑이라니? 난 그냥 얘기 좀 하려고 했을 뿐이야!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "이런 젠장! 너 좀 봐라, "+GetSexPhrase("동료","아가씨")+". 그런 부탁을 가지고 조선소 창고에 오다니!";
				link.l1 = "난 조선소로 직접 가야 해. 네 창고 따위엔 전혀 관심 없어.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "그런데 그게 왜 필요하지?";
			link.l1 = "필요가 있지. 그리고 나는 그 대가를 치를 생각이야...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "흠, 이제 좀 낫군... 좋아! 건네줘 "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", 그리고 다음 날 조선소 문을 열어 두겠소.";
			link.l1 = "너무 비싸군. 그럼 그냥 포기해야겠네...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "좋아, 동의하지. 돈 가져가고 우리가 약속한 대로 해.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "걱정 마시오, 곧 처리될 것이오.";
			link.l1 = "그러길 바라지...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
