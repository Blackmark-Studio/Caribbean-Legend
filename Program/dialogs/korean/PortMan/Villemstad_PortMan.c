// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했었지\n "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 꺼내는군...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마시오.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";

			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "노예 반란 이후 사라진 바크선에 대해 알고 싶소.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//Голландский гамбит, против всех
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "Toff Keller라는 이름의 선장을 찾고 싶소. 그는 'Leiden'이라는 플루이트선을 소유하고 있소. 그가 윌렘스타드에 자주 온다고 들었으니, 나를 도와주는 것이 어렵지 않을 것이오.";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		//работорговец
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "흠... 그런데 왜 그게 궁금하지? 흑인들이 네 전문 분야라도 되나?";
				link.l1 = "나는 총독 마티아스 벡의 명령을 받고 이곳에 왔소. 도망친 흑인들이 그 배를 훔쳐 달아났다고 의심할 만한 충분한 이유가 있소. 그러니 내가 수색하는 데 있어 가능한 모든 방법으로 협조해 주기를 바라오.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "알겠소. 하지만 도와줄 수 없소. 바크선 '"+pchar.questTemp.Slavetrader.ShipName+"'는 아침이 되자 사라졌고, 아무도 아무것도 보지 못했소. 나는 집에서 자고 있었소. 부두 경비원도 흔적도 없이 사라졌지.\n총독이 흔적이 남아 있을 때 추격하려고 슬루프를 보냈지만, 빈손으로 돌아왔소. 흑인들이나 '의 흔적도 없었소."+pchar.questTemp.Slavetrader.ShipName+"'. 솔직히 말해서, 슬루프는 그들을 별로 꼼꼼히 수색하지 않았소. 모두가 여전히 공포에 휩싸여 있었고, 카피르들이 갈고리와 마체테를 들고 정글에서 튀어나와 백인의 피를 갈구할까 두려워했으니 말이오.";
				link.l1 = "별로 도움이 되진 않았지만, 그래도 고마워. 안녕.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		//Голландский гамбит
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "토프 켈러? 물론 알지! 그는 트리니다드에 있는 산호세와 쿠마나로 자주 항해해. 최근에도 트리니다드로 갔었어. 아마 거기서 그를 찾을 수 있을 거야.";
			link.l1 = "고맙소!";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
