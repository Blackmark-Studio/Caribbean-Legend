// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해 봐라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "장교, 'Cantavro' 선박의 장교 한 명이 여기 구금되어 있다는 소식을 들었소. 사실이오?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "또다시 돈 로페에 대해 물으러 왔소, 경비관. 그의 석방 명령서를 이미 받았소?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "'Cantavro'의 장교? 돈 로페 몬토로? 그래, 여기서 구금 중이다. 그래서 뭐 어쩌라고?";
			link.l1 = "그를 면회할 허가를 받고 싶소.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "실례합니다만, 무슨 근거로 그러시는 겁니까?";
			link.l1 = "그저 개인적인 일입니다. 유럽에서 그를 알았고, 그가 감옥에 갇혔다는 소식과 마을에 퍼진 소문에 충격을 받았습니다. 그와 이야기를 나누고 싶습니다.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "흠...";
			link.l1 = "장교 나리, 혹시 제가... 그를 면회하게 해준 것에 대해 '감사'를 표할 수 있을까요?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "그럴 필요 없소. 돈 몬토로와의 면담을 허락하겠소. 경비병들이 통과시켜 줄 것이오.";
			link.l1 = "감사합니다!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "확실히, 내 명령은 돈 로페 몬토로를 직접 사령관에게 인도하는 것이오. 하지만 그 자는 몇 주 동안 감방에서 나올 일 없을 거요. 그래도 아직 여기 있을 때 만나보고 싶으면 가도 되오.";
			link.l1 = "감사합니다, 장교 나리, 그래서 제가 여기 온 것입니다.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
