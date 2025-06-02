// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham, o co chodzi?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, gdy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Nie teraz. Złe miejsce i czas."),"Prawda, teraz nie mam nic do powiedzenia, przepraszam.","Zapytam, później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Już wszystko wziąłeś. Czego jeszcze chcesz?","Czy zostało jeszcze coś, czego nie zgarnąłeś?");
            link.l1 = RandPhraseSimple("Po prostu się rozglądam...","Sprawdzam tylko, mogłem zapomnieć coś zabrać...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
