// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("어떻게 도와드릴까요?","무슨 일이야?"),"무슨 일로 걱정이 있소, "+GetAddress_Form(NPChar)+"?","세 번째로, "+GetAddress_Form(NPChar)+", 뭐가 필요하지?","너 정말 지긋지긋하다. 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어, 미안하다.","별거 아니야, 미안하다."),"용서해, 아무것도 아니야.","맞아, 벌써 세 번째야. 미안하다...","실례했습니다.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
