// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "이건 버그야. 개발자들에게 알려 줘.";
			link.l1 = "물론이지!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "뭐가 필요하지?";
			link.l1 = "너냐 "+pchar.questTemp.Shadowtrader.Guardername+"? 여기 상인이 저를 보냈어요. 지금 이 순간 당신이 오기를 애타게 기다리고 있습니다.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "아-아, 하지만 난 여기서 그를 기다리고 있었어! 선술집으로 온다고 들었거든! 미안, 바로 가볼게.";
			link.l1 = "좋아!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "좋은 저녁이오, 선장님. 싼 물건 찾으시나? 따라오시오!";
			link.l1 = "앞장서.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "좋은 저녁이오, 나리. 새로운 손님을 만나서 반갑소, 하! 내 소개를 하지. 나는 "+GetFullName(npchar)+". 내가 이 마을에서 제일 싼 물건을 팔고 있다네, 장담하지.";
			link.l1 = "드디어 만났군..."+npchar.name+". 실망시키게 될 것 같군. 나는 거래하러 온 게 아니라, 네 더러운 짓거리를 끝내러 왔다. 너는 어떤 중요한 인물의 골칫덩이였지. 그 고통이 너무 커져서, 그가 어떤 수단을 써서라도 널 막으려 하고 있어...";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "거기서 멈춰, 이 범죄자 놈! 상업 활동을 하려면 세금을 내야 한다는 걸 몰랐나? 내 눈앞에서 법을 어기는 자는 없다! "+GetFullName(npchar)+", 너는 법을 어겼고 네가 훔친 물건들은 이제 몰수다! 문 밖에는 무장한 병사들이 바로 뒤에 있으니, 시치미 떼려고도 하지 마라!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "정말이야? 이럴 줄은 몰랐는데... 넌 대체 뭐야, 이 악마 같은 놈! 이거 함정이잖아! 누가 이런 짓을 꾸몄는지 알 것 같군! 무슨 수를 써서라도... 얘들아, 저놈을 죽여!\n";
			link.l1 = "춤추자, 이 악당아!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "오, 맙소사... 장교 나리, 들어보시오! 우리 거래하자고. 나리께서는 현명하고 자비로운 분이시니! 내가 5,000에이트를 드릴 테니 2층으로 도망가게 해주시오. 물건도 가져가시오, 필요하잖소? 나까지 잡을 필요는 없잖소? 내가 지금 당장 이 마을을 떠나면 아무도 우리를 다시는 못 볼 거요. 그리고 나리께서는 돈도 챙기실 수 있소. 어때요, 장교 나리?";
		link.l1 = "네깟 놈이, 내가 이런 푼돈 때문에 내 의무를 더럽힐 거라 생각하나?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "알았어, 알았다고, 경관 나리, 내가 가진 거 전부 가져가. 만 페소야. 이게 전부야, 맹세해!";
		link.l1 = "흠... 내가 너를 체포하면 네 돈은 전부 몰수된다... 좋아! 이 밀수 거점은 폐쇄되고 모든 물건도 몰수한다... 돈 내놓고 꺼져. 다시는 여기 얼씬거리지 마라!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "감사합니다, 감사합니다, 정말 감사합니다, 나리! 여기 돈이요, 그리고 다시는 여기서 저를 못 볼 겁니다. 가자!";
			link.l1 = "나가라, 안 그러면 체포해야겠다!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "아! 자비를, 죽이지 마! 가진 거 전부 줄게!";
			link.l1 = "네 물건들은 전부 당국에 압수당할 거다. 방금 여기서 벌어진 일 이후에 내가 너한테 자비를 베풀 거라고 정말 생각하냐?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "나... 나 가진 돈이랑 물건 전부 줄게! 제발 살려만 줘! 오늘 바로 이 섬에서 떠날 테니, 다시는 여기서 나를 못 볼 거야!";
			link.l1 = "좋아. 가진 거 전부 내놔, 그리고 꺼져. 다시는 여기서 장사하려 들지 마라. 다음번엔 네 비참한 목숨도 봐주지 않을 테니까, 이 도적놈아.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "말도 안 돼, 이 자식아, 돈으로는 날 못 사. 너 같은 놈은 차가운 칼날이랑 뜨거운 납덩이로 상대해야지!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			AddDialogExitQuestFunction("ShadowTrader_KillToTrader_kino");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
