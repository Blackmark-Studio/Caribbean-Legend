// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("무슨 질문입니까?","무엇을 원하십니까?");
				link.l1 = "네덜란드 서인도 회사가 악명 높은 해적 포르투갈인 바르톨로메우의 목에 큰 현상금을 걸었다는 것을 알고 있소. 내가 그를 붙잡는 데 성공했소. 그는 현재 내 배의 선창에 있으며, 당국에 넘길 준비가 되어 있소.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("무슨 질문입니까?","무엇을 원하십니까?");
			link.l1 = RandPhraseSimple("중요한 것은 아무것도 없습니다, 나리.","드릴 말씀이 없소, 미안하오.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "유감이오, 지금은 그대에게 일을 맡길 수 없소. 현재로서는 함께 일하고 싶은 사람이 아니오. 안녕히 가시오.";
                link.l1 = "진심이신가요... 하지만 알겠습니다.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "포르투갈인 바트?! 그 자가 있소? 살아 있소?";
			link.l1 = "그가 죽을 필요 없다는 것쯤은 알고 있소. 그는 살아 있소. 그렇게 살려두려면 정말 큰 노력이 필요했소!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "대단히 훌륭하오! 이제 저자가 모든 것을 말할 것이오... 나리, 죄수를 이송할 준비를 하시오. 곧 군함을 당신 배로 보내겠소. ";
			link.l1 = "먼저 제 보상에 대해 이야기하고 싶습니다, 마인헤르... 괜찮으시겠습니까?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "보상은 걱정하지 마시오, 선장. 반드시 받게 될 것이오. 우리는 포르투갈인 바르톨로메오의 목에 현상금 1,500두블룬을 걸었소. 부관! 선장에게 보상을 가져오시오!";
			link.l1 = "흠... 휴고가 내게 이천 두블룬에 대해 거짓말을 한 것 같군... 좋아, 그렇다면.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제, 선장님, 포르투갈인을 회사로 넘겨주시겠습니까? 우리는 그와 대화할 날만을 손꼽아 기다리고 있소.";
			link.l1 = "알겠습니다, 나리. 바크선을 제 배로 보내십시오.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
