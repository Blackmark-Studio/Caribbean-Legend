// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kérdést már régen nem tett fel senki egy Tortuga üzletben...",
                          "Kérdések, kérdések és még több kérdés...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Rendben, szóval régen volt már.", "Moooore kérdések, igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Figyelj, meg kell találnom egy Gaius Marchais-t. Ahogy mondták, lekötötte a kalózkodás, és tisztességes tárgyalóféllé vált, egy kiváló gályát szerzett a spanyoloktól. Nem vásárolt véletlenül valamilyen árut tôletek kereskedelmi céllal?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Ó igen, persze, hogy emlékszem rá! De nem vásárolt semmit. Felajánlotta a hajóját fuvarozásra. Nekem történetesen egy tágas raktérrel rendelkezô hajóra volt szükségem - egy nagy tétel nyersbôrre.";
			link.l1 = "És mi volt a kirakodási hely?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Igen, ott. Köszönöm, nagyon sokat segített nekem!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Bármikor, kapitány. Bármikor beugorhat a boltomba, amikor csak akar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
