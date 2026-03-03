// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Söyle bana, "+GetAddress_FormToNPC(NPChar)+", yakın zamanda burada 'Santa Margarita' adlı kalyon var mıydı? Belki de bir korsanın ele geçirdiği bir gemi olarak?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli serviste mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O zaman hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şeyden haberim yok.";

            link.l1 = "Ne kadar da kafan karışık! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hayır, o isimde bir kalyon hatırlamıyorum. Burada bu kadar büyük gemileri nadiren görürüz.","Ne? Bir kalyon mu? Burada mı? Hiçbir fikrim yok.","Hayır efendim, o gemi son zamanlarda burada demirlemedi, en azından ben öyle bir şey hatırlamıyorum.");
			link.l1 = LinkRandPhrase("Peki...","Pekâlâ...","Anladım, ne yazık...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
