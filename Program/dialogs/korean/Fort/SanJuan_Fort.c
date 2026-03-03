// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("우리 요새가 어때 보이나? 괜찮지, 그렇지? 주둔군도 아직은 나쁘지 않다네, 하...","요새 병사의 삶은 꽤나 지루하지... 경계하고 순찰 돌고, 자고 쉬고, 그리고 또 똑같은 일의 반복이지. 하지만 마을에서는 다르다네... 무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?"),"군인에게 쓸데없는 질문으로 귀찮게 하는 것은 환영받지 않는다, "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 나에게 물어보는군...","군인이 된다는 건 쉬운 일이 아니오, 그런데도 또다시 여기 있군."+GetSexPhrase(", 이 멍청아,  "," ")+" 나를 약 올리려고 하는군. 조심해라, 아니면 요새 지하 감옥에 처박힐 테니...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 괜히 신경 쓰이게 했군.","드릴 말씀이 없소, 미안하오."),"맞소, 사과하오.","맞소, 벌써 세 번째군. 실례했소.","미안하오, 아무것도 아니오.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
