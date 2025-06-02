// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham, o co chodzi?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracującym nad sprawami kolonii, a ty wciąż mi przeszkadzasz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Nie teraz. Złe miejsce i czas."),"Prawda, nie mam teraz nic do powiedzenia, przepraszam.","Zapytam później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zabrałeś już wszystko. Czego jeszcze chcesz?","Zostało coś, czego nie zagrabiłeś?");
            link.l1 = RandPhraseSimple("Tylko się rozglądam...","Sprawdzam tylko, mogłem zapomnieć coś zabrać...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
