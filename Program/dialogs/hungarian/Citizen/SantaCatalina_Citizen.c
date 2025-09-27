// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Ki érdekli?","Kire gondolsz?","Nos, ki az?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Többet akarok tudni Jan Svensonról.";
				link.l1.go = "svenson";
			}
			link.l2 = "Váltsunk témát...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Hová szeretnél menni?","Mit keresel?","Mire van szüksége pontosan?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Hol van Jan Svenson háza?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Váltsunk témát...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Ó, a mi Jan Svensonunk nagyon fontos személy. Régen ô volt a Nyugati-fôtenger legdörzsöltebb kalóza, és még most sem rozsdásodik, ha! De azok az idôk elmúltak, már nem olyan aktív, mint régen. Van egy kúriája, ott él fiatal feleségével, és mindig szívesen látott vendég a kormányzó rezidenciáján. Sok vendég jön Janhoz, kalózok, fôleg kalózok.","Jan Svenson egy legenda Nyugat-Majna egyik legendája! Erdei ördög, így hívták ôt a spanyolok, amikor elüldözte ôket innen. Valaha híres korzsaír volt, de most már a mi kolóniánk megbecsült polgára\nBár még mindig csinál némi 'bizniszt' mellett, de már nem a saját kezével. Ritkán hagyja el a házát, mióta feleségül vett egy fiatal szépséget.");
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("Menjen egyenesen a mólótól a térig, a szökôkút melletti jobb oldali ház Svenson kúriája.","A kormányzói rezidenciától a téren keresztül menj a mólóhoz, a szökôkút mellett balra lévô ház Svenson kúriája.");
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
