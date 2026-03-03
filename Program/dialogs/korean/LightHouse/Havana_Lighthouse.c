// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("뭐 원하는 거야?","무엇을 알고 싶으신가?"),"무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?","그거, 벌써 세 번째로 나한테 물어보는 거야...","너한테 질렸으니까, 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("미안하지만, 마음이 바뀌었어.","별일 아니오, 미안하오."),"잊었네, 미안하군...","세 번째면 행운이 따르겠지, 응? 실례하네...","미안, 미안! 그럼 내가 알아서 나갈게...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 혹시 요아킴 메리만이라는 남자가 여기 온 적 있나? 그는 중년의 포르투갈 나리로, 콧수염과 염소수염에 날카로운 눈빛을 가졌지. 어쩌면 만이나 등대 근처에서 내렸을 수도 있는데, 그런 사람을 본 적 있나?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "아니, 그런 사람은 못 봤어. 봤다면 분명 기억했을 거야.";
			link.l1 = "알겠소, 안타깝군. 시간 내줘서 고맙소, 그럼 난 계속 찾아보겠소.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
