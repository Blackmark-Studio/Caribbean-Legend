// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해, 뭘 원하는가?","우리가 방금 그 얘기를 하고 있었소. 당신이 잊은 게 틀림없군...","오늘만 세 번째로 또 뭔가를 물어보시는군요...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다고. 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음 기회에.","맞아요, 왠지 까먹고 있었네요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 보시오, 후안이라는 이름이 당신에게 의미가 있소?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "1654년 4월, 미겔 디초소 선장이 지휘하는 프리깃함이 당신 항구에 정박한 뒤 그가 사라졌소. 그 이름이 기억나오? 혹시 그가 당신에게서 상품을 샀거나 무슨 말을 하지는 않았소...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "아이고, 그만 좀 하시오, 선장! 오늘만 해도 후안 두 명이 내 가게에 왔고, 어제도 또 한 명이 왔소. 내가 그 사람들 하나하나 다 기억해야 한단 말이오?";
			link.l1 = "좋소. 귀찮게 해서 미안하오...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "아이고, 선장님, 그동안 정말 많은 프리깃과 갤리온이 오가더이다, 미겔도 카를로스도...";
			link.l1 = "그렇군. 그러면 아무런 도움이 못 되는 거로군...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
