// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você precisa?");
			link.l1 = RandPhraseSimple("Nada de importante, senhor.","Não tenho nada a dizer, desculpe.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Infelizmente, não posso lhe oferecer um trabalho. No momento, você não é alguém com quem eu queira trabalhar. Adeus.";
                link.l1 = "Você não pode estar falando sério... mas tudo bem.";
                link.l1.go = "exit";
				break;
			}            
		break;		 		            
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
