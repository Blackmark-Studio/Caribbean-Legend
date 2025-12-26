// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","우리가 방금 그 얘기를 하고 있었소. 당신이 잊은 모양이군...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사 간다고. 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음번에.","맞아요, 무슨 이유에선지 내가 잊어버렸군...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠소...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
