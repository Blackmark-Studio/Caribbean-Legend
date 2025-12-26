// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("우리 요새가 어때 보이나? 괜찮아 보이지? 주둔군도 아직은 나쁘지 않지, 하...","요새 병사의 삶이란 참으로 지루하지... 경계하고 순찰 돌고, 자고 쉬고, 또 똑같은 일의 반복이지. 하지만 마을에서는 다르다네... 무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?"),"군인에게 쓸데없는 질문으로 귀찮게 하는 건 달가워하지 않소, "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 나에게 물으려 하는군...","군인이 된다는 게 쉽지 않은데, 또 이렇게 다시 왔구나"+GetSexPhrase(", 이 자식아,  "," ")+" 날 약 올리려고 하는군. 조심해라, 안 그러면 요새 지하 감옥에 처넣어 버릴 테니...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 괜히 신경 쓰이게 해서 미안하오.","드릴 말씀이 없소, 미안하오."),"맞소, 사과하오.","맞소, 벌써 세 번째군. 실례했소.","미안하오, 아무것도 아니오.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
