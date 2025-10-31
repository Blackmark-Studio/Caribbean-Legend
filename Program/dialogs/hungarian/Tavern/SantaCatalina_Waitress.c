// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kérdések, " + GetAddress_Form(NPChar) + "?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, mi a nagy ötlet, " + GetAddress_Form(NPChar) + "? ","Már megint a furcsa kérdések? Toots, menj, igyál egy kis rumot vagy valamit...") +"", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz..."+ GetSexPhrase(" Ezek a figyelem jelei?","") +"",
                          "További kérdések, gondolom, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam", "Jelenleg nincs mirôl beszélnem."), "Nem, nem szép...",
                      "Szó sem lehet róla, kedvesem...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Hogy aludt, uram? Miss MacArthur utasított minket, hogy biztosítsuk a teljes kényelmét!";
			link.l1 = "Nagyon furcsa álmom volt...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "Mi a baj, mademoiselle? Segíthetek valamiben?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Sajnálom, kapitány... Ez bûn, de nem tudok ellenállni! Nem vagyok túl tapasztalt, de ne tagadja meg a lányt, kapitány! Olyan jóképû vagy! Szeretnék a kedvében járni, megérinteni...";
			link.l1 = "Valóban, teljes kényelem... Te is nagyon szép vagy! Gyerünk, ne légy szégyenlôs.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Jobb, ha most nem ér hozzám, kisasszony - bûzlök a rumtól. De nekem tetszhet - a reggeli nagyon jól esne!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Ó, jaj, jaj, jaj!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Udvariatlanság!";
			link.l1 = "Akkor nincs reggeli?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
