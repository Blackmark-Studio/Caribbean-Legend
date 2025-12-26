// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이, "+GetSexPhrase("아들아","내 딸")+"?","물어봐, 듣고 있으니까..."),"듣고 있다, 이제 말해라. "+GetSexPhrase("아들아","내 딸")+"...","세 번째로, "+GetSexPhrase("아들아","내 딸")+", 필요한 것이 있으면 말하시오.","성직자는 할 일이 많으니 네가 나를 방해하고 있군, "+GetSexPhrase("아들아","내 딸")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 아니오, 신부님..."),"드릴 말씀이 없소, 미안하오.","나중에 물어보겠소. 용서하시오, 신부님.","실례합니다, 신부님...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "성부님, 특별한 일로 찾아왔습니다. 최근에 가이 마르셰라는 사략선장이 귀하의 본당에 아주 귀한 물건을 바쳤다고 들었습니다.\n그것은 청금석이 박힌 황금 가슴십자가였다고 하는데, 사실입니까?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "오, 그래, 아들아! 이것은 우리 본당에서 가장 훌륭한 물건이란다. 내 평생 이렇게 훌륭한 것은 본 적이 없구나! 그런데 왜 묻는 것이냐, 아들아? 이 십자가에 왜 관심이 있느냐?";
			link.l1 = "신부님, 이 말씀은 마음에 들지 않으시겠지만, 이 십자가는 다른 본당에서 도난당했고 그 과정에서 성직자가 살해당했습니다. 이 물건을 당신께 가져온 자는 살인범입니다.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "우리는 모두 죄를 짓는다, 아들아. 그리고 성직자를 살해했다는 건 중대한 혐의다. 증거가 있느냐? 이 십자가는 어느 본당에서 도난당한 것이냐?";
			link.l1 = "내 말이 증거로 충분하지 않소? 이 십자가는 산티아고 본당에서 도난당한 것이니 반드시 돌려줘야 하오.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "산티아고? 그거 스페인 도시 아니냐? 아들아, 너 정말 나를 놀라게 하는구나...";
			link.l1 = "신부님, 하느님 앞에서는 모두가 평등합니다. 스페인인들도 우리와 마찬가지로 그리스도인이고, 나라 사이의 다툼이 신자들의 마음에 영향을 주어서는 안 됩니다. 이 십자가를 산티아고 본당에 돌려주시길 간청합니다.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "아들아, 이 십자가가 우리 교구를 위해 헌신적인 그리스도인들이 바친 선물이라는 걸 모르겠느냐?! 아니, 아들아, 네가 부탁하는 건 해줄 수 없구나.";
			link.l1 = "이 십자가 때문에 피가 흘려졌다는 게 신경 쓰이지 않나? 성직자의 피라면, 스페인 사람이든 아니든 상관없지.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "아들아, 너는 아무런 증거도 내보이지 않았으니, 내가 네 말을 맹목적으로 믿을 수는 없다. 십자가는 우리 본당에 남아 있을 것이다. 이것이 내 최종 결정이다. 게다가, 이 일에서 네가 스페인인을 도운 점이 나를 매우 불편하게 하는구나.";
			link.l1 = "그러면 그렇게 하겠습니다. 그럼 안녕히 계십시오, 신부님...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
