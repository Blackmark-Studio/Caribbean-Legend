// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("우리 요새가 어떻소? 괜찮아 보이지, 그렇지? 주둔군도 그에 못지않게 훌륭하오, 하...","요새 병사의 삶이란 참으로 지루하지... 경계 근무와 순찰, 자고 쉬고, 그리고 또 똑같은 일의 반복이지. 하지만 마을에서는 다르다네... 무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?"),"군인에게 쓸데없는 질문으로 귀찮게 하는 건 환영받지 못하오, "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 나에게 묻는군...","군인으로 산다는 게 쉽지 않은데, 또다시 이렇게 왔구나"+GetSexPhrase(", 이 멍청이,  "," ")+" 나를 열받게 하려는 거냐. 조심해라, 안 그러면 이 요새 지하실에 처박힐 테니...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 괜히 폐를 끼쳤군.","드릴 말씀이 없소, 미안하오."),"맞소, 사과하오.","맞아요, 벌써 세 번째군요. 실례했습니다.","미안하오, 아무것도 아니오.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
