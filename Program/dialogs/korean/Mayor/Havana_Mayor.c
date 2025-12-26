// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","세 번째로 질문을 시도하시는군요...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각을 바꿨소...","지금은 아니오. 장소와 시간이 맞지 않소."),"그렇소... 하지만 나중에, 지금은 아니오...","물어보겠소... 하지만 조금 이따가...","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "각하, 감옥에 갇힌 장교 로페 몬토로에 관해 말씀드리러 왔습니다...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 더 무엇을 원하시오?","아직 가져가지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그저 둘러보고 있을 뿐이오...","그냥 확인하는 중이오, 뭔가 깜빡하고 안 챙겼을지도 모르니...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "이런 도둑놈들! 감히 아바나를 공격하다니?! 무엇을 원하는 것이오?!";
			link.l1 = "잠시 생각해 보십시오, 이해하게 될 것입니다.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "금이지, 당연히! 이놈들아, 너희가 관심 있을 만한 게 금 말고 뭐가 있겠어?! 그런데 우리에겐 없어... 창고에 몇 되밖에 없단 말이다.";
			link.l1 = "하하... 아니오, 우리는 금에는 관심이 없소. 우리는 상아, 그것도 검은 상아를 찾으러 왔소... 내 말 이해하겠소?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "하! 네가 노예 때문에 여기 온 줄 알았다. 하지만 그들은 요새에 있다. 우리 증원군이 오고 있으니, 네 무리는 곧 전멸할 것이다.";
				link.l1 = "젠장! 좋아, 여기 앉아서 꼼짝 말고 있어라... 이제 나가자! 젠장...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "하지만 어떻게... 어떻게 그 사실을 알았소?";
				link.l1 = "하! 바보만이 노예 5,000명을 한 곳에 모아두고 아무도 눈치채지 않을 거라 생각하지. 여기서부터 저 빌어먹을 토르투가까지 악취가 진동하오... 우리가 그들을 당신에게서 빼앗아 가는 것, 이해하리라 믿소.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "좋소, 어차피 그대가 이겼으니 우리는 그대의 폭력에 굴복할 수밖에 없구려. 하지만 그 강도질과 스페인 군함 두 척을 침몰시킨 일 이후에 정의의 심판을 피할 수 있을 거라 기대하지 마시오.";
			link.l1 = "그렇게 뻐기다간 심장마비 올 수 있소. 여기 앉아서 꼼짝 말고 있으시오...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "참으로 이상하군요... 또 불만이 있소?";
			link.l1 = "아닙니다, 아닙니다, 전혀 그렇지 않습니다, 각하. 로페는 제 오랜 군 동료로, 저희는 유럽에서 함께 싸웠습니다... 그를 도와주고 싶어서, 각하의 도움을 청하러 왔습니다.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "흠... 뭐, 내게 온 걸 보니 이미 이... 터무니없는 이야기는 알고 있겠지?";
			link.l1 = "그렇사옵니다, 각하.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "돈 로사리오 구스만에게 연락해 보시지요. 그도 그대처럼 돈 로페 몬테로를 돕고자 합니다. 그는 피해자와 접촉을 시도했으나, 협상은 성과를 내지 못했소. 그를 만나면 자세한 내용을 설명해 줄 것이오. 돈 로사리오는 오후 네 시부터 여덟 시까지 거리에서 만날 수 있습니다. 그는 매일 시 경비대 초소를 모두 점검합니다.";
			link.l1 = "감사합니다, 각하!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
