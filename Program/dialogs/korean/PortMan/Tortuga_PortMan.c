// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 이 질문을 꺼내는군...","봐라, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","할 말이 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "안녕하십니까. 저는 프랑수아 곤티에를 찾고 있습니다. 그의 코르벳 '"+pchar.questTemp.Slavetrader.ShipName+"' 분명 이 항구에 있었던 게 틀림없소.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("흠... 실망시켜 드려야겠군요. 코르벳함 '"+pchar.questTemp.Slavetrader.ShipName+" 여기에 온 적이 없고, 프랑수아 곤티에도 이곳에 등록하지 않았소.","이것에 대해 이미 물었고 내가 대답했소.","이미 말했잖아, 이 곤티에르에 대해서는 벌써 물어봤지.","제발, 내 일에 방해하지 마시오!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("고맙소. 계속 찾아보겠소.","음, 그래...","그래, 내가 정말로 부탁했지 ...","실례합니다, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
