// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli servis için mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O zaman hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum sence? Bilmiyorum, hiçbir şey bilmiyorum.";

            link.l1 = "Sen tam bir şaşkınsın! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
