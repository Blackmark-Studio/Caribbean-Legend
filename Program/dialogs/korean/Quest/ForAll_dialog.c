void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "우리에겐 더 이상 할 말이 없다.";
			link.l1 = "좋아...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 마을 시민이니 칼을 거둬 주겠나.","이봐, 나는 이 마을 시민이니 칼 좀 내려줘.");
				link.l1 = LinkRandPhrase("좋아.","그래.","좋아...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, "+GetSexPhrase("친구","소녀")+", 무기를 들고 돌아다니니 불안해지잖아...","나는 ~이 있을 때가 싫어 "+GetSexPhrase("남자들","사람들")+" 내 앞에서 무기를 뽑은 채로 걸어가고 있어. 그게 나를 겁나게 해...");
				link.l1 = RandPhraseSimple("알겠어.","알겠어.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "자, 이봐, 주머니 좀 보여 줘.";
			link.l1 = "뭐라고?!";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "내 말 들었지. 빨리 해, 말은 적게. 난 말 많은 거 싫어...";
			link.l1 = "젠장! 그리고 "+pchar.questTemp.different.FackWaitress.Name+" 너랑 같이 일할까?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "그래, 그래... 돈 내놔, 아니면 배를 갈라버릴 거야!";
			link.l1 = "안 돼! 네 배를 갈라버리겠다!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "내 돈 가져가, 이 망할 놈아! 하지만 그냥 넘어가진 않을 거야...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "그래, 그건 할 말 없지. 잘 가라, 친구. 그리고 기억해, 네가 그렇게 잘생기진 않아서 술집 아가씨들이 반하지는 않을 거야. 다음엔 좀 더 똑똑하게 굴라고!";
			link.l1 = "...어서 가.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "말씀대로 하겠습니다...";
			link.l1 = "그래, 그렇지...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "여기 있어! 나 원해, 잘생긴이?";
			link.l1 = "젠장, 일이 순식간에 커졌군...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "시간 낭비하지 말자!";
			link.l1 = "헤헤, 나도 완전 동감이야!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "안녕하시오. 내 이름은 "+GetFullName(npchar)+". 나는 선장이오 "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+"'."; 
			link.l1 = "훌륭해! 드디어 널 찾았군.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "나를 찾았다고?!";
			link.l1 = "그래. 자네가 항구 사무소에 두고 간 항해일지를 가져왔네\n "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "젠장! 이제야 어디서 잃어버렸는지 알겠군. 이 손실 때문에 내 배에서 거의 반란이 일어날 뻔했어...";
			link.l1 = "끝이 좋으면 다 좋은 거지. 항해일지 가져가고, 이제 내 돈 얘기나 하자.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "좋은 타이밍이군, 아직 새 일을 시작하지 않았으니 줄 수 있는 만큼 줄게. "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 내 개인 장신구 몇 점도 받아주시오.";
				link.l1 = "좋아. 가져가.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "흠, 있잖아, 나는 이미 새 항해일지를 쓰기 시작했어. 그래도 옛날 일지도 내게는 아직 소중해. 그러니 값을 치르지. "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 내 개인 장신구 몇 점도 받아주시오.";
					link.l1 = "좋아, 거래지. 항해일지를 가져가.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "나는 이미 새 항해일지를 시작했어. 그리고 옛날 일지에 있던 모든 기록도 옮겨놨지. 이제 더 이상 필요 없으니, 너한테 줄 돈도 없어.";
					link.l1 = "좋아. 결국 이 모든 추격이 헛수고였군.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "감사합니다. 안녕히 가십시오, "+GetSexPhrase("친구","소녀")+".";
			link.l1 = "너도 마찬가지야...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "하, 다음엔 타이밍 좀 맞춰라.";
			link.l1 = "맞는 말이야.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "내 배 갑판에서 그대를 맞이하오. 솔직히 말해, 자네가 날 완전히 놀라게 했소 - 난 외눈박이 말 사냥꾼이 날 쫓아온 줄 알았거든...";
				link.l1 = "아니요, 선장님, 오늘은 기분이 좋습니다. 도와드리려고 왔습니다.";
			}
			else
			{
				dialog.text = "내 배에 탄 걸 환영한다!";
				link.l1 = "이봐, 선장! 너를 찾고 있었어.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "왜?";
			link.l1 = "당신은 항만 관리인의 집에 항해일지를 두고 왔소\n "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "젠장, 그게 바로 그곳이었군! 이 손실 때문에 이미 골치 아픈 일이 잔뜩 생겼어.";
				link.l1 = "보상은 어때?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "젠장, 이제야 어디서 잃어버렸는지 알겠군! 고맙다만, 넌 날 너무 오래 찾았어. 난 이미 새 항해일지를 시작했거든. 그래도 옛 기록들은 새 일지에 옮겨 적어야겠지...";
					link.l1 = "얼마나 되지?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "나는 이미 새 항해일지를 시작했어. 그리고 옛날 일지에서 모든 기록을 옮겨놨어. 이제 더 이상 필요 없어.";
					link.l1 = "그래서 오래된 일지가 필요 없다는 거야? 정말이야?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "내가 돈을 줄 수 있어 "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 내 보석 몇 개도. 그게 내가 줄 수 있는 전부야.";
			link.l1 = "좋아. 네 일지를 가져가.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "다시 한 번 고맙다. 잘 가라, 친구.";
			link.l1 = "계속 그렇게 해.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "그건 확실하지. 누군가를 쫓고 있다면 더 빨라야 해.";
			link.l1 = "애초에 항해일지를 잃어버리지 말라고. 알겠어.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "다들 진정한 줄 알았는데.";
			link.l1 = "그래, 맞아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "안녕. 뭐 원하는 거야?";
			link.l1 = "별거 아니야, 그냥 소식 좀 듣고 싶어서. 팔 만한 거 있나?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "팔 게 없고, 소식도 없어. 그런데 네가 여기 있는 게 달갑지 않다. 내 말 알아들었지?";
			link.l1 = "너는... 그럼 잘 가라, 친구.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "내가 말했잖아, 네가 여기 있을 자격 없어!";
			link.l1 = "그렇군...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "왜 나를 공격한 거야?!";
			link.l1 = "나는 배를 주인에게 돌려줘야 해.";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "어떤 주인에게? 내가 바로 주인이다!";
			link.l1 = "아니, 너는 아니야. 이 배가 누구 소유인지 나도 몰라. 하지만 이 배는 도둑맞았고, 내가 돌려줘야 해.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "젠장! 하지만 난 아직 끝나지 않았어. 최소한 너라도 죽여보겠다...";
			link.l1 = "시도하는 것밖에 할 수 있는 게 없어.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "안녕하시오, "+GetAddress_Form(NPChar)+". 자네가 자기 배의 선장인가 보군? 내 이름은 "+GetFullName(npchar)+" 그리고 너한테 거래를 제안하고 싶어.";
			link.l1 = RandPhraseSimple("정말 미안하지만, 이제 가봐야겠어.","정말 미안하지만, 지금은 너와 이야기할 시간이 없어.");
			link.l1.go = "SCQ_exit";
			link.l2 = "잘 듣고 있네.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "그럼, 들어봐. "+SelectNB_battleText()+"\n나는 그를 찾을 시간도, 기회도 없어. 여긴 절대 오지 않거든. 이제 알겠지? 내가 너한테 뭘 제안하려는지?";
						link.l1 = LinkRandPhrase("내가 누군가를 찾아서 당신에게 데려와야 한다는 말이오?","아마 그 자식을 찾아서 당신에게 데려오라는 건가?","이 남자를 찾아서 여기로 데려오라는 거요?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "그럼 들어봐."+SelectNB_battleText()+"\n나는 그를 찾을 시간도, 기회도 없어. 그는 여기 절대 오지 않아. 이제 알겠지, 내가 너에게 뭘 제안하려는지?";
						link.l1 = LinkRandPhrase("내가 누군가를 찾아서 데려오길 바라는 거지?","아마도, 그 자식을 찾아서 당신에게 데려오라는 건가?","이 남자를 찾아서 여기로 데려오라는 거요?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "그럼 들어봐라. 사실, "+npchar.quest.text+" 해군에서 선장으로 복무 중이야. 나도 여기 있다는 걸 전혀 모르지!\n나도 그를 만나고 싶지만, 시간도 없고 그를 찾을 기회도 없어...";
					link.l1 = "네가 그 선장을 찾아가서 당신 얘기를 전해 달라는 거지?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "꼭 그렇진 않다. 그 자를 찾아라. 하지만 여기로 데려올 필요는 없다. 죽이면 그걸로 충분하다. 그 더러운 배와 함께 수장시키든, 총으로 쏘든, 칼로 찌르든, 어떻게 하든 상관없다. 저 자식이 더 이상 이 세상에 독을 퍼뜨리지 못하게만 해라. 보상은 넉넉히 주겠다.";
			link.l1 = "하! 그거 쉽지. 그의 이름이랑 배 이름을 말해 봐.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" ~의 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+". 그는 종종 항구에 들르는 손님이야 "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". 내가 돈을 줄게 "+FindRussianMoneyString(sti(npchar.quest.money))+" 황금 두블론으로.";
			link.l1 = "그거면 됐어. 바다에서 눈 똑바로 뜨고 있을 테니까. 그리고 네 친구를 찾으면, 내가 그놈을... '목소리를 낮추며' ...산 채로 두진 않을 거다.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "그런 일에는 이 정도로는 부족해.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "거래가 성사되어 기쁘네. 자네가 돌아오기를 기다리고 있겠네.";
			link.l1 = "어디서 널 찾을 수 있지? 지금 확실히 해 두자, 너 찾느라 시간 낭비하고 싶지 않으니까.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "나는 매일 아침 지역 교회에서 예배에 참석해. 나를 매일 오전 8시부터 9시까지 거기서 볼 수 있을 거야.";
			link.l1 = "좋아, 거래지! 곧 결과를 기대하라.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "그래. 그를 찾아서 내게 데려오너라. 살아 있는 채로. 내가 직접 처리하겠다. 넉넉하게 보상해 주마.";
			link.l1 = "글쎄, 찾아볼 수는 있겠지만, 자세한 정보가 필요해.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "그 자식 이름은 "+npchar.quest.SeekCap.name+". 그는 ~에서 복무하고 있어 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+", 지휘하는 이는 "+npchar.quest.SeekCap.capName+". 그 배는 자주 항구에서 보인다 "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". 이 일에 대한 보수를 주겠소 "+FindRussianMoneyString(sti(npchar.quest.money))+" 황금 두블룬으로.";
			link.l1 = "그 정도면 됐어. 망망대해에선 내가 경계할 테니까.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "그런 일에는 이 정도로는 부족해.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "거래가 성사되어 기쁘군. 돌아오기를 기다릴게.";
			link.l1 = "어디서 널 찾을 수 있지? 지금 확실히 해 두자, 괜히 너 찾느라 시간 낭비하고 싶지 않으니까.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "나는 매일 아침 지역 교회에서 예배를 드려. \n매일 오전 8시부터 9시까지 거기서 나를 만날 수 있어.";
			link.l1 = "좋아, 거래지! 곧 결과를 기대하라.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "정확해! 그를 찾아서 내가 이 마을에 산다고 전해 줘. 네 수고에 대한 보수는 내가 지불하겠다.";
			link.l1 = "음... 해볼 수는 있지. 자세한 내용을 말해봐.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "그의 이름은 "+npchar.quest.SeekCap.capName+". 그리고 그는 근무하고 있어 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. 그는 자주 방문해 "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". 이 일에 대한 보수를 주겠소 "+FindRussianMoneyString(sti(npchar.quest.money))+" 금화 두블룬으로.";
			link.l1 = "거래 성사다! 곧 네 친구를 찾게 되겠지.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "나에겐 이걸로는 부족해.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "거래가 성사되어 기쁘군. 돌아오기를 기다리겠소.";
			link.l1 = "어디서 널 찾을 수 있지? 지금 확실히 해두자, 너를 찾아다니며 시간 낭비하고 싶지 않으니까.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "나는 항상 지역 교회에서 저녁 예배에 참석해. 매일 오후 6시부터 8시까지 거기서 날 찾을 수 있어.";
			link.l1 = "그럼 거래지! 곧 결과를 기대하라.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "그래서? 뭘 원하시오, 나리?";
			link.l1 = "네가 선장이냐 "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "그래, 나다. 무슨 일이야?";
			link.l1 = "한 남자가 너에게 아주 큰 관심을 가지고 있어, 그의 이름은 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". 기억나지?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "네 창고에 마호가니가 많이 있다고 들었어. 내가 좀 사고 싶은데, 팔 생각 있나?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "이 이름은 처음 듣는군. 착각하신 것 같소, 선장. 이제 끝인가?";
			link.l1 = "흠. 좋아, 미안하군...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "정말인가? 하지만 그는 너를 아주 잘 기억하고 있어. 네가 그에게 진 빚에 대해 언급하더군...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "무슨 빚? 무슨 소리야?";
			link.l1 = "명예의 빚이로군!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "착각하셨군. 나는 목재 거래 안 해. 이제 끝났나?";
			link.l1 = "흠. 좋아, 실례하지...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "그래서? 뭘 원하는 거지, 나리?";
			link.l1 = "네가 선장이냐 "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "그래, 나야. 무슨 일이야?";
			link.l1 = "이름이 "+sld.quest.SeekCap.name+" 당신의 지휘 아래에서 복무하라고?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "그래. 그는 내 부하 장교 중 한 명이야. 이제 말해 봐, 왜 묻는 거지?";
			link.l1 = "물론이지, 말해주겠다. 나는 이 남자를 당국의 명령으로 찾고 있다. "+XI_ConvertString("Colony"+sld.city+"Gen")+", 그리고 나는 그를 체포해 넘길 권한이 있다 "+XI_ConvertString("Colony"+sld.city)+". 이 일을 평화롭게 해결할 수 있도록 도와주시길 부탁드립니다.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "정말이야? 그런 놈이 내 선원이라고? 진심이냐?";
				link.l1 = "그 일로 신경 쓰지 마. "+GetAddress_FormToNPC(NPChar)+". 내가 너희 배로 장선(긴 보트)을 보내겠다. 우리가 직접 그를 데려가마.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "그런가 보군. 그런데 말이야, 나리, 난 그 자의 과거 따윈 전혀 신경 안 써. 내 알 바 아니거든. 그런데 넌 누구지? 당국이라도 된다는 건가? 정말? 하! 내 부하들을 너한테도, 누구한테도 넘기지 않아. 이 얘기는 여기서 끝이다. 썩 꺼져!";
				link.l1 = "잘못 골랐군... 정말 끔찍한 선택이야!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "해야 할 일을 해.";
			link.l1 = "알겠어.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "우리 끝난 거요, 선장님?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "좋은 하루요. 무슨 일이오, 선장?";
			link.l1 = "네가 선장이야 "+GetFullName(npchar)+", 맞지?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "네 말이 맞아. 나한테 줄 게 있나?";
			link.l1 = "내가 봤어. 이름이 "+GetFullName(sld)+" 널 찾고 있어. 가능한 한 빨리 찾아오라고 하더군. 그는 \n에 살고 있어. "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "하! 그 자도 신세계로 옮겼단 말이지? 그럼 내가 꼭 한번 찾아가 봐야겠군... 정보 고마워, 나리!";
			link.l1 = "천만에. 네 친구가 내 일값을 지불할 거다. 행운을 빌지, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "즐거웠소, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "영광이었습니다, 선장님.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "이봐, "+GetAddress_Form(NPChar)+". 뭐 원하는 거야?";
			link.l1 = "네 화물에 레드우드가 많이 있다고 들었어. 그걸 좀 사고 싶은데, 팔 생각 있나?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "착각하셨군. 나는 나무를 거래하지 않아, 그리고 네가 여기 온 게 수상해 보여. 내 생각엔 네가 내 배에서 나가는 게 좋겠어!";
			link.l1 = "알았어, 그냥 물어본 거야. 잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "문제라도 만들고 싶은 거요, 나리? 다시 말해줘야겠소?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "왜 내 배를 공격했지, 이 악당아?";
			link.l1 = "나는 여기 "+GetFullName(npchar)+"의 최고의 안부를 전하러 왔소 "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , "+남자 이름+"에게서 온 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". 이제 상황을 이해했으리라 생각하오.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "말도 안 돼! 이제 나에겐 잃을 것도 없군...";
			link.l1 = "자네 삶은 어떤가?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "왜 내 배를 공격했지, 이 악당아?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "생각난 거 있어? 내가 네 장교를 순순히 넘기라고 했지. 이제는 그놈도, 너도, 네 배까지 다 가져가겠다!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "네 지휘 아래에 있는 악당이 한 명 있다. 이름은 "+sld.quest.SeekCap.name+"". "의 당국 "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" 그를 정말 보고 싶어하지. 그는 체포되어 내 선실에 갇히게 될 거야.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "그래서 내 배에서 학살을 저질렀다는 거냐? 이 망할 놈! 아직 힘이 좀 남아 있다... 널 죽여주마!";
			link.l1 = "더 강한 놈들도 시도했지...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "어떻게 생각하시오, 선장? 내 일은 진전이 있소?";
			link.l1 = "아직 아니야. 하지만 곧 할 거야.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "어떻게 생각하시오, 선장? 내 일은 좀 진척이 있소?";
					link.l1 = "그래, 나도 그렇지. 그리고 너도 분명히 마음에 들 거야."+npchar.quest.SeekCap.capName+" 죽었고 그의 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" 바다 밑바닥에 있다.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "어떻게 생각하시오, 선장? 내 일은 좀 진전이 있소?";
					link.l1 = "그래, 나도 그래. 그리고 너도 분명히 마음에 들 거야."+npchar.quest.SeekCap.Name+" 내 배 선실에서 구금 중이다.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "아, 여기 있었군. 만나서 반갑다. 임무를 성공적으로 마쳤다는 소식을 들었어!";
					link.l1 = "네 친구가 너를 찾아왔어?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "훌륭하군! 자네라면 믿을 수 있을 줄 알았지. 자, 여기 금화다. 자네가 충분히 받을 자격이 있네.";
			link.l1 = "고마워. 또 적이 생기면 다시 말 걸어.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "훌륭하군! 내가 내 부하들에게 곧바로 그를 네 배에서 데려가라고 명령하겠다. 이제 그는 절대 도망치지 못할 거다! 자, 여기 네 금화다. 네가 받을 자격이 있지.";
			link.l1 = "고마워. 이런 일이라면 언제든 나한테 와.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "그래, 그가 여기 와서 자네 얘기를 했지. 자, 금화를 가져가게. 자네가 벌었으니.";
			link.l1 = "감사하오. 안녕히 가시오, 나리!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("안녕하십니까, 선장님. 당신의 도움이 필요합니다.","선장님! 저 좀 도와주실 수 있나요? 제발요.","선장님, 도와주십시오!");
			link.l1 = RandPhraseSimple("나 바쁘다.","나는 급하다.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("무슨 일이야?","무슨 걱정이 있는지 말해 봐. 내가 도와줄 수도 있으니까.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "1년 전에 한 선장이 나를 데려가겠다고 약속했지 "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+". 하지만 그의 배에 있을 때 나는 창고에 갇혔다가 나중에 노예로 팔려갔어. 간신히 살아남았지. 몇 번이나 죽을 뻔했어... 아무튼, 내 '친구'에게 내가 아직 살아 있다는 걸 상기시켜 주고 싶군."; // belamour gen
					link.l1 = "무슨 뜻이야? 네가 원하는 걸 정확히 말해.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "내 아내가 납치당했소. 선장이라더군, 해적이라고들 하지. 그 자가 내 아내를 따라다니며 구애했소. 아내는 그놈 때문에 며칠이나 집에만 있어야 했지. 마을 관리들에게 도움을 청해봤지만 소용없었소. 그리고 지금은...";
					link.l1 = "이제 어쩔까?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "있잖아, 나는 내 고향 사람을 찾고 있어. 3년 전에 더 나은 삶을 찾아 유럽에서 함께 여기로 왔지. 그런데 서로 연락이 끊겼어. 하지만 얼마 전, 그가 지금은 무역 선장이 되었다는 소문을 들었어! 내가 직접 찾아보려고 했지만, 실패했지.";
					link.l1 = "그래서?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "그 자를 찾아서 죽여 줬으면 해. 너무 죽이고 싶어서 밥도 못 먹겠어...";
			link.l1 = "알겠소... 도와줄 수 있을 것 같군. 그의 이름과 배 이름을 말해 보시오.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "미안하지만, 난 관심 없어.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" ~의 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+". 내가 돈 줄게  "+FindRussianMoneyString(sti(npchar.quest.money))+", 그리고 내 모든 보석들도."; // belamour gen
			link.l1 = "알겠소. 바다에서는 주의하겠소. 목표를 찾는다면... 그때는 죽은 목숨이라 생각하시오.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "그 돈으로는 아무것도 안 해. 복수할 다른 바보나 찾아봐.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "그 말을 듣고 싶었어! 아, 이제 밥 좀 먹을 수 있겠네! 드디어! 얼른 뭐라도 먹어야겠다...";
			link.l1 = "맛있게 드시오. 일이 끝나면 내가 다시 찾아가겠소.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "나는 현지 교회에서 기다리고 있겠소.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "내가 너무 게을렀더니, 그 개자식이 내 아내를 납치해서 자기 배에 태워 갔어. 제발 저 악당을 찾아줘!";
			link.l1 = "흠, 그런데 왜 나랑 똑같은 악당이랑 싸워야 하지?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "나는 부자는 아니지만, 내가 가진 모든 귀중품을 기꺼이 드리겠소! 내 아내를 풀어주고 나에게 데려와 준다면, 당신에게 보수를 지급하겠소\n "+FindRussianMoneyString(sti(npchar.quest.money))+", 그리고 내 보석 전부.";
			link.l1 = "좋아, 나도 끼지. 자세히 말해 봐. 그 자의 이름, 배 이름, 그리고 네 아내 이름까지.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "아니, 친구, 그 정도 적은 돈으론 못 해. 미안하지만...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "그녀의 이름은 "+npchar.quest.SeekCap.name+". 그리고 그 자식의 이름은 "+npchar.quest.SeekCap.capName+", 그는 계속 헤엄친다 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "똥은 떠오르고, 친구야. 선장들은 항해하지...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "그래, 그래, 정말 미안해! 나는 뱃사람이 아니야, 이해해 주길 바라...";
			link.l1 = "괜찮으니 걱정하지 마. 아무튼, 끝나는 대로 바로 돌아올게.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "정말 감사합니다! 저는 현지 교회에서 기다리고 있겠습니다. 하지만 제발 서둘러 주십시오. 아내가 정말 걱정됩니다...";
			link.l1 = "그래, 나도 그녀가 부럽진 않아.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "문제는, 내 친구에게는 영지가 없다는 거야. 그의 집은 배뿐이지. 그래서 그를 찾을 수가 없어, 항상 바다에 떠 있으니까. 그리고 쓸데없는 여행을 할 여유도 없어, 살아가려면 돈을 벌어야 하거든.";
			link.l1 = "돈이 없으면 도와줄 수 없어...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "내가 돈 줄 수 있어 "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 내가 가진 모든 보석을 줄게. 지금은 이것밖에 줄 수 없어.";
			link.l1 = "이 금액이면 나도 괜찮아. 나도 끼지. 사실, 네가 내 배에 손님으로 타도 돼. 우리가 네 친구를 찾으면 바로 만날 수 있을 거야.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "그걸로는 부족해. 다른 사람을 찾아봐.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "아니, 나는 여기 남아 있을 생각이오. 수색이 얼마나 오래 갈지 모르니 내 돈을 다 잃을 수도 있잖소. 여기서 일자리가 있으니.";
			link.l1 = "알겠소. 이제 말해 보시오, 그 친구가 누구며 어느 배에 타고 있소.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "그의 이름은 "+npchar.quest.SeekCap.capName+". 내가 알기로 그는 지휘하는 배가 있어 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "알겠소. 그 친구를 만나면 자네에 대해 전해 주겠네.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "감사합니다. 지역 교회에서 당신을 기다리고 있겠습니다.\n일이 끝나면 돈을 드리겠습니다.";
			link.l1 = "알겠소. 그럼 이만, 곧 결과를 기대하시오.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "안녕하십니까, 선장님. 아직 결과가 나왔습니까?";
			link.l1 = "네 문제가 뭐였는지 다시 말해 봐...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "내 복수가 이루어진 것 같군. 맞나?";
					link.l1 = "정확히 그렇소. "+npchar.quest.SeekCap.capName+" 죽었고 그의 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" 바다 밑바닥에 있다.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "내 아내를 찾았구나! 믿을 수가 없어! 정말 그런가?";
					link.l1 = "할 수 있소. 그녀는 내 승객이오. 원한다면 그녀를 데려가도 되오, 만약\n "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" 정말 네 아내가 맞아...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "좋은 하루입니다, 선장님. 제 동료를 찾으셨습니까?";
					link.l1 = "그래, 그리고 당신에 대해 이야기했어.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "뭐? 내가 너한테 선장님의 복수를 부탁했던 거 정말 잊은 거야? "+npchar.quest.SeekCap.capName+" 내가 노예로 지낸 1년의 대가로?";
					link.l1 = "아니, 안 했어.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "내 귀를 의심하겠군! 내가 자네에게 내 아내를 찾아 구해달라고 부탁한 걸 잊었나? 그녀는 라는 이름의 해적에게 붙잡혔네 "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "아니.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "잠깐만... 내 동료를 찾아주겠다고 한 약속, 잊은 거 아니지? "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "아니.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "훌륭해, 내 예상이 맞았군! 자, 약속한 대로 네게 주는 "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 보석도 있소. 도와줘서 고맙소.";
			link.l1 = "천만에...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "오, 맙소사! 우리를 구해주셨군요! 제발, 당신의 \n "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 보석도 있소. 그리고 우리가 영원히 그대를 위해 기도할 것임을 아시오!";
			link.l1 = "기도하고 싶으면 해라. 나는 상관없다.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "훌륭해!... 자, 받아라 "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 보석도요. 그리고 감사합니다, 선장님.";
			link.l1 = "환영하네, 친구. 잘 가게...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("안녕하십니까, 선장님. 저를 도와주실 수 있습니까?","선장님! 숙녀를 도와주실 수 있나요? 그렇게 친절하게 대해주실 수 있을까요...","선장님, 도와주세요 "+GetSexPhrase("소녀","나")+".");
			link.l1 = RandPhraseSimple("나 바쁘다.","미안해, "+GetAddress_FormToNPC(NPChar)+", 하지만 나에겐 남는 시간이 없어...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("무슨 문제야, "+GetAddress_FormToNPC(NPChar)+"?","무슨 일인지 말해 보시오, "+GetAddress_FormToNPC(NPChar)+". 내가 도와주려고 해.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "내 남편은 상인이에요. 모든 식민지에 물건을 배달하러 다니죠.\n세 달 전에 바다로 나갔는데, 아직 돌아오지 않았어요!";
					link.l1 = "그에게 무슨 일이 생긴 것 같아?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("선장님, 보아하니 용감한 선장이시군요, 완벽한 악당이기도 하고요","선장님, 보아하니 당신은 강인한 여자군요. 어떤 남자든 상대할 수 있을 것 같소.")+"...";
					link.l1 = "그런데 왜 그렇게 말하는 거지, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "선장님, 제발 도와주십시오, 부탁드립니다! 제 남편이 붙잡혔어요! 그를 구해주실 수 있나요?";
					link.l1 = "잠깐만, 이해가 안 돼. 누가 누구한테 잡힌 거야?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "모르겠어, 하지만 아직도 그가 너무 바빠서 내게 편지를 못 쓰는 거라고 믿고 싶어. 나한테 편지 한 통쯤은 보낼 수도 있었잖아; 내가 그를 걱정하는 거 알 텐데!";
			link.l1 = "바다에서는 안전하지 않아, 무슨 일이든 일어날 수 있지...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "정확해! 내가 무슨 말 하는지 알겠군. 너는 마치 \n "+GetSexPhrase("용감한 선장","용감한 소녀")+", 그래서 내 남편을 찾아달라고 부탁하고 싶어요. 보수는 드릴게요 "+FindRussianMoneyString(sti(npchar.quest.money))+", 그리고 내 모든 보석도 주겠소.";
			link.l1 = "좋아. 바다에서든 어디에서든 네 남편을 만나면 네 걱정을 전해 주지. 남편 이름이랑 배 이름을 말해 봐.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "나는 그런 적은 돈에는 관심 없어.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "그의 이름은 "+npchar.quest.SeekCap.capName+". 그는 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "알겠소. 이제 기다려야 하오. 내가 그대를 찾을 수 있도록, 대부분의 시간을 교회에서 보내도록 하시오.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("그렇게 말하는 이유는, 나리, 당신이 평소에 하던 일로 고용하고 싶어서요... 그러니까 말이지.","나를 도와줬으면 해. 여자로서 내 마음을 이해해 주길 바라.")+"한 선장이 나를 성가시게 했어. 그 자를 죽이고 싶다.";
			link.l1 = "그 불쌍한 영혼이 너한테 뭘 했는데?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "이 자식이 날 속였어. 나한테 반한 척하고, 심지어 구애까지 했지. 그 모든 짓을 한 이유가 내 남편한테서 귀중한 걸 얻으려고 한 거였어! 그리고 그놈이 원하는 걸 챙기자마자, 나한테 아무 의미도 없었다고 했어... 우리가 그냥 친구일 뿐이라고!";
			link.l1 = "흠, 어쩌면 그가 맞았던 걸까?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "내가 바보로 보여?! 내가 구애하는 거랑 쓸데없는 잡담 구분도 못할 것 같아?";
			link.l1 = "그래, 잘 알지...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "그 자식이 날 이용했어! 절대 용서하지 않을 거야!";
			link.l1 = "그래, 남자란 다 그런 법이지. 하지만 좀 진정할 수 있겠나? 별로 두려워할 일은 아니야...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "아무 일도 없다고?! "+GetSexPhrase("너는 무슨 도덕군자인 척하네, 진짜 해적이 아니잖아!","그런 상황은 한 번도 겪어본 적이 없는 모양이군! 아, 그래, 누가 그런 위험을 감수하겠어... 나는 그저 힘없는 여자일 뿐인데...");
			link.l1 = "좋아. 됐다. 나는 단지 네 의도가 얼마나 진지한지 알고 싶을 뿐이야.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "젠장, "+GetSexPhrase(" 거절당한 여자의 복수가 어떤지 너는 모르는구나 ","너는 여자니까 거절당하는 기분이 어떤지 알겠지! 나는 복수하고 싶어 ")+"!";
			link.l1 = ""+GetSexPhrase("사실이야, 이런 경험은 처음이야","글쎄, 알잖아, 걔는 그냥 좀 울고, 유리 좀 깨고 나면 끝나곤 했지\n")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("운이 좋다고 생각해라. 기대를 저버리고 속인 여자는 마치 분노의 화신, 치마 입은 악마지! 세상 그 무엇도 그녀의 분노를 누그러뜨릴 수 없어\n","그리고 나는 그녀와 달라. 내 분노를 누그러뜨릴 수 있는 건 아무것도 없어")+"!\n그래서 네가 직접 그 놈을 죽였으면 한다. 그리고 죽기 전에 누가 그의 죽음을 사주했는지 반드시 알게 해야 해...";
			link.l1 = "흠, 뭐라고 해야 할지 모르겠군... 그런데 얼마 줄 건데?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "내가 가진 건 전부야. 내 보석도 줄게, 그리고 "+FindRussianMoneyString(sti(npchar.quest.money))+"! 거래할래?";
			link.l1 = "흥미롭군. 그의 이름과 배 이름을 말해 봐.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "흥미 없어. 간다.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "그 악당의 이름은 "+npchar.quest.SeekCap.capName+" 그리고 그는 ~을 타고 항해한다 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "이미 끝난 일이지, "+GetAddress_FormToNPC(NPChar)+". 현지 교회에서 나를 기다리게. 잠시 마음을 가라앉히길 바라네...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "설명드릴게요. 문제는 제 남편이 평범한 사람일 뿐인데 해적들에게 붙잡혔다는 거예요! 그놈들은 모두를 죽였고, 아무도 살려두지 않았어요...\n";
			link.l1 = "선장이 감히 저항한 것 같군. 그렇지 않았다면 선원들은 살려줬을 거야.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "그럴지도 모르지만, 내 남편은 순진한 사람이에요. 그는 거기서 그저 승객이었을 뿐이에요. 목숨을 구하려고 부자라고 말할 수밖에 없었어요. 해적들은 그를 살려줬고, 화물창에조차 가두지 않았어요.";
			link.l1 = "그걸 어떻게 아는 거지?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "그가 내게 편지를 보냈어. 자신은 괜찮고, 다른 죄수들과 달리 선실에 감금되어 있다고 썼지.";
			link.l1 = "그래서 뭘 할 생각이야? 이렇게 계속될 순 없어. 조만간 해적들이 저 자의 속셈을 간파할 거야.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "너도 해적인가? 그래, 그래, 알아... 제발 부탁이야, 우리를 도와줘, 내 남편을 구해 줘! 그는 그 해적선을 묘사했고 선장의 이름도 적어 놨어. 네가 그들을 찾는 건 어렵지 않을 거야!";
			link.l1 = "네가 생각하는 것만큼 쉽지 않아. 모든 포로는 네 남편을 잡은 선장의 정당한 전리품이야, 게다가 시간도 걸릴 거다.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "하지만 적어도 시도는 해볼 수 있잖아! 게다가 찾을 시간도 충분해. 내 남편은 바보가 아니고, 구세계에서 온 상인인 척하고 있어서 그 해적들이 당장은 돈을 요구하지 않아. 그를 구해주면 내가 가진 모든 것을 줄게!";
			link.l1 = "그래서 너한테 뭐가 있지?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "별거 아니야, "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 내 모든 보석들까지... 하지만 나는 영원히 그대의 영혼을 위해 기도할 것이오!";
			link.l1 = "그래, 그건 정말 별거 아니군... 좋아, 도와줄 준비가 됐어.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "미안하지만, 나한테는 이걸로는 부족해.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "감사합니다, 정말 고마워요!";
			link.l1 = "내가 성공하면 나한테 고마워하게 될 테니, 그만해. 남편 이름이랑 그 해적들에 대해 아는 걸 전부 말하는 게 좋을 거야.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "그의 이름은 "+GetFullName(forName)+". 선장의 "+npchar.quest.SeekCap.capName+", 그는 계속 항해한다 "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" 이름이 붙은 "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "알겠소. 이제 그대는 내가 수색에 성공하기를 기다리며 희망을 가져야 하오. 교회에 머물면서 기다리고 기도하시오 ...\n";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "아, 선장님, 이렇게 다시 뵙게 되어 정말 기쁩니다! 이제 말씀해 주시죠, 제 부탁과 관련해서 무슨 소식이 있습니까?";
			link.l1 = "흠, 다시 한 번 말해 줘, "+GetAddress_FormToNPC(NPChar)+", 무슨 일 말씀하시는 거요?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "아, 선장님, 남편에게서 편지를 받았어요! 당신이 그를 찾았다고 하네요.";
					link.l1 = "그래, 맞아, "+GetAddress_FormToNPC(NPChar)+". 당신 남편, "+npchar.quest.SeekCap.capName+", 건강하게 잘 지내고 있어. 그냥 너무 바쁠 뿐이야...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "무슨 말이오, 선장? 내가 부탁한 일은 끝냈소? 선장 "+npchar.quest.SeekCap.capName+" 죽었어?";
					link.l1 = "그래, 그는 죽었어, "+GetAddress_FormToNPC(NPChar)+". 나는 그에게 자기 죽음에 책임이 있는 사람이 누구인지 말해줬어. 그가 마지막으로 들은 말이 바로 네 이름이었지.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "당신이 제 남편을 구하셨군요! 제발, 정말이라고 말해 주세요!";
					link.l1 = "그래, 맞아. 그는 지금 내 배에 있어. 네가 원하면 볼 수 있어. "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"정말 네 남편이야...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "정말 내 남편을 찾아주겠다고 약속한 걸 잊은 거야? 그의 이름은 "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "아, 그래, 물론이지... 잊지 않았어.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "이해가 안 돼! 내 원수인, "+pchar.name+"라는 선장을 반드시 죽여야 한다는 걸 잊은 거야? "+npchar.quest.SeekCap.capName+"?!";
					link.l1 = "아, 제발, 당연히 안 그랬지. 주문은 처리 중이니, 잠시만 기다려...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "제기랄, 선장님, 내 남편을 풀어주겠다는 약속 잊으신 겁니까?";
					link.l1 = "나는 못 봤어. ... '기다리고 기도하라!' 기억나지? 그냥 기다려, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "오, 신이시여, 정말 감사드립니다! 그리고 그래, 네 것을 가져가라 "+FindRussianMoneyString(sti(npchar.quest.money))+". 그리고 다시 한 번 고맙소!";
			link.l1 = "흠, 별말씀을...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "훌륭해! 자, 네 물건을 가져가. "+FindRussianMoneyString(sti(npchar.quest.money))+" 그리고 보석들. 잘 가라...";
			link.l1 = "안녕히 가시오. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "틀림없어요, 바로 그 사람이에요! 오, 신이시여, 선장님, 정말 감사드립니다. 받아주십시오, 당신의\n "+FindRussianMoneyString(sti(npchar.quest.money))+". 내 평생 매일 당신을 위해 기도하겠소!";
			link.l1 = "좋아...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "동료에게 인사하지. 뭐 원하는 거 있나\n"+GetSexPhrase(", 친구 ",",  아가씨")+"?";
					link.l1 = "당신의 이름은 "+GetFullName(npchar)+", 맞지?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "그래, 맞아!";
			link.l1 = "안됐군. 내가 이름 하나 알려줄 테니, 잘 기억해둬."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". 그 사람 기억나지?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "흠, 그래...";
			link.l1 = "이제 들어, 녀석. 그가 너한테 엄청 화가 났어. 자유인을 노예로 팔아넘긴 대가를 치를 때가 됐지.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "돈을 내라고?! 무슨 개소리를 하는 거야?";
			link.l1 = "내가 지금 이 자리에서 너를 죽이겠다는 말이다.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "생각해 봐, 넌 누구를 위해 일하고 있는 거야?! 이 자식은 비열한 놈이고, 설탕 농장이 제자리야!";
			link.l1 = "글쎄, 이건 네가 신경 쓸 일이 아니야. 이제 네가 저지른 일에 대해 대가를 치러야지!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "호! 나는 평소처럼 한 가지 방법으로만 대답하겠다!";
			link.l1 = "계속해...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "뭘 원하지?";
			link.l1 = "묻고 싶은 게 있는데, 승객을 태우나? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "그게 너랑 무슨 상관이야?";
			link.l1 = "그냥 물어본 거야.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "그냥 묻는 거야... 이봐, 내가 기회를 줄 때 얼른 꺼지는 게 좋을 거다. 너 마음에 안 들어!";
			link.l1 = "알았어, 알았어, 진정해. 나 간다...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "우린 이미 얘기했으니, 더 이상 나를 시험하지 마!";
			link.l1 = "안 해.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "안녕하시오, 동료! 뭐 필요한 거라도 있소?";
			link.l1 = "알고 싶은데, 너 그 여자를 데려가지 않았어? "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" 이름이 붙은 "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "헤헤, 맞아, 걔 내 선실에 있어! 게다가 몸매도 끝내주더라... 근데 왜 물어보는 거야?";
			link.l1 = "이봐, 이 여자는 유부녀야. 이러면 안 돼.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "그래서 뭐? 난 그녀가 좋으니까 그게 다야. 그녀 남편이라고 해서 어떤 누더기 바보가 우리 사이에 끼어드는 건 절대 못 참아!";
			link.l1 = "이런 일은 형제단이 결코 용납하지 않는다는 걸 알아둬라. 그리고 네가 한 짓을 어떤 이들이 알게 되면, 검은 표식이 네게 전달될 거다.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "나한테 설교라도 하려는 거야?";
			link.l1 = "진정해, 그냥 관심 좀 보인 것뿐이야... 잘 가.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "그 여인에 대해서는 이미 얘기했어. 더 이상 그 일로 이야기하고 싶지 않아!";
			link.l1 = "뭐든지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "내 갑판에 동료를 맞이하게 되어 기쁘군! 무슨 일로 왔나?";
			link.l1 = "네가 어디에서 여자를 납치했는지 알고 싶군 "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" 라는 이름의"+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "헤헤, 맞아, 걔 내 선실에 있어! 뜨거운 아가씨야, 다리도 끝내주고!... 근데 왜 물어보는 거지?";
			link.l1 = "이봐, 이 여자는 유부녀야. 이러면 안 돼.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "그래서 뭐? 난 그 여자가 좋아, 그게 다야. 걔 남편이라고 해서 그런 누더기 녀석이 우리 사이에 끼어드는 건 절대 못 참아!";
			link.l1 = "이런 일은 형제단이 결코 용납하지 않는다는 걸 알아둬라. 그리고 네가 한 짓을 어떤 이들이 알게 되면, 검은 표식이 너한테 날아올 거다.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "나한테 설교라도 하려는 거야?";
			link.l1 = "진정해, 그냥 관심 좀 가져봤을 뿐이야... 잘 있어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "나한테 뭘 원해, 이 쓰레기야?!";
			link.l1 = "나는 네가 남편에게서 빼앗은 그 여자를 데리러 왔다. 기억해라\n "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? 그녀의 이름은 "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "젠장! 넌 그녀를 절대 못 볼 거야, 네 귀를 직접 볼 수 없는 것처럼!";
			link.l1 = "멍청이. 거울에 비친 네 놈 것들이 다 보여. 그리고 이제 네 것도 잘라버릴 거야!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "너 누구야?";
			link.l1 = "안녕하세요. 당신 남편이 부탁해서 당신을 데리러 왔소. 이제 당신은 자유이니, 남편에게 데려다주겠소.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "꿈이냐?! 정말이냐?!";
			link.l1 = "그렇소, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "주님을 찬양하라! 난 준비됐어, 여기서 벗어나자!";
			link.l1 = "그래, "+GetAddress_FormToNPC(NPChar)+", 남편에게 안전하게 돌아갈 준비를 하시오.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "안녕! 육지에서 동료를 만나 반갑군...";
			link.l1 = TimeGreeting()+", 너랑 볼일이 좀 있다.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "듣고 있다.";
			link.l1 = "네 동료가 너를 찾고 있다. 너희는 함께 항해해서 구세계에서 여기까지 왔지."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+", 기억하지?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "하, 당연히 알지! 그런데 지금은 어디에 살고 있지?";
			link.l1 = "In "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " 고마워! 있잖아, 난 네가 해적인 줄 알았어!";
			link.l1 = "그래, 맞아. 뭐, 그런 셈이지. 아니면 아닐 수도 있고. 하지만 어쨌든 오늘은 기분이 좋으니 걱정할 필요 없어. 잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "문제라도 있나요? 미안해요, 제가 좀 긴장해서...";
			link.l1 = "괜찮아, 친구.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+". 나한테 뭘 원하지? 난 그냥 평범한 상인일 뿐이고...";
			link.l1 = "알아, 친구. 너무 걱정하지 마, 건강에 안 좋다더라. 너랑 볼일이 좀 있어.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "무슨 일인데?";
			link.l1 = "네 친구가 너를 찾고 있어. 이름은 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". 그 사람 알아?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "오, 드디어 오셨군요! 정말 다행입니다... 이렇게 무례하게 맞이해서 미안합니다만, 처음엔 당신이 해적인 줄 알았거든요.";
			link.l1 = "나야. 뭐, 그런 셈이지. 아니면 아닐 수도 있고. 어쨌든 오늘은 기분이 좋아서 걱정할 필요 없어. 누가 너한테 전할 말을 부탁해서 내가 전해줬다. 네 동료는 \n에 살고 있어 "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "정말 대단하군! 당신은 참으로 명예로운 사람이야. 고마워!";
			link.l1 = "천만에. 잘 가고, 몸조심해라, 친구.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "안녕. 뭐 필요한 거 있어?";
			link.l1 = "당신의 이름은 "+GetFullName(npchar)+", 맞지?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "그래, 나야.";
			link.l1 = "어리석게 들릴 수도 있지만, 당신 부인이 당신을 걱정한다고 전해 달라고 했소.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "하! 알겠군... 사실 나는 너무 바빴어. 이익이 되는 제안이 많아서 아내가 너무 걱정한다고 해서 잠재적인 수입을 놓칠 수는 없지.";
			link.l1 = "하지만 적어도 그녀에게 편지를 써서 무사하다고 전할 수는 있잖아.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "그래, 네 말이 맞아. 내가 즉시 그녀에게 편지를 쓰겠네! 우리 집안 일에 참여해 줘서 고맙네!";
			link.l1 = "천만에, 친구.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "좋은 하루입니다. 무엇을 도와드릴까요?";
			link.l1 = "당신의 이름은 "+GetFullName(npchar)+", 맞지?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "그래, 나다.";
			link.l1 = "어리석게 들릴 수도 있겠지만, 당신 부인이 당신을 걱정한다고 전해 달라고 했소.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "푸, 젠장! 그 유명한 현상금 사냥꾼이 날 잡으러 온 줄 알고 겁먹었잖아. 외눈박이 스티브라지. 다행히 내가 착각한 거였군\n있잖아, 나는 일 때문에 너무 바빠서 아내한테 신경 쓸 틈도 없어. 항상 이득이 되는 제안이 들어오는데, 아내 걱정 때문에 그걸 거절할 순 없지.";			
			link.l1 = "당신 말이 맞소, 물론. 하지만 적어도 그녀에게 편지를 써서 잘 지내고 있다고 전할 수는 있지 않겠소.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "그래, 네 말이 맞아. 제일 처음 들르는 항구에서 바로 그렇게 하겠네... 우리 집안 일에 관여해줘서 고맙네!";
			link.l1 = "천만에, 친구야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "감사의 말씀을 드리오, 선장님...";
			link.l1 = "천만에.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "이 마을에서 뵙게 되어 반갑습니다, 선장님. 저에게 필요한 게 있으십니까?";
			link.l1 = ""+GetSexPhrase("있잖아요, 선장님... 휴, 뭐라고 말해야 할지 모르겠어요!","그래, 있다.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("있는 그대로 말해.","재미있군, 그게 뭔데?")+"";
			link.l1 = " 너에게 물어볼 게 있어. 혹시 이름이 \n인 여자를 아나? "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "헤, 알아. 그년을 알게 된 건 재수 없었지. 바보 같은 계집애야, 내가 말해줄 수 있지...";
			link.l1 = "흠... 그래, 그리고 이 어리석은 계집애가 나더러 너를 죽이라고 했지. 그게 다야....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "말도 안 돼.";
			link.l1 = ""+GetSexPhrase("동의하오. 실례하지만, 자네 머리에는 현상금이 걸려 있네","그렇지 않아. 현상금이 걸려 있어\n")+". 그리고 내가 그걸 가져가겠다.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "호호!... 농담하는 거요, 선장?";
			link.l1 = ""+GetSexPhrase("아니, 친구.","하려던 것도 아니었어!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("너는 내 친구가 아니야, 이 바보야! 너 따위가 무슨 선장이냐. 넌 그저 이 어리석은 분노의 장난감일 뿐이야!","젠장! 악녀 하나가 또 다른 악녀를 고용했군! 도대체 이 세상에 무슨 일이 벌어지고 있는 거야?")+"!";
			link.l1 = ""+GetSexPhrase("입 조심해, 이 쓰레기야.","너는 그녀를 이용했으니, 그녀가 복수하려고 마음먹었다고 해서 놀라지 마라.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("신경을 건드렸나?","여자들끼리의 연대?!")+"";
			link.l1 = "이제 끝내자!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "나는 이미 너랑 얘기했어. 꺼져, 이 바보야!";
			link.l1 = "멍청이?! 좋아, 그럼...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "배에 타서 반갑소, 선장. 무슨 일로 오셨소?";
			link.l1 = "당신에게 물어볼 게 있어. 혹시 이름이 이런 여자를 알아? "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "헤, 알아. 그 여자를 알게 된 건 재수 없었지. 바보 같은 계집애야, 내가 장담하지...";
			link.l1 = "그래, 그리고 이 어리석은 계집애가 나더러 너를 죽이라고 했지.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "선장, 웃기지 마시오. 나와 진지한 볼일이 없다면, 이만 작별을 고하겠소.";
			link.l1 = "그럼 이만 작별이오. 하지만 내가 한 말을 곰곰이 생각해 보시오.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "당연하지, 선장님, 달리 어떻게 되겠어?!";
			link.l1 = "잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "이 일에 대해 더 이상 이야기하고 싶지 않소, 선장. 이건 너무 터무니없군.";
			link.l1 = "뭐라고 하든지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "여기서 대체 무슨 일이 벌어지고 있는 거야?! 왜 내 배를 공격한 거지?";
			link.l1 = "라는 이름의 숙녀의 부탁으로 "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". 그녀를 아나?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "이런 젠장! 믿을 수가 없군...";
			link.l1 = "해야지! 여자들 몰라, 이 친구야? 물 수도 있다고.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "글쎄, 이렇게 허무하게 죽을 생각은 없어. 이야기해줘서 고마워, 이제 좀 힘이 돌아왔어.";
			link.l1 = "그거 너한테 아무 소용 없어.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "배에 타서 반갑군. 내가 도와줄까?";
			link.l1 = "할 수 있지. 나는 이름이 같은 남자를 찾고 있어 "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "이 남자는 내 포로다. 나는 그를 몸값 받고 풀어줄 생각이다.";
			link.l1 = "난 그를 데려가고 싶어.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "유감이지만, 그건 불가능하오. 더 할 말이 없다면 내 배에서 나가 주시오.";
			link.l1 = "좋소, 선장님, 말씀대로 하겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "이미 내 포로에 대해서는 이야기했지. 달라진 건 없어.";
			link.l1 = "그렇군...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "만나서 반갑소. 무엇을 도와드릴까?";
			link.l1 = "그래도 된다. 나는 이름이 같은 남자를 찾고 있다 "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "이 남자는 내 포로다. 나는 그를 몸값 받고 풀어줄 생각이야.";
			link.l1 = "나는 그를 데려가고 싶어.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "미안하지만, 그건 불가능해.";
			link.l1 = "안타깝군...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "젠장! 이게 뭐야?!";
			link.l1 = "네 죄수 중 이름이 "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "하! 절대 안 돼, 내 시체를 밟고 가라지!";
			link.l1 = "물어봤으니...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "너 누구야?";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+". 걱정 마, 내가 당신을 아내에게 데려다줄 거야.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "젠장, 이거 꿈꾸는 거 아니야?";
			link.l1 = "그렇지 않다고 장담할 수 있어... 뭐, 이제 다 끝났으니 여기서 벗어나자.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("나 너무 지쳤어, 도와줘.","이렇게는 더 이상 살 힘이 없어!"),RandPhraseSimple("이 일 때문에 우리가 죽어나가고 있어.","저 빌어먹을 경비병들 때문에 내 등에 가죽 한 점도 안 남았어!"));				
				link.l1 = RandPhraseSimple("정말 안타깝군.","그래, 인생 참 더럽지.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "오, 선장님, 여기 앉으시오. 내가 한턱 내겠소!";
					link.l1 = "기꺼이.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "안녕하세요, 선장님. 당신이 선장 맞지요? 혹시 해군 선장이기도 한가요?\n그래요, 분명 칼 솜씨도 좋으시겠지요. 내일 죽게 생긴 내 한심한 아들과는 달리 말이오... 다 그 음탕한 놈이 내 아들이 마음에 둔 아가씨를 넘봐서 그런 거요!";
						link.l1 = "그래, 나는 선장이야. 내 검 덕분에 이미 여러 번 목숨을 건졌지. 그런데 네 우울한 말의 나머지는 뭐지? 설명 좀 해볼래?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "안녕하십니까, 선장님. 말씀해 보시지요, 혹시 해적이신가요? 아, 물론 아니겠지요! 당신은 아니군요. 해적들은 끔찍하게 생겼고, 짐승처럼 굴며, 그 악취란...";
						link.l1 = "해적들에게 원한이라도 있나?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "이봐, 너! 그래, 너 말이야, 예의가 어디 갔어? 도대체 왜 여기 서서 나 귀찮게 하는 거야? 아니, 저 꼴 좀 봐라, 진짜 바보 같군! 너한테 말하는 거야! 비켜! 여기 외지인들이 너무 많아!";
							link.l1 = "진정해, 귀찮게 하려던 건 아니야. 미안하다.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "입 조심해라, 안 그러면 네 혀를 잘라버릴 테니, 나리.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "안녕하십니까, 선장님. 부탁드릴 일이 있습니다. 명예로운 분이라면 그냥 지나치지 않으시겠지요.\n바로 본론으로 들어가겠습니다. 한 달 전, 우리 선술집에 귀족이 머물렀습니다. 그런데 그 자는 방탕하고 못된 놈이었습니다! 게다가, 살인자이기도 합니다!";
						link.l1 = "내 기억이 맞다면, 죄 없는 자를 죽인 죄는 교수형이야. 방탕한 놈이고 사생아라는 것도 법정에선 별 도움이 안 될 거다. 내가 맞지?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "선장님, 잠깐만요, 제발 부탁드립니다. 당신은 저보다 훨씬 뛰어난 검객으로 보입니다. 그래서 제 대신 해주셨으면 합니다.";
						link.l1 = "흥미롭군. 계속해봐.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "제발, 부탁이오, 가지 말아주시오! 잠깐만... 이렇게 용감한 군인인 자네의 도움이 꼭 필요한 일에 불쌍한 사람 하나 도와줄 생각 없겠나?\n사실 내 이웃과 이 동네 포도밭 문제로 다투었는데, 그 이웃이 밀수업자들과 거래한다는 의심을 받고 있소. 그래, 그래, 심지어 해적들과도 뭔가 꾸미고 있을지 몰라—아니면 어떻게 그렇게 순식간에 큰돈을 벌 수 있었겠소?\n작년만 해도 바크 한 척밖에 없던 자가, 이제는 내 포도밭까지 빼앗으려 한다오, 들리나?! 내 포도밭을!";
						link.l1 = "네 포도밭이 안됐구나. 진심이야. 잘 가라.";
						link.l1.go = "exit";
						link.l2 = "실례지만, 현지 당국에 접근할 수는 없습니까?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "선장님, 선장님, 제발 부탁드립니다! 순진한 처자의 명예를 지켜주십시오!";
						link.l1 = "이런 데 신경 쓸 시간 없어, 이쁜이. 딴 사람 찾아봐...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "안녕하세요, 아가씨. 그렇게 떨지 마시오! 무슨 일이 있었소?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "버그다. 개발자들에게 알려 줘.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "선장님, 우리 주둔지의 장교 한 명이 나를 대놓고 따라다니고 있습니다. 그자가 나에 대해 더럽고 추잡한 소문을 퍼뜨리는 걸 분명 들으셨을 겁니다. 나를 망신주려고 애쓰고 있어요!\n아아, 내 결백을 지켜줄 친구도 하나 없으니 절망스럽습니다! 오, 맙소사, 저 사람이에요! 도와주세요!";
			link.l1 = "걱정 마, 내가 끝까지 해낼 거야.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "아, 여기 있었군, 아가씨! 또 다른 기사님이신가? 언제쯤 정착할 생각이야? 아마 영원히 못 하겠지... 그냥 창관에서 일해라, 그게 너한테 제일 어울리는 곳이니까...";
			link.l1 = "장교, 입 함부로 놀리면 내가 특별한 방법으로 그 입 다물게 해줄 테니까!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "흠... 너 누구냐? 아-아, 바다에서 단련된, 작은 배의 용감한 선장이구나, 맞지? 그런데 어쩔 셈이냐, 바다의 새끼 녀석아?";
			link.l1 = "이 여인은 내 친구다! 그리고 너한테도 한 방 먹여주지!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "뭐?! 이 일로 나한테 덤비려는 건 아니겠지...";
			link.l1 = "그만해! 두 시간 후에 등대 근처에서 기다릴 테니 와라. 그리고 칼 가져오는 거 잊지 마라!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "아, 나는 모든 걸 다 알고 있소, 나리! 내가 당신께 얼마나 감사한지 상상도 못 하실 겁니다! 주님께서 당신을 지켜주시길!";
			link.l1 = "도와줄 수 있어서 기쁘네. 행운을 빌어!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "아, 너도 다른 놈들이랑 똑같구나, 내버려 둬!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "오, "+GetAddress_Form(NPChar)+"... 감히 기대도 못 하지만, 이번에는 당신의 검이 우리 가족을 지켜줄 수 있을까요?\n말씀드렸듯이, 제 아들은 결투사가 아니지만, 새벽에 결투를 해야 합니다. 아, 그 여인과 그 빌어먹을 명예만 아니었어도...\n하지만 그는 물러설 수 없었고, 이제는 파멸이 기다릴 뿐입니다. 이해하시겠죠? 저는 절박합니다—그 아이는 제 하나뿐인 아들이자 상속자입니다. 그러니 간청합니다, 새벽 전에 제 아들에게 결투를 신청한 그 악당을 죽여 주십시오. 반드시 보답하겠습니다, 맹세합니다!\n그 남자는 선술집에 있을 겁니다 "+sTemp+" - 저기, 저런 놈들이 한가할 때 어슬렁거리는 곳이야... 제발 부탁이야...";
			link.l1 = "난 너도 네 아들도 신경 안 써. 날 놔줘!";
			link.l1.go = "exit";
			link.l2 = "흠... 그냥 이렇게 끝내자는 건가? 좋아, 어떻게 끝나는지 두고 보자.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "정말 제 아들을 도와주실 건가요? 오, "+GetAddress_Form(NPChar)+"! 당신과 당신의 행운을 위해 기도하겠습니다!";
			link.l1 = "그거야 문제될 거 없지... 나 좀 기다려!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "도대체 나한테 뭘 원해? 여기서 쉬고 있으니 귀찮게 하지 마. 빈자리가 많고, 말 들어줄 사람도 많으니, 나 좀 내버려 둬, 나리!";
			link.l1 = "안타깝지만, 쉴 날은 더 좋은 때까지 미뤄야겠군.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "뭐라고?! 네가 뭔데 나한테 이래라저래라야?!";
			link.l1 = "나를 잊었냐, 응? 하지만 나는 너를 기억하지! 그리고 내 말은, 너 같은 악당들이 존재만으로도 우리 세상을 더럽힌다는 거야!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "아?! 이봐, 뱃사람! 너 완전히 취했구나! 난 너를 오늘 처음 본다! 하지만 네 행동을 그냥 넘기진 않겠다! 이게 네 비참한 목숨을 건질 마지막 기회다! 지금 변명이나 해라, 이 뚱뚱한 청어 자식아, 그러면 네 건방진 말은 잊어주지!";
			link.l1 = "나는 변명은 명예로운 사람에게만 하지, 더러운 돼지들에게는 안 해!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "뭐야, 젠장?! 시비 걸려고 왔냐, 변소 벌레 녀석?";
			link.l1 = "네 더러운 입을 네 말로 막아주마, 이 쥐새끼야! 두 시간 뒤 등대 근처에서 기다릴 테니, 허리춤에 차고 다니는 그 녹슨 고물도 꼭 챙겨와라!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "하! 내가 거기 갈 거야!";
			link.l1 = "곧 보자!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "오, 너였구나! 살아 있네, 그 말은...";
			link.l1 = "그래, 맞아. 그리고 네 아들은 내일 아침에 결투할 필요 없어...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "이렇게 좋은 날이 또 있나! 아내에게 이 기쁜 소식을 전하러 가야겠어!\n선장님, 운명이 직접 당신을 내게 보내 도와주었소. 자, 이 동전을 받아 주시고 우리 가족의 감사를 받아 주시오!";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "꺼져, 애들 죽인 놈아!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "나? 나는 하느님께 감사하게도 괜찮지만, 내 여동생은 그렇게 운이 좋지 않아. 그녀는 선술집에서 일하고 있어.\n그곳에 자주 들르는 사략선장이 있는데, 아주 위험한 놈이야. 해적이지! 그 자의 배는 적어도 일주일은 바다에 떠 있었어. 그 남자는 술을 마시고, 사람들을 위협하고, 이성적으로 말하려는 자는 누구든 죽이겠다고 협박해. 가장 끔찍한 건 내 여동생에게 그놈이 자기 더러운 욕망을 들어주지 않으면 어디로든 끌고 가버리겠다고 자랑했다는 거야!\n어떻게 해야 할지 모르겠어! 관리들은 하녀 하나쯤은 신경도 안 쓰고, 나 같은 평범한 시민들은 그 사략선장이 두려워. 제발, 그놈을 어떻게 좀 해줘!";
			link.l1 = "나는 선술집에서 취객을 달랠 시간 없어. 그런 일은 사령관한테 말해 봐. 그런 문제 해결하라고 월급 받는 사람이니까.";
			link.l1.go = "exit";
			link.l2 = "흠, 위협적인 사략선인가? 좋아, 내가 처리하지.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "아, 고마워요, 선장님! 분명히 선장님 말씀이라면 그도 뱃사람이 뱃사람 말을 듣듯 들을 거예요! 제발 제 여동생을 완전히 내버려두게 해 주세요! 저희가 부자는 아니지만, 수고에 대한 보상은 충분히 드릴게요!";
			link.l1 = "좋아, 좋아... 네 문제 해결하러 가는 중이야. 기다려!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "그래서 뭐? 그 해적하고 얘기해 봤어? 우리를 내버려둔다고 했어?";
			link.l1 = "잠깐만 기다려. 내가 알아서 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "뭐야, 뭘 원해? 여기서 쉬고 있는 거 안 보여?";
			link.l1 = "오, 오... 맥주잔의 대군주, 아가씨들을 훔치는 자, 이 작은 마을의 폭풍이 직접 나타났군, 맞지? 그런데 마을 밖에서도 그렇게 용감할 수 있을까? 등대 근처에서, 결투다, 두 시간 뒤에?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "오호호! 영웅인 척하는 거냐? 뭐, 친구야, 오늘 기분 좋으니까 봐준다. 가서 에일이나 몇 잔 사 와!";
			link.l1 = "나는 네 친구가 아니야. 너 같은 바보한테 다시 말해줘야겠냐? 선술집에 나타날 때처럼 결투에도 용감하게 나올 수 있겠어?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "나한테 덤비는 거냐?! 너 뭐 잘못됐냐? 인생이 지겨워서 죽고 싶은 거냐, 이 쓸개 빠진 놈아? 좋아, 그게 네 진짜 바람이라면, 내가 등대까지 걸어가서 네 창자를 꺼내놓고, 이 빌어먹을 선술집도 박살 내주마!";
			link.l1 = "말은 싸지만, 칼은 비싸니 꼭 챙겨 와라!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "그래서 뭐? 그 해적이랑 얘기해 봤어? 이제 우리를 내버려 둘 거야? 내 여동생이 그러는데, 그 사람이 선술집을 나가고는 돌아오지 않았대...";
			link.l1 = "그래, 만났지. 그 녀석이 좀 무례하긴 했지만, 내 논리는 충분히 합리적이고 설득력 있었어. 이제 네 여동생은 아무것도 두려워할 필요 없어.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "이게... 끝난 건가? 이제 마음 놓고 숨 쉴 수 있는 거야? 고마워요, 선장님! 그런데... 그 놈은 어디 있죠??";
			link.l1 = "그... 그는 자기 배에 있어. 이 마을을 가능한 한 빨리 떠나기로 했어.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "이 식민지 시민들에게 큰 도움을 주었소! 자, 이 보상을 받으시오! 그리 크진 않지만, 내 친구들 모두의 존경을 얻게 될 것이오. 그리고 믿으시오, 내 친구들은 아주 많으니!";
			link.l1 = "감사하오! 그대와 그대 누이에게 행운이 있기를. 그녀가 훌륭한 사내와 혼인하길 바라오. 안녕히 가시오!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "오, 정말이냐? 그래서 어떻게 나를 막을 셈이지?";
			link.l1 = "내 검으로지, 당연하지. 너처럼 건방진 돼지에게는 그 방법밖에 어울리지 않으니까.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "훌륭해! 두 시간 후에 등대 근처에서 기다리고 있겠소.";
			link.l1 = "좋아! 꼭 갈게.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "길 비켜, 겁쟁이 놈아!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "선장님, 그 자식 만만치 않습니다. 톰, 내 오랜 친구가 그놈과 결투하다 죽었어요. 카드 사기로 몰렸지만, 정말 결백했어요, 맹세합니다. 그런데도 총독은 그 빌어먹을 결투에 죄가 없다고 했죠.";
			link.l1 = "흠... 이건 다 네 친구 잘못이야. 카드 사기는 건강에 안 좋게 끝날 수도 있지.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "그래? 지난 2주 동안 우리 마을에 카드 사기꾼이 벌써 네 명이나 있었어. 그리고 전부 우리 귀족 나리한테 사기를 치려 했다고? 그게 뭘 의미하는지 알겠어? 내 말은, 그 귀족 나리가 바로 카드 사기꾼이라는 거야. 못 믿겠으면 직접 가서 확인해 봐.";
			link.l1 = "그 자와 내기하겠다고? 아니, 난 도박 같은 건 싫어. 절대 안 돼.";
			link.l1.go = "exit";
			link.l2 = "그래, 그렇게 하지... 뭔가 여기 아주 잘못됐어.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "선장님, 제 친구들과 저는 그 귀족을 밝혀낼 자에게 돈을 모았습니다. 그리고 그 자가 저지른 모든 짓에 대한 복수도 할 생각입니다. 일이 끝나면 당신께 보상을 드리려고 마을에서 기다리고 있겠습니다.";
			link.l1 = "네 말이 사실이라면 그렇게 하겠다.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "경의를 표합니다, 나리! 귀하께서는 귀족이신 듯하고... 어쩌면 도박꾼이신가요? 한 판 하시겠습니까?";
			link.l1 = "좋아! 판돈 얘기나 해보자. 50코인 어때?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "농담하는 거야? 너 그거 없잖아!";
				link.l1 = "네 말이 맞아...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "판돈은 상관없어, 우리는 그냥 도박을 할 거야. 그게 제일 재밌지. 이 동네 멍청이들 덕분에 카드가 어떻게 생겼는지도 거의 잊어버릴 뻔했네.";
				link.l1 = "좋아, 시작하자.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "그래서 판돈은 50코인이다.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "잠깐만, 이게 뭐지?.. 말도 안 돼! 나리, 당신은 사기꾼이오! 내 동전 돌려줘!";
			link.l1 = "나를 비난하려면 확실한 근거가 있어야 할 텐데,  "+GetAddress_FormToNPC(NPChar)+". 지금 당장 저놈들을 쏘는 게 좋을 거야, 아니면 결투다!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "아, 그냥 그렇게? 좋아, 결투다! 오늘, 두 시간 뒤에, 등대 옆에서 보자!";
			link.l1 = "거래 성사!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "새 소식 있소, 선장?";
			link.l1 = "네 말이 맞았어, 나도 속임수 썼다고 누명 씌워서, 결국 그 자식이랑 결투해서 베어버렸지.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "이제 알겠지? 내가 그럴 줄 알았어! 나랑 내 친구들 모두 정말 고마워! 자, 여기 보상이다, 선장.";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "내가 여기 온 이유가 검술 교사 자리에 지원하려고 왔다는 말 했던가? 아니라고? 음, 이 지역 총독이 조카를 가르칠 교사를 찾고 있는데, 내게 딱 맞는 자리야. 이 예술의 기초는 알고 있지만, 실제로 해본 적은 없어.\n거의 일자리를 따낸 셈이었는데, 알고 보니 이 동네 상인이 곤경에 처했다더군. 위험해 보이는 놈이 그를 위협하고 있대. 총독이 내 전문성을 시험해 보겠다며 이 문제를 해결하라고 명령했지.";
			link.l1 = "그럼 해라. 잘 가라.";
			link.l1.go = "exit";
			link.l2 = "이 악당이 상인에게서 뭘 원하는데, 그리고 나한테는 왜 필요하지?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "난 그 남자가 용병인 줄 알았어. 용병이랑은 언제든 흥정할 수 있잖아. 옛 빚이든 뭐든... 하지만 그는 상인을 계속 압박하려는 의지가 확고했어. 그래서 너한테 부탁하려 했지. 용병에게서 상인을 구하고, 총독의 명령도 이행해주면 상인과 나 둘 다 도울 수 있을 거라고 말이야\n이 자리가 정말 필요해. 혼자서는 그 용병을 쫓아낼 수 없어. 제발, 도와줘. 내가 모아둔 동전 전부를 줄게. 아니면 망신스럽게 이 도시를 떠날 수밖에 없어!";
			link.l1 = "좋아, 좋아, 도와주지... '검술의 달인' 양반.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "뭐야, 뭘 원해? 안 보여? 나 지금 바쁘잖아!";
			link.l1 = "어떤 존경받는 상인을 귀찮게 하면서 소란을 피우고 있다고!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "쳇! 또 다른 보호자냐? 매일 경비를 쓰는 것보다 나한테 돈을 주는 게 더 쌀 거다. 난 빚 받아내는 일은 좋아도 사람 죽이는 일은 별로 내키지 않아. 그러니 그렇게 영웅이라면 등대에서 만나자고, 서로 결투로 실력을 겨뤄보자. 영웅이 아니라면, 다시는 내 앞길을 막지 마라.";
			link.l1 = "거래 성사다! 거기서 기다리고 있겠어.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "너는 나보다도 더 겁쟁이인 것 같군...";
			link.l1 = "그래, 맞아.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "소식 있나, 선장?";
			link.l1 = "용병은 죽었소. 이제 그 자리가 당신 것이 되었기를 바라오?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "아이고, 선장님, 감사합니다! 보상을 받아가시고 저는 우리 총독에게 보고하겠습니다!";
			link.l1 = "안녕히 계십시오... 주인님.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "한 잔 더?";
			link.l1 = "원샷이다.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "그리고 더 있어!";
			link.l1 = "잠깐만! 어디로 그렇게 급하게 가는 거야?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "질문이고 뭐고 다 집어치워! 마셔!";
			link.l1 = "좋아, 하지만 나중에 무슨 일이 있었는지 말해줄 거지?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "정말 궁금해? 그럼 내가 아직 말할 수 있을 때 들어! 며칠 안에 난 말을 못 하게 될 거야, 죽을 테니까... 그래, 죽는다고! 다 럼 때문이지. 럼을 너무 많이 마셨고, 게다가 이 장교 놈, 악마가 내 머리 위에 떨어뜨린 게 분명해!\n내가 맨정신이었거나, 적어도 이렇게 취하지 않았다면 우리 주둔지에서 제일가는 검객, 아니 온 도시에서 제일가는 놈과 싸울 일은 없었을 거야. 하지만 이제 어쩌겠어? 난 끝났고, 망했고, 죽은 목숨이야! 내가 얼마나 바보인지...";
			link.l1 = "그래, 그건 꽤 어리석었지. 하지만 앞으로는 좀 더 현명하게 행동하겠지... 물론 결투에서 살아남는다면 말이야. 잘 가라.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "술에 취하는 것도 최선의 선택은 아니오, 장교. 분명 이 문제에 대한 해결책이 있을 것이오.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "무슨 해결책이란 거지? 탈영해서 내 명예와 장교 제복을 잃으란 말인가? 아니면 돼지처럼 도살당하지 않으려고 스스로 목숨을 끊으란 건가? 네 조언은 뭐지?";
			link.l1 = "둘 다 아니오. 내가 당신을 도와주겠소, 그리고 결투 시간이 오기 전까지 상대가 당신에게 피해를 입히지 못하도록 막아보겠소. 그를 어디서 찾을 수 있소?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "진심이야? 정말 해줄 거야?! 맹세코, 꼭 보답할게!\n그는 도시에 있어. 그의 정부가 여기 살고 있거든, 모든 장교들이 그녀에 대해 들었지만, 안타깝게도 그녀의 주소는 아무도 몰라... 내 생각엔 그도 그 근처에서 찾을 수 있을 거야.";
			link.l1 = "이제 됐다. 여기서 기다려. 내가 가서 이... '최고의 검객'이랑 얘기 좀 하고 올게.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "저한테 소식 있습니까, 나리? 좋은 소식입니까, 아니면... 그다지 좋지 않은 소식입니까?";
			link.l1 = "아직 소식이 없어. 여기서 기다려. 다 잘 될 거야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "나한테 들려줄 소식 있나, 나리? 좋은 소식인가, 아니면... 별로 안 좋은 건가?";
			link.l1 = "끝났어. 네 상대가 될 수도 있었던 자는 이제 더 이상 아무도 해칠 수 없어... 이제는 안전해. 하지만 이번 일을 교훈 삼아서 모르는 사람들에게 함부로 공격적으로 굴지 않길 바란다.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "장난하는 거 아니지? 나... 정말 고마워, "+GetAddress_Form(NPChar)+"! 여기, 내가 가진 건 전부 가져가. 이게 내 임금이야, 다 가져가!\n교훈이라고? 그래, 젠장, 네 말이 맞아! 다시는 이런 일 없을 거야, 약속할게. 그리고 한 번 더 기회를 줘서 정말 고맙다!";
			link.l1 = "좋아, 그럼. 잘 가시오, 장교...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "다시 한 번 고맙다, "+GetAddress_Form(NPChar)+", 도와줘서 고마워!";
			link.l1 = "언제든 환영이오...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "이봐, 뭐야 이게? 내 아가씨 방에서 뭐 하는 거야? 당장 나가, 아니면 내가 끌어내겠어!";
			link.l1 = "나는 내가 원하는 어디든지 다닌다네, 그리고 이런 행동으로 자네를 고발할 생각도 없어! 힘으로 하겠다고? 좋아, 해보시지!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "이런 무례가 있나! 듣도 보도 못한 뻔뻔함이군! 나리, 당신은 크게 착각하고 있소! 당장 이 집에서 나가시오, 아니면 평생 후회하게 될 것이오!";
			link.l1 = "말은 쉽지! 후회하게 될 건 네놈이지, 내가 아니야, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "정말인가? 그럼 조심하는 게 좋을 거다! 내가 이 집에서 널 죽이면 그건 살인이지. 그러니 네 죽음이 내 이름을 더럽히진 않을 거다; 명예로운 자들은 이런 문제를 등대 근처에서 해결하지!\n결투를 신청한다, "+GetAddress_Form(NPChar)+", 이 건방진 놈! 네 말에 책임을 져야 할 거다! 두 시간 뒤 결투로 하지?";
			link.l1 = "그래, "+GetAddress_FormToNPC(NPChar)+" 대담한 놈.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "그럼 제때 도착하도록 하시오. 아직 우리 신부님께 진혼미사를 부탁할 시간은 있소.";
			link.l1 = "너를 위한 진혼곡? 네놈은 페소 한 푼의 값어치도 없어. 등대에서 보자!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "꺼져!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "총독을 말하는 건가? 하! 내가 불만을 털어놨더니 총독이 내게 한 말이 바로 '신의 심판'이었지! 결투라니! 어때, 이런 상황이? 나는 조용히 살고 싶은 평화로운 플랜터일 뿐, 도둑이나 싸움꾼이 아니야\n이건 결투가 아니라 살인이라고! 그리고 너, 분명히 나보다 이런 일에 훨씬 능숙하겠지. 그래서 다가오는 결투에서 내 대표가 되어주길 부탁하는 거야. 믿어줘, 너에게 신세만 지고 끝나지는 않을 거야.";
			link.l1 = "결투는 언제야?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "오늘 밤 자정 전에 등대 근처에서. 나를 도와줄 수 있겠어?";
			link.l1 = "좋아, 도와주지. 마을에서 기다려!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "거기서 무슨 일이 있었는지 말해 줘. 우리가... 미안해, 네가 이겼어?";
			link.l1 = "매복이 있었다는 사실을 알면 분명 흥미로울 거라 생각하오. 아마 당신 이웃이 한 사람만 부르는 대신 대표를 몇 명 더 불러서 안전하게 가려고 했던 모양인데, 그들 모두 노련한 산적들이었소. 다행히도 나는 검술에 능한 사람이오.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "정말 못된 놈이군! 이제 우리 총독께서 그 악당을 체포해 달라는 내 요청을 거절할 이유가 없겠지! 고맙다! 보상 받아라, 나는 이제 관저로 가야겠다.";
			link.l1 = "잘 가시오.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "버그 없는 게임은 재밌지, 그 놈들은 잡기 힘드니까.";
			link.l1 = "진정해, 내가 개발자들에게 알려줄게.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "아, 거기 있었군. 이쪽은 내 친구들이자 결투 보조들이야. 시작할까?";
					link.l1 = "저는 당신을 위해 준비되어 있습니다!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "모두 모였다. 준비됐나?";
					link.l1 = "그래, 시작하자!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "드디어군! 이 긴 길을 헛걸음한 줄 알 뻔했잖아... 빨리 끝내자고, 선술집에 럼주 한 잔이랑 뜨거운 계집이 날 기다리고 있으니까!";
					link.l1 = "이제 둘 다 더 이상 필요 없을 거라고 확신해!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "그래, 오기로 했군? 드디어! 그럼 시작하자!";
					link.l1 = "그렇게 서두르지 마, 칼에 베일 수도 있으니까.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "그리고 이쪽이 내 부하들이네, 나리. 이제 죽을 준비나 하시지!";
					link.l1 = "먼저 가시오.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "여기에 도착했소. 검을 준비하시오, 나리!";
					link.l1 = "기꺼이, 더 나은 자가 이기길 바라지!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "훌륭하군, 모두 도착했네... 시작하자, 나리!";
					link.l1 = "춤추자!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "너는 누구냐? 평범한 시민처럼은 안 보이는데, 이봐...";
					link.l1 = "그래서? 나랑 결투라도 하자는 거야?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "하! 결투다! 우리 의뢰인이 이놈인 것 같군. 얘들아, 저놈 찔러버리고 그냥 가서 보수나 받자. 배를 갈라!";
			link.l1 = "매복이라고? 한심하군, 이 정도로 날 쓰러뜨리려면 한참 멀었지...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "우리 친구를 죽이고 그냥 넘어갈 거라고 생각하지 마라! 무기를 들어라!";
				link.l1 = "이런 비참한 놈한테서 이런 일이 나올 줄 알았어야 했지!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "선장님, 명예를 되찾으셨으니 승리하셨습니다. 하지만 한 가지 충고를 드리자면, 이 도시를 떠나 당분간 얼굴을 비추지 않는 것이 좋겠습니다...";
				link.l1 = "그래서 뭐가 문제인데?";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "모두 명예를 위한 일이었으니, 이제 가서 우리 친구를 데려오자.";
				link.l1 = "그래, 말리진 않겠어...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "문제는 네가 우리 사령관의 부하를 죽였다는 거야. 그 자는 나쁜 놈이었고 아무도 그의 죽음을 슬퍼하지 않겠지만... 사령관은 그를 무척 아꼈고, 친구의 죽음을 결코 용서하지 않을 거다.";
			link.l1 = "조언 고맙네, 꼭 명심하겠네. 안녕히 가게.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
