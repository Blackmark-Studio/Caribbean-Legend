// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("병사에게 무슨 질문이 있소?","병사는 평생을 계획대로 살아가지 - 경비 서고, 바쁘게 움직이고... 내가 뭘 도와주면 되나, "+GetAddress_Form(NPChar)+"?"),"군인에게 쓸데없는 질문으로 귀찮게 하지 마라, "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 나한테 질문하려고 하는군...","군인의 삶이란 쉽지 않지, 그런데 지금 너 같은 놈들이 나를 미치게 만드는구나...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었어...","지금은 할 말이 없어."),"알겠어...","그래, 네 말이 맞아, 벌써 세 번째야...","미안해...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
