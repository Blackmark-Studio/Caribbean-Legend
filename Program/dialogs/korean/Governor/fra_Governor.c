// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("무슨 질문입니까?","무엇을 원하십니까?");
			link.l1 = RandPhraseSimple("중요한 것은 없습니다, 나리.","드릴 말씀이 없소, 용서하시오.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "유감이오만, 당신을 일에 고려할 수 없소. 지금은 함께 일하고 싶은 사람이 아니오. 안녕히 가시오.";
                link.l1 = "진심이신가요... 하지만 알겠습니다.";
                link.l1.go = "exit";
				break;
			}            
		break;		 		            
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
