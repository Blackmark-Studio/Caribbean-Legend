// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek, mi a kérdés?"), "Ez már a második alkalom, hogy megpróbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, sajnálom.", "Ne most. Rossz helyen és rossz idôben."), "Igaz, most nincs mit mondanom, sajnálom.",
                      "Majd késôbb megkérdezem.", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "Tudom, hogy a holland Nyugat-indiai Társaság vérdíjat tûzött ki egy bizonyos kalóz - Bartolomeo, a portugál - fejéért. Sikerült elfognom ôt. Jelenleg a raktérben van, és kész vagyok átadni ôt a hatóságoknak.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Már mindent elvettél. Mit akarsz még?", "Maradt még valami, amit nem vittél el?");
            link.l1 = RandPhraseSimple("Csak körülnézek...", "Csak ellenôrzöm, lehet, hogy elfelejtettem valamit...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "Bart, a portugál?! Elkaptátok, élve?!";
			link.l1 = "Tudom, hogy holtan semmi hasznát nem veszed. Életben van, és az istenek verjék meg, de meg kellett fékeznem magam, hogy így is maradjon!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "Kitûnô! Most már mindent el fog mondani nekünk... Mynheer, készítsd elô a foglyot az átszállításra. Azonnal küldünk egy katonai bárkát a hajójukra. ";
			link.l1 = "Elôször a jutalmamról szeretnék beszélni, Mynheer, ha nem bánod.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "Ne aggódjon a jutalma miatt, uram. Meg fogja kapni. Kijelöltünk egy árat Bartolomeo, a portugál fejéért - ezerötszáz dublont. Hadnagy úr! Hozza a kapitánynak a jutalmát!";
			link.l1 = "Hm... Hugo azt mondta, hogy kétezer dublont... Akkor rendben.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("Kaptál 1500 dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "És most, uram, lenne olyan kedves, és átadná a portugált a társaságnak? Nagyon szeretnénk beszélni vele.";
			link.l1 = "Persze, Mynheer, küldd a bárkát a hajómra.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
