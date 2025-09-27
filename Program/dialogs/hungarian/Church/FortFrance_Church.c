// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Szentatya, Benoit apátot keresem, sürgôs dolgom van vele. Meg tudná mondani, hol találom?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "Benoit apát elhagyta a várost az egyházi ügyek miatt az újvilági spanyol katolikus misszió képviselôivel. Nem ismerek részleteket, de Benoit apát elég sokáig van távol ahhoz, hogy feltételezzem, a tárgyalások elhúzódtak, vagy valami történt útközben. Mindannyian rosszul érezzük magunkat, de csak imádkozhatunk és várhatjuk a híreket.";
			link.l1 = "Nem feltételezhetjük, hogy minden könnyen megy. Szentatya, meg tudná mondani, hogy pontosan hová ment Benoit apát? Meg kell találnom ôt, amilyen gyorsan csak lehet.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Attól tartok, nem tudom, fiam. Amennyire én tudom, Benoit apát elment tárgyalni Új-Spanyolország püspökével és az inkvizíció prelátusával, Vincento Palotti atyával, de nem mondta meg, hogy hol lesz a találkozó.";
			link.l1 = "Ennyi elég lesz, Szentatya, köszönöm. Ismerem Palotti atyát valamilyen módon... Körülnézek Santiagóban.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
