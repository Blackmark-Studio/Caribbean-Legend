// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham, jakie jest pytanie?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz pytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, zajmującym się sprawami kolonii, a ty wciąż mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Nie teraz. To nie miejsce ani czas."),"Prawda, teraz nie mam nic do powiedzenia, przepraszam.","Zapytam później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
