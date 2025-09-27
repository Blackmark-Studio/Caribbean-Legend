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
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Szent atya, Marisa Calderát keresem. Azt mondják, nagyon vallásos és gyakran látogatta az egyházat. Meg tudná mondani, hol találhatom meg őt?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa az egyik leghűségesebb híve volt templomunknak, valódi lelke a gyülekezetnek. Hiánya nagy veszteség számunkra. Nem tudom, mi késztette őt arra, hogy eltűnjön, de biztos vagyok benne: igazságtalan próbatételek sújtották, s az ördög és szolgáinak keze is benne lehetett\nIdőnként hallani pletykákat, hogy látták őt a városban, de semmi biztosat. Csak Isten akaratában bízhatunk, és reméljük, hogy egyszer visszatér, s ismét vigaszt talál az egyház védelmében.";
			link.l1 = "Talán ismer valakit, aki többet tudna mesélni róla?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Fiam","Lányom")+", mondd el, miért keresed Marisát? Tudom, hogy időről időre olyan emberek kutatnak utána, akiknek megjelenése nem épp az igazakéhoz hasonlít. A világ tele van kísértéssel, és nem mindenki jó szándékkal keresi őt. Mielőtt bármit is mondanék, biztosnak kell lennem benne, hogy nem hozol veszélyt sem rá, sem azokra, akik körülötte vannak.";
			link.l1 = "Megértem aggodalmát, szent atya, de biztosíthatom: nincs bennem rossz szándék. Csak egy levelet szeretnék átadni, amely túl sokáig nem jutott el a címzetthez. Ki tudja, lehet, hogy fontos számára. Kérem, nézze meg.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Átadva: Levél Marisa Calderának", "None");
		break;
		
		case "LFD_Church_1_3":
			dialog.text = "Igen, ez a levél úgy tűnik, sok vihart és tengeri utat megélt, mielőtt hozzád került. Ki tudja, mi áll benne, és milyen következményei lesznek... De nemes dolgot cselekszel, kapitány, hogy visszajuttatod azt a címzettnek. Ha valaki tudja, hol lehet most Marisa, az csak a barátnője, Dolores Moño lehet — az egyetlen, akiben megbízott\nA háza a kikötői hivatal bal oldalán található. Remélem, ez a levél nem okoz neki újabb szenvedést, mert már így is sok megpróbáltatáson ment keresztül.";
			link.l1 = "Köszönöm, szent atya. Isten áldása legyen Önnel.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;
		
		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
