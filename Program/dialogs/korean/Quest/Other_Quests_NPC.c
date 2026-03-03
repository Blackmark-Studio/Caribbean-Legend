void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "이 악당아! 꽤 놀랐겠군!";
    		link.l1 = "뭐?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "하하! 여긴 노예 없어! 너 그놈들 때문에 온 거지?";
			link.l1 = "젠장. 그래서 왜 상선 핀네스에 군인들이 그렇게 많았는지 궁금했지... 함정이었군!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "그래, 이 자식아, 함정이다. 나는 상인이 아니라 군 장교다! 네가 싸움에서 이겼을지 몰라도, 심판은 피하지 못할 거다!";
			link.l1 = "그게 왜냐고? 지금 널 끝장내고, 네 배도 가라앉히면 아무도 모를 테니까.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "착각하지 마라. 그 은행가와의 거래는 이미 들통났다. 곧 총독께서도 네 꼼수를 알게 될 테니, 교수대에서 벗어날 수 없을 거다. 하지만 내가 지금 여기서 널 죽여서 은혜를 베풀어 주지!";
			link.l1 = "해 봐라, 총독의 개놈아!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", 법의 이름으로 너를 체포한다! 무기를 버리고 우리와 함께 가라!";
			link.l1 = "무슨 일이오, 경관? 항복하라고? 무슨 근거로?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "모른 척하지 마라, 선장! 네 더러운 짓거리가 이미 드러났어. 네가 저지른 학살과 그 배 때문에\n "+NationNameGenitive(sti(npchar.nation))+" 네가 침몰시킨 것 때문에, 우린 널 교수형에 처할 거다!";
			link.l1 = "그래, 그렇게 나오겠다 이거지... 엿이나 먹어라!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "이봐, 여기서 뭐 하는 거야?!";
    		link.l1 = "왜 이렇게 무례하시오, 나리? 그 쥐새끼 곤티에가 여기 어딘가에 숨어 있는 거 아니오, 응?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "아니, 그 자가 아니야! 나가!";
			link.l1 = "거짓말하는 것 같군. 내가 집을 뒤져서 확인해 보겠다...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "꺼져! 프랑수아! 도망쳐! 얘들아, 도와줘!";
			link.l1 = "젠장!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "오! 제발, 나를 다치게 하지 마!";
    		link.l1 = "뭐야...? 프랑수아 곤티에는 어디 있지? 대답해, 이 더러운 년아, 안 그러면 네 동료들처럼 똑같이 당할 줄 알아!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "아니야, 아니야, 다 말할게! 그가 창문으로 뛰어내려 자기 배로 도망쳤어.";
    		link.l1 = "무슨 배? 그 자의 배는 항구에 없다는 거 나도 알아. 내게 거짓말하지 마, 계집애. 안 그러면 더 나빠질 테니까...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "거짓말 아니야, 맹세해! 그 사람이 작은 섬에 상륙해서 여기까지 장선 타고 왔다고 했어... 분명 거기 있을 거야! 제발 나 다치게 하지 마!";
    		link.l1 = "좋아, 네 말이 진짜인 것 같군. 여기서 조용히 있어. 그리고 앞으로는 좀 더 영리하게 친구를 사귀도록 해라. 그런데 말이지, 네 눈을 보니 딱 알겠더라, 머리가 별로 없다는 걸.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "우릴 살려줘! 자비를! 항복할게!";
    		link.l1 = "오, 그래? 지금 당장 화물창으로 가! 멍청한 짓 하려는 놈은 내가 쏴버릴 거다!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "흠, 흠... 이게 누구냐? 우리 식민지에서 허가받지 않은 자들과, 또는 그들끼리 물건을 거래하는 건 금지된 거 몰랐나?";
			link.l1 = "그래요, 장교? 솔직히 말해서, 그 이야기는 처음 듣는군. 이 칙령이 얼마 전에 통과된 거 맞지?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "뭐야, 무역 "+GetGoodsNameAlt(iCGood)+"? 나는 아무것도 안 보여 "+GetGoodsNameAlt(iCGood)+" 주위를 둘러봐, 장교. 난 이 반짝이는 동전들밖에 안 보여... 그리고 저 자도 마찬가지야. 너희들도 네 병사들이랑 우리 동전 좀 구경해 보는 게 어때?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "몰랐던 거야, 응? 흠... 거짓말하는 것 같진 않군. 하지만 그렇다고 해도 법을 어긴 건 사실이야. 체포하진 않겠지만, 벌금은 내야 하네. 그리고 화물에 대해서는... 거래에 참여한 다른 한 사람과 따로 얘기하도록 하지.";
				link.l1 = "그 벌금이 얼마인데?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "모르는 척하지 마, 선장! 모두가 그 사실을 오래전부터 알고 있었지, 덧붙이자면. 너희 둘 다 밀수 혐의로 체포하겠다, 그리고 화물은 몰수될 거다.";
				link.l1 = "나는 갇힌 곳은 싫어, 장교. 난 탁 트인 바다가 더 좋지... 지금 바로 그 바다로 나갈 거야. 하지만 네 시체를 밟고서야 갈 수 있을 것 같군.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "항복할 수밖에 없군. 하지만 정말로 아무것도 몰랐어!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "이제야 말이 통하는군... 네 돈 좀 보자... 내가 꽤 구체적인 금액을 들은 것 같은데 - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". 이제 참가자가 셋이 되었으니 내가 받고 싶은 것은 "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". 그건 네 몫이고, 네 친구도 마찬가지야.";
				link.l1 = "물론이지, 장교 나리. 여기 내 반짝이는 동전들, 아니, 이제는 나리의 반짝이는 동전들이지 – 방금 해변에 실수로 떨어뜨렸잖아... 그리고 여기에는 아무런\n "+GetGoodsNameAlt(iCGood)+" 여기 있지, 하하, 내가 말했잖아.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "이봐! 너 너무 욕심 많잖아, 관리야. 네 어머니가 욕심 부리면 안 된다고 안 가르쳤냐? 내 생각엔 칼로 상대하는 게 더 싸게 먹히겠군.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "농담하는 거요, 선장? 나한테 뇌물을 주겠다는 거요? 당신은 체포됐소! 저 자를 잡아라!";
				link.l1 = "그래, 내 돈을 보고 싶지 않다면 내 검이나 봐라!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "항복할 수밖에 없군. 하지만 정말로 아무것도 몰랐어!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "그래, 네 말이 맞는 것 같군... 여기엔 신사 몇 명과 내 반짝이는 동전들 말고는 별로 볼 게 없네. 가도 좋다, 선장. 그리고 네 동료와는 우리가 얘기 좀 해보지.";
			link.l1 = "잘 가요, 장교님. 그를 다치게 하지 마시오.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". 내 기분이 좋아서 그렇지.";
			link.l1 = "감사합니다, 장교님. 정말 전혀 몰랐습니다... 자, 벌금을 낼 준비가 되어 있습니다.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "자네도 그리 정직한 사람은 아닌 것 같군, 경관. 벌금이 너무 비싸잖아. 이 식민지를 자네 같은 놈에게서 구해 주는 게 내가 도울 수 있는 일이겠지.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "좋아. 이제 가도 된다. 그리고 앞으로 이런 일이 다시 생기지 않게 현지 법을 잘 익혀두는 게 좋을 거다. 이제 가라, 우리는 이 거래의 두 번째 참가자도 처리해야 한다. 그는 모든 걸 알고 있었으니, 그건 확실하다.";
			link.l1 = "그렇다면, 좋은 하루 되시오, 경관 양반.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "사령관이 너를 상대할 거다. 따라와!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "좋은 하루입니다. 무슨 일로 오셨습니까?";
			link.l1 = "그래, 친구. 네가 내 사람이겠지. 훔친 게 바로 너지\n "+pchar.GenQuest.Device.Shipyarder.Type+"  현지 조선소에서 말이냐? 모든 증거가 너를 가리키고 있어, 그러니 변명하지 마.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "제발 용서해 주십시오, 나리! 네, 제가 조선소에서 이 이상한 물건을 훔쳤습니다. 하지만 팔지 못했어요, 아무도 이런 물건을 원하지 않더군요. 그래서 그냥 버렸습니다. 제발 살려주십시오, 좋은 나리, 저를 탓하지 말고 제 배고픔을 탓해 주십시오... 아니었으면 절대 아무것도 훔치지 않았을 겁니다!";
					link.l1 = "그게 문제군... 그리고 너도 필요 없어. 내가 찾아야 하는 건 그거야\n "+pchar.GenQuest.Device.Shipyarder.Type+". 말해 봐, 어디에 버렸지?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "제발이오, 나리! 그래, 내가 조선소에서 이 이상한 물건을 훔쳤소. 하지만 팔지 못했소, 아무도 이런 걸 원하지 않더이다. 당신께 드릴 테니 여기, 가져가시오. 제발 나를 해치지 말고 군인들도 부르지 마시오!";
					link.l1 = "좋아, 살려주지, 이 깡패 놈. 네 가죽 따위는 필요 없어, 난 그 물건이 필요하다. 당장 내놓고 꺼져라!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "무슨 뜻이지? 뭐가\n "+pchar.GenQuest.Device.Shipyarder.Type+"? 이해가 안 돼!";
					link.l1 = "내가 너나 네 시체를 뒤질 때 얻게 될 거다! 지금 내놔!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "오... 이게 뭐지 "+pchar.GenQuest.Device.Shipyarder.Type+"? 나... 그게 뭐지?";
					link.l1 = "모르는 척하거나 도망치려고 하지 마, 어차피 내가 잡을 거니까. 그냥 주머니 좀 확인하자...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "도시 성문 바로 뒤, 정글에서 멀지 않은 곳이에요. 제발 부탁입니다, 나리! 정말 그 물건이 필요하다면 직접 가져가세요. 아직 거기 있을 거라고 확신합니다.";
			link.l1 = "너를 시켜서 그걸 찾아오게 해야겠지만, 널 찾는 데에 그걸 찾는 것보다 더 많은 시간이 걸릴까 두렵군 "+pchar.GenQuest.Device.Shipyarder.Type+". 내가 직접 하겠다. 하지만 네가 나를 속이고 있다면 반드시 찾아낼 거다!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "여기, 가져가시오. 고맙소, 친절한 나리!";
			link.l1 = "그래, 이게 내가 찾던 거였군... 하! 이제 가도 된다. 어서 가. 다음엔 더 조심해라.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "이봐, 이 악기 말하는 거야? 이건 내 거고, 내가 훔친 게 아니야! 그리고 그냥 공짜로 줄 생각도 없어. 갖고 싶으면 돈 내. "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "흠... 좋아. 돈 줄게. 여기 네 동전이다, 이제 악기를 내놔!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "오, 정말인가? 네가 내가 너 같은 비참한 도둑을 믿을 거라고 생각했냐? 그거 내놔\n "+pchar.GenQuest.Device.Shipyarder.Type+" 지금 당장 내게 넘기지 않으면 경비병을 부를 거다. 그러면 우리 둘이 함께 조선소로 가서 이게 누구 물건인지 확실히 가리자고.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "멍청한 거야, 뭐야? 이봐, 이 자식아, 선택지는 둘뿐이야: 내게 그걸 주든가\n "+pchar.GenQuest.Device.Shipyarder.Type+" 아니면 널 찔러 죽이고 그 악기를 네 시체에서 빼앗을 거야!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "좋은 거래였어, 선장! 우리 모두 이익을 나눠 갖겠지, 헤헤... 가져가.";
			link.l1 = "말이 많군, 도둑놈! 네가 날 속였다고 생각하지 마라, 나는 그냥 조용히 문제 없이 끝내고 싶을 뿐이다. 이 동전들, 네게 아무 소용도 없어. 썩 꺼져!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "안 돼! 경비를 부르지 마! 나... 이 빌어먹을 악기를 줄게. 자, 가져가!";
				link.l1 = "이제 훨씬 낫군! 썩 꺼져라! 아니면 교수대에 매달릴 테니, 시간문제다.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "경비? 선장, 여기 우리 둘밖에 없잖아. 괜히 말이 많군, 내가 칼로 진정시켜 줘야겠어...";
				link.l1 = "감히 나를 협박해? 이 쓰레기 같은 놈아?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "아! 도와줘! 살인자다!";
				link.l1 = "거기서 멈춰, 이 개놈아!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "좋아, 누가 누구를 찌를지 두고 보자고, 선장!";
				link.l1 = "감히 나를 협박해? 이 쓰레기 같은 놈아?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "찾고 계십니까? 제발요, 나리!";
			link.l1 = "이제 잘 들어. 조용히 조선소에서 방금 훔친 걸 내놓든가, 아니면 내가 너를 사령관 사무실로 끌고 갈 거다. 어차피 네가 내놓게 될 거지만, 먼저 네 뒤꿈치가 달궈진 쇠로 지져질 거다. 어쩌면 그 다음엔 교수형까지 당할지도 몰라. 선택은 네가 해.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "당장 훔친 걸 내놔라, 이 자식아, 아니면 여기서 바로 끝장내버릴 테니까!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "글쎄, 날 지휘관 사무실로 데려가고 싶으면 먼저 날 잡아야 할걸 ...";
				link.l1 = "거기 멈춰, 이 개놈아!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "안 돼, 나를 사령관 사무실로 데려가지 마! 내가 직접 줄게! 자, 이거 가져가. 이걸 찾고 있었던 거지? 어차피 아무도 안 살 거야...";
				link.l1 = "에이, 뭐 어차피 널 요새까지 데려다줄 수도 있지... 좋아, 도구 내놓고 꺼져!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "아야! 제발 다치게 하지 마, 가진 거 전부 줄게! 여기, 가져가!";
			link.l1 = "이제야 말 좀 하네! 꺼져라, 다시 이 마을에서 널 보면 사령관에게 넘겨버릴 거다. 잘 가라!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "거기서 멈춰, 이봐! 네가 가지고 있는 게 우리한텐 필요해. 내놔, 그럼 가도 좋아.";
			link.l1 = "네가 말하는 그게 도대체 뭐야?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "요즘 저 거리의 놈들이 너무 건방져졌군... 각오해라, 이 망할 놈들아!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "바보인 척하지 마라! 꾸러미를 내놓으면 살려주겠다. 그렇지 않으면... 네 시체에서 빼앗아가겠다!";
			link.l1 = "네 놈들한테 유리하군... 가져가라, 이 자식들아, 나한텐 선택지가 없어.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "글쎄, 한번 해보시지!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "입 조심해, 이 친구... 운을 시험하지 않은 건 현명했군. 어차피 끝은 똑같았을 거야, 하하! 당분간은 살아 있겠지... 또 보자.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "잠깐, "+GetAddress_Form(NPChar)+", 그렇게 급하게 가지 마. 너한테 시킬 일이 있어.";
			link.l1 = "무슨 용건이지? 난 너를 모른다.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "나는 당신을 알고 있소, 선장. 이제 본론으로 들어가지. 방금 당신은 받았소\n "+pchar.questTemp.WPU.Current.Add+" 안에서 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". 부정하려 들지 마라, 우리는 이 사실을 확실히 알고 있다네 - 어쨌든 며칠 동안 이 문서를 찾아 헤맸으니까.";
			link.l1 = "이제 알겠군. 그래서 뭐?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "패키지를 넘기면 우리 짧은 만남도 끝난다. 영웅 흉내내지 마라, 선장. 우리는 이 서류를 반드시 가져갈 거고, 필요하다면 도시 주둔군과도 싸울 각오가 되어 있다\n알겠지만, 만약 싸움이 벌어지면 네가 제일 먼저 죽을 거다. 그러니 문서를 넘기면 우리도 친구처럼 헤어질 수 있지.";
			link.l1 = "네놈들한테 유리하군... 가져가라, 이 망할 놈들아, 달리 방법이 없다.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "나 겁주려고 하는 거야? 너보다 훨씬 더 용감하게 덤비는 꼬마 물고기들도 봤다! 꺼져.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "이성적으로 행동해 줘서 기쁘군, 선장. 이 일을 맡으면서 스스로 큰 위험에 빠졌소. 이제 실례하겠소, 괜찮다면.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "그건 네 결정이었지...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "잠깐, "+GetAddress_Form(NPChar)+", 그렇게 서두르지 마. 너한테 시킬 일이 있어.";
			link.l1 = "무슨 용건이지? 빨리 말해, 나 바쁘다.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "네가 누군지 알고 있지. 그리고 방금 막 하나를 받았다는 것도 알고 있어. "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". 이 서류들 때문에 내가 이렇게 당신과 꼭 이야기하고 싶었던 거요.";
			link.l1 = "그리고 난 모르는 사람들과 이 문제를 논의하고 싶지 않아. 그 서류를 받고 싶어? 이유나 대 봐...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "그만하시오, 선장! 내가 강도로 보이오? 나는 사업가이며, 그리고 나는 이해관계를 대표하고 있소 "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". 아주 이득이 되는 거래를 제안하고 싶은데, 여기서는 곤란하오. 선술집 방으로 가서 이 일에 대해 이야기합시다. 오래 걸리진 않을 것이오.";
			link.l1 = "그건 너무 수상하군... 나는 너랑은 거래 안 해, 나리! 썩 꺼져!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "흠... 네가 나한테 뭘 내놓을 수 있는지 보자. 하지만 날 공격할 생각은 하지 마라 — 좋게 끝나지 않을 거다. 가자, 내가 따라갈 테니까.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "넌 고집 세고 어리석은 놈이야, 선장! 내가 쉽게 돈 벌 기회를 줬는데도 말이야. 그런데 너... 곧 후회하게 될 거다.";
			link.l1 = "꺼져!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "훌륭해! 따라와.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "이제 우리끼리 자유롭게 말할 수 있겠군.";
			link.l1 = "그래서 제안이 뭐요?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "내가 말했듯이, 이건 네가 항구 사무실에서 받은 서류에 관한 일이야. 내가 필요한 건 그 서류의 사본뿐이야, 그게 전부야\n원본은 네가 가지고 있으니, 그 일로 돈도 받을 수 있지. 아무도 무슨 일이 있었는지 모를 거야. 게다가, 나도 넉넉하게 보수 줄게.";
			link.l1 = "실례합니다... 하지만 그 꾸러미는 봉인되어 있습니다. 봉인을 뜯지 않으면 복사본을 만들 수 없을 거예요!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "이 질문이 나올 줄 알았지. 봉인을 뜯어야겠지만, 걱정 마. 다시 복구할 수 있어. 복제용 인장과 봉인용 왁스도 당연히 준비되어 있지. 아무도 소포가 열렸다는 걸 눈치채지 못할 거야.";
			link.l1 = "이 항구 행정에 대해 잘못된 고정관념이라도 있나 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "왜 묻는 거요, 선장? 그래, 하나 있소. 내가 그냥 장난이나 치는 줄 아시오? 내가 당신에게 제안하는 건\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" 이 서류들을 볼 기회를 주어서 고맙소. 그러니 이제 그 꾸러미를 내게 줄 수 있겠소? 제발.";
			link.l1 = "가져가. 하지만 다시 돌려줘야 하고, 봉인된 채로여야 해!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "있잖아, 안 할 거야. 마음에 안 들어.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "걱정 마. 나는 전문가야. 앉아서 좀 쉬어. 한 시간쯤 걸릴 거야.";
			link.l1 = "좋아.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "흠... 이런 일은 예상 못 했군. 네가 너무 고집이 세서 말이지, 선장. 여기서 그냥 널 죽이고 물건은 공짜로 가져가야겠다. 기도나 해라. 내 칼 솜씨는 뻔한 허세만큼이나 능숙하니까.";
			link.l1 = "기도해야 할 사람은 바로 너다, 첩자 놈아!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "끝났소. 말했듯이, 가장 정확하게 처리했소. 약속한 대로 이 꾸러미를 가져가시오 "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". 그리고 난 가봐야겠어. 행운을 빌어, 선장. 우리가 거래를 해서 기뻐.";
			link.l1 = "잘 가...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "안녕하십니까! 아, 다시 뵙게 되어 정말 기쁩니다!";
			link.l1 = "좋은 하루요. 흠, 말해 보시오, 혹시 그 함선을 지휘하는 사람이 아니오? "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "오! 그런데 그 일에 대해 어떻게 알게 되었지 "+pchar.questTemp.WPU.Escort.ShipName+"그래, 내가 그녀의 선장이었지. 아니, 선장이었어... 배는 여기서 멀지 않은 곳에서 침몰했어.";
			link.l1 = "아, 그럼 드디어 찾았군... 내 소개를 하지. - "+GetFullName(pchar)+". 나는 항만 관리자 요청으로 여기 왔다 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". 그는 당신네 캐러밴의 곤경에 대해 간단히 말해주고 내게 당신네 배를 찾으라고 보냈소.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "그래서, 네가 구조대의 선장이냐?";
			link.l1 = "뭐, 그런 셈이지. 내 임무는 네 배를 찾거나, 침몰했거나 항해 불능이라는 증거를 찾는 거였어. 안타깝게도 배는 못 찾았지만, 선장은 살아 있으니 그나마 다행이지...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "아, 미안하오, 내 소개를 깜빡했군. 나는 "+GetFullName(npchar)+". 자네는 우리가 어떻게 여기 오게 됐는지 이미 아나? 폭풍 때문에 우리 배는 통제 불능이었지\n며칠 뒤, 이 만에서 멀지 않은 암초에 부딪혔고, 강풍이 순식간에 배를 산산조각냈다네. 내 선원 중 몇십 명만 살아남았어. 나머지는 모두 바다 밑에 누워 있지. 우리는 매일 그들의 영혼을 위해 기도한다네...";
			link.l1 = "조의를 표합니다, 선장님 "+GetFullName(npchar)+". 정말 미안해.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "고맙소... 살아남은 자들이 해안에 진을 치고 구원을 기다리고 있소. 마침 잘 오셨소, 선장님! 이 근방의 호전적인 인디언들이 우리 존재를 눈치챘으니, 그들이 공격해 오면 수백 명을 상대로는 버틸 수 없을 것이오.\n이 지역을 배회하는 해적선도 한 척 있소; 우리를 찾는 것처럼 보이더이다. 혹시 그 해적을 만난 적 있소, 선장님?";
			link.l1 = "아니, 못 봤어.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "주님을 찬양하라. 저자는 저 저주받은 폭풍 전에 우리를 공격했던 놈들 중 하나야. 하이에나처럼 부상당한 먹잇감을 끝장내려고 안달이 났으니, 그래서 이 섬까지 온 거지.";
			link.l1 = "알겠어. 이제 다음에 뭘 할지 정할 시간이야.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "무엇을 결정하라는 거요, 선장? 우리를 배에 태우고 이 저주받은 곳에서 어서 벗어납시다.";
			link.l1 = "물론이지. 내가 배를 구하지는 못했지만, 적어도 선원들은 구할 거다. 짐을 챙기고 진영을 정리해라. 내가 여기로 장주정을 보내라고 명령하겠다. 모두 배에 오신 걸 환영한다!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "감사합니다, 선장님! 오래 걸리지 않을 겁니다. 잠깐만... 뭐야, 이게? 악! 저 붉은 피부 악마들이 또 우리를 노리고 오고 있어! 경보다! 무기를 들어라!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "휴, 우리가 해냈어... 봐, 선장, 내가 이 만이 지옥이라고 했잖아. 벌써 인디언들의 공격이 세 번째야! 여기서 빨리 떠나야 해, 또 공격당하면 못 버텨.";
			link.l1 = "그래, 네 말이 맞다. 살아 있는 사람 전부 모아서 내 배로 옮겨! 내가 당장 우리를 데리러 장선들을 보내라고 명령하겠다!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "히끅... 뭐야, 나한테 뭘 원해? 꺼져, 너랑 얘기하고 싶지 않아.";
			link.l1 = "너냐 "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "그래, 맞다. 그런데 무슨 일로 왔지?";
			link.l1 = "간단한 일이야. 이 마을에 네 수작질에 질린 사람이 있어. 그 사람, 이제 완전히 지쳤지. 지금 너를 보니 왜 그런지 알겠군. 다시는 이 동네 사창가에 나타나지 마라, 안 그러면 곤란한 일 당할 거다. 알겠어?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "아르! 이봐, 네가 감히 날 협박한다고? 이 죽일 놈! 내 칼끝에 꽂아 닭구이처럼 구워 주마!";
						link.l1 = "각오해라, 이 자식아!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "뭐? 무슨 속임수? 속임수 같은 건 없었어. 그냥 술에 취해서 몇 번 창관에서 흥청망청 놀았을 뿐이야. 완벽한 사람은 없잖아... 알았어, 알았어, 알았다고... 다시는 거기서 그런 짓 안 할게. 이제 됐어? 내 말 믿어.";
						link.l1 = "명예의 말이 당신에게 의미가 있길 바라며, 그걸 어기면 어떤 결과가 따를지 알고 있겠지. 그 점 명심해라. 이제 작별이다.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "정말 건방진 놈이군, 나리! 해가 지기 전에 네 말 후회하게 만들어 주겠어. 결투를 신청하지! 아무래도 조용한 곳에서 단둘이 싸우는 게 좋겠군. 정글이면 충분하니, 두 시간 뒤에 거기서 보자!\n";
					link.l1 = "좋은 생각이군! 적어도 네 시체를 숨기는 건 문제 없겠지.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "뭐? 무슨 속임수? 아무런 속임수도 없었어. 그냥 몇 번 술에 취해서 사창가에서 좀 놀았을 뿐이야. 완벽한 사람이 어디 있겠어... 알았어, 알았어, 알았다고... 다시는 거기서 놀지 않을게. 이제 됐지? 내 말 믿어.";
					link.l1 = "명예의 말이 당신에게 의미가 있기를 바라오, 그리고 그것을 어긴다면 어떤 결과가 따를지 알고 있겠지. 그 점을 명심하시오. 이제 작별이오.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "잠깐! 멈춰! 항복할게! 살려줘!";
			link.l1 = "그래서 지금 네가 이렇게 말하는 거구나!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "제발, 살려주십시오! 시키는 대로 뭐든 하겠습니다! 다시는 그 사창가에 나타나지 않겠습니다!";
			link.l1 = "이런 자세는 너 같은 쓰레기한테나 어울리지. 평생 교훈이 되길 바란다. 그리고 이 마을에서는 똑바로 행동해라.";
			link.l1.go = "Badboy_exit";
			link.l2 = "그래, 이제 그만해라. 네 속임수는 여기서 끝이다.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "지옥 갈 시간이다, 이 자식아! 네 목숨이나 빌어라, 하지만 빨리 해라. 내가 하루 종일 한가한 줄 아냐...";
			link.l1 = "말은 집어치우고 싸워라, 이 쓰레기들아!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "저기 있군, 저 건방진 놈! 이 마을 주인이 누군지 보여주자, 얘들아!";
			link.l1 = "아, 너 정말 타락한 놈이구나! 하지만 내가 경고했지. 이제 곧 너랑 네 졸개들은 지옥으로 직행하게 될 거다!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "안녕. 뭐 원하는 거야?";
			link.l1 = "너 아니야 "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? 믿지 못하겠지, 하하. 네 목이 갖고 싶어.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "흠... 아니... 아무것도 아니야. 내가 착각한 것 같군. 괜히 신경 쓰게 해서 미안하다.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "뭐 이런 어리석은 농담이냐, 나리! 변명해라, 아니면 내가...";
			link.l1 = "그래서 이제 어쩔 거냐, 한심한 청어 녀석아? 너는 착한 사람한테 몹쓸 짓을 했고, 그 사람은 정말 화가 나 있다. 그러니 지금 당장 기도나 해라, 빨리. 난 바쁘거든.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "뭐... 뭐 하는 거요, 나리! 도와줘! 누가 좀 도와줘! 살인자다!";
			link.l1 = "나는 네가 마지막 순간만큼은 기도나 할 줄 알았지. 그랬다면 하늘나라에 갈 기회라도 있었을 텐데...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "또 너냐? 대체 뭘 원하는지 왜 말 안 하는 거야?";
			link.l1 = "별거 아니오.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "어?! 뭐야? 여기서 대체 뭐 하는 거야, 이 망할 놈아? 누가 들여보냈어?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "리그는 네 목숨이 필요하다, 선장...";
			link.l1 = "뭐야? 젠장!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 마을 시민이야. 그러니 칼을 집어넣어 줘.","이봐, 나는 이 마을 시민이야. 그러니 칼을 집어넣어 줘.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","그래...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, "+GetSexPhrase("친구","소녀")+", 무기를 들고 뛰다 보면 말이야. 괜히 긴장돼...","나는 그런 일이 있을 때 마음에 들지 않아 "+GetSexPhrase("놈들이","~하는 사람들")+" 내 앞에서 무기를 들고 걸어가고 있어. 무섭단 말이야...");
				link.l1 = LinkRandPhrase("알겠어.","괜찮아.","걱정하지 마...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
