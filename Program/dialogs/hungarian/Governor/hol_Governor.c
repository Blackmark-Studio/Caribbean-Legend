// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit szeretne?");
				link.l1 = "Tudom, hogy a holland Nyugat-indiai Társaság jó árat szabott ki a híres kalóz - Bartolomeo, a portugál - fejéért. Sikerült elfognom ôt. Jelenleg a hajóm rakományában van, és kész vagyok átadni ôt a hatóságoknak.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mire van szüksége?");
			link.l1 = RandPhraseSimple("Semmi fontosat, uram.", "Nincs mit mondanom, elnézést.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Sajnos, nem tudom figyelembe venni önt egy munkára. Jelenleg nem akarok önnel dolgozni. Viszontlátásra.";
                link.l1 = "Ezt nem gondolhatja komolyan... de nagyon jó.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart a portugál?! Nálad van? Élve?";
			link.l1 = "Tudom, hogy holtan nem kell neked. Élve van. Sok erôfeszítést kellett tennem, hogy így is maradjon!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Kitûnô! Most már mindent el fog mondani nekünk... Mynheer, készítsd elô a foglyot az átszállításra. Azonnal küldünk egy katonai bárkát a hajójukra. ";
			link.l1 = "Elôször a jutalmamról szeretnék beszélni, Mynheer... ha nem bánod.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Ne aggódj a jutalmad miatt, kapitány. Meg fogja kapni. Kijelöltünk egy árat Bartolomeo, a portugál fejéért - ezerötszáz dublont. Hadnagy úr! Hozza a kapitánynak a jutalmát!";
			link.l1 = "Hm... Úgy tûnik, Hugo hazudott nekem kétezer dublonnal kapcsolatban... Akkor rendben.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("Kaptál 1500 dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "És most, kapitány, lenne szíves a portugált átadni a századnak. Alig várjuk, hogy beszélhessünk vele.";
			link.l1 = "Persze, mynheer, küldje a bárkát a hajómra.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
