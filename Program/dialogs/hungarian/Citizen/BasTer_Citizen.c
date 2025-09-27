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
			link.l1 = "Többet akarok tudni Fadeyrôl, a moszkovitáról.";
			link.l1.go = "fadey";
			link.l2 = "Senkirôl, ne is törôdj vele.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Hová szeretnél menni?","Mit keresel?","Mire van szüksége pontosan?");
            link.l1 = "Hol van Fadey háza?";
			link.l1.go = "fadey_house";
			link.l2 = "Beszéljünk valami másról...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, egy fontos ember. Ô a helyi gyár tulajdonosa, és közel áll a basse-terre-i elôkelô élethez. Erôs akcentusa van, és nagyon szeret inni... de soha nem iszik.","Nagymenô és a kormányzó barátja. Fadey-nek van egy helyi gyára. Egy északi országból jött, messze, messze innen... Még a nevét sem tudom. Erôs keze van, és képes meginni egy egész hordó rumot, anélkül, hogy berúgna.");
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("A mólótól egyenesen menjetek a térig, a bal oldali ház Fadey kúriája.","A kormányzói rezidenciától a téren keresztül menj a mólóhoz, a jobb oldali ház a Fadey-kúria.");
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
