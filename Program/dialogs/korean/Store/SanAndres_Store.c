// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해, 뭐 원하는가?","우리가 바로 그 얘기를 하고 있었소. 당신이 잊어버린 게 틀림없군...","오늘만 벌써 세 번째로 그 질문을 하시는군요...","이봐, 여긴 가게야. 사람들은 여기서 물건을 사지. 나 좀 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음 기회에.","맞아요, 무슨 이유에선가 잊고 있었네요...","그래, 정말 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
