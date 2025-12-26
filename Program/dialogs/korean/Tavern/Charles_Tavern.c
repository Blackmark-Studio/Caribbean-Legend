// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 이 질문을 네가 벌써 세 번째 꺼냈다...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "발렛이라는 별명을 가진 남자를 찾고 있어. 아는가?";
				link.l1.go = "valet_1";
				link.l2 = "나는 '마를린'이라는 폴라크르 선장의 행방을 찾고 있는데, 어디서 그를 만날 수 있는지 알려줄 수 있나?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("아니, 나는 몰라. 그러니 내가 도와줄 수 있는 건 없어.","이미 말했다니까, 난 모른다고!","술에 취했나, 아니면 그냥 장난치는 거야?","날 내버려 둬!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그렇군. 아쉽네...","안타깝군. 기억할 줄 알았는데...","나 안 취했어! 그냥 끈질길 뿐이야...","흠...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("아, David Fackman 나리! 그는 조선소에서 멀지 않은 곳에 집을 세놓고 있소. 거기서 그를 찾아보시오.","방금 대답했잖아. 내 말 듣고 있었어?","술에 취했나, 아니면 그냥 장난치는 거야?","날 내버려 둬!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("감사합니다!","그래. 미안해.","나 안 취했어! 그냥 끈질긴 거야...","흠...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
