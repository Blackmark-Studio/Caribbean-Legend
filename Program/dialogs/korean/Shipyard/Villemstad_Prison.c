// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "장교 나리, 여기 바르톨로메우 포르투갈인이라는 죄수를 잡아두고 있지...";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "그래, 있다. 그런데 그게 왜 궁금하지? 네덜란드 서인도 회사의 사절만이 그를 만날 수 있고, 그것도 총독의 서면 명령이 있어야만 가능하다. 지금 회사 소속 장교 한 명이 이 해적을 심문하고 있다. 그냥 그를 보려고 온 거라면, 당장 나가라. 교수형 당할 때나 볼 수 있을 거다. 이제 가라.";
			link.l1 = "나는 그를 보러 온 게 아니오.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "그렇다면, 왜 그런지 물어봐도 되겠소?";
			link.l1 = "나는 여기 왔다... 그를 풀어주려고!";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
