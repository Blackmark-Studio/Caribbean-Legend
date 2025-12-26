// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "벨리즈 근처와 도시 안에서 도둑과 강도 무리가 활동하고 있다는 소문을 들었소.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "그 패거리에 대한 정보를 줄 수 있지.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "그 놈들 소식은 어떤가? 동굴에서 잡았나?";
				link.l1.go = "caleuche_7";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "해적을 잡았다며 온 마을이 축제 분위기군. 그 일에 대해 좀 더 말해줄 수 있나?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "기꺼이! 이 자는 평범한 해적이 아니오 - 바로 그 악당 매튜 러터요.";
			link.l1 = "결국엔 모두의 운도 다하게 마련이지.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "너는 영국인도 아니고, 상인처럼도 안 보여서 그다지 흥분하지 않는 이유를 알겠군. 루터는 수년간 이 바다를 공포에 몰아넣었지. 우리와 돈 놈들 모두를 공격했지만, 특히 우리 쪽을 더 자주 노렸어. 녀석은 항상 우리 해안 경비대를 따돌리고, 한때 군도에서 가장 빠른 배였던 코르벳, 시걸을 타고 다녔지. 어떻게 그런 전함을 손에 넣었는지는 신만이 알 거다.";
			link.l1 = "상인이랑 싸워서 졌다고? 그것도 코르벳에서? 믿기 힘든데.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "이상하게 들릴지 몰라도 사실이야. 상인인데다가, 스페인 놈이라고! 우리 해군도 그에게서 한 수 배워야 할걸. 소타 선장은 도망칠 수 없다는 걸 깨닫고 전투 준비를 했지...";
			link.l1 = "이 소타, 꽤나 별난 인물이군.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "아마도. 그는 가능한 한 많은 화물을 실을 수 있도록 배를 개조했지, 그래서 도망칠 수 없었어. 해적들이 그의 화물을 노린다는 걸 알고 표류하는 척했지. 그리고 나서...\n";
			link.l1 = "...그가 적절한 순간에 돛을 올렸다는 말인가?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "하! 아니, 루터가 다가오자 그 자는 산탄을 근거리에서 쏘아댔고, 직접 해적선에 올라탔지! 루터가 누구인지 알아내자마자 우리에게 넘겼어. 진정한 영웅이자 명예로운 사나이야!";
			link.l1 = "그를 움직인 건 명예만이 아니었지\n윈드백을 잡으면 보상이 있었던 게 분명해.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "가끔 이익이 선한 의도와 맞아떨어지기도 하지. 하지만 그래, 그는 충분히 보상을 받았어. 그분께서 그가 출항하기 전에 우리 도시의 감사 표시로 값비싼 물건들을 잔뜩 실어주셨지.";
			link.l1 = "그를 한 번 만나봤으면 좋았을 텐데. 악수라도 해보고 싶군. 말해봐...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "네 정보원이 사실을 말했군. 저 산적들은 우리에게 정말 골칫덩어리가 되었지. 그놈들에 대해 뭐라도 말해줄 건 있나?";
			link.l1 = "그것 말고도 내게서 중요한 걸 하나 훔쳐갔지 - 그 외엔 별거 없어. 자네가 그놈들에 대해 뭔가 말해줄 수 있을까 기대했네. 혹시 그들 중 한 놈이 잡혀서 지금 증언할 준비가 되어 있진 않은가...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "실망시켜서 미안하오, 선장. 그들에 대해 아는 건 없소. 내가 아는 건 그들이 정글 어딘가에 숨어 있고, 마을에 공범자들이 있다는 것뿐이오, 그게 전부요. 자네가 그들에 대해 새로운 걸 알게 되면 즉시 내게 알려주시오.";
			link.l1 = "알겠소, 경관. 그렇게 하겠소.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "진심인가, 선장? 말해 봐. 다 듣고 있으니.";
			link.l1 = "나는 그들의 정보원 중 한 명을 마을에서 찾았어. 그자가 말하길, 그들의 무리가 체투말 만에 도착할 예정인 배를 공격할 준비를 하고 있대. 악당들이 모이고 있어\n "+sTime+" 벨리즈에서 멀지 않은 동굴 근처, 밤에. 거기 가려면 정글 갈림길에서 왼쪽 길로 가기만 하면 돼.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "동굴에서라고? 훌륭한 소식이군. 저 악당들을 잡기 위해 매복을 준비하라고 명령하겠다. 네 말이 맞고 네 정보원이 진실을 말했다면, 우리가 저 놈들을 붙잡을 수 있을 거다. 그러면 내가 총독께 네게 보상을 내리도록 청원하겠다.";
			link.l1 = "고마워! 끝나면 너를 보러 올게.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "좋아. 괜찮아.";
			link.l1 = "곧 보자, 장교.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_BelizComendantPrison");
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "우리는 그 악당들을 위해 따뜻한 환영을 준비했지, 하하하! 네가 그놈들 얼굴을 봤으면 좋았을 텐데! 두목까지 포함해서 전부 붙잡았다! 몇몇은 저항하려 들었지만, 우리 용감한 병사들이 처리했다.";
				link.l1 = "훌륭한 소식이오, 장교! 이제 벨리즈 시민들이 드디어 편히 잠들 수 있겠군.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "흠... 내 병사들이 동굴에서 밤새 그놈들을 기다렸지만, 아무도 나타나지 않았지. 하사관이 완전히 분노했어. 아직 네놈을 못 잡은 게 다행이지.";
				link.l1 = "젠장! 그럴 리가 없잖아! 어느 동굴에 매복을 설치했지? 두 군데나 있는데!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "네가 말한 곳이야. 갈림길에서 오른쪽에 있는 곳에서...";
			link.l1 = "왼쪽에 있는 거다! 갈림길 왼쪽이라고, 이 멍청이들아!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "하지만 분명히 네가 '오른쪽으로'라고 말한 걸 기억하는데.";
			link.l1 = "오, 주여! 왼쪽으로! 내가 말했잖아, 왼! 쪽! 으로! 네가 놈들을 놓쳐버렸고, 그건 전적으로 네 잘못이야!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "그럼 네가 중얼거렸겠군. 나는 귀가 밝은 편이야, 알겠어.";
			link.l1 = "좋아, 장교. 더 이상 따지지 않겠소. 도와주고 싶었지만, 스스로를 돕지 못하는 자는 도울 수 없는 법이지. 잘 있으시오.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "네가 그 갱단을 소탕하는 데 한 역할에 대해 총독에게 보고했네. 총독께서는 자네의 공로를 높이 평가하셨고, 나에게 상을 수여하라고 허락하셨지. 현금 보너스와 기념 아르케부스가 그 보상일세.";
			link.l1 = "감사합니다!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "수고해 주셔서 감사합니다, 선장님! 우리 시민들이 모두 당신처럼 성실했다면 진작에 범죄를 뿌리 뽑았을 텐데! 행운을 빕니다!";
			link.l1 = "안녕히 계시오, 장교 나리! 복무에 행운이 함께하길 바라오!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
