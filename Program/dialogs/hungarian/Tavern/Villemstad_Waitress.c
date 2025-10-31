// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kérdések, " + GetAddress_Form(NPChar) + "?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, mi a nagy ötlet, " + GetAddress_Form(NPChar) + "? ","Már megint a furcsa kérdések? Toots, menj, igyál egy kis rumot vagy valamit...") +"", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz..."+ GetSexPhrase(" Ezek a figyelem jelei?","") +"",
                          "További kérdések, gondolom, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam", "Jelenleg nincs mirôl beszélnem."), "Nem, nem szép...",
                      "Nem kedvesem...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//--> Тайна Бетси Прайс
		case "TBP_BetsiPriceSex1":
			DoFunctionReloadToLocation("Villemstad_tavern_upstairs", "quest", "quest4", "TBP_Betsi_sex_2");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
