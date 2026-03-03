// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"무슨 일이냐, "+GetAddress_Form(NPChar)+"...","이제 세 번째로 나를 귀찮게 하는군...","질문이 더 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 정말로 이번이 세 번째야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "내 옛 동료 페르낭 뤽을 찾고 있어. 그에게 물어볼 게 좀 있거든. 일주일 전에 여기서 꽤 소란을 피웠다고 들었는데...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "내 친구랑 여기서 만나기로 했는데, 아무리 봐도 안 보여. 혹시 어디로 갔는지 알아? 아직 마을에 있나, 아니면 적어도 이 섬에 있나? 이름은 롱웨이야 – 중국인이야.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l2 = "좋은 소식이오, "+npchar.name+". 내가 바로 자네 상황을 구해줄 물건을 가지고 있지. 훌륭한 와인 백 병과 럼주 백 병이네. 이런 화물이라면 자네 손님들이 다시 술에 흠뻑 젖게 될 거야. 돈 낼 준비됐나?";
				link.l2.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l2 = "그렇다면, "+npchar.name+", 거래 조건에 대해 논의할 준비가 되었나?";
				link.l2.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l2 = "그래, "+npchar.name+". 내 쪽은 모두 정리됐고 물건도 이미 선술집으로 가고 있어. 이제 결제 진행할까?";
				link.l2.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "지옥에 가서도 아직 잘 놀고 있을지도 모르지. 네 친구는 죽었으니, 선장, 넌 좀 늦었어. 저기 맨 끝 테이블에 앉아 있는 저 남자가 그의 장례비를 냈어. 하지만 내 느낌엔, 그가 바로 그 일을 저지른 놈 같아. 얼굴에 죽을 죄를 쓴 놈이지. 이름은 로버트 마르텐이야. 원하면 직접 가서 물어봐. ";
			link.l1 = "고마워, 친구. 가서 로베르 나리와 얘기 좀 하고 올게. 가엾은 루크 영혼을 위해 한잔하자, 그가 평안히 쉬길 바라며...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "뭘 더 얘기할 게 있겠어? 그 자가 너랑 네 친구를 공격했고, 너희가 맞서 싸웠지. 이런 일은 거의 매일 본다. 잘했어. 이제 내가 이 난장판만 치우면 되겠군...";
			Link.l1 = "이제쯤이면 익숙해졌으니 네가 치우겠지. 그에 대해 아는 게 뭐지?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "별일 없었어, 사실. 며칠 전에 나타났지. 여기 마음에 들어 했고, 마을 변두리에 집도 하나 빌렸어. 자주 들렀고, 돈도 꼬박꼬박 냈지. 그리고 가장 중요한 건, 그동안 내내 얌전히 굴었어. 누구한테도 험한 말 한 적 없었지. 그런데 네 친구랑 너를 공격했다니 아직도 충격이야. 여기서 정착할 줄 알았거든.";
			Link.l1 = "어떻게 보면, 그랬지. 뭐, 큰 건 아니지만 그래도 고맙다, 친구. 또 보자.";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_BasTerTavern_3");
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "그 이름은 나한테 아무 의미도 없어. 그리고 대체로 그런 놈들은 내 술집에 들이지도 않고, 관심도 두지 않아.";
			Link.l1 = "좋아. 알겠어, 나중에 보자.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "오, "+GetAddress_Form(NPChar)+", 그보다 더 심각해. 안티과 출신 내 공급자가 증류소를 잃었어 — 해적들이 습격해서 전부 불타버렸지. 이제 그는 럼이나 와인은 최소 두 달은 기대하지 말라고 하더군.";
			link.l1 = "그럼 새 공급자를 찾아. 두 달이나 그냥 앉아서 기다릴 생각은 아니겠지?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "믿을 만한 공급업자를 찾는 건 쉽지 않지. 나도 소규모 상인들이랑 거래해 봤는데, 믿을 수가 없더라고. 물건이 올 때도 있고, 안 올 때도 있어. 큰 공급업자랑 거래하면 모든 게 시계처럼 딱딱 맞아떨어져 — 안정적인 납품에 품질도 좋아.";
			link.l1 = "음, 평범한 공급업자가 문제라면 그림자 속에서 일하는 사람을 찾아보는 게 어때? 그런 녀석들은 좀처럼 실망시키지 않고, 물건도 항상 준비되어 있지.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "알겠지, "+GetAddress_Form(NPChar)+", 이 선술집은 지금 공공의 감시를 받고 있어. 당국과 문제를 일으키고 싶지 않거든. 평판이 확실한 사람이 물건을 가져온다면, 한 묶음 사는 건 물론이고 어디서 났는지도 기꺼이 모른 척해 주지\n어차피 상황이 이렇게 급박한데, 그런 사소한 건 누가 신경 쓰겠어? 중요한 건 의심을 피하는 거지. 하지만 장기적으로는 진지하고 정직한 상인하고만 거래할 거야.";
			link.l1 = "알겠소. 뭐, 나중에 다시 들를지도 모르지. 영리하게 접근하면 어떤 문제든 해결할 수 있으니까.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "선장님, 이거 정말 대단하군요! 어떻게 이런 일을 해내셨습니까? 뭐, 그건 중요하지 않소. 자, 말씀해 보시오. 이렇게 호화로운 술 화물을 가져온 대가로 무엇을 원하시오? 그리고 서류 처리도 모두 문제없이 될 수 있겠소?\n";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "서류라구? 물론 전부 완벽하게 준비되어 있지. 설마 진짜로 확인할 생각은 아니겠지?";
				link.l1.go = "TPZ_Tavern2_2";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				link.l1 = "서류 작업?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				Notification_Reputation(false, 40, "low");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "선장님, 제발 이해해 주십시오. 이 술 화물을 받는 게 저에게는 정말 중요합니다. 하지만 제 자유와 명예도 그만큼 소중하지요. 총독은 암시장 상인들에게 가차 없습니다, 아주 사소한 자들까지도요. 사람들이 선장님에 대해 좋게 말한다면 서류가 없어도 모른 척할 수 있겠지만, 지금은... 선장님이 너무 눈에 띄고 있습니다...";
			link.l1 = "좋은 일 좀 할 때가 된 것 같군. 기다려, 금방 돌아올게.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "이번엔 네 말을 믿어주지. 그래서, 이번 물건은 얼마에 팔 생각이야?";
			link.l1 = "포도주 열 병마다 서른 두블론, 럼주 열 병마다 다섯 두블론을 원하지. 전부 합쳐서, 각각 백 병씩이면 삼백오십 두블론이 들 거야.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "잠깐만요, 선장님! 이건 대낮의 강도질이잖소! 내 처지가 절박하긴 해도, 손해 보면서 장사하진 않을 거요!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "아마 할인해 줄 수 있을 거야. 하지만 그게 다가 아니지. 나는 네 단골 공급자가 되고 싶어. 원활하고 제때에 물건을 공급해 줄 것을 보장하지. 바스테르에 창고를 빌릴 거고, 너는 거기서 바로 물건을 받아볼 수 있어. 술도 항상 넉넉히 비축해 둘 테니 부족할 일 없을 거야. 할인까지 해서 가격은 이백사십 두블룬이야. 어때?";
				link.l1.go = "TPZ_Tavern2_4";
				Notification_Skill(true, 50, SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "좋아, 한 번 양보해서 한 번에 이백사십 두블룬으로 깎아주지. 나도 장기적인 거래를 원하거든. 앞으로 네가 필요로 하는 건 전부 맞춰줄 수 있고, 꾸준히 물건도 대줄 수 있어. 어때?";
				link.l1.go = "TPZ_Tavern2_7";
				Notification_Skill(false, 50, SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "그래도 예전보다 더 많이 내는 거군. 하지만 이제는 교훈을 얻었지 — 안정이란 그만한 값을 치를 만하니까. 네 조건에 동의하마, 하지만 명심해라: 한 번이라도 실수하면 다른 공급자를 찾을 거다. 내가 추가로 내는 돈이 뭔지 알아야겠어. 그리고 한 가지 더 — 당국은 어떻게 처리할 생각이지?";
			link.l1 = "지금 바로 처리할게. 모든 게 정리되면 물건을 가지고 다시 올게.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "부디 지체하지 마시오. 손님들 잔이 다시 가득 차는 걸 빨리 보고 싶으니.";
			link.l1 = "걱정 마, 오래 기다리게 안 할게.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "아직도 너무 비쌉니다, 선장님. 이 가격은 내가 예전에 거래하던 공급자에게 주던 것보다 더 높소. 지금은 동의한다 해도, 몇 달 후 생산이 재개되면 다시 그에게 돌아가야 할 것이오. 굳이 더 비싸게 살 이유가 없소.";
			link.l1 = "알겠소. 좋아. 내 마지막 제안이오 — 200 더블룬이오. 그게 마음에 들지 않으면, 이 대화를 계속할 이유가 없지.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "좋아, 거래하자. 이백이면 받아들이지. 그런데 말해봐, 섬 당국은 어떻게 처리할 생각이지? 전에 말했듯이, 총독이 밀수에 대해 섬을 엄격히 감시하고 있어. 그의 코앞에서 거래가 이뤄지는 걸 절대 용납하지 않을 거야.";
			link.l1 = "하하, 글쎄, 그 점은 나도 할 말이 있지. 하지만 안심하게나 — 모든 관료적 절차는 내가 신속하게 처리할 생각이네.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "부디 지체하지 마시오. 손님들 잔이 다시 가득 차는 걸 빨리 보고 싶으니.";
			link.l1 = "걱정 마, 오래 기다리게 하진 않을게.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "물론이죠, 선장님! 그래서, 화물 값을 얼마나 받고 싶으신가요?";
				link.l1 = "포도주 열 병마다 나는 두블룬 서른 개를 원하고, 럼주 열 병마다 다섯 두블룬을 받아야겠어. 전체로 각각 백 병씩이면, 전부 해서 삼백오십 두블룬이 들 거야.";
				link.l1.go = "TPZ_Tavern2_3";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				dialog.text = "죄송합니다, 선장님, 하지만 당신의 평판은 아직도 많이 부족합니다.";
				link.l1 = "젠장...";
				link.l1.go = "exit";
				Notification_Reputation(false, 40, "low");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "물론이지요, 선장님, 물론입니다! 약속대로 240 더블룬입니다. 여기 있습니다!";
				link.l1 = "거래해서 즐거웠어! 이제 선술집에 다시 럼주와 와인이 넘쳐나겠군.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "물론이죠, 선장님, 물론입니다! 약속대로 200 더블룬입니다. 여기 있습니다!";
				link.l1 = "거래해서 즐거웠어! 이제 선술집에 다시 럼과 와인이 넘쳐나겠군.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "당신은 내 구세주요, 선장님! 앞으로도 2주마다 비슷한 화물을 기대하겠소. 반드시 약속을 지켜주길 바라오. 또 그런 가뭄이 오면 내 주점은 살아남지 못할 거요...";
			link.l1 = "걱정할 필요 없어, "+npchar.name+". 내 도시 대표는 크리스티앙 들뤼스야. 그가 네 선술집에 와인이나 럼이 떨어지는 일이 없도록 해 줄 거다.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "크리스티안? 그 사람 알아. 책임감 있는 사람이긴 한데... 뭐, 됐다. 네가 당국과 문제를 해결했다니, 그를 믿어도 되겠지.";
			link.l1 = "훌륭하군. 이제 실례하겠소, 이 마을에서 처리할 일이 하나 더 있거든.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "자주 들러 주시오!";
			link.l1 = "반드시 그렇게 하겠소.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
