// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭘 원하지?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "혹시 에드가르도 소타 선장을 만난 적 있나? 그에 대해 뭔가 아는 게 있으면 말해 줄 수 있겠나? 꽤 알아둘 만한 인물인 것 같군.";
					link.l1.go = "Sotta1";
					link.l2 = "바람쟁이의 처형을 보러 안 갈 거야?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "말해 봐, 오늘의 영웅 에드가르도 소타 선장을 본 적 있어? 난 아쉽게도 못 봤어. 어떤 사람이야? 상인이 악명 높은 바람쟁이 맷을 잡았다니 믿기지가 않아!";
					link.l1.go = "Sotta1_1";
					link.l2 = "루터가 붙잡힌 걸 온 마을이 축하하는구만, 바다에 나가본 적도 없는 녀석들까지도."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "약 한 달 반 전에 제롬 소브르니에라는 자가 벨리즈에 도착했소. '글래스 아이'에서 싸움에 휘말려 다쳤지만 살아남았지. 그를 어디서 찾을 수 있는지 말해줄 수 있겠소?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "한 달 반쯤 전에, 벨리즈에 신사가 나타났어. 이름은 제롬 소베르니에였지. 다른 남자를 찾고 있었으니 분명 마을 사람들과 얘기를 나눴을 거야. 나중에 선술집 싸움에서 다쳤지만, 다행히 살아남았지. 혹시 그를 어디서 찾을 수 있는지 말해줄 수 있나?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "두 달쯤 전에 벨리즈에 도착한 남자를 찾고 있어. 이름은 제롬 소베르니에야. 어떤 신사를 찾고 있었다고 하던데, 아마 그 일로 마을 사람들과 이야기를 나눴을 거야...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 혹시 비밀 조직에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼, 안녕히 가시오.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 조사국처럼 보여? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁이구나! 꺼져.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "나는 그와 얘기하진 못했지만, 그의 배는 봤어. 무거운 갤리언이더군. 이 바다에서 혼자 항해하는 건 위험한데, 소타는 호위 없이도 잘 다니더라.";
			link.l1 = "아마도 금화 한 닢이라도 더 쫓으려고 여기저기서 비용을 아끼고 있겠지. 뭐, 더 붙잡진 않겠다. 좋은 하루 보내.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "그래, 믿기 힘들지! 하지만 들은 얘기 전부를 믿진 마시오, 나리. 나는 그를 직접 봤소, 지금 당신을 보는 것만큼 똑똑히. 그가 루터를 잡은 건 잘한 일이지만, 왜 이런 상인 행세를 하는 거지? 그는 군인처럼 행동하오. 나는 항상 알아볼 수 있지 – 내 친척이 수년간 군 복무를 했거든.";
			link.l1 = "흥미롭군. 뭐, 누구나 비밀은 있지. 난 이만 가봐야겠다. 정보 고마워.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "나는 이미 그 남자를 봤어. 수년간 우리 상인들을 공포에 몰아넣었던 그 해적이랑 같은 사람이라고는 믿기 힘들더라. 대체 어떻게 처음에 자기 함대를 맡게 된 거지? 군인들이 그를 호송하는 걸 봤는데, 소리 지르고, 울고, 웃고 있더군. 완전히 미친놈이야.";
			link.l1 = "아마 패배와 임박한 죽음의 현실이 그에게 너무 큰 짐이었겠지. 하지만 상관없어. 잘 가라!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "그래, 나도 축하하고 있지. 내 동포들 중 상당수가 그 자의 손에 죽었거든. 운 나쁜 놈들은 아버지, 형제, 아들을 잃었지 - 무슨 말인지 알겠지. 그런 야만적인 짓이 너무 오래 계속됐어! 내 생각엔, Matt는 최근 몇 년 사이에 가장 운 좋은 해적 중 하나였을 거야.";
			link.l1 = "운이라는 건 언젠가는 다 떨어지기 마련이지. 또 보자.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "나는 그런 사람을 모릅니다, 나리. 선술집에서 싸움은 거의 매일 있는 일이라서, 다친 놈들 하나하나를 다 기억하는 건 고생만 남는 일이죠.";
    		link.l1 = "알겠소, 고맙소. 행운을 빌겠소.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "소베르니에? 프랑스인이지... 그래, 그런 사람이 있었어. 나한테 도움을 청하러 왔지만, 내가 해줄 수 있는 게 없었지. 그 후로는 본 적 없어, 미안하군.";
    		link.l1 = "감사합니다. 그럼, 계속해서 사람들에게 물어보겠습니다.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "제롬 나리! 물론이죠, 물론 기억합니다. 그는 선술집 싸움에서 다쳤어요. 그때 이후로 다리 상처를 돌보느라 집을 거의 나서지 않아요.";
			link.l1 = "그 집이 어디에 있지?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "바로 여기야, 아주 가까워, 항만청 옆에 있어. 빨간 지붕 집이야. 거기서 그를 찾을 수 있을 거야.";
    		link.l1 = "고마워, 정말 큰 도움이 되었어! 행운이 함께하길 바란다!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
