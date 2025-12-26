// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsunuz?");
			link.l1 = RandPhraseSimple("Önemli bir şey yok, efendim.","Söyleyecek bir şeyim yok, özür dilerim.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Ne yazık ki, seni bir işe alamam. Şu anda seninle çalışmak istemiyorum. Hoşça kal.";
                link.l1 = "Ciddi olamazsınız... ama peki, öyle olsun.";
                link.l1.go = "exit";
				break;
			}            
		break;		        
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
