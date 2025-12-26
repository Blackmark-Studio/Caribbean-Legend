// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 꺼내는군...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내가 마음을 바꿨다.","나한테 할 말 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "안녕하십니까. 프랑수아 곤티에 선장이 여기에서 등록했습니까? 그는 '라는 이름의 코르벳을 타고 포르토 벨로에서 출항했는데"+pchar.questTemp.Slavetrader.ShipName+"'.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("아니, 그렇지 않소. 그리고 코르벳 '"+pchar.questTemp.Slavetrader.ShipName+"'는 포트 로열에서 보이지 않았소.","이것에 대해 이미 물었고 내가 대답했소.","이미 이 곤티에라는 자에 대해 물어봤다고 말했소.","제발, 내 일에 방해하지 마시오!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("고맙소. 계속 찾아보겠소.","흠, 그래...","그래, 내가 정말로 물어봤지 ...","실례합니다, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
