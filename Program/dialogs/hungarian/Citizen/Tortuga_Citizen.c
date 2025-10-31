// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Nem ismer véletlenül egy bizonyos Joep van der Vinket, ugye?";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Azt hiszi, hogy a "+NationNameGenitive(sti(NPChar.nation))+"titkosszolgálatának dolgozom?";
			link.l1 = "Nos... nem. Akkor viszlát.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Úgy nézek ki, mint a nyomozóiroda? Nem tudom, nem tudok semmit.";

            link.l1 = "Maga olyan zavarosfejû! Távozz.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "Nos, személyesen nem ismerem, de idônként látom itt. Miért kérdezi?";
			link.l1 = "Megbíztak, hogy személyesen adjak át neki egy csomagot. De senki sem akar beszélni róla, és nem tudom, miért. És maga tudja? Rossz ember? Értékelném az ôszinte véleményét.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Ismétlem, nem ismerjük egymást személyesen, így szinte semmit sem tudok. De van egy közeli barátja a városban, és gyakran látjuk ôket együtt. Menjen el hozzá - ô majd eldönti, hogy többet mond-e magának vagy sem. A haverját Rober Martene-nek hívják.";
			link.l1 = "Rober Martene, azt mondja... És ô kicsoda? Hol találom meg?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Különbözô helyeken, de most éppen a világítótornyunknál van - egy szörnyû vihar után javítja a gályáját. It's called the 'Voltigeur'.";
			link.l1 = "Köszönöm szépen! Fogalmad sincs, mennyit segítettél nekem.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
