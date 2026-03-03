void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "버그다. 개발자들에게 꼭 알려라.";
			link.l1 = "알겠어.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "여기 있습니다, 선장님. 이제 제 제안의 세부 사항을 논의해 봅시다.\n왜 제가 이 이야기를 공개적으로 하고 싶지 않았는지 이해하게 될 겁니다.";
			link.l1 = "계속 말씀하시지요, 나리. 듣고 있습니다.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "나는 ~에서 알아내는 데 성공했어 "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" 깃발 아래의 작은 무역 호송대 "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", 상선 두 척과 호위선 한 척이 곧 근처를 항해할 거야 "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", 여기서 멀지 않아 "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". 상인들이 많은 "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 창고 안에 있소. 이 정보를 안 쓸 이유가 없지, 선장님\n우리 둘이 경비병쯤은 쉽게 처리하고 화물을 가질 수 있소. 자, 할 텐가?";
					link.l1 = "솔깃한데. 난 찬성이야!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Some"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 내가 "+를+ "와(과) 관계를 망칠 만큼 충분하지 않아 "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"아니, 난 이 짓 안 해! 잘 있어라, 나리, 그리고 날 막으려 들지도 마!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "나는 ~에서 알아내는 데 성공했어 "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" 작은 무역 호송대가 깃발 아래에 있는 "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", 상선 두 척과 호위선 한 척이 출항할 거야, 출발지는 "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" 에게 "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+". 상인들에게는 충분한 "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 그 배들의 창고에 있소. 이 정보를 이용하지 않는 건 어리석은 일이오, 선장님.\n경비병들은 당신과 내가 쉽게 처리할 수 있고, 화물도 우리 몫으로 챙길 수 있소. 가장 어려운 건 이 두 식민지 사이의 망망대해에서 그들을 찾는 일이오. 자, 할 생각이오?";
					link.l1 = "솔깃한데. 난 찬성이야!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Some "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 내가 관계를 망칠 만큼 충분하지 않아 "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+". 아니, 난 이 짓 안 해! 잘 있어라, 나리, 그리고 날 막으려고도 하지 마!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "이라는 이름의 해적에 대해 들었소 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+". 이 악당이 최근에 훔쳤어 "+RandPhraseSimple(RandPhraseSimple("English","French"),RandPhraseSimple("Spanish","Dutch"))+" 그리고 그의 화물창에 \n 실었다 "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". 하지만 안타깝게도, 그의 배 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Name")+"Acc"))+" 심하게 손상되어서 수리를 하느라 시간이 좀 걸렸어.\n지금은 "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" ~의 "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". 내 생각에 대략 "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" 그가 돛대와 선체의 구멍을 고치게 하려면 말이야. 우리가 서두르면 제때 도착할 수 있어, 그리고 우리 모두가\n "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 우리 것이 될 거야\n나 혼자서는 이 해적을 상대할 수 없어. 그는 아주 노련한 선원이고 싸움꾼이거든. 하지만 우리 둘이라면 그의 경험에도 불구하고 충분히 해낼 수 있어. 자, 같이 할 거야, 말 거야?";
					link.l1 = "혹하는데. 난 찬성이야!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "흠. 이 전리품은 너뿐만 아니라 우리 둘 모두에게도 손에 닿지 않는 것 같군. 아니, 난 이 일을 하지 않을 거야. 잘 있어라, 나리, 그리고 날 막으려고도 하지 마!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "네가 믿을 만한 녀석이라는 걸 알았지!\n한 순간도 낭비하지 말자. 네 배로 가서 앞장서라, 내가 뒤따르겠다. 이제 출항할 때다!";
			link.l1 = "닻을 올리라고 명령하십시오, 선장님!";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "대체 내가 왜 너랑 엮였을까, 선장? 네 탓에 이렇게 귀한 전리품을 놓쳐버렸잖아! 다음엔 혼자 항해하는 게 낫겠군...";
			link.l1 = "네 잘못이지, 내 잘못 아니야. 잘 가.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "정말 한심하군, 선장! 우리는 몫도 못 받았어! 이게 다 당신 때문이야! 우리가 망한 건 다 당신 탓이야, 젠장!";
				link.l1 = "내가 그렇다고? 너나 좀 봐! 전투에서 나를 도와주지도 않았잖아! 너랑 있느라 내 시간만 낭비했어... 내 배에서 당장 내려!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "음, 이번 약탈은 내가 기대했던 것만큼 성공적이지 않았어. 우리가 얻은 건 정말 보잘것없군... 뭐, 선장, 이 남은 것들이라도 나눠 갖고 서로 작별하자.";
				link.l1 = "네가 하늘의 새나 세고 있지 말고 나를 도왔더라면, 습격이 성공했을 거야... 네 몫을 가져가라 - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" 그리고 꺼져!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "잘했네, 선장! 내가 말했잖아 - 저 상인들 화물창 비우는 건 정말 쉬웠다고, 하하... 전리품은 "+FindRussianQtyString(iQty)+" 조각이지. 내 몫은 "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "맞습니다. "+npchar.name+". 나도 이의 없어. 지금 장선에 짐을 싣고 있지. 아마 앞으로 또 같이 약탈하러 갈 수도 있겠군? 너라면 내 동료로 딱 맞을 것 같아.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "훌륭해요, 선장님! 내가 말했듯이, 저 상인들의 화물창을 비우는 건 생각보다 쉬웠소, 하하... 전리품이 엄청나군요, 내가 기대했던 것보다 훨씬 많소. 이건\n "+FindRussianQtyString(iQty)+" 조각이다. 내 몫은 "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "맞다, "+npchar.name+". 나도 이의 없네. 지금 당장 장선에 짐을 싣고 있지. 어쩌면 앞으로 또 같이 습격을 할 수도 있겠군? 자네라면 내 동료로 손색없어 보여.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем ещё одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "가능성은 있소, 선장님. 내가 혼자서는 쫓을 수 없는 또 다른 이득이 될 만한 소식이 들어오면 당신을 찾아가겠소. 전투에서도 믿을 만한 동료 같으니 말이오.";
			link.l1 = "좋아! 잘 가요, 선장님. 행운을 빌어요!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "네가 믿을 만한 놈이라는 걸 알았지! 한순간도 낭비하지 말자. 네 배로 가서 앞장서라, 내가 뒤따르겠다. 이제 출항할 때다!";
			link.l1 = "정박 해제 명령을 내리십시오, 선장님.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "네가 믿을 만한 녀석인 줄 알았지!\n한 순간도 낭비하지 말자. 네 배로 가서 나를 안내해라. 이제 출항할 때다!";
			link.l1 = "닻 올리라고 명령하십시오, 선장님.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "너는 겁쟁이야, 젠장할 놈! 방금 전장에서 도망쳤잖아!";
			link.l1 = "그래서 내가 뭘 어쩌란 말이야? 그 해적이 내 배를 가라앉히게 놔두라고? 절대 안 되지, 차라리 살아 있는 겁쟁이가 되는 게 죽은 바보가 되는 것보다 낫지!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "대체 왜 너랑 엮인 거지, 선장? 승선 전투를 두려워하지 않는 사내를 찾았어야 했는데!";
			link.l1 = " 이제 내 배에서 내려주게 - 수리를 해야 하니까.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "정말 한심하군, 선장! 우리 전리품 한 조각도 못 챙겼잖아! 이게 다 너 때문이야! 우리가 망한 건 전부 네 잘못이야, 젠장할 놈!";
				link.l1 = "내가 그렇다고? 너나 좀 봐! 전투 때 나 도와주지도 않았잖아! 너랑 시간만 낭비했네... 내 배에서 꺼져!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "음, 이번 약탈은 내가 기대했던 것만큼 성공적이지 않았어, 전리품도 정말 보잘것없군... 뭐, 선장, 이 찌꺼기나 나눠 갖고 서로 작별인사나 하자고.";
				link.l1 = "네가 하늘에 나는 새나 세지 말고 나를 도왔더라면, 이번 습격은 성공했을 거야... 네 몫을 가져가라 - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" 꺼져 버려!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "잘했소, 선장님! 전리품은 "+FindRussianQtyString(iQty)+" 조각이다. 내 몫은 "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "맞아. "+npchar.name+". 이의는 없소. 지금 장주가 실리고 있네. 아마 다시 만나게 되겠지...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "훌륭합니다, 선장님! 내가 말했듯이, 꽤 쉬웠지, 하하... 전리품이 엄청나군요, 내가 기대했던 것보다 훨씬 많아. 그건\n "+FindRussianQtyString(iQty)+" 조각들이지. 내 몫은 "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "맞다, "+npchar.name+". 나는 이의 없어. 지금 롱보트에 짐을 싣고 있지. 아마 앞으로 또 같이 습격을 나갈 수도 있겠군? 너라면 내 동료로 딱 어울릴 것 같아.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", 네 배로 가라. 잡담할 시간 없어. 출항하자!";
			link.l1 = "그래, 그래, 물론이지, 네 말이 맞아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "흠... 난 안 할 거야. 꺼져! 내가 직접 할 거니까!";
			link.l1 = "그래, 그래, 그럼 좋은 항해 되시길...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
