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
				link.l1 = "벨리즈 근처와 그 도시 안에서 도둑과 강도 무리가 활동하고 있다는 소문을 들었소.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "그 갱단에 대한 정보를 줄 수 있소.";
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
				link.l1 = "도시 전체가 해적을 잡았다며 축하하는 분위기군. 그 일에 대해 더 자세히 말해줄 수 있나?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "기꺼이! 이 자는 평범한 해적이 아니오 - 바로 그 악당 매튜 루터요.";
			link.l1 = "결국엔 모두의 운도 다하게 마련이지.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "너는 영국인도 아니고, 상인처럼도 안 보여서 그다지 흥분하지 않는 이유를 알겠군. 루터는 수년간 이 바다에서 우리와 돈놈들 모두를 공격하며 공포를 퍼뜨렸지, 특히 우리를 더 자주 노렸어. 그는 늘 우리 연안 경비대를 피해 다녔고, 한때 군도에서 가장 빠른 배였던 코르벳, 시걸호를 몰았지. 그런 전함을 어떻게 손에 넣었는지는 신만이 아실 거다.";
			link.l1 = "그래서 상인한테 졌다는 게 사실이란 말이냐? 그것도 코르벳에서? 믿기 힘든데.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "이상하게 들릴지 모르지만, 사실이오. 상인인데다가 스페인 놈이라니! 우리 해군도 저 자에게서 한 수 배울 만하오. 소타 선장은 도망칠 수 없다는 걸 깨닫고 전투를 준비했소...";
			link.l1 = "이 소타, 참 별난 녀석이군.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "아마도. 그는 가능한 한 많은 화물을 실을 수 있도록 배를 개조했지, 그래서 도망칠 수 없었어. 해적들이 자기 화물을 노린다는 걸 알고 표류하는 척했지. 그리고 나서...\n";
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
			dialog.text = "하! 아니, 루터가 접근하자마자 그 자가 산탄포를 근거리에서 쏘아댔지. 그리고 직접 해적선에 올라타더군! 루터가 누군지 알아내자 우리에게 넘겼어. 진정한 영웅이자 명예로운 사내라네!";
			link.l1 = "그를 움직인 건 명예만이 아니었지\n윈드백을 잡으면 보상도 있었을 거야.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "가끔은 이익과 선의가 일치하지. 하지만 그래, 그는 후한 보상을 받았어. 출항하기 전에 각하께서 우리 도시의 감사의 표시로 값비싼 물건들을 잔뜩 실어주셨지.";
			link.l1 = "그 사람을 만났더라면 좋았을 텐데 - 악수라도 해보고 싶군. 말해봐...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "네 첩자가 한 말이 사실이었군. 저 산적들은 우리에게 정말 골칫거리가 되었지. 그들에 대해 뭐라도 말해줄 건가?";
			link.l1 = "그것 말고도 내게서 중요한 걸 하나 훔쳐갔지. 그 외엔 별거 없어. 자네가 그들에 대해 뭔가 말해줄 수 있을까 기대했네. 혹시 그들 중 한 놈이 잡혀서 지금 증언할 준비가 되어 있다든가...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "실망시켜서 미안하오, 선장. 하지만 그들에 대해 아는 건 없소. 내가 아는 건 그들이 정글 어딘가에 숨어 있고, 마을에 공범이 있다는 것뿐이오, 그게 전부요. 자네가 그들에 대해 새로운 걸 알게 되면 즉시 내게 알려주시오.";
			link.l1 = "알겠소, 장교. 그렇게 하겠소.";
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
			link.l1 = "나는 그들의 정보원 중 한 명을 마을에서 찾았소. 그자가 말하길, 그들의 무리가 체투말 만에 도착할 예정인 배를 공격할 준비를 하고 있다 하오. 악당들이 모이고 있소\n "+sTime+" 벨리즈에서 멀지 않은 동굴 근처, 밤에. 거기 가려면 정글 갈림길에서 왼쪽 길로 가기만 하면 돼.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "동굴에 있다고? 훌륭한 소식이군. 저 악당들을 잡기 위해 매복을 준비하라고 명령하겠다. 네 말이 맞고 네 정보원이 사실을 말했다면, 우리가 저 놈들을 잡을 것이고, 그다음엔 내가 총독에게 너에게 상을 주도록 청원하겠다.";
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
				dialog.text = "우리는 그 악당들을 위해 따뜻한 환영을 준비했지, 하하하! 네가 그놈들 얼굴을 봤다면 얼마나 웃겼을지! 두목까지 포함해서 전부 잡아들였어! 몇 놈이 저항하려 들었지만, 우리 용감한 병사들이 제대로 처리했지.";
				link.l1 = "훌륭한 소식이군, 장교! 이제 벨리즈 시민들이 드디어 편히 잠들 수 있겠어.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "흠... 내 병사들이 동굴에서 밤새 그놈들을 기다렸지만, 아무도 나타나지 않았지. 하사관이 완전히 분노했어. 아직도 네놈을 못 잡은 게 다행이군.";
				link.l1 = "젠장! 그럴 리가 없잖아! 어느 동굴에 매복을 했다는 거지? 두 군데나 있는데!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "네가 말한 곳이야. 갈림길에서 오른쪽에 있는 그곳에...";
			link.l1 = "왼쪽에 있는 거다! 갈림길에서 왼쪽으로, 이 멍청이들아!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "하지만 분명히 네가 '오른쪽으로'라고 말했다고 기억해.";
			link.l1 = "오, 나의 주님! 왼쪽으로! 내가 말했잖아, 왼! 쪽! 으로! 네가 놈들을 놓쳤고, 그건 네 잘못이야!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "그럼 네가 중얼거린 게 틀림없군. 나 귀는 멀쩡하거든.";
			link.l1 = "좋소, 장교. 더 이상 말다툼하지 않겠소. 도와주고 싶었으나, 스스로 돕지 못하는 자는 도울 수 없는 법이지. 안녕히 계시오.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "나는 네가 그 갱단을 소탕하는 데 한 역할을 총독에게 보고했네. 총독께서는 자네의 공로를 높이 평가하시고, 나에게 상을 수여하라고 허락하셨지. 보상금과 함께 트로피용 아르케부스도 주겠네.";
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
			dialog.text = "수고해 주셔서 감사합니다, 선장님! 우리 시민들이 모두 당신처럼 성실했다면 진작에 범죄를 뿌리 뽑았을 텐데요! 행운을 빕니다!";
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
