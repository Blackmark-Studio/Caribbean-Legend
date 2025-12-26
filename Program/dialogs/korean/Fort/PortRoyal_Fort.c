// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("우리 요새가 어때 보이나? 괜찮지, 그렇지? 주둔군도 아직은 나쁘지 않다네, 하...","요새 병사의 삶이란 참으로 지루하지... 경계하고 순찰 돌고, 자고 쉬고, 또 그걸 반복하지. 하지만 마을에서는 다르지... 무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?"),"군인에게 쓸데없는 질문으로 귀찮게 하는 건 달가워하지 않소, "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 나에게 물으려 하는군...","군인이 된다는 건 쉽지 않소, 그런데도 또다시 여기 왔구려"+GetSexPhrase(", 이 멍청아,  "," ")+" 날 열 받게 하려는 거냐. 조심해라, 안 그러면 요새 지하실에 처박힐 테니...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 괜히 폐를 끼쳤군.","드릴 말씀이 없소, 미안하오."),"맞소, 사과하오.","맞아요, 벌써 세 번째군요. 실례했습니다.","미안하오, 아무것도 아니오.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
