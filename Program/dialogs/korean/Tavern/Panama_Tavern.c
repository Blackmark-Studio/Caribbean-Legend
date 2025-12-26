// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문에 대해 "+GetCityName(npchar.city)+" 항상 대기 중이오. 무엇을 알고 싶으시오?","우리가 방금 그 얘기를 하고 있었지. 네가 잊어버린 모양이군...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음에.","그래, 뭔가 때문에 깜빡했군...","그래, 진짜로 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "네 마을에 프랑수아 공티에라는 이름의 사략선장이 있다고 들었어. 혹시 어디서 그를 찾을 수 있는지 아나?";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "이봐, 나 베르트랑 피네트라는 남자를 찾고 있는데, 들어본 적 있어? 얼마 전에 파나마에 도착했어. 가발을 쓴 위엄 있는 신사야. 여기 왔던 적 있을지도 모르지...";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("그래, 그런 녀석이 우리 마을에 온 적 있지. 어두운 데서 어슬렁거리고 다녔어... 그러다 그의 동료 몇 명이 찾아왔는데, 전부 칼잡이들처럼 보였지. 그 녀석은 그들과 함께 마을을 떠났어.","그건 이미 물어봤고 내가 대답했잖아.","말했잖아, 너 그 곤티에에 대해 이미 물어봤어.","이봐, 그냥 가서 그만 귀찮게 해! 정신이 아주 나간 거 아니야?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그가 어디로 갔는지, 알고 있나?","음, 그런가 보군...","그래, 맞아, 내가 그렇게 부탁했지...","미안해, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "음, 여기서 걸어서 나갈 수 있는 길은 포르토벨로 하나뿐이야. 그리고 그는 그쪽으로 도망쳤지. 그러니 거기서 찾아봐.";
			link.l1 = "고마워, 정말 큰 도움이 되었어!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "베르트랑 피네트? 프랑스인? 들어본 적 없어. 아니, 이봐, 여기서는 한동안 프랑스 놈들 본 적도 없다네.";
			link.l1 = "정말 안타깝군... 확실한가? 그는 돈 카를로스 데 밀리아르라는 중요한 이달고의 친구야. 둘이 같이 여기 도착하기로 되어 있었지.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "미야르 나리? 그 신사라면 1년 전에 파나마를 방문했었지. 사실 카를로스 데 미야르 돈은 포르토벨로에 살고 있어. 그는 현지 총독과 아주 가까운 친구야.";
			link.l1 = "알겠어. 정글에서 시간과 힘을 낭비할 필요는 없었군. 고마워, 친구.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
