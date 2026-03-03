// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일로 왔소? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"사실 지금은 드릴 말씀이 없소, 미안하오.","나중에 물어보겠소.","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "네덜란드 서인도 회사가 어떤 해적, 즉 포르투갈인 바르톨로메오의 목에 현상금을 걸었다는 것을 알고 있소. 내가 그를 붙잡는 데 성공했소. 현재 그는 내 화물창에 있으며, 당국에 인도할 준비가 되어 있소.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 이제 무엇을 더 원하시오?","아직 가져가지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그냥 둘러보고 있을 뿐이오...","그냥 확인하는 중이오, 뭔가 깜빡하고 안 챙겼을 수도 있으니...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "포르투갈인 바트?! 그를 살아서 데려왔단 말이오?!";
			link.l1 = "그가 죽으면 당신에게 아무 쓸모도 없다는 것쯤은 알고 있소. 그는 살아 있소, 그리고 맙소사, 내가 그를 살려두려고 참느라 애를 썼소!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "대단히 훌륭하오! 이제 그가 모든 것을 말할 것이오... 나리, 죄수를 이송할 준비를 하시오. 곧 군함을 당신 배로 보내겠소. ";
			link.l1 = "먼저 제 보상에 대해 이야기하고 싶습니다, 나리. 괜찮으시겠습니까?";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "보상에 대해서는 걱정하지 마시오, 나리. 반드시 받게 될 것이오. 우리는 포르투갈인 바르톨로메오의 목에 현상금 1,500두블론을 걸었소. \n중위! 선장께 보상을 가져오시오!";
			link.l1 = "흠... 위고가 내게 이천 두블룬이라고 했었지... 좋소, 그러면.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제, 나리, 포르투갈인을 회사로 인도해 주시겠습니까? 우리가 그와 꼭 이야기를 나누고 싶소.";
			link.l1 = "알겠습니다, 나리. 바크선을 제 배로 보내주십시오.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
